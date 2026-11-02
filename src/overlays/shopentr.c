// SHOPENTR.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"

typedef struct
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} RectShopentr;

typedef struct
{
    short next_0;
    short next_2;
    short rect_4;
    short pad_6;
    int pad_8;
    int pad_C;
    int field_10;
} EntryShopentr;

typedef struct
{
    unsigned short rect_0[4];
    short field_8;
    short field_A;
    unsigned int flags_C;
    unsigned int mask_10;
    short state_14;
    short counter_16;
} CtxShopentr;

typedef struct
{
    unsigned int flags_0;
    int pad_4;
    int pad_8;
    int pad_C;
    int pad_10;
    CtxShopentr* ctx_14;
} TaskShopentr;

extern EntryShopentr entries_800B7D08[];
extern unsigned int masks_800B7E34[];
extern RectShopentr rects_800B7CE8[];
extern int dword_800B7EAC;
extern unsigned short word_800B7CC8[2];
extern unsigned short word_800B7CD0[2];
extern unsigned short word_800B7CD8[2];
extern unsigned short word_800B7CE0[2];
extern char str_800B6E74[];
extern char str_800B6E90[];
extern char str_800B6EA4[];
extern char str_800B6EB0[];

extern EventNode* dword_8008D4A8;
extern void sub_8002BE10(void);
extern void sub_8002BA54(void* a0, int a1, void* a2, int a3);
extern void sub_8003E91C(int a0, char* a1, void* a2, int a3);
extern void sub_8003EF74(void* a0, int a1, int a2);
extern void sub_8003F264(void* a0, int a1, int a2);
extern void sub_8003D794(CtxShopentr* c, int a1);
extern int sub_8003D380(int a0);
extern int sub_8003D41C(int a0);
extern void sub_800B6CA0(void);
extern void sub_800B7520(CtxShopentr* c);
extern void sub_800B7440(CtxShopentr* c);
extern void sub_800B7144(CtxShopentr* c);
extern void sub_800B72D4(CtxShopentr* c);
extern int sub_800B73A8(CtxShopentr* c);
extern void sub_800B7594(CtxShopentr* c);
extern void sub_800B75DC(CtxShopentr* c);
extern void sub_800B7684(CtxShopentr* c);
extern void sub_800B7858(CtxShopentr* c);
extern void sub_800B7A90(RectShopentr* p, short a1, short a2);
extern void sub_800B7B64(RectShopentr* p, short a1, short a2);
extern void sub_800B7C08(RectShopentr* p);
extern char str_800B6F04[];
extern char str_800B6F08[];

INCLUDE_OVERLAY_ASM(shopentr, dword_800B6D00);

// Matched
void sub_800B6F1C(void)
{
    TaskShopentr* t;
    CtxShopentr* c;
    t = (TaskShopentr*)sub_80043AF8(dword_8008D4A8);
    if (t)
    {
        t->flags_0 = (t->flags_0 | 1) & 0xFFFF7FFF;
        c = t->ctx_14;
        c->state_14 = 4;
        c->flags_C = 0;
        c->mask_10 = 0;
        c->counter_16 = 0;
        c->mask_10 = 0;
        c->mask_10 = masks_800B7E34[c->state_14];
        sub_800B7520(c);
        c->field_8 = 0;
        c->field_A = 0;
        if (c->state_14 < 15 && entries_800B7D08[c->state_14].field_10)
        {
            c->flags_C |= 1;
        }
        dword_800B7EAC = 1;
        sub_8002BE10();
    }
}

// Matched
void sub_800B7000(TaskShopentr* t, CtxShopentr* c)
{
    int r;
    sub_8002BE10();
    sub_800B7440(c);
    r = 0;
    if (!(c->flags_C & 1))
    {
        sub_8003D794(c, r);
    }
    if (sub_8003D380(0))
    {
        if (!(c->flags_C & 1))
        {
            PlaySfx_80031494(0x7e);
            sub_800B7144(c);
        }
        else
        {
            r = 1;
        }
    }
    else if (sub_8003D41C(0))
    {
        if (!(c->flags_C & 1))
        {
            sub_800B72D4(c);
        }
        else
        {
            r = 1;
        }
    }
    if (r)
    {
        PlaySfx_80031494(0x7c);
    }
    if (c->flags_C & 1)
    {
        if (sub_800B73A8(c))
        {
            PlaySfx_80031494(0x7e);
            sub_800B7144(c);
        }
    }
    if (c->state_14 == 15)
    {
        dword_800B7EAC = 0;
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
        sub_800B6CA0();
    }
}

INCLUDE_OVERLAY_ASM(shopentr, sub_800B7144);

