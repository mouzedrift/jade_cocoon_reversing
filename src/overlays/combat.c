// COMBAT.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

#include "actor.h"
#include "engine.h"
#include "minion_init.h"
#include "combat.h"

// parameters of StartModelTask_80010850 (0x34 bytes), built from a minion by BuildMinionModelParams_800A05E0

// the part of cameraState_8008D4F0 that ResetCombatCamera_800A12B8 resets
typedef struct CombatCameraState
{
    char pad_0[0x14];
    int f14[3];
    int f20[3];
    short pad_2C;
    short f2E;
    char pad_30[4];
    SVECTOR rot_34;
    short f3C[3];
} CombatCameraState;

extern void GetActorHitFrame_80018E5C(void* p);
extern void SetActorStatusTint_80018EBC(void* p, UnitStatus* v);
extern void sub_800376A0(void* a, void* b);

extern int CountMinions_800A1A3C(Minion* p, int n);

typedef struct CombatTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombatTask;

extern void InitActors_8001D378(void);
extern void DestroyActor_8001D600(void* p);
extern void TriggerActorEffect_8001E28C(void* p);
extern void SetFadeMode_8001C19C(int a, int b);
extern void DestroySlotActor_800A0D1C(int i);
extern void FreeSlotModel_800A0B70(int i);
extern void CombatLoadStageOvl_800A14F0();
extern void CombatWaitStageOvl_800A1554();
extern void CombatEnterStage_800A15B4();
extern char* dword_8007DC78;
extern int StartModelTask_80010850(void* p);
extern CombatCameraState cameraState_8008D4F0;
extern int cameraZoom_8008B4F8;
extern int IsMinionSlotEmpty_800A1934(Minion* p);
extern void ResetCameraToLevant_800376A8(void);
extern void StartBattleCamera_80037748(void);
extern void InitCameraTask_800368F8(void);
extern void nullsub_5(void);
extern void ResetCombatCamera_800A12B8(void);
typedef struct CombatLocalCombat
{
    unsigned char b[4];
    int pad_4;
    int w[3];
} CombatLocalCombat;
extern void Cbt_8002FAA0(int a, void* b, unsigned char* c, int d);

extern void Cbt_8002C290(void* a, int b, int c);
extern void Cbt_8002B1B0(int a, void* b, int c);
extern void* memset(void* p, int c, unsigned int n);
extern void Cbt_80018A4C(void* a, char* b, int* c, int d, int e);
typedef struct CombatColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char cd;
} CombatColor;
extern void QueueFileRequest_8003BC84(FileRequestDesc* req);
extern void OnModelFileLoaded_80025D7C();
extern short defaultBones_80079140[]; // default bone table
extern int ratan2Degrees_8003B56C(int a, int b);
extern void InitPolyFT4_80029A10(void* a, void* b);
extern int ElementMixAngle_800A0968(unsigned char* a);
typedef struct CombatShortPair_combat
{
    unsigned short a;
    unsigned short b;
} CombatShortPair_combat;
typedef struct CombatReq2Combat
{
    int field_0;
    int field_4;
    char pad_8[4];
    unsigned short field_C;
    unsigned short field_E;
    unsigned short field_10;
    unsigned short field_12;
    char pad_14[8];
    unsigned short field_1C;
    unsigned short field_1E;
    unsigned short field_20;
    unsigned short field_22;
    char pad_24[4];
} CombatReq2Combat;
extern CombatShortPair_combat dword_8007DCAC[];
extern CombatShortPair_combat dword_8007DCBC[];
extern short dword_80084540[];
extern Minion dword_8008BEF8[];
extern void PlayMusic_800300E0(int a, int b);
extern void LoadUiTiy_8002BF74(void);
extern void ClearMinionSlot_800A197C(Minion* p);
extern void LoadModelTexToVram_800A0D64(int a, int b);
extern void CombatWaitUiTiy_800A14AC();
extern void CombatReq_8001E34C(void* p, void* q);

typedef struct CombatReqCombat
{
    int field_0;
    int field_4;
    void* field_8;
    short field_C;
    short field_E;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    short field_20;
    short field_22;
    short field_24;
    short field_26;
    short field_28;
    short field_2A;
    int field_2C;
    int field_30;
    char pad_34[0x2C];
} CombatReqCombat;
extern void BuildMinionModelParams_800A05E0(Minion* a, CombatModelParams* o, int c);
extern int GetElementHueAngle_800A0898(unsigned char* a);


