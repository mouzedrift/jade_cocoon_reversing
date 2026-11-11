#include "maps/map.h"

void Warp_800B2304(MapEnt* ent);
void MinionInit_800B2428(MapEnt* ent);
int AddEffects_800B2760(MapFx* fx);
void FxModel_800B28EC(MapEnt* ent);
void ExitSpot_800B2B14(MapEnt* ent);
void SavePoint_800B2C80(MapEnt* ent);
void MapInitOld_800B30F0(int phase);
void MinionIdle_800B31B8(MapEnt* ent);
void FxInit_800B31C0(MapEnt* ent);
void FxMdec_800B3278(MapEnt* ent);
void ExitSpotInit_800B3364(MapEnt* ent);
void SavePointInit_800B3400(MapEnt* ent);
void StartMapTask_800B3440(void);
void MapTaskLoad_800B3470(EventEntry* entry, int* st);
void MapTask_800B3508(EventEntry* entry, int* st);
int LeaveArea_800B35C0(MapEvent* ev, int area);
int EnterArea_800B36DC(MapEvent* ev, int area, int prev);
void RequestModels_800B37E4(MapEvent* ev);
void EntityTask_800B38B4(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3934(void* ev);
void MapInit_800B3A60(int phase);
int MinionF_800B3ACC(void);
int MinionF_800B3AD4(void);
int FxFrame_800B3ADC(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3B60(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3C2C(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[28];
extern const char str_800B22E0[8];
extern const MapFxInits fxInits_800B22E8;
extern const MapRgb savePointDim_800B22FC;
extern const MapRgb savePointLit_800B2300;
extern MapSavePoint savePoint_800B3D74;
extern short bones_800B3D84[96];
extern ActorScriptCmd* script_800B3E44;
extern MapActorModel model_800B3E48;
extern MapVoice voices_800B3E74[37];
extern MapWarp warp_800B3F9C;
extern int data_800B3FB4[4];
extern int data_800B3FC4[3];
extern MapInstr script_800B3FD0[15];
extern MapInstr script_800B40C0[146];
extern MapInstr script_800B49E0[37];
extern MapExitSpot data_800B4C30;
extern MapMinion minion_800B4C50;
extern MapEvent events_800B4C74[9];
extern short bones_800B4D28[92];
extern int scale_800B4DE0[3];
extern int data_800B4DEC[33];
extern int data_800B4E70[52];
extern int data_800B4F40[56];
extern int data_800B5020[76];

void Warp_800B2304(MapEnt* ent)
{
    MapWarp* warp;
    LevantPos* levant;

    warp = ent->data_10;
    if (fieldMode_800B0EC0 == 1 && !(battleFlags_800B1228 & 0x4000))
    {
        levant = &saveData_8008B570.levant_7A8;
        if (IsEventPointValid_800A6504(warp->point_10, (int*)levant))
        {
            savedLevantPos_80091C78.pos[0] = warp->pos_0[0];
            savedLevantPos_80091C78.pos[1] = warp->pos_0[1];
            savedLevantPos_80091C78.pos[2] = warp->pos_0[2];
            if (warp->rotY_C != 0x4000)
            {
                savedLevantRot_80091CA8[0] = 0;
                savedLevantRot_80091CA8[1] = levant->rot.vy + warp->rotY_C;
                savedLevantRot_80091CA8[2] = 0;
            }
            else
            {
                savedLevantRot_80091CA8[0] = saveData_8008B570.levant_7A8.rot.vx;
                savedLevantRot_80091CA8[1] = saveData_8008B570.levant_7A8.rot.vy;
                savedLevantRot_80091CA8[2] = saveData_8008B570.levant_7A8.rot.vz;
            }
            saveData_8008B570.mapId_2E4[0].cur_0 = warp->map_12[0];
            saveData_8008B570.mapId_2E4[1].cur_0 = warp->map_12[1];
            saveData_8008B570.mapId_2E4[2].cur_0 = warp->map_12[2];
            useSavedLevantPos_80091C98 = 1;
            forceMapReload_80091C9C = 1;
            if (warp->idle_E)
            {
                ResetLevantActorToIdle_800A8DEC();
            }
        }
    }
}

void MinionInit_800B2428(MapEnt* ent)
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
        desc.bones_34 = bones_800B4D28;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B4DE0;
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
    w->f_C = MinionF_800B3ACC;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B3AD4;
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
    ent->update_90 = MinionIdle_800B31B8;
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B38B4;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B2760(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B31C0;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

void FxModel_800B28EC(MapEnt* ent)
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
    frame = FxFrame_800B3ADC(fx, w, model->frameCount_14);
    FxTime_800B3B60(ent, fx, w);
    FxPlace_800B3C2C(fx, w);
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

/* starts its script when Levant reaches the event point; state 0: script started, 1: leave the map */
void ExitSpot_800B2B14(MapEnt* ent)
{
    MapExitSpot* exit = ent->data_10;
    int* script = ent->work_14;
    GameMapLoc loc;

    if (IsEventPointValid_800A6504(exit->point_C, (int*)&levantPos_8008BD18) && !FindEventScript_800A5AE4(*script))
    {
        ent->state_7C = 0;
    }
    switch (ent->state_7C)
    {
    case 0:
        *script = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(data_800B4E70, ent));
        ent->prev_80 = ent->state_7C;
        ent->state_7C = -1;
        break;
    case 1:
        FindMapEntrance_800ADCEC(&loc, exit->entrance_0);
        saveData_8008B570.mapId_2E4[3].cur_0 = 0;
        useMapStartPos_80091C94 = 1;
        mapStartMode_80091C54 = 0;
        saveData_8008B570.mapId_2E4[0].cur_0 = loc.area;
        saveData_8008B570.mapId_2E4[1].cur_0 = loc.map;
        saveData_8008B570.mapId_2E4[2].cur_0 = loc.entrance;
        ent->prev_80 = ent->state_7C;
        ent->state_7C = -1;
        SetLoadFadeFlag_80027478(0x40, 1);
        SetEventVar_800AD16C(0, exit->vars_4 / 256);
        SetEventVar_800AD16C(1, exit->vars_4 % 256);
        SetEventFlag_800AD0F8(exit->flag_8);
        break;
    }
}

void SavePoint_800B2C80(MapEnt* ent)
{
    int pos[3];
    short rot[4];
    int scale[3];
    MapRgb dim;
    MapRgb lit;
    MapRgb rgb;
    MapSavePoint* save;
    MapSavePointWork* w;
    FtgPolyG3List* list;
    int i;
    int alpha;
    int light;
    int near;

    save = ent->data_10;
    w = (MapSavePointWork*)ent->work_14;
    if (IsPointInViewCone_800A65F0(save->pos_0, (int*)&levantPos_8008BD18, (unsigned short*)&levantPos_8008BD18.rot, 300))
    {
        ent->armed_78 = 1;
    }
    if (ent->state_7C == 0)
    {
        saveRequest_800B06BC.active_0 = 1;
        saveRequest_800B06BC.kind_4 = 0;
        saveRequest_800B06BC.arg_8.savePlace = save->name_C;
        saveRequest_800B06BC.endOfGame_C = 0;
        ent->state_7C = -1;
    }
    list = &publicFtg_8008D4D0[1].g3_8;
    dim = savePointDim_800B22FC;
    lit = savePointLit_800B2300;
    rgb.r = dim.r + (lit.r - dim.r) * w->glow_8 / 15;
    rgb.g = dim.g + (lit.g - dim.g) * w->glow_8 / 15;
    rgb.b = dim.b + (lit.b - dim.b) * w->glow_8 / 15;
    for (i = 0; i < list->count; i++)
    {
        list->items[i].c[0].r = list->items[i].c[1].r = list->items[i].c[2].r = rgb.r;
        list->items[i].c[0].g = list->items[i].c[1].g = list->items[i].c[2].g = rgb.g;
        list->items[i].c[0].b = list->items[i].c[1].b = list->items[i].c[2].b = rgb.b;
    }
    w->glow_8 = CLAMP(w->glow_8 + (ent->armed_78 ? 1 : -1), 0, 15);
    pos[0] = save->pos_0[0];
    pos[1] = save->pos_0[1] + (short)(sinTable_80084540[w->phase_4 & 0xFFF] / 163);
    pos[2] = save->pos_0[2];
    scale[0] = scale[1] = scale[2] = (sinTable_80084540[w->phase_4 & 0xFFF] + 0x1000) / 10 + 0x1000;
    rot[0] = 0;
    rot[1] = w->angle_0;
    rot[2] = 0;
    alpha = (short)sinTable_80084540[w->phase_4 & 0xFFF] / 2 + 0x1000;
    light = FindNearestCameraPoint_80019CC4(pos);
    near = ent->armed_78 != 0;
    DrawFtgObjectAtSlot0_8004D1EC(&publicFtg_8008D4D0[1], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light],
                                  (near << 5) | 0x91 | ((0x1000 - alpha) << 16), 0);
    DrawFtgObjectAtSlot0_8004D1EC(&publicFtg_8008D4D0[2], pOT_8008D690, save->pos_0, rot, &cameraState_8008D4F0.ent_44[light], 0x31, scale);
    if (ent->armed_78)
    {
        w->angle_0 += 0x40;
        w->phase_4 += 0xE2;
    }
    else
    {
        w->angle_0 += 0x20;
        w->phase_4 += 0x71;
    }
}

/* not used: the map's init before MapInit_800B3A60 (phase 0: Levant back at the exit when event var 4 is set) */
void MapInitOld_800B30F0(int phase)
{
    if (phase == 0 && GetEventVar_800AD154(4))
    {
        saveData_8008B570.levant_7A8.pos.x = data_800B4C30.pos_10[0];
        saveData_8008B570.levant_7A8.pos.y = data_800B4C30.pos_10[1];
        saveData_8008B570.levant_7A8.pos.z = data_800B4C30.pos_10[2];
        saveData_8008B570.levant_7A8.rot.vy = data_800B4C30.rotY_1C;
        SetLevantVisible_800ABBD8(0);
        useMapStartPos_80091C94 = 0;
    }
    if (phase == 1)
    {
        StartMapTask_800B3440();
        ClearFieldMinions_800A7784();
        RequestModels_800B37E4(events_800B4C74);
        levantAnimSet_80091C74 = 49;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3934);
    }
}

void MinionIdle_800B31B8(MapEnt* ent)
{
}

void FxInit_800B31C0(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22E8;
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

void FxMdec_800B3278(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    MdecImageSet* set;
    int frame;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    set = &w->file_0->imageSets_30[FindEffectIndex_80020F00(w->file_0, 2, fx->id_2)];
    frame = FxFrame_800B3ADC(fx, w, set->count_0);
    FxTime_800B3B60(ent, fx, w);
    if (frame >= 0 && !(unknownFlags_8008D678 & 0x800))
    {
        mdecEffectVlcBuffer_8008D42C = w->file_0->mdec_34.dct_0;
        decodedImageData_8008B4A0 = w->file_0->mdec_34.work_4;
        DecodeMdec_80041920(set->images_4[frame], mdecEffectVlcBuffer_8008D42C, fx->arg_24);
        unknownFlags_8008D678 |= 0x800;
    }
}

/* event var 4 set: Levant came back through the exit (event flag 0 picks the script) */
void ExitSpotInit_800B3364(MapEnt* ent)
{
    int* script = ent->work_14;

    if (GetEventVar_800AD154(4))
    {
        *script = GetEventScriptId_800A5AD0(StartEventScriptForEntity_800A5AA0(TestEventFlag_800AD0D4(0) ? data_800B5020 : data_800B4F40, ent));
        SetEventVar_800AD16C(4, 0);
    }
    else
    {
        ent->work_14[0] = -1;
    }
    ExitSpot_800B2B14(ent);
    ent->update_90 = ExitSpot_800B2B14;
}

void SavePointInit_800B3400(MapEnt* ent)
{
    MapSavePointWork* w = (MapSavePointWork*)ent->work_14;

    w->angle_0 = 0;
    w->phase_4 = 0;
    w->glow_8 = 0;
    SavePoint_800B2C80(ent);
    ent->update_90 = SavePoint_800B2C80;
}

void StartMapTask_800B3440(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B3470;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B3470(EventEntry* entry, int* st)
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
        MapTask_800B3508(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3508;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3508(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B4C74;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B35C0(events, currentArea_80091C44);
        st[2] += EnterArea_800B36DC(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B35C0(MapEvent* ev, int area)
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

int EnterArea_800B36DC(MapEvent* ev, int area, int prev)
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
                AddEntity_800B3934(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B37E4(MapEvent* ev)
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

void EntityTask_800B38B4(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B3934(void* ev)
{
    return NewEntity(ev);
}

void MapInit_800B3A60(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B3440();
        ClearFieldMinions_800A7784();
        RequestModels_800B37E4(events_800B4C74);
        levantAnimSet_80091C74 = 49;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3934);
    }
}

int MinionF_800B3ACC(void)
{
    return 1;
}

int MinionF_800B3AD4(void)
{
    return 1;
}

int FxFrame_800B3ADC(MapFx* fx, MapFxWork* w, int count)
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
        return MOD0(fx->first_1E + DIV0((end - fx->first_1E) * w->time_18, length), count);
    }
    return -1;
}

void FxTime_800B3B60(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B3C2C(MapFx* fx, MapFxWork* w)
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
