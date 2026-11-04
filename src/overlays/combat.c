// COMBAT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

#include "actor.h"
#include "engine.h"
#include "minion_init.h"
#include "main.h"
#include "combat.h"
#include "tim.h"

int dword_800A05A0 SDATA = 14;
short combatCursor_800A1BBC[4] = { 1, 5, 5 };
short combatMenuChoice_800A1BC4 = 0;
Minion rosters_800A1BC8[2][15] = {
    {
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
    },
    {
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
    },
};
unsigned char player2Pad_800A38D8 = 0;
unsigned char curPlayer_800A38D9 = 0;
unsigned char rosterFill_800A38DA = 0;
unsigned char selMode_800A38DB = 0;
unsigned char battleResult_800A38DC = 0;
int dword_800A38E0 = 0xDF0033;
int combatTaskDesc_800A38E4[6] = { 1, 5, 0, 0, (int)CombatInit_800A13A0, (int)CombatFree_800A148C };
int combatModelLoaderDesc_800A38FC[6] = { 1, 0x8000, 92, (int)&modelLoaderTask_8008B54C, (int)ModelLoaderTask_800209AC };
int combatActorTaskDesc_800A3914[6] = { 2, 0x8000, 0x1CC, (int)&actorTasks_8008D43C };
int enemyWindowTaskDef_800A392C[6] = { 2, 0x8000, 24, (int)&enemyWindowTasks_8008B564 };
int announcerTaskDef_800A3944[6] = { 1, 0x8000, 0, (int)&announcerTasks_8008D458 };
int combatCameraTaskDesc_800A395C[6] = { 1, 0x8000, 0x21C, (int)&cameraTask_8008D4A0 };
int combatFadeTaskDesc_800A3974[6] = { 1, 0x8000, 8, (int)&fadeTask_8008D628 };
void *combatTaskList_800A398C[25] = {
    (void *)&eventDescs_80078EB8, (void *)((char *)&eventDescs_80078EB8 + 24), (void *)((char *)&eventDescs_80078EB8 + 120), (void *)((char *)&eventDescs_80078EB8 + 72),
    (void *)combatCameraTaskDesc_800A395C, (void *)((char *)&eventDescs_80078EB8 + 384), (void *)combatFadeTaskDesc_800A3974, (void *)((char *)&eventDescs_80078EB8 + 504),
    (void *)((char *)&eventDescs_80078EB8 + 528), (void *)((char *)&eventDescs_80078EB8 + 552), (void *)((char *)&eventDescs_80078EB8 + 576), (void *)((char *)&eventDescs_80078EB8 + 432),
    (void *)((char *)&eventDescs_80078EB8 + 624), (void *)combatModelLoaderDesc_800A38FC, (void *)((char *)&eventDescs_80078EB8 + 456), (void *)combatTaskDesc_800A38E4,
    (void *)combatActorTaskDesc_800A3914, (void *)((char *)&eventDescs_80078EB8 + 240), (void *)((char *)&eventDescs_80078EB8 + 216), (void *)((char *)&eventDescs_80078EB8 + 600),
    (void *)enemyWindowTaskDef_800A392C, (void *)announcerTaskDef_800A3944, (void *)((char *)&eventDescs_80078EB8 + 192), (void *)((char *)&eventDescs_80078EB8 + 312),
};
int stageOverlays_800A39F0[6] = { 22, 23, 24, 26, 27, 28 };
CombatSlot combatSlots_800A3A08[2] = { { 0 } };
int combatFlags_800A3A88 = 0;
int stage_800A3A8C = 0;
unsigned char sideWins_800A3A90[4] = { 0 }; // per side
int curPad_800A3A94 = 0; // the pad of the player whose turn it is (COMBSEL)
unsigned char sideResult_800A3A98[8] = { 0 }; // per side
Minion teams_800A3AA0[2][3] = { { { 0 } } };
int prevStage_800A4070 = 0;
int dword_800A4074 = 0;
int sideSlot_800A4078[2] = { 0 }; // per side: the teams_800A3AA0 slot of the minion in the arena, -1 none
int stageOvlRequest_800A4080 = 0;

