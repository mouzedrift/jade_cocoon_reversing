// EVENTFNC.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct EvInsEventfnc
{
    int op_0;
    int a_4;
    int b_8;
    int c_C;
} EvInsEventfnc;

typedef struct EvEntEventfnc
{
    char pad_0[0x7C];
    int f7C_7C;
    int f80_80;
    int f84_84;
    int pad_88;
    int f8C_8C;
} EvEntEventfnc;

typedef struct EvCtxEventfnc
{
    unsigned int flags_0;
    EvInsEventfnc* start_4;
    EvInsEventfnc* pc_8;
    EvInsEventfnc* ret_C;
    int f10_10;
    int f14_14;
    int f18_18;
    char pad_1C[0xE4 - 0x1C];
    int fE4_E4;
    int pad_E8;
    int fEC_EC;
    int fF0_F0;
    char pad_F4[0x100 - 0xF4];
    unsigned short f100_100;
    unsigned short f102_102;
    int f104_104;
    int f108_108;
    char pad_10C[0x120 - 0x10C];
    EvEntEventfnc* ent_120;
} EvCtxEventfnc;

INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6D00);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B6DD4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B716C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B73C0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B76B8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B79E0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B7E40);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8028);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B80C8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8184);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8220);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B82C8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B83E4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B844C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8568);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B88A4);

void sub_800B8928()
{
    int i;
    for (i = 0x2a; i >= 0; i--)
    {
    }
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8940);

int sub_800B89A8(EvCtxEventfnc* c)
{
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B89C0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B89F4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8A34);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8BE8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8CB0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8D08);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8DDC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8E9C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8F14);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8F44);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8F88);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8FB8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9020);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9110);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B91CC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9218);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9260);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B93A8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B942C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B95BC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B962C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B96D8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9720);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9768);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B97B0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B97F8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9840);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B98C4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B990C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9954);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B99D8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9A20);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9A68);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9AB4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9B00);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9B4C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9B98);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9C5C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9CC0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9D08);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9D50);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9DE0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9E48);

int sub_800B9EB0(EvCtxEventfnc* c)
{
    c->ent_120->f7C_7C = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9EDC(EvCtxEventfnc* c)
{
    if (c->ent_120->f80_80 == c->pc_8->b_8)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9F0C);

int sub_800B9F5C(EvCtxEventfnc* c)
{
    c->f108_108 |= c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9F84(EvCtxEventfnc* c)
{
    c->f100_100 = c->pc_8->a_4;
    c->f102_102 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9FB4(EvCtxEventfnc* c)
{
    c->f104_104 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9FD8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA020);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA1DC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA238);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA28C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA2E8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA338);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA40C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA45C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA4F0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA554);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA5CC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA678);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA6D0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA714);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA7A4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA82C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA880);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA8AC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA930);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA9E4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAA6C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAAC0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAB14);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAB5C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BABB0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAC60);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BACE0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAD3C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAD88);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BADF8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAEBC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAF08);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAF68);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAFAC);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB180);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB214);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB27C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB45C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB4A4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB7D8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB840);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB990);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBAB0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBAE4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBB18);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBB5C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBBA0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBBD0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBC00);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBC80);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBDA0);

extern int dword_800AEBD4;
int sub_800BBDD8(int a)
{
    return (~dword_800AEBD4 & a) == 0;
}

int sub_800BBDF4(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f8C_8C;
    }
    return 0;
}

int sub_800BBE18(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f84_84;
    }
    return -1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBE3C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC2B4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC560);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC58C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC5C8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC6C4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC7A0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC7A8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC854);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC98C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCA18);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCA68);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCB00);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCB3C);

INCLUDE_OVERLAY_ASM(eventfnc, dword_800BCDBC);
