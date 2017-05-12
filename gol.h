#ifndef _GOL_H_
#define _GOL_H_

#include <stdbool.h>

#define W_SIZE_X 10
#define W_SIZE_Y 10

struct world {
        bool world[W_SIZE_X][W_SIZE_Y];
        bool aux[W_SIZE_X][W_SIZE_Y];
};

void world_init(bool world[W_SIZE_X][W_SIZE_Y]);
void world_print(bool world[W_SIZE_X][W_SIZE_Y]);
void world_step(bool world[W_SIZE_X][W_SIZE_Y], bool worldAux[W_SIZE_X][W_SIZE_Y]);
int world_count_neighbors(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy);
bool world_get_cell(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy);
void world_copy(bool wordTarget[W_SIZE_X][W_SIZE_Y], bool worldSource[W_SIZE_X][W_SIZE_Y]);

#endif