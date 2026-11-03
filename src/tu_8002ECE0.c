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

INCLUDE_DATA(dword_800743D4);
INCLUDE_DATA(dword_800743D8);
INCLUDE_DATA(off_800743DC);
INCLUDE_DATA(off_800743E0);
INCLUDE_DATA(dword_800743E4);
INCLUDE_DATA(dword_800743E8);
INCLUDE_DATA(dword_800743EC);
INCLUDE_DATA(dword_800743F0);
INCLUDE_DATA(dword_800743F4);
INCLUDE_DATA(off_800743F8);
INCLUDE_DATA(off_800743FC);
INCLUDE_DATA(dword_80074400);
INCLUDE_DATA(dword_80074404);
INCLUDE_DATA(dword_80074408);
INCLUDE_DATA(dword_8007440C);
INCLUDE_DATA(dword_80074410);
INCLUDE_DATA(off_80074414);
INCLUDE_DATA(off_80074418);
INCLUDE_DATA(dword_8007441C);
INCLUDE_DATA(dword_80074420);
INCLUDE_DATA(dword_80074424);
INCLUDE_DATA(dword_80074428);

extern void sub_8002F23C(int a0, int a1, int a2, unsigned short* a3, int a4, int a5);
extern void sub_8002BA54(void* a, int b, void* c, int d);
void sub_8002F120(char* a0, unsigned short* pos, int a2, short a3);
extern void sub_8002C06C(void* p, int a1, int a2);
// Matched
void sub_8002ECE0(char* a0, unsigned short* pos, int a2, short ot)
{
    unsigned short loc[2];
    unsigned int st[4];
    RECT r;
    unsigned int x;
    r.x = pos[0];
    r.y = pos[1];
    r.w = 0;
    r.h = 0;
    sub_8002F23C((int)a0, 0, frameCount_8008D3FC, (unsigned short*)&r, (short)ot, 0);
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 0x37;
    sub_8002C06C(loc, 0x3B, ot);
    st[0] = 2;
    st[1] = 0;
    x = ((unsigned int*)a0)[1];
    while (x > 0x4000000)
    {
        x -= 0x4000000;
    }
    st[2] = x;
    st[3] = 0x4000000;
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 0x42;
    sub_8002BA54(st, 0, loc, (short)ot);
    loc[0] = pos[0];
    loc[1] = pos[1] + 0x24;
    sub_8002F120(a0, loc, 0, ot);
}
extern void sub_8002C06C(void* p, int a1, int a2);
extern void sub_8002C290(unsigned short* pos, int val, int ot);
void sub_8002EF5C(unsigned short* pos, short count, short a2);
// Matched
void sub_8002EE28(short* a, unsigned short* pos, short c, int d)
{
    unsigned short loc[2];
    if (d)
    {
        loc[0] = pos[0] + 0x15;
        loc[1] = pos[1];
        sub_8002C290(loc, a[0], c);
    }
    else
    {
        unsigned short x = pos[0];
        unsigned short y;
        loc[0] = x - 5;
        y = pos[1];
        loc[0] = x;
        loc[1] = y;
        sub_8002EF5C(loc, 3, c);
    }
    loc[0] = pos[0] + 0x15;
    loc[1] = pos[1];
    sub_8002C06C(loc, 0xDA, c);
    if (d)
    {
        unsigned short x = pos[0];
        unsigned short y;
        loc[0] = x + 0x2B;
        y = pos[1];
        loc[0] = x + 0x30;
        loc[1] = y;
        sub_8002C290(loc, a[1], c);
    }
    else
    {
        unsigned short x = pos[0];
        unsigned short y;
        loc[0] = x + 0x1E;
        y = pos[1];
        loc[0] = x + 0x1B;
        loc[1] = y;
        sub_8002EF5C(loc, 3, c);
    }
}
extern void sub_8002C06C(void* p, int a1, int a2);
// Matched
void sub_8002EF5C(unsigned short* pos, short count, short a2)
{
    unsigned short loc[2];
    loc[0] = pos[0];
    loc[1] = pos[1];
    do
    {
        sub_8002C06C(loc, 0xd9, a2);
        count--;
        loc[0] += 7;
    } while (count > 0);
}
extern void sub_8002BA54(void* a, int b, void* c, int d);
extern void sub_8002EE28(short* a, unsigned short* pos, short c, int d);
extern void sub_8002EFC4(char* a0, int a1, int a2, void* a3_, int a4, int a5);
// Matched
void sub_8002EFC4(char* a0, int a1, int a2, void* a3_, int a4, int a5)
{
    unsigned short pos[2];
    int local[4];
    unsigned short* a3 = (unsigned short*)a3_;
    local[0] = 1;
    local[1] = a1;
    local[2] = ((short*)a0)[0];
    local[3] = ((short*)a0)[1];
    pos[0] = a3[0];
    pos[1] = a3[1];
    sub_8002BA54(local, a2, pos, a4);
    pos[0] = a3[0] + 8;
    pos[1] = a3[1] + 7;
    sub_8002EE28(a0, pos, (short)a4, a5);
}
// Matched
void sub_8002F078(char* a0, unsigned short* pos, int a2, short a3)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 4;
    sub_8002C06C(loc, 0x76, a3);
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 3;
    sub_8002EFC4(a0 + 8, a2, 0, loc, a3, 1);
}
// Matched
void sub_8002F120(char* a0, unsigned short* pos, int a2, short a3)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 4;
    sub_8002C06C(loc, 0x71, a3);
    loc[0] = pos[0] + 0x20;
    loc[1] = pos[1] + 3;
    sub_8002EFC4(a0 + 0xC, a2, 0, loc, a3, 1);
}
typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_F1C8;
extern void sub_8002F23C(int a0, int a1, int a2, unsigned short* a3, int a4, int a5);
extern void sub_8002A384(struct_F1C8* p);
// Matched
void sub_8002F1C8(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    struct_F1C8 s;
    sub_8002F23C(a0, a1, a3, (unsigned short*)a4, a5, a6);
    s.field_8 = a2;
    s.field_0 = a4;
    s.field_4 = a3;
    s.field_A = a5;
    sub_8002A384(&s);
}

