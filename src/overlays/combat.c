// COMBAT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombatSlotCombat
{
    int field_0;
    char* field_4;
    char pad_8[0x34];
    char* field_3C;
} CombatSlotCombat;

typedef struct CombatBlkC_combat { char pad[0xF8]; } CombatBlkC_combat;
typedef struct CombatBlkA_combat { char pad[744]; } CombatBlkA_combat;
typedef struct CombatBlkB_combat { char pad[3720]; } CombatBlkB_combat;
extern CombatSlotCombat dword_800A3A08[];
extern CombatBlkA_combat dword_800A3AA0[];
extern CombatBlkB_combat dword_800A1BC8[];
extern void sub_80018E5C(void* p);
extern void sub_80018EBC(void* p, int v);
extern void sub_8001E1DC(void* p);
extern void sub_800376A0(void* a, void* b);
extern int sub_800A10C0(int i);
extern int sub_800A1A3C(CombatBlkC_combat* p, int n);

typedef struct CombatTaskCombat
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombatTaskCombat;

extern int dword_800A3A8C;
extern int dword_800A4070;
extern int dword_800A4080;
extern int dword_800A39F0[];
extern void sub_8001D378(void);
extern void sub_8001D600(void* p);
extern void sub_8001E28C(void* p);
extern void sub_8001C19C(int a, int b);
extern void sub_800A0D1C(int i);
extern void sub_800A0B70(int i);
extern void sub_800A14F0();
extern void sub_800A1554();
extern void sub_800A15B4();
extern char* dword_8007DC78;
extern int sub_80010850(void* p);
extern int dword_8008D4F0[];
extern int dword_8008B4F8;
extern char dword_800A398C[];
extern int sub_800A1934(short* p);
extern void sub_800376A8(void);
extern void sub_80037748(void);
extern void sub_800368F8(void);
extern void nullsub_5(void);
extern void sub_800A12B8(void);
extern void sub_8003BC84(void* p);
extern void sub_80025D7C();
extern char* off_8007DC70;
typedef struct CombatObjCombat
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    char pad_30[0x10];
} CombatObjCombat;
typedef struct CombatMsgCombat
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    void* field_14;
    int field_18;
    void* field_1C;
} CombatMsgCombat;
extern int Cbt_80010A44(int a);
extern int Cbt_80019A80(int a);
extern int Cbt_80024E90(int a, int b);
extern int Cbt_80024EC8(int a, int b);
extern int Cbt_80024E38(int a);
extern int Cbt_80024E64(int a);
extern int Cbt_8001D45C(void* p);
extern int Cbt_80024F00(int a, int b);
extern int Cbt_80024F38(int a, int b);
extern void Cbt_80019B14(int a, int b, int c);
extern void Cbt_8001D68C(char* p, int on);
extern int dword_80079140[];
typedef struct CombatSpawnCombat
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    short field_14;
    short field_16;
    short field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int* field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
} CombatSpawnCombat;
extern int sub_8003B56C(int a, int b);
extern void sub_80029A10(void* a, void* b);
extern int sub_800A0968(unsigned char* a);
typedef struct CombatShortPair_combat
{
    unsigned short a;
    unsigned short b;
} CombatShortPair_combat;
typedef struct CombatReq2Combat
{
    int field_0;
    int field_4;
    char pad_8[4];
    unsigned short field_C;
    unsigned short field_E;
    unsigned short field_10;
    unsigned short field_12;
    char pad_14[8];
    unsigned short field_1C;
    unsigned short field_1E;
    unsigned short field_20;
    unsigned short field_22;
    char pad_24[4];
} CombatReq2Combat;
extern CombatShortPair_combat dword_8007DCAC[];
extern CombatShortPair_combat dword_8007DCBC[];
extern short dword_80084540[];
extern short dword_800A1BBC[];
extern unsigned char byte_800A38D9;
extern unsigned char byte_800A38DA;
extern unsigned char byte_800A38DB;
extern short word_800A1BC4;
extern char data_8008EEF8[];
extern void sub_800300E0(int a, int b);
extern void sub_8002BF74(void);
extern void sub_800A197C(short* p);
extern void sub_800A0D64(int a, int b);
extern void sub_800A14AC();
extern void CombatReq_8001E34C(void* p, void* q);

typedef struct CombatReqCombat
{
    int field_0;
    int field_4;
    void* field_8;
    short field_C;
    short field_E;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    short field_20;
    short field_22;
    short field_24;
    short field_26;
    short field_28;
    short field_2A;
    int field_2C;
    int field_30;
    char pad_34[0x2C];
} CombatReqCombat;
extern void sub_800A05E0(int a, void* b, char* c);


