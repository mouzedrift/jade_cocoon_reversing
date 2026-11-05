#ifndef _TU_800318C8_H_
#define _TU_800318C8_H_

#include "unit.h"

extern ActionData* GetAbilityAction_800318C8(int idx); // an ability's action data (UnitSkill.id_1)

int GetSkillMpCost_80031A04(UnitSkill* skills, int slot);
int IsSkillLearned_80031954(void* skills, int slot);
#endif
