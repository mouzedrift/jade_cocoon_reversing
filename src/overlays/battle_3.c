// BATTLE.BIN, source file 3 of 6 from 0x800BE834 (.rdata from 0x800B6774)
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

// Matched
int IsActionDone_800BEA94()
{
    if (!(saveData_8008B570.flags_0 & 0x20))
    {
        if (AnyHitNumberActive_800BF47C() == 1)
        {
            return 0;
        }
        if (TestBattleFlag_800BC820(4) != 1)
        {
            goto handler;
        }
        if (IsActorActionDone_800BEB50() == 0)
        {
            return 0;
        }
        if (AreReactionsDone_800BEB68() == 0)
        {
            goto zero;
        }
    }
    return 1;
handler:
    if (handlerWaitsReactions_800C912C[(unsigned char)commandHandlerIdx_800C8B38[curCommand_800C9C88.kind_0]] == 0)
    {
        return IsActorActionDone_800BEB50();
    }
    return AreReactionsDone_800BEB68();
zero:
    return 0;
}

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
    BatCommand cmd;
    BatActionResult res;
    UnitStatus* actor;
    UnitStatus* target;
    int escaped;
    int side;
    unsigned int i;
    int bit;
    int defending;

    GetUnitSide_800BC7DC(actingUnit_800C9C7C);
    escaped = 1;
    actor = GetUnitStatus_80014390(actingUnit_800C9C7C);
    cmd = curCommand_800C9C88;
    if (curCommand_800C9C88.kind_0 == 0x12)
    {
        actor = GetUnitStatus_80014390(actingUnit_800C9C7C);
        actor->status_0 |= 0x8000;
    }
    for (i = 0; i < 7; i++)
    {
        side = GetUnitSide_800BC7DC(i);
        bit = 1 << i;
        unitReactions_800C9CC8[i].kind_0 = 0x14;
        unitReactions_800C9CC8[i].arg_4 = 0;
        unitReactions_800C9CC8[i].mask_8 = bit;
        unitReactions_800C9CC8[i].targets_C = 0;
        if (curCommand_800C9C88.targets_C & bit)
        {
            target = GetUnitStatus_80014390(i & 0xFF);
            res.areaElement_24 = shownAreaElement_800C9D82;
            res.fixedElement_26 = (signed char)fixedStageElement_800C9D83;
            cmd.targets_C = bit;
            ResolveBattleAction_80012BB0(actor, target, &cmd, &res);
            if (encounterRecord_800ADE78.active_0 == 1)
            {
                sub_800B4390(actor, target, &curCommand_800C9C88, &res, &encounterRecord_800ADE78);
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
                if (target->hp_8.cur_0 < unitHpDamage_800C9D38[i])
                {
                    unitHpDamage_800C9D38[i] = target->hp_8.cur_0;
                }
            }
            else if (unitHpDamage_800C9D38[i] < target->hp_8.cur_0 - target->hp_8.max_2)
            {
                unitHpDamage_800C9D38[i] = target->hp_8.cur_0 - target->hp_8.max_2;
            }
            if (unitMpDamage_800C9D48[i] > 0)
            {
                if (target->mp_C.cur_0 < unitMpDamage_800C9D48[i])
                {
                    unitMpDamage_800C9D48[i] = target->mp_C.cur_0;
                }
            }
            else if (unitMpDamage_800C9D48[i] < target->mp_C.cur_0 - target->mp_C.max_2)
            {
                unitMpDamage_800C9D48[i] = target->mp_C.cur_0 - target->mp_C.max_2;
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
                        escaped = 0;
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
                    defending = target->status_0 & 0x8000;
                    unitReactions_800C9CC8[i].kind_0 = defending ? 0x14 : 0xC;
                    hitSfx_800C9D78 = 0x70;
                    break;
                case 7:
                    unitReactions_800C9CC8[i].kind_0 = 5;
                    unitReactions_800C9CC8[i].arg_4 = res.arg_2;
                    curCommand_800C9C88.arg_4 = res.arg_2;
                    if (GetSealResultFlags_80013358(res.arg_2) == 1)
                    {
                        MarkSpeciesCaptured_800BF9F0(GetEnemySpecies_800A2BE4(i - 4));
                        if (GetCapturedMinionsFromBitfield_8003BA58(GetEnemyAliveMask_800A248C()) == 1)
                        {
                            curCommand_800C9C88.kind_0 = 0x1A;
                        }
                        SetBattleFlag_800BC838(0x40);
                        if (side == 2)
                        {
                            
                            dword_800B1238[i - 4].killer_6 = actingUnit_800C9C7C;
                            dword_800B1238[i - 4].kind_A = curCommand_800C9C88.kind_0;
                            dword_800B1238[i - 4].exp_0 = target->exp_4;
                            dword_800B1238[i - 4].level_8 = target->level_44;
                        }
                    }
                    break;
                }
                if (target->hp_8.cur_0 <= unitHpDamage_800C9D38[i] || (unitStatusInflicted_800C9CA0[i] & 0x600))
                {
                    unitHpDamage_800C9D38[i] = target->hp_8.cur_0;
                    unitReactions_800C9CC8[i].kind_0 = 0xB;
                    if (side == 2)
                    {
                        SetBattleFlag_800BC838(0x40);
                        if (IsBossSpecies_800BF9B4(GetEnemySpecies_800A2BE4(i - 4)) == 1)
                        {
                            SetBattleFlag_800BC838(0x100000);
                        }
                        else
                        {
                            ClearBattleFlag_800BC850(0x100000);
                        }
                        if (GetActiveSwapEnemy_800A2AB4() == 2)
                        {
                            SetBattleFlag_800BC838(2);
                        }
                        
                        dword_800B1238[i - 4].species_4 = GetEnemySpecies_800A2BE4(i - 4);
                        dword_800B1238[i - 4].killer_6 = actingUnit_800C9C7C;
                        dword_800B1238[i - 4].kind_A = curCommand_800C9C88.kind_0;
                        dword_800B1238[i - 4].exp_0 = target->exp_4;
                        dword_800B1238[i - 4].level_8 = target->level_44;
                        if (TestBattleFlag_800BC820(0x100000) == 1)
                        {
                            deathSfx_800C9D80 = 0x1C;
                        }
                        else
                        {
                            deathSfx_800C9D80 = 0x6F;
                        }
                    }
                    else if (side == 0)
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
        if (escaped == 1)
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
    int kind;
    if ((GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 0 && ((kind = curCommand_800C9C88.kind_0) == 5 || kind == 0x1A || kind == 2 || kind == 3 || kind == 7))
        || (GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 1 && ((kind = curCommand_800C9C88.kind_0) - 2 < 2U || kind == 8)))
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
    unsigned char rgb[3];
    rgb[0] = 0xFF;
    rgb[1] = 0xFF;
    rgb[2] = 0xFF;
    StartScreenFlash_8001C02C(rgb);
}

void StartHitNumber_800BF3DC(int unit, int kind, int amount, int pos, int lineOffset)
{
    EventEntry* entry = AllocEventEntry_80043AF8(hitNumberTasks_8008D778);
    if (entry)
    {
        BatHitNumber* hit = entry->buffer;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        hit->kind_0 = kind;
        hit->frame_8 = 0;
        hit->alpha_C = 0;
        hit->amount_4 = amount;
        hit->pos_10 = (unsigned short*)pos;
        hit->lineOffset_14 = lineOffset;
        hit->unit_18 = unit;
        entry->cb_8 = (EventEntryFn)HitNumberTask_800BF4D0;
    }
}

int AnyHitNumberActive_800BF47C()
{
    EventNode* head = hitNumberTasks_8008D778;
    EventNode* node;
    int i = 0;
    int cnt = head->count;
    for (node = head; i < cnt; i++)
    {
        if ((node->entry.flags & 0x8001) == 1)
        {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void HitNumberTask_800BF4D0(EventEntry* task, BatHitNumber* hit)
{
    DVECTOR sxy;
    SVECTOR rel;
    long depth;
    long flag;
    int step;
    rel.vx = hit->pos_10[0];
    rel.vy = hit->pos_10[2];
    rel.vz = hit->pos_10[4];
    rel.vx -= cameraEye_8008D600.vx;
    rel.vy -= cameraEye_8008D600.vy;
    rel.vz -= cameraEye_8008D600.vz;
    RotTransPers(&rel, (long*)&sxy, &depth, &flag);
    hit->frame_8++;
    if (hit->frame_8 > 0x10)
    {
        task->flags = (task->flags & ~1) | 0x8000;
        return;
    }
    if (hit->frame_8 > 8)
    {
        hit->alpha_C -= 4;
    }
    else
    {
        hit->alpha_C += 4;
    }
    step = hit->amount_4 / (0x11 - hit->frame_8);
    step = -step;
    hit->amount_4 += step;
    if (hit->kind_0 == 0)
    {
        AdjustUnitStatById_800127D0(hit->unit_18, 0, step, 0);
        if (GetUnitStatus_80014390((unsigned char)hit->unit_18)->hp_8.cur_0 <= 0)
        {
            KillUnit_800127B8(GetUnitStatus_80014390((unsigned char)hit->unit_18));
        }
    }
    if (hit->kind_0 == 1)
    {
        AdjustUnitStatById_800127D0(hit->unit_18, 2, step, 0);
    }
}
