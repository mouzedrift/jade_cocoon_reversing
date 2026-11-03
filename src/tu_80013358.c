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
int sub_80013358(int idx)
{
    return dword_80079320[idx];
}
INCLUDE_ASM(sub_80013374);
extern void sub_80012BB0(int a0, int a1, int* p, int a3);
// Matched
void sub_80013C28(int a0, int a1, int* p, int a3)
{
    int r;
    if (p[0] == 4)
    {
        switch (p[1])
        {
        case 3:
            r = rand() % 6;
            if (r == 0)
            {
                r = 1;
            }
            else if (r == 5)
            {
                r = 3;
            }
            else
            {
                r = 2;
            }
            sub_80012614(a1, 1, r, 0);
            sub_80012614(a1, 0, r, 0);
            break;
        case 4:
            sub_80012614(a1, 5, sub_80013DB0(), 0);
            break;
        case 5:
            sub_80012614(a1, 7, sub_80013DB0(), 0);
            break;
        case 6:
            sub_80012614(a1, 9, sub_80013DB0(), 0);
            break;
        case 7:
            sub_80012614(a1, 0xB, sub_80013DB0(), 0);
            break;
        case 8:
            sub_80012614(a1, 0xD, sub_80013DB0(), 0);
            break;
        }
        sub_80011B24(p[1]);
        sub_80012BB0(a0, a1, p, a3);
    }
}
