// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "model.h"

extern unsigned short padPressed_8009194C;
extern unsigned short padRepeat_800918CC;

INCLUDE_OVERLAY_ASM(tstcompo, dword_800A05A0);

typedef struct TstCompoBlk8 { char b[8]; } TstCompoBlk8;
// a menu layout of the TSTCOMPO pages: the cursor head (copied into the work cursor), then the grid geometry
typedef struct TstCompoMenu
{
    union
    {
        TstCompoBlk8 blk;
        struct
        {
            short cols_0;
            short count_2;
            short f4;
            short f6;
        } f;
    } head_0;
    short dx_8;
    short dy_A;
    short x_C;
    short y_E;
} TstCompoMenu;
typedef struct TstCompoEnt
{
    unsigned short a;
    unsigned short b;
    int p;
} TstCompoEnt;
// a TSTCOMPO page (name_800A250C[3])
typedef struct TstCompoPage
{
    TstCompoMenu* menu_0;
    TstCompoEnt* texts_4;
    short rect_8[4];
    int f10;
} TstCompoPage;
// a selectable part / colour of the compound test (dword_800A20EC[])
typedef struct TstCompoPart
{
    int text_0;
    int id_4;
    int angle_8;
    int fC;
    int f10;
} TstCompoPart;
typedef struct TstCompoBone
{
    short s0;
    short s2;
    short s4;
    short s6;
} TstCompoBone;
// parameter block of DrawAnimSkel_80046A58 / DrawAnimSkelBlend_80047E28
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
    unsigned int f1F4;
    int* f1F8;
    int f1FC;
    int f200;
    int f204;
    int f208;
    int f20C;
    int part_210[3];
    int ratio_21C[3];
    int f228;
    int f22C;
} TstCompoWork;
extern void TstCompoTask_800A097C();
extern TstCompoPage name_800A250C[];
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
    c->f1D8 = name_800A250C[c->f1E8].menu_0->head_0.blk;
    c->f1F4 = 0;
    c->f1F0 = 0;
    c->part_210[0] = 0;
    c->part_210[1] = 0;
    c->part_210[2] = 0;
    c->ratio_21C[0] = 0;
    c->ratio_21C[1] = 0;
    c->ratio_21C[2] = 0;
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
    int part_4[3];  // the compounded minions' part ids (TstCompoPart.id_4)
    int ratio_10[3]; // their shares, 0x1000 in all
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
    p->part_4[0] = 1;
    p->part_4[1] = 0xC;
    p->part_4[2] = 0x29;
    p->ratio_10[0] = 0x555;
    p->ratio_10[1] = 0x555;
    p->ratio_10[2] = 0x555;
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

