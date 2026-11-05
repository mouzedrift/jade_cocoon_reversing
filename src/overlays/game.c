// GAME.BIN, source file 1 of 3
#include "game.h"
#include "spadstack.h"

const int dword_800A05A0 = 12;
const char aAssertionFaile_800A05A4[] = "Assertion failed: file \"%s\", line %d\n";
const char aEnmbatleC_800A05CC[12] = "ENMBATLE.C\000a";

void EnableCameraPoints_800A094C(void)
{
    unknownFlags_8008D678 &= ~0x8000;
}

// Matched
void DisableCameraPoints_800A096C(void)
{
    unknownFlags_8008D678 |= 0x8000;
}

// Matched
void FreezeTileAnim_800A0988(void)
{
    *(unsigned short*)tileAnimTask_800B1DBC->entry.buffer |= 1;
}

// Matched
void UnfreezeTileAnim_800A09B0(void)
{
    *(unsigned short*)tileAnimTask_800B1DBC->entry.buffer &= 0xFFFE;
}

// Matched
void TileAnimTaskInit_800A09D8(GameTask* task, short* work)
{
    *work = 0;
    task->next_8 = TileAnimTask_800A0A04;
    TileAnimTask_800A0A04(task, work);
}

// Draws the animated tile layers on the scratchpad stack, unless the camera points are disabled.
// Matched
void TileAnimTask_800A0A04(GameTask* task, short* work)
{
    if (!(unknownFlags_8008D678 & 0x8000))
    {
        SetSpadStack(SPAD_STACK_ADDR);
        DrawTileAnimLayers_800A0A5C(work);
        ResetSpadStack();
    }
}

