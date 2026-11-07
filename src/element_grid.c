#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "element_grid.h"

const Block16 elementIconGridOffsets_800741D4 = { { 14, 0, 14, 14, 0, 14 } };

extern void DrawElementIcons_8002B2A4(short mask, short* base, int ot, Block16* d, int showUnlit);
void DrawElementIconsGrid_8002B228(short mask, short* pos, int ot, int unused)
{
    Block16 local = elementIconGridOffsets_800741D4;
    DrawElementIcons_8002B2A4(mask, pos, ot, &local, 1);
}
