#include <raylib.h>
// #include <stdio.h>

#include "./z-drive/z-types.h"

void z_system_init(ZDrive *drive) { drive->move_speed = 1000; }

ZDrive* z_system_loop(ZDrive *drive) { return drive; }

void z_movement(ZDrive *drive)
{
    float movement = drive->move_speed * drive->delta_time;
    drive->camera_position.x +=
        movement * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    drive->camera_position.y +=
        movement * (IsKeyDown(KEY_S) - IsKeyDown(KEY_W));
}

void z_zoom(ZDrive *drive)
{
    if (IsKeyPressed(KEY_I))
        drive->camera.zoom += 0.25f;
    if (IsKeyPressed(KEY_O))
        drive->camera.zoom -= 0.25f;

    if (drive->camera.zoom < 0.25f)
        drive->camera.zoom = 0.25f;
    if (drive->camera.zoom > 10.0f)
        drive->camera.zoom = 10.0f;
}

void z_hitcheck(ZDrive* drive)
{
    ZRenderSlab* render_slab = &drive->render_slab;
    ZCmdBuffer* cmd_buff = &drive->command_buffer;
    ZChunk chunk = render_slab->chunks[0];

    int box_size = 10;
    Vector2 center_world = GetScreenToWorld2D(
        (Vector2){drive->screen_size.x / 2.0f, drive->screen_size.y / 2.0f},
        drive->camera);

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
            render_slab->positions[i].x,
            render_slab->positions[i].y,
            render_slab->sizes[i].x,
            render_slab->sizes[i].y,
        };

        if (CheckCollisionRecs(whatever_this_is, center_box))
        {
            ZEntityId id = render_slab->head.index_to_id[i];
            cmd_buff->hovering[cmd_buff->hovering_count] = id;
            cmd_buff->hovering_count++;
            render_slab->bitmasks[i] |= IS_HOVERED;
            if (clicked)
            {
                cmd_buff->clicking[cmd_buff->clicking_count] = id;
                cmd_buff->clicking_count++;
                render_slab->bitmasks[i] |= IS_CLICKED;
            } // weee process this later.
        }
        else 
        { render_slab->bitmasks[i] &= ~IS_HOVERED; }
    }
}

void z_furry_processor(ZDrive* drive) {
    ZCmdBuffer* cmd_buff = &drive->command_buffer;
    ZLogicSlab* ls = &drive->logic_slab;
    for (int i = 0; i < cmd_buff->clicking_count; i++) {
        ls->onclicks[ls->head.id_to_index[cmd_buff->clicking[i]]](drive);
    }
    cmd_buff->clicking_count = 0;
    cmd_buff->hovering_count = 0;
}