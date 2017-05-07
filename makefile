CFLAGS = -Wall -Werror

.PHONY : all clean

all: main

main: main.o gol.o
	gcc main.o gol.o -o main
	
main.o: main.c gol.h
	gcc -c main.c
	
gol.o: gol.c gol.h
	gcc -c gol.c
	
clean: 
	rm *.o