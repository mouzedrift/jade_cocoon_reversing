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
INCLUDE_ASM(sub_80012828);
INCLUDE_ASM(sub_800129B0);
INCLUDE_ASM(sub_80012BB0);
extern struct_u8x12 dword_80071F58;
extern int sub_80031B30(int a0);
extern unsigned char* sub_800129B0(void* a0, int a1, int a2);
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
        q = sub_800129B0(&local, sub_80031B30(b1 & 0xFF) + p[1] * 4, b2);
        break;
    case 1:
        q = (unsigned char*)sub_8001AD64(p[1]);
        break;
    case 4:
        q = (unsigned char*)sub_8001CDF4(p[1]);
        break;
    case 26:
        break;
    }
    return q[8] == 8;
}
