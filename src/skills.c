#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "skills.h"
#include "party.h"


ActionData* GetAbilityAction_800318C8(int idx)
{
    return &abilityActions_80083594[idx];
}
int CheckMinionSkillStub_800318E4(unsigned int idx, int partySlot)
{
    Minion* m = GetMinion_80010598(3, partySlot - 1);
    if (m && IsSkillLearned_80031954(&m->skills_DE, idx))
    {
        if (idx < 0xff)
        {
            return 0;
        }
    }
    return 0;
}
void SeVibOn(void)
{
}
void SetVib(void)
{
}
void SsUtVibrateOn(void)
{
}
void SsUtVibrateOff(void)
{
}
int IsSkillLearned_80031954(void* skills, int slot)
{
    unsigned char* skill = (unsigned char*)skills + slot * 4;
    return *skill & 1;
}
int CountLearnedSkills_80031968(void* skills)
{
    int count;
    int i = 0;
    for (count = i; i < 0xff; i++)
    {
        if (IsSkillLearned_80031954(skills, i))
        {
            count++;
        }
    }
    return count;
}
extern const char* abilityNames_800834E4[];
extern const char* abilityBonusNames_80083580[];
const char* GetAbilityName_800319CC(int idx)
{
    return abilityNames_800834E4[idx];
}
const char* GetAbilityBonusName_800319E8(int idx)
{
    return abilityBonusNames_80083580[idx];
}
int GetSkillMpCost_80031A04(UnitSkill* skills, int slot)
{
    int cost;
    skills += slot;
    cost = 0;
    if (skills->flags_0 != 0)
    {
        switch (skills->id_1)
        {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            cost += 10;
            break;
        case 14:
        case 15:
            cost += 5;
            break;
        case 13:
            cost += 35;
            break;
        case 12:
            cost += 15;
            break;
        }
        switch (skills->bonus_2)
        {
        case 2:
        case 3:
        case 4:
            cost += 10;
            break;
        }
    }
    return cost;
}
