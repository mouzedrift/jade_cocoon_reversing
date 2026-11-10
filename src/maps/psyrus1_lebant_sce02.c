#include "maps/map.h"

void MinionInit_800B2300(MapEnt* ent);
int AddEffects_800B2638(MapFx* fx);
void FxSprite_800B27C4(MapEnt* ent);
void FxModel_800B2938(MapEnt* ent);
void SpriteTrail_800B2B60(MapEnt* ent);
void MapInit_800B2DC8(int phase);
void MinionIdle_800B2E34(MapEnt* ent);
int EndEffects_800B2E3C(void);
void FxInit_800B2EBC(MapEnt* ent);
void FxMdec_800B2F74(MapEnt* ent);
void SpriteTrailInit_800B3060(MapEnt* ent);
void QuakeInit_800B309C(MapEnt* ent);
void Quake_800B30E8(MapEnt* ent);
void StartMapTask_800B3218(void);
void MapTaskLoad_800B3248(EventEntry* entry, int* st);
void MapTask_800B32E0(EventEntry* entry, int* st);
int LeaveArea_800B3398(MapEvent* ev, int area);
int EnterArea_800B34B4(MapEvent* ev, int area, int prev);
void RequestModels_800B35BC(MapEvent* ev);
void EntityTask_800B368C(EventEntry* entry, MapEnt* ent);
int AddEntity_800B370C(void* ev);
int MinionF_800B3838(void);
int MinionF_800B3840(void);
int FxFrame_800B3848(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B38CC(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3998(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const char str_800B22D0[12];
extern const char str_800B22DC[16];
extern const MapFxInits fxInits_800B22EC;
extern MapSpritePoint points_800B3AE0[101];
extern MapSpritePoint points_800B4130[101];
extern ActorScriptCmd* script_800B4780;
extern MapActorModel model_800B4784;
extern ActorScriptCmd* script_800B47B0;
extern MapActorModel model_800B47B4;
extern ActorScriptCmd* script_800B47E0;
extern MapActorModel model_800B47E4;
extern MapFx effects_800B4810[3];
extern MapFx effects_800B4894[3];
extern MapFx effects_800B4918[3];
extern MapFx effects_800B499C[6];
extern MapFx effects_800B4AA4[6];
extern int unknown_800B4BAC[77];
extern MapFx effects_800B4CE0[2];
extern MapFx effects_800B4D38[3];
extern MapSpritePoint* event_800B4DBC[2];
extern int data_800B4DC4[4];
extern int data_800B4DD4[3];
extern MapEvent event_800B4DE0;
extern MapInstr script_800B4DF4[135];
extern MapMinion minion_800B5664;
extern MapMinion minion_800B5688;
extern MapMinion minion_800B56AC;
extern MapEvent events_800B56D0[6];
extern short bones_800B5748[92];
extern int scale_800B5800[3];

void MinionInit_800B2300(MapEnt* ent)
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
        desc.bones_34 = bones_800B5748;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B5800;
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
    w->f_C = MinionF_800B3838;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B3840;
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
    ent->update_90 = MinionIdle_800B2E34;
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B368C;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B2638(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B2EBC;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

/* NONMATCHING: FxSprite_800B26D0's C does not compile to its code yet */
void FxSprite_800B27C4(MapEnt* ent)
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
    frame = FxFrame_800B3848(fx, w, sprite->count_0);
    FxTime_800B38CC(ent, fx, w);
    FxPlace_800B3998(fx, w);
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

void FxModel_800B2938(MapEnt* ent)
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
    frame = FxFrame_800B3848(fx, w, model->frameCount_14);
    FxTime_800B38CC(ent, fx, w);
    FxPlace_800B3998(fx, w);
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

/* NONMATCHING: the list lookup adds the other way round and p / ofs swap registers */
/* draws effect 326's sprite animation at each point of the list the script picked, each from its own start */
void SpriteTrail_800B2B60(MapEnt* ent)
{
    MapSpritePoint** lists = ent->data_10;
    int* w = ent->work_14;
    EffectFile* file;
    EffectSprite* sprite;
    MapSpritePoint* p;
    int t;
    int frame;
    int i;
    int ofs;
    int pos[3];
    SVECTOR rot;
    EffectSpriteFrame* f;

    switch (ent->state_7C)
    {
    case 0:
    case 1:
        ent->work_14[0] = ent->state_7C;
        w[1] = 0;
        ent->state_7C = -1;
        break;
    case 2:
        ent->work_14[0] = -1;
        ent->state_7C = -1;
        break;
    }
    if (w[0] < 0)
    {
        return;
    }
    file = GetEventDataSlot_800A55B0(0);
    sprite = &file->sprites_20[FindEffectIndex_80020F00(file, 0, 326)];
    for (t = w[1]; t >= 0; t -= sprite->count_0)
    {
        for (p = lists[w[0]]; p->start_C >= 0; p++)
        {
            if (t < p->start_C)
            {
                continue;
            }
            frame = t - p->start_C;
            if (frame < 0 || frame >= sprite->count_0 || !sprite->frameCounts_4[frame])
            {
                continue;
            }
            for (i = 0, ofs = 0; i < sprite->frameCounts_4[frame]; i++, ofs += sizeof(EffectSpriteFrame))
            {
                memset(pos, 0, sizeof(pos));
                memset(&rot, 0, sizeof(rot));
                f = (EffectSpriteFrame*)((char*)sprite->frames_8[frame] + ofs);
                pos[0] = p->pos_0[0];
                pos[1] = p->pos_0[1];
                pos[2] = p->pos_0[2];
                DrawRotSprite_80044010(&sprite->poly_C, (VECTOR*)pos, &rot, &f->u_0, &f->w_4, &f->pivotX_8, f->size_C, (SVECTOR*)f->pos_10,
                                       f->rgb_18, 0, 48, pOT_8008D690);
            }
        }
    }
    w[1]++;
}

void MapInit_800B2DC8(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B3218();
        ClearFieldMinions_800A7784();
        RequestModels_800B35BC(events_800B56D0);
        levantAnimSet_80091C74 = 6;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B370C);
    }
}

void MinionIdle_800B2E34(MapEnt* ent)
{
}

int EndEffects_800B2E3C(void)
{
    EventNode* node;
    EventEntry* entry;
    int count;
    int i;

    node = eventEntities_8008D400;
    count = node->count;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1)
        {
            if (((MapEnt*)entry->buffer)->type_C == 7)
            {
                entry->flags = (entry->flags & ~1) | 0x8000;
            }
        }
        node = node->next;
    }
    pointLightRange_8008D3F0 = 0;
    return 1;
}

