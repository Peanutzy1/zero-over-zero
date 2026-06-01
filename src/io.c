#include "zero.h"
#include <raylib.h>

void z_io_init(ZCore* core) {
    core->screen_size.x = GetScreenWidth();
    core->screen_size.y = GetScreenHeight();

    core->camera.target = (Vector2){ 0.0f, 0.0f };
    core->camera.offset = (Vector2){
        core->screen_size.x / 2.0f,
        core->screen_size.y / 2.0f
    };

    core->camera.rotation = 0.0f;
    core->camera.zoom = 1.0f;
}

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

void z_output_loop(ZCore* core) {
    core->camera.target = core->camera_position;

    if (!IsWindowResized()) {
        core->camera.target = core->camera_position;
        return;
    };

    core->screen_size.x = GetScreenWidth();
    core->screen_size.y = GetScreenHeight();
    core->camera.offset = (Vector2){
        core->screen_size.x / 2.0f,
        core->screen_size.y / 2.0f
    };
}

void z_io_loop(ZCore* core) { z_output_loop(core); }
