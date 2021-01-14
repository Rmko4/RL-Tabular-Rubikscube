
#include <stdio.h>
#include <stdlib.h>

#include "simulated_annealing.h"

int main(int argc, char const *argv[]) {
  srand(time(0));
  int numberIterations = 5000;

  simulatedAnnealing(numberIterations);

  return 0;
}