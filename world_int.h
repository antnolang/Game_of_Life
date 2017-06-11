#ifndef _WORLD_INT_
#define _WORLD_INT_

#include <stdbool.h>

#include "list.h"
#include "config.h"

struct world {
	bool *cells;
	int size_x;
	int size_y;
	struct list_head alive_cells;
	struct list_head to_kill;
	struct list_head to_revive;

	bool (*get_cell)(const struct world *w, int x, int y);
	void (*set_cell)(struct world *w, int x, int y, bool val);
	bool (*fix_coords)(const struct world *w, int *x, int *y);
};

int world_init(const struct config *config, struct world *w);

#endif