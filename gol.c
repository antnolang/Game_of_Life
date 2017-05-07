#include <stdio.h>
#include "gol.h"

/* Inicializa el mundo con el patrón del glider:
 *           . # .
 *           . . #
 *           # # #
 */

void world_init(bool world[W_SIZE_X][W_SIZE_Y])
{
	int i, j;

	for(i = 0; i < W_SIZE_X; i++) 
		for(j = 0; j < W_SIZE_Y; j++) 
			world[i][j] = false;
	 
	world[0][1] = true;
	world[1][2] = true;
	world[2][0] = true;
	world[2][1] = true;
	world[2][2] = true;
}

void world_print(bool world[W_SIZE_X][W_SIZE_Y])
{
	 int i, j;
	 
	 for(i = 0; i < W_SIZE_X; i++) {
		for(j = 0; j < W_SIZE_Y; j++) {
			world[i][j] ? printf("# ") : printf(". ");
		}
		printf("\n");
	 }
}

void world_step(bool world[W_SIZE_X][W_SIZE_Y], bool worldAux[W_SIZE_X][W_SIZE_Y])
{	 
	int i, j, neighbors;
	
	for (i = 0; i < W_SIZE_X; i++) {
		for (j = 0; j < W_SIZE_Y; j++) {
			neighbors = world_count_neighbors(world, i, j);
			worldAux[i][j] = neighbors == 3 || (world[i][j] && neighbors == 2);
		}
	}
	
	world_copy(world, worldAux);
}

int world_count_neighbors(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy)
{

	int counter = 0;

	counter += world_get_cell(world, coordx - 1, coordy - 1);
	counter += world_get_cell(world, coordx - 1, coordy    );
	counter += world_get_cell(world, coordx - 1, coordy + 1);
	counter += world_get_cell(world, coordx	   , coordy - 1);
	counter += world_get_cell(world, coordx	   , coordy + 1);
	counter += world_get_cell(world, coordx + 1, coordy - 1);
	counter += world_get_cell(world, coordx + 1, coordy    );
	counter += world_get_cell(world, coordx + 1, coordy + 1);
	
	return counter;
}

bool world_get_cell(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy)
{
	if (coordx < 0)
		coordx += W_SIZE_X;
	else if (coordx > W_SIZE_X - 1)
		coordx -= W_SIZE_X;
	
	if (coordy < 0)
		coordy += W_SIZE_Y;
	else if (coordy > W_SIZE_Y - 1)
		coordy -= W_SIZE_Y;
	
	return world[coordx][coordy];
}

void world_copy(bool wordTarget[W_SIZE_X][W_SIZE_Y], bool worldSource[W_SIZE_X][W_SIZE_Y])
{
	int i, j;

	for (i = 0; i < W_SIZE_X; i++)
		for (j = 0; j < W_SIZE_Y; j++)
			wordTarget[i][j] = worldSource[i][j];
}
