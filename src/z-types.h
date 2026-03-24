#pragma once
#include <raylib.h>
#include <stdint.h>

typedef enum {
    MAX_ENTITIES = 16384,

    CHUNK_WIDTH = 1 << 10,
    CHUNK_HEIGHT = 1 << 10,

    MAP_HEIGHT = 1 << 14,
    MAP_WIDTH = 1 << 14,
} something;

typedef int16_t ZEntityId;
typedef int16_t ZEntityIdx;
typedef int16_t ZEntityMaxAmount;
typedef int16_t ZChunkId;

typedef struct {
    ZEntityMaxAmount count;
    ZEntityIdx start_index;
} ZChunk;

typedef struct ZCore ZCore;

typedef void (*ZAction)(ZCore *den);