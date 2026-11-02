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
    unsigned short mask_1E;
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
extern unsigned short word_8009194C;
extern int sub_8003D794(void* p, int a1);
extern void sub_8002BE10();
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

INCLUDE_OVERLAY_ASM(equip, dword_800C29D0);

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
    sub_8003F900(2, 0);
    sub_8003F900(1, 0);
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
    sub_8002BE10();
    sub_800C497C(c);
    c->s_3C = 0;
    c->s_3E = 0;
    t->next_8 = sub_800C48B4;
    unknownFlags_8008D678 |= 0x80000000;
}


void sub_800C48B4(EquipTask_equip* t, EquipCtx_equip* c)
{
    sub_8002BE10();
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


INCLUDE_OVERLAY_ASM(equip, sub_800C4A94);

void sub_800C4D50(EquipCtx_equip* c)
{
    int v;
    sub_8003D794(&c->r_34, 0);
    if (c->s_42 >= 8)
    {
        if (sub_8003D380(0))
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
        else if (sub_8003D41C(1))
        {
            c->field_2C = 1;
        }
    }
}


INCLUDE_OVERLAY_ASM(equip, sub_800C4DF4);

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
void sub_800C50F0(EquipTask_equip* t, EquipCtx_equip* c)
{
    char* p = name_800C5D50;
    sub_8002BE10();
    sub_800C4A94(c);
    sub_8002AF10((int)p, 0, 0xe);
    if (c->s_46 < 0x96)
    {
        c->s_46++;
    }
    if (word_8009194C || c->s_46 >= 0x96)
    {
        c->field_2C = 1;
        c->s_46 = 0;
        c->flags_44 &= ~8;
        sub_800C4DF4(c);
        t->next_8 = sub_800C48B4;
    }
}


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
    if (sub_8003D480() && c->mode_1C == 0 && sub_800AD990(c->sel_18) != 0xff)
    {
        c->flags_44 |= 4;
    }
    else
    {
        c->flags_44 &= ~4;
    }
    if (sub_8003D480() && c->mode_1C == 1 && c->s_40 != 0xff)
    {
        c->flags_44 |= 2;
    }
    else
    {
        c->flags_44 &= ~2;
    }
}


INCLUDE_OVERLAY_ASM(equip, sub_800C5314);

INCLUDE_OVERLAY_ASM(equip, sub_800C5440);

INCLUDE_OVERLAY_ASM(equip, sub_800C5510);

INCLUDE_OVERLAY_ASM(equip, dword_800C5834);
