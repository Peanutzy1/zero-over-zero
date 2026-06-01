#include "zero.h"

void very_generic_onclick(ZCore* core, ZEvent* this_event) {
    ZWorldButtonSlab* wbslab = core->wbslab;
    ZEntityIdx local_idx = this_event->target_id;
    if (!this_event->tick_timer) {
        this_event->timer = 0.2f;
        this_event->tick_timer = true;
    }

    if (this_event->timer <= 0) {
        wbslab->bitmasks[local_idx] &= ~IS_CLICKED;
        this_event->kill_me = true;
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void no_op(ZCore* core, ZEvent* this_event) {}
#pragma clang diagnostic pop

void z_setup(ZCore* core) {
    z_entity_add(core, 1);
    wbslab_add(
        core,
        1,
        (Vector2){ 0, 0 },
        (Vector2){ 320, 200 },
        &very_generic_onclick,
        &no_op
    );
}
