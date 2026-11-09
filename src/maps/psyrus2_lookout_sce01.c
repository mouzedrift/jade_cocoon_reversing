#include "maps/map.h"

void MinionInit_800B2328(MapEnt* ent);
void FxModel_800B2B20(MapEnt* ent);
void FxMdec_800B3130(MapEnt* ent);
void Door_800B2D48(MapEnt* ent);
void MinionIdle_800B3070(MapEnt* ent);
void FxInit_800B3078(MapEnt* ent);
void DoorInit_800B321C(MapEnt* ent);
void StartMapTask_800B3254(void);
void MapTaskLoad_800B3284(EventEntry* entry, int* st);
void MapTask_800B331C(EventEntry* entry, int* st);
int LeaveArea_800B33D4(MapEvent* ev, int area);
int EnterArea_800B34F0(MapEvent* ev, int area, int prev);
void RequestModels_800B35F8(MapEvent* ev);
void EntityTask_800B36C8(EventEntry* entry, MapEnt* ent);
int AddEntity_800B3748(void* ev);
int MinionF_800B3874(void);
int MinionF_800B387C(void);
int AddEffects_800B2994(MapFx* fx);
int FxFrame_800B3884(MapFx* fx, MapFxWork* w, int count);
void FxTime_800B3908(MapEnt* ent, MapFx* fx, MapFxWork* w);
void FxPlace_800B39D4(MapFx* fx, MapFxWork* w);

