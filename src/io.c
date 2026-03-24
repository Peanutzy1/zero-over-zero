#include "zcore.h"
#include <raylib.h>

void z_output_init(ZCore *core) {
    core->screen_size.x = GetScreenWidth();
    core->screen_size.y = GetScreenHeight();

    core->camera.target = (Vector2){0.0f, 0.0f};
    core->camera.offset = (Vector2){core->screen_size.x / 2.0f, core->screen_size.y / 2.0f};
    core->camera.rotation = 0.0f;
    core->camera.zoom = 1.0f;
}

// wrapper fn
void z_io_init(ZCore *core) { z_output_init(core); }

void z_output_loop(ZCore *core) {
    if (IsWindowResized()) {
        core->screen_size.x = GetScreenWidth();
        core->screen_size.y = GetScreenHeight();
        core->camera.offset = (Vector2){core->screen_size.x / 2.0f, core->screen_size.y / 2.0f};
    }; // this if statement is fine because this rarely runs, therefore predictable to branch predictor

    core->camera.target = core->camera_position;
}

void z_io_loop(ZCore *core) { z_output_loop(core); }