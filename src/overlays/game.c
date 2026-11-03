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
    sub_80037720();
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
    sub_80039FC0();
}

// Matched
void sub_800A1474(GameTask_1* t, GameQ_1* q)
{
    if (GetFileRequestStatus_8003BE30(q->req_0) == 0)
    {
        sub_8001AA50(1);
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
        GameSave_1* sd;
        FreeActiveOverlay_8002C014();
        SetFadeMode_8001C19C(0, 0x20);
        sd = (GameSave_1*)&saveData_8008B570;
        if (sd->f2f2 == sd->f2f0)
        {
            sub_80027314();
        }
        ResetOverlayLoaderTask_80020D68();
        t->next_8 = sub_800A15FC;
    }
}

// Matched
void sub_800A15FC(GameTask_1* t, GameQ_1* q)
{
    if (sub_800272D0() == 0)
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
    MemCopy_800403E8((unsigned int*)r->data_8, src, 0xe0);
    return r;
}

// Matched
void sub_800A1850(GameHolder_1* p)
{
    GameAi* q = p->f4;
    Actor* v = q->actor_8;
    p->f0 = 0;
    sub_800A2D28(q);
    DestroyActor_8001D600(v);
}

// Matched
void sub_800A188C(GameHolder_1* p)
{
    GameAi* q = p->f4;
    Actor* v = q->actor_8;
    sub_800A2EC8(q);
    SetActorActive_8001D658(v, 0);
}

// Matched
void sub_800A18C8(GameHolder_1* p)
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
            sub_8001D6EC((struct_obj_A*)q->actor_8, 1);
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
            sub_8001D6EC((struct_obj_A*)q->actor_8, 0);
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
    if (dword_80091C9C)
    {
        return 0;
    }
    if (((GameSave_1*)&saveData_8008B570)->f2f0 != ((GameSave_1*)&saveData_8008B570)->f2f2)
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
            if (IsWithinDistance_8003B740(o->actor_8->pos_38, (int*)&levantPos_8008BD18, &d) == 1)
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

#if 0
// Not matched: loop: $s4/$s5 swapped (cur slot copy vs &gCtx); tail: 'n' loaded straight into $a0 (no copy), &gCtx in $a2, dword_800B1CA8 store sinks to the epilogue. The control flow and the rest match
extern int dword_800B1CA8;
extern int sub_8001D4DC(int o, int a, int b, int c);
extern int name_8007A024[];
void sub_800A1BD0(void)
{
    char* e = sub_800A5F6C();
    int found;
    int o;
    GameSlot_1* slot;
    GameSlot_1* s;
    GameSlot_1* cur;
    int* t;
    GameAi* obj;
    int done;
    int i;
    int n;
    int* q;
    int* p;
    GameCtx_1* g;
    if (e)
    {
        o = *(int*)(e + 0xa4);
        *(int*)(e + 0xa4) = sub_8001D4DC(o, 0, 0, 0);
        slot = sub_800A17F4((unsigned int*)e, 0);
        slot->f4 = (GameAi*)CreateEnemyAiEvent_800A2D90(*(int*)(e + 0xa4), (char*)slot + 0x24, 0);
        sub_8001D730((struct_obj_A*)o, 0);
        sub_8001D68C((struct_obj_A*)o, 0);
        dword_800B1264 = (int*)slot;
    }
    found = 0;
    for (i = 0; i < 3; i++)
    {
        if (dword_800B19F0[i].f0)
        {
            s = &dword_800B19F0[i];
            cur = s;
            done = 0;
            t = *(int**)((char*)s + 0xd0);
            obj = s->f4;
            t = t ? t : name_8007A024;
            if (!found && gCtx_800B1260.f4 == (int)s)
            {
                sub_800A2EC8(obj);
                sub_8001DC34(obj->actor_8, (void*)t[0]);
                found = 1;
                done = found;
                gCtx_800B1260.f4 = (int)s;
            }
            if (!done)
            {
                sub_800A2EC8(obj);
                sub_8001DC34(obj->actor_8, (void*)t[1]);
                gCtx_800B1260.fc[gCtx_800B1260.f8] = (int)cur;
                gCtx_800B1260.f8++;
            }
        }
    }
    g = &gCtx_800B1260;
    p = (int*)g->f4;
    for (i = 0; i < 3; i++)
    {
        if ((unsigned)p[0xb8 / 4 + i * 2] >= 0xd3)
        {
            break;
        }
    }
    n = p[0xc / 4];
    if (n >= i)
    {
        n = i;
    }
    g->f76c = n;
    g->f770 = i;
    q = (int*)g->f4;
    g->f774 = q[2] == 0;
    g->f77c = 0;
    g->f778 = q[2] == 1;
    g->f780 = q[4];
    g->f784 = q[5];
    g->f788 = q[6];
    dword_800B1CA8 = 0;
    gCtx_800B1260.f0 = 1;
    g->f48 = q[7];
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
int sub_800A1E48(void)
{
    return *(int*)(*(int*)(gCtx_800B1260.f4 + 4) + 8) + 0x38;
}

// Matched
int sub_800A1E68(void)
{
    return *(int*)(*(int*)(gCtx_800B1260.f4 + 4) + 8) + 0x5c;
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
        sub_800A188C((GameHolder_1*)gCtx_800B1260.fc[i]);
    }
    sub_800A7B00(-1);
}

