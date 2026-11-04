// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "model.h"
#include "tstcompo.h"

extern unsigned short padPressed_8009194C;
extern unsigned short padRepeat_800918CC;

int dword_800A05A0 SDATA = 17;
const char a9_800A05A4[] = "\202X"; // 9
const char a8_800A05A8[] = "\202W"; // 8
const char a7_800A05AC[] = "\202V"; // 7
const char a6_800A05B0[] = "\202U"; // 6
const char a5_800A05B4[] = "\202T"; // 5
const char a4_800A05B8[] = "\202S"; // 4
const char a3_800A05BC[] = "\202R"; // 3
const char a2_800A05C0[] = "\202Q"; // 2
const char a1_800A05C4[] = "\202P"; // 1
const char a0_800A05C8[] = "\202O"; // 0
const char asc_800A05CC[] = "\203p\203h\203\213\203J"; // パドルカ
const char asc_800A05D8[] = "\203A\203\213\203p\203^\203\215\203\223"; // アルパタロン
const char asc_800A05E8[] = "\203V\203F\203\212\203N"; // シェリク
const char asc_800A05F4[] = "\203\211\203V\203\203\203o\203o"; // ラシャババ
const char asc_800A0600[] = "\203g\203D\203C\203\223\203S"; // トゥインゴ
const char asc_800A060C[] = "\203G\203X\203v"; // エスプ
const char asc_800A0614[] = "\203W\203\211\203\213"; // ジラル
const char asc_800A061C[] = "\203\210\203\213\203N"; // ヨルク
const char asc_800A0624[] = "\203E\203O\203\211\203\200"; // ウグラム
const char asc_800A0630[] = "\203X\203\212\203J\201[\203^"; // スリカータ
const char asc_800A063C[] = "\203\212\203O"; // リグ
const char asc_800A0644[] = "\203I\203W\203F"; // オジェ
const char asc_800A064C[] = "\203l\201[\203u\203C"; // ネーブイ
const char asc_800A0658[] = "\203\200\203O\201["; // ムグー
const char asc_800A0660[] = "\203}\201[\203C\203F\203\223"; // マーイェン
const char asc_800A066C[] = "\203M\203k\203C"; // ギヌイ
const char asc_800A0674[] = "\203A\203V\203\203"; // アシャ
const char asc_800A067C[] = "\203\200\203c\203L\203V\203\203\203u"; // ムツキシャブ
const char asc_800A068C[] = "\203\211\203V\203\203\203u"; // ラシャブ
const char asc_800A0698[] = "\203k\203V\203\203\203u"; // ヌシャブ
const char asc_800A06A4[] = "\203h\203O\203\213\203`\203\205\201["; // ドグルチュー
const char asc_800A06B4[] = "\203\211\203h\203\213\203`\203\205"; // ラドルチュ
const char asc_800A06C0[] = "\203p\203^\203\213\203`\203\205\203E"; // パタルチュウ
const char asc_800A06D0[] = "\203\211\203h\203C\203\201\203\213"; // ラドイメル
const char asc_800A06DC[] = "\203X\203N\203C\203\201\203\213"; // スクイメル
const char asc_800A06E8[] = "\203p\203^\203C\203\201\203\213"; // パタイメル
const char asc_800A06F4[] = "\203q\203\211\203T\203O"; // ヒラサグ
const char asc_800A0700[] = "\203}\203X\203R\203q\203\211"; // マスコヒラ
const char asc_800A070C[] = "\203q\203\211\203\213\203R"; // ヒラルコ
const char asc_800A0718[] = "\203e\203\211\203n\203\223\203u\201["; // テラハンブー
const char asc_800A0728[] = "\203h\203O\203n\203\223\203u\201["; // ドグハンブー
const char asc_800A0738[] = "\203\200\203J\203n\203\223\203u\201["; // ムカハンブー
const char asc_800A0748[] = "\203x\203\211\203o\203\223\203T"; // ベラバンサ
const char asc_800A0754[] = "\203h\203\223\203O\203\213"; // ドングル
const char asc_800A0760[] = "\203\211\203M\203h\203O\203\213"; // ラギドグル
const char asc_800A076C[] = "\203p\203^\203h\203\214\203b\203N"; // パタドレック
const char asc_800A077C[] = "\203\211\203h\203\214\203b\203O"; // ラドレッグ
const char asc_800A0788[] = "\203}\203A\203h\203\214\203b\203O"; // マアドレッグ
const char aNAMERATE_800A0798[] = "\202m\202`\202l\202d\201@\201@\201@\201@\201@\201@\202q\202`\202s\202d"; // NAME      RATE
const char aTEXHANGL_800A07B8[] = "\202s\202d\202w\201@\201@\201@\201@\201@\201@\202g\202`\202m\202f\202k"; // TEX      HANGL
const char aENEMY_800A07D8[] = "\202d\202m\202d\202l\202x"; // ENEMY