void FxInit_800B2EBC(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22EC;
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

void FxMdec_800B2F74(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    MdecImageSet* set;
    int frame;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    set = &w->file_0->imageSets_30[FindEffectIndex_80020F00(w->file_0, 2, fx->id_2)];
    frame = FxFrame_800B3848(fx, w, set->count_0);
    FxTime_800B38CC(ent, fx, w);
    if (frame >= 0 && !(unknownFlags_8008D678 & 0x800))
    {
        mdecEffectVlcBuffer_8008D42C = w->file_0->mdec_34.dct_0;
        decodedImageData_8008B4A0 = w->file_0->mdec_34.work_4;
        DecodeMdec_80041920(set->images_4[frame], mdecEffectVlcBuffer_8008D42C, fx->arg_24);
        unknownFlags_8008D678 |= 0x800;
    }
}

void SpriteTrailInit_800B3060(MapEnt* ent)
{
    ent->work_14[0] = -1;
    ent->work_14[1] = 0;
    SpriteTrail_800B2B60(ent);
    ent->update_90 = SpriteTrail_800B2B60;
}

/* work_14: frames, frames since the period changed, period, frames to the next rumble, to the next sound */
void QuakeInit_800B309C(MapEnt* ent)
{
    int* w = ent->work_14;

    ent->work_14[0] = 0;
    w[1] = 0;
    w[3] = 0;
    w[2] = 30;
    w[4] = 30;
    Quake_800B30E8(ent);
    ent->update_90 = Quake_800B30E8;
}

/* rumbles and rumbles louder every period frames: faster for 900 frames, then slower again */
void Quake_800B30E8(MapEnt* ent)
{
    int* w = ent->work_14;

    if (w[3] == 0)
    {
        StartPadVibration_80036528(0, 12);
        PlaySfx_80031494(53);
        w[3] = w[2];
        w[4] = w[3] / 3;
    }
    if (w[4] == 0)
    {
        PlaySfx_80031494(53);
    }
    if (ent->work_14[0] < 900)
    {
        if (w[1] >= 29)
        {
            if (w[2] >= 16)
            {
                w[2]--;
            }
            w[1] = 0;
        }
    }
    else if (w[1] >= 63)
    {
        if (w[2] < 30)
        {
            w[2]++;
        }
        w[1] = 0;
    }
    w[0]++;
    w[1]++;
    w[3]--;
    w[4]--;
}

void StartMapTask_800B3218(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B3248;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B3248(EventEntry* entry, int* st)
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
        MapTask_800B32E0(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B32E0;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B32E0(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B56D0;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B3398(events, currentArea_80091C44);
        st[2] += EnterArea_800B34B4(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B3398(MapEvent* ev, int area)
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

int EnterArea_800B34B4(MapEvent* ev, int area, int prev)
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
                AddEntity_800B370C(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B35BC(MapEvent* ev)
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

void EntityTask_800B368C(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B370C(void* ev)
{
    return NewEntity(ev);
}

int MinionF_800B3838(void)
{
    return 1;
}

int MinionF_800B3840(void)
{
    return 1;
}

int FxFrame_800B3848(MapFx* fx, MapFxWork* w, int count)
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

void FxTime_800B38CC(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B3998(MapFx* fx, MapFxWork* w)
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
