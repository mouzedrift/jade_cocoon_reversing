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
#include "tiy.h"
#include "pad_text.h"
#include "main.h"

extern unsigned short padPressed_8009194C[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padRepeat_800918CC[];
extern void PlaySfx_80031494(int id);

const unsigned short emptyText_80074994[2] = { 0 };
const TextBuf22 emptyNameBuf_80074998 = { { 0xFFFF } };
const int dword_800749B0 = 0;

// Matched
int AdjustByShoulderButtons_8003D198(int limit, int pos, int step, int idx)
{
    if (padRepeat_800918CC[idx] & 2)
    {
        pos += step;
    }
    else if (padRepeat_800918CC[idx] & 8)
    {
        if (!(padHeld_800918D0[idx] & 2))
        {
            pos -= step;
        }
    }
    if (pos >= limit)
    {
        pos = limit - 1;
    }
    if (pos < 0)
    {
        pos = 0;
    }
    return pos;
}
// Matched
int AdjustByLeftRight_8003D210(int limit, int pos, int step, int idx)
{
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        pos += step;
    }
    else if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (!(padHeld_800918D0[idx] & 0x2000))
        {
            pos -= step;
        }
    }
    if (pos >= limit)
    {
        pos = limit - 1;
    }
    if (pos < 0)
    {
        pos = 0;
    }
    return pos;
}
// Matched
int IsConfirmPressed_8003D288(int playSfx, int pad)
{
    int r = 0;
    unsigned int x;
    if ((padPressed_8009194C[pad] & 0x40) && !(padHeld_800918D0[pad] & 4) && !(padReleased_800918D4[pad] & 4))
    {
        goto done;
    }
    x = padPressed_8009194C[pad];
    if (!(x & 4))
    {
        goto end;
    }
    if ((padHeld_800918D0[pad] & 0x40) || (padReleased_800918D4[pad] & 0x40))
    {
        if (!(x & 0x40))
        {
            goto end;
        }
    }
done:
    if (playSfx)
    {
        PlaySfx_80031494(0x7E);
    }
    r = 1;
end:
    return r;
}
// Matched
int IsConfirmPressedP1_8003D380(int playSfx)
{
    return IsConfirmPressed_8003D288(playSfx, 0);
}
// Matched
int IsConfirmPressedP2_8003D3A0(int playSfx)
{
    return IsConfirmPressed_8003D288(playSfx, 1);
}
// Matched
int IsCancelPressed_8003D3C0(int playSfx, int pad)
{
    int r = 0;
    unsigned short x = padPressed_8009194C[pad];
    if ((x & 0x10) || (x & 1))
    {
        if (playSfx)
        {
            PlaySfx_80031494(0x7D);
        }
        r = 1;
    }
    return r;
}
// Matched
int IsCancelPressedP1_8003D41C(int playSfx)
{
    return IsCancelPressed_8003D3C0(playSfx, 0);
}
// Matched
int IsCancelPressedP2_8003D43C(int playSfx)
{
    return IsCancelPressed_8003D3C0(playSfx, 1);
}
// Matched
int IsCircleHeld_8003D45C(int idx)
{
    unsigned int f = padHeld_800918D0[idx] & 0x20;
    return f != 0;
}
// Matched
int IsCircleHeldP1_8003D480(void)
{
    return IsCircleHeld_8003D45C(0);
}
// Matched
int IsCircleHeldP2_8003D4A0(void)
{
    return IsCircleHeld_8003D45C(1);
}
// Matched
int MoveGridCursor_8003D4C0(short* m, int idx)
{
    int r = 1;
    if (m[4] < 0)
    {
        m[4] = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (m[4] % m[0] == m[0] - 1)
        {
            r |= 2;
        }
        else
        {
            m[4]++;
        }
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (m[4] % m[0] == 0)
        {
            r |= 4;
        }
        else
        {
            m[4]--;
        }
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (m[4] < m[0])
        {
            r |= 8;
        }
        else
        {
            m[4] -= m[0];
        }
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (m[4] > m[0] * (m[1] - 1) - 1)
        {
            r |= 0x10;
        }
        else
        {
            m[4] += m[0];
        }
    }
    return r;
}
// Matched
int MoveGridCursorP1_8003D630(short* m)
{
    int idx = 0;
    if (m[3] < 0)
    {
        m[3] = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (m[3] % m[4] == m[4] - 1)
        {
            return 1;
        }
        m[3]++;
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (m[3] % m[4] == 0)
        {
            return 2;
        }
        m[3]--;
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (m[3] < m[4])
        {
            return 3;
        }
        m[3] -= m[4];
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (m[3] > m[4] * (m[5] - 1) - 1)
        {
            return 4;
        }
        m[3] = m[3] + m[4];
    }
    return 0;
}
typedef struct
{
    short field_0;
    short field_2;
    unsigned short field_4;
    unsigned short field_6;
    short field_8;
    short field_A;
} MenuCursor;

