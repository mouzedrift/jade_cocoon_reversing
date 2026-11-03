// BATTLE.BIN, source file 2 of 3 from 0x800BC90C (.rdata from 0x800B6700)
#include "battle.h"

INCLUDE_OVERLAY_ASM(battle, dword_800B6700);

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

extern char dword_800C9124[];
extern char cameraState_8008D4F0[];
extern short word_8008D4C8;
extern short word_8008D51E;
extern unsigned char dword_800C911C[];
extern void sub_80043DE0(void* a0, void* a1, void* a2, void* a3);
typedef struct BatStageObj_a
{
    char pad0[0x38];
    int x_38;
    int y_3C;
    int z_40;
} BatStageObj_a;

void sub_800BC90C(BatStageObj_a* p)
{
    int scale[3] = { 0x1000, 0x1000, 0x1000 };
    int idx;
    int i;

    unknownFlags_8008D678 &= ~0x10000;
    idx = sub_80020F00(&dword_80095468, 1, dword_800C8EAC[dword_80083BD0].model_6);
    sub_8004D1EC(dword_80095468.models_28[idx].ftg_4, pOT_8008B4C8, &p->x_38, dword_800C9124, stru_8008D534, 1, scale);
    {
        unsigned short* list = dword_800C8EAC[dword_80083BD0].list_0;
        char* sd = (char*)&saveData_8008B570;
        for (; *list != 0xFFFF; list++)
        {
            EffectSprite* g = &dword_80095468.sprites_20[sub_80020F00(&dword_80095468, 0, *list)];
            int j;
            for (j = 0; j < g->n_0; j++)
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
                    pos.vy = *(int*)(sd + 0x7AC) + e->pos_10[1];
                    if (e->size_C[1] != 0)
                    {
                        col.r = l->r_30 + e->rgb_18[0] * l->r_50 / 4096;
                        col.g = l->g_31 + e->rgb_18[1] * l->g_52 / 4096;
                        col.b = l->b_32 + e->rgb_18[2] * l->b_54 / 4096;
                        if (dword_80083BD0 == 0x10)
                        {
                            SetSemiTrans(&g->poly_C, 1);
                        }
                        if (dword_80083BD0 == 0x13)
                        {
                            sz[0] = e->size_C[0] * 5;
                            sz[1] = e->size_C[1] * 5;
                            sub_80044010(&g->poly_C, &pos, dword_800C9124, &e->u_0, &e->w_4, &e->f8, sz, &e->pos_10[0], &col, 0, 0, pOT_8008B4C8);
                        }
                        else
                        {
                            sub_80043DE0(&g->poly_C, &pos, e->size_C, &col);
                        }
                    }
                }
            }
        }
    }
    if (dword_800C8EAC[dword_80083BD0].floor_8 >= 0)
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
            short* cam = &word_8008D4C8;
            v.vx = p->x_38;
            v.vy = p->y_3C;
            v.vz = p->z_40;
            a = -cam[1];
            v.vx += sinTable_80084540[a & 0xFFF];
            v.vy = levantPos_8008BD18.pos_0[1] - 0x352;
            v.vx -= dword_8008D600.vx;
            v.vy -= dword_8008D600.vy;
            v.vz += sinTable_80084540[(a + 0x400) & 0xFFF];
            v.vz -= dword_8008D600.vz;
            sv.vx = v.vx;
            sv.vy = v.vy;
            sv.vz = v.vz;
            RotTransPers(&sv, (long*)&sxy, &pp, &flag);
            poly = dword_80095468.sprites_20[dword_800C8EAC[dword_80083BD0].floor_8 + i % 4].poly_C;
            x = ((cam[1] & 0xFFF) / 4 + i * 96 - 0x400) * word_8008D51E / 240;
            if ((unsigned int)(x + 0x60) < 0x1A0)
            {
                w = word_8008D51E * 96 / 240;
                poly.r0 = poly.r0 * dword_8008D40C >> 12;
                poly.g0 = poly.g0 * dword_8008D40C >> 12;
                poly.b0 = poly.b0 * dword_8008D40C >> 12;
                setShadeTex(&poly, 0);
                setXYWH(&poly, x, sxy.vy - w, w + 1, w + 1);
                *(POLY_FT4*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = poly;
                addPrim(&pOT_8008B4C8[0x3FF], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(POLY_FT4);
            }
        }
    }
    if (dword_800C8EAC[dword_80083BD0].anim_A >= 0)
    {
        int cols = 0;
        unsigned int n = 0;
        if (dword_80083BD0 == 0xF)
        {
            cols = 3;
            n = 9;
        }
        else if (dword_80083BD0 == 0x13)
        {
            cols = 4;
            n = 0xE;
        }
        else if (dword_80083BD0 == 0x15 || dword_80083BD0 == 0x1D || dword_80083BD0 == 6 || dword_80083BD0 == 0x1C || dword_80083BD0 == 5)
        {
            cols = 1;
            n = 0xC;
        }
        switch (dword_80083BD0)
        {
        case 5:
        case 6:
        case 0xF:
        case 0x13:
        case 0x15:
        case 0x1C:
        case 0x1D:
        {
            EffectSprite* g = &dword_80095468.sprites_20[sub_80020F00(&dword_80095468, 0, dword_800C8EAC[dword_80083BD0].anim_A)];
            int j;
            for (j = 0; j < g->n_0; j++)
            {
                int half = n >> 1;
                int t = (dword_800C911C[j % 8] + (unsigned int)frameCount_8008D3FC) % n;
                int k;
                if (dword_80083BD0 == 0x13 && half < t)
                {
                    t = n - t;
                }
                if (dword_80083BD0 == 0x15 || dword_80083BD0 == 0x1D || dword_80083BD0 == 6 || dword_80083BD0 == 0x1C || dword_80083BD0 == 5)
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
                    char* sd;
                    BatLight_a* l;
                    if (dword_800C9D8C[1] < 0 && dword_800C9D8C[0] < 0)
                    {
                        dword_800C9D8C[0] = g->poly_C.u0;
                        dword_800C9D8C[1] = g->poly_C.v0;
                    }
                    du = t % cols;
                    dv = t / cols;
                    sd = (char*)&saveData_8008B570;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    pos.vx += e->pos_10[0];
                    pos.vz += e->pos_10[2];
                    pos.vy = *(int*)(sd + 0x7AC) + e->pos_10[1];
                    du = du * (e->w_4 + 1);
                    dv = dv * (e->h_6 + 1);
                    uu = e->u_0 + du;
                    vv = e->v_2 + dv;
                    if (cols == 1)
                    {
                        uu = e->u_0;
                    }
                    g->poly_C.u0 = dword_800C9D8C[0] + uu;
                    g->poly_C.v0 = dword_800C9D8C[1] + vv;
                    g->poly_C.u1 = dword_800C9D8C[0] + uu + e->w_4;
                    g->poly_C.v1 = dword_800C9D8C[1] + vv;
                    g->poly_C.u2 = dword_800C9D8C[0] + uu;
                    g->poly_C.v2 = dword_800C9D8C[1] + vv + e->h_6;
                    g->poly_C.u3 = dword_800C9D8C[0] + uu + e->w_4;
                    g->poly_C.v3 = dword_800C9D8C[1] + vv + e->h_6;
                    if (e->size_C[1] != 0)
                    {
                        l = (BatLight_a*)cameraState_8008D4F0;
                        col.r = l->r_30 + e->rgb_18[0] * l->r_50 / 4096;
                        col.g = l->g_31 + e->rgb_18[1] * l->g_52 / 4096;
                        col.b = l->b_32 + e->rgb_18[2] * l->b_54 / 4096;
                        SetSemiTrans(&g->poly_C, 1);
                        sub_80043DE0(&g->poly_C, &pos, e->size_C, &col);
                    }
                }
            }
            break;
        }
        default:
        {
            EffectSprite* g = &dword_80095468.sprites_20[sub_80020F00(&dword_80095468, 0, dword_800C8EAC[dword_80083BD0].anim_A)];
            int j = ((unsigned int)frameCount_8008D3FC % (g->n_0 * 2)) / 2;
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
                    char* sd = (char*)&saveData_8008B570;
                    BatLight_a* l = (BatLight_a*)cameraState_8008D4F0;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    d = ISqrt_8003B918(e->pos_10[0] * e->pos_10[0] + e->pos_10[2] * e->pos_10[2]);
                    ang = ratan2_8003B548(e->pos_10[0], e->pos_10[2]) + m * 512;
                    pos.vx += sinTable_80084540[(ang + 0x400) & 0xFFF] * d / 4096;
                    pos.vz += sinTable_80084540[ang & 0xFFF] * d / 4096;
                    pos.vy = *(int*)(sd + 0x7AC) + e->pos_10[1];
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
                        sub_80043DE0(&g->poly_C, &pos, e->size_C, &col);
                    }
                }
            }
            break;
        }
        }
    }
    if (dword_800C8EAC[dword_80083BD0].models_C != 0)
    {
        for (i = 0; i < 3; i++)
        {
            unsigned short* ent = &dword_800C8EAC[dword_80083BD0].models_C[i * 4];
            int id = ent[0];
            int fl = ent[1];
            unsigned long* ot = pOT_8008B4C8;
            if (id != 0xFF)
            {
                int sc[3] = { 0x1000, 0x1000, 0x1000 };
                VECTOR pos;
                SVECTOR rot;
                EffectModel* mdl = &dword_80095468.models_28[sub_80020F00(&dword_80095468, 1, id)];
                int k;
                memset(&rot, 0, 8);
                if (dword_80083BD0 == 0x10)
                {
                    rot.vy = frameCount_8008D3FC * 100;
                }
                pos.vx = p->x_38;
                pos.vy = p->y_3C;
                pos.vz = p->z_40;
                pos.vy = levantPos_8008BD18.pos_0[1];
                if (dword_80083BD0 == 0x13 && i == 0)
                {
                    sc[0] *= 3;
                    sc[1] *= 3;
                    sc[2] *= 3;
                }
                if (dword_80083BD0 == 0x14)
                {
                    pos.vy -= 0x2F8;
                }
                for (k = 0; k < mdl->n_0; k++)
                {
                    sub_8004D1EC(&mdl->ftg_4[k], ot, &pos, &rot, 0, fl, sc);
                }
            }
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BC90C);

void sub_800BDA28(BatTask_a* t)
{
    int i;
    int f;
    int m;
    if (!(dword_800B1228 & 0x1000))
    {
        sub_800BB794();
        sub_800BB7D4();
        ApplyBattleCommand_800BEBB8();
        if (!(*(int*)&saveData_8008B570 & 2))
        {
            f = 0;
            for (i = 4; i < 7; i++)
            {
                m = sub_800A248C() & (1 << i);
                if (m != 0)
                {
                    if (sub_800BF980(sub_800A2BE4(i - 4)))
                    {
                        f = 1;
                        break;
                    }
                }
            }
            if (f)
            {
                sub_80037828(sub_800BC7DC(dword_800C9C7C), (short)dword_800C9C88.kind_0, 1);
            }
            else
            {
                sub_80037828(sub_800BC7DC(dword_800C9C7C), (short)dword_800C9C88.kind_0, 0);
            }
        }
    }
    t->next_8 = sub_800BDB4C;
}

void sub_800BDB4C(BatTask_a* t)
{
    if (sub_800BDD3C() == 1)
    {
        sub_800BF2E8();
        sub_800BDEBC();
        sub_800BDF74();
        sub_800BDFAC();
        sub_800BE2C8();
        t->next_8 = sub_800BDBB0;
    }
}

void sub_800BDBB0(BatTask_a* t)
{
    if (sub_800BDE04() == 1)
    {
        if (dword_800C9C88.kind_0 == 2 && dword_800C9C7C == 0)
        {
            sub_800C0AEC(dword_800C9C98 - 1, levantPos_8008BD18.pos_0, levantPos_8008BD18.angle_E);
        }
        dword_800C9D90 = 0;
        dword_800C9D94 = 0;
        t->next_8 = sub_800BDC3C;
    }
}

void sub_800BDC3C(BatTask_a* t)
{
    int k;
    if ((short)sub_800BE364() < dword_800C9D94 && sub_800BEA94() == 1)
    {
        while ((k = dword_800C9D90--) != 0)
        {
            sub_800A2924(dword_800C9DD0[dword_800C9D90]);
        }
        t->f0 = (t->f0 & ~1) | 0x8000;
        dword_800B1228 &= ~0x1000;
    }
    else
    {
        sub_800BE3C0();
    }
    dword_800C9D94++;
}

int sub_800BDD3C()
{
    unsigned char i;
    int r;
    int m;
    if (*(int*)&saveData_8008B570 & 0x20)
    {
        return 1;
    }
    if (dword_800C9C82 == 0)
    {
        r = sub_800A89F0();
    }
    else
    {
        r = sub_800C0D60();
    }
    if (r == 0)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        m = sub_800A248C() & (1 << i);
        if (m != 0)
        {
            if (sub_800A2550(i - 4) == 0)
            {
                return 0;
            }
        }
    }
    return IsEffectTaskIdle_800148D4() != 0;
}

