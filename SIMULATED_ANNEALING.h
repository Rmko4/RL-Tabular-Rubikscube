
#ifndef SIMULATED_ANNEALING_H_INCLUDED
#define SIMULATED_ANNEALING_H_INCLUDED

#include<time.h>
#include <math.h>

#include "CUBE.h"
#include "CUBE_LIBRARY.h"
#include "STATE.h"
#include "ACTION.h"

#define EPSILON 1
#define LAMBDA 0.75
#define E_MATH 2.71828
#define SIZE_AVERAGE 10

float average(float lastTen[SIZE_AVERAGE]);

void simulatedAnnealing(int iterations);

State runIteration(State s, Library lib, float temperature, int action[NACTION][SWAP] );

void updateHeuristics(Library lib, State s);

float getTemperature(int iteration, int NumberIterations);

float P(float currentH, float nextH, float temperature);

#endif