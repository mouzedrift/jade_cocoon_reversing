// TSTMODEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern unsigned short padRepeat_800918CC[];
extern unsigned short padPressed_8009194C[];

typedef struct TstModelBone
{
    short s0;
    short s2;
    short s4;
    unsigned short flags;
} TstModelBone;
typedef struct TstModelD
{
    int state;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int count_1C;
    int f20;
    int f24;
    TstModelBone bones[41];
    short s170;
    short s172;
    short s174;
    short pad_176;
    int i178;
    int i17C;
    int i180;
    int i184;
    int i188;
    int i18C;
    char pad_190[0x14];
    int f1A4;
    int f1A8;
    int f1AC;
    int f1B0;
    int f1B4;
    int f1B8;
    int f1BC;
    char pad_1C0[0x30];
    SVECTOR rot_1F0;
} TstModelD;
typedef struct TstModelB
{
    int flags;
    unsigned short s4;
    unsigned short s6;
    short s8;
    short sA;
    short sC;
    unsigned short sE;
} TstModelB;
extern TstModelBone dword_800A09B8;
extern int sub_800A1D70();

INCLUDE_OVERLAY_ASM(tstmodel, dword_800A05A0);

typedef struct TstModelTbl { int a; TstModelBone* bones; int c; } TstModelTbl;
extern TstModelTbl name_800A33B0[];
extern void TstModelTask_800A0A8C();
void TstModelInit_800A09C0(int* task, int* c)
{
    int i;
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[4] = 0;
    c[5] = 0;
    c[8] = 0;
    ((short*)c)[0x172 / 2] = 0;
    c[7] = 0;
    if (name_800A33B0[0].a >= 0)
    {
        do
        {
            i = c[7] + 1;
            c[7] = i;
        } while (name_800A33B0[i].a >= 0);
    }
    c[0x1B8 / 4] = 0;
    c[0x1A8 / 4] = 0;
    c[0x1B4 / 4] = 0;
    c[0x1A4 / 4] = 0;
    c[0x1BC / 4] = 0;
    sub_800A0BC0(c);
    drawEnvRed_8008D448[0] = 0x40;
    drawEnvRed_8008D448[1] = 0x40;
    drawEnvRed_8008D448[2] = 0x80;
    task[2] = (int)TstModelTask_800A0A8C;
}

extern void sub_800A0C00();
extern void sub_800A0EC8();
extern void sub_800A0F20();
extern void TstModelCameraInput_800A104C();
extern void sub_800A1428();
extern void sub_800A17B8();
extern void sub_800A1614();
extern void sub_800A18F4();
extern void sub_800A19E4();
void TstModelTask_800A0A8C(int* task, int* c)
{
    switch (c[0])
    {
    case 0:
        sub_800A0C00(c);
        break;
    case 1:
        sub_800A0EC8(c);
        break;
    case 2:
        sub_800A0F20(c);
        break;
    case 3:
        TstModelCameraInput_800A104C(c);
        sub_800A1428(c);
        sub_800A18F4(c);
        break;
    case 4:
        sub_800A1428(c);
        sub_800A17B8(c);
        break;
    case 5:
        sub_800A1428(c);
        sub_800A1614(c);
        break;
    case 6:
        sub_800A19E4(c);
        break;
    }
    if ((unsigned)(c[0] - 1) >= 2 && c[0] != 6 && (padHeld_800918D0[0] & 4) && (padHeld_800918D0[0] & 1) &&
        (padHeld_800918D0[0] & 0x90A) == 0x90A)
    {
        sub_800A19E4(c);
        bStopDrawingMovie_8008D45C = 1;
    }
}
INCLUDE_OVERLAY_ASM(tstmodel, dword_800A09B8);

typedef struct TstModelA
{
    char pad_0[0x170];
    short s170;
    short s172;
    short s174;
    char pad_176[6];
    int i17C;
    char pad_180[8];
    int i188;
    char pad_18C[4];
    int i190;
    int i194;
    int i198;
    short s19C;
    short s19E;
    short s1A0;
    char pad_1A2[0x4E];
    short s1F0;
    short s1F2;
    short s1F4;
} TstModelA;

// Matched
void sub_800A0BC0(TstModelA* a)
{
    a->s174 = 0x4B0;
    a->s170 = 0;
    a->i190 = 0;
    a->i194 = 0;
    a->i198 = 0;
    a->s19C = 0;
    a->s19E = 0;
    a->s1A0 = 0;
    a->s1F0 = 0;
    a->s1F2 = 0;
    a->s1F4 = 0;
    a->i188 = -0xFA;
    a->i17C = -0xFA;
}

