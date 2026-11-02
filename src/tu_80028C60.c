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


INCLUDE_ASM(sub_80028C60);
INCLUDE_ASM(sub_80028DC0);
// Matched
int GetTiyFileCount_80028E68(int* p)
{
    return p[0];
}
extern void sub_800295D8(int* a0, int a1, int* a2, int a3, int a4);
extern void sub_80028EEC(int* a0, int a1, int* a2, int a3, int a4);
// Matched
void sub_80028E74(int* a0, int a1, int* a2, int a3, int a4)
{
    int v = *(int*)a3;
    sub_800295D8(a0, a1, a2, v, a4);
    sub_80028EEC(a0, a1, a2, a3, v);
}
// Matched
void sub_80028EEC(int* a0, int a1, int* a2, int a3, int a4)
{
    char buf[0x28];
    unsigned int i;
    for (i = 0; i < a4; i++)
    {
        sub_80029708(buf, (char*)a3 + ((int*)a3)[i + 1]);
        sub_800296A0(buf);
        if (a0 && a2)
        {
            sub_800298AC(*a0 + i * 20, *a2 + i * 8, buf);
        }
        if (a1)
        {
            InitPolyFT4_80029A10((void*)(*(int*)a1 + i * 40), buf);
        }
    }
}
extern void sub_80029D00(void* buf, void* a);
void sub_800297C0(int* a, short* b);
// Matched
void sub_80028FDC(int* a0, int a1, int* a2, int a3, int a4, short* a5, void* a6)
{
    char buf[0x28];
    unsigned int i;
    for (i = 0; i < a4; i++)
    {
        sub_80029708(buf, (char*)a3 + ((int*)a3)[i + 1]);
        if (a6)
        {
            sub_80029D00(buf, a6);
        }
        if (a5)
        {
            sub_800297C0((int*)buf, a5);
        }
        sub_800296A0(buf);
        if (a0 && a2)
        {
            sub_800298AC(*a0 + i * 20, *a2 + i * 8, buf);
        }
        if (a1)
        {
            InitPolyFT4_80029A10((void*)(*(int*)a1 + i * 40), buf);
        }
    }
}
INCLUDE_ASM(sub_800290FC);
INCLUDE_ASM(sub_800292D0);
// Matched
void sub_800295D8(int* a0, int a1, int* a2, int a3, int a4)
{
    if (a0)
    {
        *a0 = sub_8003FC8C(a3 * 20, (struct Heap*)a4);
    }
    if (a1)
    {
        *(int*)a1 = sub_8003FC8C(a3 * 40, (struct Heap*)a4);
    }
    if (a2)
    {
        *a2 = sub_8003FC8C(a3 * 8, (struct Heap*)a4);
    }
}
// Matched
void sub_80029674(void* p)
{
    char buf[0x28];
    sub_80029708(buf, p);
    sub_800296A0(buf);
}
// Matched
void sub_800296A0(void* arg0)
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
int sub_80029708(void* arg0, void* arg1)
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
void sub_800297C0(int* a, short* b)
{
    if (a[0])
    {
        switch (a[1])
        {
        case 0:
            ((RECT*)&a[3])->x += b[2];
            ((RECT*)&a[3])->y += b[3];
            break;
        case 1:
            ((RECT*)&a[3])->x += b[4];
            ((RECT*)&a[3])->y += b[5];
            break;
        }
    }
    ((RECT*)&a[7])->x += b[0];
    ((RECT*)&a[7])->y += b[1];
}
// Matched
void sub_80029868(int a0, int a1, int a2)
{
    char buf[0x28];
    sub_80029708(buf, (void*)a1);
    sub_800298AC(a0, a2, buf);
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
void sub_800298AC(int a0, int a1, void* a2)
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
void sub_800299DC(void* p, void* q)
{
    char buf[0x28];
    sub_80029708(buf, q);
    InitPolyFT4_80029A10(p, buf);
}
#if 0
void InitPolyFT4_80029A10(void* a0, void* a1)
{
}
#endif
INCLUDE_ASM(InitPolyFT4_80029A10);
// Matched
void sub_80029C68(unsigned short* d, unsigned short* s)
{
    d[3] = *s & 0x8000;
    d[0] = *s & 0x1f;
    d[1] = (*s >> 5) & 0x1f;
    d[2] = (*s >> 10) & 0x1f;
}
// Matched
void sub_80029CB4(unsigned short* d, unsigned short* s)
{
    *d = 0;
    *d = s[3];
    *d |= s[0];
    *d |= s[1] << 5;
    *d |= s[2] << 10;
}
INCLUDE_ASM(sub_80029D00);
// Matched
int sub_80029EA8(short* in, short* out)
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
INCLUDE_ASM(sub_8002A040);
