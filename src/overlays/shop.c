// SHOP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "actor.h"
#include "tu_80019BF0.h"
#include "minion_menu.h"

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


extern int name_8007DC74;
extern int StartModelTask_80010850(void* p);
extern int sub_80012204(int a, int b, int c, int d);
extern void sub_800BF02C();
extern void SetShopHelpText_800BBB54();
extern void sub_800BF704();
extern int ret_800BF520();
extern int sub_8001AB94();
extern void sub_8001AAF4();
extern void sub_8001AB1C(int a);
extern void PlaySfx_80031494(int a);
extern void sub_800BF474();
extern void sub_800BF4B8();
extern EventNode* name_8008D670; // the shop menu task list
// work area of the shop menu task
typedef struct ShopUnit3Shop
{
    short field_0; // state
    short field_2;
    short field_4;
    short field_6;
    short field_8;
    short pad_A;
    short field_C;
    short pad_E;
    int field_10;
    int field_14;
    int field_18;
    unsigned int field_1C;
    unsigned int field_20;
    int field_24;
    short field_28;
    short field_2A;
    short field_2C;
    short field_2E;
    short field_30;
    short field_32;
    short field_34;
    short field_36;
    short field_38;
    short field_3A;
    short field_3C;
    short field_3E;
    short field_40;
    short field_42;
    short field_44;
    short field_46;
    short field_48;
    short field_4A;
    Minion* field_4C;
    Minion* field_50;
    Minion* field_54;
    unsigned short field_58;
    unsigned short field_5A;
    unsigned short field_5C;
    short a5E[10];
    short a72[4];
    short a7A[2];
    short field_7E;
    short field_80;
    short pad_82;
    int field_84;
    int field_88;
    int field_8C;
    int field_90;
    short field_94;
    short field_96;
    short field_98;
} ShopUnit3Shop;

typedef struct ShopTask3Shop
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
    char pad_C[8];
    ShopUnit3Shop* field_14;
} ShopTask3Shop;

extern char name_80082680[];
extern void DrawButtonHelpBar_8002B004(void* p, int a, int b);
extern char name_800BFFE0[];
extern char name_800C0048[];
extern char name_800BFF70[];
extern char name_800BFFB8[];
extern char name_800BFF28[];
extern char name_800BFF48[];
extern char name_800BFF90[];
extern char name_800C0018[];
extern char name_800C0000[];
extern char name_800C0070[];
extern char name_800C0038[];
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
extern Minion name_800C08E8; // the merge result
extern ShopSixShop name_800B9608;
extern char name_800C07D4[];
extern int MergeMinions_800B9FC8(Minion* a, Minion* b, Minion* c, int d);
extern int sub_800AD288(int a, int b);
extern void DrawMenuWindows_8002A5A4(void* p);
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
extern void LoadUiTiy_8002BF74();
extern int sub_800BD678();
extern void sub_800BD854();
extern void sub_800BD7A8();
extern int sub_800BF3B4();
extern void sub_800BAEDC();
extern int sub_800B9888(short i);
extern Minion* sub_800B9C5C(int i);
extern int sub_800B9C10(int i);
extern Minion name_8008EF18[];
extern void ClearMagicBit_8001AE00(unsigned int* b, int i);
extern int GetMagicElement_8001AD30(int i);
extern int CountMagicBits_8001AE54(unsigned int* b);
extern char name_800B6D04[];
extern char name_800B6D2C[];
extern unsigned short name_800BF888[];
extern unsigned short name_800BF7E8[][4];
extern int sub_800AD308(int a);
extern void sub_800BF750();
typedef struct ShopBigShop
{
    char pad_0[0x5C6];
    short field_5C6;
    char pad_5C8[0x800 - 0x5C8];
} ShopBigShop;
extern ShopBigShop name_80084540[];
typedef struct ShopSetupShop
{
    int w0;
    int w4;
    int w8;
    int wC;
    int w10;
    short s14;
    short s16;
    short s18;
    short pad_1A;
    int w1C;
    int w20;
    int w24;
    int w28;
    int w2C;
    int w30;
    int w34;
    int w38;
    int w3C;
    int w40;
    int w44;
    int w48;
} ShopSetupShop;
extern int fn_80010A44(int a);
extern int fn_80024E90(int a, int b);
extern int fn_80024EC8(int a, int b);
extern int fn_80024E38(int a);
extern int fn_80024E64(int a);
extern void* fn_8001D45C(void* p);
extern int fn_80024F00(int a, int b);
extern int fn_80024F38(int a, int b);
extern void fn_80019B14(int a, int b, int c);
extern void fn_8001D68C(void* p, int on);
extern char name_80079140[];
extern signed char name_8007BA74[];
extern int sub_800B9E94(UnitStats* src, Minion* dst, short c);

extern int fn_800272D0();
extern void fn_800A7BF0(int a);
extern void fn_800A5F9C(int a);
extern void fn_800B6C6C(void* p, int a);
extern void fn_800B6CC8();
extern void fn_80027478(int a, int b);
extern void fn_800A6D30(int a);
extern int eventDispatchHalt_8008B540;
extern void fn_8002C014();
extern void fn_8001ABEC(int a);
extern int fn_800AD288(int a, int b);
extern void fn_800AD1E0(int a, int b, int c);
extern void fn_800AD3F0(int a);
extern void sub_800B9B44(short* p);
extern void sub_800BE128();
extern void sub_800BE07C();
extern void fn_80011CD0(UnitStatus* p);
extern int fn_800AD888();
extern void fn_800AD8F4(int a);

extern int name_800B6CE4;
extern unsigned int name_800C07F0[];
extern Minion* name_800B6CF0;
extern ShopCtxShop name_800C09E0;
extern Actor* name_800C0A1C; // the minion shown in the shop
Actor* sub_800BF780();
extern void SetFadeMode_8001C19C(int a, int b);
extern void DestroyActor_8001D600(void* p);
extern void DrawMenuBackground_8002BE10();
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

int sub_800B9920()
{
    int total = 27;
    Minion* items = malloc3_8003FC4C(0x1A28);
    short n = 0;
    int k;
    for (k = 0; k < 15; k++)
    {
        if (saveData_8008B570.minions[k].id == 3)
        {
            MemCopy_800403E8(&items[n], &saveData_8008B570.minions[k], 0xF8);
            n++;
        }
    }
    if (n < 3)
    {
        for (k = n; k < 3; k++)
        {
            items[k].id = 4;
        }
    }
    n = 3;
    for (k = 0; k < 15; k++)
    {
        if (saveData_8008B570.minions[k].id == 2)
        {
            MemCopy_800403E8(&items[n], &saveData_8008B570.minions[k], 0xF8);
            n++;
        }
    }
    for (k = 0; k < 12; k++)
    {
        if (saveData_8008B570.items[k].species_5C != 0xD3)
        {
            sub_800B9E94(&saveData_8008B570.items[k], &items[n], 2);
            n++;
        }
    }
    for (k = n; k < total; k++)
    {
        items[k].id = 4;
    }
    ClearMinionsAndItems_80010600();
    name_800B6CF0 = items;
    name_800B6CE4 = total;
    return total;
}

void sub_800B9B20(int i)
{
    name_800B6CF0[i].id = 4;
}

void sub_800B9B44(short* p)
{
    *p = 4;
}

Minion* sub_800B9B50(int mode, int n)
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
    return name_800B6CF0[i].id;
}

short* sub_800B9C34(int i)
{
    return &name_800B6CF0[i].id + 2;
}

char* sub_800B9C54(char* p)
{
    return p + 4;
}

Minion* sub_800B9C5C(int i)
{
    return &name_800B6CF0[i];
}

int CountItemsInState_800B9C78(int v)
{
    int i;
    int n;
    n = 0;
    for (i = 0; i < name_800B6CE4; i++)
    {
        if (v == name_800B6CF0[i].id)
        {
            n++;
        }
    }
    return n;
}

int sub_800B9CCC(short* p)
{
    *p = 3;
    return 1;
}

