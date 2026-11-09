// BATTLE.BIN, source file 5 of 6 from 0x800BFBB8
#include "battle.h"

void StopBattleWindows_800BFBB8()
{
    StopAllEventEntries_80043B40(enemyWindowsLayoutTask_8008B568);
    StopAllEventEntries_80043B40(enemyWindowTasks_8008B564);
    StopAllEventEntries_80043B40(actorWindowTask_8008D4B0);
    StopAllEventEntries_80043B40(helpWindowTask_8008D63C);
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
    EventEntry* entry = AllocEventEntry_80043AF8(enemyWindowsLayoutTask_8008B568);
    int alive;
    int count;
    int i;
    int bit;
    if (entry)
    {
        alive = GetEnemyAliveMask_800A248C();
        count = GetCapturedMinionsFromBitfield_8003BA58(alive);
        if (GetActiveSwapEnemy_800A2AB4())
        {
            alive = 0x10;
        }
        enemyWindowFlags_800C9DF8 = 0;
        enemyWindowMask_800C9E24 = 0;
        entry->cb_8 = (EventEntryFn)EnemyWindowsLayoutTask_800BFDEC;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        for (i = 0; i < 3; i++)
        {
            bit = alive & (1 << (i + 4));
            if (bit != 0)
            {
                entry = AllocEventEntry_80043AF8(enemyWindowTasks_8008B564);
                if (entry)
                {
                    BatXY* layout = (BatXY*)((char*)enemyWindowLayouts_800C9140 + ((count - 1) * 12 + i * 4));
                    BatEnemyWindow* win;
                    entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
                    win = entry->buffer;
                    win->slot_0 = i;
                    win->frame_4 = 0;
                    win->from_8[0] = layout->x;
                    win->from_8[1] = layout->y;
                    win->from_8[2] = 0x64;
                    win->from_8[3] = 0x29;
                    entry->cb_8 = (EventEntryFn)EnemyWindowTask_800C0074;
                    enemyWindows_800C9E28[i] = win;
                    enemyWindowPos_800C9E18[i].x = layout->x;
                    enemyWindowPos_800C9E18[i].x = layout->x;
                    enemyWindowPos_800C9E18[i].y = layout->y;
                    enemyWindowTasks_800C9E08[i] = entry;
                }
            }
        }
    }
}

