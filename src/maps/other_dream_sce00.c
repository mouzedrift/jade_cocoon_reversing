#include "maps/map.h"

void MinionInit_800B22F8(MapEnt* ent);
void FtgAnim_800B2630(MapEnt* ent);
void MapInit_800B276C(int phase);
void MinionIdle_800B2850(MapEnt* ent);
void CameraOrbitInit_800B2858(MapEnt* ent);
void CameraOrbit_800B2890(MapEnt* ent);
void FtgAnimInit_800B2920(MapEnt* ent);
int ExitDream_800B2958(MapExitArgs* args);
void StartMapTask_800B299C(void);
void MapTaskLoad_800B29CC(EventEntry* entry, int* st);
void MapTask_800B2A64(EventEntry* entry, int* st);
int LeaveArea_800B2B18(MapEvent* ev, int area);
int EnterArea_800B2C34(MapEvent* ev, int area, int prev);
void RequestModels_800B2D3C(MapEvent* ev);
int AddEntity_800B2E0C(void* ev);
void MapReinit_800B2F38(int phase);
int MinionF_800B2FAC(void);
int MinionF_800B2FB4(void);
void EntityTask_800B2FBC(EventEntry* entry, MapEnt* ent);

extern const int unknown_800B22C0[1];
extern const char str_800B22C4[12];
extern const char str_800B22D0[8];
extern const char str_800B22D8[20];
extern const int str_800B22EC[3];
extern int unknown_800B303C[12];
extern int data_800B306C[12];
extern ActorScriptCmd* script_800B309C;
extern MapActorModel model_800B30A0;
extern int data_800B30CC[12];
extern int data_800B30FC[12];
extern ActorScriptCmd* script_800B312C;
extern MapActorModel model_800B3130;
extern short bones_800B315C[100];
extern int data_800B3224[3];
extern SVECTOR boneScale_800B3230[24];
extern int anim_800B32F0[19];
extern int anim_800B333C[19];
extern ActorScriptCmd anim_800B3388[4];
extern ActorScriptCmd anim_800B33B8[4];
extern ActorScriptCmd anim_800B33E8[4];
extern ActorScriptCmd* script_800B3418[34];
extern int data_800B34A0[3];
extern MapActorModel model_800B34AC;
extern int data_800B34D8[3];
extern SVECTOR boneScale_800B34E4[25];
extern int anim_800B35AC[19];
extern ActorScriptCmd anim_800B35F8[5];
extern ActorScriptCmd anim_800B3634[5];
extern ActorScriptCmd* script_800B3670[32];
extern MapActorModel model_800B36F0;
extern MapVoice voices_800B371C[12];
extern SVECTOR rots_800B377C[6];
extern MapFtgAnim ftgAnim_800B37AC;
extern MapEvent event_800B37B8;
extern MapEvent event_800B37CC;
extern int data_800B37E0[2];
extern int data_800B37E8[4];
extern int data_800B37F8[4];
extern int data_800B3808[18];
extern MapInstr script_800B3850[66];
extern MapInstr script_800B3C70[45];
extern MapMinion minion_800B3F40;
extern MapMinion minion_800B3F64;
extern MapMinion minion_800B3F88;
extern MapMinion minion_800B3FAC;
extern MapEvent events_800B3FD0[5];
extern MapEvent events_800B4034[5];
extern short bones_800B4098[92];
extern int scale_800B4150[3];
extern MapEvent* curEvents_800B415C;

void MinionInit_800B22F8(MapEnt* ent)
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
        desc.bones_34 = bones_800B4098;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B4150;
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
    w->f_C = MinionF_800B2FAC;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B2FB4;
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
    ent->update_90 = MinionIdle_800B2850;
}

