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

INCLUDE_DATA(dword_800741C4);

INCLUDE_ASM(sub_8002AAF0);
INCLUDE_ASM(sub_8002AC88);
// Matched
void sub_8002ACE8(int flags, unsigned char* out)
{
    unsigned char val;
    if (flags & 2)
    {
        val = 0x40;
    }
    else
    {
        val = 0x80;
    }
    out[0] = val;
    out[1] = val;
    out[2] = val;
}
// Matched
void sub_8002AD08(int flags)
{
    if (flags & 2)
    {
        sub_8003F900(1, 1);
    }
    else
    {
        sub_8003F900(1, 0);
    }
}
// Matched
void sub_8002AD44(int flags)
{
    if (flags & 2)
    {
        sub_8003F900(2, 1);
    }
    else
    {
        sub_8003F900(2, 0);
    }
}
// Matched
void sub_8002AD80(int flags)
{
    if (flags & 2)
    {
        sub_8002C5D0(3);
    }
    else
    {
        sub_8002C5D0(0);
    }
}
INCLUDE_ASM(sub_8002ADB4);
INCLUDE_ASM(sub_8002AE38);
// Matched
void sub_8002AF10(int a0, int a1, int a2)
{
    RECT r;
    r.x = 10;
    r.y = 0x99;
    r.w = 0x12C;
    r.h = 0x3C;
    sub_8002AFA0(a0, a1, a2, &r, 4);
}
// Matched
void sub_8002AF58(int a0, int a1, int a2)
{
    RECT r;
    r.x = 10;
    r.y = 0xC3;
    r.w = 0x12C;
    r.h = 0x12;
    sub_8002AFA0(a0, a1, a2, &r, 1);
}
#if 0
void sub_8002AFA0(int a0, int a1, int a2, RECT* a3, int a4)
{
}
#endif
INCLUDE_ASM(sub_8002AFA0);
INCLUDE_ASM(sub_8002B004);
INCLUDE_ASM(sub_8002B1B0);
