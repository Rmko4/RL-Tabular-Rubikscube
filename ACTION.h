#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include "CUBE.h"

int **initActions();

void swap(int *ap, int *bp);
void turn(Cube c, int *a);

#endif