#pragma once

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "z-types.h"
#include "wbslab.h"
#include "zcore.h"
#include "zcore-utils.c"

void wbslab_init(ZCore* core) {
    core->wbslab = (ZWorldButtonSlab*)calloc(1, sizeof(ZWorldButtonSlab));
    assert(core->wbslab);

    ZWorldButtonSlab* wbslab = core->wbslab;
    memset(wbslab->chunks, -1, sizeof(wbslab->chunks));
    memset(wbslab->id_to_chunk, 0xFF, sizeof(wbslab->id_to_chunk));
    memset(wbslab->id_to_idx, 0xFF, sizeof(wbslab->id_to_idx));
    memset(wbslab->idx_to_id, 0xFF, sizeof(wbslab->idx_to_id));

    for (int i = 0; i < WBSLAB_ECOUNT; i++) {
        wbslab->onclicks[i] = &z_debug;
    }
    
    wbslab->chunks[0].start_index = 0;
    wbslab->chunks[0].count = 0;
};

void wbslab_add(ZWorldButtonSlab* wbslab, ZEntityId id, Vector2 position, Vector2 size, ZAction onclick) {
    assert(z_chunk_has_space(wbslab->chunks, 0));
    ZChunk* chunk = &wbslab->chunks[0];
    ZEntityIdx idx = chunk->start_index + chunk->count;
    chunk->count++;
    wbslab->id_to_idx[id] = idx;
    wbslab->idx_to_id[idx] = id;
    wbslab->id_to_chunk[id] = 0;
    wbslab->positions[idx] = position;
    wbslab->sizes[idx] = size;
    wbslab->onclicks[idx] = onclick;
}


void wbslab_render(ZWorldButtonSlab* wbslab)
{
    ZChunk chunk = wbslab->chunks[0];
    for (int i = 0; i < chunk.count; i++)
    {
        Rectangle rect = {
            wbslab->positions[i].x,
            wbslab->positions[i].y,
            wbslab->sizes[i].x,
            wbslab->sizes[i].y
        };

        uint8_t state_subtractor =
            64 * (((wbslab->bitmasks[i] & IS_HOVERED) != 0) +
                  ((wbslab->bitmasks[i] & IS_CLICKED) != 0));

        Color color = {
            255 - state_subtractor,
            255 - state_subtractor,
            255 - state_subtractor, 
            255
        };

        DrawRectangleRec(rect, color);
    };
}


void wbslab_hitcheck(ZCore* core)
{
    ZWorldButtonSlab* wbslab = core->wbslab;
    ZWorldButtonCmdBuffer* buffer = &wbslab->buffer;

    ZChunk chunk = wbslab->chunks[0];

    int box_size = 10;
    Vector2 center_world = GetScreenToWorld2D(
        (Vector2){core->screen_size.x / 2.0f, core->screen_size.y / 2.0f},
        core->camera);

    Rectangle center_box = {
        center_world.x - (box_size / 2.0f),
        center_world.y - (box_size / 2.0f),
        box_size,
        box_size
    };

    // printf("x: %f\ny: %f\n w: %f\nh: %f\n", center_box.x, center_box.y,
    // center_box.width, center_box.height);

    bool clicked = IsKeyPressed(KEY_ENTER);

    for (int i = chunk.start_index; i < chunk.count + chunk.start_index; i++)
    {
        Rectangle whatever_this_is = {
            wbslab->positions[i].x,
            wbslab->positions[i].y,
            wbslab->sizes[i].x,
            wbslab->sizes[i].y,
        };

        if (CheckCollisionRecs(whatever_this_is, center_box))
        {
            ZEntityId id = wbslab->idx_to_id[i];
            buffer->hovering[buffer->hovering_count] = id;
            buffer->hovering_count++;
            wbslab->bitmasks[i] |= IS_HOVERED;
            if (clicked)
            {
                buffer->clicking[buffer->clicking_count] = id;
                buffer->clicking_count++;
                wbslab->bitmasks[i] |= IS_CLICKED;
            } // weee process this later.
        }
        else 
        { wbslab->bitmasks[i] &= ~IS_HOVERED; }
    }
}

void wbslab_furry_onclick_processor(ZCore* core) {
    ZWorldButtonSlab* wbslab = core->wbslab;
    ZWorldButtonCmdBuffer* buffer = &wbslab->buffer;
    for (int i = 0; i < buffer->clicking_count; i++) {
        wbslab->onclicks[wbslab->id_to_idx[buffer->clicking[i]]](core);
    }
    buffer->clicking_count = 0;
    buffer->hovering_count = 0;
}