#include "dictionary.h"
int MAX_LENGTH = 0;
char** load_dictionary(char * fileName){	
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
	char temp_word[50];
	int c,i,j;
	while(getline(&line,&len, words) != -1){
		num_words++;
	}
	num_words++;	
	char** dictionary = (char**)malloc(num_words * sizeof(char*));
	fsetpos(words, &begin_pos);
	j = 0;
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
