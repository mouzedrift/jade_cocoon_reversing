/* PC only: the functions of the code that map (and battle script) files bring along, which the loader copies
   to 0x800B22C0 and the game calls at fixed addresses (config/fixed_symbols.txt). That code is not
   decompiled yet: these stand in for it. */
#include <psyz.h>
#include <psyz/log.h>
#include <stdlib.h>
#include <string.h>
#include "pc/mapcode.h"

#define MAP_CODE_STUB(name)                                                                                           \
    void* name(void)                                                                                                  \
    {                                                                                                                 \
        WARNF("map code %s is not decompiled yet", #name);                                                            \
        return 0;                                                                                                     \
    }

static const PcMap* curMap;
static void* saved[64][64]; /* each map's data as it was before it first ran (a map file brings it fresh) */

/* the map loader copied the code of the map file (OnMapFileLoaded_80028808) */
void Pc_MapCodeLoaded(int fileId)
{
    int m, i;
    curMap = 0;
    for (m = 0; pcMaps[m]; m++)
    {
        if (pcMaps[m]->fileId == fileId)
            break;
    }
    if (!pcMaps[m])
    {
        WARNF("map file %d: its code is not decompiled yet", fileId);
        return;
    }
    curMap = pcMaps[m];
    for (i = 0; i < curMap->count && i < 64 && m < 64; i++)
    {
        const PcMapSym* s = &curMap->syms[i];
        if (!s->size)
            continue;
        if (!saved[m][i])
        {
            saved[m][i] = malloc(s->size);
            memcpy(saved[m][i], s->ptr, s->size);
        }
        else
            memcpy(s->ptr, saved[m][i], s->size);
    }
}

/* the current map's function or data at a PlayStation address (0: not one of its names) */
void* Pc_MapPtr(unsigned int addr)
{
    int i;
    if (!curMap)
        return 0;
    for (i = 0; i < curMap->count; i++)
    {
        const PcMapSym* s = &curMap->syms[i];
        if (addr == s->addr || (addr > s->addr && addr < s->addr + s->size))
            return (char*)s->ptr + (addr - s->addr);
    }
    return 0;
}

/* a call by address (MAP_CODE_CALL); one that is not in the current map's code is reported once */
int Pc_MapCodeCall(unsigned int addr, int arg)
{
    static unsigned int reported[64];
    void* fn = Pc_MapPtr(addr);
    int i;
    if (fn)
        return ((int (*)(int))fn)(arg);
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