extern int MenuCursorInput_8003D830();

// Matched
int UpdateMenuCursor_8003D794(MenuCursor* p)
{
    unsigned short a = p->field_8;
    unsigned short b = p->field_A;
    int r = MenuCursorInput_8003D830(p);
    if (r == 0)
    {
        int t = p->field_4 - 1;
        if (t < p->field_8)
        {
            p->field_8 = t;
        }
    }
    if ((short)a != p->field_8 || (short)b != p->field_A)
    {
        PlaySfx_80031494(0x7F);
    }
    return r;
}
// Matched
int MenuCursorInput_8003D830(MenuCursor* p, int idx)
{
    int r = MoveGridCursor_8003D4C0((short*)p, idx);
    int t;
    int t2;

    if (p->field_6 & 0x40)
    {
        if (r & 8)
        {
            if (p->field_A >= p->field_0)
            {
                p->field_A -= p->field_0;
                return 8;
            }
        }
        else if (r & 0x10)
        {
            if (p->field_A < p->field_4 - p->field_0 * p->field_2)
            {
                p->field_A += p->field_0;
                return 7;
            }
        }
    }
    if (p->field_6 & 1)
    {
        if (r & 2)
        {
            t = p->field_0 - 1;
            p->field_8 -= t;
        }
        if (r & 4)
        {
            p->field_8 += p->field_0 - 1;
        }
    }
    if (p->field_6 & 2)
    {
        if (r & 8)
        {
            p->field_8 += p->field_0 * (p->field_2 - 1);
        }
        if (r & 0x10)
        {
            t2 = p->field_0 - p->field_2 * p->field_0;
            p->field_8 += t2;
        }
    }
    if ((p->field_6 & 4) && (r & 2))
    {
        return 1;
    }
    if ((p->field_6 & 8) && (r & 4))
    {
        return 2;
    }
    if ((p->field_6 & 0x10) && (r & 8))
    {
        return 3;
    }
    if ((p->field_6 & 0x20) && (r & 0x10))
    {
        return 4;
    }
    if (p->field_6 & 0x40)
    {
        p->field_A = AdjustByShoulderButtons_8003D198(p->field_4 - p->field_0 * p->field_2 + 1, p->field_A, p->field_0 * p->field_2, 0);
    }
    return 0;
}
// Matched
int GetMenuCursorIndex_8003DA54(MenuCursor* p)
{
    return (short)(p->field_8 + p->field_A);
}
typedef struct
{
    unsigned short field_0;
    unsigned short field_2;
    unsigned short field_4;
    unsigned short field_6;
    unsigned short field_8;
    unsigned short field_A;
    unsigned short field_C;
    unsigned short pad_E;
    unsigned char* field_10;
    unsigned short field_14;
    unsigned short pad_16;
} FontDef;
extern FontDef fontDefs_80086574[];
// Matched
void InitFonts_8003DA70(void)
{
    int i;
    FontDef* e;
    Font* f;
    for (i = 0; i < 3; i++)
    {
        e = &fontDefs_80086574[i];
        f = &fonts_80095FB0[i];
        MemCopy_800403E8(f, &publicTiySprts_8008D434[e->field_0], 0x14);
        f->w_10 = e->field_6;
        f->h_12 = e->field_8;
        f->tpage_14 = (unsigned short*)&publicTiyTPages_8008D440[e->field_0];
        f->u0_18 = f->u_C;
        f->v0_1A = f->v_D;
        f->firstChar_1E = e->field_4;
        f->clutX_20 = e->field_A;
        f->clutY_22 = e->field_C;
        f->widths_24 = e->field_10;
        f->columns_1C = e->field_2;
        f->charsPerClut_28 = e->field_14;
        f->clutOffset_2A = 0;
    }
}
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern void AddDrawAreaPrim_8003326C(void* p, unsigned long* ot);
typedef struct TextWindow TextWindow;
void DrawTextWindow_8003DCA4(int draw, TextWindow* w);
// Matched
int UpdateTextWindow_8003DB74(unsigned int* w, int a)
{
    if (w[9] >= 3 - (settingsFlags_8008B58C.word & 7))
    {
        w[9] = 0;
        w[7]++;
    }
    if (w[5] == 0)
    {
        w[7] = 0x0FFFFFFF;
    }
    w[8] = w[7];
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    DrawTextWindow_8003DCA4(a, (TextWindow*)w);
    AddDrawAreaPrim_8003326C(w + 1, pOT_8008D454);
    switch (w[10])
    {
    case 1:
        if (w[6] == 1 && ((padHeld_800918D0[0] & 0x60F) || (padPressed_8009194C[0] & 0xF0)))
        {
            w[7] = 0x0FFFFFFF;
        }
        else
        {
            w[9]++;
        }
        break;
    case 10:
        return 1;
    }
    return 0;
}
extern int charWidthThresholds_80086898[][12];
extern void IntToText_8003F610(unsigned short* buf, int val);
extern unsigned short* DecodeText_8003F748(int mode, unsigned short* s);
struct TextWindow
{
    short x;
    short y;
    char pad_4[8];
    int* lines;
    int ot;
    char pad_14[8];
    int limit;
    char pad_20[8];
    int state;
    signed char flags[1];
};
// Matched
void DrawTextWindow_8003DCA4(int draw, TextWindow* w)
{
    unsigned short num[12];
    TextBuf22 name;
    int limit;
    int count;
    int y;
    Font* f;
    unsigned short* s;
    unsigned short* sub;
    int* lines;
    int nl;
    int x;
    int ci;
    unsigned short c;
    short k;
    int i;
    int n;
    int col;

    sub = emptyText_80074994;
    count = 0;
    name = emptyNameBuf_80074998;
    x = w->x;
    y = w->y;
    f = &fonts_80095FB0[2];
    lines = w->lines;
    limit = w->limit;
    nl = 0;
    while (*lines != 0)
    {
        s = EncodeText_8003F684(2, (unsigned short*)*lines++);
        while (*s != 0 || *sub != 0)
        {
            if (count >= limit)
            {
                goto done;
            }
            if (*sub != 0)
            {
                c = *sub++;
            }
            else
            {
                c = *s++;
            }
            ci = c;
            if (c < 0x7F)
            {
                if (draw)
                {
                    f->clut_E = GetClut(f->clutX_20, f->clutY_22 + (ci - 1) / (unsigned short)f->charsPerClut_28 + (unsigned short)f->clutOffset_2A);
                    n = (ci - 1) % (unsigned short)f->charsPerClut_28;
                    col = n % (unsigned short)f->columns_1C;
                    n = n / (unsigned short)f->columns_1C;
                    f->x0_8 = x;
                    f->y0_A = y;
                    f->u_C = f->u0_18 + f->w_10 * col;
                    f->v_D = f->v0_1A + f->h_12 * n;
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)f)[0];
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)f)[1];
                    count++;
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)f)[2];
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)f)[3];
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)f)[4];
                    addPrim(&pOT_8008D454[w->ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
                    for (k = 12; k != 0; k--)
                    {
                        if (ci - 1 < charWidthThresholds_80086898[1][k - 1])
                        {
                            x -= k;
                            break;
                        }
                    }
                    x += f->w_10;
                }
            }
            else
            {
                switch (ci)
                {
                case -1:
                    break;
                case 0x81:
                    SetFontClutOffset_8003F900(2, 3);
                    break;
                case 0x7F:
                    SetFontClutOffset_8003F900(2, 0);
                    break;
                case 0x80:
                case 0x82:
                case 0x83:
                case 0x84:
                case 0x85:
                    SetFontClutOffset_8003F900(2, c - 0x7F);
                    break;
                case 0x86:
                case 0x87:
                    if (CopyPlayerName_8003F860(playerName_8008BD48, name.s))
                    {
                        DecodeText_8003F748(1, name.s);
                    }
                    sub = EncodeText_8003F684(2, name.s);
                    break;
                case 0x88:
                case 0x89:
                case 0x8A:
                case 0x8B:
                case 0x8C:
                    IntToText_8003F610(num, textNumberArgs_80096038[c - 0x88]);
                    sub = EncodeText_8003F684(2, num);
                    break;
                case 0xC1:
                case 0xC2:
                    nl = 1;
                    break;
                case 0x91 ... 0xC0:
                    {
                        for (i = 0; i < (int)(c - 0x91); i++)
                        {
                            w->flags[i] = -2;
                        }
                        if (w->flags[c - 0x91] == -1)
                        {
                            w->flags[c - 0x91] = c - 0x91;
                        }
                        nl = 1;
                    }
                    break;
                }
            }
        }
        if (nl == 1)
        {
            nl = 0;
        }
        else
        {
            x = w->x;
            y += 12;
        }
    }
    w->state = 10;
