#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "CUBE.h"
#include "CUBE_LIBRARY.h"

#define SIZE_LAST_POSITIONS 10

struct state {
  Cube c;
  int lastAction;
  Tree[SIZE_LAST_POSITIONS] = lastPositions;
  int indexOldestPos;
}


#endif