// GAME.BIN, source file 1 of 3
#include "game.h"

INCLUDE_OVERLAY_ASM(game, dword_800A05A0);

// Matched
void sub_800A096C(void)
{
    unknownFlags_8008D678 |= 0x8000;
}

// Matched
void sub_800A0988(void)
{
    *(unsigned short*)dword_800B1DBC->entry.buffer |= 1;
}

// Matched
void sub_800A09B0(void)
{
    *(unsigned short*)dword_800B1DBC->entry.buffer &= 0xFFFE;
}

// Matched
void sub_800A09D8(GameTask_1* t, short* q)
{
    *q = 0;
    t->next_8 = sub_800A0A04;
    sub_800A0A04(t, q);
}

// Not C: calls sub_800A0A5C with $sp moved to the scratchpad (0x1F8003FC), an inline-asm stack switch
INCLUDE_OVERLAY_ASM(game, sub_800A0A04);

#if 0
// Not matched: register pressure / spills differ (the original spills the cell pointer and u0 + 31, keeps 0xFFFFFF hoisted; here the tpage value spills); logic complete.
// Draws the map's animated tile layers (dword_8008D648.lists_14): steps each layer's frame timer, then builds a
// zoomed POLY_FT4 (or, unzoomed, a SPRT + DR_TPAGE) for every 32x32 cell of the frame's tile set.
// Runs on the scratchpad stack (sub_800A0A04); *q & 1 freezes the timers.
void sub_800A0A5C(short* q)
{
    TileAnimScratch* s = TILE_ANIM_SCRATCH;
    struct_8_4b* list;
    struct_2s* st;
    unsigned short* cells;
    int z;
    int n;
    int k;
    int v;
    int t;
    int u;
    int w;
    int b;
    setPolyFT4(&s->ft4_4);
    setSprt(&s->sprt_2C);
    setDrawTPage(&s->tpage_40, 0, 1, 0);
    s->zoom_54 = cameraZoom_8008B4F8;
    s->cx_50 = stru_8008D420.x + stru_8008D420.w / 2;
    s->cy_52 = stru_8008D420.y + stru_8008D420.h / 2;
    s->ox_58 = screenOffset_8008D474.a + (display_8008B4D8.field_C_w / 2 - (stru_8008D420.x + stru_8008D420.w / 2));
    s->oy_5C = screenOffset_8008D474.b + (display_8008B4D8.field_E_h / 2 - (stru_8008D420.y + stru_8008D420.h / 2));
    b = (sceneBrightness_8008D40C << 7) >> 12;
    s->ft4_4.r0 = b;
    s->ft4_4.g0 = b;
    s->ft4_4.b0 = b;
    s->sprt_2C.r0 = b;
    s->sprt_2C.g0 = b;
    s->sprt_2C.b0 = b;
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
    for (s->i_0 = 0; s->i_0 < dword_8008D648.listCount_10; s->i_0++)
    {
        list = &dword_8008D648.lists_14[s->i_0];
        st = &dword_8008D648.pairs_18[s->i_0];
        if (list->count >= 2)
        {
            if (!(*q & 1))
            {
                st->a++;
            }
            if ((unsigned short)st->a >= (list->items[(unsigned short)st->b].c & 0x7F))
            {
                st->b++;
                if ((unsigned short)st->b >= list->count)
                {
                    st->b = 0;
                }
                st->a = 0;
            }
        }
        s->set_70 = list->items[(unsigned short)st->b].a;
        s->clut_74 = list->items[(unsigned short)st->b].b;
        s->time_78 = list->items[(unsigned short)st->b].c & 0x7F;
        s->tiles_60 = dword_8008D648.items_C[s->set_70];
        cells = s->tiles_60.items;
        if (list->items[(unsigned short)st->b].c & 0x80)
        {
            setSemiTrans(&s->ft4_4, 1);
            setSemiTrans(&s->sprt_2C, 1);
        }
        else
        {
            setSemiTrans(&s->ft4_4, 0);
            setSemiTrans(&s->sprt_2C, 0);
        }
        z = ((dword_8008D648.field_4 +
              (unsigned int)((dword_8008D648.field_8 - dword_8008D648.field_4) * (0xFF - s->tiles_60.field_0)) / 0xFF) >>
             4) &
            0x3FF;
        s->ft4_4.clut = (s->clut_74 + 0x1F0) << 6;
        for (k = 0, n = 0; k < s->tiles_60.count; k++)
        {
            v = (short)cells[k];
            if (v & 0x8000)
            {
                n += v & 0x7FFF;
                continue;
            }
            t = v / 8;
            s->x0_48 = (n % (short)s->tiles_60.field_8) * 32 - (short)s->tiles_60.field_8 * 16;
            s->ft4_4.tpage = (((t + 20) / 4) & 0xF) | 0xA0;
            s->y0_4A = (n / (short)s->tiles_60.field_8) * 32 - (short)s->tiles_60.field_A * 16;
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
                u = ((t * 16 + 0x140) % 64) * 2;
                w = (v % 32) * 32;
                s->ft4_4.x0 = s->x0_48;
                s->ft4_4.u0 = u;
                s->ft4_4.v0 = w;
                s->ft4_4.u2 = u;
                s->ft4_4.v1 = w;
                s->ft4_4.v2 = w + 31;
                s->ft4_4.u1 = u + 31;
                s->ft4_4.y0 = s->y0_4A;
                s->ft4_4.x1 = s->x1_4C;
                s->ft4_4.y1 = s->y0_4A;
                s->ft4_4.x2 = s->x0_48;
                s->ft4_4.y2 = s->y1_4E;
                s->ft4_4.x3 = s->x1_4C;
                s->ft4_4.y3 = s->y1_4E;
                s->ft4_4.v3 = w + 31;
                s->sprt_2C.w = 32;
                s->sprt_2C.h = 32;
                s->ft4_4.u3 = u + 31;
                s->sprt_2C.x0 = s->x0_48;
                s->sprt_2C.y0 = s->y0_4A;
                setDrawTPage(&s->tpage_40, 0, 1, (((t + 20) / 4) & 0xF) | 0xA0);
                *(int*)&s->sprt_2C.u0 = *(int*)&s->ft4_4.u0;
                if (cameraZoom_8008B4F8 != 0x1000)
                {
                    *(POLY_FT4*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = s->ft4_4;
                    addPrim(&pOT_8008D690[z], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(POLY_FT4);
                }
                else
                {
                    *(SPRT*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = s->sprt_2C;
                    addPrim(&pOT_8008D690[z], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(SPRT);
                    *(DR_TPAGE*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = s->tpage_40;
                    addPrim(&pOT_8008D690[z], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(DR_TPAGE);
                }
            }
            n++;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A0A5C);

void sub_800A1314(GameTask_1* t)
{
    if (CheckEnemyContact_800A19E4() == 1)
        dword_800B1228 |= 0x4000;
    if (dword_800B1228 & 0x4000)
    {
        StartPadVibration_80036528(0, 10);
        SetFadeMode_8001C19C(0, 0x20);
        SetFadeMode_8001C19C(1, 0x20);
        sub_800A6D30(2);
        t->next_8 = sub_800A13B8;
        unknownFlags_8008D678 |= 0x4000000;
    }
}

// Matched
void sub_800A13B8(GameTask_1* t, void** q)
{
    sub_800A895C();
    sub_800A1BD0();
    sub_800A1E98();
    sub_800AC73C();
    FreeLoaderModelAnimSets_80020814();
    SetCameraBattleMode_80037720();
    *q = LoadOverlayIfChanged_80020D1C(1, 6);
    t->next_8 = sub_800A1474;
    StopSoundSeqs_80030D68(dword_80091CE0);
    PlayMusic_800300E0(0, 1);
}

// Matched
void sub_800A1444(void)
{
    FreeActiveOverlay_8002C014();
    FreeSeqSlotSound_80030664();
    FreeStageEffects_80039FC0();
}

// Matched
void sub_800A1474(GameTask_1* t, GameQ_1* q)
{
    if (GetFileRequestStatus_8003BE30(q->req_0) == 0)
    {
        StartSceneFadeOut_8001AA50(1);
        q->f8 = sub_800BA9E4();
        t->next_8 = sub_800BA254;
    }
    eventDispatchHalt_8008B540 = 1;
}

// Matched
void sub_800A14E0(GameTask_1* t, GameQ_1* q)
{
    if (GetFileRequestStatus_8003BE30(q->req_0) == 0)
    {
        sub_800A6D30(0xa);
        q->f8 = sub_800BBB94();
        t->next_8 = sub_800A167C;
        unknownFlags_8008D678 &= ~0x4000000;
        dword_800B1228 &= ~0x4000;
    }
    eventDispatchHalt_8008B540 = 1;
}

void sub_800A1578(GameTask_1* t, int** q)
{
    if ((*q[2] & 0x8001) != 1)
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
        t->next_8 = sub_800A15FC;
    }
}

// Matched
void sub_800A15FC(GameTask_1* t, GameQ_1* q)
{
    if (IsMapLoading_800272D0() == 0)
    {
        sub_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
        t->next_8 = sub_800A167C;
        q->f4 = 2;
        dword_800B1228 &= ~0x4000;
    }
    eventDispatchHalt_8008B540 = 1;
}

// Matched
void sub_800A167C(GameTask_1* t, GameQ_1* q)
{
    q->f4--;
    if (q->f4 <= 0)
    {
        SetFadeMode_8001C19C(3, 0x20);
        t->next_8 = sub_800A1314;
        unknownFlags_8008D678 &= ~0x4000000;
    }
}

// Matched
void sub_800A16DC(GameV3_1* p)
{
    dword_800ADE78.f0 = p->a;
    dword_800ADE78.f4 = p->b;
    dword_800ADE78.f8 = p->c;
    dword_800ADE78.fc = -1;
    dword_800ADE78.f10 = -1;
}

// Matched
void sub_800A170C(void)
{
    GameV6_1 v;
    int i;
    v.a = 0;
    v.b = 0;
    v.c = 0;
    sub_800A16DC((GameV3_1*)&v);
    gCtx_800B1260.f0 = 0;
    gCtx_800B1260.f8 = 0;
    gCtx_800B1260.f40 = 0;
    gCtx_800B1260.f44 = 0;
    for (i = 11; i >= 0; i--)
    {
        gCtx_800B1260.actors_7c[i] = 0;
    }
    gCtx_800B1260.f76c = 0;
    gCtx_800B1260.f770 = 0;
    gCtx_800B1260.f774 = 0;
    gCtx_800B1260.f778 = 0;
    gCtx_800B1260.f77c = 0;
    gCtx_800B1260.f780 = 1;
    gCtx_800B1260.f784 = 1;
    gCtx_800B1260.f3c = 0;
}

// Matched
void sub_800A1794(void)
{
    int i;
    for (i = 2; i >= 0; i--)
    {
        dword_800B19F0[i].f0 = 0;
    }
}

// Matched
GameSlot_1* sub_800A17BC(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0 == 0)
        {
            return &dword_800B19F0[i];
        }
    }
    return 0;
}

// Matched
GameSlot_1* sub_800A17F4(unsigned int* src, GameAi* b)
{
    GameSlot_1* r = sub_800A17BC();
    r->f0 = 1;
    r->f4 = b;
    MemCopy_800403E8(&r->data_8, src, 0xe0);
    return r;
}

// Matched
void sub_800A1850(GameSlot_1* p)
{
    GameAi* q = p->f4;
    Actor* v = q->actor_8;
    p->f0 = 0;
    sub_800A2D28(q);
    DestroyActor_8001D600(v);
}

// Matched
void sub_800A188C(GameSlot_1* p)
{
    GameAi* q = p->f4;
    Actor* v = q->actor_8;
    sub_800A2EC8(q);
    SetActorActive_8001D658(v, 0);
}

// Matched
void sub_800A18C8(GameSlot_1* p)
{
    GameAi* q = p->f4;
    Actor* v = q->actor_8;
    sub_800A2D48(q);
    SetActorActive_8001D658(v, 1);
}

// Matched
void sub_800A1904(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0)
        {
            GameAi* q = dword_800B19F0[i].f4;
            sub_800A2EC8(q);
            SetActorAnimPaused_8001D6EC(q->actor_8, 1);
        }
    }
}

// Matched
void sub_800A1974(void)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0)
        {
            GameAi* q = dword_800B19F0[i].f4;
            sub_800A2D48(q);
            SetActorAnimPaused_8001D6EC(q->actor_8, 0);
        }
    }
}

