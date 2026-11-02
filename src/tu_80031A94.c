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


typedef struct Ent4
{
    unsigned char a;
    unsigned char type;
    unsigned char b;
    unsigned char c;
} Ent4;
extern Ent4* sub_80031B30(int a0);

// Matched
int sub_80031A94(int* p)
{
    int r = 2;
    Ent4* base;
    if (p[2] & 0xF)
    {
        r = 4;
    }
    base = sub_80031B30(sub_80014358(p[2]) & 0xFF);
    base += p[1];
    if (base->type == 0xC)
    {
        r |= 1;
    }
    return r;
}
// Matched
int sub_80031B0C(Ent4* base, int idx)
{
    int r = 4;
    base += idx;
    if (base->type == 0xC)
    {
        r = 5;
    }
    return r;
}
extern Ent4* sub_800A11A0(int a0);
extern Ent4* sub_800A2BA0(int a0);

extern Ent4* sub_800A11A0(int a0);
extern Ent4* sub_800A2BA0(int a0);

extern Ent4* sub_800A11A0(int a0);
extern Ent4* sub_800A2BA0(int a0);

#if 0
Ent4* sub_80031B30(int a0)
{
    Ent4* r = 0;
    unsigned int v = a0 & 0xFF;
    if (v >= 8)
    {
        r = sub_800A11A0((a0 - 8) & 0xFF);
    }
    else if (v >= 4)
    {
        int flags = sub_800A248C();
        int bit = 1 << v;
        if (flags & bit) { r = sub_800A2BA0((a0 - 4) & 0xFF); }
    }
    else if (v != 0)
    {
        r = (Ent4*)sub_800107F8(3, (a0 - 1) & 0xFF);
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
INCLUDE_ASM(sub_80032D34);
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
// Matched
void sub_80033080(unsigned short* a, int i, int j)
{
    ((unsigned short*)&dword_8008D434[i])[4] = a[0];
    ((unsigned short*)&dword_8008D434[i])[5] = a[1];
    sub_80040298(pOT_8008D454 + j, &dword_8008D434[i], 5);
    sub_80040298(pOT_8008D454 + j, &dword_8008D440[i], 2);
}
// Matched
void sub_80033114(unsigned short* a, int idx, void* c, unsigned char* col)
{
    ((unsigned char*)&dword_8008D434[idx])[4] = col[0];
    ((unsigned char*)&dword_8008D434[idx])[5] = col[1];
    ((unsigned char*)&dword_8008D434[idx])[6] = col[2];
    ((unsigned short*)&dword_8008D434[idx])[4] = a[0];
    ((unsigned short*)&dword_8008D434[idx])[5] = a[1];
    sub_80040298(c, &dword_8008D434[idx], 5);
    sub_80040298(c, &dword_8008D440[idx], 2);
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
INCLUDE_ASM(sub_80033394);
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
INCLUDE_ASM(sub_8003355C);
extern void sub_80033754(unsigned char* a, unsigned char* b);
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
    sub_80033754((char*)m + 0x20, m);
}
#if 0
void sub_80033624(void* arg0, int arg1)
{
}
#endif
INCLUDE_ASM(sub_80033624);
// Matched
void sub_80033754(unsigned char* dst, unsigned char* src)
{
    unsigned char* tbl[2];
    int i;
    int j;
    sub_800403E8((unsigned int*)dst, (unsigned int*)(src + 0x20), 12);
    src += 0x1C;
    tbl[0] = (unsigned char*)sub_8001CDA0(src[1]);
    tbl[1] = (unsigned char*)sub_8001CD74(src[2]);
    for (j = 0; j < 2; j++)
    {
        if (tbl[j])
        {
            for (i = 0; i < 12; i++)
            {
                if ((signed char)tbl[j][i] < (signed char)dst[i])
                {
                    dst[i] = tbl[j][i];
                }
            }
        }
    }
}
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
    sub_800338DC(p + 0x4C, a, b);
    return a[0];
}
#if 0
void sub_800338DC(void* arg0, void* arg1, void* arg2)
{
}
#endif
INCLUDE_ASM(sub_800338DC);
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
INCLUDE_ASM(sub_80033AFC);
typedef struct
{
    short field_0;
    short field_2;
    short pad_4[3];
    short field_A;
    Minion* field_C_minion;
} struct_minion_ref;
extern int sub_8001AEC0(void* p, int v);
extern int sub_80031A04(void* p, int idx);
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
INCLUDE_ASM(sub_80033D20);
// Matched
int sub_80033DEC(void)
{
    return 0;
}
INCLUDE_ASM(sub_80033DF4);
