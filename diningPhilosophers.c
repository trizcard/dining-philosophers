#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "diningPhilosophers.h"

Monitor monitor;

void init_monitor(Monitor *monitor) {
    pthread_mutex_init(&monitor->mutex, NULL);
    for (int i = 0; i < N; i++) {
        monitor->states[i] = THINKING;
        pthread_cond_init(&monitor->conds[i], NULL);
    }
}

void test(Monitor *monitor, int i) {
    if (monitor->states[i] == HUNGRY &&
        monitor->states[(i + N - 1) % N] != EATING &&
        monitor->states[(i + 1) % N] != EATING) {
        monitor->states[i] = EATING;
        pthread_cond_signal(&monitor->conds[i]);
    }
}

void take_chopsticks(Monitor *monitor, int i) {
    pthread_mutex_lock(&monitor->mutex);
    monitor->states[i] = HUNGRY;
    test(monitor, i);
    while (monitor->states[i] != EATING) {
        pthread_cond_wait(&monitor->conds[i], &monitor->mutex);
    }
    pthread_mutex_unlock(&monitor->mutex);
}

void put_chopsticks(Monitor *monitor, int i) {
    pthread_mutex_lock(&monitor->mutex);
    monitor->states[i] = THINKING;
    test(monitor, (i + N - 1) % N);
    test(monitor, (i + 1) % N);
    pthread_mutex_unlock(&monitor->mutex);
}

void *philosopher(void *arg) {
    int i = *(int *)arg;
    while (true) {
        printf("Philosopher %d is thinking.\n", i);
        sleep(rand() % 10 + 1);
        take_chopsticks(&monitor, i);
        printf("Philosopher %d is eating.\n", i);
        sleep(rand() % 10 + 1);
        put_chopsticks(&monitor, i);
    }
}

int main() {
    pthread_t threads[N];
    int indices[N];
    for (int i = 0; i < N; i++) {
        indices[i] = i;
    }
    init_monitor(&monitor);
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &indices[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