done:
    if (draw)
    {
        SetFontClutOffset_8003F900(2, 0);
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)f->tpage_14)[0];
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)f->tpage_14)[1];
        addPrim(&pOT_8008D454[w->ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
    }
}
// Matched
void DrawMsgWindowNextPrompt_8003E268(unsigned short* p)
{
    short x = p[0] + 0xC3;
    short y = p[1] + 0x23;
    DrawNextPrompt_8003CF88(x, y, 0);
}
typedef struct
{
    short w;
    short h;
} struct_size_8003E3B4;
extern int MeasureTextWidth_8003E4C8(int str);
// Matched
struct_size_8003E3B4 MeasureTextLinesMasked_8003E2A8(int* list, unsigned int mask)
{
    struct_size_8003E3B4 sz;
    short w;
    int i;
    sz.w = 0;
    sz.h = 0;
    for (i = 0; list[i]; i++)
    {
        if (mask & (1 << i))
        {
            w = MeasureTextWidth_8003E4C8(list[sz.h]);
            if (sz.w < w)
            {
                sz.w = w;
            }
            sz.h++;
        }
    }
    sz.h *= 12;
    return sz;
}
typedef struct
{
    short w;
    short h;
} Size2;
extern int MeasureTextWidth_8003E4C8(int str);

// Matched
struct_size_8003E3B4 MeasureTextLines_8003E3B4(int* list)
{
    struct_size_8003E3B4 sz;
    short w;
    int i;
    sz.w = 0;
    sz.h = 0;
    for (i = 0; list[i]; i++)
    {
        if (!IsTextMarkerLine_8003E484(list[i]))
        {
            w = MeasureTextWidth_8003E4C8(list[i]);
            if (sz.w < w)
            {
                sz.w = w;
            }
            sz.h++;
        }
    }
    sz.h *= 12;
    return sz;
}
// Matched
int IsTextMarkerLine_8003E484(int text)
{
    int v = *EncodeText_8003F684(2, (unsigned short*)text);
    if (v < 0xC3)
    {
        if (v >= 0x91)
        {
            return 1;
        }
    }
    return 0;
}
extern int GetCharWidth_8003E884(int idx, short n);
// Matched
int MeasureTextWidth_8003E4C8(int str)
{
    unsigned short num[12];
    TextBuf22 name;
    unsigned short* s;
    unsigned short* sub;
    short w;
    int k;
    unsigned short c;

    sub = emptyText_80074994;
    w = 0;
    name = emptyNameBuf_80074998;
    k = -1;
    s = EncodeText_8003F684(2, (unsigned short*)str);
    while (*s != 0 || *sub != 0)
    {
        if (*sub != 0 && sub != NULL)
        {
            c = *sub++;
        }
        else
        {
            c = *s++;
        }
        if (c < 0x7F)
        {
            w += GetCharWidth_8003E884(2, (short)c);
        }
        else
        {
            switch (c)
            {
            case 0x86:
            case 0x87:
                if (CopyPlayerName_8003F860(playerName_8008BD48, name.s))
                {
                    DecodeText_8003F748(1, name.s);
                }
                sub = EncodeText_8003F684(2, name.s);
                break;
            case 0x88:
            case 0x89:
            case 0x8A:
            case 0x8B:
            case 0x8C:
                IntToText_8003F610(num, textNumberArgs_80096038[k - 0x88]);
                sub = EncodeText_8003F684(2, num);
                break;
            case -1:
                w += 14;
                break;
            }
        }
    }
    return w;
}
// Matched
int MeasureTextWidthFont1_8003E6B0(int str)
{
    unsigned short num[12];
    TextBuf22 name;
    unsigned short* s;
    unsigned short* sub;
    short w;
    int k;
    unsigned short c;

    sub = emptyText_80074994;
    w = 0;
    name = emptyNameBuf_80074998;
    k = -1;
    s = EncodeText_8003F684(1, (unsigned short*)str);
    while (*s != 0 || *sub != 0)
    {
        if (*sub != 0 && sub != NULL)
        {
            c = *sub++;
        }
        else
        {
            c = *s++;
        }
        if (c < 0x71)
        {
            w += GetCharWidth_8003E884(1, (short)c);
        }
        else
        {
            switch (c)
            {
            case 0x86:
            case 0x87:
                if (CopyPlayerName_8003F860(playerName_8008BD48, name.s))
                {
                    DecodeText_8003F748(1, name.s);
                }
                sub = EncodeText_8003F684(2, name.s);
                break;
            case 0x88:
            case 0x89:
            case 0x8A:
            case 0x8B:
            case 0x8C:
                IntToText_8003F610(num, textNumberArgs_80096038[k - 0x88]);
                sub = EncodeText_8003F684(1, num);
                break;
            case -1:
                break;
            }
        }
    }
    return w;
}