const char unknown_800B22C0[] = "w";
ActorScriptCmd* script_800B3B1C[] = { 0 };
MapActorModel model_800B3B20 = { "\x82\x6c\x82\x81\x82\x88\x82\x82\x82\x95", 0x2E, 0, 0, 0, 0, 4, script_800B3B1C, 0, 0x800000, 0, 1 };
ActorScriptCmd* script_800B3B4C[] = { 0 };
MapActorModel model_800B3B50 = { "\x82\x6b\x82\x95\x82\x89", 0x2C, 0, 0, 0, 0, 4, script_800B3B4C, 0, 0x800000, 0, 1 };
MapVoice voices_800B3B7C[] = {
    { 0, 0, 0x1B, 0x2AA, 0x17 },
    { 0, 1, 0x15, 0x2AC, 0xF },
    { 0, 2, 6, 0x2AE, 0x1B },
    { 0, 3, 0xA, 0x2AE, 0x14 },
    { 0, 4, 0x14, 0x2AF, 4 },
    { 1, 0, 0xB, 0x268, 0x14 },
    { 2, 0, 0, 0x2B1, 0x19 },
    { 3, 0, 1, 0x26A, 0x1E },
    { 3, 1, 0xA, 0x26A, 0x1C },
    { 3, 2, 3, 0x26B, 0x1A },
    { 4, 0, 0xD, 0x2B2, 0x14 },
    { 4, 1, 0x10, 0x2B2, 0x11 },
    { 4, 2, 0x19, 0x2B2, 0x18 },
    { 4, 3, 0x1D, 0x2B2, 0x1A },
    { 4, 4, 1, 0x2B3, 0x1C },
    { 0, 0, -0x1, 0, 0 },
};
int pos_800B3BFC[4] = { 0xC8, -0x759, 0x23F, 0 };
int pos_800B3C0C[3] = { -0x134, -0x18EB, 0x269 };
MapEvent doorEvent_800B3C18 = { -1, 0xD, 0, 8, { DoorInit_800B321C } };
MapFx effects_800B3C2C[] = {
    { MAP_FX_MODEL, 0x4F, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, 0, 0, 0, 0 },
    { MAP_FX_MDEC, 0x15, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0x1E, 0, 0, 0, 0, 0x1D, 2, 0, 0 },
    { MAP_FX_END },
};
MapInstr script_800B3CB0[] = {
    { 5, 0, 0, 0 },
    { 7, 0, 7, 0 },
    { 0x1A, 4, 0, 0 },
    { 0x5E, 0, 1, 0 },
    { 0x11, 0, 0, MAP_REF(doorEvent_800B3C18) },
    { 0x5A, 0, 1, MAP_REF(pos_800B3C0C) },
    { 0x67, 1, 0, 0 },
    { 0x60, 0, 0, MAP_REF(pos_800B3BFC) },
    { 0x13, 0, 0, MAP_REF(pos_800B3BFC) },
    { 0x48, 0, 0x6E, 1 },
    { 0x48, 1, 0x11, 1 },
    { 0x1B, 7, 0, 0 },
    { 0x1C, 7, 1, 0 },
    { 0x67, 2, 0x1E, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x4B, 0, 0, MAP_REF(effects_800B3C2C) },
    { 0x4D, 0, 0, MAP_REF(AddEffects_800B2994) },
    { 0xC, 0, 0x1E, 0 },
    { 0x2E, 0, 0, MAP_REF(doorEvent_800B3C18) },
    { 0x5C, 0, 0x78, 0 },
    { 0x5D, 0, 0, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x55, 0, 1, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x56, 0, 1, 0 },
    { 0x48, 0, 0x6F, 1 },
    { 0xD, 0, 1, 0 },
    { 0x49, 0, 0x700075, 1 },
    { 0x38, 1, 0, 0 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0x20012, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0x30012, 1 },
    { 0x49, 1, 0x40011, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0x50011, 1 },
    { 0x49, 1, 0x60012, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0x30012, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x1A, 4, 1, 0 },
    { 0x68, 1, 0xD, 0 },
    { 0x48, 2, 2, 1 },
    { 0xD, 0, 4, 0 },
    { 0x38, 2, 0, 1 },
    { 0x49, 0, 0x710076, 1 },
    { 0x49, 1, 0x70013, 1 },
    { 0x49, 2, 0x30008, 1 },
    { 0x68, 1, 0xE, 0 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 1, 0, 2 },
    { 0x49, 1, 0x80013, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x38, 2, 0, 3 },
    { 0x42, 0, 0, 0 },
    { 0x49, 2, 0x40008, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 2, 0x50008, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 2, 0x60008, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x48, 2, 7, 1 },
    { 0x48, 1, 9, 1 },
    { 0xD, 0, 2, 0 },
    { 0x38, 1, 0, 4 },
    { 0x42, 0, 0, 0 },
    { 0x49, 1, 0xA0014, 1 },
    { 0x42, 0, 1, 0 },
    { 0x49, 1, 0xB000C, 1 },
    { 0x42, 0, 2, 0 },
    { 0x49, 1, 0xD0016, 1 },
    { 0x42, 0, 3, 0 },
    { 0x49, 1, 0xE0017, 1 },
    { 0x42, 0, 4, 0 },
    { 0x49, 1, 0xF0018, 1 },
    { 0x3F, 0, 0, 0 },
    { 0x49, 0, 0x720074, 1 },
    { 0x48, 1, 0x10, 1 },
    { 0xD, 0, 3, 0 },
    { 0x48, 0, 0x73, 1 },
    { 0xD, 0, 1, 0 },
    { 0x67, 3, 0x1E, 0 },
    { 0xC, 0, 0x1E, 0 },
    { 0x45, 0, 1, 0 },
    { 0x1B, 1, 1, 0 },
    { 0x1C, 1, 0, 0 },
    { 8, 0, 7, 0 },
    { 4, 0, 0, 0 },
    { 0x58, 0, 0, 0 },
    { 3, 0, 0, 0 },
};
MapMinion minions_800B4250[2] = {
    { &model_800B3B20, 0, { 0, -0x759, 0x20D }, 0, 0, 1, 0, 2 },
    { &model_800B3B50, 0, { -0x177, -0x759, 0x145 }, 0, 0, 1, 0, 2 },
};
MapEvent events_800B4298[] = {
    { -1, MAP_EV_MINION, &minions_800B4250[0], 0x14, { MinionInit_800B2328 } },
    { -1, MAP_EV_MINION, &minions_800B4250[1], 0x14, { MinionInit_800B2328 } },
    { -1, MAP_EV_SCRIPT, script_800B3CB0, 0, { 0 } },
    { -1, MAP_EV_VOICES, voices_800B3B7C, 0, { 0 } },
    { 0, MAP_EV_END, 0, 0, { 0 } },
};
short bones_800B42FC[] = {
    0, 0, 0, 0x46, 1, 1, 1, 0, 2, 0x102, 2, 0xB,
    3, 0x203, 3, 0xB, 4, 0x304, 4, 0xB, 5, 0x405, 5, 0xB,
    5, 0x506, 6, 0xB, 6, 0x607, 7, 0xB, 3, 0x208, 8, 0xB,
    4, 0x809, 9, 0xB, 5, 0x90A, 0xA, 0xB, 5, 0xA0B, 0xB, 0xB,
    6, 0xB0C, 0xC, 0xB, 3, 0x20D, 0xD, 0, 4, 0xD0E, 0xE, 0xB,
    2, 0x10F, 0xF, 0xB, 3, 0xF10, 0x10, 0xB, 4, 0x1011, 0x11, 0xB,
    5, 0x1112, 0x12, 0xB, 3, 0xF13, 0x13, 0xB, 4, 0x1314, 0x14, 0xB,
    5, 0x1415, 0x15, 0xB, -0x1, -0x1, -0x1, -0x1,
};
int scale_800B43B4[3] = { 0x1000, 0x1000, 0x1000 };

