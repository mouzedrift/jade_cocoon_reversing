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
extern short dword_8008D474[2];
extern int dword_80082668;
extern char levantPos_8008BD18[];
extern void sub_80037918(int* p);
// Matched
void sub_80028DC0(void)
{
    int* p;
    unsigned short* q;
    if (dword_80082670 == 0)
    {
        p = dword_8008D4A0[0x24 / 4];
        if (dword_80082668)
        {
            sub_80037AC8((int)levantPos_8008BD18);
        }
        sub_80037918(p);
        q = (unsigned short*)&stru_8008B4D8;
        SetGeomOffset((short)q[6] / 2 + dword_8008D474[0], (short)q[7] / 2 + dword_8008D474[1]);
    }
}
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
    for (i = 0; i < (unsigned int)a4; i++)
    {
        sub_80029708(buf, (char*)a3 + ((int*)a3)[i + 1]);
        sub_800296A0(buf);
        if (a0 && a2)
        {
            sub_800298AC(*a0 + i * 20, *a2 + i * 8, buf);
        }
        if (a1)
        {
            InitPolyFT4_80029A10((char*)*(int*)a1 + i * 40, buf);
        }
    }
}
INCLUDE_ASM(sub_80028FDC);
INCLUDE_ASM(sub_800290FC);
INCLUDE_ASM(sub_800292D0);
// Matched
void sub_800295D8(int* a, int b, int* c, int n, int heap)
{
    if (a)
    {
        *a = sub_8003FC8C(n * 20, (struct Heap*)heap);
    }
    if (b)
    {
        *(int*)b = sub_8003FC8C(n * 40, (struct Heap*)heap);
    }
    if (c)
    {
        *c = sub_8003FC8C(n * 8, (struct Heap*)heap);
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
#if 0
void sub_80029708(void* arg0, void* arg1)
{
}
#endif
INCLUDE_ASM(sub_80029708);
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
// Matched
void sub_800297C0(struct_97C0_a* a, struct_97C0_b* b)
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
void sub_80029868(int a0, int a1, int a2)
{
    char buf[0x28];
    sub_80029708(buf, (void*)a1);
    sub_800298AC(a0, a2, buf);
}
#if 0
void sub_800298AC(int a0, int a1, void* a2)
{
}
#endif
INCLUDE_ASM(sub_800298AC);
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
INCLUDE_ASM(sub_80029EA8);
INCLUDE_ASM(sub_8002A040);