// Matched
void sub_800A1F0C(void)
{
    int i;
    for (i = 0; i < gCtx_800B1260.f8; i++)
    {
        sub_800A18C8((GameHolder_1*)gCtx_800B1260.fc[i]);
    }
    sub_800A7BF0(-1);
}

INCLUDE_OVERLAY_ASM(game, sub_800A1F80);

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
    return sub_8001E1C8((struct_obj_A*)gCtx_800B1260.actors_7c[a]);
}

// Matched
int sub_800A2594(int a)
{
    sub_800A2CA8(a, 0);
    return sub_8001E1DC((struct_obj_A*)gCtx_800B1260.actors_7c[a]);
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
extern GamePair_1 sub_80018A4C(int obj, int* p, int a2, int c);
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
                r = sub_80018A4C(((GameCtxA_1*)&gCtx_800B1260)->obj_7c[i - 4], p, ((GameCtxA_1*)&gCtx_800B1260)->f70c[i - 4], c);
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
            sub_8001E28C(gCtx_800B1260.actors_7c[i - 4]);
        }
    }
    return 1;
}

// Matched
void sub_800A27FC(int a, int b)
{
    sub_800A2CA8(a, 0);
    sub_80018E5C(gCtx_800B1260.actors_7c[a], b);
}

// Matched
void sub_800A284C(int a)
{
    sub_800A2CA8(a, 0);
    {
        int v = sub_800A2B60(a);
        sub_80018EBC(gCtx_800B1260.actors_7c[a], v);
    }
}

// Matched
int sub_800A2898(int a)
{
    sub_800A2CA8(a, 0);
    return AddItem_80010650((Item*)&gCtx_800B1260.ents_ac[a]);
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
            GameSave2_1* sd = (GameSave2_1*)&saveData_8008B570;
            sub_800A4940(x, dword_800B0608[sd->f2e4][sd->f2e8][sd->f2ec].f4);
        }
    }
}

