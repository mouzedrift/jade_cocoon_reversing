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
extern void sub_800A1A3C(void* p, int n);

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


INCLUDE_OVERLAY_ASM(combat, dword_800A05A0);

INCLUDE_OVERLAY_ASM(combat, sub_800A05E0);

INCLUDE_OVERLAY_ASM(combat, sub_800A0898);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A0ACC);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A0BA8);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A0D64);

INCLUDE_OVERLAY_ASM(combat, sub_800A0E1C);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A111C);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A11F4);

// Matched
void sub_800A127C(void)
{
    char* p = (char*)dword_8008D4A0;
    sub_800376A0(p + 0x10, *(void**)(p + 0x24));
    sub_80043B40((int*)dword_8008D4A0);
}

INCLUDE_OVERLAY_ASM(combat, sub_800A12B8);

INCLUDE_OVERLAY_ASM(combat, sub_800A1324);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A1988);

INCLUDE_OVERLAY_ASM(combat, sub_800A1A3C);

// Matched
void sub_800A1AAC(int i)
{
    sub_800A1A3C(&dword_800A3AA0[i], 3);
}

// Matched
void sub_800A1AEC(int i)
{
    sub_800A1A3C(&dword_800A1BC8[i], 0xF);
}

INCLUDE_OVERLAY_ASM(combat, sub_800A1B2C);

INCLUDE_OVERLAY_ASM(combat, dword_800A1BBC);
