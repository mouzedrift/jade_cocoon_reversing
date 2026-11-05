#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "model.h"
#include "main.h"
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
#include "camera.h"
#include "tim.h"
#include "model_ftg.h"
#include "util.h"


extern int mapHasCode_8008266C;
extern int dword_80091C5C;
extern int dword_80091C8C;
extern void (*mapCallback_80091CB4)(int);
extern int mapJustLoaded_80082668;
// Matched
void OnRoomDataLoaded_80028C60(int req, char* data)
{
    int n;
    char* p;
    MemCopy_800403E8(&cameraState_8008D4F0, data, sizeof(CameraView));
    p = data;
    data += 0x108;
    n = *(int*)(p + 0x104);
    LoadTiy_80028E74(0, 0, 0, (int*)data, (int)&areaHeap_80091C20);
    data += n;
    n = *(int*)data;
    data += 4;
    if (areaReload_80082670 == 0)
    {
        LoadTileSets_80027778(data, &areaHeap_80091C20);
    }
    data += n;
    n = *(int*)data;
    data += 4;
    if (areaReload_80082670 == 0)
    {
        LoadTileAnimLayers_800278BC(data, &areaHeap_80091C20);
    }
    data += n;
    if (areaReload_80082670 == 1)
    {
        p = data + 4;
        LoadTiy_80028E74(0, 0, 0, (int*)p, (int)&mapHeap_80091C68);
    }
    SetCurrentArea_800272BC(mapState_8008B500.id_0, pendingArea_8008B860);
    if (mapJustLoaded_80082668 && mapHasCode_8008266C && dword_80091C5C && dword_80091C8C == 0 && mapCallback_80091CB4)
    {
        mapCallback_80091CB4(1);
    }
}
extern short screenOffset_8008D474[2];
// Matched
void InitRoomCamera_80028DC0(void)
{
    CameraCtrl* cam;
    if (areaReload_80082670 == 0)
    {
        cam = cameraTask_8008D4A0->entry.buffer;
        if (mapJustLoaded_80082668)
        {
            SetCameraTarget_80037AC8((int)&levantPos_8008BD18);
        }
        UpdateCameraFollow_80037918(cam);
        SetGeomOffset(display_8008B4D8.w_C / 2 + screenOffset_8008D474[0], display_8008B4D8.h_E / 2 + screenOffset_8008D474[1]);
    }
}
// Matched
int GetTiyFileCount_80028E68(int* file)
{
    return file[0];
}
// Matched
void LoadTiy_80028E74(SPRT** sprts, POLY_FT4** polys, DR_TPAGE** tpages, int* file, int heap)
{
    int count = *file;
    AllocTiyPrims_800295D8(sprts, polys, tpages, count, heap);
    LoadTiyTims_80028EEC(sprts, polys, tpages, file, count);
}
// Matched
void LoadTiyTims_80028EEC(SPRT** sprts, POLY_FT4** polys, DR_TPAGE** tpages, int* file, int count)
{
    TimInfo buf;
    unsigned int i;
    for (i = 0; i < (unsigned int)count; i++)
    {
        ParseTim_80029708(&buf, (char*)file + file[i + 1]);
        LoadTimToVram_800296A0(&buf);
        if (sprts && tpages)
        {
            InitSprtFromTim_800298AC(&(*sprts)[i], &(*tpages)[i], &buf);
        }
        if (polys)
        {
            InitPolyFT4_80029A10(&(*polys)[i], &buf);
        }
    }
}
// Matched
void LoadTiyTimsRelocated_80028FDC(int sprts, int polys, int tpages, int file, int count, int reloc, int hue)
{
    TimInfo buf;
    unsigned int i;
    for (i = 0; i < count; i++)
    {
        ParseTim_80029708(&buf, (char*)file + ((int*)file)[i + 1]);
        if (hue)
        {
            ShiftClutHue_80029D00(&buf, hue);
        }
        if (reloc)
        {
            RelocateTimInfo_800297C0(&buf, (TimReloc*)reloc);
        }
        LoadTimToVram_800296A0(&buf);
        if (sprts && tpages)
        {
            InitSprtFromTim_800298AC(*(int*)sprts + i * 20, *(int*)tpages + i * 8, &buf);
        }
        if (polys)
        {
            InitPolyFT4_80029A10((void*)(*(int*)polys + i * 40), &buf);
        }
    }
}
// Matched
void ShiftVramImageHsv_800290FC(RECT* rect, short* dst, short* delta)
{
    short rgb[4];
    short hsv[4];
    RECT dstRect;
    unsigned short* buf;
    unsigned short* pixel;
    int x;
    int y;
    buf = malloc3_8003FC4C(rect->h * (rect->w << 1));
    StoreImage(rect, (u_long*)buf);
    DrawSync(0);
    pixel = buf;
    for (y = 0; y < rect->h; y++)
    {
        for (x = 0; x < rect->w; x++)
        {
            UnpackColor555_80029C68((unsigned short*)rgb, pixel);
            Rgb555ToHsv_80029EA8(rgb, hsv);
            hsv[0] += delta[0];
            hsv[1] += delta[1];
            hsv[1] = (hsv[1] < 0) ? 0 : ((hsv[1] > 31) ? 31 : hsv[1]);
            hsv[2] += delta[2];
            hsv[2] = (hsv[2] < 0) ? 0 : ((hsv[2] > 31) ? 31 : hsv[2]);
            HsvToRgb555_8002A040(hsv, rgb);
            PackColor555_80029CB4(pixel, (unsigned short*)rgb);
            pixel++;
        }
    }
    dstRect.x = dst[0];
    dstRect.y = dst[1];
    dstRect.w = rect->w;
    dstRect.h = rect->h;
    LoadImage(&dstRect, (u_long*)buf);
    DrawSync(0);
    free3_8003FC6C(buf);
}
// Matched
void TintVramImage_800292D0(void* rect, void* dst, int tint)
{
    short rgb[4];
    short out[4];
    RECT dstRect;
    unsigned short* buf;
    unsigned short* pixel;
    int x;
    int y;
    int gray;
    buf = malloc3_8003FC4C(((RECT*)rect)->h * (((RECT*)rect)->w << 1));
    StoreImage((RECT*)rect, (u_long*)buf);
    DrawSync(0);
    pixel = buf;
    for (y = 0; y < ((RECT*)rect)->h; y++)
    {
        for (x = 0; x < ((RECT*)rect)->w; x++)
        {
            UnpackColor555_80029C68((unsigned short*)rgb, pixel);
            if (rgb[0] || rgb[1] || rgb[2])
            {
                gray = (rgb[0] + rgb[1] + rgb[2]) / 3;
                out[0] = ((rgb[0] * (0x1000 - ((short*)tint)[3]) + gray * ((short*)tint)[3]) / 4096) * (0x1000 - ((short*)tint)[4]) / 4096 + ((short*)tint)[0] * ((short*)tint)[4] / 4096;
                out[1] = ((rgb[1] * (0x1000 - ((short*)tint)[3]) + gray * ((short*)tint)[3]) / 4096) * (0x1000 - ((short*)tint)[4]) / 4096 + ((short*)tint)[1] * ((short*)tint)[4] / 4096;
                out[2] = ((rgb[2] * (0x1000 - ((short*)tint)[3]) + gray * ((short*)tint)[3]) / 4096) * (0x1000 - ((short*)tint)[4]) / 4096 + ((short*)tint)[2] * ((short*)tint)[4] / 4096;
                out[3] = rgb[3];
                PackColor555_80029CB4(pixel, (unsigned short*)out);
            }
            pixel++;
        }
    }
    dstRect.x = ((short*)dst)[0];
    dstRect.y = ((short*)dst)[1];
    dstRect.w = ((RECT*)rect)->w;
    dstRect.h = ((RECT*)rect)->h;
    LoadImage(&dstRect, (u_long*)buf);
    DrawSync(0);
    free3_8003FC6C(buf);
}
// Matched
void AllocTiyPrims_800295D8(SPRT** sprts, POLY_FT4** polys, DR_TPAGE** tpages, int count, int heap)
{
    if (sprts)
    {
        *sprts = HeapAlloc_8003FC8C(count * sizeof(SPRT), heap);
    }
    if (polys)
    {
        *polys = HeapAlloc_8003FC8C(count * sizeof(POLY_FT4), heap);
    }
    if (tpages)
    {
        *tpages = HeapAlloc_8003FC8C(count * sizeof(DR_TPAGE), heap);
    }
}
// Matched
void LoadTim_80029674(void* tim)
{
    TimInfo buf;
    ParseTim_80029708(&buf, tim);
    LoadTimToVram_800296A0(&buf);
}
// Matched
void LoadTimToVram_800296A0(void* tim)
{
    int* info = (int*)tim;
    if (info[0] == 1 && info[2] != 0)
    {
        LoadImage((RECT*)&info[3], (u_long*)info[5]);
        DrawSync(0);
    }
    LoadImage((RECT*)&info[7], (u_long*)info[9]);
    DrawSync(0);
}
// Matched
int ParseTim_80029708(void* outTim, void* inTim)
{
    int* out = (int*)outTim;
    int* in = (int*)inTim;
    int* pixelBlock;
    out[1] = in[1] & 7;
    pixelBlock = in + 2;
    if (in[1] & 8)
    {
        out[0] = 1;
        out[2] = in[2] - 12;
        *(RECT*)&out[3] = *(RECT*)&in[3];
        out[5] = (int)&in[5];
        pixelBlock = (int*)((char*)pixelBlock + in[2]);
    }
    else
    {
        out[0] = 0;
        out[2] = 0;
    }
    out[6] = pixelBlock[0] - 12;
    *(RECT*)&out[7] = *(RECT*)&pixelBlock[1];
    out[9] = (int)&pixelBlock[3];
    return 1;
}
// Matched
void RelocateTimInfo_800297C0(TimInfo* tim, TimReloc* reloc)
{
    if (tim->mode_valid)
    {
        switch (tim->mode)
        {
        case 0:
            *(unsigned short*)&tim->crect.x += reloc->clut4Dx_4;
            *(unsigned short*)&tim->crect.y += reloc->clut4Dy_6;
            break;
        case 1:
            *(unsigned short*)&tim->crect.x += reloc->clut8Dx_8;
            *(unsigned short*)&tim->crect.y += reloc->clut8Dy_A;
            break;
        }
    }
    *(unsigned short*)&tim->prect.x += reloc->pixelDx_0;
    *(unsigned short*)&tim->prect.y += reloc->pixelDy_2;
}
// Matched
void InitSprtFromTimData_80029868(int sprt, int tim, int tpage)
{
    TimInfo buf;
    ParseTim_80029708(&buf, (void*)tim);
    InitSprtFromTim_800298AC(sprt, tpage, &buf);
}
// Matched
void InitSprtFromTim_800298AC(SPRT* sprt, DR_TPAGE* tpage, TimInfo* tim)
{
    SetSprt(sprt);
    sprt->r0 = 0x80;
    sprt->g0 = 0x80;
    sprt->b0 = 0x80;
    SetDrawTPage(tpage, 0, 1, GetTPage(tim->mode, 1, (tim->prect.x / 64) * 64, (tim->prect.y / 256) * 256));
    sprt->u0 = ((short)(tim->prect.x % 64) * 4) >> tim->mode;
    sprt->v0 = tim->prect.y % 256;
    sprt->w = (tim->prect.w * 4) >> tim->mode;
    sprt->h = tim->prect.h;
    sprt->clut = ((unsigned short)tim->crect.y << 6) | (((unsigned short)tim->crect.x >> 4) & 0x3F);
}
// Matched
void InitPolyFT4FromTimData_800299DC(void* poly, void* tim)
{
    TimInfo buf;
    ParseTim_80029708(&buf, tim);
    InitPolyFT4_80029A10(poly, &buf);
}
// Matched
void InitPolyFT4_80029A10(void* polyArg, void* timArg)
{
    POLY_FT4* poly = (POLY_FT4*)polyArg;
    TimInfo* tim = (TimInfo*)timArg;
    SetPolyFT4(poly);
    poly->r0 = 0x80;
    poly->g0 = 0x80;
    poly->b0 = 0x80;
    poly->tpage = getTPage(tim->mode, 1, (tim->prect.x / 64) * 64, (tim->prect.y / 256) * 256);
    poly->u0 = ((short)(tim->prect.x % 64) * 4) >> tim->mode;
    poly->v0 = tim->prect.y % 256;
    poly->u1 = (((short)(tim->prect.x % 64) * 4) >> tim->mode) + (((tim->prect.w * 4) >> tim->mode) - 1);
    poly->v1 = tim->prect.y % 256;
    poly->u2 = ((short)(tim->prect.x % 64) * 4) >> tim->mode;
    poly->v2 = tim->prect.y % 256 + (tim->prect.h - 1);
    poly->u3 = (((short)(tim->prect.x % 64) * 4) >> tim->mode) + (((tim->prect.w * 4) >> tim->mode) - 1);
    poly->v3 = tim->prect.y % 256 + (tim->prect.h - 1);
    poly->clut = ((unsigned short)tim->crect.y << 6) | (((unsigned short)tim->crect.x >> 4) & 0x3F);
}
// Matched
void UnpackColor555_80029C68(unsigned short* dst, unsigned short* src)
{
    dst[3] = *src & 0x8000;
    dst[0] = *src & 0x1f;
    dst[1] = (*src >> 5) & 0x1f;
    dst[2] = (*src >> 10) & 0x1f;
}
// Matched
void PackColor555_80029CB4(unsigned short* dst, unsigned short* src)
{
    *dst = 0;
    *dst = src[3];
    *dst |= src[0];
    *dst |= src[1] << 5;
    *dst |= src[2] << 10;
}
// Matched
void ShiftClutHue_80029D00(TimInfo* tim, unsigned int hue)
{
    short rgb[4];
    short hsv[4];
    unsigned short* clut;
    int i;
    unsigned int shift;
    if (tim->mode_valid && tim->clut_len)
    {
        clut = (unsigned short*)tim->caddr;
        for (i = 0; i < tim->crect.w; i++)
        {
            UnpackColor555_80029C68((unsigned short*)rgb, &clut[i]);
            if (Rgb555ToHsv_80029EA8(rgb, hsv))
            {
                if (hue & 0x10000)
                {
                    shift = hue >> 16;
                    hsv[0] = hsv[0] + (hue - hsv[0] * 360 / 192) + (shift & 0xFFFE) * 192 / 360;
                }
                else
                {
                    shift = hue * 192 / 360;
                    hsv[0] = (short)(hsv[0] + shift) % 192;
                }
                HsvToRgb555_8002A040(hsv, rgb);
                PackColor555_80029CB4(&clut[i], (unsigned short*)rgb);
            }
        }
    }
}
// Matched
int Rgb555ToHsv_80029EA8(short* in, short* out)
{
    int idx;
    int min;
    int dr, dg, db;
    idx = 0;
    out[2] = in[2];
    if (out[2] < in[0])
    {
        out[2] = in[0];
        idx = 1;
    }
    if (in[1] > out[2])
    {
        out[2] = in[1];
        idx = 2;
    }
    min = in[2];
    if (in[0] < min)
    {
        min = in[0];
    }
    if (in[1] < min)
    {
        min = in[1];
    }
    if (out[2] == 0)
    {
        out[1] = 0;
    }
    else
    {
        out[1] = ((out[2] - min) * 31) / out[2];
    }
    if (out[1] == 0)
    {
        out[0] = -1;
        return 0;
    }
    db = out[2] - in[2];
    dr = out[2] - in[0];
    min = out[2] - min;
    dg = out[2] - in[1];
    switch (idx)
    {
    case 0:
        out[0] = ((dg - dr) * 32) / min + 0x80;
        break;
    case 1:
        out[0] = ((db - dg) * 32) / min;
        break;
    case 2:
        out[0] = ((dr - db) * 32) / min + 0x40;
        break;
    }
    if (out[0] < 0)
    {
        out[0] += 0xC0;
    }
    out[3] = in[3];
    return 1;
}
// Matched
int HsvToRgb555_8002A040(short* in, short* out)
{
    int sector;
    short f;
    int v;
    int p, q, t;
    sector = in[0] / 32;
    f = in[0] % 32;
    v = in[2];
    p = (v * (0x3E0 - in[1] * 32) + 0x1F0) / 0x3E0;
    q = (v * (0x3E0 - in[1] * f) + 0x1F0) / 0x3E0;
    t = (v * (0x3E0 - in[1] * (32 - f)) + 0x1F0) / 0x3E0;
    switch (sector)
    {
    case 0:
        out[0] = v;
        out[1] = t;
        out[2] = p;
        break;
    case 1:
        out[0] = q;
        out[1] = v;
        out[2] = p;
        break;
    case 2:
        out[0] = p;
        out[1] = v;
        out[2] = t;
        break;
    case 3:
        out[0] = p;
        out[1] = q;
        out[2] = v;
        break;
    case 4:
        out[0] = t;
        out[1] = p;
        out[2] = v;
        break;
    case 5:
        out[0] = v;
        out[1] = p;
        out[2] = q;
        break;
    }
    out[3] = in[3];
    return 1;
}