#if 0
// Not matched: register pressure / spills differ (the original spills the cell pointer and u0 + 31, keeps 0xFFFFFF hoisted; here the tpage value spills); logic complete.
// Draws the map's animated tile layers (tileAnim_8008D648.lists_14): steps each layer's frame timer, then builds a
// zoomed POLY_FT4 (or, unzoomed, a SPRT + DR_TPAGE) for every 32x32 cell of the frame's tile set.
// Runs on the scratchpad stack (TileAnimTask_800A0A04); *q & 1 freezes the timers.
void DrawTileAnimLayers_800A0A5C(short* work)
{
    TileAnimScratch* s = TILE_ANIM_SCRATCH;
    TileAnimLayer* list;
    TileAnimTimer* st;
    unsigned short* cells;
    int otz;
    int cell;
    int k;
    int tile;
    int page;
    int texU;
    int texV;
    int bright;
    setPolyFT4(&s->ft4_4);
    setSprt(&s->sprt_2C);
    setDrawTPage(&s->tpage_40, 0, 1, 0);
    s->zoom_54 = cameraZoom_8008B4F8;
    s->cx_50 = viewport_8008D420.x + viewport_8008D420.w / 2;
    s->cy_52 = viewport_8008D420.y + viewport_8008D420.h / 2;
    s->ox_58 = screenOffset_8008D474.a + (display_8008B4D8.w_C / 2 - (viewport_8008D420.x + viewport_8008D420.w / 2));
    s->oy_5C = screenOffset_8008D474.b + (display_8008B4D8.h_E / 2 - (viewport_8008D420.y + viewport_8008D420.h / 2));
    bright = (sceneBrightness_8008D40C << 7) >> 12;
    s->ft4_4.r0 = bright;
    s->ft4_4.g0 = bright;
    s->ft4_4.b0 = bright;
    s->sprt_2C.r0 = bright;
    s->sprt_2C.g0 = bright;
    s->sprt_2C.b0 = bright;
    if (!(unknownFlags_8008D678 & 0x400) || sceneBrightness_8008D40C == 0x1000)
    {
        s->ft4_4.code = 0x2D;
        s->sprt_2C.code = 0x65;
    }
    else
    {
        s->sprt_2C.code = 0x64;
        s->ft4_4.code = 0x2C;
    }
    for (s->i_0 = 0; s->i_0 < tileAnim_8008D648.listCount_10; s->i_0++)
    {
        list = &tileAnim_8008D648.lists_14[s->i_0];
        st = &tileAnim_8008D648.pairs_18[s->i_0];
        if (list->count >= 2)
        {
            if (!(*work & 1))
            {
                st->timer_0++;
            }
            if ((unsigned short)st->timer_0 >= (list->items[(unsigned short)st->frame_2].time_2 & 0x7F))
            {
                st->frame_2++;
                if ((unsigned short)st->frame_2 >= list->count)
                {
                    st->frame_2 = 0;
                }
                st->timer_0 = 0;
            }
        }
        s->set_70 = list->items[(unsigned short)st->frame_2].set_0;
        s->clut_74 = list->items[(unsigned short)st->frame_2].clut_1;
        s->time_78 = list->items[(unsigned short)st->frame_2].time_2 & 0x7F;
        s->tiles_60 = tileAnim_8008D648.items_C[s->set_70];
        cells = s->tiles_60.items;
        if (list->items[(unsigned short)st->frame_2].time_2 & 0x80)
        {
            setSemiTrans(&s->ft4_4, 1);
            setSemiTrans(&s->sprt_2C, 1);
        }
        else
        {
            setSemiTrans(&s->ft4_4, 0);
            setSemiTrans(&s->sprt_2C, 0);
        }
        otz = ((tileAnim_8008D648.field_4 +
              (unsigned int)((tileAnim_8008D648.field_8 - tileAnim_8008D648.field_4) * (0xFF - s->tiles_60.depth_0)) / 0xFF) >>
             4) &
            0x3FF;
        s->ft4_4.clut = (s->clut_74 + 0x1F0) << 6;
        for (k = 0, cell = 0; k < s->tiles_60.count; k++)
        {
            tile = (short)cells[k];
            if (tile & 0x8000)
            {
                cell += tile & 0x7FFF;
                continue;
            }
            page = tile / 8;
            s->x0_48 = (cell % (short)s->tiles_60.columns_8) * 32 - (short)s->tiles_60.columns_8 * 16;
            s->ft4_4.tpage = (((page + 20) / 4) & 0xF) | 0xA0;
            s->y0_4A = (cell / (short)s->tiles_60.columns_8) * 32 - (short)s->tiles_60.rows_A * 16;
            s->x1_4C = s->cx_50 + (s->ox_58 + ((s->x0_48 + 32) * s->zoom_54) / 4096);
            s->y1_4E = s->cy_52 + (s->oy_5C + ((s->y0_4A + 32) * s->zoom_54) / 4096);
            s->x0_48 = s->cx_50 + (s->ox_58 + (s->x0_48 * s->zoom_54) / 4096);
            s->y0_4A = s->cy_52 + (s->oy_5C + (s->y0_4A * s->zoom_54) / 4096);
            if (s->x0_48 >= -(s->zoom_54 / 128) && s->x0_48 <= 0x140 && s->y0_4A >= -(s->zoom_54 / 128))
            {
                if (s->y0_4A > 0xF0)
                {
                    break;
                }
                texU = ((page * 16 + 0x140) % 64) * 2;
                texV = (tile % 32) * 32;
                s->ft4_4.x0 = s->x0_48;
                s->ft4_4.u0 = texU;
                s->ft4_4.v0 = texV;
                s->ft4_4.u2 = texU;
                s->ft4_4.v1 = texV;
                s->ft4_4.v2 = texV + 31;
                s->ft4_4.u1 = texU + 31;
                s->ft4_4.y0 = s->y0_4A;
                s->ft4_4.x1 = s->x1_4C;
                s->ft4_4.y1 = s->y0_4A;
                s->ft4_4.x2 = s->x0_48;
                s->ft4_4.y2 = s->y1_4E;
                s->ft4_4.x3 = s->x1_4C;
                s->ft4_4.y3 = s->y1_4E;
                s->ft4_4.v3 = texV + 31;
                s->sprt_2C.w = 32;
                s->sprt_2C.h = 32;
                s->ft4_4.u3 = texU + 31;
                s->sprt_2C.x0 = s->x0_48;
                s->sprt_2C.y0 = s->y0_4A;
                setDrawTPage(&s->tpage_40, 0, 1, (((page + 20) / 4) & 0xF) | 0xA0);
                *(int*)&s->sprt_2C.u0 = *(int*)&s->ft4_4.u0;
                if (cameraZoom_8008B4F8 != 0x1000)
                {
                    *(POLY_FT4*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = s->ft4_4;
                    addPrim(&pOT_8008D690[otz], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(POLY_FT4);
                }
                else
                {
                    *(SPRT*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = s->sprt_2C;
                    addPrim(&pOT_8008D690[otz], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(SPRT);
                    *(DR_TPAGE*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = s->tpage_40;
                    addPrim(&pOT_8008D690[otz], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(DR_TPAGE);
                }
            }
            cell++;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, DrawTileAnimLayers_800A0A5C);

void EncounterWatchTask_800A1314(GameTask* task)
{
    if (CheckEnemyContact_800A19E4() == 1)
        battleFlags_800B1228 |= 0x4000;
    if (battleFlags_800B1228 & 0x4000)
    {
        StartPadVibration_80036528(0, 10);
        SetFadeMode_8001C19C(0, 0x20);
        SetFadeMode_8001C19C(1, 0x20);
        RequestGameMode_800A6D30(2);
        task->next_8 = StartEncounterBattle_800A13B8;
        unknownFlags_8008D678 |= 0x4000000;
    }
}

// Matched
void StartEncounterBattle_800A13B8(GameTask* task, void** work)
{
    EnterLevantBattleMode_800A895C();
    SetupEncounter_800A1BD0();
    SuspendOtherEnemies_800A1E98();
    FreeLevantAnimSet_800AC73C();
    FreeLoaderModelAnimSets_80020814();
    SetCameraBattleMode_80037720();
    *work = LoadOverlayIfChanged_80020D1C(1, 6);
    task->next_8 = WaitBattleOverlay_800A1474;
    StopSoundSeqs_80030D68(&bgmSound_80091CE0);
    PlayMusic_800300E0(0, 1);
}

// Matched
void FreeBattleResources_800A1444(void)
{
    FreeActiveOverlay_8002C014();
    FreeSeqSlotSound_80030664();
    FreeStageEffects_80039FC0();
}

// Matched
void WaitBattleOverlay_800A1474(GameTask* task, GameBattleWork* work)
{
    if (GetFileRequestStatus_8003BE30(work->req_0) == 0)
    {
        StartSceneFadeOut_8001AA50(1);
        work->battleTask_8 = StartBattle_800BA9E4();
        task->next_8 = BattleEnd_800BA254;
    }
    eventDispatchHalt_8008B540 = 1;
}

// Matched
void WaitBattleReturnFiles_800A14E0(GameTask* task, GameBattleWork* work)
{
    if (GetFileRequestStatus_8003BE30(work->req_0) == 0)
    {
        RequestGameMode_800A6D30(0xa);
        work->battleTask_8 = sub_800BBB94();
        task->next_8 = EncounterFadeInWait_800A167C;
        unknownFlags_8008D678 &= ~0x4000000;
        battleFlags_800B1228 &= ~0x4000;
    }
    eventDispatchHalt_8008B540 = 1;
}

void ReturnFromBattle_800A1578(GameTask* task, int** work)
{
    if ((*work[2] & 0x8001) != 1)
    {
        SaveData* sd;
        FreeActiveOverlay_8002C014();
        SetFadeMode_8001C19C(0, 0x20);
        sd = &saveData_8008B570;
        if (sd->mapId_2E4[3].field_2 == sd->mapId_2E4[3].field_0)
        {
            RequestAreaReload_80027314();
        }
        ResetOverlayLoaderTask_80020D68();
        task->next_8 = WaitMapReloadAfterBattle_800A15FC;
    }
}

// Matched
void WaitMapReloadAfterBattle_800A15FC(GameTask* task, GameBattleWork* work)
{
    if (IsMapLoading_800272D0() == 0)
    {
        RequestGameMode_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
        task->next_8 = EncounterFadeInWait_800A167C;
        work->fadeWait_4 = 2;
        battleFlags_800B1228 &= ~0x4000;
    }
    eventDispatchHalt_8008B540 = 1;
}

// Matched
void EncounterFadeInWait_800A167C(GameTask* task, GameBattleWork* work)
{
    work->fadeWait_4--;
    if (work->fadeWait_4 <= 0)
    {
        SetFadeMode_8001C19C(3, 0x20);
        task->next_8 = EncounterWatchTask_800A1314;
        unknownFlags_8008D678 &= ~0x4000000;
    }
}

// Matched
void SetEncounterRecord_800A16DC(GameV3_1* rec)
{
    encounterRecord_800ADE78.active_0 = rec->a;
    encounterRecord_800ADE78.f4 = rec->b;
    encounterRecord_800ADE78.f8 = rec->c;
    encounterRecord_800ADE78.index_C = -1;
    encounterRecord_800ADE78.next_10 = -1;
}

// Matched
void ResetEncounter_800A170C(void)
{
    GameV6_1 rec;
    int i;
    rec.a = 0;
    rec.b = 0;
    rec.c = 0;
    SetEncounterRecord_800A16DC((GameV3_1*)&rec);
    gCtx_800B1260.active_0 = 0;
    gCtx_800B1260.otherCount_8 = 0;
    gCtx_800B1260.count_40 = 0;
    gCtx_800B1260.remaining_44 = 0;
    for (i = 11; i >= 0; i--)
    {
        gCtx_800B1260.actors_7c[i] = 0;
    }
    gCtx_800B1260.activeCount_76C = 0;
    gCtx_800B1260.memberCount_770 = 0;
    gCtx_800B1260.fixed_774 = 0;
    gCtx_800B1260.reused_778 = 0;
    gCtx_800B1260.f77c = 0;
    gCtx_800B1260.f780 = 1;
    gCtx_800B1260.f784 = 1;
    gCtx_800B1260.swapped_3C = 0;
}

// Matched
void ClearEnemySlots_800A1794(void)
{
    int i;
    for (i = 2; i >= 0; i--)
    {
        enemySlots_800B19F0[i].used_0 = 0;
    }
}

// Matched
GameEnemySlot* FindFreeEnemySlot_800A17BC(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (enemySlots_800B19F0[i].used_0 == 0)
        {
            return &enemySlots_800B19F0[i];
        }
    }
    return 0;
}

// Matched
GameEnemySlot* AddEnemySlot_800A17F4(unsigned int* src, GameAi* ai)
{
    GameEnemySlot* slot = FindFreeEnemySlot_800A17BC();
    slot->used_0 = 1;
    slot->ai_4 = ai;
    MemCopy_800403E8(&slot->data_8, src, 0xe0);
    return slot;
}

// Matched
void RemoveEnemySlot_800A1850(GameEnemySlot* slot)
{
    GameAi* ai = slot->ai_4;
    Actor* actor = ai->actor_8;
    slot->used_0 = 0;
    FreeEnemyAi_800A2D28(ai);
    DestroyActor_8001D600(actor);
}

// Matched
void SuspendEnemySlot_800A188C(GameEnemySlot* slot)
{
    GameAi* ai = slot->ai_4;
    Actor* actor = ai->actor_8;
    SuspendEnemyAi_800A2EC8(ai);
    SetActorActive_8001D658(actor, 0);
}

// Matched
void ResumeEnemySlot_800A18C8(GameEnemySlot* slot)
{
    GameAi* ai = slot->ai_4;
    Actor* actor = ai->actor_8;
    ResumeEnemyAi_800A2D48(ai);
    SetActorActive_8001D658(actor, 1);
}

// Matched
void SuspendAllEnemySlots_800A1904(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (enemySlots_800B19F0[i].used_0)
        {
            GameAi* ai = enemySlots_800B19F0[i].ai_4;
            SuspendEnemyAi_800A2EC8(ai);
            SetActorAnimPaused_8001D6EC(ai->actor_8, 1);
        }
    }
}

// Matched
void ResumeAllEnemySlots_800A1974(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (enemySlots_800B19F0[i].used_0)
        {
            GameAi* ai = enemySlots_800B19F0[i].ai_4;
            ResumeEnemyAi_800A2D48(ai);
            SetActorAnimPaused_8001D6EC(ai->actor_8, 0);
        }
    }
}

int CheckEnemyContact_800A19E4(void)
{
    int i;
    GameEnemySlot* slot;
    GameAi* ai;
    unsigned int dist;
    int radius;
    if (GetEventEnemy_800A5F6C())
    {
        return 1;
    }
    if (fieldMode_800B0EC0 != 1)
    {
        return 0;
    }
    if (forceMapReload_80091C9C)
    {
        return 0;
    }
    if (saveData_8008B570.mapId_2E4[3].field_0 != saveData_8008B570.mapId_2E4[3].field_2)
    {
        return 0;
    }
    if (IsSceneHeld_800A5E68())
    {
        return 0;
    }
    for (i = 0, slot = enemySlots_800B19F0; i < 3; i++, slot++)
    {
        if (slot->used_0)
        {
            ai = slot->ai_4;
            dist = 0xfff;
            if (IsWithinDistance_8003B740(ai->actor_8->pos_38, &levantPos_8008BD18.pos.x, &dist) == 1)
            {
                radius = ai->actor_8->baseScale_138[2] * 400 / 4096;
                if (dist < radius * radius)
                {
                    encounterSlot_800B1264 = (int*)slot;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Matched
int AreAllEncounterEnemiesGone_800A1B2C(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.count_40; i++)
    {
        if (gCtx_800B1260.gone_4C[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Matched
void DestroyEncounterActors_800A1B78(void)
{
    int i;
    for (i = 0; i < 12; i++)
    {
        if (gCtx_800B1260.actors_7c[i])
        {
            DestroyActor_8001D600(gCtx_800B1260.actors_7c[i]);
        }
    }
}

// Matched
void SetupEncounter_800A1BD0(void)
{
    GameEnemy* enemy = GetEventEnemy_800A5F6C();
    int found;
    Actor* actor;
    GameEnemySlot* slot;
    GameEnemySlot* s;
    int* anims;
    GameAi* ai;
    int done;
    int i;
    int n;
    int max;
    GameEnemySlot* p;
    GameEnemySlot* q;
    GameEncounter* enc;
    if (enemy)
    {
        actor = enemy->actors_A4[0];
        enemy->actors_A4[0] = CloneActor_8001D4DC(actor, 0, 0, 0);
        slot = AddEnemySlot_800A17F4((unsigned int*)enemy, 0);
        slot->ai_4 = CreateEnemyAiEvent_800A2D90(enemy->actors_A4[0], &slot->data_8.minion_1C, 0);
        SetActorVisible_8001D730(actor, 0);
        SetActorGroundMove_8001D68C(actor, 0);
        encounterSlot_800B1264 = (int*)slot;
    }
    found = 0;
    for (i = 0; i < 3; i++)
    {
        if (enemySlots_800B19F0[i].used_0)
        {
            s = &enemySlots_800B19F0[i];
            slot = s;
            done = 0;
            anims = s->data_8.anims_C8[0];
            ai = s->ai_4;
            anims = anims ? anims : name_8007A024;
            if (!found && gCtx_800B1260.leader_4 == s)
            {
                SuspendEnemyAi_800A2EC8(ai);
                StartActorScript_8001DC34(ai->actor_8, (void*)anims[0]);
                found = 1;
                done = found;
                gCtx_800B1260.leader_4 = s;
            }
            if (!done)
            {
                SuspendEnemyAi_800A2EC8(ai);
                StartActorScript_8001DC34(ai->actor_8, (void*)anims[1]);
                gCtx_800B1260.others_C[gCtx_800B1260.otherCount_8] = slot;
                gCtx_800B1260.otherCount_8++;
            }
        }
    }
    enc = &gCtx_800B1260;
    p = (GameEnemySlot*)enc->leader_4;
    for (i = 0; i < 3; i++)
    {
        if ((unsigned)p->data_8.members_B0[i].species_0 >= 0xd3)
        {
            break;
        }
    }
    max = p->data_8.maxCount_4;
    if (max >= i)
    {
        n = i;
    }
    else
    {
        n = max;
    }
    enc->activeCount_76C = n;
    enc->memberCount_770 = i;
    q = (GameEnemySlot*)enc->leader_4;
    enc->fixed_774 = q->data_8.kind_0 == 0;
    enc->reused_778 = q->data_8.kind_0 == 1;
    enc->f77c = 0;
    enc->f780 = q->data_8.f8;
    enc->f784 = q->data_8.fC;
    enc->f788 = q->data_8.f10;
    dword_800B1CA8[0] = 0;
    enc->groupIndex_48 = q->data_8.groupIndex_14;
    gCtx_800B1260.active_0 = 1;
}

// Matched
void EndEncounter_800A1E1C(void)
{
    ResetEncounter_800A170C();
}

// Matched
char* GetBattleSelection_800A1E3C(void)
{
    return battleSelection_800B19CC;
}

// Matched
int* GetEncounterLeaderPos_800A1E48(void)
{
    return gCtx_800B1260.leader_4->ai_4->actor_8->pos_38;
}

// Matched
short* GetEncounterLeaderRot_800A1E68(void)
{
    return gCtx_800B1260.leader_4->ai_4->actor_8->rot_5C;
}

// Matched
void EncounterNop_800A1E88(void)
{
}

// Matched
int ReturnOne_800A1E90(void)
{
    return 1;
}

// Matched
void SuspendOtherEnemies_800A1E98(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.otherCount_8; i++)
    {
        SuspendEnemySlot_800A188C(gCtx_800B1260.others_C[i]);
    }
    SuspendFieldMinions_800A7B00(-1);
}

// Matched
void ResumeOtherEnemies_800A1F0C(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.otherCount_8; i++)
    {
        ResumeEnemySlot_800A18C8(gCtx_800B1260.others_C[i]);
    }
    ResumeFieldMinions_800A7BF0(-1);
}

// Matched
void SpawnEncounterEnemies_800A1F80(void)
{
    ActorDesc desc;
    int scale[3];
    GameEncounter* enc;
    GameEnemySlot* leader;
    int count;
    short* offs;
    int i;
    int scaleIdx;
    Model* model;
    Actor* actor;
    MinionModelDesc* modelDesc;
    int* scale0;
    int* scale1;
    int rank;
    enc = &gCtx_800B1260;
    count = enc->memberCount_770;
    leader = enc->leader_4;
    if (enc->activeCount_76C < count)
    {
        offs = encounterFormations_800ADE9C[enc->activeCount_76C - 1];
    }
    else
    {
        offs = encounterFormations_800ADE9C[count - 1];
    }
    i = 0;
    do
    {
        scaleIdx = 0;
        if (i == 0 && leader->data_8.useMinion_18 == 1)
        {
            MemCopy_800403E8((unsigned int*)&gCtx_800B1260.ents_ac[gCtx_800B1260.count_40], (unsigned int*)&leader->data_8.minion_1C, sizeof(UnitStats));
        }
        else
        {
            scaleIdx = InitMinionData_8001900C(&gCtx_800B1260.ents_ac[gCtx_800B1260.count_40], &leader->data_8.members_B0[i].species_0);
        }
        if (leader->data_8.kind_0 == 0 || leader->data_8.actors_A4[i] != 0)
        {
            actor = CloneActor_8001D4DC(leader->data_8.actors_A4[i], 1, i, 1);
            if (leader->data_8.kind_0 == 1)
            {
                SetActorVisible_8001D730(actor, 1);
            }
        }
        else
        {
            modelDesc = GetSpeciesModelDesc_80019C70(leader->data_8.members_B0[i].species_0);
            model = AcquireLoaderModel_80020734(modelDesc->modelId_0);
            desc.modelId_0 = modelDesc->modelId_0;
            desc.kind_4 = 1;
            desc.pos_8[0] = 0;
            desc.pos_8[1] = 0;
            desc.pos_8[2] = 0;
            desc.rot_14[0] = 0;
            desc.rot_14[1] = 0;
            desc.rot_14[2] = 0;
            desc.clutRow_1C = i;
            desc.animIdx_20 = 4;
            desc.frame_24 = -3;
            desc.frameSpeed_28 = 0x1000;
            desc.blendDiv_2C = 4;
            desc.visible_30 = 1;
            desc.bones_34 = defaultBones_80079140;
            if (scaleIdx >= 4)
            {
                desc.baseScale_38 = (int*)GetModelBaseScale_80024E90(model, scaleIdx);
            }
            else
            {
                scale0 = (int*)GetModelBaseScale_80024E90(model, scaleIdx);
                scale1 = (int*)GetModelBaseScale_80024E90(model, scaleIdx + 1);
                rank = GetUnitRank_80019AD0(&gCtx_800B1260.ents_ac[gCtx_800B1260.count_40]);
                rank = ((scale1[0] - scale0[0]) * rank) / 4096;
                scale[0] = scale0[0] + rank;
                scale[1] = scale0[1] + rank;
                scale[2] = scale0[2] + rank;
                desc.baseScale_38 = scale;
            }
            desc.boneScale_3C = (SVECTOR*)GetModelBoneScale_80024EC8(model, scaleIdx);
            desc.anims_40 = (ActorAnim*)GetModelActorAnims_80024E38(model);
            desc.effectTbl_44 = (short (*)[6])GetModelEffectTable_80024E64(model);
            desc.hasMatrices_4C = 1;
            actor = CreateActor_8001D45C(&desc);
            SetBoneGroupFlags_80019B14(actor->bones_134, (unsigned short*)GetModelBoneGroupLevels_80024F00(model, scaleIdx), (unsigned short*)GetModelBoneGroupFlags_80024F38(model, scaleIdx));
        }
        actor->pos_38[0] = saveData_8008B570.levant_7A8.pos.x + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + offs[i % gCtx_800B1260.activeCount_76C]) & 0xfff] * 1000 / 4096;
        actor->pos_38[1] = saveData_8008B570.levant_7A8.pos.y;
        actor->pos_38[2] = saveData_8008B570.levant_7A8.pos.z + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + offs[i % gCtx_800B1260.activeCount_76C] + 0x400) & 0xfff] * 1000 / 4096;
        actor->rot_5C[0] = 0;
        actor->prevPos_44[0] = actor->pos_38[0];
        actor->prevPos_44[1] = actor->pos_38[1];
        actor->prevPos_44[2] = actor->pos_38[2];
        actor->basePos_50[0] = actor->pos_38[0];
        actor->basePos_50[1] = actor->pos_38[1];
        actor->basePos_50[2] = actor->pos_38[2];
        actor->rot_5C[1] = ratan2_8003B548(saveData_8008B570.levant_7A8.pos.x - actor->pos_38[0], saveData_8008B570.levant_7A8.pos.z - actor->pos_38[2]);
        actor->rot_5C[2] = 0;
        SetActorGroundMove_8001D68C(actor, 0);
        gCtx_800B1260.actors_7c[gCtx_800B1260.count_40] = actor;
        gCtx_800B1260.gone_4C[gCtx_800B1260.count_40] = i >= gCtx_800B1260.activeCount_76C;
        gCtx_800B1260.anims_70C[gCtx_800B1260.count_40] = (int)leader->data_8.anims_C8[i];
        gCtx_800B1260.f73c[gCtx_800B1260.count_40] = leader->data_8.fD4[i];
        i++;
        gCtx_800B1260.count_40++;
        gCtx_800B1260.remaining_44++;
    } while (i < count);
    RemoveEnemySlot_800A1850(leader);
}

// Matched
int GetEnemyAliveMask_800A248C(void)
{
    int mask = 0;
    int i;
    for (i = 0; i < gCtx_800B1260.count_40; i++)
    {
        if (gCtx_800B1260.actors_7c[i] && gCtx_800B1260.gone_4C[i] == 0)
        {
            mask |= 1 << (i + 4);
        }
    }
    return mask;
}

// Matched
int IsEnemyAlive_800A24F4(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    if (gCtx_800B1260.actors_7c[idx] != 0)
    {
        if (gCtx_800B1260.gone_4C[idx] == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Matched
int IsEnemyIdle_800A2550(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return IsActorIdle_8001E1C8(gCtx_800B1260.actors_7c[idx]);
}

// Matched
int IsEnemyReady_800A2594(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return IsActorActionReady_8001E1DC(gCtx_800B1260.actors_7c[idx]);
}

// Matched
int TurnEnemyToward_800A25D8(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return 0;
}

// Matched
int EnemyReturnZero_800A25F8(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return 0;
}

// Matched
int EnemyChooseCommand_800A2618(void* cmd, int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    ChooseEnemyCommand_800C4118(cmd, &gCtx_800B1260.ents_ac[idx], idx, gCtx_800B1260.f73c[idx]);
    return 1;
}

// Matched
GameActionFrames StartEnemyCommandAction_800A2684(int* cmd, int arg)
{
    GameActionFrames frames;
    int i;
    Actor* actor;
    memset(&frames, 0, 4);
    if (cmd[0] == 0x14)
        return frames;
    for (i = 4; i < 7; i++)
    {
        if (((unsigned)cmd[2] & (1 << i)) != 0)
        {
            actor = gCtx_800B1260.actors_7c[i - 4];
            frames = StartCommandAction_80018A4C(actor, cmd, (ActorScriptCmd**)gCtx_800B1260.anims_70C[i - 4], arg);
        }
    }
    return frames;
}

// Matched
int TriggerEnemyEffects_800A2760(unsigned int* cmd)
{
    int i;
    if (cmd[0] == 0x14)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        if (cmd[2] & (1 << i))
        {
            TriggerActorEffect_8001E28C(gCtx_800B1260.actors_7c[i - 4]);
        }
    }
    return 1;
}

// Matched
void GetEnemyHitFrame_800A27FC(int idx, int hit)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    GetActorHitFrame_80018E5C(gCtx_800B1260.actors_7c[idx], hit);
}

// Matched
void SetEnemyStatusTint_800A284C(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    {
        UnitStatus* status = GetEnemyStatus_800A2B60(idx);
        SetActorStatusTint_80018EBC(gCtx_800B1260.actors_7c[idx], status);
    }
}

// Matched
int AddEnemyItem_800A2898(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return AddItem_80010650(&gCtx_800B1260.ents_ac[idx]);
}

// Matched
int EnemyReturnZero_800A28DC(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return 0;
}

// Matched
int CanFleeFromEnemy_800A28FC(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return dword_800B19E0;
}

// Matched
void RemoveEnemy_800A2924(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    gCtx_800B1260.gone_4C[idx] = 1;
    if (--gCtx_800B1260.remaining_44 == 0)
    {
        int group = gCtx_800B1260.groupIndex_48;
        if (group >= 0)
        {
            SaveData* sd = &saveData_8008B570;
            ClearEncounterGroupFlags_800A4940(group, mapTable_800B0608[sd->mapId_2E4[0].field_0][sd->mapId_2E4[1].field_0][sd->mapId_2E4[2].field_0].encIndex_4);
        }
    }
}

// Matched
void GetEnemyEffectTarget_800A29CC(int idx, EffectTarget* out)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    {
        Actor* actor = gCtx_800B1260.actors_7c[idx];
        out->tbl_0 = actor->effectTbl_14C;
        out->pos_4 = actor->pos_38;
        out->bonePos_8 = actor->bonePos_1C4;
        out->boneMatrices_C = actor->boneMatrices_1C8;
        out->boneScale_2C = actor->boneScale_144;
        out->scale_30 = actor->scale_2C;
    }
}

// Matched
int EnemyReturnZero_800A2A50(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return 0;
}

// Matched
int GetEnemyMagicBits_800A2A70(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    {
        UnitStats* e = &gCtx_800B1260.ents_ac[idx];
        return (int)&e->magicBits_80;
    }
}

// Matched
int GetActiveSwapEnemy_800A2AB4(void)
{
    GameEncounter* enc = &gCtx_800B1260;
    if (enc->fixed_774 != 0)
    {
        if (enc->swapped_3C == 0)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

// Matched
void SwapEncounterEnemy_800A2AE8(void)
{
    if (gCtx_800B1260.swapped_3C == 0)
    {
        gCtx_800B1260.gone_4C[0] = 1;
        gCtx_800B1260.gone_4C[1] = 0;
        gCtx_800B1260.swapped_3C = 1;
    }
    else
    {
        gCtx_800B1260.gone_4C[0] = 0;
        gCtx_800B1260.gone_4C[1] = 1;
        gCtx_800B1260.swapped_3C = 0;
    }
}

// Matched
UnitStats* GetEnemyStats_800A2B20(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return &gCtx_800B1260.ents_ac[idx];
}

// Matched
UnitStatus* GetEnemyStatus_800A2B60(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return &gCtx_800B1260.ents_ac[idx].st_0;
}

// Matched
int GetEnemySkills_800A2BA0(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    {
        UnitStats* e = &gCtx_800B1260.ents_ac[idx];
        return (int)&e->skills_6C;
    }
}

// Matched
int GetEnemySpecies_800A2BE4(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    {
        UnitStats* e = &gCtx_800B1260.ents_ac[idx];
        return e->species_5C;
    }
}

// Matched
int* GetEnemyPos_800A2C28(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return gCtx_800B1260.actors_7c[idx]->pos_38;
}

// Matched
int* GetEnemyBonePos_800A2C68(int idx)
{
    AssertEnemyIndex_800A2CA8(idx, 0);
    return gCtx_800B1260.actors_7c[idx]->bonePos_1C4;
}

int AssertEnemyIndex_800A2CA8(int idx, int noExit)
{
    int ok = 0;
    if (idx < 0 || idx >= gCtx_800B1260.count_40 || gCtx_800B1260.gone_4C[idx] != 0)
    {
        ok = 1;
    }
    if (ok)
    {
        if (!noExit)
        {
            printf(aAssertionFaile_800A05A4, aFile_800A05CC, 0x512);
            exit(1);
        }
    }
    return ok;
}

// Matched
void FreeEnemyAi_800A2D28(GameAi* ai)
{
    *ai->flags_0 = (*ai->flags_0 & ~1) | 0x8000;
}

// Matched
void ResumeEnemyAi_800A2D48(GameAi* ai)
{
    *ai->flags_0 &= ~0x8000;
    SetActorAnim_8001D760(ai->actor_8, ai->anim_20, -1, 0);
}

GameAi* CreateEnemyAiEvent_800A2D90(Actor* actor, UnitStats* minion, int active)
{
    EventEntry* e = AllocEventEntry_80043AF8(enemyAiTasks_8008D49C);
    GameAi* ai;
    int species;
    int base;
    int weak;
    if (e != 0)
    {
        ai = e->buffer;
        e->flags = (e->flags | 1) & ~0x8000;
        ai->flags_0 = &e->flags;
        ai->minion_4 = minion;
        ai->actor_8 = actor;
        ai->turnDir_28 = 0;
        ai->timer_24 = 0;
        ai->turnLeft_2C = 0;
        ai->anim_20 = -1;
        ai->state_c = -1;
        ai->f10 = -1;
        if (active == 0)
        {
            e->cb_8 = EnemyAiNone_800A2EE4;
        }
        else
        {
            species = minion->species_5C;
            if ((unsigned)species < 0x39)
            {
                weak = !(levantCaptureLevel_8008BD7C - minion->st_0.level_44 < 5);

                e->cb_8 = enemyAiBySpecies_800ADEB8[species][weak];
            }
            else
            {
                base = species;
                if (base >= 0x39)
                {
                    base = (base - 0x39) / 4;
                }
                e->cb_8 = enemyAiBySpecies_800ADEB8[base][0];
            }
        }
        return ai;
    }
    return 0;
}

// Matched
void SuspendEnemyAi_800A2EC8(GameAi* ai)
{
    *ai->flags_0 |= 0x8000;
}

// Matched
void EnemyAiNone_800A2EE4(EventEntry* e, void* ai)
{
}

void EnemyAiFlee_800A2EEC(int unused, GameAi* ai)
{
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        switch (ai->state_c)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 5, 2, 0, -1, 1, 2);
            SetActorSpeedScale_8001DB58(ai->actor_8, 0x3000, 1);
            break;
        case 5:
            EnemyAiFleeStep_800A459C(ai);
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
                ai->state_c = -1;
            break;
        }
    }
}

void EnemyAiWanderChase_800A2FB8(int unused, GameAi* ai)
{
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F && ai->state_c != 0xf)
        {
            SetEnemyAiState_800A433C(ai, 0xf, 2, 0, -1, 1, 2);
            SetActorSpeedScale_8001DB58(ai->actor_8, 0x2000, 1);
        }
        switch (ai->state_c)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 8, 2, (rand() % 16) * 10 + 100, -1, 1, 2);
            break;
        case 8:
            EnemyAiWanderStep_800A46FC(ai);
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 1, 1, (rand() % 16) * 10 + 100, -1, 1, 2);
            break;
        case 1:
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 0xe, 2, 0, -1, 1, 2);
            break;
        case 0xe:
            if (EnemyAiTurnStep_800A4470(ai) == 0)
                ai->state_c = -1;
            break;
        case 0xf:
            EnemyAiChaseStep_800A45F8(ai);
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
            {
                ai->state_c = -1;
                SetActorSpeedScale_8001DB58(ai->actor_8, 0x1000, 1);
            }
            break;
        }
    }
}

