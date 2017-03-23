#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define MYPORT "3490"	// the port users will be connecting to
#define BACKLOG 0	//how many pending connections queue will hold

int main()
{
	struct sockaddr_storage, their_adr;
	socklen_t addr_size;
	struct addrinfo, hints, *res;
	int sockfd, new_fd;

	//ERROR CHECK

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	getaddrinfo(NULL, MYPORT, &hints, &res);
	
	//make a socket, bind, and listen to it.

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(sockfd, res->ai_addr, res->ai_addrlen);
	listen(sockfd, BACKLOG);

	//accept incoming connection 
	addr_size = sizeof their_addr;
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	



}
