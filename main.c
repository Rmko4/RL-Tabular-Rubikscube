
#include <stdio.h>
#include <stdlib.h>

#include "CUBE.h"

int main(int argc, char const *argv[])
{
  /* code */
  Cube c = initCube();
  printCube(c);
  freeCube(c);
  return 0;
}