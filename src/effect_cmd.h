#ifndef _EFFECT_CMD_H_
#define _EFFECT_CMD_H_

#include "globals.h"
#include "camera.h" // ShortPair
#include "camera.h" // ShortPair

ShortPair StartCommandAction_80018A4C(Actor* obj, int* cmd, ActorScriptCmd** scripts, int c);
void SpawnActorEffects_8001852C(ActorEffectReq* req, int hitFlags);
int SetupCommandAction_80018C00(ActorActionDesc* desc, int* cmd, ActorScriptCmd** scripts);
void SetTargetHitFlag_800184A0(int slot, int bit);
int PlayActorEffect_800184DC(ActorEffectReq* req, int slot);
void SetHitVariant_80018430(short variant);
int GetWeaponEffect_800189F8(void);
#endif
