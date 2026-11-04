// BATTLE.BIN, source file 2 of 3 from 0x800BC90C (.rdata from 0x800B6700)
#include "battle.h"

const int dword_800B6700[4] = { 0x1000, 0x1000, 0x1000 };
INCLUDE_OVERLAY_ASM(battle, dword_800B6710);

#if 0 // Not matched: ~900 of 1095 instructions identical; control flow, stack frame and most blocks match; left are
      // register allocation / loop-invariant hoisting differences (light, saveData and 1/240 constant bases) in every block.
      // Its .rdata (initializer at 0x800B6700, switch table at 0x800B6710) comes out right since this file was split off.
typedef struct BatLight_a
{
    char pad0[0x30];
    unsigned char r_30;
    unsigned char g_31;
    unsigned char b_32;
    char pad33[0x1D];
    short r_50;
    short g_52;
    short b_54;
} BatLight_a;

extern char stageRot_800C9124[];
extern char cameraState_8008D4F0[];
extern short cameraRot_8008D4C8;
extern short geomScreenBase_8008D51E;
extern unsigned char stageAnimPhases_800C911C[];
extern void DrawBillboardRgb_80043DE0(void* a0, void* a1, void* a2, void* a3);
typedef struct BatStageObj_a
{
    char pad0[0x38];
    int x_38;
    int y_3C;
    int z_40;
} BatStageObj_a;