void EnemyAiWatchFlee_800A31DC(int unused, GameAi* ai)
{
    int state;
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 1, 1, 0, state, 1, 2);
            SetActorSpeedScale_8001DB58(ai->actor_8, 0x1000, 0);
            break;
        case 1:
            TurnActorTowards_8001DDFC(ai->actor_8, &levantPos_8008BD18.pos, 0x155);
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
            {
                SetEnemyAiState_800A433C(ai, 5, 2, 0, -1, state, 2);
                SetActorSpeedScale_8001DB58(ai->actor_8, 0x3000, 1);
            }
            break;
        case 5:
            EnemyAiFleeStep_800A459C(ai);
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
                aiCopy->state_c = -1;
            break;
        }
    }
}

void EnemyAiSleepChase_800A333C(int unused, GameAi* ai)
{
    GameAi* aiCopy = ai;
    int moveCmd;
    int state;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 0xd, 0x17, 0, -2, 0, 2);
        case 0xd:
            if (DistanceSquaredXZ_8003B860(aiCopy->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
            {
                moveCmd = GetLevantMoveCmd_800AB39C() & 0xFFFFFFF;
                if (moveCmd == 1)
                    SetEnemyAiState_800A433C(aiCopy, 0xf, 2, 0, -1, moveCmd, 2);
            }
            break;
        case 0xf:
            EnemyAiChaseStep_800A45F8(ai);
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x1CFDE0)
                SetEnemyAiState_800A433C(ai, 1, 1, 0x32, -1, 1, 2);
            break;
        case 1:
            if (--aiCopy->timer_24 < 0)
                SetEnemyAiState_800A433C(aiCopy, 0xd, 0x17, 0, -1, state, 2);
            break;
        }
    }
}

