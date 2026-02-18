#include "systems/buttons.h"
#include "z-drive/z-entity-tools.h"
#include "z-drive/z-types.h"

void z_setup(ZDrive *drive)
{
    z_entity_add(drive, B1);
    z_entity_init_render(drive, B1, 0);

    ZRenderSlab* rs = &drive->render_slab;
    ZEntityIndex index_b1_rs = rs->head.id_to_index[B1];
    rs->positions[index_b1_rs].x = 0;
    rs->positions[index_b1_rs].y = 0;
    rs->sizes[index_b1_rs].x = 320;
    rs->sizes[index_b1_rs].y = 200;

    z_entity_init_logic(drive, B1, 0);

    ZLogicSlab* ls = &drive->logic_slab;
    ZEntityIndex index_b1_ls = ls->head.id_to_index[B1];
    ls->onclicks[index_b1_ls] = &b1_onclick;
}