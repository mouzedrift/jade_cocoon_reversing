// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "tu_8001EA48.h"

extern unsigned short padPressed_8009194C;
extern unsigned short padRepeat_800918CC;

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A05A0);

typedef struct TstCompoBlk8 { char b[8]; } TstCompoBlk8;
typedef struct TstCompoBone
{
    short s0;
    short s2;
    short s4;
    short s6;
} TstCompoBone;
// parameter block of sub_80046A58 / sub_80047E28
typedef struct TstCompoDraw
{
    FtgObject* ftg_0;
    VECTOR* pos_4;
    char* f8;
    TstCompoBone* bones_C;
    char* f10;
    ModelAnim* anim_14;
    int frame_18;
    int f1C;
    char* f20;
    VECTOR* scale_24;
    unsigned long* ot_28;
} TstCompoDraw;
// work area of the TSTCOMPO task (TstCompoInit_800A0800)
typedef struct TstCompoWork
{
    int state_0;
    Model* model_4;
    int f8;
    TstCompoBone bones_C[40];
    short yaw_14C;
    short s14E;
    short dist_150;
    short pad_152;
    int eye_154[3];
    int at_160[3];
    int pos_16C[3];
    short s178;
    short s17A;
    short s17C;
    short pad_17E;
    int frame_180;
    int anim_184;
    int animCount_188;
    int f18C;
    int f190;
    int f194;
    int f198;
    int f19C;
    int* scale_1A0;
    char* f1A4;
    TstCompoDraw draw_1A8;
    int pad_1D4;
    TstCompoBlk8 f1D8;
    short f1E0;
    short f1E2;
    int f1E4;
    int f1E8;
    int f1EC;
    int f1F0;
    int f1F4;
    int f1F8;
    int f1FC;
    int f200;
    int f204;
    int f208;
    int f20C;
    int f210;
    int f214;
    int f218;
    int f21C;
    int f220;
    int f224;
    int f228;
    int f22C;
} TstCompoWork;
extern void TstCompoTask_800A097C();
extern TstCompoBlk8* name_800A250C[];
void TstCompoInit_800A0800(EventEntry* task, TstCompoWork* c)
{
    c->anim_184 = 3;
    c->state_0 = 0;
    c->f194 = 0;
    c->f190 = 0;
    c->frame_180 = 0;
    c->f198 = 0;
    drawEnvRed_8008D448[0] = 0x40;
    drawEnvRed_8008D448[1] = 0x40;
    drawEnvRed_8008D448[2] = 0x80;
    sub_800A1BE0(c);
    sub_800A0918();
    c->f1E8 = 0;
    c->f1E4 = -1;
    c->f1EC = -1;
    c->f1E0 = 0;
    c->f1E2 = 0;
    c->f1D8 = *name_800A250C[c->f1E8 * 5];
    c->f1F4 = 0;
    c->f1F0 = 0;
    c->f210 = 0;
    c->f214 = 0;
    c->f218 = 0;
    c->f21C = 0;
    c->f220 = 0;
    c->f224 = 0;
    c->f228 = 0;
    c->f22C = 0;
    c->f208 = 0;
    c->f20C = 0;
    c->f1FC = 0;
    c->f200 = 0;
    c->f204 = 0;
    task->cb_8 = (EventEntryFn)TstCompoTask_800A097C;
}

// parameters of StartModelTask_80010850 (0x34 bytes)
typedef struct TstCompoModelParams
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int modelId_1C;
    int f20;
    int f24;
    int f28;
    int f2C;
    int f30;
} TstCompoModelParams;
extern TstCompoModelParams name_800A2768;
extern int dword_8007DC74;
void sub_800A0918()
{
    TstCompoModelParams* p = &name_800A2768;
    p->f0 = 3;
    p->f4 = 1;
    p->f8 = 0xC;
    p->fC = 0x29;
    p->f10 = 0x555;
    p->f14 = 0x555;
    p->f18 = 0x555;
    p->modelId_1C = 4;
    p->f20 = 0;
    p->f24 = 0;
    p->f28 = 0x4C;
    p->f2C = 0;
    p->f30 = dword_8007DC74;
}

