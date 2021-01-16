#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "cube.h"
#include "cubelib.h"

#define SIZE_LAST_POSITIONS 15

typedef struct statestruct {
  Cube c;
  Tree lastPositions[SIZE_LAST_POSITIONS];
  int indexOldestPos;
  int numberMoves;
} * State;

State initState(Cube c);

void freeState(State s);

#endif