int CheckEnemyContact_800A19E4(void)
{
    int i;
    GameSlot_1* s;
    GameAi* o;
    unsigned int d;
    int r;
    if (sub_800A5F6C())
    {
        return 1;
    }
    if (dword_800B0EC0 != 1)
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
    if (sub_800A5E68())
    {
        return 0;
    }
    for (i = 0, s = dword_800B19F0; i < 3; i++, s++)
    {
        if (s->f0)
        {
            o = s->f4;
            d = 0xfff;
            if (IsWithinDistance_8003B740(o->actor_8->pos_38, &levantPos_8008BD18.pos.x, &d) == 1)
            {
                r = o->actor_8->baseScale_138[2] * 400 / 4096;
                if (d < r * r)
                {
                    dword_800B1264 = (int*)s;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Matched
int sub_800A1B2C(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.f40; i++)
    {
        if (gCtx_800B1260.f4c[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Matched
void sub_800A1B78(void)
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

extern int dword_800B1CA8;
extern int name_8007A024[];
#if 0
// Not matched: 1 word short: the original loads maxCount_4 into $v0 and copies it to n (move $a0,$v0), keeps &gCtx in $a1 (here $a2) and stores dword_800B1CA8 before the f788/f0/f48 stores (here it sinks into the epilogue); everything up to there matches
void sub_800A1BD0(void)
{
    GameEnemy* e = sub_800A5F6C();
    int found;
    Actor* o;
    GameSlot_1* slot;
    GameSlot_1* s;
    int* t;
    GameAi* obj;
    int done;
    int i;
    int n;
    GameSlot_1* p;
    GameSlot_1* q;
    GameCtx_1* g;
    if (e)
    {
        o = e->actors_A4[0];
        e->actors_A4[0] = CloneActor_8001D4DC(o, 0, 0, 0);
        slot = sub_800A17F4((unsigned int*)e, 0);
        slot->f4 = CreateEnemyAiEvent_800A2D90(e->actors_A4[0], &slot->data_8.minion_1C, 0);
        SetActorVisible_8001D730(o, 0);
        SetActorGroundMove_8001D68C(o, 0);
        dword_800B1264 = (int*)slot;
    }
    found = 0;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0)
        {
            s = &dword_800B19F0[i];
            slot = s;
            done = 0;
            t = s->data_8.anims_C8[0];
            obj = s->f4;
            t = t ? t : name_8007A024;
            if (!found && gCtx_800B1260.f4 == s)
            {
                sub_800A2EC8(obj);
                StartActorScript_8001DC34(obj->actor_8, (void*)t[0]);
                found = 1;
                done = found;
                gCtx_800B1260.f4 = s;
            }
            if (!done)
            {
                sub_800A2EC8(obj);
                StartActorScript_8001DC34(obj->actor_8, (void*)t[1]);
                gCtx_800B1260.fc[gCtx_800B1260.f8] = slot;
                gCtx_800B1260.f8++;
            }
        }
    }
    g = &gCtx_800B1260;
    p = (GameSlot_1*)g->f4;
    for (i = 0; i < 3; i++)
    {
        if ((unsigned)p->data_8.members_B0[i].species_0 >= 0xd3)
        {
            break;
        }
    }
    n = p->data_8.maxCount_4;
    if (n >= i)
    {
        n = i;
    }
    g->f76c = n;
    g->f770 = i;
    q = (GameSlot_1*)g->f4;
    g->f774 = q->data_8.kind_0 == 0;
    g->f77c = 0;
    g->f778 = q->data_8.kind_0 == 1;
    g->f780 = q->data_8.f8;
    g->f784 = q->data_8.fC;
    g->f788 = q->data_8.f10;
    dword_800B1CA8 = 0;
    gCtx_800B1260.f0 = 1;
    g->f48 = q->data_8.f14;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A1BD0);

// Matched
void sub_800A1E1C(void)
{
    sub_800A170C();
}

// Matched
char* sub_800A1E3C(void)
{
    return dword_800B19CC;
}

// Matched
int* sub_800A1E48(void)
{
    return gCtx_800B1260.f4->f4->actor_8->pos_38;
}

// Matched
short* sub_800A1E68(void)
{
    return gCtx_800B1260.f4->f4->actor_8->rot_5C;
}

// Matched
void sub_800A1E88(void)
{
}

// Matched
int sub_800A1E90(void)
{
    return 1;
}

// Matched
void sub_800A1E98(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.f8; i++)
    {
        sub_800A188C(gCtx_800B1260.fc[i]);
    }
    sub_800A7B00(-1);
}

// Matched
void sub_800A1F0C(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.f8; i++)
    {
        sub_800A18C8(gCtx_800B1260.fc[i]);
    }
    sub_800A7BF0(-1);
}

// Matched
void sub_800A1F80(void)
{
    ActorDesc s;
    int v[3];
    GameCtx_1* g;
    GameSlot_1* h;
    int n;
    short* offs;
    int i;
    int k;
    Model* m;
    Actor* a;
    MinionModelDesc* d;
    int* p0;
    int* p1;
    int f;
    g = &gCtx_800B1260;
    n = g->f770;
    h = g->f4;
    if (g->f76c < n)
    {
        offs = dword_800ADE9C[g->f76c - 1];
    }
    else
    {
        offs = dword_800ADE9C[n - 1];
    }
    i = 0;
    do
    {
        k = 0;
        if (i == 0 && h->data_8.useMinion_18 == 1)
        {
            MemCopy_800403E8((unsigned int*)&gCtx_800B1260.ents_ac[gCtx_800B1260.f40], (unsigned int*)&h->data_8.minion_1C, sizeof(UnitStats));
        }
        else
        {
            k = InitMinionData_8001900C(&gCtx_800B1260.ents_ac[gCtx_800B1260.f40], &h->data_8.members_B0[i].species_0);
        }
        if (h->data_8.kind_0 == 0 || h->data_8.actors_A4[i] != 0)
        {
            a = CloneActor_8001D4DC(h->data_8.actors_A4[i], 1, i, 1);
            if (h->data_8.kind_0 == 1)
            {
                SetActorVisible_8001D730(a, 1);
            }
        }
        else
        {
            d = GetSpeciesModelDesc_80019C70(h->data_8.members_B0[i].species_0);
            m = AcquireLoaderModel_80020734(d->modelId_0);
            s.modelId_0 = d->modelId_0;
            s.kind_4 = 1;
            s.pos_8[0] = 0;
            s.pos_8[1] = 0;
            s.pos_8[2] = 0;
            s.rot_14[0] = 0;
            s.rot_14[1] = 0;
            s.rot_14[2] = 0;
            s.clutRow_1C = i;
            s.animIdx_20 = 4;
            s.frame_24 = -3;
            s.frameSpeed_28 = 0x1000;
            s.blendDiv_2C = 4;
            s.visible_30 = 1;
            s.bones_34 = defaultBones_80079140;
            if (k >= 4)
            {
                s.baseScale_38 = (int*)GetModelBaseScale_80024E90(m, k);
            }
            else
            {
                p0 = (int*)GetModelBaseScale_80024E90(m, k);
                p1 = (int*)GetModelBaseScale_80024E90(m, k + 1);
                f = GetUnitRank_80019AD0(&gCtx_800B1260.ents_ac[gCtx_800B1260.f40]);
                f = ((p1[0] - p0[0]) * f) / 4096;
                v[0] = p0[0] + f;
                v[1] = p0[1] + f;
                v[2] = p0[2] + f;
                s.baseScale_38 = v;
            }
            s.boneScale_3C = (SVECTOR*)GetModelBoneScale_80024EC8(m, k);
            s.anims_40 = (ActorAnim*)GetModelActorAnims_80024E38(m);
            s.effectTbl_44 = (short (*)[6])GetModelEffectTable_80024E64(m);
            s.hasMatrices_4C = 1;
            a = CreateActor_8001D45C(&s);
            SetBoneGroupFlags_80019B14(a->bones_134, (unsigned short*)sub_80024F00(m, k), (unsigned short*)sub_80024F38(m, k));
        }
        a->pos_38[0] = saveData_8008B570.levant_7A8.pos.x + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + offs[i % gCtx_800B1260.f76c]) & 0xfff] * 1000 / 4096;
        a->pos_38[1] = saveData_8008B570.levant_7A8.pos.y;
        a->pos_38[2] = saveData_8008B570.levant_7A8.pos.z + sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + offs[i % gCtx_800B1260.f76c] + 0x400) & 0xfff] * 1000 / 4096;
        a->rot_5C[0] = 0;
        a->prevPos_44[0] = a->pos_38[0];
        a->prevPos_44[1] = a->pos_38[1];
        a->prevPos_44[2] = a->pos_38[2];
        a->basePos_50[0] = a->pos_38[0];
        a->basePos_50[1] = a->pos_38[1];
        a->basePos_50[2] = a->pos_38[2];
        a->rot_5C[1] = ratan2_8003B548(saveData_8008B570.levant_7A8.pos.x - a->pos_38[0], saveData_8008B570.levant_7A8.pos.z - a->pos_38[2]);
        a->rot_5C[2] = 0;
        SetActorGroundMove_8001D68C(a, 0);
        gCtx_800B1260.actors_7c[gCtx_800B1260.f40] = a;
        gCtx_800B1260.f4c[gCtx_800B1260.f40] = i >= gCtx_800B1260.f76c;
        gCtx_800B1260.f70c[gCtx_800B1260.f40] = (int)h->data_8.anims_C8[i];
        gCtx_800B1260.f73c[gCtx_800B1260.f40] = h->data_8.fD4[i];
        i++;
        gCtx_800B1260.f40++;
        gCtx_800B1260.f44++;
    } while (i < n);
    sub_800A1850(h);
}

