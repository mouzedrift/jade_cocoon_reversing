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
#include "menu_window.h"
#include "effect_data.h"

const Block16 elementIconRowOffsets_800741C4 = { { 0, 0, 14, 0, 28, 0, 42 } };

typedef struct
{
    unsigned short flags;
    char pad_2[0x1A];
} struct_AAF0_item;
typedef struct
{
    int flags;
    int field_4;
    int field_8;
    int field_C;
    struct_AAF0_item** items;
    int ot;
} struct_AAF0;
typedef struct
{
    unsigned short color;
    unsigned char b;
    unsigned char c;
} struct_AAF0_param;
extern short uiColor_8008B590;
extern void DrawWindow_80042460(void* a, int b, void* c, int d);
// Matched
void DrawMenuItemWindow_8002AAF0(struct_AAF0* p, int i, int j, RECT* r)
{
    struct_AAF0_param t;
    int k;
    int f;
    struct_AAF0_item* it = &p->items[i][j];
    k = 0;
    if (it->flags & 0x20)
    {
        return;
    }
    f = p->flags;
    if (f & 8)
    {
        t.c = 0;
    }
    else if (f & 0x10)
    {
        t.c = 1;
    }
    else if (f & 0x20)
    {
        t.c = 2;
    }
    else if (f & 0x40)
    {
        t.c = 3;
    }
    else if (f & 0x80)
    {
        t.c = 4;
    }
    else
    {
        t.c = 1;
    }
    f = p->flags;
    if (f & 1)
    {
        t.b = 0;
    }
    else if (f & 2)
    {
        t.b = 1;
        if (p->field_C == i)
        {
            k = p->field_4;
        }
    }
    else if ((f & 4) && p->field_C == i)
    {
        t.b = 2;
    }
    else
    {
        t.b = 0;
    }
    f = p->flags;
    if (!(f & 0x100))
    {
        t.color = uiColor_8008B590;
    }
    else if (f & 0x2000)
    {
        t.color = 4;
    }
    else if (f & 0x1000)
    {
        t.color = 3;
    }
    else if (f & 0x800)
    {
        t.color = 2;
    }
    else if (f & 0x400)
    {
        t.color = 1;
    }
    else
    {
        t.color = 0;
    }
    DrawWindow_80042460(r, (int)&t, &pOT_8008D454[p->ot], k);
}
// Matched
void AlignMenuItem_8002AC88(int flags, short* a, int b, short* out)
{
    if (flags & 4)
    {
        out[0] = a[0] + (a[2] - b);
        out[1] = a[1];
        return;
    }
    if (flags & 8)
    {
        out[0] = a[0] + ((unsigned int)(a[2] - b) >> 1);
        out[1] = a[1];
        return;
    }
    out[0] = a[0];
    out[1] = a[1];
}
// Matched
void GetMenuItemColor_8002ACE8(int flags, unsigned char* out)
{
    unsigned char val;
    if (flags & 2)
    {
        val = 0x40;
    }
    else
    {
        val = 0x80;
    }
    out[0] = val;
    out[1] = val;
    out[2] = val;
}
// Matched
void SetMenuItemFont1Clut_8002AD08(int flags)
{
    if (flags & 2)
    {
        SetFontClutOffset_8003F900(1, 1);
    }
    else
    {
        SetFontClutOffset_8003F900(1, 0);
    }
}
// Matched
void SetMenuItemFont2Clut_8002AD44(int flags)
{
    if (flags & 2)
    {
        SetFontClutOffset_8003F900(2, 1);
    }
    else
    {
        SetFontClutOffset_8003F900(2, 0);
    }
}
// Matched
void SetMenuItemDigitColor_8002AD80(int flags)
{
    if (flags & 2)
    {
        SetLargeDigitColor_8002C5D0(3);
    }
    else
    {
        SetLargeDigitColor_8002C5D0(0);
    }
}
extern void DrawMenuWindowContents_8002A710(void* a, int b);
extern void DrawWindow_80042460(void* a, int b, void* c, int d);
// Matched
void DrawMenuItemWithWindow_8002ADB4(char* item, int window, int ot, int time)
{
    DrawMenuWindowContents_8002A710(item, ot);
    SetFontClutOffset_8003F900(2, 0);
    SetFontClutOffset_8003F900(1, 0);
    DrawWindow_80042460(item + 0x10, window, &pOT_8008D454[ot], time);
}
typedef struct
{
    unsigned short color;
    unsigned char b;
    unsigned char c;
} struct_text_param;
extern short uiColor_8008B590;
extern void DrawText_8003E91C(int mode, int a, void* b, int c);
// Matched
void DrawTextLinesWindow_8002AE38(int text, Pos16* pos, int ot, RECT* rect, int count)
{
    int* lines = (int*)text;
    Pos16 p;
    struct_text_param t;
    unsigned int i;
    p.x = pos->x;
    p.y = pos->y;
    for (i = 0; i < count; i++)
    {
        if (lines[i])
        {
            DrawText_8003E91C(2, lines[i], &p, ot);
        }
        p.y += 12;
    }
    if (rect)
    {
        t.c = 1;
        t.b = 0;
        t.color = uiColor_8008B590;
        DrawWindow_80042460(rect, (int)&t, &pOT_8008D454[ot], 0);
    }
}
// Matched
void DrawLargeTextBox_8002AF10(int text, int pos, int ot)
{
    RECT r;
    r.x = 10;
    r.y = 0x99;
    r.w = 0x12C;
    r.h = 0x3C;
    DrawTextBox_8002AFA0(text, pos, ot, &r, 4);
}
// Matched
void DrawSmallTextBox_8002AF58(int text, int pos, int ot)
{
    RECT r;
    r.x = 10;
    r.y = 0xC3;
    r.w = 0x12C;
    r.h = 0x12;
    DrawTextBox_8002AFA0(text, pos, ot, &r, 1);
}
#if 0
void DrawTextBox_8002AFA0(int a0, int a1, int a2, RECT* a3, int a4)
{
}
#endif
// Matched
void DrawTextBox_8002AFA0(int text, int pos, int ot, RECT* rect, int count)
{
    Pos16 p;
    Pos16* src = (Pos16*)pos;
    if (src)
    {
        ((Pos16*)rect)->x = src->x;
        ((Pos16*)rect)->y = src->y;
    }
    p.x = ((Pos16*)rect)->x + 4;
    p.y = ((Pos16*)rect)->y + 5;
    DrawTextLinesWindow_8002AE38(text, &p, ot, rect, count);
}
typedef struct
{
    int icon;
    int text;
} struct_B004_entry;
extern void DrawUiTiySprt_8002C06C(void* p, int a1, int a2);
extern int MeasureTextWidth_8003E4C8(int text);
// Matched
void DrawButtonHelpBar_8002B004(struct_B004_entry* e, Pos16* a1, int ot)
{
    Pos16 cur;
    Pos16 base;
    RECT r;
    struct_text_param t;
    int i;
    i = 0;
    if (a1)
    {
        base.x = a1->x;
        base.y = a1->y;
    }
    else
    {
        base.x = 10;
        base.y = 0xD6;
    }
    cur.x = base.x + 2;
    for (; e[i].icon >= 0; i++)
    {
        cur.y = base.y + (14 - uiTiySprts_8008D620[e[i].icon].h) / 2;
        DrawUiTiySprt_8002C06C(&cur, e[i].icon, ot);
        cur.x = (unsigned short)(cur.x + 1) + uiTiySprts_8008D620[e[i].icon].w;
        cur.y = base.y + 2;
        DrawText_8003E91C(2, e[i].text, &cur, ot);
        cur.x = MeasureTextWidth_8003E4C8(e[i].text) + (unsigned short)(cur.x + 4);
    }
    r.x = base.x;
    r.y = base.y;
    r.w = 0x12C;
    r.h = 0xE;
    t.c = 1;
    t.b = 0;
    t.color = uiColor_8008B590;
    DrawWindow_80042460(&r, (int)&t, &pOT_8008D454[ot], 0);
}
extern void DrawElementIcons_8002B2A4(short a, int b, int c, Block16* d, int e);
// Matched
void DrawElementIconsRow_8002B1B0(short mask, int pos, int ot)
{
    Block16 local = elementIconRowOffsets_800741C4;
    DrawElementIcons_8002B2A4(mask, pos, ot, &local, 0);
}
