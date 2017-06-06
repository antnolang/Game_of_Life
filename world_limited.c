#include <stdlib.h>

#include "world.h"
#include "world_int.h"
#include "world_limited.h"

struct world_limited 
{
	struct world super;
};

static void limited_set_cell(struct world *w, int buf, int x, int y, bool val);
static bool limited_get_cell(const struct world *w, int x, int y);

struct world_limited *world_limited_alloc(const struct config *config)
{
	struct world_limited *wl;
	wl = (struct world_limited *)malloc(sizeof(struct world_limited));
	if (!wl)
		return NULL;
		
	wl->super.get_cell = limited_get_cell;
	wl->super.set_cell = limited_set_cell;
	int check_init = world_init(config, (struct world *)wl);
	if (check_init == -1 || check_init == -2)
		return NULL;
	
	return wl;
}

void world_limited_free(struct world_limited *wl)
{
	world_free((struct world *)wl);
}

static bool limited_get_cell(const struct world *w, int x, int y)
{		
	if (x < 0 || x > w->size_x - 1 || y < 0 || y > w->size_y - 1)
		return false;
	
	int offset = w->size_y*x + y;
	return *(w->cells[0] + offset);
}

static void limited_set_cell(struct world *w, int buf, int x, int y, bool val)
{
	if (!(x < 0 || x > w->size_x - 1 || y < 0 || y > w->size_y - 1)) {
		int offset = w->size_y*x + y;
		*(w->cells[buf] + offset) = val;
	}
}