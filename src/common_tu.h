#ifndef _COMMON_TU_H_
#define _COMMON_TU_H_

#include "unit.h"

extern const int dword_800720E4;

// outcome of a battle action (ResolveBattleAction_80012BB0)
typedef struct ActionResult
{
    unsigned short kind_0;
    unsigned short arg_2; // seal index (GetSealResultFlags_80013358)
    int flags_4;  // status bits cured
    int status_8; // status bits inflicted on the target
    int actorHpCost_C;
    int actorMpCost_10;
    int actorHpDamage_14;
    int actorMpDamage_18;
    int hpDamage_1C;
    int mpDamage_20;
    short areaElement_24;
    short fixedElement_26;
} ActionResult;

// a battle command (ResolveBattleAction_80012BB0, IsDrainAction_80013228)
typedef struct BattleCmd
{
    int kind_0;    // 0 attack, 1 magic, 2 summon, 3 recall, 4 item, 5 capture, 6 special attack, 7 flee,
                   // 8 change fighter, 0xB killed, 0x12 defend, 0x14 none, 0x15 an enemy calls an ally, 0x1A capture of the last enemy
    int arg_4;     // magic / item / skill slot
    int mask_8;    // acting unit bits
    int targets_C; // target unit bits
} BattleCmd;

void AdjustUnitStatById_800127D0(int unit, int sel, int delta, int mask);
void ResolveBattleAction_80012BB0(UnitStatus* actor, UnitStatus* target, BattleCmd* cmd, ActionResult* out);
int IsDrainAction_80013228(UnitStatus* actor, UnitStatus* target, BattleCmd* cmd, ActionResult* out); // out is unused

#endif
