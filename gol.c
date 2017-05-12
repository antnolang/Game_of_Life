#include <stdio.h>
#include "gol.h"

/* Inicializa el mundo con el patrón del glider:
 *           . # .
 *           . . #
 *           # # #
 */

void world_init(struct world *w)
{
	int i, j;

	for(i = 0; i < W_SIZE_X; i++) 
		for(j = 0; j < W_SIZE_Y; j++) 
			w->world[i][j] = false;
	 
	w->world[0][1] = true;
	w->world[1][2] = true;
	w->world[2][0] = true;
	w->world[2][1] = true;
	w->world[2][2] = true;
}

void world_print(struct world *w)
{
	 int i, j;
	 
	 for(i = 0; i < W_SIZE_X; i++) {
		for(j = 0; j < W_SIZE_Y; j++) {
			w->world[i][j] ? printf("# ") : printf(". ");
		}
		printf("\n");
	 }
}

void world_step(struct world *w)
{	 
	int i, j, neighbors;
	
	for (i = 0; i < W_SIZE_X; i++) {
		for (j = 0; j < W_SIZE_Y; j++) {
			neighbors = world_count_neighbors(w, i, j);
			w->aux[i][j] = neighbors == 3 || (w->world[i][j] && neighbors == 2);
		}
	}
	
	world_copy(w);
}

int world_count_neighbors(struct world *w, int coordx, int coordy)
{

	int counter = 0;

	counter += world_get_cell(w, coordx - 1, coordy - 1);
	counter += world_get_cell(w, coordx - 1, coordy    );
	counter += world_get_cell(w, coordx - 1, coordy + 1);
	counter += world_get_cell(w, coordx    , coordy - 1);
	counter += world_get_cell(w, coordx    , coordy + 1);
	counter += world_get_cell(w, coordx + 1, coordy - 1);
	counter += world_get_cell(w, coordx + 1, coordy    );
	counter += world_get_cell(w, coordx + 1, coordy + 1);
	
	return counter;
}

bool world_get_cell(struct world *w, int coordx, int coordy)
{
	if (coordx < 0)
		coordx += W_SIZE_X;
	else if (coordx > W_SIZE_X - 1)
		coordx -= W_SIZE_X;
	
	if (coordy < 0)
		coordy += W_SIZE_Y;
	else if (coordy > W_SIZE_Y - 1)
		coordy -= W_SIZE_Y;
	
	return w->world[coordx][coordy];
}

void world_copy(struct world *w)
{
	int i, j;

	for (i = 0; i < W_SIZE_X; i++)
		for (j = 0; j < W_SIZE_Y; j++)
			w->world[i][j] = w->aux[i][j];
}