// a menu layout of the TSTCOMPO pages: the cursor head (copied into the work cursor), then the grid geometry
// a TSTCOMPO page (compoPages_800A250C[3])
// a selectable part / colour of the compound test (compoParts_800A20EC[])
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
    int nextAnim_18C;
    int animLoaded_190;
    int paused_194;
    int scaleStep_198;
    int scaleId_19C;
    int* scale_1A0;
    char* f1A4;
    TstCompoDraw draw_1A8;
    int pad_1D4;
    TstCompoBlk8 cursor_1D8;
    short sel_1E0;
    short scroll_1E2;
    int nextPage_1E4;
    int page_1E8;
    int returnPage_1EC;
    int f1F0;
    unsigned int savedSel_1F4;
    int* pickTarget_1F8;
    int blend_1FC;
    int blendFrame_200;
    int blendAnim_204;
    int listScroll_208;
    int listSel_20C;
    int part_210[3];
    int ratio_21C[3];
    int f228;
    int enemy_22C;
} TstCompoWork;
extern void TstCompoTask_800A097C();
void TstCompoInit_800A0800(EventEntry* task, TstCompoWork* c)
{
    c->anim_184 = 3;
    c->state_0 = 0;
    c->paused_194 = 0;
    c->animLoaded_190 = 0;
    c->frame_180 = 0;
    c->scaleStep_198 = 0;
    drawEnvRed_8008D448[0] = 0x40;
    drawEnvRed_8008D448[1] = 0x40;
    drawEnvRed_8008D448[2] = 0x80;
    TstCompoResetCamera_800A1BE0(c);
    SetDefaultCompoParams_800A0918();
    c->page_1E8 = 0;
    c->nextPage_1E4 = -1;
    c->returnPage_1EC = -1;
    c->sel_1E0 = 0;
    c->scroll_1E2 = 0;
    c->cursor_1D8 = compoPages_800A250C[c->page_1E8].menu_0->head_0.blk;
    c->savedSel_1F4 = 0;
    c->f1F0 = 0;
    c->part_210[0] = 0;
    c->part_210[1] = 0;
    c->part_210[2] = 0;
    c->ratio_21C[0] = 0;
    c->ratio_21C[1] = 0;
    c->ratio_21C[2] = 0;
    c->f228 = 0;
    c->enemy_22C = 0;
    c->listScroll_208 = 0;
    c->listSel_20C = 0;
    c->blend_1FC = 0;
    c->blendFrame_200 = 0;
    c->blendAnim_204 = 0;
    task->cb_8 = (EventEntryFn)TstCompoTask_800A097C;
}

