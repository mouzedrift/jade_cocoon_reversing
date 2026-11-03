// EQUIP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

struct EquipCtx_equip;
typedef struct EquipTask_equip
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
    int field_C;
    int field_10;
    struct EquipCtx_equip* ctx_14;
} EquipTask_equip;

typedef struct EquipTaskOuter_equip
{
    char pad_0[0x10];
    EquipTask_equip t;
} EquipTaskOuter_equip;

typedef struct EquipCtx_equip
{
    short a_0[6];
    short b_C[6];
    short sel_18;
    short idx_1A;
    short mode_1C;
    short mask_1E;
    int field_20;
    int pad_24;
    int field_28;
    int field_2C;
    short pad_30[2];
    short r_34;
    short r_36;
    short r_38;
    short r_3A;
    short s_3C;
    short s_3E;
    short s_40;
    short s_42;
    unsigned short flags_44;
    short s_46;
} EquipCtx_equip;

extern EquipTaskOuter_equip* equipTask_8008D4C4;
extern short tab_800C59B0[];
extern short tab_800C59B8[];
extern short tab_800C59C0[];
extern unsigned short padPressed_8009194C;
extern int UpdateMenuCursor_8003D794(void* p, int a1);
extern void DrawMenuBackground_8002BE10();
extern void sub_800AD3F0(int a0);
extern int sub_800AD308(int a0);
extern int sub_800AD288(int a0, int a1);
extern int sub_800AD9EC(int a0, int a1);
extern void sub_800C4A94(EquipCtx_equip* c);
extern void sub_800C4D50(EquipCtx_equip* c);
extern void sub_800C4DF4(EquipCtx_equip* c);
extern void sub_800C51B0(EquipCtx_equip* c);
extern void sub_800C497C(EquipCtx_equip* c);
extern void sub_800C48B4(EquipTask_equip* t, EquipCtx_equip* c);
extern void sub_800C50F0(EquipTask_equip* t, EquipCtx_equip* c);
extern void sub_800C5064(EquipCtx_equip* c);
typedef struct
{
    short x;
    short y;
    short w;
    short h;
} Rect8_equip;

typedef struct
{
    short a;
    short b;
} ShortPair_equip;

typedef struct
{
    short a;
    char b;
    char c;
} Small_equip;

extern short uiColor_8008B590;
extern char name_800C59A0[];
extern int sub_80014390(int a0);
extern void sub_8002F7D0(void* p, int a1);
extern void sub_8002E288(int a0, int a1, int a2, void* p);
extern void sub_8002E188(void* a0, void* a1, void* a2, int a3);
extern void sub_8002B3DC(ShortPair_equip p, int b, void* c, int d);
extern void DrawWindow_80042460(void* a0, void* a1, void* a2, unsigned int a3);
extern void sub_800C5440(short a0, short a1, int a2);
typedef struct Widget_equip
{
    unsigned short flags_0;
    int field_4;
    void* field_8;
    void* field_C;
    short field_10;
    short field_12;
    char pad_14[8];
    unsigned short flags_1C;
    short pad_1E;
    int field_20;
    char pad_24[8];
    short field_2C;
    short field_2E;
    char pad_30[8];
    unsigned short flags_38;
    char pad_3A[2];
    int field_3C;
    char pad_40[8];
    short field_48;
    short field_4A;
} Widget_equip;

typedef struct
{
    int a;
    int b;
    int c;
    int d;
    void* e;
    int f;
} Params5510_equip;

extern Widget_equip* tab_800C598C[];
extern char name_800C4784[];
extern char name_800C5834[];
extern char name_800C5838[];
extern char name_8008D434[];
extern char name_8008D440[];
extern int fn_8001D2D4(int a0, int a1);
extern int GetEquipmentName_8001D128(int a0, int a1);
extern int sub_800AD2C8(int a0, int a1);
extern void DrawMenuWindows_8002A5A4(void* p);
extern void sub_8002C6DC(int a0, short a1, short a2);

typedef struct
{
    short a;
    short b;
    short c;
    short d;
    short e;
    int f;
} Quad16_equip;
extern void sub_800C5510(Quad16_equip* q, Rect8_equip* r, short sel);

extern char name_800826B0[];
extern char name_800C599C[];
extern char name_800C59A8[];
extern void DrawButtonHelpBar_8002B004(void* a0, int a1, int a2);
extern void AddClipDrawAreaPrim_80033308(void* p);
extern void sub_800C0E04(void* a0, void* a1, int a2);
extern void sub_800C5314(EquipCtx_equip* c);


INCLUDE_OVERLAY_ASM(equip, dword_800C29D0);

