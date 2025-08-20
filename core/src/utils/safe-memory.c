#include "safe-memory.h"
#include "stdio.h"

void* safeMalloc(size_t size)
{
    void* p = malloc(size);
    if (!p) {
        printf("Fatal: failed to allocate %zu bytes.\n", size);
        exit(1);
    }

    return p;
}