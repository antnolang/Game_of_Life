CFLAGS = -Wall -Werror

.PHONY : all clean valgrind

all: main

valgrind: main_debug
	valgrind --leak-check=full ./main_debug

main_debug: main.o gol.o config.o
	gcc -g main.o gol.o config.o -o main_debug

main: main.o gol.o config.o
	gcc main.o gol.o config.o -o main
	
main.o: main.c gol.h
	gcc -c main.c
	
gol.o: gol.c gol.h
	gcc -c gol.c
	
config.o: config.c config.h
	gcc -c config.c
	
clean: 
	rm *.o