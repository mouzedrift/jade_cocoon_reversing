// TSTMODEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "model.h"
#include "tstmodel.h"



int dword_800A05A0 SDATA = 16;
const char aMDLOUMG_800A05A4[] = "MDL_OUMG";
const char aMDLZIRA_800A05B0[] = "MDL_ZIRA";
const char aMDLTORI_800A05BC[] = "MDL_TORI";
const char aMDLSHABUC_800A05C8[] = "MDL_SHABU_C";
const char aMDLSHABUB_800A05D4[] = "MDL_SHABU_B";
const char aMDLOJE_800A05E0[] = "MDL_OJE";
const char aMDLNEBUI_800A05E8[] = "MDL_NEBUI";
const char aMDLMUGU_800A05F4[] = "MDL_MUGU";
const char aMDLLUCHC_800A0600[] = "MDL_LUCHC";
const char aMDLLUCHB_800A060C[] = "MDL_LUCHB";
const char aMDLKANI_800A0618[] = "MDL_KANI";
const char aMDLKAMERE_800A0624[] = "MDL_KAMERE";
const char aMDLIMELC_800A0630[] = "MDL_IMEL_C";
const char aMDLIMELB_800A063C[] = "MDL_IMEL_B";
const char aMDLHIRAC_800A0648[] = "MDL_HIRA_C";
const char aMDLHIRAB_800A0654[] = "MDL_HIRA_B";
const char aMDLHANBC_800A0660[] = "MDL_HANB_C";
const char aMDLHANBB_800A066C[] = "MDL_HANB_B";
const char aMDLDONGC_800A0678[] = "MDL_DONG_C";
const char aMDLDONGB_800A0684[] = "MDL_DONG_B";
const char aMDLDLEGC_800A0690[] = "MDL_DLEG_C";
const char aMDLDLEGB_800A069C[] = "MDL_DLEG_B";
const char aMDLGINU_800A06A8[] = "MDL_GINU";
const char aMDLDONG_800A06B4[] = "MDL_DONG";
const char aMDLHIRA_800A06C0[] = "MDL_HIRA";
const char aMDLTHRE_800A06CC[] = "MDL_THRE";
const char aMDLMAIE_800A06D8[] = "MDL_MAIE";
const char aMDLIMEL_800A06E4[] = "MDL_IMEL";
const char aMDLHANBA_800A06F0[] = "MDL_HANB_A";
const char aMDLDLEG_800A06FC[] = "MDL_DLEG";
const char aMDLSHABU_800A0708[] = "MDL_SHABU";
const char aMDLLUCH_800A0714[] = "MDL_LUCH";
const char aMDLUGURAM_800A0720[] = "MDL_UGURAM";
const char aMDLASHA_800A072C[] = "MDL_ASHA";
const char aMDLRIG_800A0738[] = "MDL_RIG";
const char aMDLYOLK_800A0740[] = "MDL_YOLK";
const char aMDLRIKE_800A074C[] = "MDL_RIKE";
const char aMDLNAGK_800A0758[] = "MDL_NAGK";
const char aMDLBSZZ_800A0764[] = "MDL_BSZZ";
const char aMDLBSWE_800A0770[] = "MDL_BSWE";
const char aMDLBSWS_800A077C[] = "MDL_BSWS";
const char aMDLBSFE_800A0788[] = "MDL_BSFE";
const char aMDLBSFS_800A0794[] = "MDL_BSFS";
const char aMDLBSGE_800A07A0[] = "MDL_BSGE";
const char aMDLBSGS_800A07AC[] = "MDL_BSGS";
const char aMDLYMI_800A07B8[] = "MDL_YMI";
const char aMDLYMKK_800A07C0[] = "MDL_YMKK";
const char aMDLYMTT_800A07CC[] = "MDL_YMTT";
const char aMDLYM_800A07D8[] = "MDL_YM";
const char aMDLNCHO_800A07E0[] = "MDL_NCHO";
const char aMDLNMUU_800A07EC[] = "MDL_NMUU";
const char aMDLNRAA_800A07F8[] = "MDL_NRAA";
const char aMDLKIKI_800A0804[] = "MDL_KIKI";
const char aMDLKORI_800A0810[] = "MDL_KORI";
const char aMDLDMA_800A081C[] = "MDL_DMA";
const char aMDLDC_800A0824[] = "MDL_DC";
const char aMDLDB_800A082C[] = "MDL_DB";
const char aMDLDA_800A0834[] = "MDL_DA";
const char aMDLYUME_800A083C[] = "MDL_YUME";
const char aMDLSOUJB_800A0848[] = "MDL_SOUJB";
const char aMDLSOUJ_800A0854[] = "MDL_SOUJ";
const char aMDLZIB_800A0860[] = "MDL_ZIB";
const char aMDLZOK_800A0868[] = "MDL_ZOK";
const char aMDLMNBN_800A0870[] = "MDL_MNBN";
const char aMDLHJI_800A087C[] = "MDL_HJI";
const char aMDLMOBC_800A0884[] = "MDL_MOBC";
const char aMDLMOBB_800A0890[] = "MDL_MOBB";
const char aMDLROUBC_800A089C[] = "MDL_ROUBC";
const char aMDLROUBB_800A08A8[] = "MDL_ROUBB";
const char aMDLROUBA_800A08B4[] = "MDL_ROUBA";
const char aMDLMCHO_800A08C0[] = "MDL_MCHO";
const char aMDLSDOG_800A08CC[] = "MDL_SDOG";
const char aMDLLUIA_800A08D8[] = "MDL_LUI_A";
const char aMDLLUI_800A08E4[] = "MDL_LUI";
const char aMDLMLEB_800A08EC[] = "MDL_MLEB";
const char aMDLMKEL_800A08F8[] = "MDL_MKEL";
const char aMDLFKEL_800A0904[] = "MDL_FKEL";
const char aMDLKEL_800A0910[] = "MDL_KEL";
const char aMDLMDOG_800A0918[] = "MDL_MDOG";
const char aMDLMOBA_800A0924[] = "MDL_MOBA";
const char aMDLMABF_800A0930[] = "MDL_MABF";
const char aMDLMABE_800A093C[] = "MDL_MABE";
const char aMDLMABD_800A0948[] = "MDL_MABD";
const char aMDLMABC_800A0954[] = "MDL_MABC";
const char aMDLMABB_800A0960[] = "MDL_MABB";
const char aMDLMABA_800A096C[] = "MDL_MABA";
const char aMDLGAR_800A0978[] = "MDL_GAR";
const char aMDLLEB2_800A0980[] = "MDL_LEB2";
const char aMDLLEBANT_800A098C[] = "MDL_LEBANT";
const int dword_800A0998 = 0;

