#include <stdio.h>

#include "../z-drive/z-types.h"
#include "reuseable-code.h"

typedef enum {
    B1 = 1,
    B2 = 2,
    B3 = 3,
} buttons;

void b1_onclick (ZDrive* drive) {
    printf("hello world! \n");
    z_std_button_side(drive, B1);
}