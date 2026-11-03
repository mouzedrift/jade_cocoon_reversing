// EVENTFNC.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct EvInsEventfnc
{
    int op_0;
    int a_4;
    int b_8;
    int c_C;
} EvInsEventfnc;

typedef struct EvEntEventfnc
{
    char pad_0[0x7C];
    int f7C_7C;
    int f80_80;
    int f84_84;
    int pad_88;
    int f8C_8C;
} EvEntEventfnc;

typedef struct EvVecEventfnc
{
    int x_0;
    int y_4;
    int z_8;
} EvVecEventfnc;

extern EvVecEventfnc levantPos_8008BD18;

typedef struct EvRotEventfnc
{
    short pad_0;
    short ang_2;
} EvRotEventfnc;

typedef struct EvCtxEventfnc
{
    unsigned int flags_0;
    EvInsEventfnc* start_4;
    EvInsEventfnc* pc_8;
    EvInsEventfnc* ret_C;
    int f10_10;
    int f14_14;
    int f18_18;
    int f1C_1C;
    char pad_20[4];
    int f24_24[6];
    EvVecEventfnc vec3C_3C[5];
    EvVecEventfnc vec78_78[5];
    int fB4_B4;
    int fB8_B8;
    int fBC_BC;
    int fC0_C0;
    unsigned int fC4_C4;
    int fC8_C8;
    int fCC_CC[8];
    int fEC_EC;
    int fF0_F0;
    int fF4_F4;
    int fF8_F8;
    int fFC_FC;
    unsigned short f100_100;
    unsigned short f102_102;
    int f104_104;
    int f108_108;
    char pad_10C[4];
    int* f110_110;
    int f114_114;
    int f118_118;
    int f11C_11C;
    EvEntEventfnc* ent_120;
} EvCtxEventfnc;

typedef struct EvMsgEventfnc
{
    int m0_0;
    int m4_4;
    int m8_8;
    int mC_C;
    int m10_10;
    int m14_14;
    int m18_18;
    int m1C_1C;
    int m20_20;
    int m24_24;
} EvMsgEventfnc;

typedef struct EvObjEventfnc
{
    char pad_0[0x1A];
    short f1A_1A;
    char pad_1C[0x90 - 0x1C];
    int f90_90;
} EvObjEventfnc;

typedef struct EvTriEventfnc
{
    short x_0;
    short y_2;
    short z_4;
    char pad_6[0x12];
    short nx_18;
    short ny_1A;
    short nz_1C;
    char pad_1E[2];
} EvTriEventfnc;

typedef struct EvMeshEventfnc
{
    short nTris_0;
    short pad_2;
    EvTriEventfnc* tris_4;
} EvMeshEventfnc;

typedef struct EvSaveEventfnc
{
    char pad_0[0x2DC];
    unsigned short f2DC_2DC;
    short pad_2DE;
    unsigned short f2E0_2E0;
    short pad_2E2;
    short f2E4_2E4;
    short pad_2E6;
    short f2E8_2E8;
    short pad_2EA;
    short f2EC_2EC;
    short f2EE_2EE;
    char pad_2F0[0x7A8 - 0x2F0];
    int f7A8_7A8;
    int f7AC_7AC;
    int f7B0_7B0;
    short pad_7B4;
    unsigned short f7B6_7B6;
} EvSaveEventfnc;

extern EvVecEventfnc* sub_800BBC00(EvCtxEventfnc* c, int a, int b);
extern EvVecEventfnc* sub_800BBC80(EvCtxEventfnc* c, int a, int b);
extern EvVecEventfnc* sub_800BBBA0(int a);
extern int sub_800BB840(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b);
extern int sub_800BB990(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b);
extern void sub_800BBDA0(int a, int b);
extern int sub_800BBDD8(int a);
extern char dword_80091C10[];
extern int dword_800AEBD8;
extern void sub_800B8940(int* p);
extern void RequestLoaderModel_800206A0(int a, int b, int c, int d);
extern void StartModelLoader_8002056C(void);

INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6D00);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B6DD4);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B716C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B73C0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B76B8);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B79E0);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B7E40);

typedef struct EvQuadEventfnc
{
    short x_0;
    short y_2;
    short z_4;
    short pad_6;
} EvQuadEventfnc;
int sub_800B8028(int* out, EvQuadEventfnc* v)
{
    int i;
    int j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (i != j && v[i].x_0 == v[j].x_0 && v[i].y_2 == v[j].y_2 && v[i].z_4 == v[j].z_4)
            {
                out[0] = v[i].x_0;
                out[1] = v[i].y_2;
                out[2] = v[i].z_4;
                return 1;
            }
        }
    }
    return 0;
}

typedef struct EvMapEventfnc
{
    int f0_0;
    unsigned int nMeshes_4;
    int f8_8;
    EvMeshEventfnc* meshes_C;
    char pad_10[0x10];
    EvMeshEventfnc* meshes20_20;
} EvMapEventfnc;

extern int sub_800B76B8(EvMeshEventfnc* m, EvVecEventfnc* pos);

int sub_800B80C8(EvEntEventfnc* e)
{
    unsigned int i;
    unsigned int k = e->f84_84;
    int r;
    for (i = 0; i < ((EvMapEventfnc*)dword_8008B500)->nMeshes_4; i++, k++)
    {
        k %= ((EvMapEventfnc*)dword_8008B500)->nMeshes_4;
        r = sub_800B76B8(&((EvMapEventfnc*)dword_8008B500)->meshes_C[k], &levantPos_8008BD18);
        if (r >= 0)
        {
            e->f80_80 = r;
            if (e->f84_84 != k)
            {
                e->f84_84 = k;
            }
            return 1;
        }
    }
    return 0;
}

int sub_800B8184(EvVecEventfnc* pos, unsigned int k)
{
    unsigned int i;
    for (i = 0; i < ((EvMapEventfnc*)dword_8008B500)->nMeshes_4; i++)
    {
        k %= ((EvMapEventfnc*)dword_8008B500)->nMeshes_4;
        if (sub_800B76B8(&((EvMapEventfnc*)dword_8008B500)->meshes_C[k], pos) >= 0)
        {
            return k;
        }
        k++;
    }
    return -1;
}

extern void sub_800B79E0(int a, int* p, int b, int* c, int* d);
extern void sub_800B7E40(int* p, int a, int b, int c, int* d);
void sub_800B8220(int* p, int a1, int a2, int* a3, int* a4, int* a5)
{
    sub_800B79E0(a2, p, a1, a3, a4);
    sub_800B7E40(p, a2, *a3, *a4, a5);
    p[0] += a5[2] >> 10;
    p[2] -= a5[0] >> 10;
}

int sub_800B82C8(int* p, int* a1, char* ents, unsigned char* flags, int n)
{
    int i;
    int t0;
    int t1;
    int v[4];
    for (i = 0; i < n; i++)
    {
        if (flags[i])
        {
            t1 = -1;
            t0 = -1;
            sub_800B79E0((int)(ents + i * 8), a1, (int)p, &t0, &t1);
            if (t0 != -1 && t1 != -1)
            {
                sub_800B7E40(p, (int)(ents + i * 8), t0, t1, v);
                p[0] -= v[2] >> 10;
                p[2] += v[0] >> 10;
                return 0;
            }
        }
    }
    return 1;
}

