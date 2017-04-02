#ifndef _SYNCHRONIZE_H
#define _SYNCHRONIZE_H
#include <pthread.h>
#include <semaphore.h>
#define Q_SIZE 100
struct data_queue{
	//Struct that holds the queue and it's synchronization resources.
	//current_pos is what the producer will use to keep track of the current open slot.
	//top is used by the consumer to keep track of the next workable slot.
	//Semaphore full is used to indicate the size of the queue, blocking the producer if there are no more slots.
	//Semaphore empty is used to let the consumer take something off the queue.
	//mutex_dict is used to ensure only one thread can search the dictionary.
	int current_pos;
	int top;
	int queue[Q_SIZE];
	int Q_count;
	sem_t full;
	sem_t empty;
	pthread_mutex_t mutex_dict;
};

int add_to_queue(int, struct data_queue*);
int remove_from_queue( struct data_queue*);

#endif
