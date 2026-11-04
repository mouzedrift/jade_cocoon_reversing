// SHOPENTR.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "shopentr.h"

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



extern EventNode* dword_8008D4A8;
extern void DrawMenuBackground_8002BE10(void);
extern void DrawGauge_8002BA54(void* a0, int a1, void* a2, int a3);
extern void DrawText_8003E91C(int a0, char* a1, void* a2, short a3);
extern void DrawNumber_8003EF74(void* a0, int a1, short a2);
extern void DrawNumberRightAlignedFont1_8003F264(void* a0, int a1, short a2);
extern void UpdateMenuCursor_8003D794(CtxShopentr* c, int a1);
extern int IsConfirmPressedP1_8003D380(int a0);
extern int IsCancelPressedP1_8003D41C(int a0);
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
typedef struct
{
    short kind_0;
    char pad_2[0x92];
    char data_94[0x32];
    unsigned short field_C6;
    unsigned char field_C8;
} EntShopentr;
extern EntShopentr* sub_800B9C5C(int a0);
extern void DrawSmallText_8002FAA0(int a0, void* a1, void* a2, short a3);
extern void DrawElementIconsRow_8002B1B0(short a0, void* a1, short a2);

int dword_800B6D00 SDATA = 40;
const char asc_800B6D04[] = "\203Z\201[\203u\202\265\202\334\202\265\202\275"; // セーブしました
const char asc_800B6D14[] = "\203Z\201[\203u\202\265\202\304\202\242\202\351"; // セーブしている
const char asc_800B6D24[] = "\213\363\202\253\202\252\226\263\202\242"; // 空きが無い
const char asc_800B6D30[] = "\220V\202\265\202\255\203Z\201[\203u\202\265\202\334\202\267\202\251\201H"; // 新しくセーブしますか？
const char asc_800B6D48[] = "\217\343\217\221\202\253\202\265\202\334\202\267\202\251\201H"; // 上書きしますか？
const char asc_800B6D5C[] = "\217\343\217\221\202\253\202\265\202\304\202\242\202\351"; // 上書きしている
const char asc_800B6D6C[] = "\203t\203H\201[\203}\203b\203g\202\265\202\304\202\242\202\351"; // フォーマットしている
const char asc_800B6D84[] = "\203t\203H\201[\203}\203b\203g\202\267\202\351\202\265\202\310\202\242\201H"; // フォーマットするしない？
const char asc_800B6DA0[] = "\203A\203\223\203t\203H\201[\203}\203b\203g\202\276"; // アンフォーマットだ
const char asc_800B6DB4[] = "\203f\201[\203^\202\314\213\363\202\253\202\252\202\310\202\251\202\301\202\275"; // データの空きがなかった
const char asc_800B6DCC[] = "\203f\201[\203^\201i\202\314\213\363\202\253\201j\202\252\202\240\202\301\202\275\226\202\225\250"; // データ（の空き）があった魔物
const char asc_800B6DEC[] = "\203f\201[\203^\201i\202\314\213\363\202\253\201j\202\252\202\240\202\301\202\275\203u\203\215\203b\203N"; // データ（の空き）があったブロック
const char asc_800B6E10[] = "\203J\201[\203h\203`\203F\203b\203N\202Q"; // カードチェック２
const char asc_800B6E24[] = "\203X\203\215\203b\203g\221I\221\360\201H"; // スロット選択？
const char asc_800B6E34[] = "\203J\201[\203h\203`\203F\203b\203N\202P"; // カードチェック１
const int dword_800B6E48 = 0;

int sub_800B6F0C(void)
{
    return dword_800B7EAC;
}

// Matched
void sub_800B6F1C(void)
{
    EventEntry* t;
    CtxShopentr* c;
    t = AllocEventEntry_80043AF8(dword_8008D4A8);
    if (t)
    {
        t->flags = (t->flags | 1) & 0xFFFF7FFF;
        c = t->buffer;
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
        DrawMenuBackground_8002BE10();
    }
}

// Matched
void sub_800B7000(EventEntry* t, CtxShopentr* c)
{
    int r;
    DrawMenuBackground_8002BE10();
    sub_800B7440(c);
    r = 0;
    if (!(c->flags_C & 1))
    {
        UpdateMenuCursor_8003D794(c, r);
    }
    if (IsConfirmPressedP1_8003D380(0))
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
    else if (IsCancelPressedP1_8003D41C(0))
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
        t->flags = (t->flags & ~1) | 0x8000;
        sub_800B6CA0();
    }
}

