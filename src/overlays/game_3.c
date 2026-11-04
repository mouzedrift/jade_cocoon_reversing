// GAME.BIN, source file 3 of 3 from 0x800A5804 (.rdata from 0x800A0660)
#include "game.h"

const char aAssertionFaile_800A0660[] = "Assertion failed: file \"%s\", line %d\n";
const char aEventcomC_800A0688[] = "EVENTCOM.C";
const int dword_800A0694 = 0;

// Matched
void sub_800A5804(int a)
{
    if (a == 0)
    {
        AllocMdecVLCBuffer_80041848();
    }
    else if (a == 1)
    {
        AllocMdecVLCBufferInFileBuffer_8004188C();
    }
    dword_800AEB7C = a;
}

// Matched
int sub_800A5854(void)
{
    int old = dword_800AEB7C;
    if (old == 0)
    {
        FreeMdecBuffer_800418CC();
    }
    else if (old == 1)
    {
        ReleaseMdecVLCFileBuffer_800418FC();
    }
    dword_800AEB7C = 2;
    return old;
}

void sub_800A58B4(void)
{
    EventNode* n = eventScripts_8008D410;
    int i;
    int cnt = n->count;
    GameRect_1* r;
    for (i = 0; i < cnt; i++)
    {
        EventEntry* o = &n->entry;
        if ((o->flags & 0x8001) == 1)
            sub_800A6168(o, o->buffer);
        n = n->next;
    }
    dword_800AEBD8 = -1;
    dword_800AEBDC = 0;
    name_800AEBD4 = 0;
    StopAllEventEntries_80043B40(eventScripts_8008D410);
    SetCameraTarget_80037AC8((int)&levantPos_8008BD18);
    if (!(name_80091C38 & 0x40))
    {
        r = &stru_8008D420;
        r->x = 0;
        r->w = 0x140;
        r->y = 0;
        r->h = 0xf0;
    }
    ResetSceneFade_8001A9A4();
    dword_800AEBF0 = 0;
    dword_800AEBE8 = 0x8000;
    name_800AEBEC = 0;
    dword_800AEBE0 = 0;
    dword_800AEBF4 = 0;
}

// Matched
EventEntry* sub_800A59D0(int v)
{
    EventEntry* p = AllocEventEntry_80043AF8(eventScripts_8008D410);
    if (p)
    {
        GameEvCtx* q = p->buffer;
        int i;
        p->flags = ((((p->flags | 1) & ~0x8000) | 4) & ~0x8000);
        q->start_4 = v;
        q->pc_8 = v;
        q->ret_C = v;
        q->id_10 = dword_800AEBDC;
        q->f114 = 0;
        for (i = 7; i >= 0; i--)
        {
            q->fCC[i] = 0;
        }
        sub_800A5B54(q);
        p->cb_8 = sub_800A6060;
        p->cb_C = sub_800A6168;
        dword_800AEBDC++;
        return p;
    }
    return 0;
}

// Matched
EventEntry* sub_800A5AA0(int a, int b)
{
    EventEntry* r = sub_800A59D0(a);
    GameEvCtx* t = r->buffer;
    t->f120 = b;
    return r;
}

// Matched
int sub_800A5AD0(EventEntry* p)
{
    return ((GameEvCtx*)p->buffer)->id_10;
}

// Matched
int sub_800A5AE4(int a)
{
    EventNode* n = eventScripts_8008D410;
    EventEntry* o;
    int i;
    int cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        o = &n->entry;
        if ((o->flags & 0x8001) == 1)
        {
            if (a == ((GameEvCtx*)o->buffer)->id_10)
            {
                return (int)o;
            }
        }
        n = n->next;
    }
    return 0;
}

// Matched
void sub_800A5B54(GameEvCtx* p)
{
    int i;
    p->f14 = 0;
    p->f18 = 0;
    p->f1C = 0;
    p->f20 = 0;
    p->flags_0 = 0;
    p->fB4 = 0;
    p->fB8 = 0;
    p->fBC = 0;
    p->fC0 = 0;
    p->fC4 = 0;
    p->fC8 = -1;
    p->fEC = 0;
    p->f110 = 0;
    p->f118 = 0;
    p->f100 = -1;
    p->f102 = -1;
    p->f104 = -1;
    p->f108 = 0;
    p->f11C = 0;
    p->f120 = 0;
    p->fF0 = 0;
    for (i = 4; i >= 0; i--)
    {
        p->f24[i] = 0;
    }
}

// Matched
void sub_800A5BCC(int a)
{
    EventNode* n = eventScripts_8008D410;
    int i;
    int cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        EventEntry* o = &n->entry;
        if ((o->flags & 0x8001) == 1)
        {
            GameEvCtx* q = o->buffer;
            int m = 1 << a;
            q->f18 &= ~m;
            q->f20 &= ~m;
        }
        n = n->next;
    }
}

int sub_800A5C40(int a)
{
    int r = sub_800A5E68();
    EventNode* n = eventScripts_8008D410;
    int cnt = n->count;
    int i;
    GameEvCtx* o;
    GameEvEnt* q;
    int v;
    int k;
    EventEntry* e;
    for (i = 0; i < cnt; i++)
    {
        e = &n->entry;
        if ((e->flags & 0x8001) == 1)
        {
            o = e->buffer;
            if (r == 0 && (o->flags_0 & 8) && o->fC8 == a)
            {
                o->flags_0 |= 4;
                r = 1;
                break;
            }
        }
        n = n->next;
    }
    n = eventEntities_8008D400;
    cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        e = &n->entry;
        if ((e->flags & 0x8001) == 1)
        {
            q = e->buffer;
            if (r)
            {
                q->f78 = 0;
            }
            else if (q->f78)
            {
                k = 1;
                v = q->f84;
                if (v != -1 && (v & 0x40000000))
                {
                    k = (unsigned)((v & ~0x40000000) ^ a) < k;
                }
                if (k)
                {
                    q->f7C = 0;
                    if (q->f88)
                    {
                        sub_800A59D0(q->f88);
                        dword_800AEBD8 = dword_800AEBDC - 1;
                        r = 1;
                    }
                }
            }
        }
        n = n->next;
    }
    return r;
}

// Matched
GameEvEnt* sub_800A5DDC(int a, int b, GameEvEnt* c)
{
    EventNode* n = eventEntities_8008D400;
    int i;
    int cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        EventEntry* o = &n->entry;
        if ((o->flags & 0x8001) == 1)
        {
            GameEvEnt* q = o->buffer;
            if (c != q)
            {
                if (b == 0)
                {
                    if (a == q->f4)
                    {
                        return q;
                    }
                }
                else
                {
                    if (a == q->id_10)
                    {
                        return q;
                    }
                }
            }
        }
        n = n->next;
    }
    return 0;
}

// Matched
int sub_800A5E68(void)
{
    return dword_800AEBD8 >= 0;
}

int sub_800A5E80(int a)
{
    EventNode* n = eventEntities_8008D400;
    int i;
    int cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        EventEntry* o = &n->entry;
        if ((o->flags & 0x8001) == 1)
        {
            GameEvEnt* q = o->buffer;
            if (q->f78 != 0 && (q->f84 & 0xBFFFFFFF) == a)
                return 1;
        }
        n = n->next;
    }
    n = eventScripts_8008D410;
    cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        EventEntry* o = &n->entry;
        if ((o->flags & 0x8001) == 1)
        {
            GameEvCtx* q = o->buffer;
            if (q->fC8 == a)
                return 1;
        }
        n = n->next;
    }
    return 0;
}

// Matched
GameEnemy* sub_800A5F6C(void)
{
    if (dword_800AEBE0)
    {
        return &dword_800B1CB8;
    }
    return 0;
}

// Matched
void sub_800A5F90(int a)
{
    dword_800B1D98 = a;
}

// Matched
int sub_800A5F9C(int a)
{
    int old = dword_800AEBF4;
    dword_800AEBF4 = a;
    return old;
}

// Matched
void sub_800A5FAC(void)
{
    if (dword_800AEBE4)
    {
        SaveData* sd = &saveData_8008B570;
        GameS3_1 v;
        sub_800AD16C(4, sd->mapId_2E4[1].field_0 + 4);
        sub_800ADCEC(&v, sub_800A683C(-1));
        sub_800AD0F8(0);
        useMapStartPos_80091C94 = 1;
        dword_80091C54 = 0;
        sd->mapId_2E4[3].field_0 = 0;
        forceMapReload_80091C9C = 1;
        dword_80091C8C = 0;
        sd->mapId_2E4[0].field_0 = v.a;
        sd->mapId_2E4[1].field_0 = v.b;
        sd->mapId_2E4[2].field_0 = v.c;
        unknownFlags_8008D678 &= ~0x20000;
    }
}

void sub_800A6060(GameTask_1* t, GameEvCtx* q)
{
    while (1)
    {
        if (dword_800B0EC0 != 1)
            break;
        if (name_800BCDBC[*(int*)q->pc_8](q) == 0)
            break;
    }
    if (q->flags_0 & 0x40)
        sub_800BC2B4(q);
    if (q->flags_0 & 0x10)
    {
        q->flags_0 &= ~0x10;
        q->pc_8 = q->ret_C;
    }
    if (q->flags_0 & 1)
    {
        t->f0 &= ~1;
        t->f0 |= 0x8000;
        t->f0 &= ~4;
        t->f0 |= 0x8000;
    }
}

// Matched
void sub_800A6168(GameTask_1* t, GameEvCtx* q)
{
    if (dword_800AEBD8 == q->id_10)
    {
        sub_800B8A34(q);
    }
    t->f0 = (((t->f0 & ~1) | 0x8000) & ~4) | 0x8000;
}

void sub_800A61CC(int a, void* b, void* c)
{
    GameTim_1 t;
    GameActorDesc* i;
    if (a == 0)
    {
        t.mode_valid = 1;
        t.mode = 1;
        t.prect.x = name_8007DCA4.x;
        t.prect.y = name_8007DCA4.y;
        t.prect.w = 0x20;
        t.prect.h = 0x40;
        t.crect.x = name_8007DCA8.x;
        t.crect.y = name_8007DCA8.y;
        t.crect.w = 0x100;
        t.crect.h = 1;
    }
    else
    {
        i = sub_800A7A1C(a - 1);
        t.mode_valid = 1;
        t.mode = 1;
        t.prect.x = name_8007DCAC[i->clut_30].x;
        t.prect.y = name_8007DCAC[i->clut_30].y;
        t.prect.w = 0x20;
        t.prect.h = 0x40;
        t.crect.x = name_8007DCBC[i->clut_30].x;
        t.crect.y = name_8007DCBC[i->clut_30].y;
        t.crect.w = 0x100;
        t.crect.h = 1;
    }
    InitSprtFromTim_800298AC((int)b, (int)c, &t);
}

void sub_800A6308(int a, void* poly)
{
    GameTim_1 t;
    GameActorDesc* i;
    if (a == 0)
    {
        t.mode_valid = 1;
        t.mode = 1;
        t.prect.x = name_8007DCA4.x;
        t.prect.y = name_8007DCA4.y;
        t.prect.w = 0x20;
        t.prect.h = 0x40;
        t.crect.x = name_8007DCA8.x;
        t.crect.y = name_8007DCA8.y;
        t.crect.w = 0x100;
        t.crect.h = 1;
    }
    else
    {
        i = sub_800A7A1C(a - 1);
        t.mode_valid = 1;
        t.mode = 1;
        t.prect.x = name_8007DCAC[i->clut_30].x;
        t.prect.y = name_8007DCAC[i->clut_30].y;
        t.prect.w = 0x20;
        t.prect.h = 0x40;
        t.crect.x = name_8007DCBC[i->clut_30].x;
        t.crect.y = name_8007DCBC[i->clut_30].y;
        t.crect.w = 0x100;
        t.crect.h = 1;
    }
    InitPolyFT4_80029A10(poly, &t);
}

void GetIconSprtByKind_800A6434(int kind, int id, void* b, void* c)
{
    int icon;
    switch (kind)
    {
    case 0:
        break;
    case 1:
        sub_800A61CC(id, b, c);
        break;
    case 2:
        icon = GetItemIcon_8001D2AC(id);
        goto draw;
    case 3:
        icon = GetKeyItemIcon_8001D344(id);
        goto draw;
    case 4:
    case 5:
    case 6:
        icon = GetEquipmentIcon_8001D2D4(id, kind - 4);
    draw:
        GetPublicTiySprt_80032470(icon, b, c);
        break;
    case 7:
        printf(aAssertionFaile_800A0660, aEventcomC_800A0688, 0x2de);
        exit(1);
        break;
    }
}

INCLUDE_OVERLAY_ASM(game, dword_800A06B8);

// Matched
int sub_800A6504(int a)
{
    return sub_800B76B8(dword_8008B520 + (a << 3)) >= 0;
}

// Matched
void sub_800A6534(int a, int b)
{
    dword_8008B518[a] = b;
}

// Matched
void sub_800A654C(int a, int b)
{
    dword_8008B534[a] = b;
}

// Matched
void sub_800A6564(GameJ_1* p, int b)
{
    if (p->h0 >= 0)
    {
        sub_800A6534(p->h0, b);
    }
    if (p->h2 >= 0)
    {
        sub_800A654C(p->h2, b);
    }
}

// Matched
int sub_800A65BC(int a, int b)
{
    return (unsigned int)(WrapAngle_8003BA18((short)(a - b)) + 0x198) < 0x331;
}

// Matched
int sub_800A65F0(int* a, int* b, unsigned short* q, int r)
{
    unsigned int u = 0xfff;
    IsWithinDistance_8003B740(b, a, &u);
    if (u < (unsigned int)(r * r))
    {
        int d = GameFn_8003B9E0(b, a);
        if ((unsigned int)(WrapAngle_8003BA18((short)(q[1] - d)) + 0x198) < 0x331)
        {
            return 1;
        }
    }
    return 0;
}

#if 0
// Not matched: only $s0/$s1 swapped (p and x); tried struct p, locals, early returns, result var
int sub_800A66A4(int* p, int* x, unsigned short* q)
{
    if (p[0] >= 0 && sub_800A6504(p[0]))
    {
        int d = GameFn_8003B9E0(x, p + 1);
        if ((unsigned int)((short)WrapAngle_8003BA18((short)(q[1] - d)) + 0x198) < 0x331)
        {
            return 1;
        }
    }
    return 0;
}
#endif

INCLUDE_OVERLAY_ASM(game, sub_800A66A4);

int sub_800A6738(unsigned int a)
{
    dword_800AEBE8 = 0x8000;
    if (a <= 0xfffe)
    {
        GameTable_1* t;
        dword_800AEBE8 = a;
        t = sub_800A55B0(1);
        if (a < t->count)
        {
            int off = a * 8;
            off += 4;
            return *(int*)((char*)t + off);
        }
        return 0;
    }
    return a;
}

// Matched
int sub_800A67B4(unsigned int* p)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (p[6] & (1 << i))
        {
            if (i == 0)
            {
                sub_800A8EA4();
            }
            else
            {
                sub_800A7AD8(i - 1);
            }
        }
    }
    return 0;
}

// Matched
void sub_800A6830(int a)
{
    dword_800AEBF0 = a;
}

// Matched
int sub_800A683C(int x)
{
    int v = sub_800AD154(5) << 8;
    v += sub_800AD154(6);
    if (v == 0)
    {
        v = 0x66;
        sub_800AD16C(5, 0);
        sub_800AD16C(6, v);
    }
    if (x >= 0)
    {
        int hi = x >> 8;
        sub_800AD16C(5, hi);
        sub_800AD16C(6, x - (hi << 8));
    }
    return v;
}

void sub_800A68CC(GameTask_1* t, int* q)
{
    int i;
    int* d = dword_800B1DC8;
    sub_800A72C8((GameMode2_1*)d);
    q[0] = d[1];
    q[1] = q[0];
    q[2] = q[0];
    for (i = 11; i >= 0; i--)
    {
        q[i + 3] = 0;
    }
    q[0xf] = CreateEventList_800435B4(dword_800B0DA4);
    eventDispatchHalt_8008B540 = 0;
    dword_800B0698 = 0;
    t->next_8 = sub_800A6968;
}

void sub_800A6968(GameTask_1* t, GameQ_1* q)
{
    GameLst_1* l0 = dword_800B09FC;
    int i;
    if (l0->p0 != 0)
    {
        i = 0;
        do
        {
            sub_800A7450(*l0[i].p0);
            if (eventDispatchHalt_8008B540)
            {
                break;
            }
            i++;
        } while (l0[i].p0 != 0);
    }
    if (eventDispatchHalt_8008B540)
    {
        goto end;
    }
    ApplyAudioOutputFormat_80030988();
    sub_800A73A8();
    sub_800A6C00(t, q);
    sub_800A6A48(t, q);
    t->next_8 = sub_800A6B00;
end:
    eventDispatchHalt_8008B540 = 0;
    dword_800B0698 = 0;
}

void sub_800A6A48(GameTask_1* t, GameStage_1* q)
{
    GameLst_1* l0;
    GameLst_1* l;
    if (q->done_c[q->idx_0] == 0)
    {
        l0 = dword_800B0D74[q->idx_0];
        if (l0->p0 != 0)
        {
            l = l0;
            do
            {
                if (l->f4 & 0x1000)
                {
                    sub_800A7450(*l->p0);
                }
                l++;
            } while (l->p0 != 0);
        }
        q->done_c[q->idx_0] = 1;
    }
}

void sub_800A6B00(GameTask_1* t, GameQ_1* q)
{
    GameLst_1* l0 = dword_800B0D74[*(int*)q];
    int i;
    if (l0->p0 != 0)
    {
        i = 0;
        do
        {
            sub_800A7450(*l0[i].p0);
            if (eventDispatchHalt_8008B540)
            {
                break;
            }
            i++;
        } while (l0[i].p0 != 0);
    }
    if (unknownFlags_8008D678 & 0x8000000)
    {
        t->next_8 = sub_800A6CCC;
        goto end;
    }
    if (dword_800B0698 != 0)
    {
        sub_800A6C00(t, q);
        sub_800A6A48(t, q);
    }
end:
    eventDispatchHalt_8008B540 = 0;
    dword_800B0698 = 0;
}

void sub_800A6C00(GameTask_1* t, int* q)
{
    GameLst_1* l0 = dword_800B0D74[q[0]];
    GameLst_1* l;
    int one = 1;
    if (l0->p0 != 0)
    {
        l = l0;
        do
        {
            if (l->f4 & (one << q[2]))
                sub_800A74F0(*l->p0);
            l++;
        } while (l->p0 != 0);
    }
    if (q[0] == 11)
        q[0] = q[1];
    q[1] = q[0];
    q[0] = q[2];
}

// Matched
void sub_800A6CCC(GameTask_1* t, GameQ_1* q)
{
    RunEventListFreeCallbacks_800438F8(q->f3c);
    FreeEventList_80043A5C(q->f3c);
    bStopDrawingMovie_8008D45C = 1;
    t->f0 = (t->f0 & ~1) | 0x8000;
}

// Matched
void sub_800A6D30(int a)
{
    int* w = (int*)dword_8008D46C[9];
    dword_800B0698 = 1;
    w[2] = a;
}

int sub_800A6D50(int a)
{
    int* p = (int*)dword_8008D46C[9];
    int r = 0;
    switch ((unsigned)a)
    {
    case 0:
        r = p[0];
        break;
    case 1:
        r = p[1];
        break;
    case 2:
        r = p[2];
        break;
    }
    return r;
}

void sub_800A6DAC(GameTask_1* t, GameD_1* q)
{
    GameD_1* p;
    int ov;
    EventEntry* e;
    q->f0 = -1;
    unknownFlags_8008D678 &= ~8;
    p = q;
    q->f8 = 0;
    q->fC = 0;
    q->f10 = 0;
    q->f14 = 0;
    q->f1C = 0;
    if (forceMapReload_80091C9C == 1)
        return;
    if (saveData_8008B570.mapId_2E4[0].field_2 != saveData_8008B570.mapId_2E4[0].field_0)
        return;
    if (saveData_8008B570.mapId_2E4[1].field_2 != saveData_8008B570.mapId_2E4[1].field_0)
        return;
    if (saveData_8008B570.mapId_2E4[2].field_2 != saveData_8008B570.mapId_2E4[2].field_0)
        return;
    if (areaPreload_80091C40[1] != areaPreload_80091C40[0])
        return;
    if (saveData_8008B570.mapId_2E4[3].field_2 != saveData_8008B570.mapId_2E4[3].field_0)
        return;
    if (word_80091CB8[6] != word_80091CB8[7])
        return;
    if (IsMapLoading_800272D0())
        return;
    if (sub_800A5E68() == 0 && dword_800B0EC0 == 1 && gCtx_800B1260.f0 == 0 &&
        !(padPressed_8009194C & saveData_8008B570.buttonConfig_8[6]) && (padPressed_8009194C & saveData_8008B570.buttonConfig_8[4]))
    {
        q->f8 = dword_800B0EC0;
        q->f4 = (int)LoadOverlayIfChanged_80020D1C(1, 0xb);
        e = AllocEventEntry_80043AF8(dword_8008D498);
        e->flags = (e->flags | 1) & ~0x8000;
        q->f0 = 4;
    }
    else if (sub_800A5E68() == 0 && gCtx_800B1260.f0 == 0 && dword_800B0EC0 != 1)
    {
        p->f8 = 1;
        p->f4 = (int)LoadOverlayIfChanged_80020D1C(1, 0x1d);
        e = AllocEventEntry_80043AF8(dword_800B1DAC);
        e->flags = (e->flags | 1) & ~0x8000;
        p->f0 = 1;
    }
    else if (dword_800B06B0[0])
    {
        if (dword_800B06B0[1] == 0)
        {
            ov = 0xe;
        }
        else if (dword_800B06B0[1] == 1)
        {
            ov = 0xe;
        }
        else if (dword_800B06B0[1] == 2)
        {
            ov = 0xc;
        }
        else
        {
            ov = 0xd;
        }
        p->f8 = 1;
        p->f4 = (int)LoadOverlayIfChanged_80020D1C(1, ov);
        p->f0 = 5;
        p->f18 = (int)dword_800B06B0;
        p->f1C = (void (*)(int))sub_800A7204;
    }
    else if (sub_800A5E68() == 0 && gCtx_800B1260.f0 == 0 && dword_800B06BC)
    {
        p->f8 = 1;
        p->f4 = (int)LoadOverlayIfChanged_80020D1C(1, 0x10);
        e = AllocEventEntry_80043AF8(loadMenuTask_8008D480);
        e->flags = (e->flags | 1) & ~0x8000;
        p->f0 = 6;
        p->f18 = (int)&dword_800B06BC;
        p->f1C = (void (*)(int))sub_800A7280;
    }
    if (p->f0 >= 0)
    {
        sub_800A70F8(t, q);
    }
}

