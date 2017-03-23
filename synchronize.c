#include "synchronize.h"

int add_to_queue(int value, struct data_queue* queue)
{
	sem_wait(&(queue->full));
	queue->queue[queue->current_pos] = value;
	queue->current_pos = (queue->current_pos % 200)+1;
	sem_post(&(queue->empty));
	return 1;
}


int remove_from_queue(int value, struct data_queue*){
	int my_val;
	sem_wait(&(queue->empty));
	my_val = queue->queue[queue->top];
	queue->top = (queue->top % 200)+1;
	sem_post(&(queue->full));
	return my_val;
}
