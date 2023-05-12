#ifndef _DINING_PHILOSOPHERS_H
#define _DINING_PHILOSOPHERS_H

#include <pthread.h>

#define N 5 // define a quantidade de filósofos

typedef enum {THINKING, HUNGRY, EATING} State; // define todos os estados possíveis dos filósofos

// cria a struct do monitor
typedef struct {
    State states[N]; // vetor que armazena um estado para cada filosofos 
    pthread_mutex_t mutex; // mutex, que garante a exclusão mútua
    pthread_cond_t conds[N]; // vetor de variáveis condicionais para sincronizar as threads.
} Monitor;

void init_monitor(Monitor *monitor); // inicaliza o monitor
void take_chopsticks(Monitor *monitor, int i); // pegar os palitos 
void put_chopsticks(Monitor *monitor, int i); // devolver os palitos

#endif
