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
#include "util.h"
#include "unit_query.h"
#include "sound_seq.h"
#include "font.h"

extern unsigned short padPressed_8009194C[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padRepeat_800918CC[];

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
    int pressed = 0;
    unsigned int buttons;
    if ((padPressed_8009194C[pad] & 0x40) && !(padHeld_800918D0[pad] & 4) && !(padReleased_800918D4[pad] & 4))
    {
        goto done;
    }
    buttons = padPressed_8009194C[pad];
    if (!(buttons & 4))
    {
        goto end;
    }
    if ((padHeld_800918D0[pad] & 0x40) || (padReleased_800918D4[pad] & 0x40))
    {
        if (!(buttons & 0x40))
        {
            goto end;
        }
    }
done:
    if (playSfx)
    {
        PlaySfx_80031494(0x7E);
    }
    pressed = 1;
end:
    return pressed;
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
    int pressed = 0;
    unsigned short buttons = padPressed_8009194C[pad];
    if ((buttons & 0x10) || (buttons & 1))
    {
        if (playSfx)
        {
            PlaySfx_80031494(0x7D);
        }
        pressed = 1;
    }
    return pressed;
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
    unsigned int held = padHeld_800918D0[idx] & 0x20;
    return held != 0;
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
int MoveGridCursor_8003D4C0(short* grid, int idx)
{
    int result = 1;
    if (grid[4] < 0)
    {
        grid[4] = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (grid[4] % grid[0] == grid[0] - 1)
        {
            result |= 2;
        }
        else
        {
            grid[4]++;
        }
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (grid[4] % grid[0] == 0)
        {
            result |= 4;
        }
        else
        {
            grid[4]--;
        }
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (grid[4] < grid[0])
        {
            result |= 8;
        }
        else
        {
            grid[4] -= grid[0];
        }
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (grid[4] > grid[0] * (grid[1] - 1) - 1)
        {
            result |= 0x10;
        }
        else
        {
            grid[4] += grid[0];
        }
    }
    return result;
}
// Matched
int MoveGridCursorP1_8003D630(GridCursor* grid)
{
    int idx = 0;
    if (grid->pos_6 < 0)
    {
        grid->pos_6 = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (grid->pos_6 % grid->cols_8 == grid->cols_8 - 1)
        {
            return 1;
        }
        grid->pos_6++;
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (grid->pos_6 % grid->cols_8 == 0)
        {
            return 2;
        }
        grid->pos_6--;
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (grid->pos_6 < grid->cols_8)
        {
            return 3;
        }
        grid->pos_6 -= grid->cols_8;
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (grid->pos_6 > grid->cols_8 * (grid->rows_A - 1) - 1)
        {
            return 4;
        }
        grid->pos_6 = grid->pos_6 + grid->cols_8;
    }
    return 0;
}

// Matched
int UpdateMenuCursor_8003D794(MenuCursor* menu, int pad)
{
    unsigned short prevCursor = menu->cursor_8;
    unsigned short prevScroll = menu->scroll_A;
    int result = MenuCursorInput_8003D830(menu, pad);
    if (result == 0)
    {
        int last = menu->count_4 - 1;
        if (last < menu->cursor_8)
        {
            menu->cursor_8 = last;
        }
    }
    if ((short)prevCursor != menu->cursor_8 || (short)prevScroll != menu->scroll_A)
    {
        PlaySfx_80031494(0x7F);
    }
    return result;
}
// Matched
int MenuCursorInput_8003D830(MenuCursor* menu, int idx)
{
    int moved = MoveGridCursor_8003D4C0((short*)menu, idx);
    int wrapX;
    int wrapY;

    if (menu->flags_6 & 0x40)
    {
        if (moved & 8)
        {
            if (menu->scroll_A >= menu->columns_0)
            {
                menu->scroll_A -= menu->columns_0;
                return 8;
            }
        }
        else if (moved & 0x10)
        {
            if (menu->scroll_A < menu->count_4 - menu->columns_0 * menu->rows_2)
            {
                menu->scroll_A += menu->columns_0;
                return 7;
            }
        }
    }
    if (menu->flags_6 & 1)
    {
        if (moved & 2)
        {
            wrapX = menu->columns_0 - 1;
            menu->cursor_8 -= wrapX;
        }
        if (moved & 4)
        {
            menu->cursor_8 += menu->columns_0 - 1;
        }
    }
    if (menu->flags_6 & 2)
    {
        if (moved & 8)
        {
            menu->cursor_8 += menu->columns_0 * (menu->rows_2 - 1);
        }
        if (moved & 0x10)
        {
            wrapY = menu->columns_0 - menu->rows_2 * menu->columns_0;
            menu->cursor_8 += wrapY;
        }
    }
    if ((menu->flags_6 & 4) && (moved & 2))
    {
        return 1;
    }
    if ((menu->flags_6 & 8) && (moved & 4))
    {
        return 2;
    }
    if ((menu->flags_6 & 0x10) && (moved & 8))
    {
        return 3;
    }
    if ((menu->flags_6 & 0x20) && (moved & 0x10))
    {
        return 4;
    }
    if (menu->flags_6 & 0x40)
    {
        menu->scroll_A = AdjustByShoulderButtons_8003D198(menu->count_4 - menu->columns_0 * menu->rows_2 + 1, menu->scroll_A, menu->columns_0 * menu->rows_2, 0);
    }
    return 0;
}
// Matched
int GetMenuCursorIndex_8003DA54(MenuCursor* menu)
{
    return (short)(menu->cursor_8 + menu->scroll_A);
}
typedef struct
{
    unsigned short sprite_0; // publicTiySprts_8008D434 index
    unsigned short columns_2;
    unsigned short firstChar_4;
    unsigned short w_6;
    unsigned short h_8;
    unsigned short clutX_A;
    unsigned short clutY_C;
    unsigned short pad_E;
    unsigned char* widths_10;
    unsigned short pageGlyphs_14; // glyphs per clut row
    unsigned short pad_16;
} FontDef;
extern FontDef fontDefs_80086574[];
// Matched
void InitFonts_8003DA70(void)
{
    int i;
    FontDef* def;
    Font* font;
    for (i = 0; i < 3; i++)
    {
        def = &fontDefs_80086574[i];
        font = &fonts_80095FB0[i];
        MemCopy_800403E8(font, &publicTiySprts_8008D434[def->sprite_0], 0x14);
        font->w_10 = def->w_6;
        font->h_12 = def->h_8;
        font->tpage_14 = (unsigned short*)&publicTiyTPages_8008D440[def->sprite_0];
        font->u0_18 = font->u_C;
        font->v0_1A = font->v_D;
        font->firstChar_1E = def->firstChar_4;
        font->clutX_20 = def->clutX_A;
        font->clutY_22 = def->clutY_C;
        font->widths_24 = def->widths_10;
        font->columns_1C = def->columns_2;
        font->charsPerClut_28 = def->pageGlyphs_14;
        font->clutOffset_2A = 0;
    }
}
// Matched
int UpdateTextWindow_8003DB74(TextWindow* w, int draw)
{
    if (w->timer_24 >= 3 - (settingsFlags_8008B58C.word & 7))
    {
        w->timer_24 = 0;
        w->limit_1C++;
    }
    if (w->field_14 == 0)
    {
        w->limit_1C = 0x0FFFFFFF;
    }
    w->shown_20 = w->limit_1C;
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    DrawTextWindow_8003DCA4(draw, w);
    AddDrawAreaPrim_8003326C(&w->clip_4, pOT_8008D454);
    switch (w->state_28)
    {
    case 1:
        if (w->field_18 == 1 && ((padHeld_800918D0[0] & 0x60F) || (padPressed_8009194C[0] & 0xF0)))
        {
            w->limit_1C = 0x0FFFFFFF;
        }
        else
        {
            w->timer_24++;
        }
        break;
    case 10:
        return 1;
    }
    return 0;
}
extern int charWidthThresholds_80086898[][12];
// Matched
void DrawTextWindow_8003DCA4(int draw, TextWindow* w)
{
    unsigned short num[12];
    TextBuf22 name;
    int limit;
    int count;
    int y;
    Font* font;
    unsigned short* text;
    unsigned short* sub;
    int* lines;
    int nl;
    int x;
    int ci;
    unsigned short ch;
    short k;
    int i;
    int cell;
    int col;

    sub = emptyText_80074994;
    count = 0;
    name = emptyNameBuf_80074998;
    x = w->x_0;
    y = w->y_2;
    font = &fonts_80095FB0[2];
    lines = w->lines_C;
    limit = w->limit_1C;
    nl = 0;
    while (*lines != 0)
    {
        text = EncodeText_8003F684(2, (unsigned short*)*lines++);
        while (*text != 0 || *sub != 0)
        {
            if (count >= limit)
            {
                goto done;
            }
            if (*sub != 0)
            {
                ch = *sub++;
            }
            else
            {
                ch = *text++;
            }
            ci = ch;
            if (ch < 0x7F)
            {
                if (draw)
                {
                    font->clut_E = GetClut(font->clutX_20, font->clutY_22 + (ci - 1) / (unsigned short)font->charsPerClut_28 + (unsigned short)font->clutOffset_2A);
                    cell = (ci - 1) % (unsigned short)font->charsPerClut_28;
                    col = cell % (unsigned short)font->columns_1C;
                    cell = cell / (unsigned short)font->columns_1C;
                    font->x0_8 = x;
                    font->y0_A = y;
                    font->u_C = font->u0_18 + font->w_10 * col;
                    font->v_D = font->v0_1A + font->h_12 * cell;
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font)[0];
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font)[1];
                    count++;
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)font)[2];
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)font)[3];
                    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)font)[4];
                    addPrim(&pOT_8008D454[w->ot_10], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
                    for (k = 12; k != 0; k--)
                    {
                        if (ci - 1 < charWidthThresholds_80086898[1][k - 1])
                        {
                            x -= k;
                            break;
                        }
                    }
                    x += font->w_10;
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
                    SetFontClutOffset_8003F900(2, ch - 0x7F);
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
                    IntToText_8003F610(num, textNumberArgs_80096038[ch - 0x88]);
                    sub = EncodeText_8003F684(2, num);
                    break;
                case 0xC1:
                case 0xC2:
                    nl = 1;
                    break;
                case 0x91 ... 0xC0:
                    {
                        for (i = 0; i < (int)(ch - 0x91); i++)
                        {
                            w->marks_2C[i] = -2;
                        }
                        if (w->marks_2C[ch - 0x91] == -1)
                        {
                            w->marks_2C[ch - 0x91] = ch - 0x91;
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
            x = w->x_0;
            y += 12;
        }
    }
    w->state_28 = 10;
done:
    if (draw)
    {
        SetFontClutOffset_8003F900(2, 0);
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font->tpage_14)[0];
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font->tpage_14)[1];
        addPrim(&pOT_8008D454[w->ot_10], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
    }
}
// Matched
void DrawMsgWindowNextPrompt_8003E268(unsigned short* pos)
{
    short x = pos[0] + 0xC3;
    short y = pos[1] + 0x23;
    DrawNextPrompt_8003CF88(x, y, 0);
}
// Matched
TextSize MeasureTextLinesMasked_8003E2A8(int* list, unsigned int mask)
{
    TextSize size;
    short width;
    int i;
    size.w = 0;
    size.h = 0;
    for (i = 0; list[i]; i++)
    {
        if (mask & (1 << i))
        {
            width = MeasureTextWidth_8003E4C8(list[size.h]);
            if (size.w < width)
            {
                size.w = width;
            }
            size.h++;
        }
    }
    size.h *= 12;
    return size;
}
typedef struct
{
    short w;
    short h;
} Size2;

