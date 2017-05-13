#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

#define W_SIZE_X 10
#define W_SIZE_Y 10

int main()
{
	int i = 0;
	struct world *w;
	
	w = world_alloc(W_SIZE_X, W_SIZE_Y);
	if (!w) {
		perror("Can't allocate world");
		exit(EXIT_FAILURE);
	}
		
	do {
		printf("\033cIteration %d\n", i++);
		world_print(w);
		world_iterate(w);
	} while (getchar() != 'q');
	
	world_free(w);

	return EXIT_SUCCESS;
}