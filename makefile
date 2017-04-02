spellchecker: spellchecker.c open_listen_socket.c synchronize.c dictionary.c synchronize.h spellchecker.h open_listen_socket.h 
	gcc -g -Wall spellchecker.c open_listen_socket.c synchronize.c dictionary.c -pthread -o spellchecker
