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

INCLUDE_DATA(off_80072278);

INCLUDE_ASM(sub_800174F8);
INCLUDE_ASM(sub_8001761C);
INCLUDE_ASM(sub_80017784);
INCLUDE_ASM(sub_800178C0);
extern EventNode* dword_8008B4A8;
extern void sub_80017B10(EventEntry* e, void* buf);
// Matched
void sub_80017A6C(int a0, int a1)
{
    EventEntry* e = sub_80043AF8(dword_8008B4A8);
    int* q;
    if (e)
    {
        q = (int*)e->buffer;
        q[0x8C / 4] = (int)dword_80091C00;
        q[0] = 0;
        if (a1 > 0)
        {
            q[1] = a1;
        }
        else
        {
            q[1] = sub_800181E8();
        }
        e->cb_8 = sub_80017B10;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        sub_8004188C();
        DecDCTReset(0);
    }
}
INCLUDE_ASM(sub_80017B10);
extern void sub_80017CE4(EventEntry* e, void* buf);
extern int sub_80020F00(void* p, int a, int b);
// Matched
void sub_80017BF0(EventEntry* a0, int a1)
{
    EventEntry* e = sub_80043AF8(dword_8008B4A8);
    int* q;
    int r;
    if (e)
    {
        q = (int*)e->buffer;
        q[0x44 / 4] = ((int*)a0->buffer)[0];
        q[0x48 / 4] = ((int*)a0->buffer)[1];
        q[0x4C / 4] = ((int*)a0->buffer)[2];
        q[0] = 0;
        q[0x30 / 4] = 0;
        q[0x34 / 4] = 0x23F000;
        ((short*)q)[0x84 / 2] = 0;
        ((short*)q)[0x82 / 2] = 0;
        ((short*)q)[0x80 / 2] = 0;
        r = sub_80020F00(dword_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q[0x88 / 4] = ((int*)dword_80091BD0)[0x28 / 4] + r * 28;
        e->cb_8 = sub_80017CE4;
    }
}
INCLUDE_ASM(sub_80017CE4);
INCLUDE_ASM(sub_80017E30);
INCLUDE_ASM(sub_80017FF8);
// Matched
int sub_800181E8(void)
{
    return *dword_80091C00;
}
// Matched
#if 0
// Not matched: 10 words, register numbering of the loop counters
typedef struct
{
    short x;
    short y;
} struct_pair16;
short* sub_80018200(short* src, int a1, int a2, short a3)
{
    struct_pair16* dst = (struct_pair16*)dword_8008D3F8[0x24 / 4];
    struct_pair16* p = dst;
    struct_pair16* s = (struct_pair16*)src;
    int i;
    int j;
    int d;
    for (i = 0; i < 10; i++)
    {
        p->x = s->x;
        p->y = s->y;
        s++;
        p++;
    }
    d = a2 - a1;
    for (j = 0; j < a3; j++)
    {
        for (i = 0; i < 10; i++)
        {
            if (dst[i].x >= (unsigned short)a2)
            {
                dst[i].x += d;
            }
            if (dst[i].y >= (unsigned short)a2)
            {
                dst[i].y += d;
            }
        }
    }
    return (short*)dst;
}
#endif
INCLUDE_ASM(sub_80018200);
INCLUDE_ASM(sub_800182B8);
