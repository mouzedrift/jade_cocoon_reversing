/* PC only: the functions of the code that map (and battle script) files bring along, which the loader copies
   to 0x800B22C0 and the game calls at fixed addresses (config/fixed_symbols.txt). That code is not
   decompiled yet: these stand in for it. */
#include <psyz.h>
#include <psyz/log.h>

#define MAP_CODE_STUB(name)                                                                                           \
    void* name(void)                                                                                                  \
    {                                                                                                                 \
        WARNF("map code %s is not decompiled yet", #name);                                                            \
        return 0;                                                                                                     \
    }

/* a call by address (MAP_CODE_CALL): reported once per address */
int Pc_MapCodeCall(unsigned int addr, int arg)
{
    static unsigned int reported[64];
    int i;
    for (i = 0; i < 64 && reported[i] && reported[i] != addr; i++)
        ;
    if (i < 64 && !reported[i])
    {
        reported[i] = addr;
        WARNF("map code %08X(%d) is not decompiled yet", addr, arg);
    }
    return 0;
}

MAP_CODE_STUB(sub_800B2B40)
MAP_CODE_STUB(sub_800B3198)
MAP_CODE_STUB(sub_800B322C)
MAP_CODE_STUB(sub_800B3260)
MAP_CODE_STUB(sub_800B3274)
MAP_CODE_STUB(sub_800B32A4)
MAP_CODE_STUB(sub_800B32D4)
MAP_CODE_STUB(sub_800B32F0)
MAP_CODE_STUB(sub_800B330C)
MAP_CODE_STUB(sub_800B41A8)
MAP_CODE_STUB(sub_800B41D0)
MAP_CODE_STUB(sub_800B4200)
MAP_CODE_STUB(sub_800B42A8)
MAP_CODE_STUB(sub_800B4318)
MAP_CODE_STUB(sub_800B4390)
