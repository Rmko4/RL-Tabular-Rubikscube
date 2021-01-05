#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#define NCORNER 8
#define NEDGE 12

typedef struct cubestruct
{
  int corner[NCORNER];
  int edge[NEDGE];
} * Cube;

void *safeMalloc(int n);

Cube initCube();

void printCube(Cube c);

void freeCube(Cube c);


#endif