// Matched
int sub_800A248C(void)
{
    int mask = 0;
    int i;
    for (i = 0; i < gCtx_800B1260.f40; i++)
    {
        if (gCtx_800B1260.actors_7c[i] && gCtx_800B1260.f4c[i] == 0)
        {
            mask |= 1 << (i + 4);
        }
    }
    return mask;
}

// Matched
int sub_800A24F4(int a)
{
    sub_800A2CA8(a, 0);
    if (gCtx_800B1260.actors_7c[a] != 0)
    {
        if (gCtx_800B1260.f4c[a] == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Matched
int sub_800A2550(int a)
{
    sub_800A2CA8(a, 0);
    return sub_8001E1C8(gCtx_800B1260.actors_7c[a]);
}

// Matched
int sub_800A2594(int a)
{
    sub_800A2CA8(a, 0);
    return sub_8001E1DC(gCtx_800B1260.actors_7c[a]);
}

// Matched
int sub_800A25D8(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

// Matched
int sub_800A25F8(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

// Matched
int sub_800A2618(void* x, int n)
{
    sub_800A2CA8(n, 0);
    sub_800C4118(x, &gCtx_800B1260.ents_ac[n], n, gCtx_800B1260.f73c[n]);
    return 1;
}

#if 0
// Not matched: hidden return pointer gets $s6 instead of $s3 (and 'move $v0' is placed before the final struct copy); tried explicit out pointer, void, do-while, goto
typedef struct GamePair_1
{
    short a;
    short b;
} GamePair_1;
typedef struct GameCtxA_1
{
    char pad_0[0x7c];
    int obj_7c[3];
    char pad_88[0x70c - 0x88];
    int f70c[3];
} GameCtxA_1;
extern void* memset(void* p, int c, unsigned int n);
extern GamePair_1 StartCommandAction_80018A4C(int obj, int* p, int a2, int c);
GamePair_1 sub_800A2684(int* p, int c)
{
    GamePair_1 r;
    int i;
    memset(&r, 0, 4);
    if (p[0] != 0x14)
    {
        for (i = 4; i < 7; i++)
        {
            if (((unsigned)p[2] & (1 << i)) != 0)
            {
                r = StartCommandAction_80018A4C(((GameCtxA_1*)&gCtx_800B1260)->obj_7c[i - 4], p, ((GameCtxA_1*)&gCtx_800B1260)->f70c[i - 4], c);
            }
        }
    }
    return r;
}
#endif

INCLUDE_OVERLAY_ASM(game, sub_800A2684);

// Matched
int sub_800A2760(unsigned int* p)
{
    int i;
    if (p[0] == 0x14)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        if (p[2] & (1 << i))
        {
            TriggerActorEffect_8001E28C(gCtx_800B1260.actors_7c[i - 4]);
        }
    }
    return 1;
}

// Matched
void sub_800A27FC(int a, int b)
{
    sub_800A2CA8(a, 0);
    GetActorHitFrame_80018E5C(gCtx_800B1260.actors_7c[a], b);
}

// Matched
void sub_800A284C(int a)
{
    sub_800A2CA8(a, 0);
    {
        UnitStatus* v = sub_800A2B60(a);
        SetActorStatusTint_80018EBC(gCtx_800B1260.actors_7c[a], v);
    }
}

// Matched
int sub_800A2898(int a)
{
    sub_800A2CA8(a, 0);
    return AddItem_80010650(&gCtx_800B1260.ents_ac[a]);
}

// Matched
int sub_800A28DC(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

// Matched
int sub_800A28FC(int a)
{
    sub_800A2CA8(a, 0);
    return dword_800B19E0;
}

// Matched
void sub_800A2924(int a)
{
    sub_800A2CA8(a, 0);
    gCtx_800B1260.f4c[a] = 1;
    if (--gCtx_800B1260.f44 == 0)
    {
        int x = gCtx_800B1260.f48;
        if (x >= 0)
        {
            SaveData* sd = &saveData_8008B570;
            sub_800A4940(x, mapTable_800B0608[sd->mapId_2E4[0].field_0][sd->mapId_2E4[1].field_0][sd->mapId_2E4[2].field_0].f4);
        }
    }
}

// Matched
void sub_800A29CC(int a, EffectTarget* out)
{
    sub_800A2CA8(a, 0);
    {
        Actor* e = gCtx_800B1260.actors_7c[a];
        out->tbl_0 = e->effectTbl_14C;
        out->pos_4 = e->pos_38;
        out->bonePos_8 = e->bonePos_1C4;
        out->boneMatrices_C = e->boneMatrices_1C8;
        out->boneScale_2C = e->boneScale_144;
        out->scale_30 = e->scale_2C;
    }
}

// Matched
int sub_800A2A50(int a)
{
    sub_800A2CA8(a, 0);
    return 0;
}

// Matched
int sub_800A2A70(int a)
{
    sub_800A2CA8(a, 0);
    {
        UnitStats* e = &gCtx_800B1260.ents_ac[a];
        return (int)&e->magicBits_80;
    }
}

// Matched
int sub_800A2AB4(void)
{
    GameCtx_1* c = &gCtx_800B1260;
    if (c->f774 != 0)
    {
        if (c->f3c == 0)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

// Matched
void sub_800A2AE8(void)
{
    if (gCtx_800B1260.f3c == 0)
    {
        gCtx_800B1260.f4c[0] = 1;
        gCtx_800B1260.f4c[1] = 0;
        gCtx_800B1260.f3c = 1;
    }
    else
    {
        gCtx_800B1260.f4c[0] = 0;
        gCtx_800B1260.f4c[1] = 1;
        gCtx_800B1260.f3c = 0;
    }
}

// Matched
UnitStats* sub_800A2B20(int a)
{
    sub_800A2CA8(a, 0);
    return &gCtx_800B1260.ents_ac[a];
}

// Matched
UnitStatus* sub_800A2B60(int a)
{
    sub_800A2CA8(a, 0);
    return &gCtx_800B1260.ents_ac[a].st_0;
}

// Matched
int sub_800A2BA0(int a)
{
    sub_800A2CA8(a, 0);
    {
        UnitStats* e = &gCtx_800B1260.ents_ac[a];
        return (int)&e->skills_6C;
    }
}

// Matched
int sub_800A2BE4(int a)
{
    sub_800A2CA8(a, 0);
    {
        UnitStats* e = &gCtx_800B1260.ents_ac[a];
        return e->species_5C;
    }
}

// Matched
int* sub_800A2C28(int a)
{
    sub_800A2CA8(a, 0);
    return gCtx_800B1260.actors_7c[a]->pos_38;
}

// Matched
int* sub_800A2C68(int a)
{
    sub_800A2CA8(a, 0);
    return gCtx_800B1260.actors_7c[a]->bonePos_1C4;
}

int sub_800A2CA8(int a, int b)
{
    int ok = 0;
    if (a < 0 || a >= gCtx_800B1260.f40 || gCtx_800B1260.f4c[a] != 0)
    {
        ok = 1;
    }
    if (ok)
    {
        if (!b)
        {
            printf(aAssertionFaile_800A05A4, aFile_800A05CC, 0x512);
            exit(1);
        }
    }
    return ok;
}

// Matched
void sub_800A2D28(GameAi* p)
{
    *p->flags_0 = (*p->flags_0 & ~1) | 0x8000;
}

// Matched
void sub_800A2D48(GameAi* p)
{
    *p->flags_0 &= ~0x8000;
    SetActorAnim_8001D760(p->actor_8, p->anim_20, -1, 0);
}

GameAi* CreateEnemyAiEvent_800A2D90(Actor* a, UnitStats* b, int c)
{
    EventEntry* e = AllocEventEntry_80043AF8(enemyAiTasks_8008D49C);
    GameAi* q;
    int v;
    int k;
    int j;
    if (e != 0)
    {
        q = e->buffer;
        e->flags = (e->flags | 1) & ~0x8000;
        q->flags_0 = &e->flags;
        q->minion_4 = b;
        q->actor_8 = a;
        q->f28 = 0;
        q->timer_24 = 0;
        q->f2c = 0;
        q->anim_20 = -1;
        q->state_c = -1;
        q->f10 = -1;
        if (c == 0)
        {
            e->cb_8 = sub_800A2EE4;
        }
        else
        {
            v = b->species_5C;
            if ((unsigned)v < 0x39)
            {
                j = !(levantCaptureLevel_8008BD7C - b->st_0.level_44 < 5);

                e->cb_8 = name_800ADEB8[v][j];
            }
            else
            {
                k = v;
                if (k >= 0x39)
                {
                    k = (k - 0x39) / 4;
                }
                e->cb_8 = name_800ADEB8[k][0];
            }
        }
        return q;
    }
    return 0;
}

// Matched
void sub_800A2EC8(GameAi* p)
{
    *p->flags_0 |= 0x8000;
}

// Matched
void sub_800A2EE4(EventEntry* e, void* ai)
{
}

void sub_800A2EEC(int unused, GameAi* p)
{
    if (sub_800A4278(p) == 0)
    {
        switch (p->state_c)
        {
        case -1:
            SetActorState_800A433C(p, 5, 2, 0, -1, 1, 2);
            SetActorSpeedScale_8001DB58(p->actor_8, 0x3000, 1);
            break;
        case 5:
            sub_800A459C(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
                p->state_c = -1;
            break;
        }
    }
}

void sub_800A2FB8(int unused, GameAi* p)
{
    if (sub_800A4278(p) == 0)
    {
        if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F && p->state_c != 0xf)
        {
            SetActorState_800A433C(p, 0xf, 2, 0, -1, 1, 2);
            SetActorSpeedScale_8001DB58(p->actor_8, 0x2000, 1);
        }
        switch (p->state_c)
        {
        case -1:
            SetActorState_800A433C(p, 8, 2, (rand() % 16) * 10 + 100, -1, 1, 2);
            break;
        case 8:
            sub_800A46FC(p);
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 1, 1, (rand() % 16) * 10 + 100, -1, 1, 2);
            break;
        case 1:
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 0xe, 2, 0, -1, 1, 2);
            break;
        case 0xe:
            if (sub_800A4470(p) == 0)
                p->state_c = -1;
            break;
        case 0xf:
            sub_800A45F8(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
            {
                p->state_c = -1;
                SetActorSpeedScale_8001DB58(p->actor_8, 0x1000, 1);
            }
            break;
        }
    }
}

void sub_800A31DC(int unused, GameAi* p)
{
    int c;
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 1, 1, 0, c, 1, 2);
            SetActorSpeedScale_8001DB58(p->actor_8, 0x1000, 0);
            break;
        case 1:
            TurnActorTowards_8001DDFC(p->actor_8, &levantPos_8008BD18.pos, 0x155);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
            {
                SetActorState_800A433C(p, 5, 2, 0, -1, c, 2);
                SetActorSpeedScale_8001DB58(p->actor_8, 0x3000, 1);
            }
            break;
        case 5:
            sub_800A459C(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
                q->state_c = -1;
            break;
        }
    }
}

void sub_800A333C(int unused, GameAi* p)
{
    GameAi* q = p;
    int x;
    int c;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 0xd, 0x17, 0, -2, 0, 2);
        case 0xd:
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
            {
                x = sub_800AB39C() & 0xFFFFFFF;
                if (x == 1)
                    SetActorState_800A433C(q, 0xf, 2, 0, -1, x, 2);
            }
            break;
        case 0xf:
            sub_800A45F8(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x1CFDE0)
                SetActorState_800A433C(p, 1, 1, 0x32, -1, 1, 2);
            break;
        case 1:
            if (--q->timer_24 < 0)
                SetActorState_800A433C(q, 0xd, 0x17, 0, -1, c, 2);
            break;
        }
    }
}

void sub_800A34D8(int unused, GameAi* p)
{
    int c;
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 8, 2, (rand() % 16) * 10 + 0x64, c, 1, 2);
            break;
        case 8:
            sub_800A46FC(p);
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 1, 1, (rand() % 16) * 10 + 0x64, -1, 1, 2);
            break;
        case 1:
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 0xe, 2, 0, -1, c, 2);
            break;
        case 0xe:
            if (sub_800A4470(p) == 0)
                q->state_c = -1;
            break;
        }
    }
}

