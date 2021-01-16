#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "safeAlloc.h"

#define NCORNER 8
#define NEDGE 12

#define NACTION 6
#define SWAP 8

typedef struct cubestruct {
  int corner[NCORNER];
  int edge[NEDGE];
} * Cube;

void *safeMalloc(int n);

void initCube(Cube *c);
void freeCube(Cube c);

void printCube(Cube c);
void setCube(Cube cfrom, Cube cto);
Cube copyCube(Cube c);
int isSolved(Cube c);

void initActions(int action[NACTION][SWAP]);
void scrambleCube(Cube c, int numberMoves, int action[NACTION][SWAP]);

void swap(int *ap, int *bp);
void turn(Cube c, int *a);

#endif