int dword_800A05A0 SDATA = 14;

#if 0
// Not matched: register allocation differs in the first branch (o[4]+o[5] case); everything else was identical
void BuildMinionModelParams_800A05E0(Minion* a, CombatModelParams* o, int c)
{
    CombatLocalCombat l;
    unsigned int h = GetSpeciesModelDesc_80019C70(a->species_2)->modelId_0;
    int t;
    o->count_0 = GetTopSpecies_800338DC(a->species_4C, l.b, l.w);
    o->parts_4[0] = GetSpeciesModelDesc_80019C70(l.b[0])->modelId_0;
    o->parts_4[1] = GetSpeciesModelDesc_80019C70(l.b[1])->modelId_0;
    o->parts_4[2] = GetSpeciesModelDesc_80019C70(l.b[2])->modelId_0;
    o->weights_10[0] = l.w[0];
    o->weights_10[1] = l.w[1];
    o->weights_10[2] = l.w[2];
    if (o->parts_4[0] == o->parts_4[1])
    {
        if (o->parts_4[1] == o->parts_4[2])
        {
            o->weights_10[0] += o->weights_10[1];
            o->weights_10[1] = 0;
            o->weights_10[2] = 0;
            o->count_0 = 1;
        }
        else
        {
            t = o->weights_10[2];
            o->count_0 = 2;
            o->weights_10[0] = o->weights_10[0] + o->weights_10[1];
            o->weights_10[2] = 0;
            o->parts_4[1] = o->parts_4[2];
            o->weights_10[1] = t;
        }
    }
    else if (o->parts_4[0] == o->parts_4[2])
    {
        o->weights_10[0] = o->weights_10[0] + o->weights_10[2];
        o->weights_10[2] = 0;
        o->count_0 = 2;
    }
    else if (o->parts_4[1] == o->parts_4[2])
    {
        o->weights_10[1] = o->weights_10[1] + o->weights_10[2];
        o->weights_10[2] = 0;
        o->count_0 = 2;
    }
    o->f2C = 0;
    if (o->parts_4[0] != h)
    {
        if (o->parts_4[1] == h)
        {
            t = o->weights_10[1];
            o->parts_4[1] = o->parts_4[0];
            o->parts_4[0] = h;
            o->weights_10[1] = o->weights_10[0];
            o->weights_10[0] = t;
        }
        else if (o->parts_4[2] == h)
        {
            t = o->weights_10[2];
            o->parts_4[2] = o->parts_4[0];
            o->parts_4[0] = h;
            o->weights_10[2] = o->weights_10[0];
            o->weights_10[0] = t;
        }
        else if (o->count_0 < 2)
        {
            t = o->weights_10[0];
            o->parts_4[1] = o->parts_4[0];
            o->parts_4[0] = h;
            o->weights_10[0] = 0;
            o->count_0 = 2;
            o->weights_10[1] = t;
        }
        else
        {
            t = o->weights_10[0];
            o->parts_4[2] = o->parts_4[0];
            o->parts_4[0] = h;
            o->weights_10[0] = 0;
            o->count_0 = 3;
            o->weights_10[2] = t;
        }
    }
    o->modelId_1C = Cbt_80019A80(a->status_84.level_44);
    o->f20 = o->count_0 - 1;
    o->f28 = GetSpeciesModelDesc_80019C70(a->field_3)->modelId_0;
    o->f30 = c;
    o->angle_24 = GetElementHueAngle_800A0898(a->status_84.element_3E);
    if (o->angle_24 == -1000)
    {
        o->angle_24 = GetSpeciesModelDesc_80019C70(a->field_3)->field_2 << 1;
    }
    else
    {
        o->angle_24 = o->angle_24 - (GetSpeciesModelDesc_80019C70(a->field_3)->field_3 << 1);
        if (o->angle_24 < 0)
        {
            o->angle_24 = o->angle_24 + 0x168;
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(combat, BuildMinionModelParams_800A05E0);

// Matched
int GetElementHueAngle_800A0898(unsigned char* a)
{
    int n = 0;
    int r;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (a[i])
        {
            n++;
        }
    }
    if (n == 1)
    {
        r = -1000;
    }
    else if (n == 2)
    {
        if (a[3] && a[1])
        {
            r = a[1] < a[3] ? 0xF5 : 0x41;
        }
        else if (a[0] && a[2])
        {
            r = a[2] < a[0] ? 0x14F : 0x9B;
        }
        else
        {
            r = ElementMixAngle_800A0968(a);
        }
    }
    else
    {
        r = ElementMixAngle_800A0968(a);
    }
    return r;
}

// Matched
int ElementMixAngle_800A0968(unsigned char* a)
{
    short* t = dword_80084540;
    int p1, p0, p3, p2, p4, p5, p6, p7;
    p0 = t[0x5C6 / 2] * a[0];
    p1 = t[0x1DC6 / 2] * a[0];
    p2 = t[0x1DC6 / 2] * a[3];
    p3 = t[0x15C6 / 2] * a[3];
    p4 = t[0x15C6 / 2] * a[2];
    p5 = t[0xDC6 / 2] * a[2];
    p6 = t[0xDC6 / 2] * a[1];
    p7 = t[0x5C6 / 2] * a[1];
    return ratan2Degrees_8003B56C(p0 + p2 + p4 + p6, p1 + p3 + p5 + p7);
}

// Matched
void InitCombatSlots_800A0A28(void)
{
    int i;
    int m = -1;
    for (i = 1; i >= 0; i--)
    {
        combatSlots_800A3A08[i].task_0 = m;
    }
    InitActors_8001D378();
}

// Matched
void FreeCombatSlots_800A0A6C(void)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        if (combatSlots_800A3A08[i].task_0 >= 0)
        {
            DestroySlotActor_800A0D1C(i);
            FreeSlotModel_800A0B70(i);
        }
    }
}

