// GAME.BIN, source file 2 of 3 from 0x800A55B0 (.rdata from 0x800A061C)
#include "game.h"

GameTable_1* sub_800A55B0(int a)
{
    GameTable_1* r = 0;
    switch (a)
    {
    case 0:
        r = (GameTable_1*)name_800AEB80;
        break;
    case 1:
        r = (GameTable_1*)name_800AEBBC;
        break;
    case 2:
        r = (GameTable_1*)name_800AEBC0;
        break;
    case 3:
        r = (GameTable_1*)name_800AEBC8;
        break;
    case 4:
        r = (GameTable_1*)name_800AEBCC;
        break;
    }
    return r;
}

INCLUDE_OVERLAY_ASM(game, dword_800A0630);

extern void sub_800BC7A8(int a, int b);
extern void LoadRelocBlob_800BC854(int a, int b);
extern void sub_800BC98C(int a, int b);
extern void sub_800BCA18(int a, int b);
extern void sub_800BCA68(int a, int b);

void sub_800A5628(int kind, int a, int b)
{
    switch (kind)
    {
    case 0:
        sub_800BC7A8(a, b);
        break;
    case 1:
        LoadRelocBlob_800BC854(a, b);
        break;
    case 2:
        sub_800BC98C(a, b);
        break;
    case 3:
        sub_800BCA18(a, b);
        break;
    case 4:
        sub_800BCA68(a, b);
        break;
    }
}
INCLUDE_OVERLAY_ASM(game, dword_800A0648);

void sub_800A56BC(int kind)
{
    switch (kind)
    {
    case 0:
        if (dword_800AEB7C != 2)
            sub_800A5854();
        if (name_800AEB80[1])
            ListFreeAll_8003FEC8(&name_800AEB80[1]);
        break;
    case 1:
        if (name_800AEBBC)
        {
            ListFree_8003FE38(name_80091C10, name_800AEBBC);
            name_800AEBBC = 0;
        }
        break;
    case 2:
        if (name_800AEBC0[0])
        {
            ListFree_8003FE38(name_80091C10, name_800AEBC0[0]);
            name_800AEBC0[0] = 0;
        }
        if (name_800AEBC0[1])
        {
            ListFree_8003FE38(name_80091C10, name_800AEBC0[1]);
            name_800AEBC0[1] = 0;
        }
        break;
    case 3:
        if (name_800AEBC8)
        {
            ListFree_8003FE38(name_80091C10, name_800AEBC8);
            name_800AEBC8 = 0;
        }
        break;
    case 4:
        if (name_800AEBCC[1])
        {
            sub_80026DE8(&name_800AEBCC[1], name_800AEBCC[0], name_80091C10);
            name_800AEBCC[0] = 0;
        }
        break;
    }
}
