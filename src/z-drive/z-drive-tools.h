#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "z-args-types.h" // IWYU pragma: keep
#include "z-types.h"

void z_render_slab_init(ZDrive *drive)
{
    ZSlabHeader *header = &drive->render_slab.head;
    memset(header->index_to_chunk, 0xFF, sizeof(header->index_to_chunk));

    for (int i = 0; i < MAX_CHUNKS_PER_SLAB; i++)
    {
        drive->render_slab.chunks[i] = (ZChunk){
            .start_index = (i == 0) ? 0 : -1,
        };
    }
}

void z_debug (ZDrive* drive) {
    printf("if you see this message uhhhhhhh oopsie i forgot to assign a value to this button. \n lemme use this thing %zu", sizeof(*drive));
}

void z_logic_slab_init(ZDrive *drive)
{
    ZSlabHeader *header = &drive->logic_slab.head;
    memset(header->index_to_chunk, 0xFF, sizeof(header->index_to_chunk));

    for (int i = 0; i < MAX_CHUNKS_PER_SLAB; i++)
    {
        drive->logic_slab.chunks[i] = (ZChunk){
            .start_index = (i == 0) ? 0 : -1,
        };
    }

    for (int i = 0; i < MAX_ENTITIES; i++) {
        drive->logic_slab.onclicks[i] = &z_debug;
    }
}

ZCore* z_core_init()
{
    ZCore *core = calloc(1, sizeof(ZCore));
    if (!core)
        return nullptr;

    core->used_id_count = 0;
    core->last_offset_count = 0;
    
    return core;
}

void z_core_allocate_entities(ZCore* core, ZEntityId count) {
    if (core->slab_id_offset == 0) {
        core->slab_id_offset[core->id_offset_count++] = 0;
        core->last_offset_count = count;
    } else {
        core->slab_id_offset[core->id_offset_count] 
        = core->slab_id_offset[core->id_offset_count - 1] 
        + core->last_offset_count;
        core->last_offset_count = count;
        core->id_offset_count++;
    }
}