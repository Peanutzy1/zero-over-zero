#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "z-types.h"
#include "zcore.h"

void z_debug(ZCore* core) {
    printf("game might has a uninitialized behavior. %zu", sizeof(core));
}

ZCore* z_core_init()
{
    ZCore *core = calloc(1, sizeof(ZCore));
    if (!core)
        return nullptr;

    core->used_id_count = 0;
    return core;
}

bool z_checkif_entity_available(ZCore* core, ZEntityId id) {
    ZEntityId* id_list = core->id_used;
    for (int i = 0; i < core->used_id_count; i++) 
    {
        if (id == id_list[i])
            return false;
    }
    return true;
}

void z_entity_add(ZCore *core, ZEntityId id)
{
    assert(z_checkif_entity_available(core, id));
    core->id_used[core->used_id_count++] = id;
}

inline bool z_chunk_has_space(ZChunk *chunks, ZChunkId chunk_id)
{
    ZChunk *chunk = &chunks[chunk_id];

    if (chunk->start_index < 0)
        return false;

    if (chunk_id < MAX_CHUNKS_PER_SLAB - 1)
    {
        ZChunk *next = &chunks[chunk_id + 1];
        if (next->start_index >= 0) 
            return (chunk->start_index + chunk->count < next->start_index);
    }

    return (chunk->start_index + chunk->count < MAX_ENTITIES);
}