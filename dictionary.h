#ifndef DICT_H
#define DICT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_DICT "words"
extern int MAX_LENGTH;
char** load_dictionary(char*);
int search_dictionary(char**, char*);
int free_dictionary(char **);
#endif
