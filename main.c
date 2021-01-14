#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time

#include "simulated_annealing.h"
#include "tdlearning.h"

#define RSOLVE 10
#define RMOVE -.1

#define NPARAM 3

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

// Writes the data in csv format to the standard output
void printStats(long *episodeMean, int nEpisodes, long *instanceMean, int nInstances) {
  int i;
  long dif, xbar, sd;

  xbar = 0;
  sd = 0;

  for (i = 0; i < nEpisodes; i++) {
    episodeMean[i] /= nInstances;
  }

  for (i = 0; i < nInstances; i++) {
    xbar += instanceMean[i];
  }

  xbar /= nInstances;

  for (i = 0; i < nInstances; i++) {
    dif = instanceMean[i] - xbar;
    sd += dif * dif;
  }

  if (nInstances > 1) {
    sd = sqrtf(sd / (nInstances - 1));
    printf("%ld,%ld\n", xbar, sd);
  }
  for (i = 0; i < nEpisodes; i++) {
    printf("%ld\n", episodeMean[i]);
  }
}

int main(int argc, char const *argv[]) {
  int algorithm, policy, nInstances, nEpisodes, i;
  float param[NPARAM], R[NREW];
  long *out, *episodeMean, *instanceMean;

  if (argc < 5) {
    printArgReq();
    exit(EXIT_FAILURE);
  }

  algorithm = intParse(argv[1]);
  policy = intParse(argv[2]);
  nInstances = intParse(argv[3]);
  nEpisodes = intParse(argv[4]);

  param[0] = argc > 5 ? floatParse(argv[5]) : ALPHA;
  param[1] = argc > 6 ? floatParse(argv[6]) : GAMMA;
  param[2] = argc > 7 ? floatParse(argv[7]) : PARAM3;

  R[0] = RMOVE;
  R[1] = RSOLVE;

  srand(time(NULL));

  out = safeMalloc(nEpisodes * sizeof(float));
  episodeMean = safeCalloc(nEpisodes, sizeof(float));
  instanceMean = safeCalloc(nInstances, sizeof(float));

  if (algorithm < 2) {
    for (i = 0; i < nInstances; i++) {
      tdLearning(algorithm, policy, nEpisodes, R, param[0], param[1], param[2], out);

      for (int j = 0; j < nEpisodes; j++) {
        episodeMean[j] += out[j];
        instanceMean[i] += out[j];
      }
    }
  } else {
    // TODO: Fix
    simulatedAnnealing(nEpisodes, policy);
  }

  printStats(episodeMean, nEpisodes, instanceMean, nInstances);

  return 0;
}