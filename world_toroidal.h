#ifndef _WORLD_TOROIDAL_H_
#define _WORLD_TOROIDAL_H_

struct world_toroidal;
struct config;

struct world_toroidal *world_toroidal_alloc(const struct config *config);
void world_toroidal_free(struct world_toroidal *wt);

void toroidal_set_cell(struct world *w, int buf, int x, int y, bool val);
bool toroidal_get_cell(const struct world *w, int x, int y);

#endif