
#include <stdio.h>
#include <stdlib.h>

#include "CUBE.h"
#include "ACTION.h"
#include "CUBE_LIBRARY.h"


int main(int argc, char const *argv[])
{
  Cube c;
  int **action;

  c = initCube();
  //action = initActions();

  printCube(c);
  turn(c, action[0]);
  printCube(c);



  printf( isSolved(c) ? "cube is solved\n" : "cube is not solved\n");
  

  Cube c2 = copyCube(c);
  printCube(c2);

  Library lib = initLibrary();
  printf("%d\n", checkInLibrary(lib, c));
  insertInLibrary(c, lib);
  printf("%d\n", checkInLibrary(lib, c));
  
  freeCube(c);
  freeCube(c2);
  freeLibrary(lib);
  return 0;
}