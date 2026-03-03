#pragma once
#include <stdio.h>

#include "z-types.h"
#include "wbslab.h"
struct ZCore
{
    ZEntityId id_used[MAX_ENTITIES];
    ZEntityId used_id_count;
    
    ZWorldButtonSlab* wbslab;
    
    Camera2D camera;
    Vector2 camera_position;
    Vector2 screen_size;
    float move_speed;
    float delta_time;
    // uint32_t padding[14];
};

ZCore* z_core_init();
void z_debug(ZCore* core);
void z_entity_add(ZCore *core, ZEntityId id);