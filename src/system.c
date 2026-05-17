#include <raylib.h>
// #include <stdio.h>

#include "zero.h"

void z_system_init(ZCore* core) { core->move_speed = 1000; }

void z_movement(ZCore* core) {
    float movement = core->move_speed * core->delta_time;
    core->camera_position.x += movement * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    core->camera_position.y += movement * (IsKeyDown(KEY_S) - IsKeyDown(KEY_W));
}

void z_zoom(ZCore* core) {
    if (IsKeyPressed(KEY_I))
        core->camera.zoom += 0.25f;
    if (IsKeyPressed(KEY_O))
        core->camera.zoom -= 0.25f;

    if (core->camera.zoom < 0.25f)
        core->camera.zoom = 0.25f;
    if (core->camera.zoom > 10.0f)
        core->camera.zoom = 10.0f;
}