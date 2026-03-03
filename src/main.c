// The single transportation unit

#include <raylib.h>
#include "zcore.h"

#include "io.c"
#include "render.c"
#include "system.c"
#include "zcore-utils.c"
#include "wbslab-fn.c"
#include "mod/setup.c"

int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE); 

    InitWindow(1920, 1080, "zero-over-zero"); 

    if (!IsWindowFullscreen()) {
        ToggleFullscreen();
    }

    InitWindow(0, 0, "zero-over-zero");
    ZCore *core = z_core_init();
    
    if (!core)
        return 1;

    wbslab_init(core);

    z_setup(core);

    PollInputEvents();

    z_io_init(core);

    z_render_init();
    z_system_init(core);

    SetConfigFlags(FLAG_VSYNC_HINT);

    while (!WindowShouldClose())
    {
        z_io_loop(core);
        core->delta_time = GetFrameTime();

        z_movement(core);
        z_zoom(core);

        wbslab_hitcheck(core);

        wbslab_furry_onclick_processor(core);

        z_render_loop(core);
    }
    CloseWindow();
    free(core);
}
