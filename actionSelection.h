#ifndef ACTIONSELECTION_H_INCLUDED
#define ACTIONSELECTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "cubelib.h"
#include "safeAlloc.h"
#include "state.h"

#include <float.h> // FLT_MIN
#include <math.h>  // expf
#include <time.h>  // time


float uniform(float min, float max);
int argmax(float *a, int len);
int epsilonGreedy(float *a, int len, float epsilon);
int softmaxAction(float *Q, int len, float tau);
int actionSelection(float *Q, int len, float param, int policy);

int simulated_annealing(State s, float temperature, int action[NACTION][SWAP], Library lib );
int simulated_annealing_accept(float nextQ, float temperature, float currentQ);

#endif