INCLUDE_OVERLAY_ASM(combat, dword_800A05A0);

INCLUDE_OVERLAY_ASM(combat, sub_800A05E0);

// Matched
int sub_800A0898(unsigned char* a)
{
    int n = 0;
    int r;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (a[i])
        {
            n++;
        }
    }
    if (n == 1)
    {
        r = -1000;
    }
    else if (n == 2)
    {
        if (a[3] && a[1])
        {
            r = a[1] < a[3] ? 0xF5 : 0x41;
        }
        else if (a[0] && a[2])
        {
            r = a[2] < a[0] ? 0x14F : 0x9B;
        }
        else
        {
            r = sub_800A0968(a);
        }
    }
    else
    {
        r = sub_800A0968(a);
    }
    return r;
}

#if 0
// Not matched: register allocation of the products differs (6 words)
int sub_800A0968(unsigned char* a)
{
    short* t = dword_80084540;
    int p0 = t[0x5C6 / 2] * a[0];
    int p1 = t[0x1DC6 / 2] * a[0];
    int p2 = t[0x1DC6 / 2] * a[3];
    int p3 = t[0x15C6 / 2] * a[3];
    int p4 = t[0x15C6 / 2] * a[2];
    int p5 = t[0xDC6 / 2] * a[2];
    int p6 = t[0xDC6 / 2] * a[1];
    int p7 = t[0x5C6 / 2] * a[1];
    return sub_8003B56C(p0 + p2 + p4 + p6, p1 + p3 + p5 + p7);
}
#endif

INCLUDE_OVERLAY_ASM(combat, sub_800A0968);

// Matched
void sub_800A0A28(void)
{
    int i;
    int m = -1;
    for (i = 1; i >= 0; i--)
    {
        dword_800A3A08[i].field_0 = m;
    }
    sub_8001D378();
}

// Matched
void sub_800A0A6C(void)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        if (dword_800A3A08[i].field_0 >= 0)
        {
            sub_800A0D1C(i);
            sub_800A0B70(i);
        }
    }
}

// Matched
void sub_800A0ACC(int i, int x)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    sub_800A05E0(x, s->pad_8, dword_8007DC78 + (i << 6));
    s->field_4 = (char*)x;
    s->field_0 = sub_80010850(s->pad_8);
    s->field_3C = 0;
}

// Matched
void sub_800A0B3C(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    sub_80010A10(s->field_0);
}

// Matched
void sub_800A0B70(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    int v = s->field_0;
    s->field_0 = -1;
    sub_8001098C(v);
}

// Matched
void sub_800A0BA8(int i, int* src, short* sh)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    CombatSpawnCombat r;
    int h = Cbt_80010A44(s->field_0);
    int v = Cbt_80019A80(*(unsigned char*)(s->field_4 + 0xC8));
    int x;
    int y;
    r.field_0 = -1;
    r.field_4 = 2;
    r.field_8 = src[0];
    r.field_C = src[1];
    r.field_10 = src[2];
    r.field_14 = sh[0];
    r.field_16 = sh[1];
    r.field_18 = sh[2];
    r.field_1C = i;
    r.field_20 = 4;
    r.field_24 = -1;
    r.field_28 = 0x1000;
    r.field_2C = 4;
    r.field_30 = 0;
    r.field_48 = h;
    r.field_34 = dword_80079140;
    r.field_38 = Cbt_80024E90(h, v);
    r.field_3C = Cbt_80024EC8(h, v);
    r.field_40 = Cbt_80024E38(h);
    r.field_44 = Cbt_80024E64(h);
    r.field_4C = 1;
    s->field_3C = (char*)Cbt_8001D45C(&r);
    x = Cbt_80024F00(h, v);
    y = Cbt_80024F38(h, v);
    Cbt_80019B14(*(int*)(s->field_3C + 0x134), x, y);
    Cbt_8001D68C(s->field_3C, 0);
}

// Matched
void sub_800A0D1C(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    if (s->field_3C)
    {
        sub_8001D600(s->field_3C);
        s->field_3C = 0;
    }
}

// Matched
void sub_800A0D64(int i, int id)
{
    unsigned short* q = (unsigned short*)sub_800251E4(id);
    CombatObjCombat o;
    CombatMsgCombat m;
    sub_80025ED0((int*)&o);
    o.field_0 = 2;
    o.field_14 = 0;
    o.field_4 = (int)q;
    o.field_8 = 0;
    o.field_18 = (int)(off_8007DC70 + (i << 4));
    m.field_0 = 0x69;
    m.field_4 = q[0];
    m.field_8 = q[3] << 11;
    m.field_C = q[4] << 11;
    m.field_10 = 0;
    m.field_14 = &o;
    m.field_18 = 0x3C;
    m.field_1C = sub_80025D7C;
    sub_8003BC84(&m);
}