int sub_800BDE04()
{
    unsigned char i;
    int r;
    int m;
    if (*(int*)&saveData_8008B570 & 0x20)
    {
        return 1;
    }
    if (dword_800C9C82 == 0)
    {
        r = sub_800A8BE4();
    }
    else
    {
        r = sub_800C0D88();
    }
    if (r == 0)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        r = sub_800A248C();
        m = 1 << i;
        if (r & m)
        {
            if (sub_800A2594(i - 4) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void sub_800BDEBC()
{
    int x;
    int y;
    int ny;
    if (!(*(int*)&saveData_8008B570 & 0x20))
    {
        x = dword_800C9C88.mask_8;
        if (x & 0xF)
        {
            x &= ~0xE;
            x |= 1;
        }
        y = dword_800C9C88.targets_C;
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
            if (dword_800C9C88.mask_8)
            {
                sub_800BC468(y, dword_800C9C88.mask_8);
            }
        }
        if (x)
        {
            if (dword_800C9C88.targets_C)
            {
                sub_800BC468(x, dword_800C9C88.targets_C);
            }
        }
    }
}

void sub_800BDF74()
{
    sub_800BE058(dword_800C9D98, &dword_800C9C88, 0, dword_800C9C7C);
}

void sub_800BDFAC()
{
    unsigned char i;
    BatPair_a t;
    for (i = 0; i < 7; i++)
    {
        if (dword_800C9C7C == i)
        {
            t.a = 0;
            t.b = 0;
        }
        else
        {
            sub_800BE058(&t, &dword_800C9CC8[i], 1, i);
        }
        dword_800C9DA0[i] = t;
    }
}

BatPair_a* sub_800BE058(BatPair_a* out, BatCmd_a* p, int c, int a)
{
    BatPair_a r;
    if ((*(int*)&saveData_8008B570 & 0x20) || sub_800BC570(a) == 0)
    {
        r.a = 0;
        r.b = 0;
    }
    else
    {
        switch ((unsigned int)sub_800BC7DC(a))
        {
        case 0:
            sub_800A8A30(&r, p, c);
            break;
        case 1:
            sub_800C0DDC(&r, p, c);
            break;
        case 2:
            sub_800A2684(&r, p, c);
            break;
        }
    }
    *out = r;
    return out;
}

void sub_800BE14C(BatCmd_a* p, int b, int k)
{
    int r;
    if (*(int*)&saveData_8008B570 & 0x20)
    {
        return;
    }
    if (sub_800BC570(k) == 0)
    {
        return;
    }
    r = sub_800BC7DC(k);
    switch ((unsigned int)r)
    {
    case 0:
        sub_800A8C0C(b);
        break;
    case 1:
        sub_800C0E84(p, b);
        break;
    case 2:
        sub_800A2760(p, b);
        if (p->kind_0 == 0x13 || p->kind_0 == 0xB || p->kind_0 == 7 || (p->kind_0 == 5 && sub_80013358(p->arg_4) == 1) || (p->kind_0 == 0x1A && sub_80013358(p->arg_4) == 1))
        {
            dword_800C9DD0[dword_800C9D90] = k - 4;
            dword_800C9D90++;
        }
        break;
    }
    if (!(*(int*)&saveData_8008B570 & 2) && b == 0)
    {
        sub_800377B4(r, (short)p->kind_0, k - 4);
    }
}

void sub_800BE2C8()
{
    int m = sub_800BE364();
    unsigned char i;
    dword_800C9DBC = m - dword_800C9D98[0];
    dword_800C9D98[1] += dword_800C9DBC;
    for (i = 0; i < 7; i++)
    {
        dword_800C9DC0[i] = m - dword_800C9DA0[i].a;
        dword_800C9DA0[i].b += dword_800C9DC0[i];
    }
}

int sub_800BE364()
{
    unsigned char i;
    short m = dword_800C9D98[0];
    for (i = 0; i < 7; i++)
    {
        if (m < dword_800C9DA0[i].a)
        {
            m = dword_800C9DA0[i].a;
        }
    }
    return m;
}

void sub_800BE3C0()
{
    unsigned char i;
    int v;
    if (dword_800C9DBC == dword_800C9D94 && dword_800C9C7C < 7)
    {
        sub_800BE14C(&dword_800C9C88, 0, dword_800C9C7C);
        sub_800BF3DC(dword_800C9C7C, 0, dword_800C9C7E, sub_800BC6CC(dword_800C9C7C), 0);
        if (dword_800C9C7E > 0)
        {
            sub_80037BFC(0x1E);
            PlaySfx_80031494(0x72);
        }
        sub_800BF3DC(dword_800C9C7C, 1, dword_800C9C80, sub_800BC6CC(dword_800C9C7C), 0);
        v = dword_800C9C88.kind_0;
        if (v == 5 || v == 0x1A)
        {
            sub_800AD944(1);
        }
        else if (v == 4)
        {
            sub_800AD1E0(dword_800C9C88.arg_4, 1, 0);
        }
        else if (v == 0x13)
        {
            sub_800127B8(sub_80014390(dword_800C9C7C));
        }
        if (dword_800C9C88.kind_0 == 7 && dword_800C9C7C != 0)
        {
            PlaySeqSlot_80031160(0x1C, 1);
        }
        if (sub_800BC7DC(dword_800C9C7C) == 0 || sub_800BC7DC(dword_800C9C7C) == 1)
        {
            v = dword_800C9C88.kind_0;
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
    if (dword_800C9D98[0] + dword_800C9DBC == dword_800C9D94)
    {
        if (dword_800C9D78 >= 0)
        {
            if ((unsigned short)(dword_800C9D78 - 0x70) < 3)
            {
                PlaySfx_80031494(dword_800C9D78);
            }
        }
        if (dword_800C9D80 >= 0)
        {
            if (sub_800BC820(4) == 1 || (sub_800BC820(8) != 1 && sub_800BC820(0x100000) == 1))
            {
                PlaySeqSlot_80031160(0x1C, 1);
            }
            else
            {
                PlaySfx_80031494(0x6F);
            }
        }
        if (dword_800C9D84 != *(signed char*)&dword_800C9D82)
        {
            sub_80039ED8(dword_800C9D84);
            dword_800C9D82 = dword_800C9D84;
        }
    }
    for (i = 0; i < 7; i++)
    {
        if (dword_800C9DC0[i] == dword_800C9D94)
        {
            if (dword_800C9C7C != i)
            {
                BatCmd_a* s = &dword_800C9CC8[i];
                if ((s->kind_0 == 5 && sub_80013358(s->arg_4) == 1) || (s->kind_0 == 0x1A && sub_80013358(s->arg_4) == 1))
                {
                    sub_800A2898(i - 4);
                }
                sub_800BE14C(&dword_800C9CC8[i], 1, i);
            }
            if (dword_800C9DC0[i] == dword_800C9D94)
            {
                sub_800127D0(i, 0x11, 0, dword_800C9D58[i]);
                sub_800127D0(i, 0x10, 0, dword_800C9CA0[i]);
                sub_800BE834(i, sub_800BC6CC(i));
                if (sub_800BC784(i) == 1)
                {
                    if (i >= 4)
                    {
                        sub_800A284C(i - 4);
                    }
                    else if (i != 0 && dword_800C9C82 != 0)
                    {
                        sub_800C0F1C();
                    }
                }
            }
        }
    }
}
