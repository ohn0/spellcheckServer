#include "dictionary.h"
int MAX_LENGTH = 0;
char** load_dictionary(char * fileName){
	//Loads the dictionary into a char**, allocating each char*
	//to the size of the word at that location.	
	//Returns a pointer to an allocated array of char*, each containing a word from the dictionary.
	FILE * words = fopen(fileName, "r");
	if(words == NULL){
		printf("Error opening file.\n");
		return NULL;
	}
	fpos_t begin_pos;
	fgetpos(words, &begin_pos);
	int num_words = 0;
	char * line;
	size_t len = 0;
	char temp_word[100];
	int c,i,j;
	//Obtain the total number of words in the dictionary.
	while(getline(&line,&len, words) != -1){
		num_words++;
	}
	num_words++;	
	char** dictionary = (char**)malloc(num_words * sizeof(char*));
	fsetpos(words, &begin_pos);
	j = 0;
	//Transfer each word from the file to the array.
	while((c = getc(words)) != EOF){
		if(c != '\n'){
			temp_word[i++] = c;	
		}
		else{
			temp_word[i] = '\0';			
			dictionary[j] = (char*) malloc(i * sizeof(char));
			strcpy(dictionary[j++], temp_word);
			i = 0;
		}
	}
	MAX_LENGTH = j;
	return dictionary;
}

int search_dictionary(char** dict, char* word){
	//Performs binary search on the dictionary.
	//Returns 1 if the word is found, 0 if not.
	int cmp_result;
	int lower = 0;
	int upper = MAX_LENGTH;
	int midway = (upper+lower)/2;
	while(upper - lower != 1){
		printf("%s\n", dict[midway]);
		if((cmp_result = strcmp(dict[midway], word)) > 0){
			upper = midway;
			midway = (upper+lower)/2;
		}
		else if(cmp_result < 0){
			lower = midway;
			midway = (upper+lower)/2;
		}
		else{
			return 1;
		}
	}
	return 0;


}

int free_dictionary(char** dictionary)
{
	//Frees the array and all of its contents.
	int i;
	for(i = 0; i < MAX_LENGTH; i++){
		free(dictionary[i]);
	}
	free(dictionary);
	return 0;
}
