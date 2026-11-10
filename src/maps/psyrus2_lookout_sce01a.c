#include "maps/map.h"

void MinionInit_800B2318(MapEnt* ent);
void Door_800B2650(MapEnt* ent);
void MapInit_800B2910(int phase);
void MinionIdle_800B2980(MapEnt* ent);
void CameraOrbitInit_800B2988(MapEnt* ent);
int LoadMinionAnim_800B29C0(MapLoadArgs* args);
int LoadMinionAnimSet_800B2A68(MapLoadArgs* args);
int FadeOutSeq_800B2AE4(void);
void StartMapTask_800B2B30(void);
void MapTaskLoad_800B2B60(EventEntry* entry, int* st);
void MapTask_800B2BF8(EventEntry* entry, int* st);
int LeaveArea_800B2CB0(MapEvent* ev, int area);
int EnterArea_800B2DCC(MapEvent* ev, int area, int prev);
void RequestModels_800B2ED4(MapEvent* ev);
int AddEntity_800B2FA4(void* ev);
int MinionF_800B30D0(void);
int MinionF_800B30D8(void);
void EntityTask_800B30E0(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const char str_800B22D0[8];
extern ActorScriptCmd* script_800B3160;
extern MapActorModel model_800B3164;
extern ActorScriptCmd* script_800B3190;
extern MapActorModel model_800B3194;
extern MapVoice voices_800B31C0[19];
extern int data_800B3258[4];
extern int data_800B3268[3];
extern MapEvent event_800B3274;
extern MapInstr script_800B3288[104];
extern MapMinion minion_800B3908;
extern MapMinion minion_800B392C;
extern MapEvent events_800B3950[5];
extern short bones_800B39B4[92];
extern int scale_800B3A6C[3];

void MinionInit_800B2318(MapEnt* ent)
{
    ActorDesc desc;
    int params[2];
    UnitStats unit;
    MapMinion* m;
    MapActorModel* model;
    MapMinionSpecies* species;
    Model* mdl;
    int modelId;
    short* bones;
    int* baseScale;
    SVECTOR* boneScale;
    ActorScriptCmd** script;
    MapMinionWork* w;
    int blendDiv;
    void* effects;
    unsigned short* levels;
    unsigned short* flags;
    int rec;
    Actor* actor;

    levels = 0;
    flags = 0;
    m = ent->data_10;
    w = (MapMinionWork*)ent->work_14;
    species = m->species_4;
    model = m->model_0;
    if (species)
    {
        modelId = GetSpeciesModelDesc_80019C70(species->species_0)->modelId_0;
        blendDiv = 4;
        mdl = AcquireLoaderModel_80020734(modelId);
        params[0] = species->species_0;
        params[1] = species->level_4;
        rec = InitMinionData_8001900C(&unit, params);
        bones = defaultBones_80079140;
        baseScale = GetModelBaseScale_80024E90(mdl, rec);
        boneScale = GetModelBoneScale_80024EC8(mdl, rec);
        effects = GetModelEffectTable_80024E64(mdl);
        levels = GetModelBoneGroupLevels_80024F00(mdl, rec);
        flags = GetModelBoneGroupFlags_80024F38(mdl, rec);
        if (model && model->script_1C)
        {
            script = model->script_1C;
        }
        else
        {
            script = commandScripts_8007A024;
        }
    }
    else
    {
        modelId = model->modelId_4;
        mdl = AcquireLoaderModel_80020734(modelId);
        blendDiv = model->blendDiv_18;
        bones = model->bones_8;
        baseScale = model->baseScale_C;
        boneScale = model->boneScale_10;
        effects = GetModelEffectTable_80024E64(mdl);
        script = model->script_1C;
    }
    desc.modelId_0 = modelId;
    desc.kind_4 = GetFieldMinionCount_800A7790() + 3;
    desc.pos_8[0] = m->pos_8[0];
    desc.pos_8[1] = m->pos_8[1];
    desc.pos_8[2] = m->pos_8[2];
    desc.rot_14[0] = 0;
    desc.rot_14[1] = m->rotY_14;
    desc.rot_14[2] = 0;
    desc.clutRow_1C = GetFieldMinionCount_800A7790();
    desc.animIdx_20 = m->anim_18;
    desc.frame_24 = -1;
    desc.frameSpeed_28 = 0x1000;
    desc.blendDiv_2C = blendDiv;
    desc.visible_30 = 1;
    if (bones)
    {
        desc.bones_34 = bones;
    }
    else
    {
        desc.bones_34 = bones_800B39B4;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B3A6C;
    }
    if (boneScale)
    {
        desc.boneScale_3C = boneScale;
    }
    else
    {
        desc.boneScale_3C = 0;
    }
    desc.anims_40 = GetModelActorAnims_80024E38(mdl);
    desc.effectTbl_44 = effects;
    desc.hasMatrices_4C = (m->flags_20 >> 2) & 1;
    actor = CreateActor_8001D45C(&desc);
    if (levels && flags)
    {
        SetBoneGroupFlags_80019B14(actor->bones_134, levels, flags);
    }
    if (model->ftgs_14)
    {
        SaveModelFtgs_80024FFC(mdl, model->ftgs_14);
    }
    w->f_C = MinionF_800B30D0;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B30D8;
    w->minion_0 = AddFieldMinion_800A77A0(ent);
    if (m->flags_20 & 1)
    {
        SetActorVisible_8001D730(actor, 0);
    }
    if (m->flags_20 & 2)
    {
        SetActorRootMotion_8001D6BC(actor, 1);
    }
    if (m->flags_20 & 8)
    {
        SetActorGroundMove_8001D68C(actor, 0);
    }
    ent->update_90 = MinionIdle_800B2980;
}

void Door_800B2650(MapEnt* ent)
{
    int from[3] = { -0xB44, -0x3582, -0xC39 };
    int move[3] = { -0xEFC, 0x1A5E, -0x12EC };
    int pos[3];
    short rot[4] = { 0x1E2, -0x64C, 0, 0 };
    MapDoorWork* w;
    PointLight* light;

    w = (MapDoorWork*)ent->work_14;
    if (saveData_8008B570.mapId_2E4[3].prev_2 == 0)
    {
        if (ent->state_7C == 0)
        {
            w->state_0 = 1;
            ent->state_7C = -1;
        }
        switch (w->state_0)
        {
        case 0:
            pos[0] = from[0];
            pos[1] = from[1];
            pos[2] = from[2];
            break;
        case 1:
            w->state_0++;
            break;
        case 2:
            w->state_0++;
            break;
        case 3:
            w->state_0++;
            break;
        case 4:
            w->state_0++;
            break;
        case 5:
            w->state_0++;
            break;
        case 6:
            w->t_4 = w->t_4 + 1 < 0 ? 0 : (w->t_4 + 1 <= 120 ? w->t_4 + 1 : 120);
            break;
        }
        pos[0] = from[0] + move[0] * w->t_4 / 120;
        pos[1] = from[1] + move[1] * w->t_4 / 120;
        pos[2] = from[2] + move[2] * w->t_4 / 120;
        light = &cameraState_8008D4F0.ent_44[FindNearestCameraPoint_80019CC4(pos)];
        DrawFtgObjectAtSlot0_8004D1EC(&mapState_8008B500.ftg_3C[0], pOT_8008D690, pos, rot, light, 0, 0);
        DrawFtgObjectAtSlot0_8004D1EC(&mapState_8008B500.ftg_3C[1], pOT_8008D690, pos, rot, light, 0, 0);
        DrawFtgObjectAtSlot0_8004D1EC(&mapState_8008B500.ftg_3C[2], pOT_8008D690, pos, rot, light, 0, 0);
    }
}

void MapInit_800B2910(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B2B30();
        ClearFieldMinions_800A7784();
        RequestModels_800B2ED4(events_800B3950);
        levantAnimSet_80091C74 = 1;
        LoadLevantAnimSet_800AC708(1, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2FA4);
    }
}