int sub_800B9CDC(int i)
{
    if (CountItemsInState_800B9C78(3) < 3)
    {
        if (sub_800B9C10(i) == 2)
        {
            name_800B6CF0[i].id = 3;
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
    if (name_800B6CF0[i].id == 3)
    {
        name_800B6CF0[i].id = 2;
        return 1;
    }
    return 0;
}

int sub_800B9DA8()
{
    int cnt = name_800B6CE4;
    Minion* items = name_800B6CF0;
    int n = 0;
    int i;
    for (i = 0; i < cnt; i++)
    {
        if (items[i].id != 4)
        {
            n++;
        }
    }
    if (n < 16)
    {
        n = 0;
        for (i = 0; i < cnt; i++)
        {
            if (items[i].id != 4)
            {
                MemCopy_800403E8(&saveData_8008B570.minions[n], &items[i], 0xF8);
                n++;
            }
        }
        free3_8003FC6C(items);
        return 1;
    }
    return 0;
}

int sub_800B9E94(UnitStats* src, Minion* dst, short c)
{
    int i;
    unsigned int j;
    unsigned int r;
    dst->id = c;
    for (i = 0; i < 6; i++)
    {
        CopyName_80019AF4((unsigned int*)dst->ancestors_4[i], (unsigned int*)src->st_0.name_10);
        dst->field_7C[i] = src->st_0.elementMask_42;
    }
    r = LowestSetBit_80014358(src->st_0.elementMask_42);
    for (j = 0; j < 4; j++)
    {
        dst->status_84.element_3E[j] = 0;
    }
    if (r >= 4)
    {
        printf(name_800B6D04, name_800B6D2C, 0x1AB);
        exit(1);
    }
    dst->status_84.element_3E[r] = 0x20;
    for (i = 0; i < 0x30; i++)
    {
        dst->species_4C[i] = src->species_5C;
    }
    dst->species_2 = src->species_5C;
    dst->field_3 = src->species_5C;
    MemCopy_800403E8(&dst->status_84, &src->st_0, sizeof(UnitStatus));
    MemCopy_800403E8(&dst->skills_DE, &src->skills_6C, sizeof(UnitSkills));
    MemCopy_800403E8(&dst->magicBits_F4, &src->magicBits_80, 4);
    return 1;
}

typedef struct ShopIdxShop
{
    int v[4];
} ShopIdxShop;
extern ShopIdxShop name_800B6D38;
extern int sub_80011D98(UnitStatus* a, int b);
extern void sub_800BAB38(Minion* a, Minion* b);
extern void sub_800BA368(Minion* d, Minion* s);
extern void sub_800BA3C8(unsigned char* d, unsigned char* a, unsigned char* b);
extern void sub_800BA4CC(Minion* d, Minion* a, Minion* b);
extern void sub_800BA650(Minion* d);
extern void sub_800BA6D0(Minion* d, Minion* s, Minion* t);
extern void sub_800BA72C(Minion* a, Minion* b);
extern void sub_800BAA0C(Minion* a, Minion* b);
extern int sub_800BACD0(Minion* d);
int MergeMinions_800B9FC8(Minion* a, Minion* b, Minion* c, int d)
{
    ShopIdxShop idx;
    UnitStats tmp;
    unsigned char* p;
    int i;
    int n;
    int t;
    int r;
    MemCopy_800403E8(c, a, sizeof(Minion));
    c->field_3 = b->field_3;
    p = sub_8001CD58(d);
    if (p[0] != 0xFF)
    {
        c->field_3 = p[0];
    }
    sub_800BAB38(c, b);
    for (i = 0; i < 4; i++)
    {
        c->status_84.element_3E[i] = (c->status_84.element_3E[i] + b->status_84.element_3E[i]) >> 1;
    }
    n = 0;
    idx = name_800B6D38;
    for (i = 0; i < 4; i++)
    {
        if (c->status_84.element_3E[i] & 1)
        {
            n++;
        }
    }
restart:
    for (i = 0; i < 3; i++)
    {
        if (c->status_84.element_3E[idx.v[i]] < c->status_84.element_3E[idx.v[i + 1]])
        {
            t = idx.v[i];
            idx.v[i] = idx.v[i + 1];
            idx.v[i + 1] = t;
            goto restart;
        }
    }
    if (n == 2)
    {
        for (i = 0; i < 4; i++)
        {
            p = (unsigned char*)c + idx.v[i]; // p[0xC2] == status_84.element_3E[idx.v[i]]; the struct form changes the codegen
            t = p[0xC2];
            if (t & 1)
            {
                if (n >= 2)
                {
                    p[0xC2] = t
 + 1;
                }
                else
                {
                    p[0xC2] = t
 - 1;
                }
                n--;
            }
        }
    }
    if (n == 4)
    {
        for (i = 0; i < 4; i++)
        {
            p = (unsigned char*)c + idx.v[i]; // p[0xC2] == status_84.element_3E[idx.v[i]]; the struct form changes the codegen
            t = p[0xC2];
            if (t & 1)
            {
                if (n >= 3)
                {
                    p[0xC2] = t
 + 1;
                }
                else
                {
                    p[0xC2] = t
 - 1;
                }
                n--;
            }
        }
    }
    for (i = 3; i >= 0; i--)
    {
    }
    c->status_84.elementMask_42 = 0;
    if (c->status_84.element_3E[0] >= 8)
    {
        c->status_84.elementMask_42 = 1;
    }
    if (c->status_84.element_3E[3] >= 8)
    {
        *(unsigned short*)&c->status_84.elementMask_42 |= 8;
    }
    if (c->status_84.element_3E[2] >= 8)
    {
        *(unsigned short*)&c->status_84.elementMask_42 |= 4;
    }
    if (c->status_84.element_3E[1] >= 8)
    {
        *(unsigned short*)&c->status_84.elementMask_42 |= 2;
    }
    sub_800BA368(c, a);
    sub_800BA3C8(c->status_84.stats_2C, a->status_84.stats_2C, b->status_84.stats_2C);
    sub_800BA4CC(c, a, b);
    sub_800BA650(c);
    sub_800BA6D0(c, a, b);
    sub_80011D98(&c->status_84, 2);
    sub_800BA72C(c, b);
    sub_800BAA0C(c, b);
    FillHpMp_80011C0C(&c->status_84, &c->status_84);
    r = sub_800BACD0(c);
    if (r > 0)
    {
        idx.v[0] = r;
        idx.v[1] = (c->status_84.level_44 << 26) + c->status_84.exp_4;
        InitMinionData_8001900C(&tmp, idx.v);
        sub_800B9E94(&tmp, c, c->id);
    }
    return 1;
}

void sub_800BA340(unsigned int* a)
{
    MemCopy_800403E8(a, name_800C07F0, 0xF8);
}

void sub_800BA368(Minion* d, Minion* s)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        d->status_84.stats_2C[i] = s->status_84.stats_2C[i] - s->status_84.base_32[i] / 20;
    }
    d->status_84.maxHp_A = s->status_84.maxHp_A;
    d->status_84.maxMp_E = s->status_84.maxMp_E;
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

void sub_800BA4CC(Minion* d, Minion* a, Minion* b)
{
    int tmp[4];
    int j;
    int i;
    int v;
    int y;
    int x;
    int t;
    int r;
    int k;
    for (k = 0; k < 12; k++)
    {
        x = (signed char)a->status_84.field_20[k];
        y = (signed char)b->status_84.field_20[k];
        if (x < y)
        {
            x = x * 2;
        }
        else
        {
            y = y * 2;
        }
        v = (x + y) / 3;
        if (v >= -128)
        {
            t = v;
            if (t > 127)
            {
                t = 127;
            }
            r = t;
        }
        else
        {
            r = -128;
        }
        d->status_84.field_20[k] = r;
    }
    memset(tmp, 0, 16);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp[j] += d->status_84.element_3E[i] * name_8007BA74[j + i * 4];
        }
    }
    for (i = 0; i < 4; i++)
    {
        d->status_84.field_20[i] = tmp[i] / 32;
    }
    for (i = 11; i >= 0; i--)
    {
    }
    for (i = 11; i >= 0; i--)
    {
    }
    for (i = 11; i >= 0; i--)
    {
    }
}

void sub_800BA650(Minion* d)
{
    int i;
    int v;
    int r;
    int t;
    unsigned char* p;
    for (i = 0; i < 6; i++)
    {
        // p[0xB0] / p[0xB6] == status_84.stats_2C[i] / base_32[i]; indexing the fields lets the compiler strength-reduce the loop
        p = (unsigned char*)d + i;
        v = p[0xB0] + (unsigned char)(p[0xB6] / 20);
        if (v >= 0) { t = v; if (t > 100) t = 100; r = t; } else r = 0; p[0xB0] = r;
    }


    for (i = 5; i >= 0; i--)
    {
    }
}

void sub_800BA6D0(Minion* d, Minion* s, Minion* t)
{
    d->status_84.level_44 = s->status_84.level_44;
    d->status_84.exp_4 = s->status_84.exp_4;
    d->status_84.exp_4 += sub_80012204(s->status_84.level_44, s->status_84.exp_4, t->status_84.level_44, t->status_84.exp_4);
}

#if 0
// Not matched (25 words): only the registers of &t.slot[i] (a3 in the original) and m (t0) are swapped.
// (When writing this in C, delete the jpt_800B6D4C line behind the function.)

void sub_800BA72C(Minion* a, Minion* b)
{
    UnitSkills t;
    UnitSkill* ae;
    UnitSkill* be;
    int i;
    int mask;
    int r;
    int m;
    int v;
    t = a->skills_DE;
    ae = a->skills_DE.slot;
    be = b->skills_DE.slot;
    for (i = 0; i < 5; i++)
    {
        t.slot[i].flags_0 |= (ae[i].flags_0 | be[i].flags_0) & 1;
    }
    mask = a->status_84.elementMask_42;
    for (i = 0; i < 5; i++)
    {
        switch (t.slot[i].id_1)
        {
        case 2:
            if (!(mask & 4))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        case 3:
            if (!(mask & 8))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        case 4:
            if (!(mask & 1))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        case 5:
            if (!(mask & 2))
            {
                t.slot[i].id_1 = 0;
            }
            break;
        }
        if (t.slot[i].flags_0 & 1)
        {
            m = a->status_84.elementMask_42;
            r = -1;
            switch (ae[i].id_1)
            {
            case 0:
            case 1:
                r = ae[i].id_1;
                break;
            case 2:
                if (m & 4)
                {
                    r = ae[i].id_1;
                }
                break;
            case 3:
                if (m & 8)
                {
                    r = ae[i].id_1;
                }
                break;
            case 4:
                if (m & 1)
                {
                    r = ae[i].id_1;
                }
                break;
            case 5:
                if (m & 2)
                {
                    r = ae[i].id_1;
                }
                break;
            default:
                r = ae[i].id_1;
                break;
            }
            if (r >= 0)
            {
                t.slot[i].id_1 = r;
            }
            r = -1;
            switch (be[i].id_1)
            {
            case 0:
            case 1:
                break;
            case 2:
                if (m & 4)
                {
                    r = be[i].id_1;
                }
                break;
            case 3:
                if (m & 8)
                {
                    r = be[i].id_1;
                }
                break;
            case 4:
                if (m & 1)
                {
                    r = be[i].id_1;
                }
                break;
            case 5:
                if (m & 2)
                {
                    r = be[i].id_1;
                }
                break;
            default:
                if (t.slot[i].id_1 == 0)
                {
                    r = be[i].id_1;
                }
                break;
            }
            if (r >= 0)
            {
                t.slot[i].id_1 = r;
            }
            if (t.slot[i].id_1 == 1)
            {
                t.slot[i].id_1 = 0;
            }
        }
        else
        {
            t.slot[i].id_1 = 0;
        }
        if (t.slot[i].flags_0 & 1)
        {
            v = be[i].bonus_2;
            if (v == 1)
            {
                t.slot[i].bonus_2 = 1;
                t.slot[i].field_3 = 0;
            }
            else if (v != 0 && v < 5)
            {
                t.slot[i].bonus_2 = v;
                t.slot[i].field_3 = 1;
            }
        }
        else
        {
            t.slot[i].bonus_2 = 0;
            t.slot[i].field_3 = 0;
        }
    }
    MemCopy_800403E8(&a->skills_DE, &t, sizeof(UnitSkills));
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BA72C);
INCLUDE_OVERLAY_ASM(shop, jpt_800B6D4C);
INCLUDE_OVERLAY_ASM(shop, dword_800B6D7C);

void sub_800BAA0C(Minion* a, Minion* b)
{
    unsigned int old = a->magicBits_F4;
    unsigned int* p = &a->magicBits_F4;
    int i;
    unsigned int mask;
    if (sub_800BAB30(b))
    {
        old |= b->magicBits_F4;
    }
    mask = a->status_84.elementMask_42;
    a->magicBits_F4 = old;
    for (i = 0; i < 30; i++)
    {
        if (TestMagicBit_8001AE2C(p, i) && (mask & (1 << GetMagicElement_8001AD30(i))) == 0)
        {
            ClearMagicBit_8001AE00(p, i);
        }
    }
    if ((char)a->status_84.element_3E[0] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x15);
    }
    if ((char)a->status_84.element_3E[2] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x17);
    }
    if ((char)a->status_84.element_3E[1] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x18);
    }
    if ((char)a->status_84.element_3E[3] != 0x20)
    {
        ClearMagicBit_8001AE00(p, 0x16);
    }
}

int sub_800BAB30()
{
    return 1;
}