// Matched
void StartSlotModel_800A0ACC(int i, Minion* x)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    BuildMinionModelParams_800A05E0(x, &s->params_8, (int)(dword_8007DC78 + (i << 6)));
    s->minion_4 = x;
    s->task_0 = StartModelTask_80010850(&s->params_8);
    s->actor_3C = 0;
}

// Matched
void RunSlotModelTask_800A0B3C(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    RunModelTask_80010A10(s->task_0);
}

// Matched
void FreeSlotModel_800A0B70(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    int v = s->task_0;
    s->task_0 = -1;
    FreeModelTask_8001098C(v);
}

// Matched
void CreateSlotActor_800A0BA8(int i, int* src, short* sh)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    ActorDesc r;
    Model* h = GetModelTaskModel_80010A44(s->task_0);
    int v = GetRankForLevel_80019A80(s->minion_4->status_84.level_44);
    unsigned short* x;
    unsigned short* y;
    r.modelId_0 = -1;
    r.kind_4 = 2;
    r.pos_8[0] = src[0];
    r.pos_8[1] = src[1];
    r.pos_8[2] = src[2];
    r.rot_14[0] = sh[0];
    r.rot_14[1] = sh[1];
    r.rot_14[2] = sh[2];
    r.clutRow_1C = i;
    r.animIdx_20 = 4;
    r.frame_24 = -1;
    r.frameSpeed_28 = 0x1000;
    r.blendDiv_2C = 4;
    r.visible_30 = 0;
    r.model_48 = h;
    r.bones_34 = defaultBones_80079140;
    r.baseScale_38 = GetModelBaseScale_80024E90(h, v);
    r.boneScale_3C = GetModelBoneScale_80024EC8(h, v);
    r.anims_40 = GetModelActorAnims_80024E38(h);
    r.effectTbl_44 = GetModelEffectTable_80024E64(h);
    r.hasMatrices_4C = 1;
    s->actor_3C = CreateActor_8001D45C(&r);
    x = sub_80024F00(h, v);
    y = sub_80024F38(h, v);
    SetBoneGroupFlags_80019B14(s->actor_3C->bones_134, x, y);
    SetActorGroundMove_8001D68C(s->actor_3C, 0);
}

// Matched
void DestroySlotActor_800A0D1C(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    if (s->actor_3C)
    {
        DestroyActor_8001D600(s->actor_3C);
        s->actor_3C = 0;
    }
}