void EnemyAiWander_800A34D8(int unused, GameAi* ai)
{
    int state;
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 8, 2, (rand() % 16) * 10 + 0x64, state, 1, 2);
            break;
        case 8:
            EnemyAiWanderStep_800A46FC(ai);
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 1, 1, (rand() % 16) * 10 + 0x64, -1, 1, 2);
            break;
        case 1:
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 0xe, 2, 0, -1, state, 2);
            break;
        case 0xe:
            if (EnemyAiTurnStep_800A4470(ai) == 0)
                aiCopy->state_c = -1;
            break;
        }
    }
}

void EnemyAiWander2_800A366C(int unused, GameAi* ai)
{
    int state;
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 8, 2, (rand() % 16) * 10 + 0x64, state, 1, 2);
            break;
        case 8:
            EnemyAiWanderStep_800A46FC(ai);
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 1, 1, (rand() % 16) * 10 + 0x64, -1, 1, 2);
            break;
        case 1:
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 0xe, 2, 0, -1, state, state);
            break;
        case 0xe:
            if (EnemyAiTurnStep_800A4470(ai) == 0)
                aiCopy->state_c = -1;
            break;
        }
    }
}

void EnemyAiAlertChase_800A3804(int unused, GameAi* ai)
{
    int state;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 1, 1, 0, state, 1, 2);
            break;
        case 1:
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
                SetEnemyAiState_800A433C(ai, 0xa, 4, 0x28, -1, 1, 2);
            break;
        case 0xa:
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 0xf, 2, 0, -1, 1, 2);
            break;
        case 0xf:
            EnemyAiChaseStep_800A45F8(ai);
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x1CFDE0)
                ai->state_c = -1;
            break;
        }
    }
}

