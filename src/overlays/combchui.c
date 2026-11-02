// COMBCHUI.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int sub_8003E4C8(int);
extern void sub_8002AC88(int, void*, int, void*);
extern void sub_8003E91C(int, int, void*, int);

INCLUDE_OVERLAY_ASM(combchui, dword_800A4088);

INCLUDE_OVERLAY_ASM(combchui, sub_800A4394);

void sub_800A450C(int* p, unsigned short* q)
{
    short rect[4];
    int item;
    unsigned short y;
    sub_8003F900(2, 0);
    item = *p;
    y = q[1];
    while (item)
    {
        sub_8002AC88(8, q, (short)sub_8003E4C8(item), rect);
        rect[1] = y;
        sub_8003E91C(2, item, rect, 0);
        p++;
        item = *p;
        y += 0x10;
    }
}

INCLUDE_OVERLAY_ASM(combchui, dword_800A45B0);
