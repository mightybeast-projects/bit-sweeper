#include "mersenne-twister.h"

void initializeMTRandom(MTState* state, uint32_t seed)
{
    uint32_t* stateArray = &(state->stateArray[0]);

    stateArray[0] = seed;

    for (int i = 1; i < N; i++) {
        seed = F * (seed ^ (seed >> (W - 2))) + i;
        stateArray[i] = seed;
    }

    state->stateIndex = 0;
}

uint32_t nextMTRandom(MTState* state)
{
    uint32_t* stateArray = &(state->stateArray[0]);

    int k = state->stateIndex;

    int j = k - (N - 1);
    if (j < 0)
        j += N;

    uint32_t x = (stateArray[k] & UMASK) | (stateArray[j] & LMASK);

    uint32_t xA = x >> 1;
    if (x & 0x00000001UL)
        xA ^= A;

    j = k - (N - M);
    if (j < 0)
        j += N;

    x = stateArray[j] ^ xA;
    stateArray[k++] = x;

    if (k >= N)
        k = 0;
    state->stateIndex = k;

    uint32_t y = x ^ (x >> U);
    y = y ^ ((y << S) & B);
    y = y ^ ((y << T) & C);
    uint32_t z = y ^ (y >> L);

    return z;
}