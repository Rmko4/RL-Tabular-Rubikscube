
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "action.h"
#include "cube.h"
#include "cubelib.h"

int main(int argc, char const *argv[]) {
  Library lib;
  Cube c;
  int action[NACTION][SWAP];

  initLibrary(lib);
  initCube(c);
  initActions(action);

  printCube(c);
  turn(c, action[0]);
  printCube(c);
  printf(isSolved(c) ? "cube is solved\n" : "cube is not solved\n");

  srand(time(0));
  scrambleCube(c, 100, action);
  printCube(c);

  // stressTest
  for (int i = 0; i < 10000000; i++) {
    insertInLibrary(c, lib);
    scrambleCube(c, 1, action);
    if (isSolved(c)) {
      printf("cube is solved\n");
      break;
    }
  }

  printf("Library has %d entries\n", libraryNumberInsertions(lib));

  freeCube(c);
  freeLibrary(lib);
  return 0;
}