void sub_800B83E4(int* v, EvMeshEventfnc* m, int i)
{
    EvTriEventfnc* t = &m->tris_4[i];
    v[1] = (t->ny_1A * t->y_2 - t->nx_18 * (v[0] - t->x_0) - t->nz_1C * (v[2] - t->z_4)) / t->ny_1A;
}

typedef struct EvMapEntEventfnc
{
    short id_0;
    char pad_2[2];
    short f4_4;
    unsigned short f6_6;
    char pad_8[8];
} EvMapEntEventfnc;

typedef struct EvSpawnEventfnc
{
    int a_0[3];
    int b_C[3];
    short f18_18;
    short f1A_1A;
} EvSpawnEventfnc;

extern EvMapEntEventfnc** dword_800B0608[];
extern int sub_800A49CC(int a, int b, int* c, EvSpawnEventfnc* d);
extern void sub_800B8568(int a, int b, int c, int d);

void sub_800B844C(int* t)
{
    EvSaveEventfnc* s;
    EvSpawnEventfnc sp;
    int i;
    int n;
    if (IsModelLoaderDone_800205D0())
    {
        EvMapEntEventfnc*** tbl = dword_800B0608;
        s = (EvSaveEventfnc*)&saveData_8008B570;
        sp.f1A_1A = tbl[s->f2E4_2E4][s->f2E8_2E8][s->f2EE_2EE].f6_6;
        sp.f18_18 = tbl[s->f2E4_2E4][s->f2E8_2E8][s->f2EC_2EC].f6_6;
        n = sub_800A49CC(tbl[s->f2E4_2E4][s->f2E8_2E8][s->f2EE_2EE].f4_4, sp.f18_18, dword_80091C60, &sp);
        for (i = 0; i < n; i++)
        {
            sub_800B8568(sp.a_0[i], sp.b_C[i], -1, i);
        }
        t[0] = (t[0] & ~1) | 0x8000;
    }
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8568);

extern int* dword_8008D674;
extern void sub_800A170C();
extern void sub_800A1794();
extern void sub_800B844C();
void sub_800B88A4(int a)
{
    int* p;
    int* q;
    if (a)
    {
        sub_800B8940((int*)a);
        eventDispatchHalt_8008B540 = 1;
    }
    p = dword_8008D674;
    p[4] = (p[4] | 1) & 0xFFFF7FFF;
    p += 4;
    q = (int*)p[5];
    q[2] = 0;
    q[3] = 0;
    q[4] = 0;
    q[5] = 0;
    p[2] = (int)sub_800B844C;
    sub_800A170C();
    sub_800A1794();
}

void sub_800B8928()
{
    int i;
    for (i = 0x2a; i >= 0; i--)
    {
    }
}

void sub_800B8940(int* p)
{
    int i = 0;
    int* q = p;
    for (; i < 3; i++)
    {
        unsigned short* e = (unsigned short*)sub_80019C70(*q++);
        RequestLoaderModel_800206A0(e[0], ((unsigned char*)e)[2] << 1, 3, -1);
    }
    StartModelLoader_8002056C();
}

int sub_800B89A8(EvCtxEventfnc* c)
{
    c->pc_8++;
    return 1;
}

extern unsigned short padPressed_8009194C;
int sub_800B89C0(EvCtxEventfnc* c)
{
    if (padPressed_8009194C & 0x100)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int sub_800B8A34(EvCtxEventfnc* c);
int sub_800B89F4(EvCtxEventfnc* c)
{
    if (sub_800B8A34(c))
    {
        c->flags_0 |= 1;
    }
    return 0;
}

extern void sub_800A1974(void);
extern void sub_800A5B54(EvCtxEventfnc* c);
int sub_800B8A34(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    int i;
    switch (c->fB8_B8)
    {
    case 0:
        if (c->f1C_1C & c->f14_14)
        {
            m.m0_0 = c->f1C_1C;
            m.m4_4 = 4;
            m.mC_C = c->f24_24[c->pc_8->b_8];
            if (!sub_800BB990(c, &m, 1, 0))
            {
                return 0;
            }
        }
        c->fB8_B8++;
    case 1:
        if (c->f18_18)
        {
            return 0;
        }
        c->fB8_B8++;
    case 2:
        for (i = 0; i < 5; i++)
        {
            int bit = 1 << i;
            if (c->f14_14 & bit)
            {
                if (i == 0)
                {
                    sub_800A8E38();
                }
                else
                {
                    sub_800A785C(i - 1);
                }
                c->f14_14 &= ~(1 << i);
            }
        }
        if (c->f14_14 == 0 && (c->flags_0 & 0x20))
        {
            c->flags_0 &= ~0x20;
            sub_800A1974();
        }
        if (dword_800AEBD8 == c->f10_10)
        {
            dword_800AEBD8 = -1;
        }
        sub_800A5B54(c);
        c->fB8_B8 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

#if 0
extern int dword_800B0EC0;
extern int dword_800B1260;
extern int sub_800A6D50(int a);
extern void sub_800A1904(void);
int sub_800B8BE8(EvCtxEventfnc* c)
{
    int r;
    if (dword_800B0EC0 != 1)
    {
        return 0;
    }
    if (dword_800B1260 != 0)
    {
        return 0;
    }
    if (dword_800AEBD8 >= 0)
    {
        if (c->f10_10 != dword_800AEBD8)
        {
            return 0;
        }
    }
    r = sub_800A6D50(0);
    if (r != sub_800A6D50(2))
    {
        return 0;
    }
    c->flags_0 |= 0x20;
    sub_800A1904();
    dword_800AEBD8 = c->f10_10;
    c->pc_8++;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8BE8);

int sub_800B8CB0(EvCtxEventfnc* c)
{
    EvInsEventfnc* p = c->pc_8;
    if (p->b_8 != 0)
    {
        c->ret_C = p;
        c->pc_8 = p + 1;
        c->flags_0 |= 0x10;
    }
    else
    {
        c->flags_0 &= ~0x10;
        c->pc_8++;
    }
    return 1;
}

extern int sub_800A7810(int a);
extern void sub_800A8E0C(void);
extern void sub_800A8DEC(void);
int sub_800B8D08(EvCtxEventfnc* c)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        int bit = 1 << i;
        if (c->pc_8->b_8 & bit)
        {
            if (i == 0)
            {
                sub_800A8E0C();
                sub_800A8DEC();
            }
            else if (sub_800A7810(i - 1) == 0)
            {
                return 0;
            }
            sub_800BBC00(c, i, 1);
            sub_800BBC80(c, i, 1);
            c->f14_14 |= 1 << i;
        }
    }
    c->pc_8++;
    return 1;
}

extern void sub_800A8E38(void);
extern void sub_800A785C(int a);
int sub_800B8DDC(EvCtxEventfnc* c)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        int bit = 1 << i;
        if ((c->f14_14 & bit) && (c->pc_8->b_8 & bit))
        {
            if (i == 0)
            {
                sub_800A8E38();
            }
            else
            {
                sub_800A785C(i - 1);
            }
            c->f14_14 &= ~(1 << i);
        }
    }
    c->pc_8++;
    return 1;
}

