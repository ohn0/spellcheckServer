#include "synchronize.h"

int add_to_queue(int value, struct data_queue* socket_queue)
{
	sem_wait(&(socket_queue->full));
	socket_queue->queue[socket_queue->current_pos] = value;
	socket_queue->current_pos = ((socket_queue->current_pos+1) % Q_SIZE);
	socket_queue->Q_count++;
	sem_post(&(socket_queue->empty));
	return 1;
}


int remove_from_queue( struct data_queue* s_queue){
	int my_val;
	sem_wait(&(s_queue->empty));
	my_val = s_queue->queue[s_queue->top];
	s_queue->queue[s_queue->top] = -1;
	s_queue->top = ((s_queue->top+1) % Q_SIZE);
	s_queue->Q_count--;
	sem_post(&(s_queue->full));
	return my_val;
}
