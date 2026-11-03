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
#include "msgwin.h"

INCLUDE_DATA(dword_8007474C);
INCLUDE_DATA(dword_80074780);
INCLUDE_DATA(dword_80074794);
INCLUDE_DATA(dword_800747D0);
INCLUDE_DATA(dword_800747E8);
INCLUDE_DATA(dword_80074800);

// Matched
int sub_80034068(short* p)
{
    UnitStatus* q = sub_80014390(((unsigned char*)p)[2]);
    if (magicData_8007C438[p[0]].field_0 & 0x40)
    {
        switch (magicData_8007C438[p[0]].field_7)
        {
        case 0:
            if (q->hp_8 == q->maxHp_A)
            {
                return 3;
            }
            break;
        case 1:
            if (p[0] != 0x10 && !(q->status_0 & 0x7FB))
            {
                return 3;
            }
            break;
        }
    }
    return 0;
}
// Matched
int sub_80034124(void)
{
    return 0;
}
// Matched
int sub_8003412C(UnitStatus* p)
{
    if (p)
    {
        return p->elementMask_42;
    }
    return 0;
}
extern unsigned char** off_80083800[];
extern unsigned char* off_800837D8;
// Matched
int sub_80034140(void)
{
    unsigned char*** t = off_80083800;
    SaveData* sd = &saveData_8008B570;
    unsigned char** tbl = t[sd->mapId_2E4[0].field_0];
    unsigned char* list;
    short target;
    short i;
    if (tbl)
    {
        list = tbl[sd->mapId_2E4[1].field_0];
        if (list)
        {
            i = 0;
            if (list == off_800837D8)
            {
                target = sd->mapId_2E4[3].field_0;
            }
            else
            {
                target = sd->mapId_2E4[2].field_0;
            }
            while (list[i] != 0xFF)
            {
                if (list[i] == 200 || target == list[i])
                {
                    goto found;
                }
                i++;
            }
        }
        return 0;
    found:
        return 1;
    }
    return 0;
}
extern EventNode* messageWindowTask_8008D640;
typedef struct
{
    short w;
    short h;
} Size_8003422C;
extern Size_8003422C MeasureTextLines_8003E3B4(int* list);
extern Size_8003422C MeasureTextLinesMasked_8003E2A8(int* list, unsigned int mask);
extern int MeasureTextWidth_8003E4C8(int str);
extern void sub_800A6308(int a, void* b);
extern void sub_800A1B2C(int a, void* b);
extern short** sub_80034900(short** list);
extern void UpdateMessageWindow_80034BB8(int* a0, MsgWindow* a1);
typedef struct
{
    char pad_0[0xB4];
    int* list_B4[1];
} Win_8003422C;
typedef struct
{
    char pad_0[0x1E4];
    signed char marks_1E4[0x30];
} WinMarks_8003422C;
#define WL(n) (((Win_8003422C*)w)->list_B4[n])
#define WS(off) (*(short*)((char*)w + (off)))
#define WI(off) (*(int*)((char*)w + (off)))
#if 0
// Not matched: 41 lines; scheduling of the 0x14 store vs the 0x8/0xC/0x10 stores, and the shared tail (x+0xA) lands in a0 instead of v0
EventEntry* OpenMessageWindow_8003422C(int* cfg)
{
    unsigned short x;
    EventEntry* e;
    int* w;
    int** list;
    int* p;
    int n;
    int i;
    Size_8003422C sz;
    int c;
    signed char* q;

    e = AllocEventEntry_80043AF8(messageWindowTask_8008D640);
    if (!e)
    {
        return 0;
    }
    w = (int*)e->buffer;
    WI(0x0) = (int)e;
    WI(0x4) = 0;
    WI(0x14) = 0;
    WS(0x18) = 0;
    WS(0x1A) = 0;
    WS(0x1C) = 0;
    WS(0x1E) = 0;
    WI(0x20) = 0;
    WI(0x24) = 0;
    WI(0x34) = 0;
    WS(0x38) = 0;
    WS(0x3A) = 0;
    WS(0x3C) = 0;
    WS(0x3E) = 0;
    WI(0x48) = 0;
    WS(0x4C) = 0;
    WS(0x4E) = 0;
    WS(0x50) = 0;
    WS(0x52) = 0;
    WI(0x54) = 0;
    WI(0x78) = 0;
    WI(0x7C) = 0;
    WS(0xB0) = 0;
    WS(0xB2) = 0;
    WI(0x1B4) = 0;
    if (cfg[0x28 / 4] == 0 && cfg[0x2C / 4] != 0)
    {
        WI(0x68) = 1;
    }
    else
    {
        WI(0x68) = 0;
    }
    WS(0x6C) = 0;
    WI(0x2C) = cfg[0x3C / 4];
    WI(0x30) = cfg[0x38 / 4];
    n = cfg[0x44 / 4];
    WI(0x2A4) = n;
    if (!(((unsigned char*)&saveData_8008B570)[0x1F] & 1) && n == 1)
    {
        WI(0x4) |= 0x40000;
    }
    WI(0x14) = cfg[0x18 / 4];
    WI(0x8) = 0;
    WI(0xC) = 1;
    WI(0x10) = 0;
    WI(0x28) = cfg[0x14 / 4];
    WI(0x74) = cfg[0xC / 4];
    WI(0x84) = cfg[0x20 / 4];
    if (cfg[0x20 / 4] == 1)
    {
        sub_800A6308(cfg[0x24 / 4], (char*)w + 0x88);
    }
    else if (cfg[0x20 / 4] == 7)
    {
        sub_800A1B2C(cfg[0x24 / 4], (char*)w + 0x88);
        WI(0x84) = 1;
    }
    list = (int**)cfg[0x8 / 4];
    if (list)
    {
        list = (int**)sub_80034900((short**)list);
        while (*list)
        {
            WS(0x1C)++;
            WL(WI(0x7C)++) = (int*)list;
            sz = MeasureTextLines_8003E3B4((int*)list);
            if (WS(0x3C) < sz.w)
            {
                WS(0x3C) = sz.w;
            }
            if (WS(0x3E) < sz.h)
            {
                WS(0x3E) = sz.h;
            }
            while (*list++)
            {
            }
        }
        WL(WI(0x7C)) = 0;
    }
    p = (int*)cfg[0x1C / 4];
    if (p)
    {
        if (sub_8003E484(*p) == 1)
        {
            WI(0x1B4) = (int)(p + 1);
        }
        else
        {
            WI(0x1B4) = (int)p;
        }
        sz = MeasureTextLinesMasked_8003E2A8((int*)WI(0x1B4), WI(0x14));
        WS(0x18) = CountUntilZero_80034B14((int*)WI(0x1B4));
        WS(0x50) = sz.w;
        WS(0x52) = sz.h;
        WS(0xB0) = CountMaskedUntilZero_80034B40((int*)WI(0x1B4), WI(0x14));
    }
    c = -1;
    WS(0x1BC) = 0;
    WS(0x1BE) = 0;
    WS(0x1C0) = 0;
    WS(0x1C2) = 0;
    WI(0x1C8) = 0;
    WI(0x1D4) = 0;
    WI(0x1D8) = 0;
    WI(0x1DC) = 0;
    WI(0x1E0) = 1;
    for (i = 0x2F, q = (signed char*)w + i; i >= 0; i--, q--)
    {
        q[0x1E4] = c;
    }
    WI(0x1CC) = cfg[0x10 / 4];
    WI(0x1C4) = (int)WL(WI(0x78));
    WI(0x1D0) = cfg[0x38 / 4];
    WS(0x3E) = 0x38;
    WS(0x3C) = 0xDB;
    WS(0x46) = 0x43;
    WS(0x44) = 0x46;
    WS(0x50) += 0x11;
    WS(0x52) += 7;
    if (cfg[0x28 / 4] == 1)
    {
        if (cfg[0x4 / 4])
        {
            WS(0x40) = ((short*)cfg[0x4 / 4])[0];
            WS(0x42) = ((short*)cfg[0x4 / 4])[0] + ((short*)cfg[0x4 / 4])[1];
            WS(0x38) = WS(0x40) + 0x45;
            WS(0x3A) = WS(0x42) + 0xE;
            WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
            WS(0x70) = WS(0x3A) - 0xC;
        }
        else
        {
            switch ((unsigned int)cfg[0])
            {
            case 0:
                WS(0x42) = WS(0x40) = 0x10;
                WS(0x38) = WS(0x40) + 0x44;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x3A) + WS(0x3E) - 2;
                break;
            case 1:
                WS(0x40) = 0x10;
                WS(0x42) = 0x74;
                WS(0x38) = WS(0x40) + 0x44;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            case 2:
                WS(0x40) = 0x10;
                WS(0x42) = 0xA1;
                WS(0x38) = WS(0x40) + 0x44;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            }
        }
        x = WS(0x40);
    }
    else
    {
        if (cfg[0x4 / 4])
        {
            WS(0x40) = ((short*)cfg[0x4 / 4])[0];
            WS(0x42) = ((short*)cfg[0x4 / 4])[0] + ((short*)cfg[0x4 / 4])[1];
            WS(0x38) = WS(0x40) + 0x45;
            WS(0x3A) = WS(0x42) + 0xD;
            WS(0x6E) = WS(0x38) + WS(0x3C) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
            WS(0x70) = WS(0x3A) - 0xC;
        }
        else
        {
            switch ((unsigned int)cfg[0])
            {
            case 0:
                WS(0x42) = WS(0x38) = 0x10;
                WS(0x40) = WS(0x38) + 0xDA;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x6E) = WS(0x40) + WS(0x44) - MeasureTextWidth_8003E4C8(WI(0x74)) - 0x10;
                WS(0x70) = WS(0x42) + WS(0x46) - 2;
                break;
            case 1:
                WS(0x42) = 0x60;
                WS(0x38) = 0x10;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x40) = WS(0x38) + 0xDA;
                WS(0x6E) = WS(0x38);
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            case 2:
                WS(0x42) = 0xA1;
                WS(0x38) = 0x10;
                WS(0x3A) = WS(0x42) + 0xD;
                WS(0x40) = WS(0x38) + 0xDA;
                WS(0x6E) = WS(0x38);
                WS(0x70) = WS(0x3A) - 0x10;
                break;
            }
        }
        x = WS(0x38);
    }
    WS(0x4C) = x + 0xA;
    WS(0x4E) = WS(0x3A) + WS(0x3E) + 3;
    WS(0x70) -= 2;
    WS(0x3A) -= 2;
    WS(0x64) = WS(0x40) + 3;
    WS(0x66) = WS(0x42) + 2;
    WS(0x1B8) = WS(0x38) + 7;
    WS(0x1BA) = WS(0x3A) + 4;
    e->cb_8 = (EventEntryFn)UpdateMessageWindow_80034BB8;
    e->flags = (e->flags | 1) & ~0x8000;
    return e;
}
#endif
INCLUDE_ASM(OpenMessageWindow_8003422C);
extern unsigned short* EncodeText_8003F684(int mode, unsigned short* s);
// Matched
short** sub_80034900(short** list)
{
    short** p = list;
    short* t;
    while (*p)
    {
        t = (short*)EncodeText_8003F684(2, (unsigned short*)*p);
        if (*t == 0xC1)
        {
            *t = 0xC2;
            return list;
        }
        if (*t == 0xC2)
        {
            return p;
        }
        p++;
        if (!*p)
        {
            p++;
        }
    }
    return list;
}
// Matched
int sub_800349B4(MsgWindowEntry* a0, MsgResult* out)
{
    MsgWindow* u = a0->win_14;
    if (u->flags_4 & 0x200)
    {
        *out = u->res_18;
        return 1;
    }
    return 0;
}
// Matched
void sub_80034A00(MsgWindowEntry* a0, MsgResult* out)
{
    *out = a0->win_14->res_18;
}
// Matched
int sub_80034A30(MsgWindowEntry* a0)
{
    MsgWindow* u = a0->win_14;
    if (u->field_C == 3 || u->field_10 == 2)
    {
        return 1;
    }
    return 0;
}
// Matched
void sub_80034A68(MsgWindowEntry* a0)
{
    a0->win_14->flags_4 |= 0x800;
}
// Matched
void sub_80034A84(MsgWindowEntry* a0)
{
    a0->win_14->flags_4 |= 0x4000;
}
// Matched
void sub_80034AA0(MsgWindowEntry* a0)
{
    a0->flags_0 = (a0->flags_0 & ~1) | 0x8000;
}
// Matched
int sub_80034AB8(MsgWindowEntry* a0)
{
    return (a0->flags_0 & 0x8001) == 1;
}
// Matched
void sub_80034AD0(MsgWindowEntry* a0, int v)
{
    a0->win_14->mask_14 = v;
}
// Matched
int sub_80034ADC(MsgWindowEntry* a0, int idx)
{
    MsgWindow* u = a0->win_14;
    if (u->marks_1E4[idx] == -2 || u->marks_1E4[idx] >= 0)
    {
        u->marks_1E4[idx] = -2;
        return 1;
    }
    return 0;
}
// Matched
int CountUntilZero_80034B14(int* p)
{
    int n = 0;
    while (*p)
    {
        p++;
        n++;
    }
    return n;
}
// Matched
int CountMaskedUntilZero_80034B40(int* p, unsigned int mask)
{
    int n = 0;
    int i = 0;
    if (*p)
    {
        do
        {
            if (mask & (1 << i))
            {
                n++;
            }
            p++;
            i++;
        } while (*p);
    }
    return n;
}
// Matched
int NthMaskedIndex_80034B88(int n, unsigned int mask)
{
    int i = 0;
    if (n >= 0)
    {
        do
        {
            if (mask & (1 << i))
            {
                n--;
            }
            i++;
        } while (n >= 0);
    }
    return i - 1;
}
extern void sub_80034C18(MsgWindow* a);
extern void sub_800353A0(MsgWindow* o);
// Matched
void UpdateMessageWindow_80034BB8(int* a0, MsgWindow* a1)
{
    sub_80034C18(a1);
    sub_800353A0(a1);
    if (a1->mode_8 == 7)
    {
        a0[0] = (a0[0] & ~1) | 0x8000;
    }
}
extern void PlaySfx_80031494(int id);
extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern int sub_800429A8(void* r);
/* defined below (their parameter types are declared there) */
extern int sub_8003580C();
extern void sub_800359F8();
extern void sub_80035900();
extern void sub_800355EC();
#define PI(off) (*(int*)((char*)p + (off)))
#if 0
// Not matched: control flow and jump tables right (needs dword_80074800 cut to 0x1C in config/c_rodata.txt), register allocation of the flag temporaries and the reset block differ
void sub_80034C18(int* p)
{
    short r[4];
    int c;
    int i;
    signed char* q;
    int v;
    int f1;
    int f2;
    int f3;
    int f4;
    int f5;
    int f6;
    int f7;

    f1 = p[1];
    if (f1 & 0x80000)
    {
        f2 = f1 & ~0x40000;
        f2 &= ~0x80000;
        p[1] = f2;
    }
    switch (p[2])
    {
    case 0:
        break;
    case 1:
        if (p[0x2C / 4] == 1 || (p[1] & 0x800))
        {
            if (!(p[1] & 0x8000))
            {
                p[1] |= 0x8000;
            }
            if (!(p[1] & 0x40000))
            {
                sub_8003E268((unsigned short*)(p + 0x1B8 / 4));
            }
        }
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            c = -1;
            f2 = p[1];
            f2 &= ~0x20000;
            f2 &= ~0x8000;
            f2 &= ~0x200;
            p[1] = f2;
            PI(0x1C4) = (int)((Win_8003422C*)p)->list_B4[PI(0x78)];
            PI(0x1C8) = 0;
            PI(0x1D4) = 0;
            PI(0x1D8) = 0;
            PI(0x1DC) = 0;
            PI(0x1E0) = 1;
            for (i = 0x2F, q = (signed char*)p + i; i >= 0; i--, q--)
            {
                q[0x1E4] = c;
            }
            p[2] = 0;
            p[3] = 2;
        }
        break;
    case 2:
        if (p[0x2C / 4] == 1 || (p[1] & 0x800))
        {
            if (!(p[1] & 0x8000))
            {
                p[1] |= 0x8000;
            }
            if (!(p[1] & 0x40000))
            {
                sub_8003E268((unsigned short*)(p + 0x1B8 / 4));
            }
        }
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            f3 = p[1];
            f3 &= ~0x20000;
            f3 &= ~0x8000;
            f3 &= ~0x200;
            p[1] = f3;
        }
        if (p[1] & 0x4000)
        {
            f4 = p[1];
            f4 &= ~0x8000;
            f4 &= ~0x4000;
            p[1] = f4;
            p[2] = 6;
        }
        break;
    case 3:
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            p[2] = 5;
            f5 = p[1];
            f5 &= ~0x20000;
            f5 &= ~0x200;
            p[1] = f5;
        }
        else if (p[1] & 0x10000)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7D);
            }
            f6 = p[1];
            f6 &= ~0x20000;
            f6 &= ~0x10000;
            p[1] = f6;
        }
        if (p[1] & 0x4000)
        {
            p[1] &= ~0x4000;
            p[2] = 6;
        }
        break;
    case 4:
        if (p[1] & 0x200)
        {
            if (!(p[1] & 0x20000))
            {
                PlaySfx_80031494(0x7F);
            }
            f7 = p[1];
            p[4] = 1;
            p[2] = 0;
            f7 &= ~0x20000;
            f7 &= ~0x200;
            p[1] = f7;
        }
        if (!(p[1] & 0x40000))
        {
            sub_8003E268((unsigned short*)(p + 0x1B8 / 4));
        }
        break;
    case 5:
        p[4] = 3;
        break;
    case 6:
        p[3] = 4;
        break;
    case 7:
        break;
    }
    switch (p[3])
    {
    case 0:
        break;
    case 1:
        p[0x34 / 4]++;
        if (p[0x34 / 4] >= 8)
        {
            p[0x34 / 4] = 8;
            p[3] = 2;
        }
        InterpolateWindowRect_8004196C(r, p + 0x38 / 4, p[0x34 / 4], 8, 0);
        sub_80035898((struct_obj_A*)p, (int)r, 2);
        sub_800358CC((struct_obj_A*)p, (int)r, 0);
        InterpolateWindowRect_8004196C(r, p + 0x40 / 4, p[0x34 / 4], 8, 0);
        sub_80035898((struct_obj_A*)p, (int)r, 2);
        sub_800358CC((struct_obj_A*)p, (int)r, 0);
        break;
    case 2:
        sub_800359F8(p);
        sub_80035900(p);
        v = sub_8003580C(p, p + 0x38 / 4);
        if (v == 1)
        {
            p[3] = 3;
            PI(0x78)++;
            if ((int)((Win_8003422C*)p)->list_B4[PI(0x78)])
            {
                p[2] = v;
                if (p[1] & 0x40000)
                {
                    i = PI(0x78);
                    if (((Win_8003422C*)p)->list_B4[i + 1] == 0 && PI(0x1B4))
                    {
                        c = -1;
                        PI(0x1C8) = 0;
                        PI(0x1D4) = 0;
                        PI(0x1D8) = 0;
                        PI(0x1DC) = 0;
                        PI(0x1E0) = v;
                        PI(0x1C4) = (int)((Win_8003422C*)p)->list_B4[i];
                        for (i = 0x2F, q = (signed char*)p + i; i >= 0; i--, q--)
                        {
                            q[0x1E4] = c;
                        }
                        p[3] = 1;
                        p[0x34 / 4] = 0;
                        p[2] = 0;
                        p[4] = 0;
                        p[1] |= 0x80000;
                    }
                }
            }
            else if (PI(0x1B4))
            {
                p[2] = 4;
            }
            else
            {
                p[2] = 2;
                p[9] = v;
            }
        }
        sub_80035898((struct_obj_A*)p, (int)(p + 0x38 / 4), 2);
        sub_800358CC((struct_obj_A*)p, (int)(p + 0x38 / 4), 0);
        sub_80035898((struct_obj_A*)p, (int)(p + 0x40 / 4), 2);
        sub_800358CC((struct_obj_A*)p, (int)(p + 0x40 / 4), 0);
        break;
    case 3:
        sub_800359F8(p);
        sub_80035900(p);
        sub_8003580C(p, p + 0x38 / 4);
        sub_80035898((struct_obj_A*)p, (int)(p + 0x38 / 4), 2);
        sub_800358CC((struct_obj_A*)p, (int)(p + 0x38 / 4), 0);
        sub_80035898((struct_obj_A*)p, (int)(p + 0x40 / 4), 2);
        sub_800358CC((struct_obj_A*)p, (int)(p + 0x40 / 4), 0);
        break;
    case 4:
        p[0x34 / 4]--;
        if (p[0x34 / 4] <= 0)
        {
            p[0x34 / 4] = 0;
            p[3] = 0;
            p[2] = 7;
        }
        InterpolateWindowRect_8004196C(r, p + 0x38 / 4, p[0x34 / 4], 8, 0);
        if (sub_800429A8(r) == 1)
        {
            sub_8003580C(p, (int*)r);
            sub_80035898((struct_obj_A*)p, (int)r, 2);
            sub_800358CC((struct_obj_A*)p, (int)r, 0);
        }
        InterpolateWindowRect_8004196C(r, p + 0x40 / 4, p[0x34 / 4], 8, 0);
        sub_80035898((struct_obj_A*)p, (int)r, 2);
        sub_800358CC((struct_obj_A*)p, (int)r, 0);
        break;
    }
    switch (p[4])
    {
    case 0:
        break;
    case 1:
        p[0x48 / 4]++;
        if (p[0x48 / 4] >= 8)
        {
            p[0x48 / 4] = 8;
            p[4] = 2;
            p[2] = 3;
            p[9] = 1;
        }
        InterpolateWindowRect_8004196C(r, p + 0x4C / 4, p[0x48 / 4], 8, 5);
        if (sub_800429A8(r) == 1)
        {
            sub_800355EC(p, (int*)r);
            sub_80035898((struct_obj_A*)p, (int)r, 2);
            sub_800358CC((struct_obj_A*)p, (int)r, 0);
        }
        break;
    case 2:
        sub_800355EC(p, p + 0x4C / 4);
        sub_80035898((struct_obj_A*)p, (int)(p + 0x4C / 4), 2);
        sub_800358CC((struct_obj_A*)p, (int)(p + 0x4C / 4), 0);
        break;
    case 3:
        p[0x48 / 4]--;
        if (p[0x48 / 4] <= 0)
        {
            p[0x48 / 4] = 0;
            p[4] = 0;
            p[2] = 6;
        }
        InterpolateWindowRect_8004196C(r, p + 0x4C / 4, p[0x48 / 4], 8, 5);
        if (sub_800429A8(r) == 1)
        {
            sub_800355EC(p, (int*)r);
            sub_80035898((struct_obj_A*)p, (int)r, 2);
            sub_800358CC((struct_obj_A*)p, (int)r, 0);
        }
        break;
    }
}
#endif
INCLUDE_ASM(sub_80034C18);

