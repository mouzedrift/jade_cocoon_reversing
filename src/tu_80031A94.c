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

INCLUDE_DATA(jpt_8007470C);


extern unsigned char* sub_80031B30(unsigned char a);
// Matched
int sub_80031A94(int* p)
{
    int r;
    unsigned char* q;
    r = 2;
    if (p[2] & 0xF)
    {
        r = 4;
    }
    q = sub_80031B30(sub_80014358(p[2]));
    q += p[1] * 4;
    if (q[1] == 12)
    {
        r |= 1;
    }
    return r;
}
// Matched
int sub_80031B0C(unsigned char* p, int idx)
{
    int r;
    p += idx * 4;
    r = 4;
    if (p[1] == 12)
    {
        r = 5;
    }
    return r;
}
#if 0
// Not matched (bit test becomes srav/andi instead of sllv/and; temporaries land in a0 instead of a1)
unsigned char* sub_80031B30(unsigned char a)
{
    unsigned char* r = 0;
    if (a >= 8)
    {
        r = (unsigned char*)sub_800A11A0((unsigned char)(a - 8));
    }
    else if (a >= 4)
    {
        if ((1 << a) & sub_800A248C())
        {
            r = (unsigned char*)sub_800A2BA0((unsigned char)(a - 4));
        }
    }
    else if (a != 0)
    {
        r = (unsigned char*)sub_800107F8(3, (unsigned char)(a - 1));
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80031B30);
// Matched
int sub_80031BDC(int a0)
{
    return a0;
}
INCLUDE_ASM(sub_80031BE4);
INCLUDE_ASM(sub_80031FF4);
typedef struct
{
    int a;
    int b;
} struct_pair;
extern struct_20* dword_8008D434;
extern struct_pair* dword_8008D440;
// Matched
void sub_80032470(int idx, struct_20* pOut20, struct_pair* pOut8)
{
    *pOut20 = dword_8008D434[idx];
    *pOut8 = dword_8008D440[idx];
}
INCLUDE_ASM(sub_800324D8);
INCLUDE_ASM(sub_800327A8);
// Matched
void sub_80032D34(short* src, void* ot)
{
    short* d;
    int w;
    int h;
    w = src[8] - src[4];
    h = src[13] - src[5];
    d = sub_80040298(ot, src, 10);
    d[4] = src[4] + w;
    d[5] = src[5] + h;
    d[8] = src[4];
    d[9] = src[5] + h;
    d[12] = src[4] + w;
    d[13] = src[5];
    d[16] = src[4];
    d[17] = src[5];
}
// Matched
void sub_80032DFC(short* p, int a1)
{
    int d = p[8] - p[4];
    short* q = sub_80040298((void*)a1, p, 10);
    q[4] = p[4] + d;
    q[8] = p[4];
    q[12] = p[4] + d;
    q[16] = p[4];
}
// Matched
void sub_80032E78(unsigned short* p, int a1)
{
    int d = ((short*)p)[13] - ((short*)p)[5];
    unsigned short* q = (unsigned short*)sub_80040298((void*)a1, p, 10);
    q[5] = p[5] + d;
    q[9] = p[5] + d;
    q[13] = p[5];
    q[17] = p[5];
}
// Matched
void sub_80032EF4(unsigned short* p, int a1)
{
    int a = ((short*)p)[4];
    int b = ((short*)p)[5];
    unsigned short* q = (unsigned short*)sub_80040298((void*)a1, p, 10);
    unsigned short t;
    q[4] = p[12];
    q[5] = p[13];
    q[12] = p[16];
    q[13] = p[17];
    q[16] = p[8];
    t = p[9];
    q[8] = a;
    q[9] = b;
    q[17] = t;
}
// Matched
void sub_80032F88(unsigned short* p, int a1)
{
    int a = ((short*)p)[4];
    int b = ((short*)p)[5];
    unsigned short* q = (unsigned short*)sub_80040298((void*)a1, p, 10);
    unsigned short t;
    q[4] = p[8];
    q[5] = p[9];
    q[8] = p[16];
    q[9] = p[17];
    q[16] = p[12];
    t = p[13];
    q[12] = a;
    q[13] = b;
    q[17] = t;
}
// Matched
void sub_8003301C(void* a, void* b)
{
    sub_80040298(b, a, 10);
}
// Matched
void sub_80033048(unsigned short* p, int v)
{
    p[2] = (p[2] & 0xFF9F) | ((v & 3) << 5);
}
// Matched
void sub_80033064(unsigned short* p, int v)
{
    p[0xB] = (p[0xB] & 0xFF9F) | ((v & 3) << 5);
}
#if 0
// Not matched (5 words: scheduling of the table index/base loads)
void sub_80033080(unsigned short* a, int i, int j)
{
    struct_20* s = &dword_8008D434[i];
    unsigned short* e = (unsigned short*)s;
    e[4] = a[0];
    e[5] = a[1];
    sub_80040298(pOT_8008D454 + j, e, 5);
    sub_80040298(pOT_8008D454 + j, &dword_8008D440[i], 2);
}
#endif
INCLUDE_ASM(sub_80033080);
// Matched
void sub_80033114(unsigned short* pos, int idx, void* ot, unsigned char* rgb)
{
    ((unsigned char*)&dword_8008D434[idx])[4] = rgb[0];
    ((unsigned char*)&dword_8008D434[idx])[5] = rgb[1];
    ((unsigned char*)&dword_8008D434[idx])[6] = rgb[2];
    ((unsigned short*)&dword_8008D434[idx])[4] = pos[0];
    ((unsigned short*)&dword_8008D434[idx])[5] = pos[1];
    sub_80040298(ot, &dword_8008D434[idx], 5);
    sub_80040298(ot, &dword_8008D440[idx], 2);
}
// Matched
void sub_800331C4(unsigned short* a, unsigned char* o, void* b, void* c, unsigned char* col)
{
    if (col)
    {
        o[7] &= 0xFE;
        o[4] = col[0];
        o[5] = col[1];
        o[6] = col[2];
    }
    else
    {
        o[7] |= 1;
    }
    *(unsigned short*)(o + 8) = a[0];
    *(unsigned short*)(o + 0xA) = a[1];
    sub_80040298(c, o, 5);
    sub_80040298(c, b, 2);
}
extern DRAWENV drawEnv_8008D698[2];
// Matched
void sub_8003326C(unsigned short* a, void* b)
{
    DR_TWIN twin;
    RECT rect;
    DRAWENV* e = drawEnv_8008D698;
    unsigned short* c = (unsigned short*)&e[bDoubleBuffer_8008D428].clip;
    rect.x = a[0] + c[0];
    rect.y = a[1] + c[1];
    rect.w = a[2];
    rect.h = a[3];
    SetTexWindow(&twin, &rect);
    sub_80040298(b, &twin, 3);
}
// Matched
void sub_80033308(void* p)
{
    DR_TWIN twin;
    RECT rect;
    DRAWENV* e = drawEnv_8008D698;
    unsigned short* c = (unsigned short*)&e[bDoubleBuffer_8008D428].clip;
    rect.x = c[0];
    rect.y = c[1];
    rect.w = c[2];
    rect.h = c[3];
    SetTexWindow(&twin, &rect);
    sub_80040298(p, &twin, 3);
}
// Matched
void sub_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int t, int period, int half)
{
    int ph;
    int den;
    int r, g, b;
    if (period <= 0)
    {
        period = 40;
    }
    if (half <= 0)
    {
        half = 20;
    }
    ph = t % period;
    if (ph < half)
    {
        den = half;
    }
    else
    {
        ph = period - ph;
        den = period - half;
    }
    r = c0[0] + (c1[0] - c0[0]) * ph / den;
    g = c0[1] + (c1[1] - c0[1]) * ph / den;
    b = c0[2] + (c1[2] - c0[2]) * ph / den;
    if (r > 255)
    {
        r = 255;
    }
    if (g > 255)
    {
        g = 255;
    }
    if (b > 255)
    {
        b = 255;
    }
    if (r < 0)
    {
        r = 0;
    }
    if (g < 0)
    {
        g = 0;
    }
    if (b < 0)
    {
        b = 0;
    }
    out[0] = r;
    out[1] = g;
    out[2] = b;
}
// Matched
unsigned char sub_800334BC(unsigned char* arr, int idx)
{
    return arr[idx];
}
// Matched
short sub_800334CC(Minion* p)
{
    return p->field_A;
}
// Matched
short sub_800334D8(Minion* p)
{
    return p->field_8;
}
// Matched
short sub_800334E4(Minion* p)
{
    return p->field_E;
}
// Matched
short sub_800334F0(Minion* p)
{
    return p->field_C;
}
// Matched
int sub_800334FC(int* p)
{
    return p[1];
}
// Matched
short sub_80033508(Minion* p)
{
    return p->field_42;
}
// Matched
short sub_80033514(Minion* p)
{
    return p->field_44;
}
// Matched
unsigned char* sub_80033520(Minion* p)
{
    return p->field_2C;
}
// Matched
unsigned char sub_80033528(unsigned char* p, int idx)
{
    return sub_800334BC(p + 0x2C, idx);
}
// Matched
int sub_80033548(int* p, int mask)
{
    return (*p & mask) != 0;
}
// Matched
unsigned char sub_8003355C(unsigned char* p, int idx)
{
    return (p + idx)[0x20];
}
// Matched
int sub_8003356C(unsigned char* p, unsigned int idx)
{
    int r = 0xFF;
    switch (idx)
    {
    case 0:
        r = p[0x1C];
        break;
    case 1:
        r = p[0x1D];
        break;
    case 2:
        r = p[0x1E];
        break;
    case 3:
        r = p[0x1F];
        break;
    }
    return r;
}
extern void sub_80033754(signed char* out, unsigned char* m);
// Matched
void sub_800335D0(void* pSrc, Minion* m)
{
    int r;
    sub_800403E8((unsigned int*)m, (unsigned int*)pSrc, 0x48);
    r = sub_80033624(m->field_2C, (int)m);
    if (r)
    {
        m->field_44 = r;
    }
    sub_80033754((signed char*)m + 0x20, (unsigned char*)m);
}
#if 0
// Not matched (the out+i store pointer gets strength-reduced; clamp copy and register use differ)
int sub_80033624(void* arg0, int arg1)
{
    unsigned char* out = (unsigned char*)arg0;
    unsigned char* m = (unsigned char*)arg1;
    unsigned char* base = m + 0x2C;
    signed char* tbl[4];
    int i;
    int j;
    int v;
    int mx;
    m += 0x1C;
    tbl[0] = (signed char*)sub_8001CEF4(m[0]);
    tbl[1] = (signed char*)sub_8001CFB0(m[1]);
    tbl[2] = (signed char*)sub_8001D078(m[2]);
    tbl[3] = 0;
    for (i = 0; i < 6; i++)
    {
        v = base[i];
        for (j = 0; j < 4; j++)
        {
            if (tbl[j])
            {
                v += tbl[j][i];
            }
        }
        if (v >= 0)
        {
            mx = v;
            if (mx >= 100)
            {
                mx = 99;
            }
            out[i] = mx;
        }
        else
        {
            out[i] = 0;
        }
    }
    mx = 0;
    for (j = 0; j < 4; j++)
    {
        if (tbl[j] && mx < *(int*)(tbl[j] + 0x10))
        {
            mx = *(int*)(tbl[j] + 0x10);
        }
    }
    return mx;
}
#endif
INCLUDE_ASM(sub_80033624);
#if 0
// Not matched (2 words: a0/v1 swapped for the two lb loads in the inner loop)
void sub_80033754(signed char* out, unsigned char* m)
{
    signed char* tbl[2];
    int i;
    int j;
    sub_800403E8((unsigned int*)out, (unsigned int*)(m + 0x20), 12);
    m += 0x1C;
    tbl[0] = (signed char*)sub_8001CDA0(m[1]);
    tbl[1] = (signed char*)sub_8001CD74(m[2]);
    for (j = 0; j < 2; j++)
    {
        if (tbl[j])
        {
            for (i = 0; i < 12; i++)
            {
                if (*(out + i) < *(tbl[j] + i))
                {
                    *(out + i) = *(tbl[j] + i);
                }
            }
        }
    }
}
#endif
INCLUDE_ASM(sub_80033754);
// Matched
char* sub_80033818(Minion* p)
{
    return p->field_84;
}
// Matched
char* sub_80033820(Minion* p)
{
    return p->field_CC;
}
// Matched
char* sub_80033828(Minion* p)
{
    return p->field_94;
}
// Matched
char* sub_80033830(char* base, int idx)
{
    return base + (idx * 12 + 4);
}
// Matched
unsigned char sub_80033848(unsigned char* arr, int idx)
{
    unsigned char* p = arr + idx;
    return p[0x7C];
}
// Matched
short sub_80033858(Minion* p)
{
    return p->id;
}
// Matched
void sub_80033864(Minion* m, unsigned char* out)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        out[i] = *((unsigned char*)m + i + 0xC2);
        if (out[i] < 8)
        {
            out[i] = 0;
        }
        out[i] >>= 1;
    }
}
// Matched
unsigned char sub_800338B0(char* p)
{
    unsigned char a[8];
    unsigned char b[16];
    sub_800338DC((unsigned char*)p + 0x4C, a, (int*)b);
    return a[0];
}
// Matched
int sub_800338DC(unsigned char* src, unsigned char* ids, int* counts)
{
    unsigned char hist[0xD3];
    int i;
    int j;
    int k;
    int res;
    int sum;
    k = 0;
    res = k;
    for (i = 0; i < 0xD3; i++)
    {
        hist[i] = 0;
    }
    for (i = 0; i < 3; i++)
    {
        ids[i] = 0xD3;
        counts[i] = 0;
    }
    for (i = 0; i < 0x30; i++)
    {
        hist[src[i]]++;
    }
    for (i = 0xFF; i >= 0; i--)
    {
        for (j = 0; j < 0xD3; j++)
        {
            if (hist[j] >= i)
            {
                if (i != 0)
                {
                    ids[k] = j;
                }
                else
                {
                    ids[k] = ids[0];
                    if (res == 0)
                    {
                        res = k;
                    }
                }
                counts[k] = i;
                k++;
                hist[j] = 0;
            }
            if (k >= 3)
            {
                if (res == 0)
                {
                    res = 3;
                }
                goto done;
            }
        }
    }
done:
    sum = counts[0] + counts[1] + counts[2];
    counts[0] <<= 12;
    counts[1] <<= 12;
    counts[2] <<= 12;
    counts[0] /= sum;
    counts[1] /= sum;
    counts[2] /= sum;
    return res;
}
// Matched
void* sub_80033A60(void* p)
{
    return p;
}
// Matched
char* sub_80033A68(char* p)
{
    return p + 0x48;
}
// Matched
int sub_80033A70(unsigned char* p, int idx)
{
    return sub_80031954(p + 0x6C, idx);
}
// Matched
int sub_80033A90(Minion* p, unsigned int idx)
{
    return sub_8001AE2C((unsigned int*)((char*)p + 0x80), idx);
}
// Matched
int sub_80033AB0(Item* p)
{
    return p->id;
}
// Matched
char* sub_80033ABC(char* p)
{
    return p + 0x7C8;
}
// Matched
char* sub_80033AC4(char* p)
{
    return p + 0x7BC;
}
// Matched
Minion* sub_80033ACC(SaveData* s, int idx)
{
    return &s->minions[idx];
}
// Matched
Item* sub_80033AE4(SaveData* s, int idx)
{
    return &s->items[idx];
}
typedef struct
{
    short field_0;
    short field_2;
    short pad_4[3];
    short field_A;
    Minion* field_C_minion;
} struct_minion_ref;
extern int sub_80034140(void);
extern int sub_8001CE70(int a);
// Matched
int sub_80033AFC(struct_minion_ref* p)
{
    int a = sub_800AD288(p->field_0 + p->field_2, 0);
    if (sub_800AD2C8(p->field_0 + p->field_2, 0) <= 0)
    {
        return 1;
    }
    if (a == 0x29 && p->field_A == 1)
    {
        if (sub_80034140())
        {
            return 0;
        }
        return 3;
    }
    if (!(sub_8001CE70(a) & 1) && !(sub_8001CE70(a) & 2))
    {
        return 2;
    }
    if (p->field_A == 0)
    {
        if (!(sub_8001CE70(a) & 2))
        {
            return 4;
        }
    }
    else if (p->field_A == 1)
    {
        if (!(sub_8001CE70(a) & 1))
        {
            return 3;
        }
    }
    return 0;
}
extern int sub_8001AEC0(void* p, int v);
extern int sub_80031A04(void* p, int idx);
#if 0
// Not matched (1 word: sub_8001AC58 is declared unsigned char in funcs.h, original caller does not mask the result)
int sub_80033C08(struct_minion_ref* p)
{
    int a;
    int r;
    char* q = p->field_C_minion->field_84;
    r = sub_8001AEC0(p->field_C_minion->field_F4, p->field_0 + p->field_2);
    a = sub_8001AC58(r);
    if (r >= 30)
    {
        return 6;
    }
    if (*(short*)&q[0xC] < a)
    {
        if (p->field_A == 0)
        {
            return 5;
        }
    }
    return 0;
}
#endif
INCLUDE_ASM(sub_80033C08);
// Matched
int sub_80033C98(struct_minion_ref* p)
{
    int a;
    short idx = p->field_0;
    a = sub_80031A04(p->field_C_minion->field_DE, idx);
    if (!sub_80031954(p->field_C_minion->field_DE, idx))
    {
        return 7;
    }
    if (*(short*)&p->field_C_minion->field_84[0xC] < a)
    {
        if (p->field_A == 0)
        {
            return 5;
        }
    }
    return 0;
}
// Matched
int sub_80033D20(struct_minion_ref* p)
{
    Minion* m = p->field_C_minion;
    char* q = m->field_84;
    int r = sub_8001AEC0(m->field_F4, p->field_0 + p->field_2);
    if (dword_8007C438[r].field_0 & 0x40)
    {
        switch (dword_8007C438[r].field_7)
        {
        case 0:
            if (*(short*)&q[8] == *(short*)&q[0xA])
            {
                return 3;
            }
            break;
        case 1:
            if (r != 0x10 && !(*(int*)m->field_84 & 0x7FB))
            {
                return 3;
            }
            break;
        }
    }
    return 0;
}
// Matched
int sub_80033DEC(void)
{
    return 0;
}
INCLUDE_ASM(sub_80033DF4);