void TstModelInit_800A09C0(EventEntry* task, TstModelWork* c)
{
    int i;
    c->state_0 = 0;
    c->sel_4 = 0;
    c->scroll_8 = 0;
    c->boneSel_C = 0;
    c->boneScroll_10 = 0;
    c->models_14 = 0;
    c->loadSel_20 = 0;
    c->holdTimer_172 = 0;
    c->count_1C = 0;
    if (tstModels_800A33B0[0].modelId_0 >= 0)
    {
        do
        {
            i = c->count_1C + 1;
            c->count_1C = i;
        } while (tstModels_800A33B0[i].modelId_0 >= 0);
    }
    c->paused_1B8 = 0;
    c->anim_1A8 = 0;
    c->animLoaded_1B4 = 0;
    c->frame_1A4 = 0;
    c->scaleStep_1BC = 0;
    TstModelResetCamera_800A0BC0(c);
    drawEnvRed_8008D448[0] = 0x40;
    drawEnvRed_8008D448[1] = 0x40;
    drawEnvRed_8008D448[2] = 0x80;
    task->cb_8 = (EventEntryFn)TstModelTask_800A0A8C;
}

void TstModelTask_800A0A8C(EventEntry* task, TstModelWork* c)
{
    switch (c->state_0)
    {
    case 0:
        TstModelSelectModel_800A0C00(c);
        break;
    case 1:
        TstModelLoadModel_800A0EC8(c);
        break;
    case 2:
        TstModelWaitModel_800A0F20(c);
        break;
    case 3:
        TstModelCameraInput_800A104C(c);
        TstModelDrawModel_800A1428(c);
        TstModelFrameInput_800A18F4(c);
        break;
    case 4:
        TstModelDrawModel_800A1428(c);
        TstModelAnimSelect_800A17B8(c);
        break;
    case 5:
        TstModelDrawModel_800A1428(c);
        TstModelBoneEdit_800A1614(c);
        break;
    case 6:
        TstModelFreeModel_800A19E4(c);
        break;
    }
    if ((unsigned)(c->state_0 - 1) >= 2 && c->state_0 != 6 && (padHeld_800918D0[0] & 4) && (padHeld_800918D0[0] & 1) &&
        (padHeld_800918D0[0] & 0x90A) == 0x90A)
    {
        TstModelFreeModel_800A19E4(c);
        bStopDrawingMovie_8008D45C = 1;
    }
}
const TstModelBone dword_800A09B8 = { 0x8080, 128, 0x8080 };

// Matched
void TstModelResetCamera_800A0BC0(TstModelWork* work)
{
    work->dist_174 = 0x4B0;
    work->yaw_170 = 0;
    work->posX_190 = 0;
    work->posY_194 = 0;
    work->posZ_198 = 0;
    work->s19C = 0;
    work->s19E = 0;
    work->s1A0 = 0;
    work->rot_1F0.vx = 0;
    work->rot_1F0.vy = 0;
    work->rot_1F0.vz = 0;
    work->atY_188 = -0xFA;
    work->eyeY_17C = -0xFA;
}

void TstModelSelectModel_800A0C00(TstModelWork* c)
{
    TstGridCursor cur;
    TstModelBone tmp;
    int i;
    TstModelTbl* tbl;
    cur.cols_8 = 1;
    cur.flags_0 = 0;
    cur.unused_4 = 0;
    cur.rows_A = 0x12;
    cur.sel_6 = c->sel_4;
    cur.count_C = c->count_1C;
    cur.scroll_E = c->scroll_8;
    UpdateGridCursor_800A1D70(&cur);
    if (c->sel_4 != cur.sel_6 || c->scroll_8 != (short)cur.scroll_E)
    {
        PlaySfx_80031494(0x7F);
    }
    c->sel_4 = cur.sel_6;
    c->scroll_8 = (short)cur.scroll_E;
    for (i = 0; i < 0x12; i++)
    {
        if (c->sel_4 == i)
        {
            tmp = dword_800A09B8;
        }
    }
    if (padRepeat_800918CC[0] & 0x2000)
    {
        c->loadSel_20++;
    }
    else if (padRepeat_800918CC[0] & 0x8000)
    {
        c->loadSel_20--;
    }
    c->loadSel_20 = c->loadSel_20 < 0 ? 0 : c->loadSel_20 < 0xC0 ? c->loadSel_20 : 0xBF;
    tbl = tstModels_800A33B0;
    if (padPressed_8009194C[0] & 0x20)
    {
        c->paused_1B8 = 0;
        c->modelId_24 = tbl[c->scroll_8 + c->sel_4].modelId_0;
        c->anim_1A8 = -1;
        c->animCount_1AC = -1;
        c->scaleStep_1BC = 0;
        c->paused_1B8 = 0;
        c->animLoaded_1B4 = 0;
        c->state_0 = 1;
        for (i = 0; tstModels_800A33B0[c->scroll_8 + c->sel_4].bones_4[i].s0 >= 0; i++)
        {
            c->bones_28[i] = tstModels_800A33B0[c->scroll_8 + c->sel_4].bones_4[i];
        }
        c->bones_28[i] = tstModels_800A33B0[c->scroll_8 + c->sel_4].bones_4[i];
    }
}

void TstModelLoadModel_800A0EC8(TstModelWork* work)
{
    InitModelList_80024ADC(&work->models_14, modelLoaderVram_8007DC70, 1);
    LoadModel_80025200(work->models_14, work->modelId_24, work->loadSel_20, 2, 0);
    work->loadSel_20 = 0;
    work->state_0 = 2;
}

