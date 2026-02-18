// The single transportation unit

#include <raylib.h>

#include "./z-drive/z-drive-tools.h"

#include "io.c"
#include "render.c"
#include "setup.c"
#include "system.c"

int main(void)
{
    InitWindow(800, 450, "zero-over-zero");
    ZDrive *drive = z_drive_init();
    
    if (!drive)
        return 1;

    PollInputEvents();
    z_setup(drive);

    z_io_init(drive);

    z_render_init();
    z_system_init(drive);

    SetConfigFlags(FLAG_VSYNC_HINT);

    while (!WindowShouldClose())
    {
        z_io_loop(drive);
        drive->delta_time = GetFrameTime();

        z_movement(drive);
        z_zoom(drive);
        z_hitcheck(drive);
        z_furry_processor(drive);
        
        z_system_loop(drive);
        z_render_loop(drive);
    }
    CloseWindow();
    free(drive);
}
