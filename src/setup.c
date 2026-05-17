#include <stdio.h>

#include "zero.h"

void b1_onclick(ZCore* core) {
    printf("hi. i'm b1 the button, printing core size %zu \n", sizeof(*core));
}

void z_setup(ZCore* core) {
    ZWorldButtonSlab* wbslab = core->wbslab;
    z_entity_add(core, 1);
    wbslab_add(
        wbslab,
        1,
        (Vector2){ 0, 0 },
        (Vector2){ 320, 200 },
        &b1_onclick
    );
}