extern void sub_8002FAA0(int a0, unsigned short* pos, unsigned char* name, int a3);
extern void sub_8002B228(short a, unsigned short* pos, int ot, int flags);
// Matched
void sub_8002F23C(int a0, int a1, int a2, unsigned short* pos, int a4, int a5)
{
    unsigned short loc[2];
    loc[0] = pos[0] + 7;
    loc[1] = pos[1] + 3;
    sub_8002FAA0(0, loc, (unsigned char*)a0 + 0x10, a4);
    loc[0] = pos[0] + 3;
    loc[1] = pos[1] + 0xB;
    sub_8002EFC4((char*)a0 + 8, a1, a2, loc, a4, (a5 ^ 1) & 1);
    loc[0] = pos[0] + 0x45;
    loc[1] = pos[1] + 4;
    sub_8002B228(sub_8003412C((char*)a0), loc, a4, a5);
    if (a5 & 2)
    {
        loc[0] = pos[0] + 4;
        loc[1] = pos[1] + 0x1C;
        sub_8002C06C(loc, 0xE1, a4);
        loc[0] = pos[0] + 0x1B;
        loc[1] = pos[1] + 0x1B;
        sub_8002C06C(loc, 0x78, a4);
        loc[0] = pos[0] + 0x35;
    }
    else
    {
        loc[0] = pos[0] + 0x10;
        loc[1] = pos[1] + 0x1B;
        sub_8002C06C(loc, 0x78, a4);
        loc[0] = pos[0] + 0x2A;
    }
    loc[1] = pos[1] + 0x1D;
    if (!(a5 & 1))
    {
        loc[0] += 0xD;
        sub_8002C290(loc, ((unsigned char*)a0)[0x44], a4);
    }
    else
    {
        sub_8002EF5C(loc, 2, a4);
    }
}
// Matched
short sub_8002F424(unsigned char* p)
{
    short mask = 0;
    short i;
    if (p)
    {
        for (i = 0; i < 4; i++)
        {
            if (p[i])
            {
                mask |= 1 << i;
            }
        }
    }
    return mask;
}
INCLUDE_ASM(sub_8002F480);
