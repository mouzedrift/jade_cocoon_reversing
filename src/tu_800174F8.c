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
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
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
// Matched
void sub_8001761C(int* a0, int* a1)
{
    int* t = (int*)a1[0x88 / 4];
    int v[3];
    int f;
    a1[0x34 / 4] = a1[0x34 / 4] * 7 / 8;
    a1[0x30 / 4] += a1[0x34 / 4];
    v[0] = v[1] = v[2] = a1[0x30 / 4] / 4096;
    ((short*)a1)[0x82 / 2] += 0x80;
    f = (a1[0] < 45) ? 0 : (((a1[0] - 44) << 24) | 0x80);
    sub_8003A6C4(word_80084540[(a1[0] * 512) & 0xE00] / 2 + 0x800, t[1], t[1] + 0x54, a1[0x94 / 4]);
    sub_8004D1EC(t[1], (int)pOT_8008D690, (int)(a1 + 0x44 / 4), (int)(a1 + 0x80 / 4), (int)stru_8008D534, f | 0x31, (int)v);
    if (a1[0]++ > 60)
    {
        *a0 = (*a0 & ~1) | 0x8000;
        sub_80021804(a1[0x94 / 4], 1);
        free3_8003FC6C((void*)a1[0x94 / 4]);
    }
}
void sub_800178C0(int* a0, int* a1);
// Matched
void sub_80017784(char* a0, int a1, short* a2)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
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
extern EventNode* effectObjects_8008B4A8;
extern void MdecEffectTask_80017B10(unsigned int* a0, int* a1);
// Matched
void SpawnMdecEffect_80017A6C(int a0, int a1)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    int* q;
    if (e)
    {
        q = (int*)e->buffer;
        q[0x8C / 4] = (int)mdecEffectSchedule_80091C00;
        q[0] = 0;
        if (a1 > 0)
        {
            q[1] = a1;
        }
        else
        {
            q[1] = sub_800181E8();
        }
        e->cb_8 = (EventEntryFn)MdecEffectTask_80017B10;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        AllocMdecVLCBufferInFileBuffer_8004188C();
        DecDCTReset(0);
    }
}
// Matched
void MdecEffectTask_80017B10(unsigned int* a0, int* a1)
{
    int* t = (int*)a1[0x8C / 4];
    if (++a1[0] < a1[1] && effectOutcomeFlag_8008D780 == 0)
    {
        if (!(unknownFlags_8008D678 & 0x800))
        {
            DecodeMdec_80041920(((unsigned long**)t[1])[a1[0] % t[0]], mdecEffectVlcBuffer_8008D42C, 2);
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
extern int sub_80020F00(void* p, int a, int b);
// Matched
void sub_80017BF0(EventEntry* a0, int a1)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
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
// Matched
void sub_80017CE4(EventEntry* e, void* buf)
{
    int* a0 = (int*)e;
    int* a1 = (int*)buf;
    int* t = (int*)a1[0x88 / 4];
    int i;
    int v[3];
    int y;
    if (a1[0] < 0x80)
    {
        for (i = 0; i < 16; i++)
        {
            v[0] = v[2] = 0x1000 + i * 0x80;
            y = word_80084540[(a1[0] * 16) & 0xFF0] * (word_80084540[((i - a1[0]) * 256) & 0xF00] + 0x1000) / 4096;
            v[1] = y;
            sub_8004D1EC(t[1], (int)pOT_8008D690, (int)(a1 + 0x44 / 4), (int)(a1 + 0x80 / 4), (int)stru_8008D534, ((0x1000 - y / 2) << 16) | 0xB0, (int)v);
        }
        a1[0]++;
    }
    else
    {
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
extern int dword_800795D4;
void sub_80017FF8(EventEntry* e, void* buf);
// Matched
void sub_80017E30(EventEntry* e, void* buf)
{
    int* a1 = (int*)buf;
    int* t = (int*)a1[0x88 / 4];
    int pos[3];
    int v[3];
    int* vp;
    if ((a1[0x30 / 4] -= 0x80) <= 0)
    {
        a1[0] = 0x1000;
        a1[0x30 / 4] = 0;
        e->cb_8 = sub_80017FF8;
    }
    sub_8003A6C4(0x1000 - a1[0x30 / 4], t[1], t[1] + 0x54, a1[0x94 / 4]);
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
    sub_8004D1EC(t[1], (int)pOT_8008D690, (int)pos, (int)&dword_800795D4, (int)stru_8008D534, (a1[0x30 / 4] << 16) | 0xB0, (int)vp);
}
// Matched
void sub_80017FF8(EventEntry* e, void* buf)
{
    int* a1 = (int*)buf;
    int* t = (int*)a1[0x88 / 4];
    int pos[3];
    int v[3];
    int* vp;
    if ((a1[0] -= 0x80) > 0)
    {
        sub_8003A6C4(0x1000 - a1[0x30 / 4], t[1], t[1] + 0x54, a1[0x94 / 4]);
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
        sub_8004D1EC(t[1], (int)pOT_8008D690, (int)pos, (int)&dword_800795D4, (int)stru_8008D534, (a1[0x30 / 4] << 16) | 0xB0, (int)vp);
    }
    else
    {
        e->flags = (e->flags & ~1) | 0x8000;
        sub_80021804(a1[0x94 / 4], 1);
        free3_8003FC6C((void*)a1[0x94 / 4]);
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
    struct_4s* dst = (struct_4s*)effectTask_8008D3F8[9];
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
extern void sub_800C0FC4(void* a0);
extern void sub_800A93A4(void* a0);
extern void sub_800A29CC(int a0, void* a1);
extern void sub_800A111C(int a0, void* a1);
typedef struct
{
    unsigned char pad[0x34];
    int value;
} Entry56;
typedef struct
{
    unsigned char pad[0x40];
    int count;
    Entry56 entries[11];
} EntryList;
// Matched
void sub_800182B8(int* p, int mask)
{
    unsigned char* t = (unsigned char*)effectTask_8008D3F8[9];
    int i;
    int bit;
    ((EntryList*)p)->count = 0;
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
                    sub_800C0FC4(&((EntryList*)p)->entries[((EntryList*)p)->count]);
                    break;
                }
            case 0:
                sub_800A93A4(&((EntryList*)p)->entries[((EntryList*)p)->count]);
                break;
            case 4:
            case 5:
            case 6:
                sub_800A29CC(i - 4, &((EntryList*)p)->entries[((EntryList*)p)->count]);
                break;
            case 8:
            case 9:
                sub_800A111C(i - 8, &((EntryList*)p)->entries[((EntryList*)p)->count]);
                break;
            }
            ((EntryList*)p)->entries[((EntryList*)p)->count].value = (t + i)[0x44];
            ((EntryList*)p)->count++;
        }
    }
}