void EnemyWindowsLayoutTask_800BFDEC()
{
    int alive;
    int count;
    int removed;
    int i;
    int k;
    int one;
    int bit;
    BatXY* layout;
    alive = GetEnemyAliveMask_800A248C();
    if (alive != 0 && GetActiveSwapEnemy_800A2AB4() != 0)
    {
        alive = 0x10;
    }
    count = GetCapturedMinionsFromBitfield_8003BA58(alive);
    if (enemyWindowMask_800C9E24 != alive)
    {
        removed = (enemyWindowMask_800C9E24 | alive) ^ alive;
        enemyWindowMask_800C9E24 = alive;
        one = 1;
        enemyWindowFlags_800C9DF8 |= one;
        enemyWindowSlide_800C9E00 = 0;
        for (i = 0; i < 3; i++)
        {
            if (removed & (one << (i + 4)))
            {
                if (GetActiveSwapEnemy_800A2AB4() != 2)
                {
                    enemyWindowTasks_800C9E08[i]->flags &= ~1;
                    enemyWindowTasks_800C9E08[i]->flags |= 0x8000;
                }
                else
                {
                    SetBattleFlag_800BC838(0x10000);
                }
            }
            if (alive & (one << (i + 4)))
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
                if (alive & (bit << (i + 4)))
                {
                    layout = (BatXY*)((char*)enemyWindowLayouts_800C9140 + ((count - 1) * 12 + k * 4));
                    enemyWindows_800C9E28[i]->from_8[0] += (layout->x - enemyWindows_800C9E28[i]->from_8[0]) * enemyWindowSlide_800C9E00 >> 2;
                    enemyWindows_800C9E28[i]->from_8[1] += (layout->y - enemyWindows_800C9E28[i]->from_8[1]) * enemyWindowSlide_800C9E00 >> 2;
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

void EnemyWindowTask_800C0074(EventEntry* task, void* arg)
{
    int slot;
    UnitStatus* status;
    int swap;
    BatEnemyWindow* win;
    if (battleFlags_800B1228 & 0x10000)
    {
        return;
    }
    win = arg;
    swap = GetActiveSwapEnemy_800A2AB4();
    if (swap == 1)
        slot = 0;
    else if (GetActiveSwapEnemy_800A2AB4() == 2)
        slot = 1;
    else
        slot = win->slot_0;
    status = GetUnitStatus_80014390((slot + 4) & 0xFF);
    AddClipDrawAreaPrim_80033308(pOT_8008D454 + 10);
    SetFontClutOffset_8003F900(1, 0);
    InterpolateWindowRect_8004196C((RECT*)win->rect_10, (RECT*)win->from_8, win->frame_4, 4, 9);
    if (IsUncapturableSpecies_800BF980(GetEnemySpecies_800A2BE4(slot)))
    {
        DrawUnitStatusWindow_8002F1C8(status, enemyGaugePreview_800C9164[slot], enemyWindowsHighlight_800C9DFC, enemyHighlightTimes_800C9174[slot], (RECT*)win->rect_10, 10, 1);
    }
    else
    {
        DrawUnitStatusWindow_8002F1C8(status, enemyGaugePreview_800C9164[slot], enemyWindowsHighlight_800C9DFC, enemyHighlightTimes_800C9174[slot], (RECT*)win->rect_10, 10, 0);
    }
    win->frame_4++;
    AddDrawAreaPrim_8003326C((RECT*)win->rect_10, pOT_8008D454 + 10);
}

void StartActorWindow_800C01D8()
{
    EventEntry* entry = AllocEventEntry_80043AF8(actorWindowTask_8008D4B0);
    if (entry != 0)
    {
        BatAnimWindow* win = entry->buffer;
        entry->flags = (entry->flags | 1) & ~0x8000;
        win->frame_0 = 0;
        win->from_4[0] = 0x6E;
        win->from_4[1] = 0xAC;
        win->from_4[2] = 0x64;
        win->from_4[3] = 0x29;
        entry->cb_8 = (EventEntryFn)ActorWindowTask_800C0254;
    }
}


void ActorWindowTask_800C0254(EventEntry* task, void* arg)
{
    BatAnimWindow* win;
    short pos[4];
    WindowStyle box;
    short rect[4];
    UnitStatus* status;
    if (encounterRecord_800ADE78.active_0 == 1 && actingUnit_800C9C7C == 10)
    {
        return;
    }
    if (battleFlags_800B1228 & 0x8000)
    {
        return;
    }
    win = arg;
    status = GetUnitStatus_80014390(shownUnit_800C9C99);
    AddClipDrawAreaPrim_80033308(pOT_8008D454 + 10);
    InterpolateWindowRect_8004196C((RECT*)win->rect_C, (RECT*)win->from_4, win->frame_0, 4, 9);
    if (shownUnit_800C9C99 == 0)
    {
        DrawUnitStatusWindow_8002F1C8(status, previewHpChange_800C9180, actorWindowHighlight_800C9DFD, actorHighlightTime_800C9170, (RECT*)win->rect_C, 10, 2);
    }
    else
    {
        DrawUnitStatusWindow_8002F1C8(status, previewHpChange_800C9180, actorWindowHighlight_800C9DFD, actorHighlightTime_800C9170, (RECT*)win->rect_C, 10, 0);
    }
    if (shownUnit_800C9C99 != 0)
    {
        pos[0] = 0xD2;
        pos[1] = 0xC0;
        DrawMpGauge_8002F120(status, pos, previewMpChange_800C9182, 0xF);
        box.semiTrans_3 = 1;
        rect[2] = 0x64;
        rect[3] = 0x15;
        box.color_0 = saveData_8008B570.uiColor_20.h;
        box.colorSet_2 = 0;
        rect[0] = 0xD2;
        rect[1] = 0xC0;
        DrawWindow_80042460((RECT*)rect, &box, pOT_8008D454 + 15, 0);
    }
    win->frame_0++;
    if (win->frame_0 >= 5)
    {
        win->frame_0 = 4;
    }
    DrawMenuWindowItems_8002F480(status, 0, 0xF, 0);
    AddDrawAreaPrim_8003326C((RECT*)win->rect_C, pOT_8008D454 + 10);
}

void StartHelpWindow_800C0440()
{
    EventEntry* entry = AllocEventEntry_80043AF8(helpWindowTask_8008D63C);
    if (entry)
    {
        helpWindowText_800C9D74 = 0;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        ((BatAnimWindow*)entry->buffer)->frame_0 = 0;
        entry->cb_8 = (EventEntryFn)HelpWindowTask_800C04A4;
    }
}

// Draws the battle help window text (with the empty-cocoon count for help text 9); the void* task buffer is copied into a typed local
void HelpWindowTask_800C04A4(EventEntry* task, void* buf)
{
    BatAnimWindow* win = buf;
    int width;
    short pos[2];
    if (padPressed_8009194C[0] & 0x100)
    {
        saveData_8008B570.flags_0 ^= 0x10;
    }
    if (saveData_8008B570.flags_0 & 0x10)
    {
        return;
    }
    if (helpWindowText_800C9D74 == 0)
    {
        return;
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    width = MeasureTextWidth_8003E4C8(helpWindowText_800C9D74);
    if (battleHelpTexts_800793DC[9] == helpWindowText_800C9D74)
    {
        width += 0x10;
    }
    win->from_4[2] = width + 4;
    win->from_4[3] = 0x14;
    win->from_4[0] = 0xA;
    win->from_4[1] = 0x88;
    pos[0] = win->from_4[0] + 2;
    pos[1] = win->from_4[1] + 3;
    DrawText_8003E91C(2, helpWindowText_800C9D74, pos, 0);
    if (battleHelpTexts_800793DC[9] == helpWindowText_800C9D74)
    {
        pos[0] += width;
        pos[1] += 3;
        DrawNumberRightAlignedFont1_8003F264(pos, GetEmptyCocoons_800AD8E4(), 0);
    }
    InterpolateWindowRect_8004196C((RECT*)win->rect_C, (RECT*)win->from_4, win->frame_0, 4, 7);
    DrawUiColorWindow_800424C0((RECT*)win->rect_C, 0, pOT_8008D454, 0);
    if (++win->frame_0 >= 5)
    {
        win->frame_0 = 4;
    }
    AddDrawAreaPrim_8003326C((RECT*)win->rect_C, pOT_8008D454);
}

void BuildMinionModelReq_800C064C(Minion* minion, BatModelReq* req, struct ModelVramSlot* vram)
{
    unsigned char ids[8];
    int counts[3];
    int self;
    int swap;
    self = GetSpeciesModelDesc_80019C70(minion->species_2)->modelId_0;
    req->count_0 = GetTopSpecies_800338DC(minion->species_4C, ids, counts);
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
            swap = req->nums_10[1];
            req->nums_10[1] = req->nums_10[0];
            req->nums_10[0] = swap;
        }
        else if (req->ids_4[2] == self)
        {
            req->ids_4[2] = req->ids_4[0];
            req->ids_4[0] = self;
            swap = req->nums_10[2];
            req->nums_10[2] = req->nums_10[0];
            req->nums_10[0] = swap;
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
    req->rank_1C = GetRankForLevel_80019A80(minion->status_84.level_44);
    req->f20 = req->count_0 - 1;
    req->f28 = GetSpeciesModelDesc_80019C70(minion->field_3)->modelId_0;
    req->vram_30 = vram;
    req->angle_24 = GetElementModelAngle_800C0904(minion->status_84.element_3E);
    if (req->angle_24 == -1000)
    {
        req->angle_24 = GetSpeciesModelDesc_80019C70(minion->field_3)->field_2 * 2;
    }
    else
    {
        req->angle_24 -= GetSpeciesModelDesc_80019C70(minion->field_3)->field_3 * 2;
        if (req->angle_24 < 0)
        {
            req->angle_24 += 360;
        }
    }
}

int GetElementModelAngle_800C0904(unsigned char* elements)
{
    int count = 0;
    int i;
    int angle;
    for (i = 0; i < 4; i++)
    {
        if (elements[i])
        {
            count++;
        }
    }
    if (count == 1)
    {
        angle = -1000;
    }
    else if (count == 2)
    {
        if (elements[3] && elements[1])
        {
            if (elements[1] < elements[3])
            {
                angle = 0xF5;
            }
            else
            {
                angle = 0x41;
            }
        }
        else if (elements[0] && elements[2])
        {
            if (elements[2] < elements[0])
            {
                angle = 0x14F;
            }
            else
            {
                angle = 0x9B;
            }
        }
        else
        {
            angle = CalcElementAngle_800C09D4(elements);
        }
    }
    else
    {
        angle = CalcElementAngle_800C09D4(elements);
    }
    return angle;
}

int CalcElementAngle_800C09D4(unsigned char* elements)
{
    int t2, t1, t4, t3, t5, t6, t7, t8;
    t1 = sinTable_80084540[0x2E3] * elements[0];
    t2 = sinTable_80084540[0xEE3] * elements[0];
    t3 = sinTable_80084540[0xEE3] * elements[3];
    t4 = sinTable_80084540[0xAE3] * elements[3];
    t5 = sinTable_80084540[0xAE3] * elements[2];
    t6 = sinTable_80084540[0x6E3] * elements[2];
    t7 = sinTable_80084540[0x6E3] * elements[1];
    t8 = sinTable_80084540[0x2E3] * elements[1];
    return ratan2Degrees_8003B56C(t1 + t3 + t5 + t7, t2 + t4 + t6 + t8);
}

void EmptyCallback_800C0A94()
{
}

int GetPartyMinionMask_800C0A9C()
{
    int count = CountMinions_80010548(3);
    int mask = 0;
    int i;
    for (i = 0; i < count; i++)
    {
        mask |= 1 << (i + 1);
    }
    return mask;
}

int LoadSummonedMinion_800C0AEC(int slot, int* pos, int rotY)
{
    BatModelReq req;
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
    BuildMinionModelReq_800C064C(minion, &req, modelVramSlotLists_8007DC74[0]);
    StartModelTask_80010850(&req);
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
    ActorDesc desc;
    Model* model;
    int rank;
    unsigned short* levels;
    // RunModelTask_80010A10 is declared void in funcs.h, but its result is used here
    if (RunModelTask_80010A10(0) != 0)
    {
    model = GetModelTaskModel_80010A44(0);
    rank = GetRankForLevel_80019A80(summonedMinion_800C9188->status_84.level_44);
    desc.modelId_0 = -1;
    desc.kind_4 = 2;
    desc.pos_8[0] = summonedActor_800C9190.x_4;
    desc.pos_8[1] = summonedActor_800C9190.y_8;
    desc.pos_8[2] = summonedActor_800C9190.z_C;
    desc.rot_14[0] = 0;
    desc.rot_14[1] = summonedActor_800C9190.rotY_10;
    desc.rot_14[2] = 0;
    desc.clutRow_1C = 3;
    desc.animIdx_20 = 4;
    desc.frame_24 = -1;
    desc.frameSpeed_28 = 0x1000;
    desc.blendDiv_2C = 4;
    desc.visible_30 = 0;
    desc.model_48 = model;
    desc.bones_34 = defaultBones_80079140;
    desc.baseScale_38 = GetModelBaseScale_80024E90(model, rank);
    desc.boneScale_3C = GetModelBoneScale_80024EC8(model, rank);
    desc.anims_40 = GetModelActorAnims_80024E38(model);
    desc.effectTbl_44 = GetModelEffectTable_80024E64(model);
    desc.hasMatrices_4C = 1;
    summonedActor_800C9190.actor_0 = CreateActor_8001D45C(&desc);
    SetActorGroundMove_8001D68C(summonedActor_800C9190.actor_0, 0);
    levels = GetModelBoneGroupLevels_80024F00(model, rank);
    SetBoneGroupFlags_80019B14(summonedActor_800C9190.actor_0->bones_134, levels, GetModelBoneGroupFlags_80024F38(model, rank));
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
    return IsActorIdle_8001E1C8((void*)summonedActor_800C9190.actor_0);
}

int IsSummonedMinionReady_800C0D88()
{
    return IsActorActionReady_8001E1DC(summonedActor_800C9190.actor_0);
}

void TurnSummonedMinionToward_800C0DB0(int* pos)
{
    SetActorTurnTarget_8001DB00(summonedActor_800C9190.actor_0, pos, 0x55);
}

BatRawTiming* StartMinionAction_800C0DDC(BatRawTiming* out, BattleCmd* cmd, int isReaction)
{
    BatRawTiming timing;
    int mask;
    memset(&timing, 0, 4);
    if (cmd->kind_0 == 0x14)
    {
        *out = timing;
        return out;
    }
    if (cmd->mask_8 & (mask = 1 << (summonedMinionSlot_800C918C + 1)))
    {
        StartCommandAction_80018A4C(&timing, summonedActor_800C9190.actor_0, cmd, 0, isReaction);
    }
    *out = timing;
    return out;
}

int TriggerMinionAction_800C0E84(BattleCmd* cmd, int isReaction)
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

int MinionReturnZero_800C0F14()
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
    return GetMinionStatus_800107A0(3, slot);
}

int* GetSummonedMinionPos_800C0F9C()
{
    return summonedActor_800C9190.actor_0->pos_38;
}

int* GetSummonedMinionBonePos_800C0FAC()
{
    return summonedActor_800C9190.actor_0->bonePos_1C4;
}

void GetSummonedMinionEffectTarget_800C0FC4(EffectTarget* out)
{
    Actor* actor = summonedActor_800C9190.actor_0;
    out->tbl_0 = actor->effectTbl_14C;
    out->pos_4 = actor->pos_38;
    out->bonePos_8 = actor->bonePos_1C4;
    out->boneMatrices_C = actor->boneMatrices_1C8;
    out->boneScale_2C = actor->boneScale_144;
    out->scale_30 = actor->scale_2C;
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

void SeqStopTask_800C106C(unsigned int* flags, BatTimedSeq* seq)
{
    if (--seq->timer_4 < 0)
    {
        *flags = (*flags & ~1) | 0x8000;
        StopSeqSlot_80031334(seq->slot_0);
    }
}

void PlayTimedSeq_800C10B8(int frames, int slot)
{
    EventEntry* entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
    if (frames > 0 && entry)
    {
        BatTimedSeq* seq;
        PlaySeqSlot_80031160(slot, 1);
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        seq = entry->buffer;
        seq->slot_0 = slot;
        seq->timer_4 = frames;
        entry->cb_8 = (EventEntryFn)SeqStopTask_800C106C;
    }
}

void SfxStopTask_800C1140(unsigned int* flags, BatTimedSfx* sfx)
{
    if (--sfx->timer_4 < 0)
    {
        *flags = (*flags & ~1) | 0x8000;
        SfxKeyOff_80031574(sfx->voice_8, sfx->sfx_0.id16);
    }
}

void PlayTimedSfx_800C1190(int frames, int sfx)
{
    EventEntry* entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
    if (frames > 0 && entry)
    {
        BatTimedSfx* stop;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        stop = entry->buffer;
        stop->timer_4 = frames;
        stop->voice_8 = SfxKeyOn_800314F4(sfx);
        stop->sfx_0.id = sfx;
        entry->cb_8 = (EventEntryFn)SfxStopTask_800C1140;
    }
}

typedef struct BatDrop
{
    int frame_0;
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
} BatDrop;

void DropSpriteTask_800C1220(EventEntry* task, BatDrop* drop)
{
    int pos[3];
    short size[4];
    short offset[4];
    EffectSprite* sprite;
    EffectSpriteFrame* frame;
    drop->vel_28[0] = drop->vel_28[0] * 15 / 16;
    drop->vel_28[1] = drop->vel_28[1] * 15 / 16 + drop->size_8 / 8;
    drop->vel_28[2] = drop->vel_28[2] * 15 / 16;
    drop->pos_10[0] += drop->vel_28[0];
    drop->pos_10[1] += drop->vel_28[1];
    drop->pos_10[2] += drop->vel_28[2];
    sprite = drop->anim_40;
    frame = sprite->frames_8[0];
    pos[0] = drop->pos_10[0];
    pos[1] = drop->pos_10[1];
    pos[2] = drop->pos_10[2];
    pos[0] /= 1024;
    pos[1] /= 1024;
    pos[2] /= 1024;
    if (levantPos_8008BD18.pos.y < pos[1] || drop->size_8 < 0x800)
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
    drop->size_8 -= 0x40;
    size[0] = frame->size_C[0] * drop->size_8 / 4096;
    size[1] = frame->size_C[1] * drop->size_8 / 4096;
    offset[0] = 0x14;
    offset[1] = 0;
    offset[2] = 0;
    drop->rot_34[1] += 0x80;
    DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)pos, (SVECTOR*)drop->rot_34, &frame->u_0, &frame->w_4, &frame->pivotX_8, size, (SVECTOR*)offset, frame->rgb_18, 0, 0x30, pOT_8008D690);
}

void DropTrailTask_800C1450(EventEntry* task, BatDropTrail* trail)
{
    int pos[3];
    EffectSpriteFrame* frame;
    int i;
    EventEntry* entry;
    BatDrop* drop;
    EffectSprite* path = trail->path_88;
    if (trail->time_4 / 4096 < path->count_0)
    {
        frame = path->frames_8[trail->time_4 / 4096];
        pos[0] = frame->pos_10[0] + trail->pos_44[0];
        pos[1] = frame->pos_10[1] + trail->pos_44[1];
        pos[2] = frame->pos_10[2] + trail->pos_44[2];
        if (((trail->time_4 / 4096) & 3) == 0)
        {
            trail->count_0++;
            for (i = 0; i < 3; i++)
            {
                entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
                if (entry)
                {
                    entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
                    drop = entry->buffer;
                    drop->pos_10[0] = pos[0];
                    drop->pos_10[1] = pos[1];
                    drop->pos_10[2] = pos[2];
                    drop->pos_10[0] <<= 10;
                    drop->pos_10[1] <<= 10;
                    drop->pos_10[2] <<= 10;
                    if (trail->count_0 & 1)
                    {
                        drop->anim_40 = trail->animA_8C;
                    }
                    else
                    {
                        drop->anim_40 = trail->animB_90;
                    }
                    drop->vel_28[0] = 0;
                    drop->vel_28[1] = 0;
                    drop->vel_28[2] = 0;
                    drop->rot_34[0] = 0;
                    drop->rot_34[1] = i * 0x555;
                    drop->rot_34[2] = 0;
                    drop->frame_0 = 0;
                    drop->size_8 = (rand() & 0xFFF) + 0x800;
                    entry->cb_8 = (EventEntryFn)DropSpriteTask_800C1220;
                }
            }
        }
        trail->time_4 += trail->step_8;
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

void SpawnHomingSparks_800C1654(int* pos, short* rot, void* sprite, int speed, int* target, int* offset)
{
    int i;
    for (i = 0; i < 30; i++)
    {
        EventEntry* entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
        if (entry)
        {
            BatSpark* spark = entry->buffer;
            entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
            spark->base_1C[0] = pos[0];
            spark->base_1C[1] = pos[1];
            spark->base_1C[2] = pos[2];
            spark->pos_10[0] = pos[0];
            spark->pos_10[1] = pos[1];
            spark->pos_10[2] = pos[2];
            spark->rot_34[0] = rot[0];
            spark->rot_34[1] = rot[1];
            spark->rot_34[2] = rot[2];
            spark->anim_3C = sprite;
            spark->vel_28[0] = ((rand() & 0x7F) - 0x3F) << 10;
            spark->vel_28[1] = -(rand() & 0x3F) << 10;
            spark->vel_28[2] = ((rand() & 0x7F) - 0x3F) << 10;
            spark->rot_34[0] = 0;
            spark->rot_34[1] = 0;
            spark->rot_34[2] = 0;
            spark->frame_0 = 0;
            spark->speed_8 = ((rand() & 0xFFF) >> 1) + 0x800;
            spark->target_40 = target;
            spark->offset_44 = offset;
            entry->cb_8 = (EventEntryFn)HomingSparkTask_800C17EC;
        }
    }
}

void HomingSparkTask_800C17EC(EventEntry* task, BatSpark* spark)
{
    int step[3];
    EffectSprite* sprite;
    int i;
    EffectSpriteFrame* frame;
    int* target = spark->target_40;
    int* offset = spark->offset_44;
    spark->vel_28[0] = spark->vel_28[0] * 31 / 32 + ((target[0] + offset[0] - spark->pos_10[0]) << 5);
    spark->vel_28[1] = spark->vel_28[1] * 31 / 32 + ((target[1] + offset[1] - spark->pos_10[1]) << 5);
    spark->vel_28[2] = spark->vel_28[2] * 31 / 32 + ((target[2] + offset[2] - spark->pos_10[2]) << 5);
    step[0] = spark->vel_28[0] / 1024;
    step[1] = spark->vel_28[1] / 1024;
    step[2] = spark->vel_28[2] / 1024;
    spark->pos_10[0] += step[0];
    spark->pos_10[1] += step[1];
    spark->pos_10[2] += step[2];
    sprite = spark->anim_3C;
    if (spark->frame_0 / 4096 < sprite->count_0)
    {
        for (i = 0; i < sprite->frameCounts_4[spark->frame_0 / 4096]; i++)
        {
            frame = sprite->frames_8[spark->frame_0 / 4096] + i;
            DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)spark->pos_10, (SVECTOR*)spark->rot_34, &frame->u_0, &frame->w_4, &frame->pivotX_8, frame->size_C, &zeroSvector_800795D4, frame->rgb_18, 0, 0x30, pOT_8008D690);
        }
        spark->frame_0 += spark->speed_8;
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

void SpawnSpriteAnim_800C1A5C(int* pos, short* rot, void* sprite, int speed)
{
    EventEntry* entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
    if (entry)
    {
        BatSpark* spark;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        spark = entry->buffer;
        spark->pos_10[0] = pos[0];
        spark->pos_10[1] = pos[1];
        spark->pos_10[2] = pos[2];
        spark->rot_34[0] = rot[0];
        spark->rot_34[1] = rot[1];
        spark->rot_34[2] = rot[2];
        spark->anim_3C = sprite;
        spark->frame_0 = 0;
        spark->speed_8 = speed;
        entry->cb_8 = (EventEntryFn)SpriteAnimTask_800C1B2C;
    }
}

// SpriteAnimTask_800C1B2C: draws the current frame of a sprite animation at spark->pos_10 and advances it by speed_8; ends the task after the last frame
// (the buffer arrives as void* and is copied into a typed local: a typed param keeps its doubled REG_EQUIV live length and loses s0)
void SpriteAnimTask_800C1B2C(EventEntry* task, void* buf)
{
    BatSpark* spark = buf;
    EffectSprite* sprite = spark->anim_3C;
    int i;
    EffectSpriteFrame* frame;
    if (spark->frame_0 / 4096 < sprite->count_0)
    {
        for (i = 0; i < sprite->frameCounts_4[spark->frame_0 / 4096]; i++)
        {
            frame = sprite->frames_8[spark->frame_0 / 4096] + i;
            DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)spark->pos_10, (SVECTOR*)spark->rot_34, &frame->u_0, &frame->w_4, &frame->pivotX_8, frame->size_C, (SVECTOR*)frame->pos_10, frame->rgb_18, 0, 0x30, pOT_8008D690);
        }
        spark->frame_0 += spark->speed_8;
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

void SpawnBounceSparks_800C1C5C(int* pos, short* rot, void* sprite, int speed)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        EventEntry* entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
        if (entry)
        {
            BatSpark* spark = entry->buffer;
            entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
            spark->pos_10[0] = pos[0];
            spark->pos_10[1] = pos[1];
            spark->pos_10[2] = pos[2];
            spark->rot_34[0] = rot[0];
            spark->rot_34[1] = rot[1];
            spark->rot_34[2] = rot[2];
            spark->anim_3C = sprite;
            spark->vel_28[0] = ((rand() & 0x3F) - 0x1F) << 10;
            spark->vel_28[1] = ((rand() & 0x3F) - 0x1F) << 10;
            spark->vel_28[2] = ((rand() & 0x3F) - 0x1F) << 10;
            spark->frame_0 = 0;
            spark->speed_8 = ((rand() & 0xFFF) >> 1) + 0x800;
            entry->cb_8 = (EventEntryFn)BounceSparkTask_800C1DA4;
        }
    }
}

void BounceSparkTask_800C1DA4(EventEntry* task, BatSpark* spark)
{
    int step[3];
    EffectSprite* sprite;
    int i;
    EffectSpriteFrame* frame;
    SaveData* sd;
    spark->vel_28[0] = spark->vel_28[0] * 15 / 16;
    spark->vel_28[1] = spark->vel_28[1] * 15 / 16 + 0x200;
    spark->vel_28[2] = spark->vel_28[2] * 15 / 16;
    step[0] = spark->vel_28[0] / 1024;
    step[1] = spark->vel_28[1] / 1024;
    step[2] = spark->vel_28[2] / 1024;
    spark->pos_10[0] += step[0];
    spark->pos_10[1] += step[1];
    spark->pos_10[2] += step[2];
    sd = &saveData_8008B570;
    if (spark->pos_10[1] > sd->levant_7A8.pos.y)
    {
        spark->vel_28[1] = -spark->vel_28[1];
        spark->pos_10[1] = sd->levant_7A8.pos.y;
    }
    sprite = spark->anim_3C;
    if (spark->frame_0 / 4096 < sprite->count_0)
    {
        for (i = 0; i < sprite->frameCounts_4[spark->frame_0 / 4096]; i++)
        {
            frame = sprite->frames_8[spark->frame_0 / 4096] + i;
            DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)spark->pos_10, (SVECTOR*)spark->rot_34, &frame->u_0, &frame->w_4, &frame->pivotX_8, frame->size_C, (SVECTOR*)frame->pos_10, frame->rgb_18, 0, 0x30, pOT_8008D690);
        }
        spark->frame_0 += spark->speed_8;
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

void SpawnRisingSparks_800C1FFC(int* pos, short* rot, void* sprite, int speed, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
        if (entry)
        {
            BatSpark* spark = entry->buffer;
            entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
            spark->base_1C[0] = pos[0];
            spark->base_1C[1] = pos[1];
            spark->base_1C[2] = pos[2];
            spark->rot_34[0] = rot[0];
            spark->rot_34[1] = rot[1];
            spark->rot_34[2] = rot[2];
            spark->anim_3C = sprite;
            spark->vel_28[0] = ((rand() & 0x3F) - 0x1F) << 10;
            spark->vel_28[1] = -(rand() & 0x1F) << 10;
            spark->vel_28[2] = ((rand() & 0x3F) - 0x1F) << 10;
            spark->pos_10[0] = 0;
            spark->pos_10[1] = 0;
            spark->pos_10[2] = 0;
            spark->frame_0 = 0;
            spark->speed_8 = speed + ((rand() & 0xFFF) >> 1) + 0x800;
            entry->cb_8 = (EventEntryFn)RisingSparkTask_800C2170;
        }
    }
}

void RisingSparkTask_800C2170(EventEntry* task, BatSpark* spark)
{
    EffectSprite* sprite;
    int i;
    EffectSpriteFrame* frame;
    spark->rot_34[1] += 0x40;
    spark->vel_28[0] = spark->vel_28[0] * 12 / 13;
    spark->vel_28[1] = spark->vel_28[1] * 12 / 13 - 0x400;
    spark->vel_28[2] = spark->vel_28[2] * 12 / 13;
    {
        int step[3];
        step[0] = spark->vel_28[0] / 1024;
        step[1] = spark->vel_28[1] / 1024;
        step[2] = spark->vel_28[2] / 1024;
        spark->pos_10[0] += step[0];
        spark->pos_10[1] += step[1];
        spark->pos_10[2] += step[2];
    }
    sprite = spark->anim_3C;
    if (spark->frame_0 / 4096 < sprite->count_0)
    {
        for (i = 0; i < sprite->frameCounts_4[spark->frame_0 / 4096]; i++)
        {
            short offset[3];
            frame = sprite->frames_8[spark->frame_0 / 4096] + i;
            offset[0] = spark->pos_10[0];
            offset[1] = spark->pos_10[1];
            offset[2] = spark->pos_10[2];
            DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)spark->base_1C, (SVECTOR*)spark->rot_34, &frame->u_0, &frame->w_4, &frame->pivotX_8, frame->size_C, (SVECTOR*)offset, frame->rgb_18, 0, 0x30, pOT_8008D690);
        }
        spark->frame_0 += spark->speed_8;
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

// ShatterTask_800C23D0: after 30 frames plays sfx 0x4F, spawns a burst sprite and 24 ShardTask_800C273C shards flying out from src->pos_10
// (the buffer arrives as void* and is copied into a typed local: a typed param keeps its doubled REG_EQUIV live length and loses s5)
void ShatterTask_800C23D0(EventEntry* task, void* buf)
{
    int i;
    int angle;
    int pitch;
    int modelIdx;
    EventEntry* entry;
    BatShard* shard;
    BatSpark* src = buf;
    if (++src->frame_0 >= 30)
    {
        PlaySfx_80031494(0x4F);
        SpawnSpriteAnim_800C1A5C(src->pos_10, (short*)&zeroSvector_800795D4, &effectFile_80091BD0.sprites_20[FindEffectIndex_80020F00(&effectFile_80091BD0, 0, 0x21)], 0x1000);
        for (i = 0; i < 24; i++)
        {
            entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
            if (entry)
            {
                shard = entry->buffer;
                shard->base_1C[0] = src->pos_10[0];
                shard->base_1C[1] = src->pos_10[1];
                shard->base_1C[2] = src->pos_10[2];
                shard->frame_0 = 0;
                shard->scale_C = (rand() & 0x7FF) + 0x800;
                shard->pos_10[0] = 0;
                shard->pos_10[1] = 0;
                shard->pos_10[2] = 0;
                angle = (i << 12) / 24;
                shard->vel_28[0] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[angle & 0xFFF] / 4096;
                shard->vel_28[2] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[(angle + 0x400) & 0xFFF] / 4096;
                pitch = rand() & 0x1FF;
                angle = pitch + 0x200;
                shard->vel_28[1] = -((rand() & 0x1F) + 0x28) * sinTable_80084540[angle] / 4096;
                shard->vel_28[0] = shard->vel_28[0] * sinTable_80084540[pitch | 0x600] / 4096;
                shard->vel_28[2] = shard->vel_28[2] * sinTable_80084540[pitch | 0x600] / 4096;
                shard->vel_28[0] <<= 10;
                shard->vel_28[1] <<= 10;
                shard->vel_28[2] <<= 10;
                shard->rot_34[0] = rand() & 0x1000;
                shard->rot_34[1] = rand() & 0x1000;
                shard->rot_34[2] = rand() & 0x1000;
                shard->rot_34[3] = (rand() & 0x1FF) + 0x100;
                modelIdx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, 0x19);
                entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
                {
                    EffectModel* model = &effectFile_80091BD0.models_28[modelIdx];
                    shard->obj_3C = model->ftg_4 + i % 8;
                }
                entry->cb_8 = (EventEntryFn)ShardTask_800C273C;
            }
        }
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

void ShardTask_800C273C(EventEntry* task, BatShard* shard)
{
    int pos[4];
    int scale[3];
    shard->vel_28[1] += 0x1000;
    shard->vel_28[0] = shard->vel_28[0] * 31 / 32;
    shard->vel_28[1] = shard->vel_28[1] * 31 / 32;
    shard->vel_28[2] = shard->vel_28[2] * 31 / 32;
    shard->pos_10[0] += shard->vel_28[0];
    shard->pos_10[1] += shard->vel_28[1];
    shard->pos_10[2] += shard->vel_28[2];
    if (shard->pos_10[1] > 0)
    {
        shard->vel_28[1] = -shard->vel_28[1] * 3 / 4;
        shard->pos_10[1] = 0;
        if (shard->vel_28[1] >= -0xFFF)
        {
            task->flags = (task->flags & ~1) | 0x8000;
        }
    }
    shard->rot_34[2] += shard->rot_34[3];
    scale[0] = scale[1] = scale[2] = shard->scale_C;
    pos[0] = shard->base_1C[0] + shard->pos_10[0] / 1024;
    pos[1] = shard->base_1C[1] + shard->pos_10[1] / 1024;
    pos[2] = shard->base_1C[2] + shard->pos_10[2] / 1024;
    DrawFtgObjectAtSlot0_8004D1EC(shard->obj_3C, pOT_8008D690, pos, shard->rot_34, cameraState_8008D4F0.ent_44, 0x30, scale);
    shard->frame_0++;
}

void SpawnShatterEffect_800C2914(BatShatterSource* src, int id)
{
    EventEntry* entry;
    BatShard* shard;
    int i;
    int angle;
    int modelIdx;
    int dir[3];
    entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
    if (entry)
    {
        shard = entry->buffer;
        shard->pos_10[0] = src->pos_1C[0];
        shard->pos_10[1] = src->pos_1C[1];
        shard->pos_10[2] = src->pos_1C[2];
        shard->frame_0 = 0;
        modelIdx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, id);
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        shard->obj_3C = &effectFile_80091BD0.models_28[modelIdx];
        entry->cb_8 = (EventEntryFn)ShatterTask_800C23D0;
    }
    for (i = 0; i < 8; i++)
    {
        entry = AllocEventEntry_80043AF8(miscTasks_8008D60C);
        if (entry)
        {
            shard = entry->buffer;
            shard->base_1C[0] = src->pos_1C[0];
            shard->base_1C[1] = src->pos_1C[1];
            shard->base_1C[2] = src->pos_1C[2];
            shard->frame_0 = 0;
            shard->scale_C = (rand() & 0x7FF) + 0x800;
            angle = i << 9;
            shard->pos_10[0] = sinTable_80084540[angle & 0xFFF] * 300 / 4096;
            shard->pos_10[2] = sinTable_80084540[(angle + 0x400) & 0xFFF] * 300 / 4096;
            angle = rand() & 0x3FF;
            shard->pos_10[1] = -(sinTable_80084540[angle] * 300) / 4096;
            shard->pos_10[0] = shard->pos_10[0] * sinTable_80084540[(angle + 0x400) & 0xFFF] / 4096;
            shard->pos_10[2] = shard->pos_10[2] * sinTable_80084540[(angle + 0x400) & 0xFFF] / 4096;
            shard->pos_10[0] <<= 10;
            shard->pos_10[1] <<= 10;
            shard->pos_10[2] <<= 10;
            shard->vel_28[0] = -shard->pos_10[0] / 4;
            shard->vel_28[1] = -shard->pos_10[1] / 4;
            shard->vel_28[2] = -shard->pos_10[2] / 4;
            dir[0] = shard->vel_28[0] / 1024;
            dir[1] = shard->vel_28[1] / 1024;
            dir[2] = shard->vel_28[2] / 1024;
            VectorToAngles_8003B5D4(dir, shard->rot_34);
            shard->rot_34[2] = rand() & 0x1000;
            modelIdx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, id);
            entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
            shard->obj_3C = &effectFile_80091BD0.models_28[modelIdx];
            entry->cb_8 = (EventEntryFn)ImplodeShardTask_800C2CD8;
        }
    }
}

void ImplodeShardTask_800C2CD8(EventEntry* task, BatShard* shard)
{
    EffectModel* model = shard->obj_3C;
    int pos[4];
    int scale[3];
    if (shard->frame_0 >= 0x1A)
    {
        if (shard->frame_0 < 0x1E)
        {
            shard->pos_10[0] += shard->vel_28[0];
            shard->pos_10[1] += shard->vel_28[1];
            shard->pos_10[2] += shard->vel_28[2];
        }
        else
        {
            task->flags = (task->flags & ~1) | 0x8000;
        }
    }
    shard->rot_34[2] += 0xAA;
    scale[0] = scale[1] = scale[2] = shard->scale_C;
    pos[0] = shard->base_1C[0] + shard->pos_10[0] / 1024;
    pos[1] = shard->base_1C[1] + shard->pos_10[1] / 1024;
    pos[2] = shard->base_1C[2] + shard->pos_10[2] / 1024;
    DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, pos, shard->rot_34, cameraState_8008D4F0.ent_44, 0x30, scale);
    shard->frame_0++;
}

void SpawnSpriteTrails_800C2E28(int* pos, short* rot, void* sprite, void* model, int speed, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
        if (entry)
        {
            BatSpriteTrail* trail;
            entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
            trail = entry->buffer;
            trail->pos_44[0] = pos[0];
            trail->pos_44[1] = pos[1];
            trail->pos_44[2] = pos[2];
            trail->trail_50[0].x = pos[0];
            trail->trail_50[0].y = pos[1];
            trail->trail_50[0].z = pos[2];
            trail->trail_50[1].x = pos[0];
            trail->trail_50[1].y = pos[1];
            trail->trail_50[1].z = pos[2];
            trail->trail_50[2].x = pos[0];
            trail->trail_50[2].y = pos[1];
            trail->trail_50[2].z = pos[2];
            trail->rot_80[0] = rot[0];
            trail->rot_80[1] = rot[1];
            trail->rot_80[2] = rot[2];
            trail->anim_88 = sprite;
            trail->clip_8C = model;
            trail->rot_80[0] = 0;
            trail->rot_80[2] = 0;
            trail->frame_0 = 0;
            trail->count_4 = 0;
            trail->speed_8 = speed;
            trail->rot_80[1] = (i << 12) / count;
            entry->cb_8 = (EventEntryFn)SpriteTrailTask_800C2FC8;
        }
    }
}

