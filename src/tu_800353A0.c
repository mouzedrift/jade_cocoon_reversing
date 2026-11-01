#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"

INCLUDE_DATA(dword_80074850);
INCLUDE_DATA(dword_8007485C);
INCLUDE_DATA(dword_80074864);

INCLUDE_ASM(sub_800353A0);
INCLUDE_ASM(sub_800355EC);
INCLUDE_ASM(sub_8003580C);
// Matched
void sub_80035898(struct_obj_A* p, int a1)
{
    if (!(p->flags_4 & 0x40000))
    {
        sub_800429F8(a1, 2);
    }
}
// Matched
void sub_800358CC(struct_obj_A* p, int a1)
{
    if (!(p->flags_4 & 0x40000))
    {
        sub_80042B38(a1, 2);
    }
}
INCLUDE_ASM(sub_80035900);
INCLUDE_ASM(sub_800359F8);
INCLUDE_ASM(sub_80035AC8);
INCLUDE_ASM(sub_80035BD8);
