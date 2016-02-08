lookin:menu.o main_thread.o identifier_search.o meta_search.o extract_metadata.o get_file_type.o key_search.o
	gcc -olookin menu.o main_thread.o identifier_search.o meta_search.o extract_metadata.o get_file_type.o key_search.o -lmenu -lncurses -lextractor -lpthread
menu.o:menu.c
	gcc -c menu.c
main_thread.o:main_thread.c
	gcc -c main_thread.c
identifier_search.o:identifier_search.c
	gcc -c identifier_search.c
meta_search.o:meta_search.c
	gcc -c meta_search.c
extract_metadata.o:extract_metadata.c
	gcc -c extract_metadata.c
get_file_type.o:get_file_type.c
	gcc -c get_file_type.c
key_search.o:key_search.c
	gcc -c key_search.c
clean:
	rm *.o
