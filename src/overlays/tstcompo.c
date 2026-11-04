// TSTCOMPO.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "model.h"
#include "tstcompo.h"


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
const char aPadoruka_800A05CC[] = "\203p\203h\203\213\203J"; // パドルカ
const char aArupataron_800A05D8[] = "\203A\203\213\203p\203^\203\215\203\223"; // アルパタロン
const char aSheriku_800A05E8[] = "\203V\203F\203\212\203N"; // シェリク
const char aRashababa_800A05F4[] = "\203\211\203V\203\203\203o\203o"; // ラシャババ
const char aTuingo_800A0600[] = "\203g\203D\203C\203\223\203S"; // トゥインゴ
const char aEsupu_800A060C[] = "\203G\203X\203v"; // エスプ
const char aJiraru_800A0614[] = "\203W\203\211\203\213"; // ジラル
const char aYoruku_800A061C[] = "\203\210\203\213\203N"; // ヨルク
const char aUguramu_800A0624[] = "\203E\203O\203\211\203\200"; // ウグラム
const char aSurikaata_800A0630[] = "\203X\203\212\203J\201[\203^"; // スリカータ
const char aRigu_800A063C[] = "\203\212\203O"; // リグ
const char aOje_800A0644[] = "\203I\203W\203F"; // オジェ
const char aNeebui_800A064C[] = "\203l\201[\203u\203C"; // ネーブイ
const char aMuguu_800A0658[] = "\203\200\203O\201["; // ムグー
const char aMaayen_800A0660[] = "\203}\201[\203C\203F\203\223"; // マーイェン
const char aGinui_800A066C[] = "\203M\203k\203C"; // ギヌイ
const char aAsha_800A0674[] = "\203A\203V\203\203"; // アシャ
const char aMutsukishabu_800A067C[] = "\203\200\203c\203L\203V\203\203\203u"; // ムツキシャブ
const char aRashabu_800A068C[] = "\203\211\203V\203\203\203u"; // ラシャブ
const char aNushabu_800A0698[] = "\203k\203V\203\203\203u"; // ヌシャブ
const char aDoguruchuu_800A06A4[] = "\203h\203O\203\213\203`\203\205\201["; // ドグルチュー
const char aRadoruchu_800A06B4[] = "\203\211\203h\203\213\203`\203\205"; // ラドルチュ
const char aPataruchuu_800A06C0[] = "\203p\203^\203\213\203`\203\205\203E"; // パタルチュウ
const char aRadoimeru_800A06D0[] = "\203\211\203h\203C\203\201\203\213"; // ラドイメル
const char aSukuimeru_800A06DC[] = "\203X\203N\203C\203\201\203\213"; // スクイメル
const char aPataimeru_800A06E8[] = "\203p\203^\203C\203\201\203\213"; // パタイメル
const char aHirasagu_800A06F4[] = "\203q\203\211\203T\203O"; // ヒラサグ
const char aMasukohira_800A0700[] = "\203}\203X\203R\203q\203\211"; // マスコヒラ
const char aHiraruko_800A070C[] = "\203q\203\211\203\213\203R"; // ヒラルコ
const char aTerahanbuu_800A0718[] = "\203e\203\211\203n\203\223\203u\201["; // テラハンブー
const char aDoguhanbuu_800A0728[] = "\203h\203O\203n\203\223\203u\201["; // ドグハンブー
const char aMukahanbuu_800A0738[] = "\203\200\203J\203n\203\223\203u\201["; // ムカハンブー
const char aBerabansa_800A0748[] = "\203x\203\211\203o\203\223\203T"; // ベラバンサ
const char aDonguru_800A0754[] = "\203h\203\223\203O\203\213"; // ドングル
const char aRagidoguru_800A0760[] = "\203\211\203M\203h\203O\203\213"; // ラギドグル
const char aPatadorekku_800A076C[] = "\203p\203^\203h\203\214\203b\203N"; // パタドレック
const char aRadoreggu_800A077C[] = "\203\211\203h\203\214\203b\203O"; // ラドレッグ
const char aMaadoreggu_800A0788[] = "\203}\203A\203h\203\214\203b\203O"; // マアドレッグ
const char aNAMERATE_800A0798[] = "\202m\202`\202l\202d\201@\201@\201@\201@\201@\201@\202q\202`\202s\202d"; // NAME      RATE
const char aTEXHANGL_800A07B8[] = "\202s\202d\202w\201@\201@\201@\201@\201@\201@\202g\202`\202m\202f\202k"; // TEX      HANGL
const char aENEMY_800A07D8[] = "\202d\202m\202d\202l\202x"; // ENEMY

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
void SetDefaultCompoParams_800A0918()
{
    TstCompoModelParams* params = &compoModelParams_800A2768;
    params->partCount_0 = 3;
    params->part_4[0] = 1;
    params->part_4[1] = 0xC;
    params->part_4[2] = 0x29;
    params->ratio_10[0] = 0x555;
    params->ratio_10[1] = 0x555;
    params->ratio_10[2] = 0x555;
    params->modelId_1C = 4;
    params->texPart_20 = 0;
    params->angle_24 = 0;
    params->enemyPart_28 = 0x4C;
    params->main_2C = 0;
    params->vram_30 = dword_8007DC74;
}

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