void sub_800A366C(int unused, GameAi* p)
{
    int c;
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 8, 2, (rand() % 16) * 10 + 0x64, c, 1, 2);
            break;
        case 8:
            sub_800A46FC(p);
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 1, 1, (rand() % 16) * 10 + 0x64, -1, 1, 2);
            break;
        case 1:
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 0xe, 2, 0, -1, c, c);
            break;
        case 0xe:
            if (sub_800A4470(p) == 0)
                q->state_c = -1;
            break;
        }
    }
}

void sub_800A3804(int unused, GameAi* p)
{
    int c;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 1, 1, 0, c, 1, 2);
            break;
        case 1:
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
                SetActorState_800A433C(p, 0xa, 4, 0x28, -1, 1, 2);
            break;
        case 0xa:
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 0xf, 2, 0, -1, 1, 2);
            break;
        case 0xf:
            sub_800A45F8(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x1CFDE0)
                p->state_c = -1;
            break;
        }
    }
}

void sub_800A3954(int unused, GameAi* p)
{
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        switch (p->state_c)
        {
        case -1:
            SetActorState_800A433C(p, 0xf, 2, 0, p->state_c, 1, 2);
            break;
        case 0xf:
            sub_800A45F8(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
                SetActorState_800A433C(p, 0xa, 4, 0x46, -1, 1, 2);
            break;
        case 0xa:
            TurnActorTowards_8001DDFC(q->actor_8, &levantPos_8008BD18.pos, 0x155);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18.pos) > 0xDBBA0)
                q->state_c = -1;
            break;
        }
    }
}