void sub_800A70F8(GameTask_1* t, GameD_1* q)
{
    int c = 0;
    GameD_1* r = q;
    if (q->f8)
        c = (unsigned)GetFileRequestStatus_8003BE30(q->f4) > 0;
    if (c == 0)
    {
        if (q->f1C)
            q->f1C(q->f18);
        sub_800A6D30(q->f0);
        t->next_8 = sub_800A6DAC;
        if (q->fC)
            FreezeScreen_8001C224();
        else
            EndFade_8001C290();
        eventDispatchHalt_8008B540 = r->f10;
    }
    else
    {
        if (q->f14 == 0)
        {
            BeginFade_8001C260();
            q->f14 = 1;
            sub_800A6D30(0xb);
            t->next_8 = sub_800A70F8;
        }
        eventDispatchHalt_8008B540 = 1;
    }
}

// Matched
void sub_800A7204(GameSub_1* p)
{
    if (p->f4 == 0)
    {
        sub_800BAE2C(0, *(short*)&p->f8);
        p->f0 = 0;
    }
    else if (p->f4 == 1)
    {
        sub_800BAE2C(1, *(short*)&p->f8);
        p->f0 = 0;
    }
    else
    {
        if (p->f4 == 2)
        {
            sub_800B66C4(*(short*)&p->f8);
        }
        p->f0 = 0;
    }
}

// Matched
void sub_800A7280(GameSub_1* p)
{
    sub_800B78B8(p->f8);
    if (p->fc)
    {
        sub_800B78D0();
    }
    p->f0 = 0;
}

GameMode2_1* sub_800A72C8(GameMode2_1* out)
{
    GameMode2_1 r;
    GameS3_1 v;
    if (unknownFlags_8008D678 & 0x40000000)
    {
        r.a = 0;
        r.b = 1;
        sub_800ADCEC(&v, 0x159);
        saveData_8008B570.mapId_2E4[0].field_2 = -1;
        saveData_8008B570.mapId_2E4[1].field_2 = -1;
        saveData_8008B570.mapId_2E4[2].field_2 = -1;
        useMapStartPos_80091C94 = 1;
        saveData_8008B570.mapId_2E4[0].field_0 = v.a;
        saveData_8008B570.mapId_2E4[1].field_0 = v.b;
        saveData_8008B570.mapId_2E4[2].field_0 = v.c;
    }
    else if ((unsigned short)word_8008B558[1] == 1)
    {
        r.a = 0;
        r.b = 1;
    }
    else if ((unsigned short)word_8008B558[1] == 4)
    {
        r.a = 1;
        r.b = 1;
    }
    else
    {
        r.a = 1;
        r.b = 0;
    }
    *out = r;
    return out;
}

void sub_800A73A8(void)
{
    GameRect_1* r = &stru_8008D420;
    sceneBrightness_8008D40C = 0x1000;
    unpausedFrames_8008D404 = 0;
    r->x = 0;
    r->w = 0x140;
    r->y = 0;
    r->h = 0xf0;
    unknownFlags_8008D678 &= ~0x8000000;
    InitMapState_80026FAC();
    GameFn_800A094C();
    ResetSoundTask_8002FEB8();
    InitSceneFade_8001A38C();
    ResetCameraToLevant_800376A8();
    sub_800A8140();
    sub_800A94CC();
    useMapStartPos_80091C94 = dword_800B1DC8[0];
}

// Matched
void sub_800A7450(EventNode* n)
{
    int i;
    int cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        if (eventDispatchHalt_8008B540)
        {
            break;
        }
        if ((n->entry.flags & 0x8001) == 1)
        {
            EventEntry* o = &n->entry;
            o->cb_8(o, o->buffer);
        }
        n = n->next;
    }
}

// Matched
void sub_800A74F0(EventNode* n)
{
    int i;
    int cnt = n->count;
    for (i = 0; i < cnt; i++)
    {
        if ((n->entry.flags & 0x8004) == 4)
        {
            EventEntry* o = &n->entry;
            o->cb_C(o, o->buffer);
        }
        n = n->next;
    }
}

int sub_800A7574(void)
{
    DrawIntroMovie_8001AF64(name_800B0EA4);
    ListFreeAll_8003FEC8(name_80096090);
    SsUtAllKeyOff(0);
    if (unknownFlags_8008D678 & 0x40000000)
    {
        unknownFlags_8008D678 &= 0xBFFFFFFF;
        return 8;
    }
    if (unknownFlags_8008D678 & 0x10000000)
        return 7;
    return 0xd;
}

// Matched
void sub_800A75F8(GameTask_1* t, void** q)
{
    *q = LoadOverlayIfChanged_80020D1C(1, 0xa);
    t->next_8 = sub_800A7654;
    unknownFlags_8008D678 |= 0x4000000;
}

// Matched
void sub_800A7654(GameTask_1* t, int* q)
{
    if (GetFileRequestStatus_8003BE30(q[0]) == 0)
    {
        t->next_8 = sub_800B6BFC;
    }
}

// Matched
void sub_800A7690(GameTask_1* t, void** q)
{
    *q = LoadOverlayIfChanged_80020D1C(1, 0x14);
    t->next_8 = sub_800A76D8;
}

// Matched
void sub_800A76D8(GameTask_1* t, int* q)
{
    if (GetFileRequestStatus_8003BE30(q[0]) == 0)
    {
        t->next_8 = sub_800B66DC;
    }
}

// Matched
void sub_800A7714(int a)
{
    dword_800B0EC0 = a;
}

// Matched
void sub_800A7720(GameTask_1* t)
{
    int n = dword_800B0EC0;
    if (n != 1)
    {
        void (*f)() = dword_800B0EB8[n].fn;
        t->next_8 = f;
        f(t);
    }
    else
    {
        t->f0 = (t->f0 & ~1) | 0x8000;
    }
}

// Matched
void sub_800A7784(void)
{
    dword_800B0EC4.count = 0;
}

// Matched
int sub_800A7790(void)
{
    return dword_800B0EC4.count;
}

int sub_800A77A0(GameMember* a)
{
    GameList_1* l = &dword_800B0EC4;
    int i = l->count;
    l->a[i] = a;
    l->b[l->count] = 0;
    l->c[l->count] = 0;
    l->count++;
    return i;
}

// Matched
GameMember* sub_800A77F4(int a)
{
    return dword_800B0EC4.a[a];
}

// Matched
int sub_800A7810(int a)
{
    if (a < sub_800A7790())
    {
        GameCb_1* p = &sub_800A77F4(a)->cb_14;
        return p->cb_c(p);
    }
    return 0;
}

// Matched
void sub_800A785C(int a)
{
    if (a < sub_800A7790())
    {
        GameCb_1* p = &sub_800A77F4(a)->cb_14;
        p->cb_10(p);
    }
}

// Matched
int sub_800A78A8(int a)
{
    if (a < sub_800A7790())
    {
        return (*sub_800A77F4(a)->hdr_10)->id_0;
    }
    return 0;
}

// Matched
int sub_800A78F4(int a)
{
    if (a < sub_800A7790())
    {
        return (*sub_800A77F4(a)->hdr_10)->f2A;
    }
    return 0;
}

// Matched
int* sub_800A7940(int a)
{
    if (a < sub_800A7790())
    {
        return sub_800A77F4(a)->cb_14.actor_4->pos_38;
    }
    return 0;
}

// Matched
short* sub_800A7984(int a)
{
    if (a < sub_800A7790())
    {
        return sub_800A77F4(a)->cb_14.actor_4->rot_5C;
    }
    return 0;
}

// Matched
int sub_800A79C8(int a)
{
    if (a < sub_800A7790())
    {
        return ((sub_800A77F4(a)->cb_14.actor_4->flags_4 >> 13) ^ 1) & 1;
    }
    return 0;
}

// Matched
GameActorDesc* sub_800A7A1C(int a)
{
    if (a < sub_800A7790())
    {
        return (GameActorDesc*)sub_800A77F4(a)->cb_14.actor_4->model_15C;
    }
    return 0;
}

// Matched
int sub_800A7A60(int a)
{
    if (a < sub_800A7790())
    {
        return (int)sub_800A77F4(a)->cb_14.actor_4;
    }
    return 0;
}

// Matched
int sub_800A7A9C(int a)
{
    if (a < sub_800A7790())
    {
        return (int)sub_800A77F4(a)->cb_14.f8;
    }
    return 0;
}

// Matched
void sub_800A7AD8(int a)
{
    SkipActorAnimToEnd_8001D9B0(sub_800A7A60(a));
}

void sub_800A7B00(int a)
{
    int i;
    int end;
    Actor* o;
    if (a < 0)
    {
        i = 0;
        end = sub_800A7790();
    }
    else
    {
        i = a;
        end = a + 1;
    }
    for (; i < end; i++)
    {
        o = sub_800A77F4(i)->cb_14.actor_4;
        if (dword_800B0EC4.b[i] == 0)
        {
            if (!(o->flags_4 & 0x2000))
            {
                SetActorAnimPaused_8001D6EC(o, 1);
                SetActorVisible_8001D730(o, 0);
                dword_800B0EC4.c[i] = 1;
            }
            if (!(o->task_0->flags & 0x8000))
            {
                SetActorActive_8001D658(o, 0);
                dword_800B0EC4.b[i] = 1;
            }
        }
    }
}

void sub_800A7BF0(int a)
{
    int i, end;
    Actor* o;
    if (a < 0)
    {
        i = 0;
        end = sub_800A7790();
    }
    else
    {
        i = a;
        end = a + 1;
    }
    for (; i < end; i++)
    {
        o = sub_800A77F4(i)->cb_14.actor_4;
        if (dword_800B0EC4.b[i])
        {
            if (dword_800B0EC4.c[i])
            {
                SetActorAnimPaused_8001D6EC(o, 0);
                SetActorVisible_8001D730(o, 1);
                dword_800B0EC4.c[i] = 0;
            }
            SetActorActive_8001D658(o, 1);
            dword_800B0EC4.b[i] = 0;
        }
    }
}

int sub_800A7CB8(int a)
{
    if (a < sub_800A7790())
        return sub_8001E1C8(sub_800A77F4(a)->cb_14.actor_4);
    return 0;
}

int sub_800A7CFC(int a)
{
    if (a < sub_800A7790())
        return sub_8001E1DC(sub_800A77F4(a)->cb_14.actor_4);
    return 0;
}

typedef struct GameCmdA_1
{
    int f0;
    int kind_4;
    int f8;
    int fC;
    int f10;
    unsigned int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
} GameCmdA_1;
typedef struct GameAnimReq_1
{
    int flags;
    int f4;
    int f8;
    short hC;
    short hE;
    int f10;
    int f14;
    int f18;
    int f1C;
    short h20;
    short h22;
    short h24;
    short h26;
    short h28;
    short h2A;
    int f2C;
    int f30;
    char pad_34[0x2c];
} GameAnimReq_1;
#if 0
// Not matched: 6 words: in case 9/10 the ((f14 >> 2) & 1) result is allocated to $v1 (original $v0) and the f14 reload swaps with it. Switch table: remove the dword_800A06B8 INCLUDE (the table) when enabling
void sub_800A7D40(int a, GameCmdA_1* c)
{
    GameAnimReq_1 s;
    GameModelHdr** hdr;
    GameCb_1* ent;
    Actor* obj;
    int k;
    int t;
    int u;
    int w;
    if (a < sub_800A7790())
    {
        hdr = sub_800A77F4(a)->hdr_10;
        ent = &sub_800A77F4(a)->cb_14;
        obj = ent->actor_4;
        s.flags = 0;
        s.f4 = 0;
        s.f8 = 0;
        s.hC = 0;
        s.hE = -1;
        s.f10 = -1;
        s.f18 = 0;
        s.h20 = 0;
        s.h22 = 0;
        s.f1C = 1;
        s.h24 = -1;
        s.h26 = -1;
        s.h28 = -1;
        s.h2A = -1;
        s.f2C = 0;
        s.f30 = 0;
        s.f1C = c->f8;
        k = 0;
        switch (c->kind_4)
        {
        case 0:
            if (c->f14 != -1)
                s.h24 = c->f14;
            else
                s.h24 = (*hdr)->f20;
            s.f8 = (int)&c->f18;
            s.hC = (*hdr)->f26;
            k = 1;
            break;
        case 1:
            if (c->f14 != -1)
                s.h24 = c->f14;
            else
                s.h24 = (*hdr)->f22;
            s.f8 = (int)&c->f18;
            s.hC = (*hdr)->f26;
            k = 1;
            break;
        case 2:
            if (c->f14 != -1)
                s.h26 = c->f14;
            else
                s.h26 = (*hdr)->f24;
            s.f8 = (int)&c->f18;
            s.hC = (*hdr)->f26;
            k = 1;
            break;
        case 3:
        case 4:
            s.f4 = ent->f8[c->fC];
            k = 1;
            break;
        case 5:
            s.f4 = c->f24;
            k = 1;
            break;
        case 6:
            SetActorVisible_8001D730(obj, c->fC);
            k = 0;
            break;
        case 7:
            SetActorGroundMove_8001D68C(obj, c->fC);
            k = 0;
            break;
        case 8:
            SetActorRootMotion_8001D6BC(obj, c->fC);
            k = 0;
            break;
        case 9:
        case 10:
            s.h28 = c->fC;
            s.h2A = (c->kind_4 == 10) ? c->f10 : -1;
            s.hC = (c->f14 & 1) ? -1 : -2;
            s.f2C = (c->f14 >> 3) & 1;
            k = 1;
            s.flags = (c->f14 >> 2) & 1;
            if (c->f14 & 0x10)
            {
                s.flags |= 2;
            }
            break;
        case 11:
            s.h28 = c->fC;
            if (c->f10 >= 0)
                s.h2A = c->f10;
            else
                s.h2A = obj->animIdx_C2;
            s.hC = (c->f14 & 1) ? -1 : -2;
            s.f2C = (c->f14 >> 3) & 1;
            s.flags = (c->f14 >> 2) & 1;
            t = s.flags;
            if (c->f14 & 0x10)
                t |= 2;
            s.flags = t;
            u = t;
            if (c->f14 & 0x20)
                u |= 4;
            s.flags = u;
            s.f30 = c->f24;
            k = 1;
            break;
        case 13:
            break;
        }
        if (k)
        {
            StartActorAction_8001E254(obj, &s);
        }
        else if (c->f8)
        {
            sub_800A5BCC(a + 3);
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A7D40);

const int dword_800A06F0[18] = {
    0x800A81F4, 0x800A8388, 0x800A83A4, 0x800A83D4, 0x800A84A0, 0x800A8454, 0x800A84D0, 0x800A8514,
    0x800A8540, 0x800A85A0, 0x800A85EC, 0x800A86B4, 0x800A878C, 0x800A8818, 0x800A8840, 0x800A8870,
    0x800A8888,
};

void sub_800A80C4(int a)
{
    if (a < sub_800A7790())
        TriggerActorEffect_8001E28C(sub_800A77F4(a)->cb_14.actor_4);
}

void sub_800A8108()
{
    sub_800A6D30(sub_800A6D50(1));
    eventDispatchHalt_8008B540 = 1;
}

void sub_800A8138()
{
}

void sub_800A8140()
{
    G2Inner* p = dword_8008B4CC->f24;
    FirFilterInit_8001450C(p->turnBuf_5C, &p->turn_4C, dword_800795C0, 4);
    p->f0 = 0;
    p->f9C = 0;
    p->fC6 = 0;
}

#if 0
// (Enabling this: drop the dword_800A06F0 table definition, the switch emits it.)
// Not matched (6 words): in case 0 the first pad block's turn-on-the-spot branch fills its delay slot from the
// branch target (lui 0x5000) where the original steals the fall-through lui 0x6000; tried the polarity / |= / ?:
// forms. The |= forms keep jump.c from if-converting the turn arms.
// Levant's movement command for this frame (sub_800AB37C): 1 / 4 / 2 move, 0x10000000 / 0x20000000 turn
// (or-ed onto a move), 0x50000000 / 0x60000000 turn on the spot
void sub_800A818C(EventEntry* e, G2Inner* p)
{
    int cmd;
    short angle;
    p->pos_10.x = levantPos_8008BD18.pos.x;
    p->pos_10.y = levantPos_8008BD18.pos.y;
    p->pos_10.z = levantPos_8008BD18.pos.z;
    switch (p->fC6)
    {
    case 0:
        if (p->f0 & 0x20)
        {
            p->fC6 = 9;
            break;
        }
        if ((padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[0]) &&
                (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[5]) ||
            (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[8]) || pads_800918E8[0][8] == 4)
        {
            int dir;
            if (sub_800A9164(&dir) == 1)
            {
                cmd = 0x40000000;
                if (dir >= 0)
                {
                    cmd |= 0x20000000;
                }
                else
                {
                    cmd |= 0x10000000;
                }
            }
            else
            {
                cmd = 1;
            }
        }
        else if ((padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[0]) &&
                 !(padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[5]))
        {
            int dir;
            if (sub_800A9164(&dir) == 1)
            {
                cmd = 0x40000000;
                if (dir < 0)
                {
                    cmd |= 0x10000000;
                }
                else
                {
                    cmd |= 0x20000000;
                }
            }
            else
            {
                cmd = 4;
            }
        }
        else if (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[1])
        {
            cmd = sub_800A926C() == 1 ? 0 : 2;
        }
        else
        {
            cmd = 0;
        }
        if (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[2])
        {
            cmd |= 0x10000000;
        }
        else if (padHeld_800918D0[0] & saveData_8008B570.buttonConfig_8[3])
        {
            cmd |= 0x20000000;
        }
        if (IsConfirmPressedP1_8003D380(0) && sub_800A5C40(-1) == 1)
        {
            cmd = 0;
        }
        if (p->f0 & 0x40)
        {
            cmd = 0;
        }
        sub_800AB37C(cmd);
        break;
    case 1:
        if (!(p->f0 & 1))
        {
            p->fC6 = 0;
        }
        break;
    case 2:
        if (sub_800AB1EC(p->fCC, (p->f0 >> 3) & 1, p->f34, p->f38) == 1)
        {
            p->fC6 = 3;
        }
        break;
    case 3:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &p->fA4)));
        if ((unsigned short)(angle + 0x60) <= 0xC0)
        {
            if (sub_800AB32C() == 1 && (p->f0 & 2))
            {
                p->f0 &= ~2;
                p->fC6 = 4;
            }
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        sub_800AB37C(cmd);
        break;
    case 5:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &p->fA4)));
        if ((unsigned short)(angle + 0x60) <= 0xC0)
        {
            p->fC6 = 4;
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        sub_800AB37C(cmd);
        break;
    case 4:
        if (p->f0 & 4)
        {
            sub_800AB1A4(0);
            p->fC6 = 6;
            p->f0 &= ~4;
        }
        break;
    case 6:
        if (!(p->f0 & 8))
        {
            p->fC6 = 1;
        }
        else if (sub_800AB304() == 1)
        {
            p->fC6 = 1;
            p->f0 &= ~8;
        }
        break;
    case 7:
        p->f0 &= ~0x10;
        p->fC6 = 1;
        p->f0 |= 0x10;
        sub_800AB3D4();
        sub_800AB37C(0);
    case 8:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &p->fA4)));
        if ((unsigned short)(angle + 0x40) <= 0x80)
        {
            p->fC6 = 1;
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        sub_800AB37C(cmd);
        break;
    case 9:
        if (!(p->f0 & 0x20) && sub_800AB958() == 1)
        {
            sub_800ABC34(1);
            p->fC6 = 0;
        }
        sub_800AB37C(0);
        sub_800AB3BC();
        break;
    case 10:
    {
        int* target = &p->fA4;
        int dist = 30000;
        int walk;
        IsWithinDistance_8003B740(&levantPos_8008BD18.pos.x, target, &dist);
        if (dist < 400 || (p->f0 & 0x80))
        {
            if (sub_800AB958() == 1)
            {
                p->fC6 = 9;
                sub_800A5BCC(0);
            }
            walk = 0;
        }
        else
        {
            walk = 4;
        }
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, target)));
        if ((unsigned short)(angle + 0x40) > 0x80)
        {
            if (angle < 0)
            {
                walk |= 0x20000000;
            }
            else
            {
                walk |= 0x10000000;
            }
        }
        sub_800AB37C(walk);
        break;
    }
    case 11:
    {
        int* target = &p->fA4;
        int dist = 30000;
        int walk;
        IsWithinDistance_8003B740(&levantPos_8008BD18.pos.x, target, &dist);
        if (dist < 400 || (p->f0 & 0x80))
        {
            if (sub_800AB958() == 1)
            {
                p->fC6 = 9;
                sub_800A5BCC(0);
            }
            walk = 0;
        }
        else
        {
            walk = 1;
        }
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, target)));
        if ((unsigned short)(angle + 0x40) > 0x80)
        {
            if (angle < 0)
            {
                walk |= 0x20000000;
            }
            else
            {
                walk |= 0x10000000;
            }
        }
        sub_800AB37C(walk);
        break;
    }
    case 12:
        cmd = 0;
        angle = WrapAngle_8003BA18(
            (short)(levantPos_8008BD18.rot.vy - ratan2Difference_8003B9E0(&levantPos_8008BD18.pos.x, &p->fA4)));
        if ((unsigned short)(angle + 0x40) <= 0x80 || (p->f0 & 0x80))
        {
            p->fC6 = 9;
            sub_800A5BCC(0);
        }
        else if (angle < 0)
        {
            cmd |= 0x20000000;
        }
        else
        {
            cmd |= 0x10000000;
        }
        sub_800AB37C(cmd);
        break;
    case 13:
        if (sub_800AB938() == 1)
        {
            p->fC6 = 9;
            sub_800A5BCC(0);
        }
        break;
    case 14:
        if (sub_800AB958() == 1)
        {
            p->fC6 = 9;
            sub_800A5BCC(0);
            sub_800AB37C(0);
        }
        break;
    case 15:
        if (sub_800ABB70() == 1)
        {
            p->fC6 = 9;
        }
        break;
    case 16:
        break;
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A818C);


void sub_800A88A0(int a, int b)
{
    sub_800A88E0(a, b, sub_800A8930());
}