// Matched
void BuildMinionModelParams_800A05E0(Minion* minion, CombatModelParams* params, int vram)
{
    CombatTopSpecies top;
    unsigned int mainModel = GetSpeciesModelDesc_80019C70(minion->species_2)->modelId_0;
    int tmpWeight;
    params->count_0 = GetTopSpecies_800338DC(minion->species_4C, top.species, top.weights);
    params->parts_4[0] = GetSpeciesModelDesc_80019C70(top.species[0])->modelId_0;
    params->parts_4[1] = GetSpeciesModelDesc_80019C70(top.species[1])->modelId_0;
    params->parts_4[2] = GetSpeciesModelDesc_80019C70(top.species[2])->modelId_0;
    params->weights_10[0] = top.weights[0];
    params->weights_10[1] = top.weights[1];
    params->weights_10[2] = top.weights[2];
    if (params->parts_4[0] == params->parts_4[1])
    {
        if (params->parts_4[1] == params->parts_4[2])
        {
            params->weights_10[0] += params->weights_10[1];
            params->weights_10[0] += params->weights_10[2];
            params->weights_10[1] = 0;
            params->weights_10[2] = 0;
            params->count_0 = 1;
        }
        else
        {
            params->count_0 = 2;
            params->weights_10[0] = params->weights_10[0] + params->weights_10[1];
            params->parts_4[1] = params->parts_4[2];
            params->weights_10[1] = params->weights_10[2];
            params->weights_10[2] = 0;
        }
    }
    else if (params->parts_4[0] == params->parts_4[2])
    {
        params->weights_10[0] = params->weights_10[0] + params->weights_10[2];
        params->weights_10[2] = 0;
        params->count_0 = 2;
    }
    else if (params->parts_4[1] == params->parts_4[2])
    {
        params->weights_10[1] = params->weights_10[1] + params->weights_10[2];
        params->weights_10[2] = 0;
        params->count_0 = 2;
    }
    params->main_2C = 0;
    if (params->parts_4[0] != mainModel)
    {
        if (params->parts_4[1] == mainModel)
        {
            tmpWeight = params->weights_10[1];
            params->parts_4[1] = params->parts_4[0];
            params->parts_4[0] = mainModel;
            params->weights_10[1] = params->weights_10[0];
            params->weights_10[0] = tmpWeight;
        }
        else if (params->parts_4[2] == mainModel)
        {
            tmpWeight = params->weights_10[2];
            params->parts_4[2] = params->parts_4[0];
            params->parts_4[0] = mainModel;
            params->weights_10[2] = params->weights_10[0];
            params->weights_10[0] = tmpWeight;
        }
        else if (params->count_0 < 2)
        {
            tmpWeight = params->weights_10[0];
            params->parts_4[1] = params->parts_4[0];
            params->parts_4[0] = mainModel;
            params->weights_10[0] = 0;
            params->count_0 = 2;
            params->weights_10[1] = tmpWeight;
        }
        else
        {
            tmpWeight = params->weights_10[0];
            params->parts_4[2] = params->parts_4[0];
            params->parts_4[0] = mainModel;
            params->weights_10[0] = 0;
            params->count_0 = 3;
            params->weights_10[2] = tmpWeight;
        }
    }
    params->modelId_1C = Cbt_80019A80(minion->status_84.level_44);
    params->texPart_20 = params->count_0 - 1;
    params->texId_28 = GetSpeciesModelDesc_80019C70(minion->field_3)->modelId_0;
    params->vram_30 = vram;
    params->angle_24 = GetElementHueAngle_800A0898(minion->status_84.element_3E);
    if (params->angle_24 == -1000)
    {
        params->angle_24 = GetSpeciesModelDesc_80019C70(minion->field_3)->field_2 << 1;
    }
    else
    {
        params->angle_24 = params->angle_24 - (GetSpeciesModelDesc_80019C70(minion->field_3)->field_3 << 1);
        if (params->angle_24 < 0)
        {
            params->angle_24 = params->angle_24 + 0x168;
        }
    }
}

// Matched
int GetElementHueAngle_800A0898(unsigned char* elements)
{
    int count = 0;
    int angle;
    int i;
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
            angle = elements[1] < elements[3] ? 0xF5 : 0x41;
        }
        else if (elements[0] && elements[2])
        {
            angle = elements[2] < elements[0] ? 0x14F : 0x9B;
        }
        else
        {
            angle = ElementMixAngle_800A0968(elements);
        }
    }
    else
    {
        angle = ElementMixAngle_800A0968(elements);
    }
    return angle;
}

