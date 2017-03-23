#ifndef _OPEN_LISTEN_SOCKET_H
#define _OPEN_LISTEN_SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
int open_listenfd(int );
int server_writer(int);
#endif
