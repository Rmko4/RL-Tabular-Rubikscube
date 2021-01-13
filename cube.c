#include <stdio.h>
#include <stdlib.h>

#include "cube.h"
#include "safeAlloc.h"

void initCube(Cube *c) {
  size_t i;

  *c = safeMalloc(sizeof(struct cubestruct));
  for (i = 0; i < NCORNER; i++) {
    (*c)->corner[i] = i;
  }
  for (i = 0; i < NEDGE; i++) {
    (*c)->edge[i] = i;
  }
}

void freeCube(Cube c) { free(c); }

void printCube(Cube c) {

  printf("Corners:");
  for (int i = 0; i < NCORNER; i++) {
    printf(" %d", c->corner[i]);
  }
  printf("\n");

  printf("Edges:");
  for (int i = 0; i < NEDGE; i++) {
    printf(" %d", c->edge[i]);
  }
  printf("\n");
}

Cube copyCube(Cube c) {
  Cube newC;

  newC = safeMalloc(sizeof(struct cubestruct));
  for (int i = 0; i < NCORNER; i++) {
    newC->corner[i] = c->corner[i];
  }

  for (int i = 0; i < NEDGE; i++) {
    newC->edge[i] = c->edge[i];
  }
  return newC;
}

void setCube(Cube cfrom, Cube cto) {
  for (int i = 0; i < NCORNER; i++) {
    cto->corner[i] = cfrom->corner[i];
  }

  for (int i = 0; i < NEDGE; i++) {
    cto->edge[i] = cfrom->edge[i];
  }
}

int isSolved(Cube c) {
  for (int i = 0; i < NCORNER; i++) {
    if (c->corner[i] != i) {
      return 0;
    }
  }

  for (int i = 0; i < NEDGE; i++) {
    if (c->edge[i] != i) {
      return 0;
    }
  }
  return 1;
}

// scrambles the cube, back and forth moves are possible
void scrambleCube(Cube c, int numberMoves, int action[NACTION][SWAP]) {
  for (int i = 0; i < numberMoves; i++) {
    turn(c, action[rand() % NACTION]);
  }
}

// Order of 180 degree actions: F,U,R,L,D,B
void initActions(int action[NACTION][SWAP]) {
  int actionh[NACTION][SWAP] = {
      {0, 2, 6, 4, 0, 2, 4, 5},  {2, 3, 6, 7, 2, 3, 10, 11},
      {1, 2, 4, 7, 5, 7, 9, 11}, {0, 3, 5, 6, 4, 6, 8, 10},
      {0, 1, 4, 5, 0, 1, 8, 9},  {1, 3, 5, 7, 1, 3, 6, 7},
  };
  for (size_t i = 0; i < NACTION; i++) {
    for (size_t j = 0; j < SWAP; j++) {
      action[i][j] = actionh[i][j];
    }
  }
}

void swap(int *ap, int *bp) {
  int h;
  h = *ap;
  *ap = *bp;
  *bp = h;
}

void turn(Cube c, int a[SWAP]) {
  swap(&c->corner[a[0]], &c->corner[a[1]]);
  swap(&c->corner[a[2]], &c->corner[a[3]]);
  swap(&c->edge[a[4]], &c->edge[a[5]]);
  swap(&c->edge[a[6]], &c->edge[a[7]]);
}