// Matched
int ElementMixAngle_800A0968(unsigned char* elements)
{
    short* sinTbl = sinTable_80084540;
    int p1, p0, p3, p2, p4, p5, p6, p7;
    p0 = sinTbl[0x5C6 / 2] * elements[0];
    p1 = sinTbl[0x1DC6 / 2] * elements[0];
    p2 = sinTbl[0x1DC6 / 2] * elements[3];
    p3 = sinTbl[0x15C6 / 2] * elements[3];
    p4 = sinTbl[0x15C6 / 2] * elements[2];
    p5 = sinTbl[0xDC6 / 2] * elements[2];
    p6 = sinTbl[0xDC6 / 2] * elements[1];
    p7 = sinTbl[0x5C6 / 2] * elements[1];
    return ratan2Degrees_8003B56C(p0 + p2 + p4 + p6, p1 + p3 + p5 + p7);
}

// Matched
void InitCombatSlots_800A0A28(void)
{
    int i;
    int freeTask = -1;
    for (i = 1; i >= 0; i--)
    {
        combatSlots_800A3A08[i].task_0 = freeTask;
    }
    InitActors_8001D378();
}

// Matched
void FreeCombatSlots_800A0A6C(void)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        if (combatSlots_800A3A08[i].task_0 >= 0)
        {
            DestroySlotActor_800A0D1C(i);
            FreeSlotModel_800A0B70(i);
        }
    }
}

// Matched
void StartSlotModel_800A0ACC(int i, Minion* minion)
{
    CombatSlot* slot = &combatSlots_800A3A08[i];
    BuildMinionModelParams_800A05E0(minion, &slot->params_8, (int)(dword_8007DC78 + (i << 6)));
    slot->minion_4 = minion;
    slot->task_0 = StartModelTask_80010850(&slot->params_8);
    slot->actor_3C = 0;
}

// Matched
// returns RunModelTask_80010A10's result
int RunSlotModelTask_800A0B3C(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return RunModelTask_80010A10(s->task_0);
}

// Matched
void FreeSlotModel_800A0B70(int i)
{
    CombatSlot* slot = &combatSlots_800A3A08[i];
    int task = slot->task_0;
    slot->task_0 = -1;
    FreeModelTask_8001098C(task);
}

// Matched
void CreateSlotActor_800A0BA8(int i, int* pos, short* rot)
{
    CombatSlot* slot = &combatSlots_800A3A08[i];
    ActorDesc desc;
    Model* model = GetModelTaskModel_80010A44(slot->task_0);
    int rank = GetRankForLevel_80019A80(slot->minion_4->status_84.level_44);
    unsigned short* levels;
    unsigned short* groupFlags;
    desc.modelId_0 = -1;
    desc.kind_4 = 2;
    desc.pos_8[0] = pos[0];
    desc.pos_8[1] = pos[1];
    desc.pos_8[2] = pos[2];
    desc.rot_14[0] = rot[0];
    desc.rot_14[1] = rot[1];
    desc.rot_14[2] = rot[2];
    desc.clutRow_1C = i;
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
    slot->actor_3C = CreateActor_8001D45C(&desc);
    levels = GetModelBoneGroupLevels_80024F00(model, rank);
    groupFlags = GetModelBoneGroupFlags_80024F38(model, rank);
    SetBoneGroupFlags_80019B14(slot->actor_3C->bones_134, levels, groupFlags);
    SetActorGroundMove_8001D68C(slot->actor_3C, 0);
}

// Matched
void DestroySlotActor_800A0D1C(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    if (s->actor_3C)
    {
        DestroyActor_8001D600(s->actor_3C);
        s->actor_3C = 0;
    }
}

// Matched
void LoadModelTexToVram_800A0D64(int vramSlot, int modelId)
{
    ModelDesc* desc = GetModelDesc_800251E4(modelId);
    ModelLoadParams params;
    FileRequestDesc req;
    InitModelLoadParams_80025ED0(&params);
    params.flags_0 = 2;
    params.model_14 = 0;
    params.desc_4 = desc;
    params.sel_8 = 0;
    params.vram_18 = &modelLoaderVram_8007DC70[vramSlot];
    req.flags_0 = 0x69;
    req.fileId_4 = desc->fileId_0;
    req.offset_8 = desc->tex_6.offset << 11;
    req.size_C = desc->tex_6.size << 11;
    req.dest_10 = 0;
    req.params_14 = &params;
    req.paramsSize_18 = 0x3C;
    req.callback_1C = OnModelFileLoaded_80025D7C;
    QueueFileRequest_8003BC84(&req);
}

