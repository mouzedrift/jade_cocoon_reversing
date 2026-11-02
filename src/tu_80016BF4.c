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

INCLUDE_DATA(dword_80072270);

// Matched
void sub_80016BF4(int* p, int* q)
{
    if (--q[1] < 0)
    {
        *p = (*p & ~1) | 0x8000;
        PlaySfx_80031494(0x24);
    }
}
INCLUDE_ASM(sub_80016C3C);
INCLUDE_ASM(sub_80016E20);
INCLUDE_ASM(sub_80016FC8);
extern EventNode* dword_8008B4A8;
extern void sub_80017208(int* a0, int* a1);
// Matched
void sub_80017158(int* a0, unsigned char* a1)
{
    EventEntry* e = sub_80043AF8(dword_8008B4A8);
    int* q;
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = (int*)e->buffer;
        q[0x44 / 4] = a0[0];
        q[0x48 / 4] = a0[1];
        q[0x4C / 4] = a0[2];
        q[0] = 0;
        ((unsigned char*)q)[0xA8] = a1[0];
        ((unsigned char*)q)[0xA9] = a1[1];
        ((unsigned char*)q)[0xAA] = a1[2];
        e->cb_8 = (EventEntryFn)sub_80017208;
    }
}
// Matched
void sub_80017208(int* a0, int* a1)
{
    if (a1[0] < 0x20)
    {
        sub_800C4090((int)(a1 + 0x44 / 4), (int)(a1 + 0xA8 / 4), 0x5DC, (0x20 - a1[0]) << 7);
        a1[0] = a1[0] + 1;
    }
    else
    {
        sub_800C410C();
        a0[0] = (a0[0] & ~1) | 0x8000;
    }
}
void sub_80017A6C(int a0, int a1);
void sub_800173A8(int* a0, int* a1);
extern int sub_80020F00(void* p, int a, int b);
// Matched
void sub_80017290(char* a0, int a1)
{
    EventEntry* e;
    sub_80017A6C((int)a0, 0);
    e = sub_80043AF8(dword_8008B4A8);
    if (e)
    {
        int* b = e->buffer;
        int idx;
        b[0x44 / 4] = (*(int**)(a0 + 0x1C))[0];
        b[0x48 / 4] = (*(int**)(a0 + 0x1C))[1];
        b[0x4C / 4] = (*(int**)(a0 + 0x1C))[2];
        b[0] = 0;
        b[1] = sub_800181E8();
        b[0x30 / 4] = 0;
        b[0x34 / 4] = 0x23F000;
        ((short*)b)[0x84 / 2] = 0;
        ((short*)b)[0x82 / 2] = 0;
        ((short*)b)[0x80 / 2] = 0;
        ((short*)b)[0x86 / 2] = 0;
        idx = sub_80020F00((struct_list_14*)dword_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        b[0x88 / 4] = dword_80091BD0[0x28 / 4] + idx * 28;
        e->cb_8 = (EventEntryFn)sub_800173A8;
    }
}
#if 0
// Not matched: only the scheduling of the a0/a1 copies into $s0/$s1 differs
void sub_800173A8(int* a0, int* a1)
{
    int* t = (int*)a1[0x88 / 4];
    struct_u8x4 col;
    int v[3];
    if (a1[0] < a1[1])
    {
        col = dword_80072270;
        a1[0x34 / 4] = a1[0x34 / 4] * 7 / 8;
        a1[0x30 / 4] += a1[0x34 / 4];
        v[0] = v[1] = v[2] = a1[0x30 / 4] / 4096;
        ((short*)a1)[0x82 / 2] += ((short*)a1)[0x86 / 2];
        sub_8004D1EC(t[1], (int)pOT_8008D690, (int)(a1 + 0x44 / 4), (int)(a1 + 0x80 / 4), (int)stru_8008D534, 0x30, (int)v);
        sub_800C4090((int)(a1 + 0x44 / 4), (int)&col, 0x5DC, ((a1[1] - a1[0]) << 12) / a1[1]);
        a1[0]++;
    }
    else
    {
        sub_800C410C();
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
#endif
INCLUDE_ASM(sub_800173A8);
