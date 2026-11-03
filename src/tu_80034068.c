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

#if 0
int sub_80034068(short* p)
{
    int* q;
    int idx;
    MagicData* e;
    q = (int*)sub_80014390(((unsigned char*)p)[2]);
    idx = p[0];
    e = &magicData_8007C438[idx];
    if (e->field_0 & 0x40)
    {
        switch (e->field_7)
        {
        case 0:
            if (((short*)q)[4] != ((short*)q)[5])
            {
                return 0;
            }
            return 3;
        case 1:
            if (idx == 0x10)
            {
                return 0;
            }
            if (!(q[0] & 0x7FB))
            {
                return 3;
            }
            return 0;
        }
    }
    return 0;
}
#endif
INCLUDE_ASM(sub_80034068);
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
INCLUDE_ASM(sub_80034C18);
