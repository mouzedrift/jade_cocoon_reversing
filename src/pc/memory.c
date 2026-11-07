/* PC only: the RAM the game reaches by address (src/memmap.h) */
#include "memmap.h"

unsigned char psxRam[0x200000];
char pcPrimRam[(0x80200000u - HEAP_END) * PRIM_RAM_SCALE];

/* an address from the game's data: 0 stays NULL, RAM addresses are psxRam's */
void* Pc_PsxPtr(unsigned int addr)
{
    if (addr == 0)
        return 0;
    if ((addr & 0xFFE00000u) == 0x80000000u)
        return &psxRam[addr & 0x1FFFFF];
    return (void*)(unsigned long)addr;
}
