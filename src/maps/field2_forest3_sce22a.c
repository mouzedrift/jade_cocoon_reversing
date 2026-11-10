#include "maps/map.h"

int DrawPicture_800B2334(void);
int AddEffects_800B2444(MapFx* fx);
void FxSprite_800B25D0(MapEnt* ent);
void FxModel_800B2744(MapEnt* ent);
void MinionInit_800B296C(MapEnt* ent);
void MapInit_800B2CA4(int phase);
void FxInit_800B2DA4(MapEnt* ent);
void MinionIdle_800B2E5C(MapEnt* ent);
int PlayMovie_800B2E64(MapMovieArgs* args);
int LoadPicture_800B2EDC(void);
int SetEvents_800B2F58(MapExitArgs* args);
int WarpLostBattle_800B2FAC(void);
int FreeEventData_800B2FCC(void);
int SaveEndOfGame_800B2FEC(void);
void SfxLoopInit_800B3018(MapEnt* ent);
void SfxLoop_800B304C(MapEnt* ent);
void StartMapTask_800B309C(void);
void MapTaskLoad_800B30CC(EventEntry* entry, int* st);
void MapTask_800B3164(EventEntry* entry, int* st);
int LeaveArea_800B3218(MapEvent* ev, int area);
int EnterArea_800B3334(MapEvent* ev, int area, int prev);
void RequestModels_800B343C(MapEvent* ev);
void EntityTask_800B350C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B358C(void* ev);
void MapInitOld_800B36B8(int phase);
int FxFrame_800B3728(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B37AC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3878(MapFx* fx, MapFxWork* w);
int MinionF_800B39C0(void);
int MinionF_800B39C8(void);

extern const int unknown_800B22C0[1];
extern const char data_800B22C4[24];
extern const char data_800B22DC[12];
extern const char data_800B22E8[16];
extern const MapFxInits fxInits_800B22F8;
extern int unknown_800B39D0[50];
extern int data_800B3A98[3];
extern int data_800B3AA4[48];
extern int data_800B3B64[14];
extern int data_800B3B9C[14];
extern int data_800B3BD4[19];
extern int data_800B3C20[19];
extern int data_800B3C6C[12];
extern int data_800B3C9C[12];
extern int data_800B3CCC[12];
extern int data_800B3CFC[34];
extern int data_800B3D84[3];
extern int data_800B3D90[11];
extern int data_800B3DBC[72];
extern int data_800B3EDC[32];
extern int data_800B3F5C[11];
extern int data_800B3F88[48];
extern int data_800B4048[1];
extern int data_800B404C[3];
extern int data_800B4058[11];
extern int data_800B4084[46];
extern int data_800B413C[44];
extern int data_800B41EC[44];
extern int data_800B429C[22];
extern int data_800B42F4[18];
extern int data_800B433C[4];
extern int data_800B434C[4];
extern int data_800B435C[4];
extern int data_800B436C[4];
extern int data_800B437C[3];
extern int data_800B4388[3];
extern int data_800B4394[5];
extern int data_800B43A8[340];
extern int data_800B48F8[152];
extern int data_800B4B58[184];
extern int data_800B4E38[92];
extern int data_800B4FA8[9];
extern int data_800B4FCC[9];
extern int data_800B4FF0[9];
extern MapEvent data_800B5014[5];
extern MapEvent data_800B5078[5];
extern MapEvent data_800B50DC[4];
extern short bones_800B512C[92];
extern int scale_800B51E4[3];
extern SPRT* sprts_800B51F0;
extern DR_TPAGE* tpages_800B51F4;
extern MapEvent* curEvents_800B51F8;

/* script call (every frame): draws the two halves of the loaded picture at the scene's brightness */
int DrawPicture_800B2334(void)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        sprts_800B51F0[i].code &= ~1;
        sprts_800B51F0[i].r0 = (unsigned int)sceneBrightness_8008D40C >> 5;
        sprts_800B51F0[i].g0 = (unsigned int)sceneBrightness_8008D40C >> 5;
        sprts_800B51F0[i].b0 = (unsigned int)sceneBrightness_8008D40C >> 5;
        sprts_800B51F0[i].x0 = (i % 2) * 160;
        sprts_800B51F0[i].y0 = 0;
        AddPrimCopy_80040298(pOT_8008D690, &sprts_800B51F0[i], sizeof(SPRT) / 4);
        AddPrimCopy_80040298(pOT_8008D690, &tpages_800B51F4[i], sizeof(DR_TPAGE) / 4);
    }
    return 0;
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B350C;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B2444(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B2DA4;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

/* NONMATCHING: FxSprite_800B26D0's C does not compile to its code yet */
void FxSprite_800B25D0(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    EffectSprite* sprite;
    EffectSpriteFrame* f;
    int frame;
    int i;
    unsigned short arg;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    sprite = &w->file_0->sprites_20[FindEffectIndex_80020F00(w->file_0, 0, fx->id_2)];
    frame = FxFrame_800B3728(fx, w, sprite->count_0);
    FxTime_800B37AC(ent, fx, w);
    FxPlace_800B3878(fx, w);
    if (frame >= 0)
    {
        for (i = 0; i < sprite->frameCounts_4[frame]; i++)
        {
            arg = fx->arg_24;
            f = &sprite->frames_8[frame][i];
            DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)w->pos_4, (SVECTOR*)w->rot_10, &f->u_0, &f->w_4, &f->pivotX_8, f->size_C,
                                   (SVECTOR*)f->pos_10, f->rgb_18, (arg >> 2) & 2, (short)arg & ~8, pOT_8008D690);
        }
    }
}

