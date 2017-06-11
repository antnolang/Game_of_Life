CFLAGS = -Wall -Werror

.PHONY : all clean valgrind

all: main

valgrind: main_debug
	valgrind --leak-check=full ./main_debug config.txt

main_debug: main.o world.o world_toroidal.o world_limited.o config.o cell.o
	gcc $(CFLAGS) -g main.o world.o world_toroidal.o world_limited.o config.o cell.o -o main_debug

main: main.o world.o world_toroidal.o world_limited.o config.o cell.o
	gcc $(CFLAGS) main.o world.o world_toroidal.o world_limited.o config.o cell.o -o main

main.o: main.c world.h world_toroidal.h world_limited.h config.h
	gcc $(CFLAGS) -c main.c

world.o: world.c world.h world_int.h config.h list.h cell.h
	gcc $(CFLAGS) -c world.c

world_toroidal.o: world_toroidal.c world_toroidal.h world_int.h config.h world.h list.h cell.h
	gcc $(CFLAGS) -c world_toroidal.c

world_limited.o: world_limited.c world_limited.h world_int.h config.h world.h list.h cell.h
	gcc $(CFLAGS) -c world_limited.c

config.o: config.c config.h
	gcc $(CFLAGS) -c config.c

cell.o: cell.c cell.h list.h
	gcc $(CFLAGS) -c cell.c

clean: 
	rm *.o