// Matched
void sub_800A0E1C(int i, int* src)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    CombatReqCombat r;
    r.field_0 = 0;
    r.field_4 = 0;
    r.field_8 = 0;
    r.field_C = 0;
    r.field_E = -1;
    r.field_10 = -1;
    r.field_18 = 0;
    r.field_1C = 1;
    r.field_20 = 0;
    r.field_22 = 0;
    r.field_24 = -1;
    r.field_26 = -1;
    r.field_28 = -1;
    r.field_2A = -1;
    r.field_2C = 0;
    r.field_30 = 0;
    *(int*)(s->field_3C + 0x70) = src[0];
    *(int*)(s->field_3C + 0x74) = src[1];
    *(int*)(s->field_3C + 0x78) = src[2];
    r.field_8 = s->field_3C + 0x70;
    r.field_C = 0x100;
    r.field_26 = 2;
    CombatReq_8001E34C(s->field_3C, &r);
}

// Matched
void sub_800A0EE8(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    sub_8001E1C8((struct_obj_A*)s->field_3C);
}

// Matched
void sub_800A0F1C(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    sub_8001E1DC(s->field_3C);
}

INCLUDE_OVERLAY_ASM(combat, sub_800A0F50);

// Matched
void sub_800A0FF0(int i, int* p)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    if (*p != 0x14)
    {
        sub_8001E28C(s->field_3C);
    }
}

// Matched
void sub_800A1034(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    sub_80018E5C(s->field_3C);
}

// Matched
void sub_800A1068(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    sub_80018EBC(s->field_3C, sub_800A10C0(i));
}

// Matched
int sub_800A10A4(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    return (int)s->field_4 + 4;
}

// Matched
int sub_800A10C0(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    return (int)s->field_4 + 0x84;
}

// Matched
int sub_800A10DC(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    return (int)s->field_3C + 0x38;
}

// Matched
int sub_800A10F8(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    return *(int*)(s->field_3C + 0x1C4);
}

// Matched
void sub_800A111C(int i, int* out)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    out[0] = *(int*)(s->field_3C + 0x14C);
    out[1] = (int)(s->field_3C + 0x38);
    out[2] = *(int*)(s->field_3C + 0x1C4);
    out[3] = *(int*)(s->field_3C + 0x1C8);
    out[0xB] = *(int*)(s->field_3C + 0x144);
    out[0xC] = (int)(s->field_3C + 0x2C);
}

// Matched
int sub_800A11A0(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    return (int)s->field_4 + 0xDE;
}

// Matched
int sub_800A11BC(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    return (int)s->field_4 + 0xF4;
}

// Matched
int sub_800A11D8(int i)
{
    CombatSlotCombat* s = &dword_800A3A08[i];
    return (int)s->field_4;
}

// Matched
void sub_800A11F4(void)
{
    EventEntry* e = sub_80043AF8((EventNode*)dword_8008D4A0);
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        sub_800376A8();
        sub_80037748();
        e->cb_8 = (EventEntryFn)sub_800368F8;
        e->cb_C = (EventEntryFn)nullsub_5;
        e->flags = (e->flags | 4) & ~0x8000;
        sub_800A12B8();
    }
}

// Matched
void sub_800A127C(void)
{
    char* p = (char*)dword_8008D4A0;
    sub_800376A0(p + 0x10, *(void**)(p + 0x24));
    sub_80043B40((int*)dword_8008D4A0);
}

// Matched
void sub_800A12B8(void)
{
    char* p = (char*)dword_8008D4F0;
    char* q;
    *(short*)(p + 0x2E) = 0;
    *(int*)(p + 0x20) = 0;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(int*)(p + 0x1C) = 0;
    *(short*)(p + 0x34) = 0;
    *(short*)(p + 0x36) = 0;
    *(short*)(p + 0x38) = 0;
    *(short*)(p + 0x3C) = 0;
    *(short*)(p + 0x3E) = 0;
    *(short*)(p + 0x40) = 0;
    dword_8008B4F8 = 0x1000;
    q = (char*)&saveData_8008B570;
    *(int*)(q + 0x7A8) = 0;
    *(int*)(q + 0x7AC) = 0;
    *(int*)(q + 0x7B0) = 0;
    *(short*)(q + 0x7B4) = 0;
    *(short*)(q + 0x7B6) = 0;
    *(short*)(q + 0x7B8) = 0;
}

