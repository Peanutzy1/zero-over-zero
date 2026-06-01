#include <raylib.h>
// #include <stdio.h>

#include "zero.h"

void z_system_init(ZCore* core) { core->move_speed = 1000; }

void z_system_hitcheck(ZCore* core) {
    bool clicked = IsKeyPressed(KEY_ENTER);

    Vector2 center_world = GetScreenToWorld2D(
        (Vector2){ core->screen_size.x / 2.0f, core->screen_size.y / 2.0f },
        core->camera
    );
    Rectangle center_box = { center_world.x - 5.0f, center_world.y - 5.0f, 10.0f, 10.0f };

    ZWorldButtonSlab* wbslab = core->wbslab;
    for (int i = 0; i < wbslab->entity_count; i++) {
        Rectangle button = {
            wbslab->positions[i].x,
            wbslab->positions[i].y,
            wbslab->sizes[i].x,
            wbslab->sizes[i].y
        };

        if (!CheckCollisionRecs(center_box, button)) {
            wbslab->bitmasks[i] &= ~IS_HOVERED;
            continue;
        }

        wbslab->bitmasks[i] |= IS_HOVERED;

        z_event_add_too_complicated(core, (ZEvent){
            .target_id = i,
            .action = wbslab->onhovers[i]
        });

        if (!clicked) continue;
        wbslab->bitmasks[i] |= IS_CLICKED;
        z_event_add_too_complicated(core, (ZEvent){
            .target_id = i,
            .action = wbslab->onclicks[i]
        });
    }
}
