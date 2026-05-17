#include <assert.h>
#include <stdlib.h>
#include <string.h>
// #include <stdio.h>

#include "zero.h"

void wbslab_init(ZCore* core) {
    core->wbslab = (ZWorldButtonSlab* )calloc(1, sizeof(ZWorldButtonSlab));
    assert(core->wbslab);

    ZWorldButtonSlab* wbslab = core->wbslab;
    memset(wbslab->id_to_idx, 0xFF, sizeof(wbslab->id_to_idx));
    memset(wbslab->idx_to_id, 0xFF, sizeof(wbslab->idx_to_id));

    for (int i = 0; i < WBSLAB_ECOUNT; i++) {
        wbslab->onclicks[i] = &z_debug;
    };

    wbslab->entity_count = 0;
}

void wbslab_add(
    ZWorldButtonSlab* wbslab,
    ZEntityId id,
    Vector2 position, Vector2 size,
    ZAction onclick
) {
    assert(wbslab->entity_count < WBSLAB_ECOUNT);
    ZEntityIdx idx = wbslab->entity_count++;
    wbslab->id_to_idx[id] = idx;
    wbslab->idx_to_id[idx] = id;
    wbslab->positions[idx] = position;
    wbslab->sizes[idx] = size;
    wbslab->onclicks[idx] = onclick;
}

static void wbslab_render_entity(ZWorldButtonSlab* wbslab, ZEntityIdx idx) {

    Rectangle rect = {
        wbslab->positions[idx].x,
        wbslab->positions[idx].y,
        wbslab->sizes[idx].x,
        wbslab->sizes[idx].y
    };

    uint8_t sub = 64 
    * (((wbslab->bitmasks[idx] & IS_HOVERED) != 0)
    + ((wbslab->bitmasks[idx] & IS_CLICKED) != 0));

    Color color = {
        (uint8_t)(255 - sub),
        (uint8_t)(255 - sub),
        (uint8_t)(255 - sub),
        255 
    };

    DrawRectangleRec(rect, color);
}

void wbslab_render(ZWorldButtonSlab* wbslab) {
    for (int idx = 0; idx < wbslab->entity_count; idx++) {
        wbslab_render_entity(wbslab, idx);
    }
}

void wbslab_hitcheck(ZCore* core) {
    ZWorldButtonSlab* wbslab = core->wbslab;
    ZWorldButtonCmdBuffer* buffer = &wbslab->buffer;

    float half_screen_w = core->screen_size.x / 2.0f;
    float half_screen_h = core->screen_size.y / 2.0f;
    int box_size = 10;

    Vector2 center_world = GetScreenToWorld2D(
        (Vector2){ half_screen_w, half_screen_h },
        core->camera
    );

    Rectangle center_box = {
        center_world.x - (box_size / 2.0f),
        center_world.y - (box_size / 2.0f),
        (float)box_size,
        (float)box_size
    };

    bool clicked = IsKeyPressed(KEY_ENTER);

    for (int i = 0; i < wbslab->entity_count; i++) {
        Rectangle button_rect = {
            wbslab->positions[i].x,
            wbslab->positions[i].y,
            wbslab->sizes[i].x,
            wbslab->sizes[i].y,
        };

        if (!CheckCollisionRecs(button_rect, center_box)) {
            wbslab->bitmasks[i] &= ~IS_HOVERED;
            continue;
        }

        ZEntityId id = wbslab->idx_to_id[i];

        if (buffer->hovering_count < 16) {
            buffer->hovering[buffer->hovering_count++] = id;
        }

        wbslab->bitmasks[i] |= IS_HOVERED;

        if (!clicked) continue;

        wbslab->bitmasks[i] |= IS_CLICKED;

        if (buffer->clicking_count < 16) {
            buffer->clicking[buffer->clicking_count++] = id;
        };
    }
}

void wbslab_furry_onclick_processor(ZCore* core) {
    ZWorldButtonSlab* wbslab = core->wbslab;
    ZWorldButtonCmdBuffer* buffer = &wbslab->buffer;
    for (int i = 0; i < buffer->clicking_count; i++) {
        wbslab->onclicks[wbslab->id_to_idx[buffer->clicking[i]]](core);
        wbslab->bitmasks[i] &= ~IS_CLICKED;
    }

    buffer->clicking_count = 0;
    buffer->hovering_count = 0;
}

