#include <raylib.h>
#include <stdlib.h>

#include "zero.h"

int main(void) {
    // before making core
    ZCore* core = z_core_init();

    // after making core
    wbslab_init(core);

    z_io_init(core);

    z_system_init(core);

    z_setup(core);

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, "zero-over-zero");

    while (!WindowShouldClose()) {
        z_io_loop(core);
        core->delta_time = GetFrameTime();

        z_movement(core);
        z_zoom(core);

        z_system_hitcheck(core);

        z_event_loop(core);
        z_render_loop(core);
    }
    CloseWindow();
    free(core);
}
