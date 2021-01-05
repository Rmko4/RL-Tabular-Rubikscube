
#include <stdio.h>
#include <stdlib.h>

#include "CUBE.h"
#include "ACTION.h"
#include "CUBE_LIBRARY.h"


int main(int argc, char const *argv[])
{
  Cube c;
  int action[NACTION][SWAP];

  c = initCube();
  initActions(action);

  printCube(c);
  turn(c, action[0]);
  printCube(c);



  printf( isSolved(c) ? "cube is solved\n" : "cube is not solved\n");
  


  Library lib = initLibrary();

  scrambleCube(c, 50, action);
  printCube(c);

  //stressTest
  for (int i=0; i < 10000000; i++){
    insertInLibrary(c, lib);
    scrambleCube(c,1,action);
    if ( isSolved(c)){
      printf("cube is solved\n");
      break;
    } 
  }



  printf("Library has %d entries\n", libraryNumberInsertions(lib));


  turn(c, action[3]);

  
  freeCube(c);
  freeLibrary(lib);
  return 0;
}