void TstModelWaitModel_800A0F20(TstModelWork* work)
{
    Model* model = AcquireModel_80024D70(work->models_14, work->modelId_24);
    if (AreFileRequestsDone_80024DC4(model))
    {
        if (work->modelId_24 == 0x28 && work->anim_1A8 == -1)
        {
            work->anim_1A8 = 0;
            SaveModelFtgs_80024FFC(model, levantFtgs_800A37E8);
            LoadModelAltFtgs_80025974(model, 5, 0);
            return;
        }
        if (work->animCount_1AC <= 0)
        {
            int i = 0;
            int found = 0;
            work->animCount_1AC = model->animCount_3E;
            for (; i < work->animCount_1AC; i++)
            {
                if (model->animLoaded_44[i] != 0)
                {
                    work->anim_1A8 = i;
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                work->nextAnim_1B0 = 0;
                LoadModelAnim_80025440(model, 0, 0);
                return;
            }
        }
        else
        {
            work->anim_1A8 = work->nextAnim_1B0;
        }
        ApplyModelFtgSwaps_80025C38(model, 1);
        work->state_0 = 3;
    }
}

void TstModelCameraInput_800A104C(TstModelWork* c)
{
    MATRIX rot;
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
    RotMatrixZYX_8004D5CC(&c->rot_1F0, &rot);
    MulMatrix0(&lightDirs_800A1E84, &rot, &lightMatrix_80087114);
    PopMatrix();
    colorMatrix_80087134 = lightColors_800A1EA4;
    if (padHeld_800918D0[0] & 0x8000)
    {
        c->yaw_170 -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x2000)
    {
        c->yaw_170 += 0x20;
    }
    if (padHeld_800918D0[0] & 0x1000)
    {
        c->eyeY_17C -= 0x20;
    }
    else if (padHeld_800918D0[0] & 0x4000)
    {
        c->eyeY_17C += 0x20;
    }
    c->eyeY_17C = c->eyeY_17C < -500 ? -500 : c->eyeY_17C < 501 ? c->eyeY_17C : 500;
    if ((padHeld_800918D0[0] & 0xC) == 0xC)
    {
        TstModelResetCamera_800A0BC0(c);
    }
    else if (padHeld_800918D0[0] & 4)
    {
        c->dist_174 -= 0x20;
    }
    else if (padHeld_800918D0[0] & 8)
    {
        c->dist_174 += 0x20;
    }
    c->dist_174 = c->dist_174 < 100 ? 100 : c->dist_174 < 1201 ? c->dist_174 : 1200;
    c->eyeX_178 = c->dist_174 * sinTable_80084540[c->yaw_170 & 0xFFF] / 4096;
    c->eyeZ_180 = c->dist_174 * sinTable_80084540[(c->yaw_170 + 0x400) & 0xFFF] / 4096;
    if (padHeld_800918D0[0] & 1)
    {
        if (padHeld_800918D0[0] & 2)
        {
            TstModelResetCamera_800A0BC0(c);
        }
        else
        {
            c->atY_188 -= 0x20;
        }
    }
    else if (padHeld_800918D0[0] & 2)
    {
        c->atY_188 += 0x20;
    }
    c->atY_188 = c->atY_188 < -500 ? -500 : c->atY_188 < 501 ? c->atY_188 : 500;
    c->atX_184 = 0;
    c->atZ_18C = 0;
    SetCameraLookAt_800A1A24(c);
    if (padPressed_8009194C[0] & 0x800)
    {
        c->state_0 = 6;
    }
    else if (padPressed_8009194C[0] & 0x20)
    {
        c->state_0 = 4;
        c->nextAnim_1B0 = c->anim_1A8;
    }
    else if (padHeld_800918D0[0] & 0x40)
    {
        if (++c->holdTimer_172 >= 30)
        {
            c->boneSel_C = 0;
            c->boneScroll_10 = 0;
            c->state_0 = 5;
            c->holdTimer_172 = 0;
        }
    }
}

void TstModelDrawModel_800A1428(TstModelWork* c)
{
    VECTOR pos;
    char z[8];
    VECTOR scale;
    Model* model;
    ModelAnim* anim;
    memset(z, 0, 8);
    model = AcquireModel_80024D70(c->models_14, c->modelId_24);
    c->model_18 = model;
    anim = &model->anims_54[c->anim_1A8];
    GetAnimRootMotion_8004D288(&pos, anim, (unsigned)c->frame_1A4 % anim->frameCount_0);
    pos.vx /= anim->divisor_8;
    pos.vy /= anim->divisor_8;
    pos.vz /= anim->divisor_8;
    pos.vy += 0xFA;
    scale.vx = (c->scaleStep_1BC + 1) << 12;
    scale.vy = (c->scaleStep_1BC + 1) << 12;
    scale.vz = (c->scaleStep_1BC + 1) << 12;
    c->draw_1C0.anim_14 = &model->anims_54[c->anim_1A8];
    c->draw_1C0.ftg_0 = model->ftg_50;
    c->draw_1C0.pos_4 = &pos;
    c->draw_1C0.rot_8 = z;
    c->draw_1C0.bones_C = c->bones_28;
    c->draw_1C0.base_10 = boneScales_800A3268;
    c->draw_1C0.frame_18 = (unsigned)c->frame_1A4 % c->draw_1C0.anim_14->frameCount_0;
    c->draw_1C0.drawMode_1C = 0;
    c->draw_1C0.bonePos_20 = modelBonePos_800A3804;
    c->draw_1C0.scale_24 = &scale;
    c->draw_1C0.ot_28 = pOT_8008D690;
    PlayAnimFrameSfx_8001C364(model, c->anim_1A8, c->draw_1C0.frame_18);
    DrawAnimSkel_80046A58(&c->draw_1C0, modelLight_800A1EE8, 0);
    DrawSpriteVtxQuadsGT4_800459E4(c->bones_28, &model->mats_5C, pOT_8008D690, 0);
}

void TstModelBoneEdit_800A1614(TstModelWork* c)
{
    TstGridCursor cur;
    TstModelBone tmp;
    int n;
    int i;
    unsigned short pad;
    for (n = 0; c->bones_28[n].s0 >= 0; n++)
    {
    }
    cur.cols_8 = 1;
    cur.flags_0 = 0;
    cur.unused_4 = 0;
    cur.rows_A = 6;
    cur.sel_6 = c->boneSel_C;
    cur.count_C = n;
    cur.scroll_E = c->boneScroll_10;
    UpdateGridCursor_800A1D70(&cur);
    if (c->boneSel_C != cur.sel_6 || c->boneScroll_10 != (short)cur.scroll_E)
    {
        PlaySfx_80031494(0x7F);
    }
    c->boneSel_C = cur.sel_6;
    c->boneScroll_10 = (short)cur.scroll_E;
    for (i = 0; i < 6; i++)
    {
        tmp = dword_800A09B8;
    }
    pad = padPressed_8009194C[0];
    if (pad & 0x20)
    {
        if (c->bones_28[c->boneScroll_10 + c->boneSel_C].flags & 2)
        {
            c->bones_28[c->boneScroll_10 + c->boneSel_C].flags &= ~2;
        }
        else
        {
            c->bones_28[c->boneScroll_10 + c->boneSel_C].flags |= 2;
        }
    }
    else if (pad & 0x10)
    {
        if (c->bones_28[c->boneScroll_10 + c->boneSel_C].flags & 0x10)
        {
            c->bones_28[c->boneScroll_10 + c->boneSel_C].flags &= ~0x10;
        }
        else
        {
            c->bones_28[c->boneScroll_10 + c->boneSel_C].flags |= 0x10;
        }
    }
    else if (pad & 0x40)
    {
        c->holdTimer_172 = 0;
        c->state_0 = 3;
    }
}

void TstModelAnimSelect_800A17B8(TstModelWork* c)
{
    unsigned short pad;
    Model* model;
    if (padRepeat_800918CC[0] & 0x4000)
    {
        c->nextAnim_1B0++;
    }
    else if (padRepeat_800918CC[0] & 0x1000)
    {
        if (--c->nextAnim_1B0 < 0)
        {
            c->nextAnim_1B0 = c->animCount_1AC - 1;
        }
    }
    c->nextAnim_1B0 = (unsigned)c->nextAnim_1B0 % c->animCount_1AC;
    pad = padPressed_8009194C[0];
    if (pad & 0x20)
    {
        model = AcquireModel_80024D70(c->models_14, c->modelId_24);
        if (c->animLoaded_1B4)
        {
            FreeModelAnim_8002556C(model, c->anim_1A8);
            c->animLoaded_1B4 = 0;
        }
        if (model->animLoaded_44[c->nextAnim_1B0] == 0)
        {
            c->animLoaded_1B4 = 1;
        }
        else
        {
            c->animLoaded_1B4 = 0;
        }
        if (c->animLoaded_1B4)
        {
            LoadModelAnim_80025440(model, c->nextAnim_1B0, 0);
        }
        c->paused_1B8 = 0;
        c->frame_1A4 = 0;
        c->state_0 = 2;
    }
    else if (pad & 0x40)
    {
        c->holdTimer_172 = 0;
        c->state_0 = 3;
    }
}

void TstModelFrameInput_800A18F4(TstModelWork* c)
{
    if (c->paused_1B8)
    {
        if (padRepeat_800918CC[0] & 0x80)
        {
            c->frame_1A4++;
        }
        else if (padRepeat_800918CC[0] & 0x10)
        {
            if (--c->frame_1A4 < 0)
            {
                c->frame_1A4 = c->draw_1C0.anim_14->frameCount_0 - 1;
            }
        }
        c->frame_1A4 = c->frame_1A4 % c->draw_1C0.anim_14->frameCount_0;
    }
    else
    {
        c->frame_1A4++;
    }
    if (padPressed_8009194C[0] & 0x40)
    {
        c->holdTimer_172 = 0;
        c->paused_1B8 = !c->paused_1B8;
    }
    if (padPressed_8009194C[0] & 0x100)
    {
        c->scaleStep_1BC = (c->scaleStep_1BC + 1) & 3;
    }
}

void TstModelFreeModel_800A19E4(TstModelWork* work)
{
    if (work->models_14)
    {
        FreeModelList_80024BB0(&work->models_14);
    }
    work->models_14 = 0;
    work->state_0 = 0;
}

void SetCameraLookAt_800A1A24(TstModelWork* c)
{
    int dir[3];
    int yaw;
    cameraEye_8008D600[0] = c->eyeX_178;
    cameraEye_8008D600[1] = c->eyeY_17C;
    cameraEye_8008D600[2] = c->eyeZ_180;
    dir[0] = c->atX_184 - c->eyeX_178;
    dir[1] = c->atY_188 - c->eyeY_17C;
    dir[2] = c->atZ_18C - c->eyeZ_180;
    yaw = ratan2_8003B548(dir[0], dir[2]);
    cameraRot_8008D4C8.vy = -yaw;
    cameraRot_8008D4C8.vx = ratan2_8003B548(dir[1], ISqrt_8003B918(LengthSquared2D_8003B8BC(dir[0], dir[2])));
    cameraRot_8008D4C8.vz = 0;
    backColor_8008D460[0] = 0x40;
    backColor_8008D460[1] = 0x40;
    backColor_8008D460[2] = 0x40;
    screenOffset_8008D474[0] = 0;
    screenOffset_8008D474[1] = 0;
    geomScreenDistance_8008B548 = 0xA0;
    SetGteLightAndCamera_8004D0E8();
}

// Matched
enum GameStates TstModelMain_800A1B24(void)
{
    DrawIntroMovie_8001AF64(tstModelTaskList_800A1EDC);
    return 6;
}

int MoveGridCursor_800A1B48(TstGridCursor* cursor)
{
    int idx = 0;
    if (cursor->sel_6 < 0)
    {
        cursor->sel_6 = 0;
    }
    if (padRepeat_800918CC[idx] & 0x2000)
    {
        if (cursor->sel_6 % cursor->cols_8 == cursor->cols_8 - 1)
        {
            return 1;
        }
        cursor->sel_6++;
    }
    if (padRepeat_800918CC[idx] & 0x8000)
    {
        if (cursor->sel_6 % cursor->cols_8 == 0)
        {
            return 2;
        }
        cursor->sel_6--;
    }
    if (padRepeat_800918CC[idx] & 0x1000)
    {
        if (cursor->sel_6 < cursor->cols_8)
        {
            return 3;
        }
        cursor->sel_6 -= cursor->cols_8;
    }
    if (padRepeat_800918CC[idx] & 0x4000)
    {
        if (cursor->sel_6 > cursor->cols_8 * (cursor->rows_A - 1) - 1)
        {
            return 4;
        }
        cursor->sel_6 = cursor->sel_6 + cursor->cols_8;
    }
    return 0;
}

void WrapGridCursor_800A1CAC(TstGridCursor* cursor, int dir)
{
    if (cursor->flags_0 & gridWrapMask_800A37F4[dir - 1])
    {
        if ((cursor->flags_0 & 1) && (unsigned)(dir - 1) < 2)
        {
            cursor->sel_6 += gridWrapSign_800A37FC[dir - 1] * (cursor->cols_8 - 1);
        }
        else if ((cursor->flags_0 & 2) && (unsigned)(dir - 3) < 2)
        {
            cursor->sel_6 += gridWrapSign_800A37FC[dir - 1] * cursor->cols_8 * (cursor->rows_A - 1);
        }
    }
}

int UpdateGridCursor_800A1D70(TstGridCursor* cursor)
{
    int prevSel = cursor->sel_6;
    int dir = MoveGridCursor_800A1B48(cursor);
    unsigned short scroll = cursor->scroll_E;
    int ts = scroll << 16;
    if (dir == 3)
    {
        if ((ts >> 16) >= cursor->cols_8)
        {
            cursor->scroll_E = scroll - cursor->cols_8;
            PlaySfx_80031494(0x7F);
            return 8;
        }
    }
    else if (dir == 4)
    {
        if ((ts >> 16) < cursor->count_C - cursor->cols_8 * cursor->rows_A)
        {
            cursor->scroll_E = scroll + cursor->cols_8;
            PlaySfx_80031494(0x7F);
            return 7;
        }
    }
    WrapGridCursor_800A1CAC(cursor, dir);
    cursor->scroll_E = AdjustByShoulderButtons_8003D198(cursor->count_C - cursor->cols_8 * cursor->rows_A + 1, (short)cursor->scroll_E, cursor->cols_8 * cursor->rows_A, 0);
    if (prevSel != cursor->sel_6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 9;
}

MATRIX lightDirs_800A1E84 = {
    {
        { 0x7FC, -0xAA6, 0x8DE },
        { -0x7FC, 0xAA6, -0x8DE },
        { -0x7FC, -0xAA6, -0x8DE },
    },
};
TstModelMat lightColors_800A1EA4 = { { 0x8001000, 0x10000800, 0x8000800, 0x8001000, 0x800 } };
int tstModelTaskDesc_800A1EC4[6] = { 1, 1, 0x1F8, 0, (int)TstModelInit_800A09C0 };
char tstModelTaskList_800A1EDC[12] = { 184, 142, 7, 128, 196, 30, 10, 128 };
char modelLight_800A1EE8[24] = { 0 };
int minionBones_800A1F00[52] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x6070004, 0xB0007,
    0x7080005, 0xB0008, 0x2090003, 0xB0009, 0x90A0004, 0xB000A, 0xA0B0005, 0xB000B,
    0x20C0003, 0xB000C, 0xC0D0004, 0xB000D, 0x20E0003, 0xB000E, 0xE0F0004, 0xB000F,
    0x100002, 0xB0010, 0x10110003, 0xB0011, 0x11120004, 0xB0012, 0x12130005, 0xB0013,
    0x10140003, 0xB0014, 0x14150004, 0xB0015, 0x15160005, 0xB0016, 0x10170003, 0xB0017,
    0x17180004, 0xB0018, -1, -1,
};
int humanBones_800A1FD0[46] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007,
    0x2080003, 0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B,
    0xB0C0006, 0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F,
    0xF100003, 0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, 0xF130003, 0xB0013,
    0x13140004, 0xB0014, 0x14150005, 0xB0015, -1, -1,
};
int roubBones_800A2088[34] = {
    0, 0, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007,
    0x2080003, 0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B,
    0xB0C0006, 0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F,
    -1, -1,
};
int mchoBones_800A2110[48] = {
    0, 0, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007,
    0x2080003, 0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B,
    0xB0C0006, 0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0xE0F0005, 0xB000F,
    0x1100002, 0xB0010, 0x10110003, 0xB0011, 0x11120004, 0xB0012, 0x12130005, 0xB0013,
    0x10140003, 0xB0014, 0x14150004, 0xB0015, 0x15160005, 0xB0016, -1, -1,
};
int mobBones_800A21D0[46] = {
    0, 0, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007,
    0x2080003, 0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B,
    0xB0C0006, 0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F,
    0xF100003, 0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, 0xF130003, 0xB0013,
    0x13140004, 0xB0014, 0x14150005, 0xB0015, -1, -1,
};
int mnbnBones_800A2288[40] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060006, 0xB0006, 0x2070003, 0xB0007,
    0x7080004, 0xB0008, 0x8090005, 0xB0009, 0x20A0003, 10, 0xA0B0004, 0xB000B,
    0x10C0002, 0xB000C, 0xC0D0003, 0xB000D, 0xD0E0004, 0xB000E, 0xE0F0005, 0xB000F,
    0xC100003, 0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, -1, -1,
};
int zibBones_800A2328[40] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x6070004, 0xB0007,
    0x7080005, 0xB0008, 0x2090003, 9, 0x90A0004, 0xB000A, 0x10B0002, 0xB000B,
    0xB0C0003, 0xB000C, 0xC0D0004, 0xB000D, 0xD0E0005, 0xB000E, 0xB0F0003, 0xB000F,
    0x10100004, 0xB0010, 0x11110005, 0xB0011, 0x2120003, 0xB0012, -1, -1,
};
int soujBones_800A23C8[30] = {
    0, 0, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060006, 0xB0006, 0x2070003, 0xB0007,
    0x7080004, 0xB0008, 0x8090005, 0xB0009, 0x90A0006, 0xB000A, 0x20B0003, 11,
    0xB0C0004, 0xB000C, 0x10D0002, 0xB000D, -1, -1,
};
int yumeBones_800A2440[50] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 9, 0x30A0004, 0xB000A, 0x2120003, 0xB0012,
    0x2130003, 0xB0013, 0x2140003, 0xB0014, 0x2150003, 0xB0015, 0x2160003, 0xB0016,
    0x3170004, 0xB0017, 0x10B0002, 0xB000B, 0x20C0003, 0xB000C, 0x30D0004, 0xB000D,
    0x40E0005, 0xB000E, 0x20F0003, 0xB000F, 0x3100004, 0xB0010, 0x4110005, 0xB0011,
    -1, -1,
};
int kikiBones_800A2508[54] = {
    0, 0x20000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x2130003, 0xB0013,
    0x3140004, 0xB0014, 0x4150005, 0xB0015, 0x2160003, 0xB0016, 0x3170004, 0xB0017,
    0x4180005, 0xB0018, 0x10B0002, 0xB000B, 0x20C0003, 0xB000C, 0x30D0004, 0xB000D,
    0x40E0005, 0xB000E, 0x20F0003, 0xB000F, 0x3100004, 0xB0010, 0x4110005, 0xB0011,
    0x2120003, 0xB0012, 0x2190003, 0xB0019, -1, -1,
};
int bsgsBones_800A25E0[76] = {
    0, 0xB0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x4060005, 0xB0006, 0x4070005, 0xB0007,
    0x1080002, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x40B0005, 0xB000B,
    0x40C0005, 0xB000C, 0x40D0005, 0xB000D, 0x10E0002, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x1110002, 0xB0011, 0x2120003, 0xB0012, 0x3130004, 0xB0013,
    0x4140005, 0xB0014, 0x5150006, 0xB0015, 0x5160006, 0xB0016, 0x5170006, 0xB0017,
    0x5180006, 0xB0018, 0x2190003, 0xB0019, 0x31A0004, 0xB001A, 0x41B0005, 0xB001B,
    0x51C0006, 0xB001C, 0x51D0006, 0xB001D, 0x51E0006, 0xB001E, 0x51F0006, 0xB001F,
    0x2200003, 0xB0020, 0x3210004, 0xB0021, 0x4220005, 0xB0022, 0x5230006, 0xB0023,
    0x6240007, 0xB0024, -1, -1,
};
int mabdBones_800A2710[34] = {
    0, 0xB0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x4060005, 0xB0006, 0x5070006, 0xB0007,
    0x2080003, 0xB0008, 0x3090004, 0xB0009, 0x40A0005, 0xB000A, 0x40B0005, 0xB000B,
    0x50C0006, 0xB000C, 0x20D0003, 0xB000D, 0x30E0004, 0xB000E, 0x10F0002, 0xB000F,
    -1, -1,
};
int mabeBones_800A2798[40] = {
    0, 0xB0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x30F0004, 0xB000F, 0x3110004, 0xB0011, 0x3040004, 0xB0004, 0x4050005, 0xB0005,
    0x5060006, 0xB0006, 0x2070003, 0xB0007, 0x3100004, 0xB0010, 0x3120004, 0xB0012,
    0x3080004, 0xB0008, 0x4090005, 0xB0009, 0x50A0006, 0xB000A, 0x20B0003, 0xB000B,
    0x30C0004, 0xB000C, 0x40D0005, 0xB000D, 0x10E0002, 0xB000E, -1, -1,
};
int mabfBones_800A2838[58] = {
    0, 0, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x4060005, 0xB0006, 0x5070006, 0xB0007,
    0x2080003, 0xB0008, 0x3090004, 0xB0009, 0x40A0005, 0xB000A, 0x40B0005, 0xB000B,
    0x50C0006, 0xB000C, 0x20D0003, 0xB000D, 0x30E0004, 0xB000E, 0x10F0002, 0xB000F,
    0x2100003, 0xB0010, 0x3110004, 0xB0011, 0x4120005, 0xB0012, 0x2130003, 0xB0013,
    0x3140004, 0xB0014, 0x4150005, 0xB0015, 0x2160003, 0xB0016, 0x3170004, 0xB0017,
    0x2180003, 0xB0018, 0x3190004, 0xB0019, 0x21A0003, 0xB001A, 0x21B0003, 0xB001B,
    -1, -1,
};
int mabcBones_800A2920[54] = {
    0, 0xB0000, 0x10001, 0xB0001, 0x10F0002, 0xB000F, 0x1100002, 0xB0010,
    0x2110003, 0xB0011, 0x3120004, 0xB0012, 0x1130002, 0xB0013, 0x2140003, 0xB0014,
    0x3150004, 0xB0015, 0x1160002, 0xB0016, 0x1170002, 0xB0017, 0x1180002, 0xB0018,
    0x1190002, 0xB0019, 0x1020002, 0xB0002, 0x2030003, 0xB0003, 0x3040004, 0xB0004,
    0x4050005, 0xB0005, 0x4060005, 0xB0006, 0x5070006, 0xB0007, 0x2080003, 0xB0008,
    0x3090004, 0xB0009, 0x40A0005, 0xB000A, 0x40B0005, 0xB000B, 0x50C0006, 0xB000C,
    0x20D0003, 0xB000D, 0x30E0004, 0xB000E, -1, -1,
};
int luiaBones_800A29F8[46] = {
    0, 0xB0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x2120003, 0xB0012,
    0x2130003, 0xB0013, 0x2140003, 0xB0014, 0x2150003, 0xB0015, 0x10B0002, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, -1, -1,
};
int nraaBones_800A2AB0[40] = {
    0, 0xB0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x10B0002, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0xB0012, -1, -1,
};
int nmuuBones_800A2B50[42] = {
    0, 0xB0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x10B0002, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0xB0012, 0x2130003, 0xB0013,
    -1, -1,
};
int nchoBones_800A2BF8[48] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007,
    0x2080003, 0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B,
    0xB0C0006, 0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F,
    0xF100003, 0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, 0xF130003, 0xB0013,
    0x13140004, 0xB0014, 0x14150005, 0xB0015, 0xF160003, 0xB0016, -1, -1,
};
int ymBones_800A2CB8[32] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x2060003, 0xB0006, 0x3070004, 0xB0007,
    0x4080005, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x40B0005, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, -1, -1,
};
int bseBones_800A2D38[48] = {
    0, 0xA0000, 0x10001, 0xB0001, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x1060002, 0xB0006, 0x2070003, 0xB0007,
    0x3080004, 0xB0008, 0x4090005, 0xB0009, 0x10A0002, 0xB000A, 0x20B0003, 0xB000B,
    0x30C0004, 0xB000C, 0x40D0005, 0xB000D, 0x10E0002, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0xB0012, 0x3130004, 0xB0013,
    0x4140005, 0xB0014, 0x1150002, 0xB0015, 0x1160002, 0xB0016, -1, -1,
};
int bsfsBones_800A2DF8[82] = {
    0, 0xA0000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060006, 0xB0006, 0x5070006, 0xB0007,
    0x5080006, 0xB0008, 0x2090003, 0xB0009, 0x30A0004, 0xB000A, 0x40B0005, 0xB000B,
    0x50C0006, 0xB000C, 0x50D0006, 0xB000D, 0x50E0006, 0xB000E, 0x20F0003, 0xB000F,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x2120003, 0x1B0012, 0x2130003, 0x1B0013,
    0x1140002, 0xB0014, 0x2150003, 0xB0015, 0x3160004, 0xB0016, 0x4170005, 0xB0017,
    0x5180006, 0xB0018, 0x6190007, 0xB0019, 0x61A0007, 0xB001A, 0x61B0007, 0xB001B,
    0x31C0004, 0xB001C, 0x41D0005, 0xB001D, 0x51E0006, 0xB001E, 0x61F0007, 0xB001F,
    0x6200007, 0xB0020, 0x6210007, 0xB0021, 0x3220004, 0xB0022, 0x4230005, 0xB0023,
    0x5240006, 0xB0024, 0x6250007, 0xB0025, 0x7260008, 0xB0026, 0x8270009, 0xB0027,
    -1, -1,
};
int bswsBones_800A2F40[82] = {
    0, 0xA0000, 0x10001, 0xB0001, 0x10E0002, 0xB000E, 0x20F0003, 0xB000F,
    0x3020004, 0xB0002, 0x4030005, 0xB0003, 0x5040006, 0xB0004, 0x6050007, 0xB0005,
    0x6060007, 0xB0006, 0x6070007, 0xB0007, 0x3080004, 0xB0008, 0x4090005, 0xB0009,
    0x50A0006, 0xB000A, 0x60B0007, 0xB000B, 0x60C0007, 0xB000C, 0x60D0007, 0xB000D,
    0x3170004, 0xB0017, 0x4180005, 0xB0018, 0x5190006, 0xB0004, 0x6050007, 0xB0005,
    0x6060007, 0xB0006, 0x6070007, 0xB0007, 0x31D0004, 0xB001D, 0x41E0005, 0xB001E,
    0x51F0006, 0xB000A, 0x60B0007, 0xB000B, 0x60C0007, 0xB000C, 0x60D0007, 0xB000D,
    0x3100004, 0xB0010, 0x4110005, 0xB0011, 0x5140006, 0xB0014, 0x6150007, 0xB0015,
    0x4120005, 0xB0012, 0x4130005, 0xB0013, 0x1160002, 0xB0016, 0x2230003, 0xB0023,
    0x3240004, 0xB0024, 0x4250005, 0xB0025, 0x5260006, 0xB0026, 0x6270007, 0xB0027,
    -1, -1,
};
int bszzBones_800A3088[72] = {
    0, 0xA0000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060006, 0xB0006, 0x6090007, 0xB0009,
    0x5070006, 0xB0007, 0x60A0007, 0xB000A, 0x5080006, 0xB0008, 0x60B0007, 0xB000B,
    0x20C0003, 0xB000C, 0x30D0004, 0xB000D, 0x40E0005, 0xB000E, 0x50F0006, 0xB000F,
    0x6120007, 0xB0012, 0x5100006, 0xB0010, 0x6130007, 0xB0013, 0x5110006, 0xB0011,
    0x6140007, 0xB0014, 0x2150003, 0xB0015, 0x2160003, 0xB0016, 0x3170004, 0xB0017,
    0x2180003, 0xB0018, 0x3190004, 0xB0019, 0x11A0002, 0xB001A, 0x21B0003, 0xB001B,
    0x31C0004, 0xB001C, 0x41D0005, 0xB001D, 0x51E0006, 0xB001E, 0x21F0003, 0xB001F,
    0x3200004, 0xB0020, 0x4210005, 0xB0021, 0x5220006, 0xB0022, -1, -1,
};
int rikeBones_800A31A8[48] = {
    0, 0x20000, 0x10001, 1, 0x1020002, 0xB0002, 0x2030003, 0xB0003,
    0x3040004, 0xB0004, 0x4050005, 0xB0005, 0x5060005, 0xB0006, 0x6070006, 0xB0007,
    0x2080003, 0xB0008, 0x8090004, 0xB0009, 0x90A0005, 0xB000A, 0xA0B0005, 0xB000B,
    0xB0C0006, 0xB000C, 0x20D0003, 13, 0xD0E0004, 0xB000E, 0x10F0002, 0xB000F,
    0xF100003, 0xB0010, 0x10110004, 0xB0011, 0x11120005, 0xB0012, 0xF130003, 0xB0013,
    0x13140004, 0xB0014, 0x14150005, 0xB0015, 0x2160003, 0xB0016, -1, -1,
};
char boneScales_800A3268[328] = { 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16, 0, 0, 0, 16, 0, 16, 0, 16 };
TstModelTbl tstModels_800A33B0[90] = {
    { 40, (void *)humanBones_800A1FD0, (int)aMDLLEBANT_800A098C },
    { 39, (void *)humanBones_800A1FD0, (int)aMDLLEB2_800A0980 },
    { 22, (void *)humanBones_800A1FD0, (int)aMDLGAR_800A0978 },
    { 46, (void *)humanBones_800A1FD0, (int)aMDLMABA_800A096C },
    { 47, (void *)humanBones_800A1FD0, (int)aMDLMABB_800A0960 },
    { 48, (void *)mabcBones_800A2920, (int)aMDLMABC_800A0954 },
    { 49, (void *)mabdBones_800A2710, (int)aMDLMABD_800A0948 },
    { 50, (void *)mabeBones_800A2798, (int)aMDLMABE_800A093C },
    { 51, (void *)mabfBones_800A2838, (int)aMDLMABF_800A0930 },
    { 58, (void *)humanBones_800A1FD0, (int)aMDLMOBA_800A0924 },
    { 54, (void *)humanBones_800A1FD0, (int)aMDLMDOG_800A0918 },
    { 36, (void *)humanBones_800A1FD0, (int)aMDLKEL_800A0910 },
    { 21, (void *)humanBones_800A1FD0, (int)aMDLFKEL_800A0904 },
    { 55, (void *)humanBones_800A1FD0, (int)aMDLMKEL_800A08F8 },
    { 56, (void *)roubBones_800A2088, (int)aMDLMLEB_800A08EC },
    { 44, (void *)humanBones_800A1FD0, (int)aMDLLUI_800A08E4 },
    { 45, (void *)luiaBones_800A29F8, (int)aMDLLUIA_800A08D8 },
    { 75, (void *)humanBones_800A1FD0, (int)aMDLSDOG_800A08CC },
    { 53, (void *)mchoBones_800A2110, (int)aMDLMCHO_800A08C0 },
    { 72, (void *)roubBones_800A2088, (int)aMDLROUBA_800A08B4 },
    { 73, (void *)roubBones_800A2088, (int)aMDLROUBB_800A08A8 },
    { 74, (void *)roubBones_800A2088, (int)aMDLROUBC_800A089C },
    { 59, (void *)mobBones_800A21D0, (int)aMDLMOBB_800A0890 },
    { 60, (void *)mobBones_800A21D0, (int)aMDLMOBC_800A0884 },
    { 30, (void *)mobBones_800A21D0, (int)aMDLHJI_800A087C },
    { 57, (void *)mnbnBones_800A2288, (int)aMDLMNBN_800A0870 },
    { 102, (void *)humanBones_800A1FD0, (int)aMDLZOK_800A0868 },
    { 100, (void *)zibBones_800A2328, (int)aMDLZIB_800A0860 },
    { 79, (void *)soujBones_800A23C8, (int)aMDLSOUJ_800A0854 },
    { 80, (void *)soujBones_800A23C8, (int)aMDLSOUJB_800A0848 },
    { 99, (void *)yumeBones_800A2440, (int)aMDLYUME_800A083C },
    { 9, (void *)humanBones_800A1FD0, (int)aMDLDA_800A0834 },
    { 10, (void *)humanBones_800A1FD0, (int)aMDLDB_800A082C },
    { 11, (void *)humanBones_800A1FD0, (int)aMDLDC_800A0824 },
    { 15, (void *)humanBones_800A1FD0, (int)aMDLDMA_800A081C },
    { 38, (void *)humanBones_800A1FD0, (int)aMDLKORI_800A0810 },
    { 37, (void *)kikiBones_800A2508, (int)aMDLKIKI_800A0804 },
    { 66, (void *)nraaBones_800A2AB0, (int)aMDLNRAA_800A07F8 },
    { 65, (void *)nmuuBones_800A2B50, (int)aMDLNMUU_800A07EC },
    { 63, (void *)nchoBones_800A2BF8, (int)aMDLNCHO_800A07E0 },
    { 94, (void *)ymBones_800A2CB8, (int)aMDLYM_800A07D8 },
    { 97, (void *)ymBones_800A2CB8, (int)aMDLYMTT_800A07CC },
    { 96, (void *)ymBones_800A2CB8, (int)aMDLYMKK_800A07C0 },
    { 95, (void *)ymBones_800A2CB8, (int)aMDLYMI_800A07B8 },
    { 5, (void *)bsgsBones_800A25E0, (int)aMDLBSGS_800A07AC },
    { 4, (void *)bseBones_800A2D38, (int)aMDLBSGE_800A07A0 },
    { 3, (void *)bsfsBones_800A2DF8, (int)aMDLBSFS_800A0794 },
    { 2, (void *)bseBones_800A2D38, (int)aMDLBSFE_800A0788 },
    { 7, (void *)bswsBones_800A2F40, (int)aMDLBSWS_800A077C },
    { 6, (void *)bseBones_800A2D38, (int)aMDLBSWE_800A0770 },
    { 8, (void *)bszzBones_800A3088, (int)aMDLBSZZ_800A0764 },
    { 62, (void *)yumeBones_800A2440, (int)aMDLNAGK_800A0758 },
    { 71, (void *)rikeBones_800A31A8, (int)aMDLRIKE_800A074C },
    { 98, (void *)minionBones_800A1F00, (int)aMDLYOLK_800A0740 },
    { 70, (void *)minionBones_800A1F00, (int)aMDLRIG_800A0738 },
    { 1, (void *)minionBones_800A1F00, (int)aMDLASHA_800A072C },
    { 93, (void *)minionBones_800A1F00, (int)aMDLUGURAM_800A0720 },
    { 41, (void *)minionBones_800A1F00, (int)aMDLLUCH_800A0714 },
    { 76, (void *)minionBones_800A1F00, (int)aMDLSHABU_800A0708 },
    { 12, (void *)minionBones_800A1F00, (int)aMDLDLEG_800A06FC },
    { 24, (void *)minionBones_800A1F00, (int)aMDLHANBA_800A06F0 },
    { 31, (void *)minionBones_800A1F00, (int)aMDLIMEL_800A06E4 },
    { 52, (void *)minionBones_800A1F00, (int)aMDLMAIE_800A06D8 },
    { 81, (void *)minionBones_800A1F00, (int)aMDLTHRE_800A06CC },
    { 27, (void *)minionBones_800A1F00, (int)aMDLHIRA_800A06C0 },
    { 18, (void *)minionBones_800A1F00, (int)aMDLDONG_800A06B4 },
    { 23, (void *)minionBones_800A1F00, (int)aMDLGINU_800A06A8 },
    { 13, (void *)minionBones_800A1F00, (int)aMDLDLEGB_800A069C },
    { 14, (void *)minionBones_800A1F00, (int)aMDLDLEGC_800A0690 },
    { 19, (void *)minionBones_800A1F00, (int)aMDLDONGB_800A0684 },
    { 20, (void *)minionBones_800A1F00, (int)aMDLDONGC_800A0678 },
    { 25, (void *)minionBones_800A1F00, (int)aMDLHANBB_800A066C },
    { 26, (void *)minionBones_800A1F00, (int)aMDLHANBC_800A0660 },
    { 28, (void *)minionBones_800A1F00, (int)aMDLHIRAB_800A0654 },
    { 29, (void *)minionBones_800A1F00, (int)aMDLHIRAC_800A0648 },
    { 32, (void *)minionBones_800A1F00, (int)aMDLIMELB_800A063C },
    { 33, (void *)minionBones_800A1F00, (int)aMDLIMELC_800A0630 },
    { 34, (void *)minionBones_800A1F00, (int)aMDLKAMERE_800A0624 },
    { 35, (void *)minionBones_800A1F00, (int)aMDLKANI_800A0618 },
    { 42, (void *)minionBones_800A1F00, (int)aMDLLUCHB_800A060C },
    { 43, (void *)minionBones_800A1F00, (int)aMDLLUCHC_800A0600 },
    { 61, (void *)minionBones_800A1F00, (int)aMDLMUGU_800A05F4 },
    { 64, (void *)minionBones_800A1F00, (int)aMDLNEBUI_800A05E8 },
    { 67, (void *)minionBones_800A1F00, (int)aMDLOJE_800A05E0 },
    { 77, (void *)minionBones_800A1F00, (int)aMDLSHABUB_800A05D4 },
    { 78, (void *)minionBones_800A1F00, (int)aMDLSHABUC_800A05C8 },
    { 82, (void *)minionBones_800A1F00, (int)aMDLTORI_800A05BC },
    { 101, (void *)minionBones_800A1F00, (int)aMDLZIRA_800A05B0 },
    { 68, (void *)minionBones_800A1F00, (int)aMDLOUMG_800A05A4 },
    { -1 },
};
int levantFtgs_800A37E8[3] = { 2, 7, -1 };
short gridWrapMask_800A37F4[4] = { 1, 1, 2, 2 };
short gridWrapSign_800A37FC[4] = { -1, 1, 1, -1 };
char modelBonePos_800A3804[480] = { 0 };
