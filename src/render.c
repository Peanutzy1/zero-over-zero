#include "./z-drive/z-types.h" // IWYU pragma: keep
#include "z-drive/z-types.h"
#include <raylib.h>
// #include <stdio.h> incase i need testing

inline int z_render_init() { return 0; }

inline void z_render_button(ZDrive *drive)
{
    ZRenderSlab *render_slab = &drive->render_slab;
    ZChunk chunk = render_slab->chunks[0];
    for (int i = 0; i < chunk.count; i++)
    {
        Rectangle rect = {render_slab->positions[i].x,
                          render_slab->positions[i].y, render_slab->sizes[i].x,
                          render_slab->sizes[i].y};

        uint8_t state_subtractor =
            64 * (((render_slab->bitmasks[i] & IS_HOVERED) != 0) +
                  ((render_slab->bitmasks[i] & IS_CLICKED) != 0));

        Color color = {255 - state_subtractor, 255 - state_subtractor,
                       255 - state_subtractor, 255};

        DrawRectangleRec(rect, color);
    };
}
inline void z_draw_ui(ZDrive *drive)
{
    Vector2 center = {drive->screen_size.x / 2.0f, drive->screen_size.y / 2.0f};
    Color cross_color = GREEN;

    float cross_size = 10.0f;
    float cross_thickness = 2.0f;

    ZRenderSlab *render_slab = &drive->render_slab;
    for (int i = 0; i < render_slab->chunks[0].count; i++)
    {
        if (render_slab->bitmasks[i] & IS_HOVERED)
        {
            cross_color = GOLD;
            break;
        }
    }

    DrawLineEx((Vector2){center.x, center.y - cross_size},
               (Vector2){center.x, center.y + cross_size}, cross_thickness,
               cross_color);
    DrawLineEx((Vector2){center.x - cross_size, center.y},
               (Vector2){center.x + cross_size, center.y}, cross_thickness,
               cross_color);
}
inline void z_render_loop(ZDrive *drive)
{
    BeginDrawing();
    ClearBackground(GetColor(0x000000ff));
    BeginMode2D(drive->camera);
    z_render_button(drive);
    EndMode2D();
    z_draw_ui(drive);
    EndDrawing();
}
