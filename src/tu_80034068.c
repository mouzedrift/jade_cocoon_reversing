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

#if 0
// Not matched: register allocation of r/e/idx (a0/a2/a1)
int sub_80034068(short* a)
{
    int* r = (int*)sub_80014390(((unsigned char*)a)[2]);
    if (dword_8007C438[a[0]].field_0 & 0x40)
    {
        switch (dword_8007C438[a[0]].field_7)
        {
        case 0:
            if (((short*)r)[4] != ((short*)r)[5])
            {
                return 0;
            }
            return 3;
        case 1:
            if (a[0] == 0x10)
            {
                return 0;
            }
            if ((r[0] & 0x7FB) == 0)
            {
                return 3;
            }
            break;
        default:
            return 0;
        }
    }
    return 0;
}
#endif
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
extern void sub_80034C18(int* a);
extern void sub_800353A0(int* a);
// Matched
void sub_80034BB8(int* a0, int* a1)
{
    sub_80034C18(a1);
    sub_800353A0(a1);
    if (a1[2] == 7)
    {
        a0[0] = (a0[0] & ~1) | 0x8000;
    }
}
INCLUDE_ASM(sub_80034C18);
