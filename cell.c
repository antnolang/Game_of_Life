#include <stdlib.h>

#include "cell.h"

struct cell *cell_add(int x, int y, struct list_head *list)
{
	struct cell *c = (struct cell *)malloc(sizeof(struct cell));
	if (!c)
		return NULL;
		
	c->x = x;
	c->y = y;
	list_add(&(c->lh), list);
	return c;
}

void cell_del(struct cell *c)
{
	list_del(&(c->lh));
	free(c);
}

void cell_move_to(struct cell *c, struct list_head *list)
{
	list_move(&(c->lh), list);
}

void free_cells(struct list_head *list)
{
	struct cell *c = list_entry(list, struct cell, lh);
	struct cell *c_aux;
	list_for_each_entry_safe(c, c_aux, list, lh)
		cell_del(c);
}
