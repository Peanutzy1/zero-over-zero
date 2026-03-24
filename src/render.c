#include "wbslab-fn.c"
#include "zcore.h"
#include <raylib.h>
// #include <stdio.h> incase i need testing

int z_render_init() { return 0; }

void z_draw_ui(ZCore *core) {
    Vector2 center = {core->screen_size.x / 2.0f, core->screen_size.y / 2.0f};
    Color cross_color = GREEN;

    float cross_size = 10.0f;
    float cross_thickness = 2.0f;

    DrawLineEx((Vector2){center.x, center.y - cross_size},
               (Vector2){center.x, center.y + cross_size},
               cross_thickness,
               cross_color);
    DrawLineEx((Vector2){center.x - cross_size, center.y},
               (Vector2){center.x + cross_size, center.y},
               cross_thickness,
               cross_color);
}

void z_render_loop(ZCore *core) {
    BeginDrawing();
    ClearBackground(GetColor(0x000000ff));
    BeginMode2D(core->camera);
    wbslab_render(core->wbslab);
    EndMode2D();
    z_draw_ui(core);
    EndDrawing();
}
