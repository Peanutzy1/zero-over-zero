#include "z-drive/z-types.h"
#include <raylib.h> 

// initialize inputs (mouse)

/*
inline void z_input_init(ZDrive *drive) 
{
    drive->mouse_screen = GetMousePosition();
    drive->mouse_world = GetScreenToWorld2D(
        drive->mouse_screen,
        drive->camera
    );
}
*/

// initialize screen
inline void z_output_init(ZDrive *drive) 
{
    drive->screen_size.x = GetScreenWidth();
    drive->screen_size.y = GetScreenHeight();

    drive->camera.target = (Vector2){ 0.0f, 0.0f };
    drive->camera.offset = (Vector2){
        drive->screen_size.x / 2.0f,
        drive->screen_size.y / 2.0f
    };
    drive->camera.rotation = 0.0f;
    drive->camera.zoom = 1.0f;
}

// wrapper fn
inline void z_io_init(ZDrive *drive) 
{
    z_output_init(drive);
}

// recalculate mouse position
/*
inline void z_input_loop(ZDrive *drive) 
{
    drive->mouse_screen = GetMousePosition();
    drive->mouse_world = GetScreenToWorld2D(
        drive->mouse_screen,
        drive->camera
    );

    // Branchless update of mouse state bit
    drive->mouse_states = (drive->mouse_states & ~(Z_MOUSE_LEFT)) | (IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? Z_MOUSE_LEFT : 0);
}
*/

inline void z_output_loop(ZDrive *drive) 
{
    if (IsWindowResized()) 
    {
        drive->screen_size.x = GetScreenWidth();
        drive->screen_size.y = GetScreenHeight();
        drive->camera.offset = (Vector2){
            drive->screen_size.x / 2.0f,
            drive->screen_size.y / 2.0f
        };
    }; // this if statement is fine because this rarely runs, therefore predictable to branch predictor

    drive->camera.target = drive->camera_position;
}

inline void z_io_loop(ZDrive *drive) 
{
    z_output_loop(drive);
}