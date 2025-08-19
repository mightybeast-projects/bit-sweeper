#pragma once

#include <stdint.h>

#define N 624
#define M 397
#define W 32
#define R 31
#define UMASK (0xffffffffUL << R)
#define LMASK (0xffffffffUL >> (W - R))
#define A 0x9908b0dfUL
#define U 11
#define S 7
#define T 15
#define L 18
#define B 0x9d2c5680UL
#define C 0xefc60000UL
#define F 1812433253UL

typedef struct MTState
{
    uint32_t stateArray[N];
    int stateIndex;
} MTState;

void initializeMTRandom(MTState* state, uint32_t seed);
uint32_t nextMTRandom(MTState* state);