// Matched
void sub_800A29CC(int a, GameActorInfo* out)
{
    sub_800A2CA8(a, 0);
    {
        Actor* e = gCtx_800B1260.actors_7c[a];
        out->f0 = e->f14C;
        out->pos_4 = e->pos_38;
        out->f8 = e->bonePos_1C4;
        out->fC = (char*)e->boneMatrices_1C8;
        out->f2C = (char*)e->boneScale_144;
        out->f30 = e->scale_2C;
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

#if 0
// Not matched: early returns give the right registers but a second `jr $ra` for
// the last return; a result variable (if/else, nested, goto, ternary) lands in $v1.
int sub_800A2AB4(void)
{
    GameCtx_1* c = &gCtx_800B1260;
    if (c->f774 == 0)
    {
        return 0;
    }
    if (c->f3c == 0)
    {
        return 1;
    }
    return 2;
}
#endif

INCLUDE_OVERLAY_ASM(game, sub_800A2AB4);

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
int sub_800A2B20(int a)
{
    sub_800A2CA8(a, 0);
    return (int)&gCtx_800B1260.ents_ac[a];
}

// Matched
int sub_800A2B60(int a)
{
    sub_800A2CA8(a, 0);
    return (int)&gCtx_800B1260.ents_ac[a];
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
int sub_800A2C28(int a)
{
    sub_800A2CA8(a, 0);
    return (int)gCtx_800B1260.actors_7c[a]->pos_38;
}

// Matched
int sub_800A2C68(int a)
{
    sub_800A2CA8(a, 0);
    return (int)gCtx_800B1260.actors_7c[a]->bonePos_1C4;
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
    sub_8001D760(p->actor_8, p->anim_20, -1, 0);
}

GameAi* CreateEnemyAiEvent_800A2D90(Actor* a, UnitStats* b, int c)
{
    GameObj5_1* e = (GameObj5_1*)AllocEventEntry_80043AF8((EventNode*)dword_8008D49C);
    GameAi* q;
    int v;
    int k;
    int j;
    if (e != 0)
    {
        q = e->obj_14;
        e->flags_0 = (e->flags_0 | 1) & ~0x8000;
        q->flags_0 = &e->flags_0;
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
            e->fn_8 = sub_800A2EE4;
        }
        else
        {
            v = b->species_5C;
            if ((unsigned)v < 0x39)
            {
                j = !(levantCaptureLevel_8008BD7C - b->st_0.level_44 < 5);

                e->fn_8 = name_800ADEB8[v][j];
            }
            else
            {
                k = v;
                if (k >= 0x39)
                {
                    k = (k - 0x39) / 4;
                }
                e->fn_8 = name_800ADEB8[k][0];
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
void sub_800A2EE4(void)
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
            sub_8001DB58((struct_obj_A*)p->actor_8, 0x3000, 1);
            break;
        case 5:
            sub_800A459C(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) > 0x155CC0)
                p->state_c = -1;
            break;
        }
    }
}

void sub_800A2FB8(int unused, GameAi* p)
{
    if (sub_800A4278(p) == 0)
    {
        if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) <= 0xDBB9F && p->state_c != 0xf)
        {
            SetActorState_800A433C(p, 0xf, 2, 0, -1, 1, 2);
            sub_8001DB58((struct_obj_A*)p->actor_8, 0x2000, 1);
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
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) > 0x155CC0)
            {
                p->state_c = -1;
                sub_8001DB58((struct_obj_A*)p->actor_8, 0x1000, 1);
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
            sub_8001DB58((struct_obj_A*)p->actor_8, 0x1000, 0);
            break;
        case 1:
            TurnActorTowards_8001DDFC(p->actor_8, &levantPos_8008BD18, 0x155);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) <= 0xDBB9F)
            {
                SetActorState_800A433C(p, 5, 2, 0, -1, c, 2);
                sub_8001DB58((struct_obj_A*)p->actor_8, 0x3000, 1);
            }
            break;
        case 5:
            sub_800A459C(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) > 0x155CC0)
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
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18) <= 0xDBB9F)
            {
                x = sub_800AB39C() & 0xFFFFFFF;
                if (x == 1)
                    SetActorState_800A433C(q, 0xf, 2, 0, -1, x, 2);
            }
            break;
        case 0xf:
            sub_800A45F8(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) > 0x1CFDE0)
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
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) <= 0xDBB9F)
                SetActorState_800A433C(p, 0xa, 4, 0x28, -1, 1, 2);
            break;
        case 0xa:
            if (--p->timer_24 < 0)
                SetActorState_800A433C(p, 0xf, 2, 0, -1, 1, 2);
            break;
        case 0xf:
            sub_800A45F8(p);
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) > 0x1CFDE0)
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
            if (DistanceSquaredXZ_8003B860(p->actor_8->pos_38, &levantPos_8008BD18) <= 0xDBB9F)
                SetActorState_800A433C(p, 0xa, 4, 0x46, -1, 1, 2);
            break;
        case 0xa:
            TurnActorTowards_8001DDFC(q->actor_8, &levantPos_8008BD18, 0x155);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18) > 0xDBBA0)
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
            if (sub_800A4884(&levantPos_8008BD18, (short*)(&levantPos_8008BD18 + 1), (GameVec3_1*)p->actor_8->pos_38))
                SetActorState_800A433C(p, 0xf, 2, 0, -1, c, 2);
            break;
        case 0xf:
            sub_800A45F8(p);
            if (sub_800A4884(&levantPos_8008BD18, (short*)(&levantPos_8008BD18 + 1), (GameVec3_1*)p->actor_8->pos_38) == 0)
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
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18) <= 0xDBB9F)
            {
                SetActorState_800A433C(q, 5, 2, 0, -1, 1, 2);
                sub_8001DB58((struct_obj_A*)q->actor_8, 0x2000, 1);
            }
            break;
        case 5:
            sub_800A44C0(q);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18) > 0x155CC0)
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
            sub_8001D6EC((struct_obj_A*)q->actor_8, 1);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18) <= 0x61A7F)
                SetActorState_800A433C(q, 0xf, 2, 0, -1, 1, 2);
            break;
        case 0xf:
            sub_800A45F8(q);
            if (DistanceSquaredXZ_8003B860(q->actor_8->pos_38, &levantPos_8008BD18) > 0xDBBA0)
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
    if (sub_80011B6C() == 0)
    {
        s = 0xd;
        if (p->state_c != s)
        {
            SetActorState_800A433C(p, s, 0x17, 0, -1, 1, 2);
        }
        return 1;
    }
    r = sub_80011B6C();
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
    sub_8001D760(p->actor_8, anim, mode, flag);
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
        p->f2c = sub_8001DD44(p->actor_8, p->f28, p->f2c, 0x20);
        sub_8001D71C((struct_obj_A*)p->actor_8);
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
    v.x = ((GameSave4_1*)&saveData_8008B570)->f7a8 - p->actor_8->pos_38[0];
    v.z = ((GameSave4_1*)&saveData_8008B570)->f7b0 - p->actor_8->pos_38[2];
    ang = ratan2_8003B548(v.x, v.z);
    idx = (ang - p->actor_8->rot_5C[1]) & 0xfff;
    w.x = p->actor_8->pos_38[0] + (p->actor_8->pos_38[0] - ((GameSave4_1*)&saveData_8008B570)->f7a8);
    w.z = p->actor_8->pos_38[2] + (p->actor_8->pos_38[2] - ((GameSave4_1*)&saveData_8008B570)->f7b0);
    if (TurnActorTowards_8001DDFC(p->actor_8, (GameVec3_1*)&w, sub_800A48F4(idx * 3)) == 0)
    {
        sub_8001D71C((struct_obj_A*)p->actor_8);
    }
}

