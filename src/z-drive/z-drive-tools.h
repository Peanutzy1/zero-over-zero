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

ZDrive *z_drive_init()
{
    ZDrive *drive = calloc(1, sizeof(ZDrive));
    if (!drive)
        return nullptr;

    drive->used_id_count = 0;

    z_render_slab_init(drive);
    z_logic_slab_init(drive);
    return drive;
}
