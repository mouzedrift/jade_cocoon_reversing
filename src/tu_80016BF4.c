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
extern void PlayMusic_800300E0(int a, int b);
extern int sub_80020F00(void* p, int a, int b);
extern int dword_800795D4;
// Matched
void sub_80016C3C(int* a0, void* buf)
{
    int* a1 = (int*)buf;
    int idx;
    int* t;
    int pos[3];
    int v[3];
    int* vp;
    idx = sub_80020F00(effectFile_80091BD0, 1, 6);
    t = (int*)(effectFile_80091BD0[0x28 / 4] + idx * 28);
    if (--a1[1] > 0)
    {
        if (a1[0xA0 / 4])
        {
            vp = v;
            v[0] = ((int*)a1[0xA0 / 4])[0] * 3 / 2;
            v[1] = ((int*)a1[0xA0 / 4])[1] * 3 / 2;
            v[2] = ((int*)a1[0xA0 / 4])[2] * 3 / 2;
        }
        else
        {
            vp = 0;
        }
        pos[0] = ((int*)a1[0x20 / 4])[a1[0x98 / 4] * 3 + 0] + ((int*)a1[0x1C / 4])[0];
        pos[1] = ((int*)a1[0x20 / 4])[a1[0x98 / 4] * 3 + 1] + ((int*)a1[0x1C / 4])[1];
        pos[2] = ((int*)a1[0x20 / 4])[a1[0x98 / 4] * 3 + 2] + ((int*)a1[0x1C / 4])[2];
        sub_8004D1EC(t[1], (int)pOT_8008D690, (int)pos, (int)&dword_800795D4, (int)stru_8008D534, (a1[1] << 24) | 0xB0, (int)vp);
    }
    else
    {
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
extern void sub_800C1A5C(void* a0, short* a1, int a2, int a3);
void SpawnMdecEffect_80017A6C(int a0, int a1);
// Matched
void sub_80016E20(int* a0, void* buf)
{
    int* a1 = (int*)buf;
    short v[3];
    int i;
    short r;
    short r2;
    int idx;
    r = ratan2Difference_8003B9E0((int*)a1[0x1C / 4], (int*)a1[0x14 / 4]);
    v[0] = 0;
    v[1] = r;
    v[2] = 0;
    if (a1[1] == 1)
    {
        PlayMusic_800300E0(6, 1);
        PlaySfx_80031494(0x18);
        PlaySfx_80031494(0x4A);
        for (i = 0; i < 5; i++)
        {
            v[1] = r + (i << 12) / 5;
            idx = sub_80020F00(effectFile_80091BD0, 0, 0x176);
            sub_800C1A5C(a1 + 0x44 / 4, v, effectFile_80091BD0[0x20 / 4] + idx * 52, 0x1000);
            sub_800C32DC((int)(a1 + 0x44 / 4), 0xB2, 0, v[1]);
        }
    }
    if (a1[1] == 0x5D)
    {
        r2 = ratan2Difference_8003B9E0((int*)a1[0x1C / 4], (int*)a1[0x14 / 4]);
        StopSoundSeqById_800306FC(6);
        PlaySfx_80031494(0x1A);
        SpawnMdecEffect_80017A6C((int)a1, sub_800C32DC((int)(a1 + 0x44 / 4), 0xB3, 0, r2));
        *a0 = (*a0 & ~1) | 0x8000;
    }
    a1[1]++;
}
extern void sub_800C1190(int a0, int a1);
// Matched
void sub_80016FC8(int* a0, int* a1)
{
    short v[3];
    int i;
    int idx;
    idx = ratan2Difference_8003B9E0((int*)a1[0x1C / 4], (int*)a1[0x14 / 4]);
    v[0] = 0;
    v[1] = idx;
    v[2] = 0;
    if (a1[1] == 0)
    {
        sub_800C1190(0x32, 0x1E);
        sub_800C1190(0x50, 0x1D);
        for (i = 0; i < 4; i++)
        {
            idx = sub_80020F00(effectFile_80091BD0, 0, 0x16);
            sub_800C1A5C(a1 + 0x44 / 4, v, effectFile_80091BD0[0x20 / 4] + idx * 52, 0x1000);
            v[1] += 0x400;
            sub_800C32DC(a1[0x1C / 4], 0xF, 0, v[1]);
        }
    }
    if (a1[1] == 0x30)
    {
        idx = sub_80020F00(effectFile_80091BD0, 0, 0x15);
        sub_800C1A5C(a1 + 0x44 / 4, v, effectFile_80091BD0[0x20 / 4] + idx * 52, 0x1000);
    }
    if (a1[1] == 0x33)
    {
        sub_800C32DC(a1[0x1C / 4], 0xE, 0, v[1]);
        *a0 = (*a0 & ~1) | 0x8000;
    }
    a1[1]++;
}
extern EventNode* effectObjects_8008B4A8;
extern void sub_80017208(int* a0, int* a1);
// Matched
void sub_80017158(int* a0, unsigned char* a1)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
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
void sub_800173A8(int* a0, void* buf);
extern int sub_80020F00(void* p, int a, int b);
// Matched
void sub_80017290(char* a0, int a1)
{
    EventEntry* e;
    SpawnMdecEffect_80017A6C((int)a0, 0);
    e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
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
        idx = sub_80020F00((struct_list_14*)effectFile_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        b[0x88 / 4] = effectFile_80091BD0[0x28 / 4] + idx * 28;
        e->cb_8 = (EventEntryFn)sub_800173A8;
    }
}
// Matched
void sub_800173A8(int* a0, void* buf)
{
    int* a1 = (int*)buf;
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