// parameters of StartModelTask_80010850 (0x34 bytes)
extern int dword_8007DC74;
void SetDefaultCompoParams_800A0918()
{
    TstCompoModelParams* p = &compoModelParams_800A2768;
    p->partCount_0 = 3;
    p->part_4[0] = 1;
    p->part_4[1] = 0xC;
    p->part_4[2] = 0x29;
    p->ratio_10[0] = 0x555;
    p->ratio_10[1] = 0x555;
    p->ratio_10[2] = 0x555;
    p->modelId_1C = 4;
    p->f20 = 0;
    p->angle_24 = 0;
    p->enemyPart_28 = 0x4C;
    p->f2C = 0;
    p->f30 = dword_8007DC74;
}

extern unsigned short padHeld_800918D0[];
extern void TstCompoMenu_800A0AB8();
extern void TstCompoStartModel_800A1320();
extern void TstCompoWaitModel_800A1354();
extern void TstCompoWaitFiles_800A13B8();
extern void TstCompoDrawModel_800A1468();
extern void TstCompoDrawBlend_800A15F4();
extern void TstCompoFrameInput_800A1804();
extern void TstCompoViewInput_800A194C();
extern void TstCompoAnimSelect_800A19A4();
extern void TstCompoFreeModel_800A1AD0();
extern void TstCompoCameraInput_800A1C14();
void TstCompoTask_800A097C(EventEntry* task, TstCompoWork* c)
{
    if (c->state_0 != 1 && c->state_0 != 3 && c->state_0 != 6 && (padHeld_800918D0[0] & 4) && (padHeld_800918D0[0] & 1) &&
        (padHeld_800918D0[0] & 0x90A) == 0x90A)
    {
        TstCompoFreeModel_800A1AD0(c);
        bStopDrawingMovie_8008D45C = 1;
        return;
    }
    switch (c->state_0)
    {
    case 0:
        TstCompoMenu_800A0AB8(c);
        break;
    case 1:
        TstCompoStartModel_800A1320(c);
        break;
    case 2:
        TstCompoWaitModel_800A1354(c);
        break;
    case 3:
        TstCompoWaitFiles_800A13B8(c);
        break;
    case 4:
        TstCompoViewInput_800A194C(c);
        TstCompoCameraInput_800A1C14(c);
        TstCompoDrawModel_800A1468(c);
        TstCompoFrameInput_800A1804(c);
        break;
    case 5:
        TstCompoDrawBlend_800A15F4(c);
        TstCompoAnimSelect_800A19A4(c);
        break;
    case 6:
        TstCompoFreeModel_800A1AD0(c);
        break;
    }
}