INCLUDE_DATA(dword_80074850);
INCLUDE_DATA(dword_8007485C);
INCLUDE_DATA(dword_80074864);

extern int NthMaskedIndex_80034B88(int n, unsigned int mask);
// Matched
void sub_800353A0(MsgWindow* o)
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
                o->res_18.field_1E++;
            }
            if (o->field_2C == 1)
            {
                o->flags_4 = (o->flags_4 | 0x200) & ~0x800;
                o->res_18.field_1E++;
            }
        }
        else if ((settingsFlags_8008B58C.word & 0xC00000) == 0xC00000 && o->field_2A4 == 1 &&
                 XaNoRequestPending_800435A4() == 1 && XaIsIdle_80043584() == 1)
        {
            if (o->flags_4 & 0x800)
            {
                o->flags_4 = (o->flags_4 | 0x20200) & ~0x800;
                o->res_18.field_1E++;
            }
            if (o->field_2C == 1)
            {
                o->flags_4 = (o->flags_4 | 0x20200) & ~0x800;
                o->res_18.field_1E++;
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
            o->res_18.result_20 = 1;
            o->res_18.field_1E++;
        }
        else if (o->field_28 == 1 && IsCancelPressedP1_8003D41C(0) && (o->flags_4 & 0x800))
        {
            o->flags_4 |= 0x10000;
            o->res_18.sel_1A = NthMaskedIndex_80034B88(o->field_B2 = o->field_B0 - 1, o->mask_14);
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
void sub_800355EC(MsgWindow* o, unsigned short* r)
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
            if (o->mask_14 & (1 << i))
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
    u.st[0] = (int)&o->field_6C;
    u.st[1] = 1;
    u.st[2] = 1;
    r2.x = o->x_4C + 4;
    r2.y = o->y_4E + sel * 12 + 3;
    r2.w = r[2] - 8;
    r2.h = 13;
    sub_8002F6F8(&r2, u.st, 0);
    o->res_18.sel_1A = NthMaskedIndex_80034B88(o->field_B2, o->mask_14);
}
extern int sub_8003DB74(struct_rect_1B8* p, int a);
// Matched
int sub_8003580C(MsgWindow* o, unsigned short* r)
{
    o->clip_1B8.x = r[0] + 6;
    o->clip_1B8.y = r[1] + 4;
    o->clip_1B8.w = r[2] - 6;
    o->clip_1B8.h = r[3] - 7;
    if ((short)o->clip_1B8.h > 0 && (short)o->clip_1B8.w > 0)
    {
        return sub_8003DB74(&o->clip_1B8, ((o->flags_4 >> 18) ^ 1) & 1);
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
// Matched
void sub_80035900(MsgWindow* o)
{
    if (!(o->flags_4 & 0x40000) && o->field_84 == 1)
    {
        if (o->field_68)
        {
            o->prim_88.x1 = o->x_64;
            o->prim_88.y0 = o->y_66;
            o->prim_88.x0 = o->x_64 + 0x3F;
            o->prim_88.y1 = o->y_66;
            o->prim_88.x3 = o->x_64;
            o->prim_88.y2 = o->y_66 + 0x3F;
            o->prim_88.x2 = o->x_64 + 0x3F;
            o->prim_88.y3 = o->y_66 + 0x3F;
        }
        else
        {
            setXY4(&o->prim_88, o->x_64, o->y_66, o->x_64 + 0x3F, o->y_66, o->x_64, o->y_66 + 0x3F, o->x_64 + 0x3F, o->y_66 + 0x3F);
        }
        AddPrimCopy_80040298(pOT_8008D454 + 1, &o->prim_88, 10);
    }
}
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);

// Matched
void sub_800359F8(MsgWindow* p)
{
    short pos[2];
    short r[4];
    if (!(p->flags_4 & 0x40000))
    {
        if (p->title_74 != 0)
        {
            pos[0] = p->titleX_6E + 7;
            pos[1] = p->titleY_70 + 4;
            DrawText_8003E91C(2, p->title_74, pos, 0);
            r[0] = p->titleX_6E;
            r[1] = p->titleY_70;
            r[2] = MeasureTextWidth_8003E4C8((int)p->title_74) + 0x11;
            r[3] = 0x12;
            sub_80035898((struct_obj_A*)p, (int)r, 2);
            sub_800358CC((struct_obj_A*)p, (int)r, 0);
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
    MsgWindow* o;
    if (e)
    {
        o = e->buffer;
        o->self_0 = (int)e;
        o->flags_4 = 0;
        o->mask_14 = 0;
        o->res_18.count_18 = 0;
        o->res_18.sel_1A = 0;
        o->res_18.field_1C = 0;
        o->res_18.field_1E = 0;
        o->res_18.result_20 = 0;
        o->res_18.field_24 = 0;
        o->field_34 = 0;
        o->x_38 = 0;
        o->y_3A = 0;
        o->w_3C = 0;
        o->h_3E = 0;
        o->field_48 = 0;
        o->x_4C = 0;
        o->y_4E = 0;
        o->w_50 = 0;
        o->h_52 = 0;
        o->ot_54 = 0;
        o->field_78 = 0;
        o->count_7C = 0;
        o->field_B0 = 0;
        o->field_B2 = 0;
        o->lines_1B4 = 0;
        MemCopy_800403E8((unsigned int*)&o->item_214, (unsigned int*)init, 0x50);
        o->res_18.result_20 = 0;
        o->res_18.field_24 = 1;
        if ((unsigned int)o->item_214.mode_48 < 4)
        {
            PlayMusic_800300E0(1, 1);
        }
        e->cb_8 = UpdateItemMessageWindow_80035BD8;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        return e;
    }
    return 0;
}
typedef struct
{
    int field_0;
    unsigned int flags_4;
    int pad_8;
    int field_C;
    char pad_10[0x20C];
    int field_21C;
    ItemMsgEntry entries[3];
    int mode;
    int* text;
} ItemMsgWindow;
typedef struct
{
    short x;
    short y;
} Pos2_35BD8;
typedef struct
{
    int a;
    int b;
} TPage_35BD8;
extern int dword_80074850[];
extern int dword_8007485C[];
extern int dword_80074864[];
extern char* (*nameGetters_8007CB08[])(int id);
extern char* itemMessageSuffixes_80083818[];
extern char* off_80083820;
extern void sub_8003F264(void* pos, int val, int ot);
extern void DrawNumber_8003EF74(void* pos, int val, int ot);
extern void GetPublicTiySprt_80032470(int idx, SPRT* spr, TPage_35BD8* tp);
extern void sub_800AD1E0(int a, int b, int c);
extern void sub_800AD058(int a);
extern void sub_800AD8F4(int a);
extern void sub_800AD68C(int a);
extern void sub_800AD184(int a, int b, int c);
#if 0
// MeasureTextLines returns the 2 shorts as Size_8003422C in the code above; this near-miss reads them as x/y
extern Pos2_35BD8 MeasureTextLines_8003E3B4(int* list);
// Not matched: only the loop strength-reduction registers for o->entries[i] and the row y (line * 16 + y) are swapped ($s1/$s2).
// Needs dword_80074864 cut to 0x8 in config/c_rodata.txt (tu_800353A0 is merged into this TU for it: the jump table sits at
// 0x8007486C, which is 8-aligned only relative to this TU's .rdata start 0x8007474C; psylink packs objects on 4 bytes).
void UpdateItemMessageWindow_80035BD8(EventEntry* e, void* buf)
{
    ItemMsgWindow* o;
    SPRT spr[3];
    TPage_35BD8 tp[3];
    RECT r;
    Pos2_35BD8 p70;
    Pos2_35BD8 p78;
    Pos2_35BD8 p80;
    Pos2_35BD8 p88;
    Pos2_35BD8 p90;
    Pos2_35BD8 p98;
    Pos2_35BD8 pA0;
    int flag;
    int n;
    int i;
    int line;
    int y;
    int* text;
    int sfx;

    flag = 0;
    n = 0;
    o = buf;
    for (i = 0; i < 3; i++)
    {
        if (o->entries[i].type != -1)
        {
            n++;
        }
    }
    if (n >= 2 || (o->mode < 0 && n != 0))
    {
        flag = 1;
    }
    if (o->text)
    {
        int* q = o->text;
        while (*q++)
        {
            n++;
        }
        EncodeText_8003F684(2, (unsigned short*)o->text[0]);
        if (*(short*)o->text[0] == 0x91)
        {
            n--;
            o->text++;
        }
    }
    r.h = n * 16 | 8;
    r.w = 0xE3;
    r.x = 0x2F;
    r.y = (3 - n) * 9 + 0x5A;
    if (o->text)
    {
        p70 = MeasureTextLines_8003E3B4(o->text);
        p70.x += 8;
        if (r.w < p70.x)
        {
            r.w = p70.x;
        }
    }
    line = 0;
    y = 7;
    for (i = 0; i < 3; i++)
    {
        if (o->entries[i].type == 7)
        {
            p70.x = r.x + 6;
            p70.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, dword_80074850, &p70, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            p78.x = r.x + r.w - 4;
            p78.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            sub_8003F264(&p78, o->entries[i].count, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            line++;
            continue;
        }
        else if (o->entries[i].type == 6)
        {
            p80.x = r.x + 6;
            p80.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, dword_8007485C, &p80, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            if (flag)
            {
                p88.x = r.x + 0x84;
                p88.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawText_8003E91C(1, dword_80074864, &p88, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
                p90.x = r.x + 0x8D;
                p90.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawNumber_8003EF74(&p90, o->entries[i].count, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            }
        }
        else if ((unsigned int)o->entries[i].type < 6)
        {
            spr[i].x0 = 0;
            spr[i].y0 = 0;
            spr[i].w = 0;
            spr[i].h = 0;
            if (o->entries[i].type != -1)
            {
                switch (o->entries[i].type)
                {
                case 0:
                    GetPublicTiySprt_80032470(GetItemIcon_8001D2AC(o->entries[i].id), &spr[i], &tp[i]);
                    break;
                case 5:
                    GetPublicTiySprt_80032470(GetKeyItemIcon_8001D344(o->entries[i].id), &spr[i], &tp[i]);
                    break;
                case 1:
                case 2:
                case 3:
                    GetPublicTiySprt_80032470(((int (*)(int, int))GetEquipmentIcon_8001D2D4)(o->entries[i].id, o->entries[i].type - 1), &spr[i], &tp[i]);
                    break;
                case 4:
                    GetPublicTiySprt_80032470(((int (*)(int))GetPersonIcon_8001CD6C)(o->entries[i].id), &spr[i], &tp[i]);
                    break;
                }
                spr[i].r0 = 0x80;
                spr[i].g0 = 0x80;
                spr[i].b0 = 0x80;
                spr[i].x0 = r.x + 6;
                spr[i].y0 = r.y + (line * 16 + y) - 2;
                AddPrimCopy_80040298(pOT_8008D454, &spr[i], 5);
                AddPrimCopy_80040298(pOT_8008D454, &tp[i], 2);
            }
            p88.x = spr[i].w + r.x + 9;
            p88.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, nameGetters_8007CB08[o->entries[i].type](o->entries[i].id), &p88, 0);
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            if (flag)
            {
                p98.x = r.x + 0x84;
                p98.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawText_8003E91C(1, dword_80074864, &p98, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
                pA0.x = r.x + 0x8D;
                pA0.y = r.y + (line * 16 + y) + 2;
                AddClipDrawAreaPrim_80033308(pOT_8008D454);
                DrawNumber_8003EF74(&pA0, o->entries[i].count, 0);
                AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            }
        }
        else
        {
            continue;
        }
        line++;
    }
    if ((unsigned int)o->mode < 11 && !flag)
    {
        int w = MeasureTextWidth_8003E4C8(nameGetters_8007CB08[o->entries[0].type](o->entries[0].id)) + 0x19;
        int h = r.y + 9;
        p70.x = r.x + w;
        p70.y = h;
        AddClipDrawAreaPrim_80033308(pOT_8008D454);
        DrawText_8003E91C(2, itemMessageSuffixes_80083818[o->mode], &p70, 0);
        AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
    }
    if (o->entries[0].type != -1 && line == 1 && o->mode < 0 && !flag)
    {
        int w = MeasureTextWidth_8003E4C8(nameGetters_8007CB08[o->entries[0].type](o->entries[0].id)) + 0x19;
        int h = r.y + 9;
        p70.x = r.x + w;
        p70.y = h;
        AddClipDrawAreaPrim_80033308(pOT_8008D454);
        DrawText_8003E91C(2, off_80083820, &p70, 0);
        AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
    }
    if (o->text)
    {
        text = o->text;
        while (*text)
        {
            p70.x = r.x + 6;
            p70.y = r.y + (line * 16 + y) + 2;
            AddClipDrawAreaPrim_80033308(pOT_8008D454);
            DrawText_8003E91C(2, (void*)*text, &p70, 0);
            text++;
            AddDrawAreaPrim_8003326C(&r, pOT_8008D454);
            line++;
        }
    }
    sub_800429F8((int)&r, 0);
    sub_80042B38((int)&r, 0);
    o->field_C = 3;
    if (IsConfirmPressedP1_8003D380(0))
    {
        if ((o->flags_4 & 0x800) || o->field_21C == 1)
        {
            o->flags_4 = (o->flags_4 | 0x200) & ~0x800;
        }
    }
    if (o->flags_4 & 0x4000)
    {
        if (o->mode >= 4 && o->mode < 8)
        {
            for (i = 0; i < 3; i++)
            {
                if (o->entries[i].type == 0)
                {
                    sfx = 0x1E;
                    if (o->entries[i].id == 0x28)
                    {
                        sfx = 0x33;
                    }
                }
                else if (o->entries[i].type == 5)
                {
                    if (o->entries[i].id == 2 || o->entries[i].id == 9 || o->entries[i].id == 0x18 || o->entries[i].id == 0x11 || o->entries[i].id == 0x10 || o->entries[i].id == 0x12)
                    {
                        sfx = 0x1E;
                    }
                    else
                    {
                        sfx = 0x33;
                    }
                }
                else
                {
                    continue;
                }
                PlaySfx_80031494(sfx);
                sub_800AD1E0(o->entries[i].id, 1, o->entries[i].type);
            }
        }
        if (o->mode >= -1 && o->mode < 4)
        {
            for (i = 0; i < 3; i++)
            {
                if (o->entries[i].type == 7)
                {
                    sub_800AD058(o->entries[i].count);
                }
                else if (o->entries[i].type == 6)
                {
                    sub_800AD8F4(o->entries[i].count);
                }
                else if ((unsigned int)o->entries[i].type < 6)
                {
                    if (o->entries[i].type == 5)
                    {
                        sub_800AD68C(o->entries[i].id);
                    }
                    else
                    {
                        sub_800AD184(o->entries[i].id, o->entries[i].count, o->entries[i].type);
                    }
                }
            }
        }
        o->flags_4 &= ~0x4000;
        e->flags = (e->flags & ~1) | 0x8000;
    }
}
#endif
INCLUDE_ASM(UpdateItemMessageWindow_80035BD8);
// Matched
void InitPadVibration_800364E4(int* p)
{
    padVibration_80095460[p[1]].flags_0 = 0;
    padVibration_80095460[p[1]].motor_2[0] = 0;
    padVibration_80095460[p[1]].motor_2[1] = 0;
}
