look:main.o get_file_type.o identifier_search.o key_search.o
	gcc -olookin main.o get_file_type.o identifier_search.o key_search.o -lpthread
main.o:main.c
	gcc -c main.c
get_file_type.o:get_file_type.c
	gcc -c get_file_type.c
identifier_search.o:identifier_search.c
	gcc -c identifier_search.c
key_search.o:key_search.c
	gcc -c key_search.c
clean:
	rm *.o