// Matched
TextSize MeasureTextLines_8003E3B4(int* list)
{
    TextSize size;
    short width;
    int i;
    size.w = 0;
    size.h = 0;
    for (i = 0; list[i]; i++)
    {
        if (!IsTextMarkerLine_8003E484(list[i]))
        {
            width = MeasureTextWidth_8003E4C8(list[i]);
            if (size.w < width)
            {
                size.w = width;
            }
            size.h++;
        }
    }
    size.h *= 12;
    return size;
}
// Matched
int IsTextMarkerLine_8003E484(int text)
{
    int ch = *EncodeText_8003F684(2, (unsigned short*)text);
    if (ch < 0xC3)
    {
        if (ch >= 0x91)
        {
            return 1;
        }
    }
    return 0;
}
// Matched
int MeasureTextWidth_8003E4C8(const char* str)
{
    unsigned short num[12];
    TextBuf22 name;
    unsigned short* text;
    unsigned short* sub;
    short width;
    int k;
    unsigned short ch;

    sub = emptyText_80074994;
    width = 0;
    name = emptyNameBuf_80074998;
    k = -1;
    text = EncodeText_8003F684(2, (unsigned short*)str);
    while (*text != 0 || *sub != 0)
    {
        if (*sub != 0 && sub != NULL)
        {
            ch = *sub++;
        }
        else
        {
            ch = *text++;
        }
        if (ch < 0x7F)
        {
            width += GetCharWidth_8003E884(2, (short)ch);
        }
        else
        {
            switch (ch)
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
                width += 14;
                break;
            }
        }
    }
    return width;
}
// Matched
int MeasureTextWidthFont1_8003E6B0(int str)
{
    unsigned short num[12];
    TextBuf22 name;
    unsigned short* text;
    unsigned short* sub;
    short width;
    int k;
    unsigned short ch;

    sub = emptyText_80074994;
    width = 0;
    name = emptyNameBuf_80074998;
    k = -1;
    text = EncodeText_8003F684(1, (unsigned short*)str);
    while (*text != 0 || *sub != 0)
    {
        if (*sub != 0 && sub != NULL)
        {
            ch = *sub++;
        }
        else
        {
            ch = *text++;
        }
        if (ch < 0x71)
        {
            width += GetCharWidth_8003E884(1, (short)ch);
        }
        else
        {
            switch (ch)
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
    return width;
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
