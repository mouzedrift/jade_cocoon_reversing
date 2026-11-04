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

extern int charWidthThresholds_80086898[][12];


// Matched
int GetCharWidth_8003E884(int idx, short n)
{
    Font* p = &fonts_80095FB0[idx];
    short k = 12;
    int r = p->w_10;
    int v = n - 1;
    for (; k != 0; k--)
    {
        if (v < charWidthThresholds_80086898[idx - 1][k - 1])
        {
            r -= k;
            break;
        }
    }
    return r;
}
typedef struct
{
    unsigned short* tbl;
    int field_4;
    int count;
} CharTable_8003E91C;
extern CharTable_8003E91C charTables_8008685C[];
// Matched
void DrawText_8003E91C(int idx, unsigned short* str, short* pos, int ot)
{
    Font* p = &fonts_80095FB0[idx];
    short x = pos[0];
    short y = pos[1];
    unsigned short* s;
    unsigned short c;
    short k;
    int v;
    int col;

    s = EncodeText_8003F684(idx, str);
    c = *s;
    while (c != 0)
    {
        s++;
        if (c <= charTables_8008685C[idx].field_4)
        {
            for (k = 12; k > 0; k--)
            {
                if (c - 1 < charWidthThresholds_80086898[idx - 1][k - 1])
                {
                    break;
                }
            }
            c = c - 1;
            v = (short)(c % (unsigned short)p->field_28);
            c = c / (unsigned short)p->field_28;
            col = v % (unsigned short)p->field_1C;
            v = v / (unsigned short)p->field_1C;
            p->x0_8 = x;
            p->y0_A = y;
            p->clut_E = getClut(p->clutX_20, p->field_2A + (p->clutY_22 + c));
            p->u_C = p->field_18 + p->w_10 * col;
            p->v_D = p->field_1A + p->h_12 * v;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)p)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)p)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)p)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
            x -= k;
        }
        x += p->w_10;
        c = *s;
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
// Matched
void DrawColorText_8003EC2C(unsigned short* str, unsigned short* pos, int ot)
{
    Font* p = &fonts_80095FB0[2];
    short x = pos[0];
    short y = pos[1];
    unsigned short* s;
    unsigned short c;
    short k;
    int v;
    int col;

    s = EncodeText_8003F684(2, str);
    c = *s;
    while (c != 0)
    {
        s++;
        if (c <= charTables_8008685C[2].field_4)
        {
            for (k = 12; k > 0; k--)
            {
                if (c - 1 < charWidthThresholds_80086898[1][k - 1])
                {
                    break;
                }
            }
            c = c - 1;
            v = (short)(c % (unsigned short)p->field_28);
            c = c / (unsigned short)p->field_28;
            col = v % (unsigned short)p->field_1C;
            v = v / (unsigned short)p->field_1C;
            p->x0_8 = x;
            p->y0_A = y;
            p->clut_E = getClut(p->clutX_20, p->field_2A + (p->clutY_22 + c));
            p->u_C = p->field_18 + p->w_10 * col;
            p->v_D = p->field_1A + p->h_12 * v;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)p)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)p)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)p)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
            x = p->w_10 + (x - k);
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
        c = *s;
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}

CharTable_8003E91C charTables_8008685C[1] = { { 0 } };
void *dword_80086868[1] = { (void *)((char *)&font2CharCodes_800865B8 + 4) };
