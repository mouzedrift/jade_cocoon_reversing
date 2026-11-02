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
extern void sub_8003E91C(int a0, char* a1, void* a2, short a3);
extern void sub_8003EF74(void* a0, int a1, short a2);
extern void sub_8003F264(void* a0, int a1, short a2);
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
extern char str_800B6EBC[];
extern char str_800B6EC8[];
extern char str_800B6ED0[];
extern char str_800B6EDC[];
extern char str_800B6EE4[];
extern char str_800B6EEC[];
extern char str_800B6EF4[];
extern char str_800B6EFC[];
extern char str_800B6F04[];
typedef struct
{
    short kind_0;
    char pad_2[0x92];
    char data_94[0x32];
    unsigned short field_C6;
    unsigned char field_C8;
} EntShopentr;
extern EntShopentr* sub_800B9C5C(int a0);
extern void sub_8002FAA0(int a0, void* a1, void* a2, short a3);
extern void sub_8002B1B0(short a0, void* a1, short a2);
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

#if 0
// Not built: the jump table (switch on state - 2) lives in the overlay data blob, a compiled
// switch would emit a second table in .rdata
void sub_800B7144(CtxShopentr* c)
{
    EntryShopentr* e = &entries_800B7D08[c->state_14];
    if (e->next_0 == -1)
    {
        switch (c->state_14)
        {
        case 2:
            if (word_800918D0[0] & 0x40) c->state_14 = 5;
            else if (word_800918D0[0] & 4) c->state_14 = 6;
            else c->state_14 = 3;
            break;
        case 4:
            c->state_14 = (c->field_8 & 1) ? 0xb : 0xa;
            break;
        case 7:
            c->state_14 = c->field_8 ? 1 : 8;
            break;
        case 10:
            c->state_14 = c->field_8 ? 3 : 9;
            break;
        case 11:
            c->state_14 = c->field_8 ? 3 : 0xd;
            break;
        }
    }
    else
    {
        c->state_14 = e->next_0;
    }
    c->mask_10 = 0;
    c->mask_10 = masks_800B7E34[c->state_14];
    sub_800B7520(c);
    if (c->state_14 < 15 && entries_800B7D08[c->state_14].field_10)
    {
        c->flags_C |= 1;
    }
}
#endif
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

// Matched
void sub_800B7684(CtxShopentr* c)
{
    RectShopentr a;
    unsigned short p[2];
    unsigned short q[2];
    unsigned short l28[2];
    unsigned short l30[2];
    unsigned short l38[2];
    unsigned short l40[2];
    short i;
    int col = 14;
    a.x = 0x50;
    a.w = 0xa0;
    a.h = 0x12;
    for (i = 0; i < 5; i++)
    {
        a.y = i * 19 + 0x50;
        q[1] = a.y;
        q[0] = a.x;
        sub_8003EF74(q, c->field_A + i + 1, col);
        p[0] = 0x82;
        p[1] = a.y;
        sub_800B7B64((RectShopentr*)p, 0x14, 0x19);
        p[0] = 0xc8;
        p[1] = a.y + 4;
        sub_800B7C08((RectShopentr*)p);
    }
    l28[0] = 0x82;
    l28[1] = 0x20;
    sub_8003E91C(2, str_800B6EBC, l28, col);
    l30[0] = 0x50;
    l30[1] = 0x3c;
    sub_8003E91C(2, str_800B6EC8, l30, col);
    l38[0] = 0x82;
    l38[1] = 0x3c;
    sub_8003E91C(2, str_800B6ED0, l38, col);
    l40[0] = 0xd2;
    l40[1] = 0x3c;
    sub_8003E91C(2, str_800B6EDC, l40, col);
    p[0] = 0x20;
    p[1] = 0x50;
    sub_800B7A90((RectShopentr*)p, c->field_8 + c->field_A + 1, 0xf);
}

#if 0
// Not matched: i/s18 register allocation and delay slot filling differ (19 words)
void sub_800B7858(CtxShopentr* c)
{
    RectShopentr a;
    unsigned short p[2];
    unsigned short q[2];
    unsigned short l28[2];
    unsigned short l30[2];
    unsigned short l38[2];
    unsigned short l40[2];
    EntShopentr* e;
    char* d;
    int s16;
    unsigned short s18;
    short i;
    short col = 14;
    a.x = 0x50;
    a.w = 0xa0;
    a.h = 0x12;
    for (i = 0; i < 5; i++)
    {
        e = sub_800B9C5C(i + c->field_A);
        if (e && e->kind_0 != 4)
        {
            d = e->data_94;
            s16 = e->field_C8;
            s18 = e->field_C6;
        }
        else
        {
            d = 0;
            s16 = 0;
            s18 = 0;
        }
        a.y = i * 19 + 0x50;
        p[1] = a.y + 4;
        p[0] = a.x + 3;
        if (d)
        {
            sub_8002FAA0(0, p, d, col);
        }
        p[0] = 0xa2;
        p[1] = a.y + 4;
        if (s16)
        {
            q[0] = 0xa2;
            q[1] = p[1];
            sub_8003F264(q, s16, col);
        }
        p[0] = 0xb2;
        p[1] = a.y + 2;
        if ((short)s18)
            sub_8002B1B0(s18, p, col);
    }
    l28[0] = 0x8c;
    l28[1] = 0x20;
    sub_8003E91C(2, str_800B6EE4, l28, col);
    l30[0] = 0x50;
    l30[1] = 0x3c;
    sub_8003E91C(2, str_800B6EEC, l30, col);
    l38[0] = 0x8c;
    l38[1] = 0x3c;
    sub_8003E91C(2, str_800B6EF4, l38, col);
    l40[0] = 0xd2;
    l40[1] = 0x3c;
    sub_8003E91C(2, str_800B6EFC, l40, col);
    p[0] = 0x20;
    p[1] = 0x50;
    sub_800B7A90((RectShopentr*)p, c->field_8 + c->field_A + 1, 0x19);
}
#endif
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
