#include "maps/map.h"

void MinionInit_800B22E4(MapEnt* ent);
int AddEffects_800B261C(MapFx* fx);
void FxSprite_800B27A8(MapEnt* ent);
void FxModel_800B291C(MapEnt* ent);
void FxModels_800B2B44(MapEnt* ent);
void MapInit_800B30EC(int phase);
void MinionIdle_800B3158(MapEnt* ent);
int EndEffects_800B3160(void);
void FxInit_800B31E0(MapEnt* ent);
void FxModelsInit_800B3298(MapEnt* ent);
void FxAtLevantBone_800B32F4(int* pos, short* rot);
int SwitchBone_800B3404(void);
int ShakeCamera_800B342C(void);
void StartMapTask_800B344C(void);
void MapTaskLoad_800B347C(EventEntry* entry, int* st);
void MapTask_800B3514(EventEntry* entry, int* st);
int LeaveArea_800B35CC(MapEvent* ev, int area);
int EnterArea_800B36E8(MapEvent* ev, int area, int prev);
void RequestModels_800B37F0(MapEvent* ev);
void EntityTask_800B38C0(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3940(void* ev);
int MinionF_800B3A6C(void);
int MinionF_800B3A74(void);
int FxFrame_800B3A7C(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3B00(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B3BCC(MapFx* fx, MapFxWork* w);

extern const char unknown_800B22C0[4];
extern const char str_800B22C4[12];
extern const MapFxInits fxInits_800B22D0;
extern int data_800B3D14[3];
extern short bones_800B3D20[116];
extern ActorScriptCmd* script_800B3E08;
extern MapActorModel model_800B3E0C;
extern int bone7_800B3E38;
extern MapVoice voices_800B3E3C[5];
extern MapFxModels fxModels_800B3E64;
extern int unknown_800B3E8C[2];
extern MapFx effects_800B3E94[2];
extern MapFx effects_800B3EEC[2];
extern MapFx effects_800B3F44[2];
extern MapFx effects_800B3F9C[2];
extern MapFx effects_800B3FF4[3];
extern MapFx effects_800B4078[2];
extern MapFx effects_800B40D0[2];
extern int data_800B4128[4];
extern MapInstr script_800B4138[103];
extern MapMinion minion_800B47A8;
extern MapEvent events_800B47CC[5];
extern short bones_800B4830[92];
extern int scale_800B48E8[3];

void MinionInit_800B22E4(MapEnt* ent)
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
        desc.bones_34 = bones_800B4830;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B48E8;
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
    w->f_C = MinionF_800B3A6C;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B3A74;
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
    ent->update_90 = MinionIdle_800B3158;
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B38C0;
        return 1;
    }
    return 0;
}

/* NONMATCHING: AddEffects_800B2544's C does not compile to its code yet */
int AddEffects_800B261C(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B31E0;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

/* NONMATCHING: FxSprite_800B26D0's C does not compile to its code yet */
void FxSprite_800B27A8(MapEnt* ent)
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
    frame = FxFrame_800B3A7C(fx, w, sprite->count_0);
    FxTime_800B3B00(ent, fx, w);
    FxPlace_800B3BCC(fx, w);
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

void FxModel_800B291C(MapEnt* ent)
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
    frame = FxFrame_800B3A7C(fx, w, model->frameCount_14);
    FxTime_800B3B00(ent, fx, w);
    FxPlace_800B3BCC(fx, w);
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

/* NONMATCHING: scheduling and registers in the draw loop */
void FxModels_800B2B44(MapEnt* ent)
{
    MapFxModels* fx = ent->data_10;
    MapFxModelsWork* w = (MapFxModelsWork*)ent->work_14;
    EffectFile* file;
    EffectModel* a;
    EffectModel* b;
    EffectKey* key;
    int pos[3];
    short rot[4];
    int n;
    int i;
    int light;

    if (ent->state_7C != -1)
    {
        ent->state_7C = -1;
        ent->work_14[0]++;
    }
    switch (ent->work_14[0])
    {
    case 0:
        w->loopStart_8 = 0;
        w->loopEnd_C = 0;
        w->loopStart2_14 = 0;
        w->loopEnd2_18 = 0;
        break;
    case 1:
        w->loopStart_8 = 0;
        w->loopEnd_C = 0;
        w->loopStart2_14 = 0;
        w->loopEnd2_18 = 15;
        break;
    case 2:
        w->loopStart_8 = w->loopEnd_C = 236;
        w->loopStart2_14 = 0;
        w->loopEnd2_18 = 15;
        break;
    case 3:
        w->loopStart_8 = w->loopEnd_C = 379;
        w->loopStart2_14 = 0;
        w->loopEnd2_18 = 15;
        break;
    }
    if (w->frame_4 == 1 && !w->rumble_1C)
    {
        StartPadVibration_80036528(0, 25);
        w->rumble_1C = 1;
        PlaySfx_80031494(49);
        w->voice_20 = SfxKeyOn_800314F4(50);
    }
    if (w->frame_4 == 210 && w->stage_0 == 2 && w->rumble_1C == 1)
    {
        w->rumble_1C = 0;
        PlaySfx_80031494(49);
        SfxKeyOff_80031574(w->voice_20, 50);
    }
    if (w->frame_4 == 237 && !w->rumble_1C && w->stage_0 == 3)
    {
        StartPadVibration_80036528(0, 0);
        w->rumble_1C = 1;
        PlaySfx_80031494(49);
        w->voice_20 = SfxKeyOn_800314F4(50);
    }
    if (w->frame_4 == 345 && w->rumble_1C == 1)
    {
        w->rumble_1C = 0;
        PlaySfx_80031494(49);
        SfxKeyOff_80031574(w->voice_20, 50);
    }
    if (w->frame2_10 == 7)
    {
        PlaySfx_80031494(23);
    }
    file = GetEventDataSlot_800A55B0(0);
    a = &file->models_28[FindEffectIndex_80020F00(file, 1, fx->id_0)];
    b = &file->models_28[FindEffectIndex_80020F00(file, 1, fx->id_18)];
    n = a->keyCount_10 < b->keyCount_10 ? b->keyCount_10 : a->keyCount_10;
    for (i = 0; i < n; i++)
    {
        if (i < a->keyCount_10)
        {
            key = &(a->keys_18 + w->frame_4 * a->keyCount_10)[i];
            pos[0] = fx->pos_4[0];
            pos[1] = fx->pos_4[1];
            pos[2] = fx->pos_4[2];
            pos[0] += key->x_4;
            pos[1] += key->y_8;
            pos[2] += key->z_C;
            rot[0] = fx->rot_10[0];
            rot[1] = fx->rot_10[1];
            rot[2] = fx->rot_10[2];
            rot[0] += key->rot_10[0];
            rot[1] += key->rot_10[1];
            rot[2] += key->rot_10[2];
            light = FindNearestCameraPoint_80019CC4(pos);
            DrawFtgObjectAtSlot0_8004D1EC(&a->ftg_4[key->model_0], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light],
                                          ((0x1000 - key->alpha_2) << 16) | (key->mode_24 | 0x80), key->f18);
        }
        if (i < b->keyCount_10)
        {
            key = &(b->keys_18 + w->frame2_10 * b->keyCount_10)[i];
            pos[0] += key->x_4;
            pos[1] += key->y_8;
            pos[2] += key->z_C;
            rot[0] += key->rot_10[0];
            rot[1] += key->rot_10[1];
            rot[2] += key->rot_10[2];
            light = FindNearestCameraPoint_80019CC4(pos);
            DrawFtgObjectAtSlot0_8004D1EC(&b->ftg_4[key->model_0], pOT_8008D690, pos, rot, &cameraState_8008D4F0.ent_44[light],
                                          ((0x1000 - key->alpha_2) << 16) | (key->mode_24 | 0x80), key->f18);
        }
    }
    w->frame_4++;
    if (w->frame_4 >= w->loopEnd_C)
    {
        w->frame_4 = w->loopStart_8;
    }
    w->frame2_10 += frameCount_8008D3FC & 1;
    if (w->frame2_10 >= w->loopEnd2_18)
    {
        w->frame2_10 = w->loopStart2_14;
    }
}

void MapInit_800B30EC(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B344C();
        ClearFieldMinions_800A7784();
        RequestModels_800B37F0(events_800B47CC);
        levantAnimSet_80091C74 = 44;
        LoadLevantAnimSet_800AC708(levantAnimSet_80091C74, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3940);
    }
}

