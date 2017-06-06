CFLAGS = -Wall -Werror

.PHONY : all clean valgrind

all: main

valgrind: main_debug
	valgrind --leak-check=full ./main_debug

main_debug: main.o world.o world_toroidal.o world_limited.o config.o
	gcc -g main.o world.o world_toroidal.o world_limited.o config.o -o main_debug

main: main.o world.o world_toroidal.o world_limited.o config.o
	gcc main.o world.o world_toroidal.o world_limited.o config.o -o main

main.o: main.c world.h world_toroidal.h world_limited.h config.h
	gcc -c main.c

world.o: world.c world.h world_int.h config.h
	gcc -c world.c

world_toroidal.o: world_toroidal.c world_toroidal.h world_int.h config.h world.h
	gcc -c world_toroidal.c

world_limited.o: world_limited.c world_limited.h world_int.h config.h world.h
	gcc -c world_limited.c

config.o: config.c config.h
	gcc -c config.c

clean: 
	rm *.o