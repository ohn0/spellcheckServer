#include "synchronize.h"

int add_to_queue(int value, struct data_queue* socket_queue)
{
	//Add value to socket_queue's queue.
	//Need to first check that there is room on the queue to append value.
	//Once access is obtained, add the value into the queue and update position.
	//At the end, send a signal to a blocked worker that there is work to be done.
	sem_wait(&(socket_queue->full));
	socket_queue->queue[socket_queue->current_pos] = value;
	socket_queue->current_pos = ((socket_queue->current_pos+1) % Q_SIZE);
	sem_post(&(socket_queue->empty));
	return 1;
}


int remove_from_queue( struct data_queue* s_queue){
	//Take a value off s_queue and return it.
	//First need to ensure that there is work that needs to be done on the queue.
	//Once access is obtained, copy the value at top into a local variable.
	//Once done, update the number of empty slots on the queue, potentially waking up a producer.
	int my_val;
	sem_wait(&(s_queue->empty));
	my_val = s_queue->queue[s_queue->top];
	s_queue->queue[s_queue->top] = -1;
	s_queue->top = ((s_queue->top+1) % Q_SIZE);
	s_queue->Q_count--;
	sem_post(&(s_queue->full));
	return my_val;
}