void FtgAnim_800B2630(MapEnt* ent)
{
    MapFtgAnim* anim;
    MapFtgAnimWork* w;
    int ftg;
    SVECTOR* rot;
    int frame;
    int first;
    int carry;

    anim = ent->data_10;
    w = (MapFtgAnimWork*)ent->work_14;
    ftg = anim->first_0 + w->frame_0;
    rot = &anim->rots_8[saveData_8008B570.mapId_2E4[3].prev_2];
    DrawFtgObjectAtSlot0_8004D1EC(&mapState_8008B500.ftg_3C[ftg], pOT_8008D690, &cameraState_8008D4F0.eye_14, rot,
                                  &cameraState_8008D4F0.ent_44[FindNearestCameraPoint_80019CC4(&cameraState_8008D4F0.eye_14.x)], 0x31, 0);
    w->frac_2 += anim->speed_4;
    carry = w->frac_2 / 4096;
    w->frac_2 %= 4096;
    frame = w->frame_0 + carry;
    first = anim->first_0 - 1;
    w->frame_0 = frame % (anim->last_2 - first);
}

void MapInit_800B276C(int phase)
{
    if (phase == 0)
    {
        MapEvent* events[2] = { events_800B3FD0, events_800B4034 };
        int animSets[2] = { 3, 4 };

        curEvents_800B415C = events[GetEventVar_800AD154(0)];
        levantAnimSet_80091C74 = animSets[GetEventVar_800AD154(0)];
    }
    if (phase == 1)
    {
        StartMapTask_800B299C();
        ClearFieldMinions_800A7784();
        RequestModels_800B2D3C(curEvents_800B415C);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2E0C);
    }
}

void MinionIdle_800B2850(MapEnt* ent)
{
}

void CameraOrbitInit_800B2858(MapEnt* ent)
{
    MapDoorWork* w;

    w = (MapDoorWork*)ent->work_14;
    w->state_0 = 0;
    w->t_4 = 0;
    CameraOrbit_800B2890(ent);
    ent->update_90 = CameraOrbit_800B2890;
}

void CameraOrbit_800B2890(MapEnt* ent)
{
    MapDoorWork* w;
    int state;

    w = (MapDoorWork*)ent->work_14;
    if (ent->state_7C == 0)
    {
        w->state_0 = 1;
        ent->state_7C = -1;
    }
    state = w->state_0;
    switch (state)
    {
    case 0:
        StartCameraOrbit_80037C24();
        break;
    case 1:
        StopCameraOrbit_80037C4C();
        if (GetCameraMode_800378F8() == 0)
        {
            ent->prev_80 = state;
        }
        break;
    }
}

void FtgAnimInit_800B2920(MapEnt* ent)
{
    MapFtgAnimWork* w;

    w = (MapFtgAnimWork*)ent->work_14;
    w->frame_0 = 0;
    w->frac_2 = 0;
    FtgAnim_800B2630(ent);
    ent->update_90 = FtgAnim_800B2630;
}

int ExitDream_800B2958(MapExitArgs* args)
{
    SetEventVar_800AD16C(0, args->var_0);
    mapStartMode_80091C54 = 0;
    forceMapReload_80091C9C = args->reload_4;
    return 1;
}

void StartMapTask_800B299C(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B29CC;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B29CC(EventEntry* entry, int* st)
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
        MapTask_800B2A64(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B2A64;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B2A64(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = curEvents_800B415C;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2B18(events, currentArea_80091C44);
        st[2] += EnterArea_800B2C34(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2B18(MapEvent* ev, int area)
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

int EnterArea_800B2C34(MapEvent* ev, int area, int prev)
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
                AddEntity_800B2E0C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B2D3C(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B2FBC;
        return 1;
    }
    return 0;
}

int AddEntity_800B2E0C(void* ev)
{
    return NewEntity(ev);
}

void MapReinit_800B2F38(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B299C();
        ClearFieldMinions_800A7784();
        RequestModels_800B2D3C(curEvents_800B415C);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2E0C);
    }
}

int MinionF_800B2FAC(void)
{
    return 1;
}

int MinionF_800B2FB4(void)
{
    return 1;
}

void EntityTask_800B2FBC(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
