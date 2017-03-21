#include "dictionary.h"

int main(int argc, char** argv){
	char** dict = load_dictionary("words");
	int i = search_dictionary(dict, "anal");
	int j = search_dictionary(dict, "loli");
	printf("anal in dict? %d\n", i);
	printf("loli in dict? %d\n", j);
	return 0;
}