const MapFxInits fxInits_800B22D8 = { { 0, FxModel_800B2B20, 0, FxMdec_800B3130, 0 } };

void MinionInit_800B2328(MapEnt* ent)
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
        desc.bones_34 = bones_800B42FC;
    }
    if (baseScale)
    {
        desc.baseScale_38 = baseScale;
    }
    else
    {
        desc.baseScale_38 = scale_800B43B4;
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
    w->f_C = MinionF_800B3874;
    w->actor_4 = actor;
    w->script_8 = script;
    w->f_10 = MinionF_800B387C;
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
    ent->update_90 = MinionIdle_800B3070;
}

void FadeSprites_800B2660(MapEnt* ent)
{
    SPRT sprt;
    DR_TPAGE tpage;
    MapFadeWork* w;
    EffectModel* model;
    int ended;
    int any;
    int i;
    int n;
    int t;
    int c;

    w = (MapFadeWork*)ent->work_14;
    ended = 0;
    any = 0;
    model = w->model_0;
    for (i = 0; i < 2; i++)
    {
        n = w->index_4 + i;
        if (n >= model->ftgCount_0)
        {
            break;
        }
        t = w->time_8[n & 1] - 160;
        if (t >= 0)
        {
            MakeFtgSprt_800221DC(model->ftg_4[n].ft4_30.items, &sprt, &tpage);
            c = sinTable_80084540[((t << 11) / 192) & 0xFFF] / 32;
            sprt.r0 = c;
            sprt.g0 = c;
            sprt.b0 = c;
            SetSemiTrans(&sprt, 1);
            SetDrTPageAbr_80033048((unsigned short*)&tpage, 1);
            sprt.x0 = 160 - sprt.w / 2;
            sprt.y0 = 120 - sprt.h / 2;
            *(SPRT*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = sprt;
            addPrim(pOT_8008D454, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(SPRT);
            *(DR_TPAGE*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = tpage;
            addPrim(pOT_8008D454, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(DR_TPAGE);
        }
        if (++w->time_8[(i + w->index_4) & 1] > 352)
        {
            ended = 1;
            w->time_8[(i + w->index_4) & 1] = 160;
        }
        any = 1;
    }
    if (ended)
    {
        w->index_4++;
    }
    if (!any)
    {
        ent->state_7C = -2;
    }
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
        entry->cb_8 = (EventEntryFn)EntityTask_800B36C8;
        return 1;
    }
    return 0;
}

int AddEffects_800B2994(MapFx* fx)
{
    MapEvent ev;

    while (fx->type_0 != MAP_FX_END)
    {
        ev.areas_0 = -1;
        ev.type_4 = 7;
        ev.data_8 = fx;
        ev.size_C = 0x20;
        ev.run_10.init = FxInit_800B3078;
        NewEntity(&ev);
        fx++;
    }
    return 1;
}

void FxModel_800B2B20(MapEnt* ent)
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
    frame = FxFrame_800B3884(fx, w, model->frameCount_14);
    FxTime_800B3908(ent, fx, w);
    FxPlace_800B39D4(fx, w);
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
                                          ((0x1000 - key->alpha_2) << 16) | (key->mode_24 | 0x80), key->f18);
        }
    }
}

