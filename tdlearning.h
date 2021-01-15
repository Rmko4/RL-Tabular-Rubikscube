#ifndef TDLEARNING_H_INCLUDED
#define TDLEARNING_H_INCLUDED

#include "actionSelection.h"

#define NREW 2

void tdLearning(int onPolicy, int policy, int nEpisodes, float R[NREW],
                float alpha, float gamma, float param3, long *out);

#endif