void FxModel_800B2744(MapEnt* ent)
{
    int pos[3];
    short rot[3];
    MapFx* fx;
    MapFxWork* w;
    EffectModel* model;
    EffectKey* key;
    int frame;
    int i;
    int light;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    model = &w->file_0->models_28[FindEffectIndex_80020F00(w->file_0, 1, fx->id_2)];
    frame = FxFrame_800B3728(fx, w, model->frameCount_14);
    FxTime_800B37AC(ent, fx, w);
    FxPlace_800B3878(fx, w);
    if (frame >= 0)
    {
        for (i = 0; i < model->keyCount_10; i++)
        {
            key = &model->keys_18[frame * model->keyCount_10] + i;
            pos[0] = w->pos_4[0];
            pos[1] = w->pos_4[1];
            pos[2] = w->pos_4[2];
            pos[0] += key->x_4;
            pos[1] += key->y_8;
            pos[2] += key->z_C;
            rot[0] = w->rot_10[0];
            rot[1] = w->rot_10[1];
            rot[2] = w->rot_10[2];
            rot[0] += key->rot_10[0];
            rot[1] += key->rot_10[1];
            rot[2] += key->rot_10[2];
            light = FindNearestCameraPoint_80019CC4(pos);
            DrawFtgObjectAtSlot0_8004D1EC(&model->ftg_4[key->model_0], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light],
                                          ((0x1000 - key->alpha_2) << 16) | 0x80 | key->mode_24, key->f18);
        }
    }
}

void MinionInit_800B296C(MapEnt* ent)
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
        desc.bones_34 = bones_800B512C;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B51E4;
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
    w->f_C = MinionF_800B39C0;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B39C8;
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
    ent->update_90 = MinionIdle_800B2E5C;
}

/* phase 0: the event table and the map to come back to that event var 11 picks */
void MapInit_800B2CA4(int phase)
{
    if (phase == 0)
    {
        MapEvent* events[3] = { data_800B5014, data_800B5078, data_800B50DC };
        int maps[3] = { 5, 4, 5 };

        curEvents_800B51F8 = events[GetEventVar_800AD154(11)];
        savedLevantPos_80091C78.mapIdx = maps[GetEventVar_800AD154(11)];
    }
    if (phase == 1)
    {
        StartMapTask_800B309C();
        ClearFieldMinions_800A7784();
        RequestModels_800B343C(curEvents_800B51F8);
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74 = 8, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B358C);
    }
}

void FxInit_800B2DA4(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22F8;
    MapFx* fx;
    MapFxWork* w;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    w->file_0 = GetEventDataSlot_800A55B0(0);
    w->time_18 = 0;
    w->delay_1A = 0;
    w->runs_1C = 0;
    w->pos_4[0] = 0;
    w->pos_4[1] = 0;
    w->pos_4[2] = 0;
    w->rot_10[0] = 0;
    w->rot_10[1] = 0;
    w->rot_10[2] = 0;
    ent->update_90 = inits.init[fx->type_0];
    ent->update_90(ent);
}

void MinionIdle_800B2E5C(MapEnt* ent)
{
}

int PlayMovie_800B2E64(MapMovieArgs* args)
{
    int played = args->played_4;
    int mode;

    if (!played)
    {
        mode = FreeMdecBuffer_800A5854();
        PlayMovie_80040EB4(args->movie_0);
        ClearOTagRAll_8001B260();
        AllocMdecBuffer_800A5804(mode);
        args->played_4 = 1;
        eventDispatchHalt_8008B540 = 1;
    }
    return played;
}

/* script call: loads the picture (file 58), darkens the scene and fades it in, stops the camera and the party */
int LoadPicture_800B2EDC(void)
{
    int* file = DATA_GetFileBuffer_8003CAA0(58);

    LoadTiy_80028E74(&sprts_800B51F0, 0, &tpages_800B51F4, file, &mapHeap_80091C68);
    free3_8003FC6C(file);
    SetSceneDark_8001A9E4();
    StartSceneFadeIn_8001AA04(120);
    DisableCameraPoints_800A096C();
    SuspendFieldMinions_800A7B00(-1);
    return 1;
}

