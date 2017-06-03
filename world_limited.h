#ifndef _WORLD_LIMITED_H_
#define _WORLD_LIMITED_H_

struct world_limited;
struct config;

struct world_limited *world_limited_alloc(const struct config *config);
void world_limited_free(struct world_limited *wl);

void limited_set_cell(struct world *w, int buf, int x, int y, bool val);
bool limited_get_cell(const struct world *w, int x, int y);

#endif