void SpriteTrailTask_800C2FC8(EventEntry* task, BatSpriteTrail* trail)
{
    EffectSprite* sprite = trail->anim_88;
    int i;
    int* offset;
    EffectSpriteFrame* frame;
    if (trail->frame_0 / 4096 < sprite->count_0)
    {
        offset = 0;
        for (i = 0; i < sprite->frameCounts_4[trail->frame_0 / 4096]; i++)
        {
            frame = sprite->frames_8[trail->frame_0 / 4096] + i;
            offset = (int*)DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)trail->pos_44, (SVECTOR*)trail->rot_80, &frame->u_0, &frame->w_4, &frame->pivotX_8, frame->size_C, (SVECTOR*)frame->pos_10, frame->rgb_18, 0, 0x30, pOT_8008D690);
        }
        trail->trail_50[0].x = trail->pos_44[0] + offset[0];
        trail->trail_50[0].y = trail->pos_44[1] + offset[1];
        trail->trail_50[0].z = trail->pos_44[2] + offset[2];
        if (trail->count_4 == 0)
        {
            trail->trail_50[3].x = trail->trail_50[0].x;
            trail->trail_50[3].y = trail->trail_50[0].y;
            trail->trail_50[3].z = trail->trail_50[0].z;
            trail->trail_50[2].x = trail->trail_50[0].x;
            trail->trail_50[2].y = trail->trail_50[0].y;
            trail->trail_50[2].z = trail->trail_50[0].z;
            trail->trail_50[1].x = trail->trail_50[0].x;
            trail->trail_50[1].y = trail->trail_50[0].y;
            trail->trail_50[1].z = trail->trail_50[0].z;
        }
        trail->frame_0 += trail->speed_8;
        DrawFtgObjectAt_80044D0C(trail->clip_8C->ftg_4, pOT_8008D690, (VECTOR*)&trail->trail_50[0], (SVECTOR*)trail->rot_80, cameraState_8008D4F0.ent_44, 0x30, 0, 0);
        DrawFtgObjectAt_80044D0C(trail->clip_8C->ftg_4 + 1, pOT_8008D690, (VECTOR*)&trail->trail_50[1], (SVECTOR*)trail->rot_80, cameraState_8008D4F0.ent_44, 0x30, 0, 1);
        DrawFtgObjectAt_80044D0C(trail->clip_8C->ftg_4 + 2, pOT_8008D690, (VECTOR*)&trail->trail_50[2], (SVECTOR*)trail->rot_80, cameraState_8008D4F0.ent_44, 0x30, 0, 2);
        DrawFtgObjectAt_80044D0C(trail->clip_8C->ftg_4 + 3, pOT_8008D690, (VECTOR*)&trail->trail_50[3], (SVECTOR*)trail->rot_80, cameraState_8008D4F0.ent_44, 0x30, 0, 3);
        DrawSpriteVtxQuadsGT4_800459E4(defaultBoneSlots_800C91A4, &trail->clip_8C->mats_8, pOT_8008D690, 0x30);
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
    if (++trail->count_4 & 1)
    {
        trail->trail_50[3].x = trail->trail_50[2].x;
        trail->trail_50[3].y = trail->trail_50[2].y;
        trail->trail_50[3].z = trail->trail_50[2].z;
        trail->trail_50[2].x = trail->trail_50[1].x;
        trail->trail_50[2].y = trail->trail_50[1].y;
        trail->trail_50[2].z = trail->trail_50[1].z;
        trail->trail_50[1].x = trail->trail_50[0].x;
        trail->trail_50[1].y = trail->trail_50[0].y;
        trail->trail_50[1].z = trail->trail_50[0].z;
    }
}

