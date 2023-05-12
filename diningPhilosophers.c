#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "diningPhilosophers.h"

Monitor monitor;

// inicializa o monitor
void init_monitor(Monitor *monitor) {
    pthread_mutex_init(&monitor->mutex, NULL); // inicializa o mutex
    for (int i = 0; i < N; i++) {
        monitor->states[i] = THINKING; // inicializa todos os estados como "pensando"
        pthread_cond_init(&monitor->conds[i], NULL); // define as condiçĩes iniciais como nulas
    }
}

// verifica se o filósofo i pode pegar os palitos para começar a comer
void test(Monitor *monitor, int i) {
    // verifica se ele está com fome e se os filosofos ao lado não estão se alimentando
    if (monitor->states[i] == HUNGRY &&
        monitor->states[(i + N - 1) % N] != EATING &&
        monitor->states[(i + 1) % N] != EATING) {
        monitor->states[i] = EATING; // atualiza o estado do filosofo para se alimentando
        pthread_cond_signal(&monitor->conds[i]); // tira a thread associada da espera
    }
}

// função para o filosofo pegar o palito
void take_chopsticks(Monitor *monitor, int i) {
    pthread_mutex_lock(&monitor->mutex); // o mutex trava para evitar um conflito
    monitor->states[i] = HUNGRY; // seta para o estado "faminto"
    test(monitor, i); // testa se o filosofo pode comer
    while (monitor->states[i] != EATING) { // caso não possa, ele entra em espera
        pthread_cond_wait(&monitor->conds[i], &monitor->mutex);
    }
    pthread_mutex_unlock(&monitor->mutex); // libera o mutex
}

// função para devolver o palito
void put_chopsticks(Monitor *monitor, int i) {
    pthread_mutex_lock(&monitor->mutex); // trava o mutex
    monitor->states[i] = THINKING; // seta para o estado "pensando"
    // testa os filosfos que estão ao seu lado
    test(monitor, (i + N - 1) % N);
    test(monitor, (i + 1) % N);
    pthread_mutex_unlock(&monitor->mutex); // libera o mutex
}

// thread de um filosofo
void *philosopher(void *arg) {
    int i = *(int *)arg; // seta qual filosofo é 
    while (true) {
        // inicializa ele como pensando
        printf("Philosopher %d is thinking.\n", i); 
        sleep(rand() % 10 + 1); // delay 
        // pega o palito
        take_chopsticks(&monitor, i);
        printf("Philosopher %d is eating.\n", i);
        sleep(rand() % 10 + 1); // delay
        // devolver o palito
        put_chopsticks(&monitor, i);
    }
}

int main() {
    // define as threads e a quantidade de threads
    pthread_t threads[N];
    int indices[N]; // seta os indices dos filosofos
    for (int i = 0; i < N; i++) {
        indices[i] = i;
    }
    // chama a função que inicializa o monitos
    init_monitor(&monitor);
    // cria as threads
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &indices[i]);
    }
    // espera que elas terminem
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
