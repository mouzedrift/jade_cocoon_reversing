#ifndef _COMMON_TU_H_
#define _COMMON_TU_H_

extern const int dword_800720E4;

// outcome of a battle action (ResolveBattleAction_80012BB0)
typedef struct ActionResult
{
    unsigned short kind_0;
    short arg_2;
    int flags_4;
    int status_8;
    int actorHpCost_C;
    int actorMpCost_10;
    int actorHpDamage_14;
    int actorMpDamage_18;
    int hpDamage_1C;
    int mpDamage_20;
    short areaElement_24;
    short fixedElement_26;
} ActionResult;

#endif