FontDef fontDefs_80086574[2] = {
    { 0, 16, 0, 6, 6, 0x380, 0x133 },
    { 19, 16, 0, 8, 8, 0x300, 0x106, 0, 0, 112 },
};
int fontDef2_800865A4[5] = { 0x120012, 0xE0000, 0x300000E, 0x102 };
int font2CharCodes_800865B8[169] = {
    126, 0x45814981, 0x50824481, 0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x40814081,
    0x40814081, 0x66814381, 0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x40814081,
    0x40814081, 0x69816882, 0x40816A81, 0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x40814081,
    0x40814081, 0x61826082, 0x63826282, 0x65826482, 0x67826682, 0x6A826982, 0x6D826B82, 0x6F826E82,
    0x71827082, 0x74827282, 0x79827582, 0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x40814081,
    0x40814081, 0x51824F82, 0x53825282, 0x55825482, 0x57825682, 0x48815882, 0x60815B81, 0x40814081,
    0x40814081, 0x73826C82, 0x77827682, 0xF4817882, 0x5E819781, 0x40814081, 0x40814081, 0x40814081,
    0x40814081, 0x82828182, 0x84828382, 0x86828582, 0x88828782, 0x8A828982, 0x8C828B82, 0x8E828D82,
    0x90828F82, 0x92829182, 0x94829382, 0x96829582, 0x98829782, 0x9A829982, 0, 0x49814081,
    0x45814381, 0x66814481, 0x47814681, 0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x40814081,
    0x86826882, 0x8A828982, 0x50829482, 0x6A816981, 0x40818C82, 0x40814081, 0x40814081, 0x40814081,
    0x40814081, 0x85828382, 0x8F828782, 0x93829282, 0x9A829882, 0x54825282, 0x56825582, 0x58825782,
    0x40814881, 0x40814081, 0x81826982, 0x84828282, 0x8B828882, 0x90828E82, 0x95829182, 0x53825182,
    0x5B814F82, 0x81814F81, 0x40814081, 0x62826182, 0x64826382, 0x66826582, 0x6E826B82, 0x70826F82,
    0x8D827282, 0x97829682, 0x94819982, 0x7C817B81, 0x6A826782, 0x71826D82, 0x79827482, 0x40819781,
    0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x40814081, 0x6C826082, 0x75827382, 0x78827782,
    0x76826081, 0x9B81A08C, 0xA2817E81, 0x9581A081, 0x40814081, 0x40814081, 0xB881BE81, 0xBA81B981,
    0xBC81BB81, 0xBF83BD81, 0x4087C083, 0x42874187, 0x44874387, 0x87878887, 0x87818587, 0x55875487,
    0x57875687, 0x59875887, 0x5B875A87, 0x5D875C87, 0x5F875E87, 0x61876087, 0x63876287, 0x65876487,
    0x67876687, 0x69876887, 0x6B876A87, 0x6D876C87, 0x6F876E87, 0x71877087, 0x73877287, 0x75877487,
    0x77877687, 0x79877887, 0x7B877A87, 0x7D877C87, 0x7F877E87, 0x81878087, 0x83878287, 0xF0818487,
    0xF181,
};
