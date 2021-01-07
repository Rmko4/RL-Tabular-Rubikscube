#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "action.h"

#define NCORNER 8
#define NEDGE 12

typedef struct cubestruct {
  int corner[NCORNER];
  int edge[NEDGE];
} * Cube;

void *safeMalloc(int n);

void initCube(Cube c);

void printCube(Cube c);

void freeCube(Cube c);

Cube copyCube(Cube c);

int isSolved(Cube c);

void scrambleCube(Cube c, int numberMoves, int action[NACTION][SWAP]);

#endif