void EnemyAiChaseAlert_800A3954(int unused, GameAi* ai)
{
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        switch (ai->state_c)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 0xf, 2, 0, ai->state_c, 1, 2);
            break;
        case 0xf:
            EnemyAiChaseStep_800A45F8(ai);
            if (DistanceSquaredXZ_8003B860(ai->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
                SetEnemyAiState_800A433C(ai, 0xa, 4, 0x46, -1, 1, 2);
            break;
        case 0xa:
            TurnActorTowards_8001DDFC(aiCopy->actor_8, &levantPos_8008BD18.pos, 0x155);
            if (DistanceSquaredXZ_8003B860(aiCopy->actor_8->pos_38, &levantPos_8008BD18.pos) > 0xDBBA0)
                aiCopy->state_c = -1;
            break;
        }
    }
}

void EnemyAiWanderBump_800A3A8C(int unused, GameAi* ai)
{
    int state;
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 8, 2, 0, state, 1, 2);
            break;
        case 8:
            EnemyAiWanderStep_800A46FC(ai);
            if (EnemyAiCheckBlocked_800A4804(ai))
                SetEnemyAiState_800A433C(ai, 1, 1, (rand() % 16) * 8 + 0x32, -1, 1, 2);
            break;
        case 1:
            if (--ai->timer_24 < 0)
            {
                SetEnemyAiState_800A433C(ai, 0xe, 1, 0, -1, state, 2);
                RandomizeEnemyTurn_800A43FC(ai);
            }
            break;
        case 0xe:
            if (EnemyAiTurnStep_800A4470(ai) == 0)
                aiCopy->state_c = -1;
            break;
        }
    }
}

