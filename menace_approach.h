
#ifndef menace_approach_H_INCLUDED
#define menace_approach_H_INCLUDED

#include <float.h> // FLT_MIN
#include <math.h>  // expf

#include "cubelib.h"
#include "safeAlloc.h"

#include "cube.h"
#include "cubelib.h"
#include "state.h"


void updateHeuristics(Library lib, State s, float lambda, float epsilon);

float getTemperature(int iteration, int NumberIterations);

void menace_approach(int policy, int nEpisodes, float epsilon, float lambda,
                      float param ,long *out);

#endif