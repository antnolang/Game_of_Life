#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

struct world;

void world_init(struct world *w);
void world_print(const struct world *w);
void world_step(struct world *w);

#endif