int sub_800A88E0(G2P* p, int a, int b)
{
    int x = b ^ a;
    if (x & 1)
        p->s0 = 0x130 - p->u4;
    else
        p->s0 = 0x10;
    if (x & 2)
        p->s2 = 0xE0 - p->u6;
    else
        p->s2 = 0x10;
    return x;
}

int sub_800A8930()
{
    int r = cameraTargetScreenPos_8008D668[0] > 0xA0;
    if (cameraTargetScreenPos_8008D668[1] >= 0x79)
        r += 2;
    return r;
}

void sub_800A895C()
{
    dword_8008B4CC->f24->f0 |= 0x41;
}

void sub_800A8984(int a)
{
    G2Inner* p = dword_8008B4CC->f24;
    p->f0 &= ~1;
    p->f0 &= ~0x10;
    sub_800AB444(a, p);
}

void sub_800A89C8()
{
    dword_8008B4CC->f24->f0 &= ~0x40;
}

void sub_800A89F0()
{
    sub_800AB304();
}

void sub_800A8A10()
{
    sub_800AB354();
}

G2Pair_1 sub_800A8A30(int* c, int mode)
{
    G2Pair_1 r;
    unsigned int u;
    G2Inner* p = dword_8008B4CC->f24;
    if (name_800B1084[c[0]].a == 0x10)
    {
        p->fC6 = 5;
        r.a = 0;
        r.b = 0;
        return r;
    }
    p->fC6 = name_800B1084[c[0]].a;
    p->fCC = name_800B1084[c[0]].b;
    if (p->fCC == 8 && (int)((settingsFlags_8008B58C.word >> 21) & 1) == 1)
    {
        p->fCC = 7;
    }
    sub_800AC340(c[0] == 0x1a);
    u = (p->f0 | 2) & ~4;
    p->f38 = c[1];
    p->f34 = c[3];
    p->f0 = u;
    switch (mode)
    {
    case 0:
        p->f0 = u | 8;
        break;
    case 1:
        p->f0 = u & ~8;
        break;
    }
    if (c[0] == 0x12)
    {
        sub_800AB264();
    }
    else
    {
        sub_800AB28C();
    }
    if (c[0] == 0x10)
    {
        sub_800AB2B4();
    }
    else
    {
        sub_800AB2DC();
    }
    r.a = sub_800AB750(p->fCC);
    r.b = sub_800AB4D8(p->fCC);
    return r;
}

int sub_800A8BE4()
{
    return dword_8008B4CC->f24->fC6 == 4;
}

void sub_800A8C0C()
{
    dword_8008B4CC->f24->f0 |= 4;
}

UnitStatus* sub_800A8C34()
{
    return &levantStatus_8008BD38;
}

char* sub_800A8C40()
{
    return (char*)&levantPos_8008BD18;
}

void sub_800A8C4C(int a)
{
    SaveData* s = &saveData_8008B570;
    s->levantStatus_7C8.hp_8.cur_0 -= a;
    if ((short)s->levantStatus_7C8.hp_8.cur_0 < 0)
    {
        s->levantStatus_7C8.hp_8.cur_0 = 0;
        return;
    }
    if ((short)s->levantStatus_7C8.hp_8.max_2 < (short)s->levantStatus_7C8.hp_8.cur_0)
        s->levantStatus_7C8.hp_8.cur_0 = s->levantStatus_7C8.hp_8.max_2;
}

void sub_800A8CA0(int a)
{
    SaveData* s = &saveData_8008B570;
    s->levantStatus_7C8.mp_C.cur_0 -= a;
    if ((short)s->levantStatus_7C8.mp_C.cur_0 < 0)
    {
        s->levantStatus_7C8.mp_C.cur_0 = 0;
        return;
    }
    if ((short)s->levantStatus_7C8.mp_C.max_2 < (short)s->levantStatus_7C8.mp_C.cur_0)
        s->levantStatus_7C8.mp_C.cur_0 = s->levantStatus_7C8.mp_C.max_2;
}

void sub_800A8CF4()
{
    dword_8008B4CC->f24->fC6 = 0;
}

void sub_800A8D0C(int* a)
{
    G2Inner* p = dword_8008B4CC->f24;
    p->fC6 = 7;
    p->fA4 = a[0];
    p->fA8 = a[1];
    p->fAC = a[2];
}

void sub_800A8D48(int* a)
{
    G2Inner* p = dword_8008B4CC->f24;
    p->fC6 = 8;
    p->fA4 = a[0];
    p->fA8 = a[1];
    p->fAC = a[2];
}

int sub_800A8D84()
{
    return dword_8008B4CC->f24->fC6 == 1;
}

void sub_800A8DAC()
{
    sub_800AB85C();
}

void sub_800A8DCC()
{
    sub_800AB884();
}

void sub_800A8DEC()
{
    sub_800AB8AC();
}

void sub_800A8E0C()
{
    G2Inner* p = dword_8008B4CC->f24;
    p->fC6 = 9;
    p->f0 |= 0x20;
}

void sub_800A8E38()
{
    G2Inner* p = dword_8008B4CC->f24;
    p->f0 &= ~0x20;
    sub_800A913C();
    sub_800ABAD4();
}

int sub_800A8E7C()
{
    return dword_8008B4CC->f24->fC6 == 9;
}

void sub_800A8EA4()
{
    sub_800AC318();
}

void sub_800A8EC4(G2Cmd_1* c)
{
    G2Inner* p = dword_8008B4CC->f24;
    int b;
    switch (c->kind_4)
    {
    case 0:
    case 1:
    case 2:
        p->fA4 = c->f18;
        p->fA8 = c->f1C;
        p->fAC = c->f20;
        break;
    case 9:
    case 10:
        if (c->f14 & 1)
        {
            sub_800ABB98(0);
        }
        else
        {
            sub_800ABB98(1);
        }
        b = -1;
        if (c->kind_4 == 10)
        {
            b = c->f10;
        }
        if (c->f14 & 4)
        {
            sub_800AB9A8(c->fC, b, 0);
        }
        else
        {
            sub_800AB9A8(c->fC, b, 1);
        }
        goto set;
    case 11:
        sub_800ABC78(1);
        sub_800ABAA4(c->f24);
        sub_800ABB98(1);
        sub_800AB9A8(c->fC, -1, 1);
    set:
        p->fC6 = 9;
        p->fB0 = c->kind_4;
        break;
    case 13:
        break;
    }
}

int sub_800A8FE0()
{
    return dword_8008B4CC->f24->fC6 == 9;
}

void sub_800A9008(G2Cmd_1* c)
{
    G2Inner* p = dword_8008B4CC->f24;
    p->f0 &= ~0x80;
    switch (c->kind_4)
    {
    case 0:
        p->fC6 = 10;
        break;
    case 1:
        p->fC6 = 11;
        break;
    case 2:
        p->fC6 = 12;
        break;
    case 4:
        p->fC6 = 14;
        sub_800AB910();
        break;
    case 6:
        sub_800ABBD8(c->fC);
        break;
    case 7:
        sub_800ABC34(c->fC);
        break;
    case 8:
        sub_800ABC78(c->fC);
        break;
    case 9:
    case 10:
    case 11:
        if (c->f14 & 8)
        {
            p->fC6 = 9;
            sub_800A5BCC(0);
        }
        else
        {
            p->fC6 = 13;
        }
        sub_800AB1A4(1);
        break;
    case 13:
        break;
    }
}
// (When writing sub_800AA51C in C, delete the jpt_800A07A8 line.)
INCLUDE_OVERLAY_ASM(game, jpt_800A07A8);
const char aAssertionFailed_800A07E0[] = "Assertion failed: file \"%s\", line %d\n";
const char aPLDISPC_800A0808[] = "PLDISP.C";
const int dword_800A0814 = 0;

void sub_800A911C(int a)
{
    sub_800A5C40(a);
}

void sub_800A913C()
{
    dword_8008B4CC->f24->f0 |= 0x80;
}

int sub_800A9164(int* out)
{
    int best = 0x7FFFFFFF;
    int n = sub_800A7790();
    int i;
    int* v;
    short y;
    for (i = 0; i < n; i++)
    {
        if (sub_800A79C8(i))
        {
            v = name_800A7940(i);
            IsWithinDistance_8003B740(&saveData_8008B570.levant_7A8.pos, v, &best);
            if (best <= 0x9C3F)
            {
                y = WrapAngle_8003BA18((short)((unsigned short)saveData_8008B570.levant_7A8.rot.vy - sub_8003B9E0(&saveData_8008B570.levant_7A8.pos.x, v)));
                *out = y;
                if ((unsigned)(y + 0x3FF) < 0x7FF)
                    return 1;
            }
        }
    }
    return 0;
}

int sub_800A926C()
{
    int best = 0x7FFFFFFF;
    int n = sub_800A7790();
    int i;
    int* v;
    short y;
    for (i = 0; i < n; i++)
    {
        if (sub_800A79C8(i))
        {
            v = name_800A7940(i);
            IsWithinDistance_8003B740(&saveData_8008B570.levant_7A8.pos, v, &best);
            if (best <= 0x9C3F)
            {
                y = WrapAngle_8003BA18((short)((unsigned short)saveData_8008B570.levant_7A8.rot.vy - sub_8003B9E0(&saveData_8008B570.levant_7A8.pos.x, v)));
                if (!((unsigned)(y + 0x400) < 0x801))
                    return 1;
            }
        }
    }
    return 0;
}

void sub_800A9364()
{
    sub_800AB910();
}

void sub_800A9384()
{
    sub_800ABBD8();
}

void sub_800A93A4(EffectTarget* a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    a->tbl_0 = GetModelEffectTable_80024E64(p->model_40);
    a->pos_4 = &levantPos_8008BD18.pos.x;
    a->bonePos_8 = p->bonePos_590[0];
    a->boneMatrices_C = p->mats_90;
    a->boneScale_2C = dword_800B0FB0;
    a->scale_30 = 0;
}

void sub_800A9414(void* pv, int b, int c)
{
    G2Act* p = (G2Act*)pv;
    ApplyModelFtgSwaps_80025C38(p->model_40, (((unsigned)unknownFlags_8008D678 >> 24) ^ 1) & 1);
    FirFilterInit_8001450C(p->turnBuf_780, &p->turn_770, dword_800795C0, 4);
    sub_800AB010(p, b, c, 0);
    p->fC = 0;
    if (sub_800AAFD8(p->s1e) != 1)
        p->f0 &= ~0x10;
    sub_800ABAD4();
    sub_800AA140(p);
}

void sub_800A94CC(void)
{
    G2Init_1* p = (G2Init_1*)gameTask_8008B4A4->f24;
    p->s1c = 3;
    p->s1e = 3;
    p->fC = 0;
    p->f8 = 0;
    p->f10 = 0;
    p->s26 = 0;
    p->f0 = 0;
    p->f30 = 0;
    p->s1a = 0;
    p->s18 = 0x1000;
    p->f4 = 0;
    sub_800AB8DC();
    sub_800A9414(p, 0, 3);
    sub_800AB150((G2Obj*)p);
    sub_800B80C8(p);
    p->f3C = dword_8008BD38;
    sub_800ABECC(dword_8008BD38);
}

void sub_800A955C()
{
}

void sub_800A9564(int a, G2Act* p)
{
    int i;
    p->turn_770.input_8 = 0;
    p->v48.a = levantPos_8008BD18.pos.x;
    p->v48.b = levantPos_8008BD18.pos.y;
    p->v48.c = levantPos_8008BD18.pos.z;
    if (p->s26 >= 0x1000)
    {
        p->f0 &= ~0x10;
    }
    else
    {
        p->s26 += 0x400;
    }
    p->u1a += p->u18;
    if (p->u1a >= 0x1000)
    {
        p->u1a -= 0x1000;
        p->f10++;
    }
    if (p->f0 & 0x800)
    {
        if (p->f10 == (unsigned short)sub_800AC878(p->s1c, sub_800AC474(p->s1c)))
        {
            p->f0 |= 0x8000;
            p->f10 = (unsigned short)sub_800AC834(p->s1c, sub_800AC474(p->s1c));
            sub_800AA140(p);
        }
    }
    sub_800AAF58(p);
    sub_800A9A9C(p);
    sub_800A99DC(p);
    DrawLevantModel_800A9708(p);
    sub_800AA220(p);
    for (i = 0; i < 40; i++)
    {
        p->mats_90[i] = boneMatrices_80098188[i];
    }
}

void DrawLevantModel_800A9708(G2Act* p)
{
    G2Skel_1 sk;
    int v;
    ModelAnim* anim;
    int flags;
    int st;
    char* sd; // read as a scalar: through SaveData* gcc reloads the status after the p->f3c store
    v = FindNearestCameraPoint_80019CC4(&saveData_8008B570.levant_7A8);
    sd = (char*)&saveData_8008B570;
    if (p->f3c != *(int*)(sd + 0x7c8))
    {
        p->f3c = *(int*)(sd + 0x7c8);
        sub_800ABECC(*(int*)(sd + 0x7c8));
    }
    anim = &p->model_40->anims_54[sub_800AC4A8(p->s1c)];
    if (*(int*)(sd + 0x7c8) & 0x3fd)
    {
        flags = (word_8007DC8A - word_8007DC82) << 8;
    }
    else
    {
        flags = 0;
    }
    if (p->f0 & 6)
    {
        int t = flags | 0xb0;
        flags = t | (p->f30 << 16);
    }
    if (p->f0 & 2)
    {
        p->f30 += 0x80;
        if (p->f30 >= 0x1000)
        {
            p->f30 = 0x1000;
        }
    }
    else if (p->f0 & 4)
    {
        p->f30 -= 0x80;
        if (p->f30 < 0)
        {
            p->f30 = 0;
            sub_800AB150(p);
        }
    }
    if (p->f30 == 0x1000)
    {
        return;
    }
    if (p->f0 & 0x20000)
    {
        return;
    }
    sk.ftg_0 = p->model_40->ftg_50;
    sk.f4 = &levantPos_8008BD18.pos;
    sk.f8 = &levantPos_8008BD18.rot;
    sk.bones = &dword_800B0EF8;
    sk.base = dword_800B0FB0;
    sk.f24 = 0;
    sk.pose = (char*)anim;
    sk.frame = p->f10 % anim->frameCount_0;
    sk.flags = flags;
    sk.pos = (char*)p + 0x590;
    sk.ot = pOT_8008D690;
    if (sub_800AC518(p->s1e) == 0)
    {
        p->f0 &= ~0x10;
    }
    if (!(p->f0 & 0x10))
    {
        DrawAnimSkel_80046A58(&sk, &pointLights_8008D534[v], 0);
    }
    else
    {
        anim = &p->model_40->anims_54[sub_800AC4A8(p->s1e)];
        DrawAnimSkelBlend_80047E28(&sk, dword_800B0FB0, (char*)anim, p->f14 % anim->frameCount_0, 0x1000 - p->s26, &pointLights_8008D534[v], 0);
    }
    DrawSpriteVtxQuadsGT4_800459E4(&dword_800B0EF8, &p->model_40->mats_5C, pOT_8008D690, sk.flags);
}

void sub_800A99DC(G2Act* p)
{
    if (p->f4 & 0x10000000)
        p->turn_770.input_8 = -0x40;
    if (p->f4 & 0x20000000)
        p->turn_770.input_8 = 0x40;
    if (p->f4 & 0x40000000)
        p->turn_770.input_8 /= 2;
    p->f4 &= ~0x30000000;
    FirFilterStep_80014588(p->turnBuf_780, &p->turn_770, frameCount_8008D3FC);
    saveData_8008B570.levant_7A8.rot.vy += p->turn_770.output_C.low;
}

#if 0
// Not matched: 24 words: dx/dz get $s2/$s3 swapped (the original keeps the 0x6c delta in $s3), the tri address adds base + index the other way round, and the path_78 reads become register copies (move $v1,$a0) in the original instead of reloads; the rest matches
void sub_800A9A9C(G2Act* p)
{
    G2V12 prev;
    int dz;
    int dx;
    int div;
    MapTri* t;
    int k;
    int f;
    int rot;
    G2Path* path;
    int sn;
    int cs;
    short ang;
    prev.a = p->v6c.a;
    prev.b = p->v6c.b;
    prev.c = p->v6c.c;
    sub_800AA140(p);
    dz = 0;
    if (p->f0 & 8)
    {
        p->f0 &= ~8;
        dx = dz;
    }
    else
    {
        dx = p->v6c.a - prev.a;
        sub_800AC4A8(p->s1c);
        p->v6c.c -= (dx & 0x1f) * Sign_8003B664(dx);
        dz = p->v6c.c - prev.c;
        sub_800AC4A8(p->s1c);
        p->v6c.c -= (dz & 0x1f) * Sign_8003B664(dz);
    }
    if (p->f10 == (unsigned short)sub_800AC8BC(p->s1c, sub_800AC474(p->s1c)) ||
        ((p->f0 & 0x800) && p->f10 == (unsigned short)sub_800AC878(p->s1c, sub_800AC474(p->s1c))))
    {
        p->f0 |= 0x8000;
        p->f10 = (unsigned short)sub_800AC834(p->s1c, sub_800AC474(p->s1c));
        sub_800AA140(p);
    }
    if (p->f8 == 2 && (p->f0 & 0x200000))
    {
        dx = 0;
        dz = dx;
    }
    if (!(p->f0 & 0x84000))
    {
        div = p->model_40->anims_54[sub_800AC4A8(p->s1c)].divisor_8;
        sub_800B80C8(p);
        t = &mapState_8008B500.meshes_C[p->mesh_84].tris_4[p->tri_80];
        f = t->nx_18 * sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff] / 4096 +
            t->nz_1C * sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff] / 4096;
        f = 0x1000 - f * f / 4096;
        saveData_8008B570.levant_7A8.pos.x += dx * sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff] / 4096 * f / 4096 / div;
        saveData_8008B570.levant_7A8.pos.z += -(dx * sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff] / 4096) * f / 4096 / div;
        saveData_8008B570.levant_7A8.pos.x += dz * sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff] / 4096 * f / 4096 / div;
        saveData_8008B570.levant_7A8.pos.z += dz * sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff] / 4096 * f / 4096 / div;
        if (!(p->f0 & 0x40000))
        {
            f = sub_800B6DD4(p);
            if (f < 0)
            {
                p->f778 = -0x40;
            }
            else if (f > 0)
            {
                p->f778 = 0x40;
            }
        }
    }
    else if (p->f0 & 0x400000)
    {
        p->v6c.a = p->path_78->steps_8[p->f7c].x;
        p->v6c.b = p->path_78->steps_8[p->f7c].y;
        p->v6c.c = p->path_78->steps_8[p->f7c].z;
        rot = p->path_78->steps_8[p->f7c].rotY;
        div = p->path_78->div_4;
        p->f7c++;
        if (p->f7c >= p->path_78->count_0)
        {
            p->f0 &= ~0x400000;
            sub_800ABC78(0);
            p->f0 = (p->f0 & ~0x800) | 8;
            sub_800AB010(p, 0, 3, 0);
            p->fC = 0;
        }
        saveData_8008B570.levant_7A8.pos.x = p->v60.a + p->v6c.a / div;
        saveData_8008B570.levant_7A8.pos.y = p->v60.b + p->v6c.b / div;
        saveData_8008B570.levant_7A8.pos.z = p->v60.c + p->v6c.c / div;
        saveData_8008B570.levant_7A8.rot.vy = rot;
    }
    else
    {
        div = p->model_40->anims_54[sub_800AC4A8(p->s1c)].divisor_8;
        sub_800AA140(p);
        sn = sinTable_80084540[saveData_8008B570.levant_7A8.rot.vy & 0xfff];
        cs = sinTable_80084540[(saveData_8008B570.levant_7A8.rot.vy + 0x400) & 0xfff];
        saveData_8008B570.levant_7A8.pos.z = p->v60.c + (p->v6c.c * cs - p->v6c.a * sn) / 4096 / div;
        saveData_8008B570.levant_7A8.pos.x = p->v60.a + (p->v6c.c * sn + p->v6c.a * cs) / 4096 / div;
        saveData_8008B570.levant_7A8.pos.y = p->v60.b + p->v6c.b / 32;
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A9A9C);

void sub_800AA140(G2Act* p)
{
    ModelAnim* t = &p->model_40->anims_54[sub_800AC4A8(p->s1c)];
    GetAnimRootMotion_8004D288((char*)p + 0x6c, t, (unsigned)p->f10 % ((sub_800AC8BC(p->s1c, sub_800AC474(p->s1c)) & 0xffff) + 1));
}

int sub_800AA1C0(G2Act* p)
{
    return p->f4 & 0xFFFFFFF;
}

int sub_800AA1D4(unsigned char* p)
{
    return p[1] & 1;
}

void sub_800AA1E0(G2Act* a)
{
    a->s20 = a->u22;
    sub_800AB010(a, 0x17, 3, 0);
    a->fC = 3;
}

void sub_800AA220(G2Act* a)
{
    RunAnimFrameCues_8001C440(a->model_40, sub_800AC4A8(a->s1c), a->f10);
}

void sub_800AA25C(G2Act* p)
{
    if (sub_800AA1D4(p) == 1)
    {
        sub_800AB010(p, 7, 3, 0);
        p->fC = 1;
        return;
    }
    if (p->f0 & 0x4000)
    {
        return;
    }
    if (p->f0 & 0x10)
    {
        return;
    }
    if (sub_800AA1C0(p) == 1)
    {
        sub_800AB010(p, 5, 2, 0);
        return;
    }
    if (sub_800AA1C0(p) == 2)
    {
        sub_800AB010(p, 4, 1, 0);
        return;
    }
    if (sub_800AA1C0(p) == 4)
    {
        sub_800AB010(p, 2, 0, 0);
        p->f0 &= ~0x200000;
        return;
    }
    if (p->f4 & 0x30000000)
    {
        sub_800AB010(p, 2, 0, 0);
        p->f0 |= 0x200000;
        return;
    }
    if (sub_800AA1C0(p) == 3)
    {
        sub_800AA1E0(p);
        return;
    }
    if (++p->s28 > 0x5a)
    {
        sub_800AB010(p, 1, 4, 0);
        p->s28 = 0x5a;
    }
    else
    {
        sub_800AB010(p, 0, 3, 0);
    }
}

void sub_800AA3F0(G2Act* a)
{
    sub_800AB010(a, 0, 3, 0);
    a->fC = 0;
    a->f0 |= 0x2000;
}