void MinionIdle_800B3158(MapEnt* ent)
{
}

int EndEffects_800B3160(void)
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

void FxInit_800B31E0(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22D0;
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

void FxModelsInit_800B3298(MapEnt* ent)
{
    MapFxModelsWork* w = (MapFxModelsWork*)ent->work_14;

    ent->work_14[0] = 0;
    w->loopEnd2_18 = 0;
    w->loopStart2_14 = 0;
    w->frame2_10 = 0;
    w->loopEnd_C = 0;
    w->loopStart_8 = 0;
    w->frame_4 = 0;
    w->rumble_1C = 0;
    w->voice_20 = -1;
    FxModels_800B2B44(ent);
    ent->update_90 = FxModels_800B2B44;
}

/* places an effect at Levant's bone 7 (bone7_800B3E38) or 1 */
void FxAtLevantBone_800B32F4(int* pos, short* rot)
{
    EffectTarget t;
    int p[3];
    SVECTOR r;
    int bone;

    memset(p, 0, sizeof(p));
    memset(&r, 0, sizeof(r));
    GetLevantEffectTarget_800A93A4(&t);
    bone = 1;
    if (bone7_800B3E38)
    {
        bone = 7;
    }
    p[0] = t.pos_4[0];
    p[1] = t.pos_4[1];
    p[2] = t.pos_4[2];
    p[0] = t.bonePos_8[bone * 3] + p[0];
    p[1] = t.bonePos_8[bone * 3 + 1] + p[1];
    p[2] = t.bonePos_8[bone * 3 + 2] + p[2];
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    rot[0] = r.vx;
    rot[1] = r.vy;
    rot[2] = r.vz;
}

/* script call: switches bone7_800B3E38 */
int SwitchBone_800B3404(void)
{
    if (bone7_800B3E38)
    {
        bone7_800B3E38 = 0;
    }
    else
    {
        bone7_800B3E38 = 1;
    }
    return 1;
}

int ShakeCamera_800B342C(void)
{
    StartCameraShake_80037BFC(0);
    return 1;
}

void StartMapTask_800B344C(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B347C;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B347C(EventEntry* entry, int* st)
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
        MapTask_800B3514(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B3514;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B3514(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B47CC;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B35CC(events, currentArea_80091C44);
        st[2] += EnterArea_800B36E8(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B35CC(MapEvent* ev, int area)
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

int EnterArea_800B36E8(MapEvent* ev, int area, int prev)
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
                AddEntity_800B3940(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B37F0(MapEvent* ev)
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

void EntityTask_800B38C0(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B3940(void* ev)
{
    return NewEntity(ev);
}

int MinionF_800B3A6C(void)
{
    return 1;
}

int MinionF_800B3A74(void)
{
    return 1;
}

int FxFrame_800B3A7C(MapFx* fx, MapFxWork* w, int count)
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

void FxTime_800B3B00(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B3BCC(MapFx* fx, MapFxWork* w)
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
