#ifndef MEMMAP_H
#define MEMMAP_H

/* Places in the PlayStation's RAM that belong to no image and that the game reaches by their address: the heap
   above the overlays, the buffers above the heap (file loads, primitives, movie decoding), the map code area.
   PSX_RAM(0x801B9250) is that address on the PlayStation; on PC (__psyz) the same place in psxRam, the 2 MB that
   stand in for the RAM there. */
#ifdef __psyz
extern unsigned char psxRam[0x200000];
#define PSX_RAM(addr) ((void*)&psxRam[(unsigned int)(addr) & 0x1FFFFF])
#else
#define PSX_RAM(addr) ((void*)(addr))
#endif

#define HEAP_END 0x801B9250 /* the heap runs from heapStart_800CD858 up to here, the buffers follow */
#ifdef __psyz
#define heapStart_800CD858 ((char*)PSX_RAM(0x800CD858))
#endif

#endif