void Door_800B2D48(MapEnt* ent)
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

void MapInit_800B3008(int phase)
{
    if (phase == 1)
    {
        StartMapTask_800B3254();
        ClearFieldMinions_800A7784();
        RequestModels_800B35F8(events_800B4298);
        levantAnimSet_80091C74 = 0;
        LoadLevantAnimSet_800AC708(0, 1);
        SetLoadFadeFlag_80027478(0x18, 1);
        SetEventHook_800A5F90((EventHookFn)AddEntity_800B3748);
    }
}

void MinionIdle_800B3070(MapEnt* ent)
{
}

void FxInit_800B3078(MapEnt* ent)
{
    MapFxInits inits = fxInits_800B22D8;
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

void FxMdec_800B3130(MapEnt* ent)
{
    MapFx* fx;
    MapFxWork* w;
    MdecImageSet* set;
    int frame;

    fx = ent->data_10;
    w = (MapFxWork*)ent->work_14;
    set = &w->file_0->imageSets_30[FindEffectIndex_80020F00(w->file_0, 2, fx->id_2)];
    frame = FxFrame_800B3884(fx, w, set->count_0);
    FxTime_800B3908(ent, fx, w);
    if (frame >= 0 && !(unknownFlags_8008D678 & 0x800))
    {
        mdecEffectVlcBuffer_8008D42C = w->file_0->mdec_34.dct_0;
        decodedImageData_8008B4A0 = w->file_0->mdec_34.work_4;
        DecodeMdec_80041920(set->images_4[frame], mdecEffectVlcBuffer_8008D42C, fx->arg_24);
        unknownFlags_8008D678 |= 0x800;
    }
}

void DoorInit_800B321C(MapEnt* ent)
{
    MapDoorWork* w;

    w = (MapDoorWork*)ent->work_14;
    w->state_0 = 0;
    w->t_4 = 0;
    Door_800B2D48(ent);
    ent->update_90 = Door_800B2D48;
}

void StartMapTask_800B3254(void)
{
    EventNode* task;

    task = mapEventTasks_800B1DA8[0];
    task->entry.cb_8 = (EventEntryFn)MapTaskLoad_800B3284;
    task->entry.flags = (task->entry.flags | 1) & ~0x8000;
}

void MapTaskLoad_800B3284(EventEntry* entry, int* st)
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
        MapTask_800B331C(entry, st);
        entry->cb_8 = (EventEntryFn)MapTask_800B331C;
        st[0] = 1;
        SetLoadFadeFlag_80027478(0x18, 0);
        eventDispatchHalt_8008B540 = 1;
    }
}

void MapTask_800B331C(EventEntry* entry, int* st)
{
    MapEvent* events;

    events = events_800B4298;
    if (st[0])
    {
        st[0] = 0;
    }
    if (currentArea_80091C44 == saveData_8008B570.mapId_2E4[3].cur_0 && currentArea_80091C44 != st[1])
    {
        st[2] -= LeaveArea_800B33D4(events, currentArea_80091C44);
        st[2] += EnterArea_800B34F0(events, saveData_8008B570.mapId_2E4[3].cur_0, st[1]);
        st[1] = saveData_8008B570.mapId_2E4[3].cur_0;
    }
}

int LeaveArea_800B33D4(MapEvent* ev, int area)
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

int EnterArea_800B34F0(MapEvent* ev, int area, int prev)
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
                AddEntity_800B3748(ev);
                n++;
            }
        }
    }
    return n;
}

void RequestModels_800B35F8(MapEvent* ev)
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

void EntityTask_800B36C8(EventEntry* entry, MapEnt* ent)
{
    StepEntity(entry, ent);
}

int AddEntity_800B3748(void* ev)
{
    return NewEntity(ev);
}

int MinionF_800B3874(void)
{
    return 1;
}

int MinionF_800B387C(void)
{
    return 1;
}

int FxFrame_800B3884(MapFx* fx, MapFxWork* w, int count)
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

void FxTime_800B3908(MapEnt* ent, MapFx* fx, MapFxWork* w)
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

void FxPlace_800B39D4(MapFx* fx, MapFxWork* w)
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