void EnemyAiChaseBehind_800A3BEC(int unused, GameAi* ai)
{
    int state;
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 1, 1, (rand() % 16) * 8 + 0x32, state, 1, 2);
            break;
        case 1:
            if (IsInFrontHalf_800A4884(&levantPos_8008BD18.pos, &levantPos_8008BD18.rot.vx, (Vec3i*)ai->actor_8->pos_38))
                SetEnemyAiState_800A433C(ai, 0xf, 2, 0, -1, state, 2);
            break;
        case 0xf:
            EnemyAiChaseStep_800A45F8(ai);
            if (IsInFrontHalf_800A4884(&levantPos_8008BD18.pos, &levantPos_8008BD18.rot.vx, (Vec3i*)ai->actor_8->pos_38) == 0)
                aiCopy->state_c = -1;
            break;
        }
    }
}

void EnemyAiWanderShort_800A3D24(int unused, GameAi* ai)
{
    int state;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 8, 2, 0x14, state, 1, 2);
            break;
        case 8:
            EnemyAiWanderStep_800A46FC(ai);
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 1, 1, (rand() % 16) * 8 + 0x32, -1, 1, 2);
            break;
        case 1:
            if (--ai->timer_24 < 0)
            {
                SetEnemyAiState_800A433C(ai, 0xe, 2, 0, -1, state, 2);
                RandomizeEnemyTurn_800A43FC(ai);
            }
            break;
        case 0xe:
            if (EnemyAiTurnStep_800A4470(ai) == 0)
                ai->state_c = -1;
            break;
        }
    }
}

void EnemyAiHideFlee_800A3E88(int unused, GameAi* ai)
{
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        switch (ai->state_c)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 0x10, 0x12, 0, ai->state_c, 1, 2);
        case 0x10:
            if (DistanceSquaredXZ_8003B860(aiCopy->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
            {
                SetEnemyAiState_800A433C(aiCopy, 5, 2, 0, -1, 1, 2);
                SetActorSpeedScale_8001DB58(aiCopy->actor_8, 0x2000, 1);
            }
            break;
        case 5:
            EnemyAiFleeTurnStep_800A44C0(aiCopy);
            if (DistanceSquaredXZ_8003B860(aiCopy->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
                aiCopy->state_c = -1;
            break;
        }
    }
}

void EnemyAiWanderMid_800A3FC0(int unused, GameAi* ai)
{
    int state;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        state = ai->state_c;
        switch (state)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 8, 2, 0x21, state, 1, 2);
            break;
        case 8:
            EnemyAiWanderStep_800A46FC(ai);
            if (--ai->timer_24 < 0)
                SetEnemyAiState_800A433C(ai, 1, 1, (rand() % 16) * 8 + 0x32, -1, 1, 2);
            break;
        case 1:
            if (--ai->timer_24 < 0)
            {
                SetEnemyAiState_800A433C(ai, 0xe, 2, 0, -1, state, 2);
                RandomizeEnemyTurn_800A43FC(ai);
            }
            break;
        case 0xe:
            if (EnemyAiTurnStep_800A4470(ai) == 0)
                ai->state_c = -1;
            break;
        }
    }
}

