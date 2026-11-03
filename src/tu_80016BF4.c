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
#include "effect_obj.h"

INCLUDE_DATA(dword_80072270);

// Matched
void sub_80016BF4(int* p, int* q)
{
    if (--((EffectObj*)q)->field_4 < 0)
    {
        *p = (*p & ~1) | 0x8000;
        PlaySfx_80031494(0x24);
    }
}
extern void PlayMusic_800300E0(int a, int b);
extern int dword_800795D4;
// Matched
void sub_80016C3C(int* a0, void* buf)
{
    EffectObj* a1 = buf;
    int idx;
    EffectModel* t;
    int pos[3];
    int v[3];
    int* vp;
    idx = sub_80020F00(&effectFile_80091BD0, 1, 6);
    t = &effectFile_80091BD0.models_28[idx];
    if (--a1->field_4 > 0)
    {
        if (a1->field_A0)
        {
            vp = v;
            v[0] = ((int*)a1->field_A0)[0] * 3 / 2;
            v[1] = ((int*)a1->field_A0)[1] * 3 / 2;
            v[2] = ((int*)a1->field_A0)[2] * 3 / 2;
        }
        else
        {
            vp = 0;
        }
        pos[0] = ((int*)a1->field_20)[a1->field_98 * 3 + 0] + ((int*)a1->field_1C)[0];
        pos[1] = ((int*)a1->field_20)[a1->field_98 * 3 + 1] + ((int*)a1->field_1C)[1];
        pos[2] = ((int*)a1->field_20)[a1->field_98 * 3 + 2] + ((int*)a1->field_1C)[2];
        sub_8004D1EC(t->ftg_4, pOT_8008D690, pos, &dword_800795D4, stru_8008D534, (a1->field_4 << 24) | 0xB0, vp);
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
    EffectObj* a1 = buf;
    short v[3];
    int i;
    short r;
    short r2;
    int idx;
    r = ratan2Difference_8003B9E0((int*)a1->field_1C, (int*)a1->field_14);
    v[0] = 0;
    v[1] = r;
    v[2] = 0;
    if (a1->field_4 == 1)
    {
        PlayMusic_800300E0(6, 1);
        PlaySfx_80031494(0x18);
        PlaySfx_80031494(0x4A);
        for (i = 0; i < 5; i++)
        {
            v[1] = r + (i << 12) / 5;
            idx = sub_80020F00(&effectFile_80091BD0, 0, 0x176);
            sub_800C1A5C(a1->pos_44, v, (int)&effectFile_80091BD0.sprites_20[idx], 0x1000);
            sub_800C32DC((int)a1->pos_44, 0xB2, 0, v[1]);
        }
    }
    if (a1->field_4 == 0x5D)
    {
        r2 = ratan2Difference_8003B9E0((int*)a1->field_1C, (int*)a1->field_14);
        StopSoundSeqById_800306FC(6);
        PlaySfx_80031494(0x1A);
        SpawnMdecEffect_80017A6C((int)a1, sub_800C32DC((int)a1->pos_44, 0xB3, 0, r2));
        *a0 = (*a0 & ~1) | 0x8000;
    }
    a1->field_4++;
}
extern void sub_800C1190(int a0, int a1);
// Matched
void sub_80016FC8(int* a0, EffectObj* a1)
{
    short v[3];
    int i;
    int idx;
    idx = ratan2Difference_8003B9E0((int*)a1->field_1C, (int*)a1->field_14);
    v[0] = 0;
    v[1] = idx;
    v[2] = 0;
    if (a1->field_4 == 0)
    {
        sub_800C1190(0x32, 0x1E);
        sub_800C1190(0x50, 0x1D);
        for (i = 0; i < 4; i++)
        {
            idx = sub_80020F00(&effectFile_80091BD0, 0, 0x16);
            sub_800C1A5C(a1->pos_44, v, (int)&effectFile_80091BD0.sprites_20[idx], 0x1000);
            v[1] += 0x400;
            sub_800C32DC(a1->field_1C, 0xF, 0, v[1]);
        }
    }
    if (a1->field_4 == 0x30)
    {
        idx = sub_80020F00(&effectFile_80091BD0, 0, 0x15);
        sub_800C1A5C(a1->pos_44, v, (int)&effectFile_80091BD0.sprites_20[idx], 0x1000);
    }
    if (a1->field_4 == 0x33)
    {
        sub_800C32DC(a1->field_1C, 0xE, 0, v[1]);
        *a0 = (*a0 & ~1) | 0x8000;
    }
    a1->field_4++;
}
extern EventNode* effectObjects_8008B4A8;
extern void sub_80017208(int* a0, EffectObj* a1);
// Matched
void sub_80017158(int* a0, unsigned char* a1)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    EffectObj* q;
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q->pos_44[0] = a0[0];
        q->pos_44[1] = a0[1];
        q->pos_44[2] = a0[2];
        q->field_0 = 0;
        q->rgb_A8[0] = a1[0];
        q->rgb_A8[1] = a1[1];
        q->rgb_A8[2] = a1[2];
        e->cb_8 = (EventEntryFn)sub_80017208;
    }
}
// Matched
void sub_80017208(int* a0, EffectObj* a1)
{
    if (a1->field_0 < 0x20)
    {
        sub_800C4090((int)a1->pos_44, (int)a1->rgb_A8, 0x5DC, (0x20 - a1->field_0) << 7);
        a1->field_0 = a1->field_0 + 1;
    }
    else
    {
        sub_800C410C();
        a0[0] = (a0[0] & ~1) | 0x8000;
    }
}
void sub_800173A8(int* a0, void* buf);
// Matched
void sub_80017290(EffectObj* a0, int a1)
{
    EventEntry* e;
    SpawnMdecEffect_80017A6C((int)a0, 0);
    e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    if (e)
    {
        EffectObj* b = e->buffer;
        int idx;
        b->pos_44[0] = ((int*)a0->field_1C)[0];
        b->pos_44[1] = ((int*)a0->field_1C)[1];
        b->pos_44[2] = ((int*)a0->field_1C)[2];
        b->field_0 = 0;
        b->field_4 = sub_800181E8();
        b->field_30 = 0;
        b->field_34 = 0x23F000;
        b->rot_80.vz = 0;
        b->rot_80.vy = 0;
        b->rot_80.vx = 0;
        b->rot_80.pad = 0;
        idx = sub_80020F00(&effectFile_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        b->field_88 = (int)&effectFile_80091BD0.models_28[idx];
        e->cb_8 = (EventEntryFn)sub_800173A8;
    }
}
// Matched
void sub_800173A8(int* a0, void* buf)
{
    EffectObj* a1 = buf;
    EffectModel* t = (EffectModel*)a1->field_88;
    struct_u8x4 col;
    int v[3];
    if (a1->field_0 < a1->field_4)
    {
        col = dword_80072270;
        a1->field_34 = a1->field_34 * 7 / 8;
        a1->field_30 += a1->field_34;
        v[0] = v[1] = v[2] = a1->field_30 / 4096;
        a1->rot_80.vy += a1->rot_80.pad;
        sub_8004D1EC(t->ftg_4, pOT_8008D690, a1->pos_44, &a1->rot_80, stru_8008D534, 0x30, v);
        sub_800C4090((int)a1->pos_44, (int)&col, 0x5DC, ((a1->field_4 - a1->field_0) << 12) / a1->field_4);
        a1->field_0++;
    }
    else
    {
        sub_800C410C();
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
