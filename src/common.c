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
#include "unit.h"
#include "common_tu.h"
#include "engine.h"
#include "skills.h"
#include "unit_stats.h"
#include "util.h"

const ActionData defaultActionData_80071F58 = { 0, 0, 100, 255, 115, 0, 0, 10, { 0, 3 } };
const char aAssertionFaile_2[] = "Assertion failed: file \"%s\", line %d\n";
const char aCommonC[] = "COMMON.C";
int sealResultFlags_80079320[10] = {
    1, 0, 1, 0, 5, 7, 11, 13,
    9, 15,
};
unsigned short statGrowthTable_80079348[0x15] = {
    0x11D, 0x140, 0x163, 0x186, 0x1A9, 0x1CC, 0x1EF, 0x212,
    0x235, 0x258, 0x27B, 0x29E, 0x2C1, 0x2E4, 0x307, 0x32A,
    0x34D, 0x370, 0x393, 0x3B6, 0x3E7,
};
unsigned short growthKindThresholds_80079374[40] = {
    190, 19, 180, 18, 170, 17, 160, 16,
    150, 15, 140, 14, 130, 13, 120, 12,
    110, 11, 100, 10, 90, 9, 80, 8,
    70, 7, 60, 6, 50, 5, 40, 4,
    30, 3, 20, 2, 10, 1,
};
unsigned char sealRatioThresholds_800793C4[4] = { 2, 3, 5, 10 };
unsigned char sealOutcomeTable_800793C8[5][4] = {
    { 0, 0, 4, 16 },
    { 5, 8, 12, 16 },
    { 8, 10, 14, 16 },
    { 14, 16, 16, 16 },
    { 15, 16, 16, 16 },
};
// the battle command menu's help / prompt / message lines
const char* battleHelpTexts_800793DC[41] = {
    helpEmpty_80071F00,
    helpAttackMenu_80071EF0,
    helpDefend_80071ED0,
    helpUseItem_80071EC0,
    helpEscape_80071EAC,
    helpChangeEquipment_80071E9C,
    helpWeaponAttack_80071E80,
    helpUseMagic_80071E68,
    helpSummonMinion_80071E58,
    helpSealInCocoon_80071E44,
    helpNormalAttack_80071E2C,
    helpBackToCocoonMaster_80071E1C,
    helpSpecialAttack_80071E08,
    helpSwapMinion_80071DF4,
    msgAttackWhom_80071DE0,
    msgCastMagicOnWhom_80071DC8,
    msgUseItemOnWhom_80071DAC,
    msgSpecialAttackWhom_80071D90,
    msgWhichMagic_80071D78,
    msgSummonWhichMinion_80071D5C,
    msgWhichItem_80071D40,
    msgSealWhichMinion_80071D24,
    msgWhichSpecialAttack_80071D08,
    msgSwapWhichMinion_80071CEC,
    msgMagicSealed_80071CD4,
    msgNotEnoughMp_80071CC0,
    msgNoElementMinion_80071CA0,
    msgCannotUseInBattle_80071C8C,
    msgNoMinionEquipped_80071C74,
    msgMinionIsDead_80071C5C,
    msgNoEmptyCocoon_80071C48,
    msgCannotSealMore_80071C30,
    msgSealSucceeded_80071C1C,
    msgSealFailed_80071C08,
    msgCannotUseItemNow_80071BEC,
    msgEscapedBattle_80071BD8,
    msgCouldNotEscape_80071BC4,
    msgCannotChooseCommand_80071BA8,
    msgPoisonDamage_80071B98,
    msgParalyzed_80071B88,
    msgAsleep_80071B78,
};
int dword_80079480[16] = {
    256, 256, 256, 256, 256, 256, 256, 256,
    256, 256, 256, 256, 256, 256, 256, 256,
};
int dword_800794C0[16] = {
    200, 325, 450, 475, 500, 475, 450, 375,
    300, 250, 200, 150, 100, 80, 55, 0,
};
int dword_80079500[8] = {
    -50, -75, -100, -70, -40, -25, -10, -5,
};
int dword_80079520[32] = {
    20, 30, 40, 50, 59, 79, 98, 128,
    157, 177, 197, 206, 216, 226, 236, 238,
    236, 226, 216, 206, 197, 177, 157, 128,
    98, 79, 59, 50, 40, 30, 20, 10,
};

