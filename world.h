#ifndef _WORLD_H_
#define _WORLD_H_

#include <stdbool.h>

#include "config.h"

struct world;

struct world *world_alloc(const struct config *config);
void world_free(struct world *w);

void world_iterate(struct world *w);
void world_print(const struct world *w);

#endif