// Matched
void MoveSlotActorTo_800A0E1C(int i, int* pos)
{
    CombatSlot* slot = &combatSlots_800A3A08[i];
    ActorActionDesc action;
    action.flags_0 = 0;
    action.script_4 = 0;
    action.target_8 = 0;
    action.turnStep_C = 0;
    action.hitAnim_E = -1;
    action.effect_10 = -1;
    action.effectKinds_18 = 0;
    action.field_1C = 1;
    action.loopCount_20 = 0;
    action.scaleTarget_22 = 0;
    action.nextAnim_24 = -1;
    action.nextAnim_26 = -1;
    action.anim_28 = -1;
    action.queuedAnim_2A = -1;
    action.field_2C = 0;
    action.path_30 = 0;
    slot->actor_3C->target_70.vx = pos[0];
    slot->actor_3C->target_70.vy = pos[1];
    slot->actor_3C->target_70.vz = pos[2];
    action.target_8 = (int*)&slot->actor_3C->target_70;
    action.turnStep_C = 0x100;
    action.nextAnim_26 = 2;
    SetActorAction_8001E34C(slot->actor_3C, &action);
}

// Matched
int IsSlotActorIdle_800A0EE8(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return IsActorIdle_8001E1C8(s->actor_3C);
}

// Matched
int IsSlotActorReady_800A0F1C(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return IsActorActionReady_8001E1DC(s->actor_3C);
}

// Matched
ShortPair StartSlotAction_800A0F50(int i, int* cmd, int x)
{
    ShortPair hit;
    CombatSlot* slot;
    memset(&hit, 0, 4);
    slot = &combatSlots_800A3A08[i];
    if (*cmd == 0x14)
    {
        return hit;
    }
    hit = StartCommandAction_80018A4C(slot->actor_3C, cmd, 0, x);
    return hit;
}

// Matched
void TriggerSlotEffect_800A0FF0(int i, int* p, int x)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    if (*p != 0x14)
    {
        TriggerActorEffect_8001E28C(s->actor_3C);
    }
}

// Matched
int GetSlotHitFrame_800A1034(int i, unsigned int idx)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return GetActorHitFrame_80018E5C(s->actor_3C, idx);
}

// Matched
void SetSlotStatusTint_800A1068(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    SetActorStatusTint_80018EBC(s->actor_3C, GetSlotStatus_800A10C0(i));
}

// Matched
int GetSlotAncestors_800A10A4(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return (int)s->minion_4->ancestors_4;
}

// Matched
UnitStatus* GetSlotStatus_800A10C0(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return &s->minion_4->status_84;
}

// Matched
int* GetSlotPos_800A10DC(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return s->actor_3C->pos_38;
}

// Matched
int* GetSlotBonePos_800A10F8(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return s->actor_3C->bonePos_1C4;
}

// Matched
void GetSlotEffectTarget_800A111C(int i, EffectTarget* out)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    out->tbl_0 = s->actor_3C->effectTbl_14C;
    out->pos_4 = s->actor_3C->pos_38;
    out->bonePos_8 = s->actor_3C->bonePos_1C4;
    out->boneMatrices_C = s->actor_3C->boneMatrices_1C8;
    out->boneScale_2C = s->actor_3C->boneScale_144;
    out->scale_30 = s->actor_3C->scale_2C;
}

// Matched
int GetSlotSkills_800A11A0(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return (int)&s->minion_4->skills_DE;
}

// Matched
unsigned int* GetSlotMagicBits_800A11BC(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return &s->minion_4->magicBits_F4;
}

// Matched
Minion* GetSlotMinion_800A11D8(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return s->minion_4;
}

// Matched
void StartCombatCamera_800A11F4(void)
{
    EventEntry* e = AllocEventEntry_80043AF8(cameraTask_8008D4A0);
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        ResetCameraToLevant_800376A8();
        StartBattleCamera_80037748();
        e->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
        e->cb_C = FreeCameraTask_800376A0;
        e->flags = (e->flags | 4) & ~0x8000;
        ResetCombatCamera_800A12B8();
    }
}

// Matched
void StopCombatCamera_800A127C(void)
{
    EventNode* p = cameraTask_8008D4A0;
    FreeCameraTask_800376A0(&p->entry, p->entry.buffer);
    StopAllEventEntries_80043B40(cameraTask_8008D4A0);
}

