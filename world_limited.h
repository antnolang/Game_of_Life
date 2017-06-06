#ifndef _WORLD_LIMITED_H_
#define _WORLD_LIMITED_H_

#include "config.h"

struct world_limited;

struct world_limited *world_limited_alloc(const struct config *config);
void world_limited_free(struct world_limited *wl);

#endif