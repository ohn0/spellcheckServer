#ifndef _SYNCHRONIZE_H
#define _SYNCHRONIZE_H
#include <pthread.h>
#include <semaphore.h>

struct data_queue{
	int current_pos;
	int queue[200];
	sem_t full;
	sem_t empty;
	pthread_mutex_t control_mutex;

};

int add_to_queue(int, struct data_queue*);
int remove_from_queue(int, struct data_queue*);

#endif
