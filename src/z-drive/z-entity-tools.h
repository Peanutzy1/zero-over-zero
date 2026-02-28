#pragma once

#include "z-types.h"
#include <assert.h>

bool z_chunk_has_space(ZChunk *chunks, uint8_t chunk_id)
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

bool z_checkif_entity_available(ZDrive* drive, ZEntityId id) {
    ZEntityId* id_list = drive->id_used;
    for (int i = 0; i < drive->used_id_count; i++) 
    {
        if (id == id_list[i])
            return false;
    }
    return true;
}

void z_entity_add(ZDrive *drive, ZEntityId id)
{
    assert(z_checkif_entity_available(drive, id));

    drive->id_used[drive->used_id_count] = id;
    drive->used_id_count++;
}

void z_entity_init_render(ZDrive *drive, ZEntityId id, ZChunkId chunk) {
    ZRenderSlab* rs = &drive->render_slab;
    assert(z_chunk_has_space(rs->chunks, chunk));

    ZSlabHeader* header = &rs->head;
    ZChunk* zchunk = &rs->chunks[chunk];

    ZEntityIndex render_slab_index = zchunk->start_index + zchunk->count;
    zchunk->count++;

    header->id_to_index[id] = render_slab_index;
    header->index_to_id[render_slab_index] = id;
    header->index_to_chunk[render_slab_index] = chunk;
}

void z_entity_init_logic(ZDrive *drive, ZEntityId id, ZChunkId chunk) {
    ZLogicSlab* ls = &drive->logic_slab;
    assert(z_chunk_has_space(ls->chunks, chunk));

    ZSlabHeader* header = &ls->head;
    ZChunk* zchunk = &ls->chunks[chunk];

    ZEntityIndex render_slab_index = zchunk->start_index + zchunk->count;
    zchunk->count++;

    header->id_to_index[id] = render_slab_index;
    header->index_to_id[render_slab_index] = id;
    header->index_to_chunk[render_slab_index] = chunk;
}

ZEntityIndex z_entity_header_remove (
    ZSlabHeader *header, ZChunk *chunks,
    ZEntityId id_to_remove,
    ZEntityIndex *out_last_index
) {
    ZEntityIndex hole_index = header->id_to_index[id_to_remove];
    uint8_t cid = header->index_to_chunk[hole_index];
    ZChunk *chunk = &chunks[cid];

    *out_last_index = chunk->start_index + chunk->count - 1;

    ZEntityId last_id = header->index_to_id[*out_last_index];

    header->id_to_index[last_id] = hole_index;
    header->index_to_id[hole_index] = last_id;
    header->index_to_chunk[hole_index] = cid;

    chunk->count--;
    return hole_index;
}

void z_entity_remove(ZDrive *drive, ZEntityId id_to_remove)
{
    ZEntityIndex last_index; // changes per slab
    ZSlabHeader *header = &drive->render_slab.head;
    ZChunk *chunks = drive->render_slab.chunks;
    ZEntityIndex hole_idx =
        z_entity_header_remove(header, chunks, id_to_remove, &last_index);
    drive->render_slab.positions[hole_idx] = drive->render_slab.positions[last_index];
    drive->used_id_count--;
}