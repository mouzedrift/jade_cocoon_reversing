#ifndef _EFFECT_CMD_H_
#define _EFFECT_CMD_H_

#include "globals.h"
#include "common_tu.h" // BattleCmd
#include "actor.h"
#include "effect_obj.h" // ActorEffectReq

// the frames of an action: its first hit and its end (StartCommandAction_80018A4C, the battle action starters)
typedef struct ActionFrames
{
    short hit_0;
    short end_2;
} ActionFrames;

ActionFrames StartCommandAction_80018A4C(Actor* obj, BattleCmd* cmd, ActorScriptCmd** scripts, int c);
void SpawnActorEffects_8001852C(ActorEffectReq* req, int hitFlags);
int SetupCommandAction_80018C00(ActorActionDesc* desc, BattleCmd* cmd, ActorScriptCmd** scripts);
void SetTargetHitFlag_800184A0(int slot, int bit);
int PlayActorEffect_800184DC(ActorEffectReq* req, int slot);
void SetHitVariant_80018430(short variant);
int GetWeaponEffect_800189F8(void);
#endif
