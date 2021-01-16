#ifndef TDLEARNING_H_INCLUDED
#define TDLEARNING_H_INCLUDED

#include "actionSelection.h"

#define RSOLVE 10
#define RMOVE -.1

void tdLearning(int onPolicy, int policy, int nEpisodes, float alpha,
                float gamma, float param3, long *out);

#endif