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
typedef struct
{
    int field_0;
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} struct_rect_1B8;
typedef struct
{
    int field_0;
    unsigned int field_4_flags;
    char pad_8[0x1B0];
    struct_rect_1B8 field_1B8;
} struct_1BC_owner;
extern int sub_8003DB74(struct_rect_1B8* p, int a);
// Matched
int sub_8003580C(struct_1BC_owner* o, unsigned short* r)
{
    o->field_1B8.x = r[0] + 6;
    o->field_1B8.y = r[1] + 4;
    o->field_1B8.w = r[2] - 6;
    o->field_1B8.h = r[3] - 7;
    if ((short)o->field_1B8.h > 0 && (short)o->field_1B8.w > 0)
    {
        return sub_8003DB74(&o->field_1B8, ((o->field_4_flags >> 18) ^ 1) & 1);
    }
    return 1;
}
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
