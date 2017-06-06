#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "world.h"
#include "world_int.h"

static int count_neighbors(const struct world *w, int coordx, int coordy);

struct world *world_alloc(const struct config *config)
{
	struct world *w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;
	
	int check_init = world_init(config, w);
	if (check_init == -1 || check_init == -2)
		return NULL;
	
	return w;
}

void world_free(struct world *w) 
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}

void world_print(const struct world *w)
{
	int i, j, x, y;
	 
	x = w->size_x;
	y = w->size_y;
	
	for(i = 0; i < x; i++) {
		for(j = 0; j < y; j++) {
			w->get_cell(w, i, j) ? printf("# ") : printf(". ");
		}
		printf("\n");
	}
}

void world_iterate(struct world *w)
{	
	int size_x = w->size_x;
	int size_y = w->size_y;
	int i, j, neighbors;
	bool next_cell;
	bool *aux;
	
	for (i = 0; i < size_x; i++) {
		for (j = 0; j < size_y; j++) {
			neighbors = count_neighbors(w, i, j);
			next_cell = neighbors == 3 || 
				    (w->get_cell(w, i, j) && neighbors == 2);
			w->set_cell(w, 1, i, j, next_cell);
		}
	}
	
	//El mundo auxiliar pasa a ser el principal
	aux = w->cells[0];
	w->cells[0] = w->cells[1];
	w->cells[1] = aux;
}

static int count_neighbors(const struct world *w, int coordx, int coordy)
{
	int counter = 0;

	counter += w->get_cell(w, coordx - 1, coordy - 1);
	counter += w->get_cell(w, coordx - 1, coordy    );
	counter += w->get_cell(w, coordx - 1, coordy + 1);
	counter += w->get_cell(w, coordx    , coordy - 1);
	counter += w->get_cell(w, coordx    , coordy + 1);
	counter += w->get_cell(w, coordx + 1, coordy - 1);
	counter += w->get_cell(w, coordx + 1, coordy    );
	counter += w->get_cell(w, coordx + 1, coordy + 1);
	
	return counter;
}

int world_init(const struct config *config, struct world *w)
{
	bool *mainWorld;
	bool *auxWorld;
	int i, j;
	int x = config->size_x;
	int y = config->size_y;
	
	mainWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(w);
		return -1;
	}
		
	auxWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(mainWorld);
		free(w);
		return -2;
	}
	
	w->cells[0] = mainWorld;
	w->cells[1] = auxWorld;
	w->size_x = x;
	w->size_y = y;
	 
	switch(config->init_mode) {
	case CFG_DEFAULT:
		for(i = 0; i < x; i++)
			for (j = 0; j < y; j++)
				w->set_cell(w, 0, i, j, false);
		break;
	case CFG_GLIDER:
		for(i = 0; i < x; i++)
			for (j = 0; j < y; j++)
				w->set_cell(w, 0, i, j, false);
		
		w->set_cell(w, 0, 0, 1, true);
		w->set_cell(w, 0, 1, 2, true);
		w->set_cell(w, 0, 2, 0, true);
		w->set_cell(w, 0, 2, 1, true);
		w->set_cell(w, 0, 2, 2, true);
		break;
	case CFG_RANDOM:
		srand(time(0));
				
		for(i = 0; i < x; i++)
			for (j = 0; j < y; j++)
				w->set_cell(w, 0, i, 
					    j, rand()%2==0 ? true : false);
		break;
	default:
		world_free(w);
		printf("\nInit mode is not valid.\n");
		exit(EXIT_FAILURE);
		break;
	}
	
	return EXIT_SUCCESS;
}