void DrawBattleStage_800BC90C(BatStageObj_a* p)
{
    int scale[3] = { 0x1000, 0x1000, 0x1000 };
    int idx;
    int i;

    unknownFlags_8008D678 &= ~0x10000;
    idx = FindEffectIndex_80020F00(&battleEffectFile_80095468, 1, battleStages_800C8EAC[battleStageId_80083BD0].model_6);
    DrawFtgObjectAtSlot0_8004D1EC(battleEffectFile_80095468.models_28[idx].ftg_4, pOT_8008B4C8, &p->x_38, stageRot_800C9124, pointLights_8008D534, 1, scale);
    {
        unsigned short* list = battleStages_800C8EAC[battleStageId_80083BD0].list_0;
        SaveData* sd = &saveData_8008B570;
        for (; *list != 0xFFFF; list++)
        {
            EffectSprite* g = &battleEffectFile_80095468.sprites_20[FindEffectIndex_80020F00(&battleEffectFile_80095468, 0, *list)];
            int j;
            for (j = 0; j < g->count_0; j++)
            {
                int k;
                for (k = 0; k < g->frameCounts_4[j]; k++)
                {
                    VECTOR pos;
                    CVECTOR col;
                    short sz[2];
                    EffectSpriteFrame* e = &g->frames_8[j][k];
                    BatLight_a* l = (BatLight_a*)cameraState_8008D4F0;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    pos.vx += e->pos_10[0];
                    pos.vz += e->pos_10[2];
                    pos.vy = sd->levant_7A8.pos.y + e->pos_10[1];
                    if (e->size_C[1] != 0)
                    {
                        col.r = l->r_30 + e->rgb_18[0] * l->r_50 / 4096;
                        col.g = l->g_31 + e->rgb_18[1] * l->g_52 / 4096;
                        col.b = l->b_32 + e->rgb_18[2] * l->b_54 / 4096;
                        if (battleStageId_80083BD0 == 0x10)
                        {
                            SetSemiTrans(&g->poly_C, 1);
                        }
                        if (battleStageId_80083BD0 == 0x13)
                        {
                            sz[0] = e->size_C[0] * 5;
                            sz[1] = e->size_C[1] * 5;
                            DrawRotSprite_80044010(&g->poly_C, &pos, stageRot_800C9124, &e->u_0, &e->w_4, &e->f8, sz, &e->pos_10[0], &col, 0, 0, pOT_8008B4C8);
                        }
                        else
                        {
                            DrawBillboardRgb_80043DE0(&g->poly_C, &pos, e->size_C, &col);
                        }
                    }
                }
            }
        }
    }
    if (battleStages_800C8EAC[battleStageId_80083BD0].floor_8 >= 0)
    {
        for (i = 0; i < 32; i++)
        {
            DVECTOR sxy;
            VECTOR v;
            POLY_FT4 poly;
            SVECTOR sv;
            long pp;
            long flag;
            int a;
            int x;
            int w;
            short* cam = &cameraRot_8008D4C8;
            v.vx = p->x_38;
            v.vy = p->y_3C;
            v.vz = p->z_40;
            a = -cam[1];
            v.vx += sinTable_80084540[a & 0xFFF];
            v.vy = levantPos_8008BD18.pos.y - 0x352;
            v.vx -= cameraEye_8008D600.vx;
            v.vy -= cameraEye_8008D600.vy;
            v.vz += sinTable_80084540[(a + 0x400) & 0xFFF];
            v.vz -= cameraEye_8008D600.vz;
            sv.vx = v.vx;
            sv.vy = v.vy;
            sv.vz = v.vz;
            RotTransPers(&sv, (long*)&sxy, &pp, &flag);
            poly = battleEffectFile_80095468.sprites_20[battleStages_800C8EAC[battleStageId_80083BD0].floor_8 + i % 4].poly_C;
            x = ((cam[1] & 0xFFF) / 4 + i * 96 - 0x400) * geomScreenBase_8008D51E / 240;
            if ((unsigned int)(x + 0x60) < 0x1A0)
            {
                w = geomScreenBase_8008D51E * 96 / 240;
                poly.r0 = poly.r0 * sceneBrightness_8008D40C >> 12;
                poly.g0 = poly.g0 * sceneBrightness_8008D40C >> 12;
                poly.b0 = poly.b0 * sceneBrightness_8008D40C >> 12;
                setShadeTex(&poly, 0);
                setXYWH(&poly, x, sxy.vy - w, w + 1, w + 1);
                *(POLY_FT4*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = poly;
                addPrim(&pOT_8008B4C8[0x3FF], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(POLY_FT4);
            }
        }
    }
    if (battleStages_800C8EAC[battleStageId_80083BD0].anim_A >= 0)
    {
        int cols = 0;
        unsigned int n = 0;
        if (battleStageId_80083BD0 == 0xF)
        {
            cols = 3;
            n = 9;
        }
        else if (battleStageId_80083BD0 == 0x13)
        {
            cols = 4;
            n = 0xE;
        }
        else if (battleStageId_80083BD0 == 0x15 || battleStageId_80083BD0 == 0x1D || battleStageId_80083BD0 == 6 || battleStageId_80083BD0 == 0x1C || battleStageId_80083BD0 == 5)
        {
            cols = 1;
            n = 0xC;
        }
        switch (battleStageId_80083BD0)
        {
        case 5:
        case 6:
        case 0xF:
        case 0x13:
        case 0x15:
        case 0x1C:
        case 0x1D:
        {
            EffectSprite* g = &battleEffectFile_80095468.sprites_20[FindEffectIndex_80020F00(&battleEffectFile_80095468, 0, battleStages_800C8EAC[battleStageId_80083BD0].anim_A)];
            int j;
            for (j = 0; j < g->count_0; j++)
            {
                int half = n >> 1;
                int t = (stageAnimPhases_800C911C[j % 8] + (unsigned int)frameCount_8008D3FC) % n;
                int k;
                if (battleStageId_80083BD0 == 0x13 && half < t)
                {
                    t = n - t;
                }
                if (battleStageId_80083BD0 == 0x15 || battleStageId_80083BD0 == 0x1D || battleStageId_80083BD0 == 6 || battleStageId_80083BD0 == 0x1C || battleStageId_80083BD0 == 5)
                {
                    if (half < t)
                    {
                        t = n - t;
                    }
                    t = t / 2;
                }
                for (k = 0; k < g->frameCounts_4[j]; k++)
                {
                    VECTOR pos;
                    CVECTOR col;
                    EffectSpriteFrame* e = &g->frames_8[j][k];
                    int du;
                    int dv;
                    int uu;
                    int vv;
                    SaveData* sd;
                    BatLight_a* l;
                    if (stageAnimUv_800C9D8C[1] < 0 && stageAnimUv_800C9D8C[0] < 0)
                    {
                        stageAnimUv_800C9D8C[0] = g->poly_C.u0;
                        stageAnimUv_800C9D8C[1] = g->poly_C.v0;
                    }
                    du = t % cols;
                    dv = t / cols;
                    sd = &saveData_8008B570;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    pos.vx += e->pos_10[0];
                    pos.vz += e->pos_10[2];
                    pos.vy = sd->levant_7A8.pos.y + e->pos_10[1];
                    du = du * (e->w_4 + 1);
                    dv = dv * (e->h_6 + 1);
                    uu = e->u_0 + du;
                    vv = e->v_2 + dv;
                    if (cols == 1)
                    {
                        uu = e->u_0;
                    }
                    g->poly_C.u0 = stageAnimUv_800C9D8C[0] + uu;
                    g->poly_C.v0 = stageAnimUv_800C9D8C[1] + vv;
                    g->poly_C.u1 = stageAnimUv_800C9D8C[0] + uu + e->w_4;
                    g->poly_C.v1 = stageAnimUv_800C9D8C[1] + vv;
                    g->poly_C.u2 = stageAnimUv_800C9D8C[0] + uu;
                    g->poly_C.v2 = stageAnimUv_800C9D8C[1] + vv + e->h_6;
                    g->poly_C.u3 = stageAnimUv_800C9D8C[0] + uu + e->w_4;
                    g->poly_C.v3 = stageAnimUv_800C9D8C[1] + vv + e->h_6;
                    if (e->size_C[1] != 0)
                    {
                        l = (BatLight_a*)cameraState_8008D4F0;
                        col.r = l->r_30 + e->rgb_18[0] * l->r_50 / 4096;
                        col.g = l->g_31 + e->rgb_18[1] * l->g_52 / 4096;
                        col.b = l->b_32 + e->rgb_18[2] * l->b_54 / 4096;
                        SetSemiTrans(&g->poly_C, 1);
                        DrawBillboardRgb_80043DE0(&g->poly_C, &pos, e->size_C, &col);
                    }
                }
            }
            break;
        }
        default:
        {
            EffectSprite* g = &battleEffectFile_80095468.sprites_20[FindEffectIndex_80020F00(&battleEffectFile_80095468, 0, battleStages_800C8EAC[battleStageId_80083BD0].anim_A)];
            int j = ((unsigned int)frameCount_8008D3FC % (g->count_0 * 2)) / 2;
            int k;
            for (k = 0; k < g->frameCounts_4[j]; k++)
            {
                int m;
                for (m = 0; m < 8; m++)
                {
                    VECTOR pos;
                    CVECTOR col;
                    int d;
                    int ang;
                    EffectSpriteFrame* e = &g->frames_8[j][k];
                    SaveData* sd = &saveData_8008B570;
                    BatLight_a* l = (BatLight_a*)cameraState_8008D4F0;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    d = ISqrt_8003B918(e->pos_10[0] * e->pos_10[0] + e->pos_10[2] * e->pos_10[2]);
                    ang = ratan2_8003B548(e->pos_10[0], e->pos_10[2]) + m * 512;
                    pos.vx += sinTable_80084540[(ang + 0x400) & 0xFFF] * d / 4096;
                    pos.vz += sinTable_80084540[ang & 0xFFF] * d / 4096;
                    pos.vy = sd->levant_7A8.pos.y + e->pos_10[1];
                    g->poly_C.u0 = e->u_0;
                    g->poly_C.v0 = e->v_2;
                    g->poly_C.u1 = e->u_0 + e->w_4;
                    g->poly_C.v1 = e->v_2;
                    g->poly_C.u2 = e->u_0;
                    g->poly_C.v2 = e->v_2 + e->h_6;
                    g->poly_C.u3 = e->u_0 + e->w_4;
                    g->poly_C.v3 = e->v_2 + e->h_6;
                    if (e->size_C[1] != 0)
                    {
                        col.r = l->r_30 + e->rgb_18[0] * l->r_50 / 4096;
                        col.g = l->g_31 + e->rgb_18[1] * l->g_52 / 4096;
                        col.b = l->b_32 + e->rgb_18[2] * l->b_54 / 4096;
                        DrawBillboardRgb_80043DE0(&g->poly_C, &pos, e->size_C, &col);
                    }
                }
            }
            break;
        }
        }
    }
    if (battleStages_800C8EAC[battleStageId_80083BD0].models_C != 0)
    {
        for (i = 0; i < 3; i++)
        {
            unsigned short* ent = &battleStages_800C8EAC[battleStageId_80083BD0].models_C[i * 4];
            int id = ent[0];
            int fl = ent[1];
            unsigned long* ot = pOT_8008B4C8;
            if (id != 0xFF)
            {
                int sc[3] = { 0x1000, 0x1000, 0x1000 };
                VECTOR pos;
                SVECTOR rot;
                EffectModel* mdl = &battleEffectFile_80095468.models_28[FindEffectIndex_80020F00(&battleEffectFile_80095468, 1, id)];
                int k;
                memset(&rot, 0, 8);
                if (battleStageId_80083BD0 == 0x10)
                {
                    rot.vy = frameCount_8008D3FC * 100;
                }
                pos.vx = p->x_38;
                pos.vy = p->y_3C;
                pos.vz = p->z_40;
                pos.vy = levantPos_8008BD18.pos.y;
                if (battleStageId_80083BD0 == 0x13 && i == 0)
                {
                    sc[0] *= 3;
                    sc[1] *= 3;
                    sc[2] *= 3;
                }
                if (battleStageId_80083BD0 == 0x14)
                {
                    pos.vy -= 0x2F8;
                }
                for (k = 0; k < mdl->ftgCount_0; k++)
                {
                    DrawFtgObjectAtSlot0_8004D1EC(&mdl->ftg_4[k], ot, &pos, &rot, 0, fl, sc);
                }
            }
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, DrawBattleStage_800BC90C);

void ActionStart_800BDA28(BatTask_a* t)
{
    int i;
    int f;
    int m;
    if (!(battleFlags_800B1228 & 0x1000))
    {
        ResetUnitReactions_800BB794();
        ResetTurnResults_800BB7D4();
        ApplyBattleCommand_800BEBB8();
        if (!(saveData_8008B570.field_0 & 2))
        {
            f = 0;
            for (i = 4; i < 7; i++)
            {
                m = GetEnemyAliveMask_800A248C() & (1 << i);
                if (m != 0)
                {
                    if (IsUncapturableSpecies_800BF980(GetEnemySpecies_800A2BE4(i - 4)))
                    {
                        f = 1;
                        break;
                    }
                }
            }
            if (f)
            {
                MoveBattleCameraForAction_80037828(GetUnitSide_800BC7DC(actingUnit_800C9C7C), (short)curCommand_800C9C88.kind_0, 1);
            }
            else
            {
                MoveBattleCameraForAction_80037828(GetUnitSide_800BC7DC(actingUnit_800C9C7C), (short)curCommand_800C9C88.kind_0, 0);
            }
        }
    }
    t->next_8 = ActionWaitIdle_800BDB4C;
}

void ActionWaitIdle_800BDB4C(BatTask_a* t)
{
    if (AreUnitsIdle_800BDD3C() == 1)
    {
        UpdateWindowsHidden_800BF2E8();
        FaceActorAndTargets_800BDEBC();
        StartActorAction_800BDF74();
        StartReactions_800BDFAC();
        AlignActionTimings_800BE2C8();
        t->next_8 = ActionWaitReady_800BDBB0;
    }
}

void ActionWaitReady_800BDBB0(BatTask_a* t)
{
    if (AreUnitsReady_800BDE04() == 1)
    {
        if (curCommand_800C9C88.kind_0 == 2 && actingUnit_800C9C7C == 0)
        {
            LoadSummonedMinion_800C0AEC(commandUnit_800C9C98 - 1, &levantPos_8008BD18.pos.x, levantPos_8008BD18.rot.vy);
        }
        removedEnemyCount_800C9D90 = 0;
        actionFrame_800C9D94 = 0;
        t->next_8 = ActionRun_800BDC3C;
    }
}

void ActionRun_800BDC3C(BatTask_a* t)
{
    int k;
    if ((short)GetLatestHitFrame_800BE364() < actionFrame_800C9D94 && IsActionDone_800BEA94() == 1)
    {
        while ((k = removedEnemyCount_800C9D90--) != 0)
        {
            RemoveEnemy_800A2924(removedEnemies_800C9DD0[removedEnemyCount_800C9D90]);
        }
        t->f0 = (t->f0 & ~1) | 0x8000;
        battleFlags_800B1228 &= ~0x1000;
    }
    else
    {
        UpdateAction_800BE3C0();
    }
    actionFrame_800C9D94++;
}

int AreUnitsIdle_800BDD3C()
{
    unsigned char i;
    int r;
    int m;
    if (saveData_8008B570.field_0 & 0x20)
    {
        return 1;
    }
    if (summonedUnit_800C9C82 == 0)
    {
        r = IsLevantIdle_800A89F0();
    }
    else
    {
        r = IsSummonedMinionIdle_800C0D60();
    }
    if (r == 0)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        m = GetEnemyAliveMask_800A248C() & (1 << i);
        if (m != 0)
        {
            if (IsEnemyIdle_800A2550(i - 4) == 0)
            {
                return 0;
            }
        }
    }
    return IsEffectTaskIdle_800148D4() != 0;
}

int AreUnitsReady_800BDE04()
{
    unsigned char i;
    int r;
    int m;
    if (saveData_8008B570.field_0 & 0x20)
    {
        return 1;
    }
    if (summonedUnit_800C9C82 == 0)
    {
        r = IsLevantReady_800A8BE4();
    }
    else
    {
        r = IsSummonedMinionReady_800C0D88();
    }
    if (r == 0)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        r = GetEnemyAliveMask_800A248C();
        m = 1 << i;
        if (r & m)
        {
            if (IsEnemyReady_800A2594(i - 4) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void FaceActorAndTargets_800BDEBC()
{
    int x;
    int y;
    int ny;
    if (!(saveData_8008B570.field_0 & 0x20))
    {
        x = curCommand_800C9C88.mask_8;
        if (x & 0xF)
        {
            x &= ~0xE;
            x |= 1;
        }
        y = curCommand_800C9C88.targets_C;
        if (y & 0xF)
        {
            y &= ~0xE;
            y |= 1;
        }
        ny = y & ~x;
        x = x & ~y;
        y = ny;
        if (y)
        {
            if (curCommand_800C9C88.mask_8)
            {
                TurnUnitsToward_800BC468(y, curCommand_800C9C88.mask_8);
            }
        }
        if (x)
        {
            if (curCommand_800C9C88.targets_C)
            {
                TurnUnitsToward_800BC468(x, curCommand_800C9C88.targets_C);
            }
        }
    }
}

void StartActorAction_800BDF74()
{
    StartUnitAction_800BE058(actorTiming_800C9D98, &curCommand_800C9C88, 0, actingUnit_800C9C7C);
}

void StartReactions_800BDFAC()
{
    unsigned char i;
    BatPair_a t;
    for (i = 0; i < 7; i++)
    {
        if (actingUnit_800C9C7C == i)
        {
            t.hit_0 = 0;
            t.end_2 = 0;
        }
        else
        {
            StartUnitAction_800BE058(&t, &unitReactions_800C9CC8[i], 1, i);
        }
        reactionTimings_800C9DA0[i] = t;
    }
}

BatPair_a* StartUnitAction_800BE058(BatPair_a* out, BatCmd_a* cmd, int isReaction, int unit)
{
    BatPair_a r;
    if ((saveData_8008B570.field_0 & 0x20) || IsUnitOnField_800BC570(unit) == 0)
    {
        r.hit_0 = 0;
        r.end_2 = 0;
    }
    else
    {
        switch ((unsigned int)GetUnitSide_800BC7DC(unit))
        {
        case 0:
            StartLevantAction_800A8A30(&r, cmd, isReaction);
            break;
        case 1:
            StartMinionAction_800C0DDC(&r, cmd, isReaction);
            break;
        case 2:
            StartEnemyCommandAction_800A2684(&r, cmd, isReaction);
            break;
        }
    }
    *out = r;
    return out;
}

void TriggerUnitAction_800BE14C(BatCmd_a* cmd, int isReaction, int unit)
{
    int side;
    if (saveData_8008B570.field_0 & 0x20)
    {
        return;
    }
    if (IsUnitOnField_800BC570(unit) == 0)
    {
        return;
    }
    side = GetUnitSide_800BC7DC(unit);
    switch ((unsigned int)side)
    {
    case 0:
        TriggerLevantAction_800A8C0C(isReaction);
        break;
    case 1:
        TriggerMinionAction_800C0E84(cmd, isReaction);
        break;
    case 2:
        TriggerEnemyEffects_800A2760(cmd, isReaction);
        if (cmd->kind_0 == 0x13 || cmd->kind_0 == 0xB || cmd->kind_0 == 7 || (cmd->kind_0 == 5 && sub_80013358(cmd->arg_4) == 1) || (cmd->kind_0 == 0x1A && sub_80013358(cmd->arg_4) == 1))
        {
            removedEnemies_800C9DD0[removedEnemyCount_800C9D90] = unit - 4;
            removedEnemyCount_800C9D90++;
        }
        break;
    }
    if (!(saveData_8008B570.field_0 & 2) && isReaction == 0)
    {
        StartBattleCameraSpline_800377B4(side, (short)cmd->kind_0, unit - 4);
    }
}

void AlignActionTimings_800BE2C8()
{
    int m = GetLatestHitFrame_800BE364();
    unsigned char i;
    actorHitShift_800C9DBC = m - actorTiming_800C9D98[0];
    actorTiming_800C9D98[1] += actorHitShift_800C9DBC;
    for (i = 0; i < 7; i++)
    {
        reactionHitFrames_800C9DC0[i] = m - reactionTimings_800C9DA0[i].hit_0;
        reactionTimings_800C9DA0[i].end_2 += reactionHitFrames_800C9DC0[i];
    }
}

int GetLatestHitFrame_800BE364()
{
    unsigned char i;
    short m = actorTiming_800C9D98[0];
    for (i = 0; i < 7; i++)
    {
        if (m < reactionTimings_800C9DA0[i].hit_0)
        {
            m = reactionTimings_800C9DA0[i].hit_0;
        }
    }
    return m;
}

void UpdateAction_800BE3C0()
{
    unsigned char i;
    int v;
    if (actorHitShift_800C9DBC == actionFrame_800C9D94 && actingUnit_800C9C7C < 7)
    {
        TriggerUnitAction_800BE14C(&curCommand_800C9C88, 0, actingUnit_800C9C7C);
        StartHitNumber_800BF3DC(actingUnit_800C9C7C, 0, actorHpChange_800C9C7E, GetUnitPos_800BC6CC(actingUnit_800C9C7C), 0);
        if (actorHpChange_800C9C7E > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            PlaySfx_80031494(0x72);
        }
        StartHitNumber_800BF3DC(actingUnit_800C9C7C, 1, actorMpChange_800C9C80, GetUnitPos_800BC6CC(actingUnit_800C9C7C), 0);
        v = curCommand_800C9C88.kind_0;
        if (v == 5 || v == 0x1A)
        {
            RemoveEmptyCocoons_800AD944(1);
        }
        else if (v == 4)
        {
            RemoveInventory_800AD1E0(curCommand_800C9C88.arg_4, 1, 0);
        }
        else if (v == 0x13)
        {
            KillUnit_800127B8(GetUnitStatus_80014390(actingUnit_800C9C7C));
        }
        if (curCommand_800C9C88.kind_0 == 7 && actingUnit_800C9C7C != 0)
        {
            PlaySeqSlot_80031160(0x1C, 1);
        }
        if (GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 0 || GetUnitSide_800BC7DC(actingUnit_800C9C7C) == 1)
        {
            v = curCommand_800C9C88.kind_0;
            if (v == 5)
            {
                if (((BatSettingsBits*)&settingsFlags_8008B58C.word)->b21 == 1)
                {
                    StartPadVibration_80036528(0, 3);
                }
                else
                {
                    StartPadVibration_80036528(0, 4);
                }
            }
            else if (v - 2 < 2U)
            {
                StartPadVibration_80036528(0, 9);
            }
        }
    }
    if (actorTiming_800C9D98[0] + actorHitShift_800C9DBC == actionFrame_800C9D94)
    {
        if (hitSfx_800C9D78 >= 0)
        {
            if ((unsigned short)(hitSfx_800C9D78 - 0x70) < 3)
            {
                PlaySfx_80031494(hitSfx_800C9D78);
            }
        }
        if (deathSfx_800C9D80 >= 0)
        {
            if (TestBattleFlag_800BC820(4) == 1 || (TestBattleFlag_800BC820(8) != 1 && TestBattleFlag_800BC820(0x100000) == 1))
            {
                PlaySeqSlot_80031160(0x1C, 1);
            }
            else
            {
                PlaySfx_80031494(0x6F);
            }
        }
        if (areaElement_800C9D84 != shownAreaElement_800C9D82)
        {
            sub_80039ED8(areaElement_800C9D84);
            shownAreaElement_800C9D82 = areaElement_800C9D84;
        }
    }
    for (i = 0; i < 7; i++)
    {
        if (reactionHitFrames_800C9DC0[i] == actionFrame_800C9D94)
        {
            if (actingUnit_800C9C7C != i)
            {
                BatCmd_a* s = &unitReactions_800C9CC8[i];
                if ((s->kind_0 == 5 && sub_80013358(s->arg_4) == 1) || (s->kind_0 == 0x1A && sub_80013358(s->arg_4) == 1))
                {
                    AddEnemyItem_800A2898(i - 4);
                }
                TriggerUnitAction_800BE14C(&unitReactions_800C9CC8[i], 1, i);
            }
            if (reactionHitFrames_800C9DC0[i] == actionFrame_800C9D94)
            {
                AdjustUnitStatById_800127D0(i, 0x11, 0, unitResultFlags_800C9D58[i]);
                AdjustUnitStatById_800127D0(i, 0x10, 0, unitStatusInflicted_800C9CA0[i]);
                ShowUnitHitResult_800BE834(i, GetUnitPos_800BC6CC(i));
                if (IsUnitInBattle_800BC784(i) == 1)
                {
                    if (i >= 4)
                    {
                        SetEnemyStatusTint_800A284C(i - 4);
                    }
                    else if (i != 0 && summonedUnit_800C9C82 != 0)
                    {
                        UpdateMinionStatusTint_800C0F1C();
                    }
                }
            }
        }
    }
}