int SetEvents_800B2F58(MapExitArgs* args)
{
    SetEventVar_800AD16C(11, args->var_0);
    mapStartMode_80091C54 = 0;
    if ((forceMapReload_80091C9C = args->reload_4) != 0)
    {
        SetLoadFadeFlag_80027478(0x40, 1);
    }
    return 1;
}

int WarpLostBattle_800B2FAC(void)
{
    WarpAfterLostBattle_800A5FAC();
    return 1;
}

int FreeEventData_800B2FCC(void)
{
    FreeEventData_800A56BC(0);
    return 1;
}

/* script call: opens the save menu at the end of the game */
int SaveEndOfGame_800B2FEC(void)
{
    static const char place[16] = "\x83I\x83V\x83}\x83""C\x83""f\x81[\x83^\0\x8e";

    saveRequest_800B06BC.active_0 = 1;
    saveRequest_800B06BC.kind_4 = 0;
    saveRequest_800B06BC.arg_8.savePlace = place;
    saveRequest_800B06BC.endOfGame_C = 1;
    return 1;
}

void SfxLoopInit_800B3018(MapEnt* ent)
{
    ent->work_14[0] = 0;
    SfxLoop_800B304C(ent);
    ent->update_90 = SfxLoop_800B304C;
}

void SfxLoop_800B304C(MapEnt* ent)
{
    if (ent->work_14[0] == 0)
    {
        PlaySfx_80031494(31);
        ent->work_14[0] = 45;
    }
    ent->work_14[0]--;
}

void StartMapTask_800B309C(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B30CC;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B30CC(EventEntry* entry, int* st)
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
        MapTask_800B3164(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3164;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3164(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = curEvents_800B51F8;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B3218(events, currentArea_80091C44);
        st[2] += EnterArea_800B3334(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B3218(MapEvent* ev, int area)
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

int EnterArea_800B3334(MapEvent* ev, int area, int prev)
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
                AddEntity_800B358C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B343C(MapEvent* ev)
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

void EntityTask_800B350C(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B358C(void* ev)
{
    return NewEntity(ev);
}

void MapInitOld_800B36B8(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B309C();
        ClearFieldMinions_800A7784();
        RequestModels_800B343C(curEvents_800B51F8);
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74 = 8, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B358C);
    }
}

int FxFrame_800B3728(MapFx* fx, MapFxWork* w, int count)
{
    int end;
    int length;

    if (fx->delay_1A <= w->delay_1A)
    {
        end = count;
        if (fx->last_22 >= 0)
        {
            end = fx->last_22 + 1;
        }
        length = count;
        if (fx->length_18 >= 0)
        {
            length = fx->length_18;
        }
        return (fx->first_1E + (end - fx->first_1E) * w->time_18 / length) % count;
    }
    return -1;
}

void FxTime_800B37AC(MapEnt* ent, MapFx* fx, MapFxWork* w)
{
    int delay;

    delay = fx->delay_1A;
    if (w->delay_1A < delay)
    {
        w->delay_1A = CLAMP(w->delay_1A + 1, 0, delay);
        return;
    }
    if (++w->time_18 >= fx->length_18)
    {
        if (fx->runs_1C >= 0 && w->runs_1C >= fx->runs_1C)
        {
            if (fx->type_0 == 4)
            {
                pointLightRange_8008D3F0 = 0;
            }
            ent->state_7C = -2;
        }
        w->time_18 = fx->restart_20;
        w->runs_1C++;
    }
}

void FxPlace_800B3878(MapFx* fx, MapFxWork* w)
{
    int pos[3];
    short rot[3];

    if (fx->place_28)
    {
        fx->place_28(pos, rot);
        w->pos_4[0] = pos[0];
        w->pos_4[1] = pos[1];
        w->pos_4[2] = pos[2];
        w->pos_4[0] += fx->pos_4[0];
        w->pos_4[1] += fx->pos_4[1];
        w->pos_4[2] += fx->pos_4[2];
        w->rot_10[0] = rot[0];
        w->rot_10[1] = rot[1];
        w->rot_10[2] = rot[2];
        w->rot_10[0] += fx->rot_10[0];
        w->rot_10[1] += fx->rot_10[1];
        w->rot_10[2] += fx->rot_10[2];
    }
    else
    {
        w->pos_4[0] = fx->pos_4[0];
        w->pos_4[1] = fx->pos_4[1];
        w->pos_4[2] = fx->pos_4[2];
        w->rot_10[0] = fx->rot_10[0];
        w->rot_10[1] = fx->rot_10[1];
        w->rot_10[2] = fx->rot_10[2];
    }
}

int MinionF_800B39C0(void)
{
    return 1;
}

int MinionF_800B39C8(void)
{
    return 1;
}
