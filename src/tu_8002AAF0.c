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

INCLUDE_DATA(dword_800741C4);

INCLUDE_ASM(sub_8002AAF0);
INCLUDE_ASM(sub_8002AC88);
// Matched
void sub_8002ACE8(int flags, unsigned char* out)
{
    unsigned char val;
    if (flags & 2)
    {
        val = 0x40;
    }
    else
    {
        val = 0x80;
    }
    out[0] = val;
    out[1] = val;
    out[2] = val;
}
// Matched
void sub_8002AD08(int flags)
{
    if (flags & 2)
    {
        sub_8003F900(1, 1);
    }
    else
    {
        sub_8003F900(1, 0);
    }
}
// Matched
void sub_8002AD44(int flags)
{
    if (flags & 2)
    {
        sub_8003F900(2, 1);
    }
    else
    {
        sub_8003F900(2, 0);
    }
}
// Matched
void sub_8002AD80(int flags)
{
    if (flags & 2)
    {
        sub_8002C5D0(3);
    }
    else
    {
        sub_8002C5D0(0);
    }
}
extern void sub_8002A710(void* a, int b);
extern void sub_80042460(void* a, int b, void* c, int d);
// Matched
void sub_8002ADB4(char* a0, int a1, int a2, int a3)
{
    sub_8002A710(a0, a2);
    sub_8003F900(2, 0);
    sub_8003F900(1, 0);
    sub_80042460(a0 + 0x10, a1, &pOT_8008D454[a2], a3);
}
INCLUDE_ASM(sub_8002AE38);
// Matched
void sub_8002AF10(int a0, int a1, int a2)
{
    RECT r;
    r.x = 10;
    r.y = 0x99;
    r.w = 0x12C;
    r.h = 0x3C;
    sub_8002AFA0(a0, a1, a2, &r, 4);
}
// Matched
void sub_8002AF58(int a0, int a1, int a2)
{
    RECT r;
    r.x = 10;
    r.y = 0xC3;
    r.w = 0x12C;
    r.h = 0x12;
    sub_8002AFA0(a0, a1, a2, &r, 1);
}
#if 0
void sub_8002AFA0(int a0, int a1, int a2, RECT* a3, int a4)
{
}
#endif
typedef struct
{
    unsigned short x;
    unsigned short y;
} Pos16;
extern void sub_8002AE38(int a0, Pos16* a1, int a2, RECT* a3, int a4);
// Matched
void sub_8002AFA0(int a0, int a1, int a2, RECT* a3, int a4)
{
    Pos16 p;
    Pos16* src = (Pos16*)a1;
    if (src)
    {
        ((Pos16*)a3)->x = src->x;
        ((Pos16*)a3)->y = src->y;
    }
    p.x = ((Pos16*)a3)->x + 4;
    p.y = ((Pos16*)a3)->y + 5;
    sub_8002AE38(a0, &p, a2, a3, a4);
}
INCLUDE_ASM(sub_8002B004);
typedef struct
{
    short s[8];
} Block16;
extern Block16 dword_800741C4;
extern void sub_8002B2A4(short a, int b, int c, Block16* d, int e);
// Matched
void sub_8002B1B0(short a, int b, int c)
{
    Block16 local = dword_800741C4;
    sub_8002B2A4(a, b, c, &local, 0);
}
