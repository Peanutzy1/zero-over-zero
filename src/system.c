#include <raylib.h>
// #include <stdio.h>

#include "zero.h"

void z_system_init(ZCore* core) { core->move_speed = 1000; }

static inline void z_panel_check_click(
    Vector2 pos, Vector2 size, 
    uint16_t* bitmask, ZEntityId id,
    ZCommandBuffer* buffer, Rectangle center_box, bool clicked
) {
    Rectangle rect = { pos.x, pos.y, size.x, size.y };

    if (!CheckCollisionRecs(rect, center_box)) {
        *bitmask &= ~IS_HOVERED;
        return;
    }

    *bitmask |= IS_HOVERED;
    if (buffer->hovering_count < 16) {
        buffer->hovering[buffer->hovering_count++] = id;
    }

    if (clicked) {
        *bitmask |= IS_CLICKED;
        if (buffer->clicking_count < 16) {
            buffer->clicking[buffer->clicking_count++] = id;
        }
    }
}

void z_system_hitcheck(ZCore* core) {
    ZCommandBuffer* buffer = &core->buffer;
    bool clicked = IsKeyPressed(KEY_ENTER);

    Vector2 center_world = GetScreenToWorld2D(
        (Vector2){ core->screen_size.x / 2.0f, core->screen_size.y / 2.0f },
        core->camera
    );
    Rectangle center_box = { center_world.x - 5.0f, center_world.y - 5.0f, 10.0f, 10.0f };

    ZWorldButtonSlab* wbslab = core->wbslab;
    for (int i = 0; i < wbslab->entity_count; i++) {
        z_panel_check_click(
            wbslab->positions[i], wbslab->sizes[i], 
            &wbslab->bitmasks[i], wbslab->idx_to_id[i],
            buffer, center_box, clicked
        );
    }
}

static inline void actual_furry_click_processor(ZCore* core, void* raw_ptr, ZMetaData meta) {
    switch (meta.slab_id) {
        case WBSLAB: {
            ZWorldButtonSlab* slab = (ZWorldButtonSlab*)raw_ptr;
            slab->onclicks[meta.idx](core);
            slab->bitmasks[meta.idx] &= ~IS_CLICKED;
            break;
        }
        default: break;
    }
}

void z_furry_onclick_processor(ZCore* core) {
    ZCommandBuffer* buffer = &core->buffer;
    
    for (int i = 0; i < buffer->clicking_count; i++) {
        ZEntityId global_id = buffer->clicking[i];
        ZMetaData metadata = core->id_to_metadata[global_id];
        
        void* raw_ptr = core->slab_lookup_table[metadata.slab_id];

        actual_furry_click_processor(core, raw_ptr, metadata);
    }

    buffer->clicking_count = 0;
    buffer->hovering_count = 0;
}