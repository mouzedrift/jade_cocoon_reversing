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



// Matched
void sub_80018430(short v)
{
    unsigned char* base = (unsigned char*)dword_8008D3F8[0x24 / 4];
    *(short*)(base + 0x40) = v;
}
// Matched
void sub_80018448(short v)
{
    unsigned char* base = (unsigned char*)dword_8008D3F8[0x24 / 4];
    *(short*)(base + 0x42) = v;
}
// Matched
void sub_80018460(int on)
{
    unsigned char* base = (unsigned char*)dword_8008D3F8[0x24 / 4];
    if (on)
    {
        *(unsigned int*)(base + 0x28) |= 8;
    }
    else
    {
        *(unsigned int*)(base + 0x28) &= ~8;
    }
}
// Matched
void sub_800184A0(int arg, int bit)
{
    unsigned char* base = (unsigned char*)dword_8008D3F8[0x24 / 4];
    if (bit == 0)
    {
        (base + arg)[0x44] = 0;
    }
    else
    {
        (base + arg)[0x44] |= 1 << bit;
    }
}
// Matched
int sub_800184DC(int a0, int a1)
{
    int* p = dword_8008D3F8[9];
    sub_8001852C(a0, *((unsigned char*)p + a1 + 0x44));
    p[0x28 / 4] |= 1;
    return 1;
}
INCLUDE_ASM(sub_8001852C);
#if 0
// Not matched: registers of i and the row pointer are swapped
int sub_80018908(int id, short (*tbl)[6])
{
    int i;
    int r = -1;
    if (tbl != 0 && tbl[0][0] != -1)
    {
        for (i = 0; tbl[i][0] != -1; i++)
        {
            if (id == tbl[i][0])
            {
                if (tbl[i][2] == -1 && tbl[i][3] == -1 && tbl[i][4] == -1 && tbl[i][5] == -1)
                {
                    int link = tbl[i][1];
                    short* p = tbl[0];
                    for (i = 0; *p != -1; i++)
                    {
                        if (link == *p)
                        {
                            r = i;
                            break;
                        }
                        p += 6;
                    }
                }
                else
                {
                    r = i;
                }
                break;
            }
        }
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80018908);
// Matched
int sub_800189F8(void)
{
    SaveData* sd = &saveData_8008B570;
    struct_24* p = sub_8001CF84(*((unsigned char*)sd + 0x7E4));
    sub_800BFAF8(*((unsigned char*)sd + 0x7E4));
    return dword_80079708[((short*)p)[1]];
}
typedef struct
{
    short a;
    short b;
} ShortPair;
typedef struct
{
    int f0;
    int f4;
    int f8;
    short fC;
    short fE;
    int f10;
    int f14;
    int f18;
    int f1C;
    short f20;
    short f22;
    short f24[4];
    int f2C;
    int f30;
    int pad[11];
} ActionDesc;
extern int sub_80018C00(ActionDesc* d, int* p, int* a2);
// Matched
ShortPair sub_80018A4C(char* obj, int* p, int* a2, int c)
{
    ShortPair r;
    ActionDesc d;
    char* q;
    memset(&r, 0, 4);
    if (p[0] == 0x16)
    {
        q = *(char**)(obj + 0x148) + 0x65C;
        if (*(short*)(q + 0x24) < 0)
        {
            *(short*)(q + 0x24) = *(short*)(*(char**)(obj + 0x148) + 0x656);
            *(short*)(q + 0x26) = *(short*)(q + 0x24) + 30;
        }
        if (*(short*)(q + 0x26) - *(short*)(q + 0x24) < 30)
        {
            *(short*)(q + 0x24) = *(short*)(*(char**)(obj + 0x148) + 0x656);
            *(short*)(q + 0x26) = *(short*)(q + 0x24) + 30;
        }
    }
    d.fE = -1;
    d.f10 = -1;
    d.f24[0] = -1;
    d.f24[1] = -1;
    d.f24[2] = -1;
    d.f24[3] = -1;
    d.f0 = 0;
    d.f4 = 0;
    d.f8 = 0;
    d.fC = 0;
    d.f18 = 0;
    d.f20 = 0;
    d.f22 = 0;
    d.f1C = 1;
    d.f2C = 0;
    d.f30 = 0;
    d.f1C = (c == 0);
    d.f14 = p[2];
    if (sub_80018C00(&d, p, a2))
    {
        d.f1C = 1;
    }
    r.a = ((int (*)(char*, ActionDesc*))sub_8001E254)(obj, &d);
    r.b = sub_8001F03C((int)obj, *(int*)(obj + 0xD0), -1, 0x10);
    if (p[0] != 0x12 && c)
    {
        r.a = 0;
    }
    return r;
}
extern int off_8007A024[];
extern int dword_800B129C[];
extern int sub_8001AC8C(int idx);
extern int sub_80031870(int a0);
extern int sub_800316EC(int a0, int a1);
// Matched
int sub_80018C00(ActionDesc* d, int* p, int* t)
{
    int r;
    if (t == 0)
    {
        t = off_8007A024;
    }
    switch (p[0])
    {
    case 0:
        d->f4 = t[0x8 / 4];
        d->fE = 5;
        d->f10 = 0x13;
        d->f18 = p[3];
        break;
    case 1:
        d->f4 = t[0x24 / 4];
        d->fC = p[1];
        d->fE = 0xC;
        d->f10 = sub_8001AC8C(p[1]);
        d->f18 = p[3];
        break;
    case 2:
        d->fE = 4;
        d->f10 = 0x3A;
        d->f4 = t[0x44 / 4];
        d->f18 = p[2];
        break;
    case 3:
        d->fE = 4;
        d->f10 = 0x39;
        d->f4 = t[0x48 / 4];
        d->f18 = p[2];
        break;
    case 6:
        r = sub_80031870(p[1]);
        d->f4 = t[0xC / 4 + r];
        d->fC = r;
        d->fE = r + 6;
        d->f10 = sub_800316EC(p[1], p[2]);
        d->f18 = p[3];
        break;
    case 7:
        d->f4 = t[0x34 / 4];
        d->fE = 4;
        break;
    case 9:
        d->f4 = t[0x28 / 4];
        d->fE = 0xD;
        break;
    case 10:
        d->f4 = t[0x2C / 4];
        d->fE = 0xE;
        break;
    case 11:
        d->f4 = t[0x40 / 4];
        d->fE = 0x15;
        break;
    case 12:
        d->f4 = t[0x30 / 4];
        d->fE = 0x14;
        break;
    case 13:
        d->f4 = t[0x50 / 4];
        break;
    case 14:
        d->f4 = t[0x4C / 4];
        break;
    case 15:
        d->f4 = t[0x58 / 4];
        d->fE = 0x18;
        break;
    case 16:
        d->f4 = t[0x54 / 4];
        d->fE = 0x17;
        break;
    case 18:
        d->f4 = t[0x38 / 4];
        d->fE = 0x12;
        break;
    case 17:
        d->f4 = t[0x3C / 4];
        d->fE = 0x13;
        break;
    case 19:
        d->f4 = t[0x5C / 4];
        d->fE = 0x19;
        break;
    case 21:
        d->fE = 0x1A;
        d->f10 = dword_800B129C[0] ? 0x3A : 0x39;
        d->f4 = t[0x44 / 4];
        d->f18 = p[2];
        break;
    case 22:
        d->fE = 0x1B;
        d->f10 = dword_800B129C[0] ? 0x39 : 0x3A;
        d->f4 = t[0x48 / 4];
        d->f18 = p[2];
        break;
    case 5:
    case 26:
        d->f4 = t[0x70 / 4 + p[1]];
        break;
    case 27:
        break;
    }
    return 0;
}
