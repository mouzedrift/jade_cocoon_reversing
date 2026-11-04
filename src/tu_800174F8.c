#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "tu_80036528.h"
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
#include "tu_800174F8.h"

const int off_80072278[0] = {  };

void sub_8001761C(int* a0, EffectObj* a1);
// Matched
void sub_800174F8(EffectObj* a0, int a1)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    if (e)
    {
        EffectObj* b = e->buffer;
        EffectModel* p;
        int idx;
        b->pos_44[0] = a0->field_1C[0];
        b->pos_44[1] = a0->field_1C[1];
        b->pos_44[2] = a0->field_1C[2];
        b->field_0 = 0;
        b->field_30 = 0;
        b->field_34 = 0x23F000;
        b->rot_80.vz = 0;
        b->rot_80.vy = 0;
        b->rot_80.vx = 0;
        b->rot_80.pad = 0;
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        p = &effectFile_80091BD0.models_28[idx];
        b->field_88 = (int)p;
        b->work_94 = malloc3_8003FC4C(0x54);
        CopyFtgObject_800218A8(p->ftg_4, b->work_94, 1);
        sub_80039FE4(p->ftg_4, p->ftg_4 + 1, b->work_94);
        e->cb_8 = (EventEntryFn)sub_8001761C;
    }
}
// Matched
void sub_8001761C(int* a0, EffectObj* a1)
{
    EffectModel* t = (EffectModel*)a1->field_88;
    int v[3];
    int f;
    a1->field_34 = a1->field_34 * 7 / 8;
    a1->field_30 += a1->field_34;
    v[0] = v[1] = v[2] = a1->field_30 / 4096;
    a1->rot_80.vy += 0x80;
    f = (a1->field_0 < 45) ? 0 : (((a1->field_0 - 44) << 24) | 0x80);
    LerpFtgObject_8003A6C4(word_80084540[(a1->field_0 * 512) & 0xE00] / 2 + 0x800, t->ftg_4, t->ftg_4 + 1, a1->work_94);
    sub_8004D1EC(t->ftg_4, pOT_8008D690, a1->pos_44, &a1->rot_80, stru_8008D534, f | 0x31, v);
    if (a1->field_0++ > 60)
    {
        *a0 = (*a0 & ~1) | 0x8000;
        FreeFtgObjectData_80021804(a1->work_94, 1);
        free3_8003FC6C(a1->work_94);
    }
}
void sub_800178C0(int* a0, EffectObj* a1);
// Matched
void sub_80017784(EffectObj* a0, int a1, short* a2)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    if (e)
    {
        EffectObj* b = e->buffer;
        EffectModel* p;
        int idx;
        b->pos_44[0] = a0->field_1C[0];
        b->pos_44[1] = a0->field_1C[1];
        b->pos_44[2] = a0->field_1C[2];
        b->field_0 = 0;
        b->field_8 = 0;
        b->field_30 = 0;
        b->field_34 = 0x23F000;
        b->rot_80.vx = a2[0];
        b->rot_80.vy = a2[1];
        b->rot_80.vz = a2[2];
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & ~0x8000;
        p = &effectFile_80091BD0.models_28[idx];
        b->field_88 = (int)p;
        b->work_94 = malloc3_8003FC4C(0x54);
        CopyFtgObject_800218A8(p->ftg_4, b->work_94, 1);
        sub_80039FE4(p->ftg_4, p->ftg_4 + 1, b->work_94);
        e->cb_8 = (EventEntryFn)sub_800178C0;
    }
}
// Matched
void sub_800178C0(int* a0, EffectObj* a1)
{
    EffectModel* t = (EffectModel*)a1->field_88;
    int v[3];
    a1->field_34 = a1->field_34 * 7 / 8;
    a1->field_30 += a1->field_34;
    v[0] = v[1] = v[2] = a1->field_30 / 4096;
    if (a1->field_8 < 3)
    {
        LerpFtgObject_8003A6C4(0x1000 - (a1->field_0 << 10), t->ftg_4, &t->ftg_4[a1->field_8 + 1], a1->work_94);
        if (++a1->field_0 >= 5)
        {
            a1->field_8++;
            a1->field_0 = 0;
            if (a1->field_8 < 3)
            {
                sub_80039FE4(&t->ftg_4[a1->field_8], &t->ftg_4[a1->field_8 + 1], a1->work_94);
            }
        }
    }
    else
    {
        if (++a1->field_0 >= 0x35)
        {
            a1->field_0 = 0;
            *a0 = (*a0 & ~1) | 0x8000;
            FreeFtgObjectData_80021804(a1->work_94, 1);
            free3_8003FC6C(a1->work_94);
        }
    }
    sub_8004D1EC(t->ftg_4, pOT_8008D690, a1->pos_44, &a1->rot_80, stru_8008D534, 0x10, v);
}
extern EventNode* effectObjects_8008B4A8;
extern void MdecEffectTask_80017B10(unsigned int* a0, EffectObj* a1);
// Matched
void SpawnMdecEffect_80017A6C(int a0, int a1)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    EffectObj* q;
    if (e)
    {
        q = e->buffer;
        q->field_8C = (int)mdecEffectSchedule_80091C00;
        q->field_0 = 0;
        if (a1 > 0)
        {
            q->field_4 = a1;
        }
        else
        {
            q->field_4 = sub_800181E8();
        }
        e->cb_8 = (EventEntryFn)MdecEffectTask_80017B10;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        AllocMdecVLCBufferInFileBuffer_8004188C();
        DecDCTReset(0);
    }
}
// Matched
void MdecEffectTask_80017B10(unsigned int* a0, EffectObj* a1)
{
    int* t = (int*)a1->field_8C;
    if (++a1->field_0 < a1->field_4 && effectOutcomeFlag_8008D780 == 0)
    {
        if (!(unknownFlags_8008D678 & 0x800))
        {
            DecodeMdec_80041920(((unsigned long**)t[1])[a1->field_0 % t[0]], mdecEffectVlcBuffer_8008D42C, 2);
            unknownFlags_8008D678 |= 0x800;
        }
    }
    else
    {
        ReleaseMdecVLCFileBuffer_800418FC();
        unknownFlags_8008D678 &= ~0x800;
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
extern void sub_80017CE4(EventEntry* e, void* buf);
// Matched
void sub_80017BF0(EventEntry* a0, int a1)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    EffectObj* q;
    int r;
    if (e)
    {
        q = e->buffer;
        q->pos_44[0] = ((int*)a0->buffer)[0];
        q->pos_44[1] = ((int*)a0->buffer)[1];
        q->pos_44[2] = ((int*)a0->buffer)[2];
        q->field_0 = 0;
        q->field_30 = 0;
        q->field_34 = 0x23F000;
        q->rot_80.vz = 0;
        q->rot_80.vy = 0;
        q->rot_80.vx = 0;
        r = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, a1);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q->field_88 = (int)&effectFile_80091BD0.models_28[r];
        e->cb_8 = sub_80017CE4;
    }
}
// Matched
void sub_80017CE4(EventEntry* e, void* buf)
{
    int* a0 = (int*)e;
    EffectObj* a1 = buf;
    EffectModel* t = (EffectModel*)a1->field_88;
    int i;
    int v[3];
    int y;
    if (a1->field_0 < 0x80)
    {
        for (i = 0; i < 16; i++)
        {
            v[0] = v[2] = 0x1000 + i * 0x80;
            y = word_80084540[(a1->field_0 * 16) & 0xFF0] * (word_80084540[((i - a1->field_0) * 256) & 0xF00] + 0x1000) / 4096;
            v[1] = y;
            sub_8004D1EC(t->ftg_4, pOT_8008D690, a1->pos_44, &a1->rot_80, stru_8008D534, ((0x1000 - y / 2) << 16) | 0xB0, v);
        }
        a1->field_0++;
    }
    else
    {
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
void sub_80017FF8(EventEntry* e, void* buf);
// Matched
void sub_80017E30(EventEntry* e, void* buf)
{
    EffectObj* a1 = buf;
    EffectModel* t = (EffectModel*)a1->field_88;
    int pos[3];
    int v[3];
    int* vp;
    if ((a1->field_30 -= 0x80) <= 0)
    {
        a1->field_0 = 0x1000;
        a1->field_30 = 0;
        e->cb_8 = sub_80017FF8;
    }
    LerpFtgObject_8003A6C4(0x1000 - a1->field_30, t->ftg_4, t->ftg_4 + 1, a1->work_94);
    if (a1->field_A0)
    {
        vp = v;
        v[0] = a1->field_A0[0] * 3 / 2;
        v[1] = a1->field_A0[1] * 3 / 2;
        v[2] = a1->field_A0[2] * 3 / 2;
    }
    else
    {
        vp = 0;
    }
    pos[0] = a1->field_20[a1->field_98 * 3 + 0] + a1->field_1C[0];
    pos[1] = a1->field_20[a1->field_98 * 3 + 1] + a1->field_1C[1];
    pos[2] = a1->field_20[a1->field_98 * 3 + 2] + a1->field_1C[2];
    sub_8004D1EC(t->ftg_4, pOT_8008D690, pos, &dword_800795D4, stru_8008D534, (a1->field_30 << 16) | 0xB0, vp);
}
// Matched
void sub_80017FF8(EventEntry* e, void* buf)
{
    EffectObj* a1 = buf;
    EffectModel* t = (EffectModel*)a1->field_88;
    int pos[3];
    int v[3];
    int* vp;
    if ((a1->field_0 -= 0x80) > 0)
    {
        LerpFtgObject_8003A6C4(0x1000 - a1->field_30, t->ftg_4, t->ftg_4 + 1, a1->work_94);
        if (a1->field_A0)
        {
            vp = v;
            v[0] = a1->field_A0[0] * 3 / 2;
            v[1] = a1->field_A0[1] * 3 / 2;
            v[2] = a1->field_A0[2] * 3 / 2;
        }
        else
        {
            vp = 0;
        }
        pos[0] = a1->field_20[a1->field_98 * 3 + 0] + a1->field_1C[0];
        pos[1] = a1->field_20[a1->field_98 * 3 + 1] + a1->field_1C[1];
        pos[2] = a1->field_20[a1->field_98 * 3 + 2] + a1->field_1C[2];
        sub_8004D1EC(t->ftg_4, pOT_8008D690, pos, &dword_800795D4, stru_8008D534, (a1->field_30 << 16) | 0xB0, vp);
    }
    else
    {
        e->flags = (e->flags & ~1) | 0x8000;
        FreeFtgObjectData_80021804(a1->work_94, 1);
        free3_8003FC6C(a1->work_94);
    }
}
// Matched
int sub_800181E8(void)
{
    return *mdecEffectSchedule_80091C00;
}
// Matched
// Matched
struct_4s* sub_80018200(struct_4s* src, unsigned short lo, unsigned short hi, short n)
{
    struct_4s* dst = ((EffectTaskState*)effectTask_8008D3F8->entry.buffer)->pairs_0;
    int i;
    int j;
    short d;
    for (i = 0; i < 10; i++)
    {
        dst[i].field_0 = src[i].field_0;
        dst[i].field_2 = src[i].field_2;
    }
    d = hi - lo;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (dst[j].field_0 >= hi)
            {
                dst[j].field_0 += d;
            }
            if (dst[j].field_2 >= hi)
            {
                dst[j].field_2 += d;
            }
        }
    }
    return dst;
}
extern int sub_800C0D50(void);
extern void sub_800C0FC4(EffectTarget* a0);
extern void sub_800A93A4(EffectTarget* a0);
extern void sub_800A29CC(int a0, EffectTarget* a1);
extern void sub_800A111C(int a0, EffectTarget* a1);
// Matched
void sub_800182B8(ActorEffectReq* p, int mask)
{
    EffectTaskState* t = effectTask_8008D3F8->entry.buffer;
    int i;
    int bit;
    p->count_40 = 0;
    for (i = 0; i < 11; i++)
    {
        bit = 1 << i;
        if (mask & bit)
        {
            switch (i)
            {
            case 1:
            case 2:
            case 3:
                if (sub_800C0D50() >= 0)
                {
                    sub_800C0FC4(&p->targets_44[p->count_40]);
                    break;
                }
            case 0:
                sub_800A93A4(&p->targets_44[p->count_40]);
                break;
            case 4:
            case 5:
            case 6:
                sub_800A29CC(i - 4, &p->targets_44[p->count_40]);
                break;
            case 8:
            case 9:
                sub_800A111C(i - 8, &p->targets_44[p->count_40]);
                break;
            }
            p->targets_44[p->count_40].field_34 = t->bits_44[i];
            p->count_40++;
        }
    }
}
