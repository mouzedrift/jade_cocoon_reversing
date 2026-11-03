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


extern char cameraState_8008D4F0[];
extern int dword_80091C68[];
extern int dword_8008266C;
extern int dword_80091C5C;
extern int dword_80091C8C;
extern void (*dword_80091CB4)(int);
extern void sub_80027778(char* p, int* q);
extern void sub_800278BC(char* p, int* q);
extern int dword_80082668;
#if 0
// Not matched (1 word): the original computes a1 + 0x108 from the $v0 copy of a1, this from $s0
void sub_80028C60(int a0, char* a1)
{
    int n;
    char* p;
    MemCopy_800403E8((unsigned int*)cameraState_8008D4F0, (unsigned int*)a1, 0x104);
    p = a1;
    a1 += 0x108;
    n = *(int*)(p + 0x104);
    LoadTiy_80028E74(0, 0, 0, (int)a1, (int)&dword_80091C20);
    a1 += n;
    n = *(int*)a1;
    a1 += 4;
    if (dword_80082670 == 0)
    {
        sub_80027778(a1, &dword_80091C20);
    }
    a1 += n;
    n = *(int*)a1;
    a1 += 4;
    if (dword_80082670 == 0)
    {
        sub_800278BC(a1, &dword_80091C20);
    }
    a1 += n;
    if (dword_80082670 == 1)
    {
        LoadTiy_80028E74(0, 0, 0, (int)(a1 + 4), (int)dword_80091C68);
    }
    sub_800272BC(dword_8008B500[0], word_8008B860);
    if (dword_80082668 && dword_8008266C && dword_80091C5C && dword_80091C8C == 0 && dword_80091CB4)
    {
        dword_80091CB4(1);
    }
}
#endif
INCLUDE_ASM(sub_80028C60);
extern short dword_8008D474[2];
extern char levantPos_8008BD18[];
extern void sub_80037918(int* p);
// Matched
void sub_80028DC0(void)
{
    int* p;
    unsigned short* q;
    if (dword_80082670 == 0)
    {
        p = cameraTask_8008D4A0[0x24 / 4];
        if (dword_80082668)
        {
            SetCameraTarget_80037AC8((int)levantPos_8008BD18);
        }
        sub_80037918(p);
        q = (unsigned short*)&display_8008B4D8;
        SetGeomOffset((short)q[6] / 2 + dword_8008D474[0], (short)q[7] / 2 + dword_8008D474[1]);
    }
}
// Matched
int GetTiyFileCount_80028E68(int* p)
{
    return p[0];
}
extern void AllocTiyPrims_800295D8(int* a0, int a1, int* a2, int a3, int a4);
extern void LoadTiyTims_80028EEC(int* a0, int a1, int* a2, int a3, int a4);
// Matched
void LoadTiy_80028E74(int* a0, int a1, int* a2, int a3, int a4)
{
    int v = *(int*)a3;
    AllocTiyPrims_800295D8(a0, a1, a2, v, a4);
    LoadTiyTims_80028EEC(a0, a1, a2, a3, v);
}
// Matched
void LoadTiyTims_80028EEC(int* a0, int a1, int* a2, int a3, int a4)
{
    char buf[0x28];
    unsigned int i;
    for (i = 0; i < (unsigned int)a4; i++)
    {
        ParseTim_80029708(buf, (char*)a3 + ((int*)a3)[i + 1]);
        LoadTimToVram_800296A0(buf);
        if (a0 && a2)
        {
            InitSprtFromTim_800298AC(*a0 + i * 20, *a2 + i * 8, buf);
        }
        if (a1)
        {
            InitPolyFT4_80029A10((char*)*(int*)a1 + i * 40, buf);
        }
    }
}
extern void ShiftClutHue_80029D00(void* buf, unsigned int a);
typedef struct
{
    int field_0;
    int field_4;
    short pad_8[2];
    unsigned short field_C;
    unsigned short field_E;
    char pad_10[0xC];
    unsigned short field_1C;
    unsigned short field_1E;
} struct_97C0_a;
typedef struct
{
    unsigned short field_0;
    unsigned short field_2;
    unsigned short field_4;
    unsigned short field_6;
    unsigned short field_8;
    unsigned short field_A;
} struct_97C0_b;
void RelocateTimInfo_800297C0(struct_97C0_a* a, struct_97C0_b* b);
// Matched
void LoadTiyTimsRelocated_80028FDC(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    char buf[0x28];
    unsigned int i;
    for (i = 0; i < a4; i++)
    {
        ParseTim_80029708(buf, (char*)a3 + ((int*)a3)[i + 1]);
        if (a6)
        {
            ShiftClutHue_80029D00(buf, a6);
        }
        if (a5)
        {
            RelocateTimInfo_800297C0((struct_97C0_a*)buf, (struct_97C0_b*)a5);
        }
        LoadTimToVram_800296A0(buf);
        if (a0 && a2)
        {
            InitSprtFromTim_800298AC(*(int*)a0 + i * 20, *(int*)a2 + i * 8, buf);
        }
        if (a1)
        {
            InitPolyFT4_80029A10((void*)(*(int*)a1 + i * 40), buf);
        }
    }
}
int Rgb555ToHsv_80029EA8(short* in, short* out);
int HsvToRgb555_8002A040(short* in, short* out);
void UnpackColor555_80029C68(unsigned short* d, unsigned short* s);
void PackColor555_80029CB4(unsigned short* d, unsigned short* s);
// Matched
void ShiftVramImageHsv_800290FC(RECT* r, short* dst, short* d)
{
    short rgb[4];
    short hsv[4];
    RECT r2;
    unsigned short* buf;
    unsigned short* p;
    int x;
    int y;
    buf = malloc3_8003FC4C(r->h * (r->w << 1));
    StoreImage(r, (u_long*)buf);
    DrawSync(0);
    p = buf;
    for (y = 0; y < r->h; y++)
    {
        for (x = 0; x < r->w; x++)
        {
            UnpackColor555_80029C68((unsigned short*)rgb, p);
            Rgb555ToHsv_80029EA8(rgb, hsv);
            hsv[0] += d[0];
            hsv[1] += d[1];
            hsv[1] = (hsv[1] < 0) ? 0 : ((hsv[1] > 31) ? 31 : hsv[1]);
            hsv[2] += d[2];
            hsv[2] = (hsv[2] < 0) ? 0 : ((hsv[2] > 31) ? 31 : hsv[2]);
            HsvToRgb555_8002A040(hsv, rgb);
            PackColor555_80029CB4(p, (unsigned short*)rgb);
            p++;
        }
    }
    r2.x = dst[0];
    r2.y = dst[1];
    r2.w = r->w;
    r2.h = r->h;
    LoadImage(&r2, (u_long*)buf);
    DrawSync(0);
    free3_8003FC6C(buf);
}
// Matched
void TintVramImage_800292D0(void* a0, void* a1, int a2)
{
    short c[4];
    short o[4];
    RECT r2;
    unsigned short* buf;
    unsigned short* p;
    int x;
    int y;
    int gray;
    buf = malloc3_8003FC4C(((RECT*)a0)->h * (((RECT*)a0)->w << 1));
    StoreImage((RECT*)a0, (u_long*)buf);
    DrawSync(0);
    p = buf;
    for (y = 0; y < ((RECT*)a0)->h; y++)
    {
        for (x = 0; x < ((RECT*)a0)->w; x++)
        {
            UnpackColor555_80029C68((unsigned short*)c, p);
            if (c[0] || c[1] || c[2])
            {
                gray = (c[0] + c[1] + c[2]) / 3;
                o[0] = ((c[0] * (0x1000 - ((short*)a2)[3]) + gray * ((short*)a2)[3]) / 4096) * (0x1000 - ((short*)a2)[4]) / 4096 + ((short*)a2)[0] * ((short*)a2)[4] / 4096;
                o[1] = ((c[1] * (0x1000 - ((short*)a2)[3]) + gray * ((short*)a2)[3]) / 4096) * (0x1000 - ((short*)a2)[4]) / 4096 + ((short*)a2)[1] * ((short*)a2)[4] / 4096;
                o[2] = ((c[2] * (0x1000 - ((short*)a2)[3]) + gray * ((short*)a2)[3]) / 4096) * (0x1000 - ((short*)a2)[4]) / 4096 + ((short*)a2)[2] * ((short*)a2)[4] / 4096;
                o[3] = c[3];
                PackColor555_80029CB4(p, (unsigned short*)o);
            }
            p++;
        }
    }
    r2.x = ((short*)a1)[0];
    r2.y = ((short*)a1)[1];
    r2.w = ((RECT*)a0)->w;
    r2.h = ((RECT*)a0)->h;
    LoadImage(&r2, (u_long*)buf);
    DrawSync(0);
    free3_8003FC6C(buf);
}
// Matched
void AllocTiyPrims_800295D8(int* a, int b, int* c, int n, int heap)
{
    if (a)
    {
        *a = HeapAlloc_8003FC8C(n * 20, (struct Pool*)heap);
    }
    if (b)
    {
        *(int*)b = HeapAlloc_8003FC8C(n * 40, (struct Pool*)heap);
    }
    if (c)
    {
        *c = HeapAlloc_8003FC8C(n * 8, (struct Pool*)heap);
    }
}
// Matched
void LoadTim_80029674(void* p)
{
    char buf[0x28];
    ParseTim_80029708(buf, p);
    LoadTimToVram_800296A0(buf);
}
// Matched
void LoadTimToVram_800296A0(void* arg0)
{
    int* p = (int*)arg0;
    if (p[0] == 1 && p[2] != 0)
    {
        LoadImage((RECT*)&p[3], (u_long*)p[5]);
        DrawSync(0);
    }
    LoadImage((RECT*)&p[7], (u_long*)p[9]);
    DrawSync(0);
}
// Matched
int ParseTim_80029708(void* arg0, void* arg1)
{
    int* out = (int*)arg0;
    int* in = (int*)arg1;
    int* q;
    out[1] = in[1] & 7;
    q = in + 2;
    if (in[1] & 8)
    {
        out[0] = 1;
        out[2] = in[2] - 12;
        *(RECT*)&out[3] = *(RECT*)&in[3];
        out[5] = (int)&in[5];
        q = (int*)((char*)q + in[2]);
    }
    else
    {
        out[0] = 0;
        out[2] = 0;
    }
    out[6] = q[0] - 12;
    *(RECT*)&out[7] = *(RECT*)&q[1];
    out[9] = (int)&q[3];
    return 1;
}
// Matched
void RelocateTimInfo_800297C0(struct_97C0_a* a, struct_97C0_b* b)
{
    if (a->field_0)
    {
        switch (a->field_4)
        {
        case 0:
            a->field_C += b->field_4;
            a->field_E += b->field_6;
            break;
        case 1:
            a->field_C += b->field_8;
            a->field_E += b->field_A;
            break;
        }
    }
    a->field_1C += b->field_0;
    a->field_1E += b->field_2;
}
// Matched
void InitSprtFromTimData_80029868(int a0, int a1, int a2)
{
    char buf[0x28];
    ParseTim_80029708(buf, (void*)a1);
    InitSprtFromTim_800298AC(a0, a2, buf);
}
typedef struct
{
    int mode_valid;
    int mode;
    int clut_len;
    RECT crect;
    u_long* caddr;
    int pix_len;
    RECT prect;
    u_long* paddr;
} TimInfo;
// Matched
void InitSprtFromTim_800298AC(int a0, int a1, void* a2)
{
    SPRT* s = (SPRT*)a0;
    TimInfo* t = (TimInfo*)a2;
    SetSprt(s);
    s->r0 = 0x80;
    s->g0 = 0x80;
    s->b0 = 0x80;
    SetDrawTPage((DR_TPAGE*)a1, 0, 1, GetTPage(t->mode, 1, (t->prect.x / 64) * 64, (t->prect.y / 256) * 256));
    s->u0 = ((short)(t->prect.x % 64) * 4) >> t->mode;
    s->v0 = t->prect.y % 256;
    s->w = (t->prect.w * 4) >> t->mode;
    s->h = t->prect.h;
    s->clut = ((unsigned short)t->crect.y << 6) | (((unsigned short)t->crect.x >> 4) & 0x3F);
}
// Matched
void InitPolyFT4FromTimData_800299DC(void* p, void* q)
{
    char buf[0x28];
    ParseTim_80029708(buf, q);
    InitPolyFT4_80029A10(p, buf);
}
// Matched
void InitPolyFT4_80029A10(void* a0, void* a1)
{
    POLY_FT4* s = (POLY_FT4*)a0;
    TimInfo* t = (TimInfo*)a1;
    SetPolyFT4(s);
    s->r0 = 0x80;
    s->g0 = 0x80;
    s->b0 = 0x80;
    s->tpage = getTPage(t->mode, 1, (t->prect.x / 64) * 64, (t->prect.y / 256) * 256);
    s->u0 = ((short)(t->prect.x % 64) * 4) >> t->mode;
    s->v0 = t->prect.y % 256;
    s->u1 = (((short)(t->prect.x % 64) * 4) >> t->mode) + (((t->prect.w * 4) >> t->mode) - 1);
    s->v1 = t->prect.y % 256;
    s->u2 = ((short)(t->prect.x % 64) * 4) >> t->mode;
    s->v2 = t->prect.y % 256 + (t->prect.h - 1);
    s->u3 = (((short)(t->prect.x % 64) * 4) >> t->mode) + (((t->prect.w * 4) >> t->mode) - 1);
    s->v3 = t->prect.y % 256 + (t->prect.h - 1);
    s->clut = ((unsigned short)t->crect.y << 6) | (((unsigned short)t->crect.x >> 4) & 0x3F);
}
// Matched
void UnpackColor555_80029C68(unsigned short* d, unsigned short* s)
{
    d[3] = *s & 0x8000;
    d[0] = *s & 0x1f;
    d[1] = (*s >> 5) & 0x1f;
    d[2] = (*s >> 10) & 0x1f;
}
// Matched
void PackColor555_80029CB4(unsigned short* d, unsigned short* s)
{
    *d = 0;
    *d = s[3];
    *d |= s[0];
    *d |= s[1] << 5;
    *d |= s[2] << 10;
}
int Rgb555ToHsv_80029EA8(short* in, short* out);
int HsvToRgb555_8002A040(short* in, short* out);
#if 0
// Not matched (17 words): only the saved registers of t and the two division constants are rotated (s3/s4/s5)
void ShiftClutHue_80029D00(TimInfo* t, unsigned int a1)
{
    short rgb[4];
    short hsv[4];
    unsigned short* p;
    int i;
    unsigned int v;
    if (t->mode_valid && t->clut_len)
    {
        p = (unsigned short*)t->caddr;
        for (i = 0; i < t->crect.w; i++)
        {
            UnpackColor555_80029C68((unsigned short*)rgb, &p[i]);
            if (Rgb555ToHsv_80029EA8(rgb, hsv))
            {
                if (a1 & 0x10000)
                {
                    v = a1 >> 16;
                    hsv[0] = hsv[0] + (a1 - hsv[0] * 360 / 192) + (v & 0xFFFE) * 192 / 360;
                }
                else
                {
                    v = a1 * 192 / 360;
                    hsv[0] = (short)(hsv[0] + v) % 192;
                }
                HsvToRgb555_8002A040(hsv, rgb);
                PackColor555_80029CB4(&p[i], (unsigned short*)rgb);
            }
        }
    }
}
#endif
INCLUDE_ASM(ShiftClutHue_80029D00);
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
