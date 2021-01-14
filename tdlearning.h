#ifndef TDLEARNING_H_INCLUDED
#define TDLEARNING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <float.h> // FLT_MIN
#include <math.h>  // expf
#include <time.h>  // time

#include "cubelib.h"
#include "safeAlloc.h"

#define NREW 2

float uniform(float min, float max);
int argmax(float *a, int len);
void getQ(Cube c, Library lib, float **Q);

int epsilonGreedy(float *a, int len, float epsilon);
int softmaxAction(float *Q, int len, float tau);
int actionSelection(float *Q, int len, int param, int policy);

void tdLearning(int onPolicy, int policy, int nEpisodes, float R[NREW],
                float alpha, float gamma, float param3, long *out);

#endif