void MinionIdle_800B2980(MapEnt* ent)
{
}

void CameraOrbitInit_800B2988(MapEnt* ent)
{
    MapDoorWork* w;

    w = (MapDoorWork*)ent->work_14;
    w->state_0 = 0;
    w->t_4 = 0;
    Door_800B2650(ent);
    ent->update_90 = Door_800B2650;
}

/* script call: loads animation 18 of the second party member (its animations 108 and 109 resident) */
int LoadMinionAnim_800B29C0(MapLoadArgs* args)
{
    Model* model = GetFieldMinionModelDesc_800A7A1C(1);
    Actor* actor;

    switch (args->step_0)
    {
    case 0:
        actor = GetFieldMinionActor_800A7A60(1);
        actor->anims_148[108].kind_1 = 1;
        actor->anims_148[109].kind_1 = 1;
        args->step_0++;
        args->arg_4 = LoadModelAnim_80025440(model, 18, 0);
        break;
    case 1:
        return AreFileRequestsDone_80024DC4(model);
    }
    return 0;
}

/* script call: loads animation set arg_4 of the second party member */
int LoadMinionAnimSet_800B2A68(MapLoadArgs* args)
{
    Model* model = GetFieldMinionModelDesc_800A7A1C(1);

    switch (args->step_0)
    {
    case 0:
        args->step_0 = 1;
        args->arg_4 = LoadModelAnimSet_80025780(model, args->arg_4, 0);
        break;
    case 1:
        return AreFileRequestsDone_80024DC4(model);
    }
    return 0;
}

