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


// Matched
void sub_80018430(short a0)
{
    ((short*)dword_8008D3F8[9])[0x40 / 2] = a0;
}
// Matched
void sub_80018448(short a0)
{
    ((short*)dword_8008D3F8[9])[0x42 / 2] = a0;
}
// Matched
void sub_80018460(int a0)
{
    int* p = dword_8008D3F8[9];
    if (a0 != 0)
    {
        p[0x28 / 4] |= 8;
    }
    else
    {
        p[0x28 / 4] &= ~8;
    }
}
// Matched
void sub_800184A0(int arg, int bit)
{
    unsigned char* base = (unsigned char*)dword_8008D3F8[0x24 / 4];
    if (bit == 0)
    {
        (base + arg)[0x44] = 0;
    }
    else
    {
        (base + arg)[0x44] |= 1 << bit;
    }
}
// Matched
int sub_800184DC(int a0, int a1)
{
    int* p = dword_8008D3F8[9];
    sub_8001852C(a0, *((unsigned char*)p + a1 + 0x44));
    p[0x28 / 4] |= 1;
    return 1;
}
INCLUDE_ASM(sub_8001852C);
#if 0
// Not matched: registers of i and the row pointer are swapped
int sub_80018908(int id, short (*tbl)[6])
{
    int i;
    int r = -1;
    if (tbl != 0 && tbl[0][0] != -1)
    {
        for (i = 0; tbl[i][0] != -1; i++)
        {
            if (id == tbl[i][0])
            {
                if (tbl[i][2] == -1 && tbl[i][3] == -1 && tbl[i][4] == -1 && tbl[i][5] == -1)
                {
                    int link = tbl[i][1];
                    short* p = tbl[0];
                    for (i = 0; *p != -1; i++)
                    {
                        if (link == *p)
                        {
                            r = i;
                            break;
                        }
                        p += 6;
                    }
                }
                else
                {
                    r = i;
                }
                break;
            }
        }
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80018908);
// Matched
int sub_800189F8(void)
{
    SaveData* sd = &saveData_8008B570;
    struct_24* p = sub_8001CF84(*((unsigned char*)sd + 0x7E4));
    sub_800BFAF8(*((unsigned char*)sd + 0x7E4));
    return dword_80079708[((short*)p)[1]];
}
INCLUDE_ASM(sub_80018A4C);
INCLUDE_ASM(sub_80018C00);
