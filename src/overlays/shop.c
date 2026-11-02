// SHOP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct ShopItemShop
{
    short state_0;
    char pad_2[0xF6];
} ShopItemShop;

typedef struct ShopCtxShop
{
    int field_0;
    char pad_4[0x38];
    void* field_3C;
} ShopCtxShop;

typedef struct ShopTaskShop
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} ShopTaskShop;

typedef struct ShopUnitShop
{
    char pad_0[0x84];
    int field_84;
    int field_88;
    char pad_8C[0x3C];
    unsigned char field_C8;
} ShopUnitShop;

extern int name_8007DC74;
extern int sub_80010850(void* p);
extern int sub_80012204(int a, int b, int c, int d);
extern void sub_800BF02C();
extern int name_800B6CE4;
extern unsigned int name_800C07F0[];
extern ShopItemShop* name_800B6CF0;
extern ShopCtxShop name_800C09E0;
extern int name_800C0A1C;
extern void sub_8001C19C(int a, int b);
extern void sub_8001D600(void* p);
extern void sub_8002BE10();
extern void* memset(void* p, int c, unsigned int n);
extern void sub_800BC380();
extern void sub_800BF574();

INCLUDE_OVERLAY_ASM(shop, dword_800B6D00);

INCLUDE_OVERLAY_ASM(shop, sub_800B97B0);

INCLUDE_OVERLAY_ASM(shop, sub_800B9888);

INCLUDE_OVERLAY_ASM(shop, sub_800B9920);

void sub_800B9B20(int i)
{
    name_800B6CF0[i].state_0 = 4;
}

void sub_800B9B44(short* p)
{
    *p = 4;
}

INCLUDE_OVERLAY_ASM(shop, sub_800B9B50);

int sub_800B9C10(int i)
{
    return name_800B6CF0[i].state_0;
}

short* sub_800B9C34(int i)
{
    return &name_800B6CF0[i].state_0 + 2;
}

char* sub_800B9C54(char* p)
{
    return p + 4;
}

ShopItemShop* sub_800B9C5C(int i)
{
    return &name_800B6CF0[i];
}

#if 0 // near miss: i/n register swap
int sub_800B9C78(int v)
{
    int n;
    int i;
    int cnt;
    ShopItemShop* p;
    n = 0;
    i = n;
    if (name_800B6CE4 > 0)
    {
        cnt = name_800B6CE4;
        p = name_800B6CF0;
        do
        {
            if (v == p->state_0)
            {
                n++;
            }
            i++;
            p++;
        } while (i < cnt);
    }
    return n;
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800B9C78);

int sub_800B9CCC(short* p)
{
    *p = 3;
    return 1;
}

int sub_800B9CDC(int i)
{
    if (sub_800B9C78(3) < 3)
    {
        if (sub_800B9C10(i) == 2)
        {
            name_800B6CF0[i].state_0 = 3;
            return 1;
        }
    }
    return 0;
}

int sub_800B9D48(short* p)
{
    if (*p == 3)
    {
        *p = 2;
        return 1;
    }
    return 0;
}

int sub_800B9D6C(int i)
{
    if (name_800B6CF0[i].state_0 == 3)
    {
        name_800B6CF0[i].state_0 = 2;
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(shop, sub_800B9DA8);

INCLUDE_OVERLAY_ASM(shop, sub_800B9E94);

INCLUDE_OVERLAY_ASM(shop, sub_800B9FC8);

void sub_800BA340(unsigned int* a)
{
    sub_800403E8(a, name_800C07F0, 0xF8);
}

void sub_800BA368(unsigned char* d, unsigned char* s)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        (d + i)[0xB0] = (s + i)[0xB0] - (s + i)[0xB6] / 20;
    }
    *(unsigned short*)(d + 0x8E) = *(unsigned short*)(s + 0x8E);
    *(unsigned short*)(d + 0x92) = *(unsigned short*)(s + 0x92);
}

INCLUDE_OVERLAY_ASM(shop, sub_800BA3C8);

unsigned char sub_800BA46C(unsigned char a, unsigned char b)
{
    int s = (a + b) >> 1;
    int c = b - 200;
    int r = s + (a + c) / 7;
    int out = 0;
    if (r >= 0)
    {
        out = r;
        if (out > 200)
        {
            out = 200;
        }
    }
    return out;
}

INCLUDE_OVERLAY_ASM(shop, sub_800BA4CC);

INCLUDE_OVERLAY_ASM(shop, sub_800BA650);

void sub_800BA6D0(ShopUnitShop* d, ShopUnitShop* s, ShopUnitShop* t)
{
    d->field_C8 = s->field_C8;
    d->field_88 = s->field_88;
    d->field_88 += sub_80012204(s->field_C8, s->field_88, t->field_C8, t->field_88);
}

INCLUDE_OVERLAY_ASM(shop, sub_800BA72C);

INCLUDE_OVERLAY_ASM(shop, sub_800BAA0C);

int sub_800BAB30()
{
    return 1;
}

INCLUDE_OVERLAY_ASM(shop, sub_800BAB38);

INCLUDE_OVERLAY_ASM(shop, sub_800BACD0);

int sub_800BAE80(ShopUnitShop* p)
{
    unsigned int v = p->field_C8;
    int r;
    if (v < 4)
    {
        r = 0x21;
    }
    else if (v < 7)
    {
        r = 0x22;
    }
    else if (v < 12)
    {
        r = 0x23;
    }
    else if (v < 18)
    {
        r = 0x24;
    }
    else if (v < 25)
    {
        r = 0x25;
    }
    else if (v < 31)
    {
        r = 0x26;
    }
    else
    {
        r = 0x27;
    }
    return r;
}

