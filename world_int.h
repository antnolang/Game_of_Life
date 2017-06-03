#ifndef _WORLD_INT_
#define _WORLD_INT_

#include <stdbool.h>

struct config;

struct world {
	bool *cells[2];
	int size_x;
	int size_y;

	bool (*get_cell)(const struct world *w, int x, int y);
	void (*set_cell)(struct world *w, int buf, int x, int y, bool val);
};

void init_cells(const struct config *config, struct world *w);

#endif