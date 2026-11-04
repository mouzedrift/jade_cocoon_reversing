// BATTLE.BIN, source file 3 of 3 from 0x800BE834 (.rdata from 0x800B6774)
#include "battle.h"


void ShowUnitHitResult_800BE834(int unit, int pos)
{
    switch (unitHitKinds_800C9CBC[unit])
    {
    case 0:
        break;
    case 1:
        StartHitNumber_800BF3DC(unit, 0, unitHpDamage_800C9D38[unit], pos, 0);
        if (unitHpDamage_800C9D38[unit] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            if (unit == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 2:
        StartHitNumber_800BF3DC(unit, 1, unitMpDamage_800C9D48[unit], pos, 0);
        if (unitMpDamage_800C9D48[unit] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            if (unit == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 3:
        StartHitNumber_800BF3DC(unit, 0, unitHpDamage_800C9D38[unit], pos, 0);
        StartHitNumber_800BF3DC(unit, 1, unitMpDamage_800C9D48[unit], pos, 0xC);
        if (unitHpDamage_800C9D38[unit] > 0 || unitMpDamage_800C9D48[unit] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            if (unit == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 4:
        StartHitNumber_800BF3DC(unit, 2, 0, pos, 0);
        StartHitNumber_800BF3DC(unit, 0, unitHpDamage_800C9D38[unit], pos, 0xC);
        FlashScreenWhite_800BF3AC();
        StartCameraShake_80037BFC(0x1E);
        if (unit == 0)
        {
            StartPadVibration_80036528(0, 1);
        }
        else
        {
            StartPadVibration_80036528(0, 2);
        }
        break;
    case 5:
        StartPadVibration_80036528(0, 0x26);
        break;
    case 6:
        break;
    case 7:
        StartPadVibration_80036528(0, captureVibrations_800C9134[unitReactions_800C9CC8[unit].arg_4]);
        break;
    }
}

#if 0 // Not matched: the shared 'return 1' block sits after the AreReactionsDone_800BEB68 test in the original (here it lands at the end and the last test flips); tried goto/early-return layouts
int IsActionDone_800BEA94()
{
    if (!(saveData_8008B570.field_0 & 0x20))
    {
        if (AnyHitNumberActive_800BF47C() == 1)
        {
            return 0;
        }
        if (TestBattleFlag_800BC820(4) == 1)
        {
            if (IsActorActionDone_800BEB50() == 0)
            {
                return 0;
            }
            if (AreReactionsDone_800BEB68() == 0)
            {
                return 0;
            }
        }
        else
        {
            if (handlerWaitsReactions_800C912C[(unsigned char)commandHandlerIdx_800C8B38[curCommand_800C9C88.kind_0]] == 0)
            {
                return IsActorActionDone_800BEB50();
            }
            return AreReactionsDone_800BEB68();
        }
    }
    return 1;
}
#endif

INCLUDE_OVERLAY_ASM(battle, IsActionDone_800BEA94);

int IsActorActionDone_800BEB50()
{
    return actionFrame_800C9D94 > actorTiming_800C9D98[1];
}

int AreReactionsDone_800BEB68()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (actionFrame_800C9D94 < reactionTimings_800C9DA0[i].end_2)
        {
            return 0;
        }
    }
    effectOutcomeFlag_8008D780 = 1;
    return 1;
}

void ApplyBattleCommand_800BEBB8()
{
    BatCmd_a cmd;
    BatResult_a res;
    UnitStatus* actor;
    UnitStatus* m;
    int flag;
    int r;
    unsigned int i;
    int bit;
    int a;

    GetUnitSide_800BC7DC(actingUnit_800C9C7C);
    flag = 1;
    actor = GetUnitStatus_80014390(actingUnit_800C9C7C);
    cmd = curCommand_800C9C88;
    if (curCommand_800C9C88.kind_0 == 0x12)
    {
        actor = GetUnitStatus_80014390(actingUnit_800C9C7C);
        actor->status_0 |= 0x8000;
    }
    for (i = 0; i < 7; i++)
    {
        r = GetUnitSide_800BC7DC(i);
        bit = 1 << i;
        unitReactions_800C9CC8[i].kind_0 = 0x14;
        unitReactions_800C9CC8[i].arg_4 = 0;
        unitReactions_800C9CC8[i].mask_8 = bit;
        unitReactions_800C9CC8[i].targets_C = 0;
        if (curCommand_800C9C88.targets_C & bit)
        {
            m = GetUnitStatus_80014390(i & 0xFF);
            res.areaElement_24 = shownAreaElement_800C9D82;
            res.f26 = (signed char)dword_800C9D83;
            cmd.targets_C = bit;
            ResolveBattleAction_80012BB0(actor, m, &cmd, &res);
            if (dword_800ADE78.f0 == 1)
            {
                sub_800B4390(actor, m, &curCommand_800C9C88, &res, &dword_800ADE78);
            }
            areaElement_800C9D84 = res.areaElement_24;
            unitHpDamage_800C9D38[i] = res.hpDamage_1C;
            unitMpDamage_800C9D48[i] = res.mpDamage_20;
            if (actingUnit_800C9C7C < 7 && i != actingUnit_800C9C7C)
            {
                unitHpDamage_800C9D38[actingUnit_800C9C7C] += res.actorHpDamage_14;
                unitMpDamage_800C9D48[actingUnit_800C9C7C] += res.actorMpDamage_18;
                if (unitHpDamage_800C9D38[actingUnit_800C9C7C] != 0)
                {
                    if (unitMpDamage_800C9D48[actingUnit_800C9C7C] != 0)
                    {
                        unitHitKinds_800C9CBC[actingUnit_800C9C7C] = 3;
                    }
                    else
                    {
                        unitHitKinds_800C9CBC[actingUnit_800C9C7C] = 1;
                    }
                }
                else if (unitMpDamage_800C9D48[actingUnit_800C9C7C] != 0)
                {
                    unitHitKinds_800C9CBC[actingUnit_800C9C7C] = 2;
                }
            }
            if (unitHpDamage_800C9D38[i] > 0)
            {
                if (m->hp_8.cur_0 < unitHpDamage_800C9D38[i])
                {
                    unitHpDamage_800C9D38[i] = m->hp_8.cur_0;
                }
            }
            else if (unitHpDamage_800C9D38[i] < m->hp_8.cur_0 - m->hp_8.max_2)
            {
                unitHpDamage_800C9D38[i] = m->hp_8.cur_0 - m->hp_8.max_2;
            }
            if (unitMpDamage_800C9D48[i] > 0)
            {
                if (m->mp_C.cur_0 < unitMpDamage_800C9D48[i])
                {
                    unitMpDamage_800C9D48[i] = m->mp_C.cur_0;
                }
            }
            else if (unitMpDamage_800C9D48[i] < m->mp_C.cur_0 - m->mp_C.max_2)
            {
                unitMpDamage_800C9D48[i] = m->mp_C.cur_0 - m->mp_C.max_2;
            }
            if (res.actorHpCost_C != 0)
            {
                actorHpChange_800C9C7E = res.actorHpCost_C;
            }
            if (res.actorMpCost_10 != 0)
            {
                actorMpChange_800C9C80 = res.actorMpCost_10;
            }
            if (IsUnitInBattle_800BC784(i) == 1)
            {
                unitHitKinds_800C9CBC[i] = res.kind_0;
                unitResultFlags_800C9D58[i] = res.flags_4;
                unitStatusInflicted_800C9CA0[i] = res.status_8;
                switch (res.kind_0)
                {
                case 0:
                    unitReactions_800C9CC8[i].arg_4 = res.arg_2;
                    if (res.arg_2 != 0)
                    {
                        flag = 0;
                    }
                    break;
                case 1:
                case 2:
                case 3:
                    if (unitHpDamage_800C9D38[i] > 0 || unitMpDamage_800C9D48[i] > 0)
                    {
                        unitReactions_800C9CC8[i].kind_0 = 9;
                        hitSfx_800C9D78 = 0x72;
                    }
                    break;
                case 4:
                    unitReactions_800C9CC8[i].kind_0 = 10;
                    hitSfx_800C9D78 = 0x71;
                    break;
                case 5:
                    a = m->status_0 & 0x8000;
                    unitReactions_800C9CC8[i].kind_0 = a ? 0x14 : 0xC;
                    hitSfx_800C9D78 = 0x70;
                    break;
                case 7:
                    unitReactions_800C9CC8[i].kind_0 = 5;
                    unitReactions_800C9CC8[i].arg_4 = res.arg_2;
                    curCommand_800C9C88.arg_4 = res.arg_2;
                    if (sub_80013358(res.arg_2) == 1)
                    {
                        MarkSpeciesCaptured_800BF9F0(sub_800A2BE4(i - 4));
                        if (GetCapturedMinionsFromBitfield_8003BA58(sub_800A248C()) == 1)
                        {
                            curCommand_800C9C88.kind_0 = 0x1A;
                        }
                        SetBattleFlag_800BC838(0x40);
                        if (r == 2)
                        {
                            
                            dword_800B1238[i - 4].killer_6 = actingUnit_800C9C7C;
                            dword_800B1238[i - 4].kind_A = curCommand_800C9C88.kind_0;
                            dword_800B1238[i - 4].exp_0 = m->exp_4;
                            dword_800B1238[i - 4].level_8 = m->level_44;
                        }
                    }
                    break;
                }
                if (m->hp_8.cur_0 <= unitHpDamage_800C9D38[i] || (unitStatusInflicted_800C9CA0[i] & 0x600))
                {
                    unitHpDamage_800C9D38[i] = m->hp_8.cur_0;
                    unitReactions_800C9CC8[i].kind_0 = 0xB;
                    if (r == 2)
                    {
                        SetBattleFlag_800BC838(0x40);
                        if (sub_800BF9B4(sub_800A2BE4(i - 4)) == 1)
                        {
                            SetBattleFlag_800BC838(0x100000);
                        }
                        else
                        {
                            ClearBattleFlag_800BC850(0x100000);
                        }
                        if (sub_800A2AB4() == 2)
                        {
                            SetBattleFlag_800BC838(2);
                        }
                        
                        dword_800B1238[i - 4].species_4 = sub_800A2BE4(i - 4);
                        dword_800B1238[i - 4].killer_6 = actingUnit_800C9C7C;
                        dword_800B1238[i - 4].kind_A = curCommand_800C9C88.kind_0;
                        dword_800B1238[i - 4].exp_0 = m->exp_4;
                        dword_800B1238[i - 4].level_8 = m->level_44;
                        if (TestBattleFlag_800BC820(0x100000) == 1)
                        {
                            deathSfx_800C9D80 = 0x1C;
                        }
                        else
                        {
                            deathSfx_800C9D80 = 0x6F;
                        }
                    }
                    else if (r == 0)
                    {
                        SetBattleFlag_800BC838(4);
                        deathSfx_800C9D80 = 0x1C;
                    }
                    else
                    {
                        SetBattleFlag_800BC838(8);
                        deathSfx_800C9D80 = 0x6F;
                    }
                }
            }
            if (i == actingUnit_800C9C7C)
            {
                unitReactions_800C9CC8[i].kind_0 = 0x14;
            }
        }
    }
    if (curCommand_800C9C88.kind_0 == 7)
    {
        if (flag == 1)
        {
            curCommand_800C9C88.arg_4 = 0;
            if (GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 0)
            {
                SetBattleFlag_800BC838(0x80);
            }
        }
        else
        {
            curCommand_800C9C88.arg_4 = 1;
            if (GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 2)
            {
                curCommand_800C9C88.kind_0 = 0x14;
            }
        }
    }
}

void UpdateWindowsHidden_800BF2E8()
{
    int v;
    if ((GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 0 && ((v = curCommand_800C9C88.kind_0) == 5 || v == 0x1A || v == 2 || v == 3 || v == 7))
        || (GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 1 && ((v = curCommand_800C9C88.kind_0) - 2 < 2U || v == 8)))
    {
        SetBattleFlag_800BC838(0x8000);
        SetBattleFlag_800BC838(0x10000);
    }
    else
    {
        ClearBattleFlag_800BC850(0x8000);
        ClearBattleFlag_800BC850(0x10000);
    }
}

void FlashScreenWhite_800BF3AC()
{
    unsigned char buf[3];
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    StartScreenFlash_8001C02C(buf);
}

void StartHitNumber_800BF3DC(int unit, int kind, int amount, int pos, int f14)
{
    EventEntry* p = AllocEventEntry_80043AF8(hitNumberTasks_8008D778);
    if (p)
    {
        BatHitNum_a* q = p->buffer;
        p->flags = (p->flags | 1) & 0xFFFF7FFF;
        q->kind_0 = kind;
        q->frame_8 = 0;
        q->alpha_C = 0;
        q->amount_4 = amount;
        q->pos_10 = (unsigned short*)pos;
        q->f14 = f14;
        q->unit_18 = unit;
        p->cb_8 = (EventEntryFn)HitNumberTask_800BF4D0;
    }
}

int AnyHitNumberActive_800BF47C()
{
    EventNode* h = hitNumberTasks_8008D778;
    EventNode* n;
    int i = 0;
    int cnt = h->count;
    for (n = h; i < cnt; i++)
    {
        if ((n->entry.flags & 0x8001) == 1)
        {
            return 1;
        }
        n = n->next;
    }
    return 0;
}

void HitNumberTask_800BF4D0(EventEntry* t, BatHitNum_a* u)
{
    DVECTOR sxy;
    SVECTOR v;
    long p;
    long flag;
    int x;
    v.vx = u->pos_10[0];
    v.vy = u->pos_10[2];
    v.vz = u->pos_10[4];
    v.vx -= cameraEye_8008D600.vx;
    v.vy -= cameraEye_8008D600.vy;
    v.vz -= cameraEye_8008D600.vz;
    RotTransPers(&v, (long*)&sxy, &p, &flag);
    u->frame_8++;
    if (u->frame_8 > 0x10)
    {
        t->flags = (t->flags & ~1) | 0x8000;
        return;
    }
    if (u->frame_8 > 8)
    {
        u->alpha_C -= 4;
    }
    else
    {
        u->alpha_C += 4;
    }
    x = u->amount_4 / (0x11 - u->frame_8);
    x = -x;
    u->amount_4 += x;
    if (u->kind_0 == 0)
    {
        AdjustUnitStatById_800127D0(u->unit_18, 0, x, 0);
        if (GetUnitStatus_80014390((unsigned char)u->unit_18)->hp_8.cur_0 <= 0)
        {
            KillUnit_800127B8(GetUnitStatus_80014390((unsigned char)u->unit_18));
        }
    }
    if (u->kind_0 == 1)
    {
        AdjustUnitStatById_800127D0(u->unit_18, 2, x, 0);
    }
}

#if 0 // Not matched: cse keeps 500 in a register for case 2 (original reloads it), which reorders the init stores; tried if-chains, struct, returns, default
void InitTurnGauges_800BF648(short* p, int mode)
{
    p[0] = 500;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = -0x2BC;
    p[6] = -0x578;
    switch (mode)
    {
    case 1:
        p[0] = 1000;
        return;
    case 0:
        return;
    case 2:
        p[0] = 0;
        p[4] = 1000;
        p[5] = 500;
        p[6] = 0x14D;
        return;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, InitTurnGauges_800BF648);

#if 0 // Not matched: body matches with a goto inner loop (a for loop gets strength-reduced); prologue saves are not interleaved and a/b take s3/s2 in the original (s2/s3 here)
int AdvanceTurnGauges_800BF6BC(unsigned short* gauges, int summoned)
{
    int next;
    unsigned int i;
    next = -1;
    do
    {
        i = 0;
    loop:
        if (i >= 4 || summoned == i)
        {
            gauges[i] += GetUnitTurnSpeed_800BF784(i);
            if ((short)gauges[i] >= 1000)
            {
                gauges[i] = 0;
                next = i;
                continue;
            }
        }
        i++;
        if (i < 7)
        {
            goto loop;
        }
    } while (next < 0);
    return next;
}
#endif

INCLUDE_OVERLAY_ASM(battle, AdvanceTurnGauges_800BF6BC);

void ResetTurnGauge_800BF770(short* p, int i)
{
    p[i] = 0x320;
}

int GetUnitTurnSpeed_800BF784(int unit)
{
    unsigned char stats[0x18];
    UnitStatus* p = GetUnitStatus_80014390(unit & 0xFF);
    if (p == 0)
    {
        return 0;
    }
    CalcEquippedStats_80033624(stats, p);
    return stats[4] + 10;
}

#if 0 // Not matched: body close with a goto loop; prologue saves are not interleaved with the arg copies in the original and b/f/table-base get different saved registers
typedef struct BatChance_a
{
    unsigned int mask;
    unsigned int chance;
} BatChance_a;
extern BatChance_a statusCureChances_800C9138[];
extern int GetEquipmentId_8003356C(UnitStatus* p, unsigned int idx);
extern unsigned int Rand100_80013E30();
void TickUnitStatus_800BF7C4(UnitStatus* p, short* hpChange, short* mpChange)
{
    unsigned int f = p->status_0;
    unsigned int f0 = f;
    int i;
    BatChance_a* e;
    *hpChange = 0;
    *mpChange = 0;
    f = AdvancePetrification_800BFA34(f);
    if ((GetEquipmentId_8003356C(p, 2) & 0xFF) == 0x10)
    {
        f |= 0x4000;
    }
    if (f0 & 1)
    {
        *hpChange = p->hp_8.max_2 / 10;
        f &= ~2;
    }
    else if (f & 0x4000)
    {
        *hpChange = -(short)(p->hp_8.max_2 / 20);
    }
    if (f0 & 0x8000)
    {
        *mpChange = -((p->level_44 >> 2) + 3);
        f &= ~0x8000;
    }
    if (f & 0x200)
    {
        *hpChange = p->hp_8.cur_0;
    }
    i = 0;
loop:
    e = &statusCureChances_800C9138[i];
    if (f0 & e->mask)
    {
        if (Rand100_80013E30() >= e->chance)
        {
            f &= ~e->mask;
        }
    }
    i++;
    if (i < 1)
    {
        goto loop;
    }
    p->status_0 = f;
}
#endif

INCLUDE_OVERLAY_ASM(battle, TickUnitStatus_800BF7C4);

int IsUncapturableSpecies_800BF980(int species)
{
    int r = 0;
    if (species >= 0x29)
    {
        if (species < 0x39)
        {
            r = 1;
        }
        else if (species < 0xD3)
        {
            if (species > 0xC8)
            {
                r = 1;
            }
        }
    }
    return r;
}

int sub_800BF9B4(int species)
{
    int r = 0;
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
        r = 1;
        break;
    }
    return r;
}

INCLUDE_OVERLAY_ASM(battle, dword_800B67F0);

#if 0 // Not matched: x is copied to v1 and the mask is built before the load in the original; regalloc/schedule differ in every variant tried
void MarkSpeciesCaptured_800BF9F0(int species)
{
    unsigned int x = species;
    unsigned int* p = allMinionsBitfields_8008BD84;
    if (x < 0xE0)
    {
        unsigned int* q = &p[x >> 5];
        int m = 1 << (x & 0x1F);
        *q = m | *q;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, MarkSpeciesCaptured_800BF9F0);

int AdvancePetrification_800BFA34(int x)
{
    int y = x & 0x3F8;
    return (x & ~0x3F8) | (y << 1);
}

#if 0 // Not matched: only the last test: andi goes to v1 instead of v0 (and branch sense/layout); tried ternary, if/else, r variable, int params
int GetStatusCommand_800BFA4C(unsigned int status, unsigned int prevStatus)
{
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
    if (!(status & 0x4000))
    {
        return 0x14;
    }
    return 0x19;
}
#endif

INCLUDE_OVERLAY_ASM(battle, GetStatusCommand_800BFA4C);

void SetHitVariantForCommand_800BFAF8(int x)
{
    int a;
    switch (x)
    {
    case 9:
        a = 1;
        break;
    case 7:
        a = 8;
        break;
    case 11:
        a = 4;
        break;
    case 14:
        a = 0;
        break;
    case 18:
        a = 2;
        break;
    case 2:
        a = 3;
        break;
    case 13:
        a = 5;
        break;
    case 21:
        a = 7;
        break;
    case 22:
    default:
        return;
    }
    SetHitVariant_80018430(a);
}

void StartBattleWindows_800BFB80()
{
    ResetWindowHighlights_800BFC10();
    StartEnemyWindows_800BFC40();
    StartActorWindow_800C01D8();
    StartHelpWindow_800C0440();
}

void StopBattleWindows_800BFBB8()
{
    StopAllEventEntries_80043B40(dword_8008B568);
    StopAllEventEntries_80043B40(dword_8008B564);
    StopAllEventEntries_80043B40(dword_8008D4B0);
    StopAllEventEntries_80043B40(dword_8008D63C);
}

void ResetWindowHighlights_800BFC10()
{
    actorWindowHighlight_800C9DFD = 0;
    enemyWindowsHighlight_800C9DFC = 0;
    actorHighlightTime_800C9170 = 0;
    enemyHighlightTimes_800C9174[0] = 0;
    enemyHighlightTimes_800C9174[1] = 0;
    enemyHighlightTimes_800C9174[2] = 0;
}

void StartEnemyWindows_800BFC40()
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008B568);
    int m;
    int n;
    int i;
    int b;
    if (e)
    {
        m = sub_800A248C();
        n = GetCapturedMinionsFromBitfield_8003BA58(m);
        if (sub_800A2AB4())
        {
            m = 0x10;
        }
        enemyWindowFlags_800C9DF8 = 0;
        enemyWindowMask_800C9E24 = 0;
        e->cb_8 = (EventEntryFn)EnemyWindowsLayoutTask_800BFDEC;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        for (i = 0; i < 3; i++)
        {
            b = m & (1 << (i + 4));
            if (b != 0)
            {
                e = AllocEventEntry_80043AF8(dword_8008B564);
                if (e)
                {
                    BatXY_a* pp = (BatXY_a*)((char*)enemyWindowLayouts_800C9140 + ((n - 1) * 12 + i * 4));
                    BatUnitWin_a* q;
                    e->flags = (e->flags | 1) & 0xFFFF7FFF;
                    q = e->buffer;
                    q->slot_0 = i;
                    q->frame_4 = 0;
                    q->from_8[0] = pp->x;
                    q->from_8[1] = pp->y;
                    q->from_8[2] = 0x64;
                    q->from_8[3] = 0x29;
                    e->cb_8 = (EventEntryFn)EnemyWindowTask_800C0074;
                    enemyWindows_800C9E28[i] = q;
                    enemyWindowPos_800C9E18[i].x = pp->x;
                    enemyWindowPos_800C9E18[i].x = pp->x;
                    enemyWindowPos_800C9E18[i].y = pp->y;
                    enemyWindowTasks_800C9E08[i] = e;
                }
            }
        }
    }
}

void EnemyWindowsLayoutTask_800BFDEC()
{
    int m;
    int n;
    int diff;
    int i;
    int k;
    int one;
    int bit;
    BatXY_a* pp;
    m = sub_800A248C();
    if (m != 0 && sub_800A2AB4() != 0)
    {
        m = 0x10;
    }
    n = GetCapturedMinionsFromBitfield_8003BA58(m);
    if (enemyWindowMask_800C9E24 != m)
    {
        diff = (enemyWindowMask_800C9E24 | m) ^ m;
        enemyWindowMask_800C9E24 = m;
        one = 1;
        enemyWindowFlags_800C9DF8 |= one;
        enemyWindowSlide_800C9E00 = 0;
        for (i = 0; i < 3; i++)
        {
            if (diff & (one << (i + 4)))
            {
                if (sub_800A2AB4() != 2)
                {
                    enemyWindowTasks_800C9E08[i]->flags &= ~1;
                    enemyWindowTasks_800C9E08[i]->flags |= 0x8000;
                }
                else
                {
                    SetBattleFlag_800BC838(0x10000);
                }
            }
            if (m & (one << (i + 4)))
            {
                enemyWindowPos_800C9E18[i].x = enemyWindows_800C9E28[i]->from_8[0];
                enemyWindowPos_800C9E18[i].y = enemyWindows_800C9E28[i]->from_8[1];
            }
        }
    }
    if (enemyWindowFlags_800C9DF8 & 1)
    {
        if (enemyWindowSlide_800C9E00 < 4)
        {
            enemyWindowSlide_800C9E00++;
            k = 0;
            for (i = 0, bit = 1; i < 3; i++)
            {
                if (m & (bit << (i + 4)))
                {
                    pp = (BatXY_a*)((char*)enemyWindowLayouts_800C9140 + ((n - 1) * 12 + k * 4));
                    enemyWindows_800C9E28[i]->from_8[0] += (pp->x - enemyWindows_800C9E28[i]->from_8[0]) * enemyWindowSlide_800C9E00 >> 2;
                    enemyWindows_800C9E28[i]->from_8[1] += (pp->y - enemyWindows_800C9E28[i]->from_8[1]) * enemyWindowSlide_800C9E00 >> 2;
                    k++;
                }
            }
        }
        else
        {
            enemyWindowFlags_800C9DF8 &= ~1;
        }
    }
}

// Matched
extern void DrawUnitStatusWindow_8002F1C8();
void EnemyWindowTask_800C0074(EventEntry* t, void* arg)
{
    int k;
    UnitStatus* m;
    int r;
    BatUnitWin_a* u;
    if (dword_800B1228 & 0x10000)
    {
        return;
    }
    u = arg;
    r = sub_800A2AB4();
    if (r == 1)
        k = 0;
    else if (sub_800A2AB4() == 2)
        k = 1;
    else
        k = u->slot_0;
    m = GetUnitStatus_80014390((k + 4) & 0xFF);
    AddClipDrawAreaPrim_80033308(pOT_8008D454 + 10);
    SetFontClutOffset_8003F900(1, 0);
    InterpolateWindowRect_8004196C(u->rect_10, u->from_8, u->frame_4, 4, 9);
    if (IsUncapturableSpecies_800BF980(sub_800A2BE4(k)))
    {
        DrawUnitStatusWindow_8002F1C8(m, enemyGaugePreview_800C9164[k], enemyWindowsHighlight_800C9DFC, enemyHighlightTimes_800C9174[k], u->rect_10, 10, 1);
    }
    else
    {
        DrawUnitStatusWindow_8002F1C8(m, enemyGaugePreview_800C9164[k], enemyWindowsHighlight_800C9DFC, enemyHighlightTimes_800C9174[k], u->rect_10, 10, 0);
    }
    u->frame_4++;
    AddDrawAreaPrim_8003326C(u->rect_10, pOT_8008D454 + 10);
}

void StartActorWindow_800C01D8()
{
    EventEntry* r = AllocEventEntry_80043AF8(dword_8008D4B0);
    if (r != 0)
    {
        BatWin_b* p = r->buffer;
        r->flags = (r->flags | 1) & ~0x8000;
        p->frame_0 = 0;
        p->from_4[0] = 0x6E;
        p->from_4[1] = 0xAC;
        p->from_4[2] = 0x64;
        p->from_4[3] = 0x29;
        r->cb_8 = (EventEntryFn)ActorWindowTask_800C0254;
    }
}

typedef struct BatBox_b
{
    short col_0;
    char c_2;
    char c_3;
} BatBox_b;
extern void DrawMpGauge_8002F120(int a0, short* pos, int a2, int a3);
extern void DrawStatusIcons_8002F480(int a0, void* pos, int ot, int reverse);
extern void DrawWindow_80042460(void* rect, BatBox_b* box, void* ot, int a3);
extern unsigned short uiColor_8008B590;

// Matched
void ActorWindowTask_800C0254(EventEntry* t, void* arg)
{
    BatWin_b* u;
    short pos[4];
    BatBox_b box;
    short rect[4];
    UnitStatus* m;
    if (dword_800ADE78.f0 == 1 && actingUnit_800C9C7C == 10)
    {
        return;
    }
    if (dword_800B1228 & 0x8000)
    {
        return;
    }
    u = arg;
    m = GetUnitStatus_80014390(shownUnit_800C9C99);
    AddClipDrawAreaPrim_80033308(pOT_8008D454 + 10);
    InterpolateWindowRect_8004196C(u->rect_C, u->from_4, u->frame_0, 4, 9);
    if (shownUnit_800C9C99 == 0)
    {
        DrawUnitStatusWindow_8002F1C8(m, previewHpChange_800C9180, actorWindowHighlight_800C9DFD, actorHighlightTime_800C9170, u->rect_C, 10, 2);
    }
    else
    {
        DrawUnitStatusWindow_8002F1C8(m, previewHpChange_800C9180, actorWindowHighlight_800C9DFD, actorHighlightTime_800C9170, u->rect_C, 10, 0);
    }
    if (shownUnit_800C9C99 != 0)
    {
        pos[0] = 0xD2;
        pos[1] = 0xC0;
        DrawMpGauge_8002F120(m, pos, previewMpChange_800C9182, 0xF);
        box.c_3 = 1;
        rect[2] = 0x64;
        rect[3] = 0x15;
        box.col_0 = uiColor_8008B590;
        box.c_2 = 0;
        rect[0] = 0xD2;
        rect[1] = 0xC0;
        DrawWindow_80042460(rect, &box, pOT_8008D454 + 15, 0);
    }
    u->frame_0++;
    if (u->frame_0 >= 5)
    {
        u->frame_0 = 4;
    }
    DrawStatusIcons_8002F480(m, 0, 0xF, 0);
    AddDrawAreaPrim_8003326C(u->rect_C, pOT_8008D454 + 10);
}

void StartHelpWindow_800C0440()
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D63C);
    if (e)
    {
        helpWindowText_800C9D74 = 0;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        ((BatWin_b*)e->buffer)->frame_0 = 0;
        e->cb_8 = (EventEntryFn)HelpWindowTask_800C04A4;
    }
}

#if 0 // Not matched: u and w swap saved registers (s1/s0); tried w types, decl order, pre-increment
extern unsigned char sealOutcomeTable_800793C8[];
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);
extern void DrawNumberRightAlignedFont1_8003F264(void* pos, int val, int ot);
extern void DrawUiColorWindow_800424C0();
void HelpWindowTask_800C04A4(EventEntry* t, BatWin_b* u)
{
    int w;
    short pos[2];
    unsigned char* g;
    if (padPressed_8009194C & 0x100)
    {
        saveData_8008B570.field_0 ^= 0x10;
    }
    if (saveData_8008B570.field_0 & 0x10)
    {
        return;
    }
    if (helpWindowText_800C9D74 == 0)
    {
        return;
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    w = MeasureTextWidth_8003E4C8(helpWindowText_800C9D74);
    g = sealOutcomeTable_800793C8 + 0x14;
    if (*(int*)(g + 0x24) == helpWindowText_800C9D74)
    {
        w += 0x10;
    }
    u->from_4[2] = w + 4;
    u->from_4[3] = 0x14;
    u->from_4[0] = 0xA;
    u->from_4[1] = 0x88;
    pos[0] = u->from_4[0] + 2;
    pos[1] = u->from_4[1] + 3;
    DrawText_8003E91C(2, (void*)helpWindowText_800C9D74, pos, 0);
    if (*(int*)(g + 0x24) == helpWindowText_800C9D74)
    {
        pos[0] += w;
        pos[1] += 3;
        DrawNumberRightAlignedFont1_8003F264(pos, sub_800AD8E4(), 0);
    }
    InterpolateWindowRect_8004196C(u->rect_C, u->from_4, u->frame_0, 4, 7);
    DrawUiColorWindow_800424C0(u->rect_C, 0, pOT_8008D454, 0);
    if (++u->frame_0 >= 5)
    {
        u->frame_0 = 4;
    }
    AddDrawAreaPrim_8003326C(u->rect_C, pOT_8008D454);
}
#endif

INCLUDE_OVERLAY_ASM(battle, HelpWindowTask_800C04A4);

void BuildMinionModelReq_800C064C(Minion* m, BatModelReq_a* req, int f30)
{
    unsigned char ids[8];
    int counts[3];
    int self;
    int t;
    self = GetSpeciesModelDesc_80019C70(m->species_2)->modelId_0;
    req->count_0 = GetTopSpecies_800338DC(m->species_4C, ids, counts);
    req->ids_4[0] = GetSpeciesModelDesc_80019C70(ids[0])->modelId_0;
    req->ids_4[1] = GetSpeciesModelDesc_80019C70(ids[1])->modelId_0;
    req->ids_4[2] = GetSpeciesModelDesc_80019C70(ids[2])->modelId_0;
    req->nums_10[0] = counts[0];
    req->nums_10[1] = counts[1];
    req->nums_10[2] = counts[2];
    if (req->ids_4[0] == req->ids_4[1])
    {
        if (req->ids_4[1] == req->ids_4[2])
        {
            req->nums_10[0] += req->nums_10[1];
            req->nums_10[0] += req->nums_10[2];
            req->nums_10[1] = 0;
            req->nums_10[2] = 0;
            req->count_0 = 1;
        }
        else
        {
            req->nums_10[0] += req->nums_10[1];
            req->ids_4[1] = req->ids_4[2];
            req->nums_10[1] = req->nums_10[2];
            req->count_0 = 2;
            req->nums_10[2] = 0;
        }
    }
    else if (req->ids_4[0] == req->ids_4[2])
    {
        req->nums_10[0] += req->nums_10[2];
        req->nums_10[2] = 0;
        req->count_0 = 2;
    }
    else if (req->ids_4[1] == req->ids_4[2])
    {
        req->nums_10[1] += req->nums_10[2];
        req->nums_10[2] = 0;
        req->count_0 = 2;
    }
    req->f2C = 0;
    if (req->ids_4[0] != self)
    {
        if (req->ids_4[1] == self)
        {
            req->ids_4[1] = req->ids_4[0];
            req->ids_4[0] = self;
            t = req->nums_10[1];
            req->nums_10[1] = req->nums_10[0];
            req->nums_10[0] = t;
        }
        else if (req->ids_4[2] == self)
        {
            req->ids_4[2] = req->ids_4[0];
            req->ids_4[0] = self;
            t = req->nums_10[2];
            req->nums_10[2] = req->nums_10[0];
            req->nums_10[0] = t;
        }
        else if (req->count_0 < 2)
        {
            req->ids_4[1] = req->ids_4[0];
            req->ids_4[0] = self;
            req->nums_10[1] = req->nums_10[0];
            req->nums_10[0] = 0;
            req->count_0 = 2;
        }
        else
        {
            req->ids_4[2] = req->ids_4[0];
            req->ids_4[0] = self;
            req->nums_10[2] = req->nums_10[0];
            req->nums_10[0] = 0;
            req->count_0 = 3;
        }
    }
    req->f1C = GetRankForLevel_80019A80(m->status_84.level_44);
    req->f20 = req->count_0 - 1;
    req->f28 = GetSpeciesModelDesc_80019C70(m->field_3)->modelId_0;
    req->f30 = f30;
    req->angle_24 = GetElementModelAngle_800C0904(m->status_84.element_3E);
    if (req->angle_24 == -1000)
    {
        req->angle_24 = GetSpeciesModelDesc_80019C70(m->field_3)->field_2 * 2;
    }
    else
    {
        req->angle_24 -= GetSpeciesModelDesc_80019C70(m->field_3)->field_3 * 2;
        if (req->angle_24 < 0)
        {
            req->angle_24 += 360;
        }
    }
}

int GetElementModelAngle_800C0904(unsigned char* p)
{
    int n = 0;
    int i;
    int r;
    for (i = 0; i < 4; i++)
    {
        if (p[i])
        {
            n++;
        }
    }
    if (n == 1)
    {
        r = -1000;
    }
    else if (n == 2)
    {
        if (p[3] && p[1])
        {
            if (p[1] < p[3])
            {
                r = 0xF5;
            }
            else
            {
                r = 0x41;
            }
        }
        else if (p[0] && p[2])
        {
            if (p[2] < p[0])
            {
                r = 0x14F;
            }
            else
            {
                r = 0x9B;
            }
        }
        else
        {
            r = CalcElementAngle_800C09D4(p);
        }
    }
    else
    {
        r = CalcElementAngle_800C09D4(p);
    }
    return r;
}

// Matched
extern short sinTable_80084540[];
int CalcElementAngle_800C09D4(unsigned char* p)
{
    int t2, t1, t4, t3, t5, t6, t7, t8;
    t1 = sinTable_80084540[0x2E3] * p[0];
    t2 = sinTable_80084540[0xEE3] * p[0];
    t3 = sinTable_80084540[0xEE3] * p[3];
    t4 = sinTable_80084540[0xAE3] * p[3];
    t5 = sinTable_80084540[0xAE3] * p[2];
    t6 = sinTable_80084540[0x6E3] * p[2];
    t7 = sinTable_80084540[0x6E3] * p[1];
    t8 = sinTable_80084540[0x2E3] * p[1];
    return ratan2Degrees_8003B56C(t1 + t3 + t5 + t7, t2 + t4 + t6 + t8);
}

void sub_800C0A94()
{
}

int GetPartyMinionMask_800C0A9C()
{
    int n = CountMinions_80010548(3);
    int r = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        r |= 1 << (i + 1);
    }
    return r;
}

