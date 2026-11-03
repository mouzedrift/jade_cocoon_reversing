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
#if 0
// Not matched (2 words: first branch emits subu/subu; written as a[0] + (a[2] - b) gcc cross-jumps it into the second branch)
void sub_8002AC88(int flags, short* a, int b, short* out)
{
    if (flags & 4)
    {
        out[0] = a[0] - (b - a[2]);
    }
    else if (flags & 8)
    {
        out[0] = a[0] + ((unsigned int)(a[2] - b) >> 1);
    }
    else
    {
        out[0] = a[0];
    }
    out[1] = a[1];
}
#endif
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
typedef struct
{
    unsigned short x;
    unsigned short y;
} Pos16;
typedef struct
{
    unsigned short color;
    unsigned char b;
    unsigned char c;
} struct_text_param;
extern short uiColor_8008B590;
extern void DrawText_8003E91C(int mode, int a, void* b, int c);
// Matched
void sub_8002AE38(int a0, Pos16* a1, int a2, RECT* a3, int a4)
{
    int* lines = (int*)a0;
    Pos16 p;
    struct_text_param t;
    unsigned int i;
    p.x = a1->x;
    p.y = a1->y;
    for (i = 0; i < a4; i++)
    {
        if (lines[i])
        {
            DrawText_8003E91C(2, lines[i], &p, a2);
        }
        p.y += 12;
    }
    if (a3)
    {
        t.c = 1;
        t.b = 0;
        t.color = uiColor_8008B590;
        sub_80042460(a3, (int)&t, &pOT_8008D454[a2], 0);
    }
}
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
