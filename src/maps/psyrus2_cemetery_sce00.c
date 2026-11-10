#include "maps/map.h"

void MinionInit_800B22D0(MapEnt* ent);
void ScriptSpot_800B2608(MapEnt* ent);
void MinionIdle_800B267C(MapEnt* ent);
void TintParty_800B2684(MapEnt* ent);
void CameraOrbitInit_800B2718(MapEnt* ent);
void CameraOrbit_800B2750(MapEnt* ent);
void MapInit_800B2758(int phase);
void StartMapTask_800B27C8(void);
void MapTaskLoad_800B27F8(EventEntry* entry, int* st);
void MapTask_800B2890(EventEntry* entry, int* st);
int LeaveArea_800B2948(MapEvent* ev, int area);
int EnterArea_800B2A64(MapEvent* ev, int area, int prev);
void RequestModels_800B2B6C(MapEvent* ev);
int AddEntity_800B2C3C(void* ev);
int StopLevantIfSet_800B2D68(MapScriptSpot* spot);
int MinionF_800B2D98(void);
int MinionF_800B2DA0(void);
void EntityTask_800B2DA8(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const int str_800B22C4[3];
extern short bones_800B2E28[92];
extern ActorScriptCmd* script_800B2EE0;
extern MapActorModel model_800B2EE4;
extern int data_800B2F10[2];
extern MapMinion minion_800B2F18;
extern int data_800B2F3C[1];
extern MapEvent events_800B2F40[5];
extern int data_800B2FA4[16];
extern short bones_800B2FE4[92];
extern int scale_800B309C[3];

void MinionInit_800B22D0(MapEnt* ent)
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
        desc.bones_34 = bones_800B2FE4;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B309C;
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
    w->f_C = MinionF_800B2D98;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B2DA0;
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
    ent->update_90 = MinionIdle_800B267C;
}

void ScriptSpot_800B2608(MapEnt* ent)
{
    MapScriptSpot* spot = ent->data_10;

    if (fieldMode_800B0EC0 == 1 && IsEventPointValid_800A6504(spot->point_0, (int*)&levantPos_8008BD18) && !ent->arg_8C)
    {
        ent->arg_8C = spot;
        StartEventScript_800A59D0(data_800B2FA4);
    }
}

void MinionIdle_800B267C(MapEnt* ent)
{
}

void TintParty_800B2684(MapEnt* ent)
{
    int mask = (long)ent->data_10; /* the party members to tint, one bit each (bit 0: Levant) */
    int i;

    for (i = 0; i < 5; i++)
    {
        int bit = mask & (1 << i);

        if (bit && i != 0)
        {
            SetActorTint_8001DAAC(GetFieldMinionActor_800A7A60(i - 1), (short*)&statusTintLevel5_8007A0D4);
        }
    }
    ent->state_7C = -2;
}

void CameraOrbitInit_800B2718(MapEnt* ent)
{
    MapDoorWork* w;

    w = (MapDoorWork*)ent->work_14;
    w->state_0 = 0;
    w->t_4 = 0;
    CameraOrbit_800B2750(ent);
    ent->update_90 = CameraOrbit_800B2750;
}

void CameraOrbit_800B2750(MapEnt* ent)
{
}

void MapInit_800B2758(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B27C8();
        ClearFieldMinions_800A7784();
        RequestModels_800B2B6C(events_800B2F40);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2C3C);
    }
}

void StartMapTask_800B27C8(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B27F8;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B27F8(EventEntry* entry, int* st)
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
        MapTask_800B2890(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B2890;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B2890(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B2F40;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2948(events, currentArea_80091C44);
        st[2] += EnterArea_800B2A64(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2948(MapEvent* ev, int area)
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

int EnterArea_800B2A64(MapEvent* ev, int area, int prev)
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
                AddEntity_800B2C3C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B2B6C(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B2DA8;
        return 1;
    }
    return 0;
}

int AddEntity_800B2C3C(void* ev)
{
    return NewEntity(ev);
}

int StopLevantIfSet_800B2D68(MapScriptSpot* spot)
{
    if (spot->idle_2)
    {
        ResetLevantActorToIdle_800A8DEC();
    }
    return 1;
}

int MinionF_800B2D98(void)
{
    return 1;
}

int MinionF_800B2DA0(void)
{
    return 1;
}

void EntityTask_800B2DA8(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
