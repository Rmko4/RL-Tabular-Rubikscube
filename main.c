#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time

#include "tdlearning.h"

#define REWSOLVE 10
#define REWMOVE -.1

#define ALPHA 0.4
#define GAMMA 0.95
#define PARAM3 0.1

void printArgReq() { // OLD TODO: FIX
  printf("NEEDS FIX!!! Provide args: <Value distribution> <Algorithm> <Param "
         "1> [N-runs] "
         "[K-arms] [T-steps]\n");
  printf("Value distribution: Gaussian: 0 - Bernoulli: 1\n");
  printf("Algorithm:          Espilon Greedy: 0 - Reinforcement Comparison: "
         "1\n");
  printf("                    Pursuit Method: 2 - Stochastic Gradient "
         "Ascent: 3\n");
  printf("Param 1:            (Float) Alpha, Beta, Epsilon\n");
  printf("N-runs (optional):  (int) > 0 - Default: 20000\n");
  printf("K-arms (optional):  (int) > 0 - Default: 10\n");
  printf("T-steps (optional): (int) > 0 - Default: 1000\n");
}

int main(int argc, char const *argv[]) {
  int algorithm, policy, nEpisodes;
  float alpha, gamma, param3, R[NREW];

  if (argc < 4) {
    printArgReq();
    exit(EXIT_FAILURE);
  }

  algorithm = intParse(argv[1]);
  policy = intParse(argv[2]);
  nEpisodes = intParse(argv[3]);

  alpha = argc > 4 ? intParse(argv[4]) : ALPHA;
  gamma = argc > 5 ? intParse(argv[5]) : GAMMA;
  param3 = argc > 6 ? intParse(argv[6]) : PARAM3;
  R[0] = REWMOVE;
  R[1] = REWSOLVE;

  srand(time(NULL));

  printf("SARSA ----- "); // FIX PRINT
  printf("Epsilon: %lf -- Alpha: %lf -- Gamma: %lf", ALPHA, GAMMA, PARAM3);

  tdLearning(algorithm, policy, nEpisodes, R, alpha, gamma, param3);

  return 0;
}