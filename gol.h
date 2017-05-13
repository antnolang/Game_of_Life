#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

struct world;

struct world *world_alloc(int size_x, int size_y);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

#endif