extern TstCompoPart dword_800A20EC[];
extern int AdjustByLeftRight_8003D210(int limit, int pos, int step, int idx);
extern int AdjustByShoulderButtons_8003D198(int limit, int pos, int step, int idx);
extern int UpdateMenuCursor_8003D794(void* p, int idx);
extern void DrawBobbingCursorHand_8003D090(short x, short y, int a2, int a3, int idx);
extern void DrawText_8003E91C(int a, int b, void* c, int d);
extern void DrawNumberRightAlignedFont1_8003F264(void* pos, int val, int ot);
extern void DrawTextListWindow_800A2030(short* rect, TstCompoEnt* e, int idx);
// Matched
void sub_800A0AB8(TstCompoWork* c)
{
    short p0[4];
    short p1[4];
    short p2[4];
    short p3[4];
    short p4[4];
    short p5[4];
    TstCompoMenu* m;
    int i;
    int j;
    int a;
    int b;
    int d;
    unsigned int total;

    if (c->f1E4 != -1)
    {
        c->f1E8 = c->f1E4;
        c->f1E4 = -1;
        c->f1D8 = name_800A250C[c->f1E8].menu_0->head_0.blk;
        c->f1E0 = 0;
        c->f1E2 = 0;
        switch (c->f1E8)
        {
        case 0:
            c->f1E0 = c->f1F4;
            break;
        case 1:
            break;
        case 2:
            c->f1E0 = c->f20C;
            c->f1E2 = c->f208;
            break;
        }
    }
    switch (c->f1E8)
    {
    case 0:
        if (IsConfirmPressedP1_8003D380(1))
        {
            c->f1E4 = 2;
            c->f1EC = 0;
            c->f1F8 = &c->part_210[c->f1E0];
            c->f1F4 = c->f1E0;
        }
        c->ratio_21C[c->f1E0] = AdjustByLeftRight_8003D210(10, c->ratio_21C[c->f1E0], 1, 0);
        break;
    case 1:
        if (IsConfirmPressedP1_8003D380(1))
        {
            c->f1F8 = &c->f22C;
            c->f1E4 = 2;
            c->f1EC = 1;
            c->f1F4 = c->f1E0;
        }
        name_800A2768.f24 = AdjustByLeftRight_8003D210(0x167, name_800A2768.f24, 1, 0);
        name_800A2768.f24 = AdjustByShoulderButtons_8003D198(0x168, name_800A2768.f24, 10, 0);
        break;
    case 2:
        if (IsConfirmPressedP1_8003D380(1))
        {
            *c->f1F8 = c->f1E0 + c->f1E2;
            c->f1E4 = c->f1EC;
        }
        else if (IsCancelPressedP1_8003D41C(1))
        {
            c->f1E4 = c->f1EC;
        }
        m = name_800A250C[c->f1EC].menu_0;
        DrawBobbingCursorHand_8003D090(m->x_C + (c->f1F4 % m->head_0.f.cols_0) * m->dx_8,
                     m->y_E + (c->f1F4 / m->head_0.f.cols_0) * m->dy_A + 6, 0, 0, 0);
        c->f20C = c->f1E0;
        c->f208 = c->f1E2;
        break;
    }
    switch (UpdateMenuCursor_8003D794(&c->f1D8, 0))
    {
    case 4:
        c->f1E8++;
        c->f1D8 = name_800A250C[c->f1E8].menu_0->head_0.blk;
        c->f1E0 = 0;
        c->f1E2 = 0;
        break;
    case 3:
        c->f1E8--;
        c->f1D8 = name_800A250C[c->f1E8].menu_0->head_0.blk;
        c->f1E0 = name_800A250C[c->f1E8].menu_0->head_0.f.count_2 - 1;
        c->f1E2 = 0;
        break;
    }
    m = name_800A250C[c->f1E8].menu_0;
    DrawBobbingCursorHand_8003D090(m->x_C + (c->f1E0 % m->head_0.f.cols_0) * m->dx_8,
                 m->y_E + (c->f1E0 / m->head_0.f.cols_0) * m->dy_A + 6, 0, 0, 0);
    if (c->f1E8 < 3)
    {
        if (c->f1E8 >= 0)
        {
            p0[0] = 0x22;
            p0[1] = 0x1C;
            DrawText_8003E91C(1, dword_800A20EC[c->part_210[0]].text_0, p0, 0);
            p1[0] = 0x22;
            p1[1] = 0x26;
            DrawText_8003E91C(1, dword_800A20EC[c->part_210[1]].text_0, p1, 0);
            p2[0] = 0x22;
            p2[1] = 0x30;
            DrawText_8003E91C(1, dword_800A20EC[c->part_210[2]].text_0, p2, 0);
            p3[0] = 0x92;
            p3[1] = 0x1C;
            DrawNumberRightAlignedFont1_8003F264(p3, c->ratio_21C[0], 0);
            p4[0] = 0x92;
            p4[1] = 0x26;
            DrawNumberRightAlignedFont1_8003F264(p4, c->ratio_21C[1], 0);
            p5[0] = 0x92;
            p5[1] = 0x30;
            DrawNumberRightAlignedFont1_8003F264(p5, c->ratio_21C[2], 0);
            p0[0] = 0x22;
            p0[1] = 0x46;
            DrawText_8003E91C(1, dword_800A20EC[c->f22C].text_0, p0, 0);
            p1[0] = 0x92;
            p1[1] = 0x46;
            DrawNumberRightAlignedFont1_8003F264(p1, name_800A2768.f24, 0);
            for (i = 0; i < 20; i++)
            {
                p0[0] = 0xCA;
                p0[1] = (i + 1) * 10 + 0x12;
                DrawText_8003E91C(1, dword_800A20EC[c->f208 + i].text_0, p0, 0);
            }
            for (j = 0; j < 3; j++)
            {
                DrawTextListWindow_800A2030(name_800A250C[j].rect_8, name_800A250C[j].texts_4, 0);
            }
        }
    }
    if (padPressed_8009194C & 0x800)
    {
        name_800A2768.f0 = 3;
        name_800A2768.modelId_1C = 4;
        name_800A2768.f20 = 0;
        name_800A2768.f28 = dword_800A20EC[c->f22C].id_4;
        name_800A2768.f2C = 0;
        name_800A2768.part_4[0] = a = dword_800A20EC[c->part_210[0]].id_4;
        name_800A2768.part_4[1] = b = dword_800A20EC[c->part_210[1]].id_4;
        name_800A2768.part_4[2] = d = dword_800A20EC[c->part_210[2]].id_4;
        if (a == b)
        {
            if (b == d)
            {
                c->ratio_21C[0] += c->ratio_21C[1];
                c->ratio_21C[0] += c->ratio_21C[2];
                c->ratio_21C[1] = 0;
                c->ratio_21C[2] = 0;
            }
            else
            {
                c->ratio_21C[0] += c->ratio_21C[1];
                c->ratio_21C[1] = 0;
            }
        }
        else if (a == d)
        {
            c->ratio_21C[0] += c->ratio_21C[2];
            c->ratio_21C[2] = 0;
        }
        else if (b == d)
        {
            c->ratio_21C[1] += c->ratio_21C[2];
            c->ratio_21C[2] = 0;
        }
        total = c->ratio_21C[0] + c->ratio_21C[1] + c->ratio_21C[2];
        name_800A2768.ratio_10[0] = (c->ratio_21C[0] << 12) / total;
        name_800A2768.ratio_10[1] = (c->ratio_21C[1] << 12) / total;
        name_800A2768.ratio_10[2] = (c->ratio_21C[2] << 12) / total;
        name_800A2768.f24 += dword_800A20EC[c->f22C].angle_8;
        if (name_800A2768.f24 >= 0x168)
        {
            name_800A2768.f24 -= 0x168;
        }
        c->state_0 = 1;
    }
}

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
extern void DrawAnimSkel_80046A58(void* a, void* b, void* c);
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
    c->scale_1A0 = GetModelBaseScale_80024E90(c->model_4, c->f19C);
    scale.vx = c->scale_1A0[0] + (c->f198 << 12);
    scale.vy = c->scale_1A0[1] + (c->f198 << 12);
    scale.vz = c->scale_1A0[2] + (c->f198 << 12);
    c->f1A4 = GetModelBoneScale_80024EC8(c->model_4, c->f19C);
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
    DrawAnimSkel_80046A58(&c->draw_1A8, name_800A2570, c->model_4->anims_54);
    DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
}

