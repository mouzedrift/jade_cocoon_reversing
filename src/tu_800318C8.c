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
struct_12* sub_800318C8(int idx)
{
    return &stru_80083594[idx];
}
// Matched
int sub_800318E4(unsigned int idx, int nth)
{
    Minion* m = sub_80010598(3, nth - 1);
    if (m && sub_80031954(m->field_DE, idx))
    {
        if (idx < 0xff)
        {
            return 0;
        }
    }
    return 0;
}
// Matched
void SeVibOn(void)
{
}
// Matched
void SetVib(void)
{
}
// Matched
void SsUtVibrateOn(void)
{
}
// Matched
void SsUtVibrateOff(void)
{
}
// Matched
int sub_80031954(void* pv, int idx)
{
    unsigned char* q = (unsigned char*)pv + idx * 4;
    return *q & 1;
}
INCLUDE_ASM(sub_80031968);
INCLUDE_ASM(sub_80031A04);
