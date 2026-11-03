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

typedef struct
{
    int field_0;
    unsigned int flags_4;
    unsigned int mode_8;
    char pad_C[8];
    unsigned int field_14;
    short pad_18;
    short field_1A;
    short pad_1C;
    unsigned short field_1E;
    int field_20;
    int pad_24;
    int field_28;
    int field_2C;
    char pad_30[0x1C];
    unsigned short x_4C;
    unsigned short y_4E;
    int pad_50;
    int ot_54;
    char pad_58[0x14];
    char field_6C[0x44];
    unsigned short field_B0;
    short field_B2;
    char pad_B4[0x100];
    unsigned short** lines_1B4;
    char pad_1B8[0xEC];
    int field_2A4;
} Msg_353A0;
extern int NthMaskedIndex_80034B88(int n, unsigned int mask);
// Matched
void sub_800353A0(Msg_353A0* o)
{
    switch (o->mode_8)
    {
    case 1:
    case 2:
        if (IsConfirmPressedP1_8003D380(0))
        {
            if (o->flags_4 & 0x800)
            {
                o->flags_4 = (o->flags_4 | 0x200) & ~0x800;
                o->field_1E++;
            }
            if (o->field_2C == 1)
            {
                o->flags_4 = (o->flags_4 | 0x200) & ~0x800;
                o->field_1E++;
            }
        }
        else if ((settingsFlags_8008B58C & 0xC00000) == 0xC00000 && o->field_2A4 == 1 &&
                 XaNoRequestPending_800435A4() == 1 && XaIsIdle_80043584() == 1)
        {
            if (o->flags_4 & 0x800)
            {
                o->flags_4 = (o->flags_4 | 0x20200) & ~0x800;
                o->field_1E++;
            }
            if (o->field_2C == 1)
            {
                o->flags_4 = (o->flags_4 | 0x20200) & ~0x800;
                o->field_1E++;
            }
        }
        break;
    case 4:
        if (IsConfirmPressedP1_8003D380(0))
        {
            o->flags_4 |= 0x200;
        }
        break;
    case 3:
        if (IsConfirmPressedP1_8003D380(0) && (o->flags_4 & 0x800))
        {
            o->flags_4 = (o->flags_4 | 0x200) & ~0x800;
            o->field_20 = 1;
            o->field_1E++;
        }
        else if (o->field_28 == 1 && IsCancelPressedP1_8003D41C(0) && (o->flags_4 & 0x800))
        {
            o->flags_4 |= 0x10000;
            o->field_1A = NthMaskedIndex_80034B88(o->field_B2 = o->field_B0 - 1, o->field_14);
        }
        break;
    }
}
extern void AddDrawAreaPrim_8003326C(void* a, unsigned long* ot);
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern void sub_8003EC2C(unsigned short* text, unsigned short* pos, int ot);
extern int MoveGridCursorP1_8003D630(short* m);
extern void sub_8002F6F8(void* a0, void* st, int a2);
// Matched
void sub_800355EC(Msg_353A0* o, unsigned short* r)
{
    RECT clip;
    union
    {
        unsigned short loc[2];
        int st[3];
        struct
        {
            int pad[2];
            int f0;
            short m[4];
        } menu;
    } u;
    RECT r2;
    int sel;
    clip.x = r[0] + 6;
    clip.y = r[1] + 4;
    clip.w = r[2] - 6;
    clip.h = r[3] - 7;
    if (clip.h > 0 && clip.w > 0)
    {
        int i = 0;
        unsigned short x = o->x_4C + 8;
        unsigned short y = o->y_4E + 4;
        unsigned short** p = o->lines_1B4;
        while (*p)
        {
            if (o->field_14 & (1 << i))
            {
                u.loc[1] = y;
                y += 12;
                u.loc[0] = x;
                AddClipDrawAreaPrim_80033308(&pOT_8008D454[o->ot_54]);
                sub_8003EC2C(*p, u.loc, o->ot_54);
                AddDrawAreaPrim_8003326C(&clip, &pOT_8008D454[o->ot_54]);
            }
            p++;
            i++;
        }
    }
    if (o->mode_8 == 3)
    {
        u.menu.f0 = 0;
        u.menu.m[0] = 0;
        u.menu.m[2] = 1;
        u.menu.m[3] = o->field_B0;
        u.menu.m[1] = o->field_B2;
        MoveGridCursorP1_8003D630((short*)&u.menu.f0);
        if (o->field_B2 != u.menu.m[1])
        {
            PlaySfx_80031494(0x7F);
        }
        o->field_B2 = u.menu.m[1];
    }
    sel = o->field_B2;
    u.st[0] = (int)o->field_6C;
    u.st[1] = 1;
    u.st[2] = 1;
    r2.x = o->x_4C + 4;
    r2.y = o->y_4E + sel * 12 + 3;
    r2.w = r[2] - 8;
    r2.h = 13;
    sub_8002F6F8(&r2, u.st, 0);
    o->field_1A = NthMaskedIndex_80034B88(o->field_B2, o->field_14);
}
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
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);
extern int MeasureTextWidth_8003E4C8(void* str);

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
            DrawText_8003E91C(2, *(void**)((char*)p + 0x74), pos, 0);
            r[0] = *(unsigned short*)((char*)p + 0x6E);
            r[1] = *(unsigned short*)((char*)p + 0x70);
            r[2] = MeasureTextWidth_8003E4C8(*(void**)((char*)p + 0x74)) + 0x11;
            r[3] = 0x12;
            sub_80035898(p, (int)r, 2);
            sub_800358CC(p, (int)r, 0);
        }
    }
}
extern EventNode* messageWindowTask_8008D640;
extern void PlayMusic_800300E0(int a, int b);
extern void UpdateItemMessageWindow_80035BD8(EventEntry* e, void* buf);
// Matched
EventEntry* OpenItemMessageWindow_80035AC8(int* init)
{
    EventEntry* e = AllocEventEntry_80043AF8(messageWindowTask_8008D640);
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
            PlayMusic_800300E0(1, 1);
        }
        e->cb_8 = UpdateItemMessageWindow_80035BD8;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        return e;
    }
    return 0;
}
INCLUDE_ASM(UpdateItemMessageWindow_80035BD8);
// Matched
void InitPadVibration_800364E4(int* p)
{
    padVibration_80095460[p[1]].flags_0 = 0;
    padVibration_80095460[p[1]].motor_2[0] = 0;
    padVibration_80095460[p[1]].motor_2[1] = 0;
}
