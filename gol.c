#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

struct world {
	bool *cells[2];
	int size_x;
	int size_y;
};

static void init(struct world *w);
static int count_neighbors(const struct world *w, int coordx, int coordy);
static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int coordx, int coordy);
static void copy(struct world *w);

struct world * world_alloc(int x, int y)
{
	struct world *w;
	bool *mainWorld;
	bool *auxWorld;
	
	w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;
	
	mainWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(w);
		return NULL;
	}
		
	auxWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(mainWorld);
		free(w);
		return NULL;
	}
	
	w->cells[0] = mainWorld;
	w->cells[1] = auxWorld;
	w->size_x = x;
	w->size_y = y;
	
	init(w);
	
	return w;	
}

void world_free(struct world *w) 
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}

void init(struct world *w)
{
	int i, x, y;
	
	x = w->size_x;
	y = w->size_y;

	for(i = 0; i < x*y; i++)
		*(w->cells[0] + i) = false;
	 
	*(w->cells[0] + 1)	 = true;
	*(w->cells[0] + y + 2)   = true;
	*(w->cells[0] + 2*y)	 = true;
	*(w->cells[0] + 2*y + 1) = true;
	*(w->cells[0] + 2*y + 2) = true;
}

void world_print(const struct world *w)
{
	int i, x, y;
	 
	x = w->size_x;
	y = w->size_y;
	 
	for(i = 0; i < x*y; i++) {
		if (i%y == 0) {
			printf("\n");
		}
		*(w->cells[0] + i) ? printf("# ") : printf(". ");
	}
	printf("\n");
}

void world_iterate(struct world *w)
{	
	int size_x = w->size_x;
	int size_y = w->size_y;
	int i, j, neighbors, offset;
	
	for (i = 0; i < size_x; i++) {
		for (j = 0; j < size_y; j++) {
			offset = w->size_y*i + j;
			neighbors = count_neighbors(w, i, j);
			*(w->cells[1] + offset) = neighbors == 3 || (*(w->cells[0] + offset) && neighbors == 2);
		}
	}
	
	copy(w);
}

int count_neighbors(const struct world *w, int coordx, int coordy)
{
	int counter = 0;

	counter += get_cell(w, coordx - 1, coordy - 1);
	counter += get_cell(w, coordx - 1, coordy    );
	counter += get_cell(w, coordx - 1, coordy + 1);
	counter += get_cell(w, coordx    , coordy - 1);
	counter += get_cell(w, coordx    , coordy + 1);
	counter += get_cell(w, coordx + 1, coordy - 1);
	counter += get_cell(w, coordx + 1, coordy    );
	counter += get_cell(w, coordx + 1, coordy + 1);
	
	return counter;
}

void fix_coords(const struct world *w, int *x, int *y) 
{
	int size_x = w->size_x;
	int size_y = w->size_y;

	if (*x < 0)
		*x += size_x;
	else if (*x > size_x - 1)
		*x -= size_x;
	
	if (*y < 0)
		*y += size_y;
	else if (*y > size_y - 1)
		*y -= size_y;
}

bool get_cell(const struct world *w, int coordx, int coordy)
{
	fix_coords(w, &coordx, &coordy);
	int offset = w->size_y*coordx + coordy;
	
	return *(w->cells[0] + offset);
}

void copy(struct world *w)
{
	int i, x, y;
	
	x = w->size_x;
	y = w->size_y;

	for(i = 0; i < x*y; i++)
		*(w->cells[0] + i) = *(w->cells[1] + i);
}