/*
comment out because, i have more problems to worry about than culling.

void wbslab_culler_labeler(ZWorldButtonSlab* wbslab) {
    int chunk_acrosse = MAP_WIDTH / CHUNK_WIDTH;

    for (int i = 0; i < wbslab->entity_count; i++) {
        float absolute_map_x = wbslab->positions[i].x + MAP_WIDTH_F / 2;
        int chunk_x = floorf(absolute_map_x / CHUNK_WIDTH_F);

        float absolute_map_y = wbslab->positions[i].y + MAP_HEIGHT_F / 2;
        int chunk_y = floorf(absolute_map_y / CHUNK_HEIGHT_F);

        int spatial_hash = chunk_y * chunk_acrosse + chunk_x;
        wbslab->idx_to_chunk_location[i] = spatial_hash;
    }
}

#define SLAB_SWAP(arr, i, j) \
    do { \
        auto _tmp = (arr)[(i)]; \
        (arr)[(i)] = (arr)[(j)]; \
        (arr)[(j)] = _tmp; \ } while (0)

void wbslab_culler_swapper(ZWorldButtonSlab* wbslab, ZEntityIdx idx1, ZEntityIdx
idx2) { if (idx1 == idx2) return;

    ZEntityId idx1_id = wbslab->idx_to_id[idx1];
    ZEntityId idx2_id = wbslab->idx_to_id[idx2];

    // lil id and idx swappy thing
    wbslab->id_to_idx[idx1_id] = idx2;
    wbslab->id_to_idx[idx2_id] = idx1;
    wbslab->idx_to_id[idx1] = idx2_id;
    wbslab->idx_to_id[idx2] = idx1_id;

    // swap of all other components
    SLAB_SWAP(wbslab->positions, idx1, idx2);
    SLAB_SWAP(wbslab->sizes, idx1, idx2);
    SLAB_SWAP(wbslab->bitmasks, idx1, idx2);
    SLAB_SWAP(wbslab->onclicks, idx1, idx2);
    SLAB_SWAP(wbslab->idx_to_chunk_location, idx1, idx2);

    // dude im sorry for having this slop
}

void wbslab_insertion_sort_cull_everything_becuz_whynot(ZWorldButtonSlab
*wbslab) { for (int i = 0; i < wbslab->entity_count; i++) { ZEntityIdx j = i;

        while (j > 0 && wbslab->idx_to_chunk_location[j] <
wbslab->idx_to_chunk_location[j - 1]) { wbslab_culler_swapper(wbslab, j, j - 1);
            j--;
        }
    }
}

void
wbslab_now_i_accumulate_so_theres_starting_idxs_and_location(ZWorldButtonSlab
*wbslab) { if (wbslab->entity_count == 0) return; int chunk_count = 0; // person
count int current_chunk_location = wbslab->idx_to_chunk_location[0]; // current
person's birthplace int accumulator = 0; // current person's age (in entities)

    wbslab->chunks[0].start_index = 0;                  // initiate birthtime at
time entity 0 wbslab->chunk_location[0] = current_chunk_location; // initiate
birthplace to current birth place.

    for (int i = 0; i < wbslab->entity_count; i++) {
        if (i > 0 && current_chunk_location != wbslab->idx_to_chunk_location[i])
{

            // close up the old done for hag. (aka the old chunk)
            wbslab->chunks[chunk_count].count = accumulator;

            chunk_count++; // START A NEW LIFE!!!

            current_chunk_location = wbslab->idx_to_chunk_location[i]; // set up
my tracking record for new boy wbslab->chunks[chunk_count].start_index = i; //
reset time of birth

            wbslab->chunk_location[chunk_count] = current_chunk_location; //
reset birth location

            accumulator = 0; // reset age
        }

        accumulator++; // age the current person by 1 entity.
    }
    wbslab->chunks[chunk_count].count = accumulator; // close up the last old
hag. wbslab->chunk_count = chunk_count + 1;           // record
}

void wbslab_culler(ZWorldButtonSlab* wbslab) {
    wbslab_culler_labeler(wbslab);
    wbslab_insertion_sort_cull_everything_becuz_whynot(wbslab);
    wbslab_now_i_accumulate_so_theres_starting_idxs_and_location(wbslab);
}

static int wbslab_find_chunk_index(ZWorldButtonSlab* wbslab, ZChunkId target_id)
{ for (int i = 0; i < wbslab->chunk_count; i++) { if (wbslab->chunk_location[i]
== target_id) { return i;
        }

        if (wbslab->chunk_location[i] > target_id) {
            return -1;
        }
    }
    return -1;
}

void wbslab_update_visible_set(ZCore* core) {
    ZWorldButtonSlab* wbslab = core->wbslab;
    wbslab->buffer.visible_chunk_count = 0;

    // the bounds of your screen in my world
    Vector2 top_left = GetScreenToWorld2D((Vector2){0, 0}, core->camera);
    Vector2 bottom_right = GetScreenToWorld2D((Vector2){core->screen_size.x,
core->screen_size.y}, core->camera);

    // convert said bounds into chunk location max and min
    int min_x = (int)((top_left.x + MAP_WIDTH_F / 2) / CHUNK_WIDTH_F);
    int min_y = (int)((top_left.y + MAP_HEIGHT_F / 2) / CHUNK_HEIGHT_F);
    int max_x = (int)((bottom_right.x + MAP_WIDTH_F / 2) / CHUNK_WIDTH_F);
    int max_y = (int)((bottom_right.y + MAP_HEIGHT_F / 2) / CHUNK_HEIGHT_F);

    int chunk_acrosse = MAP_WIDTH / CHUNK_WIDTH;

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {

            if (x < 0 || x >= chunk_acrosse || y < 0) // kill it if it outta
bounds continue;

            ZChunkId target = (y * chunk_acrosse) + x;

            int c_idx = wbslab_find_chunk_index(wbslab, target);

            if (c_idx != -1) {
                if (wbslab->buffer.visible_chunk_count < 16) {
                    wbslab->buffer.visible_chunks[wbslab->buffer.visible_chunk_count++]
= c_idx;
                }
            }
        }
    }
}
*/