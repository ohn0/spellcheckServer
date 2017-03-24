#include "spellchecker.h"

struct data_queue socket_queue;
char* OK = " OK\n";
char* MISSPELLED = " MISSPELLED\n";
char ** dictionary;
void *worker();
int main(int argc, char** argv){
	socket_queue.current_pos = 0;
	socket_queue.top = 0;
	sem_init(&(socket_queue.full), 0, Q_SIZE);
	sem_init(&(socket_queue.empty), 0, 0);
	pthread_t workers[NUM_THREADS];
	struct sockaddr_in client;
	int clientlen = sizeof(client);
	int port, listener, connfd;
	if(argc == 2 ){
		if((dictionary = load_dictionary(argv[1]) == NULL)){
			//Assuming the only argument user passed was a port.
			port = atoi(argv[1]);
			dictionary = load_dictionary(DEFAULT_DICTIONARY);
		}else{
			//Assuming only argument user passed was a valid dictionary.
			port = DEFAULT_PORT;
		}		
	}
	if(argc == 3){
		printf("Began working!\n");
		if((dictionary = load_dictionary(argv[1])) == NULL){
			printf("Error opening dictionary.\nFormat: dictionary, port number.\n");
			return 0;
		}
		port = atoi(argv[2]);
	}
	//dictionary = load_dictionary(argv[1]);
	listener = open_listenfd(port);
	int i;
	for(i = 0; i < NUM_THREADS; i++){
		//pthread_create(&workers[i], NULL, worker, NULL);
	}
	while(1){
		connfd = accept(listener, (struct sockaddr *) &client, &clientlen);
		add_to_queue(connfd, &socket_queue);
		pthread_t worker_thread;
		pthread_create(&worker_thread, NULL, worker, NULL);
	}
}

void * worker(){
	int connfd = remove_from_queue(&socket_queue);	
	char buffer[200];
	char buffer2[200];
	int j = 0;
	int c = 0;
	printf("worker has received socket %d to consume.\n", connfd);
	int rec_size = recv(connfd, buffer, 200, 0);	
	if(rec_size == 2){
		while(buffer[0] != '\n'){
			buffer2[j] = buffer[0];
			recv(connfd, buffer,1,0);
			j++;
		}
		buffer2[j-1] = '\0';
	}else if(rec_size > 2){
		while(buffer[j] != '\n'){
			buffer2[j] = buffer[j];
			j++;	
		}
		buffer2[j-1] = '\0';
	}
	printf("%s\n", buffer);
	int result = search_dictionary(dictionary, buffer2);
	if(result == 1){
		strcat(buffer2, OK);
		send(connfd, buffer2, strlen(buffer2),0);
	}
	else{
		strcat(buffer2, MISSPELLED);
		send(connfd, buffer2, strlen(buffer2), 0);
	}
	close(connfd);
}