int LoadSummonedMinion_800C0AEC(int slot, int* pos, int rotY)
{
    BatModelReq_a buf;
    Minion* minion;
    if (GetSummonedMinionSlot_800C0D50() != -1)
    {
        return 0;
    }
    minion = GetMinion_80010598(3, slot);
    if (minion == 0)
    {
        return 0;
    }
    summonedMinion_800C9188 = minion;
    BuildMinionModelReq_800C064C(minion, &buf, dword_8007DC74);
    StartModelTask_80010850(&buf);
    summonedActor_800C9190.x_4 = pos[0];
    summonedActor_800C9190.y_8 = pos[1];
    summonedActor_800C9190.z_C = pos[2];
    summonedMinionSlot_800C918C = slot;
    summonedActor_800C9190.rotY_10 = rotY;
    return 1;
}

int FreeSummonedMinion_800C0BA0()
{
    if (GetSummonedMinionSlot_800C0D50() >= 0)
    {
        FreeModelTask_8001098C(0);
        DestroyActor_8001D600(summonedActor_800C9190.actor_0);
        summonedMinionSlot_800C918C = -1;
        return 1;
    }
    return 0;
}

int CreateSummonedMinionActor_800C0BF0()
{
    ActorDesc s;
    Model* m;
    int k;
    int x;
    // RunModelTask_80010A10 is declared void in funcs.h, but its result is used here
    if (((int (*)(int))RunModelTask_80010A10)(0) != 0)
    {
    m = GetModelTaskModel_80010A44(0);
    k = GetRankForLevel_80019A80(summonedMinion_800C9188->status_84.level_44);
    s.modelId_0 = -1;
    s.kind_4 = 2;
    s.pos_8[0] = summonedActor_800C9190.x_4;
    s.pos_8[1] = summonedActor_800C9190.y_8;
    s.pos_8[2] = summonedActor_800C9190.z_C;
    s.rot_14[0] = 0;
    s.rot_14[1] = summonedActor_800C9190.rotY_10;
    s.rot_14[2] = 0;
    s.clutRow_1C = 3;
    s.animIdx_20 = 4;
    s.frame_24 = -1;
    s.frameSpeed_28 = 0x1000;
    s.blendDiv_2C = 4;
    s.visible_30 = 0;
    s.model_48 = m;
    s.bones_34 = defaultBones_80079140;
    s.baseScale_38 = GetModelBaseScale_80024E90(m, k);
    s.boneScale_3C = GetModelBoneScale_80024EC8(m, k);
    s.anims_40 = GetModelActorAnims_80024E38(m);
    s.effectTbl_44 = GetModelEffectTable_80024E64(m);
    s.hasMatrices_4C = 1;
    summonedActor_800C9190.actor_0 = CreateActor_8001D45C(&s);
    SetActorGroundMove_8001D68C(summonedActor_800C9190.actor_0, 0);
    x = sub_80024F00(m, k);
    SetBoneGroupFlags_80019B14(summonedActor_800C9190.actor_0->bones_134, x, sub_80024F38(m, k));
        return 1;
    }
    return 0;
}

int GetSummonedMinionSlot_800C0D50()
{
    return summonedMinionSlot_800C918C;
}

int IsSummonedMinionIdle_800C0D60()
{
    return sub_8001E1C8((void*)summonedActor_800C9190.actor_0);
}

int IsSummonedMinionReady_800C0D88()
{
    return sub_8001E1DC(summonedActor_800C9190.actor_0);
}

void TurnSummonedMinionToward_800C0DB0(int pos)
{
    SetActorTurnTarget_8001DB00(summonedActor_800C9190.actor_0, pos, 0x55);
}

// Matched
BatCol_a* StartMinionAction_800C0DDC(BatCol_a* out, BatCmd_a* cmd, int isReaction)
{
    BatCol_a buf;
    int mask;
    memset(&buf, 0, 4);
    if (cmd->kind_0 == 0x14)
    {
        *out = buf;
        return out;
    }
    if (cmd->mask_8 & (mask = 1 << (summonedMinionSlot_800C918C + 1)))
    {
        StartCommandAction_80018A4C(&buf, summonedActor_800C9190.actor_0, cmd, 0, isReaction);
    }
    *out = buf;
    return out;
}

int TriggerMinionAction_800C0E84(BatCmd_a* cmd)
{
    int mask;
    if (cmd->kind_0 == 0x14)
    {
        return 0;
    }
    mask = 1 << (summonedMinionSlot_800C918C + 1);
    if (cmd->mask_8 & mask)
    {
        TriggerActorEffect_8001E28C(summonedActor_800C9190.actor_0);
    }
    return 1;
}

void GetMinionHitFrame_800C0EE8(int a)
{
    GetActorHitFrame_80018E5C(summonedActor_800C9190.actor_0, a);
}

int sub_800C0F14()
{
    return 0;
}

void UpdateMinionStatusTint_800C0F1C()
{
    SetActorStatusTint_80018EBC(summonedActor_800C9190.actor_0, GetPartyMinionStatus_800C0F78(summonedMinionSlot_800C918C));
}

void GetPartyMinionName_800C0F54(int slot)
{
    GetMinionName_800106F8(3, slot);
}

UnitStatus* GetPartyMinionStatus_800C0F78(int slot)
{
    GetMinionStatus_800107A0(3, slot); // sic: no return, the result is left in $v0
}

int* GetSummonedMinionPos_800C0F9C()
{
    return summonedActor_800C9190.actor_0->pos_38;
}

int* GetSummonedMinionBonePos_800C0FAC()
{
    return summonedActor_800C9190.actor_0->bonePos_1C4;
}

void GetSummonedMinionEffectTarget_800C0FC4(EffectTarget* p)
{
    Actor* q = summonedActor_800C9190.actor_0;
    p->tbl_0 = q->effectTbl_14C;
    p->pos_4 = q->pos_38;
    p->bonePos_8 = q->bonePos_1C4;
    p->boneMatrices_C = q->boneMatrices_1C8;
    p->boneScale_2C = q->boneScale_144;
    p->scale_30 = q->scale_2C;
}

UnitSkills* GetPartyMinionSkills_800C100C(int slot)
{
    Minion* minion = GetMinion_80010598(3, slot);
    if (minion)
    {
        return &minion->skills_DE;
    }
    return 0;
}

unsigned int* GetPartyMinionMagicBits_800C103C(int slot)
{
    Minion* minion = GetMinion_80010598(3, slot);
    if (minion)
    {
        return &minion->magicBits_F4;
    }
    return 0;
}

void SeqStopTask_800C106C(unsigned int* flags, BatSeqStop_a* u)
{
    if (--u->timer_4 < 0)
    {
        *flags = (*flags & ~1) | 0x8000;
        StopSeqSlot_80031334(u->slot_0);
    }
}

void PlayTimedSeq_800C10B8(int frames, int slot)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (frames > 0 && e)
    {
        BatSeqStop_a* q;
        PlaySeqSlot_80031160(slot, 1);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q->slot_0 = slot;
        q->timer_4 = frames;
        e->cb_8 = (EventEntryFn)SeqStopTask_800C106C;
    }
}

void SfxStopTask_800C1140(unsigned int* flags, BatSfxStop_a* u)
{
    if (--u->timer_4 < 0)
    {
        *flags = (*flags & ~1) | 0x8000;
        SfxKeyOff_80031574(u->voice_8, u->sfx_0.id16);
    }
}

void PlayTimedSfx_800C1190(int frames, int sfx)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (frames > 0 && e)
    {
        BatSfxStop_a* q;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q->timer_4 = frames;
        q->voice_8 = SfxKeyOn_800314F4(sfx);
        q->sfx_0.id = sfx;
        e->cb_8 = (EventEntryFn)SfxStopTask_800C1140;
    }
}

typedef struct BatDrop_a
{
    int f0;
    int f4;
    short size_8;
    short padA;
    int padC;
    int pos_10[3];
    char pad1C[0xC];
    int vel_28[3];
    short rot_34[4];
    int pad3C;
    EffectSprite* anim_40;
} BatDrop_a;

// Matched
void DropSpriteTask_800C1220(EventEntry* t, BatDrop_a* u)
{
    int v[3];
    short s[4];
    short w[4];
    EffectSprite* d;
    EffectSpriteFrame* e;
    u->vel_28[0] = u->vel_28[0] * 15 / 16;
    u->vel_28[1] = u->vel_28[1] * 15 / 16 + u->size_8 / 8;
    u->vel_28[2] = u->vel_28[2] * 15 / 16;
    u->pos_10[0] += u->vel_28[0];
    u->pos_10[1] += u->vel_28[1];
    u->pos_10[2] += u->vel_28[2];
    d = u->anim_40;
    e = d->frames_8[0];
    v[0] = u->pos_10[0];
    v[1] = u->pos_10[1];
    v[2] = u->pos_10[2];
    v[0] /= 1024;
    v[1] /= 1024;
    v[2] /= 1024;
    if (levantPos_8008BD18.pos.y < v[1] || u->size_8 < 0x800)
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
    u->size_8 -= 0x40;
    s[0] = e->size_C[0] * u->size_8 / 4096;
    s[1] = e->size_C[1] * u->size_8 / 4096;
    w[0] = 0x14;
    w[1] = 0;
    w[2] = 0;
    u->rot_34[1] += 0x80;
    DrawRotSprite_80044010(&d->poly_C, v, u->rot_34, &e->u_0, &e->w_4, &e->f8, s, w, e->rgb_18, 0, 0x30, pOT_8008D690);
}