// Matched
void sub_800B72D4(CtxShopentr* c)
{
    int snd;
    if (entries_800B7D08[c->state_14].next_2 != -2)
    {
        c->state_14 = entries_800B7D08[c->state_14].next_2;
        snd = 0x7d;
    }
    else
    {
        snd = 0x7c;
    }
    PlaySfx_80031494(snd);
    c->mask_10 = 0;
    c->mask_10 = masks_800B7E34[c->state_14];
    sub_800B7520(c);
    if (c->state_14 < 15 && entries_800B7D08[c->state_14].field_10)
    {
        c->flags_C |= 1;
    }
}

// Matched
int sub_800B73A8(CtxShopentr* c)
{
    short r[2];
    int v[4];
    v[0] = 2;
    v[1] = 0;
    v[2] = c->counter_16;
    v[3] = 0x3c;
    r[0] = 0x8c;
    r[1] = 0xa0;
    sub_8002BA54(v, 0, r, 14);
    if (c->counter_16 < 0x3c)
    {
        c->counter_16++;
        return 0;
    }
    c->counter_16 = 0;
    c->flags_C &= ~1;
    return 1;
}

// Matched
void sub_800B7440(CtxShopentr* c)
{
    short i;
    for (i = 0; i < 4; i++)
    {
        if (c->mask_10 & (1 << i))
        {
            switch (i)
            {
            case 0:
                sub_800B7594(c);
                break;
            case 1:
                sub_800B75DC(c);
                break;
            case 2:
                sub_800B7684(c);
                break;
            case 3:
                sub_800B7858(c);
                break;
            }
        }
    }
}

// Matched
void sub_800B7520(CtxShopentr* c)
{
    RectShopentr* r;
    if (c->state_14 < 15)
    {
        r = &rects_800B7CE8[entries_800B7D08[c->state_14].rect_4];
        c->rect_0[0] = r->x;
        c->rect_0[1] = r->y;
        c->rect_0[2] = r->w;
        c->rect_0[3] = r->h;
    }
}

// Matched
void sub_800B7594(CtxShopentr* c)
{
    unsigned short r[2];
    r[0] = word_800B7CC8[0];
    r[1] = word_800B7CC8[1];
    sub_8003E91C(2, str_800B6E74, r, 14);
}

// Matched
void sub_800B75DC(CtxShopentr* c)
{
    unsigned short r[2];
    unsigned short q[2];
    unsigned short u[2];
    r[0] = word_800B7CD0[0];
    r[1] = word_800B7CD0[1];
    sub_8003E91C(2, str_800B6E90, r, 14);
    q[0] = word_800B7CD8[0];
    q[1] = word_800B7CD8[1];
    sub_8003E91C(2, str_800B6EA4, q, 14);
    u[0] = word_800B7CE0[0];
    u[1] = word_800B7CE0[1];
    sub_8003E91C(2, str_800B6EB0, u, 14);
}

INCLUDE_OVERLAY_ASM(shopentr, sub_800B7684);

INCLUDE_OVERLAY_ASM(shopentr, sub_800B7858);

// Matched
void sub_800B7A90(RectShopentr* p, short a1, short a2)
{
    RectShopentr r;
    unsigned short l18[2];
    unsigned short l20[2];
    unsigned short l28[2];
    l18[0] = p->x + 0x12;
    l18[1] = p->y + 2;
    sub_8003F264(l18, a1, 14);
    l20[0] = p->x + 0x12;
    l20[1] = p->y + 2;
    sub_8003E91C(1, str_800B6F04, l20, 14);
    l28[0] = p->x + 0x2a;
    l28[1] = p->y + 2;
    sub_8003F264(l28, a2, 14);
    r.x = p->x;
    r.y = p->y;
    r.w = 0x2c;
    r.h = 0xc;
}

// Matched
void sub_800B7B64(RectShopentr* p, short a1, short a2)
{
    unsigned short l10[2];
    unsigned short l18[2];
    unsigned short l20[2];
    l10[0] = p->x;
    l10[1] = p->y;
    sub_8003EF74(l10, a1, 14);
    l18[0] = p->x + 0x18;
    l18[1] = 0x3c;
    sub_8003E91C(2, str_800B6F04, l18, 14);
    l20[0] = p->x + 0x24;
    l20[1] = p->y;
    sub_8003EF74(l20, a2, 14);
}

// Matched
void sub_800B7C08(RectShopentr* p)
{
    unsigned short l10[2];
    unsigned short l18[2];
    unsigned short l20[2];
    unsigned short l28[2];
    l10[0] = p->x + 0x10;
    l10[1] = p->y;
    sub_8003F264(l10, 0, 14);
    l18[0] = p->x + 0x10;
    l18[1] = p->y;
    sub_8003E91C(1, str_800B6F08, l18, 14);
    l20[0] = p->x + 0x20;
    l20[1] = p->y;
    sub_8003F264(l20, 0, 14);
    l28[0] = p->x + 0x28;
    l28[1] = p->y;
    sub_8003F264(l28, 0, 14);
}

INCLUDE_OVERLAY_ASM(shopentr, dword_800B7CC0);
