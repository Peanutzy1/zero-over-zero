#pragma once
#include <raylib.h>
#include <stdint.h>

typedef struct ZDrive ZDrive;

typedef enum
{
    MAX_ENTITIES = 128,
    MAX_CHUNKS_PER_SLAB = 16
} something;

typedef int16_t ZEntityId;
typedef int16_t ZEntityIndex;
typedef int16_t ZEntityMaxAmount;
typedef int16_t ZChunkId;

typedef struct
{
    ZEntityMaxAmount count;
    ZEntityIndex start_index;
} ZChunk;

typedef struct
{
    ZEntityIndex index_to_chunk[MAX_ENTITIES];
    ZEntityIndex id_to_index[MAX_ENTITIES];
    ZEntityId index_to_id[MAX_ENTITIES];

    uint8_t chunk_count;

    uint8_t pad;
} ZSlabHeader;

typedef enum
{
    IS_HOVERED = 1 << 0,
    IS_CLICKED = 1 << 1,
} renslab_bit;

typedef struct
{
    ZSlabHeader head;
    ZChunk chunks[MAX_CHUNKS_PER_SLAB];
    Vector2 positions[MAX_ENTITIES];
    Vector2 sizes[MAX_ENTITIES];
    uint16_t bitmasks[MAX_ENTITIES];
} ZRenderSlab;

typedef void (*ZLogicAction)(ZDrive* den);

typedef struct
{
    ZSlabHeader head;
    ZChunk chunks[MAX_CHUNKS_PER_SLAB];
    ZLogicAction onclicks[MAX_ENTITIES];
}ZLogicSlab;

typedef struct
{
    ZEntityId hovering[16];
    ZEntityId clicking[16];
    int hovering_count;
    int clicking_count;
} ZCmdBuffer;

struct ZDrive
{
    ZEntityId id_used[MAX_ENTITIES];
    ZEntityId used_id_count;

    ZRenderSlab render_slab;
    ZLogicSlab logic_slab;
    ZCmdBuffer command_buffer;
    Camera2D camera;

    Vector2 camera_position;
    Vector2 screen_size;
    float move_speed;
    float delta_time;
    // uint32_t padding[14];
};