int SpawnModelAnim_800C32DC(int* pos, int modelId, int clip, int rotY)
{
    EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    BatModelAnim* anim;
    int idx;
    EffectModel* model;
    if (entry != 0)
    {
    anim = entry->buffer;
    anim->pos_44[0] = pos[0];
    anim->pos_44[1] = pos[1];
    anim->pos_44[2] = pos[2];
    anim->frame_0 = 0;
    anim->speed_8 = 0;
    anim->rot_82 = rotY;
    idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, modelId);
    entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
    model = &effectFile_80091BD0.models_28[idx];
    anim->clip_88 = model + clip;
    entry->cb_8 = (EventEntryFn)ModelAnimTask_800C33E4;
    return model->frameCount_14;
    }
    return -1;
}

// Plays one frame of an effect clip's keyed model animation; the void* task buffer is copied into a typed local
void ModelAnimTask_800C33E4(EventEntry* task, void* buf)
{
    BatModelAnim* anim = buf;
    EffectModel* clip = anim->clip_88;
    int any;
    int i;
    EffectKey* key;
    int pos[3];
    short rot[3];
    any = 0;
    if (anim->frame_0 < clip->frameCount_14)
    {
        for (i = 0; i < clip->keyCount_10; i++)
        {
            key = &clip->keys_18[i + anim->frame_0 * clip->keyCount_10];
            if (key->model_0 >= 0)
            {
                rot[0] = key->rot_10[0];
                rot[1] = key->rot_10[1];
                rot[2] = key->rot_10[2];
                rot[1] += anim->rot_82;
                pos[0] = anim->pos_44[0] + key->x_4 * sinTable_80084540[(anim->rot_82 + 0x400) & 0xFFF] / 4096 + key->z_C * sinTable_80084540[anim->rot_82 & 0xFFF] / 4096;
                pos[1] = anim->pos_44[1] + key->y_8;
                pos[2] = anim->pos_44[2] - key->x_4 * sinTable_80084540[anim->rot_82 & 0xFFF] / 4096 + key->z_C * sinTable_80084540[(anim->rot_82 + 0x400) & 0xFFF] / 4096;
                DrawFtgObjectAt_80044D0C(&clip->ftg_4[key->model_0], pOT_8008D690, (VECTOR*)pos, (SVECTOR*)rot, cameraState_8008D4F0.ent_44, (0x1000 - key->alpha_2) << 16 | 0x80 | key->mode_24, (VECTOR*)key->f18, i);
                if (clip->ftg_4[key->model_0].texSpriteCount_48)
                {
                    any = 1;
                }
            }
        }
        anim->frame_0++;
        if (any)
        {
            if (clip->mats_8.count_0)
            {
                DrawSpriteVtxQuadsGT4_800459E4(defaultBoneSlots_800C91A4, &clip->mats_8, pOT_8008D690, 0x30);
            }
        }
        else if (clip->mats_8.count_0)
        {
            DrawSpriteVtxQuadsG4_80045E48(&clip->mats_8, pOT_8008D690, 0x30);
        }
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

void GlowTask_800C371C(EventEntry* task, void* arg)
{
    unsigned char col[4] = { 0xE8, 0xE8, 0x80, 0 };
    BatGlow* glow = arg;
    EffectModel* model = glow->model_88;
    if (glow->frame_0 < glow->end_4 && effectOutcomeFlag_8008D780[0] == 0)
    {
        int scale[4];
        int pos[4];
        int alpha;
        glow->alpha_30 += 0x100;
        if (glow->alpha_30 > 0x1000)
        {
            glow->alpha_30 = 0x1000;
        }
        scale[0] = glow->scale_A0[0] * 3 / 2;
        scale[1] = glow->scale_A0[1] * 3 / 2;
        scale[2] = glow->scale_A0[2] * 3 / 2;
        alpha = glow->alpha_30;
        pos[0] = glow->path_20[glow->idx_98 * 3 + 0] + glow->base_1C[0];
        pos[1] = glow->path_20[glow->idx_98 * 3 + 1] + glow->base_1C[1];
        pos[2] = glow->path_20[glow->idx_98 * 3 + 2] + glow->base_1C[2];
        LerpFtgObject_8003A6C4(alpha, model->ftg_4, model->ftg_4 + 1, glow->work_94);
        DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, pos, &zeroSvector_800795D4, cameraState_8008D4F0.ent_44, ((0x1000 - alpha) << 16) | 0xB0, scale);
        SetPointLight_800C4090(glow->pos_44, col, 0x5DC, glow->alpha_30);
        glow->frame_0++;
    }
    else
    {
        int scale[4];
        int pos[4];
        int alpha;
        scale[0] = glow->scale_A0[0] * 3 / 2;
        scale[1] = glow->scale_A0[1] * 3 / 2;
        scale[2] = glow->scale_A0[2] * 3 / 2;
        alpha = glow->alpha_30;
        pos[0] = glow->path_20[glow->idx_98 * 3 + 0] + glow->base_1C[0];
        pos[1] = glow->path_20[glow->idx_98 * 3 + 1] + glow->base_1C[1];
        pos[2] = glow->path_20[glow->idx_98 * 3 + 2] + glow->base_1C[2];
        LerpFtgObject_8003A6C4(alpha, model->ftg_4, model->ftg_4 + 1, glow->work_94);
        DrawFtgObjectAtSlot0_8004D1EC(model->ftg_4, pOT_8008D690, pos, &zeroSvector_800795D4, cameraState_8008D4F0.ent_44, ((0x1000 - alpha) << 16) | 0xB0, scale);
        if (glow->alpha_30 == 0x1000)
        {
            SpawnOrb_800C3B50(pos, 0x25);
        }
        SetPointLight_800C4090(glow->pos_44, col, 0x5DC, glow->alpha_30);
        if (glow->alpha_30 <= 0)
        {
            ClearPointLight_800C410C();
            FreeFtgObjectData_80021804(glow->work_94, HEAP_MALLOC3);
            free3_8003FC6C(glow->work_94);
            task->flags = (task->flags & ~1) | 0x8000;
        }
        glow->alpha_30 -= 0x100;
    }
}


void SpawnOrb_800C3B50(int* pos, int id)
{
    EventEntry* entry = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    BatOrb* orb;
    EffectModel* model;
    BatHero* hero;
    int idx;
    short* flag;
    if (entry == 0)
    {
        return;
    }
    orb = entry->buffer;
    orb->pos_44[0] = pos[0];
    orb->pos_44[1] = pos[1];
    orb->pos_44[2] = pos[2];
    orb->frame_0 = 0;
    orb->fx_E = FindEffectIndex_80020F00(&effectFile_80091BD0, 0, id);
    orb->alpha_30 = 0x1000;
    orb->f34 = 0;
    orb->rot_80[2] = 0;
    orb->rot_80[1] = 0;
    orb->rot_80[0] = 0;
    orb->vel_38[0] = 0;
    orb->vel_38[1] = -0xC8;
    orb->vel_38[2] = 0;
    entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
    flag = &effectOutcomeFlag_8008D780[1];
    if (*flag == 0)
    {
        idx = FindEffectIndex_80020F00(&effectFile_80091BD0, 1, 0x1F);
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        model = &effectFile_80091BD0.models_28[idx];
        orb->clip_88 = model;
        orb->model_94 = malloc3_8003FC4C(sizeof(*orb->model_94));
        CopyFtgObject_800218A8(model->ftg_4, orb->model_94, HEAP_MALLOC3);
        DiffFtgObjects_80039FE4(model->ftg_4, model->ftg_4 + 1, orb->model_94);
        hero = gameTask_8008B4A4->entry.buffer;
        orb->pos_44[0] = hero->pos_5E4[0];
        orb->pos_44[1] = hero->pos_5E4[1];
        orb->pos_44[2] = hero->pos_5E4[2];
        orb->pos_44[0] += levantPos_8008BD18.pos.x;
        orb->pos_44[1] += levantPos_8008BD18.pos.y;
        orb->pos_44[2] += levantPos_8008BD18.pos.z;
        entry->cb_8 = (EventEntryFn)OrbFadeTask_800C3D34;
        PlaySfx_80031494(0x3F);
    }
    else
    {
        PlaySfx_80031494(0x47);
        entry->cb_8 = (EventEntryFn)OrbHomingTask_800C3DF8;
    }
}

void OrbFadeTask_800C3D34(EventEntry* task, BatOrb* orb)
{
    EffectModel* clip = orb->clip_88;
    int alpha = orb->alpha_30 - 0x100;
    orb->alpha_30 = alpha;
    if (alpha > 0)
    {
        LerpFtgObject_8003A6C4(alpha, clip->ftg_4, clip->ftg_4 + 1, orb->model_94);
    }
    else
    {
        task->flags = (task->flags & ~1) | 0x8000;
        FreeFtgObjectData_80021804(orb->model_94, HEAP_MALLOC3);
        free3_8003FC6C(orb->model_94);
    }
    DrawFtgObjectAtSlot0_8004D1EC(clip->ftg_4, pOT_8008D690, orb->pos_44, orb->rot_80, cameraState_8008D4F0.ent_44, ((0x1000 - orb->alpha_30) << 16) | 0xB0, 0);
}

void OrbHomingTask_800C3DF8(EventEntry* task, BatOrb* orb)
{
    int target[3];
    BatHero* hero;
    BatOrb* orbCopy;
    orbCopy = orb;
    SpawnSpriteAnim_800C1A5C(orb->pos_44, (short*)&zeroSvector_800795D4, &effectFile_80091BD0.sprites_20[orb->fx_E], 0x1000);
    hero = gameTask_8008B4A4->entry.buffer;
    target[0] = hero->pos_5E4[0];
    target[1] = hero->pos_5E4[1];
    target[2] = hero->pos_5E4[2];
    target[0] += levantPos_8008BD18.pos.x;
    target[1] += levantPos_8008BD18.pos.y;
    target[2] += levantPos_8008BD18.pos.z;
    if (DistanceSquared3D_8003B80C(target, orb->pos_44) >= 0x57E5)
    {
        orb->vel_38[0] += ((target[0] - orb->pos_44[0]) << 10) / 70;
        orb->vel_38[1] += ((target[1] - orb->pos_44[1]) << 10) / 70;
        orb->vel_38[2] += ((target[2] - orb->pos_44[2]) << 10) / 70;
        orb->vel_38[0] = orb->vel_38[0] * 31 / 32;
        orb->vel_38[1] = orb->vel_38[1] * 31 / 32;
        orb->vel_38[2] = orb->vel_38[2] * 31 / 32;
        orb->pos_44[0] += orb->vel_38[0] / 1024;
        orb->pos_44[1] += orb->vel_38[1] / 1024;
        orb->pos_44[2] += orb->vel_38[2] / 1024;
    }
    else
    {
        SpawnBounceSparks_800C1C5C(target, (short*)&zeroSvector_800795D4, &effectFile_80091BD0.sprites_20[orbCopy->fx_E], 0x1000);
        task->flags = (task->flags & ~1) | 0x8000;
    }
}

void SetPointLight_800C4090(void* posArg, void* rgbArg, int range, int intensity)
{
    int* pos = posArg;
    unsigned char* rgb = rgbArg;
    unsigned int scale = intensity;
    pointLightPos_8008D680[0] = pos[0];
    pointLightPos_8008D680[1] = pos[1];
    pointLightPos_8008D680[2] = pos[2];
    pointLightRange_8008D3F0 = range;
    pointLightColor_8008D418.vx = rgb[0] * scale >> 7;
    pointLightColor_8008D418.vy = rgb[1] * scale >> 7;
    pointLightColor_8008D418.vz = rgb[2] * scale >> 7;
}

void ClearPointLight_800C410C()
{
    pointLightRange_8008D3F0 = 0;
}