// Matched
void LoadModelTexToVram_800A0D64(int i, int id)
{
    ModelDesc* q = GetModelDesc_800251E4(id);
    ModelLoadParams o;
    FileRequestDesc m;
    InitModelLoadParams_80025ED0(&o);
    o.flags_0 = 2;
    o.model_14 = 0;
    o.desc_4 = q;
    o.sel_8 = 0;
    o.vram_18 = &modelLoaderVram_8007DC70[i];
    m.flags_0 = 0x69;
    m.fileId_4 = q->fileId_0;
    m.offset_8 = q->tex_6.offset << 11;
    m.size_C = q->tex_6.size << 11;
    m.dest_10 = 0;
    m.params_14 = &o;
    m.paramsSize_18 = 0x3C;
    m.callback_1C = OnModelFileLoaded_80025D7C;
    QueueFileRequest_8003BC84(&m);
}

// Matched
void MoveSlotActorTo_800A0E1C(int i, int* src)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    CombatReqCombat r;
    r.field_0 = 0;
    r.field_4 = 0;
    r.field_8 = 0;
    r.field_C = 0;
    r.field_E = -1;
    r.field_10 = -1;
    r.field_18 = 0;
    r.field_1C = 1;
    r.field_20 = 0;
    r.field_22 = 0;
    r.field_24 = -1;
    r.field_26 = -1;
    r.field_28 = -1;
    r.field_2A = -1;
    r.field_2C = 0;
    r.field_30 = 0;
    s->actor_3C->target_70.vx = src[0];
    s->actor_3C->target_70.vy = src[1];
    s->actor_3C->target_70.vz = src[2];
    r.field_8 = (int*)&s->actor_3C->target_70;
    r.field_C = 0x100;
    r.field_26 = 2;
    CombatReq_8001E34C(s->actor_3C, &r);
}

// Matched
void sub_800A0EE8(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    sub_8001E1C8(s->actor_3C);
}

// Matched
void sub_800A0F1C(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    sub_8001E1DC(s->actor_3C);
}

// Matched
CombatColor sub_800A0F50(int i, int* p, int x)
{
    CombatColor c;
    CombatSlot* s;
    memset(&c, 0, 4);
    s = &combatSlots_800A3A08[i];
    if (*p == 0x14)
    {
        return c;
    }
    Cbt_80018A4C(&c, s->actor_3C, p, 0, x);
    return c;
}

// Matched
void TriggerSlotEffect_800A0FF0(int i, int* p)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    if (*p != 0x14)
    {
        TriggerActorEffect_8001E28C(s->actor_3C);
    }
}

// Matched
void GetSlotHitFrame_800A1034(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    GetActorHitFrame_80018E5C(s->actor_3C);
}

// Matched
void SetSlotStatusTint_800A1068(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    SetActorStatusTint_80018EBC(s->actor_3C, GetSlotStatus_800A10C0(i));
}

// Matched
int GetSlotAncestors_800A10A4(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return (int)s->minion_4->ancestors_4;
}

// Matched
UnitStatus* GetSlotStatus_800A10C0(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return &s->minion_4->status_84;
}

// Matched
int* GetSlotPos_800A10DC(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return s->actor_3C->pos_38;
}

// Matched
int* GetSlotBonePos_800A10F8(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return s->actor_3C->bonePos_1C4;
}

// Matched
void GetSlotEffectTarget_800A111C(int i, EffectTarget* out)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    out->tbl_0 = s->actor_3C->effectTbl_14C;
    out->pos_4 = s->actor_3C->pos_38;
    out->bonePos_8 = s->actor_3C->bonePos_1C4;
    out->boneMatrices_C = s->actor_3C->boneMatrices_1C8;
    out->boneScale_2C = s->actor_3C->boneScale_144;
    out->scale_30 = s->actor_3C->scale_2C;
}

// Matched
int GetSlotSkills_800A11A0(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return (int)&s->minion_4->skills_DE;
}

// Matched
int GetSlotMagicBits_800A11BC(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return (int)&s->minion_4->magicBits_F4;
}

// Matched
Minion* GetSlotMinion_800A11D8(int i)
{
    CombatSlot* s = &combatSlots_800A3A08[i];
    return s->minion_4;
}


// Matched
void StartCombatCamera_800A11F4(void)
{
    EventEntry* e = AllocEventEntry_80043AF8(cameraTask_8008D4A0);
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        ResetCameraToLevant_800376A8();
        StartBattleCamera_80037748();
        e->cb_8 = (EventEntryFn)InitCameraTask_800368F8;
        e->cb_C = (EventEntryFn)nullsub_5;
        e->flags = (e->flags | 4) & ~0x8000;
        ResetCombatCamera_800A12B8();
    }
}