void sub_800B7144(CtxShopentr* c)
{
    if (entries_800B7D08[c->state_14].next_0 == -1)
    {
        switch (c->state_14)
        {
        case 2:
            if (padHeld_800918D0[0] & 0x40)
            {
                c->state_14 = 5;
            }
            else if (padHeld_800918D0[0] & 4)
            {
                c->state_14 = 6;
            }
            else
            {
                c->state_14 = 3;
            }
            break;
        case 4:
            if (c->field_8 & 1)
            {
                c->state_14 = 0xb;
            }
            else
            {
                c->state_14 = 0xa;
            }
            break;
        case 7:
            if (c->field_8)
            {
                c->state_14 = 1;
            }
            else
            {
                c->state_14 = 8;
            }
            break;
        case 10:
            if (c->field_8)
            {
                c->state_14 = 3;
            }
            else
            {
                c->state_14 = 9;
            }
            break;
        case 11:
            if (!c->field_8)
            {
                c->state_14 = 0xd;
            }
            else
            {
                c->state_14 = 3;
            }
            break;
        }
    }
    else
    {
        c->state_14 = entries_800B7D08[c->state_14].next_0;
    }
    c->mask_10 = 0;
    c->mask_10 = masks_800B7E34[c->state_14];
    sub_800B7520(c);
    if (c->state_14 < 15 && entries_800B7D08[c->state_14].field_10)
    {
        c->flags_C |= 1;
    }
}
const char str_800B6E74[] = "\203\201\203\202\203\212\201[\203J\201[\203h\201@\203`\203F\203b\203N\222\206"; // メモリーカード　チェック中
const char str_800B6E90[] = "\203\201\203\202\203\212\201[\203J\201[\203h\221I\221\360"; // メモリーカード選択
const char str_800B6EA4[] = "\203X\203\215\203b\203g\202P"; // スロット１
const char str_800B6EB0[] = "\203X\203\215\203b\203g\202Q"; // スロット２
const char str_800B6EBC[] = "\226\232\222I\221I\221\360"; // 繭棚選択
const char str_800B6EC8[] = "\226\232\222I"; // 繭棚
const char str_800B6ED0[] = "\202\265\202\340\202\327\220\224"; // しもべ数
const char str_800B6EDC[] = "\216\236\212\324"; // 時間
const char str_800B6EE4[] = "\223o\230^"; // 登録
const char str_800B6EEC[] = "\226\274\221O"; // 名前
const char str_800B6EF4[] = "\212K\213\211"; // 階級
const char str_800B6EFC[] = "\221\256\220\253"; // 属性
const char str_800B6F04[] = "\201^"; // /
const char str_800B6F08[] = "\201F"; // :

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
// what DrawGauge_8002BA54 takes (struct_BA54 in ui_gauge.c)
typedef struct GaugeShopentr
{
    int state_0;
    int f4;
    int value_8;
    int max_C;
} GaugeShopentr;
int sub_800B73A8(CtxShopentr* c)
{
    short r[2];
    GaugeShopentr v;
    v.state_0 = 2;
    v.f4 = 0;
    v.value_8 = c->counter_16;
    v.max_C = 0x3c;
    r[0] = 0x8c;
    r[1] = 0xa0;
    DrawGauge_8002BA54(&v, 0, r, 14);
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
    DrawText_8003E91C(2, str_800B6E74, r, 14);
}

// Matched
void sub_800B75DC(CtxShopentr* c)
{
    unsigned short r[2];
    unsigned short q[2];
    unsigned short u[2];
    r[0] = word_800B7CD0[0];
    r[1] = word_800B7CD0[1];
    DrawText_8003E91C(2, str_800B6E90, r, 14);
    q[0] = word_800B7CD8[0];
    q[1] = word_800B7CD8[1];
    DrawText_8003E91C(2, str_800B6EA4, q, 14);
    u[0] = word_800B7CE0[0];
    u[1] = word_800B7CE0[1];
    DrawText_8003E91C(2, str_800B6EB0, u, 14);
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
        DrawNumber_8003EF74(q, c->field_A + i + 1, col);
        p[0] = 0x82;
        p[1] = a.y;
        sub_800B7B64((RectShopentr*)p, 0x14, 0x19);
        p[0] = 0xc8;
        p[1] = a.y + 4;
        sub_800B7C08((RectShopentr*)p);
    }
    l28[0] = 0x82;
    l28[1] = 0x20;
    DrawText_8003E91C(2, str_800B6EBC, l28, col);
    l30[0] = 0x50;
    l30[1] = 0x3c;
    DrawText_8003E91C(2, str_800B6EC8, l30, col);
    l38[0] = 0x82;
    l38[1] = 0x3c;
    DrawText_8003E91C(2, str_800B6ED0, l38, col);
    l40[0] = 0xd2;
    l40[1] = 0x3c;
    DrawText_8003E91C(2, str_800B6EDC, l40, col);
    p[0] = 0x20;
    p[1] = 0x50;
    sub_800B7A90((RectShopentr*)p, c->field_8 + c->field_A + 1, 0xf);
}

