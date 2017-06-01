#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

struct world;
struct config;

struct world *world_alloc(const struct config *config);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

#endif