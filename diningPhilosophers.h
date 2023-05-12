#ifndef _DINING_PHILOSOPHERS_H
#define _DINING_PHILOSOPHERS_H

#include <pthread.h>

#define N 5

typedef enum { THINKING, HUNGRY, EATING } State;

typedef struct {
    State states[N];
    pthread_mutex_t mutex;
    pthread_cond_t conds[N];
} Monitor;

void init_monitor(Monitor *monitor);
void take_chopsticks(Monitor *monitor, int i);
void put_chopsticks(Monitor *monitor, int i);

#endif
