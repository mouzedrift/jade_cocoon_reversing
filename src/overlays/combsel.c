// COMBSEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombSelTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombSelTask;

typedef struct CombSelUnit
{
    char pad_0[0xF8];
} CombSelUnit;

typedef struct CombSelItem
{
    char pad_0[0x10];
    short field_10;
} CombSelItem;

extern short* dword_800A566C[3];
extern short* dword_800A57E4[6];
extern short* dword_800A5930[5];
extern volatile unsigned char byte_800A38D9;
extern CombSelUnit dword_800A3AA0[2][3];
extern int dword_800A3A94;
extern unsigned char byte_800A38DB;
extern char dword_800A5978[];
extern void sub_800A16FC();
extern int sub_800A1934(void*);
extern void sub_800A4D64(void*);
extern void sub_800A5538();
extern int sub_8003DA54(void*);
extern void sub_80031494(int);

INCLUDE_OVERLAY_ASM(combsel, dword_800A4088);

INCLUDE_OVERLAY_ASM(combsel, sub_800A4360);

void sub_800A4C74()
{
    short v[2];
    int i;
    for (i = 0; i < 3; i++)
    {
        v[0] = 0xA;
        v[1] = 0xA6;
        dword_800A566C[i][8] = v[byte_800A38D9];
    }
    for (i = 0; i < 6; i++)
    {
        v[0] = 0x9B;
        v[1] = 0x15;
        dword_800A57E4[i][8] = v[byte_800A38D9];
    }
    for (i = 0; i < 5; i++)
    {
        v[0] = 0xA;
        v[1] = 0xCA;
        dword_800A5930[i][8] = v[byte_800A38D9];
    }
}

INCLUDE_OVERLAY_ASM(combsel, sub_800A4D64);

void sub_800A4E4C()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        sub_800A4D64(dword_800A3AA0[i]);
    }
}

INCLUDE_OVERLAY_ASM(combsel, sub_800A4E94);

INCLUDE_OVERLAY_ASM(combsel, sub_800A5080);

INCLUDE_OVERLAY_ASM(combsel, sub_800A5188);

INCLUDE_OVERLAY_ASM(combsel, sub_800A53B0);

void sub_800A54A0(CombSelTask* t)
{
    if (sub_8003D288(0, dword_800A3A94))
    {
        sub_80031494(0x7E);
        if ((short)sub_8003DA54(dword_800A5978) == 0)
        {
            sub_80043564(1, 0x678, 0x1F);
            t->next_8 = sub_800A5538;
        }
        else
        {
            byte_800A38DB = 0;
        }
    }
    else if (sub_8003D3C0(1, dword_800A3A94))
    {
        byte_800A38DB = 0;
    }
}

void sub_800A5538(CombSelTask* t)
{
    t->next_8 = sub_800A16FC;
    t->next_8(t);
}

// Near miss: the compiler copies p to a callee-saved register before the loop test
#if 0
int sub_800A5560(CombSelUnit* p, int n)
{
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (sub_800A1934(p) == 0)
        {
            return 0;
        }
    }
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(combsel, sub_800A5560);

INCLUDE_OVERLAY_ASM(combsel, dword_800A55C4);
