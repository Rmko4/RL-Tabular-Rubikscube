
#ifndef menace_approach_H_INCLUDED
#define menace_approach_H_INCLUDED

#include <float.h> // FLT_MIN
#include <math.h>  // expf

#include "cubelib.h"
#include "safeAlloc.h"

#include "cube.h"
#include "cubelib.h"
#include "state.h"
#include "actionSelection.h"




void menace_approach(int policy, int nEpisodes, float lambda, float reward, float param ,long *out);

#endif