extern unsigned short padHeld_800918D0[];
extern void sub_800A0AB8();
extern void sub_800A1320();
extern void sub_800A1354();
extern void sub_800A13B8();
extern void sub_800A1468();
extern void sub_800A15F4();
extern void sub_800A1804();
extern void sub_800A194C();
extern void sub_800A19A4();
extern void sub_800A1AD0();
extern void TstCompoCameraInput_800A1C14();
void TstCompoTask_800A097C(EventEntry* task, TstCompoWork* c)
{
    if (c->state_0 != 1 && c->state_0 != 3 && c->state_0 != 6 && (padHeld_800918D0[0] & 4) && (padHeld_800918D0[0] & 1) &&
        (padHeld_800918D0[0] & 0x90A) == 0x90A)
    {
        sub_800A1AD0(c);
        bStopDrawingMovie_8008D45C = 1;
        return;
    }
    switch (c->state_0)
    {
    case 0:
        sub_800A0AB8(c);
        break;
    case 1:
        sub_800A1320(c);
        break;
    case 2:
        sub_800A1354(c);
        break;
    case 3:
        sub_800A13B8(c);
        break;
    case 4:
        sub_800A194C(c);
        TstCompoCameraInput_800A1C14(c);
        sub_800A1468(c);
        sub_800A1804(c);
        break;
    case 5:
        sub_800A15F4(c);
        sub_800A19A4(c);
        break;
    case 6:
        sub_800A1AD0(c);
        break;
    }
}

INCLUDE_OVERLAY_ASM(tstcompo, sub_800A0AB8);

extern void name_80010850();
void sub_800A1320(TstCompoWork* a)
{
    name_80010850(&name_800A2768);
    a->state_0 = 2;
}

extern int name_80010A10(int);
extern Model* name_80010A44(int);
extern void sub_800A1AFC();
void sub_800A1354(TstCompoWork* a)
{
    if (name_80010A10(0))
    {
        a->model_4 = name_80010A44(0);
        sub_800A1AFC(a);
        a->animCount_188 = -1;
        a->f198 = 0;
        a->f19C = name_800A2768.modelId_1C;
        a->state_0 = 3;
    }
}

extern int name_80024DC4(Model*);
void sub_800A13B8(TstCompoWork* a)
{
    if (name_80024DC4(a->model_4))
    {
        if (a->animCount_188 <= 0)
        {
            int i;
            a->animCount_188 = a->model_4->animCount_3E;
            for (i = 0; i < a->animCount_188; i++)
            {
                if (a->model_4->animLoaded_44[i] != 0)
                {
                    a->anim_184 = i;
                    break;
                }
            }
        }
        else
        {
            a->anim_184 = a->f18C;
        }
        a->state_0 = 4;
    }
}

extern void* memset(void* p, int c, unsigned int n);
extern void sub_80046A58(void* a, void* b, void* c);
extern void DrawSpriteVtxQuadsGT4_800459E4(void* a, void* b, void* c, int d);
extern char name_800A2588[];
extern char name_800A2570[];
void sub_800A1468(TstCompoWork* c)
{
    VECTOR pos;
    char z[8];
    VECTOR scale;
    memset(z, 0, 8);
    pos.vx = c->pos_16C[0];
    pos.vy = c->pos_16C[1];
    pos.vz = c->pos_16C[2];
    pos.vy += 0xFA;
    c->scale_1A0 = sub_80024E90(c->model_4, c->f19C);
    scale.vx = c->scale_1A0[0] + (c->f198 << 12);
    scale.vy = c->scale_1A0[1] + (c->f198 << 12);
    scale.vz = c->scale_1A0[2] + (c->f198 << 12);
    c->f1A4 = sub_80024EC8(c->model_4, c->f19C);
    c->draw_1A8.anim_14 = &c->model_4->anims_54[c->anim_184];
    c->draw_1A8.ftg_0 = c->model_4->ftg_50;
    c->draw_1A8.pos_4 = &pos;
    c->draw_1A8.f8 = z;
    c->draw_1A8.bones_C = c->bones_C;
    c->draw_1A8.f10 = c->f1A4;
    c->draw_1A8.frame_18 = (unsigned)c->frame_180 % c->draw_1A8.anim_14->frameCount_0;
    c->draw_1A8.f1C = 0;
    c->draw_1A8.f20 = name_800A2588;
    c->draw_1A8.scale_24 = &scale;
    c->draw_1A8.ot_28 = pOT_8008D690;
    sub_80046A58(&c->draw_1A8, name_800A2570, c->model_4->anims_54);
    DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
}