void EnemyAiAmbush_800A4124(int unused, GameAi* ai)
{
    GameAi* aiCopy = ai;
    if (ApplySporeToEnemyAi_800A4278(ai) == 0)
    {
        switch (ai->state_c)
        {
        case -1:
            SetEnemyAiState_800A433C(ai, 2, 1, 0, ai->state_c, 1, 2);
        case 2:
            SetActorAnimPaused_8001D6EC(aiCopy->actor_8, 1);
            if (DistanceSquaredXZ_8003B860(aiCopy->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0x61A7F)
                SetEnemyAiState_800A433C(aiCopy, 0xf, 2, 0, -1, 1, 2);
            break;
        case 0xf:
            EnemyAiChaseStep_800A45F8(aiCopy);
            if (DistanceSquaredXZ_8003B860(aiCopy->actor_8->pos_38, &levantPos_8008BD18.pos) > 0xDBBA0)
                SetEnemyAiState_800A433C(aiCopy, 2, 1, 0, -1, 1, 2);
            break;
        }
    }
}

// Matched
int ApplySporeToEnemyAi_800A4278(GameAi* ai)
{
    if (GetSporeMode_80011B6C() == 0)
    {
        if (ai->state_c != 0xd)
            SetEnemyAiState_800A433C(ai, 0xd, 0x17, 0, -1, 1, 2);
        return 1;
    }
    else if (GetSporeMode_80011B6C() == 1)
    {
        if (ai->state_c != 8)
            SetEnemyAiState_800A433C(ai, 8, 2, 0, -1, 1, 2);
        EnemyAiChaseStep_800A45F8(ai);
        return 1;
    }
    return 0;
}

void SetEnemyAiState_800A433C(GameAi* ai, int state, int anim, int timer, int animMode, int animFlag, int div)
{
    ai->state_c = state;
    ai->timer_24 = timer;
    ai->anim_20 = anim;
    SetActorAnim_8001D760(ai->actor_8, anim, animMode, animFlag);
    if (state == 0xe)
    {
        ai->turnLeft_2C = 0x1000 / (rand() % 16) / div;
        ai->turnDir_28 = (rand() & 1) ? 1 : 2;
    }
}

void RandomizeEnemyTurn_800A43FC(GameAi* ai)
{
    ai->turnLeft_2C = 0x1000 / (rand() % 16) / 2;
    ai->turnDir_28 = (rand() & 1) ? 1 : 2;
}

// Matched
int EnemyAiTurnStep_800A4470(GameAi* ai)
{
    if (ai->turnLeft_2C)
    {
        ai->turnLeft_2C = TurnActorBy_8001DD44(ai->actor_8, ai->turnDir_28, ai->turnLeft_2C, 0x20);
        RestartActorMotion_8001D71C(ai->actor_8);
        return 1;
    }
    return 0;
}

// Matched
void EnemyAiFleeTurnStep_800A44C0(GameAi* ai)
{
    GameVec4_1 toLevant;
    GameVec4_1 away;
    int ang;
    int idx;
    EnemyAiWanderStep_800A46FC(ai);
    toLevant.x = saveData_8008B570.levant_7A8.pos.x - ai->actor_8->pos_38[0];
    toLevant.z = saveData_8008B570.levant_7A8.pos.z - ai->actor_8->pos_38[2];
    ang = ratan2_8003B548(toLevant.x, toLevant.z);
    idx = (ang - ai->actor_8->rot_5C[1]) & 0xfff;
    away.x = ai->actor_8->pos_38[0] + (ai->actor_8->pos_38[0] - saveData_8008B570.levant_7A8.pos.x);
    away.z = ai->actor_8->pos_38[2] + (ai->actor_8->pos_38[2] - saveData_8008B570.levant_7A8.pos.z);
    if (TurnActorTowards_8001DDFC(ai->actor_8, (Vec3i*)&away, TurnStepForAngle_800A48F4(idx * 3)) == 0)
    {
        RestartActorMotion_8001D71C(ai->actor_8);
    }
}

// Matched
void EnemyAiFleeStep_800A459C(GameAi* ai)
{
    Vec3i away;
    ReflectPoint_800A47B8(&levantPos_8008BD18.pos, (Vec3i*)ai->actor_8->pos_38, &away);
    if (TurnActorTowards_8001DDFC(ai->actor_8, &away, 0x155) == 0)
    {
        RestartActorMotion_8001D71C(ai->actor_8);
    }
}

void EnemyAiChaseStep_800A45F8(GameAi* ai)
{
    int dir;
    int step;
    if (ai->turnLeft_2C)
    {
        ai->turnLeft_2C = TurnActorBy_8001DD44(ai->actor_8, ai->turnDir_28, ai->turnLeft_2C, 0x80);
    }
    dir = FindActorInFront_8001DECC(ai->actor_8, 0x190, 0);
    ai->turnDir_28 = dir;
    if (dir != 3)
    {
        if (dir != 0)
        {
            goto turn;
        }
        dir = ai->actor_8->ground_80;
        ai->turnDir_28 = dir;
        if (dir != 3)
        {
            goto check;
        }
    }
    ai->turnDir_28 = 2;
    ai->turnLeft_2C = 0x745;
check:
    if (ai->turnDir_28)
    {
    turn:
        TurnActorBy_8001DD44(ai->actor_8, ai->turnDir_28, 0x800, 0x40);
        return;
    }
    step = 0x40;
    if (IsInFrontHalf_800A4884((Vec3i*)ai->actor_8->pos_38, ai->actor_8->rot_5C, &levantPos_8008BD18.pos))
    {
        step = 0x80;
    }
    TurnActorTowards_8001DDFC(ai->actor_8, (VECTOR*)&levantPos_8008BD18.pos, step);
}

void EnemyAiWanderStep_800A46FC(GameAi* ai)
{
    int dir;
    if (ai->turnLeft_2C)
    {
        ai->turnLeft_2C = TurnActorBy_8001DD44(ai->actor_8, ai->turnDir_28, ai->turnLeft_2C, 0x20);
    }
    else
    {
        dir = FindActorInFront_8001DECC(ai->actor_8, 0x190, 0);
        ai->turnDir_28 = dir;
        if (dir == 3)
        {
            ai->turnDir_28 = 2;
            ai->turnLeft_2C = 0x745;
        }
        else if ((unsigned)(dir - 1) < 2)
        {
            ai->turnLeft_2C = 0x1e1;
        }
        else
        {
            dir = ai->actor_8->ground_80;
            ai->turnDir_28 = dir;
            if (dir == 3)
            {
                ai->turnDir_28 = 2;
                ai->turnLeft_2C = 0x745;
            }
            else if ((unsigned)(dir - 1) < 2)
            {
                ai->turnLeft_2C = 0x100;
            }
        }
    }
}

void ReflectPoint_800A47B8(Vec3i* center, Vec3i* point, Vec3i* out)
{
    int d;
    d = point->x - center->x;
    out->x = point->x + d;
    d = point->y - center->y;
    out->y = point->y + d;
    d = point->z - center->z;
    out->z = point->z + d;
}

// Matched
int EnemyAiCheckBlocked_800A4804(GameAi* ai)
{
    int dir = FindActorInFront_8001DECC(ai->actor_8, 0x190, 0);
    if (dir == 0)
    {
        dir = ai->actor_8->ground_80;
    }
    if (dir != 0)
    {
        if (dir == 1)
        {
            ai->turnDir_28 = 1;
        }
        else
        {
            ai->turnDir_28 = 2;
        }
        if (dir == 3)
        {
            ai->timer_24 = 0x745;
        }
        else
        {
            ai->timer_24 = 0x1e1;
        }
    }
    return 0;
}

// Matched
int IsInFrontHalf_800A4884(Vec3i* from, short* rot, Vec3i* to)
{
    int ang = ratan2_8003B548(from->x - to->x, from->z - to->z);
    return sinTable_80084540[(ang - rot[1] + 0x400) & 0xfff] >= 0;
}

// Matched
int TurnStepForAngle_800A48F4(int angle)
{
    int step = 0x20;
    if (angle > 0x800)
    {
        step = 0x100;
    }
    else if (angle > 0x400)
    {
        step = 0x80;
    }
    else if (angle > 0x200)
    {
        step = 0x40;
    }
    else if (angle < 0x101)
    {
        step = 0x10;
    }
    return step;
}

void ClearEncounterGroupFlags_800A4940(int group, int encIndex)
{
    unsigned short* flags;
    if (unknownFlags_8008D678 & 0x20000)
    {
        flags = sub_800B322C();
    }
    else
    {
        flags = GetMapEncounterFlags_800A53CC();
        if (flags)
        {
            flags += encIndex;
        }
    }
    if (flags)
    {
        *flags &= ~(0x1f << (group * 5));
    }
}

void RollEncounterGroup_800A4DD0(int a, int b, MapList16* c, GameSpawnEntry* p, GameSpawnOut* e, unsigned short* f);

// Rolls the encounter groups for an encounter index/entrance into out (members + places), returns how many were rolled.
// The early exits are 'goto end' to the single final 'return count' (separate 'return count's add refs to count and
// flip its global-alloc priority against the out->members_0 giv).
// Matched
int RollEncounterGroups_800A49CC(int encIndex, int entrance, MapList16* groups, GameSpawnOut* out)
{
    int count;
    unsigned short* flags;
    unsigned short* flagTbl;
    int i;
    GameSpawnEntry* tbl;
    int idx;
    int bits;
    int j;
    int k;
    GameSpawnMember* members;
    GameSpawnEntry* ent;
    count = 0;
    flags = 0;
    if (unknownFlags_8008D678 & 0x20000)
    {
        flags = sub_800B322C();
    }
    else
    {
        flagTbl = GetMapEncounterFlags_800A53CC();
        if (flagTbl != 0)
        {
            flags = flagTbl + encIndex;
        }
    }
    if (flags == 0)
    {
        goto end;
    }
    {
        int n;
        for (n = 0; n < 3; n++)
        {
            out->members_0[n] = 0;
            out->places_C[n] = 0;
        }
    }
    tbl = 0;
    if (unknownFlags_8008D678 & 0x20000)
    {
        tbl = sub_800B2B40();
    }
    else
    {
        idx = FindInLists_800A52EC(encounterMapLists_800AE9DC, 0x49, entrance);
        if (idx >= 0)
        {
            tbl = encounterTables_800AE524[idx];
        }
    }
    if (tbl == 0)
    {
        goto end;
    }
    if (*flags & 0x8000)
    {
        *flags &= 0x7FFF;
        for (i = 0; i < groups->count_0 && i < 3; i++)
        {
            RollEncounterGroup_800A4DD0(count, i, groups, tbl, out, flags);
            count++;
        }
    }
    else if (*flags == 0)
    {
        if (groups->count_0 == 0)
        {
            goto end;
        }
        if (rand() % 3 == 0)
        {
            goto end;
        }
        if (groups->count_0 < 3)
        {
            k = rand() % groups->count_0;
        }
        else
        {
            k = rand() % 3;
        }
        RollEncounterGroup_800A4DD0(count, k, groups, tbl, out, flags);
        count++;
    }
    else
    {
        bits = *flags;
        for (j = 0; j < 3; bits >>= 5, j++)
        {
            if (bits & 0x10)
            {
                ent = &tbl[bits & 3];
                encounterGroups_800AEB00[j][0].species_0 = encounterSpecies_800AEB6C[ent->species0];
                encounterGroups_800AEB00[j][1].species_0 = encounterSpecies_800AEB6C[ent->species1];
                encounterGroups_800AEB00[j][2].species_0 = encounterSpecies_800AEB6C[ent->species2];
                encounterGroups_800AEB00[j][0].f4 = ent->v0 << 26;
                encounterGroups_800AEB00[j][1].f4 = ent->v1 << 26;
                encounterGroups_800AEB00[j][2].f4 = ent->v2 << 26;
                if (unknownFlags_8008D678 & 0x20000)
                {
                    int lv = (sub_800B330C() - 1) / 4 + 1;
                    if (lv >= 8)
                    {
                        lv = 7;
                    }
                    encounterGroups_800AEB00[j][0].f4 = (ent->v0 + lv) << 26;
                    encounterGroups_800AEB00[j][1].f4 = (ent->v1 + lv) << 26;
                    encounterGroups_800AEB00[j][2].f4 = (ent->v2 + lv) << 26;
                }
                out->members_0[count] = encounterGroups_800AEB00[j];
                out->places_C[count] = &groups->items_4[j];
                count++;
            }
        }
    }
end:
    return count;
}

// rolls one encounter group: picks a GameSpawnEntry by chance, fills encounterGroups_800AEB00[group] and records it in out and *flags
// Matched
void RollEncounterGroup_800A4DD0(int outIdx, int group, MapList16* groups, GameSpawnEntry* tbl, GameSpawnOut* out, unsigned short* flags)
{
    int roll = rand() % 16;
    int i;
    int unkFlags;
    int k;
    GameSpawnMember (*grp)[3];
    GameSpawnMember* members;
    grp = encounterGroups_800AEB00;
    unkFlags = unknownFlags_8008D678;
    i = 0;
    members = grp[group];
    for (; i < 3; i++)
    {
        if (roll < tbl[i].chance)
        {
            members[0].species_0 = encounterSpecies_800AEB6C[tbl[i].species0];
            members[1].species_0 = encounterSpecies_800AEB6C[tbl[i].species1];
            members[2].species_0 = encounterSpecies_800AEB6C[tbl[i].species2];
            members[0].f4 = tbl[i].v0 << 26;
            members[1].f4 = tbl[i].v1 << 26;
            members[2].f4 = tbl[i].v2 << 26;
            if (unknownFlags_8008D678 & 0x20000)
            {
                k = (sub_800B330C() - 1) / 4 + 1;
                if (k >= 8)
                {
                    k = 7;
                }
                members[0].f4 = (tbl[i].v0 + k) << 26;
                members[1].f4 = (tbl[i].v1 + k) << 26;
                members[2].f4 = (tbl[i].v2 + k) << 26;
            }
            {
                unsigned short bits = i | 0x10;
                out->members_0[outIdx] = members;
                out->places_C[outIdx] = &groups->items_4[group];
                *flags |= bits << (group * 5);
            }
            return;
        }
        roll -= tbl[i].chance;
    }
}

int* SelectEncounterSpecies_800A5030(int entrance, int prevEntrance, int force)
{
    int* src = 0;
    int* result = 0;
    int i;
    short variant;
    int j;
    if (unknownFlags_8008D678 & 0x20000)
    {
        src = sub_800B3198();
        if (src != 0)
        {
            if (encounterSpecies_800AEB6C[0] == src[0] && encounterSpecies_800AEB6C[1] == src[1] && encounterSpecies_800AEB6C[2] == src[2])
            {
                src = 0;
            }
            if (src != 0)
            {
                encounterSpecies_800AEB6C[0] = src[0];
                encounterSpecies_800AEB6C[1] = src[1];
                encounterSpecies_800AEB6C[2] = src[2];
                encounterSpecies_800AEB6C[3] = 0xd3;
            }
        }
    }
    else
    {
        if (IsOtherEncounterArea_800A5240(entrance, prevEntrance))
        {
            force = 1;
        }
        if (force == 1)
        {
            i = FindInLists_800A52EC(encounterAreaMaps_800AE3D0, 0x11, entrance);
            if (i >= 0)
            {
                src = encounterAreaSpecies_800AE4E0[i];
                if (src != 0)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (ELEM(src[j]) != -1 && encounterVariantToggle_8008B554 == 0)
                        {
                            variant = (ELEM(src[j]) + 1) % 4;
                            encounterSpecies_800AEB6C[j] = src[j] * 4 + variant + 0x39;
                        }
                        else
                        {
                            encounterSpecies_800AEB6C[j] = src[j];
                        }
                    }
                    encounterSpecies_800AEB6C[3] = 0xd3;
                    encounterVariantToggle_8008B554 = encounterVariantToggle_8008B554 == 0;
                }
            }
        }
    }
    if (src)
    {
        result = encounterSpecies_800AEB6C;
    }
    return result;
}

