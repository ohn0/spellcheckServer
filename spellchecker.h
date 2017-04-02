#ifndef _SPELLCHECKER_H
#define _SPELLCHECKER_H
#include <unistd.h>
#include "dictionary.h"
#include "synchronize.h"
#include "open_listen_socket.h"
#define DEFAULT_PORT 9001
#define DEFAULT_DICTIONARY "words"
void *worker();
#endif
