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


INCLUDE_OVERLAY_ASM(combat, dword_800A05A0);

INCLUDE_OVERLAY_ASM(combat, sub_800A05E0);

INCLUDE_OVERLAY_ASM(combat, sub_800A0898);

INCLUDE_OVERLAY_ASM(combat, sub_800A0968);

INCLUDE_OVERLAY_ASM(combat, sub_800A0A28);

INCLUDE_OVERLAY_ASM(combat, sub_800A0A6C);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A0D1C);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A0FF0);

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

INCLUDE_OVERLAY_ASM(combat, sub_800A14AC);

INCLUDE_OVERLAY_ASM(combat, sub_800A14F0);

INCLUDE_OVERLAY_ASM(combat, sub_800A1554);

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
