#ifndef _CELL_H_
#define _CELL_H_

#include "list.h"

struct cell {
	int x, y;
	struct list_head lh;
};

struct cell *cell_add(int x, int y, struct list_head *list);
void cell_del(struct cell *c);
void cell_move_to(struct cell *c, struct list_head *list);
void free_cells(struct list_head *list);

#endif