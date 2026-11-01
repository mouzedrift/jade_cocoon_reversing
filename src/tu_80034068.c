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

INCLUDE_DATA(dword_8007474C);
INCLUDE_DATA(dword_80074780);
INCLUDE_DATA(dword_80074794);
INCLUDE_DATA(dword_800747D0);
INCLUDE_DATA(dword_800747E8);
INCLUDE_DATA(dword_80074800);

INCLUDE_ASM(sub_80034068);
// Matched
int sub_80034124(void)
{
    return 0;
}
// Matched
int sub_8003412C(char* p)
{
    if (p)
    {
        return *(short*)(p + 0x42);
    }
    return 0;
}
INCLUDE_ASM(sub_80034140);
INCLUDE_ASM(sub_8003422C);
INCLUDE_ASM(sub_80034900);
// Matched
int sub_80034B14(int* p)
{
    int n = 0;
    while (*p)
    {
        p++;
        n++;
    }
    return n;
}
// Matched
int sub_80034B40(int* p, unsigned int mask)
{
    int n = 0;
    int i = 0;
    if (*p)
    {
        do
        {
            if (mask & (1 << i))
            {
                n++;
            }
            p++;
            i++;
        } while (*p);
    }
    return n;
}
// Matched
int sub_80034B88(int n, unsigned int mask)
{
    int i = 0;
    if (n >= 0)
    {
        do
        {
            if (mask & (1 << i))
            {
                n--;
            }
            i++;
        } while (n >= 0);
    }
    return i - 1;
}
INCLUDE_ASM(sub_80034BB8);
INCLUDE_ASM(sub_80034C18);