// Matched
void StopCombatCamera_800A127C(void)
{
    EventNode* p = cameraTask_8008D4A0;
    sub_800376A0(&p->entry, p->entry.buffer);
    StopAllEventEntries_80043B40(cameraTask_8008D4A0);
}

// Matched
void ResetCombatCamera_800A12B8(void)
{
    CombatCameraState* p = &cameraState_8008D4F0;
    SaveData* q;
    p->f2E = 0;
    p->f20[0] = 0;
    p->f20[1] = 0;
    p->f20[2] = 0;
    p->f14[0] = 0;
    p->f14[1] = 0;
    p->f14[2] = 0;
    p->rot_34.vx = 0;
    p->rot_34.vy = 0;
    p->rot_34.vz = 0;
    p->f3C[0] = 0;
    p->f3C[1] = 0;
    p->f3C[2] = 0;
    cameraZoom_8008B4F8 = 0x1000;
    q = &saveData_8008B570;
    q->levant_7A8.pos.x = 0;
    q->levant_7A8.pos.y = 0;
    q->levant_7A8.pos.z = 0;
    q->levant_7A8.rot.vx = 0;
    q->levant_7A8.rot.vy = 0;
    q->levant_7A8.rot.vz = 0;
}

// Matched
// COMBAT overlay entry (the battle arena): runs combatTaskList_800A398C, back to the title menu after
int CombatMain_800A1324(void)
{
    unknownFlags_8008D678 |= 0x2000000;
    unknownFlags_8008D678 |= 0x4000000;
    DrawIntroMovie_8001AF64(combatTaskList_800A398C);
    unknownFlags_8008D678 &= ~0x2000000;
    unknownFlags_8008D678 &= ~0x4000000;
    return 6;
}

// Matched
void CombatInit_800A13A0(CombatTask* t)
{
    int i;
    int j;
    combatCursor_800A1BBC[0] = 1;
    combatCursor_800A1BBC[1] = 5;
    combatCursor_800A1BBC[2] = 5;
    combatCursor_800A1BBC[3] = 2;
    combatCursor_800A1BBC[4] = 0;
    combatCursor_800A1BBC[5] = 0;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            ClearMinionSlot_800A197C(&teams_800A3AA0[i][j]);
        }
    }
    PlayMusic_800300E0(0x8E, 1);
    LoadUiTiy_8002BF74();
    LoadModelTexToVram_800A0D64(2, 0x42);
    LoadModelTexToVram_800A0D64(3, 0x41);
    t->next_8 = CombatWaitUiTiy_800A14AC;
}

// Matched
void CombatFree_800A148C(void)
{
    FreeActiveOverlay_8002C014();
}

// Matched
void CombatWaitUiTiy_800A14AC(CombatTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        stage_800A3A8C = 0;
        prevStage_800A4070 = 0;
        t->next_8 = CombatLoadStageOvl_800A14F0;
        t->next_8(t);
    }
}

// Matched
void CombatLoadStageOvl_800A14F0(CombatTask* t)
{
    SetFadeMode_8001C19C(0, 0x20);
    stageOvlRequest_800A4080 = LoadOverlay_80020BF8(1, stageOverlays_800A39F0[stage_800A3A8C]);
    t->next_8 = CombatWaitStageOvl_800A1554;
}

// Matched
void CombatWaitStageOvl_800A1554(CombatTask* t, int x)
{
    if (GetFileRequestStatus_8003BE30(stageOvlRequest_800A4080) == 0)
    {
        SetFadeMode_8001C19C(3, 0x20);
        t->next_8 = CombatEnterStage_800A15B4;
        t->next_8(t, x);
    }
}

extern void sub_800A4394();
extern void sub_800A4360();
extern void sub_800A40FC();
extern void sub_800A4170();
extern void sub_800A4B8C();
extern void sub_800A40E0();
extern int CountRosterMinions_800A1AEC(int i);