// Matched
void sub_800A459C(GameAi* p)
{
    GameVec3_1 v;
    ReflectPoint_800A47B8(&levantPos_8008BD18, (GameVec3_1*)p->actor_8->pos_38, &v);
    if (TurnActorTowards_8001DDFC(p->actor_8, &v, 0x155) == 0)
    {
        sub_8001D71C((struct_obj_A*)p->actor_8);
    }
}

void sub_800A45F8(GameAi* p)
{
    int r;
    int step;
    if (p->f2c)
    {
        p->f2c = sub_8001DD44(p->actor_8, p->f28, p->f2c, 0x80);
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
        sub_8001DD44(p->actor_8, p->f28, 0x800, 0x40);
        return;
    }
    step = 0x40;
    if (sub_800A4884((GameVec3_1*)p->actor_8->pos_38, p->actor_8->rot_5C, &levantPos_8008BD18))
    {
        step = 0x80;
    }
    TurnActorTowards_8001DDFC(p->actor_8, (VECTOR*)&levantPos_8008BD18, step);
}

void sub_800A46FC(GameAi* p)
{
    int r;
    if (p->f2c)
    {
        p->f2c = sub_8001DD44(p->actor_8, p->f28, p->f2c, 0x20);
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

void ReflectPoint_800A47B8(GameVec3_1* a, GameVec3_1* b, GameVec3_1* out)
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
int sub_800A4884(GameVec3_1* a, short* q, GameVec3_1* b)
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
        p = (unsigned short*)sub_800B322C();
    }
    else
    {
        p = (unsigned short*)sub_800A53CC();
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
        f = (unsigned short*)sub_800B322C();
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
    sub_80039FA4(r);
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
    switch (sub_80039FB0())
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
    GameSave2_1* b = (GameSave2_1*)&saveData_8008B570;
    unsigned short* r = 0;
    if (b->f2e4 == 4)
    {
        if (b->f2e8 == 1)
        {
            r = b->f838;
        }
        else if (b->f2e8 == 2)
        {
            r = b->f850;
        }
        else if (b->f2e8 == 3)
        {
            r = b->f874;
        }
        else if (b->f2e8 == 4)
        {
            r = b->f8cc;
        }
    }
    else if (b->f2e4 == 5)
    {
        if (b->f2e8 == 1)
        {
            r = b->f8f8;
        }
        else if (b->f2e8 == 2)
        {
            r = b->f90c;
        }
        else if (b->f2e8 == 3)
        {
            r = b->f92c;
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
        sub_80026DE8(&name_800AEBCC[1], name_800AEBCC[0], name_80091C10);
        name_800AEBCC[0] = 0;
    }
}
