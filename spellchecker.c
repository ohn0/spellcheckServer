#include "spellchecker.h"

struct data_queue socket_queue;
char* OK = " OK\n";
char* MISSPELLED = " MISSPELLED\n";
char* NEXT_WORD = "Enter next word or EOF to quit.\n";
char ** dictionary;
int main(int argc, char** argv)
{
	//First initialize the port number and dictionary, which the user can specify, if they want.
	//Connect to the port and begin listening.
	//If a connection comes in, a worker thread will be created to service that request, repeat until server closes.

	//Initialize the queue_structs values and semaphores.
	socket_queue.current_pos = 0;
	socket_queue.top = 0;
	socket_queue.Q_count = 0;
	sem_init(&(socket_queue.full), 0, Q_SIZE);
	sem_init(&(socket_queue.empty), 0, 0);
	pthread_mutex_init(&socket_queue.mutex_dict, NULL);
	//Initialize the socket struct that will hold the information for the connected socket.
	struct sockaddr_in client;
	unsigned int clientlen = sizeof(client);
	int port, listener, connfd;
	//flags to ensure user enters valid port number and file.
	int validport ,validdict;
	validport = validdict = 0;
	if(argc == 1){
		//User specified no port or file.
		dictionary = load_dictionary(DEFAULT_DICTIONARY);
		port = DEFAULT_PORT;
		printf("No dictionary or port number specified, using default port and dictionary.\n");
		validport = validdict = 1;
	}
	else{
		//Parse arguments and set port and dictionary to user's values if they are valid.
		int i;
		for(i = 0; i != argc - 1; i++){
			if(strcmp(argv[i], "-p") == 0){
				port = atoi(argv[i+1]);
				if(port < 10000 || port > 65536){
					printf("Invalid port, using default.\n");
					port = DEFAULT_PORT;
				}
				validport = 1;
			}
			else if(strcmp(argv[i], "-d") == 0){
				if((dictionary = load_dictionary(argv[i+1])) == NULL){
					printf("invalid dictionary, using default.\n");
					dictionary = load_dictionary(DEFAULT_DICTIONARY);
				}
				validdict = 1;
			}
		}

	}

	if(!validport || !validdict){
		printf("Error loading dictionary or getting port number. format: -p PORT -d DICTIONARY.\n");
		return 0;
	}
	listener = open_listenfd(port);
	//Begin listening for incoming requests and creating threads to work on them.
	while(1){
		connfd = accept(listener, (struct sockaddr *) &client, &clientlen);
		add_to_queue(connfd, &socket_queue);
		pthread_t worker_thread;
		pthread_create(&worker_thread, NULL, worker, NULL);
	}
	free_dictionary(dictionary);
}

void * worker(){
	//Thread that opens a line to a client, the client will send a word which the thread will 
	//check to ensure it is spelled correctly.
	int connfd = remove_from_queue(&socket_queue);	
	char buffer[200];
	char buffer2[200];
	int j = 0;
	printf("worker has received socket %d to consume.\n", connfd);
	//Begin receiving data from client.
	int rec_size = 0; 
	//Depending on the client's telnet, the data they send could either come as one line, or as a 
	//byte everytime recv is called. This is handled by inspecting rec_size and copying the right
	//number of bytes depending on the situation.
	while(1){
		j = 0;
		memset(buffer, 0, 200);
		memset(buffer2, 0, 200);
		rec_size = recv(connfd, buffer, 200,0);
		if(buffer[0] == EOF){break;}
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
		//Check if buffer2 is a valid word and respond accordingly, then close the connection.
		//Need a mutex here because search_dictionary could result in a race condition if multiple clients
		//send their requests at the same time.
		pthread_mutex_lock(&socket_queue.mutex_dict);
		int result = search_dictionary(dictionary, buffer2);
		pthread_mutex_unlock(&socket_queue.mutex_dict);
		if(result == 1){
			strcat(buffer2, OK);
			send(connfd, buffer2, strlen(buffer2),0);
		}
		else{
			strcat(buffer2, MISSPELLED);
			send(connfd, buffer2, strlen(buffer2), 0);
		}
		send(connfd, NEXT_WORD, strlen(NEXT_WORD), 0);
	}
	printf("Closing %d.\n", connfd);
	close(connfd);
	pthread_exit(0);
}
