#include <stdio.h>
#include <stdlib.h>

#include "menace.h"

float getTemperature(int iteration, int NumberIterations, float tempScale) {
  return 0.02 + expf(-(float)iteration * (16 * tempScale / (float)NumberIterations));
}

void updateHeuristics(Library lib, State s, float lambda, float epsilon) {
  float new, n, current;
  for (int i = 0; i < SIZE_LAST_POSITIONS; i++) {
    s->indexOldestPos = s->indexOldestPos == 0 ? SIZE_LAST_POSITIONS - 1
                                               : s->indexOldestPos - 1;
    if (s->lastPositions[s->indexOldestPos] != NULL) {
      new = pow(lambda, i) * epsilon;
      current = s->lastPositions[s->indexOldestPos]->heuristic;
      s->lastPositions[s->indexOldestPos]->timesReevaluate += 1;
      n = s->lastPositions[s->indexOldestPos]->timesReevaluate;
      s->lastPositions[s->indexOldestPos]->heuristic += (new - current) / n;
    }
  }
}

void getAllHeuristics(Cube c, Library lib, float *heuristics,
                      int action[NACTION][SWAP]) {
  Tree leave;
  for (int i = 0; i < NACTION; i++) {
    turn(c, action[i]);
    getNode(lib, c, &leave);
    heuristics[i] = leave->heuristic + (float)(rand() % 100) / 100000;
    turn(c, action[i]);
  }
}

State runEpisode(State s, Library lib, float temperature,
                 int action[NACTION][SWAP], float param, int policy) {

  int a = 0;
  float nextH, currentH = 0;
  Tree leave;
  float *heuristics = safeMalloc(NACTION * sizeof(float));
  ;

  while (!isSolved(s->c)) {

    if (policy == 2) {
      a = simulated_annealing(lib, s, temperature, action);
    } else {
      getAllHeuristics(s->c, lib, heuristics, action);
      a = actionSelection(heuristics, NACTION, param, policy);
    }

    turn(s->c, action[a]);
    getNode(lib, s->c, &leave);

    s->numberMoves += 1;
    s->lastPositions[s->indexOldestPos] = leave;
    s->indexOldestPos = (s->indexOldestPos + 1) % SIZE_LAST_POSITIONS;
  }

  free(heuristics);

  return s;
}

void menace_approach(int policy, int nEpisodes, float lambda, float reward,
                     float param, long *out) {
  Library lib;
  Cube c;
  State s;
  int action[NACTION][SWAP];
  float temperature;

  int index = 0;

  initCube(&c);
  initActions(action);
  initLibrary(&lib);

  for (int i = 0; i < nEpisodes; i++) {
    scrambleCube(c, 25, action);
    s = initState(c);

    temperature = getTemperature(i, nEpisodes, param);

    runEpisode(s, lib, temperature, action, param, policy);

    updateHeuristics(lib, s, lambda, reward);

    out[i] = s->numberMoves;

    freeState(s);
  }

  freeCube(c);
  freeLibrary(lib);
}
