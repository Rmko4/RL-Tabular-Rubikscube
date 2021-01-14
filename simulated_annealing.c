#include <stdio.h>
#include <stdlib.h>

#include "simulated_annealing.h"

float average(float lastTen[SIZE_AVERAGE]) {
  float sum = 0;
  for (int i = 0; i < SIZE_AVERAGE; i++) {
    sum += lastTen[i];
  }
  return sum / SIZE_AVERAGE;
}

void simulatedAnnealing(int iterations, int policy) {
  Library lib;
  Cube c;
  State s;
  int action[NACTION][SWAP];
  float temperature;

  float lastFewEval[SIZE_AVERAGE];
  for (int i = 0; i < SIZE_AVERAGE; i++) {
    lastFewEval[i] = 1000000;
  }
  int index = 0;

  initCube(&c);
  initActions(action);
  initLibrary(&lib);

  for (int i = 0; i < iterations; i++) {
    scrambleCube(c, 25, action);
    s = initState(c);
    temperature = getTemperature(i, iterations);

    runIteration(s, lib, temperature, action);

    updateHeuristics(lib, s);

    lastFewEval[index] = s->numberMoves;
    index = (index + 1) % SIZE_AVERAGE;
    printf(
        "iteration %d, temperature %.3f, solved in (10 move average): %.1f\n",
        i, temperature, average(lastFewEval));

    freeState(s);
  }
  printf("done\n");

  freeCube(c);
  freeLibrary(lib);
}

State runIteration(State s, Library lib, float temperature,
                   int action[NACTION][SWAP]) {

  int randAction;
  float nextH, currentH = 0;
  Tree leave;

  while (!isSolved(s->c)) {
    randAction = rand() % NACTION;

    turn(s->c, action[randAction]);
    getNode(lib, s->c, &leave);
    nextH = leave->heuristic;

    if (nextH >= currentH ||
        P(currentH, nextH, temperature) >= (float)rand() / (float)(RAND_MAX)) {
      // accept move
      currentH = nextH;
      s->numberMoves += 1;
      s->lastPositions[s->indexOldestPos] = leave;
      s->indexOldestPos = (s->indexOldestPos + 1) % SIZE_LAST_POSITIONS;

    } else {
      // rejectmove
      turn(s->c, action[randAction]);
    }
  }
  return s;
}

void updateHeuristics(Library lib, State s) {
  float new, n, current;
  for (int i = 0; i < SIZE_LAST_POSITIONS; i++) {
    s->indexOldestPos = s->indexOldestPos == 0 ? SIZE_LAST_POSITIONS - 1
                                               : s->indexOldestPos - 1;
    if (s->lastPositions[s->indexOldestPos] != NULL) {
      new = pow(LAMBDA, i) * EPSILON;
      current = s->lastPositions[s->indexOldestPos]->heuristic;
      s->lastPositions[s->indexOldestPos]->timesReevaluate += 1;
      n = s->lastPositions[s->indexOldestPos]->timesReevaluate;
      s->lastPositions[s->indexOldestPos]->heuristic += (new - current) / n;
    }
  }
}

float getTemperature(int iteration, int NumberIterations) {
  float temperature;

  // nonelinear
  temperature =
      0.02 + pow(E_MATH, -(float)iteration * (6 / (float)NumberIterations));

  return temperature;
}

float P(float currentH, float nextH, float temperature) {
  float res = pow(E_MATH, -((currentH - nextH) / temperature));
  if (rand() % 10000 == 42) {
    printf("current = %f, next = %f, temperature = %f     ------->    "
           "likelyhood = %f \n",
           currentH, nextH, temperature, res);
  }
  return pow(E_MATH, -((currentH - nextH) / temperature));
}