// Matched
void ResetCombatCamera_800A12B8(void)
{
    CameraView* cam = &cameraState_8008D4F0;
    SaveData* save;
    cam->geomScreen_2E = 0;
    cam->lookAt_20.x = 0;
    cam->lookAt_20.y = 0;
    cam->lookAt_20.z = 0;
    cam->eye_14.x = 0;
    cam->eye_14.y = 0;
    cam->eye_14.z = 0;
    cam->lightDir_34.vx = 0;
    cam->lightDir_34.vy = 0;
    cam->lightDir_34.vz = 0;
    cam->lightColor_3C.vx = 0;
    cam->lightColor_3C.vy = 0;
    cam->lightColor_3C.vz = 0;
    cameraZoom_8008B4F8 = 0x1000;
    save = &saveData_8008B570;
    save->levant_7A8.pos.x = 0;
    save->levant_7A8.pos.y = 0;
    save->levant_7A8.pos.z = 0;
    save->levant_7A8.rot.vx = 0;
    save->levant_7A8.rot.vy = 0;
    save->levant_7A8.rot.vz = 0;
}

// COMBAT overlay entry (the battle arena): runs combatTaskList_800A398C, back to the title menu after
// Matched
int CombatMain_800A1324(void)
{
    unknownFlags_8008D678 |= 0x2000000;
    unknownFlags_8008D678 |= 0x4000000;
    DrawIntroMovie_8001AF64(combatTaskList_800A398C);
    unknownFlags_8008D678 &= ~0x2000000;
    unknownFlags_8008D678 &= ~0x4000000;
    return 6;
}

// Matched
void CombatInit_800A13A0(CombatTask* t)
{
    int i;
    int j;
    combatCursor_800A1BBC[0] = 1;
    combatCursor_800A1BBC[1] = 5;
    combatCursor_800A1BBC[2] = 5;
    combatCursor_800A1BBC[3] = 2;
    combatCursor_800A1BBC[4] = 0;
    combatCursor_800A1BBC[5] = 0;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            ClearMinionSlot_800A197C(&teams_800A3AA0[i][j]);
        }
    }
    PlayMusic_800300E0(0x8E, 1);
    LoadUiTiy_8002BF74();
    LoadModelTexToVram_800A0D64(2, 0x42);
    LoadModelTexToVram_800A0D64(3, 0x41);
    t->next_8 = CombatWaitUiTiy_800A14AC;
}

// Matched
void CombatFree_800A148C(void)
{
    FreeActiveOverlay_8002C014();
}

// Matched
void CombatWaitUiTiy_800A14AC(CombatTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        stage_800A3A8C = 0;
        prevStage_800A4070 = 0;
        t->next_8 = CombatLoadStageOvl_800A14F0;
        t->next_8(t);
    }
}

// Matched
void CombatLoadStageOvl_800A14F0(CombatTask* t)
{
    SetFadeMode_8001C19C(0, 0x20);
    stageOvlRequest_800A4080 = LoadOverlay_80020BF8(1, stageOverlays_800A39F0[stage_800A3A8C]);
    t->next_8 = CombatWaitStageOvl_800A1554;
}

// Matched
void CombatWaitStageOvl_800A1554(CombatTask* t, int x)
{
    if (GetFileRequestStatus_8003BE30(stageOvlRequest_800A4080) == 0)
    {
        SetFadeMode_8001C19C(3, 0x20);
        t->next_8 = CombatEnterStage_800A15B4;
        t->next_8(t, x);
    }
}

void CombatEnterStage_800A15B4(CombatTask* t, int x)
{
    unsigned int prev;
    switch (stage_800A3A8C)
    {
    case 0:
        t->next_8 = VersusIntroTask_800A4394;
        break;
    case 1:
        prev = prevStage_800A4070;
        switch (prev)
        {
        case 0:
        case 3:
            selMode_800A38DB = 0;
            curPlayer_800A38D9 = 0;
            combatMenuChoice_800A1BC4 = 0;
            break;
        case 2:
            if (CountRosterMinions_800A1AEC(curPlayer_800A38D9))
            {
                selMode_800A38DB = prev;
                combatMenuChoice_800A1BC4 = 1;
            }
            else
            {
                selMode_800A38DB = 0;
            }
            break;
        }
        t->next_8 = CombSelMain_800A4360;
        break;
    case 2:
        t->next_8 = CombLoadStart_800A40FC;
        break;
    case 3:
        t->next_8 = VersusSetupTask_800A4170;
        break;
    case 4:
        t->next_8 = CombBtlStart_800A4B8C;
        break;
    case 5:
        t->next_8 = VersusResultTask_800A40E0;
        break;
    case 6:
        break;
    }
    t->next_8(t, x);
}