#if 0
// Not matched: the original reloads p->f2C after the v19 select (lw 0x2c before 'sw 0x18'); here the compare's value is reused, so everything after is 2 words short
void sub_800AA430(G2Act* p)
{
    G2L2 L;
    int v19;
    short* r17;
    int r16;
    if (p->f2C != 0x46)
    {
        v19 = 4;
        if (!((unsigned short)(p->s1c - 7) < 2))
            v19 = p->s2A;
        L.f0 = p->f2C;
        r17 = sub_800AC9CC(p->s20);
        r16 = (unsigned short)sub_800AC834(p->s1c, sub_800AC474(p->s1c));
        L.f4 = RepeatHitTimes_80018200(r17, r16, (unsigned short)sub_800AC878(p->s1c, sub_800AC474(p->s1c)), v19, p->f2C);
        sub_800A93A4(L.rest);
        CollectEffectTargets_800182B8(&L, p->f38);
        PlayActorEffect_800184DC((int)&L, 0);
    }
}
#endif

INCLUDE_OVERLAY_ASM(game, sub_800AA430);

#if 0
// Not matched: one block differs: case 16 passes the matched constant (in $v0) as sub_800AB010's third argument where this C reloads s1c.
// The prototypes below change the code of matched callers further down, and sub_800AC900 must return int
// here (the original tests its result as a short): settle both before enabling this.
extern short effectOutcomeFlag_8008D780;
void sub_800AA430(G2Act* p);
unsigned short sub_800AB170(int a);
void sub_800ABCF4(G2Act* p);
void sub_800ABDF0(G2Act* a);
int sub_800AC604(int a, int b);
int sub_800AC768();
short sub_800AC834(int a, int b);
short sub_800AC878(int a, int b);
unsigned short sub_800AC8BC(int a, int b);
int sub_800AC900(int a, int b);
void sub_800AA51C(G2Act* o)
{
    short r;
    switch (o->f8)
    {
    case 7:
        if (GetCameraMode_800378F8() == 3)
        {
            sub_800AB010(o, 9, 0xE, 0);
        }
        break;
    case 9:
        if (sub_800AA1D4(o) == 0 && !(o->f0 & 0x1000))
        {
            SetModelFtg_80025B5C(o->model_40, 2, 0x17);
            SetModelFtg_80025B5C(o->model_40, 7, 0x19);
            sub_800AA3F0(o);
            break;
        }
        if (o->f10 == sub_800AB170(o->s1c))
        {
            SetModelFtg_80025B5C(o->model_40, 2, 0x18);
            SetModelFtg_80025B5C(o->model_40, 7, 0x1A);
        }
    case 8:
        if ((unsigned int)o->f10 >= (unsigned short)sub_800AC834(o->s1c, sub_800AC474(o->s1c)))
        {
            o->f8 = 10;
        }
        break;
    case 10:
        o->f0 = (o->f0 | 0x800) & ~0x8000;
        if (sub_800AA1D4(o) == 1)
        {
            if (o->f0 & 1)
            {
                o->f8 = 11;
            }
            break;
        }
        if (o->f0 & 2)
        {
            SetModelFtg_80025B5C(o->model_40, 2, 0x17);
            SetModelFtg_80025B5C(o->model_40, 7, 0x19);
            SetModelFtg_80025B5C(o->model_40, 0xC, 0xC);
        }
        if (o->f0 & 0x1000)
        {
            sub_800AC604(10, 0);
            sub_800AB010(o, 0x11, -1, -1);
            break;
        }
        if (o->f0 & 2)
        {
            sub_800AB010(o, 0x12, 3, 0);
        }
        else
        {
            sub_800AB010(o, 0x12, 0xF, 0);
        }
        o->f0 &= ~0x800;
        break;
    case 11:
        if (o->f0 & 0x1000000)
        {
            sub_800AC604(10, 0);
        }
        sub_800AC518(o->s20);
        sub_800AC604(o->s20, 0);
        o->f8 = 12;
        o->f2C = 0x46;
        if (o->f0 & 0x200)
        {
            sub_800ABCF4(o);
        }
        break;
    case 12:
        if (o->f2C == 0x46 || IsEffectReady_80014954() == 1 || o->f2C == 0x46)
        {
            if (sub_800AC768() == 1)
            {
                o->f8 = 13;
            }
        }
        break;
    case 13:
        if (o->f0 & 0x20)
        {
            if (!(sub_800AC900(o->s20, sub_800AC474(o->s20)) & 1))
            {
                if (o->s20 == o->s1c)
                {
                    sub_800AB010(o, 0x10, -1, -1);
                }
                else
                {
                    sub_800AB010(o, 0x10, o->s20, 0);
                }
            }
            else
            {
                sub_800AB010(o, 0xE, 0xF, 0);
                o->f0 &= ~0x800;
            }
            o->f0 &= ~0x20;
        }
        if ((unsigned short)(o->s20 - 0x19) < 2 || o->s20 == 0x1C)
        {
            o->s2A = 2;
        }
        else if ((unsigned short)(o->s20 - 7) < 2)
        {
            o->s2A = 0x1E;
        }
        else
        {
            o->s2A = 0;
        }
        break;
    case 14:
        if (o->f10 == sub_800AB170(o->s1c))
        {
            SetModelFtg_80025B5C(o->model_40, 2, 0x17);
            SetModelFtg_80025B5C(o->model_40, 7, 0x19);
        }
        if (o->f10 == sub_800AC8BC(o->s1c, sub_800AC474(o->s1c)))
        {
            sub_800AB010(o, 0x10, o->s20, 0);
        }
        break;
    case 16:
        sub_800ABDF0(o);
        if (o->s1c == 0x13 || o->s1c == 0x18)
        {
            o->f0 = (o->f0 & ~1) | 0x800;
            sub_800AB010(o, 0x14, o->s1c, 0);
        }
        else
        {
            o->f8 = 0xF;
        }
        sub_800AA430(o);
        break;
    case 15:
        o->f0 &= ~0x800;
        sub_800ABDF0(o);
        if (o->s1c == 0x19 || o->s1c == 7 || o->s1c == 0x1A || o->s1c == 0x1C || o->s1c == 8)
        {
            if ((unsigned int)o->f10 >= (unsigned short)sub_800AC878(o->s1c, sub_800AC474(o->s1c)))
            {
                if (effectOutcomeFlag_8008D780 == 1)
                {
                    o->s2A = -1;
                }
                else if (--o->s2A >= 0)
                {
                    o->f10 = (unsigned short)sub_800AC834(o->s1c, sub_800AC474(o->s1c));
                }
            }
        }
        if (o->f10 == sub_800AC8BC(o->s1c, sub_800AC474(o->s1c)))
        {
            r = sub_800AC900(o->s20, sub_800AC474(o->s20) & 1);
            if (r == 0)
            {
                if (o->f0 & 0x400)
                {
                    if (o->s1c == 0x14)
                    {
                        sub_800AB010(o, 10, -1, -1);
                    }
                    else
                    {
                        sub_800AB010(o, 8, 0x14, 0);
                    }
                }
                else if (o->f0 & 0x10000)
                {
                    if (o->s1c == 0x16)
                    {
                        sub_800AB010(o, 10, -1, -1);
                    }
                    else
                    {
                        sub_800AB010(o, 8, 0x16, 0);
                    }
                }
                else
                {
                    sub_800AB010(o, 10, 0xE, (unsigned short)sub_800AC878(0xE, sub_800AC474(0xE)));
                }
            }
            else if (o->f0 & 0x1000000)
            {
                sub_800AB010(o, 0x13, 10, 0);
            }
            else
            {
                sub_800AB010(o, 9, 0xE, 0);
            }
            o->f0 &= ~1;
        }
        break;
    case 17:
        if (sub_800AC768() == 1)
        {
            if (o->f0 & 2)
            {
                sub_800AB010(o, 0x12, 3, 0);
            }
            else
            {
                sub_800AB010(o, 0x12, 0xF, 0);
            }
            o->f0 &= ~0x800;
        }
        break;
    case 18:
        if (o->f10 == sub_800AB170(o->s1c))
        {
            SetModelFtg_80025B5C(o->model_40, 2, 0x17);
            SetModelFtg_80025B5C(o->model_40, 7, 0x19);
            SetModelFtg_80025B5C(o->model_40, 0xC, 0xC);
        }
        if ((unsigned int)o->f10 >= sub_800AC8BC(o->s1c, sub_800AC474(o->s1c)))
        {
            o->f0 &= ~0x800;
            if (o->f0 & 0x1000)
            {
                sub_800AB010(o, 0x13, 10, 0);
            }
            else
            {
                sub_800AA3F0(o);
            }
        }
        break;
    case 19:
        if ((unsigned int)o->f10 >= sub_800AC8BC(o->s1c, sub_800AC474(o->s1c)))
        {
            sub_800AA3F0(o);
        }
        break;
    case 20:
        if (!(o->f0 & 0x800))
        {
            sub_800AA3F0(o);
        }
        break;
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800AA51C);

void sub_800AACF8(G2Act* p)
{
    switch (p->f8)
    {
    case 0x17:
        if (p->f0 & 0x20)
        {
            if (p->f0 & 0x100000)
            {
                sub_800AB010(p, 0x18, p->s20, (unsigned short)sub_800AC834(p->s20, sub_800AC474(p->s20)));
            }
            else
            {
                sub_800AB010(p, 0x18, p->s20, 0);
            }
            p->f0 &= ~0x8000;
            if (p->s24 >= 0)
            {
                p->f0 &= ~0x800;
            }
        }
        break;
    case 0x18:
        if (p->f0 & 0x800000)
        {
            if (p->f0 & 0x800)
            {
                p->f0 &= ~0x800000;
                p->f10 = (unsigned short)sub_800AC834(p->s1c, sub_800AC474(p->s1c));
                p->f0 &= ~0x8000;
            }
            else
            {
                p->f0 &= ~0x800000;
                p->f10 = (unsigned short)sub_800AC8BC(p->s1c, sub_800AC474(p->s1c));
            }
        }
        if (p->f10 == (unsigned short)sub_800AC8BC(p->s1c, sub_800AC474(p->s1c)))
        {
            if (p->s24 < 0)
            {
                sub_800AB010(p, 0, 3, 0);
                p->fC = 0;
            }
            else
            {
                if (p->f0 & 0x100000)
                {
                    sub_800AB010(p, -1, p->s24, (unsigned short)sub_800AC834(p->s24, sub_800AC474(p->s24)));
                }
                else
                {
                    sub_800AB010(p, -1, p->s24, 0);
                }
                p->s24 = -1;
                p->s20 = p->u22;
                p->f0 |= 0x800;
            }
        }
        if (p->s20 != (short)p->u22)
        {
            if (sub_800AC604((short)p->u22, 0) == 0)
            {
                p->f8 = 0x17;
                p->s20 = p->u22;
            }
            else
            {
                printf(aAssertionFailed_800A07E0, aPLDISPC_800A0808, 0x44e);
                exit(1);
            }
        }
        break;
    }
}

void sub_800AAF58(G2Act* a)
{
    switch ((unsigned)a->fC)
    {
    case 0:
        sub_800AA25C(a);
        break;
    case 1:
        sub_800AA51C(a);
        break;
    case 2:
        sub_800AACF8(a);
        break;
    case 3:
        sub_800AC02C(a);
        break;
    default:
        break;
    }
}

int sub_800AAFD8(int a)
{
    if (sub_800AC518(a))
        return 1;
    sub_800AC6A8(a);
    return 0;
}

void sub_800AB010(G2Act* p, int a, int b, int c)
{
    if (c == 0)
        c = (short)sub_800AC7F0(b, sub_800AC474(b));
    if (p->f8 == a && p->s1c == b)
        return;
    p->s28 = 0;
    if (b < 0)
    {
        p->f8 = a;
    }
    else if (a < 0)
    {
        unsigned short t = p->s1c;
        int t3 = p->f10;
        p->s1c = b;
        p->f10 = c;
        p->s26 = 0;
        p->s1e = t;
        p->f14 = t3;
    }
    else
    {
        unsigned short t = p->s1c;
        int t3 = p->f10;
        p->f8 = a;
        p->s1c = b;
        p->f10 = c;
        p->s26 = 0;
        p->s1e = t;
        p->f14 = t3;
    }
    if (p->s1e != p->s1c)
    {
        p->f0 |= 8;
        if (sub_800AAFD8(p->s1e) == 1)
            p->f0 |= 0x10;
    }
}

void sub_800AB114(G2Obj* p)
{
    p->f30 = 0x1000;
    p->f0 = (p->f0 | 4) & ~2;
}

void sub_800AB134(G2Obj* p)
{
    p->f30 = 0;
    p->f0 = (p->f0 | 2) & ~4;
}

void sub_800AB150(G2Obj* p)
{
    p->f30 = 0;
    p->f0 &= ~4;
    p->f0 &= ~2;
}

unsigned short sub_800AB170(int a)
{
    return sub_800AC944(a, sub_800AC474(a));
}

void sub_800AB1A4(int a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    p->f0 |= 0x20;
    if (a == 1)
    {
        p->f0 |= 0x800;
        p->f0 &= ~0x8000;
    }
}

int sub_800AB1EC(int a, int b, int c, int d)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (!(p->f0 & 1))
    {
        if (b == 1)
            p->f0 |= 0x200;
        else
            p->f0 &= ~0x200;
        p->s20 = a;
        p->f38 = c;
        p->f34 = d;
        p->f0 &= ~0x2000;
        p->f0 |= 1;
        p->f0 &= ~0x20;
        return 1;
    }
    return 0;
}

void sub_800AB264()
{
    gameTask_8008B4A4->f24->f0 |= 0x400;
}

void sub_800AB28C()
{
    gameTask_8008B4A4->f24->f0 &= ~0x400;
}

void sub_800AB2B4()
{
    gameTask_8008B4A4->f24->f0 |= 0x10000;
}

void sub_800AB2DC()
{
    gameTask_8008B4A4->f24->f0 &= ~0x10000;
}

int sub_800AB304()
{
    return (gameTask_8008B4A4->f24->f0 & 1) ^ 1;
}

int sub_800AB32C()
{
    return gameTask_8008B4A4->f24->f8 == 0xD;
}

int sub_800AB354()
{
    unsigned t = gameTask_8008B4A4->f24->f0 & 0x400;
    return t != 0;
}

int sub_800AB37C(int v)
{
    gameTask_8008B4A4->f24->f4 = v;
    return 1;
}

int sub_800AB39C()
{
    return gameTask_8008B4A4->f24->f4;
}

void sub_800AB3BC()
{
    gameTask_8008B4A4->f24->s28 = 0;
}

void sub_800AB3D4()
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (!(p->f0 & 0x100))
    {
        p->f0 |= 0x4100;
        p->v60.a = levantPos_8008BD18.pos.x;
        p->v60.b = levantPos_8008BD18.pos.y;
        p->v60.c = levantPos_8008BD18.pos.z;
        p->v54.a = p->v48.a;
        p->v54.b = p->v48.b;
        p->v54.c = p->v48.c;
    }
}

void sub_800AB444(int a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (p->f0 & 0x100)
    {
        if (a == 1)
            p->f0 |= 0x1000;
        else
            p->f0 &= ~0x1000;
        p->f0 &= ~0x100;
        levantPos_8008BD18.pos.x = p->v60.a;
        levantPos_8008BD18.pos.y = p->v60.b;
        levantPos_8008BD18.pos.z = p->v60.c;
        p->v48.a = p->v60.a;
        p->v48.b = p->v60.b;
        p->v48.c = p->v60.c;
    }
}

short sub_800AB4D8(int a)
{
    int s = (unsigned short)sub_800AC834(a, sub_800AC474(a));
    int e = (unsigned short)sub_800AC878(a, sub_800AC474(a));
    int t;
    switch ((unsigned)a)
    {
    case 25:
    case 26:
    case 28:
        return sub_800AC8BC(a, sub_800AC474(a)) + (e - s) * 2;
    case 7:
    case 8:
        t = sub_800AC8BC(14, sub_800AC474(14));
        return t + sub_800AC8BC(a, sub_800AC474(a)) + (e - s) * 30;
    }
    return sub_800AC8BC(a, sub_800AC474(a));
}

short sub_800AB5F8(int a)
{
    return sub_800AC834(a, sub_800AC474(a));
}

short sub_800AB630(int a)
{
    int s = (unsigned short)sub_800AC834(a, sub_800AC474(a));
    int e = (unsigned short)sub_800AC878(a, sub_800AC474(a));
    int t;
    switch ((unsigned)a)
    {
    case 25:
    case 26:
    case 28:
        return sub_800AC878(a, sub_800AC474(a)) + (e - s) * 2;
    case 7:
    case 8:
        t = sub_800AC8BC(14, sub_800AC474(14));
        return t + sub_800AC878(a, sub_800AC474(a)) + (e - s) * 30;
    }
    return sub_800AC878(a, sub_800AC474(a));
}

short sub_800AB750(int a)
{
    int s = (unsigned short)sub_800AC834(a, sub_800AC474(a));
    int e = (unsigned short)sub_800AC878(a, sub_800AC474(a));
    short t;
    switch ((unsigned)a)
    {
    case 25:
    case 26:
    case 28:
        return sub_800AB170(a) + (e - s) * 2;
    case 7:
        t = sub_800AC8BC(14, sub_800AC474(14));
        t = t + sub_800AB170(a) + 0x4c;
        return t;
    case 8:
        t = sub_800AC8BC(14, sub_800AC474(14));
        t = t + sub_800AB170(a);
        return t;
    }
    return sub_800AB170(a);
}

int sub_800AB85C()
{
    unsigned t = gameTask_8008B4A4->f24->f0 & 0x2000;
    return t != 0;
}

void sub_800AB884()
{
    gameTask_8008B4A4->f24->f0 &= ~0x4000;
}

void sub_800AB8AC()
{
    sub_800A9414(gameTask_8008B4A4->f24, 0, 3);
}

void sub_800AB8DC()
{
    G2Act* p = gameTask_8008B4A4->f24;
    p->model_40 = sub_800AC38C();
}

void sub_800AB910()
{
    gameTask_8008B4A4->f24->f0 &= ~0x800;
}

int sub_800AB938()
{
    return ((unsigned char*)gameTask_8008B4A4->f24)[1] >> 7;
}

int sub_800AB958()
{
    return (unsigned)gameTask_8008B4A4->f24->f8 < 2;
}

void sub_800AB978(short a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    p->s24 = -1;
    p->u22 = a;
    p->f0 &= ~0x20;
}

void sub_800AB9A8(int a, int b, int c)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (sub_800AC604(a, 0) == 0 && (b < 0 || sub_800AC604(b, 0) == 0))
    {
        sub_800AB010(p, 0x17, a, 0);
        p->fC = 2;
        if (c)
            p->f0 |= 0x10;
        else
            p->f0 &= ~0x10;
    }
    else
    {
        printf(aAssertionFailed_800A07E0, aPLDISPC_800A0808, 0x6B9);
        exit(1);
    }
    p->u22 = a;
    p->s20 = a;
    p->s24 = b;
    p->f0 &= ~0x20;
    p->f0 &= ~1;
}

void sub_800ABAA4(G2Path* a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    p->path_78 = a;
    p->f7c = 0;
    p->f0 |= 0x400000;
}

void sub_800ABAD4()
{
    G2Act* p = gameTask_8008B4A4->f24;
    p->f0 &= ~0x400000;
    sub_800ABC78(0);
    p->f0 = (p->f0 & ~0x800) | 8;
    sub_800AB010(p, 0, 3, 0);
    p->fC = 0;
}

int sub_800ABB44()
{
    return ((gameTask_8008B4A4->f24->f0 >> 22) ^ 1) & 1;
}

int sub_800ABB70()
{
    return gameTask_8008B4A4->f24->f8 == 0x17;
}

void sub_800ABB98(int a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (a == 1)
        p->f0 |= 0x100000;
    else
        p->f0 &= ~0x100000;
}

void sub_800ABBD8(int a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (a)
    {
        p->f0 &= ~0x20000;
        sub_800AB150((G2Obj*)p);
    }
    else
    {
        p->f0 |= 0x20000;
    }
}

void sub_800ABC34(int a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (a)
        p->f0 &= ~0x40000;
    else
        p->f0 |= 0x40000;
}

void sub_800ABC78(int a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (a)
    {
        p->f0 |= 0x80000;
        p->v60.a = levantPos_8008BD18.pos.x;
        p->v60.b = levantPos_8008BD18.pos.y;
        p->v60.c = levantPos_8008BD18.pos.z;
        p->v54.a = p->v48.a;
        p->v54.b = p->v48.b;
        p->v54.c = p->v48.c;
    }
    else
    {
        p->f0 &= ~0x80000;
    }
}

void sub_800ABCF4(G2Act* p)
{
    if (p->s20 == 0x19)
    {
        p->f2C = GetMagicEffect_8001AC8C(p->f34);
        RequestEffect_800148F4(p->f2C);
    }
    else if ((unsigned short)(p->s20 - 7) < 2)
    {
        p->f2C = 0x25;
        RequestEffect_800148F4(0x25);
        sub_80013358(p->f34);
        word_8008D782 = sub_80013358(p->f34);
    }
    else if (p->s20 == 0x1A)
    {
        p->f2C = 0x39;
        RequestEffect_800148F4(p->f2C);
    }
    else if (p->s20 == 0x1C)
    {
        p->f2C = 0x3A;
        RequestEffect_800148F4(p->f2C);
    }
    else if (p->s20 == 0x10)
    {
        p->f2C = GetWeaponEffect_800189F8();
        RequestEffect_800148F4(p->f2C);
    }
    else if (p->s20 == 0x1D)
    {
        p->f2C = ((int (*)(int))GetItemEffect_8001CDCC)(p->f34);
        RequestEffect_800148F4(p->f2C);
    }
}

void sub_800ABDF0(G2Act* a)
{
    if (a->s1c == 0x1A)
    {
        if (a->f10 == (unsigned short)sub_800AC834(a->s1c, sub_800AC474(0x1A)))
            sub_800AB134((G2Obj*)a);
    }
    if (a->s1c == 0x1D)
    {
        if (a->f10 == (unsigned short)sub_800AB170(0x1D))
            PlaySfx_80031494(0x44);
        if (a->f10 == (unsigned short)sub_800AB170(a->s1c) - 10)
            PlaySeqSlot_80031160(0x1D, 1);
    }
    if (a->s1c == 0x1C && a->f10 == 2)
        sub_800AB114((G2Obj*)a);
}