// Matched
int sub_800A1324(void)
{
    unknownFlags_8008D678 |= 0x2000000;
    unknownFlags_8008D678 |= 0x4000000;
    DrawIntroMovie_8001AF64(dword_800A398C);
    unknownFlags_8008D678 &= ~0x2000000;
    unknownFlags_8008D678 &= ~0x4000000;
    return 6;
}

#if 0
// Not matched: the original keeps the full address of the table in a register across the loops
void sub_800A13A0(CombatTaskCombat* t)
{
    int i;
    int j;
    int off = 0;
    dword_800A1BBC[0] = 1;
    dword_800A1BBC[1] = 5;
    dword_800A1BBC[2] = 5;
    dword_800A1BBC[3] = 2;
    dword_800A1BBC[4] = 0;
    dword_800A1BBC[5] = 0;
    for (i = 0; i < 2; i++)
    {
        char* q = (char*)dword_800A3AA0;
        for (j = 0; j < 3; j++)
        {
            sub_800A197C((short*)((char*)off + (int)q));
            q += 0xF8;
        }
        off += 0x2E8;
    }
    sub_800300E0(0x8E, 1);
    sub_8002BF74();
    sub_800A0D64(2, 0x42);
    sub_800A0D64(3, 0x41);
    t->next_8 = sub_800A14AC;
}
#endif

INCLUDE_OVERLAY_ASM(combat, sub_800A13A0);

// Matched
void sub_800A148C(void)
{
    FreeActiveOverlay_8002C014();
}

// Matched
void sub_800A14AC(CombatTaskCombat* t)
{
    if (dword_8008B4E8)
    {
        dword_800A3A8C = 0;
        dword_800A4070 = 0;
        t->next_8 = sub_800A14F0;
        t->next_8(t);
    }
}

// Matched
void sub_800A14F0(CombatTaskCombat* t)
{
    sub_8001C19C(0, 0x20);
    dword_800A4080 = LoadOverlay_80020BF8(1, dword_800A39F0[dword_800A3A8C]);
    t->next_8 = sub_800A1554;
}

// Matched
void sub_800A1554(CombatTaskCombat* t, int x)
{
    if (sub_8003BE30(dword_800A4080) == 0)
    {
        sub_8001C19C(3, 0x20);
        t->next_8 = sub_800A15B4;
        t->next_8(t, x);
    }
}

INCLUDE_OVERLAY_ASM(combat, sub_800A15B4);

INCLUDE_OVERLAY_ASM(combat, sub_800A16FC);

INCLUDE_OVERLAY_ASM(combat, sub_800A1844);

// Matched
int sub_800A1934(short* p)
{
    if (p == 0)
    {
        return 1;
    }
    return *p == 4;
}

// Matched
void sub_800A1958(char* p)
{
    sub_80033548((int*)(p + 0x84), 0x400);
}

// Matched
void sub_800A197C(short* p)
{
    *p = 4;
}

#if 0
// Not matched: address arithmetic of the destination is reassociated by the compiler
void sub_800A1988(void)
{
    int i;
    char* src = data_8008EEF8;
    byte_800A38DA = 0;
    for (i = 0; i < 15; i++)
    {
        sub_800403E8((unsigned int*)((char*)(byte_800A38D9 * 3720) + (int)&((CombatBlkA_combat*)dword_800A1BC8)[byte_800A38DA]), (unsigned int*)src, 0xF8);
        src += 0xF8;
        byte_800A38DA++;
    }
}
#endif

INCLUDE_OVERLAY_ASM(combat, sub_800A1988);

// Matched
int sub_800A1A3C(CombatBlkC_combat* p, int n)
{
    int i;
    int count = 0;
    for (i = 0; i < n; i++)
    {
        if (!sub_800A1934((short*)&p[i]))
        {
            count++;
        }
    }
    return count;
}

// Matched
void sub_800A1AAC(int i)
{
    sub_800A1A3C((CombatBlkC_combat*)&dword_800A3AA0[i], 3);
}

// Matched
void sub_800A1AEC(int i)
{
    sub_800A1A3C((CombatBlkC_combat*)&dword_800A1BC8[i], 0xF);
}

// Matched
void sub_800A1B2C(int i, void* p)
{
    CombatReq2Combat r;
    r.field_0 = 1;
    r.field_4 = 1;
    r.field_1C = dword_8007DCAC[i].a;
    r.field_1E = dword_8007DCAC[i].b;
    r.field_20 = 0x20;
    r.field_22 = 0x40;
    r.field_C = dword_8007DCBC[i].a;
    r.field_E = dword_8007DCBC[i].b;
    r.field_10 = 0x100;
    r.field_12 = 1;
    sub_80029A10(p, &r);
}

INCLUDE_OVERLAY_ASM(combat, dword_800A1BBC);