extern int AdjustByLeftRight_8003D210(int limit, int pos, int step, int idx);
extern int AdjustByShoulderButtons_8003D198(int limit, int pos, int step, int idx);
extern int UpdateMenuCursor_8003D794(void* p, int idx);
extern void DrawBobbingCursorHand_8003D090(short x, short y, int a2, int a3, int idx);
extern void DrawText_8003E91C(int a, int b, void* c, int d);
extern void DrawNumberRightAlignedFont1_8003F264(void* pos, int val, int ot);
extern void DrawTextListWindow_800A2030(short* rect, TstCompoEnt* e, int idx);
// Matched
void TstCompoMenu_800A0AB8(TstCompoWork* c)
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

    if (c->nextPage_1E4 != -1)
    {
        c->page_1E8 = c->nextPage_1E4;
        c->nextPage_1E4 = -1;
        c->cursor_1D8 = compoPages_800A250C[c->page_1E8].menu_0->head_0.blk;
        c->sel_1E0 = 0;
        c->scroll_1E2 = 0;
        switch (c->page_1E8)
        {
        case 0:
            c->sel_1E0 = c->savedSel_1F4;
            break;
        case 1:
            break;
        case 2:
            c->sel_1E0 = c->listSel_20C;
            c->scroll_1E2 = c->listScroll_208;
            break;
        }
    }
    switch (c->page_1E8)
    {
    case 0:
        if (IsConfirmPressedP1_8003D380(1))
        {
            c->nextPage_1E4 = 2;
            c->returnPage_1EC = 0;
            c->pickTarget_1F8 = &c->part_210[c->sel_1E0];
            c->savedSel_1F4 = c->sel_1E0;
        }
        c->ratio_21C[c->sel_1E0] = AdjustByLeftRight_8003D210(10, c->ratio_21C[c->sel_1E0], 1, 0);
        break;
    case 1:
        if (IsConfirmPressedP1_8003D380(1))
        {
            c->pickTarget_1F8 = &c->enemy_22C;
            c->nextPage_1E4 = 2;
            c->returnPage_1EC = 1;
            c->savedSel_1F4 = c->sel_1E0;
        }
        compoModelParams_800A2768.angle_24 = AdjustByLeftRight_8003D210(0x167, compoModelParams_800A2768.angle_24, 1, 0);
        compoModelParams_800A2768.angle_24 = AdjustByShoulderButtons_8003D198(0x168, compoModelParams_800A2768.angle_24, 10, 0);
        break;
    case 2:
        if (IsConfirmPressedP1_8003D380(1))
        {
            *c->pickTarget_1F8 = c->sel_1E0 + c->scroll_1E2;
            c->nextPage_1E4 = c->returnPage_1EC;
        }
        else if (IsCancelPressedP1_8003D41C(1))
        {
            c->nextPage_1E4 = c->returnPage_1EC;
        }
        m = compoPages_800A250C[c->returnPage_1EC].menu_0;
        DrawBobbingCursorHand_8003D090(m->x_C + (c->savedSel_1F4 % m->head_0.f.cols_0) * m->dx_8,
                     m->y_E + (c->savedSel_1F4 / m->head_0.f.cols_0) * m->dy_A + 6, 0, 0, 0);
        c->listSel_20C = c->sel_1E0;
        c->listScroll_208 = c->scroll_1E2;
        break;
    }
    switch (UpdateMenuCursor_8003D794(&c->cursor_1D8, 0))
    {
    case 4:
        c->page_1E8++;
        c->cursor_1D8 = compoPages_800A250C[c->page_1E8].menu_0->head_0.blk;
        c->sel_1E0 = 0;
        c->scroll_1E2 = 0;
        break;
    case 3:
        c->page_1E8--;
        c->cursor_1D8 = compoPages_800A250C[c->page_1E8].menu_0->head_0.blk;
        c->sel_1E0 = compoPages_800A250C[c->page_1E8].menu_0->head_0.f.count_2 - 1;
        c->scroll_1E2 = 0;
        break;
    }
    m = compoPages_800A250C[c->page_1E8].menu_0;
    DrawBobbingCursorHand_8003D090(m->x_C + (c->sel_1E0 % m->head_0.f.cols_0) * m->dx_8,
                 m->y_E + (c->sel_1E0 / m->head_0.f.cols_0) * m->dy_A + 6, 0, 0, 0);
    if (c->page_1E8 < 3)
    {
        if (c->page_1E8 >= 0)
        {
            p0[0] = 0x22;
            p0[1] = 0x1C;
            DrawText_8003E91C(1, compoParts_800A20EC[c->part_210[0]].text_0, p0, 0);
            p1[0] = 0x22;
            p1[1] = 0x26;
            DrawText_8003E91C(1, compoParts_800A20EC[c->part_210[1]].text_0, p1, 0);
            p2[0] = 0x22;
            p2[1] = 0x30;
            DrawText_8003E91C(1, compoParts_800A20EC[c->part_210[2]].text_0, p2, 0);
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
            DrawText_8003E91C(1, compoParts_800A20EC[c->enemy_22C].text_0, p0, 0);
            p1[0] = 0x92;
            p1[1] = 0x46;
            DrawNumberRightAlignedFont1_8003F264(p1, compoModelParams_800A2768.angle_24, 0);
            for (i = 0; i < 20; i++)
            {
                p0[0] = 0xCA;
                p0[1] = (i + 1) * 10 + 0x12;
                DrawText_8003E91C(1, compoParts_800A20EC[c->listScroll_208 + i].text_0, p0, 0);
            }
            for (j = 0; j < 3; j++)
            {
                DrawTextListWindow_800A2030(compoPages_800A250C[j].rect_8, compoPages_800A250C[j].texts_4, 0);
            }
        }
    }
    if (padPressed_8009194C & 0x800)
    {
        compoModelParams_800A2768.partCount_0 = 3;
        compoModelParams_800A2768.modelId_1C = 4;
        compoModelParams_800A2768.f20 = 0;
        compoModelParams_800A2768.enemyPart_28 = compoParts_800A20EC[c->enemy_22C].id_4;
        compoModelParams_800A2768.f2C = 0;
        compoModelParams_800A2768.part_4[0] = a = compoParts_800A20EC[c->part_210[0]].id_4;
        compoModelParams_800A2768.part_4[1] = b = compoParts_800A20EC[c->part_210[1]].id_4;
        compoModelParams_800A2768.part_4[2] = d = compoParts_800A20EC[c->part_210[2]].id_4;
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
        compoModelParams_800A2768.ratio_10[0] = (c->ratio_21C[0] << 12) / total;
        compoModelParams_800A2768.ratio_10[1] = (c->ratio_21C[1] << 12) / total;
        compoModelParams_800A2768.ratio_10[2] = (c->ratio_21C[2] << 12) / total;
        compoModelParams_800A2768.angle_24 += compoParts_800A20EC[c->enemy_22C].angle_8;
        if (compoModelParams_800A2768.angle_24 >= 0x168)
        {
            compoModelParams_800A2768.angle_24 -= 0x168;
        }
        c->state_0 = 1;
    }
}