// Matched
void DropTrailTask_800C1450(EventEntry* t, BatDropSrc_a* u)
{
    int v[3];
    EffectSpriteFrame* f;
    int i;
    EventEntry* e;
    BatDrop_a* q;
    EffectSprite* s = u->path_88;
    if (u->time_4 / 4096 < s->count_0)
    {
        f = s->frames_8[u->time_4 / 4096];
        v[0] = f->pos_10[0] + u->pos_44[0];
        v[1] = f->pos_10[1] + u->pos_44[1];
        v[2] = f->pos_10[2] + u->pos_44[2];
        if (((u->time_4 / 4096) & 3) == 0)
        {
            u->count_0++;
            for (i = 0; i < 3; i++)
            {
                e = AllocEventEntry_80043AF8(dword_8008D60C);
                if (e)
                {
                    e->flags = (e->flags | 1) & 0xFFFF7FFF;
                    q = e->buffer;
                    q->pos_10[0] = v[0];
                    q->pos_10[1] = v[1];
                    q->pos_10[2] = v[2];
                    q->pos_10[0] <<= 10;
                    q->pos_10[1] <<= 10;
                    q->pos_10[2] <<= 10;
                    if (u->count_0 & 1)
                    {
                        q->anim_40 = u->animA_8C;
                    }
                    else
                    {
                        q->anim_40 = u->animB_90;
                    }
                    q->vel_28[0] = 0;
                    q->vel_28[1] = 0;
                    q->vel_28[2] = 0;
                    q->rot_34[0] = 0;
                    q->rot_34[1] = i * 0x555;
                    q->rot_34[2] = 0;
                    q->f0 = 0;
                    q->size_8 = (rand() & 0xFFF) + 0x800;
                    e->cb_8 = (EventEntryFn)DropSpriteTask_800C1220;
                }
            }
        }
        u->time_4 += u->step_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

void SpawnHomingSparks_800C1654(int* pos, short* rot, int sprite, int speed, int target, int offset)
{
    int i;
    for (i = 0; i < 30; i++)
    {
        EventEntry* ev = AllocEventEntry_80043AF8(dword_8008D60C);
        if (ev)
        {
            BatSpark_a* b = ev->buffer;
            ev->flags = (ev->flags | 1) & 0xFFFF7FFF;
            b->base_1C[0] = pos[0];
            b->base_1C[1] = pos[1];
            b->base_1C[2] = pos[2];
            b->pos_10[0] = pos[0];
            b->pos_10[1] = pos[1];
            b->pos_10[2] = pos[2];
            b->rot_34[0] = rot[0];
            b->rot_34[1] = rot[1];
            b->rot_34[2] = rot[2];
            b->anim_3C = (EffectSprite*)sprite;
            b->vel_28[0] = ((rand() & 0x7F) - 0x3F) << 10;
            b->vel_28[1] = -(rand() & 0x3F) << 10;
            b->vel_28[2] = ((rand() & 0x7F) - 0x3F) << 10;
            b->rot_34[0] = 0;
            b->rot_34[1] = 0;
            b->rot_34[2] = 0;
            b->frame_0 = 0;
            b->speed_8 = ((rand() & 0xFFF) >> 1) + 0x800;
            b->target_40 = (int*)target;
            b->offset_44 = (int*)offset;
            ev->cb_8 = (EventEntryFn)HomingSparkTask_800C17EC;
        }
    }
}

void HomingSparkTask_800C17EC(EventEntry* t, BatSpark_a* u)
{
    int s[3];
    EffectSprite* d;
    int i;
    EffectSpriteFrame* e;
    int* a = u->target_40;
    int* b = u->offset_44;
    u->vel_28[0] = u->vel_28[0] * 31 / 32 + ((a[0] + b[0] - u->pos_10[0]) << 5);
    u->vel_28[1] = u->vel_28[1] * 31 / 32 + ((a[1] + b[1] - u->pos_10[1]) << 5);
    u->vel_28[2] = u->vel_28[2] * 31 / 32 + ((a[2] + b[2] - u->pos_10[2]) << 5);
    s[0] = u->vel_28[0] / 1024;
    s[1] = u->vel_28[1] / 1024;
    s[2] = u->vel_28[2] / 1024;
    u->pos_10[0] += s[0];
    u->pos_10[1] += s[1];
    u->pos_10[2] += s[2];
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d->count_0)
    {
        for (i = 0; i < d->frameCounts_4[u->frame_0 / 4096]; i++)
        {
            e = d->frames_8[u->frame_0 / 4096] + i;
            DrawRotSprite_80044010(&d->poly_C, u->pos_10, u->rot_34, &e->u_0, &e->w_4, &e->f8, e->size_C, (int*)&zeroSvector_800795D4, e->rgb_18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

void SpawnSpriteAnim_800C1A5C(int* pos, short* rot, int sprite, int speed)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (e)
    {
        BatSpark_a* b;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b = e->buffer;
        b->pos_10[0] = pos[0];
        b->pos_10[1] = pos[1];
        b->pos_10[2] = pos[2];
        b->rot_34[0] = rot[0];
        b->rot_34[1] = rot[1];
        b->rot_34[2] = rot[2];
        b->anim_3C = (EffectSprite*)sprite;
        b->frame_0 = 0;
        b->speed_8 = speed;
        e->cb_8 = (EventEntryFn)SpriteAnimTask_800C1B2C;
    }
}

#if 0 // Not matched: register permutation only (u/d/offset get s2/s0/s1, original s0/s1/s2); tried decl order and an explicit offset counter
void SpriteAnimTask_800C1B2C(EventEntry* t, BatSpark_a* u)
{
    EffectSprite* d = u->anim_3C;
    int i;
    EffectSpriteFrame* e;
    if (u->frame_0 / 4096 < d->count_0)
    {
        for (i = 0; i < d->frameCounts_4[u->frame_0 / 4096]; i++)
        {
            e = d->frames_8[u->frame_0 / 4096] + i;
            DrawRotSprite_80044010(&d->poly_C, u->pos_10, u->rot_34, &e->u_0, &e->w_4, &e->f8, e->size_C, e->pos_10, e->rgb_18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, SpriteAnimTask_800C1B2C);

void SpawnBounceSparks_800C1C5C(int* pos, short* rot, int sprite)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            BatSpark_a* b = e->buffer;
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            b->pos_10[0] = pos[0];
            b->pos_10[1] = pos[1];
            b->pos_10[2] = pos[2];
            b->rot_34[0] = rot[0];
            b->rot_34[1] = rot[1];
            b->rot_34[2] = rot[2];
            b->anim_3C = (EffectSprite*)sprite;
            b->vel_28[0] = ((rand() & 0x3F) - 0x1F) << 10;
            b->vel_28[1] = ((rand() & 0x3F) - 0x1F) << 10;
            b->vel_28[2] = ((rand() & 0x3F) - 0x1F) << 10;
            b->frame_0 = 0;
            b->speed_8 = ((rand() & 0xFFF) >> 1) + 0x800;
            e->cb_8 = (EventEntryFn)BounceSparkTask_800C1DA4;
        }
    }
}

void BounceSparkTask_800C1DA4(EventEntry* t, BatSpark_a* u)
{
    int s[3];
    EffectSprite* d;
    int i;
    EffectSpriteFrame* e;
    SaveData* sd;
    u->vel_28[0] = u->vel_28[0] * 15 / 16;
    u->vel_28[1] = u->vel_28[1] * 15 / 16 + 0x200;
    u->vel_28[2] = u->vel_28[2] * 15 / 16;
    s[0] = u->vel_28[0] / 1024;
    s[1] = u->vel_28[1] / 1024;
    s[2] = u->vel_28[2] / 1024;
    u->pos_10[0] += s[0];
    u->pos_10[1] += s[1];
    u->pos_10[2] += s[2];
    sd = &saveData_8008B570;
    if (u->pos_10[1] > sd->levant_7A8.pos.y)
    {
        u->vel_28[1] = -u->vel_28[1];
        u->pos_10[1] = sd->levant_7A8.pos.y;
    }
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d->count_0)
    {
        for (i = 0; i < d->frameCounts_4[u->frame_0 / 4096]; i++)
        {
            e = d->frames_8[u->frame_0 / 4096] + i;
            DrawRotSprite_80044010(&d->poly_C, u->pos_10, u->rot_34, &e->u_0, &e->w_4, &e->f8, e->size_C, e->pos_10, e->rgb_18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

void SpawnRisingSparks_800C1FFC(int* pos, short* rot, int sprite, int speed, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            BatSpark_a* b = e->buffer;
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            b->base_1C[0] = pos[0];
            b->base_1C[1] = pos[1];
            b->base_1C[2] = pos[2];
            b->rot_34[0] = rot[0];
            b->rot_34[1] = rot[1];
            b->rot_34[2] = rot[2];
            b->anim_3C = (EffectSprite*)sprite;
            b->vel_28[0] = ((rand() & 0x3F) - 0x1F) << 10;
            b->vel_28[1] = -(rand() & 0x1F) << 10;
            b->vel_28[2] = ((rand() & 0x3F) - 0x1F) << 10;
            b->pos_10[0] = 0;
            b->pos_10[1] = 0;
            b->pos_10[2] = 0;
            b->frame_0 = 0;
            b->speed_8 = speed + ((rand() & 0xFFF) >> 1) + 0x800;
            e->cb_8 = (EventEntryFn)RisingSparkTask_800C2170;
        }
    }
}

void RisingSparkTask_800C2170(EventEntry* t, BatSpark_a* u)
{
    EffectSprite* d;
    int i;
    EffectSpriteFrame* e;
    u->rot_34[1] += 0x40;
    u->vel_28[0] = u->vel_28[0] * 12 / 13;
    u->vel_28[1] = u->vel_28[1] * 12 / 13 - 0x400;
    u->vel_28[2] = u->vel_28[2] * 12 / 13;
    {
        int s[3];
        s[0] = u->vel_28[0] / 1024;
        s[1] = u->vel_28[1] / 1024;
        s[2] = u->vel_28[2] / 1024;
        u->pos_10[0] += s[0];
        u->pos_10[1] += s[1];
        u->pos_10[2] += s[2];
    }
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d->count_0)
    {
        for (i = 0; i < d->frameCounts_4[u->frame_0 / 4096]; i++)
        {
            short c[3];
            e = d->frames_8[u->frame_0 / 4096] + i;
            c[0] = u->pos_10[0];
            c[1] = u->pos_10[1];
            c[2] = u->pos_10[2];
            DrawRotSprite_80044010(&d->poly_C, u->base_1C, u->rot_34, &e->u_0, &e->w_4, &e->f8, e->size_C, c, e->rgb_18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

#if 0 // Not matched: only u and the hoisted sinTable base swap saved registers (s5/s6); tried decl order, explicit table pointer, early return, temp for the first lookup
void ShatterTask_800C23D0(EventEntry* t, BatSpark_a* u)
{
    int i;
    int a;
    int k;
    int n;
    EventEntry* e;
    BatShard_a* b;
    if (++u->frame_0 >= 30)
    {
        PlaySfx_80031494(0x4F);
        SpawnSpriteAnim_800C1A5C(u->pos_10, (short*)&zeroSvector_800795D4, (int)&effectFile_80091BD0.sprites_20[FindEffectIndex_80020F00(&effectFile_80091BD0, 0, 0x21)], 0x1000);
        for (i = 0; i < 24; i++)
        {
            e = AllocEventEntry_80043AF8(dword_8008D60C);
            if (e)
            {
                b = e->buffer;
                b->base_1C[0] = u->pos_10[0];
                b->base_1C[1] = u->pos_10[1];
                b->base_1C[2] = u->pos_10[2];
                b->frame_0 = 0;
                b->scale_C = (rand() & 0x7FF) + 0x800;
                b->pos_10[0] = 0;
                b->pos_10[1] = 0;
                b->pos_10[2] = 0;
                a = (i << 12) / 24;
                b->vel_28[0] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[a & 0xFFF] / 4096;
                b->vel_28[2] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
                k = rand() & 0x1FF;
                a = k + 0x200;
                b->vel_28[1] = -((rand() & 0x1F) + 0x28) * sinTable_80084540[a] / 4096;
                b->vel_28[0] = b->vel_28[0] * sinTable_80084540[k | 0x600] / 4096;
                b->vel_28[2] = b->vel_28[2] * sinTable_80084540[k | 0x600] / 4096;
                b->vel_28[0] <<= 10;
                b->vel_28[1] <<= 10;
                b->vel_28[2] <<= 10;
                b->rot_34[0] = rand() & 0x1000;
                b->rot_34[1] = rand() & 0x1000;
                b->rot_34[2] = rand() & 0x1000;
                b->rot_34[3] = (rand() & 0x1FF) + 0x100;
                n = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, 0x19);
                e->flags = (e->flags | 1) & 0xFFFF7FFF;
                {
                    EffectModel* ent = &effectFile_80091BD0.models_28[n];
                    b->obj_3C = ent->ftg_4 + i % 8;
                }
                e->cb_8 = (EventEntryFn)ShardTask_800C273C;
            }
        }
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, ShatterTask_800C23D0);

void ShardTask_800C273C(EventEntry* t, BatShard_a* u)
{
    int v[4];
    int s[3];
    u->vel_28[1] += 0x1000;
    u->vel_28[0] = u->vel_28[0] * 31 / 32;
    u->vel_28[1] = u->vel_28[1] * 31 / 32;
    u->vel_28[2] = u->vel_28[2] * 31 / 32;
    u->pos_10[0] += u->vel_28[0];
    u->pos_10[1] += u->vel_28[1];
    u->pos_10[2] += u->vel_28[2];
    if (u->pos_10[1] > 0)
    {
        u->vel_28[1] = -u->vel_28[1] * 3 / 4;
        u->pos_10[1] = 0;
        if (u->vel_28[1] >= -0xFFF)
        {
            t->flags = (t->flags & ~1) | 0x8000;
        }
    }
    u->rot_34[2] += u->rot_34[3];
    s[0] = s[1] = s[2] = u->scale_C;
    v[0] = u->base_1C[0] + u->pos_10[0] / 1024;
    v[1] = u->base_1C[1] + u->pos_10[1] / 1024;
    v[2] = u->base_1C[2] + u->pos_10[2] / 1024;
    DrawFtgObjectAtSlot0_8004D1EC(u->obj_3C, pOT_8008D690, v, u->rot_34, pointLights_8008D534, 0x30, s);
    u->frame_0++;
}

void SpawnShatterEffect_800C2914(BatSrc_a* src, int id)
{
    EventEntry* e;
    BatShard_a* b;
    int i;
    int a;
    int n;
    int s[3];
    e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (e)
    {
        b = e->buffer;
        b->pos_10[0] = src->pos_1C[0];
        b->pos_10[1] = src->pos_1C[1];
        b->pos_10[2] = src->pos_1C[2];
        b->frame_0 = 0;
        n = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, id);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b->obj_3C = &effectFile_80091BD0.models_28[n];
        e->cb_8 = (EventEntryFn)ShatterTask_800C23D0;
    }
    for (i = 0; i < 8; i++)
    {
        e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            b = e->buffer;
            b->base_1C[0] = src->pos_1C[0];
            b->base_1C[1] = src->pos_1C[1];
            b->base_1C[2] = src->pos_1C[2];
            b->frame_0 = 0;
            b->scale_C = (rand() & 0x7FF) + 0x800;
            a = i << 9;
            b->pos_10[0] = sinTable_80084540[a & 0xFFF] * 300 / 4096;
            b->pos_10[2] = sinTable_80084540[(a + 0x400) & 0xFFF] * 300 / 4096;
            a = rand() & 0x3FF;
            b->pos_10[1] = -(sinTable_80084540[a] * 300) / 4096;
            b->pos_10[0] = b->pos_10[0] * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
            b->pos_10[2] = b->pos_10[2] * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
            b->pos_10[0] <<= 10;
            b->pos_10[1] <<= 10;
            b->pos_10[2] <<= 10;
            b->vel_28[0] = -b->pos_10[0] / 4;
            b->vel_28[1] = -b->pos_10[1] / 4;
            b->vel_28[2] = -b->pos_10[2] / 4;
            s[0] = b->vel_28[0] / 1024;
            s[1] = b->vel_28[1] / 1024;
            s[2] = b->vel_28[2] / 1024;
            VectorToAngles_8003B5D4(s, b->rot_34);
            b->rot_34[2] = rand() & 0x1000;
            n = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, id);
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            b->obj_3C = &effectFile_80091BD0.models_28[n];
            e->cb_8 = (EventEntryFn)ImplodeShardTask_800C2CD8;
        }
    }
}

void ImplodeShardTask_800C2CD8(EventEntry* t, BatShard_a* u)
{
    EffectModel* d = u->obj_3C;
    int v[4];
    int s[3];
    if (u->frame_0 >= 0x1A)
    {
        if (u->frame_0 < 0x1E)
        {
            u->pos_10[0] += u->vel_28[0];
            u->pos_10[1] += u->vel_28[1];
            u->pos_10[2] += u->vel_28[2];
        }
        else
        {
            t->flags = (t->flags & ~1) | 0x8000;
        }
    }
    u->rot_34[2] += 0xAA;
    s[0] = s[1] = s[2] = u->scale_C;
    v[0] = u->base_1C[0] + u->pos_10[0] / 1024;
    v[1] = u->base_1C[1] + u->pos_10[1] / 1024;
    v[2] = u->base_1C[2] + u->pos_10[2] / 1024;
    DrawFtgObjectAtSlot0_8004D1EC(d->ftg_4, pOT_8008D690, v, u->rot_34, pointLights_8008D534, 0x30, s);
    u->frame_0++;
}

void SpawnSpriteTrails_800C2E28(int* pos, short* rot, int sprite, int model, int speed, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        EventEntry* ev = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
        if (ev)
        {
            BatTrail_a* b;
            ev->flags = (ev->flags | 1) & 0xFFFF7FFF;
            b = ev->buffer;
            b->pos_44[0] = pos[0];
            b->pos_44[1] = pos[1];
            b->pos_44[2] = pos[2];
            b->trail_50[0].x = pos[0];
            b->trail_50[0].y = pos[1];
            b->trail_50[0].z = pos[2];
            b->trail_50[1].x = pos[0];
            b->trail_50[1].y = pos[1];
            b->trail_50[1].z = pos[2];
            b->trail_50[2].x = pos[0];
            b->trail_50[2].y = pos[1];
            b->trail_50[2].z = pos[2];
            b->rot_80[0] = rot[0];
            b->rot_80[1] = rot[1];
            b->rot_80[2] = rot[2];
            b->anim_88 = (EffectSprite*)sprite;
            b->clip_8C = (EffectModel*)model;
            b->rot_80[0] = 0;
            b->rot_80[2] = 0;
            b->frame_0 = 0;
            b->count_4 = 0;
            b->speed_8 = speed;
            b->rot_80[1] = (i << 12) / n;
            ev->cb_8 = (EventEntryFn)SpriteTrailTask_800C2FC8;
        }
    }
}

void SpriteTrailTask_800C2FC8(EventEntry* t, BatTrail_a* u)
{
    EffectSprite* d = u->anim_88;
    int i;
    int* r;
    EffectSpriteFrame* e;
    if (u->frame_0 / 4096 < d->count_0)
    {
        r = 0;
        for (i = 0; i < d->frameCounts_4[u->frame_0 / 4096]; i++)
        {
            e = d->frames_8[u->frame_0 / 4096] + i;
            r = DrawRotSprite_80044010(&d->poly_C, u->pos_44, u->rot_80, &e->u_0, &e->w_4, &e->f8, e->size_C, e->pos_10, e->rgb_18, 0, 0x30, pOT_8008D690);
        }
        u->trail_50[0].x = u->pos_44[0] + r[0];
        u->trail_50[0].y = u->pos_44[1] + r[1];
        u->trail_50[0].z = u->pos_44[2] + r[2];
        if (u->count_4 == 0)
        {
            u->trail_50[3].x = u->trail_50[0].x;
            u->trail_50[3].y = u->trail_50[0].y;
            u->trail_50[3].z = u->trail_50[0].z;
            u->trail_50[2].x = u->trail_50[0].x;
            u->trail_50[2].y = u->trail_50[0].y;
            u->trail_50[2].z = u->trail_50[0].z;
            u->trail_50[1].x = u->trail_50[0].x;
            u->trail_50[1].y = u->trail_50[0].y;
            u->trail_50[1].z = u->trail_50[0].z;
        }
        u->frame_0 += u->speed_8;
        DrawFtgObjectAt_80044D0C(u->clip_8C->ftg_4, pOT_8008D690, &u->trail_50[0], u->rot_80, pointLights_8008D534, 0x30, 0, 0);
        DrawFtgObjectAt_80044D0C(u->clip_8C->ftg_4 + 1, pOT_8008D690, &u->trail_50[1], u->rot_80, pointLights_8008D534, 0x30, 0, 1);
        DrawFtgObjectAt_80044D0C(u->clip_8C->ftg_4 + 2, pOT_8008D690, &u->trail_50[2], u->rot_80, pointLights_8008D534, 0x30, 0, 2);
        DrawFtgObjectAt_80044D0C(u->clip_8C->ftg_4 + 3, pOT_8008D690, &u->trail_50[3], u->rot_80, pointLights_8008D534, 0x30, 0, 3);
        DrawSpriteVtxQuadsGT4_800459E4(defaultBoneSlots_800C91A4, &u->clip_8C->mats_8, pOT_8008D690, 0x30);
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
    if (++u->count_4 & 1)
    {
        u->trail_50[3].x = u->trail_50[2].x;
        u->trail_50[3].y = u->trail_50[2].y;
        u->trail_50[3].z = u->trail_50[2].z;
        u->trail_50[2].x = u->trail_50[1].x;
        u->trail_50[2].y = u->trail_50[1].y;
        u->trail_50[2].z = u->trail_50[1].z;
        u->trail_50[1].x = u->trail_50[0].x;
        u->trail_50[1].y = u->trail_50[0].y;
        u->trail_50[1].z = u->trail_50[0].z;
    }
}

int SpawnModelAnim_800C32DC(int* pos, int modelId, int clip, int rotY)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    BatAnim_a* b;
    int idx;
    EffectModel* t;
    if (e != 0)
    {
    b = e->buffer;
    b->pos_44[0] = pos[0];
    b->pos_44[1] = pos[1];
    b->pos_44[2] = pos[2];
    b->frame_0 = 0;
    b->speed_8 = 0;
    b->rot_82 = rotY;
    idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, modelId);
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    t = &effectFile_80091BD0.models_28[idx];
    b->clip_88 = t + clip;
    e->cb_8 = (EventEntryFn)ModelAnimTask_800C33E4;
    return t->frameCount_14;
    }
    return -1;
}

#if 0 // Not matched: only u and c swap saved registers (s1/s2); tried decl/init order, early return, tail shapes, pointer arithmetic
void ModelAnimTask_800C33E4(EventEntry* t, BatAnim_a* u)
{
    EffectModel* c = u->clip_88;
    int any;
    int i;
    EffectKey* k;
    int v[3];
    short r[3];
    any = 0;
    if (u->frame_0 < c->frameCount_14)
    {
        for (i = 0; i < c->keyCount_10; i++)
        {
            k = &c->keys_18[i + u->frame_0 * c->keyCount_10];
            if (k->model_0 >= 0)
            {
                r[0] = k->rot_10[0];
                r[1] = k->rot_10[1];
                r[2] = k->rot_10[2];
                r[1] += u->rot_82;
                v[0] = u->pos_44[0] + k->x_4 * sinTable_80084540[(u->rot_82 + 0x400) & 0xFFF] / 4096 + k->z_C * sinTable_80084540[u->rot_82 & 0xFFF] / 4096;
                v[1] = u->pos_44[1] + k->y_8;
                v[2] = u->pos_44[2] - k->x_4 * sinTable_80084540[u->rot_82 & 0xFFF] / 4096 + k->z_C * sinTable_80084540[(u->rot_82 + 0x400) & 0xFFF] / 4096;
                DrawFtgObjectAt_80044D0C(&c->ftg_4[k->model_0], pOT_8008D690, v, r, pointLights_8008D534, (0x1000 - k->alpha_2) << 16 | 0x80 | k->mode_24, k->f18, i);
                if (c->ftg_4[k->model_0].texSpriteCount_48)
                {
                    any = 1;
                }
            }
        }
        u->frame_0++;
        if (any)
        {
            if (c->mats_8.count_0)
            {
                DrawSpriteVtxQuadsGT4_800459E4(defaultBoneSlots_800C91A4, &c->mats_8, pOT_8008D690, 0x30);
            }
        }
        else if (c->mats_8.count_0)
        {
            DrawSpriteVtxQuadsG4_80045E48(&c->mats_8, pOT_8008D690, 0x30);
        }
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, ModelAnimTask_800C33E4);

void GlowTask_800C371C(EventEntry* t, void* arg)
{
    unsigned char col[4] = { 0xE8, 0xE8, 0x80, 0 };
    BatGlow_a* u = arg;
    EffectModel* m = u->model_88;
    if (u->frame_0 < u->end_4 && effectOutcomeFlag_8008D780 == 0)
    {
        int s[4];
        int v[4];
        int a;
        u->f30 += 0x100;
        if (u->f30 > 0x1000)
        {
            u->f30 = 0x1000;
        }
        s[0] = u->scale_A0[0] * 3 / 2;
        s[1] = u->scale_A0[1] * 3 / 2;
        s[2] = u->scale_A0[2] * 3 / 2;
        a = u->f30;
        v[0] = u->path_20[u->idx_98 * 3 + 0] + u->base_1C[0];
        v[1] = u->path_20[u->idx_98 * 3 + 1] + u->base_1C[1];
        v[2] = u->path_20[u->idx_98 * 3 + 2] + u->base_1C[2];
        LerpFtgObject_8003A6C4(a, m->ftg_4, m->ftg_4 + 1, u->work_94);
        DrawFtgObjectAtSlot0_8004D1EC(m->ftg_4, pOT_8008D690, v, &zeroSvector_800795D4, pointLights_8008D534, ((0x1000 - a) << 16) | 0xB0, s);
        SetPointLight_800C4090((int)u->f44, (int)col, 0x5DC, u->f30);
        u->frame_0++;
    }
    else
    {
        int s[4];
        int v[4];
        int a;
        s[0] = u->scale_A0[0] * 3 / 2;
        s[1] = u->scale_A0[1] * 3 / 2;
        s[2] = u->scale_A0[2] * 3 / 2;
        a = u->f30;
        v[0] = u->path_20[u->idx_98 * 3 + 0] + u->base_1C[0];
        v[1] = u->path_20[u->idx_98 * 3 + 1] + u->base_1C[1];
        v[2] = u->path_20[u->idx_98 * 3 + 2] + u->base_1C[2];
        LerpFtgObject_8003A6C4(a, m->ftg_4, m->ftg_4 + 1, u->work_94);
        DrawFtgObjectAtSlot0_8004D1EC(m->ftg_4, pOT_8008D690, v, &zeroSvector_800795D4, pointLights_8008D534, ((0x1000 - a) << 16) | 0xB0, s);
        if (u->f30 == 0x1000)
        {
            SpawnOrb_800C3B50(v, 0x25);
        }
        SetPointLight_800C4090((int)u->f44, (int)col, 0x5DC, u->f30);
        if (u->f30 <= 0)
        {
            ClearPointLight_800C410C();
            FreeFtgObjectData_80021804(u->work_94, 1);
            free3_8003FC6C(u->work_94);
            t->flags = (t->flags & ~1) | 0x8000;
        }
        u->f30 -= 0x100;
    }
}


#if 0 // Not matched: regalloc only: the 0xFFFF7FFF mask and the effect-file base swap saved registers (orig s0/s3); body and schedule otherwise match
extern void PlaySfx_80031494(int id);
extern void OrbHomingTask_800C3DF8();
extern void OrbFadeTask_800C3D34();
void SpawnOrb_800C3B50(int* p, int id)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    BatOrb_a* b;
    EffectModel* ent;
    BatHero_a* q;
    int f;
    int idx;
    if (e == 0)
    {
        return;
    }
    b = e->buffer;
    b->pos_44[0] = p[0];
    b->pos_44[1] = p[1];
    b->pos_44[2] = p[2];
    b->frame_0 = 0;
    b->fx_E = FindEffectIndex_80020F00(&effectFile_80091BD0, 0, id);
    b->alpha_30 = 0x1000;
    b->f34 = 0;
    b->rot_80[2] = 0;
    b->rot_80[1] = 0;
    b->rot_80[0] = 0;
    b->vel_38[0] = 0;
    b->vel_38[1] = -0xC8;
    b->vel_38[2] = 0;
    f = (&effectOutcomeFlag_8008D780)[1];
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    if (f == 0)
    {
    idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, 0x1F);
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    ent = &effectFile_80091BD0.models_28[idx];
    b->clip_88 = ent;
    b->model_94 = malloc3_8003FC4C(0x54);
    CopyFtgObject_800218A8(ent->ftg_4, b->model_94, 1);
    DiffFtgObjects_80039FE4(ent->ftg_4, ent->ftg_4 + 1, b->model_94);
    q = gameTask_8008B4A4->hero_24;
    b->pos_44[0] = q->pos_5E4[0];
    b->pos_44[1] = q->pos_5E4[1];
    b->pos_44[2] = q->pos_5E4[2];
    b->pos_44[0] += levantPos_8008BD18.pos.x;
    b->pos_44[1] += levantPos_8008BD18.pos.y;
    b->pos_44[2] += levantPos_8008BD18.pos.z;
    e->cb_8 = (EventEntryFn)OrbFadeTask_800C3D34;
    PlaySfx_80031494(0x3F);
    }
    else
    {
        PlaySfx_80031494(0x47);
        e->cb_8 = (EventEntryFn)OrbHomingTask_800C3DF8;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, SpawnOrb_800C3B50);

void OrbFadeTask_800C3D34(EventEntry* t, BatOrb_a* u)
{
    EffectModel* m = u->clip_88;
    int v = u->alpha_30 - 0x100;
    u->alpha_30 = v;
    if (v > 0)
    {
        LerpFtgObject_8003A6C4(v, m->ftg_4, m->ftg_4 + 1, u->model_94);
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
        FreeFtgObjectData_80021804(u->model_94, 1);
        free3_8003FC6C(u->model_94);
    }
    DrawFtgObjectAtSlot0_8004D1EC(m->ftg_4, pOT_8008D690, u->pos_44, u->rot_80, pointLights_8008D534, ((0x1000 - u->alpha_30) << 16) | 0xB0, 0);
}

void OrbHomingTask_800C3DF8(EventEntry* t, BatOrb_a* u)
{
    int v[3];
    BatHero_a* q;
    BatOrb_a* w;
    w = u;
    SpawnSpriteAnim_800C1A5C(u->pos_44, (short*)&zeroSvector_800795D4, (int)&effectFile_80091BD0.sprites_20[u->fx_E], 0x1000);
    q = gameTask_8008B4A4->hero_24;
    v[0] = q->pos_5E4[0];
    v[1] = q->pos_5E4[1];
    v[2] = q->pos_5E4[2];
    v[0] += levantPos_8008BD18.pos.x;
    v[1] += levantPos_8008BD18.pos.y;
    v[2] += levantPos_8008BD18.pos.z;
    if (DistanceSquared3D_8003B80C(v, u->pos_44) >= 0x57E5)
    {
        u->vel_38[0] += ((v[0] - u->pos_44[0]) << 10) / 70;
        u->vel_38[1] += ((v[1] - u->pos_44[1]) << 10) / 70;
        u->vel_38[2] += ((v[2] - u->pos_44[2]) << 10) / 70;
        u->vel_38[0] = u->vel_38[0] * 31 / 32;
        u->vel_38[1] = u->vel_38[1] * 31 / 32;
        u->vel_38[2] = u->vel_38[2] * 31 / 32;
        u->pos_44[0] += u->vel_38[0] / 1024;
        u->pos_44[1] += u->vel_38[1] / 1024;
        u->pos_44[2] += u->vel_38[2] / 1024;
    }
    else
    {
        ((void (*)())SpawnBounceSparks_800C1C5C)(v, &zeroSvector_800795D4, (int)&effectFile_80091BD0.sprites_20[w->fx_E], 0x1000);
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

void SetPointLight_800C4090(int posArg, int rgbArg, int range, int intensity)
{
    int* pos = (int*)posArg;
    unsigned char* rgb = (unsigned char*)rgbArg;
    unsigned int scale = intensity;
    pointLightPos_8008D680[0] = pos[0];
    pointLightPos_8008D680[1] = pos[1];
    pointLightPos_8008D680[2] = pos[2];
    pointLightRange_8008D3F0 = range;
    dword_8008D418[0] = rgb[0] * scale >> 7;
    dword_8008D418[1] = rgb[1] * scale >> 7;
    dword_8008D418[2] = rgb[2] * scale >> 7;
}

void ClearPointLight_800C410C()
{
    pointLightRange_8008D3F0 = 0;
}

extern int EnemyAiBD_800C4A40(BatTask* t);
extern void BossAi03_800C5BC0(BatTask* t);
extern void BossAi04_800C59A0(BatTask* t);
extern void BossAi0A_800C58BC(BatTask* t);
extern void BossAi0B_800C5EB8(BatTask* t);
extern void BossAi0C_800C6038(BatTask* t);
extern void BossAi0D_800C5D04(BatTask* t);
extern void BossAi0E_800C61FC(BatTask* t);
extern void BossAi0F_800C66F4(BatTask* t);
extern void BossAi10_800C6824(BatTask* t);
extern void BossAi11_800C6928(BatTask* t);
extern void EnemyAiFirstSkill_800C6A40(BatTask* t);
void BossAi02_800C5A7C(BatTask* t);
void EnemyAiDefend_800C58AC(BatTask* t);

// Matched
void ChooseEnemyCommand_800C4118(BatCmd_a* cmd, UnitStats* self, int slot, unsigned int script)
{
    BatTask t;
    unsigned int species;
    int minion;
    species = self->species_5C;
    t.magicBits_0 = &self->magicBits_80;
    t.skills_4 = &self->skills_6C;
    t.cmd_8 = cmd;
    t.slot_C = slot;
    t.self_10 = self;
    t.f1C = 4;
    minion = GetSummonedMinionSlot_800C0D50();
    if (minion >= 0)
    {
        t.targetMask_18 = 1 << (minion + 1);
        t.target_14 = GetMinionStatus_800107A0(3, minion);
    }
    else
    {
        t.targetMask_18 = 1;
        t.target_14 = &levantStatus_8008BD38;
    }
    t.cmd_8->mask_8 = 1 << (slot + 4);
    switch (script)
    {
    case 0:
        if (species < 0x39)
        {
            enemyAi_800C9204[species](&t);
        }
        else if (species < 0xC9)
        {
            if (species - 0xBD < 4)
            {
                EnemyAiBD_800C4A40(&t);
            }
            EnemyAiDefault_800C473C(&t);
            break;
        }
        else
        {
            species -= 0xC9;
            enemyAiHigh_800C91DC[species](&t);
        }
        break;
    case 2:
        BossAi02_800C5A7C(&t);
        break;
    case 15:
        BossAi0F_800C66F4(&t);
        break;
    case 16:
        BossAi10_800C6824(&t);
        break;
    case 17:
        BossAi11_800C6928(&t);
        break;
    case 3:
        BossAi03_800C5BC0(&t);
        break;
    case 4:
        BossAi04_800C59A0(&t);
        break;
    case 10:
        BossAi0A_800C58BC(&t);
        break;
    case 11:
        BossAi0B_800C5EB8(&t);
        break;
    case 12:
        BossAi0C_800C6038(&t);
        break;
    case 13:
        BossAi0D_800C5D04(&t);
        break;
    case 14:
        BossAi0E_800C61FC(&t);
        break;
    case 7:
    case 8:
    case 9:
        EnemyAiFirstSkill_800C6A40(&t);
        break;
    default:
        EnemyAiDefend_800C58AC(&t);
        break;
    }
}

void EnemyAiC9_800C4328(BatTask* t)
{
    UnitStatus* s = t->target_14;
    short x = GetHp_800334D8(s);
    short y = GetMaxHp_800334CC(s);
    if (x < (short)(y / 10))
    {
        AiSetCommand_800C6AFC(t, 6, 0);
    }
    else if (rand() & 1)
    {
        AiSetCommand_800C6AFC(t, 6, 1);
    }
    else
    {
        AiSetCommand_800C6AFC(t, 0, 0);
    }
}

void EnemyAiCA_800C43D8(BatTask* t)
{
    if (rand(t) & 1)
    {
        AiSetCommand_800C6AFC(t, 1, 8);
    }
    else
    {
        AiSetCommand_800C6AFC(t, 1, 6);
    }
}

void EnemyAiCB_800C4424(BatTask* t)
{
    if (rand(t) & 1)
    {
        AiSetCommand_800C6AFC(t, 6, 2);
    }
    else
    {
        AiSetCommand_800C6AFC(t, 0, 0);
    }
}

void EnemyAiCC_800C4470(int t)
{
    AiSetCommand_800C6AFC(t, 1, 0x14);
}

void EnemyAiCD_800C4494(BatTask* t)
{
    int x = rand();
    if (x % 3)
    {
        AiSetCommand_800C6AFC(t, 6, 3);
    }
    else
    {
        AiSetCommand_800C6AFC(t, 0, 0);
    }
}

void EnemyAiCE_800C44FC(BatTask* t)
{
    if (rand(t) & 1)
    {
        AiSetCommand_800C6AFC(t, 6, 1);
    }
    else
    {
        AiSetCommand_800C6AFC(t, 6, 2);
    }
}

void EnemyAiCF_800C4548(BatTask* t)
{
    if (AiHealWeakAlly_800C6DF8(t, 0xD) == 0)
    {
        if (rand() & 1)
        {
            AiDefend_800C6C44(t);
        }
        else
        {
            AiSetCommand_800C6AFC(t, 0, 0);
        }
    }
}

void EnemyAiD0_800C45A8(BatTask* t)
{
    if (TargetHasStatus_800C6EC8(t, 0x3F8) == 0 && rand() % 10 < 7)
    {
        AiSetCommand_800C6AFC(t, 6, 0);
    }
    else if (TargetHasStatus_800C6EC8(t, 2) == 0 && rand() % 10 < 7)
    {
        AiSetCommand_800C6AFC(t, 6, 1);
    }
    else if (TargetHasStatus_800C6EC8(t, 1) == 0 && rand() % 10 < 7)
    {
        AiSetCommand_800C6AFC(t, 6, 2);
    }
    else
    {
        AiAttack_800C6A68(t);
    }
}

void EnemyAiD1_800C46FC()
{
    EnemyAiDefault_800C473C();
}

void EnemyAiD2_800C471C()
{
    EnemyAiDefault_800C473C();
}

int EnemyAiDefault_800C473C(BatTask* t)
{
    UnitStatus* s = &t->self_10->st_0;
    int r;
    int i;
    if ((GetAreaElement_800BC868() == 0 || GetAreaElement_800BC868() == -1) && (r = AiCastMagic_800C6BD0(t, 0x16)))
    {
        return r;
    }
    if ((GetAreaElement_800BC868() == 1 || GetAreaElement_800BC868() == -1) && (r = AiCastMagic_800C6BD0(t, 0x15)))
    {
        return r;
    }
    if ((GetAreaElement_800BC868() == 2 || GetAreaElement_800BC868() == -1) && (r = AiCastMagic_800C6BD0(t, 0x18)))
    {
        return r;
    }
    if ((GetAreaElement_800BC868() == 3 || GetAreaElement_800BC868() == -1) && (r = AiCastMagic_800C6BD0(t, 0x17)))
    {
        return r;
    }
    if (TargetHasStatus_800C6EC8(t, 0x3F8) == 0 && rand() % 10 < 7 && (r = AiCastMagic_800C6BD0(t, 0x13)))
    {
        return r;
    }
    if (TargetHasStatus_800C6EC8(t, 2) == 0 && rand() % 10 < 7 && (r = AiCastMagic_800C6BD0(t, 0x12)))
    {
        return r;
    }
    if (TargetHasStatus_800C6EC8(t, 1) == 0 && rand() % 10 < 7 && (r = AiCastMagic_800C6BD0(t, 0x11)))
    {
        return r;
    }
    if ((rand() & 1) && (r = AiCastMagic_800C6BD0(t, 0x14)))
    {
        return r;
    }
    if ((r = AiHealWeakAlly_800C6DF8(t, 0xD)))
    {
        return r;
    }
    if (s->stats_2C.cur_0[1] > s->stats_2C.cur_0[3])
    {
        if (rand() % 10 < 8 && (r = AiUseSkill_800C6A8C(t)))
        {
            return r;
        }
    }
    else
    {
        for (i = 0; i < 12; i++)
        {
            if ((r = AiCastMagic_800C6BD0(t, i)))
            {
                return r;
            }
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAiBD_800C4A40(BatTask* t)
{
    int r;
    if (rand() & 1)
    {
        if (TargetHasStatus_800C6EC8(t, 0x3F8) == 0)
        {
            r = AiCastMagic_800C6BD0(t, 0x13);
        }
        else
        {
            r = AiUseSkill_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        if (TargetHasStatus_800C6EC8(t, 2) == 0)
        {
            r = AiCastMagic_800C6BD0(t, 0x12);
        }
        else
        {
            r = AiUseSkill_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        if (TargetHasStatus_800C6EC8(t, 1) == 0)
        {
            r = AiCastMagic_800C6BD0(t, 0x11);
        }
        else
        {
            r = AiUseSkill_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        r = AiCastMagic_800C6BD0(t, 0x14);
        if (r == 0)
        {
            r = AiUseSkill_800C6A8C(t);
        }
        return r;
    }
    return AiFlee_800C6C58(t);
}

int EnemyAi0F_800C4B34(BatTask* t)
{
    int r;
    UnitStatus* s = &t->self_10->st_0;
    short x = GetHp_800334D8(s);
    short y = GetMaxHp_800334CC(s);
    if (x < (short)(y / 3))
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
        if (rand() & 1)
        {
            r = AiDefend_800C6C44(t);
            if (r)
            {
                return r;
            }
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi06_800C4BE4(BatTask* t)
{
    int r;
    UnitStatus* s = &t->self_10->st_0;
    r = AiHealWeakAlly_800C6DF8(t, 0xD);
    if (r)
    {
        return r;
    }
    {
        short x = GetHp_800334D8(s);
        short y = GetMaxHp_800334CC(s);
        if (x < y)
        {
            if (rand() & 1)
            {
                r = AiDefend_800C6C44(t);
                if (r)
                {
                    return r;
                }
            }
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi12_800C4C74(BatTask* t)
{
    int r;
    if (TargetHasStatus_800C6EC8(t, 1) == 0)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi0C_800C4CBC(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (m < 30)
    {
        r = AiCastMagic_800C6BD0(t, 0);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi00_800C4D38(BatTask* t)
{
    int r;
    UnitStatus* s = &t->self_10->st_0;
    short x = GetHp_800334D8(s);
    short y = GetMaxHp_800334CC(s);
    if (x < y / 4)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi09_800C4DB8(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (m < 50)
    {
        r = AiCastMagic_800C6BD0(t, 9);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi07_800C4E34(BatTask* t)
{
    int r;
    if (rand() % 10 < 7)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi0A_800C4EA8(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (aiCounter_800C8B30 < 2)
    {
        if (TargetHasStatus_800C6EC8(t, 2) == 0 && m < 40)
        {
            r = AiCastMagic_800C6BD0(t, 0x12);
            if (r)
            {
                return r;
            }
            aiCounter_800C8B30++;
        }
        if (TargetHasStatus_800C6EC8(t, 2) == 0 && m < 40)
        {
            r = AiUseSkill_800C6A8C(t);
            if (r)
            {
                return r;
            }
            aiCounter_800C8B30++;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi1A_800C4FA8(BatTask* t)
{
    int r = AiCastMagic_800C6BD0(t, 4);
    if (r == 0)
    {
        r = AiAttack_800C6A68(t);
    }
    return r;
}

int EnemyAi03_800C4FE0(BatTask* t)
{
    int r;
    if (IsTargetWeakToMagic_800C6EE4(t))
    {
        r = AiCastMagic_800C6BD0(t, 7);
        if (r)
        {
            return r;
        }
    }
    r = AiUseSkill_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi0E_800C5034(BatTask* t)
{
    int r;
    if (TargetHasStatus_800C6EC8(t, 0x3F8) == 0)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi13_800C507C(BatTask* t)
{
    int r = AiUseSkill_800C6A8C(t);
    if (r == 0)
    {
        r = AiAttack_800C6A68(t);
    }
    return r;
}

int EnemyAi17_800C50B0(BatTask* t)
{
    int r;
    UnitStatus* s = &t->self_10->st_0;
    short x;
    short y;
    if (GetAreaElement_800BC868() == 3 || GetAreaElement_800BC868() == -1)
    {
        r = AiCastMagic_800C6BD0(t, 0x17);
        if (r)
        {
            return r;
        }
    }
    if (rand() % 10 < 6)
    {
        r = AiCastMagic_800C6BD0(t, 6);
        if (r)
        {
            return r;
        }
    }
    x = GetHp_800334D8(s);
    y = GetMaxHp_800334CC(s);
    if (x <= (short)(y / 3) && (rand() & 1))
    {
        r = AiFlee_800C6C58(t);
        if (r)
        {
            return r;
        }
    }
    return AiDefend_800C6C44(t);
}

int EnemyAi1B_800C51D8(BatTask* t)
{
    int r;
    if (rand(t) & 1)
    {
        r = AiUseSkill_800C6A8C(t);
    }
    else
    {
        r = AiAttack_800C6A68(t);
    }
    return r;
}

int EnemyAiUnused_800C5220(BatTask* t)
{
    UnitStatus* s = t->target_14;
    int r = AiHealWeakAlly_800C6DF8(t, 0xD);
    if (r)
    {
        return r;
    }
    if ((short)GetHp_800334D8(s) != 1)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi15_800C5290(BatTask* t)
{
    int r;
    if (rand() % 10 < 6)
    {
        r = AiCastMagic_800C6BD0(t, 2);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi10_800C5304(BatTask* t)
{
    int r;
    if (TargetHasStatus_800C6EC8(t, 1) == 0 && rand() % 10 < 7)
    {
        r = AiCastMagic_800C6BD0(t, 0x11);
        if (r)
        {
            return r;
        }
    }
    if (rand() & 1)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi1C_800C53B0(BatTask* t)
{
    int r;
    if (rand() % 10 < 6)
    {
        r = AiCastMagic_800C6BD0(t, 5);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi0D_800C5424(BatTask* t)
{
    int r;
    UnitStatus* s = &t->self_10->st_0;
    short x = GetHp_800334D8(s);
    short y = GetMaxHp_800334CC(s);
    if (x <= y / 2)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi02_800C54A4(BatTask* t)
{
    int r;
    if (GetAreaElement_800BC868() == 1 || GetAreaElement_800BC868() == -1)
    {
        r = AiCastMagic_800C6BD0(t, 0x15);
        if (r)
        {
            return r;
        }
    }
    r = AiUseSkill_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi0B_800C5510(BatTask* t)
{
    int r;
    if (AiCastMagic_800C6BD0(t, 8) == 0)
    {
        return AiFlee_800C6C58(t);
    }
    r = rand() & 1;
    if (r)
    {
        return r;
    }
    if (GetMp_800334F0(t->target_14) != 0)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    r = AiAttack_800C6A68(t);
    if (r)
    {
        return r;
    }
    return AiFlee_800C6C58(t);
}

int EnemyAi14_800C5594(BatTask* t)
{
    int r;
    if (rand() % 10 < 7)
    {
        r = AiUseSkill_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi16_800C5608(BatTask* t)
{
    int r;
    if (GetAreaElement_800BC868() == 0 || GetAreaElement_800BC868() == -1)
    {
        r = AiCastMagic_800C6BD0(t, 0x16);
        if (r)
        {
            return r;
        }
    }
    r = AiUseSkill_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi18_800C5670(BatTask* t)
{
    int r;
    if (TargetHasStatus_800C6EC8(t, 0x3F8) == 0)
    {
        r = AiCastMagic_800C6BD0(t, 0x13);
        if (r)
        {
            return r;
        }
    }
    return AiDefend_800C6C44(t);
}

int EnemyAi05_800C56B8(BatTask* t)
{
    int r = AiCastMagic_800C6BD0(t, 0xB);
    if (r)
    {
        return r;
    }
    r = AiUseSkill_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi1D_800C5700(BatTask* t)
{
    int r;
    if (GetAreaElement_800BC868() == 2 || GetAreaElement_800BC868() == -1)
    {
        r = AiCastMagic_800C6BD0(t, 0x18);
        if (r)
        {
            return r;
        }
    }
    r = AiUseSkill_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi19_800C576C(BatTask* t)
{
    int r;
    if (GetAreaElement_800BC868() == 3 || GetAreaElement_800BC868() == -1)
    {
        r = AiCastMagic_800C6BD0(t, 0x17);
        if (r)
        {
            return r;
        }
    }
    r = AiUseSkill_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return AiAttack_800C6A68(t);
}

int EnemyAi04_800C57D8(BatTask* t)
{
    int r = AiUseSkill_800C6A8C(t);
    if (r == 0)
    {
        r = AiAttack_800C6A68(t);
    }
    return r;
}

int EnemyAi08_800C580C(BatTask* t)
{
    int r = AiUseSkill_800C6A8C(t);
    if (r == 0)
    {
        r = AiAttack_800C6A68(t);
    }
    return r;
}

int EnemyAi1F_800C5840(BatTask* t)
{
    int r = AiUseSkill_800C6A8C(t);
    if (r == 0)
    {
        r = AiAttack_800C6A68(t);
    }
    return r;
}

int EnemyAi1E_800C5874(BatTask* t)
{
    int r = AiCastMagic_800C6BD0(t, 0x14);
    if (r == 0)
    {
        r = AiAttack_800C6A68(t);
    }
    return r;
}

void EnemyAiDefend_800C58AC(BatTask* t)
{
    t->cmd_8->kind_0 = 0x12;
}

void BossAi0A_800C58BC(BatTask* t)
{
    unsigned char k = aiCounter_800C8B30 % 6;
    switch (k)
    {
    case 0:
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = 2;
        t->cmd_8->targets_C = t->targetMask_18;
        break;
    case 2:
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = 3;
        t->cmd_8->targets_C = t->targetMask_18;
        break;
    case 4:
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = 1;
        t->cmd_8->targets_C = t->targetMask_18;
        break;
    case 1:
    case 3:
    case 5:
        t->cmd_8->kind_0 = 0;
        t->cmd_8->targets_C = t->targetMask_18;
        break;
    }
    aiCounter_800C8B30++;
}

const char aAttackWithReadi_800B68AC[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202\227\202\211\202\224\202\210\201@\202\222\202\205\202\201\202\204\202\211\202\205\202\204\201@\202\227\202\205\202\201\202\220\202\217\202\216"; // Attack with readied weapon
const char aDefendToReduceD_800B68E4[] = "\202c\202\205\202\206\202\205\202\216\202\204\201@\202\224\202\217\201@\202\222\202\205\202\204\202\225\202\203\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205"; // Defend to reduce damage
const char aSummonDivineMin_800B6914[] = "\202r\202\225\202\215\202\215\202\217\202\216\201@\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216"; // Summon Divine Minion
const char aCaptureMinionIn_800B6940[] = "\202b\202\201\202\220\202\224\202\225\202\222\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202\211\202\216\202\224\202\217\201@\202d\202\215\202\220\202\224\202\231\201@\202b\202\217\202\203\202\217\202\217\202\216\201D"; // Capture Minion into Empty Cocoon.
const char aUseItem_800B6984[] = "\202t\202\223\202\205\201@\202h\202\224\202\205\202\215"; // Use Item
const char aFleeFromCombat_800B6998[] = "\202e\202\214\202\205\202\205\201@\202\206\202\222\202\217\202\215\201@\202\203\202\217\202\215\202\202\202\201\202\224"; // Flee from combat
const char aUseNormalAttack_800B69BC[] = "\202t\202\223\202\205\201@\202\216\202\217\202\222\202\215\202\201\202\214\201@\202\201\202\224\202\224\202\201\202\203\202\213"; // Use normal attack
const char aUseSpecialAttac_800B69E0[] = "\202t\202\223\202\205\201@\202\223\202\220\202\205\202\203\202\211\202\201\202\214\201@\202\201\202\224\202\224\202\201\202\203\202\213"; // Use special attack
const char aUseMagicSpell_800B6A08[] = "\202t\202\223\202\205\201@\202\215\202\201\202\207\202\211\202\203\201@\202\223\202\220\202\205\202\214\202\214"; // Use magic spell
const char aChangeCurrentFi_800B6A28[] = "\202b\202\210\202\201\202\216\202\207\202\205\201@\202\203\202\225\202\222\202\222\202\205\202\216\202\224\201@\202\206\202\211\202\207\202\210\202\224\202\205\202\222"; // Change current fighter
const char aNoDivineMinions_800B6A58[] = "\202m\202\217\201@\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\222\202\205\202\201\202\204\202\231"; // No Divine Minions ready
const char aCannotSummonInt_800B6A88[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\223\202\225\202\215\202\215\202\217\202\216\201@\202\211\202\216\202\224\202\217\201@\202\203\202\217\202\215\202\202\202\201\202\224"; // Cannot summon into combat
const char aNotEnoughMana_800B6ABC[] = "\202m\202\217\202\224\201@\202\205\202\216\202\217\202\225\202\207\202\210\201@\202l\202\201\202\216\202\201"; // Not enough Mana
const char aCannotCapture_800B6ADC[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\203\202\201\202\220\202\224\202\225\202\222\202\205"; // Cannot capture
const char aNoEmptyCocoons_800B6AFC[] = "\202m\202\217\201@\202\205\202\215\202\220\202\224\202\231\201@\202\203\202\217\202\203\202\217\202\217\202\216\202\223"; // No empty cocoons
const char aCannotEscape_800B6B20[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\205\202\223\202\203\202\201\202\220\202\205"; // Cannot escape
const char aNoNeedToUseItem_800B6B3C[] = "\202m\202\217\201@\202\216\202\205\202\205\202\204\201@\202\224\202\217\201@\202\225\202\223\202\205\201@\202\211\202\224\202\205\202\215"; // No need to use item
const char aCannotSelect_800B6B64[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\223\202\205\202\214\202\205\202\203\202\224"; // Cannot select
const char aThisItemIsForDi_800B6B80[] = "\202s\202\210\202\211\202\223\201@\202\211\202\224\202\205\202\215\201@\202\211\202\223\201@\202\206\202\217\202\222\201@\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223"; // This item is for Divine Minions
const char aDivineMinionsCa_800B6BC0[] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\203\202\201\202\216\202\216\202\217\202\224\201@\202\225\202\223\202\205\201@\202\224\202\210\202\211\202\223\201@\202\211\202\224\202\205\202\215"; // Divine Minions cannot use this item
const char aCannotUseHere_800B6C08[] = "\202b\202\201\202\216\202\216\202\217\202\224\201@\202\225\202\223\202\205\201@\202\210\202\205\202\222\202\205"; // Cannot use here
const char aAttractsNearbyM_800B6C28[] = "\202`\202\224\202\224\202\222\202\201\202\203\202\224\202\223\201@\202\216\202\205\202\201\202\222\202\202\202\231\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // Attracts nearby minions.
const char aTreeSporesWithA_800B6C5C[] = "\202s\202\222\202\205\202\205\201@\202\223\202\220\202\217\202\222\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202\201\201@\202\203\202\201\202\220\202\224\202\211\202\226\202\201\202\224\202\211\202\216\202\207\201@\202\223\202\203\202\205\202\216\202\224\201D"; // Tree spores with a captivating scent.
const char aCausesSurroundi_800B6CA8[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\223\202\225\202\222\202\222\202\217\202\225\202\216\202\204\202\211\202\216\202\207\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\224\202\217\201@\202\206\202\201\202\214\202\214\201@\202\201\202\223\202\214\202\205\202\205\202\220\201D"; // Causes surrounding Minions to fall asleep.
const char aSweetSmellingSl_800B6D00[] = "\202r\202\227\202\205\202\205\202\224\201|\202\223\202\215\202\205\202\214\202\214\202\211\202\216\202\207\201C\201@\202\223\202\214\202\205\202\205\202\220\201|\202\211\202\216\202\204\202\225\202\203\202\211\202\216\202\207\201@\202\223\202\220\202\217\202\222\202\205\202\223\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\224\202\222\202\205\202\205\201D"; // Sweet-smelling, sleep-inducing spores from a tree.
const char aTreeSpores_800B6D68[] = "\202s\202\222\202\205\202\205\201@\202r\202\220\202\217\202\222\202\205\202\223"; // Tree Spores
const char aBendsAndBecomes_800B6D80[] = "\202a\202\205\202\216\202\204\202\223\201@\202\201\202\216\202\204\201@\202\202\202\205\202\203\202\217\202\215\202\205\202\223\201@\202\227\202\217\202\222\202\224\202\210\202\214\202\205\202\223\202\223\201@\202\201\202\206\202\224\202\205\202\222\201@\202\217\202\216\202\205\201@\202\225\202\223\202\205\201D"; // Bends and becomes worthless after one use.
const char aMultipurposeKey_800B6DD8[] = "\202l\202\225\202\214\202\224\202\211\202\220\202\225\202\222\202\220\202\217\202\223\202\205\201@\202\213\202\205\202\231\201@\202\206\202\217\202\222\201@\202\217\202\220\202\205\202\216\202\211\202\216\202\207\201@\202f\202\205\202\210\202\205\202\216\202\201\201@\202o\202\201\202\214\202\205\201@\202\203\202\210\202\205\202\223\202\224\202\223\201D"; // Multipurpose key for opening Gehena Pale chests.
const char aKeyToTreasureCh_800B6E3C[] = "\202j\202\205\202\231\201@\202\224\202\217\201@\202s\202\222\202\205\202\201\202\223\202\225\202\222\202\205\201@\202b\202\210\202\205\202\223\202\224\202\223"; // Key to Treasure Chests
const char aHighestGradeBes_800B6E6C[] = "\202g\202\211\202\207\202\210\202\205\202\223\202\224\201|\202\207\202\222\202\201\202\204\202\205\201C\201@\202\202\202\205\202\223\202\224\201|\202\221\202\225\202\201\202\214\202\211\202\224\202\231\201@\202\223\202\211\202\214\202\213\201D"; // Highest-grade, best-quality silk.
const char aSoftThreadThatG_800B6EB0[] = "\202r\202\217\202\206\202\224\201@\202\224\202\210\202\222\202\205\202\201\202\204\201@\202\224\202\210\202\201\202\224\201@\202\207\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\207\202\217\202\204\202\214\202\231\201@\202\214\202\211\202\207\202\210\202\224\201D"; // Soft thread that gives off a godly light.
const char aSecondHighestGr_800B6F04[] = "\202r\202\205\202\203\202\217\202\216\202\204\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Second-highest grade of silk.
const char aGivesOffAnUnear_800B6F40[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\202\216\201@\202\225\202\216\202\205\202\201\202\222\202\224\202\210\202\214\202\231\201@\202\202\202\222\202\211\202\214\202\214\202\211\202\201\202\216\202\224\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off an unearthly brilliant shine.
const char aThirdHighestGra_800B6F90[] = "\202s\202\210\202\211\202\222\202\204\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Third-highest grade of silk.
const char aGivesOffAPhosph_800B6FCC[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\220\202\210\202\217\202\223\202\220\202\210\202\217\202\222\202\205\202\223\202\203\202\205\202\216\202\224\201@\202\227\202\210\202\211\202\224\202\205\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off a phosphorescent white shine.
const char aFourthHighestGr_800B701C[] = "\202e\202\217\202\225\202\222\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Fourth-highest grade of silk.
const char aGivesOffAModera_800B7058[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\215\202\217\202\204\202\205\202\222\202\201\202\224\202\205\201C\201@\202\203\202\214\202\205\202\201\202\222\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off a moderate, clear shine.
const char aFifthHighestGra_800B70A0[] = "\202e\202\211\202\206\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Fifth-highest grade of silk.
const char aGivesOffADazzli_800B70DC[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\204\202\201\202\232\202\232\202\214\202\211\202\216\202\207\201@\202\223\202\210\202\211\202\216\202\205\201D"; // Gives off a dazzling shine.
const char aSixthHighestGra_800B7114[] = "\202r\202\211\202\230\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Sixth-highest grade of silk.
const char aEmitsVagueInsta_800B7150[] = "\202d\202\215\202\211\202\224\202\223\201@\202\226\202\201\202\207\202\225\202\205\201C\201@\202\211\202\216\202\223\202\224\202\201\202\216\202\224\202\201\202\216\202\205\202\217\202\225\202\223\201@\202\206\202\214\202\201\202\223\202\210\202\205\202\223\201@\202\217\202\206\201@\202\214\202\211\202\207\202\210\202\224\201D"; // Emits vague, instantaneous flashes of light.
const char aSeventhHighestG_800B71AC[] = "\202r\202\205\202\226\202\205\202\216\202\224\202\210\201|\202\210\202\211\202\207\202\210\202\205\202\223\202\224\201@\202\207\202\222\202\201\202\204\202\205\201@\202\217\202\206\201@\202\223\202\211\202\214\202\213\201D"; // Seventh-highest grade of silk.
const char aGivesOffAShineT_800B71EC[] = "\202f\202\211\202\226\202\205\202\223\201@\202\217\202\206\202\206\201@\202\201\201@\202\223\202\210\202\211\202\216\202\205\201@\202\224\202\210\202\201\202\224\201@\202\207\202\222\202\201\202\202\202\223\201@\202\231\202\217\202\225\202\222\201@\202\201\202\224\202\224\202\205\202\216\202\224\202\211\202\217\202\216\201D"; // Gives off a shine that grabs your attention.
const char aSilkThreadSpunF_800B7248[] = "\202r\202\211\202\214\202\213\201@\202\224\202\210\202\222\202\205\202\201\202\204\201@\202\223\202\220\202\225\202\216\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\227\202\210\202\211\202\224\202\205\201@\202\203\202\217\202\203\202\217\202\217\202\216\201D"; // Silk thread spun from a white cocoon.
const char aInflictsAWindBa_800B7294[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\215\202\225\202\214\202\224\202\211\202\220\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts a Wind-based attack on multiple enemies.
const char aAttackMultipleE_800B72F8[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202l\202\225\202\214\202\224\202\211\202\220\202\214\202\205\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202v\202\211\202\216\202\204"; // Attack Multiple Enemies with Wind
const char aInflictsAWindBa_800B733C[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts a Wind-based attack on a single enemy.
const char aSealWithTheMark_800B739C[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202l\202\201\202\214\202\224\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\211\202\216\202\204\201D"; // Seal with the mark of Malty, the Disciple of Wind.
const char aAttackSingleEne_800B7404[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202v\202\211\202\216\202\204"; // Attack Single Enemy with Wind
const char aInflictsAFireBa_800B7440[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202e\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts a Fire-based attack on all enemies.
const char aAttackAllEnemie_800B749C[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202e\202\211\202\222\202\205"; // Attack All Enemies with Fire
const char aInflictsAFireBa_800B74D8[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202e\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts a Fire-based attack on a single enemy.
const char aSealWithTheMark_800B7538[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202`\202\207\202\216\202\211\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202e\202\211\202\222\202\205\201D"; // Seal with the mark of Agni, the Disciple of Fire.
const char aAttackSingleEne_800B759C[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202e\202\211\202\222\202\205"; // Attack Single Enemy with Fire
const char aInflictsAWaterB_800B75D8[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts a Water-based attack on all enemies.
const char aAttackAllEnemie_800B7634[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202v\202\201\202\224\202\205\202\222"; // Attack All Enemies with Water
const char aInflictsAWaterB_800B7670[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\201@\202v\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts a Water-based attack on a single enemy.
const char aSealWithTheMark_800B76D4[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202u\202\201\202\222\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222\201D"; // Seal with the mark of Vary, the Disciple of Water.
const char aAttackSingleEne_800B773C[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202v\202\201\202\224\202\205\202\222"; // Attack Single Enemy with Water
const char aInflictsAnEarth_800B777C[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\202\216\201@\202d\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Inflicts an Earth-based attack on all enemies.
const char aAttackAllEnemie_800B77DC[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\227\202\211\202\224\202\210\201@\202d\202\201\202\222\202\224\202\210"; // Attack All Enemies with Earth
const char aInflictsAnEarth_800B7818[] = "\202h\202\216\202\206\202\214\202\211\202\203\202\224\202\223\201@\202\201\202\216\201@\202d\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\217\202\216\201@\202\201\201@\202\223\202\211\202\216\202\207\202\214\202\205\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Inflicts an Earth-based attack on a single enemy.
const char aSealWithTheMark_800B787C[] = "\202r\202\205\202\201\202\214\201@\202\227\202\211\202\224\202\210\201@\202\224\202\210\202\205\201@\202\215\202\201\202\222\202\213\201@\202\217\202\206\201@\202t\202\222\202\226\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202d\202\201\202\222\202\224\202\210\201D"; // Seal with the mark of Urvy, the Disciple of Earth.
const char aAttackSingleEne_800B78E4[] = "\202`\202\224\202\224\202\201\202\203\202\213\201@\202r\202\211\202\216\202\207\202\214\202\205\201@\202d\202\216\202\205\202\215\202\231\201@\202\227\202\211\202\224\202\210\201@\202d\202\201\202\222\202\224\202\210"; // Attack Single Enemy with Earth
const char aChangesAreaProp_800B7924[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202v\202\211\202\216\202\204\201D"; // Changes area properties to the advantage of Wind.
const char aACharmBlessedBy_800B7988[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202l\202\201\202\214\202\224\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\211\202\216\202\204\201D"; // A charm blessed by Malty, the Disciple of Wind.
const char aChangesAreaProp_800B79E8[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202e\202\211\202\222\202\205\201D"; // Changes area properties to the advantage of Fire.
const char aACharmBlessedBy_800B7A4C[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202`\202\207\202\216\202\211\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202e\202\211\202\222\202\205\201D"; // A charm blessed by Agni, the Disciple of Fire.
const char aChangesAreaProp_800B7AAC[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222\201D"; // Changes area properties to the advantage of Water.
const char aACharmBlessedBy_800B7B14[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202u\202\201\202\222\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222\201D"; // A charm blessed by Vary, the Disciple of Water.
const char aChangesAreaProp_800B7B74[] = "\202b\202\210\202\201\202\216\202\207\202\205\202\223\201@\202\201\202\222\202\205\202\201\201@\202\220\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\201\202\204\202\226\202\201\202\216\202\224\202\201\202\207\202\205\201@\202\217\202\206\201@\202d\202\201\202\222\202\224\202\210\201D"; // Changes area properties to the advantage of Earth.
const char aACharmBlessedBy_800B7BDC[] = "\202`\201@\202\203\202\210\202\201\202\222\202\215\201@\202\202\202\214\202\205\202\223\202\223\202\205\202\204\201@\202\202\202\231\201@\202t\202\222\202\226\202\231\201C\201@\202\224\202\210\202\205\201@\202c\202\211\202\223\202\203\202\211\202\220\202\214\202\205\201@\202\217\202\206\201@\202d\202\201\202\222\202\224\202\210\201D"; // A charm blessed by Urvy, the Disciple of Earth.
const char aChangeAreaPrope_800B7C3C[] = "\202b\202\210\202\201\202\216\202\207\202\205\201@\202`\202\222\202\205\202\201\201@\202o\202\222\202\217\202\220\202\205\202\222\202\224\202\211\202\205\202\223"; // Change Area Properties
const char aAllAbnormalStat_800B7C6C[] = "\202\201\202\214\202\214\201@\202\201\202\202\202\216\202\217\202\222\202\215\202\201\202\214\201@\202\223\202\224\202\201\202\224\202\205\202\223\201C\201@\202\202\202\225\202\224\201@\202\227\202\211\202\214\202\214\201@\202\202\202\222\202\205\202\201\202\213\201@\202\211\202\216\201@\202\224\202\210\202\205\201@\202\220\202\222\202\217\202\203\202\205\202\223\202\223\201D"; // all abnormal states, but will break in the process.
const char aReflectsAllUncl_800B7CD4[] = "\202q\202\205\202\206\202\214\202\205\202\203\202\224\202\223\201@\202\201\202\214\202\214\201@\202\225\202\216\202\203\202\214\202\205\202\201\202\216\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\202\223\201D\201@\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224"; // Reflects all unclean elements. Protects against
const char aProtectionFromA_800B7D34[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\211\202\217\202\216\201@\202\206\202\222\202\217\202\215\201@\202`\202\214\202\214"; // Protection from All
const char aInstantlyCauses_800B7D5C[] = "\202h\202\216\202\223\202\224\202\201\202\216\202\224\202\214\202\231\201@\202\203\202\201\202\225\202\223\202\205\202\223\201@\202\204\202\205\202\201\202\224\202\210\201@\202\202\202\231\201@\202\223\202\224\202\217\202\220\202\220\202\211\202\216\202\207\201@\202\224\202\210\202\205\201@\202\210\202\205\202\201\202\222\202\224\201D"; // Instantly causes death by stopping the heart.
const char aReleasesADeathM_800B7DB8[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\201\201@\202\204\202\205\202\201\202\224\202\210\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases a death mist when broken.
const char aCauseDeath_800B7E00[] = "\202b\202\201\202\225\202\223\202\205\201@\202c\202\205\202\201\202\224\202\210"; // Cause Death
const char aCausesBodyHarde_800B7E18[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\202\202\217\202\204\202\231\201@\202\210\202\201\202\222\202\204\202\205\202\216\202\211\202\216\202\207\201@\202\223\202\224\202\201\202\222\202\224\202\211\202\216\202\207\201@\202\206\202\222\202\217\202\215\201@\202\224\202\210\202\205\201@\202\206\202\205\202\205\202\224\201D"; // Causes body hardening starting from the feet.
const char aReleasesAFleshT_800B7E74[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\201\201@\202\206\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases a flesh to stone mist when broken.
const char aFleshToStone_800B7ECC[] = "\202e\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202r\202\224\202\217\202\216\202\205"; // Flesh to Stone
const char aCausesADeepSlum_800B7EEC[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\201@\202\204\202\205\202\205\202\220\201@\202\223\202\214\202\225\202\215\202\202\202\205\202\222\201@\202\205\202\221\202\225\202\201\202\214\201@\202\224\202\217\201@\202\224\202\210\202\201\202\224\201@\202\217\202\206\201@\202\223\202\214\202\205\202\205\202\220\201@\202\223\202\220\202\217\202\222\202\205\202\223\201D"; // Causes a deep slumber equal to that of sleep spores.
const char aReleasesASleepM_800B7F58[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\201\201@\202\223\202\214\202\205\202\205\202\220\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases a sleep mist when broken.
const char aInduceSleep_800B7FA0[] = "\202h\202\216\202\204\202\225\202\203\202\205\201@\202r\202\214\202\205\202\205\202\220"; // Induce Sleep
const char aInstantlyCauses_800B7FBC[] = "\202h\202\216\202\223\202\224\202\201\202\216\202\224\202\214\202\231\201@\202\203\202\201\202\225\202\223\202\205\202\223\201@\202\205\202\230\202\203\202\222\202\225\202\203\202\211\202\201\202\224\202\211\202\216\202\207\201@\202\220\202\201\202\211\202\216\201D"; // Instantly causes excruciating pain.
const char aReleasesPoisonM_800B8004[] = "\202q\202\205\202\214\202\205\202\201\202\223\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201@\202\215\202\211\202\223\202\224\201@\202\227\202\210\202\205\202\216\201@\202\202\202\222\202\217\202\213\202\205\202\216\201D"; // Releases poison mist when broken.
const char aSprayPoison_800B8048[] = "\202r\202\220\202\222\202\201\202\231\201@\202o\202\217\202\211\202\223\202\217\202\216"; // Spray Poison
const char aInnerStrengthTo_800B8064[] = "\202\211\202\216\202\216\202\205\202\222\201@\202\223\202\224\202\222\202\205\202\216\202\207\202\224\202\210\201@\202\224\202\217\201@\202\224\202\225\202\222\202\216\201@\202\223\202\224\202\217\202\216\202\205\201@\202\202\202\201\202\203\202\213\201@\202\211\202\216\202\224\202\217\201@\202\206\202\214\202\205\202\223\202\210\201D"; // inner strength to turn stone back into flesh.
const char aPowderMadeFromS_800B80C0[] = "\202o\202\217\202\227\202\204\202\205\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\223\202\225\202\216\201|\202\204\202\222\202\211\202\205\202\204\201@\202\211\202\213\202\201\202\222\202\211\201@\202\210\202\205\202\222\202\202\201D\201@\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Powder made from sun-dried ikari herb. Increases
const char aStoneToFlesh_800B8124[] = "\202r\202\224\202\217\202\216\202\205\201@\202\224\202\217\201@\202e\202\214\202\205\202\223\202\210"; // Stone to Flesh
const char aSoothesTheSpiri_800B8144[] = "\202r\202\217\202\217\202\224\202\210\202\205\202\223\201@\202\224\202\210\202\205\201@\202\223\202\220\202\211\202\222\202\211\202\224\201@\202\201\202\216\202\204\201@\202\204\202\222\202\211\202\226\202\205\202\223\201@\202\217\202\225\202\224\201@\202\220\202\217\202\211\202\223\202\217\202\216\201D"; // Soothes the spirit and drives out poison.
const char aPowderedFormOfD_800B8198[] = "\202o\202\217\202\227\202\204\202\205\202\222\202\205\202\204\201@\202\206\202\217\202\222\202\215\201@\202\217\202\206\201@\202\204\202\222\202\211\202\205\202\204\201@\202\226\202\201\202\214\202\205\202\222\202\211\202\201\202\216\201@\202\222\202\217\202\217\202\224\201D"; // Powdered form of dried valerian root.
const char aPoisonAntidote_800B81E4[] = "\202o\202\217\202\211\202\223\202\217\202\216\201@\202`\202\216\202\224\202\211\202\204\202\217\202\224\202\205"; // Poison Antidote
const char aAdjustsTheVisce_800B8204[] = "\202`\202\204\202\212\202\225\202\223\202\224\202\223\201@\202\224\202\210\202\205\201@\202\226\202\211\202\223\202\203\202\205\202\222\202\201\201D"; // Adjusts the viscera.
const char aAlsoCalledTheIm_800B8230[] = "\202`\202\214\202\223\202\217\201@\202\203\202\201\202\214\202\214\202\205\202\204\201@\202\224\202\210\202\205\201@\202h\202\215\202\215\202\217\202\222\202\224\202\201\202\214\202\211\202\224\202\231\201@\202q\202\217\202\217\202\224\201D"; // Also called the Immortality Root.
const char aDriedRootOfAGre_800B8274[] = "\202c\202\222\202\211\202\205\202\204\201@\202\222\202\217\202\217\202\224\201@\202\217\202\206\201@\202\201\201@\202\207\202\222\202\205\202\201\202\224\201@\202\224\202\222\202\205\202\205\201@\202\206\202\222\202\217\202\215\201@\202\204\202\205\202\205\202\220\201@\202\211\202\216\201@\202\224\202\210\202\205\201@\202\206\202\217\202\222\202\205\202\223\202\224\201D"; // Dried root of a great tree from deep in the forest.
const char aTotalRestoratio_800B82DC[] = "\202s\202\217\202\224\202\201\202\214\201@\202q\202\205\202\223\202\224\202\217\202\222\202\201\202\224\202\211\202\217\202\216"; // Total Restoration
const char aRestoresAllMini_800B8300[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\202\214\202\214\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201D"; // Restores all Minion HP and Mana.
const char aSpecialLiquorMa_800B8344[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202\214\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Special liquor made from pickled Shab Minion.
const char aRestoresAGreatD_800B83A0[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\201@\202\207\202\222\202\205\202\201\202\224\201@\202\204\202\205\202\201\202\214\201@\202\217\202\206\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201D"; // Restores a great deal of Minion HP and Mana.
const char aExcellentLiquor_800B83FC[] = "\202d\202\230\202\203\202\205\202\214\202\214\202\205\202\216\202\224\201@\202\214\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Excellent liquor made from pickled Shab Minion.
const char aRestoresMinionH_800B845C[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201@\202\224\202\217\201@\202\201\201@\202\203\202\205\202\222\202\224\202\201\202\211\202\216\201@\202\204\202\205\202\207\202\222\202\205\202\205\201D"; // Restores Minion HP and Mana to a certain degree.
const char aFineLiquorMadeF_800B84C0[] = "\202e\202\211\202\216\202\205\201@\202\214\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Fine liquor made from pickled Shab Minion.
const char aRestoresSomeMin_800B8518[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201\201D"; // Restores some Minion HP and Mana.
const char aLiquorMadeFromP_800B855C[] = "\202k\202\211\202\221\202\225\202\217\202\222\201@\202\215\202\201\202\204\202\205\201@\202\206\202\222\202\217\202\215\201@\202\220\202\211\202\203\202\213\202\214\202\205\202\204\201@\202r\202\210\202\201\202\202\201@\202l\202\211\202\216\202\211\202\217\202\216\201D"; // Liquor made from pickled Shab Minion.
const char aRestoreMinionHP_800B85A8[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202g\202o\201@\202\201\202\216\202\204\201@\202l\202\201\202\216\202\201"; // Restore Minion HP and Mana
const char aStrengthensMini_800B85E0[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\223\202\220\202\211\202\222\202\211\202\224\201D"; // Strengthens minion's spirit.
const char aOilFromAPlantWi_800B861C[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\220\202\214\202\201\202\216\202\224\201@\202\227\202\211\202\224\202\210\201@\202\222\202\205\202\204\201@\202\206\202\214\202\217\202\227\202\205\202\222\202\223\201D"; // Oil from a plant with red flowers.
const char aIncreaseMinionM_800B8664[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202l\202\201\202\207\202\211\202\203\201@\202c\202\205\202\206\202\205\202\216\202\223\202\205"; // Increase Minion Magic Defense
const char aStrengthensMini_800B86A0[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\227\202\211\202\214\202\214\201D"; // Strengthens minion's will.
const char aOilFromTreeWith_800B86D8[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\224\202\222\202\205\202\205\201@\202\227\202\211\202\224\202\210\201@\202\220\202\225\202\222\202\220\202\214\202\205\201@\202\202\202\214\202\217\202\223\202\223\202\217\202\215\202\223\201D"; // Oil from tree with purple blossoms.
const char aIncreaseMinionM_800B8720[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202l\202\201\202\207\202\211\202\203\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Increase Minion Magic Attack
const char aHardensMinionSS_800B875C[] = "\202g\202\201\202\222\202\204\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\223\202\213\202\211\202\216\201D"; // Hardens minion's skin.
const char aOilFromAPlantWi_800B878C[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\220\202\214\202\201\202\216\202\224\201@\202\227\202\211\202\224\202\210\201@\202\227\202\210\202\211\202\224\202\205\201@\202\206\202\214\202\217\202\227\202\205\202\222\202\223\201D"; // Oil from a plant with white flowers.
const char aIncreaseMinionD_800B87D8[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202c\202\205\202\206\202\205\202\216\202\223\202\211\202\226\202\205\201@\202o\202\217\202\227\202\205\202\222"; // Increase Minion Defensive Power
const char aStrengthensMini_800B8818[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\214\202\205\202\207\202\223\201D"; // Strengthens minion's legs.
const char aOilFromAVeryPot_800B8850[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\226\202\205\202\222\202\231\201@\202\220\202\217\202\224\202\205\202\216\202\224\201@\202\220\202\214\202\201\202\216\202\224\201D"; // Oil from a very potent plant.
const char aIncreasesMinion_800B888C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202r\202\220\202\205\202\205\202\204"; // Increases Minion Speed
const char aSharpensMinionS_800B88BC[] = "\202r\202\210\202\201\202\222\202\220\202\205\202\216\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\201f\202\223\201@\202\203\202\214\202\201\202\227\202\223\201D"; // Sharpens minion's claws.
const char aOilFromATreeWit_800B88F0[] = "\202n\202\211\202\214\201@\202\206\202\222\202\217\202\215\201@\202\201\201@\202\224\202\222\202\205\202\205\201@\202\227\202\211\202\224\202\210\201@\202\223\202\210\202\201\202\222\202\220\201@\202\224\202\210\202\217\202\222\202\216\202\223\201D"; // Oil from a tree with sharp thorns.
const char aIncreaseMinionA_800B8938[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\202o\202\217\202\227\202\205\202\222"; // Increase Minion Attack Power
const char aStrengthensTheB_800B8974[] = "\202r\202\224\202\222\202\205\202\216\202\207\202\224\202\210\202\205\202\216\202\223\201@\202\224\202\210\202\205\201@\202\202\202\217\202\204\202\231\201@\202\201\202\216\202\204\201@\202\220\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\201\202\207\202\211\202\216\202\207\201D"; // Strengthens the body and protects against aging.
const char aANutPackingEner_800B89D8[] = "\202`\201@\202\216\202\225\202\224\201@\202\220\202\201\202\203\202\213\202\211\202\216\202\207\201@\202\205\202\216\202\205\202\222\202\207\202\231\201@\202\206\202\217\202\222\201@\202\223\202\220\202\222\202\217\202\225\202\224\202\211\202\216\202\207\201@\202\201\201@\202\216\202\205\202\227\201@\202\224\202\222\202\205\202\205\201D"; // A nut packing energy for sprouting a new tree.
const char aIncreaseMaxHeal_800B8A38[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\201@\202l\202\201\202\230\201@\202g\202\205\202\201\202\214\202\224\202\210"; // Increase Max Health
const char aBitterTasteThat_800B8A60[] = "\202\202\202\211\202\224\202\224\202\205\202\222\201@\202\224\202\201\202\223\202\224\202\205\201@\202\224\202\210\202\201\202\224\201@\202\205\202\214\202\225\202\204\202\205\202\223\201@\202\224\202\217\201@\202\211\202\224\202\223\201@\202\223\202\224\202\222\202\217\202\216\202\207\201@\202\203\202\225\202\222\202\211\202\216\202\207\201@\202\220\202\217\202\227\202\205\202\222\201D"; // bitter taste that eludes to its strong curing power.
const char aATypeOfMugwortW_800B8ACC[] = "\202`\201@\202\224\202\231\202\220\202\205\201@\202\217\202\206\201@\202\215\202\225\202\207\202\227\202\217\202\222\202\224\201@\202\227\202\211\202\224\202\210\201@\202\201\201@\202\222\202\205\202\201\202\214\202\214\202\231\201@\202\223\202\224\202\222\202\217\202\216\202\207\201@\202\223\202\215\202\205\202\214\202\214\201@\202\201\202\216\202\204"; // A type of mugwort with a really strong smell and
const char aCuresBleedingAn_800B8B30[] = "\202b\202\225\202\222\202\205\202\223\201@\202\202\202\214\202\205\202\205\202\204\202\211\202\216\202\207\201@\202\201\202\216\202\204\201@\202\222\202\205\202\204\202\225\202\203\202\205\202\223\201@\202\206\202\205\202\226\202\205\202\222\201D"; // Cures bleeding and reduces fever.
const char aSweeterSmelling_800B8B74[] = "\202\223\202\227\202\205\202\205\202\224\202\205\202\222\201@\202\223\202\215\202\205\202\214\202\214\202\211\202\216\202\207\201C\201@\202\201\202\216\202\204\201@\202\227\202\211\202\224\202\210\201@\202\206\202\225\202\232\202\232\202\211\202\205\202\222\201@\202\214\202\205\202\201\202\226\202\205\202\223\201D"; // sweeter smelling, and with fuzzier leaves.
const char aATypeOfMugwortB_800B8BCC[] = "\202`\201@\202\224\202\231\202\220\202\205\201@\202\217\202\206\201@\202\215\202\225\202\207\202\227\202\217\202\222\202\224\201C\201@\202\202\202\225\202\224\201@\202\223\202\215\202\201\202\214\202\214\202\205\202\222\201C"; // A type of mugwort, but smaller,
const char aGrindLeavesInto_800B8C0C[] = "\202f\202\222\202\211\202\216\202\204\201@\202\214\202\205\202\201\202\226\202\205\202\223\201@\202\211\202\216\202\224\202\217\201@\202\220\202\217\202\227\202\204\202\205\202\222\201@\202\201\202\216\202\204\201@\202\201\202\220\202\220\202\214\202\231\201@\202\224\202\217\201@\202\227\202\217\202\225\202\216\202\204\202\223\201D"; // Grind leaves into powder and apply to wounds.
const char aIncreasesHealth_800B8C68[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\210\202\205\202\201\202\214\202\224\202\210\201@\202\201\202\216\202\204\201@\202\223\202\214\202\217\202\227\202\223\201@\202\202\202\214\202\205\202\205\202\204\202\211\202\216\202\207\201D"; // Increases health and slows bleeding.
const char aGrowsInOpenArea_800B8CB4[] = "\202f\202\222\202\217\202\227\202\223\201@\202\211\202\216\201@\202\217\202\220\202\205\202\216\201@\202\201\202\222\202\205\202\201\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202\206\202\217\202\222\202\205\202\223\202\224\201D"; // Grows in open areas of the forest.
const char aRestoreHealth_800B8CFC[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202g\202\205\202\201\202\214\202\224\202\210"; // Restore Health
const char aEffectivenessOf_800B8D1C[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\205\202\201\202\222\202\224\202\210\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of earth for duration of battle.
const char aIncreasesWindAt_800B8D7C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\211\202\216\202\204\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases wind attack power and decreases
const char aEnhanceWind_800B8DD0[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\211\202\216\202\204"; // Enhance Wind
const char aEffectivenessOf_800B8DEC[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\201\202\224\202\205\202\222\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of water for duration of battle.
const char aIncreasesEarthA_800B8E4C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\205\202\201\202\222\202\224\202\210\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases earth attack power and decreases
const char aEnhanceEarth_800B8EA4[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202d\202\201\202\222\202\224\202\210"; // Enhance Earth
const char aEffectivenessOf_800B8EC0[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\206\202\211\202\222\202\205\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of fire for duration of battle.
const char aIncreasesWaterA_800B8F1C[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\227\202\201\202\224\202\205\202\222\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases water attack power and decreases
const char aEnhanceWater_800B8F74[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202v\202\201\202\224\202\205\202\222"; // Enhance Water
const char aEffectivenessOf_800B8F90[] = "\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\202\216\202\205\202\223\202\223\201@\202\217\202\206\201@\202\227\202\211\202\216\202\204\201@\202\206\202\217\202\222\201@\202\204\202\225\202\222\202\201\202\224\202\211\202\217\202\216\201@\202\217\202\206\201@\202\202\202\201\202\224\202\224\202\214\202\205\201D"; // effectiveness of wind for duration of battle.
const char aIncreasesFireAt_800B8FEC[] = "\202h\202\216\202\203\202\222\202\205\202\201\202\223\202\205\202\223\201@\202\206\202\211\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\201@\202\220\202\217\202\227\202\205\202\222\201@\202\201\202\216\202\204\201@\202\204\202\205\202\203\202\222\202\205\202\201\202\223\202\205\202\223"; // Increases fire attack power and decreases
const char aEnhanceFire_800B9040[] = "\202d\202\216\202\210\202\201\202\216\202\203\202\205\201@\202e\202\211\202\222\202\205"; // Enhance Fire
const char aCausesAnEnemyTo_800B905C[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\206\202\201\202\214\202\214\201@\202\204\202\205\202\201\202\204\201@\202\211\202\215\202\215\202\205\202\204\202\211\202\201\202\224\202\205\202\214\202\231\201D"; // Causes an enemy to fall dead immediately.
const char aDeath_800B90B0[] = "\202c\202\205\202\201\202\224\202\210"; // Death
const char aTurnsAnEnemyInt_800B90BC[] = "\202s\202\225\202\222\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\211\202\216\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Turns an enemy into stone.
const char aPutsAnEnemyToSl_800B90F4[] = "\202o\202\225\202\224\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Puts an enemy to sleep.
const char aSleep_800B9124[] = "\202r\202\214\202\205\202\205\202\220"; // Sleep
const char aPoisonsAnEnemy_800B9130[] = "\202o\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Poisons an enemy.
const char aPoison_800B9154[] = "\202o\202\217\202\211\202\223\202\217\202\216"; // Poison
const char aEndsOnceItProte_800B9164[] = "\202d\202\216\202\204\202\223\201@\202\217\202\216\202\203\202\205\201@\202\211\202\224\201@\202\220\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\203\202\201\202\223\202\224\202\205\202\222\201@\202\224\202\210\202\222\202\205\202\205\201@\202\224\202\211\202\215\202\205\202\223\201D"; // Ends once it protects caster three times.
const char aProtectsAgainst_800B91B8[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\223\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\220\202\217\202\211\202\223\202\217\202\216\201C\201@\202\223\202\214\202\205\202\205\202\220\201C\201@\202\201\202\216\202\204\201@\202\206\202\214\202\205\202\223\202\210\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Protects against poison, sleep, and flesh to stone.
const char aProtection_800B9220[] = "\202o\202\222\202\217\202\224\202\205\202\203\202\224\202\211\202\217\202\216"; // Protection
const char aCuresPoisonAndT_800B9238[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\223\202\224\202\217\202\216\202\205\201@\202\202\202\201\202\203\202\213\201@\202\224\202\217\201@\202\206\202\214\202\205\202\223\202\210\201D"; // Cures poison and turns stone back to flesh.
const char aReturnToNormal_800B9290[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202m\202\217\202\222\202\215\202\201\202\214"; // Return to Normal
const char aRestoresAllHP_800B92B4[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\201\202\214\202\214\201@\202g\202o\201D"; // Restores all HP.
const char aRestoreAllHP_800B92D8[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202`\202\214\202\214\201@\202g\202o"; // Restore All HP
const char aRestoresSomeHP_800B92F8[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202g\202o\201D"; // Restores some HP.
const char aRestoreHP_800B931C[] = "\202q\202\205\202\223\202\224\202\217\202\222\202\205\201@\202g\202o"; // Restore HP
const char aCuresPoison_800B9334[] = "\202b\202\225\202\222\202\205\202\223\201@\202\220\202\217\202\211\202\223\202\217\202\216\201D"; // Cures poison.
const char aCurePoison_800B9350[] = "\202b\202\225\202\222\202\205\201@\202o\202\217\202\211\202\223\202\217\202\216"; // Cure Poison
const char aAdvancedWindAtt_800B9368[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Wind Attack
const char aWindAttackAllEn_800B9394[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Wind Attack (All Enemies)
const char aHigherWindEleme_800B93C8[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\211\202\216\202\204\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher wind element ratio yields more damage.
const char aExtraDamageVsEa_800B9424[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202d\202\201\202\222\202\224\202\210"; // Extra damage vs. Earth
const char aWindAttackOneEn_800B9454[] = "\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Wind Attack (One Enemy)
const char aAdvancedEarthAt_800B9484[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Earth Attack
const char aEarthAttackAllE_800B94B0[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Earth Attack (All Enemies)
const char aHigherEarthElem_800B94E8[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\205\202\201\202\222\202\224\202\210\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher earth element ratio yields more damage.
const char aExtraDamageVsWa_800B9548[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202v\202\201\202\224\202\205\202\222"; // Extra damage vs. Water
const char aEarthAttackOneE_800B9578[] = "\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Earth Attack (One Enemy)
const char aAdvancedWaterAt_800B95AC[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Water Attack
const char aWaterAttackAllE_800B95D8[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Water Attack (All Enemies)
const char aHigherWaterElem_800B9610[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\227\202\201\202\224\202\205\202\222\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher water element ratio yields more damage.
const char aExtraDamageVsFi_800B9670[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202e\202\211\202\222\202\205"; // Extra damage vs. Fire
const char aWaterAttackOneE_800B969C[] = "\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Water Attack (One Enemy)
const char aAdvancedFireAtt_800B96D0[] = "\202`\202\204\202\226\202\201\202\216\202\203\202\205\202\204\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Advanced Fire Attack
const char aFireAttackAllEn_800B96FC[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Fire Attack (All Enemies)
const char aHigherFireEleme_800B9730[] = "\202g\202\211\202\207\202\210\202\205\202\222\201@\202\206\202\211\202\222\202\205\201@\202\205\202\214\202\205\202\215\202\205\202\216\202\224\201@\202\222\202\201\202\224\202\211\202\217\201@\202\231\202\211\202\205\202\214\202\204\202\223\201@\202\215\202\217\202\222\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201D"; // Higher fire element ratio yields more damage.
const char aExtraDamageVsAi_800B978C[] = "\202d\202\230\202\224\202\222\202\201\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\226\202\223\201D\201@\202`\202\211\202\222"; // Extra damage vs. Air
const char aFireAttackOneEn_800B97B8[] = "\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202n\202\216\202\205\201@\202d\202\216\202\205\202\215\202\231\201j"; // Fire Attack (One Enemy)
const char aMakesItEasierTo_800B97E8[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\227\202\211\202\216\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill winged enemies and
const char aSpecialAttackBr_800B9840[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202v\202\211\202\216\202\207\202\223\201j"; // Special Attack (Break Wings)
const char aSlightlyMoreDif_800B987C[] = "\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // slightly more difficult for them to score a hit.
const char aMakesItEasierTo_800B98E0[] = "\202l\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\205\202\201\202\223\202\211\202\205\202\222\201@\202\224\202\217\201@\202\213\202\211\202\214\202\214\201@\202\224\202\227\202\217\201|\202\214\202\205\202\207\202\207\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\216\202\204"; // Makes it easier to kill two-legged enemies and
const char aSpecialAttackBr_800B9940[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202a\202\222\202\205\202\201\202\213\201@\202k\202\205\202\207\202\223\201j"; // Special Attack (Break Legs)
const char aItMoreDifficult_800B9978[] = "\202\211\202\224\201@\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // it more difficult for them to score a hit.
const char aReducesAnEnemie_800B99D0[] = "\202q\202\205\202\204\202\225\202\203\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202g\202o\201@\202\224\202\217\201@\202P\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223"; // Reduces an enemies HP to 1 and makes
const char aSpecialAttackCr_800B9A1C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202b\202\222\202\211\202\224\202\211\202\203\202\201\202\214\201@\202g\202\211\202\224\201j"; // Special Attack (Critical Hit)
const char aBringsEnemiesTo_800B9A58[] = "\202a\202\222\202\211\202\216\202\207\202\223\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202\202\202\222\202\211\202\216\202\213\201@\202\217\202\206\201@\202\204\202\205\202\201\202\224\202\210\201D"; // Brings enemies to the brink of death.
const char aAttacksAllEnemi_800B9AA4[] = "\202`\202\224\202\224\202\201\202\203\202\213\202\223\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\201\202\224\201@\202\217\202\216\202\203\202\205\201D"; // Attacks all enemies at once.
const char aSpecialAttackAl_800B9AE0[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\214\202\214\201@\202d\202\216\202\205\202\215\202\211\202\205\202\223\201j"; // Special Attack (All Enemies)
const char aUsesItToRestore_800B9B1C[] = "\202\225\202\223\202\205\202\223\201@\202\211\202\224\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202l\202\201\202\216\202\201\201D"; // uses it to restore attacker's Mana.
const char aStealsSomeManaF_800B9B64[] = "\202r\202\224\202\205\202\201\202\214\202\223\201@\202\223\202\217\202\215\202\205\201@\202l\202\201\202\216\202\201\201@\202\206\202\222\202\217\202\215\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204"; // Steals some Mana from an enemy and
const char aSpecialAttackAb_800B9BAC[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Absorb Mana)
const char aAnEnemyToRestor_800B9BE8[] = "\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\222\202\205\202\223\202\224\202\217\202\222\202\205\201@\202\224\202\210\202\205\201@\202\201\202\224\202\224\202\201\202\203\202\213\202\205\202\222\201f\202\223\201@\202g\202o\201D"; // an enemy to restore the attacker's HP.
const char aTakesSomeOfTheD_800B9C38[] = "\202s\202\201\202\213\202\205\202\223\201@\202\223\202\217\202\215\202\205\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202\204\202\201\202\215\202\201\202\207\202\205\201@\202\211\202\216\202\206\202\214\202\211\202\203\202\224\202\205\202\204\201@\202\217\202\216"; // Takes some of the damage inflicted on
const char aSpecialAttackAb_800B9C84[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202`\202\202\202\223\202\217\202\222\202\202\201@\202g\202o\201j"; // Special Attack (Absorb HP)
const char aMoreDifficultFo_800B9CBC[] = "\202\215\202\217\202\222\202\205\201@\202\204\202\211\202\206\202\206\202\211\202\203\202\225\202\214\202\224\201@\202\206\202\217\202\222\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\203\202\217\202\222\202\205\201@\202\201\201@\202\210\202\211\202\224\201D"; // more difficult for them to score a hit.
const char aCausesAnEnemyTo_800B9D0C[] = "\202b\202\201\202\225\202\223\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\224\202\217\201@\202\214\202\217\202\223\202\205\201@\202l\202\201\202\216\202\201\201@\202\201\202\216\202\204\201@\202\215\202\201\202\213\202\205\202\223\201@\202\211\202\224\201@\202\223\202\214\202\211\202\207\202\210\202\224\202\214\202\231"; // Causes an enemy to lose Mana and makes it slightly
const char aSpecialAttackDe_800B9D74[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202`\202\224\202\224\202\201\202\203\202\213\201@\201i\202c\202\205\202\223\202\224\202\222\202\217\202\231\201@\202l\202\201\202\216\202\201\201j"; // Special Attack (Destroy Mana)
const char aPhysicallyDamag_800B9DB0[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\224\202\225\202\222\202\216\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\224\202\217\202\216\202\205\201D"; // Physically damages an enemy and turns them to stone.
const char aSpecialFleshToS_800B9E1C[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\214\202\205\202\223\202\210\201|\202\224\202\217\201|\202r\202\224\202\217\202\216\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Flesh-to-Stone Attack
const char aPhysicallyDamag_800B9E58[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201@\202\201\202\216\202\204\201@\202\220\202\225\202\224\202\223\201@\202\224\202\210\202\205\202\215\201@\202\224\202\217\201@\202\223\202\214\202\205\202\205\202\220\201D"; // Physically damages an enemy and puts them to sleep.
const char aSpecialSleepAtt_800B9EC0[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202r\202\214\202\205\202\205\202\220\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Sleep Attack
const char aPhysicallyDamag_800B9EEC[] = "\202o\202\210\202\231\202\223\202\211\202\203\202\201\202\214\202\214\202\231\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\223\201@\202\201\202\216\202\204\201@\202\220\202\217\202\211\202\223\202\217\202\216\202\223\201@\202\201\202\216\201@\202\205\202\216\202\205\202\215\202\231\201D"; // Physically damages and poisons an enemy.
const char aSpecialPoisonAt_800B9F40[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202o\202\217\202\211\202\223\202\217\202\216\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Poison Attack
const char aVeryEffectiveAg_800B9F6C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\205\202\201\202\222\202\224\202\210\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against earth-based enemies.
const char aSpecialWindAtta_800B9FC4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\211\202\216\202\204\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Wind Attack
const char aVeryEffectiveAg_800B9FEC[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\211\202\216\202\204\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against wind-based enemies.
const char aSpecialFireAtta_800BA044[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202e\202\211\202\222\202\205\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Fire Attack
const char aVeryEffectiveAg_800BA06C[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\206\202\211\202\222\202\205\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against fire-based enemies.
const char aSpecialWaterAtt_800BA0C4[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202v\202\201\202\224\202\205\202\222\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Water Attack
const char aVeryEffectiveAg_800BA0F0[] = "\202u\202\205\202\222\202\231\201@\202\205\202\206\202\206\202\205\202\203\202\224\202\211\202\226\202\205\201@\202\201\202\207\202\201\202\211\202\216\202\223\202\224\201@\202\227\202\201\202\224\202\205\202\222\201|\202\202\202\201\202\223\202\205\202\204\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201D"; // Very effective against water-based enemies.
const char aSpecialEarthAtt_800BA148[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202d\202\201\202\222\202\224\202\210\201@\202`\202\224\202\224\202\201\202\203\202\213"; // Special Earth Attack
const int dword_800BA174[2] = { 0 };

void BossAi04_800C59A0(BatTask* t)
{
    unsigned char k = aiCounter_800C8B30 % 3;
    switch (k)
    {
    case 0:
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = 3;
        t->cmd_8->targets_C = t->targetMask_18;
        break;
    case 1:
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = 2;
        t->cmd_8->targets_C = t->targetMask_18;
        break;
    case 2:
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = 1;
        t->cmd_8->targets_C = t->targetMask_18;
        break;
    }
    aiCounter_800C8B30++;
}

void BossAi02_800C5A7C(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
        }
        else
        {
            t->cmd_8->kind_0 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
        }
    }
    else if (t->slot_C == 1)
    {
        unsigned char k = aiCounter_800C8B30 % 3;
        switch (k)
        {
        case 0:
            t->cmd_8->kind_0 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        case 1:
            t->cmd_8->kind_0 = 6;
            t->cmd_8->arg_4 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        case 2:
            t->cmd_8->kind_0 = 1;
            t->cmd_8->arg_4 = 2;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        }
        aiCounter_800C8B30++;
    }
}

void BossAi03_800C5BC0(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
        }
        else
        {
            t->cmd_8->kind_0 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
        }
    }
    else if (t->slot_C == 1)
    {
        unsigned char k = aiCounter_800C8B30 % 3;
        switch (k)
        {
        case 0:
            t->cmd_8->kind_0 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        case 1:
            t->cmd_8->kind_0 = 6;
            t->cmd_8->arg_4 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        case 2:
            t->cmd_8->kind_0 = 1;
            t->cmd_8->arg_4 = 2;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        }
        aiCounter_800C8B30++;
    }
}

void BossAi0D_800C5D04(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
        }
        else
        {
            t->cmd_8->kind_0 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
        }
    }
    else
    {
        unsigned char* p = &aiCounter_800C8B30;
        if (p[1])
        {
            t->cmd_8->kind_0 = 6;
            t->cmd_8->arg_4 = 2;
            t->cmd_8->targets_C = t->targetMask_18;
            p[1] = 0;
        }
        else
        {
            switch (rand() % 3)
            {
            case 0:
                t->cmd_8->kind_0 = 1;
                t->cmd_8->arg_4 = 0x1B;
                t->cmd_8->targets_C = t->targetMask_18;
                SetHitVariant_80018430(2);
                break;
            case 1:
                t->cmd_8->kind_0 = 6;
                t->cmd_8->arg_4 = 1;
                t->cmd_8->targets_C = t->targetMask_18;
                break;
            default:
                t->cmd_8->kind_0 = 6;
                t->cmd_8->arg_4 = 0;
                t->cmd_8->targets_C = t->cmd_8->mask_8;
                (&aiCounter_800C8B30)[1] = 1;
                break;
            }
        }
    }
    aiCounter_800C8B30++;
}

void BossAi0B_800C5EB8(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
        }
        else
        {
            t->cmd_8->kind_0 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
        }
    }
    else
    {
        switch (rand() % 3)
        {
        case 0:
            if (GetMp_800334F0(t->target_14))
            {
                t->cmd_8->kind_0 = 6;
                t->cmd_8->arg_4 = 1;
                t->cmd_8->targets_C = t->targetMask_18;
                break;
            }
        case 1:
            t->cmd_8->kind_0 = 1;
            t->cmd_8->arg_4 = 0x19;
            t->cmd_8->targets_C = t->targetMask_18;
            SetHitVariant_80018430(0);
            break;
        case 2:
            t->cmd_8->kind_0 = 6;
            t->cmd_8->arg_4 = 3;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        }
    }
    aiCounter_800C8B30++;
}

#if 0 // Not matched: one spot: in the 'f8[3] = f8[2]; aiCounter_800C8B30 = 0' arm the byte store is scheduled above the word store (original keeps it in the j delay slot), which also swaps v0/v1
void BossAi0C_800C6038(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
        }
        else
        {
            t->cmd_8->kind_0 = 0;
            t->cmd_8->targets_C = t->targetMask_18;
        }
    }
    else if (aiCounter_800C8B30 != 0 && TargetHasStatus_800C6EC8(t, 2))
    {
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = 0;
        t->cmd_8->targets_C = t->cmd_8->mask_8;
        aiCounter_800C8B30 = 0;
    }
    else
    {
        aiCounter_800C8B30++;
        switch (rand() % 3)
        {
        case 0:
            t->cmd_8->kind_0 = 1;
            t->cmd_8->arg_4 = 0x1C;
            t->cmd_8->targets_C = t->targetMask_18;
            SetHitVariant_80018430(1);
            break;
        case 1:
            t->cmd_8->kind_0 = 6;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        case 2:
            t->cmd_8->kind_0 = 6;
            t->cmd_8->arg_4 = 3;
            t->cmd_8->targets_C = t->targetMask_18;
            break;
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, BossAi0C_800C6038);

void BossAi0E_800C61FC(BatTask* t)
{
    unsigned short f;
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
        }
        else
        {
            t->self_10->st_0.elementMask_42 = 0;
            SetElementAffinity_800C66B4((unsigned char*)t->self_10, 0xC);
            t->cmd_8->kind_0 = 6;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = t->targetMask_18;
        }
    }
    else if ((GetAreaElement_800BC868() == 0 && !((unsigned short)t->self_10->st_0.elementMask_42 & 1)) || (aiCounter_800C8B30 >= 3 && GetAreaElement_800BC868() == 0))
    {
        AiSetCommand_800C6AFC(t, 6, 2);
        t->skills_4->slot[2].id_1 = 0x25;
        t->self_10->st_0.elementMask_42 = 8;
        SetHitVariant_80018430(3);
        SetElementAffinity_800C66B4((unsigned char*)t->self_10, 2);
        aiCounter_800C8B30 = 0;
    }
    else if ((GetAreaElement_800BC868() == 1 && !((unsigned short)t->self_10->st_0.elementMask_42 & 2)) || (aiCounter_800C8B30 >= 3 && GetAreaElement_800BC868() == 1))
    {
        AiSetCommand_800C6AFC(t, 6, 2);
        t->skills_4->slot[2].id_1 = 0x22;
        t->self_10->st_0.elementMask_42 = 1;
        SetHitVariant_80018430(0);
        SetElementAffinity_800C66B4((unsigned char*)t->self_10, 3);
        aiCounter_800C8B30 = 0;
    }
    else if ((GetAreaElement_800BC868() == 2 && !((unsigned short)t->self_10->st_0.elementMask_42 & 4)) || (aiCounter_800C8B30 >= 3 && GetAreaElement_800BC868() == 2))
    {
        AiSetCommand_800C6AFC(t, 6, 2);
        t->skills_4->slot[2].id_1 = 0x23;
        t->self_10->st_0.elementMask_42 = 2;
        SetHitVariant_80018430(1);
        SetElementAffinity_800C66B4((unsigned char*)t->self_10, 0);
        aiCounter_800C8B30 = 0;
    }
    else if ((GetAreaElement_800BC868() == 3 && !((unsigned short)t->self_10->st_0.elementMask_42 & 8)) || (aiCounter_800C8B30 >= 4 && GetAreaElement_800BC868() == 3) || GetAreaElement_800BC868() == -1)
    {
        AiSetCommand_800C6AFC(t, 6, 2);
        t->skills_4->slot[2].id_1 = 0x24;
        t->self_10->st_0.elementMask_42 = 4;
        SetHitVariant_80018430(2);
        SetElementAffinity_800C66B4((unsigned char*)t->self_10, 1);
        aiCounter_800C8B30 = 0;
    }
    else
    {
        f = (unsigned short)t->self_10->st_0.elementMask_42;
        if (f & 8)
        {
            if (aiCounter_800C8B30 == 1)
            {
                AiSetCommandOnSelf_800C6B24(t, 1, 0x1D);
            }
            else
            {
                AiSetCommand_800C6AFC(t, 6, 0);
            }
        }
        else if (f & 1)
        {
            if (rand() & 1)
            {
                AiSetCommand_800C6AFC(t, 6, 1);
                t->skills_4->slot[1].id_1 = 4;
            }
            else
            {
                AiSetCommand_800C6AFC(t, 1, 0x19);
                SetHitVariant_80018430(0);
            }
        }
        else if (f & 2)
        {
            if (rand() % 3 != 0)
            {
                AiSetCommand_800C6AFC(t, 1, 0x1C);
                SetHitVariant_80018430(1);
            }
            else
            {
                AiSetCommand_800C6AFC(t, 6, 1);
                t->skills_4->slot[1].id_1 = 5;
            }
        }
        else if (f & 4)
        {
            if (rand() % 3 != 0)
            {
                AiSetCommand_800C6AFC(t, 6, 1);
                t->skills_4->slot[1].id_1 = 2;
            }
            else
            {
                AiSetCommand_800C6AFC(t, 1, 0x1B);
                SetHitVariant_80018430(2);
            }
        }
    }
    aiCounter_800C8B30 += ((rand() & 3) >> 1) + 1;
}

void SetElementAffinity_800C66B4(unsigned char* buf, unsigned int b)
{
    int i;
    unsigned int c = 0xC;
    unsigned char* p;
    if (b == c)
    {
        c = 0x30;
    }
    for (i = 3, p = buf + 3; i >= 0; i--, p--)
    {
        p[0x20] = c;
    }
    if (b < 0xC)
    {
        (buf + b)[0x20] = 0x18;
    }
}

void BossAi0F_800C66F4(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
            return;
        }
    }
    else if (t->slot_C == 1)
    {
        if ((rand() & 1) || ((unsigned short)t->target_14->elementMask_42 & 2))
        {
            goto act;
        }
        else
        {
            short x = GetHp_800334D8(&t->self_10->st_0);
            short y = GetMaxHp_800334CC(&t->self_10->st_0);
            if (x < (short)(y / 3))
            {
            act:
                if (AiUseSkill_800C6A8C(t))
                {
                    return;
                }
            }
        }
    }
    else
    {
        return;
    }
    t->cmd_8->kind_0 = 0;
    t->cmd_8->targets_C = t->targetMask_18;
}

void BossAi10_800C6824(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
            return;
        }
    }
    else if (t->slot_C == 1)
    {
        short x = GetHp_800334D8(&t->self_10->st_0);
        short y = GetMaxHp_800334CC(&t->self_10->st_0);
        if (x < y / 4)
        {
            if (AiUseSkill_800C6A8C(t))
            {
                return;
            }
        }
        if (AiCastMagic_800C6BD0(t, 9))
        {
            return;
        }
    }
    else
    {
        return;
    }
    t->cmd_8->kind_0 = 0;
    t->cmd_8->targets_C = t->targetMask_18;
}

void BossAi11_800C6928(BatTask* t)
{
    if (t->slot_C == 0)
    {
        if (aiAllyCalled_800C8B34 == 0)
        {
            t->cmd_8->mask_8 = 0x10;
            t->cmd_8->kind_0 = 0x15;
            aiAllyCalled_800C8B34 = 1;
            t->cmd_8->arg_4 = 1;
            t->cmd_8->targets_C = 2;
            return;
        }
    }
    else if (t->slot_C == 1)
    {
        short x = GetHp_800334D8(&t->self_10->st_0);
        short y = GetMaxHp_800334CC(&t->self_10->st_0);
        if (x < y / 2)
        {
            if (AiUseSkill_800C6A8C(t))
            {
                return;
            }
        }
        if (rand() & 1)
        {
            if (AiCastMagic_800C6BD0(t, 6))
            {
                return;
            }
        }
    }
    else
    {
        return;
    }
    t->cmd_8->kind_0 = 0;
    t->cmd_8->targets_C = t->targetMask_18;
}

void EnemyAiFirstSkill_800C6A40(BatTask* t)
{
    t->cmd_8->kind_0 = 6;
    t->cmd_8->arg_4 = 0;
    t->cmd_8->targets_C = t->targetMask_18;
}

int AiAttack_800C6A68(BatTask* t)
{
    t->cmd_8->kind_0 = 0;
    t->cmd_8->targets_C = t->targetMask_18;
    return 1;
}

int AiUseSkill_800C6A8C(BatTask* t)
{
    int r = FindUsableSkill_800C6D6C(t->skills_4, t->self_10);
    if (r != 5)
    {
        t->cmd_8->kind_0 = 6;
        t->cmd_8->arg_4 = r;
        t->cmd_8->targets_C = t->targetMask_18;
        return 1;
    }
    return 0;
}

void AiSetCommand_800C6AFC(BatTask* t, int kind, int arg)
{
    t->cmd_8->kind_0 = kind;
    t->cmd_8->arg_4 = arg;
    t->cmd_8->targets_C = t->targetMask_18;
}

void AiSetCommandOnSelf_800C6B24(BatTask* t, int kind, int arg)
{
    BatCmd_a* p;
    t->cmd_8->kind_0 = kind;
    t->cmd_8->arg_4 = arg;
    p = t->cmd_8;
    p->targets_C = p->mask_8;
}

int AiCastMagicOnAlly_800C6B50(BatTask* t, int magic, int ally)
{
    if (CanCastMagic_800C6CFC(magic, t->magicBits_0, t->self_10) != 0)
    {
        t->cmd_8->kind_0 = 1;
        t->cmd_8->arg_4 = magic;
        t->cmd_8->targets_C = 1 << (ally + 4);
        return 1;
    }
    return 0;
}

int AiCastMagic_800C6BD0(BatTask* t, int magic)
{
    if (CanCastMagic_800C6CFC(magic, t->magicBits_0, t->self_10) != 0)
    {
        t->cmd_8->kind_0 = 1;
        t->cmd_8->arg_4 = magic;
        t->cmd_8->targets_C = t->targetMask_18;
        return 1;
    }
    return 0;
}

int AiDefend_800C6C44(BatTask* t)
{
    t->cmd_8->kind_0 = 0x12;
    return 1;
}

int AiFlee_800C6C58(BatTask* t)
{
    t->cmd_8->kind_0 = 7;
    t->cmd_8->targets_C = t->targetMask_18;
    return 1;
}

void GetEnemyStatuses_800C6C7C(UnitStatus** out)
{
    int bits = sub_800A248C();
    int i;
    for (i = 0; i < 3; i++)
    {
        int m = 1 << (i + 4);
        if (bits & m)
        {
            out[i] = sub_800A2B60(i);
        }
        else
        {
            out[i] = 0;
        }
    }
}

int CanCastMagic_800C6CFC(unsigned int magic, unsigned int* magicBits, UnitStats* self)
{
    if (TestMagicBit_8001AE2C(magicBits, magic) != 0)
    {
        if (magicData_8007C438[magic].field_4 <= self->st_0.mp_C.cur_0)
        {
            return 1;
        }
    }
    return 0;
}

int FindUsableSkill_800C6D6C(UnitSkills* skills, UnitStats* self)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (skills->slot[i].flags_0 & 1)
        {
            short h = self->st_0.mp_C.cur_0;
            if (!(h < GetSkillMpCost_80031A04(skills, i)))
            {
                return i;
            }
        }
    }
    return i;
}

int AiHealWeakAlly_800C6DF8(BatTask* t, int magic)
{
    UnitStatus* allies[3];
    int i;
    GetEnemyStatuses_800C6C7C(allies);
    for (i = 0; i < 3; i++)
    {
        if (allies[i])
        {
            short x = GetHp_800334D8(allies[i]);
            short y = GetMaxHp_800334CC(allies[i]);
            if (x <= y / 4)
            {
                if (AiCastMagicOnAlly_800C6B50(t, magic, i))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int TargetHasStatus_800C6EC8(BatTask* t, int m)
{
    return (t->target_14->status_0 & m) != 0;
}

int IsTargetWeakToMagic_800C6EE4(BatTask* t)
{
    return t->target_14->stats_2C.cur_0[1] > t->target_14->stats_2C.cur_0[3];
}

int StartBattleMenu_800C6EFC()
{
    int i;
    int m;
    int n = 0;
    EventEntry* e = AllocEventEntry_80043AF8(battleMenuTask_8008D468);
    if (e)
    {
        e->cb_8 = (EventEntryFn)BattleMenuTask_800C8A08;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        if (actingUnit_800C9C7C == 0)
        {
            menuForMinion_800C9E49 = 0;
        }
        else
        {
            menuForMinion_800C9E49 = 1;
        }
        menuCommand_800C9E58.kind_0 = 0;
        menuCommand_800C9E58.arg_4 = 0;
        menuCommand_800C9E58.targets_C = 0;
        menuCommand_800C9E58.mask_8 = 1 << actingUnit_800C9C7C;
        partyMinionMask_800C9E78 = GetPartyMinionMask_800C0A9C();
        partyMinionCount_800C9E4B = GetCapturedMinionsFromBitfield_8003BA58(partyMinionMask_800C9E78);
        enemyMask_800C9E4C = sub_800A248C();
        enemyCount_800C9E4A = GetCapturedMinionsFromBitfield_8003BA58(enemyMask_800C9E4C);
        for (i = 0; i < 3; i++)
        {
            m = 1 << (i + 4);
            if (enemyMask_800C9E4C & m)
            {
                enemyUnits_800C9E80[n] = i + 4;
                enemyBits_800C9E72[n] = m;
                n++;
            }
        }
        menuPage_800C9E50 = 0;
        prevMenuPage_800C9E40 = 0;
        menuState_800C9E48 = 0;
        targetFlags_800C9E68 = 4;
        dword_800C9E70 = 0;
        InitMenuCursors_800C7088();
        SelectMenuWindows_800C71A0();
        DisableMenuCommands_800C71C8();
        cameraFocus_800C9E38 = -1;
    }
    return (int)e;
}

void InitMenuCursors_800C7088()
{
    if (menuForMinion_800C9E49 == 0)
    {
        if (sub_800AD308(0) + 1 >= 5)
        {
            itemMenu_800C9308->count_4 = sub_800AD308(0) + 1;
        }
        itemMenu_800C9308->cursor_8 = 0;
        commandMenu_800C92D8->count_4 = 6;
        commandMenu_800C92D8->cursor_8 = 0;
    }
    else
    {
        if (CountMagicBits_8001AE54(GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1)) >= 5)
        {
            magicMenu_800C92F0->count_4 = CountMagicBits_8001AE54(GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1));
        }
        magicMenu_800C92F0->cursor_8 = 0;
        skillMenu_800C92E4->cursor_8 = 0;
        commandMenu_800C92D8->count_4 = 5;
        commandMenu_800C92D8->cursor_8 = 0;
    }
    if ((unsigned char)savedEnemyCursor_800C9D56 > enemyCount_800C9E4A - 1)
    {
        savedEnemyCursor_800C9D56 = 0;
    }
    enemyTargetMenu_800C9314->f0 = enemyCount_800C9E4A;
    enemyTargetMenu_800C9314->count_4 = enemyCount_800C9E4A;
    enemyTargetMenu_800C9314->cursor_8 = (unsigned char)savedEnemyCursor_800C9D56;
}

void SelectMenuWindows_800C71A0()
{
    menuWindows_800C9630.windows_10 = menuWindowSets_800C9628[menuForMinion_800C9E49];
}

void DisableMenuCommands_800C71C8()
{
    if (menuForMinion_800C9E49 == 0)
    {
        if (GetPartyMinionMask_800C0A9C() == 0)
        {
            levantMenuItems_800C93A4[2].data_4 = msgNoDivineMinions_800C9378;
            winSummon_800C946C[0].flags_0 |= 2;
        }
        if (CanCapture_800C7334() == 0)
        {
            levantMenuItems_800C93A4[3].data_4 = msgCannotCapture_800C9384;
            winCapture_800C94A4[0].flags_0 |= 2;
        }
        else if (sub_800AD8E4() == 0)
        {
            levantMenuItems_800C93A4[3].data_4 = msgNoEmptyCocoons_800C9388;
            winCapture_800C94A4[0].flags_0 |= 2;
        }
        if (CanFlee_800C72B8() == 0)
        {
            levantMenuItems_800C93A4[5].data_4 = msgCannotEscape_800C938C;
            winFlee_800C9514[0].flags_0 |= 2;
        }
        menuItems_800C9E6C = levantMenuItems_800C93A4;
    }
    else
    {
        menuItems_800C9E6C = minionMenuItems_800C93D4;
    }
}

int CanFlee_800C72B8()
{
    int i;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = enemyMask_800C9E4C & (1 << (i + 4));
        if (m != 0)
        {
            if (sub_800A28FC(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int CanCapture_800C7334()
{
    int i;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = enemyMask_800C9E4C & (1 << (i + 4));
        if (m != 0)
        {
            if (IsUncapturableSpecies_800BF980(sub_800A2BE4(i)) == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

BatMenu_a* GetPageCursor_800C73B8(unsigned char page)
{
    if (page == 4)
    {
        if (targetFlags_800C9E68 & 1)
        {
            return allTargetsMenu_800C932C;
        }
        if (targetFlags_800C9E68 & 4)
        {
            return enemyTargetMenu_800C9314;
        }
        return targetMenu_800C9320;
    }
    return pageMenus_800C9338[page];
}

void HighlightTargetWindows_800C7424(unsigned char page)
{
    ResetWindowHighlights_800BFC10();
    if (page == 4)
    {
        if (targetFlags_800C9E68 & 1)
        {
            if (targetFlags_800C9E68 & 4)
            {
                enemyWindowsHighlight_800C9DFC = 1;
                enemyHighlightTimes_800C9174[0] = GetTime30Hz_8002C64C();
                enemyHighlightTimes_800C9174[1] = GetTime30Hz_8002C64C();
                enemyHighlightTimes_800C9174[2] = GetTime30Hz_8002C64C();
            }
            if (targetFlags_800C9E68 & 2)
            {
                actorWindowHighlight_800C9DFD = 1;
                actorHighlightTime_800C9170 = GetTime30Hz_8002C64C();
            }
        }
        else if (targetFlags_800C9E68 & 4)
        {
            short i;
            enemyWindowsHighlight_800C9DFC = 1;
            i = GetMenuCursorIndex_8003DA54(enemyTargetMenu_800C9314);
            enemyHighlightTimes_800C9174[enemyUnits_800C9E80[i] - 4] = GetTime30Hz_8002C64C();
        }
        else
        {
            actorWindowHighlight_800C9DFD = 1;
            actorHighlightTime_800C9170 = GetTime30Hz_8002C64C();
        }
    }
}

int IsMenuSelectionValid_800C7530()
{
    struct_minion_ref q;
    BatTgtQ_a b;
    short idx;
    int* p;
    idx = GetMenuCursorIndex_8003DA54(pageCursor_800C9E44);
    q.cursor_0 = pageCursor_800C9E44->cursor_8;
    q.scroll_2 = pageCursor_800C9E44->scroll_A;
    q.field_A = 0;
    menuErrorText_800C9E7C = 0;
    switch (menuPage_800C9E50)
    {
    case 0:
        p = menuItems_800C9E6C[idx].data_4;
        if (p == 0)
        {
            return 1;
        }
        menuErrorText_800C9E7C = *p;
        return 0;
    case 1:
        switch (CheckItemUsable_80033AFC(&q))
        {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
        case 4:
            menuErrorText_800C9E7C = msgCannotUseHere_800C93A0;
            return 0;
        case 3:
        case 5:
        case 6:
        case 7:
        default:
            return 1;
        }
    case 2:
        q.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        switch (CheckSkillUsable_80033C98(&q))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        default:
            return 1;
        case 5:
            menuErrorText_800C9E7C = msgNotEnoughMana_800C9380;
            return 0;
        case 7:
            return 0;
        }
    case 3:
        q.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        switch (CheckMagicCastable_80033C08(&q))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        default:
            return 1;
        case 5:
            menuErrorText_800C9E7C = msgNotEnoughMana_800C9380;
            return 0;
        case 6:
            return 0;
        }
    case 4:
        b.f0 = menuCommand_800C9E58.arg_4;
        b.f2 = actingUnit_800C9C7C;
        b.f4 = menuTarget_800C9E54;
        b.f6 = 0;
        if (GetSelectedCommand_800C78D0() == 4)
        {
            switch (CheckItemOnTarget_80033DF4(&b))
            {
            case 0:
                return 1;
            case 1:
                menuErrorText_800C9E7C = msgDivineMinionsCannot_800C939C;
                return 0;
            case 2:
                menuErrorText_800C9E7C = msgItemForDivineMinions_800C9398;
                return 0;
            case 3:
                menuErrorText_800C9E7C = msgNoNeedToUseItem_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 6)
        {
            switch (((int (*)(BatTgtQ_a*))CheckUsableStub_80034124)(&b))
            {
            case 0:
                return 1;
            case 1:
                menuErrorText_800C9E7C = msgDivineMinionsCannot_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                menuErrorText_800C9E7C = msgNoNeedToUseItem_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            switch (CheckMagicUsable_80034068(&b))
            {
            case 0:
                return 1;
            case 1:
                menuErrorText_800C9E7C = msgDivineMinionsCannot_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                menuErrorText_800C9E7C = msgNoNeedToUseItem_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 2 || GetSelectedCommand_800C78D0() == 8)
        {
            if (HasStatusFlag_80033548(GetUnitStatus_80014390((unsigned char)menuTarget_800C9E54), 0x400) == 0)
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
        menuErrorText_800C9E7C = msgCannotSummon_800C937C;
        return 0;
    case 5:
    default:
        return 1;
    }
}

INCLUDE_OVERLAY_ASM(battle, dword_800BA238);

unsigned char GetSelectedCommand_800C78D0()
{
    return commandByCursor_800C9648[menuForMinion_800C9E49 + (short)GetMenuCursorIndex_8003DA54(commandMenu_800C92D8) * 2];
}

#if 0 // Not matched: b and r swap registers (v1/a0); tried declaration order, int b, re-reading the global, early returns
int GetSelectedTargets_800C791C()
{
    unsigned char b = targetFlags_800C9E68;
    int r = 0;
    if (b & 1)
    {
        if (b & 4)
        {
            r = enemyMask_800C9E4C;
        }
        if (b & 2)
        {
            r |= 1;
            r |= partyMinionMask_800C9E78;
        }
    }
    else if (b & 4)
    {
        short i = GetMenuCursorIndex_8003DA54(enemyTargetMenu_800C9314);
        r = enemyBits_800C9E72[i];
    }
    else
    {
        r = 1 << menuTarget_800C9E54;
    }
    return r;
}
#endif

INCLUDE_OVERLAY_ASM(battle, GetSelectedTargets_800C791C);

int GetSelectedItem_800C79B8()
{
    return sub_800AD288((short)GetMenuCursorIndex_8003DA54(itemMenu_800C9308), 0);
}

int GetSelectedSkill_800C79EC()
{
    return MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4));
}

int GetSelectedMagic_800C7A1C()
{
    unsigned int* h = GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1);
    return FindNthMagicBit_8001AEC0(h, (short)GetMenuCursorIndex_8003DA54(magicMenu_800C92F0));
}

void AdvanceMenuPage_800C7A6C()
{
    int h;
    char* m;
    prevMenuPage_800C9E40 = menuPage_800C9E50;
    switch (menuPage_800C9E50)
    {
    case 0:
        targetFlags_800C9E68 = commandTargetFlags_800C9660[GetSelectedCommand_800C78D0()];
        menuPage_800C9E50 = commandNextPage_800C9654[GetSelectedCommand_800C78D0()];
        menuCommand_800C9E58.kind_0 = commandKinds_800C96A4[GetSelectedCommand_800C78D0()];
        break;
    case 1:
        targetFlags_800C9E68 = GetItemTargetFlags_8001CE8C(GetSelectedItem_800C79B8());
        menuPage_800C9E50 = 4;
        menuCommand_800C9E58.arg_4 = GetSelectedItem_800C79B8();
        break;
    case 2:
        h = GetUnitSkills_80031B30(actingUnit_800C9C7C);
        targetFlags_800C9E68 = sub_80031B0C(h, MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4)));
        menuPage_800C9E50 = 4;
        menuCommand_800C9E58.arg_4 = GetSelectedSkill_800C79EC();
        break;
    case 3:
        m = GetMinionMagicBits_80010824(3, actingUnit_800C9C7C - 1);
        targetFlags_800C9E68 = GetMagicTargetFlags_8001ACE4(FindNthMagicBit_8001AEC0(m, (short)GetMenuCursorIndex_8003DA54(magicMenu_800C92F0)));
        menuPage_800C9E50 = 4;
        menuCommand_800C9E58.arg_4 = GetSelectedMagic_800C7A1C();
        break;
    case 4:
        menuPage_800C9E50 = 5;
        menuCommand_800C9E58.targets_C = GetSelectedTargets_800C791C();
        break;
    case 5:
        break;
    }
    if (menuPage_800C9E50 == 4)
    {
        if (GetSelectedCommand_800C78D0() == 4)
        {
            targetMenu_800C9320[0].f2 = partyMinionCount_800C9E4B + 1;
            targetMenu_800C9320[0].count_4 = partyMinionCount_800C9E4B + 1;
        }
        else if (GetSelectedCommand_800C78D0() == 2)
        {
            targetMenu_800C9320[0].f2 = partyMinionCount_800C9E4B;
            targetMenu_800C9320[0].count_4 = partyMinionCount_800C9E4B;
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            targetMenu_800C9320[0].f2 = 1;
            targetMenu_800C9320[0].count_4 = 1;
        }
        else if (GetSelectedCommand_800C78D0() == 8)
        {
            targetMenu_800C9320[0].f2 = partyMinionCount_800C9E4B;
            targetMenu_800C9320[0].count_4 = partyMinionCount_800C9E4B;
        }
        targetMenu_800C9320[0].cursor_8 = 0;
        targetMenu_800C9320[0].scroll_A = 0;
    }
}

void UpdateMenuWindows_800C7CE8(unsigned char page)
{
    unsigned int n;
    if (page == 0)
    {
        menuWindows_800C9630.mode_0 = 2;
    }
    else
    {
        menuWindows_800C9630.mode_0 = 4;
    }
    menuWindows_800C9630.time_4 = GetTime30Hz_8002C64C();
    n = menuWindows_800C9630.frame_8;
    if (n < 8)
    {
        menuWindows_800C9630.frame_8 = n + 1;
    }
    menuWindows_800C9630.cursor_C = commandMenu_800C92D8[0].cursor_8;
}

void UpdateShownUnit_800C7D54(unsigned char page)
{
    if (page != 4)
    {
        shownUnit_800C9C99 = actingUnit_800C9C7C;
    }
    else if (targetFlags_800C9E68 & 5)
    {
        shownUnit_800C9C99 = actingUnit_800C9C7C;
    }
    else
    {
        shownUnit_800C9C99 = menuTarget_800C9E54;
    }
}

void BattleMenuDraw_800C7DA8()
{
    int flags = 0;
    int k = 0;
    int c;
    short sel[2];
    previewHpChange_800C9180 = 0;
    previewMpChange_800C9182 = 0;
    if (IsCircleHeldP1_8003D480() == 1 && menuState_800C9E48 != 1)
    {
        if (menuPage_800C9E50 == 0)
        {
            k = 1;
            DrawMenuHelpText_800C8828(*menuItems_800C9E6C[(short)GetMenuCursorIndex_8003DA54(commandMenu_800C92D8)].text);
        }
        else if (menuPage_800C9E50 == 1)
        {
            if (GetSelectedItem_800C79B8() != 0xFF)
            {
                DrawLargeTextBox_8002AF10((int)itemDescriptions_800C96C8[GetSelectedItem_800C79B8()], 0, 0xF);
                k = 1;
            }
        }
        else if (menuPage_800C9E50 == 2)
        {
            Minion* m = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
            DrawAbilityDescription_8002C670(m, 0, skillDescriptions_800C9B58, (short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4), 0xF);
            k = 1;
        }
        else if (menuPage_800C9E50 == 3)
        {
            if (GetSelectedMagic_800C7A1C() < 0x1E)
            {
                DrawLargeTextBox_8002AF10((int)magicDescriptions_800C9978[GetSelectedMagic_800C7A1C()], 0, 0xF);
                k = 1;
            }
        }
    }
    if (k != 0)
    {
        k = 1;
    }
    else
    {
        k = menuState_800C9E48;
    }
    sel[0] = menuCommand_800C9E58.arg_4;
    sel[1] = actingUnit_800C9C7C;
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][k] & 0x10))
    {
        if (targetFlags_800C9E68 & 1)
        {
            c = -1;
        }
        else
        {
            c = (short)GetMenuCursorIndex_8003DA54(pageCursor_800C9E44);
        }
        if (GetSelectedCommand_800C78D0() == 4)
        {
            if (targetFlags_800C9E68 & 2)
            {
                menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 0, c, 0xF);
                flags |= 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 6)
        {
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            if (targetFlags_800C9E68 & 2)
            {
                menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 1, c, 0xF);
                flags |= 1;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 2)
        {
            menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 2, c, 0xF);
            flags |= 1;
        }
        else if (GetSelectedCommand_800C78D0() == 8)
        {
            menuTarget_800C9E54 = DrawTargetSelectMenu_8002D250(sel, 3, c, 0xF);
            flags |= 1;
        }
    }
    if (pageHideFlags_800C968C[menuPage_800C9E50][k] & 2)
    {
        SetBattleFlag_800BC838(0x8000);
    }
    else
    {
        ClearBattleFlag_800BC850(0x8000);
    }
    if (pageHideFlags_800C968C[menuPage_800C9E50][k] & 1)
    {
        SetBattleFlag_800BC838(0x10000);
    }
    else
    {
        ClearBattleFlag_800BC850(0x10000);
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][k] & 4) && !(flags & 1))
    {
        DrawMenuWindows_8002A5A4(&menuWindows_800C9630);
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][k] & 0x20) && !(flags & 2))
    {
        struct_minion_ref w;
        w.field_4 = 2;
        w.ot_6 = 0xF;
        w.field_8 = -1;
        w.minion_C = 0;
        w.field_A = 0;
        w.cursor_0 = itemMenu_800C9308->cursor_8;
        w.scroll_2 = itemMenu_800C9308->scroll_A;
        DrawItemList_8002C728(&w);
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][k] & 0x40) && !(flags & 4))
    {
        struct_minion_ref w;
        w.field_4 = 2;
        w.ot_6 = 0xF;
        w.field_8 = -1;
        w.cursor_0 = skillMenu_800C92E4->cursor_8;
        w.scroll_2 = skillMenu_800C92E4->scroll_A;
        w.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        w.field_A = 0;
        DrawAbilityList_8002CE28(&w, 0);
        previewMpChange_800C9182 = -GetSkillMpCost_80031A04(&w.minion_C->skills_DE, MenuIndexToSkillSlot_80031BDC((short)GetMenuCursorIndex_8003DA54(skillMenu_800C92E4)));
    }
    if (!(pageHideFlags_800C968C[menuPage_800C9E50][k] & 0x80) && !(flags & 8))
    {
        struct_minion_ref w;
        short sz[2];
        w.field_4 = 2;
        w.ot_6 = 0xF;
        w.field_8 = -1;
        w.cursor_0 = magicMenu_800C92F0->cursor_8;
        w.scroll_2 = magicMenu_800C92F0->scroll_A;
        w.minion_C = GetMinion_80010598(3, actingUnit_800C9C7C - 1);
        sz[0] = 0x60;
        w.field_A = 0;
        sz[1] = 0x45;
        DrawMagicList_8002CAC8(&w, sz);
        previewMpChange_800C9182 = -GetMagicMpCost_8001AC58(FindNthMagicBit_8001AEC0(&w.minion_C->magicBits_F4, (short)GetMenuCursorIndex_8003DA54(magicMenu_800C92F0)));
    }
    DrawButtonHelpBar_8002B004(pageButtonHelp_800C9674[menuPage_800C9E50], 0, 0xF);
}

void PreviewCommandResult_800C83B0()
{
    BatTgtQ_a b;
    BatCmd_a a;
    BatResult_a d;
    unsigned int i;
    int bit;
    UnitStatus* self;
    UnitStatus* m;
    a = menuCommand_800C9E58;
    if (menuPage_800C9E50 == 4)
    {
        previewHpChange_800C9180 = 0;
        previewMpChange_800C9182 = 0;
        self = GetUnitStatus_80014390(actingUnit_800C9C7C);
        for (i = 0; i < 4; i++)
        {
            bit = 1 << i;
            if ((menuCommand_800C9E58.targets_C & bit) && i == shownUnit_800C9C99)
            {
                m = GetUnitStatus_80014390(i & 0xFF);

                d.areaElement_24 = shownAreaElement_800C9D82;
                d.f26 = (signed char)dword_800C9D83;
                a.targets_C = bit;
                ResolveBattleAction_80012BB0(self, m, &a, &d);
                if (sub_80013228(self, m, &a, &d) == 0 && (menuCommand_800C9E58.mask_8 & bit))
                {
                    previewHpChange_800C9180 -= d.actorHpCost_C;
                    previewMpChange_800C9182 -= d.actorMpCost_10;
                    previewHpChange_800C9180 -= d.actorHpDamage_14;
                    previewMpChange_800C9182 -= d.actorMpDamage_18;
                }
                previewHpChange_800C9180 -= d.hpDamage_1C;
                previewMpChange_800C9182 -= d.mpDamage_20;
                if (previewHpChange_800C9180 > m->hp_8.max_2 - m->hp_8.cur_0)
                {
                    previewHpChange_800C9180 = m->hp_8.max_2 - m->hp_8.cur_0;
                }
                if (previewMpChange_800C9182 > m->mp_C.max_2 - m->mp_C.cur_0)
                {
                    previewMpChange_800C9182 = m->mp_C.max_2 - m->mp_C.cur_0;
                }
            }
        }
        b.f0 = menuCommand_800C9E58.arg_4;
        b.f2 = actingUnit_800C9C7C;
        b.f4 = menuTarget_800C9E54;
        b.f6 = 0;
        if (GetSelectedCommand_800C78D0() == 4)
        {
            if (CheckItemOnTarget_80033DF4(&b))
            {
                previewHpChange_800C9180 = 0;
                previewMpChange_800C9182 = 0;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 6)
        {
            if (((int (*)(BatTgtQ_a*))CheckUsableStub_80034124)(&b))
            {
                previewHpChange_800C9180 = 0;
            }
        }
        else if (GetSelectedCommand_800C78D0() == 7)
        {
            if (CheckMagicUsable_80034068(&b))
            {
                previewHpChange_800C9180 = 0;
            }
        }
    }
}

void SetCameraFocusTargets_800C8694(unsigned char page)
{
    if (page == 4 && (targetFlags_800C9E68 & 5) == 4)
    {
        newCameraFocus_800C9E3C = enemyBits_800C9E72[(short)GetMenuCursorIndex_8003DA54(enemyTargetMenu_800C9314)];
    }
    else
    {
        newCameraFocus_800C9E3C = enemyMask_800C9E4C;
    }
}

void UpdateTargetCamera_800C8710()
{
    if (cameraFocus_800C9E38 != newCameraFocus_800C9E3C)
    {
        cameraFocus_800C9E38 = newCameraFocus_800C9E3C;
        FocusBattleCamera_80037AE0((unsigned short)newCameraFocus_800C9E3C);
        TurnUnitsToward_800BC468(newCameraFocus_800C9E3C, 1 << actingUnit_800C9C7C);
    }
}

void MenuInput_800C8768()
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (IsMenuSelectionValid_800C7530())
        {
            PlaySfx_80031494(0x7E);
            AdvanceMenuPage_800C7A6C();
        }
        else
        {
            PlaySfx_80031494(0x7C);
            if (menuErrorText_800C9E7C)
            {
                menuErrorTimer_800C9E51 = 0x96;
                menuState_800C9E48 = 1;
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        if (menuPage_800C9E50)
        {
            unsigned char c;
            PlaySfx_80031494(0x7D);
            c = prevMenuPage_800C9E40;
            prevMenuPage_800C9E40 = 0;
            menuPage_800C9E50 = c;
        }
    }
}

// Matched
extern void DrawTextLinesWindow_8002AE38(void* a0, void* a1, int a2, void* a3, int a4);
void DrawMenuHelpText_800C8828(int text)
{
    short rect[4];
    short p[4];
    short pos[2];
    int s[1];
    rect[0] = 0x19;
    rect[1] = 0x8A;
    rect[2] = MeasureTextWidth_8003E4C8(text) + 4;
    rect[3] = 0x12;
    s[0] = text;
    p[0] = rect[0];
    p[1] = rect[1];
    pos[0] = rect[0] + 2;
    pos[1] = rect[1] + 4;
    DrawTextLinesWindow_8002AE38(s, pos, 0xF, rect, 1);
}

void DrawMenuMessage_800C88AC(int text)
{
    int lines[4];
    lines[0] = text;
    lines[1] = 0;
    lines[2] = 0;
    lines[3] = 0;
    DrawLargeTextBox_8002AF10((int)lines, 0, 0xF);
}

void MenuShowError_800C88E4()
{
    if (padPressed_8009194C)
    {
        menuErrorTimer_800C9E51 = 0;
    }
    if (menuErrorTimer_800C9E51 == 0)
    {
        menuState_800C9E48 = 0;
    }
    else
    {
        menuErrorTimer_800C9E51--;
    }
    if (menuErrorText_800C9E7C)
    {
        if (menuPage_800C9E50 == 0)
        {
            DrawMenuHelpText_800C8828(menuErrorText_800C9E7C);
        }
        else
        {
            DrawMenuMessage_800C88AC(menuErrorText_800C9E7C);
        }
    }
}

void CommitMenuCommand_800C8970()
{
    int v;
    curCommand_800C9C88.kind_0 = menuCommand_800C9E58.kind_0;
    curCommand_800C9C88.arg_4 = menuCommand_800C9E58.arg_4;
    curCommand_800C9C88.mask_8 = menuCommand_800C9E58.mask_8;
    v = menuCommand_800C9E58.kind_0;
    if (v == 7 || v == 0x12)
    {
        curCommand_800C9C88.targets_C = enemyMask_800C9E4C;
    }
    else if (v == 8)
    {
        curCommand_800C9C88.targets_C = 0;
    }
    else
    {
        curCommand_800C9C88.targets_C = menuCommand_800C9E58.targets_C;
    }
    commandUnit_800C9C98 = LowestSetBit_80014358(menuCommand_800C9E58.targets_C);
}

void BattleMenuTask_800C8A08(EventEntry* t, int a)
{
    pageCursor_800C9E44 = GetPageCursor_800C73B8(menuPage_800C9E50);
    HighlightTargetWindows_800C7424(menuPage_800C9E50);
    UpdateMenuCursor_8003D794(pageCursor_800C9E44, 0);
    UpdateMenuWindows_800C7CE8(menuPage_800C9E50);
    BattleMenuDraw_800C7DA8();
    menuCommand_800C9E58.targets_C = GetSelectedTargets_800C791C();
    UpdateShownUnit_800C7D54(menuPage_800C9E50);
    PreviewCommandResult_800C83B0();
    SetCameraFocusTargets_800C8694(menuPage_800C9E50);
    UpdateTargetCamera_800C8710();
    menuStateFns_800C966C[menuState_800C9E48](t, a);
    if (menuPage_800C9E50 == 5)
    {
        savedEnemyCursor_800C9D56 = enemyTargetMenu_800C9314->cursor_8;
        ResetWindowHighlights_800BFC10();
        CommitMenuCommand_800C8970();
        previewHpChange_800C9180 = 0;
        previewMpChange_800C9182 = 0;
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

int dword_800C8B2C = 0xFFFF;
unsigned char aiCounter_800C8B30 = 0;
int aiAllyCalled_800C8B34 = 0;
char commandHandlerIdx_800C8B38[28] = { 0, 0, 1, 2, 0, 3, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 6, 0, 0, 0, 3 };
int commandHandlers_800C8B54[7] = { (int)CmdAction_800BBA24, (int)CmdSummon_800BBBA8, (int)CmdRecall_800BBDB4, (int)CmdSimple_800BC0FC, (int)CmdSwapMinion_800BBBF4, (int)CmdEnemyCall_800BBEFC, (int)sub_800BBFFC };
unsigned short stage00Sprites_800C8B70[8] = { 40, 41, 42, 43, 44, 45, 46, 0xFFFF };
unsigned short stage01Sprites_800C8B80[8] = { 51, 52, 53, 54, 55, 56, 0xFFFF };
unsigned short stage02Sprites_800C8B90[8] = { 61, 62, 63, 64, 65, 66, 67, 0xFFFF };
unsigned short stage03Sprites_800C8BA0[8] = { 72, 73, 74, 75, 76, 77, 78, 0xFFFF };
unsigned short stage04Sprites_800C8BB0[8] = { 84, 85, 86, 87, 88, 89, 90, 0xFFFF };
unsigned short stage05Sprites_800C8BC0[10] = {
    91, 92, 93, 94, 95, 96, 97, 98,
    0xFFFF,
};
unsigned short stage06Sprites_800C8BD4[10] = {
    99, 100, 101, 102, 103, 104, 105, 106,
    0xFFFF,
};
unsigned short stage07Sprites_800C8BE8[8] = { 108, 109, 110, 111, 112, 113, 0xFFFF };
unsigned short stage08Sprites_800C8BF8[10] = {
    118, 119, 120, 121, 122, 123, 124, 125,
    0xFFFF,
};
unsigned short stage09Sprites_800C8C0C[8] = { 126, 127, 128, 129, 130, 131, 0xFFFF };
unsigned short stage0ASprites_800C8C1C[8] = { 136, 137, 138, 139, 140, 141, 0xFFFF };
unsigned short stage0BSprites_800C8C2C[8] = { 0x11D, 0x11E, 0x11F, 0x120, 0x121, 0x122, 0xFFFF };
unsigned short stage0CSprites_800C8C3C[10] = {
    0x127, 0x128, 0x129, 0x12A, 0x12B, 0x12C, 0x12D, 0x12E,
    0xFFFF,
};
unsigned short stage0DSprites_800C8C50[8] = { 0x12F, 0x130, 0x131, 0x132, 0x133, 0x134, 0xFFFF };
unsigned short stage0ESprites_800C8C60[8] = { 0x139, 0x13A, 0x13B, 0x13C, 0x13D, 0x13E, 0xFFFF };
unsigned short stage0FSprites_800C8C70[6] = { 146, 147, 148, 149, 150, 0xFFFF };
unsigned short stage10Sprites_800C8C7C[6] = { 152, 153, 154, 155, 0xFFFF };
unsigned short stage11Sprites_800C8C88[8] = { 156, 157, 158, 159, 160, 161, 0xFFFF };
unsigned short stage12Sprites_800C8C98[2] = { 0xFFFF };
unsigned short stage13Sprites_800C8C9C[6] = { 166, 167, 168, 169, 0xFFFF };
unsigned short stage14Sprites_800C8CA8[6] = { 171, 172, 173, 174, 175, 0xFFFF };
unsigned short stage15Sprites_800C8CB4[6] = { 176, 177, 178, 179, 180, 0xFFFF };
unsigned short stage16Sprites_800C8CC0[6] = { 182, 183, 184, 185, 186, 0xFFFF };
unsigned short stage17Sprites_800C8CCC[8] = { 187, 188, 189, 190, 191, 192, 193, 0xFFFF };
unsigned short stage18Sprites_800C8CDC[8] = { 198, 199, 200, 201, 202, 203, 0xFFFF };
unsigned short stage19Sprites_800C8CEC[8] = { 208, 209, 210, 211, 212, 213, 214, 0xFFFF };
unsigned short stage1ASprites_800C8CFC[8] = { 219, 220, 221, 222, 223, 224, 225, 0xFFFF };
unsigned short stage1BSprites_800C8D0C[8] = { 0x16F, 0x170, 0x171, 0x172, 0x173, 0x174, 0x175, 0xFFFF };
unsigned short stage1CSprites_800C8D1C[10] = {
    0x10C, 0x10D, 0x10E, 0x10F, 0x110, 0x111, 0x112, 0x113,
    0xFFFF,
};
unsigned short stage1DSprites_800C8D30[10] = {
    0x114, 0x115, 0x116, 0x117, 0x118, 0x119, 0x11A, 0x11B,
    0xFFFF,
};
unsigned short stage1ESprites_800C8D44[8] = { 230, 231, 232, 233, 234, 235, 0xFFFF };
unsigned short stage1FSprites_800C8D54[10] = {
    240, 241, 242, 243, 244, 245, 246, 247,
    0xFFFF,
};
unsigned short stage20Sprites_800C8D68[8] = { 248, 249, 250, 251, 252, 253, 0xFFFF };
unsigned short stage21Sprites_800C8D78[8] = { 0x102, 0x103, 0x104, 0x105, 0x106, 0x107, 0xFFFF };
unsigned short stage22Sprites_800C8D88[8] = { 0x183, 0x184, 0x185, 0x186, 0x187, 0x188, 0xFFFF };
unsigned short stage23Sprites_800C8D98[6] = { 0x197, 0x198, 0x199, 0x19A, 0x19B, 0xFFFF };
unsigned short stage24Sprites_800C8DA4[8] = { 0x18D, 0x18E, 0x18F, 0x190, 0x191, 0x192, 0xFFFF };
unsigned short stage25Sprites_800C8DB4[8] = { 0x1A0, 0x1A1, 0x1A2, 0x1A3, 0x1A4, 0x1A5, 0xFFFF };
unsigned short stage26Sprites_800C8DC4[8] = { 0x179, 0x17A, 0x17B, 0x17C, 0x17D, 0x17E, 0xFFFF };
unsigned short stage10Models_800C8DD4[12] = {
    49, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage12Models_800C8DEC[12] = {
    52, 0, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage13Models_800C8E04[12] = {
    54, 0, 1, 0, 55, 48, 0, 0,
    56, 48,
};
unsigned short stage0AModels_800C8E1C[12] = {
    193, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage0EModels_800C8E34[12] = {
    194, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage21Models_800C8E4C[12] = {
    195, 48, 0, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage14Models_800C8E64[12] = {
    58, 0, 1, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage15Models_800C8E7C[12] = {
    60, 0, 1, 0, 255, 0, 0, 0,
    255,
};
unsigned short stage16Models_800C8E94[12] = {
    62, 0, 1, 0, 255, 0, 0, 0,
    255,
};
BatStage_a battleStages_800C8EAC[39] = {
    { stage00Sprites_800C8B70, 0x3A6, 37, 0, 7, -1 },
    { stage01Sprites_800C8B80, 0x3A8, 38, 0, 6, -1 },
    { stage02Sprites_800C8B90, 0x3A9, 39, 0, 7, -1 },
    { stage03Sprites_800C8BA0, 0x3AA, 40, 0, 7, -1 },
    { stage04Sprites_800C8BB0, 0x3AB, 41, 0, -1, 83 },
    { stage05Sprites_800C8BC0, 0x3C5, 42, 0, -1, 0x1AA },
    { stage06Sprites_800C8BD4, 0x3C7, 43, 0, -1, 107 },
    { stage07Sprites_800C8BE8, 0x3AC, 44, 0, 6, -1 },
    { stage08Sprites_800C8BF8, 0x3AD, 45, 0, -1, -1 },
    { stage09Sprites_800C8C0C, 0x3B7, 46, 0, -1, -1 },
    { stage0ASprites_800C8C1C, 0x3BA, 47, 0, -1, -1, stage0AModels_800C8E1C },
    { stage0BSprites_800C8C2C, 0x3B3, 74, 0, 6, -1 },
    { stage0CSprites_800C8C3C, 0x3B5, 75, 0, -1, -1 },
    { stage0DSprites_800C8C50, 0x3B8, 76, 0, 6, -1 },
    { stage0ESprites_800C8C60, 0x3BB, 77, 0, 6, -1, stage0EModels_800C8E34 },
    { stage0FSprites_800C8C70, 0x3BD, 48, 0, -1, 151 },
    { stage10Sprites_800C8C7C, 0x3BE, 50, 0, -1, -1, stage10Models_800C8DD4 },
    { stage11Sprites_800C8C88, 0x3BF, 51, 0, -1, -1 },
    { stage12Sprites_800C8C98, 0x3C0, 53, 0, 0, -1, stage12Models_800C8DEC },
    { stage13Sprites_800C8C9C, 0x3C1, 57, 0, -1, 170, stage13Models_800C8E04 },
    { stage14Sprites_800C8CA8, 0x3C2, 59, 0, -1, -1, stage14Models_800C8E64 },
    { stage15Sprites_800C8CB4, 0x3C3, 61, 0, -1, 181, stage15Models_800C8E7C },
    { stage16Sprites_800C8CC0, 0x3C4, 63, 0, -1, -1, stage16Models_800C8E94 },
    { stage17Sprites_800C8CCC, 0x3AE, 64, 0, 7, -1 },
    { stage18Sprites_800C8CDC, 0x3AF, 65, 0, 6, -1 },
    { stage19Sprites_800C8CEC, 0x3B0, 66, 0, 7, -1 },
    { stage1ASprites_800C8CFC, 0x3B1, 67, 0, 7, -1 },
    { stage1BSprites_800C8D0C, 0x3B2, 175, 0, -1, 0x16E },
    { stage1CSprites_800C8D1C, 0x3C6, 72, 0, -1, 0x1AB },
    { stage1DSprites_800C8D30, 0x3C8, 73, 0, -1, 0x11C },
    { stage1ESprites_800C8D44, 0x3B4, 68, 0, 6, -1 },
    { stage1FSprites_800C8D54, 0x3B6, 69, 0, -1, -1 },
    { stage20Sprites_800C8D68, 0x3B9, 70, 0, 6, -1 },
    { stage21Sprites_800C8D78, 0x3BC, 71, 0, 6, -1, stage21Models_800C8E4C },
    { stage22Sprites_800C8D88, 0x434, 187, 0, 6, -1 },
    { stage23Sprites_800C8D98, 0x435, 189, 0, 5, -1 },
    { stage24Sprites_800C8DA4, 0x436, 188, 0, 6, -1 },
    { stage25Sprites_800C8DB4, 0x437, 190, 0, 6, -1 },
    { stage26Sprites_800C8DC4, 0x438, 186, 0, 6, -1 },
};
int stageAnimPhases_800C911C[2] = { 0x2090501, 0x4070306 };
int stageRot_800C9124[2] = { 0 };
char handlerWaitsReactions_800C912C[8] = { 0, 0, 0, 1 };
unsigned char captureVibrations_800C9134[4] = { 5, 6, 7, 8 };
int statusCureChances_800C9138[2] = { 2, 77 };
BatXY_a enemyWindowLayouts_800C9140[9] = {
    { 110, 20 },
    { -1, -1 },
    { -1, -1 },
    { 60, 20 },
    { 160, 20 },
    { -1, -1 },
    { 10, 20 },
    { 110, 20 },
    { 210, 20 },
};
int enemyGaugePreview_800C9164[3] = { 0 };
int actorHighlightTime_800C9170 = 0;
int enemyHighlightTimes_800C9174[3] = { 0 };
short previewHpChange_800C9180 = 0;
short previewMpChange_800C9182 = 0;
int dword_800C9184 = 0x24639300;
Minion *summonedMinion_800C9188 = 0;
int summonedMinionSlot_800C918C = -1;
BatSummon_a summonedActor_800C9190 = { 0 };
char defaultBoneSlots_800C91A4[56] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2 };
BatFxFn enemyAiHigh_800C91DC[10] = {
    EnemyAiC9_800C4328, EnemyAiCA_800C43D8, EnemyAiCB_800C4424, (BatFxFn)EnemyAiCC_800C4470,
    EnemyAiCD_800C4494, EnemyAiCE_800C44FC, EnemyAiCF_800C4548, EnemyAiD0_800C45A8,
    (BatFxFn)EnemyAiD1_800C46FC, (BatFxFn)EnemyAiD2_800C471C,
};
BatFxFn enemyAi_800C9204[53] = {
    (BatFxFn)EnemyAi00_800C4D38, (BatFxFn)EnemyAi00_800C4D38, (BatFxFn)EnemyAi02_800C54A4, (BatFxFn)EnemyAi03_800C4FE0,
    (BatFxFn)EnemyAi04_800C57D8, (BatFxFn)EnemyAi05_800C56B8, (BatFxFn)EnemyAi06_800C4BE4, (BatFxFn)EnemyAi07_800C4E34,
    (BatFxFn)EnemyAi08_800C580C, (BatFxFn)EnemyAi09_800C4DB8, (BatFxFn)EnemyAi0A_800C4EA8, (BatFxFn)EnemyAi0B_800C5510,
    (BatFxFn)EnemyAi0C_800C4CBC, (BatFxFn)EnemyAi0D_800C5424, (BatFxFn)EnemyAi0E_800C5034, (BatFxFn)EnemyAi0F_800C4B34,
    (BatFxFn)EnemyAi10_800C5304, (BatFxFn)EnemyAi0F_800C4B34, (BatFxFn)EnemyAi12_800C4C74, (BatFxFn)EnemyAi13_800C507C,
    (BatFxFn)EnemyAi14_800C5594, (BatFxFn)EnemyAi15_800C5290, (BatFxFn)EnemyAi16_800C5608, (BatFxFn)EnemyAi17_800C50B0,
    (BatFxFn)EnemyAi18_800C5670, (BatFxFn)EnemyAi19_800C576C, (BatFxFn)EnemyAi1A_800C4FA8, (BatFxFn)EnemyAi1B_800C51D8,
    (BatFxFn)EnemyAi1C_800C53B0, (BatFxFn)EnemyAi1D_800C5700, (BatFxFn)EnemyAi1E_800C5874, (BatFxFn)EnemyAi1F_800C5840,
    (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C,
    (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C,
    (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C,
    (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C,
    (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C, (BatFxFn)EnemyAiDefault_800C473C,
    (BatFxFn)EnemyAiDefault_800C473C,
};
BatMenu_a commandMenu_800C92D8[1] = { { 2, 3 } };
BatMenu_a skillMenu_800C92E4[1] = { { 1, 5, 5 } };
BatMenu_a magicMenu_800C92F0[1] = { { 1, 4, 4, 64 } };
int dword_800C92FC[3] = { 0x10001, 1 };
BatMenu_a itemMenu_800C9308[1] = { { 1, 4, 4, 64 } };
BatMenu_a enemyTargetMenu_800C9314[1] = { { 0, 1 } };
BatMenu_a targetMenu_800C9320[1] = { { 1 } };
BatMenu_a allTargetsMenu_800C932C[1] = { { 1, 1, 1 } };
BatMenu_a *pageMenus_800C9338[6] = { commandMenu_800C92D8, itemMenu_800C9308, skillMenu_800C92E4, magicMenu_800C92F0, targetMenu_800C9320, commandMenu_800C92D8 };
int helpAttack_800C9350[1] = { (int)aAttackWithReadi_800B68AC };
int helpDefend_800C9354[1] = { (int)aDefendToReduceD_800B68E4 };
int helpSummon_800C9358[1] = { (int)aSummonDivineMin_800B6914 };
int helpCapture_800C935C[1] = { (int)aCaptureMinionIn_800B6940 };
int helpItem_800C9360[1] = { (int)aUseItem_800B6984 };
int helpFlee_800C9364[1] = { (int)aFleeFromCombat_800B6998 };
int helpMinionAttack_800C9368[1] = { (int)aUseNormalAttack_800B69BC };
int helpSpecialAttack_800C936C[1] = { (int)aUseSpecialAttac_800B69E0 };
int helpMagic_800C9370[1] = { (int)aUseMagicSpell_800B6A08 };
int helpChangeFighter_800C9374[1] = { (int)aChangeCurrentFi_800B6A28 };
int msgNoDivineMinions_800C9378[1] = { (int)aNoDivineMinions_800B6A58 };
int msgCannotSummon_800C937C = (int)aCannotSummonInt_800B6A88;
int msgNotEnoughMana_800C9380 = (int)aNotEnoughMana_800B6ABC;
int msgCannotCapture_800C9384[1] = { (int)aCannotCapture_800B6ADC };
int msgNoEmptyCocoons_800C9388[1] = { (int)aNoEmptyCocoons_800B6AFC };
int msgCannotEscape_800C938C[1] = { (int)aCannotEscape_800B6B20 };
int msgNoNeedToUseItem_800C9390 = (int)aNoNeedToUseItem_800B6B3C;
int msgCannotSelect_800C9394[1] = { (int)aCannotSelect_800B6B64 };
int msgItemForDivineMinions_800C9398 = (int)aThisItemIsForDi_800B6B80;
int msgDivineMinionsCannot_800C939C = (int)aDivineMinionsCa_800B6BC0;
int msgCannotUseHere_800C93A0 = (int)aCannotUseHere_800B6C08;
BatMenuItem_a levantMenuItems_800C93A4[6] = {
    { helpAttack_800C9350 },
    { helpDefend_800C9354 },
    { helpSummon_800C9358 },
    { helpCapture_800C935C },
    { helpItem_800C9360 },
    { helpFlee_800C9364 },
};
BatMenuItem_a minionMenuItems_800C93D4[5] = {
    { helpMinionAttack_800C9368 },
    { helpDefend_800C9354 },
    { helpSpecialAttack_800C936C },
    { helpMagic_800C9370 },
    { helpChangeFighter_800C9374 },
};
BatMenuWin_a winAttack_800C93FC[2] = {
    { 8, 1, 13, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 157, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winDefend_800C9434[2] = {
    { 8, 1, 48, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 157, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winSummon_800C946C[2] = {
    { 8, 1, 180, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winCapture_800C94A4[2] = {
    { 8, 1, 224, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winItem_800C94DC[2] = {
    { 8, 1, 88, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 195, 38, 18, 2, 3 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winFlee_800C9514[2] = {
    { 8, 1, 57, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 195, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winSpecialAttack_800C954C[2] = {
    { 8, 1, 183, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winMagic_800C9584[2] = {
    { 8, 1, 108, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 60, 176, 38, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a winChangeFighter_800C95BC[2] = {
    { 8, 1, 40, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 22, 195, 76, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
};
BatMenuWin_a *levantMenuWindows_800C95F4[7] = { winAttack_800C93FC, winDefend_800C9434, winSummon_800C946C, winCapture_800C94A4, winItem_800C94DC, winFlee_800C9514 };
BatMenuWin_a *minionMenuWindows_800C9610[6] = { winAttack_800C93FC, winDefend_800C9434, winSpecialAttack_800C954C, winMagic_800C9584, winChangeFighter_800C95BC };
BatMenuWin_a **menuWindowSets_800C9628[2] = { levantMenuWindows_800C95F4, minionMenuWindows_800C9610 };
BatMenuWins_a menuWindows_800C9630 = { 2 };
unsigned char commandByCursor_800C9648[12] = { 0, 0, 1, 1, 2, 6, 3, 7, 4, 8, 5, 5 };
unsigned char commandNextPage_800C9654[12] = { 4, 5, 4, 4, 1, 5, 2, 3, 4 };
unsigned char commandTargetFlags_800C9660[12] = { 4, 0, 2, 4, 0, 0, 4, 4, 2 };
void (*menuStateFns_800C966C[2])(EventEntry *t, int a) = { (void (*)(EventEntry *, int))MenuInput_800C8768, (void (*)(EventEntry *, int))MenuShowError_800C88E4 };
int pageButtonHelp_800C9674[6] = { 0x80082698, 0x800826B0, 0x800826B0, 0x800826B0, 0x80082680 };
unsigned short pageHideFlags_800C968C[6][2] = {
    { 0x1F0, 240 },
    { 0x1D1, 0x1D7 },
    { 0x1B1, 0x1B7 },
    { 0x170, 0x176 },
    { 0x1E0, 246 },
};
int commandKinds_800C96A4[9] = {
    0, 18, 2, 5, 4, 7, 6, 1,
    8,
};
int itemDescriptions_800C96C8[43][4] = {
    { (int)aRestoreHealth_800B8CFC, (int)aGrowsInOpenArea_800B8CB4, (int)aIncreasesHealth_800B8C68, (int)aGrindLeavesInto_800B8C0C },
    { (int)aRestoreHealth_800B8CFC, (int)aATypeOfMugwortB_800B8BCC, (int)aSweeterSmelling_800B8B74, (int)aCuresBleedingAn_800B8B30 },
    { (int)aRestoreHealth_800B8CFC, (int)aATypeOfMugwortW_800B8ACC, (int)aBitterTasteThat_800B8A60 },
    { (int)aIncreaseMaxHeal_800B8A38, (int)aANutPackingEner_800B89D8, (int)aStrengthensTheB_800B8974 },
    { (int)aIncreaseMinionA_800B8938, (int)aOilFromATreeWit_800B88F0, (int)aSharpensMinionS_800B88BC },
    { (int)aIncreasesMinion_800B888C, (int)aOilFromAVeryPot_800B8850, (int)aStrengthensMini_800B8818 },
    { (int)aIncreaseMinionD_800B87D8, (int)aOilFromAPlantWi_800B878C, (int)aHardensMinionSS_800B875C },
    { (int)aIncreaseMinionM_800B8720, (int)aOilFromTreeWith_800B86D8, (int)aStrengthensMini_800B86A0 },
    { (int)aIncreaseMinionM_800B8664, (int)aOilFromAPlantWi_800B861C, (int)aStrengthensMini_800B85E0 },
    { (int)aRestoreMinionHP_800B85A8, (int)aLiquorMadeFromP_800B855C, (int)aRestoresSomeMin_800B8518 },
    { (int)aRestoreMinionHP_800B85A8, (int)aFineLiquorMadeF_800B84C0, (int)aRestoresMinionH_800B845C },
    { (int)aRestoreMinionHP_800B85A8, (int)aExcellentLiquor_800B83FC, (int)aRestoresAGreatD_800B83A0 },
    { (int)aRestoreMinionHP_800B85A8, (int)aSpecialLiquorMa_800B8344, (int)aRestoresAllMini_800B8300 },
    { (int)aTotalRestoratio_800B82DC, (int)aDriedRootOfAGre_800B8274, (int)aAlsoCalledTheIm_800B8230, (int)aAdjustsTheVisce_800B8204 },
    { (int)aPoisonAntidote_800B81E4, (int)aPowderedFormOfD_800B8198, (int)aSoothesTheSpiri_800B8144 },
    { (int)aStoneToFlesh_800B8124, (int)aPowderMadeFromS_800B80C0, (int)aInnerStrengthTo_800B8064 },
    { (int)aSprayPoison_800B8048, (int)aReleasesPoisonM_800B8004, (int)aInstantlyCauses_800B7FBC },
    { (int)aInduceSleep_800B7FA0, (int)aReleasesASleepM_800B7F58, (int)aCausesADeepSlum_800B7EEC },
    { (int)aFleshToStone_800B7ECC, (int)aReleasesAFleshT_800B7E74, (int)aCausesBodyHarde_800B7E18 },
    { (int)aCauseDeath_800B7E00, (int)aReleasesADeathM_800B7DB8, (int)aInstantlyCauses_800B7D5C },
    { (int)aProtectionFromA_800B7D34, (int)aReflectsAllUncl_800B7CD4, (int)aAllAbnormalStat_800B7C6C },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7BDC, (int)aChangesAreaProp_800B7B74 },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7B14, (int)aChangesAreaProp_800B7AAC },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7A4C, (int)aChangesAreaProp_800B79E8 },
    { (int)aChangeAreaPrope_800B7C3C, (int)aACharmBlessedBy_800B7988, (int)aChangesAreaProp_800B7924 },
    { (int)aAttackSingleEne_800B78E4, (int)aSealWithTheMark_800B787C, (int)aInflictsAnEarth_800B7818 },
    { (int)aAttackAllEnemie_800B77DC, (int)aSealWithTheMark_800B787C, (int)aInflictsAnEarth_800B777C },
    { (int)aAttackSingleEne_800B773C, (int)aSealWithTheMark_800B76D4, (int)aInflictsAWaterB_800B7670 },
    { (int)aAttackAllEnemie_800B7634, (int)aSealWithTheMark_800B76D4, (int)aInflictsAWaterB_800B75D8 },
    { (int)aAttackSingleEne_800B759C, (int)aSealWithTheMark_800B7538, (int)aInflictsAFireBa_800B74D8 },
    { (int)aAttackAllEnemie_800B749C, (int)aSealWithTheMark_800B7538, (int)aInflictsAFireBa_800B7440 },
    { (int)aAttackSingleEne_800B7404, (int)aSealWithTheMark_800B739C, (int)aInflictsAWindBa_800B733C },
    { (int)aAttackMultipleE_800B72F8, (int)aSealWithTheMark_800B739C, (int)aInflictsAWindBa_800B7294 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAShineT_800B71EC, (int)aSeventhHighestG_800B71AC },
    { (int)aSilkThreadSpunF_800B7248, (int)aEmitsVagueInsta_800B7150, (int)aSixthHighestGra_800B7114 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffADazzli_800B70DC, (int)aFifthHighestGra_800B70A0 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAModera_800B7058, (int)aFourthHighestGr_800B701C },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAPhosph_800B6FCC, (int)aThirdHighestGra_800B6F90 },
    { (int)aSilkThreadSpunF_800B7248, (int)aGivesOffAnUnear_800B6F40, (int)aSecondHighestGr_800B6F04 },
    { (int)aSilkThreadSpunF_800B7248, (int)aSoftThreadThatG_800B6EB0, (int)aHighestGradeBes_800B6E6C },
    { (int)aKeyToTreasureCh_800B6E3C, (int)aMultipurposeKey_800B6DD8, (int)aBendsAndBecomes_800B6D80 },
    { (int)aTreeSpores_800B6D68, (int)aSweetSmellingSl_800B6D00, (int)aCausesSurroundi_800B6CA8 },
    { (int)aTreeSpores_800B6D68, (int)aTreeSporesWithA_800B6C5C, (int)aAttractsNearbyM_800B6C28 },
};
int magicDescriptions_800C9978[30][4] = {
    { (int)aFireAttackOneEn_800B97B8, (int)aExtraDamageVsAi_800B978C, (int)aHigherFireEleme_800B9730 },
    { (int)aFireAttackAllEn_800B96FC, (int)aExtraDamageVsAi_800B978C, (int)aHigherFireEleme_800B9730 },
    { (int)aAdvancedFireAtt_800B96D0, (int)aExtraDamageVsAi_800B978C, (int)aHigherFireEleme_800B9730 },
    { (int)aWaterAttackOneE_800B969C, (int)aExtraDamageVsFi_800B9670, (int)aHigherWaterElem_800B9610 },
    { (int)aWaterAttackAllE_800B95D8, (int)aExtraDamageVsFi_800B9670, (int)aHigherWaterElem_800B9610 },
    { (int)aAdvancedWaterAt_800B95AC, (int)aExtraDamageVsFi_800B9670, (int)aHigherWaterElem_800B9610 },
    { (int)aEarthAttackOneE_800B9578, (int)aExtraDamageVsWa_800B9548, (int)aHigherEarthElem_800B94E8 },
    { (int)aEarthAttackAllE_800B94B0, (int)aExtraDamageVsWa_800B9548, (int)aHigherEarthElem_800B94E8 },
    { (int)aAdvancedEarthAt_800B9484, (int)aExtraDamageVsWa_800B9548, (int)aHigherEarthElem_800B94E8 },
    { (int)aWindAttackOneEn_800B9454, (int)aExtraDamageVsEa_800B9424, (int)aHigherWindEleme_800B93C8 },
    { (int)aWindAttackAllEn_800B9394, (int)aExtraDamageVsEa_800B9424, (int)aHigherWindEleme_800B93C8 },
    { (int)aAdvancedWindAtt_800B9368, (int)aExtraDamageVsEa_800B9424, (int)aHigherWindEleme_800B93C8 },
    { (int)aCurePoison_800B9350, (int)aCuresPoison_800B9334 },
    { (int)aRestoreHP_800B931C, (int)aRestoresSomeHP_800B92F8 },
    { (int)aRestoreAllHP_800B92D8, (int)aRestoresAllHP_800B92B4 },
    { (int)aReturnToNormal_800B9290, (int)aCuresPoisonAndT_800B9238 },
    { (int)aProtection_800B9220, (int)aProtectsAgainst_800B91B8, (int)aEndsOnceItProte_800B9164 },
    { (int)aPoison_800B9154, (int)aPoisonsAnEnemy_800B9130 },
    { (int)aSleep_800B9124, (int)aPutsAnEnemyToSl_800B90F4 },
    { (int)aFleshToStone_800B7ECC, (int)aTurnsAnEnemyInt_800B90BC },
    { (int)aDeath_800B90B0, (int)aCausesAnEnemyTo_800B905C },
    { (int)aEnhanceFire_800B9040, (int)aIncreasesFireAt_800B8FEC, (int)aEffectivenessOf_800B8F90 },
    { (int)aEnhanceWater_800B8F74, (int)aIncreasesWaterA_800B8F1C, (int)aEffectivenessOf_800B8EC0 },
    { (int)aEnhanceEarth_800B8EA4, (int)aIncreasesEarthA_800B8E4C, (int)aEffectivenessOf_800B8DEC },
    { (int)aEnhanceWind_800B8DD0, (int)aIncreasesWindAt_800B8D7C, (int)aEffectivenessOf_800B8D1C },
};
char skillDescriptions_800C9B58[256] = { 116, 161, 11, 128, 116, 161, 11, 128, 116, 161, 11, 128, 0, 0, 0, 0, 116, 161, 11, 128, 116, 161, 11, 128, 116, 161, 11, 128, 0, 0, 0, 0, 72, 161, 11, 128, 240, 160, 11, 128, 232, 148, 11, 128, 0, 0, 0, 0, 196, 160, 11, 128, 108, 160, 11, 128, 16, 150, 11, 128, 0, 0, 0, 0, 68, 160, 11, 128, 236, 159, 11, 128, 48, 151, 11, 128, 0, 0, 0, 0, 196, 159, 11, 128, 108, 159, 11, 128, 200, 147, 11, 128, 0, 0, 0, 0, 64, 159, 11, 128, 236, 158, 11, 128, 0, 0, 0, 0, 0, 0, 0, 0, 192, 158, 11, 128, 88, 158, 11, 128, 0, 0, 0, 0, 0, 0, 0, 0, 28, 158, 11, 128, 176, 157, 11, 128, 0, 0, 0, 0, 0, 0, 0, 0, 116, 157, 11, 128, 12, 157, 11, 128, 188, 156, 11, 128, 0, 0, 0, 0, 132, 156, 11, 128, 56, 156, 11, 128, 232, 155, 11, 128, 0, 0, 0, 0, 172, 155, 11, 128, 100, 155, 11, 128, 28, 155, 11, 128, 0, 0, 0, 0, 224, 154, 11, 128, 164, 154, 11, 128, 88, 154, 11, 128, 0, 0, 0, 0, 28, 154, 11, 128, 208, 153, 11, 128, 120, 153, 11, 128, 0, 0, 0, 0, 64, 153, 11, 128, 224, 152, 11, 128, 124, 152, 11, 128, 0, 0, 0, 0, 64, 152, 11, 128, 232, 151, 11, 128, 124, 152, 11, 128 };
int battleLoadState_800C9C58 = 0;
int dword_800C9C5C[3] = { 0 };
short turnGauges_800C9C68[8] = { 0 };
int *chainEntry_800C9C78 = 0;
unsigned char actingUnit_800C9C7C = 0;
short actorHpChange_800C9C7E = 0;
short actorMpChange_800C9C80 = 0;
unsigned char summonedUnit_800C9C82 = 0;
int dword_800C9C84 = 0;
BatCmd_a curCommand_800C9C88 = { 0 };
unsigned char commandUnit_800C9C98 = 0;
unsigned char shownUnit_800C9C99 = 0;
int dword_800C9C9C = 0;
int unitStatusInflicted_800C9CA0[7] = { 0 };
char unitHitKinds_800C9CBC[12] = { 0 };
BatCmd_a unitReactions_800C9CC8[7] = { { 0 } };
short unitHpDamage_800C9D38[8] = { 0 };
short unitMpDamage_800C9D48[8] = { 0 };
int unitResultFlags_800C9D58[7] = { 0 };
int helpWindowText_800C9D74 = 0;
short hitSfx_800C9D78 = 0;
int btlExecLoad_800C9D7C = 0;
short deathSfx_800C9D80 = 0;
signed char shownAreaElement_800C9D82 = 0;
char dword_800C9D83 = 0;
signed char areaElement_800C9D84 = 0;
int dword_800C9D88 = 0;
short stageAnimUv_800C9D8C[2] = { 0 };
int removedEnemyCount_800C9D90 = 0;
short actionFrame_800C9D94 = 0;
short actorTiming_800C9D98[4] = { 0 };
BatPair_a reactionTimings_800C9DA0[7] = { { 0 } };
short actorHitShift_800C9DBC = 0;
short reactionHitFrames_800C9DC0[8] = { 0 };
int removedEnemies_800C9DD0[10] = { 0 };
int enemyWindowFlags_800C9DF8 = 0;
char enemyWindowsHighlight_800C9DFC = 0;
char actorWindowHighlight_800C9DFD = 0;
unsigned int enemyWindowSlide_800C9E00 = 0;
int dword_800C9E04 = 0;
EventEntry *enemyWindowTasks_800C9E08[4] = { 0 };
BatXY_a enemyWindowPos_800C9E18[3] = { { 0 } };
int enemyWindowMask_800C9E24 = 0;
BatUnitWin_a *enemyWindows_800C9E28[4] = { 0 };
int cameraFocus_800C9E38 = 0;
int newCameraFocus_800C9E3C = 0;
unsigned char prevMenuPage_800C9E40 = 0;
BatMenu_a *pageCursor_800C9E44 = 0;
unsigned char menuState_800C9E48 = 0;
unsigned char menuForMinion_800C9E49 = 0;
unsigned char enemyCount_800C9E4A = 0;
unsigned char partyMinionCount_800C9E4B = 0;
int enemyMask_800C9E4C = 0;
unsigned char menuPage_800C9E50 = 0;
unsigned char menuErrorTimer_800C9E51 = 0;
int menuTarget_800C9E54 = 0;
BatCmd_a menuCommand_800C9E58 = { 0 };
unsigned char targetFlags_800C9E68 = 0;
BatMenuItem_a *menuItems_800C9E6C = 0;
INCLUDE_OVERLAY_ASM(battle, dword_800C9E70);
INCLUDE_OVERLAY_ASM(battle, partyMinionMask_800C9E78);
INCLUDE_OVERLAY_ASM(battle, menuErrorText_800C9E7C);
INCLUDE_OVERLAY_ASM(battle, enemyUnits_800C9E80);
