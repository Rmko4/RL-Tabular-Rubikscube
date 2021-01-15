#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time

#include "menace_approach.h"
#include "tdlearning.h"

#define RSOLVE 10
#define RMOVE -.1

#define NPARAM 3

#define ALPHA .4
#define GAMMA .95
#define PARAM3 .2

#define LAMBDA 0.78
#define REWARD 1

void printArgReq() {
  printf(" Provide args: <Algorithm> <Policy> <# Instances> <# Episodes> "
         "[Param1] [Param2] [Param3]\n");
  printf("Algorithm:          Q-leaning: 0 - SARSA: 1 - MENACE Approach: 2\n");
  printf("Policy:             Espilon Greedy: 0 - Softmax: 1 - Simulated Annealing (only MENACE Approach): 2\n");
  printf("# Instances:        (int) > 0\n");
  printf("# Episodes:         (int) > 0\n");
  printf("Param 1 for  Q-leaning & SARSA: (optional): (Float) Alpha, Beta - Default: 0.4\n");
  printf("Param 1 for   MENACE Approach: (optional): (Float) Lambda - Default: 0.78\n");
  printf("Param 2 for  Q-leaning & SARSA:(optional): (Float) Gamma, Beta - Default: 0.95\n");
  printf("Param 2 for   MENACE Approach:(optional): (Float) Reward - Default: 1\n");
  printf("Param 3 (optional): (Float) Epsilon, Tau, Beta - Default: 0.2\n");
}

// Writes the data in csv format to the standard output
void printStats(long *episodeMean, int nEpisodes, long *instanceSum,
                int nInstances) {
  int i;
  float dif, xbar, sd;

  xbar = 0;
  sd = 0;

  for (i = 0; i < nEpisodes; i++) {
    episodeMean[i] /= nInstances;
  }

  for (i = 0; i < nInstances; i++) {
    instanceSum[i] /= nEpisodes;
    xbar += instanceSum[i];
  }

  xbar /= nInstances;

  for (i = 0; i < nInstances; i++) {
    dif = instanceSum[i] - xbar;
    sd += dif * dif;
  }

  if (nInstances > 1) {
    sd = sqrtf(sd / (nInstances - 1));
    printf("%lf,%lf\n", xbar, sd);
  }
  for (i = 0; i < nEpisodes; i++) {
    printf("%ld\n", episodeMean[i]);
  }
}

int main(int argc, char const *argv[]) {
  int algorithm, policy, nInstances, nEpisodes, i;
  float param[NPARAM], R[NREW];
  long *out, *episodeMean, *instanceSum;

  if (argc < 5) {
    printArgReq();
    exit(EXIT_FAILURE);
  }

  // Parsing args
  algorithm = intParse(argv[1]);
  policy = intParse(argv[2]);
  nInstances = intParse(argv[3]);
  nEpisodes = intParse(argv[4]);
  
  if (algorithm < 2){
    param[0] = argc > 5 ? floatParse(argv[5]) : ALPHA;
    param[1] = argc > 6 ? floatParse(argv[6]) : GAMMA;
    param[2] = argc > 7 ? floatParse(argv[7]) : PARAM3;
  }else{
    param[0] = argc > 5 ? floatParse(argv[5]) : LAMBDA;
    param[1] = argc > 6 ? floatParse(argv[6]) : REWARD;
    param[2] = argc > 7 ? floatParse(argv[7]) : PARAM3;
  }

  R[0] = RMOVE;
  R[1] = RSOLVE;

  srand(time(NULL));

  out = safeMalloc(nEpisodes * sizeof(long));
  episodeMean = safeCalloc(nEpisodes, sizeof(long));
  instanceSum = safeCalloc(nInstances, sizeof(long));

  // Running and recording "nInstances" instances for the algorithm.
  for (i = 0; i < nInstances; i++) {
    if (algorithm < 2) {
      tdLearning(algorithm, policy, nEpisodes, R, param[0], param[1], param[2],
                 out);
    } else {
      menace_approach(policy, nEpisodes, param[0], param[1], param[2] , out);
    }
    for (int j = 0; j < nEpisodes; j++) {
      episodeMean[j] += out[j];
      instanceSum[i] += out[j];
    }
  }

  printStats(episodeMean, nEpisodes, instanceSum, nInstances);

  free(out);
  free(episodeMean);
  free(instanceSum);

  return 0;
}