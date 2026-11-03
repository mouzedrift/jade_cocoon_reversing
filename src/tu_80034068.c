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

INCLUDE_DATA(dword_8007474C);
INCLUDE_DATA(dword_80074780);
INCLUDE_DATA(dword_80074794);
INCLUDE_DATA(dword_800747D0);
INCLUDE_DATA(dword_800747E8);
INCLUDE_DATA(dword_80074800);

// Matched
int sub_80034068(short* p)
{
    char* q = (char*)sub_80014390(((unsigned char*)p)[2]);
    if (magicData_8007C438[p[0]].field_0 & 0x40)
    {
        switch (magicData_8007C438[p[0]].field_7)
        {
        case 0:
            if (*(short*)&q[8] == *(short*)&q[0xA])
            {
                return 3;
            }
            break;
        case 1:
            if (p[0] != 0x10 && !(*(int*)q & 0x7FB))
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
int sub_8003412C(char* p)
{
    if (p)
    {
        return *(short*)(p + 0x42);
    }
    return 0;
}
extern unsigned char** off_80083800[];
extern unsigned char* off_800837D8;
// Matched
int sub_80034140(void)
{
    unsigned char*** t = off_80083800;
    char* sd = (char*)&saveData_8008B570;
    unsigned char** tbl = t[*(short*)(sd + 0x2E4)];
    unsigned char* list;
    short target;
    short i;
    if (tbl)
    {
        list = tbl[*(short*)(sd + 0x2E8)];
        if (list)
        {
            i = 0;
            if (list == off_800837D8)
            {
                target = *(short*)(sd + 0x2F0);
            }
            else
            {
                target = *(short*)(sd + 0x2EC);
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
extern void UpdateMessageWindow_80034BB8(int* a0, int* a1);
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
typedef struct
{
    int v[4];
} Quad_349B4;
typedef struct
{
    int field_0;
    int flags_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    Quad_349B4 field_18;
    char pad_28[0x1BC];
    signed char field_1E4[1];
} Unit_349B4;
typedef struct
{
    int flags_0;
    char pad_4[0x10];
    Unit_349B4* unit_14;
} UnitRef_349B4;
// Matched
int sub_800349B4(UnitRef_349B4* a0, Quad_349B4* out)
{
    Unit_349B4* u = a0->unit_14;
    if (u->flags_4 & 0x200)
    {
        *out = u->field_18;
        return 1;
    }
    return 0;
}
// Matched
void sub_80034A00(UnitRef_349B4* a0, Quad_349B4* out)
{
    *out = a0->unit_14->field_18;
}
// Matched
int sub_80034A30(UnitRef_349B4* a0)
{
    Unit_349B4* u = a0->unit_14;
    if (u->field_C == 3 || u->field_10 == 2)
    {
        return 1;
    }
    return 0;
}
// Matched
void sub_80034A68(UnitRef_349B4* a0)
{
    a0->unit_14->flags_4 |= 0x800;
}
// Matched
void sub_80034A84(UnitRef_349B4* a0)
{
    a0->unit_14->flags_4 |= 0x4000;
}
// Matched
void sub_80034AA0(UnitRef_349B4* a0)
{
    a0->flags_0 = (a0->flags_0 & ~1) | 0x8000;
}
// Matched
int sub_80034AB8(UnitRef_349B4* a0)
{
    return (a0->flags_0 & 0x8001) == 1;
}
// Matched
void sub_80034AD0(UnitRef_349B4* a0, int v)
{
    a0->unit_14->field_14 = v;
}
// Matched
int sub_80034ADC(UnitRef_349B4* a0, int idx)
{
    Unit_349B4* u = a0->unit_14;
    if (u->field_1E4[idx] == -2 || u->field_1E4[idx] >= 0)
    {
        u->field_1E4[idx] = -2;
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
extern void sub_80034C18(int* a);
extern void sub_800353A0(int* a);
// Matched
void UpdateMessageWindow_80034BB8(int* a0, int* a1)
{
    sub_80034C18(a1);
    sub_800353A0(a1);
    if (a1[2] == 7)
    {
        a0[0] = (a0[0] & ~1) | 0x8000;
    }
}
extern void PlaySfx_80031494(int id);
extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern int sub_800429A8(void* r);
extern int sub_8003580C(int* o, int* r);
extern void sub_800359F8(int* p);
extern void sub_80035900(int* p);
extern void sub_800355EC(int* o, int* r);
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