extern void sub_80047E28(void* a, void* b, void* c, int d, int e, void* f, void* g);
void sub_800A15F4(TstCompoWork* c)
{
    VECTOR pos;
    char z[8];
    VECTOR scale;
    ModelAnim* anim;
    memset(z, 0, 8);
    pos.vx = c->pos_16C[0];
    pos.vy = c->pos_16C[1];
    pos.vz = c->pos_16C[2];
    pos.vy += 0xFA;
    c->scale_1A0 = sub_80024E90(c->model_4, c->f19C);
    scale.vx = c->scale_1A0[0] + (c->f198 << 12);
    scale.vy = c->scale_1A0[1] + (c->f198 << 12);
    scale.vz = c->scale_1A0[2] + (c->f198 << 12);
    c->f1A4 = sub_80024EC8(c->model_4, c->f19C);
    c->draw_1A8.anim_14 = &c->model_4->anims_54[3];
    c->draw_1A8.ftg_0 = c->model_4->ftg_50;
    c->draw_1A8.pos_4 = &pos;
    c->draw_1A8.f8 = z;
    c->draw_1A8.bones_C = c->bones_C;
    c->draw_1A8.f10 = c->f1A4;
    c->draw_1A8.frame_18 = (unsigned)c->frame_180 % c->draw_1A8.anim_14->frameCount_0;
    c->draw_1A8.f1C = 0;
    c->draw_1A8.f20 = name_800A2588;
    c->draw_1A8.scale_24 = &scale;
    c->draw_1A8.ot_28 = pOT_8008D690;
    c->f1FC += 0x88;
    c->frame_180++;
    if ((unsigned)c->f1FC >= 0x1000)
    {
        sub_80046A58(&c->draw_1A8, name_800A2570, c->model_4->anims_54);
        DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
    }
    else
    {
        anim = &c->model_4->anims_54[c->f204];
        sub_80047E28(&c->draw_1A8, c->draw_1A8.f10, anim, (unsigned)c->f200 % anim->frameCount_0, 0x1000 - c->f1FC,
                     name_800A2570, c->model_4->anims_54);
        DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
    }
}

void sub_800A1804(TstCompoWork* c)
{
    if (c->f194)
    {
        if (padRepeat_800918CC & 0x80)
        {
            c->frame_180++;
        }
        else if (padRepeat_800918CC & 0x10)
        {
            if (--c->frame_180 < 0)
            {
                c->frame_180 = c->draw_1A8.anim_14->frameCount_0 - 1;
            }
        }
        c->frame_180 = c->frame_180 % c->draw_1A8.anim_14->frameCount_0;
    }
    else
    {
        c->frame_180++;
    }
    if (padPressed_8009194C & 0x40)
    {
        c->s14E = 0;
        c->f194 = !c->f194;
    }
    if (c->f194 == 0)
    {
        if (padPressed_8009194C & 0x100)
        {
            c->f198 = (c->f198 + 1) & 3;
        }
        if (padPressed_8009194C & 0x10)
        {
            c->f19C = (c->f19C + 1) % 5;
        }
    }
}

void sub_800A194C(TstCompoWork* c)
{
    if (padPressed_8009194C & 0x800)
    {
        c->state_0 = 6;
    }
    else if (padPressed_8009194C & 0x20)
    {
        c->state_0 = 5;
        c->f1FC = 0;
        c->f18C = c->anim_184;
        c->f200 = c->frame_180;
        c->f204 = c->anim_184;
    }
}

extern void name_8002556C(Model* a, int b);
extern void name_80025440(Model* a, int b, int c);
void sub_800A19A4(TstCompoWork* c)
{
    unsigned short pad = padRepeat_800918CC;
    if (pad & 0x1000)
    {
        int v = c->f18C + 1;
        int t = c->animCount_188 - 1;
        c->f18C = v;
        if (t < v)
        {
            c->f18C = t;
        }
    }
    else if (pad & 0x4000)
    {
        int v = c->f18C - 1;
        c->f18C = v;
        if (v <= 0)
        {
            c->f18C = 1;
        }
    }
    pad = padPressed_8009194C;
    if (pad & 0x20)
    {
        if (c->f190)
        {
            name_8002556C(c->model_4, c->anim_184);
            c->f190 = 0;
        }
        if (c->model_4->animLoaded_44[c->f18C] == 0)
        {
            c->f190 = 1;
        }
        else
        {
            c->f190 = 0;
        }
        if (c->f190)
        {
            name_80025440(c->model_4, c->f18C, 0);
        }
        c->f194 = 0;
        c->frame_180 = 0;
        c->state_0 = 3;
    }
    else if (pad & 0x40)
    {
        c->s14E = 0;
        c->state_0 = 4;
    }
}

// Matched
void sub_800A1AD0(TstCompoWork* a)
{
    FreeModelTask_8001098C(0);
    a->state_0 = 0;
}

extern TstCompoBone dword_80079140[];
extern void sub_80019B14(void* p, char* a1, char* a2);
void sub_800A1AFC(TstCompoWork* a)
{
    int i;
    char* r;
    for (i = 0; dword_80079140[i].s0 >= 0; i++)
    {
        a->bones_C[i] = dword_80079140[i];
    }
    a->bones_C[i] = dword_80079140[i];
    r = sub_80024F00(a->model_4, name_800A2768.modelId_1C);
    sub_80019B14(a->bones_C, r, sub_80024F38(a->model_4, name_800A2768.modelId_1C));
}

// Matched
void sub_800A1BE0(TstCompoWork* a)
{
    a->dist_150 = 0x4B0;
    a->yaw_14C = 0;
    a->pos_16C[0] = 0;
    a->pos_16C[1] = 0;
    a->pos_16C[2] = 0;
    a->s178 = 0;
    a->s17A = 0;
    a->s17C = 0;
    a->at_160[1] = -0xFA;
    a->eye_154[1] = -0xFA;
}

