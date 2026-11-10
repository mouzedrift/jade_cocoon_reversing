#include "maps/map.h"

void MinionInit_800B22F8(MapEnt* ent);
void MoviePlayer_800B2630(MapEnt* ent);
void ScriptSpot_800B2820(MapEnt* ent);
void MinionIdle_800B2894(MapEnt* ent);
void MoviePlayerInit_800B289C(MapEnt* ent);
void CameraOrbitInit_800B28DC(MapEnt* ent);
void CameraOrbit_800B2914(MapEnt* ent);
void MapInit_800B291C(int phase);
void StartMapTask_800B298C(void);
void MapTaskLoad_800B29BC(EventEntry* entry, int* st);
void MapTask_800B2A54(EventEntry* entry, int* st);
int LeaveArea_800B2B0C(MapEvent* ev, int area);
int EnterArea_800B2C28(MapEvent* ev, int area, int prev);
void RequestModels_800B2D30(MapEvent* ev);
int AddEntity_800B2E00(void* ev);
int StopLevantIfSet_800B2F2C(MapScriptSpot* spot);
int MinionF_800B2F5C(void);
int MinionF_800B2F64(void);
void EntityTask_800B2F6C(EventEntry* entry, MapEnt* ent);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[16];
extern short bones_800B2FEC[92];
extern ActorScriptCmd* script_800B30A4;
extern MapActorModel model_800B30A8;
extern int data_800B30D4[2];
extern MapMovie data_800B30DC;
extern MapVoice voices_800B30E4[11];
extern int event_800B313C[1];
extern MapInstr script_800B3140[74];
extern MapMinion minion_800B35E0;
extern MapEvent events_800B3604[7];
extern int data_800B3690[16];
extern short bones_800B36D0[92];
extern int scale_800B3788[3];

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
        desc.bones_34 = bones_800B36D0;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B3788;
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
    w->f_C = MinionF_800B2F5C;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B2F64;
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
    ent->update_90 = MinionIdle_800B2894;
}

/* NONMATCHING: case 7 (unknownFlags_8008D678 &= ~8) allocates other registers (5 words) */
/* plays the movie the script asks for (state_7C) between a fade out and a fade in */
void MoviePlayer_800B2630(MapEnt* ent)
{
    MapMovie* movies = ent->data_10;
    MapMovieWork* w = (MapMovieWork*)ent->work_14;
    int mode;

    if (ent->state_7C >= 0)
    {
        if (w->active_0)
        {
            goto run;
        }
        w->index_4 = ent->state_7C;
        ent->state_7C = -1;
        w->active_0 = 1;
    }
    if (!w->active_0)
    {
        return;
    }
run:
    switch (w->step_C)
    {
    case 0:
        StartSceneFadeOut_8001AA50(30);
        w->step_C++;
        break;
    case 1:
        if (!IsSceneFadeDone_8001AB94())
        {
            break;
        }
        if (movies[w->index_4].music_4 >= 0)
        {
            w->music_8 = GetBattleMusic_800315E4();
            PlayMusic_800300E0(movies[w->index_4].music_4, 1);
        }
        DisableCameraPoints_800A096C();
        ent->prev_80 = 0;
        unknownFlags_8008D678 |= 8;
        w->step_C++;
        break;
    case 4:
        mode = FreeMdecBuffer_800A5854();
        PlayMovie_80040EB4(movies[w->index_4].movie_0);
        ClearOTagRAll_8001B260();
        AllocMdecBuffer_800A5804(mode);
        if (movies[w->index_4].music_4 >= 0)
        {
            PlayMusic_800300E0(w->music_8, 1);
        }
        w->step_C++;
        break;
    case 7:
        EnableCameraPoints_800A094C();
        unknownFlags_8008D678 &= ~8;
        StartSceneFadeIn_8001AA04(30);
    case 2:
    case 3:
    case 5:
    case 6:
        w->step_C++;
        break;
    case 8:
        if (IsSceneFadeDone_8001AB94())
        {
            w->active_0 = 0;
            w->step_C = 0;
            ent->prev_80 = 1;
        }
        break;
    }
}

void ScriptSpot_800B2820(MapEnt* ent)
{
    MapScriptSpot* spot = ent->data_10;

    if (fieldMode_800B0EC0 == 1 && IsEventPointValid_800A6504(spot->point_0, (int*)&levantPos_8008BD18) && !ent->arg_8C)
    {
        ent->arg_8C = spot;
        StartEventScript_800A59D0(data_800B3690);
    }
}

void MinionIdle_800B2894(MapEnt* ent)
{
}

void MoviePlayerInit_800B289C(MapEnt* ent)
{
    MapMovieWork* w = (MapMovieWork*)ent->work_14;

    w->active_0 = 0;
    w->index_4 = 0;
    w->step_C = 0;
    MoviePlayer_800B2630(ent);
    ent->update_90 = MoviePlayer_800B2630;
}

void CameraOrbitInit_800B28DC(MapEnt* ent)
{
    MapDoorWork* w;

    w = (MapDoorWork*)ent->work_14;
    w->state_0 = 0;
    w->t_4 = 0;
    CameraOrbit_800B2914(ent);
    ent->update_90 = CameraOrbit_800B2914;
}

void CameraOrbit_800B2914(MapEnt* ent)
{
}

void MapInit_800B291C(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B298C();
        ClearFieldMinions_800A7784();
        RequestModels_800B2D30(events_800B3604);
        if (levantAnimSet_80091C74 >= 0)
        {
            LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        }
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B2E00);
    }
}

void StartMapTask_800B298C(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B29BC;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B29BC(EventEntry* entry, int* st)
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
        MapTask_800B2A54(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B2A54;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B2A54(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B3604;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B2B0C(events, currentArea_80091C44);
        st[2] += EnterArea_800B2C28(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B2B0C(MapEvent* ev, int area)
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

int EnterArea_800B2C28(MapEvent* ev, int area, int prev)
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
                AddEntity_800B2E00(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B2D30(MapEvent* ev)
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B2F6C;
        return 1;
    }
    return 0;
}

int AddEntity_800B2E00(void* ev)
{
    return NewEntity(ev);
}

int StopLevantIfSet_800B2F2C(MapScriptSpot* spot)
{
    if (spot->idle_2)
    {
        ResetLevantActorToIdle_800A8DEC();
    }
    return 1;
}

int MinionF_800B2F5C(void)
{
    return 1;
}

int MinionF_800B2F64(void)
{
    return 1;
}

void EntityTask_800B2F6C(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}