extern void StartModelTask_80010850();
void TstCompoStartModel_800A1320(TstCompoWork* a)
{
    StartModelTask_80010850(&compoModelParams_800A2768);
    a->state_0 = 2;
}

extern int name_80010A10(int); // RunModelTask_80010A10 (declared void), its v0 is tested
extern void TstCompoInitBones_800A1AFC();
void TstCompoWaitModel_800A1354(TstCompoWork* a)
{
    if (name_80010A10(0))
    {
        a->model_4 = GetModelTaskModel_80010A44(0);
        TstCompoInitBones_800A1AFC(a);
        a->animCount_188 = -1;
        a->scaleStep_198 = 0;
        a->scaleId_19C = compoModelParams_800A2768.modelId_1C;
        a->state_0 = 3;
    }
}

void TstCompoWaitFiles_800A13B8(TstCompoWork* a)
{
    if (AreFileRequestsDone_80024DC4(a->model_4))
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
            a->anim_184 = a->nextAnim_18C;
        }
        a->state_0 = 4;
    }
}

extern void* memset(void* p, int c, unsigned int n);
extern void DrawAnimSkel_80046A58(void* a, void* b, void* c);
extern void DrawSpriteVtxQuadsGT4_800459E4(void* a, void* b, void* c, int d);
void TstCompoDrawModel_800A1468(TstCompoWork* c)
{
    VECTOR pos;
    char z[8];
    VECTOR scale;
    memset(z, 0, 8);
    pos.vx = c->pos_16C[0];
    pos.vy = c->pos_16C[1];
    pos.vz = c->pos_16C[2];
    pos.vy += 0xFA;
    c->scale_1A0 = GetModelBaseScale_80024E90(c->model_4, c->scaleId_19C);
    scale.vx = c->scale_1A0[0] + (c->scaleStep_198 << 12);
    scale.vy = c->scale_1A0[1] + (c->scaleStep_198 << 12);
    scale.vz = c->scale_1A0[2] + (c->scaleStep_198 << 12);
    c->f1A4 = GetModelBoneScale_80024EC8(c->model_4, c->scaleId_19C);
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
void TstCompoDrawBlend_800A15F4(TstCompoWork* c)
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
    c->scale_1A0 = GetModelBaseScale_80024E90(c->model_4, c->scaleId_19C);
    scale.vx = c->scale_1A0[0] + (c->scaleStep_198 << 12);
    scale.vy = c->scale_1A0[1] + (c->scaleStep_198 << 12);
    scale.vz = c->scale_1A0[2] + (c->scaleStep_198 << 12);
    c->f1A4 = GetModelBoneScale_80024EC8(c->model_4, c->scaleId_19C);
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
    c->blend_1FC += 0x88;
    c->frame_180++;
    if ((unsigned)c->blend_1FC >= 0x1000)
    {
        DrawAnimSkel_80046A58(&c->draw_1A8, name_800A2570, c->model_4->anims_54);
        DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
    }
    else
    {
        anim = &c->model_4->anims_54[c->blendAnim_204];
        DrawAnimSkelBlend_80047E28(&c->draw_1A8, c->draw_1A8.f10, anim, (unsigned)c->blendFrame_200 % anim->frameCount_0, 0x1000 - c->blend_1FC,
                     name_800A2570, c->model_4->anims_54);
        DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
    }
}

