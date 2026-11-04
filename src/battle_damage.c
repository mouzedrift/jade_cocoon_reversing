#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"




// Matched
int GetSealResultFlags_80013358(int idx)
{
    return sealResultFlags_80079320[idx];
}
typedef struct
{
    unsigned short flags_0;
    short power_2;
    signed char c4;
    unsigned char c5;
    unsigned char c6;
    signed char hit_7;
    unsigned char element_8;
    unsigned char kind_9;
    unsigned char statusMode_A; // 0: the status flags always apply, 3: they apply on a chance roll
    unsigned char damageType_B; // 0 hp, 1 mp (halved), 2 hp + 2/5 as mp, 3 instant death chance
} AttackDesc;
typedef struct
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
} AttackResult;
extern double sqrt(double);
extern int Rand100_80013E30(void);
// Matched
void CalcActionDamage_80013374(AttackDesc* action, UnitStatus* actorStatus, UnitStatus* targetStatus, int* actorStats, int* targetStats, int* cmd, AttackResult* out)
{
    int crit0;
    int crit1;
    int targetUnit;
    int atk;
    int def;
    int hit;
    int eva;
    int hitRoll;
    int critRoll;
    int damage;
    int i;
    int statusChance;
    int deathChance;
    int statusRoll;
    int ch;
    int statusPower;
    double root;
    double dmg;

    crit0 = 0;
    crit1 = 0;
    hit = 0;
    eva = 0;
    atk = 0;
    def = 0;
    targetUnit = LowestSetBit_80014358(cmd[3]);
    switch (action->kind_9)
    {
    case 0:
        atk = actorStats[0];
        hit = actorStats[4];
        def = targetStats[1];
        eva = targetStats[5];
        crit0 = actorStats[6];
        crit1 = targetStats[7];
        break;
    case 1:
        atk = actorStats[2];
        def = targetStats[3];
        hit = 100;
        break;
    case 2:
        atk = action->power_2;
        def = 1;
        hit = 100;
        break;
    }
    if ((signed char)targetStatus->modifiers_20[action->element_8] < 0)
    {
        def = 1;
        eva = def;
    }
    if (def == 0)
    {
        def = 1;
    }
    if (action->power_2 != 0)
    {
        hitRoll = Rand100_80013E30();
        critRoll = Rand100_80013E30();
        if (!(hit - eva < hitRoll) || HasStatusFlag_80033548(targetStatus, 2) != 0)
        {
            out->kind_0 = 1;
            if (action->element_8 != 0xFF)
            {
                root = atk * 100 / def;
                root = sqrt(root);
                dmg = (double)(atk * (actorStatus->level_44 + 3)) * root / 10.0 * action->power_2 / 100.0 / 20.0;
                if (critRoll < crit0 - crit1 + action->hit_7 && action->kind_9 == 0)
                {
                    out->kind_0 = 4;
                    dmg = dmg * 7.0 / 4.0;
                }
                if (action->element_8 < 4)
                {
                    root = sqrt(sqrt(actorStatus->element_3E[action->element_8] * 1250));
                    dmg = dmg * (root / 10.0);
                }
                dmg = dmg * (signed char)targetStatus->modifiers_20[action->element_8];
                dmg = dmg / 32.0;
                ch = dmg;
                damage = dmg;
                if (ch == 0 || (damage += frameCount_8008D3FC & 1) == 0)
                {
                    damage = 1;
                }
            }
            else
            {
                damage = atk;
            }
            if (HasStatusFlag_80033548(targetStatus, 0x400) && (action->statusMode_A != 0 || !(action->flags_0 & 0x400)))
            {
                damage = 0;
            }
            if (action->damageType_B == 0)
            {
                out->hpDamage_1C = damage;
                if (action->element_8 == 8 && damage > 0)
                {
                    if (GetHp_800334D8(targetStatus) < damage)
                    {
                        damage = GetHp_800334D8(targetStatus);
                    }
                    out->actorHpDamage_14 = -damage;
                }
            }
            else if (action->damageType_B == 1)
            {
                damage /= 2;
                out->mpDamage_20 = damage;
                out->kind_0 = 2;
                if (action->element_8 == 8 && damage > 0)
                {
                    if (GetMp_800334F0(targetStatus) < damage)
                    {
                        damage = GetMp_800334F0(targetStatus);
                    }
                    out->actorMpDamage_18 = -damage;
                }
            }
            else if (action->damageType_B == 3)
            {
                deathChance = (signed char)targetStatus->modifiers_20[action->element_8];
                if (rand() % 32 < deathChance)
                {
                    out->hpDamage_1C = GetHp_800334D8(targetStatus) - 1;
                    out->kind_0 = 4;
                    out->flags_4 |= 2;
                }
                else
                {
                    goto miss;
                }
            }
            else if (action->damageType_B == 2)
            {
                out->hpDamage_1C = damage;
                out->kind_0 = 3;
                out->mpDamage_20 = damage / 5 * 2;
            }
        }
        else
        {
        miss:
            out->kind_0 = 5;
        }
    }
    if (out->hpDamage_1C > 0 || out->mpDamage_20 > 0)
    {
        out->flags_4 |= 2;
    }
    if (action->power_2 == 0 || out->kind_0 != 5)
    {
        statusPower = (action->c6 + actorStats[8]) * targetStats[9] / 100;
        if (action->statusMode_A == 3)
        {
            statusRoll = Rand100_80013E30();
            if (action->element_8 == 11)
            {
                statusChance = 100;
            }
            else
            {
                statusChance = (statusPower * (signed char)targetStatus->modifiers_20[action->element_8]) ? statusPower * (signed char)targetStatus->modifiers_20[action->element_8] / 32 : 0;
            }
            if (statusChance > statusRoll)
            {
                goto status;
            }
            if (action->flags_0 & 0x7FB)
            {
                SetTargetHitFlag_800184A0(targetUnit, 2);
            }
        }
        else if (action->statusMode_A == 0)
        {
            if (action->flags_0 & 0x3800)
            {
            status:
                out->status_8 |= action->flags_0;
            }
            else
            {
                out->flags_4 |= action->flags_0;
            }
        }
    }
    if (HasStatusFlag_80033548(targetStatus, 0x3800) && (action->flags_0 & 0x7FB) && action->statusMode_A == 3)
    {
        for (i = 0; i < 3; i++)
        {
            int m = 1 << (i + 11);
            if (targetStatus->status_0 & m)
            {
                break;
            }
        }
        if (i == 0)
        {
            out->flags_4 |= 0x800;
            SetTargetHitFlag_800184A0(targetUnit, 3);
        }
        else if (i == 1)
        {
            out->flags_4 |= 0x1800;
            SetTargetHitFlag_800184A0(targetUnit, 4);
        }
        else
        {
            out->flags_4 |= 0x3800;
            SetTargetHitFlag_800184A0(targetUnit, 5);
        }
        out->status_8 &= ~0x7FB;
        SetTargetHitFlag_800184A0(targetUnit, 2);
    }
    if (out->hpDamage_1C == 0 && out->mpDamage_20 == 0 && out->status_8 != 0 && out->flags_4 != 0)
    {
        out->kind_0 = 5;
    }
    if (out->status_8 & 0x400)
    {
        out->hpDamage_1C = GetHp_800334D8(targetStatus);
        out->kind_0 = 1;
    }
    if (HasStatusFlag_80033548(targetStatus, 2))
    {
        out->status_8 &= ~2;
    }
}
extern void ResolveBattleAction_80012BB0(UnitStatus* actor, UnitStatus* target, int* cmd, int result);
// Matched
void UseItemOnUnit_80013C28(UnitStatus* actor, UnitStatus* target, int* cmd, int result)
{
    int bonus;
    if (cmd[0] == 4)
    {
        switch (cmd[1])
        {
        case 3:
            bonus = rand() % 6;
            if (bonus == 0)
            {
                bonus = 1;
            }
            else if (bonus == 5)
            {
                bonus = 3;
            }
            else
            {
                bonus = 2;
            }
            AdjustUnitStat_80012614(target, 1, bonus, 0);
            AdjustUnitStat_80012614(target, 0, bonus, 0);
            break;
        case 4:
            AdjustUnitStat_80012614(target, 5, RollOilBonus_80013DB0(), 0);
            break;
        case 5:
            AdjustUnitStat_80012614(target, 7, RollOilBonus_80013DB0(), 0);
            break;
        case 6:
            AdjustUnitStat_80012614(target, 9, RollOilBonus_80013DB0(), 0);
            break;
        case 7:
            AdjustUnitStat_80012614(target, 0xB, RollOilBonus_80013DB0(), 0);
            break;
        case 8:
            AdjustUnitStat_80012614(target, 0xD, RollOilBonus_80013DB0(), 0);
            break;
        }
        UseSporeItem_80011B24(cmd[1]);
        ResolveBattleAction_80012BB0(actor, target, cmd, result);
    }
}
