#include <stdlib.h>

#include "world.h"
#include "world_int.h"
#include "world_limited.h"

#define INDEX_OUT_OF_LIMITS x < 0 || x > w->size_y-1 || y < 0 || y > w->size_y-1

struct world_limited {
	struct world super;
};

static bool fix_coords(const struct world *w, int *x, int *y);
static void set_cell(struct world *w, int x, int y, bool val);
static bool get_cell(const struct world *w, int x, int y);

struct world_limited *world_limited_alloc(const struct config *config)
{
	struct world_limited *wl;
	wl = (struct world_limited *)malloc(sizeof(struct world_limited));
	if (!wl)
		return NULL;
		
	wl->super.get_cell = get_cell;
	wl->super.set_cell = set_cell;
	wl->super.fix_coords = fix_coords;
	int check_init = world_init(config, (struct world *)wl);
	if (-5 < check_init && check_init < 0) {
		free(wl);
		return NULL;
	}
	
	return wl;
}

void world_limited_free(struct world_limited *wl)
{
	world_free((struct world *)wl);
}

static bool get_cell(const struct world *w, int x, int y)
{		
	if (INDEX_OUT_OF_LIMITS)
		return false;
	
	int offset = w->size_y*x + y;
	return *(w->cells + offset);
}

static void set_cell(struct world *w, int x, int y, bool val)
{
	if (!(INDEX_OUT_OF_LIMITS)) {
		int offset = w->size_y*x + y;
		*(w->cells + offset) = val;
	}
}

static bool fix_coords(const struct world *w, int *x, int *y)
{
	return !(*x < 0 || *x > w->size_y - 1 || *y < 0 || *y > w->size_y-1);
}