void sub_800ABECC()
{
    G2V12* r = &dword_8007A164;
    unsigned int f = dword_8008BD38;
    if (f & 0x200)
    {
        if (f & 1)
            r = &statusTintPoisonLevel7_8007A14C;
        else
            r = &statusTintLevel7_8007A0EC;
    }
    else if (f & 0x100)
    {
        if (f & 1)
            r = &statusTintPoisonLevel6_8007A140;
        else
            r = &statusTintLevel6_8007A0E0;
    }
    else if (f & 0x80)
    {
        if (f & 1)
            r = &statusTintPoisonLevel5_8007A134;
        else
            r = &statusTintLevel5_8007A0D4;
    }
    else if (f & 0x40)
    {
        if (f & 1)
            r = &statusTintPoisonLevel4_8007A128;
        else
            r = &statusTintLevel4_8007A0C8;
    }
    else if (f & 0x20)
    {
        if (f & 1)
            r = &statusTintPoisonLevel3_8007A11C;
        else
            r = &statusTintLevel3_8007A0BC;
    }
    else if (f & 0x10)
    {
        if (f & 1)
            r = &statusTintPoisonLevel2_8007A110;
        else
            r = &statusTintLevel2_8007A0B0;
    }
    else if (f & 8)
    {
        if (f & 1)
            r = &dword_8007A104;
        else
            r = &statusTintLevel1_8007A0A4;
    }
    else if (f & 1)
    {
        r = &statusTintPoison_8007A0F8;
    }
    TintVramImage_800292D0(&dword_8007DC80, &dword_8007DC88, r);
}

void sub_800AC02C(G2Act* p)
{
    switch (p->f8)
    {
    case 0x15:
        if (p->s26 >= 0x1000)
        {
            p->f0 &= ~0x10;
            sub_800AC604(p->s20, 0);
            p->f8 = 0x16;
        }
        break;
    case 0x16:
        if (sub_800AC768() == 1)
        {
            p->f8 = 0x17;
        }
        break;
    case 0x17:
        if (p->f0 & 0x20)
        {
            if (p->f0 & 0x100000)
            {
                sub_800AB010(p, 0x18, p->s20, (unsigned short)sub_800AC834(p->s20, sub_800AC474(p->s20)));
            }
            else
            {
                sub_800AB010(p, 0x18, p->s20, 0);
            }
            p->f0 &= ~0x8000;
            if (p->s24 >= 0)
            {
                p->f0 &= ~0x800;
            }
        }
        break;
    case 0x18:
        if (p->f10 == (unsigned short)sub_800AC8BC(p->s1c, sub_800AC474(p->s1c)))
        {
            if (p->s24 < 0)
            {
                sub_800AB010(p, 0, 3, 0);
                p->fC = 0;
                if (sub_800AAFD8(p->s20) == 1)
                {
                    p->f0 |= 0x10;
                }
            }
            else
            {
                if (p->f0 & 0x100000)
                {
                    sub_800AB010(p, -1, p->s24, 0);
                }
                else
                {
                    sub_800AB010(p, -1, p->s24, (unsigned short)sub_800AC834(p->s24, sub_800AC474(p->s24)));
                }
                p->s20 = p->u22;
                if (sub_800AAFD8(p->s20) == 1)
                {
                    p->f0 |= 0x10;
                }
                p->f0 |= 0x800;
            }
        }
        if (p->s20 != (short)p->u22)
        {
            if (sub_800AC604((short)p->u22, 0) == 0)
            {
                p->s20 = p->u22;
                p->f8 = 0x17;
                if (sub_800AAFD8(p->s20) == 1)
                {
                    p->f0 |= 0x10;
                }
            }
            else
            {
                sub_800AB010(p, 0x19, 3, 0);
                p->f0 |= 0x10;
            }
        }
        break;
    case 0x19:
        if (p->s26 >= 0x1000)
        {
            p->f0 &= ~0x10;
            sub_800AAFD8(p->s20);
            p->s20 = p->u22;
            sub_800AC604(p->s20, 0);
            p->f8 = 0x16;
        }
        break;
    case 0x1a:
        break;
    }
}

void sub_800AC318()
{
    gameTask_8008B4A4->f24->f0 |= 0x800000;
}

void sub_800AC340(int a)
{
    G2Act* p = gameTask_8008B4A4->f24;
    if (a)
        p->f0 |= 0x1000000;
    else
        p->f0 &= ~0x1000000;
}

void sub_800AC380(int v)
{
    dword_8008BDA0 = v;
}

Model* sub_800AC38C()
{
    return dword_8007DC60->items_8;
}

void sub_800AC3A4(short v)
{
    word_8008BDA4 = v;
}

void sub_800AC3B0(int a)
{
    word_8008BDA6 = a;
    sub_800AC380(1);
}

char* sub_800AC3D8()
{
    return &dword_800B1DF8;
}

int sub_800AC3E4()
{
    return word_8008BDA4;
}

int sub_800AC3F4()
{
    SaveData* s = &saveData_8008B570;
    int r;
    if (s->field_830)
    {
        r = ((int (*)(int))GetArmorOutfit_8001D060)(s->levantStatus_7C8.field_1C[1]) + dword_800B11B8[s->field_834];
    }
    else
    {
        r = dword_800B116C[s->field_834];
    }
    return r;
}

int sub_800AC464()
{
    return word_8008BDA6;
}

int sub_800AC474(int a)
{
    return dword_800B11DC[sub_800AC3E4()];
}

int sub_800AC4A8(int a)
{
    G2Rec* p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[sub_800AC794(a, dword_800B11DC[sub_800AC3E4()])].f0;
}

int sub_800AC518(int a)
{
    G2Rec* p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    if (p[r].f1)
        return 1;
    return IsAnimInModelAnimSet_80025924(dword_8007DC60->items_8, (short)sub_800AC988(a, dword_800B11DC[sub_800AC3E4()]));
}

int sub_800AC5D0(int a, int b)
{
    return LoadModelAnim_80025440(dword_8007DC60->items_8, a, b) != 0;
}

int sub_800AC604(int a, int b)
{
    int t = dword_800B11DC[sub_800AC3E4()];
    return LoadModelAnim_80025440(dword_8007DC60->items_8, (short)sub_800AC988(a, t), b) != 0;
}

void sub_800AC678(int a)
{
    FreeModelAnim_8002556C(dword_8007DC60->items_8, a);
}

void sub_800AC6A8(int a)
{
    int t = dword_800B11DC[sub_800AC3E4()];
    FreeModelAnim_8002556C(dword_8007DC60->items_8, (short)sub_800AC988(a, t));
}

void sub_800AC708(int a, int b)
{
    LoadModelAnimSet_80025780(dword_8007DC60->items_8, a, b);
}

void sub_800AC73C()
{
    FreeModelAnimSet_80025884(dword_8007DC60->items_8);
}

int sub_800AC768()
{
    return AreFileRequestsDone_80024DC4(dword_8007DC60->items_8);
}

int sub_800AC794(int a, int b)
{
    if ((unsigned)(a - 0xE) >= 0x60)
        return a;
    return a + b * 16;
}

unsigned char* sub_800AC7B4(int a)
{
    return (unsigned char*)GetModelActorAnims_80024E38(dword_8007DC60->items_8) + ((a << 10) + 0x380);
}

short sub_800AC7F0(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[r].s4;
}

short sub_800AC834(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[r].s6;
}

short sub_800AC878(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[r].s8;
}

unsigned short sub_800AC8BC(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[r].sA;
}

unsigned char sub_800AC900(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[r].f3;
}

short sub_800AC944(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[r].sC;
}

unsigned char sub_800AC988(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return p[r].f0;
}

short* sub_800AC9CC(int a)
{
    G2Rec* p;
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return &p[r].sC;
}

int* sub_800ACA38(int a)
{
    G2Rec* p;
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    p = GetModelActorAnims_80024E38(dword_8007DC60->items_8);
    return &p[r].f34;
}

void sub_800ACAA4(int* a, int* b)
{
    SaveData* s = &saveData_8008B570;
    b[0] = 0;
    b[1] = 0;
    b[2] = -1;
    b[3] = -1;
    b[4] = -1;
    b[5] = -1;
    b[6] = -1;
    b[7] = -1;
    b[8] = -1;
    b[9] = 0;
    sub_800AC380(s->levantStatus_7C8.field_1C[1] != 0xFF);
    sub_800AC3A4(GetWeaponData_8001CF84(s->levantStatus_7C8.field_1C[0])->field_2);
    PoolInit_8003FF1C(&dword_800B1DD0, 0x2BF20);
    sub_800ACB64(a, b);
    a[2] = (int)sub_800ACB64;
}

typedef struct G2Ld_1
{
    int state;
    int flags;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
} G2Ld_1;
extern ModelVramSlot* dword_8007DC6C;
extern int name_800B1164[];
extern void sub_800ACF3C();
extern void sub_800ACFB8();
// Matched
void sub_800ACB64(int* a, void* buf)
{
    int more = 1;
    G2Ld_1* q = buf;
    Model* m;
    do
    {
        switch (q->state)
        {
        case 0:
            if (q->f8 != saveData_8008B570.field_830)
            {
                q->f10 = -1;
                q->flags |= 0xd;
                sub_800AC3A4(saveData_8008B570.field_834);
            }
            if (q->f10 != saveData_8008B570.field_834 || q->f18 != saveData_8008B570.field_836)
            {
                q->flags |= 0x16;
                sub_800ACF3C(q);
            }
            if (q->flags == 0)
            {
                more = 0;
            }
            else
            {
                PoolSetInited_80040148((int*)&dword_800B1DD0, 1);
                q->state = 1;
            }
            break;
        case 1:
            if (q->flags & 1)
            {
                if (dword_8007DC60)
                {
                    FreeModelList_80024BB0(&dword_8007DC60);
                }
                InitModelList_80024ADC(&dword_8007DC60, dword_8007DC6C, (int)&dword_800B1DD0);
                LoadModel_80025200(dword_8007DC60, name_800B1164[saveData_8008B570.field_830], 0, 2, 1);
                q->fC = q->f8;
                q->f8 = saveData_8008B570.field_830;
                q->flags &= ~1;
            }
            else if (q->flags & 2)
            {
                m = AcquireModel_80024D70(dword_8007DC60, name_800B1164[saveData_8008B570.field_830]);
                LoadModelAltFtgs_80025974(m, sub_800AC3F4(), 1);
                q->f14 = sub_800AC3E4();
                q->f10 = saveData_8008B570.field_834;
                q->f1C = sub_800AC464();
                q->f18 = saveData_8008B570.field_836;
                q->flags &= ~2;
            }
            else if (q->flags & 4)
            {
                sub_800ACFB8(q);
                q->flags &= ~4;
            }
            BeginFade_8001C260();
            eventDispatchHalt_8008B540 = 1;
            ClearOTagRAll_8001B260();
            q->state = 2;
            break;
        case 2:
            if (AreFileRequestsDone_80024DC4(dword_8007DC60->items_8) == 1)
            {
                q->state = 3;
            }
            else
            {
                more = 0;
                eventDispatchHalt_8008B540 = 1;
            }
            break;
        case 3:
            if ((q->flags & 9) == 8)
            {
                m = AcquireModel_80024D70(dword_8007DC60, name_800B1164[saveData_8008B570.field_830]);
                SaveModelFtgs_80024FFC(m, dword_800B11CC);
                q->flags &= ~8;
            }
            if ((q->flags & 0x12) == 0x10)
            {
                m = AcquireModel_80024D70(dword_8007DC60, name_800B1164[saveData_8008B570.field_830]);
                ApplyModelFtgSwaps_80025C38(m, (((unsigned)unknownFlags_8008D678 >> 24) ^ 1) & 1);
                q->flags &= ~0x10;
            }
            if (q->flags == 0)
            {
                more = 0;
                sub_800AB8DC();
                ClearOTagRAll_8001B260();
                EndFade_8001C290();
            }
            PoolSetInited_80040148((int*)&dword_800B1DD0, 0);
            q->state = 0;
            break;
        }
    } while (more);
}

void sub_800ACF0C()
{
    FreeModelList_80024BB0(&dword_8007DC60);
    PoolDestroy_8003FF7C(&dword_800B1DD0);
}

void sub_800ACF3C(G2Act* p)
{
    unsigned char* q;
    int i;
    if (p->f14 >= 0)
    {
        q = sub_800AC7B4(dword_800B11DC[p->f14]);
        for (i = 0; i < 16; i++, q += 0x40)
        {
            if (q[1])
                sub_800AC678(q[0]);
        }
    }
}

void sub_800ACFB8()
{
    unsigned char* p = sub_800AC7B4(dword_800B11DC[sub_800AC3E4()]);
    int i;
    for (i = 0; i < 16; i++, p += 0x40)
    {
        if (p[1])
            sub_800AC5D0(p[0], 1);
    }
}

int sub_800AD02C()
{
    int v = playerYan_8008B594.yan_0;
    if (v > 9999999)
        v = 9999999;
    return v;
}

int sub_800AD058(int a)
{
    SaveData* s = &saveData_8008B570;
    int v;
    if (s->inv_24.yan_0 <= 9999998)
    {
        v = s->inv_24.yan_0 + a;
        if (v <= 9999998)
            s->inv_24.yan_0 = v;
        else
            s->inv_24.yan_0 = 9999999;
        return 1;
    }
    return 0;
}

int sub_800AD0A4(int a)
{
    SaveData* s = &saveData_8008B570;
    if (s->inv_24.yan_0 >= a)
    {
        s->inv_24.yan_0 -= a;
        return 1;
    }
    return 0;
}

int sub_800AD0D4(unsigned a)
{
    return (playerYan_8008B594.bits_290[a >> 3] >> (a & 7)) & 1;
}

void sub_800AD0F8(unsigned a)
{
    playerYan_8008B594.bits_290[a >> 3] |= 1 << (a & 7);
}

void sub_800AD124(unsigned a)
{
    playerYan_8008B594.bits_290[a >> 3] &= ~(1 << (a & 7));
}

int sub_800AD154(int a)
{
    return playerYan_8008B594.vars_2A3[a];
}

int sub_800AD16C(int a, int b)
{
    playerYan_8008B594.vars_2A3[a] = b;
    return b;
}

int sub_800AD184(int a, int b, int c)
{
    InvSlot* r = sub_800AD4D8(a, b, c);
    if (r && a != 0xFF)
    {
        r->id = a;
        r->count += b;
        return 1;
    }
    return 0;
}

int sub_800AD1E0(int a, int b, int c)
{
    InvSlot* r = sub_800AD58C(a, c);
    if (r)
    {
        if (sub_800AD67C(r->count, b))
        {
            r->count -= b;
            if (r->count == 0)
                r->id = 0xFF;
            return 1;
        }
    }
    return 0;
}

int sub_800AD254()
{
    InvSlot* r = sub_800AD58C();
    if (r)
        return r->count;
    return 0;
}

int sub_800AD288(int a, int b)
{
    InvSlot* p = sub_800AD604(b);
    if (p)
        return p[a].id;
    return 0xFF;
}

int sub_800AD2C8(int a, int b)
{
    InvSlot* p = sub_800AD604(b);
    if (p)
        return p[a].count;
    return 0;
}

int sub_800AD308(int a)
{
    InvSlot* p = sub_800AD604(a);
    int n = sub_800AD374(a);
    int i;
    if (p)
    {
        for (i = n - 1; i > 0; i--)
        {
            if (p[i].id != 0xFF)
                return i;
        }
    }
    return 0;
}

int sub_800AD374(int a)
{
    int r;
    unsigned u = a;
    r = 0;
    if (u < 4)
        goto L;
    if (u == 4)
    {
    L:
        r = 0x40;
    }
    return r;
}

int sub_800AD398()
{
    int x;
    if (sub_800AD308(4) > 0)
        return 1;
    if (sub_800AD288(0, 4) != 0xFF)
    {
        x = sub_800AD2C8(0, 4);
        if (x)
            return 1;
    }
    return 0;
}

void sub_800AD3F0(int a)
{
    unsigned char tmp[2];
    int n = sub_800AD374(a);
    InvSlot* tbl = sub_800AD604(a);
    short cnt = 0;
    short i;
    InvSlot* r;
    for (i = 0; i < n; i++)
    {
        r = sub_800AD58C(i, a);
        if (r)
        {
            MemCopy_800403E8(tmp, &tbl[cnt], 2);
            MemCopy_800403E8(&tbl[cnt], r, 2);
            MemCopy_800403E8(r, tmp, 2);
            cnt++;
        }
    }
}

InvSlot* sub_800AD4D8(int a, int b, int c)
{
    InvSlot* r = sub_800AD58C(a, c);
    if (r)
    {
        if (sub_800AD670(r->count, b))
        {
            if ((unsigned)(c - 1) < 3 && a == sub_800AD990(c - 1))
            {
                if (!(r->count + b < 0x14))
                    return 0;
            }
            return r;
        }
        return 0;
    }
    return sub_800AD58C(0xFF, c);
}

InvSlot* sub_800AD58C(int a, int b)
{
    int n = sub_800AD374(b);
    InvSlot* p = sub_800AD604(b);
    int i;
    if (p != 0)
    {
        for (i = 0; i < n; i++)
        {
            if (a == p[i].id)
                return &p[i];
        }
    }
    return 0;
}

InvSlot* sub_800AD604(int n)
{
    switch ((unsigned)n)
    {
    case 0:
        return saveData_8008B570.inv_24.inventory_4[0];
    case 1:
        return saveData_8008B570.inv_24.inventory_4[1];
    case 2:
        return saveData_8008B570.inv_24.inventory_4[2];
    case 3:
        return saveData_8008B570.inv_24.inventory_4[3];
    case 4:
        return saveData_8008B570.inv_24.inventory_4[4];
    }
    return 0;
}

int sub_800AD670(int a, int b)
{
    return a + b < 0x15;
}

int sub_800AD67C(int a, int b)
{
    return (a - b) >= 0;
}

int sub_800AD68C(int n)
{
    SaveInventory* f = &playerYan_8008B594;
    if (n < 0x40)
    {
        f->flags_288[n / 32] |= 1 << (n % 32);
        return 1;
    }
    return 0;
}

void sub_800AD6E4(int n)
{
    SaveInventory* f = &playerYan_8008B594;
    if (n < 0x40)
        f->flags_288[n / 32] &= ~(1 << (n % 32));
}

int sub_800AD73C(int n)
{
    SaveInventory* f = &playerYan_8008B594;
    if (n < 0x40)
    {
        if (f->flags_288[n / 32] & (1 << (n % 32)))
            return 1;
    }
    return 0;
}

int sub_800AD79C()
{
    short i;
    int c = 0;
    for (i = 0; i < 0x26; i++)
    {
        if (sub_800AD73C(i))
            c++;
    }
    return c;
}

int sub_800AD7F8(int a)
{
    short i;
    int c = 0;
    for (i = 0; i < 0x26; i++)
    {
        if (sub_800AD73C(i))
        {
            if (a == (short)c++)
                return i;
        }
    }
    return 0x26;
}

int sub_800AD888()
{
    int v = 12 - sub_800AD8BC();
    if (v < 0)
        v = 0;
    return v;
}

int sub_800AD8BC()
{
    return levantEmptyCocoons_8008B818 + CountMinions_80010548(0);
}

int sub_800AD8E4()
{
    return levantEmptyCocoons_8008B818;
}

int sub_800AD8F4(int a)
{
    int ret = 1;
    int v = sub_800AD8E4() + a;
    if (v >= 13)
    {
        v = 12;
        ret = 0;
    }
    levantEmptyCocoons_8008B818 = v;
    return ret;
}

int sub_800AD944(int a)
{
    int ret = 1;
    int v = sub_800AD8E4() - a;
    if (v < 0)
    {
        v = 0;
        ret = v;
    }
    levantEmptyCocoons_8008B818 = v;
    return ret;
}

unsigned int sub_800AD990(int a)
{
    unsigned int r = 0;
    switch ((unsigned)a)
    {
    case 0:
        r = equippedWeaponId_8008BD54;
        break;
    case 1:
        r = equippedArmor_8008BD55;
        break;
    case 2:
        r = byte_8008BD56;
        break;
    }
    return r;
}

int SetEquipment_800AD9EC(int a, int b)
{
    unsigned char old = sub_800AD990(b);
    SaveData* s;
    switch ((unsigned)b)
    {
    case 0:
        if (old == 0xFF)
        {
            if (a == 0xFF)
                return 1;
        }
        else if (a == 0xFF)
        {
            goto fail;
        }
        s = &saveData_8008B570;
        s->levantStatus_7C8.field_1C[0] = a;
        sub_800AD1E0(a, 1, 1);
        if (old < 0x17)
            sub_800AD184(old, 1, 1);
        sub_800AC3A4(GetWeaponData_8001CF84(a)->field_2);
        GetArmorData_8001D034(s->levantStatus_7C8.field_1C[1]);
        sub_800AC3B0(dword_8001D060(s->levantStatus_7C8.field_1C[1]));
        break;
    case 1:
        if (old == 0xFF)
        {
            if (a == 0xFF)
                return 1;
        }
        else if (a == 0xFF)
        {
            goto fail;
        }
        s = &saveData_8008B570;
        s->levantStatus_7C8.field_1C[1] = a;
        sub_800AD1E0(a, 1, 2);
        if (old < 0xF)
            sub_800AD184(old, 1, 2);
        sub_800AC3A4(GetWeaponData_8001CF84(s->levantStatus_7C8.field_1C[0])->field_2);
        GetArmorData_8001D034(a);
        sub_800AC3B0(dword_8001D060(a));
        break;
    fail:
        return 0;
    case 2:
        byte_8008BD56 = a;
        sub_800AD1E0(a, 1, 3);
        if (old != 0xFF)
            sub_800AD184(old, 1, 3);
        break;
    }
    return 1;
}

int sub_800ADBA0(short* p)
{
    SaveData* base = &saveData_8008B570;
    int i;
    for (i = 0; i < base->nMapVars_2F4; i++)
    {
        if (base->mapVars_2F8[i].area_0 == p[0] && base->mapVars_2F8[i].map_2 == p[1] && base->mapVars_2F8[i].sub_4 == p[2])
            return i;
    }
    return -1;
}

int sub_800ADC1C(short* p)
{
    int r = sub_800ADBA0(p);
    if (r != -1)
        r = saveData_8008B570.mapVars_2F8[r].value_6;
    return r;
}

void sub_800ADC5C(unsigned short* p, int b)
{
    int i;
    if (b != -2)
    {
        i = sub_800ADBA0((short*)p);
        if (i == -1)
            i = saveData_8008B570.nMapVars_2F4++;
        saveData_8008B570.mapVars_2F8[i].area_0 = p[0];
        saveData_8008B570.mapVars_2F8[i].map_2 = p[1];
        saveData_8008B570.mapVars_2F8[i].sub_4 = p[2];
        saveData_8008B570.mapVars_2F8[i].value_6 = b;
    }
}