// Matched
int IsOtherEncounterArea_800A5240(int entrance, int prevEntrance)
{
    if (prevEntrance != -1)
    {
        return FindInLists_800A52EC(encounterAreaMaps_800AE3D0, 0x11, entrance) != FindInLists_800A52EC(encounterAreaMaps_800AE3D0, 0x11, prevEntrance);
    }
    return 1;
}

// Matched
void SetBattleStageForMap_800A52AC(int entrance)
{
    int stage = FindInLists_800A52EC(battleStageMaps_800AE254, 0x27, entrance);
    if (stage < 0)
    {
        stage = 0;
    }
    SetBattleStageId_80039FA4(stage);
}

// Matched
int FindInLists_800A52EC(short** tab, int count, int key)
{
    int found = -1;
    int i;
    for (i = 0; i < count; i++)
    {
        short* list = tab[i];
        while (*list != -1)
        {
            if (key == *list)
            {
                found = i;
                goto done;
            }
            list++;
        }
    }
done:
    return found;
}

// Matched
int GetSpecialStageIndex_800A5354(void)
{
    int idx = -1;
    switch (GetBattleStageId_80039FB0())
    {
    case 0xf:
        idx = 0;
        break;
    case 0x10:
        idx = 1;
        break;
    case 0x11:
        idx = 2;
        break;
    }
    return idx;
}

// Matched
unsigned short* GetMapEncounterFlags_800A53CC(void)
{
    SaveData* sd = &saveData_8008B570;
    unsigned short* flags = 0;
    if (sd->mapId_2E4[0].field_0 == 4)
    {
        if (sd->mapId_2E4[1].field_0 == 1)
        {
            flags = sd->tbl_838;
        }
        else if (sd->mapId_2E4[1].field_0 == 2)
        {
            flags = sd->tbl_850;
        }
        else if (sd->mapId_2E4[1].field_0 == 3)
        {
            flags = sd->tbl_874;
        }
        else if (sd->mapId_2E4[1].field_0 == 4)
        {
            flags = sd->tbl_8CC;
        }
    }
    else if (sd->mapId_2E4[0].field_0 == 5)
    {
        if (sd->mapId_2E4[1].field_0 == 1)
        {
            flags = sd->tbl_8F8;
        }
        else if (sd->mapId_2E4[1].field_0 == 2)
        {
            flags = sd->tbl_90C;
        }
        else if (sd->mapId_2E4[1].field_0 == 3)
        {
            flags = sd->tbl_92C;
        }
    }
    return flags;
}

// Matched
void ClearEncounterSpecies_800A5474(void)
{
    int i;
    int v = 0xd3;
    for (i = 3; i >= 0; i--)
    {
        encounterSpecies_800AEB6C[i] = v;
    }
}

void FreeAllEventData_800A54A0(void)
{
    if (mdecBufferMode_800AEB7C != 2)
        FreeMdecBuffer_800A5854();
    if (eventEffects_800AEB80[1])
        ListFreeAll_8003FEC8(&eventEffects_800AEB80[1]);
    if (eventReloc_800AEBBC)
    {
        ListFree_8003FE38(&eventHeap_80091C10, eventReloc_800AEBBC);
        eventReloc_800AEBBC = 0;
    }
    if (eventTiy_800AEBC0[0])
    {
        ListFree_8003FE38(&eventHeap_80091C10, eventTiy_800AEBC0[0]);
        eventTiy_800AEBC0[0] = 0;
    }
    if (eventTiy_800AEBC0[1])
    {
        ListFree_8003FE38(&eventHeap_80091C10, eventTiy_800AEBC0[1]);
        eventTiy_800AEBC0[1] = 0;
    }
    if (eventDataBuf_800AEBC8)
    {
        ListFree_8003FE38(&eventHeap_80091C10, eventDataBuf_800AEBC8);
        eventDataBuf_800AEBC8 = 0;
    }
    if (eventRecords_800AEBCC[1])
    {
        FreeRecordTables_80026DE8(&eventRecords_800AEBCC[1], eventRecords_800AEBCC[0], (int)&eventHeap_80091C10);
        eventRecords_800AEBCC[0] = 0;
    }
}