void CombatEnterStage_800A15B4(CombatTask* t, int x)
{
    unsigned int v;
    switch (stage_800A3A8C)
    {
    case 0:
        t->next_8 = sub_800A4394;
        break;
    case 1:
        v = prevStage_800A4070;
        switch (v)
        {
        case 0:
        case 3:
            byte_800A38DB = 0;
            curPlayer_800A38D9 = 0;
            combatMenuChoice_800A1BC4 = 0;
            break;
        case 2:
            if (CountRosterMinions_800A1AEC(curPlayer_800A38D9))
            {
                byte_800A38DB = v;
                combatMenuChoice_800A1BC4 = 1;
            }
            else
            {
                byte_800A38DB = 0;
            }
            break;
        }
        t->next_8 = sub_800A4360;
        break;
    case 2:
        t->next_8 = sub_800A40FC;
        break;
    case 3:
        t->next_8 = sub_800A4170;
        break;
    case 4:
        t->next_8 = sub_800A4B8C;
        break;
    case 5:
        t->next_8 = sub_800A40E0;
        break;
    case 6:
        break;
    }
    t->next_8(t, x);
}
INCLUDE_OVERLAY_ASM(combat, dword_800A05C0);


// called by the stage overlays when they are done: picks the next stage and loads its overlay
void CombatNextStage_800A16FC(CombatTask* t)
{
    int v = stage_800A3A8C;
    short s;
    prevStage_800A4070 = v;
    switch (v)
    {
    case 0:
        stage_800A3A8C = 1;
        break;
    case 1:
        s = combatMenuChoice_800A1BC4;
        switch (s)
        {
        case 0:
            stage_800A3A8C = 2;
            break;
        case 3:
            stage_800A3A8C = s;
            break;
        case 4:
            bStopDrawingMovie_8008D45C = 1;
            return;
        }
        break;
    case 2:
        stage_800A3A8C = 1;
        break;
    case 3:
        if (dword_800A3A88 & 1)
        {
            stage_800A3A8C = 4;
        }
        else
        {
            stage_800A3A8C = 1;
        }
        break;
    case 4:
        switch (battleResult_800A38DC)
        {
        case 0:
        case 1:
            stage_800A3A8C = 5;
            break;
        case 2:
            stage_800A3A8C = 3;
            break;
        }
        break;
    case 5:
        stage_800A3A8C = 3;
        break;
    case 6:
        break;
    }
    t->next_8 = CombatLoadStageOvl_800A14F0;
    t->next_8(t);
}

// Matched
void DrawMinionNameLevel_800A1844(Minion* a, unsigned short* pt, unsigned int flags)
{
    UnitStatus* q;
    unsigned short v[2];
    if (IsMinionSlotEmpty_800A1934(a) != 1)
    {
        if (flags & 2)
        {
            SetFontClutOffset_8003F900(1, 1);
        }
        else
        {
            SetFontClutOffset_8003F900(1, 0);
        }
        q = &a->status_84;
        v[0] = pt[0] + 5;
        v[1] = pt[1] + 6;
        Cbt_8002FAA0(0, v, a->status_84.name_10, 0);
        v[0] = pt[0] + 0x50;
        v[1] = pt[1] + 6;
        Cbt_8002C290(v, q->level_44, 0);
        v[0] = pt[0] + 0x54;
        v[1] = pt[1] + 3;
        Cbt_8002B1B0(q->elementMask_42, v, 0);
    }
}

// Matched
int IsMinionSlotEmpty_800A1934(Minion* p)
{
    if (p == 0)
    {
        return 1;
    }
    return p->id == 4;
}

// Matched
void sub_800A1958(Minion* p)
{
    HasStatusFlag_80033548(&p->status_84, 0x400);
}

// Matched
void ClearMinionSlot_800A197C(Minion* p)
{
    p->id = 4;
}

// Matched
void CopySaveMinionsToRoster_800A1988(void)
{
    int i;
    rosterFill_800A38DA = 0;
    for (i = 0; i < 15; i++)
    {
        MemCopy_800403E8(&rosters_800A1BC8[curPlayer_800A38D9][rosterFill_800A38DA], &dword_8008BEF8[i], 0xF8);
        rosterFill_800A38DA++;
    }
}

// Matched
int CountMinions_800A1A3C(Minion* p, int n)
{
    int i;
    int count = 0;
    for (i = 0; i < n; i++)
    {
        if (!IsMinionSlotEmpty_800A1934(&p[i]))
        {
            count++;
        }
    }
    return count;
}

