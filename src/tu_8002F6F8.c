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

INCLUDE_DATA(dword_8007442C);
INCLUDE_DATA(dword_80074430);
INCLUDE_DATA(dword_80074434);

typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_F6F8;
extern void sub_8002A384(struct_F6F8* p);
// Matched
void sub_8002F6F8(int a0, int* st)
{
    unsigned char col[4];
    struct_F6F8 s;
    short v = 20;
    if (st[2])
    {
        (*(short*)st[0])++;
        if (*(short*)st[0] == 40)
        {
            *(short*)st[0] = 0;
        }
        v = *(short*)st[0];
        if (v > 20)
        {
            v = 40 - v;
        }
    }
    col[0] = col[1] = col[2] = v * 8;
    if (!st[1])
    {
        col[0] = col[1] = col[2] = 0xA0;
    }
    s.field_8 = 1;
    s.field_0 = a0;
    s.field_4 = v;
    s.field_A = 0xF;
    sub_8002A384(&s);
}
extern unsigned char byte_8008BD38[];
extern unsigned char dword_80082F04[];
extern unsigned char dword_80082EBC[];
extern void sub_8002C06C(void* p, int a1, int a2);
extern void sub_8002C100(unsigned short* pos, int v, int ot);
// Matched
void sub_8002F7D0(unsigned short* pos, short ot)
{
    unsigned short loc[2];
    unsigned char vals[0x18];
    short i;
    sub_80033624(vals, (int)byte_8008BD38);
    for (i = 0; i < 5; i++)
    {
        loc[0] = pos[0] + 6;
        loc[1] = pos[1] + dword_80082F04[i] + 1;
        sub_8002C06C(loc, dword_80082EBC[i], ot);
        loc[0] = pos[0] + 0x45;
        loc[1] = pos[1] + dword_80082F04[i] + 2;
        sub_8002C100(loc, vals[i], ot);
    }
}
INCLUDE_ASM(sub_8002F8E4);
// Matched
short sub_8002FA70(void)
{
    return sub_80033514((Minion*)sub_80033ABC((char*)&saveData_8008B570));
}
INCLUDE_ASM(sub_8002FAA0);
INCLUDE_ASM(sub_8002FBD8);
