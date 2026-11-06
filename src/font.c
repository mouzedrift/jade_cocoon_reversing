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
#include "pad_text.h"
#include "font.h"
#include "util.h"

extern int charWidthThresholds_80086898[][12];


int GetCharWidth_8003E884(int idx, short c)
{
    Font* font = &fonts_80095FB0[idx];
    short k = 12;
    int width = font->w_10;
    int code = c - 1;
    for (; k != 0; k--)
    {
        if (code < charWidthThresholds_80086898[idx - 1][k - 1])
        {
            width -= k;
            break;
        }
    }
    return width;
}
void DrawText_8003E91C(int idx, const char* str, short* pos, int ot)
{
    Font* font = &fonts_80095FB0[idx];
    short x = pos[0];
    short y = pos[1];
    unsigned short* codes;
    unsigned short c;
    short k;
    int row;
    int col;

    codes = EncodeText_8003F684(idx, (unsigned short*)str);
    c = *codes;
    while (c != 0)
    {
        codes++;
        if (c <= charTables_8008685C[idx].lastChar_4)
        {
            for (k = 12; k > 0; k--)
            {
                if (c - 1 < charWidthThresholds_80086898[idx - 1][k - 1])
                {
                    break;
                }
            }
            c = c - 1;
            row = (short)(c % (unsigned short)font->charsPerClut_28);
            c = c / (unsigned short)font->charsPerClut_28;
            col = row % (unsigned short)font->columns_1C;
            row = row / (unsigned short)font->columns_1C;
            font->x0_8 = x;
            font->y0_A = y;
            font->clut_E = getClut(font->clutX_20, font->clutOffset_2A + (font->clutY_22 + c));
            font->u_C = font->u0_18 + font->w_10 * col;
            font->v_D = font->v0_1A + font->h_12 * row;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)font)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)font)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)font)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
            x -= k;
        }
        x += font->w_10;
        c = *codes;
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
void DrawColorText_8003EC2C(unsigned short* str, unsigned short* pos, int ot)
{
    Font* font = &fonts_80095FB0[2];
    short x = pos[0];
    short y = pos[1];
    unsigned short* codes;
    unsigned short c;
    short k;
    int row;
    int col;

    codes = EncodeText_8003F684(2, str);
    c = *codes;
    while (c != 0)
    {
        codes++;
        if (c <= charTables_8008685C[2].lastChar_4)
        {
            for (k = 12; k > 0; k--)
            {
                if (c - 1 < charWidthThresholds_80086898[1][k - 1])
                {
                    break;
                }
            }
            c = c - 1;
            row = (short)(c % (unsigned short)font->charsPerClut_28);
            c = c / (unsigned short)font->charsPerClut_28;
            col = row % (unsigned short)font->columns_1C;
            row = row / (unsigned short)font->columns_1C;
            font->x0_8 = x;
            font->y0_A = y;
            font->clut_E = getClut(font->clutX_20, font->clutOffset_2A + (font->clutY_22 + c));
            font->u_C = font->u0_18 + font->w_10 * col;
            font->v_D = font->v0_1A + font->h_12 * row;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)font)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)font)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)font)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
            x = font->w_10 + (x - k);
        }
        else
        {
            switch (c)
            {
            case 0x81:
                SetFontClutOffset_8003F900(2, 3);
                break;
            case 0x7f:
                SetFontClutOffset_8003F900(2, 0);
                break;
            case 0x80:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x85:
                SetFontClutOffset_8003F900(2, c - 0x7f);
                break;
            }
        }
        c = *codes;
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}

CharTable charTables_8008685C[1] = { { 0 } };
void *dword_80086868[1] = { (void *)((char *)&font2CharCodes_800865B8 + 4) };
