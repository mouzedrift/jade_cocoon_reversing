#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "tiy.h"
#include "effect_data.h"
#include "util.h"
#include "unit_query.h"
#include "ui_sprites.h"
#include "ui_gauge.h"

const CVECTOR colorGrey_800741E4 = { 128, 128, 128 };
const CVECTOR colorWhite_800741E8 = { 255, 255, 255 };

extern int elementIcons_800827BC[];
void DrawElementIcons_8002B2A4(short mask, short* base, int ot, short (*offsets)[2], int showUnlit)
{
    short pos[2];
    int i;
    int icon;
    for (i = 0; i < 4; i++)
    {
        pos[0] = base[0] + offsets[i][0];
        pos[1] = base[1] + offsets[i][1];
        if (mask == 0)
        {
            icon = elementIconsUnlit_800827D0[4];
        }
        else if ((mask >> i) & 1)
        {
            icon = elementIcons_800827BC[i];
        }
        else if (showUnlit == 0)
        {
            icon = elementIconsUnlit_800827D0[4];
        }
        else
        {
            icon = elementIconsUnlit_800827D0[i];
        }
        SetShadeTex(uiTiySprts_8008D620 + icon, 1);
        DrawUiTiySprt_8002C06C(pos, icon, ot);
    }
}
extern const CVECTOR colorGrey_800741E4;
extern const CVECTOR colorWhite_800741E8;
void DrawScrollArrow_8002B3DC(ScrollArrow arrow, int time, short* pos, int ot)
{
    CVECTOR c0;
    CVECTOR c1;
    short idx;
    int ang;
    int nx;
    int ny;
    c0 = colorGrey_800741E4;
    c1 = colorWhite_800741E8;
    ang = arrow.dir << 10;
    idx = scrollArrowIcons_8008279C[(short)saveData_8008B570.uiColor_20.i * 3 + arrow.kind];
    publicTiyPolyFT4s_8008D430[idx].x0 = 1 - publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y0 = 1 - publicTiySprts_8008D434[idx].h / 2;
    publicTiyPolyFT4s_8008D430[idx].x1 = publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y1 = 1 - publicTiySprts_8008D434[idx].h / 2;
    publicTiyPolyFT4s_8008D430[idx].x2 = 1 - publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y2 = publicTiySprts_8008D434[idx].h / 2;
    publicTiyPolyFT4s_8008D430[idx].x3 = publicTiySprts_8008D434[idx].w / 2;
    publicTiyPolyFT4s_8008D430[idx].y3 = publicTiySprts_8008D434[idx].h / 2;
    nx = publicTiyPolyFT4s_8008D430[idx].x0 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - publicTiyPolyFT4s_8008D430[idx].y0 * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = publicTiyPolyFT4s_8008D430[idx].x0 * sinTable_80084540[ang & 0xFFF] / 4096 + publicTiyPolyFT4s_8008D430[idx].y0 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x0 = pos[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y0 = pos[1] + ny;
    nx = publicTiyPolyFT4s_8008D430[idx].x1 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - publicTiyPolyFT4s_8008D430[idx].y1 * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = publicTiyPolyFT4s_8008D430[idx].x1 * sinTable_80084540[ang & 0xFFF] / 4096 + publicTiyPolyFT4s_8008D430[idx].y1 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x1 = pos[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y1 = pos[1] + ny;
    nx = publicTiyPolyFT4s_8008D430[idx].x2 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - publicTiyPolyFT4s_8008D430[idx].y2 * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = publicTiyPolyFT4s_8008D430[idx].x2 * sinTable_80084540[ang & 0xFFF] / 4096 + publicTiyPolyFT4s_8008D430[idx].y2 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x2 = pos[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y2 = pos[1] + ny;
    nx = publicTiyPolyFT4s_8008D430[idx].x3 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096 - publicTiyPolyFT4s_8008D430[idx].y3 * sinTable_80084540[ang & 0xFFF] / 4096;
    ny = publicTiyPolyFT4s_8008D430[idx].x3 * sinTable_80084540[ang & 0xFFF] / 4096 + publicTiyPolyFT4s_8008D430[idx].y3 * sinTable_80084540[(ang + 0x400) & 0xFFF] / 4096;
    publicTiyPolyFT4s_8008D430[idx].x3 = pos[0] + nx;
    publicTiyPolyFT4s_8008D430[idx].y3 = pos[1] + ny;
    setShadeTex(&publicTiyPolyFT4s_8008D430[idx], 0);
    PulseColor_80033394((unsigned char*)&publicTiyPolyFT4s_8008D430[idx].r0, (unsigned char*)&c0, (unsigned char*)&c1, time, 0x28, 0xA);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &publicTiyPolyFT4s_8008D430[idx], sizeof(publicTiyPolyFT4s_8008D430[idx]) / 4);
    AddPrimCopy_80040298(&pOT_8008D454[ot], &publicTiyTPages_8008D440[idx], sizeof(publicTiyTPages_8008D440[idx]) / 4);
}
void DrawScrollArrows_8002B8DC(ScrollArrow arrow, short* list, short* pos, int ot)
{
    switch (arrow.dir)
    {
    case 0:
    case 2:
        if (list[5] > 0)
        {
            arrow.dir = 0;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos, ot);
        }
        if (list[0] * list[1] + list[5] < (unsigned short)list[2])
        {
            arrow.dir = 2;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos + 2, ot);
        }
        break;
    case 1:
    case 3:
        if (list[5] > 0)
        {
            arrow.dir = 3;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos, ot);
        }
        if (list[0] * list[1] + list[5] < (unsigned short)list[2])
        {
            arrow.dir = 1;
            DrawScrollArrow_8002B3DC(arrow, GetTime30Hz_8002C64C(), pos + 2, ot);
        }
        break;
    }
}
void DrawGauge_8002BA54(Gauge* gauge, int time, short* origin, int ot)
{
    short pos[2];
    int idx;
    int pulseTime;
    int length;
    int frameIcon;
    int width;
    int deltaWidth;
    int delta;
    int absDelta;
    idx = 2;
    pulseTime = time;
    length = 0x2F;
    frameIcon = 0x69;
    switch ((unsigned int)gauge->state)
    {
    case 0:
        if (gauge->cur_8 < gauge->max_C / 4)
        {
            idx = 0x42;
        }
        else
        {
            idx = 2;
            pulseTime = 0;
        }
        length = 0x57;
        frameIcon = 0x6A;
        break;
    case 1:
        if (gauge->cur_8 < gauge->max_C / 4)
        {
            idx = 0x42;
        }
        else
        {
            idx = 2;
            pulseTime = 0;
        }
        break;
    case 2:
        idx = 0x14;
        break;
    }
    width = ScaleGaugeLength_8002BC60(gauge->cur_8, gauge->max_C, length);
    delta = gauge->delta_4;
    if (delta)
    {
        if (delta < 0)
        {
            pos[0] = origin[0] + 8;
            pos[1] = origin[1] + 2;
            absDelta = -delta;
        }
        else
        {
            pos[0] = (short)(origin[0] + 8) + width;
            pos[1] = origin[1] + 2;
            absDelta = delta;
        }
        if (gauge->max_C < gauge->cur_8 + gauge->delta_4)
        {
#ifdef __psyz /* the original's rest of the bar is in points, not pixels: a heal past the maximum blinks a bar many
                 times too long (up to the 512 pixel clamp); on PC it is scaled like the bar */
            deltaWidth = ScaleGaugeLength_8002BC60(gauge->max_C - gauge->cur_8, gauge->max_C, length);
#else
            deltaWidth = gauge->max_C - gauge->cur_8;
#endif
        }
        else
        {
            deltaWidth = ScaleGaugeLength_8002BC60(absDelta, gauge->max_C, length);
        }
        if (frameCount_8008D3FC & 0x10)
        {
            DrawGaugeBar_8002BCAC(0x14, deltaWidth, pos, pulseTime, ot);
        }
    }
    pos[0] = origin[0] + 8;
    pos[1] = origin[1] + 2;
    DrawGaugeBar_8002BCAC(idx, width, pos, pulseTime, ot);
    DrawUiTiySprt_8002C06C(origin, frameIcon, ot);
}
unsigned int ScaleGaugeLength_8002BC60(unsigned int value, unsigned int max, unsigned int length)
{
    if (max < value)
    {
        value = max;
    }
    if (value)
    {
        value = value * length / max;
        if (value == 0)
        {
            return 1;
        }
        return value;
    }
    return 0;
}
extern const CVECTOR colorWhite_800741E8;
void DrawGaugeBar_8002BCAC(int idx, int scale, short* pos, unsigned int time, int ot)
{
    POLY_FT4 poly;
    CVECTOR c0;
    CVECTOR c1;
    if (scale)
    {
        c0 = colorWhite_800741E8;
        c1 = colorWhite_800741E8;
        setPolyFT4(&poly);
        poly.code = publicTiyPolyFT4s_8008D430[idx].code;
        poly.clut = publicTiyPolyFT4s_8008D430[idx].clut;
        poly.tpage = publicTiyPolyFT4s_8008D430[idx].tpage;
        poly.u0 = publicTiyPolyFT4s_8008D430[idx].u0;
        poly.v0 = publicTiyPolyFT4s_8008D430[idx].v0;
        poly.u1 = publicTiyPolyFT4s_8008D430[idx].u1;
        poly.v1 = publicTiyPolyFT4s_8008D430[idx].v1;
        poly.u2 = publicTiyPolyFT4s_8008D430[idx].u2;
        poly.v2 = publicTiyPolyFT4s_8008D430[idx].v2;
        poly.u3 = publicTiyPolyFT4s_8008D430[idx].u3;
        poly.v3 = publicTiyPolyFT4s_8008D430[idx].v3;
        setShadeTex(&poly, 0);
#ifdef __psyz
        // temp hack fix to prevent hp bars from being too wide on the pc version (root cause unknown)
        scale *= 256;
#else
        scale *= 512;
#endif
        PulseColor_80033394(&poly.r0, (unsigned char*)&c0, (unsigned char*)&c1, time, 40, 10);
        AddScaledPolyFT4_80031BE4(&poly, pOT_8008D454 + ot, pos[0], pos[1], scale, 0x100, 0, 0x11);
    }
}
