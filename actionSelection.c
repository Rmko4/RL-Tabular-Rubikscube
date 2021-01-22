#include "actionSelection.h"

float uniform(float min, float max) {
  float div = RAND_MAX / (max - min);
  return min + rand() / div;
}


// Returns index of highest value in array
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

// Selsects random action with probability epsilon and the best otherwise
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

// Not called from action selection because it does not need an array of
// Q-values instead a cube is given
int simulated_annealing(Library lib, State s, float temperature,
                        int action[NACTION][SWAP]) {
  int a;
  Tree leave;
  float currentQ, nextQ;
  getNode(lib, s->c, &leave);
  currentQ = leave->heuristic;
  do {
    a = rand() % NACTION;
    turn(s->c, action[a]);
    getNode(lib, s->c, &leave);
    nextQ = leave->heuristic;
    turn(s->c, action[a]);

  } while (!simulated_annealing_accept(nextQ, temperature, currentQ));
  return a;
}

// Returns 1 if accepted and 0 otherwise
int simulated_annealing_accept(float nextQ, float temperature, float currentQ) {
  return (nextQ >= currentQ ||
          expf(-((currentQ - nextQ) / temperature)) + 0.04 >=
              (float)rand() / (float)(RAND_MAX));
}

// Samples an action based on the preferences using the Gibbs distribution.
// Q are the state-action Q-values, the probabilities will be assigned to pi.
int softmaxAction(float *Q, int len, float tau) {
  int action, aMax;
  float *pi;
  float sum, x, run;

  pi = safeMalloc(len * sizeof(float));

  aMax = argmax(Q, len); // Used for normalization
  sum = 0;
  for (action = 0; action < len; action++) {
    pi[action] = expf((Q[action] - Q[aMax]) / tau);
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
  action = action < 0 ? 0 : action;

  free(pi);
  return action;
}


// Call the correct action selection function based on the value "policy"
int actionSelection(float *Q, int len, float param, int policy) {
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