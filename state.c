#include <stdio.h>
#include <stdlib.h>

#include "state.h"


State initState(Cube c){
    State s = safeMalloc(sizeof(struct statestruct));

    s->indexOldestPos = 0;
    for (int i =0; i < SIZE_LAST_POSITIONS; i++){
        s->lastPositions[i] = NULL;
    }
    s->numberMoves = 0;
    s->c = c;
    return s;
}

void freeState(State s){
    free(s);
}