void sub_800A3A8C(int unused, GameAi* p)
{
    int c;
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 8, 2, 0, c, 1, 2);
            break;
        case 8:
            sub_800A46FC(p);
            if (sub_800A4804(p))
                SetActorState_800A433C(p, 1, 1, (rand() % 16) * 8 + 0x32, -1, 1, 2);
            break;
        case 1:
            if (--p->timer_24 < 0)
            {
                SetActorState_800A433C(p, 0xe, 1, 0, -1, c, 2);
                sub_800A43FC(p);
            }
            break;
        case 0xe:
            if (sub_800A4470(p) == 0)
                q->state_c = -1;
            break;
        }
    }
}

void sub_800A3BEC(int unused, GameAi* p)
{
    int c;
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 1, 1, (rand() % 16) * 8 + 0x32, c, 1, 2);
            break;
        case 1:
            if (sub_800A4884(&levantPos_8008BD18.pos, &levantPos_8008BD18.rot.vx, (struct_v3*)p->actor_8->pos_38))
                SetActorState_800A433C(p, 0xf, 2, 0, -1, c, 2);
            break;
        case 0xf:
            sub_800A45F8(p);
            if (sub_800A4884(&levantPos_8008BD18.pos, &levantPos_8008BD18.rot.vx, (struct_v3*)p->actor_8->pos_38) == 0)
                q->state_c = -1;
            break;
        }
    }
}

