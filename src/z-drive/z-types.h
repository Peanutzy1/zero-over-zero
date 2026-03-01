#pragma once
#include <raylib.h>
#include <stdint.h>

typedef struct ZCore ZCore;

typedef enum
{
    MAX_ENTITIES = 128,
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

typedef enum
{
    IS_HOVERED = 1 << 0,
    IS_CLICKED = 1 << 1,
    WBSLAB_ECOUNT = 128,
    WBSLAB_CCOUNT = 16,
} bslab_globals;

typedef void (*ZAction)(ZSlab* den);

typedef struct
{
    ZChunk chunks[WBSLAB_CCOUNT];
    ZEntityIdx index_to_chunk[WBSLAB_ECOUNT];
    ZEntityIdx id_to_idx[WBSLAB_ECOUNT];
    ZEntityId idx_to_id[WBSLAB_ECOUNT];
    Vector2 positions[WBSLAB_ECOUNT];
    Vector2 sizes[WBSLAB_ECOUNT];
    uint16_t bitmasks[WBSLAB_ECOUNT];
    ZAction onclicks[WBSLAB_ECOUNT];
} ZWorldButtonSlab;


typedef struct
{
    ZEntityId hovering[16];
    ZEntityId clicking[16];
    int hovering_count;
    int clicking_count;
} ZWorldButtonCmdBuffer;

struct ZCore
{
    ZEntityId id_used[MAX_ENTITIES];
    ZEntityId used_id_count;
    alignas(64);

    ZEntityId slab_id_offset[MAX_ENTITIES];
    ZEntityId last_offset_count;
    ZEntityId id_offset_count;
    alignas(64);

    Camera2D camera;
    Vector2 camera_position;
    Vector2 screen_size;
    float move_speed;
    float delta_time;
    // uint32_t padding[14];
};
