#include <stdio.h>
#include <stdlib.h>

#include "action.h"
#include "cube.h"

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