// Matched
void CountTeamMinions_800A1AAC(int i)
{
    CountMinions_800A1A3C(teams_800A3AA0[i], 3);
}

// Matched
int CountRosterMinions_800A1AEC(int i)
{
    return CountMinions_800A1A3C(rosters_800A1BC8[i], 0xF);
}

// Matched
void sub_800A1B2C(int i, void* p)
{
    CombatReq2Combat r;
    r.field_0 = 1;
    r.field_4 = 1;
    r.field_1C = dword_8007DCAC[i].a;
    r.field_1E = dword_8007DCAC[i].b;
    r.field_20 = 0x20;
    r.field_22 = 0x40;
    r.field_C = dword_8007DCBC[i].a;
    r.field_E = dword_8007DCBC[i].b;
    r.field_10 = 0x100;
    r.field_12 = 1;
    InitPolyFT4_80029A10(p, &r);
}

short combatCursor_800A1BBC[4] = { 1, 5, 5 };
short combatMenuChoice_800A1BC4 = 0;
Minion rosters_800A1BC8[2][15] = {
    {
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
    },
    {
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
        { 4 },
    },
};
unsigned char byte_800A38D8 = 0;
unsigned char curPlayer_800A38D9 = 0;
unsigned char rosterFill_800A38DA = 0;
unsigned char byte_800A38DB = 0;
unsigned char battleResult_800A38DC = 0;
int dword_800A38E0 = 0xDF0033;
int combatTaskDesc_800A38E4[6] = { 1, 5, 0, 0, (int)CombatInit_800A13A0, (int)CombatFree_800A148C };
int combatModelLoaderDesc_800A38FC[6] = { 1, 0x8000, 92, (int)&modelLoaderTask_8008B54C, (int)ModelLoaderTask_800209AC };
int combatActorTaskDesc_800A3914[6] = { 2, 0x8000, 0x1CC, (int)&actorTasks_8008D43C };
int dword_800A392C[6] = { 2, 0x8000, 24, (int)&dword_8008B564 };
int dword_800A3944[6] = { 1, 0x8000, 0, (int)&dword_8008D458 };
int combatCameraTaskDesc_800A395C[6] = { 1, 0x8000, 0x21C, (int)&cameraTask_8008D4A0 };
int combatFadeTaskDesc_800A3974[6] = { 1, 0x8000, 8, (int)&fadeTask_8008D628 };
void *combatTaskList_800A398C[25] = {
    (void *)&eventDescs_80078EB8, (void *)((char *)&eventDescs_80078EB8 + 24), (void *)((char *)&eventDescs_80078EB8 + 120), (void *)((char *)&eventDescs_80078EB8 + 72),
    (void *)combatCameraTaskDesc_800A395C, (void *)((char *)&eventDescs_80078EB8 + 384), (void *)combatFadeTaskDesc_800A3974, (void *)((char *)&eventDescs_80078EB8 + 504),
    (void *)((char *)&eventDescs_80078EB8 + 528), (void *)((char *)&eventDescs_80078EB8 + 552), (void *)((char *)&eventDescs_80078EB8 + 576), (void *)((char *)&eventDescs_80078EB8 + 432),
    (void *)((char *)&eventDescs_80078EB8 + 624), (void *)combatModelLoaderDesc_800A38FC, (void *)((char *)&eventDescs_80078EB8 + 456), (void *)combatTaskDesc_800A38E4,
    (void *)combatActorTaskDesc_800A3914, (void *)((char *)&eventDescs_80078EB8 + 240), (void *)((char *)&eventDescs_80078EB8 + 216), (void *)((char *)&eventDescs_80078EB8 + 600),
    (void *)dword_800A392C, (void *)dword_800A3944, (void *)((char *)&eventDescs_80078EB8 + 192), (void *)((char *)&eventDescs_80078EB8 + 312),
};
int stageOverlays_800A39F0[6] = { 22, 23, 24, 26, 27, 28 };
CombatSlot combatSlots_800A3A08[2] = { { 0 } };
int dword_800A3A88 = 0;
int stage_800A3A8C = 0;
int dword_800A3A90[4] = { 0 };
Minion teams_800A3AA0[2][3] = { { { 0 } } };
int prevStage_800A4070 = 0;
int dword_800A4074[3] = { 0 };
int stageOvlRequest_800A4080 = 0;
