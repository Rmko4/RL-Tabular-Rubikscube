#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#define NACTION 6
#define SWAP 8

#include "CUBE.h"

void initActions(int action[NACTION][SWAP]);

void swap(int *ap, int *bp);
void turn(Cube c, int *a);

#endif