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
extern void sub_800BBB54();
extern void sub_800BF704();
extern int ret_800BF520();
extern int sub_8001AB94();
extern void sub_8001AAF4();
extern void sub_8001AB1C(int a);
extern void PlaySfx_80031494(int a);
extern void sub_800BF474();
extern void sub_800BF4B8();
extern int name_8008D670;
typedef struct ShopUnit3Shop
{
    short field_0;
    short field_2;
    short field_4;
    char pad_6[0x16];
    int field_1C;
    int field_20;
    int field_24;
    short field_28;
    short field_2A;
    short field_2C;
    short field_2E;
    short field_30;
    short field_32;
    char pad_34[8];
    short field_3C;
    short pad_3E;
    short field_40;
    short field_42;
    short field_44;
    short field_46;
    short field_48;
    short field_4A;
    void* field_4C;
    void* field_50;
    void* field_54;
    unsigned short field_58;
    unsigned short field_5A;
    unsigned short field_5C;
    short a5E[7];
    short field_6C;
    short field_6E;
    short pad_70;
    short a72[2];
    short field_76;
    short pad_78;
    short a7A[2];
    short field_7E;
    char pad_80[0x16];
    short field_96;
} ShopUnit3Shop;

typedef struct ShopTask3Shop
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
    char pad_C[8];
    ShopUnit3Shop* field_14;
} ShopTask3Shop;

typedef struct ShopSixShop
{
    int w0;
    int w1;
    int w2;
    int w3;
    int w4;
    int w5;
} ShopSixShop;

extern short name_800BFD1C[];
extern unsigned short name_800BFD3C[];
extern unsigned short name_800BFD5C[];
extern char name_800C08E8[];
extern ShopSixShop name_800B9608;
extern char name_800C07D4[];
extern void sub_800B9FC8(void* a, void* b, void* c, int d);
extern int sub_800AD288(int a, int b);
extern void sub_8002A5A4(void* p);
extern void sub_800BB148();
typedef struct ShopEntShop
{
    int w0;
    int w4;
} ShopEntShop;
extern int* name_800BFCF4[];
extern int* name_800BFD08[];
extern ShopEntShop name_800BF7C8[];
extern short name_800BF8B4[];
extern void sub_800A7B00(int a);
extern void sub_8002BF74();
extern int sub_800BD678();
extern void sub_800BD854();
extern void sub_800BD7A8();
extern int sub_800BF3B4();
extern void sub_800BAEDC();
extern int sub_800B9888(short i);
extern ShopItemShop* sub_800B9C5C(int i);
extern int sub_800B9C10(int i);
extern ShopItemShop name_8008EF18[];
extern void sub_8001AE00(unsigned int* b, int i);
extern int sub_8001AD30(int i);
extern int sub_8001AE54(unsigned int* b);
extern char name_800B6D04[];
extern char name_800B6D2C[];
extern unsigned short name_800BF888[];
extern unsigned short name_800BF7E8[][4];
extern int sub_800AD308(int a);
extern void sub_800BF750();
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

int sub_800B97B0()
{
    int r = 0;
    short i;
    short j;
    for (i = 3; i < name_800B6CE4; i++)
    {
        if (sub_800B9C10(i) == 4)
        {
            j = sub_800B9888(i);
            if (j <= 0)
            {
                break;
            }
            r = 1;
            sub_800BAEDC(&name_800B6CF0[i], &name_800B6CF0[j]);
        }
    }
    return r;
}

int sub_800B9888(short i)
{
    for (; i < name_800B6CE4; i++)
    {
        if (sub_800B9C10(i) == 2)
        {
            return i;
        }
    }
    return -1;
}

INCLUDE_OVERLAY_ASM(shop, sub_800B9920);

void sub_800B9B20(int i)
{
    name_800B6CF0[i].state_0 = 4;
}

void sub_800B9B44(short* p)
{
    *p = 4;
}

ShopItemShop* sub_800B9B50(int mode, int n)
{
    int cnt = 0;
    int i;
    for (i = 0; i < name_800B6CE4; i++)
    {
        if (mode == sub_800B9C10(i) || (mode == 0 && sub_800B9C10(i) != 4))
        {
            if (cnt == n)
            {
                return sub_800B9C5C(i);
            }
            cnt++;
        }
    }
    return 0;
}

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

