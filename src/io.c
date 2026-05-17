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

void z_output_loop(ZCore* core) {
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