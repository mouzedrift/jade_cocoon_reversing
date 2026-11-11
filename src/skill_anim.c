#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "skill_anim.h"




int SkillSlotToAnimIndex_80031870(int slot)
{
    switch (slot)
    {
    case 0:
        return 3;
    case 1:
        return 0;
    case 2:
        return 2;
    case 3:
        return 1;
    case 4:
        return 4;
    }
    return 0;
}
const int unused_800746D0 = 0;