void sub_800ADCEC(short* out, int key)
{
    int i, j, k;
    G2Ent16** row;
    G2Ent16* e;
    for (i = 0; name_800B0608[i]; i++)
    {
        row = name_800B0608[i];
        for (j = 0; row[j]; j++)
        {
            e = row[j];
            for (k = 0; e[k].id != -1; k++)
            {
                if (key == e[k].s6)
                {
                    out[0] = i;
                    out[1] = j;
                    out[2] = k;
                    out[3] = e[k].u4;
                    return;
                }
            }
        }
    }
}

#if 0
// Not matched: loop registers rotated (key/-1/saveData copy get $a2/$a3/$t0 instead of $a3/$t0/$a2)
void sub_800ADDAC(void)
{
    GameS3_1 v;
    int r;
    int i;
    int key;
    G2Ent16* e;
    v.a = saveData_8008B570.mapId_2E4[0].field_0;
    v.b = saveData_8008B570.mapId_2E4[1].field_0;
    v.c = saveData_8008B570.mapId_2E4[2].field_0;
    r = sub_800ADC1C(&v);
    e = name_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0];
    key = saveData_8008B570.mapId_2E4[2].field_0;
    i = 0;
    if (e->id >= 0)
    {
        do
        {
            if (key == (short)e[i].u4 && (r == -1 || r == e[i].s6))
            {
                saveData_8008B570.mapId_2E4[2].field_0 = i;
                return;
            }
            i++;
        } while (e[i].id >= 0);
    }
}
#endif

INCLUDE_OVERLAY_ASM(game, sub_800ADDAC);

