#include "open_listen_socket.h"

int open_listenfd(int port)
{
	//Taken from the textbook. Sets up a listener socket that will
	//later be used to generate client sockets.
	//Returns the file descriptor bound to the connection if successful, -1 otherwise.
	int listenfd, optval = 1;
	struct sockaddr_in serveraddr;

	//Create a socket descriptor
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ return  -1;}

	//Get rid of "Already in use" error.
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
				  (const void *)&optval, sizeof(int)) < 0){return -1;}
	//Clears serveraddr
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short) port);
	if(bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){return -1;}

	if(listen(listenfd, 20) < 0){return -1;}
	return listenfd;
}

