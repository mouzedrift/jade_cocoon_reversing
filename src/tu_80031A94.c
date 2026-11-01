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


INCLUDE_ASM(sub_80031A94);
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
INCLUDE_ASM(sub_80032EF4);
INCLUDE_ASM(sub_80032F88);
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
INCLUDE_ASM(sub_80033080);
INCLUDE_ASM(sub_80033114);
INCLUDE_ASM(sub_800331C4);
INCLUDE_ASM(sub_8003326C);
INCLUDE_ASM(sub_80033308);
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
extern void sub_80033754(void* a, void* b);
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
INCLUDE_ASM(sub_80033C08);
INCLUDE_ASM(sub_80033C98);
INCLUDE_ASM(sub_80033D20);
// Matched
int sub_80033DEC(void)
{
    return 0;
}
INCLUDE_ASM(sub_80033DF4);
