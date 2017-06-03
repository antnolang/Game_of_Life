#include <stdlib.h>

#include "world_int.h"
#include "world_limited.h"
#include "config.h"

struct world_limited 
{
	struct world super;
};

struct world_limited *world_limited_alloc(const struct config *config)
{
	struct world_limited *wl;
	bool *mainWorld;
	bool *auxWorld;
	int x = config->size_x;
	int y = config->size_y;
	
	wl = (struct world_limited *)malloc(sizeof(struct world_limited));
	if (!wl)
		return NULL;
	
	mainWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(wl);
		return NULL;
	}
		
	auxWorld = (bool *)malloc(x*y*sizeof(int));
	if (!mainWorld) {
		free(mainWorld);
		free(wl);
		return NULL;
	}
	
	wl->super.cells[0] = mainWorld;
	wl->super.cells[1] = auxWorld;
	wl->super.size_x = x;
	wl->super.size_y = y;
	wl->super.get_cell = limited_get_cell;
	wl->super.set_cell = limited_set_cell;
	init_cells(config, (struct world *)wl);
	
	return wl;
}

void world_limited_free(struct world_limited *wl)
{
	struct world *w= (struct world *)wl;

	free(w->cells[0]);
	free(w->cells[1]);
	free(wl);
}

bool limited_get_cell(const struct world *w, int x, int y)
{		
	if (x < 0 || x > w->size_x - 1 || y < 0 || y > w->size_y - 1)
		return false;
	
	int offset = w->size_y*x + y;
	return *(w->cells[0] + offset);
}

void limited_set_cell(struct world *w, int buf, int x, int y, bool val)
{
	if (!(x < 0 || x > w->size_x - 1 || y < 0 || y > w->size_y - 1)) {
		int offset = w->size_y*x + y;
		*(w->cells[buf] + offset) = val;
	}
}