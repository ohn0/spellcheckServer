#ifndef _SPELLCHECKER_H
#define _SPELLCHECKER_H
#include "dictionary.h"
#include "synchronize.h"
#include "open_listen_socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define DEFAULT_PORT 9001
#define DEFAULT_DICTIONARY "words"
#define NUM_THREADS 10
#endif
