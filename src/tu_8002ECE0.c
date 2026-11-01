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

INCLUDE_DATA(dword_800743D4);
INCLUDE_DATA(dword_800743D8);
INCLUDE_DATA(off_800743DC);
INCLUDE_DATA(off_800743E0);
INCLUDE_DATA(dword_800743E4);
INCLUDE_DATA(dword_800743E8);
INCLUDE_DATA(dword_800743EC);
INCLUDE_DATA(dword_800743F0);
INCLUDE_DATA(dword_800743F4);
INCLUDE_DATA(off_800743F8);
INCLUDE_DATA(off_800743FC);
INCLUDE_DATA(dword_80074400);
INCLUDE_DATA(dword_80074404);
INCLUDE_DATA(dword_80074408);
INCLUDE_DATA(dword_8007440C);
INCLUDE_DATA(dword_80074410);
INCLUDE_DATA(off_80074414);
INCLUDE_DATA(off_80074418);
INCLUDE_DATA(dword_8007441C);
INCLUDE_DATA(dword_80074420);
INCLUDE_DATA(dword_80074424);
INCLUDE_DATA(dword_80074428);

INCLUDE_ASM(sub_8002ECE0);
INCLUDE_ASM(sub_8002EE28);
extern void sub_8002C06C(void* p, int a1, short a2);
// Matched
void sub_8002EF5C(unsigned short* pos, short count, short a2)
{
    unsigned short loc[2];
    loc[0] = pos[0];
    loc[1] = pos[1];
    do
    {
        sub_8002C06C(loc, 0xd9, a2);
        count--;
        loc[0] += 7;
    } while (count > 0);
}
INCLUDE_ASM(sub_8002EFC4);
INCLUDE_ASM(sub_8002F078);
INCLUDE_ASM(sub_8002F120);
typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_F1C8;
extern void sub_8002F23C(int a0, int a1, int a2, int a3, int a4, int a5);
extern void sub_8002A384(struct_F1C8* p);
// Matched
void sub_8002F1C8(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    struct_F1C8 s;
    sub_8002F23C(a0, a1, a3, a4, a5, a6);
    s.field_8 = a2;
    s.field_0 = a4;
    s.field_4 = a3;
    s.field_A = a5;
    sub_8002A384(&s);
}

INCLUDE_ASM(sub_8002F23C);
// Matched
short sub_8002F424(unsigned char* p)
{
    short mask = 0;
    short i;
    if (p)
    {
        for (i = 0; i < 4; i++)
        {
            if (p[i])
            {
                mask |= 1 << i;
            }
        }
    }
    return mask;
}
INCLUDE_ASM(sub_8002F480);