extern unsigned short padHeld_800918D0[];
extern short sinTable_80084540[];
extern void SetCameraLookAt_800A1E68();
void TstCompoCameraInput_800A1C14(TstCompoWork* a)
{
    if (padHeld_800918D0[0] & 0x8000)
    {
        a->yaw_14C -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x2000)
    {
        a->yaw_14C += 0x20;
    }
    if (padHeld_800918D0[0] & 0x1000)
    {
        a->eye_154[1] -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x4000)
    {
        a->eye_154[1] += 0x20;
    }
    a->eye_154[1] = a->eye_154[1] < -1000 ? -1000 : a->eye_154[1] < 1001 ? a->eye_154[1] : 1000;
    if ((padHeld_800918D0[0] & 0xC) == 0xC)
    {
        sub_800A1BE0(a);
    }
    else if (padHeld_800918D0[0] & 4)
    {
        a->dist_150 -= 0x20;
    }
    else if (padHeld_800918D0[0] & 8)
    {
        a->dist_150 += 0x20;
    }
    a->dist_150 = a->dist_150 < 100 ? 100 : a->dist_150 < 1201 ? a->dist_150 : 1200;
    a->eye_154[0] = a->dist_150 * sinTable_80084540[a->yaw_14C & 0xFFF] / 4096;
    a->eye_154[2] = a->dist_150 * sinTable_80084540[(a->yaw_14C + 0x400) & 0xFFF] / 4096;
    if (padHeld_800918D0[0] & 1)
    {
        if (padHeld_800918D0[0] & 2)
        {
            sub_800A1BE0(a);
        }
        else
        {
            a->at_160[1] -= 0x20;
        }
    }
    else if (padHeld_800918D0[0] & 2)
    {
        a->at_160[1] += 0x20;
    }
    a->at_160[1] = a->at_160[1] < -1000 ? -1000 : a->at_160[1] < 1001 ? a->at_160[1] : 1000;
    a->at_160[0] = 0;
    a->at_160[2] = 0;
    SetCameraLookAt_800A1E68(a);
}

typedef struct TstCompoMat
{
    int w[8];
} TstCompoMat;
extern int name_8008D600[];
extern short name_8008D4C8[];
extern unsigned char name_8008D460[];
extern short name_8008D474[];
extern int geomScreenDistance_8008B548;
extern int name_8003B548();
extern void name_8004D0E8();
extern TstCompoMat dword_8007C2EC;
extern TstCompoMat dword_8007C30C;
extern TstCompoMat dword_80087114;
extern TstCompoMat dword_80087134;
void SetCameraLookAt_800A1E68(TstCompoWork* c)
{
    int v[3];
    int yaw;
    name_8008D600[0] = c->eye_154[0];
    name_8008D600[1] = c->eye_154[1];
    name_8008D600[2] = c->eye_154[2];
    v[0] = c->at_160[0] - c->eye_154[0];
    v[1] = c->at_160[1] - c->eye_154[1];
    v[2] = c->at_160[2] - c->eye_154[2];
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
    dword_80087114 = dword_8007C2EC;
    dword_80087134 = dword_8007C30C;
    name_8004D0E8();
}

extern char name_800A2560[];
// Matched
int sub_800A200C()
{
    DrawIntroMovie_8001AF64(name_800A2560);
    return 6;
}

typedef struct TstCompoEnt
{
    unsigned short a;
    unsigned short b;
    int p;
} TstCompoEnt;
extern unsigned short uiColor_8008B590;
extern void DrawText_8003E91C(int a, int b, void* c, int d);
extern void DrawWindow_80042460(int a, void* b, void* c, int d);
// window style for DrawWindow_80042460
typedef struct TstCompoWinStyle
{
    unsigned short color_0;
    unsigned char colors_2; // GetWindowColors_8004226C
    unsigned char frame_3;  // DrawWindowFrame_80041ED0
} TstCompoWinStyle;
void DrawTextListWindow_800A2030(int p, TstCompoEnt* e, int idx)
{
    union
    {
        unsigned short pos[2];
        TstCompoWinStyle style;
    } t; // the text position, then the window style
    if (e)
    {
        int i = 0;
        while (e[i].p)
        {
            t.pos[0] = e[i].a;
            t.pos[1] = e[i].b;
            DrawText_8003E91C(1, e[i].p, t.pos, idx);
            i++;
        }
    }
    if (p)
    {
        t.style.colors_2 = 1;
        t.style.frame_3 = 1;
        t.style.color_0 = uiColor_8008B590;
        DrawWindow_80042460(p, &t.style, pOT_8008D454 + idx, 0);
    }
}

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A20EC);
