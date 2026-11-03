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
void sub_80035898(struct_obj_A* p, int a1, int a2)
{
    if (!(p->flags_4 & 0x40000))
    {
        sub_800429F8(a1, 2);
    }
}
// Matched
void sub_800358CC(struct_obj_A* p, int a1, int a2)
{
    if (!(p->flags_4 & 0x40000))
    {
        sub_80042B38(a1, 2);
    }
}
typedef struct
{
    int field_0;
    unsigned int flags_4;
    char pad_8[0x5C];
    unsigned short x;
    unsigned short y;
    int field_68;
    char pad_6C[0x18];
    int field_84;
    POLY_FT4 prim;
} struct_obj_35900;
// Matched
void sub_80035900(struct_obj_35900* o)
{
    if (!(o->flags_4 & 0x40000) && o->field_84 == 1)
    {
        if (o->field_68)
        {
            o->prim.x1 = o->x;
            o->prim.y0 = o->y;
            o->prim.x0 = o->x + 0x3F;
            o->prim.y1 = o->y;
            o->prim.x3 = o->x;
            o->prim.y2 = o->y + 0x3F;
            o->prim.x2 = o->x + 0x3F;
            o->prim.y3 = o->y + 0x3F;
        }
        else
        {
            setXY4(&o->prim, o->x, o->y, o->x + 0x3F, o->y, o->x, o->y + 0x3F, o->x + 0x3F, o->y + 0x3F);
        }
        AddPrimCopy_80040298(pOT_8008D454 + 1, &o->prim, 10);
    }
}
extern void sub_8003E91C(int mode, void* str, void* pos, int z);
extern int sub_8003E4C8(void* str);

// Matched
void sub_800359F8(struct_obj_A* p)
{
    short pos[2];
    short r[4];
    if (!(p->flags_4 & 0x40000))
    {
        if (*(int*)((char*)p + 0x74) != 0)
        {
            pos[0] = *(unsigned short*)((char*)p + 0x6E) + 7;
            pos[1] = *(unsigned short*)((char*)p + 0x70) + 4;
            sub_8003E91C(2, *(void**)((char*)p + 0x74), pos, 0);
            r[0] = *(unsigned short*)((char*)p + 0x6E);
            r[1] = *(unsigned short*)((char*)p + 0x70);
            r[2] = sub_8003E4C8(*(void**)((char*)p + 0x74)) + 0x11;
            r[3] = 0x12;
            sub_80035898(p, (int)r, 2);
            sub_800358CC(p, (int)r, 0);
        }
    }
}
extern EventNode* dword_8008D640;
extern void sub_800300E0(int a, int b);
extern void sub_80035BD8(EventEntry* e, void* buf);
// Matched
EventEntry* sub_80035AC8(int* init)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D640);
    int* o;
    if (e)
    {
        o = (int*)e->buffer;
        o[0] = (int)e;
        o[1] = 0;
        o[0x14 / 4] = 0;
        ((short*)o)[0x18 / 2] = 0;
        ((short*)o)[0x1A / 2] = 0;
        ((short*)o)[0x1C / 2] = 0;
        ((short*)o)[0x1E / 2] = 0;
        o[0x20 / 4] = 0;
        o[0x24 / 4] = 0;
        o[0x34 / 4] = 0;
        ((short*)o)[0x38 / 2] = 0;
        ((short*)o)[0x3A / 2] = 0;
        ((short*)o)[0x3C / 2] = 0;
        ((short*)o)[0x3E / 2] = 0;
        o[0x48 / 4] = 0;
        ((short*)o)[0x4C / 2] = 0;
        ((short*)o)[0x4E / 2] = 0;
        ((short*)o)[0x50 / 2] = 0;
        ((short*)o)[0x52 / 2] = 0;
        o[0x54 / 4] = 0;
        o[0x78 / 4] = 0;
        o[0x7C / 4] = 0;
        ((short*)o)[0xB0 / 2] = 0;
        ((short*)o)[0xB2 / 2] = 0;
        o[0x1B4 / 4] = 0;
        MemCopy_800403E8((unsigned int*)(o + 0x214 / 4), (unsigned int*)init, 0x50);
        o[0x20 / 4] = 0;
        o[0x24 / 4] = 1;
        if ((unsigned int)o[0x25C / 4] < 4)
        {
            sub_800300E0(1, 1);
        }
        e->cb_8 = sub_80035BD8;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        return e;
    }
    return 0;
}
INCLUDE_ASM(sub_80035BD8);
