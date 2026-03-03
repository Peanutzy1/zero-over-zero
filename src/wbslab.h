#pragma once
#include "z-types.h"

typedef enum
{
    IS_HOVERED = 1 << 0,
    IS_CLICKED = 1 << 1,
    WBSLAB_ECOUNT = 128,
    WBSLAB_CCOUNT = 16,
} bslab_globals;

typedef struct
{
    ZEntityId hovering[16];
    ZEntityId clicking[16];
    int hovering_count;
    int clicking_count;
} ZWorldButtonCmdBuffer;

typedef struct
{ 
    // slop exist here
    ZEntityIdx id_to_idx[MAX_ENTITIES];
    ZChunk chunks[WBSLAB_CCOUNT];
    ZEntityIdx id_to_chunk[WBSLAB_ECOUNT];
    ZEntityId idx_to_id[WBSLAB_ECOUNT];

    Vector2 positions[WBSLAB_ECOUNT];
    Vector2 sizes[WBSLAB_ECOUNT];
    uint16_t bitmasks[WBSLAB_ECOUNT];
    ZAction onclicks[WBSLAB_ECOUNT];

    ZWorldButtonCmdBuffer buffer;
} ZWorldButtonSlab;

void wbslab_init(ZCore* core);

void wbslab_render(ZWorldButtonSlab* wbslab);

void wbslab_add(ZWorldButtonSlab* wbslab, ZEntityId id, Vector2 position, Vector2 size, ZAction onclick);

void wbslab_hitcheck(ZCore* core);

void wbslab_furry_onclick_processor(ZCore* core);