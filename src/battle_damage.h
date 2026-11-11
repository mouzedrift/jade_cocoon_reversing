#ifndef _BATTLE_DAMAGE_H_
#define _BATTLE_DAMAGE_H_

#include "globals.h"
#include "common_tu.h" // BattleCmd, ActionResult

int GetSealResultFlags_80013358(int idx);
void UseItemOnUnit_80013C28(UnitStatus* actor, UnitStatus* target, BattleCmd* cmd, ActionResult* result);
#endif
