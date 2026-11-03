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

INCLUDE_DATA(dword_80071F58);
INCLUDE_DATA(dword_80071F5C);
INCLUDE_DATA(dword_80071F60);
INCLUDE_DATA(aAssertionFaile_2);
INCLUDE_DATA(aCommonC);
INCLUDE_DATA(byte_800793C4);
INCLUDE_DATA(dword_800793C8);

// Matched
void sub_80012794(struct_obj_B* p, int a1)
{
    if (p->flags_0 & 0x3F8)
    {
        a1 &= ~0x3F8;
    }
    p->flags_0 |= a1;
}
// Matched
void sub_800127B8(struct_obj_B* p)
{
    p->field_4 = 0;
    p->field_8 = 0;
    p->flags_0 |= 0x400;
}
// Matched
void sub_800127D0(int a0, int a1, int a2, int a3)
{
    int v = sub_80014390(a0 & 0xFF);
    if (v != 0)
    {
        sub_80012614(v, a1, a2, a3);
    }
}
// Matched
void sub_80012828(int* p, unsigned int* f)
{
    if (*f & 1)
    {
        p[0] = p[0] * 4 / 5;
        p[2] = p[2] * 4 / 5;
    }
    if (*f & 2)
    {
        p[1] = p[1] * 2 / 3;
        p[3] = p[3] * 2 / 3;
        p[5] = 0;
    }
    if (*f & 0x3F8)
    {
        p[4] = p[4] * 3 / 5;
        p[5] = p[5] * 3 / 5;
    }
    if (*f & 0x8000)
    {
        p[3] = (0x7FFF < p[3] + p[3] * 5) ? 0x7FFF : p[3] + p[3] * 5;
        p[1] = (0x7FFF < p[1] + p[1] * 5) ? 0x7FFF : p[1] + p[1] * 5;
        p[5] = 0;
    }
}
typedef struct
{
    unsigned char c0;
    unsigned char c1;
    short s2;
    unsigned char c4;
    unsigned char c5;
    unsigned char c6;
    unsigned char c7;
    int f8;
} Stats12;
extern int sub_80014444(int a0);
extern int sub_8001449C(int a0);
// Matched
unsigned char* sub_800129B0(Stats12* out, unsigned char* in, int a2)
{
    int id = 0xD3;
    int kind = in[1];
    int m;
    MemCopy_800403E8((unsigned int*)out, (unsigned int*)sub_800318C8(kind), 12);
    m = sub_80014444(a2 & 0xFF);
    if (m)
    {
        id = ((unsigned char*)m)[2];
    }
    m = sub_8001449C(a2 & 0xFF);
    if (m)
    {
        id = ((int*)m)[0x5C / 4];
    }
    if (id != 0xD3)
    {
        if (kind == 0xF)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 2)
            {
                out->c7 = ((signed char)out->c7 + 60 < 126) ? out->c7 + 60 : 125;
            }
        }
        else if (kind == 0xE)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 1)
            {
                out->c7 = ((signed char)out->c7 + 60 < 126) ? out->c7 + 60 : 125;
            }
        }
        else if (kind == 0xC)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 2)
            {
                out->s2 = 0;
            }
        }
    }
    switch (in[2])
    {
    case 2:
        out->s2 = ((short)out->s2 + 30 < 256) ? (unsigned short)out->s2 + 30 : 255;
        break;
    case 3:
        out->c5 = (out->c5 + 30 > 255) ? 255 : out->c5 + 30;
        out->c6 = (out->c6 + 20 > 255) ? 255 : out->c6 + 20;
        break;
    case 4:
        out->c7 = ((signed char)out->c7 + 50 < 126) ? out->c7 + 50 : 125;
        break;
    }
    return (unsigned char*)out;
}
INCLUDE_ASM(sub_80012BB0);
extern struct_u8x12 dword_80071F58;
extern int sub_80031B30(int a0);
extern struct_12* sub_8001AD64(unsigned int idx);
extern struct_12* sub_8001D260(void);
// Matched
int sub_80013228(int a0, int a1, int* p)
{
    struct_u8x12 local = dword_80071F58;
    unsigned char* q = local.c;
    int b1 = sub_80014358(p[2]);
    int b2 = sub_80014358(p[3]);
    switch (p[0])
    {
    case 0:
        if (p[2] == 1)
        {
            q = (unsigned char*)sub_8001D260();
        }
        break;
    case 6:
        q = sub_800129B0((Stats12*)&local, (unsigned char*)(sub_80031B30(b1 & 0xFF) + p[1] * 4), b2);
        break;
    case 1:
        q = (unsigned char*)sub_8001AD64(p[1]);
        break;
    case 4:
        q = (unsigned char*)GetItemData_8001CDF4(p[1]);
        break;
    case 26:
        break;
    }
    return q[8] == 8;
}

// zero word at the end of this TU's .rdata, in front of the jump table of sub_80013C28 (tu_80013358)
INCLUDE_DATA(dword_800720E4);
