#include <stdio.h>
#include <stdlib.h>

#include <float.h> // FLT_MIN
#include <math.h>  // expf
#include <time.h>  // time

#include "cubelib.h"
#include "safeAlloc.h"

#define NEPISODES 100000

#define NREW 2
#define REWSOLVE 10
#define REWMOVE -.1

#define ALPHA 0.4
#define GAMMA 0.95
#define PARAM3 0.1

float uniform(float min, float max) {
  float div = RAND_MAX / (max - min);
  return min + rand() / div;
}

int argmax(float *a, int len) {
  int i, imax;
  float max;
  imax = 0;
  max = FLT_MIN;
  for (i = 0; i < len; i++) {
    if (a[i] > max) {
      max = a[i];
      imax = i;
    }
  }
  return imax;
}

void getQ(Cube c, Library lib, float **Q) {
  Tree tr;
  int new = getNode(lib, c, &tr);
  if (new) {
    tr->Q = safeMalloc(NACTION * sizeof(float));
    for (size_t j = 0; j < NACTION; j++) {
      tr->Q[j] = uniform(0, 1);
    }
  }
  *Q = tr->Q;
}

int epsilonGreedy(float *a, int len, float epsilon) {
  int action;
  if (uniform(0, 1) < epsilon) {
    action = (int)uniform(0, len);
  } else {
    action = argmax(a, len);
  }

  action = action == len ? len - 1 : action;
  return action;
}

// Samples an action based on the preferences, using the Gibbs distribution.
// Q are the state-action Q-values, the probabilities will be assigned to pi.
int softmaxAction(float *Q, int len, float tau) {
  int action;
  float *pi;
  float sum, x, run;

  pi = safeMalloc(len * sizeof(float));

  sum = 0;

  for (action = 0; action < len; action++) {
    pi[action] = expf(Q[action] / tau);
    sum += pi[action];
  }

  x = uniform(0, sum);
  run = 0;
  action = 0;

  while (x > run && action < len) {
    run += pi[action];
    action++;
  }
  action--;
  action = action == len ? len - 1 : action;

  free(pi);
  return action;
}

int actionSelection(float *Q, int len, int param, int policy) {
  int a;
  switch (policy) {
  case 0:
    a = epsilonGreedy(Q, len, param);
    break;
  case 1:
    a = softmaxAction(Q, len, param);
    break;
  default:
    a = argmax(Q, len);
  }
  return a;
}

void tdLearning(int onPolicy, int policy, float R[NREW], float alpha,
                float gamma, float param3) {
  Library lib;
  Tree tr;
  Cube c;
  float *Q, *QNext;
  int action[NACTION][SWAP];

  size_t i, j;
  int a, aNext, t;
  float r;

  // Initialization
  initLibrary(&lib);
  initActions(action);
  initCube(&c);

  // For the Terminal state s, for all actions a: Q(s,a) = 0
  getNode(lib, c, &tr);
  tr->Q = safeMalloc(NACTION * sizeof(float));
  Q = tr->Q;
  for (j = 0; j < NACTION; j++) {
    Q[j] = 0;
  }

  for (i = 0; i < NEPISODES; i++) {
    // Start from a random scramble of 20 random moves.
    scrambleCube(c, 20, action);
    r = isSolved(c) ? R[1] : 0;
    getQ(c, lib, &Q);

    if (onPolicy) {
      a = actionSelection(Q, NACTION, param3, policy);
    }

    t = 0;
    while (r < 1) {
      if (!onPolicy) {
        a = actionSelection(Q, NACTION, param3, policy);
      }
      turn(c, action[a]);
      if (isSolved(c)) {
        r = R[1];
      } else {
        r = R[0];
      }

      // Retrieve action a' (aNext) from epsilon greedy policy on Q.
      getQ(c, lib, &QNext);
      if (onPolicy) {
        aNext = actionSelection(Q, NACTION, param3, policy);
      } else {
        aNext = argmax(QNext, NACTION);
      }

      // Update rule
      Q[a] += alpha * (r + gamma * QNext[aNext] - Q[a]);
      a = aNext;
      Q = QNext;
      t++;
    }
    // if (i > NEPISODES - 100) {
    printf("%d\n", t);
    //}
  }

  freeCube(c);
  freeLibrary(lib);
}

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
  int algorithm, policy;
  float alpha, gamma, param3, R[NREW];

  if (argc < 3) {
    printArgReq();
    exit(EXIT_FAILURE);
  }

  algorithm = intParse(argv[1]);
  policy = intParse(argv[2]);

  alpha = argc > 3 ? intParse(argv[4]) : ALPHA;
  gamma = argc > 4 ? intParse(argv[5]) : GAMMA;
  param3 = argc > 5 ? intParse(argv[6]) : PARAM3;
  R[0] = REWMOVE;
  R[1] = REWSOLVE;

  srand(time(NULL));

  printf("SARSA ----- "); // FIX PRINT
  printf("Epsilon: %lf -- Alpha: %lf -- Gamma: %lf", ALPHA, GAMMA, PARAM3);

  tdLearning(algorithm, policy, R, alpha, gamma, param3);

  return 0;
}