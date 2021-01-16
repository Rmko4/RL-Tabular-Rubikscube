#include "tdlearning.h"

// Retrieves the Q-values for a given cube state and initializes it if the node
// is new in the library.
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

// Runs an instance of TD-learning on the Rubik's cube problem restricted to 180
// degree moves only. onPolicy indicates whether Q-learning or SARA will be
// used. param3 is epsilon or tau for epsilon greedy and softmax respectively.
void tdLearning(int onPolicy, int policy, int nEpisodes, float alpha,
                float gamma, float param3, long *out) {
  Library lib;
  Tree tr;
  Cube c;
  float *Q, *QNext;
  int action[NACTION][SWAP];

  size_t i, j;
  int a, aNext, t;
  float r;

  // Initialization of constructs
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

  for (i = 0; i < nEpisodes; i++) {
    // Start from a random scramble of 25 random moves.
    scrambleCube(c, 25, action);
    r = isSolved(c) ? RSOLVE : 0;
    getQ(c, lib, &Q);

    // SARSA: Selects an action based on the policy.
    if (onPolicy) {
      a = actionSelection(Q, NACTION, param3, policy);
    }

    t = 0;
    while (r < 1) {
      // Q-Learning: Selects an action based on the policy.
      if (!onPolicy) {
        a = actionSelection(Q, NACTION, param3, policy);
      }
      turn(c, action[a]); // Applies the action
      if (isSolved(c)) {
        r = RSOLVE;
      } else {
        r = RMOVE;
      }

      // Retrieve action a' (aNext) either on-policy or off-policy (greedy)
      getQ(c, lib, &QNext);
      if (onPolicy) {
        aNext = actionSelection(QNext, NACTION, param3, policy);
      } else {
        aNext = argmax(QNext, NACTION);
      }

      // Update rule
      Q[a] += alpha * (r + gamma * QNext[aNext] - Q[a]);
      a = aNext;
      Q = QNext;
      t++;
    }
    out[i] = (long)t;
  }

  freeCube(c);
  freeLibrary(lib);
}