#if 0
// Not matched: i/s18 register allocation and delay slot filling differ (19 words).
// Copying s18 into a short k (k = s18; if (k) DrawElementIconsRow_8002B1B0(k, p, col);) fixes the registers and the
// sign extension, but then the beqz delay slot is filled from the taken path (one extra word).
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
            DrawSmallText_8002FAA0(0, p, d, col);
        }
        p[0] = 0xa2;
        p[1] = a.y + 4;
        if (s16)
        {
            q[0] = 0xa2;
            q[1] = p[1];
            DrawNumberRightAlignedFont1_8003F264(q, s16, col);
        }
        p[0] = 0xb2;
        p[1] = a.y + 2;
        if ((short)s18)
            DrawElementIconsRow_8002B1B0(s18, p, col);
    }
    l28[0] = 0x8c;
    l28[1] = 0x20;
    DrawText_8003E91C(2, str_800B6EE4, l28, col);
    l30[0] = 0x50;
    l30[1] = 0x3c;
    DrawText_8003E91C(2, str_800B6EEC, l30, col);
    l38[0] = 0x8c;
    l38[1] = 0x3c;
    DrawText_8003E91C(2, str_800B6EF4, l38, col);
    l40[0] = 0xd2;
    l40[1] = 0x3c;
    DrawText_8003E91C(2, str_800B6EFC, l40, col);
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
    DrawNumberRightAlignedFont1_8003F264(l18, a1, 14);
    l20[0] = p->x + 0x12;
    l20[1] = p->y + 2;
    DrawText_8003E91C(1, str_800B6F04, l20, 14);
    l28[0] = p->x + 0x2a;
    l28[1] = p->y + 2;
    DrawNumberRightAlignedFont1_8003F264(l28, a2, 14);
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
    DrawNumber_8003EF74(l10, a1, 14);
    l18[0] = p->x + 0x18;
    l18[1] = 0x3c;
    DrawText_8003E91C(2, str_800B6F04, l18, 14);
    l20[0] = p->x + 0x24;
    l20[1] = p->y;
    DrawNumber_8003EF74(l20, a2, 14);
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
    DrawNumberRightAlignedFont1_8003F264(l10, 0, 14);
    l18[0] = p->x + 0x10;
    l18[1] = p->y;
    DrawText_8003E91C(1, str_800B6F08, l18, 14);
    l20[0] = p->x + 0x20;
    l20[1] = p->y;
    DrawNumberRightAlignedFont1_8003F264(l20, 0, 14);
    l28[0] = p->x + 0x28;
    l28[1] = p->y;
    DrawNumberRightAlignedFont1_8003F264(l28, 0, 14);
}

int dword_800B7CC0[2] = { 0xC80010, 0xC0120 };
unsigned short word_800B7CC8[2] = { 16, 120 };
int dword_800B7CCC = 0x120120;
unsigned short word_800B7CD0[2] = { 80, 32 };
int dword_800B7CD4 = 0x1200A0;
unsigned short word_800B7CD8[2] = { 40, 120 };
int dword_800B7CDC = 0x12003C;
unsigned short word_800B7CE0[2] = { 200, 120 };
int dword_800B7CE4 = 0x12003C;
RectShopentr rects_800B7CE8[4] = {
    { 1, 1, 1 },
    { 2, 1, 2, 1 },
    { 1, 5, 15, 64 },
    { 1, 5, 25, 64 },
};
EntryShopentr entries_800B7D08[15] = {
    { 1, -2, 0, 0, 0, 0, 1 },
    { 2, 15, 1, 0, 1 },
    { -1, -2, 0, 0, 0, 0, 1 },
    { 4, 1, 2 },
    { 15, 15, 3 },
    { 1, 1 },
    { 7, 1 },
    { -1, 1, 1, 0, 1 },
    { 2, -2, 0, 0, 0, 0, 1 },
    { 15, -2, 0, 0, 0, 0, 1 },
    { -1, 4, 1, 0, 1 },
    { -1, 4, 1, 0, 1 },
    { 3, 4 },
    { 14, -2, 0, 0, 0, 0, 1 },
    { 15, 15 },
};
unsigned int masks_800B7E34[30] = {
    1, 2, 1, 4, 8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (unsigned int)asc_800B6E34,
    (unsigned int)asc_800B6E24, (unsigned int)asc_800B6E10, (unsigned int)asc_800B6DEC, (unsigned int)asc_800B6DCC, (unsigned int)asc_800B6DB4, (unsigned int)asc_800B6DA0, (unsigned int)asc_800B6D84, (unsigned int)asc_800B6D6C,
    (unsigned int)asc_800B6D5C, (unsigned int)asc_800B6D48, (unsigned int)asc_800B6D30, (unsigned int)asc_800B6D24, (unsigned int)asc_800B6D14, (unsigned int)asc_800B6D04,
};
int dword_800B7EAC = 0;
