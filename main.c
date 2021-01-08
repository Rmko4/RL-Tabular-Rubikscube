#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cubelib.h"

#define NEPISODES 100000
#define EPS 0.1
#define ALPHA 0.2
#define GAMMA 0.95

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

void getQ(Cube c, Library lib, float **Q) {
  Tree tr;
  int new = nodeInLibrary(c, lib, &tr);
  if (new) {
    tr->value = safeMalloc(NACTION * sizeof(float));
    for (size_t j = 0; j < NACTION; j++) {
      tr->value[j] = uniform(-1, 1);
    }
  }
  *Q = tr->value;
}

void qLearning() {
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
  nodeInLibrary(c, lib, &tr);
  tr->value = safeMalloc(NACTION * sizeof(float));
  Q = tr->value;
  for (j = 0; j < NACTION; j++) {
    Q[j] = 0;
  }

  for (i = 0; i < NEPISODES; i++) {
    // Start from a random scramble of 20 random moves.
    scrambleCube(c, 20, action);
    r = isSolved(c) ? 1 : 0;
    getQ(c, lib, &Q);

    t = 0;
    while (r < 0.99) {
      // Choose action a from epsilon greedy policy on Q.
      a = epsilonGreedy(Q, NACTION, EPS);
      turn(c, action[a]);
      if (isSolved(c)) {
        r = 1;
      }

      // Retrieve a' (aNext) such that argmax_a' Q(s', a')
      getQ(c, lib, &QNext);
      aNext = argmax(QNext, NACTION);

      // Update rule
      Q[a] += ALPHA * (r + GAMMA * QNext[aNext] - Q[a]);
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

void sarsa() {
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
  nodeInLibrary(c, lib, &tr);
  tr->value = safeMalloc(NACTION * sizeof(float));
  Q = tr->value;
  for (j = 0; j < NACTION; j++) {
    Q[j] = 0;
  }

  for (i = 0; i < NEPISODES; i++) {
    // Start from a random scramble of 20 random moves.

    scrambleCube(c, 20, action);
    r = isSolved(c) ? 1 : 0;
    getQ(c, lib, &Q);
    a = epsilonGreedy(Q, NACTION, EPS);

    t = 0;
    while (r < 0.99) {
      turn(c, action[a]);
      if (isSolved(c)) {
        r = 1;
      }

      // Retrieve action a' (aNext) from epsilon greedy policy on Q.
      getQ(c, lib, &QNext);
      aNext = epsilonGreedy(QNext, NACTION, EPS);

      // Update rule
      Q[a] += ALPHA * (r + GAMMA * QNext[aNext] - Q[a]);
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

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  printf("QLEARNING ------ ");
  printf("Epsilon: %lf -- Alpha: %lf -- Gamma: %lf", EPS, ALPHA, GAMMA);
  qLearning();
  // printf("SARSA ----- ");
  // printf("Epsilon: %lf -- Alpha: %lf -- Gamma: %lf", EPS, ALPHA, GAMMA);
  // sarsa();
  return 0;
}