/* script call: fades the system sound sequence out */
int FadeOutSeq_800B2AE4(void)
{
    SoundStruct* snd = &systemSound_80091D40;

    if (snd->seqNum_4 >= 0)
    {
        SsSepSetDecrescendo(snd->sepAccessNum_C, snd->seqNum_4, 127, 120);
        snd->seqNum_4 = -1;
    }
    return 1;
}

void StartMapTask_800B2B30(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B2B60;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B2B60(EventEntry* entry, int* st)
{
    if (!AreLevantFilesLoaded_800AC768() || !IsModelLoaderDone_800205D0())
    {
        eventDispatchHalt_8008B540 = 1;
    }
    else
    {
        st[0] = 0;
        st[1] = -1;
        st[2] = 0;
        MapTask_800B2BF8(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B2BF8;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B2BF8(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B3950;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2CB0(events, currentArea_80091C44);
        st[2] += EnterArea_800B2DCC(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2CB0(MapEvent* ev, int area)
{
    EventNode* node;
    EventEntry* entry;
    int areas;
    int n;
    int i;
    int count;

    n = 0;
    for (; ev->type_4 != MAP_EV_END; ev++)
    {
        if (ev->type_4 == MAP_EV_SCRIPT && ev->areas_0 != -1 && !InAreas(ev->areas_0, area))
        {
            entry = ev->run_10.script;
            if (entry)
            {
                n++;
                entry->flags = (entry->flags & ~1) | 0x8000;
            }
            ev->run_10.script = 0;
        }
    }
    node = eventEntities_8008D400;
    count = node->count;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            areas = ((MapEnt*)entry->buffer)->areas_8;
            if (areas != -1 && !InAreas(areas, area))
            {
                entry->flags = (entry->flags & ~1) | 0x8000;
                n++;
            }
        }
        node = node->next;
    }
    return n;
}

int EnterArea_800B2DCC(MapEvent* ev, int area, int prev)
{
    int n;
    int areas;
    int enter;

    n = 0;
    for (; ev->type_4 != MAP_EV_END; ev++)
    {
        areas = ev->areas_0;
        enter = 0;
        if ((prev == -1 || !InAreas(areas, prev)) && InAreas(areas, area))
        {
            enter = 1;
        }
        if (enter)
        {
            if (ev->type_4 == MAP_EV_VOICES)
            {
                SetVoiceTable_800A6830(ev->data_8);
            }
            else if (ev->type_4 == MAP_EV_SCRIPT)
            {
                n++;
                ev->run_10.script = StartEventScript_800A59D0(ev->data_8);
            }
            else
            {
                AddEntity_800B2FA4(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B2ED4(MapEvent* ev)
{
    MapMinion* m;
    MapActorModel* model;
    MinionModelDesc* desc;

    for (; ev->type_4 != MAP_EV_END; ev++)
    {
        if (ev->type_4 == MAP_EV_MINION)
        {
            m = ev->data_8;
            model = m->model_0;
            if (m->species_4)
            {
                desc = GetSpeciesModelDesc_80019C70(m->species_4->species_0);
                if (!RequestLoaderModel_800206A0(desc->modelId_0, desc->field_2 * 2 + model->sel_28, 3, m->f1C))
                {
                    break;
                }
            }
            else if (model)
            {
                if (!RequestLoaderModel_800206A0(model->modelId_4, model->sel_28, 2, m->f1C))
                {
                    break;
                }
            }
        }
    }
    StartModelLoader_8002056C();
}

/* an entity for the event (MapEvent.run_10.init its update) */
static inline int NewEntity(MapEvent* ev)
{
    EventEntry* entry;
    MapEnt* ent;

    entry = AllocEventEntry_80043AF8(eventEntities_8008D400);
    if (entry)
    {
        ent = entry->buffer;
        entry->flags = (entry->flags | 1) & ~0x8000;
        ent->entry_0 = entry;
        ent->event_4 = ev;
        ent->areas_8 = ev->areas_0;
        ent->type_C = ev->type_4;
        ent->data_10 = ev->data_8;
        ent->armed_78 = 0;
        ent->state_7C = -1;
        ent->prev_80 = -1;
        ent->trigger_84 = -1;
        ent->script_88 = 0;
        ent->arg_8C = 0;
        ent->update_90 = ev->run_10.init;
        if ((unsigned)ev->type_4 >= 14)
        {
            StepEntity(entry, entry->buffer);
        }
        entry->cb_8 = (EventEntryFn)EntityTask_800B30E0;
        return 1;
    }
    return 0;
}

int AddEntity_800B2FA4(void* ev)
{
    return NewEntity(ev);
}

int MinionF_800B30D0(void)
{
    return 1;
}

int MinionF_800B30D8(void)
{
    return 1;
}

void EntityTask_800B30E0(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
