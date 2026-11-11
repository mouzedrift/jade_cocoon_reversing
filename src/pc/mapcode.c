/* PC only: the code that map (and battle script) files bring along, which the loader copies to 0x800B22C0 on the
   PlayStation: here the current map's C (src/maps, scripts/pc_maps.py tables), reached by its PlayStation
   addresses (event scripts, the hooks the game calls at fixed addresses, config/fixed_symbols.txt). */
#include <psyz.h>
#include <psyz/log.h>
#include <stdlib.h>
#include <string.h>
#include "pc/mapcode.h"
#include "memmap.h"

static const PcMap* curMap;
static void*** saved; /* per map, its data as it was before it first ran (a map file brings it fresh) */

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
    if (!saved)
    {
        int n = m;
        while (pcMaps[n])
            n++;
        saved = calloc(n, sizeof(*saved));
    }
    if (!saved[m])
        saved[m] = calloc(curMap->count, sizeof(**saved));
    for (i = 0; i < curMap->count; i++)
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
        if (addr == curMap->syms[i].addr)
            return curMap->syms[i].ptr;
    /* inside one: on the PlayStation it ends where the next name starts (the table is in address order; the PC
       object may be bigger) */
    for (i = 0; i < curMap->count; i++)
    {
        const PcMapSym* s = &curMap->syms[i];
        unsigned int end = s->addr + s->size;
        if (i + 1 < curMap->count && curMap->syms[i + 1].addr < end)
            end = curMap->syms[i + 1].addr;
        if (addr > s->addr && addr < end)
            return (char*)s->ptr + (addr - s->addr);
    }
    return 0;
}

/* the PlayStation address of the current map's object (or a place in one) at p; 0: not one of its */
unsigned int Pc_MapAddr(const void* p)
{
    int i;
    if (!curMap || !p)
        return 0;
    for (i = 0; i < curMap->count; i++)
    {
        const PcMapSym* s = &curMap->syms[i];
        if (p == s->ptr)
            return s->addr;
        if (s->size && (const char*)p > (const char*)s->ptr && (const char*)p < (const char*)s->ptr + s->size)
            return s->addr + (unsigned int)((const char*)p - (const char*)s->ptr);
    }
    return 0;
}

/* a call by address (MAP_CODE_CALL); one that is not in the current map's code is reported once */
int Pc_MapCodeCall(unsigned int addr, long arg)
{
    static unsigned int reported[64];
    void* fn = Pc_MapPtr(addr);
    int i;
    if (arg == (long)(int)arg && (unsigned int)arg >= 0x80000000u && (unsigned int)arg < 0x80200000u)
        arg = (long)Pc_PsxPtr((unsigned int)arg); /* an address from a script (an int operand, sign-extended) */
    if (fn)
        return ((int (*)(long))fn)(arg);
    for (i = 0; i < 64 && reported[i] && reported[i] != addr; i++)
        ;
    if (i < 64 && !reported[i])
    {
        reported[i] = addr;
        WARNF("map code %08X(%ld) is not decompiled yet", addr, arg);
    }
    return 0;
}

/* the functions GAME, BATTLE, MENU and the executable call at fixed addresses (config/fixed_symbols.txt): the
   current map's function there (the hunting map's species tables, a battle chain's hooks), else 0 */
static void* MapFunc(unsigned int addr)
{
    int i;
    if (curMap)
    {
        for (i = 0; i < curMap->count; i++)
            if (curMap->syms[i].addr == addr && !curMap->syms[i].size)
                return curMap->syms[i].ptr;
    }
    WARNF("no map code at %08X (map %s)", addr, curMap ? curMap->name : "none");
    return 0;
}

#define MAP_HOOK_0(ret, name, addr)                                                                                \
    ret name(void)                                                                                                 \
    {                                                                                                              \
        ret (*fn)(void) = (ret (*)(void))MapFunc(addr);                                                            \
        return fn ? fn() : 0;                                                                                      \
    }
#define MAP_HOOK_1(ret, name, addr, t1)                                                                            \
    ret name(t1 a)                                                                                                 \
    {                                                                                                              \
        ret (*fn)(t1) = (ret (*)(t1))MapFunc(addr);                                                                \
        return fn ? fn(a) : 0;                                                                                     \
    }
#define MAP_HOOK_2(ret, name, addr)                                                                                \
    ret name(void* a, void* b)                                                                                     \
    {                                                                                                              \
        ret (*fn)(void*, void*) = (ret (*)(void*, void*))MapFunc(addr);                                            \
        return fn ? fn(a, b) : 0;                                                                                  \
    }

MAP_HOOK_0(void*, sub_800B2B40, 0x800B2B40)
MAP_HOOK_0(void*, sub_800B3198, 0x800B3198)
MAP_HOOK_0(void*, sub_800B322C, 0x800B322C)
MAP_HOOK_1(void*, sub_800B3260, 0x800B3260, int)
MAP_HOOK_1(void*, sub_800B3274, 0x800B3274, int)
MAP_HOOK_1(void*, sub_800B32A4, 0x800B32A4, int)
MAP_HOOK_1(void*, sub_800B32D4, 0x800B32D4, int)
MAP_HOOK_1(void*, sub_800B32F0, 0x800B32F0, int)
MAP_HOOK_0(int, sub_800B330C, 0x800B330C)
MAP_HOOK_1(void*, sub_800B41A8, 0x800B41A8, void*)
MAP_HOOK_1(int, sub_800B41D0, 0x800B41D0, void*)
MAP_HOOK_1(void*, sub_800B4200, 0x800B4200, void*)
MAP_HOOK_2(int, sub_800B4318, 0x800B4318)

void sub_800B42A8(void* cmd, void* chain)
{
    void (*fn)(void*, void*) = (void (*)(void*, void*))MapFunc(0x800B42A8);
    if (fn)
        fn(cmd, chain);
}

void sub_800B4390(void* actor, void* target, void* cmd, void* res, void* chain)
{
    void (*fn)(void*, void*, void*, void*, void*) = (void (*)(void*, void*, void*, void*, void*))MapFunc(0x800B4390);
    if (fn)
        fn(actor, target, cmd, res, chain);
}
