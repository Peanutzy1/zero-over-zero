#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "zero.h"

void z_debug(ZCore* core) {
    printf("game might has a uninitialized behavior. %zu", sizeof(*core));
}

ZCore* z_core_init() {
    ZCore* core = calloc(1, sizeof(ZCore));
    assert(core);

    core->used_id_count = 0;
    return core;
}

static bool z_checkif_entity_available(ZCore* core, ZEntityId id) {
    ZEntityId* id_list = core->id_used;
    for (int i = 0; i < core->used_id_count; i++) {
        if (id == id_list[i]) return false;
    }
    return true;
}

void z_entity_add(ZCore* core, ZEntityId id) {
    assert(id >= 0 && id < MAX_ENTITIES);
    assert(z_checkif_entity_available(core, id));
    core->id_used[core->used_id_count++] = id;
}