int sub_800B8E9C(EvCtxEventfnc* c)
{
    int target = c->pc_8[c->fEC_EC].b_8;
    EvInsEventfnc* p = c->start_4;
    while (p->op_0 != 3)
    {
        if (p->op_0 == 9 && target == p->b_8)
        {
            c->pc_8 = p;
            c->fEC_EC = 0;
            return 1;
        }
        p++;
    }
    return 0;
}

#if 0
// Not matched: the original copies p to $v1 and stores ret_C in the return delay slot (stores 8,4,C); no source order reproduced it
int sub_800B8F14(EvCtxEventfnc* c)
{
    EvInsEventfnc* p = (EvInsEventfnc*)c->pc_8[c->fEC_EC].c_C;
    c->fEC_EC = 0;
    c->pc_8 = p;
    c->ret_C = c->start_4 = p;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800B8F14);

int sub_800B8F44(EvCtxEventfnc* c)
{
    c->fC4_C4++;
    if (c->fC4_C4 >= c->pc_8->b_8 + 1)
    {
        c->fC4_C4 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B8F88(EvCtxEventfnc* c)
{
    if (c->f18_18 & c->pc_8->b_8)
    {
        return 0;
    }
    c->pc_8++;
    return 1;
}

extern int sub_800AD16C(int a, int b);
int sub_800B8FB8(EvCtxEventfnc* c)
{
    unsigned int v = c->pc_8->b_8;
    int hi = v >> 16;
    int lo = v & 0xFFFF;
    if (c->pc_8->a_4 == 0)
    {
        c->fCC_CC[hi] = lo;
    }
    else
    {
        sub_800AD16C(hi, lo);
    }
    c->pc_8++;
    return 1;
}

int sub_800B9020(EvCtxEventfnc* c)
{
    unsigned int a = c->pc_8->a_4;
    unsigned int b = c->pc_8->b_8;
    int slot = a >> 16;
    int lo = a & 0xFFFF;
    int mod = b >> 16;
    int idx = b & 0xFFFF;
    int r;
    if (slot == 9)
    {
        do
        {
            r = rand() % mod;
        } while (r < lo);
        c->fEC_EC = r;
        if (idx < 8)
        {
            c->fCC_CC[idx] = r;
        }
    }
    else
    {
        c->fEC_EC = c->fCC_CC[slot];
        if (++c->fCC_CC[slot] >= mod)
        {
            if (idx)
            {
                c->fCC_CC[slot] = lo;
            }
            else
            {
                c->fCC_CC[slot] = mod - 1;
            }
        }
    }
    c->pc_8++;
    return 1;
}

extern int sub_800AD154(int a);
int sub_800B9110(EvCtxEventfnc* c)
{
    unsigned int a = c->pc_8->a_4;
    unsigned int b = c->pc_8->b_8;
    int hi = a >> 16;
    int lo = a & 0xFFFF;
    int hi2 = b >> 16;
    int lo2 = b & 0xFFFF;
    int v = sub_800AD154(hi);
    c->fEC_EC = v;
    sub_800AD16C(hi, v + 1);
    if (sub_800AD154(hi) >= hi2)
    {
        if (lo2)
        {
            sub_800AD16C(hi, lo);
        }
        else
        {
            sub_800AD16C(hi, hi2 - 1);
        }
    }
    c->pc_8++;
    return 1;
}

extern void (*dword_800B1D98)(int);
int sub_800B91CC(EvCtxEventfnc* c)
{
    dword_800B1D98(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

extern int sub_800A59D0(int a);
int sub_800B9218(EvCtxEventfnc* c)
{
    sub_800A59D0(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

extern EvVecEventfnc* sub_800BBBD0(int i);
extern short dword_8008D474[2];
extern void sub_80037918(int p);
extern void SetGeomOffset(long ofx, long ofy);
int sub_800B9260(EvCtxEventfnc* c)
{
    int* q = (int*)c->pc_8->c_C;
    EvVecEventfnc* pos = sub_800BBBA0(c->pc_8->a_4);
    EvRotEventfnc* rot = (EvRotEventfnc*)sub_800BBBD0(c->pc_8->a_4);
    int ang;
    if (q)
    {
        ang = q[3];
    }
    else
    {
        q = (int*)sub_800BBC00(c, c->pc_8->a_4, 0);
        ang = sub_800BBC80(c, c->pc_8->a_4, 0)->y_4;
    }
    pos->x_0 = q[0];
    pos->y_4 = q[1];
    pos->z_8 = q[2];
    rot->ang_2 = ang;
    sub_80037918(cameraTask_8008D4A0[0x24 / 4]);
    SetGeomOffset(display_8008B4D8.field_C_w / 2 + dword_8008D474[0], display_8008B4D8.field_E_h / 2 + dword_8008D474[1]);
    c->pc_8++;
    return 1;
}

int sub_800B93A8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc* v = (EvVecEventfnc*)c->pc_8->c_C;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = c->pc_8->op_0 != 0x14;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->b_8;
    return sub_800BB840(c, &m, 1, 1);
}

extern short name_80084540[];
int sub_800B942C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc d;
    EvVecEventfnc* a = sub_800BBBA0(c->pc_8->a_4);
    EvVecEventfnc* b;
    int ang;
    if (c->pc_8->a_4 == c->pc_8->b_8)
    {
        b = sub_800BBC00(c, c->pc_8->a_4, 0);
    }
    else
    {
        b = sub_800BBBA0(c->pc_8->b_8);
    }
    d.x_0 = a->x_0 - b->x_0;
    d.z_8 = a->z_8 - b->z_8;
    ang = ratan2_8003B548(d.x_0, d.z_8);
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = c->pc_8->op_0 != 0x15;
    m.m18_18 = b->x_0 + name_80084540[ang & 0xFFF] * 200 / 4096;
    m.m1C_1C = b->y_4;
    m.m20_20 = b->z_8 + name_80084540[(ang + 0x400) & 0xFFF] * 200 / 4096;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B95BC(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvInsEventfnc* i = c->pc_8;
    EvVecEventfnc* v = (EvVecEventfnc*)i->c_C;
    int a = i->a_4;
    m.m0_0 = a;
    m.m4_4 = 2;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->b_8;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B962C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    EvVecEventfnc* v;
    int a = c->pc_8->a_4;
    int b = c->pc_8->b_8;
    v = (a == b) ? sub_800BBC80(c, b, 0) : sub_800BBBA0(b);
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 2;
    m.m18_18 = v->x_0;
    m.m1C_1C = v->y_4;
    m.m20_20 = v->z_8;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB840(c, &m, 1, 1);
}

int sub_800B96D8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 6;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B9720(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 7;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B9768(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = c->pc_8->a_4;
    m.m4_4 = 8;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 0, 1);
}

int sub_800B97B0(EvCtxEventfnc* c)
{
    sub_800BBC00(c, c->pc_8->a_4, 1);
    c->pc_8++;
    return 1;
}

int sub_800B97F8(EvCtxEventfnc* c)
{
    sub_800BBC80(c, c->pc_8->a_4, 1);
    c->pc_8++;
    return 1;
}

extern int sub_800AD0D4(int a);
int sub_800B9840(EvCtxEventfnc* c)
{
    if (c->pc_8->a_4 == 0)
    {
        if (sub_800AD0D4(c->pc_8->b_8))
        {
            c->pc_8++;
            return 1;
        }
        return 0;
    }
    c->fEC_EC = sub_800AD0D4(c->pc_8->b_8) == 0;
    c->pc_8++;
    return 1;
}

extern void sub_800AD0F8(int a);
int sub_800B98C4(EvCtxEventfnc* c)
{
    sub_800AD0F8(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern void sub_800AD124(int a);
int sub_800B990C(EvCtxEventfnc* c)
{
    sub_800AD124(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800B9954(EvCtxEventfnc* c)
{
    if (c->pc_8->a_4 == 0)
    {
        if (sub_800BBDD8(c->pc_8->b_8))
        {
            c->pc_8++;
            return 1;
        }
        return 0;
    }
    c->fEC_EC = sub_800BBDD8(c->pc_8->b_8) == 0;
    c->pc_8++;
    return 1;
}

int sub_800B99D8(EvCtxEventfnc* c)
{
    sub_800BBDA0(c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

int sub_800B9A20(EvCtxEventfnc* c)
{
    sub_800BBDA0(c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

extern int sub_800AD184(int a, int b, int c);
extern int sub_800AD1E0(int a, int b, int c);
int sub_800B9A68(EvCtxEventfnc* c)
{
    sub_800AD184(c->pc_8->a_4, c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

int sub_800B9AB4(EvCtxEventfnc* c)
{
    sub_800AD1E0(c->pc_8->a_4, c->pc_8->b_8, 0);
    c->pc_8++;
    return 1;
}

int sub_800B9B00(EvCtxEventfnc* c)
{
    sub_800AD184(c->pc_8->a_4, c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

int sub_800B9B4C(EvCtxEventfnc* c)
{
    sub_800AD1E0(c->pc_8->a_4, c->pc_8->b_8, 1);
    c->pc_8++;
    return 1;
}

extern int sub_800AD73C(int a);
#if 0
// Not matched: the original places a shared 'return 0' block in front of the body and tests the condition differently
int sub_800B9B98(EvCtxEventfnc* c)
{
    unsigned int f;
    if (c->pc_8->a_4 == 0)
    {
        if (dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
        {
            f = c->flags_0 | 8;
            c->flags_0 = f;
            c->fC8_C8 = c->pc_8->b_8;
            if (!(f & 4))
            {
                return 0;
            }
            c->flags_0 = f & ~0xC;
            c->fC8_C8 = -1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        c->fEC_EC = sub_800AD73C(c->pc_8->b_8) == 0;
    }
    c->pc_8++;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800B9B98);

extern int sub_800AD68C(int a);
extern int sub_800AD6E4(int a);
int sub_800B9C5C(EvCtxEventfnc* c)
{
    int a = c->pc_8->a_4;
    int b = c->pc_8->b_8;
    if (a != 0)
    {
        sub_800AD68C(b);
    }
    else
    {
        sub_800AD6E4(b);
    }
    c->pc_8++;
    return 1;
}

extern int sub_800AD058(int a);
int sub_800B9CC0(EvCtxEventfnc* c)
{
    sub_800AD058(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern int sub_800AD8F4(int a);
int sub_800B9D08(EvCtxEventfnc* c)
{
    sub_800AD8F4(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern char* sub_800A8C34();
extern void Heal_80011CD0();
extern void FillHpMp_80011C0C();
int sub_800B9D50(EvCtxEventfnc* c)
{
    int i;
    char* p;
    Heal_80011CD0(sub_800A8C34());
    for (i = 0; i < CountMinions_80010548(3); i++)
    {
        p = GetMinionStatus_800107A0(3, i);
        Heal_80011CD0(p);
        FillHpMp_80011C0C(p, p);
    }
    c->pc_8 += 1;
    return 1;
}

extern EvEntEventfnc* sub_800A5DDC(int a, int b, int c);
int sub_800B9DE0(EvCtxEventfnc* c)
{
    EvEntEventfnc* e = sub_800A5DDC(c->pc_8->c_C, c->pc_8->a_4, 0);
    if (e == 0)
    {
        return 0;
    }
    e->f7C_7C = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9E48(EvCtxEventfnc* c)
{
    EvEntEventfnc* e = sub_800A5DDC(c->pc_8->c_C, c->pc_8->a_4, 0);
    if (e != 0 && e->f80_80 == c->pc_8->b_8)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9EB0(EvCtxEventfnc* c)
{
    c->ent_120->f7C_7C = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9EDC(EvCtxEventfnc* c)
{
    if (c->ent_120->f80_80 == c->pc_8->b_8)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9F0C(EvCtxEventfnc* c)
{
    if (sub_800A5DDC(c->pc_8->c_C, c->pc_8->b_8, 0) == 0)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800B9F5C(EvCtxEventfnc* c)
{
    c->f108_108 |= c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9F84(EvCtxEventfnc* c)
{
    c->f100_100 = c->pc_8->a_4;
    c->f102_102 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

int sub_800B9FB4(EvCtxEventfnc* c)
{
    c->f104_104 = c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

extern void sub_800A6830(int a);
int sub_800B9FD8(EvCtxEventfnc* c)
{
    sub_800A6830(c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

extern void sub_800BC7A0(EvCtxEventfnc* c);
extern int sub_800BBE3C(EvCtxEventfnc* c);
extern int sub_800BC2B4(EvCtxEventfnc* c);
extern int XaRequestStop_80043524(void);
int sub_800BA020(EvCtxEventfnc* c)
{
    EvInsEventfnc* pc = c->pc_8;
    switch (c->fB4_B4)
    {
    case 0:
        if (pc->op_0 == 0x3F)
        {
            c->fB4_B4 = 3;
            c->flags_0 &= ~0x40;
            return 1;
        }
        c->fB4_B4++;
    case 1:
        sub_800BC7A0(c);
        if (!sub_800BBE3C(c))
        {
            break;
        }
        c->f110_110 = (int*)c->pc_8;
        c->fB4_B4++;
    case 2:
        if (pc->op_0 == 0x38 || pc->op_0 == 0x3A)
        {
            c->fB4_B4 = 0;
            c->flags_0 |= 0x40;
            c->pc_8++;
            return 1;
        }
        c->fB4_B4++;
    case 3:
        if (!sub_800BC2B4(c))
        {
            break;
        }
        c->fB4_B4++;
    case 4:
        if (c->flags_0 & 0x100)
        {
            if (!XaRequestStop_80043524())
            {
                break;
            }
            c->flags_0 &= ~0x100;
        }
    case 5:
        if (c->f118_118)
        {
            c->fB4_B4 = 2;
            c->pc_8++;
            return 1;
        }
        if ((*(int*)c->f11C_11C & 0x8001) == 1)
        {
            break;
        }
        c->f11C_11C = 0;
        c->fB4_B4 = 0;
        c->pc_8++;
        return 1;
    }
    c->pc_8 = pc;
    return 0;
}
INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6D4C);

int sub_800BA1DC(EvCtxEventfnc* c)
{
    int* p = c->f110_110;
    if (p != 0)
    {
        EvInsEventfnc* i = c->pc_8;
        unsigned int a = i->a_4;
        unsigned int b = i->b_8;
        if (b >= a)
        {
            p[3] = i->c_C;
        }
        else
        {
            i->b_8 = b + 1;
        }
    }
    c->pc_8++;
    return 1;
}

extern int sub_80034ADC(int a, int b);
int sub_800BA238(EvCtxEventfnc* c)
{
    if (sub_80034ADC(c->f11C_11C, c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BA28C(EvCtxEventfnc* c)
{
    EvInsEventfnc* i = c->pc_8;
    if (i->a_4 == 1)
    {
        c->f114_114 |= i->b_8;
    }
    else
    {
        c->f114_114 &= ~i->b_8;
    }
    c->pc_8++;
    return 1;
}

int sub_800BA2E8(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 3;
    m.mC_C = c->pc_8->b_8;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA338(EvCtxEventfnc* c)
{
    EvInsEventfnc* ins = c->pc_8;
    EvMsgEventfnc m;
    switch (c->fB8_B8)
    {
    case 0:
        m.m0_0 = ins->b_8;
        m.m4_4 = 4;
        m.mC_C = c->f24_24[c->pc_8->a_4];
        if (sub_800BB990(c, &m, 1, 0))
        {
            c->fB8_B8++;
        }
    case 1:
        if ((c->f18_18 & c->pc_8->b_8) == 0)
        {
            c->fB8_B8 = 0;
            c->pc_8++;
            return 1;
        }
        c->pc_8 = ins;
        return 0;
    default:
        c->pc_8 = ins;
        return 0;
    }
}

int sub_800BA40C(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 5;
    m.m24_24 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

extern EvObjEventfnc* sub_800A7A60(int a);
int sub_800BA45C(EvCtxEventfnc* c)
{
    int ok = 0;
    int a = c->pc_8->a_4;
    if (a != 0)
    {
        EvObjEventfnc* o = sub_800A7A60(a - 1);
        if (o->f90_90 == o->f1A_1A)
        {
            sub_8001D6EC((struct_obj_A*)o, c->pc_8->b_8);
            ok = 1;
        }
    }
    if (ok)
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

int sub_800BA4F0(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 9;
    m.mC_C = c->pc_8->b_8;
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA554(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    m.m0_0 = 1 << c->pc_8->a_4;
    m.m4_4 = 0xA;
    m.mC_C = ((unsigned short*)&c->pc_8->b_8)[1];
    m.m10_10 = ((unsigned short*)&c->pc_8->b_8)[0];
    m.m14_14 = c->pc_8->c_C;
    return sub_800BB990(c, &m, 1, 1);
}

extern int* sub_800A55B0(int a);
int sub_800BA5CC(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    int n = c->pc_8->c_C;
    int* r = sub_800A55B0(4);
    unsigned int a = c->pc_8->a_4;
    m.m0_0 = 1 << (a >> 16);
    m.m4_4 = 0xB;
    m.mC_C = ((unsigned short*)&c->pc_8->b_8)[1];
    m.m10_10 = ((unsigned short*)&c->pc_8->b_8)[0];
    m.m24_24 = r[1] + n * 12;
    m.m14_14 = a & 0xFFFF;
    return sub_800BB990(c, &m, 1, 1);
}

int sub_800BA678(EvCtxEventfnc* c)
{
    c->fF0_F0 = c->pc_8->c_C;
    if (c->fF0_F0 == 0)
    {
        c->fF0_F0 = sub_800BBDF4(c);
    }
    c->pc_8++;
    return 1;
}

int sub_800BA6D0(EvCtxEventfnc* c)
{
    c->fF4_F4 = c->pc_8->a_4;
    c->fF8_F8 = c->pc_8->b_8;
    c->fFC_FC = c->pc_8->c_C;
    c->fF0_F0 = (int)&c->fF4_F4;
    c->pc_8++;
    return 1;
}

int sub_800BA714(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == 1 || dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
    {
        if (((int (*)(int))c->pc_8->c_C)(c->fF0_F0) == 1)
        {
            c->fF0_F0 = 0;
            c->pc_8++;
            return 1;
        }
    }
    return 0;
}

int sub_800BA7A4(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == 1 || dword_800AEBD8 < 0 || dword_800AEBD8 == c->f10_10)
    {
        c->fEC_EC = ((int (*)(int))c->pc_8->c_C)(c->fF0_F0);
        c->fF0_F0 = 0;
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int dword_80091C94;
extern int eventDispatchHalt_8008B540;

extern int sub_800A6D30(int a);
#if 0
// Not matched: the tail is scheduled differently (the constant 1 lands in $v0 and the halt store sinks below the pc store; original: $v1, halt store first)
int sub_800BA82C(EvCtxEventfnc* c)
{
    EvSaveEventfnc* s = (EvSaveEventfnc*)&saveData_8008B570;
    s->f2DC_2DC = *(unsigned short*)&c->pc_8->b_8;
    sub_800A6D30(0);
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BA82C);

int sub_800BA880(EvCtxEventfnc* c)
{
    EvSaveEventfnc* s = (EvSaveEventfnc*)&saveData_8008B570;
    s->f2E0_2E0 = *(unsigned short*)&c->pc_8->b_8;
    c->pc_8++;
    return 1;
}

extern void sub_800ADC5C(unsigned short* v, int a);
int sub_800BA8AC(EvCtxEventfnc* c)
{
    unsigned short v[3];
    v[0] = ((unsigned short*)&c->pc_8->a_4)[0];
    v[1] = ((unsigned short*)&c->pc_8->b_8)[1];
    v[2] = ((unsigned short*)&c->pc_8->b_8)[0];
    sub_800ADC5C(v, c->pc_8->c_C);
    c->pc_8++;
    return 1;
}

int sub_800BA930(EvCtxEventfnc* c)
{
    EvSaveEventfnc* s = (EvSaveEventfnc*)&saveData_8008B570;
    int* p;
    s->f2E4_2E4 = ((unsigned short*)&c->pc_8->a_4)[0];
    s->f2E8_2E8 = ((unsigned short*)&c->pc_8->b_8)[1];
    s->f2EC_2EC = ((unsigned short*)&c->pc_8->b_8)[0];
    s->f2EE_2EE = -1;
    p = (int*)c->pc_8->c_C;
    if (p)
    {
        s->f7A8_7A8 = p[0];
        s->f7AC_7AC = p[1];
        s->f7B0_7B0 = p[2];
        s->f7B6_7B6 = p[3];
    }
    else
    {
        dword_80091C94 = 1;
    }
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 1;
}

extern void sub_800ADCEC(unsigned short* v, int a);
extern int dword_80091C9C;
extern int dword_80091C54;
int sub_800BA9E4(EvCtxEventfnc* c)
{
    unsigned short v[3];
    EvSaveEventfnc* s;
    sub_800ADCEC(v, c->pc_8->b_8);
    dword_80091C9C = 1;
    dword_80091C54 = 0;
    dword_80091C94 = 1;
    s = (EvSaveEventfnc*)&saveData_8008B570;
    s->f2E4_2E4 = v[0];
    s->f2E8_2E8 = v[1];
    s->f2EC_2EC = v[2];
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 0;
}

int sub_800BAA6C(EvCtxEventfnc* c)
{
    if (((int (*)(int))sub_80027330)(c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int sub_80027358(int a);
int sub_800BAAC0(EvCtxEventfnc* c)
{
    if (sub_80027358(c->pc_8->b_8))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int sub_800A683C(int a);
int sub_800BAB14(EvCtxEventfnc* c)
{
    sub_800A683C(c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

#if 0
extern int SetFadeMode_8001C19C(int a, int b);
int sub_800BAB5C(EvCtxEventfnc* c)
{
    SetFadeMode_8001C19C(1, 0x20);
    sub_800A6D30(8);
    eventDispatchHalt_8008B540 = 1;
    c->pc_8++;
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BAB5C);

typedef struct EvWaitEventfnc
{
    int f0_0;
    int f4_4;
    int f8_8;
} EvWaitEventfnc;
extern EvWaitEventfnc dword_800B06B0;
extern int sub_800A5F9C(int a);
int sub_800BABB0(EvCtxEventfnc* c)
{
    switch (c->fB8_B8)
    {
    case 0:
        dword_800B06B0.f0_0 = 1;
        dword_800B06B0.f4_4 = ((unsigned short*)&c->pc_8->b_8)[1];
        dword_800B06B0.f8_8 = ((unsigned short*)&c->pc_8->b_8)[0];
        c->fB8_B8 = 1;
        return 0;
    case 1:
        if (dword_800B06B0.f0_0 == 0)
        {
            c->fEC_EC = sub_800A5F9C(0);
            c->fB8_B8 = 0;
            c->pc_8++;
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

extern void sub_800379DC(EvVecEventfnc* v, int b);
int sub_800BAC60(EvCtxEventfnc* c)
{
    EvVecEventfnc v;
    EvVecEventfnc* src = (EvVecEventfnc*)c->pc_8->c_C;
    v.x_0 = src->x_0;
    v.y_4 = src->y_4 + 0x15E;
    v.z_8 = src->z_8;
    sub_800379DC(&v, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BACE0(EvCtxEventfnc* c)
{
    sub_800379DC(sub_800BBBA0(c->pc_8->a_4), c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

extern void sub_80037A20(int a, int b);
int sub_800BAD3C(EvCtxEventfnc* c)
{
    sub_80037A20(c->pc_8->c_C, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BAD88(EvCtxEventfnc* c)
{
    int v = ((int (*)())sub_80037A4C)();
    int b = c->pc_8->b_8;
    if ((b == 1 && (short)v == 0x1000) || (b == 0 && (short)v == 0))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

typedef struct EvRectEventfnc
{
    short x_0;
    short y_2;
    short w_4;
    short h_6;
} EvRectEventfnc;
extern EvRectEventfnc dword_8008D420;
int sub_800BADF8(EvCtxEventfnc* c)
{
    if (c->pc_8->c_C)
    {
        dword_8008D420 = *(EvRectEventfnc*)c->pc_8->c_C;
    }
    else
    {
        switch (c->pc_8->b_8)
        {
        case 0:
            dword_8008D420.x_0 = 0;
            dword_8008D420.y_2 = 0;
            dword_8008D420.w_4 = 0x140;
            dword_8008D420.h_6 = 0xF0;
            break;
        case 1:
            dword_8008D420.x_0 = 0;
            dword_8008D420.y_2 = 0x20;
            dword_8008D420.w_4 = 0x140;
            dword_8008D420.h_6 = 0xA0;
            break;
        }
    }
    c->pc_8++;
    return 1;
}

extern void sub_80037A6C(int a, int b);
int sub_800BAEBC(EvCtxEventfnc* c)
{
    sub_80037A6C(c->pc_8->a_4, c->pc_8->b_8);
    c->pc_8++;
    return 1;
}

int sub_800BAF08(EvCtxEventfnc* c)
{
    int v = c->pc_8->c_C;
    if (v == 0)
    {
        v = (int)sub_800BBBA0(c->pc_8->a_4);
    }
    SetCameraTarget_80037AC8(v);
    c->pc_8++;
    return 1;
}

int sub_800BAF68(EvCtxEventfnc* c)
{
    char* s = (char*)&saveData_8008B570;
    unsigned short v = *(unsigned short*)&c->pc_8->b_8;
    *(unsigned short*)(s + 0x2F0) = v;
    if ((short)v == *(short*)(s + 0x2F2))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

extern int sub_800A7790(void);
extern int IsWithinDistance_8003B740(int* a, int* b, unsigned int* c);
int sub_800BAFAC(EvCtxEventfnc* c)
{
    EvVecEventfnc* lev;
    EvRotEventfnc* rot;
    EvVecEventfnc* p;
    int i;
    int hit;
    unsigned int dist;
    if (dword_800AEBD8 >= 0 && dword_800AEBD8 != c->f10_10)
    {
        return 0;
    }
    if (c->flags_0 & 4)
    {
        c->flags_0 &= ~0xC;
        c->pc_8++;
        return 1;
    }
    c->flags_0 &= ~0xC;
    lev = sub_800BBBA0(0);
    rot = (EvRotEventfnc*)sub_800BBBD0(0);
    for (i = 1; i < sub_800A7790() + 1; i++)
    {
        int bit = 1 << i;
        if (c->pc_8->b_8 & bit)
        {
            p = sub_800BBBA0(i);
            hit = 0;
            if (c->pc_8->a_4 >= 0)
            {
                hit = sub_800B76B8(&((EvMapEventfnc*)dword_8008B500)->meshes20_20[c->pc_8->a_4], lev) >= 0;
            }
            else
            {
                dist = 0xFFF;
                IsWithinDistance_8003B740((int*)lev, (int*)p, &dist);
                if (dist <= 0x15F8F)
                {
                    hit = 1;
                }
            }
            if (hit)
            {
                if ((unsigned int)(WrapAngle_8003BA18((short)(rot->ang_2 - ratan2Difference_8003B9E0((int*)lev, (int*)p))) + 0x198) < 0x331)
                {
                    c->flags_0 |= 8;
                    break;
                }
            }
        }
    }
    return 0;
}

int sub_800BB180(EvCtxEventfnc* c)
{
    EvMsgEventfnc m;
    int r;
    int v = c->pc_8->b_8 & 0x80000000;
    c->f24_24[c->pc_8->a_4] = v;
    if ((c->pc_8->b_8 & 0x80000000) == 0)
    {
        c->pc_8++;
        r = 1;
    }
    else
    {
        m.m0_0 = 1 << c->pc_8->a_4;
        m.m4_4 = 3;
        m.mC_C = v;
        r = sub_800BB990(c, &m, 1, 1);
    }
    return r;
}

extern int sub_800A6504(int a, EvVecEventfnc* v);
int sub_800BB214(EvCtxEventfnc* c)
{
    EvVecEventfnc* v = sub_800BBBA0(c->pc_8->a_4);
    if (sub_800A6504(c->pc_8->b_8, v))
    {
        c->pc_8++;
        return 1;
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB27C);

extern int dword_800B1230;
int sub_800BB45C(EvCtxEventfnc* c)
{
    if (c->pc_8->b_8 == dword_800B1230)
    {
        c->fEC_EC = 0;
    }
    else
    {
        c->fEC_EC = 1;
    }
    c->pc_8++;
    return 1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB4A4);

extern void StartPadVibration_80036528(int a, int b);
extern void StopPadVibration_80036658(int a);
int sub_800BB7D8(EvCtxEventfnc* c)
{
    EvInsEventfnc* i = c->pc_8;
    if (i->a_4 == 1)
    {
        StartPadVibration_80036528(0, *(unsigned char*)&i->b_8);
    }
    else
    {
        StopPadVibration_80036658(0);
    }
    c->pc_8++;
    return 1;
}

extern int sub_800BBAB0(int i);
extern int sub_800BBAE4(int i);
extern int sub_800BBB18(int* p);
extern int sub_800BBB5C(int* p);
#if 0
// Not matched: the original keeps fC0 in $s0 for the whole loop (default case spins on the stale value); register allocation differs
int sub_800BB840(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b)
{
    while (1)
    {
        switch (c->fC0_C0)
        {
        case 0:
            m->m8_8 = a;
            if (c->f18_18 & (1 << m->m0_0))
            {
                return 0;
            }
            if (!sub_800BBAB0(m->m0_0))
            {
                return 0;
            }
            sub_800BBB18((int*)m);
            if (a)
            {
                c->f18_18 |= 1 << m->m0_0;
            }
            c->fC0_C0 = 1;
            break;
        case 1:
            if (!sub_800BBAE4(m->m0_0))
            {
                return 0;
            }
            sub_800BBB5C((int*)m);
            if (b)
            {
                c->pc_8++;
            }
            if (m->m4_4 == 3)
            {
                c->f1C_1C |= c->fC0_C0 << m->m0_0;
            }
            else if (m->m4_4 == 4)
            {
                c->f1C_1C &= ~(c->fC0_C0 << m->m0_0);
            }
            c->fC0_C0 = 0;
            return 1;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BB840);

int sub_800BB990(EvCtxEventfnc* c, EvMsgEventfnc* m, int a, int b)
{
    int i;
    int bit;
    switch (c->fBC_BC)
    {
    case 0:
        c->f24_24[5] = m->m0_0;
        c->fBC_BC++;
    case 1:
        for (i = 0; i < 5; i++)
        {
            bit = 1 << i;
            if (c->f24_24[5] & bit)
            {
                m->m0_0 = i;
                if (!sub_800BB840(c, m, a, 0))
                {
                    break;
                }
                c->f24_24[5] &= ~bit;
            }
        }
        if (c->f24_24[5] == 0)
        {
            if (b)
            {
                c->pc_8++;
            }
            c->fBC_BC = 0;
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

extern int sub_800A8E7C();
extern int sub_800A7CB8(int a);
int sub_800BBAB0(int i)
{
    int r;
    if (i == 0)
    {
        r = sub_800A8E7C();
    }
    else
    {
        r = sub_800A7CB8(i - 1);
    }
    return r;
}

extern int sub_800A8FE0();
extern int sub_800A7CFC(int a);
int sub_800BBAE4(int i)
{
    int r;
    if (i == 0)
    {
        r = sub_800A8FE0();
    }
    else
    {
        r = sub_800A7CFC(i - 1);
    }
    return r;
}

#if 0
// Not matched: p is copied to $a1 in the original, $v0 here (if/else, ternary, early return all tried)
extern int sub_800A8EC4(int* p);
extern int sub_800A7D40(int a);
int sub_800BBB18(int* p)
{
    int r;
    int v = *p;
    if (v == 0)
    {
        r = sub_800A8EC4(p);
    }
    else
    {
        r = sub_800A7D40(v - 1);
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBB18);

#if 0
// Not matched: same $a1/$v0 copy register as sub_800BBB18
extern int sub_800A9008(int* p);
extern int sub_800A80C4(int a);
int sub_800BBB5C(int* p)
{
    int r;
    int v = *p;
    if (v == 0)
    {
        r = sub_800A9008(p);
    }
    else
    {
        r = sub_800A80C4(v - 1);
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBB5C);

extern EvVecEventfnc* sub_800A7940(int a);
EvVecEventfnc* sub_800BBBA0(int i)
{
    EvVecEventfnc* r;
    if (i == 0)
    {
        r = &levantPos_8008BD18;
    }
    else
    {
        r = sub_800A7940(i - 1);
    }
    return r;
}

extern EvVecEventfnc levantRot_8008BD24;
extern EvVecEventfnc* sub_800A7984(int a);
EvVecEventfnc* sub_800BBBD0(int i)
{
    EvVecEventfnc* r;
    if (i == 0)
    {
        r = &levantRot_8008BD24;
    }
    else
    {
        r = sub_800A7984(i - 1);
    }
    return r;
}

EvVecEventfnc* sub_800BBC00(EvCtxEventfnc* c, int idx, int mode)
{
    if (mode == 1)
    {
        EvVecEventfnc* v = sub_800BBBA0(idx);
        c->vec3C_3C[idx].x_0 = v->x_0;
        c->vec3C_3C[idx].y_4 = v->y_4;
        c->vec3C_3C[idx].z_8 = v->z_8;
    }
    return &c->vec3C_3C[idx];
}

EvVecEventfnc* sub_800BBC80(EvCtxEventfnc* c, int idx, int mode)
{
    if (mode == 1)
    {
        EvVecEventfnc* v = sub_800BBBA0(idx);
        EvRotEventfnc* r = (EvRotEventfnc*)sub_800BBBD0(idx);
        c->vec78_78[idx].x_0 = v->x_0 + name_80084540[r->ang_2 & 0xFFF] * 100 / 4096;
        c->vec78_78[idx].y_4 = r->ang_2;
        c->vec78_78[idx].z_8 = v->z_8 + name_80084540[(r->ang_2 + 0x400) & 0xFFF] * 100 / 4096;
    }
    return &c->vec78_78[idx];
}

extern int dword_800AEBD4;
void sub_800BBDA0(int a, int b)
{
    if (b == 1)
    {
        dword_800AEBD4 |= a;
    }
    else
    {
        dword_800AEBD4 &= ~a;
    }
}

int sub_800BBDD8(int a)
{
    return (~dword_800AEBD4 & a) == 0;
}

int sub_800BBDF4(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f8C_8C;
    }
    return 0;
}

int sub_800BBE18(EvCtxEventfnc* c)
{
    if (c->ent_120 != 0)
    {
        return c->ent_120->f84_84;
    }
    return -1;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BBE3C);

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC2B4);

int* sub_800BC560(int* p)
{
    int n = 0;
    do
    {
        n++;
        if (*p != 0)
        {
            n = 0;
        }
        p++;
    } while (n != 2);
    return p;
}

int sub_800BC58C(int* p)
{
    int m = 0;
    int i;
    for (i = 0; *p != 0; p++, i++)
    {
        m |= 1 << i;
    }
    return m;
}

extern unsigned short word_8008D600[];
extern void sub_8005BBC8();
int sub_800BC5C8(int a, int b)
{
    unsigned short v[3];
    short r1[4];
    short r2[4];
    short tmp[4];
    unsigned short* p = (unsigned short*)sub_800BBBA0(a);
    unsigned short* q;
    v[0] = p[0];
    v[1] = p[2];
    v[2] = p[4];
    v[0] -= word_8008D600[0];
    v[1] -= word_8008D600[2];
    v[2] -= word_8008D600[4];
    sub_8005BBC8(v, r1, tmp, tmp);
    q = (unsigned short*)sub_800BBBA0(b);
    v[0] = q[0];
    v[1] = q[2];
    v[2] = q[4];
    v[0] -= word_8008D600[0];
    v[1] -= word_8008D600[2];
    v[2] -= word_8008D600[4];
    sub_8005BBC8(v, r2, tmp, tmp);
    return r1[0] < r2[0];
}

typedef struct EvSrcEventfnc
{
    short a_0;
    short b_2;
    int c_4;
} EvSrcEventfnc;
typedef struct EvSlotEventfnc
{
    int f0_0;
    int f4_4;
    int f8_8;
    int fC_C;
    int f10_10;
} EvSlotEventfnc;
extern void memset(void* p, int v, int n);
#if 0
// Not matched: loop induction variables are allocated differently (the original strength-reduces only the slot offset)
void sub_800BC6C4(char* base, EvSrcEventfnc* src, int n)
{
    int local[8];
    int i;
    int off = 0xC;
    EvSlotEventfnc* p;
    memset(local, 0, 0x20);
    local[0] = 2;
    local[5] = 3;
    for (i = 0; i < 3; i++, off += 0x14)
    {
        p = (EvSlotEventfnc*)(base + off);
        if (i < n)
        {
            p->f0_0 = src->a_0;
            p->f4_4 = src->b_2;
            p->f8_8 = src->c_4;
        }
        else
        {
            p->f0_0 = -1;
            p->f4_4 = 0;
            p->f8_8 = 0;
        }
        if (p->f0_0 >= 0)
        {
            p->fC_C = local[p->f0_0];
            p->f10_10 = p->f4_4;
        }
        src++;
    }
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC6C4);

void sub_800BC7A0(EvCtxEventfnc* c)
{
}

typedef struct EvGfxEventfnc
{
    int f0_0;
    int f4_4;
    char pad_8[0x24];
    int f2C_2C;
} EvGfxEventfnc;
typedef struct EvGfxArgEventfnc
{
    EvGfxEventfnc* g_0;
    short s_4[6];
    int f10_10;
} EvGfxArgEventfnc;
extern int dword_800AEB7C;
extern EvGfxEventfnc dword_800AEB80;
extern void sub_800A5854(void);
extern void sub_800A5804(int a);
extern void OnEffectFileLoaded_80020F5C(EvGfxArgEventfnc* p, int a);
void sub_800BC7A8(int a)
{
    EvGfxArgEventfnc t;
    if (dword_800AEB7C != 2)
    {
        sub_800A5854();
    }
    if (dword_800AEB80.f4_4)
    {
        ListFreeAll_8003FEC8(&dword_800AEB80.f4_4);
    }
    t.g_0 = &dword_800AEB80;
    t.s_4[5] = 0;
    t.s_4[4] = 0;
    t.s_4[3] = 0;
    t.s_4[2] = 0;
    t.s_4[1] = 0;
    t.s_4[0] = 0;
    t.f10_10 = 0;
    ListInit_8003FDB0(&dword_800AEB80.f4_4);
    OnEffectFileLoaded_80020F5C(&t, a);
    if (dword_800AEB80.f2C_2C)
    {
        sub_800A5804(0);
    }
}


#if 0
// Not matched: src/size are allocated to $s1/$s0 (original $s0/$s1); the rest is identical. The global is wrapped in a struct so the stores through it reload it (as the original does)
typedef struct EvBlobPtrEventfnc
{
    int* p_0;
} EvBlobPtrEventfnc;
extern EvBlobPtrEventfnc dword_800AEBBC;
void sub_800BC854(int* src)
{
    int size;
    int n;
    int i;
    int j;
    int m;
    int* p;
    int* e;
    size = *src++;
    if (dword_800AEBBC.p_0)
    {
        ListFree_8003FE38(dword_80091C10, dword_800AEBBC.p_0);
        dword_800AEBBC.p_0 = 0;
    }
    dword_800AEBBC.p_0 = (int*)ListAlloc_8003FDC0(dword_80091C10, size);
    MemCopy_800403E8((unsigned int*)dword_800AEBBC.p_0, (unsigned int*)src, size);
    n = dword_800AEBBC.p_0[0];
    for (i = 0; i < n; i++)
    {
        e = (int*)((char*)dword_800AEBBC.p_0 + (i * 8 + 4));
        *e = (int)dword_800AEBBC.p_0 + *e;
    }
    for (i = 0; i < n; i++)
    {
        e = (int*)((char*)dword_800AEBBC.p_0 + (i * 8 + 4));
        m = e[1];
        p = (int*)e[0];
        for (j = 0; j < m; j++, p++)
        {
            if (*p == -1)
            {
                *p = 0;
            }
            else
            {
                *p = (int)dword_800AEBBC.p_0 + *p;
            }
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BC854);

extern int dword_800AEBC0[2];
void sub_800BC98C(int a)
{
    if (dword_800AEBC0[0])
    {
        ListFree_8003FE38(dword_80091C10, dword_800AEBC0[0]);
        dword_800AEBC0[0] = 0;
    }
    if (dword_800AEBC0[1])
    {
        ListFree_8003FE38(dword_80091C10, dword_800AEBC0[1]);
        dword_800AEBC0[1] = 0;
    }
    LoadTiy_80028E74(&dword_800AEBC0[0], 0, &dword_800AEBC0[1], a, (int)dword_80091C10);
}

#if 0
// Not matched: a/b land in $s1/$s0 in the original, swapped here (param types, temporaries, call-embedded assignment tried)
extern int dword_800AEBC8;
void sub_800BCA18(unsigned int* a, unsigned int* b)
{
    unsigned int* r = (unsigned int*)ListAlloc_8003FDC0(dword_80091C10);
    dword_800AEBC8 = (int)r;
    MemCopy_800403E8(r, a, (unsigned int)b);
}
#endif
INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCA18);

extern int dword_800AEBCC[2];
extern void sub_80026DE8(int* a, int b, void* c);
extern void sub_80026D78(int* a, int b, void* c);
extern void sub_80026E74(int a, int b, void* c);
void sub_800BCA68(int a)
{
    if (dword_800AEBCC[1] != 0)
    {
        sub_80026DE8(&dword_800AEBCC[1], dword_800AEBCC[0], dword_80091C10);
        dword_800AEBCC[0] = 0;
    }
    dword_800AEBCC[0] = sub_80026D6C((int*)a);
    sub_80026D78(&dword_800AEBCC[1], dword_800AEBCC[0], dword_80091C10);
    sub_80026E74(dword_800AEBCC[1], a, dword_80091C10);
}

typedef struct TaskEventfnc
{
    unsigned int flags_0;
    int f4_4;
    void (*next_8)();
} TaskEventfnc;
extern void sub_800BCB3C();
void sub_800BCB00(TaskEventfnc* t, int* x)
{
    x[0] = 0;
    x[1] = 0x1D;
    sub_800BCB3C(t, x);
    t->next_8 = sub_800BCB3C;
}

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCB3C);

INCLUDE_OVERLAY_ASM(eventfnc, dword_800BCDBC);