#if 0 // near miss: compiler strength-reduces the first loop to pointer increments (96 of 102 words differ)
void sub_800BAB38(Minion* a, Minion* b)
{
    unsigned char tmp[0x30];
    unsigned int e[18];
    unsigned char g[6];
    int i;
    int j;
    for (i = 0; i < 0x30; i++)
    {
        if (i < 0x20)
        {
            if (i * 2 < 0x30)
            {
                tmp[i] = a->species_4C[i * 2];
            }
            else
            {
                tmp[i] = a->species_4C[i * 6 - 0x8F];
            }
        }
        else
        {
            tmp[i] = b->species_4C[i * 3 - 0x60];
        }
    }
    MemCopy_800403E8(a->species_4C, tmp, 0x30);
    CopyName_80019AF4(e, (unsigned int*)a->status_84.name_10);
    CopyName_80019AF4(e + 3, (unsigned int*)b->status_84.name_10);
    CopyName_80019AF4(e + 6, (unsigned int*)a->ancestors_4[0]);
    CopyName_80019AF4(e + 9, (unsigned int*)a->ancestors_4[1]);
    CopyName_80019AF4(e + 12, (unsigned int*)b->ancestors_4[0]);
    CopyName_80019AF4(e + 15, (unsigned int*)b->ancestors_4[1]);
    for (j = 0; j < 6; j++)
    {
        CopyName_80019AF4((unsigned int*)a->ancestors_4[j], e + j * 3);
    }
    g[0] = a->status_84.elementMask_42;
    g[1] = b->status_84.elementMask_42;
    g[2] = a->field_7C[0];
    g[3] = a->field_7C[1];
    g[4] = b->field_7C[0];
    g[5] = b->field_7C[1];
    for (j = 0; j < 6; j++)
    {
        a->field_7C[j] = g[j];
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BAB38);

int sub_800BACD0(Minion* d)
{
    int r = -1;
    int n6 = 0;
    int n5 = n6;
    int n4 = n6;
    int n3 = n6;
    int n2 = n6;
    int n1 = n6;
    int i = n6;
    unsigned char v;
    for (; i < 0x30; i++)
    {
        v = d->species_4C[i];
        if (v == 0x1E || v == 0xB1 || v == 0xB2 || v == 0xB3 || v == 0xB4)
        {
            n1++;
        }
        else if (v == 0xE || v == 0x71 || v == 0x72 || v == 0x73 || v == 0x74)
        {
            n2++;
        }
        else if (v == 0xF || v == 0x75 || v == 0x76 || v == 0x77 || v == 0x78)
        {
            n3++;
        }
        else if (v == 3 || v == 0x45 || v == 0x46 || v == 0x47 || v == 0x48)
        {
            n4++;
        }
        else if (v == 7 || v == 0x55 || v == 0x56 || v == 0x57 || v == 0x58)
        {
            n5++;
        }
        else if (v == 9 || v == 0x5D || v == 0x5E || v == 0x5F || v == 0x60)
        {
            n6++;
        }
    }
    if (n1 >= 3 && n2 >= 3 && n3 >= 3)
    {
        r = 0x22;
    }
    else if (n4 >= 3 && n5 >= 3 && n3 >= 3 && n6 >= 3)
    {
        r = 0x23;
    }
    return r;
}

int sub_800BAE80(Minion* p)
{
    unsigned int v = p->status_84.level_44;
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
    MemCopy_800403E8(t1, a, 0xF8);
    MemCopy_800403E8(t2, b, 0xF8);
    MemCopy_800403E8(a, t2, 0xF8);
    MemCopy_800403E8(b, t1, 0xF8);
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
    EventEntry* t = AllocEventEntry_80043AF8(name_8008D670);
    ShopUnit3Shop* u;
    if (t)
    {
        u = t->buffer;
        t->flags = (t->flags | 1) & ~0x8000;
        SetFontClutOffset_8003F900(2, 0);
        SetFontClutOffset_8003F900(1, 0);
        DrawMenuBackground_8002BE10();
        u->field_96 = a;
        sub_800BB148(u);
        sub_800BC380(u);
        t->cb_8 = sub_800BB0F8;
    }
}

extern void ShopMenuTask_800BB444();
void sub_800BB0F8(ShopTaskShop* t, int a)
{
    DrawMenuBackground_8002BE10();
    sub_800BC380(a);
    SetFadeMode_8001C19C(3, 0x20);
    t->next_8 = ShopMenuTask_800BB444;
}

// Matched
void sub_800BB148(ShopUnit3Shop* u)
{
    short i;
    void* r;
    Minion* mn;
    u->field_0 = 0;
    u->field_2 = -2;
    for (i = 0; i < 10; i++)
    {
        u->a5E[i] = 0;
    }
    for (i = 0; i < 4; i++)
    {
        u->a72[i] = 0;
    }
    for (i = 0; i < 2; i++)
    {
        u->a7A[i] = 0;
    }
    u->field_34 = 3;
    u->field_36 = 1;
    u->field_38 = 3;
    u->field_3A = 1;
    u->field_40 = 1;
    u->field_42 = 1;
    u->field_44 = 1;
    u->field_46 = 0x40;
    u->field_84 = 0;
    u->field_88 = 0;
    u->field_8C = 0;
    u->field_90 = 0;
    u->field_80 = 0;
    u->field_94 = 0;
    u->field_32 = 0;
    u->field_30 = 0;
    u->field_3E = 0;
    u->field_3C = 0;
    u->field_4A = 0;
    u->field_48 = 0;
    u->field_4C = 0;
    u->field_50 = 0;
    u->field_54 = 0;
    u->field_5C = 0;
    u->field_5A = 0;
    u->field_58 = 0;
    u->field_18 = 0;
    u->field_8 = 0;
    u->field_14 = 0;
    u->field_10 = 0;
    u->field_C = 0;
    u->field_98 = 0;
    u->field_7E = 0;
    u->field_24 = 1;
    u->field_1C = 0;
    u->field_1C = name_800BF8B4[u->field_0];
    u->field_20 = 0;
    SetShopHelpText_800BBB54(u, 0);
    sub_800BD854(u);
    fn_80011CD0(&levantStatus_8008BD38);
    for (i = 0; i < 12; i++)
    {
        r = GetSaveItem_80033AE4(&saveData_8008B570, i);
        if (r)
        {
            fn_80011CD0(r);
        }
    }
    for (i = 0; i < 3; i++)
    {
        mn = GetMinion_80010598(3, i);
        if (mn)
        {
            fn_80011CD0(&mn->status_84);
        }
    }
    sub_800B9920();
    fn_800AD8F4(fn_800AD888());
}

int sub_800BB38C(ShopUnit3Shop* p)
{
    switch (p->field_0)
    {
    case 5:
        if (p->field_84)
        {
            break;
        }
    case 1:
    case 2:
    case 7:
    case 8:
    case 10:
        return 1;
    }
    return 0;
}

int sub_800BB3E8(ShopUnit3Shop* p)
{
    switch (p->field_0)
    {
    case 5:
        if (p->field_84 == 0)
        {
    case 1:
    case 7:
            return 1;
        }
    }
    return 0;
}

extern int UpdateMenuCursor_8003D794(void* p, int a);
extern void sub_800BEBC8();
extern void sub_800BECC8();
extern void sub_800BBAAC();
extern void sub_800BBA3C();
extern void sub_800BBE24();
extern void sub_800BC2DC();
extern void sub_800BC1A8();
extern void sub_800BD0D4();
extern void sub_800BE2B4();
extern void sub_800B6CB8();
extern unsigned short padPressed_8009194C;
void ShopMenuTask_800BB444(ShopTaskShop* t, ShopUnit3Shop* u)
{
    short old;
    int r;
    DrawMenuBackground_8002BE10();
    if (u->field_24 & 1)
    {
        u->field_4 = CountItemsInState_800B9C78(2);
        u->field_6 = CountItemsInState_800B9C78(3);
        u->field_24 &= ~1;
    }
    if (u->field_0 != 15 && !(u->field_24 & 0x400))
    {
        u->field_24 &= ~0x1C0;
    }
    if ((u->field_24 & 2) || u->field_0 == 11 || u->field_0 == 12)
    {
        sub_8003CF88(0x11E, 0x3C, 0xE);
    }
    if (u->field_18 == 0)
    {
        sub_800BB798(u);
        sub_800BEBC8(u);
        sub_800BECC8(u);
    }
    sub_800BC380(u);
    if (u->field_18 == 0)
    {
        sub_800BB798(u);
        sub_800BBAAC(u);
        if (u->field_10 || u->field_14)
        {
            sub_800BD0D4(u);
        }
        if (!(u->field_24 & 4))
        {
            if (u->field_0 == 3 && (u->field_24 & 2))
            {
                old = u->field_3C;
                UpdateMenuCursor_8003D794(&u->field_34, 0);
                if (u->field_3C != old)
                {
                    u->field_40 = 1;
                    u->field_42 = 1;
                    u->field_44 = 1;
                    u->field_46 = 0;
                    u->field_4A = 0;
                    u->field_48 = 0;
                    if (u->field_24 & 0x40)
                    {
                        u->field_44 = 5;
                        u->field_42 = 5;
                    }
                    else if (u->field_24 & 0x80)
                    {
                        sub_800BECC8(u);
                        r = CountMagicBits_8001AE54(&u->field_54->magicBits_F4);
                        if (r < 4)
                        {
                            r = 4;
                        }
                        u->field_42 = 4;
                        u->field_40 = 1;
                        u->field_44 = r;
                        u->field_46 = 0x40;
                    }
                }
                if (u->field_24 & 0x400)
                {
                    UpdateMenuCursor_8003D794(&u->field_40, 0);
                }
            }
            if (!(u->field_24 & 2))
            {
                sub_800BBE24(u);
                if (u->field_0 == 8 || sub_800BB38C(u))
                {
                    if (padPressed_8009194C & 0x20)
                    {
                        if (u->field_4C->id != 4)
                        {
                            u->field_24 = (u->field_24 | 0x20) & ~0x400;
                            u->field_24 &= ~0x1C0;
                            sub_800BE2B4(u->field_54);
                        }
                    }
                }
            }
            else
            {
                sub_800BC2DC(u);
                if (u->field_0 == 3)
                {
                    if (padPressed_8009194C & 0x20)
                    {
                        if (u->field_4C->id != 4)
                        {
                            u->field_24 = (u->field_24 | 0x20) & ~0x400;
                            u->field_24 &= ~0x1C0;
                            sub_800BE2B4(u->field_54);
                        }
                    }
                    else if (padPressed_8009194C & 0x80)
                    {
                        u->field_24 |= 0x400;
                        sub_800BC1A8(u);
                    }
                }
                else if (sub_800BB38C(u))
                {
                    if (padPressed_8009194C & 0x20)
                    {
                        if (u->field_4C->id != 4)
                        {
                            u->field_24 = (u->field_24 | 0x20) & ~0x400;
                            u->field_24 &= ~0x1C0;
                            sub_800BE2B4(u->field_54);
                        }
                    }
                }
            }
        }
        else
        {
            t->flags_0 = (t->flags_0 & ~1) | 0x8000;
            sub_800B6CB8();
        }
    }
    else
    {
        sub_800BBA3C(u);
    }
    if (u->field_C < 8)
    {
        u->field_C++;
    }
}

void sub_800BB798(ShopUnit3Shop* u)
{
    short a;
    unsigned short b;
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

void sub_800BB828(ShopUnit3Shop* u)
{
    unsigned short b;
    short a;
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

extern unsigned short padPressed_8009194C;
void sub_800BBA3C(ShopUnit3Shop* u)
{
    if (u->field_98 < 0x96)
    {
        u->field_98 += 1;
    }
    if (padPressed_8009194C != 0 || u->field_98 >= 0x96)
    {
        SetShopHelpText_800BBB54(u, 0);
        u->field_18 = 0;
        u->field_98 = 0;
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

extern int* name_800BFC04[];
extern int* name_800BFC68[];
extern int* name_800BFB34[];
extern int* name_800BFB74[];
extern int name_800BF9B8[];
extern int name_800BFAA8[];
extern int* name_800BFAB4[];
extern int* name_800BFAF4[];
void SetShopHelpText_800BBB54(ShopUnit3Shop* u, int mode)
{
    switch ((short)mode)
    {
    case 1:
        if (u->field_96 == 4)
        {
            name_800BF7C8[0].w4 = name_800BFC04[u->field_8][0];
            name_800BF7C8[1].w4 = name_800BFC04[u->field_8][1];
            name_800BF7C8[2].w4 = name_800BFC04[u->field_8][2];
        }
        else
        {
            name_800BF7C8[0].w4 = name_800BFC68[u->field_8][0];
            name_800BF7C8[1].w4 = name_800BFC68[u->field_8][1];
            name_800BF7C8[2].w4 = name_800BFC68[u->field_8][2];
        }
        break;
    case 3:
        if (u->field_96 == 4)
        {
            name_800BF7C8[0].w4 = name_800BFB34[u->field_0][0];
            name_800BF7C8[1].w4 = name_800BFB34[u->field_0][1];
            name_800BF7C8[2].w4 = name_800BFB34[u->field_0][2];
        }
        else
        {
            name_800BF7C8[0].w4 = name_800BFB74[u->field_0][0];
            name_800BF7C8[1].w4 = name_800BFB74[u->field_0][1];
            name_800BF7C8[2].w4 = name_800BFB74[u->field_0][2];
        }
        break;
    case 2:
        if (u->field_96 == 4)
        {
            name_800BF7C8[0].w4 = name_800BF9B8[0];
            name_800BF7C8[1].w4 = name_800BF9B8[1];
            name_800BF7C8[2].w4 = name_800BF9B8[2];
        }
        else
        {
            name_800BF7C8[0].w4 = name_800BFAA8[0];
            name_800BF7C8[1].w4 = name_800BFAA8[1];
            name_800BF7C8[2].w4 = name_800BFAA8[2];
        }
        break;
    default:
        if (u->field_0 == 0)
        {
            if (u->field_96 == 4)
            {
                name_800BF7C8[0].w4 = name_800BFCF4[u->field_30][0];
                name_800BF7C8[1].w4 = name_800BFCF4[u->field_30][1];
                name_800BF7C8[2].w4 = name_800BFCF4[u->field_30][2];
            }
            else
            {
                name_800BF7C8[0].w4 = name_800BFD08[u->field_30][0];
                name_800BF7C8[1].w4 = name_800BFD08[u->field_30][1];
                name_800BF7C8[2].w4 = name_800BFD08[u->field_30][2];
            }
        }
        else
        {
            if (u->field_96 == 4)
            {
                name_800BF7C8[0].w4 = name_800BFAB4[u->field_0][0];
                name_800BF7C8[1].w4 = name_800BFAB4[u->field_0][1];
                name_800BF7C8[2].w4 = name_800BFAB4[u->field_0][2];
            }
            else
            {
                name_800BF7C8[0].w4 = name_800BFAF4[u->field_0][0];
                name_800BF7C8[1].w4 = name_800BFAF4[u->field_0][1];
                name_800BF7C8[2].w4 = name_800BFAF4[u->field_0][2];
            }
        }
        break;
    }
}

#if 0
// Not matched (34 words): only the f24 & 8 block differs. The original passes snd (in s1) to
// UpdateMenuCursor instead of a folded 0 (that needs int snd), keeps r in a1, and stores snd to
// s28/s7E through a copy; with int snd the copies and the r register still differ.
extern int sub_800BD6C4();
void sub_800BBE24(ShopUnit3Shop* u)
{
    short snd;
    int r;
    int k;
    unsigned int bit;
    if (u->field_24 & 8)
    {
        sub_800BEBC8(u);
        snd = 0;
        r = (short)UpdateMenuCursor_8003D794(&u->field_28, snd);
        if (r == 4)
        {
            snd = 1;
            u->field_2C = 0x18;
            u->field_2E = 0x50;
            u->field_28 = snd;
            u->field_7E = snd;
            u->field_2A = r;
            u->field_30 = 0;
            u->field_24 &= ~0x10;
            sub_800BB798(u);
        }
        else if (r == 3)
        {
            snd = 1;
            u->field_28 = snd;
            u->field_2E = 0x20;
            u->field_2A = r;
            u->field_2C = r;
            u->field_30 = 2;
            u->field_7E = 0;
            u->field_24 |= 0x10;
            sub_800BB798(u);
        }
        if (snd)
        {
            PlaySfx_80031494(0x7F);
        }
    }
    else
    {
        UpdateMenuCursor_8003D794(&u->field_28, 0);
    }
    if (u->field_0 == 15)
    {
        UpdateMenuCursor_8003D794(&u->field_40, 0);
    }
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (u->field_0 != 5)
        {
            if (sub_800BD6C4(u))
            {
                u->field_14 = 1;
            }
            else if (u->field_0 == 2 || u->field_0 == 10)
            {
                if (u->field_4C == u->field_50)
                {
                    u->field_14 = 1;
                }
                else
                {
                    u->field_10 = 1;
                }
            }
            else
            {
                u->field_10 = 1;
            }
        }
        else
        {
            if (u->field_4C->id != 4)
            {
                if (u->field_24 & 0x10)
                {
                    bit = 1 << (short)(u->field_30 + u->field_32);
                    if (!(u->field_88 & bit))
                    {
                        u->field_88 |= bit;
                        u->field_84 |= bit;
                        u->field_80++;
                    }
                    else
                    {
                        u->field_88 &= ~bit;
                        u->field_84 &= ~bit;
                        u->field_80--;
                    }
                }
                else
                {
                    k = (short)(u->field_30 + u->field_32);
                    bit = 1 << k;
                    if (!(u->field_8C & bit))
                    {
                        u->field_8C |= bit;
                        u->field_84 |= 1 << (k + 3);
                        u->field_80++;
                    }
                    else
                    {
                        u->field_8C &= ~bit;
                        u->field_84 &= ~(1 << (k + 3));
                        u->field_80--;
                    }
                }
                PlaySfx_80031494(0x7E);
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        u->field_14 = 1;
    }
    else if (padPressed_8009194C & 0x80)
    {
        if (u->field_0 == 8)
        {
            u->field_40 = 1;
            u->field_42 = 1;
            u->field_44 = 1;
            u->field_46 = 0;
            u->field_4A = 0;
            u->field_48 = 0;
            u->field_10 = 1;
            u->field_24 |= 0x400;
        }
        else if (u->field_0 == 15)
        {
            sub_800BC1A8(u);
        }
        else if (sub_800BB3E8(u) && sub_800B97B0())
        {
            PlaySfx_80031494(0x7E);
        }
    }
    else if (padPressed_8009194C & 0x20)
    {
        if (u->field_80 > 0 && u->field_0 == 5)
        {
            u->field_10 = 1;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BBE24);

void sub_800BC1A8(ShopUnit3Shop* u)
{
    int fl;
    int r;
    int t;
    if (u->field_54->id != 4)
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
            t = fl & ~0x40;
            t &= ~0x100;
            u->field_24 = t | 0x80;
            r = CountMagicBits_8001AE54(&u->field_54->magicBits_F4);
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
            int t2 = fl & ~0x40;
            t2 &= ~0x80;
            u->field_24 = t2 | 0x100;
        }
        else if (fl & 0x100)
        {
            int fl2 = fl & ~0x100;
            u->field_24 = fl2;
            if (u->field_0 == 3 && (fl & 2))
            {
                u->field_24 = fl2 & ~0x400;
            }
        }
        PlaySfx_80031494(0x7F);
    }
}

void sub_800BC2DC(ShopUnit3Shop* u)
{
    if (IsConfirmPressedP1_8003D380(0) || IsCancelPressedP1_8003D41C(0))
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
            SetShopHelpText_800BBB54(u, 0);
            u->field_24 &= ~2;
        }
    }
}

typedef struct ShopPosShop
{
    short x;
    short y;
} ShopPosShop;
typedef struct ShopRectShop
{
    short x;
    short y;
    short w;
    short h;
} ShopRectShop;
// window style for DrawWindow_80042460
typedef struct ShopWinShop
{
    short color;
    unsigned char field_2;
    unsigned char field_3;
} ShopWinShop;
// DrawUiWindow_8002A384's parameter block
typedef struct ShopUiWinShop
{
    ShopRectShop* rect_0;
    int time_4;
    short field_8;
    short ot_A;
} ShopUiWinShop;
typedef struct ShopPairShop
{
    short a;
    short b;
} ShopPairShop;
extern void sub_8002B3DC(ShopPairShop p, int b, void* c, int d);
extern int IsCircleHeldP1_8003D480(void);
extern int FindNthMagicBit_8001AEC0(unsigned int* bits, int n);
extern void sub_8002A4E4(int a);
extern void DrawTextList_8002A310(void* p, int a);
extern void sub_8002C670(Minion* m, ShopPosShop* pos, void* a2, int idx, int ot);
extern void DrawUiTiySprt_8002C06C(void* pos, int idx, int ot);
extern void DrawWindow_80042460(void* rect, ShopWinShop* w, void* ot, int t);
extern void sub_8002CE28(struct_minion_ref* a0, ShopPosShop* a1);
extern void sub_8002CAC8(struct_minion_ref* a0, ShopPosShop* a1);
extern void sub_8002D7D0(Minion* m, int ot, ShopPosShop* base);
extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern void sub_8002DB48(UnitStatus* m, int ot, void* rect, ShopPosShop* pos, Minion* mn, UnitStatus* cmp);
extern void sub_8002FAA0(int a0, unsigned short* pos, char* name, int a3);
extern void DrawUiWindow_8002A384(ShopUiWinShop* p);
extern void sub_800BCEDC(ShopUnit3Shop* u);
extern void sub_800BCCD8(ShopUnit3Shop* u);
extern void sub_800BE53C(ShopUnit3Shop* u);
extern void sub_800BE7F0(ShopUnit3Shop* u);
extern void DrawPersonList_800BED48();
extern ShopRectShop name_800BF790;
extern ShopRectShop name_800BF798;
extern ShopRectShop name_800BF7A0;
extern ShopRectShop name_800BF7A8;
extern ShopRectShop name_800BF7B0[];
extern char name_800C044C[];
extern char name_800C026C[][16];
#if 0
// Not matched: stack layout matches; loop-invariant constant 2 is not hoisted (the original keeps it in a spilled pseudo, rematerialised in $t1), so a few registers differ
void sub_800BC380(ShopUnit3Shop* u)
{
    ShopPosShop pos;
    ShopWinShop win;
    short i;
    short j;
    short n;
    int c;
    int t;
    if (u->field_24 & 0x40)
    {
        c = 0;
        if (u->field_54->skills_DE.slot[u->field_48].flags_0 & 1)
        {
            c = 0 < u->field_54->skills_DE.slot[u->field_48].id_1;
        }
        if (IsCircleHeldP1_8003D480() && c)
        {
            u->field_24 |= 0x1000;
        }
        else
        {
            u->field_24 &= ~0x1000;
        }
    }
    else if (u->field_24 & 0x80)
    {
        j = u->field_48 + u->field_4A;
        c = FindNthMagicBit_8001AEC0(&u->field_54->magicBits_F4, j) < 0x1E;
        if (IsCircleHeldP1_8003D480() && c)
        {
            u->field_24 |= 0x1000;
        }
        else
        {
            u->field_24 &= ~0x1000;
        }
    }
    if (u->field_0 == 3 && (u->field_24 & 2))
    {
        u->field_24 &= ~0x1000;
    }
    if (!(u->field_24 & 0x1000))
    {
        sub_8002A4E4(0xE);
        DrawTextList_8002A310(name_800BF7C8, 0xE);
        sub_800429F8((int)&name_800BF798, 0xE);
        sub_80042B38((int)&name_800BF798, 0xE);
    }
    else
    {
        pos.x = 10;
        pos.y = 0x12;
        if (u->field_24 & 0x40)
        {
            sub_8002C670(u->field_54, &pos, name_800C044C, u->field_48, 0xE);
        }
        else if (u->field_24 & 0x80)
        {
            DrawLargeTextBox_8002AF10((int)name_800C026C[FindNthMagicBit_8001AEC0(&u->field_54->magicBits_F4, u->field_48 + u->field_4A)], (int)&pos, 0xE);
        }
    }
    if (u->field_1C & 2)
    {
        pos.x = name_800BF7A0.x + 5;
        pos.y = name_800BF7A0.y + 3;
        pos.x = name_800BF7A0.x + 3;
        DrawUiTiySprt_8002C06C(&pos, 0xB5, 0xE);
        win.field_3 = 1;
        win.field_2 = 0;
        win.color = saveData_8008B570.uiColor_20.h;
        DrawWindow_80042460(&name_800BF7A0, &win, pOT_8008D454 + 0xE, 0);
        pos.x = name_800BF7A8.x + 5;
        pos.y = name_800BF7A8.y + 3;
        pos.x = name_800BF7A8.x + 4;
        DrawUiTiySprt_8002C06C(&pos, 0xE, 0xE);
        DrawWindow_80042460(&name_800BF7A8, &win, pOT_8008D454 + 0xE, 0);
        sub_800BE53C(u);
        sub_800BE7F0(u);
    }
    for (i = 0; i < 7; i++)
    {
        if (!((1 << i) & u->field_1C))
        {
            continue;
        }
        n = 8;
        if (!((1 << i) & u->field_20))
        {
            n = u->field_C;
        }
        if (i == 2)
        {
            if (u->field_54->id != 4 && !(u->field_24 & 0x20))
            {
                ShopPosShop p28;
                struct_minion_ref r30;
                ShopPosShop p40;
                struct_minion_ref r48;
                ShopPosShop p58;
                ShopPosShop p60;
                ShopRectShop r68;
                if (u->field_24 & 0x1C0)
                {
                    if (u->field_24 & 0x40)
                    {
                        p28.x = 0x5C;
                        p28.y = 0x5E;
                        r30.field_0 = u->field_48;
                        r30.field_2 = u->field_4A;
                        r30.field_4 = 2;
                        r30.field_6 = 0xE;
                        r30.field_8 = 0;
                        r30.field_A = 1;
                        r30.field_C_minion = u->field_54;
                        sub_8002CE28(&r30, &p28);
                    }
                    else if (u->field_24 & 0x80)
                    {
                        p40.x = 0x7E;
                        p40.y = 0x6D;
                        r48.field_0 = u->field_48;
                        r48.field_2 = u->field_4A;
                        r48.field_4 = 2;
                        r48.field_6 = 0xE;
                        r48.field_8 = 0;
                        r48.field_A = 1;
                        r48.field_C_minion = u->field_54;
                        sub_8002CAC8(&r48, &p40);
                    }
                    else if (u->field_24 & 0x100)
                    {
                        p58.x = 0x28;
                        p58.y = 0x1E;
                        sub_8002D7D0(u->field_54, 0xE, &p58);
                    }
                }
                if (!(u->field_24 & 0x1C0))
                {
                    p60.x = 0x5C;
                    p60.y = 0x5E;
                    InterpolateWindowRect_8004196C(&r68, &name_800BF790, n, 8, 0);
                    if (u->field_0 == 3 && u->field_3C == 2)
                    {
                        sub_8002DB48(&name_800C08E8.status_84, 0xE, &r68, &p60, u->field_54, &u->field_4C->status_84);
                    }
                    else
                    {
                        sub_8002DB48(&u->field_54->status_84, 0xE, &r68, &p60, u->field_54, 0);
                    }
                }
            }
            if (!(u->field_24 & 0x1C0))
            {
                ShopWinShop w28;
                w28.field_2 = 0;
                w28.field_3 = 1;
                w28.color = saveData_8008B570.uiColor_20.h;
                DrawWindow_80042460(&name_800BF790, &w28, pOT_8008D454 + 0xE, 0);
            }
        }
        if (!(u->field_24 & 0x800) && i == 3)
        {
            if (!(u->field_24 & 2) && u->field_18 == 0)
            {
                ShopRectShop r28;
                ShopUiWinShop w30;
                r28.x = 0x56;
                r28.y = u->field_30 * 16 + 0x25;
                r28.w = 0x1E;
                r28.h = 0x10;
                w30.rect_0 = &r28;
                w30.ot_A = 0xE;
                w30.time_4 = frameCount_8008D3FC;
                w30.field_8 = 1;
                DrawUiWindow_8002A384(&w30);
            }
        }
        if (i == 0)
        {
            sub_800BCEDC(u);
        }
        if (i == 4)
        {
            ShopRectShop r28;
            ShopPosShop p30;
            p30.x = name_800BF7B0[0].x + name_800BF7B0[0].w / 2;
            p30.y = name_800BF7B0[0].y + 2;
            InterpolateWindowRect_8004196C(&r28, &name_800BF7B0[0], 8, 8, 0);
            sub_8002FAA0(2, (unsigned short*)&p30, u->field_4C->status_84.name_10, 0xE);
            t = 0;
            if (u->field_3C == 0 && u->field_0 == 3 && (u->field_24 & 2))
            {
                t = frameCount_8008D3FC;
            }
            {
                ShopWinShop w38;
                w38.field_2 = 1;
                w38.field_3 = 1;
                w38.color = saveData_8008B570.uiColor_20.h;
                DrawWindow_80042460(&r28, &w38, pOT_8008D454 + 0xE, t);
            }
        }
        if (i == 5)
            for (j = 1; j < 3; j++)
            {
                ShopRectShop r38;
                InterpolateWindowRect_8004196C(&r38, &name_800BF7B0[j], 8, 8, 0);
                switch (j)
                {
                case 1:
                {
                    ShopPosShop p40;
                    p40.x = name_800BF7B0[j].x + name_800BF7B0[j].w / 2;
                    p40.y = name_800BF7B0[j].y + 2;
                    sub_8002FAA0(2, (unsigned short*)&p40, u->field_50->status_84.name_10, 0xE);
                    break;
                }
                case 2:
                {
                    ShopPosShop p48;
                    p48.x = name_800BF7B0[j].x + 7;
                    p48.y = name_800BF7B0[j].y + 1;
                    DrawUiTiySprt_8002C06C(&p48, 0x42, 0xE);
                    break;
                }
                }
                t = 0;
                if (j == u->field_3C && u->field_0 == 3 && (u->field_24 & 2))
                {
                    t = frameCount_8008D3FC;
                }
                {
                    ShopWinShop w40;
                    w40.field_2 = 1;
                    w40.field_3 = 1;
                    w40.color = saveData_8008B570.uiColor_20.h;
                    DrawWindow_80042460(&r38, &w40, pOT_8008D454 + 0xE, t);
                }
                if (u->field_0 == 3 && (u->field_24 & 2))
                {
                    ShopPairShop p48;
                    ShopPosShop p50;
                    p50.x = 0xA5;
                    p48.a = 0;
                    p48.b = 0;
                    p50.y = 0x55;
                    sub_8002B3DC(p48, frameCount_8008D3FC, &p50, 0xE);
                    p50.x = 0xFA;
                    sub_8002B3DC(p48, frameCount_8008D3FC, &p50, 0xE);
                }
            }
        if (i == 6)
        {
            struct_minion_ref r40;
            r40.field_0 = u->a5E[8];
            r40.field_2 = u->a72[2];
            r40.field_4 = 2;
            r40.field_6 = 0xE;
            r40.field_8 = 0;
            r40.field_A = 1;
            r40.field_C_minion = 0;
            DrawPersonList_800BED48(&r40);
        }
        if (u->field_C == 8)
        {
            u->field_20 |= 1 << i;
        }
    }
    if (u->field_0 != 11)
    {
        sub_800BCCD8(u);
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BC380);

void sub_800BCCD8(ShopUnit3Shop* u)
{
    switch (u->field_0)
    {
    case 1:
        if (u->field_24 & 0x20)
            DrawButtonHelpBar_8002B004(name_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_800C0048, 0, 0xE);
        break;
    case 2:
        if (u->field_24 & 0x20)
            DrawButtonHelpBar_8002B004(name_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_800BFF70, 0, 0xE);
        break;
    case 3:
        if (u->field_24 & 0x20)
            DrawButtonHelpBar_8002B004(name_800BFFE0, 0, 0xE);
        else if (u->field_24 & 2)
            DrawButtonHelpBar_8002B004(name_800BFFB8, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_80082680, 0, 0xE);
        break;
    case 5:
        if (u->field_24 & 0x20)
            DrawButtonHelpBar_8002B004(name_800BFFE0, 0, 0xE);
        else if (!u->field_84)
            DrawButtonHelpBar_8002B004(name_800BFF48, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_800BFF28, 0, 0xE);
        break;
    case 8:
        if (u->field_24 & 0x20)
            DrawButtonHelpBar_8002B004(name_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_800BFF90, 0, 0xE);
        break;
    case 15:
        if (u->field_24 & 0xC0)
            DrawButtonHelpBar_8002B004(name_800C0018, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_800C0000, 0, 0xE);
        break;
    case 7:
        if (u->field_24 & 0x20)
            DrawButtonHelpBar_8002B004(name_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_800C0048, 0, 0xE);
        break;
    case 10:
        if (u->field_24 & 0x20)
            DrawButtonHelpBar_8002B004(name_800BFFE0, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_800C0070, 0, 0xE);
        break;
    default:
        if (u->field_24 & 2)
            DrawButtonHelpBar_8002B004(name_800C0038, 0, 0xE);
        else
            DrawButtonHelpBar_8002B004(name_80082680, 0, 0xE);
        break;
    }
}
INCLUDE_OVERLAY_ASM(shop, dword_800B9608);

void sub_800BCEDC(ShopUnit3Shop* u)
{
    ShopSixShop q = name_800B9608;
    q.w1 = GetTime30Hz_8002C64C();
    q.w4 = (int)name_800C07D4;
    q.w0 = (q.w0 & ~7) | 2;
    q.w3 = u->field_30;
    q.w2 = 8;
    DrawMenuWindows_8002A5A4(&q);
}

#if 0 // near miss: orig shares the field_30 == 0 block with case 4 and cross-jumps the return-2 tails
int sub_800BCF74(ShopUnit3Shop* u)
{
    int s;
    if (u->field_0 == 0)
    {
        s = u->field_30;
        if (s == 0)
        {
            if (u->field_4 + u->field_6 < 2)
            {
                return 1;
            }
        }
        else if (s >= 0 && s < 4)
        {
            if (u->field_4 + u->field_6 == 0)
            {
                return 2;
            }
        }
        return 0;
    }
    switch (u->field_0)
    {
    case 5:
        if (!u->field_84 && !u->field_88)
        {
            return 2;
        }
        return 0;
    case 1:
    case 8:
        if (u->field_4C->id == 4)
        {
            return 2;
        }
        return 0;
    case 2:
        if (u->field_50->id == 4)
        {
            return 2;
        }
        if (u->field_50 == u->field_4C)
        {
            return 3;
        }
        return 0;
    case 4:
        if (u->field_4 + u->field_6 < 2)
        {
            return 1;
        }
        return 0;
    case 14:
        if (sub_800AD288(u->a5E[8] + u->a72[2], 4) == 0xFF)
        {
            return 4;
        }
        u->field_24 |= 0x200;
        return 0;
    }
    return 0;
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BCF74);
INCLUDE_OVERLAY_ASM(shop, jpt_800B9624);

extern short name_800BF868[]; // next state per state (-1: decided per cursor, -3: sub_800BD9DC)
extern short name_800BF8A8[]; // next state per cursor row of state 0
extern int sub_800AD398();
extern void sub_800BD9DC(ShopUnit3Shop* u);
int sub_800BCF74(ShopUnit3Shop* u);
int sub_800BD650(short* p);
int sub_800BD678(ShopUnit3Shop* p);
void sub_800BD720(ShopUnit3Shop* u);
// Matched
void sub_800BD0D4(ShopUnit3Shop* u)
{
    short s;
    int changed;
    int f;
    short k;
    s = 0;
    changed = 0;
    if (u->field_10)
    {
        s = sub_800BCF74(u);
        if (s == 0)
        {
            f = u->field_24;
            if (f & 8)
            {
                if (u->field_7E == 0)
                {
                    u->field_24 = f | 0x10;
                    u->field_58 = u->field_30;
                    if (u->field_0 != 5)
                    {
                        u->field_84 |= 1 << u->field_30;
                        u->field_88 |= 1 << u->field_30;
                    }
                }
                else
                {
                    u->field_24 = f & ~0x10;
                    u->field_5A = u->field_30;
                    u->field_5C = u->field_32;
                    if (u->field_0 != 5)
                    {
                        u->field_84 |= 1 << (u->field_30 + u->field_32 + 3);
                        u->field_8C |= 1 << (u->field_30 + u->field_32);
                    }
                }
            }
            if (name_800BF868[u->field_0] >= 0)
            {
                if (u->field_0 == 1)
                {
                    MemCopy_800403E8(&name_800C08E8, u->field_4C, sizeof(Minion));
                }
                PlaySfx_80031494(0x7E);
                u->field_2 = u->field_0;
                u->field_0 = name_800BF868[u->field_0];
                changed = 1;
                u->field_32 = 0;
                u->field_30 = 0;
                u->field_C = 0;
            }
            else if (name_800BF868[u->field_0] == -1)
            {
                u->field_2 = u->field_0;
                switch (u->field_0)
                {
                case 0:
                    if (u->field_30 == 4)
                    {
                        PlaySfx_80031494(0x7E);
                        if (u->field_4 < 13)
                        {
                            u->field_0 = 11;
                        }
                        else
                        {
                            u->field_0 = 12;
                        }
                    }
                    else
                    {
                        PlaySfx_80031494(0x7E);
                        u->field_0 = name_800BF8A8[u->field_30];
                    }
                    break;
                case 4:
                    if (u->field_30 == 0)
                    {
                        PlaySfx_80031494(0x7E);
                        u->field_0 = 1;
                        u->field_2 = 0;
                    }
                    else if (u->field_30 == 1)
                    {
                        PlaySfx_80031494(0x7D);
                        u->field_0 = 0;
                    }
                    break;
                case 2:
                    PlaySfx_80031494(0x7E);
                    if (sub_800AD398())
                    {
                        u->field_0 = 13;
                    }
                    else
                    {
                        sub_800BD720(u);
                        u->field_0 = 3;
                    }
                    u->field_2 = 2;
                    break;
                case 13:
                    if (u->field_30 == 0)
                    {
                        PlaySfx_80031494(0x7E);
                        u->field_0 = 14;
                    }
                    else
                    {
                        sub_800BD720(u);
                        u->field_0 = 3;
                    }
                    u->field_2 = 2;
                    break;
                case 14:
                    PlaySfx_80031494(0x7E);
                    sub_800BD720(u);
                    u->field_0 = 3;
                    u->field_2 = 1;
                    break;
                case 8:
                    PlaySfx_80031494(0x7E);
                    u->field_2 = u->field_0;
                    if (u->field_24 & 0x400)
                    {
                        u->field_0 = 15;
                        u->field_24 &= ~0x400;
                    }
                    else
                    {
                        u->field_0 = 9;
                    }
                    break;
                }
                changed = 1;
                u->field_32 = 0;
                u->field_30 = 0;
                u->field_C = 0;
            }
            else if (name_800BF868[u->field_0] == -3)
            {
                PlaySfx_80031494(0x7E);
                sub_800BD9DC(u);
            }
        }
        else
        {
            PlaySfx_80031494(0x7C);
            f = u->field_24;
            if (f & 8)
            {
                if (u->field_7E == 0)
                {
                    u->field_24 = f | 0x10;
                    u->field_58 = u->field_30;
                }
                else
                {
                    u->field_24 = f & ~0x10;
                    u->field_5A = u->field_30;
                    u->field_5C = u->field_32;
                }
            }
            u->field_8 = s;
            SetShopHelpText_800BBB54(u, 1);
            u->field_18 = 1;
        }
    }
    else if (u->field_14)
    {
        if (u->field_0 != 0 || u->field_30 != 4)
        {
            PlaySfx_80031494(0x7D);
            if (u->field_0 != 13 && u->field_0 != 14)
            {
                u->field_84 = 0;
                u->field_88 = 0;
                u->field_8C = 0;
            }
            if (u->field_0 == 3)
            {
                if (u->a7A[0] == 0)
                {
                    k = u->a5E[1];
                    u->field_84 |= 1 << k;
                    u->field_88 |= 1 << k;
                }
                else if (u->a7A[0] == 1)
                {
                    k = u->a5E[1] + u->a72[0];
                    u->field_84 |= 1 << (k + 3);
                    u->field_8C |= 1 << k;
                }
            }
            sub_800BB8C4(u);
            changed = 1;
        }
    }
    u->field_14 = 0;
    u->field_10 = 0;
    if (!(u->field_24 & 4))
    {
        if (s == 0 && changed)
        {
            if (sub_800BD650(&u->field_0))
            {
                u->field_24 |= 2;
                SetShopHelpText_800BBB54(u, 3);
            }
            else
            {
                SetShopHelpText_800BBB54(u, 0);
            }
        }
        sub_800BD7A8(u);
        if (sub_800BD678(u))
        {
            u->field_24 |= 8;
        }
        else
        {
            u->field_24 &= ~8;
        }
        sub_800BD854(u);
    }
}

int sub_800BD650(short* p)
{
    if (*p == 3 || *p == 13)
    {
        return 1;
    }
    return 0;
}

int sub_800BD678(ShopUnit3Shop* p)
{
    switch (p->field_0)
    {
    case 1:
    case 2:
    case 5:
    case 7:
    case 8:
    case 10:
        return 1;
    }
    return 0;
}

int sub_800BD6C4(ShopUnit3Shop* p)
{
    switch (*(short*)p)
    {
    case 3:
    case 4:
    case 6:
    case 9:
    case 13:
        if (p->field_30 == 1)
        {
            return 1;
        }
    }
    return 0;
}
INCLUDE_OVERLAY_ASM(shop, dword_800B96F0);

void sub_800BD720(ShopUnit3Shop* u)
{
    int d;
    if (u->field_4C && u->field_50)
    {
        if (u->field_24 & 0x200)
        {
            d = sub_800AD288(u->a5E[8] + u->a72[2], 4);
        }
        else
        {
            d = 10;
        }
        MergeMinions_800B9FC8(u->field_4C, u->field_50, &name_800C08E8, d);
    }
}

void sub_800BD7A8(ShopUnit3Shop* u)
{
    short i;
    unsigned short v;
    int s;
    v = u->field_20;
    u->field_1C = 0;
    s = name_800BF8B4[u->field_0];
    u->field_20 = 0;
    u->field_1C = s;
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

#if 0
// Not matched (8 words): the two blocks that set tk = name_8008D670 + 0x10 before a call load
// name_8008D670 straight into s0 and add 0x10 in place; here the load goes to a temporary.
// (When writing this in C, delete the jpt_800B96F4 line behind the function.)
extern void sub_800BDD74();
extern void sub_800BDE44();
extern void sub_80027314();
extern void sub_8001AAA8(int a);
extern void fn_800AD184(int a, int b, int c);
extern int sub_800BAF54(short* a, short* b, short c, short d);
void sub_800BD9DC(ShopUnit3Shop* u)
{
    ShopTaskShop* tk;
    SaveData* sv;
    int* p;
    int any;
    short i;
    switch (u->field_0)
    {
    case 3:
        if (u->field_30 != 0)
        {
            break;
        }
        sv = &saveData_8008B570;
        if (sv->settings_1C.bits.d_5 == 1)
        {
            MemCopy_800403E8(u->field_4C, &name_800C08E8, sizeof(Minion));
            sub_800B9B44((short*)u->field_50);
            if (u->field_4C->species_4C[0] == 0x23)
            {
                p = (int*)sv->allMinionsBitfields_814;
                p[1] |= 8;
            }
            else if (u->field_4C->species_4C[0] == 0x22)
            {
                p = (int*)sv->allMinionsBitfields_814;
                p[1] |= 4;
            }
            if (u->field_24 & 0x200)
            {
                fn_800AD1E0(fn_800AD288(u->a5E[8] + u->a72[2], 4), 1, 4);
                fn_800AD3F0(4);
                u->field_24 &= ~0x200;
            }
            u->field_84 = 0;
            u->field_88 = 0;
            u->field_8C = 0;
            u->field_24 |= 1;
            if (saveData_8008B570.settings_1C.bits.d_5 == 1)
            {
                tk = (ShopTaskShop*)&name_8008D670->entry;
                fn_80027478(0x40, 1);
                fn_8002C014();
                sub_80027314();
                tk->next_8 = sub_800BDD74;
                break;
            }
        }
        u->field_94 = 1;
        u->field_24 |= 0x800;
        tk = (ShopTaskShop*)&name_8008D670->entry;
        fn_8001ABEC(1);
        tk->next_8 = sub_800BDE44;
        sub_8001AAA8(0x20);
        break;
    case 6:
        if (u->field_30 != 0)
        {
            break;
        }
        any = 0;
        for (i = any; i < 27; i++)
        {
            if ((unsigned int)u->field_84 & (1 << i))
            {
                fn_800AD184(sub_800BAE80(sub_800B9C5C(i)), 1, 0);
                sub_800B9B20(i);
                any = 1;
            }
        }
        if (any == 0)
        {
            break;
        }
        u->field_84 = 0;
        u->field_88 = 0;
        u->field_8C = 0;
        u->field_24 |= 1;
        if (saveData_8008B570.settings_1C.bits.d_5 == 1)
        {
            tk = (ShopTaskShop*)&name_8008D670->entry;
            fn_80027478(0x40, 1);
            fn_8002C014();
            sub_80027314();
            tk->next_8 = sub_800BDD74;
        }
        else
        {
            u->field_94 = 2;
            u->field_24 |= 0x800;
            tk = (ShopTaskShop*)&name_8008D670->entry;
            fn_8001ABEC(1);
            tk->next_8 = sub_800BDE44;
            sub_8001AAA8(0x20);
        }
        break;
    case 9:
        sub_800BAF54((short*)u->field_4C, (short*)u->field_50, u->a7A[0] == 0 ? 3 : 2, u->a7A[1] == 0 ? 3 : 2);
        u->field_84 = 0;
        u->field_88 = 0;
        u->field_8C = 0;
        u->field_0 = 7;
        u->field_2 = 0;
        u->field_24 |= 1;
        SetShopHelpText_800BBB54(u, 0);
        break;
    case 10:
        tk = (ShopTaskShop*)&name_8008D670->entry;
        tk->next_8 = sub_800BE128;
        tk->flags_0 = (tk->flags_0 & ~1) | 0x8000;
        fn_800B6C6C(u->field_4C->status_84.name_10
, 0);
        SetFadeMode_8001C19C(0, 0x20);
        u->field_84 = 0;
        u->field_88 = 0;
        u->field_8C = 0;
        break;
    case 11:
        u->field_24 |= 4;
        break;
    case 12:
        u->field_0 = 0;
        break;
    }
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BD9DC);
INCLUDE_OVERLAY_ASM(shop, jpt_800B96F4);
INCLUDE_OVERLAY_ASM(shop, dword_800B971C);

void sub_800BDD74(ShopTaskShop* t, void* arg)
{
    ShopUnit3Shop* u = (ShopUnit3Shop*)arg;
    extern void sub_800BE128();
    extern void sub_800BE07C();
    if (fn_800272D0() == 0)
    {
        fn_800A7BF0(-1);
        if (u->field_0 == 3)
        {
            fn_800A5F9C(1);
            t->next_8 = sub_800BE128;
            fn_800B6C6C(u->field_4C->status_84.name_10
, 1);
        }
        else if (u->field_0 == 6)
        {
            fn_800A5F9C(2);
            t->next_8 = sub_800BE07C;
            fn_800B6CC8();
        }
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
        fn_80027478(0x40, 0);
        fn_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
    }
}

extern void sub_800BDEA8();
void sub_800BDE44(ShopTaskShop* t, int a)
{
    DrawMenuBackground_8002BE10();
    sub_800BC380(a);
    if (sub_8001AB94())
    {
        sub_8001AAF4();
        sub_8001AB1C(0x20);
        t->next_8 = sub_800BDEA8;
    }
}

void sub_800BDEA8(int dummy, ShopUnit3Shop* u)
{
    ShopTaskShop* tk;
    SaveData* sv;
    int* p;
    DrawMenuBackground_8002BE10();
    sub_800BC380(u);
    if (sub_8001AB94())
    {
        tk = (ShopTaskShop*)&name_8008D670->entry;
        if (u->field_94 == 1)
        {
            tk->next_8 = sub_800BE128;
        }
        else if (u->field_94 == 2)
        {
            tk->next_8 = sub_800BE07C;
        }
        tk->flags_0 = (tk->flags_0 & ~1) | 0x8000;
        fn_8002C014();
        if (u->field_94 == 1)
        {
            sv = &saveData_8008B570;
            if (!((sv->settings_1C.word >> 5) & 1))
            {
                MemCopy_800403E8(u->field_4C, &name_800C08E8, sizeof(Minion));
                sub_800B9B44((short*)u->field_50);
                if (u->field_4C->species_4C[0] == 0x23)
                {
                    p = (int*)sv->allMinionsBitfields_814;
                    p[1] |= 8;
                }
                else if (u->field_4C->species_4C[0] == 0x22)
                {
                    p = (int*)sv->allMinionsBitfields_814;
                    p[1] |= 4;
                }
                if (u->field_24 & 0x200)
                {
                    fn_800AD1E0(fn_800AD288(u->a5E[8] + u->a72[2], 4), 1, 4);
                    fn_800AD3F0(4);
                    u->field_24 &= ~0x200;
                }
                u->field_84 = 0;
                u->field_88 = 0;
                u->field_8C = 0;
                u->field_24 |= 1;
            }
            fn_800B6C6C(u->field_4C->status_84.name_10
, 1);
            SetFadeMode_8001C19C(0, 0x20);
        }
        else if (u->field_94 == 2)
        {
            fn_800B6CC8();
            SetFadeMode_8001C19C(0, 0x20);
        }
        u->field_24 &= ~0x800;
        fn_8001ABEC(0);
        u->field_94 = 0;
    }
}

extern void sub_800BE210();
void sub_800BE07C(ShopTaskShop* t, ShopUnit3Shop* u)
{
    u->field_0 = 5;
    u->field_2 = 0;
    sub_800BD7A8(u);
    SetShopHelpText_800BBB54(u, 0);
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
    LoadUiTiy_8002BF74();
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
    SetShopHelpText_800BBB54(u, 0);
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
    DrawMenuBackground_8002BE10();
    sub_800BC380(u);
    SetFadeMode_8001C19C(3, 0x20);
    sub_800A7B00(-1);
    t->next_8 = ShopMenuTask_800BB444;
}

extern void sub_800BE264();
void sub_800BE210(ShopTaskShop* t, int a)
{
    if (uiTiyLoaded_8008B4E8)
    {
        DrawMenuBackground_8002BE10();
        sub_800BC380(a);
        t->next_8 = sub_800BE264;
    }
}

extern void ShopMenuTask_800BB444();
void sub_800BE264(ShopTaskShop* t, int a)
{
    DrawMenuBackground_8002BE10();
    sub_800BC380(a);
    SetFadeMode_8001C19C(3, 0x20);
    t->next_8 = ShopMenuTask_800BB444;
}

extern void sub_800BE4D0();
void sub_800BE2B4(int a)
{
    ShopTaskShop* g = (ShopTaskShop*)&name_8008D670->entry;
    PlaySfx_80031494(0x7E);
    sub_800BF474();
    unknownFlags_8008D678 |= 0x10000;
    unknownFlags_8008D678 |= 0x4000000;
    sub_800BF4B8(a);
    g->next_8 = sub_800BE4D0;
}

extern void ShopMenuTask_800BB444();
void sub_800BE334(ShopTaskShop* t, ShopUnit3Shop* u)
{
    Actor* c;
    int v;
    DrawMenuBackground_8002BE10();
    sub_800BC380(u);
    c = sub_800BF780();
    if (padHeld_800918D0[0] & 0x8000)
    {
        *(unsigned short*)&c->rot_5C[1] += 0x88;
    }
    else if (padHeld_800918D0[0] & 0x2000)
    {
        *(unsigned short*)&c->rot_5C[1] -= 0x88;
    }
    if (padHeld_800918D0[0] & 8)
    {
        v = c->baseScale_138[0] + 0x40;
        if (v < 0x1000)
        {
            c->baseScale_138[0] = v;
            c->baseScale_138[1] += 0x40;
            c->baseScale_138[2] += 0x40;
        }
    }
    else if (padHeld_800918D0[0] & 2)
    {
        v = c->baseScale_138[0] - 0x40;
        if (v > 0x400)
        {
            c->baseScale_138[0] = v;
            c->baseScale_138[1] -= 0x40;
            c->baseScale_138[2] -= 0x40;
        }
    }
    if (IsCancelPressedP1_8003D41C(1))
    {
        sub_800BF750();
        unknownFlags_8008D678 &= ~0x10000;
        unknownFlags_8008D678 &= ~0x4000000;
        if (u->field_0 == 3)
        {
            SetShopHelpText_800BBB54(u, 3);
        }
        else
        {
            SetShopHelpText_800BBB54(u, 0);
        }
        if (u->field_0 == 5)
        {
            u->field_10 = 0;
        }
        u->field_24 &= ~0x20;
        t->next_8 = ShopMenuTask_800BB444;
    }
}

extern void sub_800BE334();
void sub_800BE4D0(ShopTaskShop* t, ShopUnit3Shop* a)
{
    DrawMenuBackground_8002BE10();
    sub_800BC380(a);
    if (ret_800BF520() == 1)
    {
        SetShopHelpText_800BBB54(a, 2);
        sub_800BF704(a->field_96);
        t->next_8 = sub_800BE334;
    }
}

extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern void sub_8002FAA0(int a0, unsigned short* pos, char* name, int a3);
extern ShopSixShop name_800B971C;
extern char name_800BFE24[];
void sub_800BE53C(ShopUnit3Shop* u)
{
    short r[4];
    short out[4];
    unsigned short p[2];
    ShopSixShop q;
    short sel;
    short h;
    int clut;
    short i;
    char* s;
    Minion* e;
    clut = 0;
    if (sub_800BD678(u))
    {
        sel = u->field_30;
    }
    else
    {
        sel = -1;
    }
    h = 8;
    if (!(u->field_20 & 2))
    {
        h = u->field_C;
    }
    r[2] = 0x40;
    r[3] = 0xE;
    for (i = 0; i < 3; i++)
    {
        if (sub_800B9C10(i) == 3)
        {
            e = sub_800B9C5C(i);
            s = (e->id == 4) ? 0 : e->status_84.name_10
;
        }
        else
        {
            s = 0;
        }
        r[0] = 0xD;
        r[1] = i * 15 + 0x5D;
        if (((unsigned int)u->field_84 & (1 << i)) && ((unsigned int)u->field_88 & (1 << i)))
        {
            SetFontClutOffset_8003F900(1, 3);
            clut = 1;
        }
        InterpolateWindowRect_8004196C(out, r, (short)h, 8, 0);
        p[0] = r[0] + r[2] / 2;
        p[1] = r[1] + 3;
        if (s)
        {
            sub_8002FAA0(2, p, s, 0xE);
        }
        if (clut)
        {
            SetFontClutOffset_8003F900(1, 0);
            clut = 0;
        }
        SetFontClutOffset_8003F900(1, 0);
    }
    q = name_800B971C;
    q.w1 = GetTime30Hz_8002C64C();
    q.w2 = (short)h;
    q.w4 = (int)name_800BFE24;
    if (u->field_24 & 0x10)
    {
        q.w3 = (short)sel;
    }
    else
    {
        q.w3 = -1;
    }
    if (u->field_0 == 6 || u->field_0 == 9 || u->field_0 == 3 || u->field_0 == 15)
    {
        q.w0 |= 4;
    }
    else
    {
        q.w0 |= 2;
    }
    q.w2 = 8;
    DrawMenuWindows_8002A5A4(&q);
    SetFontClutOffset_8003F900(1, 0);
}

extern char name_800BFF14[];
void sub_800BE7F0(ShopUnit3Shop* u)
{
    short r[4];
    short out[4];
    ShopPairShop p;
    ShopSixShop q;
    ShopPairShop pos1;
    ShopPairShop pos2;
    int base;
    short sel;
    short h;
    int clut;
    short i;
    char* s;
    Minion* e;
    int k;
    base = sub_800BEB60(u);
    clut = 0;
    if (sub_800BD678(u))
    {
        sel = u->field_30;
    }
    else
    {
        sel = -1;
    }
    h = 8;
    if (!(u->field_20 & 2))
    {
        h = u->field_C;
    }
    r[2] = 0x40;
    r[3] = 0xE;
    for (i = 0; i < 4; i++)
    {
        k = i + (short)base + 3;
        if (sub_800B9C10(k) == 2)
        {
            e = sub_800B9C5C(k);
            s = (e->id == 4) ? 0 : e->status_84.name_10
;
        }
        else
        {
            s = 0;
        }
        r[0] = 0xD;
        r[1] = i * 15 + 0x9A;
        if (((unsigned int)u->field_84 & (1 << (i + (short)base + 3))) && ((unsigned int)u->field_8C & (1 << (i + (short)base))))
        {
            SetFontClutOffset_8003F900(1, 3);
            clut = 1;
        }
        InterpolateWindowRect_8004196C(out, r, h, 8, 0);
        p.a = r[0] + r[2] / 2;
        p.b = r[1] + 3;
        if (s)
        {
            sub_8002FAA0(2, (unsigned short*)&p, s, 0xE);
        }
        if (clut)
        {
            SetFontClutOffset_8003F900(1, 0);
            clut = 0;
        }
    }
    q = name_800B971C;
    q.w1 = GetTime30Hz_8002C64C();
    q.w4 = (int)name_800BFF14;
    if (u->field_24 & 0x10)
    {
        q.w3 = -1;
    }
    else
    {
        q.w3 = sel;
    }
    if (u->field_0 == 6 || u->field_0 == 9 || u->field_0 == 3 || u->field_0 == 15)
    {
        q.w0 |= 4;
    }
    else
    {
        q.w0 |= 2;
    }
    q.w2 = 8;
    DrawMenuWindows_8002A5A4(&q);
    SetFontClutOffset_8003F900(1, 0);
    if (!(u->field_24 & 0x10))
    {
        if ((short)base < 20)
        {
            p.a = 2;
            p.b = 1;
            pos1.a = 0x52;
            pos1.b = 0xCB;
            sub_8002B3DC(p, frameCount_8008D3FC, &pos1, 0xE);
        }
        if ((short)base != 0)
        {
            p.a = 2;
            p.b = 3;
            pos2.a = 0x52;
            pos2.b = 0xA2;
            sub_8002B3DC(p, frameCount_8008D3FC, &pos2, 0xE);
        }
    }
}

int sub_800BEB60(ShopUnit3Shop* u)
{
    switch (u->field_0)
    {
    case 1:
    case 2:
    case 5:
    case 7:
    case 8:
    case 10:
        return u->field_32;
    case 3:
    case 4:
    case 13:
    case 14:
        return u->a72[1];
    case 6:
    case 9:
    case 15:
        return u->a72[0];
    }
    return -1;
}
INCLUDE_OVERLAY_ASM(shop, dword_800B9770);

void sub_800BEBC8(ShopUnit3Shop* u)
{
    int n;
    int v;
    switch (u->field_0)
    {
    case 1:
    case 5:
    case 7:
    case 8:
    case 15:
        if (u->field_24 & 0x10)
        {
            n = 0;
            v = (unsigned short)u->a5E[1];
        }
        else
        {
            n = 1;
            v = (unsigned short)u->a5E[1] + sub_800BEB60(u) + 3;
        }
        u->field_4C = sub_800B9C5C((short)v);
        u->a7A[0] = n;
        break;
    case 2:
    case 10:
        if (u->field_24 & 0x10)
        {
            n = 0;
            v = (unsigned short)u->a5E[2];
        }
        else
        {
            n = 1;
            v = (unsigned short)u->a5E[2] + sub_800BEB60(u) + 3;
        }
        u->field_50 = sub_800B9C5C((short)v);
        u->a7A[1] = n;
        break;
    }
}

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
            u->field_54 = &name_800C08E8;
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

typedef struct ShopWgtShop
{
    unsigned short flags_0;
    short pad_2;
    int val_4;
    void* p_8;
    void* p_C;
    short x_10;
    short y_12;
    int pad_14;
    int pad_18;
} ShopWgtShop;
extern ShopWgtShop* name_800C0258[];
extern char name_800B6D7C[];
extern char name_8008D434[];
extern char name_8008D440[];
extern char name_800C0090[];
extern char name_800C0094[];
extern void sub_8002C6DC(void* p, int a, int b);
void DrawPersonList_800BED48(short* s)
{
    ShopSixShop q;
    short h = 8;
    short prev = s[0];
    short i;
    int id;
    int icon;
    int name;
    int cnt;
    int y;
    int n;
    for (i = 0; i < 4; i++)
    {
        id = sub_800AD288(i + s[1], 4);
        if (id < 11)
        {
            icon = GetPersonIcon_8001CD6C(id);
            name = GetPersonName_8001CD3C(id);
            cnt = sub_800AD2C8(i + s[1], 4);
        }
        else
        {
            icon = -1;
            name = (int)name_800B6D7C;
            cnt = 0;
        }
        name_800C0258[i][0].val_4 = icon;
        name_800C0258[i][0].p_8 = name_8008D434;
        name_800C0258[i][0].p_C = name_8008D440;
        name_800C0258[i][1].val_4 = name;
        name_800C0258[i][2].val_4 = cnt;
        name_800C0258[i][0].x_10 = 0x7B;
        y = i * 22 + 0x68;
        name_800C0258[i][0].y_12 = y;
        name_800C0258[i][1].x_10 = 0x90;
        name_800C0258[i][1].y_12 = y;
        name_800C0258[i][2].x_10 = 0xFB;
        name_800C0258[i][2].y_12 = y;
        s[0] = i;
        if (cnt == 0)
        {
            name_800C0258[i][0].flags_0 |= 0x40;
            name_800C0258[i][1].flags_0 |= 0x40;
            name_800C0258[i][2].flags_0 |= 0x40;
        }
        else
        {
            name_800C0258[i][0].flags_0 &= ~0x40;
            name_800C0258[i][1].flags_0 &= ~0x40;
            name_800C0258[i][2].flags_0 &= ~0x40;
        }
    }
    q.w0 = s[2];
    q.w1 = frameCount_8008D3FC;
    q.w2 = h;
    q.w3 = prev;
    q.w4 = (int)name_800C0258;
    q.w5 = s[3];
    DrawMenuWindows_8002A5A4(&q);
    SetFontClutOffset_8003F900(2, 0);
    n = sub_800AD308(4) + 1;
    if (n < 4)
    {
        n = 4;
    }
    if (s[1] != 0)
    {
        sub_8002C6DC(name_800C0090, 3, s[3]);
    }
    if (s[1] < n - 4 && n >= 5)
    {
        sub_8002C6DC(name_800C0094, 1, s[3]);
    }
}

#if 0
// Not matched (17 words): the original cross-jumps the all-equal case into the o[1] == o[3] tail
// (o[4] += o[6]) and reloads o[6] in the o[2] != o[3] case; here the two tails get different registers.
typedef struct ShopLocalShop
{
    unsigned char b[4];
    int pad_4;
    int w[3];
} ShopLocalShop;
extern int sub_800BF2E4(unsigned char* p);
void sub_800BF02C(Minion* a, int* o, int c)
{
    ShopLocalShop l;
    unsigned int h = sub_80019C70(a->species_2)->modelId_0;
    int t;
    o[0] = sub_800338DC(a->species_4C, l.b, l.w);
    o[1] = sub_80019C70(l.b[0])->modelId_0;
    o[2] = sub_80019C70(l.b[1])->modelId_0;
    o[3] = sub_80019C70(l.b[2])->modelId_0;
    o[4] = l.w[0];
    o[5] = l.w[1];
    o[6] = l.w[2];
    if (o[1] == o[2])
    {
        if (o[2] == o[3])
        {
            o[4] = o[4] + o[5] + o[6];
            o[5] = 0;
            o[6] = 0;
            o[0] = 1;
        }
        else
        {
            t = o[6];
            o[0] = 2;
            o[4] = o[4] + o[5];
            o[6] = 0;
            o[2] = o[3];
            o[5] = t;
        }
    }
    else if (o[1] == o[3])
    {
        o[4] = o[4] + o[6];
        o[6] = 0;
        o[0] = 2;
    }
    else if (o[2] == o[3])
    {
        o[5] = o[5] + o[6];
        o[6] = 0;
        o[0] = 2;
    }
    o[11] = 0;
    if (o[1] != h)
    {
        if (o[2] == h)
        {
            t = o[5];
            o[2] = o[1];
            o[1] = h;
            o[5] = o[4];
            o[4] = t;
        }
        else if (o[3] == h)
        {
            t = o[6];
            o[3] = o[1];
            o[1] = h;
            o[6] = o[4];
            o[4] = t;
        }
        else if (o[0] < 2)
        {
            t = o[4];
            o[2] = o[1];
            o[1] = h;
            o[4] = 0;
            o[0] = 2;
            o[5] = t;
        }
        else
        {
            t = o[4];
            o[3] = o[1];
            o[1] = h;
            o[4] = 0;
            o[0] = 3;
            o[6] = t;
        }
    }
    o[7] = GetRankForLevel_80019A80(a->status_84.level_44);
    o[8] = o[0] - 1;
    o[10] = sub_80019C70(a->field_3)->modelId_0;
    o[12] = c;
    o[9] = sub_800BF2E4(a->status_84.element_3E);
    if (o[9] == -1000)
    {
        o[9] = sub_80019C70(a->field_3)->field_2 << 1;
    }
    else
    {
        o[9] = o[9] - (sub_80019C70(a->field_3)->field_3 << 1);

        if (o[9] < 0)
        {
            o[9] = o[9] + 0x168;
        }
    }
}
#endif
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

int sub_800BF3B4(unsigned char* p)
{
    int t2, t1, t4, t3, t5, t6, t7, t8;
    t1 = name_80084540[0].field_5C6 * p[0];
    t2 = name_80084540[3].field_5C6 * p[0];
    t3 = name_80084540[3].field_5C6 * p[3];
    t4 = name_80084540[2].field_5C6 * p[3];
    t5 = name_80084540[2].field_5C6 * p[2];
    t6 = name_80084540[1].field_5C6 * p[2];
    t7 = name_80084540[1].field_5C6 * p[1];
    t8 = name_80084540[0].field_5C6 * p[1];
    return ratan2Degrees_8003B56C(t1 + t3 + t5 + t7, t2 + t4 + t6 + t8);
}

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
    c->field_0 = StartModelTask_80010850(c->pad_4 + 4);
    c->field_3C = 0;
}

void sub_800BF520()
{
    RunModelTask_80010A10(name_800C09E0.field_0);
}

void sub_800BF548()
{
    int v = name_800C09E0.field_0;
    name_800C09E0.field_0 = -1;
    FreeModelTask_8001098C(v);
}

#if 0 // near miss: store scheduling / temp registers (17 words)
void sub_800BF574(int* a, unsigned short* b)
{
    ShopSetupShop q;
    ShopCtxShop* c = &name_800C09E0;
    int r = fn_80010A44(c->field_0);
    int v;
    int x;
    q.w0 = -1;
    q.w4 = 2;
    q.w8 = a[0];
    q.wC = a[1];
    q.w10 = a[2];
    q.s14 = b[0];
    q.s16 = b[1];
    v = *(int*)((char*)c + 0x24);
    q.s18 = b[2];
    q.w28 = 0x1000;
    q.w30 = 1;
    q.w1C = 0;
    q.w20 = 4;
    q.w24 = -1;
    q.w2C = 4;
    q.w48 = r;
    q.w34 = (int)name_80079140;
    q.w38 = fn_80024E90(r, v);
    q.w3C = fn_80024EC8(r, v);
    q.w40 = fn_80024E38(r);
    q.w44 = fn_80024E64(r);
    c->field_3C = fn_8001D45C(&q);
    x = fn_80024F00(r, v);
    r = fn_80024F38(r, v);
    fn_80019B14(*(int*)((char*)c->field_3C + 0x134), x, r);
    fn_8001D68C(c->field_3C, 0);
}
#endif
INCLUDE_OVERLAY_ASM(shop, sub_800BF574);

void sub_800BF6C4()
{
    ShopCtxShop* c = &name_800C09E0;
    if (c->field_3C)
    {
        DestroyActor_8001D600(c->field_3C);
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

Actor* sub_800BF780()
{
    return name_800C0A1C;
}

INCLUDE_OVERLAY_ASM(shop, dword_800BF790);
