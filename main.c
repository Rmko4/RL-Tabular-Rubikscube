
#include <stdio.h>
#include <stdlib.h>

#include "CUBE.h"
#include "ACTION.h"

int main(int argc, char const *argv[])
{
  /* code */
  Cube c = initCube();
  int **actions = initActions();

  printCube(c);
  printf( isSolved(c) ? "cube is solved\n" : "cube is not solved\n");
  

  Cube c2 = copyCube(c);
  printCube(c2);
  
  freeCube(c);
  freeCube(c2);
  return 0;
}