// Matched
void TstCompoMenu_800A0AB8(TstCompoWork* c)
{
    short p0[4];
    short p1[4];
    short p2[4];
    short p3[4];
    short p4[4];
    short p5[4];
    TstCompoMenu* menu;
    int i;
    int j;
    int part0;
    int part1;
    int part2;
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
        menu = compoPages_800A250C[c->returnPage_1EC].menu_0;
        DrawBobbingCursorHand_8003D090(menu->x_C + (c->savedSel_1F4 % menu->head_0.f.cols_0) * menu->dx_8,
                     menu->y_E + (c->savedSel_1F4 / menu->head_0.f.cols_0) * menu->dy_A + 6, 0, 0, 0);
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
    menu = compoPages_800A250C[c->page_1E8].menu_0;
    DrawBobbingCursorHand_8003D090(menu->x_C + (c->sel_1E0 % menu->head_0.f.cols_0) * menu->dx_8,
                 menu->y_E + (c->sel_1E0 / menu->head_0.f.cols_0) * menu->dy_A + 6, 0, 0, 0);
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
        compoModelParams_800A2768.texPart_20 = 0;
        compoModelParams_800A2768.enemyPart_28 = compoParts_800A20EC[c->enemy_22C].id_4;
        compoModelParams_800A2768.main_2C = 0;
        compoModelParams_800A2768.part_4[0] = part0 = compoParts_800A20EC[c->part_210[0]].id_4;
        compoModelParams_800A2768.part_4[1] = part1 = compoParts_800A20EC[c->part_210[1]].id_4;
        compoModelParams_800A2768.part_4[2] = part2 = compoParts_800A20EC[c->part_210[2]].id_4;
        if (part0 == part1)
        {
            if (part1 == part2)
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
        else if (part0 == part2)
        {
            c->ratio_21C[0] += c->ratio_21C[2];
            c->ratio_21C[2] = 0;
        }
        else if (part1 == part2)
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

void TstCompoStartModel_800A1320(TstCompoWork* work)
{
    StartModelTask_80010850(&compoModelParams_800A2768);
    work->state_0 = 2;
}

void TstCompoWaitModel_800A1354(TstCompoWork* work)
{
    if (name_80010A10(0))
    {
        work->model_4 = GetModelTaskModel_80010A44(0);
        TstCompoInitBones_800A1AFC(work);
        work->animCount_188 = -1;
        work->scaleStep_198 = 0;
        work->scaleId_19C = compoModelParams_800A2768.modelId_1C;
        work->state_0 = 3;
    }
}

void TstCompoWaitFiles_800A13B8(TstCompoWork* work)
{
    if (AreFileRequestsDone_80024DC4(work->model_4))
    {
        if (work->animCount_188 <= 0)
        {
            int i;
            work->animCount_188 = work->model_4->animCount_3E;
            for (i = 0; i < work->animCount_188; i++)
            {
                if (work->model_4->animLoaded_44[i] != 0)
                {
                    work->anim_184 = i;
                    break;
                }
            }
        }
        else
        {
            work->anim_184 = work->nextAnim_18C;
        }
        work->state_0 = 4;
    }
}

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
    c->boneScale_1A4 = GetModelBoneScale_80024EC8(c->model_4, c->scaleId_19C);
    c->draw_1A8.anim_14 = &c->model_4->anims_54[c->anim_184];
    c->draw_1A8.ftg_0 = c->model_4->ftg_50;
    c->draw_1A8.pos_4 = &pos;
    c->draw_1A8.rot_8 = z;
    c->draw_1A8.bones_C = c->bones_C;
    c->draw_1A8.base_10 = c->boneScale_1A4;
    c->draw_1A8.frame_18 = (unsigned)c->frame_180 % c->draw_1A8.anim_14->frameCount_0;
    c->draw_1A8.drawMode_1C = 0;
    c->draw_1A8.bonePos_20 = compoBonePos_800A2588;
    c->draw_1A8.scale_24 = &scale;
    c->draw_1A8.ot_28 = pOT_8008D690;
    DrawAnimSkel_80046A58(&c->draw_1A8, compoLight_800A2570, c->model_4->anims_54);
    DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
}

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
    c->boneScale_1A4 = GetModelBoneScale_80024EC8(c->model_4, c->scaleId_19C);
    c->draw_1A8.anim_14 = &c->model_4->anims_54[3];
    c->draw_1A8.ftg_0 = c->model_4->ftg_50;
    c->draw_1A8.pos_4 = &pos;
    c->draw_1A8.rot_8 = z;
    c->draw_1A8.bones_C = c->bones_C;
    c->draw_1A8.base_10 = c->boneScale_1A4;
    c->draw_1A8.frame_18 = (unsigned)c->frame_180 % c->draw_1A8.anim_14->frameCount_0;
    c->draw_1A8.drawMode_1C = 0;
    c->draw_1A8.bonePos_20 = compoBonePos_800A2588;
    c->draw_1A8.scale_24 = &scale;
    c->draw_1A8.ot_28 = pOT_8008D690;
    c->blend_1FC += 0x88;
    c->frame_180++;
    if ((unsigned)c->blend_1FC >= 0x1000)
    {
        DrawAnimSkel_80046A58(&c->draw_1A8, compoLight_800A2570, c->model_4->anims_54);
        DrawSpriteVtxQuadsGT4_800459E4(c->bones_C, &c->model_4->mats_5C, pOT_8008D690, 0);
    }
    else
    {
        anim = &c->model_4->anims_54[c->blendAnim_204];
        DrawAnimSkelBlend_80047E28(&c->draw_1A8, c->draw_1A8.base_10, anim, (unsigned)c->blendFrame_200 % anim->frameCount_0, 0x1000 - c->blend_1FC,
                     compoLight_800A2570, c->model_4->anims_54);
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
        int last = c->animCount_188 - 1;
        c->nextAnim_18C = v;
        if (last < v)
        {
            c->nextAnim_18C = last;
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
void TstCompoFreeModel_800A1AD0(TstCompoWork* work)
{
    FreeModelTask_8001098C(0);
    work->state_0 = 0;
}

void TstCompoInitBones_800A1AFC(TstCompoWork* work)
{
    int i;
    char* levels;
    for (i = 0; defaultBones_80079140[i].s0 >= 0; i++)
    {
        work->bones_C[i] = defaultBones_80079140[i];
    }
    work->bones_C[i] = defaultBones_80079140[i];
    levels = GetModelBoneGroupLevels_80024F00(work->model_4, compoModelParams_800A2768.modelId_1C);
    SetBoneGroupFlags_80019B14(work->bones_C, levels, GetModelBoneGroupFlags_80024F38(work->model_4, compoModelParams_800A2768.modelId_1C));
}

// Matched
void TstCompoResetCamera_800A1BE0(TstCompoWork* work)
{
    work->dist_150 = 0x4B0;
    work->yaw_14C = 0;
    work->pos_16C[0] = 0;
    work->pos_16C[1] = 0;
    work->pos_16C[2] = 0;
    work->s178 = 0;
    work->s17A = 0;
    work->s17C = 0;
    work->at_160[1] = -0xFA;
    work->eye_154[1] = -0xFA;
}

void TstCompoCameraInput_800A1C14(TstCompoWork* work)
{
    if (padHeld_800918D0[0] & 0x8000)
    {
        work->yaw_14C -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x2000)
    {
        work->yaw_14C += 0x20;
    }
    if (padHeld_800918D0[0] & 0x1000)
    {
        work->eye_154[1] -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x4000)
    {
        work->eye_154[1] += 0x20;
    }
    work->eye_154[1] = work->eye_154[1] < -1000 ? -1000 : work->eye_154[1] < 1001 ? work->eye_154[1] : 1000;
    if ((padHeld_800918D0[0] & 0xC) == 0xC)
    {
        TstCompoResetCamera_800A1BE0(work);
    }
    else if (padHeld_800918D0[0] & 4)
    {
        work->dist_150 -= 0x20;
    }
    else if (padHeld_800918D0[0] & 8)
    {
        work->dist_150 += 0x20;
    }
    work->dist_150 = work->dist_150 < 100 ? 100 : work->dist_150 < 1201 ? work->dist_150 : 1200;
    work->eye_154[0] = work->dist_150 * sinTable_80084540[work->yaw_14C & 0xFFF] / 4096;
    work->eye_154[2] = work->dist_150 * sinTable_80084540[(work->yaw_14C + 0x400) & 0xFFF] / 4096;
    if (padHeld_800918D0[0] & 1)
    {
        if (padHeld_800918D0[0] & 2)
        {
            TstCompoResetCamera_800A1BE0(work);
        }
        else
        {
            work->at_160[1] -= 0x20;
        }
    }
    else if (padHeld_800918D0[0] & 2)
    {
        work->at_160[1] += 0x20;
    }
    work->at_160[1] = work->at_160[1] < -1000 ? -1000 : work->at_160[1] < 1001 ? work->at_160[1] : 1000;
    work->at_160[0] = 0;
    work->at_160[2] = 0;
    SetCameraLookAt_800A1E68(work);
}

void SetCameraLookAt_800A1E68(TstCompoWork* c)
{
    int dir[3];
    int yaw;
    cameraEye_8008D600[0] = c->eye_154[0];
    cameraEye_8008D600[1] = c->eye_154[1];
    cameraEye_8008D600[2] = c->eye_154[2];
    dir[0] = c->at_160[0] - c->eye_154[0];
    dir[1] = c->at_160[1] - c->eye_154[1];
    dir[2] = c->at_160[2] - c->eye_154[2];
    yaw = ratan2_8003B548(dir[0], dir[2]);
    cameraRot_8008D4C8[1] = -yaw;
    cameraRot_8008D4C8[0] = ratan2_8003B548(dir[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(dir[0], dir[2])));
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

void DrawTextListWindow_800A2030(short* rect, TstCompoEnt* texts, int ot)
{
    union
    {
        unsigned short pos[2];
        TstCompoWinStyle style;
    } scratch; // the text position, then the window style
    if (texts)
    {
        int i = 0;
        while (texts[i].text_4)
        {
            scratch.pos[0] = texts[i].x_0;
            scratch.pos[1] = texts[i].y_2;
            DrawText_8003E91C(1, texts[i].text_4, scratch.pos, ot);
            i++;
        }
    }
    if (rect)
    {
        scratch.style.colors_2 = 1;
        scratch.style.frame_3 = 1;
        scratch.style.color_0 = uiColor_8008B590;
        DrawWindow_80042460(rect, &scratch.style, pOT_8008D454 + ot, 0);
    }
}

TstCompoPart compoParts_800A20EC[48] = {
    { (int)aMaadoreggu_800A0788, 12, 0, 29 },
    { (int)aRadoreggu_800A077C, 13, 0, 192, 1 },
    { (int)aPatadorekku_800A076C, 14, 0, 0x162, 2 },
    { (int)aRagidoguru_800A0760, 18, 0, 118, 3 },
    { (int)aDonguru_800A0754, 19, 0, 14, 4 },
    { (int)aBerabansa_800A0748, 20, 0, 200, 5 },
    { (int)aMukahanbuu_800A0738, 24, 0, 0x121, 6 },
    { (int)aDoguhanbuu_800A0728, 25, 0, 31, 7 },
    { (int)aTerahanbuu_800A0718, 26, 0, 136, 8 },
    { (int)aHiraruko_800A070C, 27, 0, 72, 9 },
    { (int)aMasukohira_800A0700, 28, 0, 0x11E, 10 },
    { (int)aHirasagu_800A06F4, 29, 0, 230, 11 },
    { (int)aPataimeru_800A06E8, 31, 0, 56, 12 },
    { (int)aSukuimeru_800A06DC, 32, 0, 56, 13 },
    { (int)aRadoimeru_800A06D0, 33, 0, 56, 14 },
    { (int)aPataruchuu_800A06C0, 41, 0, 15, 15 },
    { (int)aRadoruchu_800A06B4, 42, 0, 100, 16 },
    { (int)aDoguruchuu_800A06A4, 43, 0, 218, 17 },
    { (int)aNushabu_800A0698, 76, 0, 234, 18 },
    { (int)aRashabu_800A068C, 77, 0, 53, 19 },
    { (int)aMutsukishabu_800A067C, 78, 0, 184, 20 },
    { (int)aAsha_800A0674, 1, 0, 36, 21 },
    { (int)aGinui_800A066C, 23, 0, 0x105, 22 },
    { (int)aMaayen_800A0660, 52, 0, 72, 23 },
    { (int)aMuguu_800A0658, 61, 0, 144, 24 },
    { (int)aNeebui_800A064C, 64, 0, 111, 25 },
    { (int)aOje_800A0644, 67, 0, 211, 26 },
    { (int)aRigu_800A063C, 70, 0, 43, 27 },
    { (int)aSurikaata_800A0630, 81, 0, 186, 28 },
    { (int)aUguramu_800A0624, 93, 0, 0x103, 29 },
    { (int)aYoruku_800A061C, 98, 0, 61, 30 },
    { (int)aJiraru_800A0614, 101, 0, 183, 31 },
    { (int)aEsupu_800A060C, 34, 0, 206, 32 },
    { (int)aTuingo_800A0600, 35, 0, 227, 34 },
    { (int)aRashababa_800A05F4, 68, 0, 28, 33 },
    { (int)aSheriku_800A05E8, 82, 0, 80, 35 },
    { (int)aArupataron_800A05D8, 0, 0, 0, 36 },
    { (int)aPadoruka_800A05CC, 69, 0, 0, 37 },
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
char compoLight_800A2570[24] = { 0 };
char compoBonePos_800A2588[480] = { 0 };
TstCompoModelParams compoModelParams_800A2768 = { 0 };
