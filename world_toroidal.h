#ifndef _WORLD_TOROIDAL_H_
#define _WORLD_TOROIDAL_H_

#include "config.h"

struct world_toroidal;

struct world_toroidal *world_toroidal_alloc(const struct config *config);
void world_toroidal_free(struct world_toroidal *wt);

#endif