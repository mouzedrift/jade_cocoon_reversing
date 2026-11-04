// TSTMODEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "tu_8001EA48.h"

extern unsigned short padRepeat_800918CC[];
extern unsigned short padPressed_8009194C[];

typedef struct TstModelBone
{
    short s0;
    short s2;
    short s4;
    unsigned short flags;
} TstModelBone;
// parameter block of sub_80046A58
typedef struct TstModelDraw
{
    FtgObject* ftg_0;
    VECTOR* pos_4;
    char* f8;
    TstModelBone* bones_C;
    char* f10;
    ModelAnim* anim_14;
    int frame_18;
    int f1C;
    char* f20;
    VECTOR* scale_24;
    unsigned long* ot_28;
} TstModelDraw;
// work area of the TSTMODEL task (TstModelInit_800A09C0)
typedef struct TstModelD
{
    int state;
    int f4;
    int f8;
    int fC;
    int f10;
    ModelList* models_14;
    Model* model_18;
    int count_1C;
    int f20;
    int modelId_24;
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
    int i190;
    int i194;
    int i198;
    short s19C;
    short s19E;
    short s1A0;
    short pad_1A2;
    int f1A4;
    int f1A8;
    int f1AC;
    int f1B0;
    int f1B4;
    int f1B8;
    int f1BC;
    TstModelDraw draw_1C0;
    int pad_1EC;
    SVECTOR rot_1F0;
} TstModelD;
typedef struct TstModelB
{
    int flags;
    unsigned short s4;
    short s6;
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
void TstModelInit_800A09C0(EventEntry* task, TstModelD* c)
{
    int i;
    c->state = 0;
    c->f4 = 0;
    c->f8 = 0;
    c->fC = 0;
    c->f10 = 0;
    c->models_14 = 0;
    c->f20 = 0;
    c->s172 = 0;
    c->count_1C = 0;
    if (name_800A33B0[0].a >= 0)
    {
        do
        {
            i = c->count_1C + 1;
            c->count_1C = i;
        } while (name_800A33B0[i].a >= 0);
    }
    c->f1B8 = 0;
    c->f1A8 = 0;
    c->f1B4 = 0;
    c->f1A4 = 0;
    c->f1BC = 0;
    sub_800A0BC0(c);
    drawEnvRed_8008D448[0] = 0x40;
    drawEnvRed_8008D448[1] = 0x40;
    drawEnvRed_8008D448[2] = 0x80;
    task->cb_8 = (EventEntryFn)TstModelTask_800A0A8C;
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
void TstModelTask_800A0A8C(EventEntry* task, TstModelD* c)
{
    switch (c->state)
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
    if ((unsigned)(c->state - 1) >= 2 && c->state != 6 && (padHeld_800918D0[0] & 4) && (padHeld_800918D0[0] & 1) &&
        (padHeld_800918D0[0] & 0x90A) == 0x90A)
    {
        sub_800A19E4(c);
        bStopDrawingMovie_8008D45C = 1;
    }
}
INCLUDE_OVERLAY_ASM(tstmodel, dword_800A09B8);

// Matched
void sub_800A0BC0(TstModelD* a)
{
    a->s174 = 0x4B0;
    a->s170 = 0;
    a->i190 = 0;
    a->i194 = 0;
    a->i198 = 0;
    a->s19C = 0;
    a->s19E = 0;
    a->s1A0 = 0;
    a->rot_1F0.vx = 0;
    a->rot_1F0.vy = 0;
    a->rot_1F0.vz = 0;
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
    if (c->f4 != cur.s6 || c->f8 != (short)cur.sE)
    {
        PlaySfx_80031494(0x7F);
    }
    c->f4 = cur.s6;
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
        c->modelId_24 = tbl[c->f8 + c->f4].a;
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

void sub_800A0EC8(TstModelD* a)
{
    InitModelList_80024ADC(&a->models_14, off_8007DC70, 1);
    LoadModel_80025200(a->models_14, a->modelId_24, a->f20, 2, 0);
    a->f20 = 0;
    a->state = 2;
}

extern int name_800A37E8[];
void sub_800A0F20(TstModelD* a)
{
    Model* m = AcquireModel_80024D70(a->models_14, a->modelId_24);
    if (AreFileRequestsDone_80024DC4(m))
    {
        if (a->modelId_24 == 0x28 && a->f1A8 == -1)
        {
            a->f1A8 = 0;
            sub_80024FFC(m, name_800A37E8);
            sub_80025974(m, 5, 0);
            return;
        }
        if (a->f1AC <= 0)
        {
            int i = 0;
            int found = 0;
            a->f1AC = m->animCount_3E;
            for (; i < a->f1AC; i++)
            {
                if (m->animLoaded_44[i] != 0)
                {
                    a->f1A8 = i;
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                a->f1B0 = 0;
                LoadModelAnim_80025440(m, 0, 0);
                return;
            }
        }
        else
        {
            a->f1A8 = a->f1B0;
        }
        sub_80025C38(m, 1);
        a->state = 3;
    }
}

typedef struct TstModelMat
{
    int w[8];
} TstModelMat;
extern unsigned short padHeld_800918D0[];
extern short sinTable_80084540[];
extern MATRIX name_800A1E84;
extern TstModelMat name_800A1EA4;
extern MATRIX lightMatrix_80087114;
extern TstModelMat colorMatrix_80087134;
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
    MulMatrix0(&name_800A1E84, &m, &lightMatrix_80087114);
    PopMatrix();
    colorMatrix_80087134 = name_800A1EA4;
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
        sub_800A0BC0(c);
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
    c->i178 = c->s174 * sinTable_80084540[c->s170 & 0xFFF] / 4096;
    c->i180 = c->s174 * sinTable_80084540[(c->s170 + 0x400) & 0xFFF] / 4096;
    if (padHeld_800918D0[0] & 1)
    {
        if (padHeld_800918D0[0] & 2)
        {
            sub_800A0BC0(c);
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
extern void sub_8004D288(VECTOR* out, ModelAnim* anim, int frame);
extern void PlayAnimFrameSfx_8001C364(Model* a0, int idx, int a2);
extern void sub_80046A58(void* a, void* b, int c);
extern void DrawSpriteVtxQuadsGT4_800459E4(void* a, void* b, void* c, int d);
extern char name_800A3268[];
extern char name_800A3804[];
extern char name_800A1EE8[];
void sub_800A1428(TstModelD* c)
{
    VECTOR pos;
    char z[8];
    VECTOR scale;
    Model* m;
    ModelAnim* anim;
    memset(z, 0, 8);
    m = AcquireModel_80024D70(c->models_14, c->modelId_24);
    c->model_18 = m;
    anim = &m->anims_54[c->f1A8];
    sub_8004D288(&pos, anim, (unsigned)c->f1A4 % anim->frameCount_0);
    pos.vx /= anim->divisor_8;
    pos.vy /= anim->divisor_8;
    pos.vz /= anim->divisor_8;
    pos.vy += 0xFA;
    scale.vx = (c->f1BC + 1) << 12;
    scale.vy = (c->f1BC + 1) << 12;
    scale.vz = (c->f1BC + 1) << 12;
    c->draw_1C0.anim_14 = &m->anims_54[c->f1A8];
    c->draw_1C0.ftg_0 = m->ftg_50;
    c->draw_1C0.pos_4 = &pos;
    c->draw_1C0.f8 = z;
    c->draw_1C0.bones_C = c->bones;
    c->draw_1C0.f10 = name_800A3268;
    c->draw_1C0.frame_18 = (unsigned)c->f1A4 % c->draw_1C0.anim_14->frameCount_0;
    c->draw_1C0.f1C = 0;
    c->draw_1C0.f20 = name_800A3804;
    c->draw_1C0.scale_24 = &scale;
    c->draw_1C0.ot_28 = pOT_8008D690;
    PlayAnimFrameSfx_8001C364(m, c->f1A8, c->draw_1C0.frame_18);
    sub_80046A58(&c->draw_1C0, name_800A1EE8, 0);
    DrawSpriteVtxQuadsGT4_800459E4(c->bones, &m->mats_5C, pOT_8008D690, 0);
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
    if (c->fC != cur.s6 || c->f10 != (short)cur.sE)
    {
        PlaySfx_80031494(0x7F);
    }
    c->fC = cur.s6;
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

extern void name_8002556C(Model* m, int a);
void sub_800A17B8(TstModelD* c)
{
    unsigned short pad;
    Model* m;
    if (padRepeat_800918CC[0] & 0x4000)
    {
        c->f1B0++;
    }
    else if (padRepeat_800918CC[0] & 0x1000)
    {
        if (--c->f1B0 < 0)
        {
            c->f1B0 = c->f1AC - 1;
        }
    }
    c->f1B0 = (unsigned)c->f1B0 % c->f1AC;
    pad = padPressed_8009194C[0];
    if (pad & 0x20)
    {
        m = AcquireModel_80024D70(c->models_14, c->modelId_24);
        if (c->f1B4)
        {
            name_8002556C(m, c->f1A8);
            c->f1B4 = 0;
        }
        if (m->animLoaded_44[c->f1B0] == 0)
        {
            c->f1B4 = 1;
        }
        else
        {
            c->f1B4 = 0;
        }
        if (c->f1B4)
        {
            LoadModelAnim_80025440(m, c->f1B0, 0);
        }
        c->f1B8 = 0;
        c->f1A4 = 0;
        c->state = 2;
    }
    else if (pad & 0x40)
    {
        c->s172 = 0;
        c->state = 3;
    }
}

void sub_800A18F4(TstModelD* c)
{
    if (c->f1B8)
    {
        if (padRepeat_800918CC[0] & 0x80)
        {
            c->f1A4++;
        }
        else if (padRepeat_800918CC[0] & 0x10)
        {
            if (--c->f1A4 < 0)
            {
                c->f1A4 = c->draw_1C0.anim_14->frameCount_0 - 1;
            }
        }
        c->f1A4 = c->f1A4 % c->draw_1C0.anim_14->frameCount_0;
    }
    else
    {
        c->f1A4++;
    }
    if (padPressed_8009194C[0] & 0x40)
    {
        c->s172 = 0;
        c->f1B8 = !c->f1B8;
    }
    if (padPressed_8009194C[0] & 0x100)
    {
        c->f1BC = (c->f1BC + 1) & 3;
    }
}

void sub_800A19E4(TstModelD* a)
{
    if (a->models_14)
    {
        FreeModelList_80024BB0(&a->models_14);
    }
    a->models_14 = 0;
    a->state = 0;
}

extern int name_8008D600[];
extern short name_8008D4C8[];
extern unsigned char name_8008D460[];
extern short name_8008D474[];
extern int geomScreenDistance_8008B548;
extern int name_8003B548();
extern void name_8004D0E8();
void SetCameraLookAt_800A1A24(TstModelD* c)
{
    int v[3];
    int yaw;
    name_8008D600[0] = c->i178;
    name_8008D600[1] = c->i17C;
    name_8008D600[2] = c->i180;
    v[0] = c->i184 - c->i178;
    v[1] = c->i188 - c->i17C;
    v[2] = c->i18C - c->i180;
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

int MoveGridCursor_800A1B48(TstModelB* m)
{
    int idx = 0;
    if (m->s6 < 0)
    {
        m->s6 = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (m->s6 % m->s8 == m->s8 - 1)
        {
            return 1;
        }
        m->s6++;
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (m->s6 % m->s8 == 0)
        {
            return 2;
        }
        m->s6--;
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (m->s6 < m->s8)
        {
            return 3;
        }
        m->s6 -= m->s8;
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (m->s6 > m->s8 * (m->sA - 1) - 1)
        {
            return 4;
        }
        m->s6 = m->s6 + m->s8;
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
    int old = p->s6;
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
    if (old != p->s6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 9;
}

INCLUDE_OVERLAY_ASM(tstmodel, dword_800A1E84);
