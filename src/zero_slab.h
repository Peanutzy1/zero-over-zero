#pragma once
#include <stdint.h>

constexpr uint16_t MAX_ENTITIES = (1 << 16) - 1;
typedef struct {
    float cam_x;
    float cam_y;
    float mouse_x;
    float mouse_y;

    uint32_t* pos_x_arr[];
} ZeroSlab;