#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cubelib.h"

#define NEPISODES 100000
#define EPS 0.05
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

void sarsa() {
  Library lib;
  Tree tr, trNext;
  Cube c, cNext;
  int action[NACTION][SWAP];

  size_t i, j;
  int new, a, aNext, iter;
  float r;

  initLibrary(&lib);
  initActions(action);
  initCube(&c);
  initCube(&cNext);

  for (i = 0; i < NEPISODES; i++) {
    r = iter = 0;
    scrambleCube(c, 20, action);
    new = nodeInLibrary(c, lib, &tr);
    if (new) {
      tr->value = safeMalloc(NACTION * sizeof(float));
      for (j = 0; j < NACTION; j++) {
        tr->value[j] = uniform(-1, 1);
      }
    }
    a = epsilonGreedy(tr->value, NACTION, EPS);

    while (r < 0.9) {
      iter++;
      setCube(c, cNext);
      turn(cNext, action[a]);
      new = nodeInLibrary(cNext, lib, &trNext);
      if (isSolved(c)) {
        r = 1;
      }
      if (new) {
        trNext->value = safeMalloc(NACTION * sizeof(float));
        if (r == 1) {
          for (j = 0; j < NACTION; j++) {
            trNext->value[j] = 0;
          }
        } else {
          for (j = 0; j < NACTION; j++) {
            trNext->value[j] = uniform(-1, 1);
          }
        }
      }
      aNext = epsilonGreedy(trNext->value, NACTION, 0.1);
      tr->value[a] += ALPHA * (r + GAMMA * trNext->value[aNext] - tr->value[a]);
      setCube(cNext, c);
      a = aNext;
      tr = trNext;
    }
    if (i > NEPISODES - 100) {
      printf("%d\n", iter);
    }
  }

  freeCube(c);
  freeLibrary(lib);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  printf("Epsilon: %lf -- Alpha: %lf -- Gamma: %lf", EPS, ALPHA, GAMMA);
  sarsa();
  return 0;
}