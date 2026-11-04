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

const CVECTOR dword_80074BA0 = { 128, 128, 128 };

// Matched
int sub_80041E68(int mode, int a, int b, int c)
{
    switch (mode)
    {
    case 0:
        return a;
    case 1:
        return a + c;
    case 2:
        return a - c + b;
    case 3:
        return a + b;
    }
    return -1;
}
extern const CVECTOR dword_80074BA0;
extern int byte_80086F9C[];
extern int dword_80087070[][8];
// Matched
void DrawWindowFrame_80041ED0(RECT* r, unsigned char* rgb, u_long* ot, unsigned char semi)
{
    POLY_F4 p[5];
    DR_TPAGE dm;
    CVECTOR col = dword_80074BA0;
    int abe;
    int i;
    int cr;
    int cg;
    int cb;

    if (semi)
    {
        abe = 1;
        semi = semi - 1;
    }
    else
    {
        abe = 0;
        semi = 0;
    }
    for (i = 0; i < 5; i++)
    {
        setPolyF4(&p[i]);
        setSemiTrans(&p[i], abe);
        if (rgb)
        {
            cr = rgb[0] * byte_80086F9C[i] / 100;
            cg = rgb[1] * byte_80086F9C[i] / 100;
            cb = rgb[2] * byte_80086F9C[i] / 100;
            if (cr > 255)
            {
                cr = 255;
            }
            if (cg > 255)
            {
                cg = 255;
            }
            if (cb > 255)
            {
                cb = 255;
            }
            if (cr < 0)
            {
                cr = 0;
            }
            if (cg < 0)
            {
                cg = 0;
            }
            if (cb < 0)
            {
                cb = 0;
            }
            col.r = cr;
            col.g = cg;
            col.b = cb;
        }
        setRGB0(&p[i], col.r, col.g, col.b);
        p[i].x0 = sub_80041E68(dword_80087070[i][0], r->x, r->w, 2);
        p[i].y0 = sub_80041E68(dword_80087070[i][1], r->y, r->h, 2);
        p[i].x1 = sub_80041E68(dword_80087070[i][2], r->x, r->w, 2);
        p[i].y1 = sub_80041E68(dword_80087070[i][3], r->y, r->h, 2);
        p[i].x2 = sub_80041E68(dword_80087070[i][4], r->x, r->w, 2);
        p[i].y2 = sub_80041E68(dword_80087070[i][5], r->y, r->h, 2);
        p[i].x3 = sub_80041E68(dword_80087070[i][6], r->x, r->w, 2);
        p[i].y3 = sub_80041E68(dword_80087070[i][7], r->y, r->h, 2);
        AddPrimCopy_80040298(ot, &p[i], 6);
    }
    setDrawTPage(&dm, 0, 0, GetTPage(0, semi, 0, 0));
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)&dm)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)&dm)[1];
    addPrim(ot, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}

INCLUDE_DATA(byte_80086F9C);