extern void DrawAnimSkelBlend_80047E28(void* a, void* b, void* c, int d, int e, void* f, void* g);
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
    c->scale_1A0 = GetModelBaseScale_80024E90(c->model_4, c->f19C);
    scale.vx = c->scale_1A0[0] + (c->f198 << 12);
    scale.vy = c->scale_1A0[1] + (c->f198 << 12);
    scale.vz = c->scale_1A0[2] + (c->f198 << 12);
    c->f1A4 = GetModelBoneScale_80024EC8(c->model_4, c->f19C);
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
        DrawAnimSkel_80046A58(&c->draw_1A8, name_800A2570, c->model_4->anims_54);
        DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
    }
    else
    {
        anim = &c->model_4->anims_54[c->f204];
        DrawAnimSkelBlend_80047E28(&c->draw_1A8, c->draw_1A8.f10, anim, (unsigned)c->f200 % anim->frameCount_0, 0x1000 - c->f1FC,
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

extern TstCompoBone defaultBones_80079140[];
extern void SetBoneGroupFlags_80019B14(void* p, char* a1, char* a2);
void sub_800A1AFC(TstCompoWork* a)
{
    int i;
    char* r;
    for (i = 0; defaultBones_80079140[i].s0 >= 0; i++)
    {
        a->bones_C[i] = defaultBones_80079140[i];
    }
    a->bones_C[i] = defaultBones_80079140[i];
    r = sub_80024F00(a->model_4, name_800A2768.modelId_1C);
    SetBoneGroupFlags_80019B14(a->bones_C, r, sub_80024F38(a->model_4, name_800A2768.modelId_1C));
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
extern TstCompoMat lightMatrix_80087114;
extern TstCompoMat colorMatrix_80087134;
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
    lightMatrix_80087114 = dword_8007C2EC;
    colorMatrix_80087134 = dword_8007C30C;
    name_8004D0E8();
}

extern char name_800A2560[];
// Matched
int sub_800A200C()
{
    DrawIntroMovie_8001AF64(name_800A2560);
    return 6;
}

extern unsigned short uiColor_8008B590;
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);
// window style for DrawWindow_80042460
typedef struct TstCompoWinStyle
{
    unsigned short color_0;
    unsigned char colors_2; // GetWindowColors_8004226C
    unsigned char frame_3;  // DrawWindowFrame_80041ED0
} TstCompoWinStyle;
void DrawTextListWindow_800A2030(short* p, TstCompoEnt* e, int idx)
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
