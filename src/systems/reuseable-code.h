#include "../z-drive/z-types.h"

void z_std_button_side(ZDrive *drive, ZEntityId id)
{
    ZRenderSlab *rs = &drive->render_slab;
    ZEntityIdx idx = rs->head.id_to_idx[id];
    rs->bitmasks[idx] &= ~IS_CLICKED;
}