void sub_800A0C00(TstModelD* c)
{
    TstModelB cur;
    TstModelBone tmp;
    int i;
    TstModelTbl* tbl;
    cur.s8 = 1;
    cur.flags = 0;
    cur.s4 = 0;
    cur.sA = 0x12;
    cur.s6 = c->f4;
    cur.sC = c->count_1C;
    cur.sE = c->f8;
    sub_800A1D70(&cur);
    if (c->f4 != (short)cur.s6 || c->f8 != (short)cur.sE)
    {
        PlaySfx_80031494(0x7F);
    }
    c->f4 = (short)cur.s6;
    c->f8 = (short)cur.sE;
    for (i = 0; i < 0x12; i++)
    {
        if (c->f4 == i)
        {
            tmp = dword_800A09B8;
        }
    }
    if (padRepeat_800918CC[0] & 0x2000)
    {
        c->f20++;
    }
    else if (padRepeat_800918CC[0] & 0x8000)
    {
        c->f20--;
    }
    c->f20 = c->f20 < 0 ? 0 : c->f20 < 0xC0 ? c->f20 : 0xBF;
    tbl = name_800A33B0;
    if (padPressed_8009194C[0] & 0x20)
    {
        c->f1B8 = 0;
        c->f24 = tbl[c->f8 + c->f4].a;
        c->f1A8 = -1;
        c->f1AC = -1;
        c->f1BC = 0;
        c->f1B8 = 0;
        c->f1B4 = 0;
        c->state = 1;
        for (i = 0; name_800A33B0[c->f8 + c->f4].bones[i].s0 >= 0; i++)
        {
            c->bones[i] = name_800A33B0[c->f8 + c->f4].bones[i];
        }
        c->bones[i] = name_800A33B0[c->f8 + c->f4].bones[i];
    }
}

extern int off_8007DC70;
extern int InitModelList_80024ADC(int* a, int b, int c);
extern void LoadModel_80025200(int a, int b, int c, int d, int e);
void sub_800A0EC8(int* a)
{
    InitModelList_80024ADC(&a[5], off_8007DC70, 1);
    LoadModel_80025200(a[5], a[9], a[8], 2, 0);
    a[8] = 0;
    a[0] = 2;
}

