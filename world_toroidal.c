#include <stdlib.h>

#include "world.h"
#include "world_int.h"
#include "world_toroidal.h"

struct world_toroidal {
	struct world super;
};

static bool fix_coords(const struct world *w, int *x, int *y);
static void set_cell(struct world *w, int x, int y, bool val);
static bool get_cell(const struct world *w, int x, int y);

struct world_toroidal *world_toroidal_alloc(const struct config *config)
{
	struct world_toroidal *wt;
	wt = (struct world_toroidal *)malloc(sizeof(struct world_toroidal));
	if (!wt)
		return NULL;
	
	wt->super.get_cell = get_cell;
	wt->super.set_cell = set_cell;
	wt->super.fix_coords = fix_coords;
	int check_init = world_init(config, (struct world *)wt);
	if (-5 < check_init && check_init < 0) {
		free(wt);
		return NULL;
	}
	return wt;
}

void world_toroidal_free(struct world_toroidal *wt)
{
	world_free((struct world *)wt);
}

static bool get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	int offset = w->size_y*x + y;
	
	return *(w->cells + offset);
}

static void set_cell(struct world *w, int x, int y, bool val)
{
	int offset = w->size_y*x + y;
	*(w->cells + offset) = val;
}

static bool fix_coords(const struct world *w, int *x, int *y)
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
		
	return true;
}