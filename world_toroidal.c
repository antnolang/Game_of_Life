#include <stdlib.h>

#include "world_int.h"
#include "world_toroidal.h"
#include "config.h"

struct world_toroidal 
{
	struct world super;
};

static void fix_coords(const struct world *w, int *x, int *y);

struct world_toroidal *world_toroidal_alloc(const struct config *config)
{
	struct world_toroidal *wt;
	bool *mainWorld;
	bool *auxWorld;
	int x = config->size_x;
	int y = config->size_y;
	
	wt = (struct world_toroidal *)malloc(sizeof(struct world_toroidal));
	if (!wt)
		return NULL;
	
	mainWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(wt);
		return NULL;
	}
		
	auxWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(mainWorld);
		free(wt);
		return NULL;
	}
	
	wt->super.cells[0] = mainWorld;
	wt->super.cells[1] = auxWorld;
	wt->super.size_x = x;
	wt->super.size_y = y;
	wt->super.get_cell = toroidal_get_cell;
	wt->super.set_cell = toroidal_set_cell;
	init_cells(config, (struct world *)wt);
	
	return wt;
}

void world_toroidal_free(struct world_toroidal *wt)
{
	struct world *w= (struct world *)wt;

	free(w->cells[0]);
	free(w->cells[1]);
	free(wt);
}

bool toroidal_get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	int offset = w->size_y*x + y;
	
	return *(w->cells[0] + offset);
}

void toroidal_set_cell(struct world *w, int buf, int x, int y, bool val)
{
	int offset = w->size_y*x + y;
	*(w->cells[buf] + offset) = val;
}

static void fix_coords(const struct world *w, int *x, int *y) 
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