extern void sub_80024FFC(struct_112* p, void* a);
extern void sub_80025974(struct_112* p, int a, int b);
extern int LoadModelAnim_80025440(struct_112* p, int a, int b);
extern char name_800A37E8[];
void sub_800A0F20(int* a)
{
    struct_112* m = AcquireModel_80024D70((struct_112_list*)a[5], a[9]);
    if (AreFileRequestsDone_80024DC4(m))
    {
        if (a[9] == 0x28 && a[0x1A8 / 4] == -1)
        {
            a[0x1A8 / 4] = 0;
            sub_80024FFC(m, name_800A37E8);
            sub_80025974(m, 5, 0);
            return;
        }
        if (a[0x1AC / 4] <= 0)
        {
            int i = 0;
            int found = 0;
            a[0x1AC / 4] = m->field_3E;
            for (; i < a[0x1AC / 4]; i++)
            {
                if (((unsigned char*)m->field_44)[i] != 0)
                {
                    a[0x1A8 / 4] = i;
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                a[0x1B0 / 4] = 0;
                LoadModelAnim_80025440(m, 0, 0);
                return;
            }
        }
        else
        {
            a[0x1A8 / 4] = a[0x1B0 / 4];
        }
        sub_80025C38(m, 1);
        a[0] = 3;
    }
}

typedef struct TstModelMat
{
    int w[8];
} TstModelMat;
extern unsigned short padHeld_800918D0[];
extern short word_80084540[];
extern MATRIX name_800A1E84;
extern TstModelMat name_800A1EA4;
extern MATRIX dword_80087114;
extern TstModelMat dword_80087134;
extern void SetCameraLookAt_800A1A24();
extern MATRIX* MulMatrix0(MATRIX* m0, MATRIX* m1, MATRIX* m2);
extern MATRIX* RotMatrixZYX_8004D5CC(SVECTOR* r, MATRIX* m);
void TstModelCameraInput_800A104C(TstModelD* c)
{
    MATRIX m;
    if (padHeld_800918D0[1] & 0x8000)
    {
        c->rot_1F0.vy -= 0x20;
    }
    else if (padHeld_800918D0[1] & 0x2000)
    {
        c->rot_1F0.vy += 0x20;
    }
    if (padHeld_800918D0[1] & 0x1000)
    {
        c->rot_1F0.vx -= 0x20;
    }
    else if (padHeld_800918D0[1] & 0x4000)
    {
        c->rot_1F0.vx += 0x20;
    }
    c->rot_1F0.vz = 0;
    PushMatrix();
    RotMatrixZYX_8004D5CC(&c->rot_1F0, &m);
    MulMatrix0(&name_800A1E84, &m, &dword_80087114);
    PopMatrix();
    dword_80087134 = name_800A1EA4;
    if (padHeld_800918D0[0] & 0x8000)
    {
        c->s170 -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x2000)
    {
        c->s170 += 0x20;
    }
    if (padHeld_800918D0[0] & 0x1000)
    {
        c->i17C -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x4000)
    {
        c->i17C += 0x20;
    }
    c->i17C = c->i17C < -500 ? -500 : c->i17C < 501 ? c->i17C : 500;
    if ((padHeld_800918D0[0] & 0xC) == 0xC)
    {
        sub_800A0BC0((TstModelA*)c);
    }
    else if (padHeld_800918D0[0] & 4)
    {
        c->s174 -= 0x20;
    }
    else if (padHeld_800918D0[0] & 8)
    {
        c->s174 += 0x20;
    }
    c->s174 = c->s174 < 100 ? 100 : c->s174 < 1201 ? c->s174 : 1200;
    c->i178 = c->s174 * word_80084540[c->s170 & 0xFFF] / 4096;
    c->i180 = c->s174 * word_80084540[(c->s170 + 0x400) & 0xFFF] / 4096;
    if (padHeld_800918D0[0] & 1)
    {
        if (padHeld_800918D0[0] & 2)
        {
            sub_800A0BC0((TstModelA*)c);
        }
        else
        {
            c->i188 -= 0x20;
        }
    }
    else if (padHeld_800918D0[0] & 2)
    {
        c->i188 += 0x20;
    }
    c->i188 = c->i188 < -500 ? -500 : c->i188 < 501 ? c->i188 : 500;
    c->i184 = 0;
    c->i18C = 0;
    SetCameraLookAt_800A1A24(c);
    if (padPressed_8009194C[0] & 0x800)
    {
        c->state = 6;
    }
    else if (padPressed_8009194C[0] & 0x20)
    {
        c->state = 4;
        c->f1B0 = c->f1A8;
    }
    else if (padHeld_800918D0[0] & 0x40)
    {
        if (++c->s172 >= 30)
        {
            c->fC = 0;
            c->f10 = 0;
            c->state = 5;
            c->s172 = 0;
        }
    }
}

extern void* memset(void* p, int c, unsigned int n);
extern void sub_8004D288(VECTOR* out, int* anim, int frame);
extern void PlayAnimFrameSfx_8001C364(char* a0, int idx, int a2);
extern void sub_80046A58(void* a, void* b, int c);
extern void sub_800459E4(void* a, void* b, void* c, int d);
extern char name_800A3268[];
extern char name_800A3804[];
extern char name_800A1EE8[];
void sub_800A1428(int* c)
{
    VECTOR pos;
    char z[8];
    VECTOR scale;
    char* m;
    int* anim;
    memset(z, 0, 8);
    m = (char*)AcquireModel_80024D70((struct_112_list*)c[5], c[9]);
    c[6] = (int)m;
    anim = (int*)(*(char**)(m + 0x54) + c[0x1A8 / 4] * 28);
    sub_8004D288(&pos, anim, (unsigned)c[0x1A4 / 4] % anim[0]);
    pos.vx /= anim[2];
    pos.vy /= anim[2];
    pos.vz /= anim[2];
    pos.vy += 0xFA;
    scale.vx = (c[0x1BC / 4] + 1) << 12;
    scale.vy = (c[0x1BC / 4] + 1) << 12;
    scale.vz = (c[0x1BC / 4] + 1) << 12;
    c[0x1D4 / 4] = (int)(*(char**)(m + 0x54) + c[0x1A8 / 4] * 28);
    c[0x1C0 / 4] = *(int*)(m + 0x50);
    c[0x1C4 / 4] = (int)&pos;
    c[0x1C8 / 4] = (int)z;
    c[0x1CC / 4] = (int)(c + 10);
    c[0x1D0 / 4] = (int)name_800A3268;
    c[0x1D8 / 4] = (unsigned)c[0x1A4 / 4] % *(unsigned*)c[0x1D4 / 4];
    c[0x1DC / 4] = 0;
    c[0x1E0 / 4] = (int)name_800A3804;
    c[0x1E4 / 4] = (int)&scale;
    c[0x1E8 / 4] = (int)pOT_8008D690;
    PlayAnimFrameSfx_8001C364(m, c[0x1A8 / 4], c[0x1D8 / 4]);
    sub_80046A58(c + 0x1C0 / 4, name_800A1EE8, 0);
    sub_800459E4(c + 10, m + 0x5C, pOT_8008D690, 0);
}

void sub_800A1614(TstModelD* c)
{
    TstModelB cur;
    TstModelBone tmp;
    int n;
    int i;
    unsigned short pad;
    for (n = 0; c->bones[n].s0 >= 0; n++)
    {
    }
    cur.s8 = 1;
    cur.flags = 0;
    cur.s4 = 0;
    cur.sA = 6;
    cur.s6 = c->fC;
    cur.sC = n;
    cur.sE = c->f10;
    sub_800A1D70(&cur);
    if (c->fC != (short)cur.s6 || c->f10 != (short)cur.sE)
    {
        PlaySfx_80031494(0x7F);
    }
    c->fC = (short)cur.s6;
    c->f10 = (short)cur.sE;
    for (i = 0; i < 6; i++)
    {
        tmp = dword_800A09B8;
    }
    pad = padPressed_8009194C[0];
    if (pad & 0x20)
    {
        if (c->bones[c->f10 + c->fC].flags & 2)
        {
            c->bones[c->f10 + c->fC].flags &= ~2;
        }
        else
        {
            c->bones[c->f10 + c->fC].flags |= 2;
        }
    }
    else if (pad & 0x10)
    {
        if (c->bones[c->f10 + c->fC].flags & 0x10)
        {
            c->bones[c->f10 + c->fC].flags &= ~0x10;
        }
        else
        {
            c->bones[c->f10 + c->fC].flags |= 0x10;
        }
    }
    else if (pad & 0x40)
    {
        c->s172 = 0;
        c->state = 3;
    }
}

extern void name_8002556C(struct_112* m, int a);
void sub_800A17B8(int* c)
{
    unsigned short pad;
    struct_112* m;
    if (padRepeat_800918CC[0] & 0x4000)
    {
        c[0x1B0 / 4]++;
    }
    else if (padRepeat_800918CC[0] & 0x1000)
    {
        if (--c[0x1B0 / 4] < 0)
        {
            c[0x1B0 / 4] = c[0x1AC / 4] - 1;
        }
    }
    c[0x1B0 / 4] = (unsigned)c[0x1B0 / 4] % c[0x1AC / 4];
    pad = padPressed_8009194C[0];
    if (pad & 0x20)
    {
        m = AcquireModel_80024D70((struct_112_list*)c[5], c[9]);
        if (c[0x1B4 / 4])
        {
            name_8002556C(m, c[0x1A8 / 4]);
            c[0x1B4 / 4] = 0;
        }
        if (((unsigned char*)m->field_44)[c[0x1B0 / 4]] == 0)
        {
            c[0x1B4 / 4] = 1;
        }
        else
        {
            c[0x1B4 / 4] = 0;
        }
        if (c[0x1B4 / 4])
        {
            LoadModelAnim_80025440(m, c[0x1B0 / 4], 0);
        }
        c[0x1B8 / 4] = 0;
        c[0x1A4 / 4] = 0;
        c[0] = 2;
    }
    else if (pad & 0x40)
    {
        ((short*)c)[0x172 / 2] = 0;
        c[0] = 3;
    }
}

typedef struct TstModelC
{
    char pad_0[0x172];
    short s172;
    char pad_174[0x30];
    int i1A4;
    char pad_1A8[0x10];
    int i1B8;
    int i1BC;
    char pad_1C0[0x14];
    unsigned int* p1D4;
} TstModelC;
void sub_800A18F4(TstModelC* c)
{
    if (c->i1B8)
    {
        if (padRepeat_800918CC[0] & 0x80)
        {
            c->i1A4++;
        }
        else if (padRepeat_800918CC[0] & 0x10)
        {
            if (--c->i1A4 < 0)
            {
                c->i1A4 = *c->p1D4 - 1;
            }
        }
        c->i1A4 = c->i1A4 % *c->p1D4;
    }
    else
    {
        c->i1A4++;
    }
    if (padPressed_8009194C[0] & 0x40)
    {
        c->s172 = 0;
        c->i1B8 = !c->i1B8;
    }
    if (padPressed_8009194C[0] & 0x100)
    {
        c->i1BC = (c->i1BC + 1) & 3;
    }
}

void sub_800A19E4(int* a)
{
    if (a[5])
    {
        FreeModelList_80024BB0(&a[5]);
    }
    a[5] = 0;
    a[0] = 0;
}

extern int name_8008D600[];
extern short name_8008D4C8[];
extern unsigned char name_8008D460[];
extern short name_8008D474[];
extern int geomScreenDistance_8008B548;
extern int name_8003B548();
extern void name_8004D0E8();
void SetCameraLookAt_800A1A24(int* c)
{
    int v[3];
    int yaw;
    name_8008D600[0] = c[0x178 / 4];
    name_8008D600[1] = c[0x17C / 4];
    name_8008D600[2] = c[0x180 / 4];
    v[0] = c[0x184 / 4] - c[0x178 / 4];
    v[1] = c[0x188 / 4] - c[0x17C / 4];
    v[2] = c[0x18C / 4] - c[0x180 / 4];
    yaw = ratan2_8003B548(v[0], v[2]);
    name_8008D4C8[1] = -yaw;
    name_8008D4C8[0] = name_8003B548(v[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(v[0], v[2])));
    name_8008D4C8[2] = 0;
    name_8008D460[0] = 0x40;
    name_8008D460[1] = 0x40;
    name_8008D460[2] = 0x40;
    name_8008D474[0] = 0;
    name_8008D474[1] = 0;
    geomScreenDistance_8008B548 = 0xA0;
    name_8004D0E8();
}

extern char name_800A1EDC[];
// Matched
int sub_800A1B24()
{
    DrawIntroMovie_8001AF64(name_800A1EDC);
    return 6;
}

int MoveGridCursor_800A1B48(short* m)
{
    int idx = 0;
    if (m[3] < 0)
    {
        m[3] = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (m[3] % m[4] == m[4] - 1)
        {
            return 1;
        }
        m[3]++;
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (m[3] % m[4] == 0)
        {
            return 2;
        }
        m[3]--;
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (m[3] < m[4])
        {
            return 3;
        }
        m[3] -= m[4];
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (m[3] > m[4] * (m[5] - 1) - 1)
        {
            return 4;
        }
        m[3] = m[3] + m[4];
    }
    return 0;
}

extern short name_800A37F4[];
extern short name_800A37FC[];
void sub_800A1CAC(TstModelB* p, int k)
{
    if (p->flags & name_800A37F4[k - 1])
    {
        if ((p->flags & 1) && (unsigned)(k - 1) < 2)
        {
            p->s6 += name_800A37FC[k - 1] * (p->s8 - 1);
        }
        else if ((p->flags & 2) && (unsigned)(k - 3) < 2)
        {
            p->s6 += name_800A37FC[k - 1] * p->s8 * (p->sA - 1);
        }
    }
}

extern int MoveGridCursor_800A1B48();
extern int name_8003D198();
extern void PlaySfx_80031494();
int sub_800A1D70(TstModelB* p)
{
    int old = (short)p->s6;
    int k = MoveGridCursor_800A1B48(p);
    unsigned short t = p->sE;
    int ts = t << 16;
    if (k == 3)
    {
        if ((ts >> 16) >= p->s8)
        {
            p->sE = t - p->s8;
            PlaySfx_80031494(0x7F);
            return 8;
        }
    }
    else if (k == 4)
    {
        if ((ts >> 16) < p->sC - p->s8 * p->sA)
        {
            p->sE = t + p->s8;
            PlaySfx_80031494(0x7F);
            return 7;
        }
    }
    sub_800A1CAC(p, k);
    p->sE = name_8003D198(p->sC - p->s8 * p->sA + 1, (short)p->sE, p->s8 * p->sA, 0);
    if (old != (short)p->s6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 9;
}

INCLUDE_OVERLAY_ASM(tstmodel, dword_800A1E84);
