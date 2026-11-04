// GAME.BIN, source file 3 of 3 from 0x800A5804 (.rdata from 0x800A0660)
#include "game.h"

INCLUDE_OVERLAY_ASM(game, dword_800A0660);

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
    EventNode* n = dword_8008D410;
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
    StopAllEventEntries_80043B40(dword_8008D410);
    SetCameraTarget_80037AC8((int)&levantPos_8008BD18);
    if (!(name_80091C38 & 0x40))
    {
        r = &stru_8008D420;
        r->x = 0;
        r->w = 0x140;
        r->y = 0;
        r->h = 0xf0;
    }
    sub_8001A9A4();
    dword_800AEBF0 = 0;
    dword_800AEBE8 = 0x8000;
    name_800AEBEC = 0;
    dword_800AEBE0 = 0;
    dword_800AEBF4 = 0;
}

// Matched
EventEntry* sub_800A59D0(int v)
{
    EventEntry* p = AllocEventEntry_80043AF8(dword_8008D410);
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
    EventNode* n = dword_8008D410;
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
    EventNode* n = dword_8008D410;
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
    EventNode* n = dword_8008D410;
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
    n = dword_8008D400;
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
    EventNode* n = dword_8008D400;
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
    EventNode* n = dword_8008D400;
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
    n = dword_8008D410;
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
        dword_80091C94 = 1;
        dword_80091C54 = 0;
        sd->mapId_2E4[3].field_0 = 0;
        dword_80091C9C = 1;
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
    if (dword_80091C9C == 1)
        return;
    if (saveData_8008B570.mapId_2E4[0].field_2 != saveData_8008B570.mapId_2E4[0].field_0)
        return;
    if (saveData_8008B570.mapId_2E4[1].field_2 != saveData_8008B570.mapId_2E4[1].field_0)
        return;
    if (saveData_8008B570.mapId_2E4[2].field_2 != saveData_8008B570.mapId_2E4[2].field_0)
        return;
    if (word_80091C40[1] != word_80091C40[0])
        return;
    if (saveData_8008B570.mapId_2E4[3].field_2 != saveData_8008B570.mapId_2E4[3].field_0)
        return;
    if (word_80091CB8[6] != word_80091CB8[7])
        return;
    if (sub_800272D0())
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
        e = AllocEventEntry_80043AF8(dword_8008D480);
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
            sub_8001C224();
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
        dword_80091C94 = 1;
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
    dword_8008D40C = 0x1000;
    dword_8008D404 = 0;
    r->x = 0;
    r->w = 0x140;
    r->y = 0;
    r->h = 0xf0;
    unknownFlags_8008D678 &= ~0x8000000;
    sub_80026FAC();
    GameFn_800A094C();
    ResetSoundTask_8002FEB8();
    sub_8001A38C();
    ResetCameraToLevant_800376A8();
    sub_800A8140();
    sub_800A94CC();
    dword_80091C94 = dword_800B1DC8[0];
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
    sub_8001D9B0(sub_800A7A60(a));
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
                sub_8001D6EC(o, 1);
                sub_8001D730(o, 0);
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
                sub_8001D6EC(o, 0);
                sub_8001D730(o, 1);
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
            sub_8001D730(obj, c->fC);
            k = 0;
            break;
        case 7:
            sub_8001D68C(obj, c->fC);
            k = 0;
            break;
        case 8:
            sub_8001D6BC(obj, c->fC);
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
            sub_8001E254(obj, &s);
        }
        else if (c->f8)
        {
            sub_800A5BCC(a + 3);
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(game, sub_800A7D40);

INCLUDE_OVERLAY_ASM(game, dword_800A06F0);

void sub_800A80C4(int a)
{
    if (a < sub_800A7790())
        sub_8001E28C(sub_800A77F4(a)->cb_14.actor_4);
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
    int r = word_8008D668[0] > 0xA0;
    if (word_8008D668[1] >= 0x79)
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
    G2InnerC* p = (G2InnerC*)dword_8008B4CC->f24;
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
    s->levantStatus_7C8.hp_8 -= a;
    if ((short)s->levantStatus_7C8.hp_8 < 0)
    {
        s->levantStatus_7C8.hp_8 = 0;
        return;
    }
    if ((short)s->levantStatus_7C8.maxHp_A < (short)s->levantStatus_7C8.hp_8)
        s->levantStatus_7C8.hp_8 = s->levantStatus_7C8.maxHp_A;
}

void sub_800A8CA0(int a)
{
    SaveData* s = &saveData_8008B570;
    s->levantStatus_7C8.mp_C -= a;
    if ((short)s->levantStatus_7C8.mp_C < 0)
    {
        s->levantStatus_7C8.mp_C = 0;
        return;
    }
    if ((short)s->levantStatus_7C8.maxMp_E < (short)s->levantStatus_7C8.mp_C)
        s->levantStatus_7C8.mp_C = s->levantStatus_7C8.maxMp_E;
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
INCLUDE_OVERLAY_ASM(game, dword_800A07E0);

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
    G2Act* p = dword_8008B4A4->f24;
    a->tbl_0 = sub_80024E64(p->model_40);
    a->pos_4 = &levantPos_8008BD18.pos.x;
    a->bonePos_8 = p->bonePos_590[0];
    a->boneMatrices_C = p->mats_90;
    a->boneScale_2C = dword_800B0FB0;
    a->scale_30 = 0;
}

void sub_800A9414(void* pv, int b, int c)
{
    G2Act* p = (G2Act*)pv;
    sub_80025C38(p->model_40, (((unsigned)unknownFlags_8008D678 >> 24) ^ 1) & 1);
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
    G2Init_1* p = (G2Init_1*)dword_8008B4A4->f24;
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
        p->mats_90[i] = dword_80098188[i];
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
    v = sub_80019CC4(&saveData_8008B570.levant_7A8);
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
        sub_80046A58(&sk, &stru_8008D534[v], 0);
    }
    else
    {
        anim = &p->model_40->anims_54[sub_800AC4A8(p->s1e)];
        sub_80047E28(&sk, dword_800B0FB0, (char*)anim, p->f14 % anim->frameCount_0, 0x1000 - p->s26, &stru_8008D534[v], 0);
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
        t = &dword_8008B500.meshes_C[p->mesh_84].tris_4[p->tri_80];
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
    sub_8004D288((char*)p + 0x6c, t, (unsigned)p->f10 % ((sub_800AC8BC(p->s1c, sub_800AC474(p->s1c)) & 0xffff) + 1));
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
    sub_8001C440(a->model_40, sub_800AC4A8(a->s1c), a->f10);
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
        L.f4 = sub_80018200(r17, r16, (unsigned short)sub_800AC878(p->s1c, sub_800AC474(p->s1c)), v19, p->f2C);
        sub_800A93A4(L.rest);
        sub_800182B8(&L, p->f38);
        sub_800184DC((int)&L, 0);
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
            sub_80025B5C(o->model_40, 2, 0x17);
            sub_80025B5C(o->model_40, 7, 0x19);
            sub_800AA3F0(o);
            break;
        }
        if (o->f10 == sub_800AB170(o->s1c))
        {
            sub_80025B5C(o->model_40, 2, 0x18);
            sub_80025B5C(o->model_40, 7, 0x1A);
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
            sub_80025B5C(o->model_40, 2, 0x17);
            sub_80025B5C(o->model_40, 7, 0x19);
            sub_80025B5C(o->model_40, 0xC, 0xC);
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
            sub_80025B5C(o->model_40, 2, 0x17);
            sub_80025B5C(o->model_40, 7, 0x19);
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
            sub_80025B5C(o->model_40, 2, 0x17);
            sub_80025B5C(o->model_40, 7, 0x19);
            sub_80025B5C(o->model_40, 0xC, 0xC);
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
                printf(dword_800A07E0, dword_800A0808, 0x44e);
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
    G2Act* p = dword_8008B4A4->f24;
    p->f0 |= 0x20;
    if (a == 1)
    {
        p->f0 |= 0x800;
        p->f0 &= ~0x8000;
    }
}

int sub_800AB1EC(int a, int b, int c, int d)
{
    G2Act* p = dword_8008B4A4->f24;
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
    dword_8008B4A4->f24->f0 |= 0x400;
}

void sub_800AB28C()
{
    dword_8008B4A4->f24->f0 &= ~0x400;
}

void sub_800AB2B4()
{
    dword_8008B4A4->f24->f0 |= 0x10000;
}

void sub_800AB2DC()
{
    dword_8008B4A4->f24->f0 &= ~0x10000;
}

int sub_800AB304()
{
    return (dword_8008B4A4->f24->f0 & 1) ^ 1;
}

int sub_800AB32C()
{
    return dword_8008B4A4->f24->f8 == 0xD;
}

int sub_800AB354()
{
    unsigned t = dword_8008B4A4->f24->f0 & 0x400;
    return t != 0;
}

int sub_800AB37C(int v)
{
    dword_8008B4A4->f24->f4 = v;
    return 1;
}

int sub_800AB39C()
{
    return dword_8008B4A4->f24->f4;
}

void sub_800AB3BC()
{
    dword_8008B4A4->f24->s28 = 0;
}

void sub_800AB3D4()
{
    G2Act* p = dword_8008B4A4->f24;
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
    G2Act* p = dword_8008B4A4->f24;
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
    unsigned t = dword_8008B4A4->f24->f0 & 0x2000;
    return t != 0;
}

void sub_800AB884()
{
    dword_8008B4A4->f24->f0 &= ~0x4000;
}

void sub_800AB8AC()
{
    sub_800A9414(dword_8008B4A4->f24, 0, 3);
}

void sub_800AB8DC()
{
    G2Act* p = dword_8008B4A4->f24;
    p->model_40 = sub_800AC38C();
}

void sub_800AB910()
{
    dword_8008B4A4->f24->f0 &= ~0x800;
}

int sub_800AB938()
{
    return ((unsigned char*)dword_8008B4A4->f24)[1] >> 7;
}

int sub_800AB958()
{
    return (unsigned)dword_8008B4A4->f24->f8 < 2;
}

void sub_800AB978(short a)
{
    G2Act* p = dword_8008B4A4->f24;
    p->s24 = -1;
    p->u22 = a;
    p->f0 &= ~0x20;
}

void sub_800AB9A8(int a, int b, int c)
{
    G2Act* p = dword_8008B4A4->f24;
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
        printf(dword_800A07E0, dword_800A0808, 0x6B9);
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
    G2Act* p = dword_8008B4A4->f24;
    p->path_78 = a;
    p->f7c = 0;
    p->f0 |= 0x400000;
}

void sub_800ABAD4()
{
    G2Act* p = dword_8008B4A4->f24;
    p->f0 &= ~0x400000;
    sub_800ABC78(0);
    p->f0 = (p->f0 & ~0x800) | 8;
    sub_800AB010(p, 0, 3, 0);
    p->fC = 0;
}

int sub_800ABB44()
{
    return ((dword_8008B4A4->f24->f0 >> 22) ^ 1) & 1;
}

int sub_800ABB70()
{
    return dword_8008B4A4->f24->f8 == 0x17;
}

void sub_800ABB98(int a)
{
    G2Act* p = dword_8008B4A4->f24;
    if (a == 1)
        p->f0 |= 0x100000;
    else
        p->f0 &= ~0x100000;
}

void sub_800ABBD8(int a)
{
    G2Act* p = dword_8008B4A4->f24;
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
    G2Act* p = dword_8008B4A4->f24;
    if (a)
        p->f0 &= ~0x40000;
    else
        p->f0 |= 0x40000;
}

void sub_800ABC78(int a)
{
    G2Act* p = dword_8008B4A4->f24;
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
        p->f2C = sub_8001AC8C(p->f34);
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
        p->f2C = sub_800189F8();
        RequestEffect_800148F4(p->f2C);
    }
    else if (p->s20 == 0x1D)
    {
        p->f2C = ((int (*)(int))sub_8001CDCC)(p->f34);
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
            r = &dword_8007A14C;
        else
            r = &dword_8007A0EC;
    }
    else if (f & 0x100)
    {
        if (f & 1)
            r = &dword_8007A140;
        else
            r = &dword_8007A0E0;
    }
    else if (f & 0x80)
    {
        if (f & 1)
            r = &dword_8007A134;
        else
            r = &dword_8007A0D4;
    }
    else if (f & 0x40)
    {
        if (f & 1)
            r = &dword_8007A128;
        else
            r = &dword_8007A0C8;
    }
    else if (f & 0x20)
    {
        if (f & 1)
            r = &dword_8007A11C;
        else
            r = &dword_8007A0BC;
    }
    else if (f & 0x10)
    {
        if (f & 1)
            r = &dword_8007A110;
        else
            r = &dword_8007A0B0;
    }
    else if (f & 8)
    {
        if (f & 1)
            r = &dword_8007A104;
        else
            r = &dword_8007A0A4;
    }
    else if (f & 1)
    {
        r = &dword_8007A0F8;
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
    dword_8008B4A4->f24->f0 |= 0x800000;
}

void sub_800AC340(int a)
{
    G2Act* p = dword_8008B4A4->f24;
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
        r = ((int (*)(int))sub_8001D060)(s->levantStatus_7C8.field_1C[1]) + dword_800B11B8[s->field_834];
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
    G2Rec* p = sub_80024E38(dword_8007DC60->items_8);
    return p[sub_800AC794(a, dword_800B11DC[sub_800AC3E4()])].f0;
}

int sub_800AC518(int a)
{
    G2Rec* p = sub_80024E38(dword_8007DC60->items_8);
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
    return (unsigned char*)sub_80024E38(dword_8007DC60->items_8) + ((a << 10) + 0x380);
}

short sub_800AC7F0(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = sub_80024E38(dword_8007DC60->items_8);
    return p[r].s4;
}

short sub_800AC834(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = sub_80024E38(dword_8007DC60->items_8);
    return p[r].s6;
}

short sub_800AC878(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = sub_80024E38(dword_8007DC60->items_8);
    return p[r].s8;
}

unsigned short sub_800AC8BC(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = sub_80024E38(dword_8007DC60->items_8);
    return p[r].sA;
}

unsigned char sub_800AC900(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = sub_80024E38(dword_8007DC60->items_8);
    return p[r].f3;
}

short sub_800AC944(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = sub_80024E38(dword_8007DC60->items_8);
    return p[r].sC;
}

unsigned char sub_800AC988(int a, int b)
{
    G2Rec* p;
    int r = sub_800AC794(a, b);
    p = sub_80024E38(dword_8007DC60->items_8);
    return p[r].f0;
}

short* sub_800AC9CC(int a)
{
    G2Rec* p;
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    p = sub_80024E38(dword_8007DC60->items_8);
    return &p[r].sC;
}

int* sub_800ACA38(int a)
{
    G2Rec* p;
    int r = sub_800AC794(a, dword_800B11DC[sub_800AC3E4()]);
    p = sub_80024E38(dword_8007DC60->items_8);
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
extern int dword_800B11CC[]; // model FTG ids for sub_80024FFC, -1 ends
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
                sub_80040148((int*)&dword_800B1DD0, 1);
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
                sub_80025974(m, sub_800AC3F4(), 1);
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
                sub_80024FFC(m, dword_800B11CC);
                q->flags &= ~8;
            }
            if ((q->flags & 0x12) == 0x10)
            {
                m = AcquireModel_80024D70(dword_8007DC60, name_800B1164[saveData_8008B570.field_830]);
                sub_80025C38(m, (((unsigned)unknownFlags_8008D678 >> 24) ^ 1) & 1);
                q->flags &= ~0x10;
            }
            if (q->flags == 0)
            {
                more = 0;
                sub_800AB8DC();
                ClearOTagRAll_8001B260();
                EndFade_8001C290();
            }
            sub_80040148((int*)&dword_800B1DD0, 0);
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

INCLUDE_OVERLAY_ASM(game, dword_800A094C);

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

INCLUDE_OVERLAY_ASM(game, dword_800ADE78);
