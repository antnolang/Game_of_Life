#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

int main()
{
	int i = 0;
	bool world[W_SIZE_X][W_SIZE_Y];
	bool worldAux[W_SIZE_X][W_SIZE_Y];
	
	world_init(world);
		
	do {
		printf("\033cIteration %d\n", i++);
		world_print(world);
		world_step(world, worldAux);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}