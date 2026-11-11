#include "maps/map.h"

void FtgAnim_800B22F4(MapEnt* ent);
void MinionInit_800B2430(MapEnt* ent);
void MapInit_800B2768(int phase);
void CameraOrbitInit_800B27D4(MapEnt* ent);
void CameraOrbit_800B280C(MapEnt* ent);
void FtgAnimInit_800B289C(MapEnt* ent);
void MinionIdle_800B28D4(MapEnt* ent);
int SetLevantAnimSet_800B28DC(void);
void StartMapTask_800B28F0(void);
void MapTaskLoad_800B2920(EventEntry* entry, int* st);
void MapTask_800B29B8(EventEntry* entry, int* st);
int LeaveArea_800B2A70(MapEvent* ev, int area);
int EnterArea_800B2B8C(MapEvent* ev, int area, int prev);
void RequestModels_800B2C94(MapEvent* ev);
int AddEntity_800B2D64(void* ev);
int MinionF_800B2E90(void);
int MinionF_800B2E98(void);
void EntityTask_800B2EA0(EventEntry* entry, MapEnt* ent);

extern const int unknown_800B22C0[1];
extern const char str_800B22C4[20];
extern const char str_800B22D8[12];
extern const char str_800B22E4[16];
extern short bones_800B2F20[100];
extern int data_800B2FE8[3];
extern SVECTOR boneScale_800B2FF4[24];
extern int anim_800B30B4[19];
extern int anim_800B3100[19];
extern ActorScriptCmd anim_800B314C[4];
extern ActorScriptCmd anim_800B317C[4];
extern ActorScriptCmd anim_800B31AC[4];
extern ActorScriptCmd* script_800B31DC[34];
extern int data_800B3264[3];
extern MapActorModel model_800B3270;
extern int data_800B329C[3];
extern SVECTOR boneScale_800B32A8[25];
extern int anim_800B3370[19];
extern ActorScriptCmd anim_800B33BC[5];
extern ActorScriptCmd anim_800B33F8[5];
extern ActorScriptCmd* script_800B3434[32];
extern MapActorModel model_800B34B4;
extern int data_800B34E0[12];
extern MapActorModel model_800B3510;
extern MapVoice voices_800B353C[8];
extern int data_800B357C[2];
extern int data_800B3584[4];
extern int data_800B3594[18];
extern int data_800B35DC[];
extern int species_800B3600[9];
extern SVECTOR boneScale_800B3624[6];
extern MapFtgAnim ftgAnim_800B3654;
extern MapEvent event_800B3660[2];
extern MapInstr script_800B3688[80];
extern MapMinion minion_800B3B88;
extern MapMinion minion_800B3BAC;
extern MapMinion minion_800B3BD0;
extern MapEvent events_800B3BF4[6];
extern short bones_800B3C6C[92];
extern int scale_800B3D24[3];

void FtgAnim_800B22F4(MapEnt* ent)
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

void MinionInit_800B2430(MapEnt* ent)
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
        desc.bones_34 = bones_800B3C6C;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B3D24;
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
    w->f_C = MinionF_800B2E90;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B2E98;
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
    ent->update_90 = MinionIdle_800B28D4;
}

void MapInit_800B2768(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B28F0();
        ClearFieldMinions_800A7784();
        RequestModels_800B2C94(events_800B3BF4);
        levantAnimSet_80091C74 = 10;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2D64);
    }
}

void CameraOrbitInit_800B27D4(MapEnt* ent)
{
    MapDoorWork* w;

    w = (MapDoorWork*)ent->work_14;
    w->state_0 = 0;
    w->t_4 = 0;
    CameraOrbit_800B280C(ent);
    ent->update_90 = CameraOrbit_800B280C;
}

void CameraOrbit_800B280C(MapEnt* ent)
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

void FtgAnimInit_800B289C(MapEnt* ent)
{
    MapFtgAnimWork* w;

    w = (MapFtgAnimWork*)ent->work_14;
    w->frame_0 = 0;
    w->frac_2 = 0;
    FtgAnim_800B22F4(ent);
    ent->update_90 = FtgAnim_800B22F4;
}

void MinionIdle_800B28D4(MapEnt* ent)
{
}

int SetLevantAnimSet_800B28DC(void)
{
    levantAnimSet_80091C74 = 11;
    return 1;
}

void StartMapTask_800B28F0(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B2920;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B2920(EventEntry* entry, int* st)
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
        MapTask_800B29B8(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B29B8;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B29B8(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B3BF4;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2A70(events, currentArea_80091C44);
        st[2] += EnterArea_800B2B8C(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2A70(MapEvent* ev, int area)
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

int EnterArea_800B2B8C(MapEvent* ev, int area, int prev)
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
                AddEntity_800B2D64(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B2C94(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B2EA0;
        return 1;
    }
    return 0;
}

int AddEntity_800B2D64(void* ev)
{
    return NewEntity(ev);
}

int MinionF_800B2E90(void)
{
    return 1;
}

int MinionF_800B2E98(void)
{
    return 1;
}

void EntityTask_800B2EA0(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