void sub_800A3D24(int unused, GameAi* p)
{
    int c;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 8, 2, 0x14, c, 1, 2);
            break;
        case 8:
            sub_800A46FC(p);
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 1, 1, (rand() % 16) * 8 + 0x32, -1, 1, 2);
            break;
        case 1:
            if (--p->timer_24 < 0)
            {
                SetActorState_800A433C(p, 0xe, 2, 0, -1, c, 2);
                sub_800A43FC(p);
            }
            break;
        case 0xe:
            if (sub_800A4470(p) == 0)
                p->state_c = -1;
            break;
        }
    }
}

void sub_800A3E88(int unused, GameAi* p)
{
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        switch (p->state_c)
        {
        case -1:
            SetActorState_800A433C(p, 0x10, 0x12, 0, p->state_c, 1, 2);
        case 0x10:
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0xDBB9F)
            {
                SetActorState_800A433C(q, 5, 2, 0, -1, 1, 2);
                SetActorSpeedScale_8001DB58(q->actor_8, 0x2000, 1);
            }
            break;
        case 5:
            sub_800A44C0(q);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18.pos) > 0x155CC0)
                q->state_c = -1;
            break;
        }
    }
}

void sub_800A3FC0(int unused, GameAi* p)
{
    int c;
    if (sub_800A4278(p) == 0)
    {
        c = p->state_c;
        switch (c)
        {
        case -1:
            SetActorState_800A433C(p, 8, 2, 0x21, c, 1, 2);
            break;
        case 8:
            sub_800A46FC(p);
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 1, 1, (rand() % 16) * 8 + 0x32, -1, 1, 2);
            break;
        case 1:
            if (--p->timer_24 < 0)
            {
                SetActorState_800A433C(p, 0xe, 2, 0, -1, c, 2);
                sub_800A43FC(p);
            }
            break;
        case 0xe:
            if (sub_800A4470(p) == 0)
                p->state_c = -1;
            break;
        }
    }
}

void sub_800A4124(int unused, GameAi* p)
{
    GameAi* q = p;
    if (sub_800A4278(p) == 0)
    {
        switch (p->state_c)
        {
        case -1:
            SetActorState_800A433C(p, 2, 1, 0, p->state_c, 1, 2);
        case 2:
            SetActorAnimPaused_8001D6EC(q->actor_8, 1);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18.pos) <= 0x61A7F)
                SetActorState_800A433C(q, 0xf, 2, 0, -1, 1, 2);
            break;
        case 0xf:
            sub_800A45F8(q);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18.pos) > 0xDBBA0)
                SetActorState_800A433C(q, 2, 1, 0, -1, 1, 2);
            break;
        }
    }
}

#if 0
// Not matched: first SetActorState_800A433C call: 'move $a0,$s0' / 'move $a1,$v0' swapped (which one fills the beq delay slot)
int sub_800A4278(GameAi* p)
{
    int r;
    int s;
    if (GetSporeMode_80011B6C() == 0)
    {
        s = 0xd;
        if (p->state_c != s)
        {
            SetActorState_800A433C(p, s, 0x17, 0, -1, 1, 2);
        }
        return 1;
    }
    r = GetSporeMode_80011B6C();
    if (r != 1)
        return 0;
    if (p->state_c != 8)
        SetActorState_800A433C(p, 8, 2, 0, -1, r, 2);
    sub_800A45F8(p);
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A4278);

void SetActorState_800A433C(GameAi* p, int state, int anim, int timer, int mode, int flag, int div)
{
    p->state_c = state;
    p->timer_24 = timer;
    p->anim_20 = anim;
    SetActorAnim_8001D760(p->actor_8, anim, mode, flag);
    if (state == 0xe)
    {
        p->f2c = 0x1000 / (rand() % 16) / div;
        p->f28 = (rand() & 1) ? 1 : 2;
    }
}

void sub_800A43FC(GameAi* p)
{
    p->f2c = 0x1000 / (rand() % 16) / 2;
    p->f28 = (rand() & 1) ? 1 : 2;
}

// Matched
int sub_800A4470(GameAi* p)
{
    if (p->f2c)
    {
        p->f2c = TurnActorBy_8001DD44(p->actor_8, p->f28, p->f2c, 0x20);
        RestartActorMotion_8001D71C(p->actor_8);
        return 1;
    }
    return 0;
}

// Matched
void sub_800A44C0(GameAi* p)
{
    GameVec4_1 v;
    GameVec4_1 w;
    int ang;
    int idx;
    sub_800A46FC(p);
    v.x = saveData_8008B570.levant_7A8.pos.x - p->actor_8->pos_38[0];
    v.z = saveData_8008B570.levant_7A8.pos.z - p->actor_8->pos_38[2];
    ang = ratan2_8003B548(v.x, v.z);
    idx = (ang - p->actor_8->rot_5C[1]) & 0xfff;
    w.x = p->actor_8->pos_38[0] + (p->actor_8->pos_38[0] - saveData_8008B570.levant_7A8.pos.x);
    w.z = p->actor_8->pos_38[2] + (p->actor_8->pos_38[2] - saveData_8008B570.levant_7A8.pos.z);
    if (TurnActorTowards_8001DDFC(p->actor_8, (struct_v3*)&w, sub_800A48F4(idx * 3)) == 0)
    {
        RestartActorMotion_8001D71C(p->actor_8);
    }
}

// Matched
void sub_800A459C(GameAi* p)
{
    struct_v3 v;
    ReflectPoint_800A47B8(&levantPos_8008BD18.pos, (struct_v3*)p->actor_8->pos_38, &v);
    if (TurnActorTowards_8001DDFC(p->actor_8, &v, 0x155) == 0)
    {
        RestartActorMotion_8001D71C(p->actor_8);
    }
}