GameRec_1 dword_800ADE78 = { 0 };
short dword_800ADE8C[2] = { 0 };
short dword_800ADE90[2] = { -0x11C, 0x11C };
short dword_800ADE94[4] = { -0x200, 0, 0x200 };
short *dword_800ADE9C[7] = { dword_800ADE8C, dword_800ADE90, dword_800ADE94, (short *)0x61A80, (short *)0xDBBA0, (short *)0x155CC0, (short *)0x1CFDE0 };
void (*name_800ADEB8[53][2])() = {
    { sub_800A333C, sub_800A3E88 },
    { sub_800A333C, sub_800A3E88 },
    { sub_800A333C, sub_800A3E88 },
    { sub_800A3804, sub_800A3E88 },
    { sub_800A3804, sub_800A3E88 },
    { sub_800A3804, sub_800A3E88 },
    { sub_800A31DC, sub_800A31DC },
    { sub_800A3FC0, sub_800A3E88 },
    { sub_800A3FC0, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A34D8, sub_800A3E88 },
    { sub_800A3A8C, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A3954, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A3BEC, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A34D8, sub_800A3E88 },
    { sub_800A366C, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A3D24, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2EEC, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
    { sub_800A2FB8, sub_800A3E88 },
};
short dword_800AE060[8] = { 106, 107, 109, 111, 112, 114, -1 };
short dword_800AE070[10] = {
    118, 119, 120, 121, 122, 124, 132, 133,
    -1,
};
short dword_800AE084[4] = { 125, 126, -1 };
short dword_800AE08C[4] = { 123, 128, 131, -1 };
short dword_800AE094[2] = { 129, -1 };
short dword_800AE098[2] = { 110, -1 };
short dword_800AE09C[2] = { 108, -1 };
short dword_800AE0A0[14] = {
    143, 144, 145, 146, 147, 148, 149, 151,
    153, 155, 157, 160, 162, -1,
};
short dword_800AE0BC[8] = { 137, 138, 139, 140, 141, 142, -1 };
short dword_800AE0CC[4] = { 158, 159, -1 };
short dword_800AE0D4[2] = { 161, -1 };
short dword_800AE0D8[14] = {
    168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 181, 183, -1,
};
short dword_800AE0F4[6] = { 163, 164, 165, 166, 167, -1 };
short dword_800AE100[4] = { 179, 180, -1 };
short dword_800AE108[2] = { 182, -1 };
short dword_800AE10C[2] = { 217, -1 };
short dword_800AE110[2] = { 228, -1 };
short dword_800AE114[2] = { 0x104, -1 };
short dword_800AE118[2] = { 0x105, -1 };
short dword_800AE11C[2] = { 0x107, -1 };
short dword_800AE120[6] = { 186, 187, 188, 189, 190, -1 };
short dword_800AE12C[4] = { 195, 196, -1 };
short dword_800AE134[6] = { 191, 192, 193, 194, -1 };
short dword_800AE140[8] = { 210, 211, 213, 215, 216, 217, -1 };
short dword_800AE150[8] = { 221, 222, 223, 224, 225, 227, 234, -1 };
short dword_800AE160[2] = { 228, -1 };
short dword_800AE164[4] = { 226, 230, 233, -1 };
short dword_800AE16C[2] = { 231, -1 };
short dword_800AE170[2] = { 214, -1 };
short dword_800AE174[2] = { 212, -1 };
short dword_800AE178[18] = {
    242, 243, 244, 245, 246, 247, 248, 249,
    250, 251, 252, 253, 254, 255, 0x102, 0x104,
    -1,
};
short dword_800AE19C[6] = { 237, 238, 239, 240, 241, -1 };
short dword_800AE1A8[4] = { 0x100, 0x101, -1 };
short dword_800AE1B0[2] = { 0x103, -1 };
short dword_800AE1B4[16] = {
    0x117, 0x118, 0x119, 0x11A, 0x11B, 0x11C, 0x11D, 0x11E,
    0x11F, 0x120, 0x121, 0x122, 0x123, 0x124, 0x125, -1,
};
short dword_800AE1D4[16] = {
    0x126, 0x127, 0x128, 0x129, 0x12A, 0x12B, 0x12C, 0x12D,
    0x12E, 0x12F, 0x130, 0x131, 0x132, 0x133, 0x134, -1,
};
short dword_800AE1F4[16] = {
    0x135, 0x136, 0x137, 0x138, 0x139, 0x13A, 0x13B, 0x13C,
    0x13D, 0x13E, 0x13F, 0x140, 0x141, 0x142, 0x143, -1,
};
short dword_800AE214[16] = {
    0x144, 0x145, 0x146, 0x147, 0x148, 0x149, 0x14A, 0x14B,
    0x14C, 0x14D, 0x14E, 0x14F, 0x150, 0x151, 0x152, -1,
};
short dword_800AE234[16] = {
    0x108, 0x109, 0x10A, 0x10B, 0x10C, 0x10D, 0x10E, 0x10F,
    0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, -1,
};
short *dword_800AE254[39] = {
    dword_800AE060, dword_800AE070, dword_800AE084, dword_800AE08C,
    dword_800AE094, dword_800AE098, dword_800AE09C, dword_800AE0A0,
    dword_800AE0BC, dword_800AE0CC, dword_800AE0D4, dword_800AE0D8,
    dword_800AE0F4, dword_800AE100, dword_800AE108, dword_800AE10C,
    dword_800AE110, dword_800AE114, dword_800AE118, dword_800AE11C,
    dword_800AE120, dword_800AE12C, dword_800AE134, dword_800AE140,
    dword_800AE150, dword_800AE160, dword_800AE164, dword_800AE16C,
    dword_800AE170, dword_800AE174, dword_800AE178, dword_800AE19C,
    dword_800AE1A8, dword_800AE1B0, dword_800AE1B4, dword_800AE1D4,
    dword_800AE1F4, dword_800AE214, dword_800AE234,
};
short dword_800AE2F0[6] = { 106, 107, 108, 109, 112, -1 };
short dword_800AE2FC[4] = { 110, 111, 114, -1 };
short dword_800AE304[2] = { -1 };
short dword_800AE308[8] = { 118, 119, 120, 121, 122, 124, 132, -1 };
short dword_800AE318[6] = { 123, 128, 129, 131, -1 };
short dword_800AE324[6] = { 137, 138, 139, 143, 144, -1 };
short dword_800AE330[6] = { 140, 142, 145, 146, 147, -1 };
short dword_800AE33C[6] = { 158, 159, 160, 161, -1 };
short dword_800AE348[16] = {
    163, 164, 165, 166, 167, 168, 169, 170,
    171, 172, 179, 180, 181, 182, -1,
};
short dword_800AE368[10] = {
    186, 187, 188, 189, 191, 192, 193, 194,
    195, -1,
};
short dword_800AE37C[4] = { 210, 211, 212, -1 };
short dword_800AE384[6] = { 213, 214, 215, 216, 217, -1 };
short dword_800AE390[8] = { 221, 222, 223, 224, 225, 227, 234, -1 };
short dword_800AE3A0[6] = { 226, 230, 231, 233, -1 };
short dword_800AE3AC[6] = { 237, 238, 239, 242, 243, -1 };
short dword_800AE3B8[6] = { 240, 241, 244, 245, 246, -1 };
short dword_800AE3C4[6] = { 0x100, 0x101, 0x102, 0x103, -1 };
short *dword_800AE3D0[17] = {
    dword_800AE2F0, dword_800AE2FC, dword_800AE304, dword_800AE308,
    dword_800AE318, dword_800AE324, dword_800AE330, dword_800AE33C,
    dword_800AE348, dword_800AE368, dword_800AE37C, dword_800AE384,
    dword_800AE390, dword_800AE3A0, dword_800AE3AC, dword_800AE3B8,
    dword_800AE3C4,
};
int dword_800AE414[3] = { 15, 12, 6 };
int dword_800AE420[3] = { 18, 0, 6 };
int dword_800AE42C[3] = { 12, 15, 6 };
int dword_800AE438[3] = { 0, 9, 27 };
int dword_800AE444[3] = { 27, 10, 26 };
int dword_800AE450[3] = { 3, 14, 17 };
int dword_800AE45C[3] = { 17, 7, 14 };
int dword_800AE468[3] = { 19, 23, 17 };
int dword_800AE474[3] = { 30, 30, 30 };
int dword_800AE480[3] = { 1, 21, 16 };
int dword_800AE48C[3] = { 13, 2, 28 };
int dword_800AE498[3] = { 13, 2, 28 };
int dword_800AE4A4[3] = { 11, 4, 24 };
int dword_800AE4B0[3] = { 24, 22, 4 };
int dword_800AE4BC[3] = { 5, 29, 31 };
int dword_800AE4C8[3] = { 25, 8, 20 };
int dword_800AE4D4[3] = { 31, 5, 8 };
int *name_800AE4E0[17] = {
    dword_800AE414, dword_800AE420, dword_800AE42C, dword_800AE438,
    dword_800AE444, dword_800AE450, dword_800AE45C, dword_800AE468,
    dword_800AE474, dword_800AE480, dword_800AE48C, dword_800AE498,
    dword_800AE4A4, dword_800AE4B0, dword_800AE4BC, dword_800AE4C8,
    dword_800AE4D4,
};
int dword_800AE524[219] = {
    0x3030110, 0x3030300, 0x3030300, 0x3030010, 0x3030300, 0x3030300, 0x3030210, 0x3030300,
    0x3030300, 0x3030108, 0x3030008, 0x3030300, 0x3030210, 0x3030300, 0x3030300, 0x3000010,
    0x3030300, 0x3030300, 0x3020008, 0x3020108, 0x3030300, 0x3031110, 0x3030300, 0x3030300,
    0x3031010, 0x3030300, 0x3030300, 0x3031008, 0x3031908, 0x3030300, 0x3031008, 0x3031908,
    0x3030300, 0x3031008, 0x3191008, 0x3030300, 0x3191908, 0x31B1008, 0x3030300, 0x3181808,
    0x3031808, 0x3030300, 0x3101008, 0x3191908, 0x3030300, 0x3212110, 0x3030300, 0x3030300,
    0x3222210, 0x3030300, 0x3030300, 0x3181810, 0x3030300, 0x3030300, 0x10101008, 0x19191908,
    0x3030300, 0x3033010, 0x3030300, 0x3030300, 0x303310A, 0x3033006, 0x3030300, 0x303320E,
    0x3303202, 0x3030300, 0x3033010, 0x3030300, 0x3030300, 0x303300E, 0x3313002, 0x3030300,
    0x3033010, 0x3030300, 0x3030300, 0x3303108, 0x3033108, 0x3030300, 0x303300E, 0x3313002,
    0x3030300, 0x3313108, 0x3313208, 0x3030300, 0x30313208, 0x3313208, 0x3030300, 0x3033810,
    0x3030300, 0x3030300, 0x33A3808, 0x3033808, 0x3030300, 0x33A3808, 0x3033808, 0x3030300,
    0x3393910, 0x3030300, 0x3030300, 0x3404008, 0x3034008, 0x3030300, 0x3034A10, 0x3030300,
    0x3030300, 0x3034910, 0x3030300, 0x3030300, 0x3034810, 0x3030300, 0x3030300, 0x3034810,
    0x3030300, 0x3030300, 0x3034A0A, 0x3034906, 0x3030300, 0x34A4808, 0x3484A08, 0x3030300,
    0x3034807, 0x3034907, 0x3484902, 0x3034A07, 0x3034907, 0x48494A02, 0x3034808, 0x3034A08,
    0x3030300, 0x3035210, 0x3030300, 0x3030300, 0x3035910, 0x3030300, 0x3030300, 0x3035810,
    0x3030300, 0x3030300, 0x3035208, 0x3595908, 0x3030300, 0x3035810, 0x3030300, 0x3030300,
    0x3035208, 0x3525208, 0x3030300, 0x3035808, 0x3585908, 0x3030300, 0x3005806, 0x3035205,
    0x3525905, 0x3036010, 0x3030300, 0x3030300, 0x3036008, 0x3036908, 0x3030300, 0x3036008,
    0x3036908, 0x3030300, 0x3036908, 0x3696908, 0x3030300, 0x3037208, 0x3036908, 0x3030300,
    0x3707008, 0x3037008, 0x3030300, 0x3696008, 0x3697208, 0x3030300, 0x3707010, 0x3030300,
    0x3030300, 0x3727110, 0x3030300, 0x3030300, 0x3707010, 0x3030300, 0x3030300, 0x3696010,
    0x3030300, 0x3030300, 0x3037810, 0x3030300, 0x3030300, 0x3038110, 0x3030300, 0x3030300,
    0x3038A10, 0x3030300, 0x3030300, 0x3038810, 0x3030300, 0x3030300, 0x3888810, 0x3030300,
    0x3030300, 0x3038110, 0x3030300, 0x3030300, 0x3788110, 0x3030300, 0x3030300, 0x3038A10,
    0x3030300, 0x3030300, 0x3898A10, 0x38A8900, 0x3030300, 0x3888810, 0x3030300, 0x3030300,
    0x88798A01, 0x38A7907, 0x3798808,
};
int dword_800AE890 = 0xFFFF006A;
int dword_800AE894 = 0xFFFF006B;
int dword_800AE898 = 0xFFFF006C;
int dword_800AE89C = 0xFFFF006D;
int dword_800AE8A0 = 0xFFFF006E;
int dword_800AE8A4 = 0xFFFF006F;
int dword_800AE8A8 = 0xFFFF0070;
int dword_800AE8AC = 0xFFFF0072;
int dword_800AE8B0 = 0xFFFF0076;
int dword_800AE8B4 = 0xFFFF0077;
int dword_800AE8B8 = 0xFFFF0078;
int dword_800AE8BC = 0xFFFF0079;
int dword_800AE8C0 = 0xFFFF007A;
int dword_800AE8C4 = 0xFFFF007B;
int dword_800AE8C8 = 0xFFFF007C;
int dword_800AE8CC = 0xFFFF0080;
int dword_800AE8D0 = 0xFFFF0081;
int dword_800AE8D4 = 0xFFFF0083;
int dword_800AE8D8 = 0xFFFF0084;
int dword_800AE8DC = 0xFFFF0089;
int dword_800AE8E0 = 0xFFFF008A;
int dword_800AE8E4 = 0xFFFF008B;
int dword_800AE8E8 = 0xFFFF008C;
int dword_800AE8EC = 0xFFFF008E;
int dword_800AE8F0 = 0xFFFF008F;
int dword_800AE8F4 = 0xFFFF0090;
int dword_800AE8F8 = 0xFFFF0091;
int dword_800AE8FC = 0xFFFF0092;
int dword_800AE900 = 0xFFFF0093;
int dword_800AE904 = 0xFFFF009E;
int dword_800AE908 = 0xFFFF009F;
int dword_800AE90C = 0xFFFF00A0;
int dword_800AE910 = 0xFFFF00A1;
int dword_800AE914[8] = { 0xA400A3, 0xA600A5, 0xA800A7, 0xAA00A9, 0xAC00AB, 0xB400B3, 0xB600B5, 0xFFFF };
int dword_800AE934 = 0xFFFF00BB;
int dword_800AE938[2] = { 0xBA00BC, 0xFFFF };
int dword_800AE940 = 0xFFFF00BD;
int dword_800AE944 = 0xFFFF;
int dword_800AE948 = 0xFFFF00BF;
int dword_800AE94C = 0xFFFF00C0;
int dword_800AE950 = 0xFFFF00C1;
int dword_800AE954 = 0xFFFF00C2;
int dword_800AE958 = 0xFFFF00C3;
int dword_800AE95C = 0xFFFF00D2;
int dword_800AE960 = 0xFFFF00D3;
int dword_800AE964 = 0xFFFF00D4;
int dword_800AE968 = 0xFFFF00D5;
int dword_800AE96C = 0xFFFF00D6;
int dword_800AE970 = 0xFFFF00D7;
int dword_800AE974 = 0xFFFF00D8;
int dword_800AE978 = 0xFFFF00D9;
int dword_800AE97C = 0xFFFF00DD;
int dword_800AE980 = 0xFFFF00DE;
int dword_800AE984 = 0xFFFF00DF;
int dword_800AE988 = 0xFFFF00E0;
int dword_800AE98C = 0xFFFF00E1;
int dword_800AE990 = 0xFFFF00E2;
int dword_800AE994 = 0xFFFF00E3;
int dword_800AE998 = 0xFFFF00E4;
int dword_800AE99C = 0xFFFF00E7;
int dword_800AE9A0 = 0xFFFF00E9;
int dword_800AE9A4 = 0xFFFF00EA;
int dword_800AE9A8 = 0xFFFF00ED;
int dword_800AE9AC = 0xFFFF00EE;
int dword_800AE9B0 = 0xFFFF00EF;
int dword_800AE9B4 = 0xFFFF00F0;
int dword_800AE9B8 = 0xFFFF00F1;
int dword_800AE9BC = 0xFFFF00F2;
int dword_800AE9C0 = 0xFFFF00F3;
int dword_800AE9C4 = 0xFFFF00F4;
int dword_800AE9C8 = 0xFFFF00F5;
int dword_800AE9CC = 0xFFFF00F6;
int dword_800AE9D0[3] = { 0x1010100, 0x1030102, 0xFFFF };
void *dword_800AE9DC[73] = {
    (void *)&dword_800AE890, (void *)&dword_800AE894, (void *)&dword_800AE898, (void *)&dword_800AE89C,
    (void *)&dword_800AE8A0, (void *)&dword_800AE8A4, (void *)&dword_800AE8A8, (void *)&dword_800AE8AC,
    (void *)&dword_800AE8B0, (void *)&dword_800AE8B4, (void *)&dword_800AE8B8, (void *)&dword_800AE8BC,
    (void *)&dword_800AE8C0, (void *)&dword_800AE8C4, (void *)&dword_800AE8C8, (void *)&dword_800AE8CC,
    (void *)&dword_800AE8D0, (void *)&dword_800AE8D4, (void *)&dword_800AE8D8, (void *)&dword_800AE8DC,
    (void *)&dword_800AE8E0, (void *)&dword_800AE8E4, (void *)&dword_800AE8E8, (void *)&dword_800AE8EC,
    (void *)&dword_800AE8F0, (void *)&dword_800AE8F4, (void *)&dword_800AE8F8, (void *)&dword_800AE8FC,
    (void *)&dword_800AE900, (void *)&dword_800AE904, (void *)&dword_800AE908, (void *)&dword_800AE90C,
    (void *)&dword_800AE910, (void *)dword_800AE914, (void *)&dword_800AE934, (void *)dword_800AE938,
    (void *)&dword_800AE940, (void *)&dword_800AE944, (void *)&dword_800AE948, (void *)&dword_800AE94C,
    (void *)&dword_800AE950, (void *)&dword_800AE954, (void *)&dword_800AE958, (void *)&dword_800AE95C,
    (void *)&dword_800AE960, (void *)&dword_800AE964, (void *)&dword_800AE968, (void *)&dword_800AE96C,
    (void *)&dword_800AE970, (void *)&dword_800AE974, (void *)&dword_800AE978, (void *)&dword_800AE97C,
    (void *)&dword_800AE980, (void *)&dword_800AE984, (void *)&dword_800AE988, (void *)&dword_800AE98C,
    (void *)&dword_800AE990, (void *)&dword_800AE994, (void *)&dword_800AE998, (void *)&dword_800AE99C,
    (void *)&dword_800AE9A0, (void *)&dword_800AE9A4, (void *)&dword_800AE9A8, (void *)&dword_800AE9AC,
    (void *)&dword_800AE9B0, (void *)&dword_800AE9B4, (void *)&dword_800AE9B8, (void *)&dword_800AE9BC,
    (void *)&dword_800AE9C0, (void *)&dword_800AE9C4, (void *)&dword_800AE9C8, (void *)&dword_800AE9CC,
    (void *)dword_800AE9D0,
};
int dword_800AEB00[27] = {
    0, 0, 0, 3, 0, 0, 3, 0,
    0, 0, 0, 0, 3, 0, 0, 3,
    0, 0, 0, 0, 0, 3, 0, 0,
    3,
};
int dword_800AEB6C[3] = { 211, 211, 211 };
int dword_800AEB78 = 211;
int dword_800AEB7C = 2;
int name_800AEB80[15] = { 0 };
int *name_800AEBBC = 0;
void *name_800AEBC0[2] = { 0 };
void *name_800AEBC8 = 0;
int name_800AEBCC[2] = { 0 };
int name_800AEBD4 = 0;
int dword_800AEBD8 = -1;
int dword_800AEBDC = 0;
int dword_800AEBE0 = 0;
int dword_800AEBE4 = 1;
int dword_800AEBE8 = 0x8000;
int name_800AEBEC = 0;
int dword_800AEBF0 = 0;
int dword_800AEBF4 = 0;
int dword_800AEBF8[19] = {
    -1, 0x30001, 0x400000, 0, 0x30001, 0x400000, 0, 0x30001,
    0x400000, 0, 0x30001, 0x400000, 0, 0x30001, 0x400000, 0,
    0x30001, 0x400000,
};
int dword_800AEC44[20] = {
    0x1D70067, 0xFFFF0000, 0x10019, 0, 0x1D80068, 0xFFFF0001, 0x10019, 0,
    0x1D90069, 0xFFFF0002, 0x10019, 0, 0x1DA006A, 0xFFFF0003, 0x10019, 0,
    -1,
};
int dword_800AEC94[20] = {
    0x1DB006B, 0xFFFF0000, 0x10019, 0, 0x1DC006C, 0xFFFF0001, 0x10019, 0,
    0x1DD006D, 0xFFFF0002, 0x10019, 0, 0x1DE006E, 0xFFFF0003, 0x10019, 0,
    -1,
};
int dword_800AECE4[16] = {
    0x1DF006F, 0, 0x10022, 0x800B276C, 0x1DF0071, 0x10000, 0x10022, 0x800B2768,
    0x1E00070, 0xFFFF0001, 0x10019, 0x800B2618, -1,
};
int dword_800AED24[304] = {
    0x1E10072, 0x1080000, 143, 0x800B3128, 0x1E20073, 0x1090001, 143, 0,
    0x1E30074, 0x10A0002, 143, 0, 0x1E40075, 0x10B0003, 143, 0,
    0x1E50076, 0x10C0004, 143, 0, 0x1E60077, 0x10D0005, 143, 0,
    0x1E70078, 0x10E0006, 143, 0, 0x1E80079, 0x10F0007, 143, 0,
    0x1E9007A, 0x1100008, 143, 0, 0x1EA007B, 0x1110009, 143, 0,
    0x1EB007C, 0x112000A, 143, 0, 0x1EC007D, 0x113000B, 143, 0,
    0x1ED007E, 0x114000C, 143, 0, 0x1EE007F, 0x115000D, 143, 0,
    0x1EF0080, 0x116000E, 143, 0, 0x1F00081, 0x117000F, 143, 0,
    0x1F10082, 0x1180010, 143, 0, 0x1F20083, 0x1190011, 143, 0,
    0x1F30084, 0x11A0012, 143, 0, 0x1F40085, 0x11B0013, 143, 0,
    0x1F50086, 0x11C0014, 143, 0, 0x1F60087, 0x11D0015, 143, 0,
    0x1F70088, 0x11E0016, 143, 0, 0x1F80089, 0x11F0017, 143, 0,
    0x1F9008A, 0x1200018, 143, 0, 0x1FA008B, 0x1210019, 143, 0,
    0x1FB008C, 0x122001A, 143, 0, 0x1FC008D, 0x123001B, 143, 0,
    0x1FD008E, 0x124001C, 143, 0, 0x1FE008F, 0x125001D, 143, 0,
    0x1FF0090, 0x126001E, 143, 0, 0x2000091, 0x127001F, 143, 0,
    0x2010092, 0x1280020, 143, 0, 0x2020093, 0x1290021, 143, 0,
    0x2030094, 0x12A0022, 143, 0, 0x2040095, 0x12B0023, 143, 0,
    0x2050096, 0x12C0024, 143, 0, 0x2060097, 0x12D0025, 143, 0,
    0x2070098, 0x12E0026, 143, 0, 0x2080099, 0x12F0027, 143, 0,
    0x209009A, 0x1300028, 143, 0, 0x20A009B, 0x1310029, 143, 0,
    0x20B009C, 0x132002A, 143, 0, 0x20C009D, 0x133002B, 143, 0,
    0x20D009E, 0x134002C, 143, 0, 0x20E009F, 0x135002D, 143, 0,
    0x20F00A0, 0x136002E, 143, 0, 0x21000A1, 0x137002F, 143, 0,
    0x21100A2, 0x1380030, 143, 0, 0x21200A3, 0x1390031, 143, 0,
    0x21300A4, 0x13A0032, 143, 0, 0x21400A5, 0x13B0033, 143, 0,
    0x21500A6, 0x13C0034, 143, 0, 0x21600A7, 0x13D0035, 143, 0,
    0x21700A8, 0x13E0036, 143, 0, 0x21800A9, 0x13F0037, 143, 0,
    0x21900AA, 0x1400038, 143, 0, 0x21A00AB, 0x1410039, 143, 0,
    0x21B00AC, 0x142003A, 143, 0, 0x21C00AD, 0x143003B, 143, 0,
    0x21D00AE, 0x144003C, 143, 0, 0x21E00AF, 0x145003D, 143, 0,
    0x21F00B0, 0x146003E, 143, 0, 0x22000B1, 0x147003F, 143, 0,
    0x22100B2, 0x1480040, 143, 0, 0x22200B3, 0x1490041, 143, 0,
    0x22300B4, 0x14A0042, 143, 0, 0x22400B5, 0x14B0043, 143, 0,
    0x22500B6, 0x14C0044, 143, 0, 0x22600B7, 0x14D0045, 143, 0,
    0x22700B8, 0x14E0046, 143, 0, 0x22800B9, 0x14F0047, 143, 0,
    0x22900BA, 0x1500048, 143, 0, 0x22A00BB, 0x1510049, 143, 0,
    0x22B00BC, 0x152004A, 143, 0, -1,
};
int dword_800AF1E4[32] = {
    0x22C00BD, 0x1530000, 0x10021, 0x800B260C, 0x22D00BE, 0x1540001, 0x10021, 0x800B2DB0,
    0x22E00BF, 0x1550002, 0x10021, 0x800B23E8, 0x22F00C0, 0x1560003, 0x10021, 0x800B2728,
    0x23000C1, 0x1570004, 0x10021, 0x800B2ADC, 0x23100C2, 0x1580005, 0x10021, 0,
    0x22C00BD, 0x1590000, 0x10021, 0x800B260C, -1,
};
int dword_800AF264[36] = {
    0x23200C3, 0x20000, 0x1000E, 0x800B2920, 0x23200C7, 0x30000, 0x1000E, 0x800B2D98,
    0x23200C8, 0x40000, 0x1000E, 0x800B2A54, 0x23200C9, 0x50000, 0x1000E, 0x800B2D98,
    0x23200CA, 0x60000, 0x1000E, 0x800B2D98, 0x23300C4, 0x70001, 0x10010, 0x800B22C4,
    0x23400C5, 0x80002, 0x10010, 0x800B2DC8, 0x23500C6, 0x90003, 0x1000E, 0x800B22C4,
    -1,
};
int dword_800AF2F4[32] = {
    0x23600CB, 0xA0000, 0x1000E, 0x800B2BCC, 0x23700CC, 0xB0000, 0x1000E, 0x800B2E5C,
    0x23700D0, 0xC0000, 0x1000E, 0x800B2E5C, 0x23700D1, 0xD0000, 0x1000E, 0x800B2E5C,
    0x23700D2, 0xE0000, 0x1000E, 0x800B2E5C, 0x23800CD, 0xFFFF0000, 0x1000E, 0,
    0x23900CE, 0xF0003, 0x1000E, 0x800B2910, -1,
};
int dword_800AF374[20] = {
    0x23B00D3, 0x100000, 0x1000E, 0x800B2A34, 0x23B00D4, 0x110000, 0x1000E, 0x800B2A2C,
    0x23B00D5, 0x120000, 0x1000E, 0x800B2A34, 0x23B00D6, 0x130000, 0x1000E, 0x800B2A3C,
    -1,
};
int dword_800AF3C4[20] = {
    0x23C00D7, 0x140000, 0x1000E, 0x800B2688, 0x23C00D8, 0x150000, 0x1000E, 0x800B2684,
    0x23C00D9, 0x160000, 0x1000E, 0x800B2690, 0x23C00DA, 0x170000, 0x1000E, 0x800B2688,
    -1,
};
int dword_800AF414[36] = {
    0x23D00DB, 0x180000, 0x1000E, 0x800B2A58, 0x23D00DD, 0x190000, 0x1000E, 0x800B2A58,
    0x23D00DE, 0x1A0000, 0x1000E, 0x800B2A58, 0x23D00DF, 0x1B0000, 0x1000E, 0x800B2A58,
    0x23E00DC, 0x1C0001, 0x1000E, 0x800B2BCC, 0x23E00E0, 0x1D0001, 0x1000E, 0x800B2BCC,
    0x23E00E1, 0x1E0001, 0x1000E, 0x800B2BCC, 0x23E00E2, 0x1F0001, 0x1000E, 0x800B2BCC,
    -1,
};
int dword_800AF4A4[24] = {
    0x23F00E3, 0x200000, 0x1000E, 0x800B2614, 0x23F00E5, 0x210000, 0x1000E, 0x800B2690,
    0x23F00E6, 0x220000, 0x1000E, 0x800B2690, 0x23F00E7, 0x230000, 0x1000E, 0x800B2680,
    0x24000E4, 0x240001, 0x1001E, 0x800B2608, -1,
};
int dword_800AF504[56] = {
    0x24100E8, 0x250000, 0x1000E, 0x800B23E8, 0x24200E9, 0x260001, 0x1000C, 0x800B29F0,
    0x24200EE, 0x270001, 0x1000C, 0x800B29E4, 0x24300EA, 0x280000, 0x1000E, 0x800B22C4,
    0x24400EB, 0x290003, 0x1000E, 0x800B272C, 0x24400EF, 0x2A0003, 0x1000E, 0x800B272C,
    0x24400F0, 0x2B0003, 0x1000E, 0x800B272C, 0x24400F1, 0x2C0003, 0x1000E, 0x800B272C,
    0x24500EC, 0x2D0004, 0x1000E, 0x800B2728, 0x24500F2, 0x2E0004, 0x1000E, 0x800B2734,
    0x24500F3, 0x2F0004, 0x1000E, 0x800B2728, 0x24500F4, 0x300004, 0x1000E, 0x800B2728,
    0x24600ED, 0x310005, 0x10017, 0x800B29EC, -1,
};
int dword_800AF5E4[20] = {
    0x24700F5, 0x320000, 0x1000E, 0x800B291C, 0x24700F6, 0x330000, 0x1000E, 0x800B291C,
    0x24700F7, 0x340000, 0x1000E, 0x800B2924, 0x24700F8, 0x350000, 0x1000E, 0x800B291C,
    -1,
};
int dword_800AF634[20] = {
    0x24800F9, 0x360000, 0x1000E, 0x800B268C, 0x24800FA, 0x370000, 0x1000E, 0x800B268C,
    0x24800FB, 0x380000, 0x1000E, 0x800B268C, 0x24800FC, 0x390000, 0x1000E, 0x800B268C,
    -1,
};
int dword_800AF684[20] = {
    0x24900FD, 0x3A0000, 0x1000E, 0x800B2604, 0x24900FE, 0x3B0000, 0x1000E, 0x800B2604,
    0x24900FF, 0x3C0000, 0x1000E, 0x800B2604, 0x2490100, 0x3D0000, 0x1000E, 0x800B2604,
    -1,
};
int dword_800AF6D4[20] = {
    0x24A0101, 0x3E0000, 0x1000E, 0x800B2608, 0x24A0102, 0x3F0000, 0x1000E, 0x800B2608,
    0x24A0103, 0x400000, 0x1000E, 0x800B2608, 0x24A0104, 0x410000, 0x1000E, 0x800B2608,
    -1,
};
int dword_800AF724[8] = { 0x24B0105, 0x420000, 0x1000E, 0x800B22C4, -1 };
int dword_800AF744[16] = {
    0x24C0106, 0x430000, 0x1000D, 0x800B2D98, 0x24C0107, 0x440000, 0x1000F, 0x800B2D98,
    0x24D0108, 0x450002, 0x1009A, 0x800B25CC, -1,
};
int dword_800AF784[24] = {
    0x24E0109, 0x460000, 0x10091, 0x800B2E50, 0x24E010A, 0x470001, 0x1000F, 0x800B22C4,
    0x24F010B, 0xFFFF0001, 0x1000D, 0, 0x250010C, 0x480000, 0x1000F, 0x800B2A38,
    0x251010D, 0x490001, 0x1007C, 0x800B2928, -1,
};
int dword_800AF7E4[12] = {
    0x252010E, 0x4A0000, 0x10091, 0x800B2A3C, 0x252010F, 0x4B0000, 0x1000F, 0x800B2AC0,
    -1,
};
int dword_800AF814[12] = {
    0x2530110, 0x4C0000, 0x10091, 0x800B2688, 0x2530111, 0x4D0000, 0x1000F, 0x800B2728,
    -1,
};
int dword_800AF844[20] = {
    0x2540112, 0x4E0000, 0x1000D, 0x800B2A3C, 0x2540113, 0x4F0000, 0x1000F, 0x800B2A34,
    0x2550114, 0x500001, 0x1000D, 0x800B2BC0, 0x2550115, 0x510001, 0x1000F, 0x800B2BC0,
    -1,
};
int dword_800AF894[20] = {
    0x2560116, 0x520000, 0x1000F, 0x800B2714, 0x2560117, 0x530000, 0x1000D, 0x800B2680,
    0x2570118, 0x540001, 0x1007E, 0x800B3008, 0x2570119, 0x550001, 0x1001E, 0x800B2910,
    -1,
};
int dword_800AF8E4[28] = {
    0x258011A, 0x560000, 0x1000D, 0x800B23E8, 0x259011B, 0x570001, 0x10091, 0x800B272C,
    0x259011C, 0x580001, 0x1000F, 0x800B272C, 0x25A011D, 0x590002, 0x1000D, 0x800B23E8,
    0x25B011E, 0x5A0003, 0x10015, 0x800B29D8, 0x25C011F, 0x5B0002, 0x10091, 0x800B23E8,
    -1,
};
int dword_800AF954[8] = { 0x25D0120, 0x5C0000, 0x1000F, 0x800B2758, -1 };
int dword_800AF974[8] = { 0x25E0121, 0x5D0000, 0x1000F, 0x800B2338, -1 };
int dword_800AF994[16] = {
    0x25F0122, 0x5E0000, 0x1000D, 0x800B260C, 0x2600123, 0xFFFF0001, 0x1000D, 0,
    0x2610124, 0x5F0000, 0x1000F, 0x800B260C, -1,
};
int dword_800AF9D4[16] = {
    0x2620125, 0x600000, 0x1000D, 0x800B2620, 0x2630126, 0xFFFF0001, 0x1000D, 0,
    0x2640127, 0x610000, 0x1000F, 0x800B2608, -1,
};
int dword_800AFA14[16] = {
    0x2650128, 0x620000, 0x1000D, 0x800B2618, 0x2660129, 0xFFFF0001, 0x1000D, 0,
    0x267012A, 0x630000, 0x1000F, 0x800B2610, -1,
};
int dword_800AFA54[28] = {
    0x268012B, 0x640000, 0x1FFFF, 0x800B2EE0, 0x2680131, 0x650000, 0x1FFFF, 0x800B3244,
    0x2680132, 0x660000, 0x1FFFF, 0x800B3054, 0x2680133, 0x670000, 0x1FFFF, 0x800B39D0,
    0x26D0130, 0x680000, 0x1FFFF, 0x800B39D0, 0x269012C, 0x690000, 0x10019, 0x800B2604,
    -1,
};
int dword_800AFAC4[56] = {
    0x26E0134, 0x6A0000, 17, 0x800B298C, 0x26F0135, 0x6B0001, 17, 0x800B2B10,
    0x2700136, 0x6C0002, 17, 0x800B2924, 0x2710137, 0x6D0003, 17, 0x800B2994,
    0x2720138, 0x6E0004, 17, 0x800B29D4, 0x2730139, 0x6F0005, 17, 0x800B296C,
    0x274013A, 0x700006, 17, 0x800B298C, 0x274013B, 0x710006, 0x10011, 0x800B2CDC,
    0x275013C, 0x720007, 17, 0x800B23E8, 0x276013D, 0x730008, 17, 0x800B3684,
    0x277013E, 0x740009, 0x10019, 0x800B272C, 0x277013F, 0x750009, 0x10019, 0x800B23E8,
    0x2780140, 0xFFFF000A, 0x10011, 0x800B30CC, -1,
};
int dword_800AFBA4[80] = {
    0x2790141, 0x760000, 32, 0x800B29AC, 0x27A0142, 0x770001, 32, 0x800B2984,
    0x27B0143, 0x780002, 32, 0x800B23E8, 0x27C0144, 0x790003, 32, 0x800B29AC,
    0x27D0145, 0x7A0004, 32, 0x800B2984, 0x27E0146, 0x7B0005, 32, 0x800B2924,
    0x27F0147, 0x7C0006, 32, 0x800B2AEC, 0x2800148, 0x7D0007, 0x10020, 0x800B3184,
    0x2800149, 0x7E0007, 0x10020, 0x800B2E5C, 0x281014A, 0x7F0008, 32, 0x800B3684,
    0x282014B, 0x800009, 32, 0x800B23E8, 0x283014C, 0x81000A, 32, 0x800B2AF0,
    0x284014D, 0x82000B, 32, 0x800B2C44, 0x285014E, 0x83000C, 32, 0x800B2924,
    0x286014F, 0x84000D, 32, 0x800B298C, 0x2860150, 0x85000D, 0x10020, 0x800B2CE4,
    0x2870151, 0x86000E, 32, 0x800B2878, 0x2870152, 0x87000E, 0x10020, 0x800B314C,
    0x28A0155, 0x880011, 32, 0x800B23E8, -1,
};
int dword_800AFCE4[200] = {
    0x28B0156, 0x890000, 26, 0x800B23E8, 0x28C0157, 0x8A0001, 26, 0x800B29CC,
    0x28D0158, 0x8B0002, 26, 0x800B23E8, 0x28E0159, 0x8C0003, 26, 0x800B296C,
    0x28E015A, 0x8D0003, 0x1001A, 0x800B2CBC, 0x28F015B, 0x8E0004, 26, 0x800B23E8,
    0x290015C, 0x8F0005, 26, 0x800B2924, 0x291015D, 0x900006, 26, 0x800B29AC,
    0x292015E, 0x910007, 26, 0x800B2994, 0x293015F, 0x920008, 26, 0x800B23E8,
    0x2940160, 0x930009, 26, 0x800B297C, 0x2950161, 0x94000A, 26, 0x800B3674,
    0x2960162, 0x95000B, 0x10012, 0x800B2CDC, 0x2960163, 0x96000B, 0x10012, 0x800B2CDC,
    0x2970164, 0x97000C, 0x10012, 0x800B2BC0, 0x2970165, 0x98000C, 0x10012, 0x800B2BC0,
    0x2980166, 0x99000D, 0x10012, 0x800B2CFC, 0x2980167, 0x9A000D, 0x10012, 0x800B2CFC,
    0x2990168, 0x9B000E, 0x10012, 0x800B2CDC, 0x2990169, 0x9C000E, 0x10012, 0x800B2CDC,
    0x29A016A, 0x9D000F, 26, 0x800B2F0C, 0x29B016B, 0x9E0010, 26, 0x800B298C,
    0x29C016C, 0x9F0011, 26, 0x800B2DB4, 0x29D016D, 0xA00012, 26, 0x800B29DC,
    0x29E016E, 0xA10013, 26, 0x800B23E8, 0x29F016F, 0xA20014, 0x1001C, 0x800B29D8,
    0x2A00170, 0xA30000, 26, 0x800B23E8, 0x2A10171, 0xA40001, 26, 0x800B29CC,
    0x2A20172, 0xA50002, 26, 0x800B23E8, 0x2A30173, 0xA60003, 26, 0x800B296C,
    0x2A40174, 0xA70004, 26, 0x800B23E8, 0x2A50175, 0xA80005, 26, 0x800B2924,
    0x2A60176, 0xA90006, 26, 0x800B29AC, 0x2A70177, 0xAA0007, 26, 0x800B2994,
    0x2A80178, 0xAB0008, 26, 0x800B23E8, 0x2A90179, 0xAC0009, 26, 0x800B297C,
    0x2AA017A, 0xAD000A, 26, 0x800B31E4, 0x2AB017B, 0xAE000B, 0x10012, 0x800B2CDC,
    0x2AC017C, 0xAF000C, 0x10012, 0x800B2734, 0x2AD017D, 0xB0000D, 0x10012, 0x800B2CFC,
    0x2AE017E, 0xB1000E, 0x10012, 0x800B2994, 0x2AF017F, 0xB2000F, 26, 0x800B2A80,
    0x2B00180, 0xB30010, 26, 0x800B298C, 0x2B10181, 0xB40011, 26, 0x800B2924,
    0x2B20182, 0xB50012, 26, 0x800B29DC, 0x2B30183, 0xB60013, 26, 0x800B23E8,
    0x2B40184, 0xB70014, 26, 0x800B23E8, 0x2B50185, 0xB80015, 26, 0x800B30CC,
    0x2B60186, 0xB90015, 26, 0x800B30CC, -1,
};
int dword_800B0004[100] = {
    0x2B70187, 0xBA0000, 31, 0x800B29B4, 0x2B80188, 0xBB0001, 31, 0x800B2924,
    0x2B90189, 0xBC0002, 31, 0x800B23E8, 0x2BA018A, 0xBD0003, 31, 0x800B2924,
    0x2BB018B, 0xBE0004, 31, 0x800B2E1C, 0x2BC018C, 0xBF0005, 31, 0x800B298C,
    0x2BD018D, 0xC00006, 31, 0x800B2974, 0x2BE018E, 0xC10007, 31, 0x800B2AEC,
    0x2BF018F, 0xC20008, 31, 0x800B2924, 0x2C00190, 0xC30009, 31, 0x800B296C,
    0x2C00191, 0xC40009, 0x1001F, 0x800B2CC4, 0x2C10192, 0xC5000A, 31, 0x800B2984,
    0x2C20193, 0xC6000B, 31, 0x800B2870, 0x2C30194, 0xC7000C, 0x10021, 0x800B30EC,
    0x2C40195, 0xC8000D, 0x10021, 0x800B23E8, 0x2C50196, 0xC9000E, 0x10021, 0x800B2728,
    0x2C60197, 0xCA000F, 0x10021, 0x800B2ADC, 0x2C70198, 0xCB0010, 0x10021, 0x800B30F0,
    0x2C70199, 0xCC0010, 0x10021, 0x800B30F0, 0x2C7019A, 0xCD0010, 0x10021, 0x800B30F0,
    0x2C8019B, 0xCE0011, 0x10021, 0x800B2908, 0x2C9019C, 0xCF0012, 0x1007A, 0x800B2B50,
    0x2CA019D, 0xD00013, 0x1007A, 0x800B2B50, 0x2CB019E, 0xD10014, 0x10097, 0x800B2678,
    -1,
};
int dword_800B0194[48] = {
    0x2CC019F, 0xD20000, 41, 0x800B23E8, 0x2CD01A0, 0xD30001, 41, 0x800B23E8,
    0x2CE01A1, 0xD40002, 41, 0x800B2924, 0x2CF01A2, 0xD50003, 41, 0x800B23E8,
    0x2D001A3, 0xD60004, 41, 0x800B23E8, 0x2D101A4, 0xD70005, 41, 0x800B23E8,
    0x2D201A5, 0xD80006, 41, 0x800B299C, 0x2D301A6, 0xD90007, 0x10029, 0x800B2C88,
    0x2D401A7, 0xDA0008, 0x10029, 0x800B30D4, 0x2D501A8, 0xDB0009, 0x10029, 0x800B23E8,
    0x2D601A9, 0xDC000A, 0x10029, 0x800B30D4, -1,
};
int dword_800B0254[68] = {
    0x2D701AA, 0xDD0000, 42, 0x800B23E8, 0x2D801AB, 0xDE0001, 42, 0x800B23E8,
    0x2D901AC, 0xDF0002, 42, 0x800B23E8, 0x2DA01AD, 0xE00003, 42, 0x800B23E8,
    0x2DB01AE, 0xE10004, 42, 0x800B23E8, 0x2DC01AF, 0xE20005, 42, 0x800B23E8,
    0x2DD01B0, 0xE30006, 42, 0x800B2924, 0x2DE01B1, 0xE40007, 0x1002A, 0x800B312C,
    0x2DF01B2, 0xE50008, 42, 0x800B30D4, 0x2E001B3, 0xE60009, 42, 0x800B23E8,
    0x2E101B4, 0xE7000A, 42, 0x800B23E8, 0x2E201B5, 0xE8000B, 42, 0x800B2C44,
    0x2E301B6, 0xE9000C, 42, 0x800B23E8, 0x2E401B7, 0xEA000D, 42, 0x800B296C,
    0x2E501B8, 0xEB000E, 42, 0x800B2E34, 0x2E801BB, 0xEC0011, 42, 0x800B23E8,
    -1,
};
int dword_800B0364[112] = {
    0x2E901BC, 0xED0000, 39, 0x800B23E8, 0x2EA01BD, 0xEE0001, 39, 0x800B23E8,
    0x2EB01BE, 0xEF0002, 39, 0x800B23E8, 0x2EC01BF, 0xF00003, 39, 0x800B23E8,
    0x2ED01C0, 0xF10004, 39, 0x800B23E8, 0x2EE01C1, 0xF20005, 39, 0x800B23E8,
    0x2EF01C2, 0xF30006, 39, 0x800B23E8, 0x2F001C3, 0xF40007, 39, 0x800B29A4,
    0x2F101C4, 0xF50008, 39, 0x800B23E8, 0x2F201C5, 0xF60009, 39, 0x800B23E8,
    0x2F301C6, 0xF7000A, 39, 0x800B30D4, 0x2F401C7, 0xF8000B, 0x1002B, 0x800B23E8,
    0x2F401C8, 0xF9000B, 0x1002B, 0x800B2AF8, 0x2F501C9, 0xFA000C, 0x1002B, 0x800B2878,
    0x2F501CA, 0xFB000C, 0x1002B, 0x800B2B00, 0x2F601CB, 0xFC000D, 0x1002B, 0x800B23E8,
    0x2F601CC, 0xFD000D, 0x1002B, 0x800B2AF8, 0x2F701CD, 0xFE000E, 0x10027, 0x800B23E8,
    0x2F801CE, 0xFF000F, 39, 0x800B2F10, 0x2F901CF, 0x1000010, 39, 0x800B2924,
    0x2FA01D0, 0x1010011, 39, 0x800B2878, 0x2FB01D1, 0x1020012, 39, 0x800B2924,
    0x2FC01D2, 0x1030013, 39, 0x800B23E8, 0x2FD01D3, 0x1040014, 0x10028, 0x800B2B9C,
    0x2FE01D4, 0x1050015, 39, 0x800B30D4, 0x2FF01D5, 0x1060014, 0x10028, 0x800B2800,
    0x2FF01D6, 0x1070014, 0x10028, 0x800B2CA4, -1,
};
void *dword_800B0524[6] = { (void *)dword_800AEC44, (void *)dword_800AEC94, (void *)dword_800AECE4, (void *)dword_800AED24, (void *)dword_800AF1E4 };
void *dword_800B053C[13] = {
    (void *)dword_800AF264, (void *)dword_800AF2F4, (void *)dword_800AF374, (void *)dword_800AF3C4,
    (void *)dword_800AF414, (void *)dword_800AF4A4, (void *)dword_800AF504, (void *)dword_800AF5E4,
    (void *)dword_800AF634, (void *)dword_800AF684, (void *)dword_800AF6D4, (void *)dword_800AF724,
};
void *dword_800B0570[13] = {
    (void *)dword_800AF744, (void *)dword_800AF784, (void *)dword_800AF7E4, (void *)dword_800AF814,
    (void *)dword_800AF844, (void *)dword_800AF894, (void *)dword_800AF8E4, (void *)dword_800AF954,
    (void *)dword_800AF974, (void *)dword_800AF994, (void *)dword_800AF9D4, (void *)dword_800AFA14,
};
void *dword_800B05A4[13] = {
    (void *)dword_800AF264, (void *)dword_800AF2F4, (void *)dword_800AF374, (void *)dword_800AF3C4,
    (void *)dword_800AF414, (void *)dword_800AF4A4, (void *)dword_800AF504, (void *)dword_800AF5E4,
    (void *)dword_800AF634,
};
void *dword_800B05D8[6] = { (void *)dword_800AFA54, (void *)dword_800AFAC4, (void *)dword_800AFBA4, (void *)dword_800AFCE4, (void *)dword_800B0004 };
void *dword_800B05F0[6] = { (void *)dword_800AFA54, (void *)dword_800B0194, (void *)dword_800B0254, (void *)dword_800B0364, (void *)dword_800B0004 };
G2Ent16 **name_800B0608[36] = {
    (void *)dword_800B0524, (void *)dword_800B053C, (void *)dword_800B0570, (void *)dword_800B05A4,
    (void *)dword_800B05D8, (void *)dword_800B05F0, 0, (G2Ent16 **)5,
    (G2Ent16 **)12, (G2Ent16 **)12, (G2Ent16 **)12, (G2Ent16 **)5,
    (G2Ent16 **)5, (G2Ent16 **)1, (G2Ent16 **)2, (G2Ent16 **)3,
    (G2Ent16 **)4, (G2Ent16 **)5, 0, (G2Ent16 **)1,
    (G2Ent16 **)1, (G2Ent16 **)1, (G2Ent16 **)4, (G2Ent16 **)4,
    0, (G2Ent16 **)2, (G2Ent16 **)2, (G2Ent16 **)2,
    (G2Ent16 **)4, (G2Ent16 **)4, 0, (G2Ent16 **)3,
    (G2Ent16 **)3, (G2Ent16 **)3, (G2Ent16 **)5, (G2Ent16 **)5,
};
int dword_800B0698 = 0;
int dword_800B069C[5] = { 0x462, -0x2B2, 0x772, 0xFC000000 };
int dword_800B06B0[3] = { 0 };
int dword_800B06BC = 0;
int dword_800B06C0[3] = { 0 };
int dword_800B06CC[6] = { 1, 5, 8, (int)&mapLoaderTask_800B1DC4, (int)InitMapLoaderTask_80027CC0, (int)ResetMapLoaderTask_8002830C };
int dword_800B06E4[6] = { 1, 1, 8, (int)&areaLoaderTask_800B1DB8, (int)InitAreaLoaderTask_80028388 };
int dword_800B06FC[6] = { 1, 5, 40, (int)dword_800B1DA0, (int)sub_800ACAA4, (int)sub_800ACF0C };
int dword_800B0714[6] = { 1, 0x8000, 92, (int)&modelLoaderTask_8008B54C, (int)ModelLoaderTask_800209AC };
int dword_800B072C[6] = { 7, 0x8000, 0x1CC, (int)&actorTasks_8008D43C };
int dword_800B0744[6] = { 1, 1, 4, (int)&dword_800B1DBC, (int)sub_800A09D8 };
int dword_800B075C[6] = { 10, 0x8000, 0x124, (int)&eventScripts_8008D410 };
int dword_800B0774[6] = { 1, 5, 16, 0x8008B4D0, (int)sub_800A1314, (int)sub_800A1444 };
int dword_800B078C[6] = { 1, 0x8000, 16, (int)&dword_8008D624 };
int dword_800B07A4[6] = { 1, 0x8000, 12, (int)&battleMenuTask_8008D468 };
int dword_800B07BC[6] = { 1, 0x8000, 0, (int)&dword_8008D444 };
int dword_800B07D4[6] = { 1, 0x8000, 48, 0x8008B568 };
int dword_800B07EC[6] = { 3, 0x8000, 24, (int)&dword_8008B564 };
int dword_800B0804[6] = { 1, 0x8000, 20, (int)&dword_8008D4B0 };
int dword_800B081C[6] = { 1, 0x8000, 20, 0x8008D63C };
int dword_800B0834[6] = { 1, 1, 0x9D0, (int)&dword_8008B4CC, (int)sub_800A818C };
int dword_800B084C[6] = { 1, 0x8000, 0x2E0, 0x8008D490 };
int dword_800B0864[6] = { 1, 5, 0x7C0, (int)&gameTask_8008B4A4, (int)sub_800A9564, (int)sub_800A955C };
int dword_800B087C[6] = { 1, 0x8000, 24, (int)&encounterTask_8008D674 };
int dword_800B0894[6] = { 3, 0x8000, 48, (int)&enemyAiTasks_8008D49C };
int dword_800B08AC[6] = { 1, 0x8000, 12, (int)dword_800B1DA8 };
int dword_800B08C4[6] = { 25, 0x8000, 148, (int)&eventEntities_8008D400 };
int dword_800B08DC[6] = { 1, 1, 4, (int)dword_800B1DC0, (int)sub_800A8108 };
int dword_800B08F4[6] = { 1, 1, 0x100, (int)dword_800B1DA4, (int)sub_800A75F8, 0x800B6F60 };
int dword_800B090C[6] = { 1, 0x8000, 124, 0x8008D498, 0x800BD40C };
int dword_800B0924[6] = { 1, 0x8000, 0, (int)&dword_8008D438, 0x800B67C0 };
int dword_800B093C[6] = { 1, 0x8000, 156, (int)&dword_8008D670, 0x800BB444 };
int dword_800B0954[6] = { 1, 0x8000, 24, (int)&dword_8008D4A8, 0x800B7000 };
int dword_800B096C[6] = { 1, 0x8000, 84, (int)&dword_8008D3E0, 0x800BB1F4 };
int dword_800B0984[6] = { 1, 0x8000, 0, 0x8008D478 };
int dword_800B099C[6] = { 1, 1, 8, (int)dword_800B1DB0, (int)sub_800A7690 };
int dword_800B09B4[6] = { 1, 1, 8, (int)&sporeTask_8008D464, (int)InitSporeTask_80011ADC };
int dword_800B09CC[6] = { 1, 0x8000, 80, (int)&dword_800B1DAC, (int)sub_800A7720 };
int dword_800B09E4[6] = { 1, 1, 32, (int)dword_800B1DB4, (int)sub_800A6DAC };
GameLst_1 dword_800B09FC[2] = { { dword_800B1DA0 } };
GameLst_1 dword_800B0A0C[4] = {
    { &overlayLoaderTask_8008D4C0 },
    { &soundTask_8008D4A4, 0x1000 },
    { dword_800B1DB0 },
};
GameLst_1 dword_800B0A2C[26] = {
    { &overlayLoaderTask_8008D4C0 },
    { dword_800B1DA0 },
    { &modelLoaderTask_8008B54C },
    { &soundTask_8008D4A4 },
    { (void *)&mapLoaderTask_800B1DC4, 0x100 },
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &modelTasks_8008D618 },
    { (void *)((char *)&battleMenuTask_8008D468 + 8) },
    { &eventScripts_8008D410 },
    { dword_800B1DA8 },
    { dword_800B1DB4 },
    { &dword_800B1DAC },
    { &fadeTask_8008D628 },
    { &dword_800B1DBC },
    { &cameraTask_8008D4A0 },
    { (void *)((char *)&dword_8008B4CC + 4) },
    { &eventEntities_8008D400 },
    { (void *)&dword_8008B4CC },
    { (void *)&gameTask_8008B4A4 },
    { (void *)&encounterTask_8008D674 },
    { &enemyAiTasks_8008D49C },
    { &actorTasks_8008D43C },
    { (void *)&messageWindowTask_8008D640 },
    { (void *)&vibrationTasks_8008D4B8 },
    { &sporeTask_8008D464 },
};
GameLst_1 dword_800B0AFC[35] = {
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &soundTask_8008D4A4 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)((char *)&battleMenuTask_8008D468 + 8) },
    { &fadeTask_8008D628 },
    { (void *)((char *)&dword_8008B4CC + 4) },
    { dword_800B1DB4 },
    { &modelTasks_8008D618 },
    { &dword_800B1DBC },
    { &cameraTask_8008D4A0 },
    { (void *)&dword_8008D624 },
    { (void *)&dword_8008B4C0 },
    { (void *)&battleMenuTask_8008D468 },
    { (void *)&dword_8008D444 },
    { (void *)&dword_8008D614 },
    { (void *)&messageWindowTask_8008D640 },
    { (void *)((char *)&dword_8008B4AC + 4) },
    { &screenFlashTasks_8008D61C },
    { (void *)((char *)&dword_8008B564 + 4) },
    { (void *)&dword_8008B564 },
    { (void *)&dword_8008D4B0 },
    { (void *)((char *)&dword_8008D634 + 8) },
    { (void *)&dword_8008B4AC },
    { (void *)&hitNumberTasks_8008D778 },
    { (void *)&vibrationTasks_8008D4B8 },
    { (void *)&dword_8008B4CC },
    { (void *)&gameTask_8008B4A4 },
    { &enemyAiTasks_8008D49C },
    { &actorTasks_8008D43C },
    { &effectTask_8008D3F8 },
    { (void *)&dword_8008D5F8 },
    { &effectObjects_8008B4A8 },
    { &dword_8008D60C },
    { (void *)((char *)&dword_8008D48C + 4) },
};
GameLst_1 dword_800B0C14[4] = {
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)((char *)&dword_8008D48C + 4) },
    { (void *)&messageWindowTask_8008D640 },
};
GameLst_1 dword_800B0C34[3] = {
    { &overlayLoaderTask_8008D4C0 },
    { (void *)&dword_8008D4C4 },
};
GameLst_1 dword_800B0C4C[7] = {
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)((char *)&dword_8008D48C + 12) },
    { (void *)&dword_8008D4C4 },
    { (void *)&dword_8008B4B8 },
    { (void *)&messageWindowTask_8008D640 },
};
GameLst_1 dword_800B0C84[12] = {
    { (void *)((char *)&battleMenuTask_8008D468 + 8) },
    { (void *)&areaLoaderTask_800B1DB8, 0x100 },
    { &overlayLoaderTask_8008D4C0 },
    { (void *)&dword_8008D438 },
    { (void *)&dword_8008D670 },
    { (void *)((char *)&loadMenuTask_8008D480 + 4) },
    { &modelTasks_8008D618 },
    { (void *)&dword_8008D3E0 },
    { &actorTasks_8008D43C },
    { (void *)&dword_8008D4A8 },
    { &fadeTask_8008D628 },
};
GameLst_1 dword_800B0CE4[4] = {
    { (void *)&dword_8008D62C },
    { &overlayLoaderTask_8008D4C0 },
    { &loadMenuTask_8008D480 },
};
GameLst_1 dword_800B0D04[2] = { { dword_800B1DC0 } };
GameLst_1 dword_800B0D14[6] = {
    { &soundTask_8008D4A4 },
    { dword_800B1DA0 },
    { (void *)((char *)&battleMenuTask_8008D468 + 8) },
    { &overlayLoaderTask_8008D4C0 },
    { dword_800B1DA4 },
};
GameLst_1 dword_800B0D44[3] = {
    { &overlayLoaderTask_8008D4C0 },
    { (void *)((char *)&screenOffset_8008D474 + 4) },
};
GameLst_1 dword_800B0D5C[3] = {
    { &overlayLoaderTask_8008D4C0 },
    { dword_800B1DB4 },
};
GameLst_1 *dword_800B0D74[12] = {
    dword_800B0A0C, dword_800B0A2C, dword_800B0AFC, dword_800B0C34,
    dword_800B0C4C, dword_800B0C84, dword_800B0CE4, dword_800B0D04,
    dword_800B0D14, dword_800B0D44, dword_800B0C14, dword_800B0D5C,
};
char dword_800B0DA4[232] = { 204, 6, 11, 128, 0, 143, 7, 128, 24, 143, 7, 128, 228, 6, 11, 128, 252, 6, 11, 128, 20, 7, 11, 128, 44, 7, 11, 128, 152, 144, 7, 128, 72, 143, 7, 128, 68, 7, 11, 128, 96, 143, 7, 128, 116, 7, 11, 128, 140, 7, 11, 128, 40, 145, 7, 128, 164, 7, 11, 128, 188, 7, 11, 128, 16, 145, 7, 128, 80, 144, 7, 128, 104, 144, 7, 128, 212, 7, 11, 128, 236, 7, 11, 128, 4, 8, 11, 128, 28, 8, 11, 128, 76, 8, 11, 128, 32, 144, 7, 128, 56, 144, 7, 128, 168, 143, 7, 128, 52, 8, 11, 128, 100, 8, 11, 128, 176, 144, 7, 128, 200, 144, 7, 128, 224, 144, 7, 128, 248, 144, 7, 128, 128, 144, 7, 128, 172, 8, 11, 128, 196, 8, 11, 128, 8, 144, 7, 128, 120, 143, 7, 128, 12, 9, 11, 128, 192, 143, 7, 128, 216, 143, 7, 128, 240, 143, 7, 128, 220, 8, 11, 128, 244, 8, 11, 128, 92, 7, 11, 128, 144, 143, 7, 128, 36, 9, 11, 128, 60, 9, 11, 128, 84, 9, 11, 128, 108, 9, 11, 128, 132, 9, 11, 128, 156, 9, 11, 128, 180, 9, 11, 128, 124, 8, 11, 128, 148, 8, 11, 128, 204, 9, 11, 128, 228, 9, 11, 128 };
int dword_800B0E8C[6] = { 1, 1, 64, 0x8008D46C, (int)sub_800A68CC };
char name_800B0EA4[20] = { 184, 142, 7, 128, 208, 142, 7, 128, 48, 143, 7, 128, 140, 14, 11, 128 };
GameTab_1 dword_800B0EB8[1] = { { 52, (void (*)())name_800BCB00 } };
int dword_800B0EC0 = 1;
GameList_1 dword_800B0EC4 = { 0 };
char dword_800B0EF8 = 0;
int dword_800B0EFC[45] = {
    0x460000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003, 0x3040004,
    0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007, 0x2080003,
    0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B, 0xB0C0006,
    0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F, 0xF100003,
    0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, 0xF130003, 0xB0013, 0x13140004,
    0xB0014, 0x14150005, 0xB0015, -1, -1,
};
SVECTOR dword_800B0FB0[55] = {
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0x1000, 0x1000, 0x1000 },
    { 0 },
    { 0 },
    { 0, 0, 0, -1 },
    { 0 },
    { 0, 0, 2 },
    { 16, 0, 2 },
    { 25, 0, 2 },
    { 26, 0, 2 },
    { 28, 0, 2 },
    { 29, 0, 2 },
    { 8, 0, 2 },
    { 16, 0, 2 },
    { 13, 0, 2 },
    { 19, 0, 2 },
    { 17, 0, 2 },
    { 18, 0, 2 },
    { 19, 0, 2 },
    { 20, 0, 2 },
    { 21, 0, 2 },
    { 20, 0, 2 },
    { 23, 0, 2 },
    { 22, 0, 2 },
    { 21, 0, 2 },
    { 20, 0, 2 },
    { 24, 0, 16 },
    { 16, 0, 2 },
    { 6, 0, 2 },
    { 12, 0, 2 },
    { 17, 0, 2 },
    { 4, 0, 16 },
    { 16, 0, 2 },
    { 8, 0, 0, 26 },
    { 0, 0, 40 },
};
int dword_800B1168 = 39;
int dword_800B116C[19] = {
    5, 6, 4, 1, 3, 2, 0, 12,
    10, 13, 11, 9, 7, 8, 18, 17,
    15, 16, 14,
};
unsigned char dword_800B11B8[20] = { 45, 54, 36, 9, 27, 18, 0, 108, 90, 117, 99, 81, 63, 72, 162, 153, 135, 144, 126 };
int dword_800B11CC[4] = { 12, 2, 7, -1 };
int dword_800B11DC[19] = {
    0, 0, 0, 1, 1, 1, 1, 2,
    2, 2, 2, 2, 3, 2, 4, 4,
    4, 4, 2,
};
int dword_800B1228 = 0;
int dword_800B122C[13] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0xB00,
};
GameCtx_1 gCtx_800B1260 = { 0 };
int dword_800B1CAC[3] = { 0 };
GameEnemy dword_800B1CB8 = { 0 };
int dword_800B1D98 = 0;
int dword_800B1D9C = 0;
EventNode *dword_800B1DA0[1] = { 0 };
EventNode *dword_800B1DA4[1] = { 0 };
EventNode *dword_800B1DA8[1] = { 0 };
EventNode *dword_800B1DAC = 0;
EventNode *dword_800B1DB0[1] = { 0 };
EventNode *dword_800B1DB4[1] = { 0 };
int** areaLoaderTask_800B1DB8 = 0;
EventNode *dword_800B1DBC = 0;
EventNode *dword_800B1DC0[1] = { 0 };
int** mapLoaderTask_800B1DC4 = 0;
int dword_800B1DC8[2] = { 0 };
char dword_800B1DD0 = 0;
int dword_800B1DD4[9] = { 0 };
char dword_800B1DF8 = 0;
int dword_800B1DFC[304] = { 0 };
