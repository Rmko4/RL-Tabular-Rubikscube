#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include "CUBE.h"

#define NACTION 6
#define SWAP 8

void initActions(int action[NACTION][SWAP]);

void swap(int *ap, int *bp);
void turn(Cube c, int *a);

#endif