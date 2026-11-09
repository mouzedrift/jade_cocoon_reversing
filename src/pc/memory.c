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

/* the event message table on PC (LoadRelocBlob_800BC854): blob[0] entries of { offset of the message's words,
   their count } behind it, each word the offset of a line in the blob or -1 for 0; the table built here has the
   layout GameMsgTable has on PC (pointers), with the lines' pointers behind it */
#include <stdlib.h>

void* pcEventMsgTable;

typedef struct
{
    void** text;
    int count;
} PcMsgEntry;

void* Pc_EventMsgTable(int* blob)
{
    char* base = (char*)blob;
    int n = blob[0];
    size_t words = 0;
    size_t head;
    char* tbl;
    PcMsgEntry* e;
    void** out;
    int i;
    int j;
    for (i = 0; i < n; i++)
        words += blob[i * 2 + 2];
    head = sizeof(void*) + (n > 0 ? n : 0) * sizeof(PcMsgEntry); /* the count, padded to the entries' alignment */
    free(pcEventMsgTable);
    tbl = calloc(1, head + words * sizeof(void*));
    *(unsigned int*)tbl = n; /* GameMsgTable.count, the entries follow at offsetof(GameMsgTable, e) */
    e = (PcMsgEntry*)(tbl + sizeof(void*));
    out = (void**)(tbl + head);
    for (i = 0; i < n; i++)
    {
        int* src = (int*)(base + blob[i * 2 + 1]);
        int m = blob[i * 2 + 2];
        e[i].text = out;
        e[i].count = m;
        for (j = 0; j < m; j++)
            *out++ = src[j] == -1 ? 0 : base + src[j];
    }
    return tbl;
}