void sub_800A45F8(GameAi* p)
{
    int r;
    int step;
    if (p->f2c)
    {
        p->f2c = TurnActorBy_8001DD44(p->actor_8, p->f28, p->f2c, 0x80);
    }
    r = FindActorInFront_8001DECC(p->actor_8, 0x190, 0);
    p->f28 = r;
    if (r != 3)
    {
        if (r != 0)
        {
            goto turn;
        }
        r = p->actor_8->ground_80;
        p->f28 = r;
        if (r != 3)
        {
            goto check;
        }
    }
    p->f28 = 2;
    p->f2c = 0x745;
check:
    if (p->f28)
    {
    turn:
        TurnActorBy_8001DD44(p->actor_8, p->f28, 0x800, 0x40);
        return;
    }
    step = 0x40;
    if (sub_800A4884((struct_v3*)p->actor_8->pos_38, p->actor_8->rot_5C, &levantPos_8008BD18.pos))
    {
        step = 0x80;
    }
    TurnActorTowards_8001DDFC(p->actor_8, (VECTOR*)&levantPos_8008BD18.pos, step);
}

void sub_800A46FC(GameAi* p)
{
    int r;
    if (p->f2c)
    {
        p->f2c = TurnActorBy_8001DD44(p->actor_8, p->f28, p->f2c, 0x20);
    }
    else
    {
        r = FindActorInFront_8001DECC(p->actor_8, 0x190, 0);
        p->f28 = r;
        if (r == 3)
        {
            p->f28 = 2;
            p->f2c = 0x745;
        }
        else if ((unsigned)(r - 1) < 2)
        {
            p->f2c = 0x1e1;
        }
        else
        {
            r = p->actor_8->ground_80;
            p->f28 = r;
            if (r == 3)
            {
                p->f28 = 2;
                p->f2c = 0x745;
            }
            else if ((unsigned)(r - 1) < 2)
            {
                p->f2c = 0x100;
            }
        }
    }
}

void ReflectPoint_800A47B8(struct_v3* a, struct_v3* b, struct_v3* out)
{
    int t;
    t = b->x - a->x;
    out->x = b->x + t;
    t = b->y - a->y;
    out->y = b->y + t;
    t = b->z - a->z;
    out->z = b->z + t;
}

// Matched
int sub_800A4804(GameAi* p)
{
    int r = FindActorInFront_8001DECC(p->actor_8, 0x190, 0);
    if (r == 0)
    {
        r = p->actor_8->ground_80;
    }
    if (r != 0)
    {
        if (r == 1)
        {
            p->f28 = 1;
        }
        else
        {
            p->f28 = 2;
        }
        if (r == 3)
        {
            p->timer_24 = 0x745;
        }
        else
        {
            p->timer_24 = 0x1e1;
        }
    }
    return 0;
}

// Matched
int sub_800A4884(struct_v3* a, short* q, struct_v3* b)
{
    int ang = ratan2_8003B548(a->x - b->x, a->z - b->z);
    return sinTable_80084540[(ang - q[1] + 0x400) & 0xfff] >= 0;
}

// Matched
int sub_800A48F4(int a)
{
    int r = 0x20;
    if (a > 0x800)
    {
        r = 0x100;
    }
    else if (a > 0x400)
    {
        r = 0x80;
    }
    else if (a > 0x200)
    {
        r = 0x40;
    }
    else if (a < 0x101)
    {
        r = 0x10;
    }
    return r;
}

void sub_800A4940(int a, int b)
{
    unsigned short* p;
    if (unknownFlags_8008D678 & 0x20000)
    {
        p = sub_800B322C();
    }
    else
    {
        p = sub_800A53CC();
        if (p)
        {
            p += b;
        }
    }
    if (p)
    {
        *p &= ~(0x1f << (a * 5));
    }
}

typedef struct GameSpawnEnt_1
{
    unsigned int chance : 8;
    unsigned int k0 : 3;
    unsigned int v0 : 5;
    unsigned int k1 : 3;
    unsigned int v1 : 5;
    unsigned int k2 : 3;
    unsigned int v2 : 5;
} GameSpawnEnt_1;
typedef struct GameSpawnOut_1
{
    int f0;
    int f4;
    int f8;
} GameSpawnOut_1;
extern GameSpawnOut_1 name_800AEB00[][3];
extern int sub_800B330C(void);
extern GameSpawnEnt_1* sub_800B2B40();
extern short* name_800AE9DC[];
extern GameSpawnEnt_1 name_800AE524[][3];
void sub_800A4DD0(int a, int b, MapList16* c, GameSpawnEnt_1* p, int* e, unsigned short* f);

#if 0
// Not matched (3 words long, registers differ): the original clears e[] with a scratch counter, keeps c in $s7 and
// dword_800AEB6C in $fp, and leaves the 0x8000 loop unrotated (bottom "i < c->count_0" exit, then a jump back to the
// "i < 3" test); the original also reloads *f for the == 0 test
int sub_800A49CC(int a, int b, MapList16* c, int* e)
{
    int n;
    unsigned short* f;
    unsigned short* t;
    int i;
    GameSpawnEnt_1* tbl;
    int r;
    int bits;
    int j;
    int k;
    GameSpawnOut_1* d;
    GameSpawnEnt_1* q;
    int* o;
    n = 0;
    f = 0;
    if (unknownFlags_8008D678 & 0x20000)
    {
        f = sub_800B322C();
    }
    else
    {
        t = sub_800A53CC();
        if (t != 0)
        {
            f = t + a;
        }
    }
    if (f == 0)
    {
        return n;
    }
    for (i = 0; i < 3; i++)
    {
        e[i] = 0;
        e[i + 3] = 0;
    }
    tbl = 0;
    if (unknownFlags_8008D678 & 0x20000)
    {
        tbl = sub_800B2B40();
    }
    else
    {
        r = sub_800A52EC(name_800AE9DC, 0x49, b);
        if (r >= 0)
        {
            tbl = name_800AE524[r];
        }
    }
    if (tbl == 0)
    {
        return n;
    }
    if (*f & 0x8000)
    {
        *f &= 0x7FFF;
        for (i = 0; i < c->count_0; i++, n++)
        {
            if (i >= 3)
            {
                break;
            }
            sub_800A4DD0(n, i, c, tbl, e, f);
        }
    }
    else if (*f == 0)
    {
        if (c->count_0 == 0)
        {
            return n;
        }
        if (rand() % 3 == 0)
        {
            return n;
        }
        if (c->count_0 < 3)
        {
            k = rand() % c->count_0;
        }
        else
        {
            k = rand() % 3;
        }
        sub_800A4DD0(n, k, c, tbl, e, f);
        n++;
    }
    else
    {
        bits = *f;
        d = name_800AEB00[0];
        o = e + n;
        for (j = 0; j < 3; j++, d += 3, bits >>= 5)
        {
            if (bits & 0x10)
            {
                q = &tbl[bits & 3];
                d[0].f0 = dword_800AEB6C[q->k0];
                d[1].f0 = dword_800AEB6C[q->k1];
                d[2].f0 = dword_800AEB6C[q->k2];
                d[0].f4 = q->v0 << 26;
                d[1].f4 = q->v1 << 26;
                d[2].f4 = q->v2 << 26;
                if (unknownFlags_8008D678 & 0x20000)
                {
                    k = (sub_800B330C() - 1) / 4 + 1;
                    if (k >= 8)
                    {
                        k = 7;
                    }
                    d[0].f4 = (q->v0 + k) << 26;
                    d[1].f4 = (q->v1 + k) << 26;
                    d[2].f4 = (q->v2 + k) << 26;
                }
                n++;
                o[0] = (int)d;
                o[3] = (int)&c->items_4[j];
                o++;
            }
        }
    }
    return n;
}
#endif