INCLUDE_OVERLAY_ASM(shop, sub_800BAEDC);

INCLUDE_OVERLAY_ASM(shop, sub_800BAF54);

INCLUDE_OVERLAY_ASM(shop, sub_800BB058);

extern void sub_800BB444();
void sub_800BB0F8(ShopTaskShop* t, int a)
{
    sub_8002BE10();
    sub_800BC380(a);
    sub_8001C19C(3, 0x20);
    t->next_8 = sub_800BB444;
}

INCLUDE_OVERLAY_ASM(shop, sub_800BB148);

INCLUDE_OVERLAY_ASM(shop, sub_800BB38C);

#if 0 // near miss: reg alloc of field_84 load
int sub_800BB3E8(ShopUnitShop* p)
{
    switch (*(short*)p)
    {
    case 5:
        if (p->field_84)
        {
            return 0;
        }
    case 1:
    case 7:
        return 1;
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BB3E8);

INCLUDE_OVERLAY_ASM(shop, sub_800BB444);

INCLUDE_OVERLAY_ASM(shop, sub_800BB798);

INCLUDE_OVERLAY_ASM(shop, sub_800BB828);

INCLUDE_OVERLAY_ASM(shop, sub_800BB8C4);

INCLUDE_OVERLAY_ASM(shop, sub_800BBA3C);

INCLUDE_OVERLAY_ASM(shop, sub_800BBAAC);

INCLUDE_OVERLAY_ASM(shop, sub_800BBB54);

INCLUDE_OVERLAY_ASM(shop, sub_800BBE24);

INCLUDE_OVERLAY_ASM(shop, sub_800BC1A8);

INCLUDE_OVERLAY_ASM(shop, sub_800BC2DC);

INCLUDE_OVERLAY_ASM(shop, sub_800BC380);

INCLUDE_OVERLAY_ASM(shop, sub_800BCCD8);

INCLUDE_OVERLAY_ASM(shop, sub_800BCEDC);

INCLUDE_OVERLAY_ASM(shop, sub_800BCF74);

INCLUDE_OVERLAY_ASM(shop, sub_800BD0D4);

int sub_800BD650(short* p)
{
    if (*p == 3 || *p == 13)
    {
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(shop, sub_800BD678);

INCLUDE_OVERLAY_ASM(shop, sub_800BD6C4);

INCLUDE_OVERLAY_ASM(shop, sub_800BD720);

INCLUDE_OVERLAY_ASM(shop, sub_800BD7A8);

INCLUDE_OVERLAY_ASM(shop, sub_800BD854);

INCLUDE_OVERLAY_ASM(shop, sub_800BD9DC);

INCLUDE_OVERLAY_ASM(shop, sub_800BDD74);

INCLUDE_OVERLAY_ASM(shop, sub_800BDE44);

INCLUDE_OVERLAY_ASM(shop, sub_800BDEA8);

INCLUDE_OVERLAY_ASM(shop, sub_800BE07C);

INCLUDE_OVERLAY_ASM(shop, sub_800BE128);

INCLUDE_OVERLAY_ASM(shop, sub_800BE210);

INCLUDE_OVERLAY_ASM(shop, sub_800BE264);

INCLUDE_OVERLAY_ASM(shop, sub_800BE2B4);

INCLUDE_OVERLAY_ASM(shop, sub_800BE334);

INCLUDE_OVERLAY_ASM(shop, sub_800BE4D0);

INCLUDE_OVERLAY_ASM(shop, sub_800BE53C);

INCLUDE_OVERLAY_ASM(shop, sub_800BE7F0);

INCLUDE_OVERLAY_ASM(shop, sub_800BEB60);

INCLUDE_OVERLAY_ASM(shop, sub_800BEBC8);

INCLUDE_OVERLAY_ASM(shop, sub_800BECC8);

INCLUDE_OVERLAY_ASM(shop, sub_800BED48);

INCLUDE_OVERLAY_ASM(shop, sub_800BF02C);

INCLUDE_OVERLAY_ASM(shop, sub_800BF2E4);

INCLUDE_OVERLAY_ASM(shop, sub_800BF3B4);

void sub_800BF474()
{
    name_800C09E0.field_0 = -1;
}

void sub_800BF484()
{
    if (name_800C09E0.field_0 >= 0)
    {
        sub_800BF6C4();
        sub_800BF548();
    }
}

void sub_800BF4B8(int a)
{
    ShopCtxShop* c = &name_800C09E0;
    sub_800BF02C(a, c->pad_4 + 4, name_8007DC74);
    *(int*)c->pad_4 = a;
    c->field_0 = sub_80010850(c->pad_4 + 4);
    c->field_3C = 0;
}

void sub_800BF520()
{
    sub_80010A10(name_800C09E0.field_0);
}

void sub_800BF548()
{
    int v = name_800C09E0.field_0;
    name_800C09E0.field_0 = -1;
    sub_8001098C(v);
}

INCLUDE_OVERLAY_ASM(shop, sub_800BF574);

void sub_800BF6C4()
{
    ShopCtxShop* c = &name_800C09E0;
    if (c->field_3C)
    {
        sub_8001D600(c->field_3C);
        c->field_3C = 0;
    }
}

void sub_800BF704()
{
    char a[12];
    char b[8];
    memset(a, 0, 12);
    memset(b, 0, 8);
    sub_800BF574(a, b);
}

void sub_800BF750()
{
    sub_800BF6C4();
    sub_800BF548();
    sub_800BF484();
}

int sub_800BF780()
{
    return name_800C0A1C;
}

INCLUDE_OVERLAY_ASM(shop, dword_800BF790);