void TstCompoFrameInput_800A1804(TstCompoWork* c)
{
    if (c->paused_194)
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
        c->paused_194 = !c->paused_194;
    }
    if (c->paused_194 == 0)
    {
        if (padPressed_8009194C & 0x100)
        {
            c->scaleStep_198 = (c->scaleStep_198 + 1) & 3;
        }
        if (padPressed_8009194C & 0x10)
        {
            c->scaleId_19C = (c->scaleId_19C + 1) % 5;
        }
    }
}

void TstCompoViewInput_800A194C(TstCompoWork* c)
{
    if (padPressed_8009194C & 0x800)
    {
        c->state_0 = 6;
    }
    else if (padPressed_8009194C & 0x20)
    {
        c->state_0 = 5;
        c->blend_1FC = 0;
        c->nextAnim_18C = c->anim_184;
        c->blendFrame_200 = c->frame_180;
        c->blendAnim_204 = c->anim_184;
    }
}

void TstCompoAnimSelect_800A19A4(TstCompoWork* c)
{
    unsigned short pad = padRepeat_800918CC;
    if (pad & 0x1000)
    {
        int v = c->nextAnim_18C + 1;
        int t = c->animCount_188 - 1;
        c->nextAnim_18C = v;
        if (t < v)
        {
            c->nextAnim_18C = t;
        }
    }
    else if (pad & 0x4000)
    {
        int v = c->nextAnim_18C - 1;
        c->nextAnim_18C = v;
        if (v <= 0)
        {
            c->nextAnim_18C = 1;
        }
    }
    pad = padPressed_8009194C;
    if (pad & 0x20)
    {
        if (c->animLoaded_190)
        {
            FreeModelAnim_8002556C(c->model_4, c->anim_184);
            c->animLoaded_190 = 0;
        }
        if (c->model_4->animLoaded_44[c->nextAnim_18C] == 0)
        {
            c->animLoaded_190 = 1;
        }
        else
        {
            c->animLoaded_190 = 0;
        }
        if (c->animLoaded_190)
        {
            LoadModelAnim_80025440(c->model_4, c->nextAnim_18C, 0);
        }
        c->paused_194 = 0;
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
void TstCompoFreeModel_800A1AD0(TstCompoWork* a)
{
    FreeModelTask_8001098C(0);
    a->state_0 = 0;
}

extern TstCompoBone defaultBones_80079140[];
extern void SetBoneGroupFlags_80019B14(void* p, char* a1, char* a2);
void TstCompoInitBones_800A1AFC(TstCompoWork* a)
{
    int i;
    char* r;
    for (i = 0; defaultBones_80079140[i].s0 >= 0; i++)
    {
        a->bones_C[i] = defaultBones_80079140[i];
    }
    a->bones_C[i] = defaultBones_80079140[i];
    r = GetModelBoneGroupLevels_80024F00(a->model_4, compoModelParams_800A2768.modelId_1C);
    SetBoneGroupFlags_80019B14(a->bones_C, r, GetModelBoneGroupFlags_80024F38(a->model_4, compoModelParams_800A2768.modelId_1C));
}

// Matched
void TstCompoResetCamera_800A1BE0(TstCompoWork* a)
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
        TstCompoResetCamera_800A1BE0(a);
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
            TstCompoResetCamera_800A1BE0(a);
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
extern int cameraEye_8008D600[];
extern short cameraRot_8008D4C8[];
extern unsigned char backColor_8008D460[];
extern short screenOffset_8008D474[];
extern int geomScreenDistance_8008B548;
extern void SetGteLightAndCamera_8004D0E8();
extern TstCompoMat dword_8007C2EC;
extern TstCompoMat dword_8007C30C;
extern TstCompoMat lightMatrix_80087114;
extern TstCompoMat colorMatrix_80087134;
void SetCameraLookAt_800A1E68(TstCompoWork* c)
{
    int v[3];
    int yaw;
    cameraEye_8008D600[0] = c->eye_154[0];
    cameraEye_8008D600[1] = c->eye_154[1];
    cameraEye_8008D600[2] = c->eye_154[2];
    v[0] = c->at_160[0] - c->eye_154[0];
    v[1] = c->at_160[1] - c->eye_154[1];
    v[2] = c->at_160[2] - c->eye_154[2];
    yaw = ratan2_8003B548(v[0], v[2]);
    cameraRot_8008D4C8[1] = -yaw;
    cameraRot_8008D4C8[0] = ratan2_8003B548(v[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(v[0], v[2])));
    cameraRot_8008D4C8[2] = 0;
    backColor_8008D460[0] = 0x40;
    backColor_8008D460[1] = 0x40;
    backColor_8008D460[2] = 0x40;
    screenOffset_8008D474[0] = 0;
    screenOffset_8008D474[1] = 0;
    geomScreenDistance_8008B548 = 0xA0;
    lightMatrix_80087114 = dword_8007C2EC;
    colorMatrix_80087134 = dword_8007C30C;
    SetGteLightAndCamera_8004D0E8();
}

// Matched
int TstCompoMain_800A200C()
{
    DrawIntroMovie_8001AF64(tstCompoTaskList_800A2560);
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
        while (e[i].text_4)
        {
            t.pos[0] = e[i].x_0;
            t.pos[1] = e[i].y_2;
            DrawText_8003E91C(1, e[i].text_4, t.pos, idx);
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

TstCompoPart compoParts_800A20EC[48] = {
    { (int)asc_800A0788, 12, 0, 29 },
    { (int)asc_800A077C, 13, 0, 192, 1 },
    { (int)asc_800A076C, 14, 0, 0x162, 2 },
    { (int)asc_800A0760, 18, 0, 118, 3 },
    { (int)asc_800A0754, 19, 0, 14, 4 },
    { (int)asc_800A0748, 20, 0, 200, 5 },
    { (int)asc_800A0738, 24, 0, 0x121, 6 },
    { (int)asc_800A0728, 25, 0, 31, 7 },
    { (int)asc_800A0718, 26, 0, 136, 8 },
    { (int)asc_800A070C, 27, 0, 72, 9 },
    { (int)asc_800A0700, 28, 0, 0x11E, 10 },
    { (int)asc_800A06F4, 29, 0, 230, 11 },
    { (int)asc_800A06E8, 31, 0, 56, 12 },
    { (int)asc_800A06DC, 32, 0, 56, 13 },
    { (int)asc_800A06D0, 33, 0, 56, 14 },
    { (int)asc_800A06C0, 41, 0, 15, 15 },
    { (int)asc_800A06B4, 42, 0, 100, 16 },
    { (int)asc_800A06A4, 43, 0, 218, 17 },
    { (int)asc_800A0698, 76, 0, 234, 18 },
    { (int)asc_800A068C, 77, 0, 53, 19 },
    { (int)asc_800A067C, 78, 0, 184, 20 },
    { (int)asc_800A0674, 1, 0, 36, 21 },
    { (int)asc_800A066C, 23, 0, 0x105, 22 },
    { (int)asc_800A0660, 52, 0, 72, 23 },
    { (int)asc_800A0658, 61, 0, 144, 24 },
    { (int)asc_800A064C, 64, 0, 111, 25 },
    { (int)asc_800A0644, 67, 0, 211, 26 },
    { (int)asc_800A063C, 70, 0, 43, 27 },
    { (int)asc_800A0630, 81, 0, 186, 28 },
    { (int)asc_800A0624, 93, 0, 0x103, 29 },
    { (int)asc_800A061C, 98, 0, 61, 30 },
    { (int)asc_800A0614, 101, 0, 183, 31 },
    { (int)asc_800A060C, 34, 0, 206, 32 },
    { (int)asc_800A0600, 35, 0, 227, 34 },
    { (int)asc_800A05F4, 68, 0, 28, 33 },
    { (int)asc_800A05E8, 82, 0, 80, 35 },
    { (int)asc_800A05D8, 0, 0, 0, 36 },
    { (int)asc_800A05CC, 69, 0, 0, 37 },
    { (int)a0_800A05C8, 83, 0, 0, 201 },
    { (int)a1_800A05C4, 84, 0, 0, 202 },
    { (int)a2_800A05C0, 85, 0, 0, 203 },
    { (int)a3_800A05BC, 86, 0, 0, 204 },
    { (int)a4_800A05B8, 87, 0, 0, 205 },
    { (int)a5_800A05B4, 88, 0, 0, 206 },
    { (int)a6_800A05B0, 89, 0, 0, 207 },
    { (int)a7_800A05AC, 90, 0, 0, 208 },
    { (int)a8_800A05A8, 91, 0, 0, 209 },
    { (int)a9_800A05A4, 92, 0, 0, 210 },
};
int compoTexts0_800A24AC[4] = { 0x120022, (int)aNAMERATE_800A0798 };
int compoTexts1_800A24BC[4] = { 0x3C0022, (int)aTEXHANGL_800A07B8 };
int compoTexts2_800A24CC[4] = { 0x1200CA, (int)aENEMY_800A07D8 };
int compoMenu0_800A24DC[4] = { 0x30001, 0x200003, 0xA0000, 0x1A0022 };
int compoMenu1_800A24EC[4] = { 0x10001, 0x100001, 0xA0000, 0x440022 };
int compoMenu2_800A24FC[4] = { 0x140001, 0x400030, 0xA0000, 0x1A00CA };
TstCompoPage compoPages_800A250C[3] = {
    { (void *)compoMenu0_800A24DC, (void *)compoTexts0_800A24AC, { 32, 16, 114, 42 } },
    { (void *)compoMenu1_800A24EC, (void *)compoTexts1_800A24BC, { 32, 58, 114, 22 } },
    { (void *)compoMenu2_800A24FC, (void *)compoTexts2_800A24CC, { 200, 16, 64, 212 } },
};
int tstCompoTaskDesc_800A2548[6] = { 1, 1, 0x230, 0, (int)TstCompoInit_800A0800 };
char tstCompoTaskList_800A2560[16] = { 184, 142, 7, 128, 128, 144, 7, 128, 72, 37, 10, 128 };
char name_800A2570[24] = { 0 };
char name_800A2588[480] = { 0 };
TstCompoModelParams compoModelParams_800A2768 = { 0 };