#if 0 // near miss: i/p register swap
int sub_800B9DA8()
{
    int cnt = name_800B6CE4;
    ShopItemShop* items = name_800B6CF0;
    int n = 0;
    int i = 0;
    ShopItemShop* p;
    ShopItemShop* dst;
    for (; i < cnt; i++)
    {
        if (items[i].state_0 != 4)
        {
            n++;
        }
    }
    if (n < 16)
    {
        i = 0;
        if (i < cnt)
        {
            dst = name_8008EF18;
            p = items;
            do
            {
                if (p->state_0 != 4)
                {
                    sub_800403E8((unsigned int*)dst, (unsigned int*)p, 0xF8);
                    dst++;
                }
                i++;
                p++;
            } while (i < cnt);
        }
        free3_8003FC6C(items);
        return 1;
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800B9DA8);

#if 0 // near miss: lbu/addiu order in first loop
int sub_800B9E94(char* src, char* dst, short c)
{
    int i;
    int k;
    unsigned int j;
    unsigned int r;
    *(short*)dst = c;
    for (i = 0, k = 4; i < 6; k += 12)
    {
        sub_80019AF4((unsigned int*)(dst + k), (unsigned int*)(src + 0x10));
        (dst + i)[0x7C] = src[0x42];
        i++;
    }
    r = sub_80014358(*(short*)(src + 0x42));
    for (j = 0; j < 4; j++)
    {
        (dst + j)[0xC2] = 0;
    }
    if (r >= 4)
    {
        printf(name_800B6D04, name_800B6D2C, 0x1AB);
        exit(1);
    }
    (dst + r)[0xC2] = 0x20;
    for (i = 0; i < 0x30; i++)
    {
        (dst + i)[0x4C] = src[0x5C];
    }
    dst[2] = src[0x5C];
    dst[3] = src[0x5C];
    sub_800403E8((unsigned int*)(dst + 0x84), (unsigned int*)src, 0x48);
    sub_800403E8((unsigned int*)(dst + 0xDE), (unsigned int*)(src + 0x6C), 0x14);
    sub_800403E8((unsigned int*)(dst + 0xF4), (unsigned int*)(src + 0x80), 4);
    return 1;
}
#endif
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

void sub_800BA3C8(unsigned char* d, unsigned char* a, unsigned char* b)
{
    int i;
    for (i = 5; i >= 0; i--)
    {
    }
    for (i = 5; i >= 0; i--)
    {
    }
    for (i = 0; i < 6; i++)
    {
        (d + i)[6] = sub_800BA46C((a + i)[6], (b + i)[6]);
    }
    for (i = 5; i >= 0; i--)
    {
    }
}

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

#if 0 // near miss: pointer induction var
void sub_800BA650(unsigned char* d)
{
    int i;
    int v;
    unsigned char* p;
    for (i = 0, p = d; i < 6; i++, p = d + i)
    {
        v = p[0xB0] + (unsigned char)(p[0xB6] / 20);
        if (v < 0)
        {
            v = 0;
        }
        else if (v > 100)
        {
            v = 100;
        }
        p[0xB0] = v;
    }
    for (i = 5; i >= 0; i--)
    {
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BA650);

void sub_800BA6D0(ShopUnitShop* d, ShopUnitShop* s, ShopUnitShop* t)
{
    d->field_C8 = s->field_C8;
    d->field_88 = s->field_88;
    d->field_88 += sub_80012204(s->field_C8, s->field_88, t->field_C8, t->field_88);
}

INCLUDE_OVERLAY_ASM(shop, sub_800BA72C);

#if 0 // near miss: orig keeps (1 << x) & mask as sllv/and, we get sra/andi
void sub_800BAA0C(char* a, char* b)
{
    unsigned int old = *(unsigned int*)(a + 0xF4);
    unsigned int* p = (unsigned int*)(a + 0xF4);
    int i;
    int mask;
    if (sub_800BAB30(b))
    {
        old |= *(unsigned int*)(b + 0xF4);
    }
    mask = *(short*)(a + 0xC6);
    *(unsigned int*)(a + 0xF4) = old;
    for (i = 0; i < 30; i++)
    {
        if (sub_8001AE2C(p, i) && !((1 << sub_8001AD30(i)) & mask))
        {
            sub_8001AE00(p, i);
        }
    }
    if (a[0xC2] != 0x20)
    {
        sub_8001AE00(p, 0x15);
    }
    if (a[0xC4] != 0x20)
    {
        sub_8001AE00(p, 0x17);
    }
    if (a[0xC3] != 0x20)
    {
        sub_8001AE00(p, 0x18);
    }
    if (a[0xC5] != 0x20)
    {
        sub_8001AE00(p, 0x16);
    }
}
#endif
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

void sub_800BAEDC(unsigned int* a, unsigned int* b)
{
    unsigned int t1[0x3E];
    unsigned int t2[0x3E];
    sub_800403E8(t1, a, 0xF8);
    sub_800403E8(t2, b, 0xF8);
    sub_800403E8(a, t2, 0xF8);
    sub_800403E8(b, t1, 0xF8);
}

#if 0 // near miss: orig jumps from the b==3 case into the b==4 copy of the *a = 3 store (cross-jump)
int sub_800BAF54(short* a, short* b, short c, short d)
{
    if (*a == 3)
    {
        if (*b == 2)
        {
            *a = 2;
            *b = 3;
        }
        else if (*b == 4 && d == 2)
        {
            *a = 2;
        }
    }
    else if (*a == 2)
    {
        if (*b == 3)
        {
            *b = 2;
            *a = 3;
        }
        else if (*b == 4 && d == 3)
        {
            *a = 3;
        }
    }
    else if (*a == 4)
    {
        if (c == 3)
        {
            if (*b == 2 && d == 2)
            {
                *b = 3;
            }
        }
        else if (c == 2)
        {
            if (*b == 3 && d == 3)
            {
                *b = 2;
            }
        }
    }
    else
    {
        goto end;
    }
    sub_800BAEDC(a, b);
end:
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BAF54);

extern void sub_800BB0F8();
void sub_800BB058(int a)
{
    EventEntry* t = sub_80043AF8((EventNode*)name_8008D670);
    ShopUnit3Shop* u;
    if (t)
    {
        u = t->buffer;
        t->flags = (t->flags | 1) & ~0x8000;
        sub_8003F900(2, 0);
        sub_8003F900(1, 0);
        sub_8002BE10();
        u->field_96 = a;
        sub_800BB148(u);
        sub_800BC380(u);
        t->cb_8 = sub_800BB0F8;
    }
}

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

#if 0 // near miss: load order of table entries
void sub_800BB798(ShopUnit3Shop* u)
{
    unsigned short b;
    int a;
    unsigned short c;
    a = name_800BFD1C[u->field_0];
    b = name_800BFD3C[u->field_0];
    c = name_800BFD5C[u->field_0];
    if (a >= 0)
    {
        u->a5E[a] = u->field_30;
    }
    if ((short)b >= 0)
    {
        u->a72[(short)b] = u->field_32;
    }
    if ((short)c >= 0)
    {
        u->a7A[(short)c] = u->field_7E;
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BB798);

#if 0 // near miss: load order of table entries
void sub_800BB828(ShopUnit3Shop* u)
{
    unsigned short b;
    int a;
    unsigned short c;
    a = name_800BFD1C[u->field_0];
    b = name_800BFD3C[u->field_0];
    c = name_800BFD5C[u->field_0];
    if (a >= 0)
    {
        u->field_30 = u->a5E[a];
    }
    if ((short)b >= 0)
    {
        u->field_32 = u->a72[(short)b];
    }
    if ((short)c >= 0)
    {
        u->field_7E = u->a7A[(short)c];
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BB828);

void sub_800BB8C4(ShopUnit3Shop* u)
{
    short s = u->field_0;
    short t;
    if (s == 0)
    {
        if (u->field_30 != 4)
        {
            u->field_30 = 4;
        }
        else
        {
            if (u->field_4 >= 13)
            {
                u->field_0 = 12;
            }
            else
            {
                u->field_0 = 11;
            }
        }
    }
    else if (s == 3)
    {
        u->field_0 = 2;
        u->field_2 = 1;
        u->field_24 &= ~0x200;
        u->field_30 = u->a5E[2];
        u->field_32 = u->a72[1];
    }
    else if (s == 4)
    {
        u->field_0 = 0;
        u->field_32 = 0;
        u->field_30 = 0;
    }
    else if (s == 12)
    {
        u->field_0 = 0;
    }
    else if (s == 11)
    {
        u->field_24 |= 4;
    }
    else if (s == 13)
    {
        sub_800BD720(u);
        u->field_0 = 3;
        u->field_2 = 2;
    }
    else if (s == 14)
    {
        u->field_0 = 13;
        u->field_2 = 2;
    }
    else
    {
        if (s == 2 || s == 10)
        {
            u->field_7E = u->a7A[0];
        }
        t = u->field_2;
        u->field_0 = t;
        u->field_2 = name_800BF888[t];
        sub_800BB828(u);
    }
}

extern unsigned short word_8009194C;
void sub_800BBA3C(char* u)
{
    if (*(short*)(u + 0x98) < 0x96)
    {
        *(short*)(u + 0x98) += 1;
    }
    if (word_8009194C != 0 || *(short*)(u + 0x98) >= 0x96)
    {
        sub_800BBB54(u, 0);
        *(int*)(u + 0x18) = 0;
        *(short*)(u + 0x98) = 0;
    }
}

void sub_800BBAAC(ShopUnit3Shop* u)
{
    short i;
    if (u->field_0 == 0)
    {
        for (i = 0; i < 3; i++)
        {
            if (u->field_96 == 4)
            {
                name_800BF7C8[i].w4 = name_800BFCF4[u->field_30][i];
            }
            else
            {
                name_800BF7C8[i].w4 = name_800BFD08[u->field_30][i];
            }
        }
    }
}

INCLUDE_OVERLAY_ASM(shop, sub_800BBB54);

INCLUDE_OVERLAY_ASM(shop, sub_800BBE24);

#if 0 // near miss: orig does not fold the two flag masks (and/and with separate constants)
void sub_800BC1A8(ShopUnit3Shop* u)
{
    int fl;
    int r;
    if (*(short*)u->field_54 != 4)
    {
        fl = u->field_24;
        u->field_40 = 1;
        u->field_42 = 1;
        u->field_44 = 1;
        u->field_46 = 0;
        u->field_4A = 0;
        u->field_48 = 0;
        if ((fl & 0x1C0) == 0)
        {
            u->field_24 = fl | 0x40;
            u->field_44 = 5;
            u->field_42 = 5;
        }
        else if (fl & 0x40)
        {
            fl &= ~0x40;
            fl &= ~0x100;
            u->field_24 = fl | 0x80;
            r = sub_8001AE54((unsigned int*)((char*)u->field_54 + 0xF4));
            if (r < 4)
            {
                r = 4;
            }
            u->field_40 = 1;
            u->field_42 = 4;
            u->field_44 = r;
            u->field_46 = 0x40;
        }
        else if (fl & 0x80)
        {
            fl &= ~0x40;
            fl &= ~0x80;
            u->field_24 = fl | 0x100;
        }
        else if (fl & 0x100)
        {
            int fl2 = fl & ~0x100;
            u->field_24 = fl2;
            if (u->field_0 == 3 && (fl & 2))
            {
                u->field_24 = fl2 & ~0x401;
            }
        }
        PlaySfx_80031494(0x7F);
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BC1A8);

void sub_800BC2DC(ShopUnit3Shop* u)
{
    if (sub_8003D380(0) || sub_8003D41C(0))
    {
        int fl = u->field_24;
        if ((fl & 0x400) && u->field_0 == 3 && (fl & 2))
        {
            PlaySfx_80031494(0x7D);
            u->field_24 &= ~0x400;
        }
        else
        {
            PlaySfx_80031494(0x7E);
            sub_800BBB54(u, 0);
            u->field_24 &= ~2;
        }
    }
}

INCLUDE_OVERLAY_ASM(shop, sub_800BC380);

INCLUDE_OVERLAY_ASM(shop, sub_800BCCD8);

void sub_800BCEDC(ShopUnit3Shop* u)
{
    ShopSixShop q = name_800B9608;
    q.w1 = sub_8002C64C();
    q.w4 = (int)name_800C07D4;
    q.w0 = (q.w0 & ~7) | 2;
    q.w3 = u->field_30;
    q.w2 = 8;
    sub_8002A5A4(&q);
}

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

void sub_800BD720(ShopUnit3Shop* u)
{
    int d;
    if (u->field_4C && u->field_50)
    {
        if (u->field_24 & 0x200)
        {
            d = sub_800AD288(u->field_6E + u->field_76, 4);
        }
        else
        {
            d = 10;
        }
        sub_800B9FC8(u->field_4C, u->field_50, name_800C08E8, d);
    }
}

#if 0 // near miss: tab/v register swap
void sub_800BD7A8(ShopUnit3Shop* u)
{
    short i;
    unsigned short v = u->field_20;
    u->field_1C = 0;
    u->field_20 = 0;
    u->field_1C = name_800BF8B4[u->field_0];
    for (i = 0; i < 7; i++)
    {
        if ((v >> i) & 1)
        {
            if ((name_800BF8B4[u->field_0] >> i) & 1)
            {
                u->field_20 |= 1 << i;
            }
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BD7A8);

void sub_800BD854(ShopUnit3Shop* u)
{
    unsigned short* e = name_800BF7E8[u->field_0];
    int r;
    u->field_28 = e[0];
    u->field_2A = e[1];
    u->field_2C = e[2];
    u->field_2E = e[3];
    if (u->field_1C & 8)
    {
        if (u->field_0 == 4)
        {
            u->field_30 = 0;
        }
        else
        {
            u->field_30 = 1;
        }
    }
    if (u->field_0 == 3)
    {
        u->field_3C = 2;
    }
    if (u->field_24 & 8)
    {
        if (u->field_7E == 0)
        {
            u->field_24 |= 0x10;
            u->field_28 = 1;
            u->field_2E = 0x20;
            u->field_2A = 3;
            u->field_2C = 3;
            if (u->field_0 == 2 || u->field_0 == 10)
            {
                u->field_30 = u->field_58;
            }
        }
        else
        {
            u->field_24 &= ~0x10;
            u->field_28 = 1;
            u->field_2A = 4;
            u->field_2C = 0x18;
            u->field_2E = 0x50;
            if (u->field_0 == 2 || u->field_0 == 10)
            {
                u->field_30 = u->field_5A;
                u->field_32 = u->field_5C;
            }
        }
    }
    if (u->field_0 == 14)
    {
        r = sub_800AD308(4);
        if (r < 3)
        {
            r = 3;
        }
        u->field_2C = r + 1;
    }
}

INCLUDE_OVERLAY_ASM(shop, sub_800BD9DC);

INCLUDE_OVERLAY_ASM(shop, sub_800BDD74);

extern void sub_800BDEA8();
void sub_800BDE44(ShopTaskShop* t, int a)
{
    sub_8002BE10();
    sub_800BC380(a);
    if (sub_8001AB94())
    {
        sub_8001AAF4();
        sub_8001AB1C(0x20);
        t->next_8 = sub_800BDEA8;
    }
}

INCLUDE_OVERLAY_ASM(shop, sub_800BDEA8);

extern void sub_800BE210();
void sub_800BE07C(ShopTaskShop* t, ShopUnit3Shop* u)
{
    u->field_0 = 5;
    u->field_2 = 0;
    sub_800BD7A8(u);
    sub_800BBB54(u, 0);
    if (sub_800BD678(u))
    {
        u->field_24 |= 8;
    }
    else
    {
        u->field_24 &= ~8;
    }
    sub_800BD854(u);
    u->field_30 = u->a5E[1];
    u->field_32 = u->a72[0];
    sub_800A7B00(-1);
    sub_8002BF74();
    t->next_8 = sub_800BE210;
}

void sub_800BE128(ShopTaskShop* t, ShopUnit3Shop* u)
{
    if (u->field_0 == 9)
    {
        u->field_0 = 8;
    }
    else
    {
        u->field_0 = 4;
    }
    u->field_2 = 0;
    sub_800BD7A8(u);
    sub_800BBB54(u, 0);
    if (sub_800BD678(u))
    {
        u->field_24 |= 8;
    }
    else
    {
        u->field_24 &= ~8;
    }
    sub_800BD854(u);
    u->field_30 = u->a5E[1];
    u->field_32 = u->a72[0];
    if (u->field_0 == 4)
    {
        u->field_30 = 0;
    }
    sub_8002BE10();
    sub_800BC380(u);
    sub_8001C19C(3, 0x20);
    sub_800A7B00(-1);
    t->next_8 = sub_800BB444;
}

extern void sub_800BE264();
void sub_800BE210(ShopTaskShop* t, int a)
{
    if (dword_8008B4E8)
    {
        sub_8002BE10();
        sub_800BC380(a);
        t->next_8 = sub_800BE264;
    }
}

extern void sub_800BB444();
void sub_800BE264(ShopTaskShop* t, int a)
{
    sub_8002BE10();
    sub_800BC380(a);
    sub_8001C19C(3, 0x20);
    t->next_8 = sub_800BB444;
}

extern void sub_800BE4D0();
void sub_800BE2B4(int a)
{
    char* g = (char*)name_8008D670 + 0x10;
    PlaySfx_80031494(0x7E);
    sub_800BF474();
    unknownFlags_8008D678 |= 0x10000;
    unknownFlags_8008D678 |= 0x4000000;
    sub_800BF4B8(a);
    *(void (**)())(g + 8) = sub_800BE4D0;
}

extern void sub_800BB444();
void sub_800BE334(ShopTaskShop* t, ShopUnit3Shop* u)
{
    char* c;
    int v;
    sub_8002BE10();
    sub_800BC380(u);
    c = (char*)sub_800BF780();
    if (word_800918D0[0] & 0x8000)
    {
        *(unsigned short*)(c + 0x5E) += 0x88;
    }
    else if (word_800918D0[0] & 0x2000)
    {
        *(unsigned short*)(c + 0x5E) -= 0x88;
    }
    if (word_800918D0[0] & 8)
    {
        v = *(int*)(c + 0x138) + 0x40;
        if (v < 0x1000)
        {
            *(int*)(c + 0x138) = v;
            *(int*)(c + 0x13C) += 0x40;
            *(int*)(c + 0x140) += 0x40;
        }
    }
    else if (word_800918D0[0] & 2)
    {
        v = *(int*)(c + 0x138) - 0x40;
        if (v > 0x400)
        {
            *(int*)(c + 0x138) = v;
            *(int*)(c + 0x13C) -= 0x40;
            *(int*)(c + 0x140) -= 0x40;
        }
    }
    if (sub_8003D41C(1))
    {
        sub_800BF750();
        unknownFlags_8008D678 &= ~0x10000;
        unknownFlags_8008D678 &= ~0x4000000;
        if (u->field_0 == 3)
        {
            sub_800BBB54(u, 3);
        }
        else
        {
            sub_800BBB54(u, 0);
        }
        if (u->field_0 == 5)
        {
            *(int*)((char*)u + 0x10) = 0;
        }
        u->field_24 &= ~0x20;
        t->next_8 = sub_800BB444;
    }
}

extern void sub_800BE334();
void sub_800BE4D0(ShopTaskShop* t, ShopUnitShop* a)
{
    sub_8002BE10();
    sub_800BC380(a);
    if (ret_800BF520() == 1)
    {
        sub_800BBB54(a, 2);
        sub_800BF704(*(short*)((char*)a + 0x96));
        t->next_8 = sub_800BE334;
    }
}

INCLUDE_OVERLAY_ASM(shop, sub_800BE53C);

INCLUDE_OVERLAY_ASM(shop, sub_800BE7F0);

INCLUDE_OVERLAY_ASM(shop, sub_800BEB60);

INCLUDE_OVERLAY_ASM(shop, sub_800BEBC8);

void sub_800BECC8(ShopUnit3Shop* u)
{
    if (u->field_0 == 3)
    {
        switch (u->field_3C)
        {
        case 1:
            u->field_54 = u->field_50;
            return;
        case 0:
            goto def;
        case 2:
            u->field_54 = name_800C08E8;
            return;
        }
        return;
    }
    if (u->field_0 == 2 || u->field_0 == 10)
    {
        u->field_54 = u->field_50;
        return;
    }
def:
    u->field_54 = u->field_4C;
}

INCLUDE_OVERLAY_ASM(shop, sub_800BED48);

INCLUDE_OVERLAY_ASM(shop, sub_800BF02C);

int sub_800BF2E4(unsigned char* p)
{
    int n = 0;
    int i;
    int r;
    for (i = 0; i < 4; i++)
    {
        if (p[i])
        {
            n++;
        }
    }
    if (n == 1)
    {
        r = -1000;
        goto done;
    }
    if (n == 2)
    {
        if (p[3] && p[1])
        {
            if (p[1] < p[3])
            {
                r = 0xF5;
            }
            else
            {
                r = 0x41;
            }
            goto done;
        }
        if (p[0] && p[2])
        {
            if (p[2] < p[0])
            {
                r = 0x14F;
            }
            else
            {
                r = 0x9B;
            }
            goto done;
        }
    }
    r = sub_800BF3B4(p);
done:
    return r;
}

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
