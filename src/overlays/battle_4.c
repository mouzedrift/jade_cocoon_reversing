// BATTLE.BIN, source file 4 of 6 from 0x800BF648, compiled with -O1 (config/overlay_cc.txt)
#include "battle.h"

// Matched
void InitTurnGauges_800BF648(short* gauges, unsigned int mode)
{
    gauges[0] = 500;
    gauges[1] = 0;
    gauges[2] = 0;
    gauges[3] = 0;
    gauges[4] = 0;
    gauges[5] = -0x2BC;
    gauges[6] = -0x578;
    switch (mode)
    {
    case 1:
        gauges[0] = 1000;
        return;
    case 0:
        return;
    case 2:
        gauges[0] = 0;
        gauges[4] = 1000;
        gauges[5] = 500;
        gauges[6] = 0x14D;
        return;
    }
}

// Matched
int AdvanceTurnGauges_800BF6BC(unsigned short* gauges, int summonedUnit)
{
    int next;
    unsigned int i;
    next = -1;
    do
    {
        for (i = 0; i < 7; i++)
        {
            if (i >= 4 || i == summonedUnit)
            {
                gauges[i] += GetUnitTurnSpeed_800BF784(i);
                if ((short)gauges[i] >= 1000)
                {
                    gauges[i] = 0;
                    next = i;
                    break;
                }
            }
        }
    } while (next < 0);
    return next;
}

void ResetTurnGauge_800BF770(short* gauges, int unit)
{
    gauges[unit] = 0x320;
}

int GetUnitTurnSpeed_800BF784(int unit)
{
    unsigned char stats[0x18];
    UnitStatus* status = GetUnitStatus_80014390(unit & 0xFF);
    if (status == 0)
    {
        return 0;
    }
    CalcEquippedStats_80033624(stats, status);
    return stats[4] + 10;
}

// Matched
void TickUnitStatus_800BF7C4(UnitStatus* unitStatus, short* hpChange, short* mpChange)
{
    unsigned int status = unitStatus->status_0;
    unsigned int oldStatus = status;
    int i;
    BatCureChance* cure;
    *hpChange = 0;
    *mpChange = 0;
    status = AdvancePetrification_800BFA34(status);
    if ((GetEquipmentId_8003356C(unitStatus, 2) & 0xFF) == 0x10)
    {
        status |= 0x4000;
    }
    if (oldStatus & 1)
    {
        *hpChange = unitStatus->hp_8.max_2 / 10;
        status &= ~2;
    }
    else if (status & 0x4000)
    {
        int damage = (short)(unitStatus->hp_8.max_2 / 20);
        *hpChange = -damage;
    }
    if (oldStatus & 0x8000)
    {
        *mpChange = -((unitStatus->level_44 >> 2) + 3);
        status &= ~0x8000;
    }
    if (status & 0x200)
    {
        *hpChange = unitStatus->hp_8.cur_0;
    }
    for (i = 0; i < COUNTOF_S(statusCureChances_800C9138); i++)
    {
        cure = &statusCureChances_800C9138[i];
        if (oldStatus & cure->mask)
        {
            if (Rand100_80013E30() >= cure->chance)
            {
                status &= ~cure->mask;
            }
        }
    }
    unitStatus->status_0 = status;
}

int IsUncapturableSpecies_800BF980(int species)
{
    int result = 0;
    if (species >= 0x29)
    {
        if (species < 0x39)
        {
            result = 1;
        }
        else if (species < 0xD3)
        {
            if (species > 0xC8)
            {
                result = 1;
            }
        }
    }
    return result;
}

int IsBossSpecies_800BF9B4(int species)
{
    int result = 0;
    switch (species)
    {
    case 0x29:
    case 0x2C:
    case 0x2E:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x37:
        result = 1;
        break;
    }
    return result;
}


// Matched
void MarkSpeciesCaptured_800BF9F0(int species)
{
    unsigned int id = species;
    unsigned int* bits = allMinionsBitfields_8008BD84;
    if (id < 0xE0)
    {
        unsigned int* word = &bits[id >> 5];
        int bit = 1 << (id & 0x1F);
        *word = bit | *word;
    }
}

int AdvancePetrification_800BFA34(int status)
{
    int stage = status & 0x3F8;
    return (status & ~0x3F8) | (stage << 1);
}

// Matched
int GetStatusCommand_800BFA4C(unsigned int status, unsigned int prevStatus)
{
    int cmd;
    if (status & 0x200)
    {
        return 0x13;
    }
    if (status & 2)
    {
        if (!(prevStatus & 2))
        {
            return 0x10;
        }
    }
    if (status & 0x8000)
    {
        if (!(prevStatus & 0x8000))
        {
            return 0x12;
        }
    }
    if (status & 1)
    {
        return 9;
    }
    if (prevStatus & 2)
    {
        if (!(status & 2))
        {
            return 0xF;
        }
    }
    if (prevStatus & 0x8000)
    {
        if (!(status & 0x8000))
        {
            return 0x11;
        }
    }
    if (status & 0x4000)
    {
        return 0x19;
    }
    cmd = 0x14;
    return cmd;
}

void SetHitVariantForCommand_800BFAF8(int kind)
{
    int variant;
    switch (kind)
    {
    case 9:
        variant = 1;
        break;
    case 7:
        variant = 8;
        break;
    case 11:
        variant = 4;
        break;
    case 14:
        variant = 0;
        break;
    case 18:
        variant = 2;
        break;
    case 2:
        variant = 3;
        break;
    case 13:
        variant = 5;
        break;
    case 21:
        variant = 7;
        break;
    case 22:
    default:
        return;
    }
    SetHitVariant_80018430(variant);
}

void StartBattleWindows_800BFB80()
{
    ResetWindowHighlights_800BFC10();
    StartEnemyWindows_800BFC40();
    StartActorWindow_800C01D8();
    StartHelpWindow_800C0440();
}