// Matched
void AddStatus_80012794(UnitStatus* status, int bits)
{
    if (status->status_0 & 0x3F8)
    {
        bits &= ~0x3F8;
    }
    status->status_0 |= bits;
}
// Matched
void KillUnit_800127B8(UnitStatus* status)
{
    status->exp_4 = 0;
    status->hp_8.cur_0 = 0;
    status->status_0 |= 0x400;
}
// Matched
void AdjustUnitStatById_800127D0(int unit, int sel, int delta, int mask)
{
    UnitStatus* status = GetUnitStatus_80014390(unit & 0xFF);

    if (status != 0)
    {
        AdjustUnitStat_80012614(status, sel, delta, mask);
    }
}
// Matched
void ApplyStatusPenalties_80012828(int* stats, UnitStatus* status)
{
    if (status->status_0 & 1)
    {
        stats[0] = stats[0] * 4 / 5;
        stats[2] = stats[2] * 4 / 5;
    }
    if (status->status_0 & 2)
    {
        stats[1] = stats[1] * 2 / 3;
        stats[3] = stats[3] * 2 / 3;
        stats[5] = 0;
    }
    if (status->status_0 & 0x3F8)
    {
        stats[4] = stats[4] * 3 / 5;
        stats[5] = stats[5] * 3 / 5;
    }
    if (status->status_0 & 0x8000)
    {
        stats[3] = (0x7FFF < stats[3] + stats[3] * 5) ? 0x7FFF : stats[3] + stats[3] * 5;
        stats[1] = (0x7FFF < stats[1] + stats[1] * 5) ? 0x7FFF : stats[1] + stats[1] * 5;
        stats[5] = 0;
    }
}