// called by the stage overlays when they are done: picks the next stage and loads its overlay
void CombatNextStage_800A16FC(CombatTask* t)
{
    int stage = stage_800A3A8C;
    short choice;
    prevStage_800A4070 = stage;
    switch (stage)
    {
    case 0:
        stage_800A3A8C = 1;
        break;
    case 1:
        choice = combatMenuChoice_800A1BC4;
        switch (choice)
        {
        case 0:
            stage_800A3A8C = 2;
            break;
        case 3:
            stage_800A3A8C = choice;
            break;
        case 4:
            bStopDrawingMovie_8008D45C = 1;
            return;
        }
        break;
    case 2:
        stage_800A3A8C = 1;
        break;
    case 3:
        if (combatFlags_800A3A88 & 1)
        {
            stage_800A3A8C = 4;
        }
        else
        {
            stage_800A3A8C = 1;
        }
        break;
    case 4:
        switch (battleResult_800A38DC)
        {
        case 0:
        case 1:
            stage_800A3A8C = 5;
            break;
        case 2:
            stage_800A3A8C = 3;
            break;
        }
        break;
    case 5:
        stage_800A3A8C = 3;
        break;
    case 6:
        break;
    }
    t->next_8 = CombatLoadStageOvl_800A14F0;
    t->next_8(t);
}

// Matched
void DrawMinionNameLevel_800A1844(Minion* minion, unsigned short* pt, unsigned int flags)
{
    UnitStatus* status;
    unsigned short pos[2];
    if (IsMinionSlotEmpty_800A1934(minion) != 1)
    {
        if (flags & 2)
        {
            SetFontClutOffset_8003F900(1, 1);
        }
        else
        {
            SetFontClutOffset_8003F900(1, 0);
        }
        status = &minion->status_84;
        pos[0] = pt[0] + 5;
        pos[1] = pt[1] + 6;
        DrawSmallText_8002FAA0(0, pos, minion->status_84.name_10, 0);
        pos[0] = pt[0] + 0x50;
        pos[1] = pt[1] + 6;
        DrawSmallNumber3_8002C290(pos, status->level_44, 0);
        pos[0] = pt[0] + 0x54;
        pos[1] = pt[1] + 3;
        DrawElementIconsRow_8002B1B0(status->elementMask_42, pos, 0);
    }
}

// Matched
int IsMinionSlotEmpty_800A1934(Minion* minion)
{
    if (minion == 0)
    {
        return 1;
    }
    return minion->id == 4;
}

// Matched
int IsMinionFainted_800A1958(Minion* minion)
{
    return HasStatusFlag_80033548(&minion->status_84, 0x400);
}

// Matched
void ClearMinionSlot_800A197C(Minion* minion)
{
    minion->id = 4;
}

// Matched
void CopySaveMinionsToRoster_800A1988(void)
{
    int i;
    rosterFill_800A38DA = 0;
    for (i = 0; i < 15; i++)
    {
        MemCopy_800403E8(&rosters_800A1BC8[curPlayer_800A38D9][rosterFill_800A38DA], &saveMinions_8008BEF8[i], 0xF8);
        rosterFill_800A38DA++;
    }
}

// Matched
int CountMinions_800A1A3C(Minion* minions, int len)
{
    int i;
    int count = 0;
    for (i = 0; i < len; i++)
    {
        if (!IsMinionSlotEmpty_800A1934(&minions[i]))
        {
            count++;
        }
    }
    return count;
}

// Matched
int CountTeamMinions_800A1AAC(int side)
{
    return CountMinions_800A1A3C(teams_800A3AA0[side], 3);
}

// Matched
int CountRosterMinions_800A1AEC(int side)
{
    return CountMinions_800A1A3C(rosters_800A1BC8[side], 0xF);
}

// Matched
void GetCombatPortraitPoly_800A1B2C(int i, void* poly)
{
    TimInfo tim;
    tim.mode_valid = 1;
    tim.mode = 1;
    tim.prect.x = dword_8007DCAC[i].x;
    tim.prect.y = dword_8007DCAC[i].y;
    tim.prect.w = 0x20;
    tim.prect.h = 0x40;
    tim.crect.x = dword_8007DCBC[i].x;
    tim.crect.y = dword_8007DCBC[i].y;
    tim.crect.w = 0x100;
    tim.crect.h = 1;
    InitPolyFT4_80029A10(poly, &tim);
}