// Matched
void sub_800C47A8(void)
{
    EquipTask_equip* t = &equipTask_8008D4C4->t;
    EquipCtx_equip* c;
    short i;
    t->flags_0 = (t->flags_0 | 1) & 0xFFFF7FFF;
    c = t->ctx_14;
    for (i = 0; i < 6; i++)
    {
        c->b_C[i] = 0;
        c->a_0[i] = 0;
    }
    c->sel_18 = 0;
    SetFontClutOffset_8003F900(2, 0);
    SetFontClutOffset_8003F900(1, 0);
    c->mask_1E = 0;
    c->field_20 = 0;
    c->mode_1C = 0;
    c->flags_44 = 0;
    c->idx_1A = 0;
    c->field_2C = 0;
    c->field_28 = 0;
    c->s_40 = 0;
    c->s_42 = 0;
    c->s_46 = 0;
    c->mask_1E |= 3;
    c->field_20 |= 2;
    DrawMenuBackground_8002BE10();
    sub_800C497C(c);
    c->s_3C = 0;
    c->s_3E = 0;
    t->next_8 = sub_800C48B4;
    unknownFlags_8008D678 |= 0x80000000;
}


// Matched
void sub_800C48B4(EquipTask_equip* t, EquipCtx_equip* c)
{
    DrawMenuBackground_8002BE10();
    if (unknownFlags_8008D678 >= 0)
    {
        sub_800AD3F0(1);
        sub_800AD3F0(2);
        sub_800AD3F0(3);
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
    sub_800C4A94(c);
    sub_800C4D50(c);
    if (c->field_28 || c->field_2C)
    {
        sub_800C4DF4(c);
    }
    sub_800C51B0(c);
    if (c->s_42 < 8)
    {
        c->s_42++;
    }
}


// Matched
void sub_800C497C(EquipCtx_equip* c)
{
    short i;
    for (i = 0; i < 4; i++)
    {
        if ((tab_800C59B8[c->mode_1C] >> i) & 1)
        {
            short* e = &tab_800C59C0[i * 4];
            int v;
            c->r_34 = e[0];
            c->r_36 = e[1];
            c->r_38 = e[2];
            c->r_3A = e[3];
            if (c->mode_1C == 1)
            {
                v = sub_800AD308(c->sel_18 + 1);
                if (v < 2)
                {
                    v = 2;
                }
                c->r_38 = v + 1;
                if (c->sel_18 == 2)
                {
                    if (sub_800AD308(3) >= 2)
                    {
                        c->r_38++;
                    }
                }
            }
            break;
        }
    }
}


#if 0
// Not matched: register allocation of the hoisted constants differs ($19/$20 swapped)
void sub_800C4A94(EquipCtx_equip* c)
{
    short i;
    int ofs = 0x38;
    int k;
    Rect8_equip r;
    union
    {
        Quad16_equip q;
        Small_equip s;
    } u;
    Quad16_equip q28;
    if (unknownFlags_8008D678 < 0)
    {
        DrawButtonHelpBar_8002B004(name_800826B0, 0, 0xe);
    }
    for (i = 0; i < 4; i++)
    {
        if ((c->mask_1E >> i) & 1)
        {
            AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + ofs);
            switch (i)
            {
            case 0:
                if (c->flags_44 & 4)
                {
                    sub_800C5440(sub_800AD990(c->sel_18), c->sel_18, 0);
                }
                else if (!(c->flags_44 & 8))
                {
                    r.x = 0x53;
                    r.y = 0x89;
                    u.q.a = c->a_0[c->sel_18 + 1];
                    u.q.b = c->b_C[c->sel_18 + 1];
                    k = 2;
                    if (c->mode_1C != 1)
                    {
                        k = 1;
                    }
                    u.q.c = k;
                    u.q.d = 0xe;
                    u.q.e = 0;
                    u.q.f = 0;
                    sub_800C5510(&u.q, &r, c->sel_18);
                }
                AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + ofs);
                break;
            case 1:
                if (!(c->flags_44 & 2))
                {
                    r.x = 0xa;
                    r.y = 0x3d;
                    q28.a = c->sel_18;
                    q28.b = 0;
                    k = 4;
                    if (c->mode_1C == 0)
                    {
                        k = 2;
                    }
                    q28.c = k;
                    q28.d = 0xe;
                    q28.e = 0;
                    q28.f = 0;
                    sub_800C0E04(&q28, &r, 8);
                    sub_800C5314(c);
                    u.s.a = uiColor_8008B590;
                    u.s.b = 0;
                    u.s.c = 1;
                    DrawWindow_80042460(name_800C59A8, &u.s, (char*)pOT_8008D454 + 0x38, 0);
                }
                else
                {
                    sub_800C5440(sub_800AD288(c->a_0[c->sel_18 + 1] + c->b_C[c->sel_18 + 1], c->sel_18 + 1), c->sel_18, (int)name_800C599C);
                }
                AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + ofs);
                break;
            }
            if (c->s_42 == 8)
            {
                c->field_20 |= 1 << i;
            }
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(equip, sub_800C4A94);


// Matched
void sub_800C4D50(EquipCtx_equip* c)
{
    int v;
    UpdateMenuCursor_8003D794(&c->r_34, 0);
    if (c->s_42 >= 8)
    {
        if (IsConfirmPressedP1_8003D380(0))
        {
            v = tab_800C59B0[c->idx_1A + 1];
            if (v != -1)
            {
                if (v != 2)
                {
                    PlaySfx_80031494(0x7e);
                }
                c->field_28 = 1;
            }
        }
        else if (IsCancelPressedP1_8003D41C(1))
        {
            c->field_2C = 1;
        }
    }
}


// Matched
void sub_800C4DF4(EquipCtx_equip* c)
{
    if (c->field_28)
    {
        if (c->mode_1C == 1)
        {
            c->s_40 = sub_800AD288(c->s_3C + c->s_3E, c->sel_18 + 1);
        }
        c->a_0[c->idx_1A] = c->s_3C;
        c->b_C[c->idx_1A] = c->s_3E;
        c->s_3C = c->a_0[c->idx_1A + 1];
        c->s_3E = c->b_C[c->idx_1A + 1];
        c->idx_1A++;
        c->mode_1C = tab_800C59B0[c->idx_1A];
        if (c->mode_1C == 1)
        {
            c->s_3C = c->a_0[c->sel_18 + 1];
            c->s_3E = c->b_C[c->sel_18 + 1];
        }
        if (c->mode_1C != 1)
        {
            c->s_42 = 0;
        }
    }
    else if (c->field_2C)
    {
        c->idx_1A--;
        if (c->idx_1A == -1)
        {
            unknownFlags_8008D678 &= 0x7FFFFFFF;
            return;
        }
        c->mask_1E &= 0xfffc;
        c->mode_1C = tab_800C59B0[c->idx_1A];
        c->s_3C = c->a_0[c->idx_1A];
        c->s_3E = c->b_C[c->idx_1A];
        if (c->mode_1C == 1)
        {
            c->s_3C = c->a_0[c->sel_18 + 1];
            c->s_3E = c->b_C[c->sel_18 + 1];
        }
    }
    c->mask_1E |= 3;
    if (c->field_2C)
    {
        c->field_20 = (short)c->mask_1E;
    }
    sub_800C497C(c);
    c->field_2C = 0;
    c->field_28 = 0;
}


// Matched
void sub_800C5064(EquipCtx_equip* c)
{
    EquipTask_equip* t;
    if (sub_800AD9EC(c->s_40, c->sel_18))
    {
        PlaySfx_80031494(0x7e);
        c->field_2C = 1;
        sub_800C4DF4(c);
    }
    else
    {
        t = &equipTask_8008D4C4->t;
        PlaySfx_80031494(0x7c);
        c->flags_44 |= 8;
        t->next_8 = sub_800C50F0;
    }
}


extern char name_800C5D50[];
// Matched
void sub_800C50F0(EquipTask_equip* t, EquipCtx_equip* c)
{
    char* p = name_800C5D50;
    DrawMenuBackground_8002BE10();
    sub_800C4A94(c);
    DrawLargeTextBox_8002AF10((int)p, 0, 0xe);
    if (c->s_46 < 0x96)
    {
        c->s_46++;
    }
    if (padPressed_8009194C || c->s_46 >= 0x96)
    {
        c->field_2C = 1;
        c->s_46 = 0;
        c->flags_44 &= ~8;
        sub_800C4DF4(c);
        t->next_8 = sub_800C48B4;
    }
}


// Matched
void sub_800C51B0(EquipCtx_equip* c)
{
    short v;
    switch (c->mode_1C)
    {
    case 0:
        c->sel_18 = c->s_3C;
        c->a_0[0] = c->s_3C;
        break;
    case 1:
        c->s_40 = sub_800AD288(c->s_3C + c->s_3E, c->sel_18 + 1);
        c->a_0[c->sel_18 + 1] = c->s_3C;
        c->b_C[c->sel_18 + 1] = c->s_3E;
        break;
    case 2:
        sub_800C5064(c);
        break;
    }
    if (IsCircleHeldP1_8003D480() && c->mode_1C == 0 && sub_800AD990(c->sel_18) != 0xff)
    {
        c->flags_44 |= 4;
    }
    else
    {
        c->flags_44 &= ~4;
    }
    if (IsCircleHeldP1_8003D480() && c->mode_1C == 1 && c->s_40 != 0xff)
    {
        c->flags_44 |= 2;
    }
    else
    {
        c->flags_44 &= ~2;
    }
}



// Matched
void sub_800C5314(EquipCtx_equip* c)
{
    char buf10[0x18];
    char buf28[0x18];
    Rect8_equip r40;
    int h;
    int mode;
    h = sub_80014390(0);
    CalcEquippedStats_80033624(buf10, h);
    r40.x = 0xc2;
    r40.y = 0x31;
    sub_8002F7D0(&r40, 0xe);
    mode = c->mode_1C;
    if (mode == 1 && c->s_40 != 0xff)
    {
        union
        {
            ShortPair_equip p;
            Small_equip s;
        } u;
        Rect8_equip r50;
        sub_8002E288(h, c->s_40, c->sel_18, buf28);
        r40.x = 0x119;
        r40.y = 0x34;
        sub_8002E188(buf10, buf28, &r40, 0xe);
        u.p.a = 2;
        u.p.b = 0;
        r50.x = 0x112;
        r50.y = 0x57;
        sub_8002B3DC(u.p, frameCount_8008D3FC, &r50, 0xe);
        u.s.a = uiColor_8008B590;
        u.s.b = 0;
        u.s.c = mode;
        DrawWindow_80042460(name_800C59A0, &u.s, (char*)pOT_8008D454 + 0x38, 0);
    }
}


extern char tab_800C59E0[][16];
extern char tab_800C5B50[][16];
extern char tab_800C5C40[][16];
void sub_800C5440(short a0, short a1, int a2)
{
    int e = 0;
    switch (a1)
    {
    case 0:
        if (a0 < 0x17)
        {
            e = (int)tab_800C59E0 + a0 * 16;
        }
        break;
    case 1:
        if (a0 < 0xf)
        {
            e = (int)tab_800C5B50 + a0 * 16;
        }
        break;
    case 2:
        if (a0 < 0x11)
        {
            e = (int)tab_800C5C40 + a0 * 16;
        }
        break;
    default:
        e = 0;
        break;
    }
    if (e)
    {
        DrawLargeTextBox_8002AF10(e, a2, 0xe);
    }
}


#if 0
// Not matched: the constant 8 in the stack struct is built as addiu/sll/sra in the original
void sub_800C5510(Quad16_equip* q, Rect8_equip* r, short sel)
{
    short i;
    int v;
    int a;
    int flag;
    Params5510_equip prm;
    for (i = 0; i < 3; i++)
    {
        v = sub_800AD288(i + q->b, sel + 1);
        if (v != 0xff)
        {
            a = fn_8001D2D4(v, sel);
            v = GetEquipmentName_8001D128(v, sel);
            flag = sub_800AD2C8(i + q->b, sel + 1);
        }
        else
        {
            a = -1;
            v = (int)name_800C4784;
            flag = 0;
        }
        tab_800C598C[i]->field_4 = a;
        tab_800C598C[i]->field_20 = v;
        tab_800C598C[i]->field_3C = flag;
        tab_800C598C[i]->field_8 = name_8008D434;
        tab_800C598C[i]->field_C = name_8008D440;
        tab_800C598C[i]->field_10 = r->x;
        tab_800C598C[i]->field_12 = r->y + i * 22;
        tab_800C598C[i]->field_2C = r->x + 0x15;
        tab_800C598C[i]->field_2E = r->y + i * 22;
        tab_800C598C[i]->field_48 = r->x + 0x85;
        tab_800C598C[i]->field_4A = r->y + i * 22;
        if (flag == 0)
        {
            tab_800C598C[i]->flags_0 |= 0x40;
            tab_800C598C[i]->flags_1C |= 0x40;
            tab_800C598C[i]->flags_38 |= 0x40;
        }
        else
        {
            tab_800C598C[i]->flags_0 &= ~0x40;
            tab_800C598C[i]->flags_1C &= ~0x40;
            tab_800C598C[i]->flags_38 &= ~0x40;
        }
    }
    prm.a = q->c;
    prm.b = frameCount_8008D3FC;
    prm.c = (short)8;
    prm.d = q->a;
    prm.e = tab_800C598C;
    prm.f = q->d;
    DrawMenuWindows_8002A5A4(&prm);
    SetFontClutOffset_8003F900(2, 0);
    v = sub_800AD308(sel + 1) + 1;
    if (v < 3)
    {
        v = 3;
    }
    if (q->b != 0)
    {
        sub_8002C6DC((int)name_800C5834, 3, q->d);
    }
    if (q->b < v - 3 && v >= 4)
    {
        sub_8002C6DC((int)name_800C5838, 1, q->d);
    }
}
#endif
INCLUDE_OVERLAY_ASM(equip, sub_800C5510);


INCLUDE_OVERLAY_ASM(equip, dword_800C5834);
