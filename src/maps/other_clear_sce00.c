#include "maps/map.h"

void MinionInit_800B22D4(MapEnt* ent);
void MapInit_800B260C(int phase);
void MinionIdle_800B26E4(MapEnt* ent);
int EndingDone_800B26EC(void);
void EndingSkip_800B2708(MapEnt* ent);
void EndingStop_800B274C(MapEnt* ent);
void EndingWait_800B27B4(MapEnt* ent);
void StartMapTask_800B2808(void);
void MapTaskLoad_800B2838(EventEntry* entry, int* st);
void MapTask_800B28D0(EventEntry* entry, int* st);
int LeaveArea_800B2984(MapEvent* ev, int area);
int EnterArea_800B2AA0(MapEvent* ev, int area, int prev);
void RequestModels_800B2BA8(MapEvent* ev);
int AddEntity_800B2C78(void* ev);
void MapInitOld_800B2DA4(int phase);
int MinionF_800B2E14(void);
int MinionF_800B2E1C(void);
void EntityTask_800B2E24(EventEntry* entry, MapEnt* ent);

extern const int unknown_800B22C0[1];
extern const char data_800B22C4[8];
extern const int data_800B22CC[2];
extern int unknown_800B2EA4[40];
extern int data_800B2F44[1];
extern int data_800B2F48[11];
extern int data_800B2F74[42];
extern int data_800B301C[1];
extern int data_800B3020[11];
extern int data_800B304C[18];
extern int data_800B3094[16];
extern int data_800B30D4[4];
extern int data_800B30E4[5];
extern int data_800B30F8[356];
extern int data_800B3688[196];
extern int data_800B3998[9];
extern int data_800B39BC[9];
extern int data_800B39E0[9];
extern int data_800B3A04[9];
extern MapEvent data_800B3A28[5];
extern MapEvent data_800B3A8C[5];
extern short bones_800B3AF0[92];
extern int scale_800B3BA8[3];
extern MapEvent* curEvents_800B3BB4;

void MinionInit_800B22D4(MapEnt* ent)
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
        desc.bones_34 = bones_800B3AF0;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B3BA8;
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
    w->f_C = MinionF_800B2E14;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B2E1C;
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
    ent->update_90 = MinionIdle_800B26E4;
}

/* NONMATCHING: the index lives in v1 (the original: a0) */
/* phase 0: the event table and the map to come back to by unknownFlags_8008D678 bit 30 */
void MapInit_800B260C(int phase)
{
    if (phase == 0)
    {
        int i;
        MapEvent* events[2];
        int maps[2];

        events[0] = data_800B3A28;
        events[1] = data_800B3A8C;
        maps[1] = 1;
        maps[0] = 0;
        i = ((unsigned int)unknownFlags_8008D678 >> 30) & 1;
        curEvents_800B3BB4 = events[i];
        savedLevantPos_80091C78.mapIdx = maps[i];
    }
    if (phase == 1)
    {
        StartMapTask_800B2808();
        ClearFieldMinions_800A7784();
        RequestModels_800B2BA8(curEvents_800B3BB4);
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74 = 9, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2C78);
    }
}

void MinionIdle_800B26E4(MapEnt* ent)
{
}

/* script call: the ending is over */
int EndingDone_800B26EC(void)
{
    unknownFlags_8008D678 |= 0x48000000;
    return 0;
}

/* Start skips the ending: fade, then stop the voice, the scripts and the messages */
void EndingSkip_800B2708(MapEnt* ent)
{
    if (padPressed_8009194C & 0x800)
    {
        BeginFade_8001C260();
        ent->update_90 = EndingStop_800B274C;
    }
}

void EndingStop_800B274C(MapEnt* ent)
{
    if (cdReadState_80086550.idle_0)
    {
        XaRequestStop_80043524();
        CancelAreaPreload_8002741C();
        StopAllEventEntries_80043B40(eventScripts_8008D410);
        StopAllEventEntries_80043B40(messageWindowTask_8008D640);
        ent->update_90 = EndingWait_800B27B4;
    }
}

void EndingWait_800B27B4(MapEnt* ent)
{
    if (XaRequestStop_80043524() && !GetFileRequestCount_8003BC34())
    {
        EndFade_8001C290();
        unknownFlags_8008D678 |= 0x48000000;
    }
}

void StartMapTask_800B2808(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B2838;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B2838(EventEntry* entry, int* st)
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
        MapTask_800B28D0(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B28D0;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B28D0(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = curEvents_800B3BB4;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2984(events, currentArea_80091C44);
        st[2] += EnterArea_800B2AA0(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2984(MapEvent* ev, int area)
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

int EnterArea_800B2AA0(MapEvent* ev, int area, int prev)
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
                AddEntity_800B2C78(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B2BA8(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B2E24;
        return 1;
    }
    return 0;
}

int AddEntity_800B2C78(void* ev)
{
    return NewEntity(ev);
}

void MapInitOld_800B2DA4(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B2808();
        ClearFieldMinions_800A7784();
        RequestModels_800B2BA8(curEvents_800B3BB4);
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74 = 9, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2C78);
    }
}

int MinionF_800B2E14(void)
{
    return 1;
}

int MinionF_800B2E1C(void)
{
    return 1;
}

void EntityTask_800B2E24(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