INCLUDE_OVERLAY_ASM(game, sub_800A49CC);

#if 0
// Not matched: logic and bitfield layout right; callee-saved registers differ and b*5 / the table address get hoisted out of the loop, the original computes b*5 in the found path
void sub_800A4DD0(int a, int b, MapList16* c, GameSpawnEnt_1* p, int* e, unsigned short* f)
{
    int r = rand() % 16;
    int i;
    int fl;
    int k;
    GameSpawnOut_1* d;
    GameSpawnEnt_1* q;
    int* o;
    fl = unknownFlags_8008D678;
    d = name_800AEB00[b];
    o = e + a;
    q = p;
    for (i = 0; i < 3; i++, q++)
    {
        if (r < q->chance)
        {
            d[0].f0 = dword_800AEB6C[q->k0];
            d[1].f0 = dword_800AEB6C[q->k1];
            d[2].f0 = dword_800AEB6C[q->k2];
            d[0].f4 = q->v0 << 26;
            d[1].f4 = q->v1 << 26;
            d[2].f4 = q->v2 << 26;
            if (unknownFlags_8008D678 & 0x20000)
            {
                k = (sub_800B330C() - 1) / 4 + 1;
                if (k >= 8)
                {
                    k = 7;
                }
                d[0].f4 = (q->v0 + k) << 26;
                d[1].f4 = (q->v1 + k) << 26;
                d[2].f4 = (q->v2 + k) << 26;
            }
            o[0] = (int)d;
            o[3] = (int)&c->items_4[b];
            *f |= (unsigned short)(i | 0x10) << (b * 5);
            return;
        }
        r -= q->chance;
    }
}
#endif

INCLUDE_OVERLAY_ASM(game, sub_800A4DD0);

int* sub_800A5030(int a, int b, int c)
{
    int* src = 0;
    int* r = 0;
    int i;
    short m;
    int j;
    if (unknownFlags_8008D678 & 0x20000)
    {
        src = sub_800B3198();
        if (src != 0)
        {
            if (dword_800AEB6C[0] == src[0] && dword_800AEB6C[1] == src[1] && dword_800AEB6C[2] == src[2])
            {
                src = 0;
            }
            if (src != 0)
            {
                dword_800AEB6C[0] = src[0];
                dword_800AEB6C[1] = src[1];
                dword_800AEB6C[2] = src[2];
                dword_800AEB6C[3] = 0xd3;
            }
        }
    }
    else
    {
        if (sub_800A5240(a, b))
        {
            c = 1;
        }
        if (c == 1)
        {
            i = sub_800A52EC(dword_800AE3D0, 0x11, a);
            if (i >= 0)
            {
                src = name_800AE4E0[i];
                if (src != 0)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (ELEM(src[j]) != -1 && dword_8008B554 == 0)
                        {
                            m = (ELEM(src[j]) + 1) % 4;
                            dword_800AEB6C[j] = src[j] * 4 + m + 0x39;
                        }
                        else
                        {
                            dword_800AEB6C[j] = src[j];
                        }
                    }
                    dword_800AEB6C[3] = 0xd3;
                    dword_8008B554 = dword_8008B554 == 0;
                }
            }
        }
    }
    if (src)
    {
        r = dword_800AEB6C;
    }
    return r;
}

// Matched
int sub_800A5240(int x, int y)
{
    if (y != -1)
    {
        return sub_800A52EC(dword_800AE3D0, 0x11, x) != sub_800A52EC(dword_800AE3D0, 0x11, y);
    }
    return 1;
}

// Matched
void sub_800A52AC(int a)
{
    int r = sub_800A52EC(dword_800AE254, 0x27, a);
    if (r < 0)
    {
        r = 0;
    }
    SetBattleStageId_80039FA4(r);
}

// Matched
int sub_800A52EC(short** tab, int n, int key)
{
    int r = -1;
    int i;
    for (i = 0; i < n; i++)
    {
        short* q = tab[i];
        while (*q != -1)
        {
            if (key == *q)
            {
                r = i;
                goto done;
            }
            q++;
        }
    }
done:
    return r;
}

// Matched
int sub_800A5354(void)
{
    int v = -1;
    switch (GetBattleStageId_80039FB0())
    {
    case 0xf:
        v = 0;
        break;
    case 0x10:
        v = 1;
        break;
    case 0x11:
        v = 2;
        break;
    }
    return v;
}

// Matched
unsigned short* sub_800A53CC(void)
{
    SaveData* b = &saveData_8008B570;
    unsigned short* r = 0;
    if (b->mapId_2E4[0].field_0 == 4)
    {
        if (b->mapId_2E4[1].field_0 == 1)
        {
            r = b->tbl_838;
        }
        else if (b->mapId_2E4[1].field_0 == 2)
        {
            r = b->tbl_850;
        }
        else if (b->mapId_2E4[1].field_0 == 3)
        {
            r = b->tbl_874;
        }
        else if (b->mapId_2E4[1].field_0 == 4)
        {
            r = b->tbl_8CC;
        }
    }
    else if (b->mapId_2E4[0].field_0 == 5)
    {
        if (b->mapId_2E4[1].field_0 == 1)
        {
            r = b->tbl_8F8;
        }
        else if (b->mapId_2E4[1].field_0 == 2)
        {
            r = b->tbl_90C;
        }
        else if (b->mapId_2E4[1].field_0 == 3)
        {
            r = b->tbl_92C;
        }
    }
    return r;
}

// Matched
void sub_800A5474(void)
{
    int i;
    int v = 0xd3;
    for (i = 3; i >= 0; i--)
    {
        dword_800AEB6C[i] = v;
    }
}

void sub_800A54A0(void)
{
    if (dword_800AEB7C != 2)
        sub_800A5854();
    if (name_800AEB80[1])
        ListFreeAll_8003FEC8(&name_800AEB80[1]);
    if (name_800AEBBC)
    {
        ListFree_8003FE38(name_80091C10, name_800AEBBC);
        name_800AEBBC = 0;
    }
    if (name_800AEBC0[0])
    {
        ListFree_8003FE38(name_80091C10, name_800AEBC0[0]);
        name_800AEBC0[0] = 0;
    }
    if (name_800AEBC0[1])
    {
        ListFree_8003FE38(name_80091C10, name_800AEBC0[1]);
        name_800AEBC0[1] = 0;
    }
    if (name_800AEBC8)
    {
        ListFree_8003FE38(name_80091C10, name_800AEBC8);
        name_800AEBC8 = 0;
    }
    if (name_800AEBCC[1])
    {
        FreeRecordTables_80026DE8(&name_800AEBCC[1], name_800AEBCC[0], name_80091C10);
        name_800AEBCC[0] = 0;
    }
}