// Matched
ActionData* GetAbilityActionData_800129B0(ActionData* out, unsigned char* skill, int unit)
{
    int id = 0xD3;
    int kind = skill[1];
    Minion* minion;
    UnitStats* stats;
    MemCopy_800403E8(out, GetAbilityAction_800318C8(kind), 12);
    minion = GetUnitMinion_80014444(unit & 0xFF);
    if (minion)
    {
        id = minion->species_2;
    }
    stats = GetUnitStats_8001449C(unit & 0xFF);
    if (stats)
    {
        id = stats->species_5C;
    }
    if (id != 0xD3)
    {
        if (kind == 0xF)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 2)
            {
                out->hit_7 = ((signed char)out->hit_7 + 60 < 126) ? out->hit_7 + 60 : 125;
            }
        }
        else if (kind == 0xE)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 1)
            {
                out->hit_7 = ((signed char)out->hit_7 + 60 < 126) ? out->hit_7 + 60 : 125;
            }
        }
        else if (kind == 0xC)
        {
            if (GetMinionEnhancementBody_80019C0C(id) & 2)
            {
                out->power_2 = 0;
            }
        }
    }
    switch (skill[2])
    {
    case 2:
        out->power_2 = ((short)out->power_2 + 30 < 256) ? (unsigned short)out->power_2 + 30 : 255;
        break;
    case 3:
        out->c5 = (out->c5 + 30 > 255) ? 255 : out->c5 + 30;
        out->c6 = (out->c6 + 20 > 255) ? 255 : out->c6 + 20;
        break;
    case 4:
        out->hit_7 = ((signed char)out->hit_7 + 50 < 126) ? out->hit_7 + 50 : 125;
        break;
    }
    return out;
}
extern const char aAssertionFaile_2[];
extern const char aCommonC[];
extern const ActionData defaultActionData_80071F58; // an empty action
extern int GetUnitSkills_80031B30(int unit);
extern int GetSkillMpCost_80031A04(int skills, int slot);
extern void CalcEffectiveStatus_800335D0(UnitStatus* src, UnitStatus* out);
extern void CalcBattleStats_80013EE8(int* out, UnitStatus* status, ActionData* action, int mode);
extern void CalcActionDamage_80013374(ActionData* action, UnitStatus* actorStatus, UnitStatus* targetStatus, int* actorStats, int* targetStats, BattleCmd* cmd, ActionResult* out);
extern int Rand100_80013E30(void);
// Matched
void ResolveBattleAction_80012BB0(UnitStatus* actor, UnitStatus* target, BattleCmd* cmd, ActionResult* out)
{
    int actorStats[12];
    int targetStats[12];
    UnitStatus actorStatus;
    UnitStatus targetStatus;
    ActionData local = defaultActionData_80071F58;
    ActionData* action;
    int actorUnit;
    int targetUnit;
    int skills;
    int id;
    Minion* minion;
    UnitStats* stats;
    int targetLevel;
    short maxHp;
    short hp;
    int element;
    int value;
    int levelDiff;
    int k;
    int j;
    int roll;

    actorUnit = LowestSetBit_80014358(cmd->mask_8);
    targetUnit = LowestSetBit_80014358(cmd->targets_C);
    out->kind_0 = 0;
    out->flags_4 = 0;
    out->status_8 = 0;
    out->actorHpCost_C = 0;
    out->actorMpCost_10 = 0;
    out->actorHpDamage_14 = 0;
    out->actorMpDamage_18 = 0;
    out->hpDamage_1C = 0;
    out->mpDamage_20 = 0;
    SetTargetHitFlag_800184A0(targetUnit, 0);
    action = &local;
    switch (cmd->kind_0)
    {
    case 0:
        if (cmd->mask_8 == 1)
        {
            MemCopy_800403E8(&local, GetLevantWeaponAction_8001D260(), 12);
        }
        break;
    case 6:
        skills = GetUnitSkills_80031B30(actorUnit & 0xFF);
        action = GetAbilityActionData_800129B0(&local, (unsigned char*)(skills + cmd->arg_4 * 4), targetUnit);
        out->actorMpCost_10 = GetSkillMpCost_80031A04(skills, cmd->arg_4);
        break;
    case 1:
        MemCopy_800403E8(&local, GetMagicAction_8001AD64(cmd->arg_4), 12);
        out->actorMpCost_10 = GetMagicMpCost_8001AC58(cmd->arg_4);
        break;
    case 4:
        MemCopy_800403E8(&local, GetItemData_8001CDF4(cmd->arg_4), 12);
        break;
    case 26:
        break;
    }
    CalcEffectiveStatus_800335D0(actor, &actorStatus);
    CalcEffectiveStatus_800335D0(target, &targetStatus);
    CalcBattleStats_80013EE8(actorStats, &actorStatus, action, cmd->mask_8);
    CalcBattleStats_80013EE8(targetStats, &targetStatus, action, cmd->targets_C);
    ApplyStatusPenalties_80012828(actorStats, &actorStatus);
    ApplyStatusPenalties_80012828(targetStats, &targetStatus);
    if (out->areaElement_24 == action->element_8 && action->power_2 != 0)
    {
        action->power_2 = (0xFFFF < action->power_2 + 60) ? -1 : (unsigned short)action->power_2 + 60;
    }
    if (out->fixedElement_26 == -1)
    {
        element = (signed char)action->areaElement_4;
        if (element != -1)
        {
            if ((element == 0 && out->areaElement_24 == 1) || (element == 3 && out->areaElement_24 == 0) || (element == 2 && out->areaElement_24 == 3) ||
                (element == 1 && out->areaElement_24 == 2) || out->areaElement_24 == -1)
            {
                out->areaElement_24 = (signed char)action->areaElement_4;
            }
        }
    }
    id = 0xD3;
    minion = GetUnitMinion_80014444(actorUnit & 0xFF);
    if (minion)
    {
        id = minion->species_2;
    }
    stats = GetUnitStats_8001449C(actorUnit & 0xFF);
    if (stats)
    {
        id = stats->species_5C;
    }
    if (id != 0xD3)
    {
        if ((GetMinionEnhancementBody_80019C0C(id) & 2) && cmd->kind_0 == 1 && action->power_2 > 0)
        {
            action->power_2 = (0xFFFF < action->power_2 + 10) ? -1 : (unsigned short)action->power_2 + 10;
        }
        if ((GetMinionEnhancementBody_80019C0C(id) & 1) && cmd->kind_0 == 6 && action->power_2 > 0)
        {
            action->power_2 = (0xFFFF < action->power_2 + 10) ? -1 : (unsigned short)action->power_2 + 10;
        }
    }
    switch (cmd->kind_0)
    {
    case 0:
    case 1:
    case 4:
    case 6:
        CalcActionDamage_80013374(action, &actorStatus, &targetStatus, actorStats, targetStats, cmd, out);
        break;
    case 5:
    case 26:
        maxHp = GetMaxHp_800334CC(target);
        hp = GetHp_800334D8(target);
        out->kind_0 = 7;
        value = maxHp / hp;
        targetLevel = GetLevel_80033514(target);
        if (targetLevel > 40)
        {
            targetLevel = 40;
        }
        levelDiff = (GetLevel_80033514(actor) - targetLevel) * 10 / 12;
        if (levelDiff > 0)
        {
            if (levelDiff > 5)
            {
                levelDiff = 5;
            }
            value <<= levelDiff;
        }
        else if (levelDiff < 0)
        {
            levelDiff = -levelDiff;
            if (levelDiff > 5)
            {
                levelDiff = 5;
            }
            value /= 1 << levelDiff;
        }
        if (HasStatusFlag_80033548(target, 2))
        {
            value <<= 3;
        }
        k = 0;
        while (sealRatioThresholds_800793C4[k] < value && k < 4)
        {
            k++;
        }
        roll = rand() % 16;
        j = 0;
        while (sealOutcomeTable_800793C8[k][j] <= roll)
        {
            j++;
            if (j >= 4)
            {
                printf(aAssertionFaile_2, aCommonC, 0x41C);
                exit(1);
            }
        }
        out->arg_2 = j;
        out->flags_4 |= 2;
        break;
    case 7:
        value = Rand100_80013E30();
        out->kind_0 = 0;
        if (value < 81)
        {
            out->arg_2 = 0;
        }
        else
        {
            out->arg_2 = 1;
        }
        if (HasStatusFlag_80033548(target, 2))
        {
            out->arg_2 = 0;

        }
        break;
    }
    if (out->kind_0 == 5)
    {
        SetTargetHitFlag_800184A0(targetUnit, 1);
        SetTargetHitFlag_800184A0(targetUnit, 2);
    }
}
// Matched
int IsDrainAction_80013228(UnitStatus* actor, UnitStatus* target, BattleCmd* cmd, ActionResult* out)
{
    ActionData local = defaultActionData_80071F58;
    ActionData* action = &local;
    int actorUnit = LowestSetBit_80014358(cmd->mask_8);
    int targetUnit = LowestSetBit_80014358(cmd->targets_C);
    switch (cmd->kind_0)
    {
    case 0:
        if (cmd->mask_8 == 1)
        {
            action = GetLevantWeaponAction_8001D260();
        }
        break;
    case 6:
        action = GetAbilityActionData_800129B0(&local, (unsigned char*)(GetUnitSkills_80031B30(actorUnit & 0xFF) + cmd->arg_4 * 4), targetUnit);
        break;
    case 1:
        action = GetMagicAction_8001AD64(cmd->arg_4);
        break;
    case 4:
        action = GetItemData_8001CDF4(cmd->arg_4);
        break;
    case 26:
        break;
    }
    return action->element_8 == 8;
}

// zero word at the end of this TU's .rdata, in front of the jump table of UseItemOnUnit_80013C28 (battle_damage)
const int dword_800720E4 = 0;
