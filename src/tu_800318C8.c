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
#include "tu_800318C8.h"


// Matched
ActionData* sub_800318C8(int idx)
{
    return &stru_80083594[idx];
}
// Matched
int sub_800318E4(unsigned int idx, int nth)
{
    Minion* m = GetMinion_80010598(3, nth - 1);
    if (m && sub_80031954(&m->skills_DE, idx))
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
// Matched
int sub_80031968(void* p)
{
    int n;
    int i = 0;
    for (n = i; i < 0xff; i++)
    {
        if (sub_80031954(p, i))
        {
            n++;
        }
    }
    return n;
}
extern int abilityNames_800834E4[];
extern int abilityBonusNames_80083580[];
// Matched
int GetAbilityName_800319CC(int idx)
{
    return abilityNames_800834E4[idx];
}
// Matched
int GetAbilityBonusName_800319E8(int idx)
{
    return abilityBonusNames_80083580[idx];
}
// Matched
int sub_80031A04(unsigned char* p, int idx)
{
    int r;
    p += idx * 4;
    r = 0;
    if (p[0] != 0)
    {
        switch (p[1])
        {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            r += 10;
            break;
        case 14:
        case 15:
            r += 5;
            break;
        case 13:
            r += 35;
            break;
        case 12:
            r += 15;
            break;
        }
        switch (p[2])
        {
        case 2:
        case 3:
        case 4:
            r += 10;
            break;
        }
    }
    return r;
}
