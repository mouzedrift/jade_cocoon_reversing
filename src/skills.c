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
#include "skills.h"
#include "party.h"


// Matched
ActionData* GetAbilityAction_800318C8(int idx)
{
    return &abilityActions_80083594[idx];
}
// Matched
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
// Matched
void SeVibOn(void)
{
}
// Matched
void SetVib(void)
{
}
// Matched
void SsUtVibrateOn(void)
{
}
// Matched
void SsUtVibrateOff(void)
{
}
// Matched
int IsSkillLearned_80031954(void* skills, int slot)
{
    unsigned char* skill = (unsigned char*)skills + slot * 4;
    return *skill & 1;
}
// Matched
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
extern int abilityNames_800834E4[];
extern int abilityBonusNames_80083580[];
// Matched
int GetAbilityName_800319CC(int idx)
{
    return abilityNames_800834E4[idx];
}
// Matched
int GetAbilityBonusName_800319E8(int idx)
{
    return abilityBonusNames_80083580[idx];
}
// Matched
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
