#pragma once
#include <raylib.h>
#include <stdint.h>

typedef enum
{
    MAX_ENTITIES = 16384,
    MAX_CHUNKS_PER_SLAB = 16
} something;

typedef int16_t ZEntityId;
typedef int16_t ZEntityIdx;
typedef int16_t ZEntityMaxAmount;
typedef int16_t ZChunkId;

typedef struct
{
    ZEntityMaxAmount count;
    ZEntityIdx start_index;
} ZChunk;

typedef struct ZCore ZCore;

typedef void (*ZAction)(ZCore* den);