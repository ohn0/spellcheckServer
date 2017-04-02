#include "open_listen_socket.h"

int open_listenfd(int port)
{
	//literally copied this from the book.
	int listenfd, optval = 1;
	struct sockaddr_in serveraddr;

	//Create a socket descriptor
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ return  -1;}

	//Get rid of "Already in use" error.
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
				  (const void *)&optval, sizeof(int)) < 0){return -1;}

	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short) port);
	if(bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){return -1;}

	if(listen(listenfd, 20) < 0){return -1;}
	return listenfd;
}

int server_writer(int port)
{
	int listener, connfd, clientlen;
	struct sockaddr_in client;
	listener = open_listenfd(port);
	char* message = "Can you read this?\n";
	clientlen = sizeof(client);
	char read_buffer[200];
	printf("Listening on port %d.\n", port);
	connfd =accept(listener, (struct sockaddr *)&client, &clientlen);
	int i, rec_size;
	char buffer[200];
	i = 0;
	while(1){
		//send(connfd, message, 19*(sizeof(char)), 0);
		rec_size = recv(connfd, read_buffer, 200, 0);
		if(read_buffer[0] == EOF){close(connfd); break;}
		printf("Client wrote:%s", read_buffer);
		send(connfd, read_buffer, strlen(read_buffer), 0);
		bzero(read_buffer, strlen(read_buffer));
	}
}
