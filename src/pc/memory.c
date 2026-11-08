/* PC only: the RAM the game reaches by address (src/memmap.h) */
#include "memmap.h"

unsigned char psxRam[0x200000];
char pcPrimRam[(0x80200000u - HEAP_END) * PRIM_RAM_SCALE];

/* an address from the game's data: 0 stays NULL, RAM addresses are psxRam's */
#include "pc/mapcode.h"

void* Pc_PsxPtr(unsigned int addr)
{
    if (addr == 0)
        return 0;
    if (addr >= 0x800B22C0u && addr < 0x800CD858u && Pc_MapPtr(addr)) /* the map's code and data (src/maps) */
        return Pc_MapPtr(addr);
    if ((addr & 0xFFE00000u) == 0x80000000u)
        return &psxRam[addr & 0x1FFFFF];
    return (void*)(unsigned long)addr;
}
