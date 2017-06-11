#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "cell.h"
#include "world.h"
#include "world_int.h"

static const int neighbors_coords[8][2] = {
	{-1, -1}, {0, -1}, {1, -1},
	{-1,  0},          {1,  0},
	{-1,  1}, {0,  1}, {1,  1}
};

static int count_neighbors(const struct world *w, int coordx, int coordy);
static int init_glider(struct world *w, int x, int y);
static int init_default(struct world *w, int x, int y);
static int init_random(struct world *w, int x, int y);
static bool add_initial_cell(struct world *w, int x, int y);
static void next_cell_state(struct world *w);
static void kill_cells(struct world *w);
static void revive_cells(struct world *w);

struct world *world_alloc(const struct config *config)
{
	struct world *w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;
	
	int check_init = world_init(config, w);
	if (-5 < check_init && check_init < 0) {
		free(w);
		return NULL;
	}
	
	return w;
}

void world_free(struct world *w) 
{
	free(w->cells);
	free_cells(&(w->alive_cells));
	free_cells(&(w->to_kill));
	free_cells(&(w->to_revive));
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
	next_cell_state(w);
	kill_cells(w);
	revive_cells(w);
}

static void next_cell_state(struct world *w)
{
	int i, neighbors, x, y;
	struct cell *c_aux, *c_add;
	struct cell *c = list_entry(&(w->alive_cells), struct cell, lh);
	
	list_for_each_entry_safe(c, c_aux, &(w->alive_cells), lh) {
		neighbors = count_neighbors(w, c->x, c->y);
		if (neighbors != 3 && neighbors != 2)
			cell_move_to(c, &(w->to_kill));
	
		for (i = 0; i < 8; i++) {
			x = c->x + neighbors_coords[i][0];
			y = c->y + neighbors_coords[i][1];
			if (w->fix_coords(w, &x, &y) && !(w->get_cell(w, x, y)) 
					     && count_neighbors(w, x, y) == 3) {
				c_add = cell_add(x, y, &(w->to_revive));
				if (!c_add) {
					printf("ERROR: Can't allocate cell\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}

static void kill_cells(struct world *w)
{
	struct cell *c_aux;
	struct cell *c = list_entry(&(w->to_kill), struct cell, lh);
	
	list_for_each_entry_safe(c, c_aux, &(w->to_kill), lh) {
		w->set_cell(w, c->x, c->y, false);
		cell_del(c);
	}
}

static void revive_cells(struct world *w)
{
	struct cell *c_aux;
	struct cell *c = list_entry(&(w->to_revive), struct cell, lh);
	
	list_for_each_entry_safe(c, c_aux, &(w->to_revive), lh) {
		if (w->get_cell(w, c->x, c->y)) {
			cell_del(c);
		} else {
			w->set_cell(w, c->x, c->y, true);
			cell_move_to(c, &(w->alive_cells));
		}
	}
}

static int count_neighbors(const struct world *w, int coordx, int coordy)
{
	int i, counter = 0;
	
	for (i = 0; i < 8; i++) {
		counter += w->get_cell(w, coordx + neighbors_coords[i][0],
					  coordy + neighbors_coords[i][1]);
	}
	
	return counter;
}

int world_init(const struct config *config, struct world *w)
{
	int x = config->size_x;
	int y = config->size_y;
	
	bool *mainWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld)
		return -1;
	
	w->cells = mainWorld;
	w->size_x = x;
	w->size_y = y;
	INIT_LIST_HEAD(&w->alive_cells);
	INIT_LIST_HEAD(&w->to_kill);
	INIT_LIST_HEAD(&w->to_revive);
	 
	switch(config->init_mode) {
	case CFG_DEFAULT:
		return init_default(w, x, y);
		break;
	case CFG_GLIDER:
		return init_glider(w, x, y);
		break;
	case CFG_RANDOM:
		return init_random(w, x, y);
		break;
	default:
		free(w->cells);
		printf("\nInit mode is not valid.\n");
		return -4;
		break;
	}
}

static int init_glider(struct world *w, int x, int y)
{
	int i, j;
	bool check = true;
	
	for(i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			w->set_cell(w, i, j, false);
		
	check &= add_initial_cell(w, 0, 1);
	check &= add_initial_cell(w, 1, 2);
	check &= add_initial_cell(w, 2, 0);
	check &= add_initial_cell(w, 2, 1);
	check &= add_initial_cell(w, 2, 2);
	
	if (!check) {
		free_cells(&(w->alive_cells));
		free(w->cells);
		return -2;
	}
	
	return EXIT_SUCCESS;
}

static int init_default(struct world *w, int x, int y)
{
	int i, j;
	for(i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			w->set_cell(w, i, j, false);
	
	return EXIT_SUCCESS;
}

static int init_random(struct world *w, int x, int y)
{
	int i, j;
	bool check = true;
	srand(time(0));
			
	for(i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			if (rand()%2==0)
				check &= add_initial_cell(w, i, j);
			else
				w->set_cell(w, i, j, false);
		}
	}
	
	if (!check) {
		free_cells(&(w->alive_cells));
		free(w->cells);
		return -3;
	}
	
	return EXIT_SUCCESS;
}

static bool add_initial_cell(struct world *w, int x, int y)
{
	struct cell *c = cell_add(x, y, &(w->alive_cells));			
	w->set_cell(w, x, y, true);
	
	return !(!c);
}