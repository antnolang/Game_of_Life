#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

#define W_SIZE_X 10
#define W_SIZE_Y 10

struct world {
        bool world[W_SIZE_X][W_SIZE_Y];
        bool aux[W_SIZE_X][W_SIZE_Y];
};

void world_init(struct world *w);
void world_print(const struct world *w);
void world_step(struct world *w);
int world_count_neighbors(const struct world *w, int coordx, int coordy);
bool world_get_cell(const struct world *w, int coordx, int coordy);
void world_copy(struct world *w);

#endif