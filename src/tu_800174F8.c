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

void sub_8001761C(int* a0, int* a1);
// Matched
void sub_800174F8(char* a0, int a1)
{
    EventEntry* e = sub_80043AF8(dword_8008B4A8);
    if (e)
    {
        int* b = e->buffer;
        int* p;
        int idx;
        b[0x44 / 4] = (*(int**)(a0 + 0x1C))[0];
        b[0x48 / 4] = (*(int**)(a0 + 0x1C))[1];
        b[0x4C / 4] = (*(int**)(a0 + 0x1C))[2];
        b[0] = 0;
        b[0x30 / 4] = 0;
        b[0x34 / 4] = 0x23F000;
        ((short*)b)[0x84 / 2] = 0;
        ((short*)b)[0x82 / 2] = 0;
        ((short*)b)[0x80 / 2] = 0;
        ((short*)b)[0x86 / 2] = 0;
        idx = sub_80020F00((struct_list_14*)dword_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        p = (int*)(dword_80091BD0[0x28 / 4] + idx * 28);
        b[0x88 / 4] = (int)p;
        b[0x94 / 4] = (int)malloc3_8003FC4C(0x54);
        sub_800218A8(p[1], (void*)b[0x94 / 4], 1);
        sub_80039FE4(p[1], p[1] + 0x54, b[0x94 / 4]);
        e->cb_8 = (EventEntryFn)sub_8001761C;
    }
}
INCLUDE_ASM(sub_8001761C);
void sub_800178C0(int* a0, int* a1);
// Matched
void sub_80017784(char* a0, int a1, short* a2)
{
    EventEntry* e = sub_80043AF8(dword_8008B4A8);
    if (e)
    {
        int* b = e->buffer;
        int* p;
        int idx;
        b[0x44 / 4] = (*(int**)(a0 + 0x1C))[0];
        b[0x48 / 4] = (*(int**)(a0 + 0x1C))[1];
        b[0x4C / 4] = (*(int**)(a0 + 0x1C))[2];
        b[0] = 0;
        ((short*)b)[8 / 2] = 0;
        b[0x30 / 4] = 0;
        b[0x34 / 4] = 0x23F000;
        ((short*)b)[0x80 / 2] = a2[0];
        ((short*)b)[0x82 / 2] = a2[1];
        ((short*)b)[0x84 / 2] = a2[2];
        idx = sub_80020F00((struct_list_14*)dword_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        p = (int*)(dword_80091BD0[0x28 / 4] + idx * 28);
        b[0x88 / 4] = (int)p;
        b[0x94 / 4] = (int)malloc3_8003FC4C(0x54);
        sub_800218A8(p[1], (void*)b[0x94 / 4], 1);
        sub_80039FE4(p[1], p[1] + 0x54, b[0x94 / 4]);
        e->cb_8 = (EventEntryFn)sub_800178C0;
    }
}
// Matched
void sub_800178C0(int* a0, int* a1)
{
    int* t = (int*)a1[0x88 / 4];
    int v[3];
    a1[0x34 / 4] = a1[0x34 / 4] * 7 / 8;
    a1[0x30 / 4] += a1[0x34 / 4];
    v[0] = v[1] = v[2] = a1[0x30 / 4] / 4096;
    if (((short*)a1)[8 / 2] < 3)
    {
        sub_8003A6C4(0x1000 - (a1[0] << 10), t[1], (int)&((struct_54*)t[1])[((short*)a1)[8 / 2] + 1], a1[0x94 / 4]);
        if (++a1[0] >= 5)
        {
            ((short*)a1)[8 / 2]++;
            a1[0] = 0;
            if (((short*)a1)[8 / 2] < 3)
            {
                sub_80039FE4((int)&((struct_54*)t[1])[((short*)a1)[8 / 2]], (int)&((struct_54*)t[1])[((short*)a1)[8 / 2] + 1], a1[0x94 / 4]);
            }
        }
    }
    else
    {
        if (++a1[0] >= 0x35)
        {
            a1[0] = 0;
            *a0 = (*a0 & ~1) | 0x8000;
            sub_80021804(a1[0x94 / 4], 1);
            free3_8003FC6C((void*)a1[0x94 / 4]);
        }
    }
    sub_8004D1EC(t[1], (int)pOT_8008D690, (int)(a1 + 0x44 / 4), (int)(a1 + 0x80 / 4), (int)stru_8008D534, 0x10, (int)v);
}
extern EventNode* dword_8008B4A8;
extern void sub_80017B10(unsigned int* a0, int* a1);
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
        e->cb_8 = (EventEntryFn)sub_80017B10;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        sub_8004188C();
        DecDCTReset(0);
    }
}
// Matched
void sub_80017B10(unsigned int* a0, int* a1)
{
    int* t = (int*)a1[0x8C / 4];
    if (++a1[0] < a1[1] && word_8008D780 == 0)
    {
        if (!(unknownFlags_8008D678 & 0x800))
        {
            DecodeMdec_80041920(((unsigned long**)t[1])[a1[0] % t[0]], dword_8008D42C, 2);
            unknownFlags_8008D678 |= 0x800;
        }
    }
    else
    {
        sub_800418FC();
        unknownFlags_8008D678 &= ~0x800;
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
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
