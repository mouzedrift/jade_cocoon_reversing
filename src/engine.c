#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "memmap.h"
#include "globals.h"
#include "engine.h"
#include "camera.h"
#include "gte.h"
#include "model.h"
#include "sound.h"
#include "data_decls.h"
#include "effect_data.h"
#include "effect.h"
#include "event.h"
#include "main.h"
#include "util.h"
#include "cd.h"
#include "sound_seq.h"
#include "tim.h"
#include "effect_model.h"
#include "effect_cmd.h"
#include "model_ftg.h"
/* defined further on / elsewhere without a prototype the callers see */
#ifdef __psyz /* with these two the PlayStation code would change (a short result, short arguments) */
short GetActorHitTimes_8001F268(Actor* o, HitTimes* out, ActorScriptCmd* script, int anim);
void UpdatePadRepeat_8001CAF0(int port, unsigned short delay, unsigned short rate);
#endif
void AllocActorBones_8001E7F0(Actor* actor, ActorDesc* desc);
void InitSprt_8001B9A0(int buffer);
void ReleaseModelAnimRef_80020278(int ref, int user);
void ResetFtgSpriteVtx_8004D924(void);
void UpdatePadAnalog_8001CC04(int port);


// the bit masks SetBoneGroupFlags_80019B14 (minion_init.c) copies: the first .rdata of this file, which has to start at 4 mod 8
// for its switch tables (.align 3), so SetBoneGroupFlags_80019B14 is probably the first function of this TU
const struct_int3 boneGroupMasks_8007303C = { { 0x1F8, 0xF000, 0x7E0000 } };
const char emptyName_80073048[4] = "";
const char aDevaMalti_8007304C[24] = "\202c\202\205\202\226\202\201\201@\202l\202\201\202\214\202\224\202\211"; // Deva Malti
const char aDevaUlvi_80073064[20] = "\202c\202\205\202\226\202\201\201@\202t\202\214\202\226\202\211"; // Deva Ulvi
const char aDevaVali_80073078[20] = "\202c\202\205\202\226\202\201\201@\202u\202\201\202\214\202\211"; // Deva Vali
const char aDevaAgni_8007308C[20] = "\202c\202\205\202\226\202\201\201@\202`\202\207\202\216\202\211"; // Deva Agni
const char aAdMumuls_800730A0[20] = "\202`\202\204\201@\202l\202\225\202\215\202\225\202\214\202\223"; // Ad Mumuls
const char aAdRoqua_800730B4[20] = "\202`\202\204\201@\202q\202\217\202\221\202\225\202\201"; // Ad Roqua
const char aAdSlahm_800730C8[20] = "\202`\202\204\201@\202r\202\214\202\201\202\210\202\215"; // Ad Slahm
const char aAdVenon_800730DC[20] = "\202`\202\204\201@\202u\202\205\202\216\202\217\202\216"; // Ad Venon
const char aSelSelahm_800730F0[24] = "\202r\202\205\202\214\201@\202r\202\205\202\214\202\201\202\210\202\215"; // Sel Selahm
const char aSelahm_80073108[16] = "\202r\202\205\202\214\202\201\202\210\202\215"; // Selahm
const char aMedinia_80073118[16] = "\202l\202\205\202\204\202\211\202\216\202\211\202\201"; // Medinia
const char aMedina_80073128[16] = "\202l\202\205\202\204\202\211\202\216\202\201"; // Medina
const char aSelahmVenon_80073138[28] = "\202r\202\205\202\214\202\201\202\210\202\215\201@\202u\202\205\202\216\202\217\202\216"; // Selahm Venon
const char aMaltia_80073154[16] = "\202l\202\201\202\214\202\224\202\211\202\201"; // Maltia
const char aMaltis_80073164[16] = "\202l\202\201\202\214\202\224\202\211\202\223"; // Maltis
const char aMalti_80073174[12] = "\202l\202\201\202\214\202\224\202\211"; // Malti
const char aUlvia_80073180[12] = "\202t\202\214\202\226\202\211\202\201"; // Ulvia
const char aUlvis_8007318C[12] = "\202t\202\214\202\226\202\211\202\223"; // Ulvis
const char aUlvi_80073198[12] = "\202t\202\214\202\226\202\211"; // Ulvi
const char aVahlia_800731A4[16] = "\202u\202\201\202\210\202\214\202\211\202\201"; // Vahlia
const char aVahlis_800731B4[16] = "\202u\202\201\202\210\202\214\202\211\202\223"; // Vahlis
const char aVahli_800731C4[12] = "\202u\202\201\202\210\202\214\202\211"; // Vahli
const char aAgnia_800731D0[12] = "\202`\202\207\202\216\202\211\202\201"; // Agnia
const char aAgnis_800731DC[12] = "\202`\202\207\202\216\202\211\202\223"; // Agnis
const char emptyName_800731E8[4] = "";
const char aAgni_800731EC[12] = "\202`\202\207\202\216\202\211"; // Agni
unsigned int* const overlayAddr1_800731F8 = PSX_RAM(0x800C9E88);
unsigned int* const overlayAddr2_800731FC = PSX_RAM(0x800A4088);
unsigned int* const overlayAddr3_80073200 = PSX_RAM(0x800A05A0);
unsigned int* const overlayAddr4_80073204 = PSX_RAM(0x800B66C0);
unsigned int* const overlayAddr5_80073208 = PSX_RAM(0x800C29D0);
unsigned int* const overlayAddr6_8007320C = PSX_RAM(0x800B6D00);
unsigned int *const mapCodeAddr_80073210 = PSX_RAM(0x800B22C0);
/* char* data001Path_80086570 = "\\DATA\\DATA.001;1"; (the string literal would be emitted into .rdata, not owned yet) */

signed char GetMinionElement_80019BF0(int idx)
{
    return minionBaseStats_8007A4B4[idx].element;
}
unsigned char GetMinionEnhancementBody_80019C0C(int idx)
{
    return minionBaseStats_8007A4B4[idx].enhancementBody;
}
UnitSkills* GetSpeciesSkills_80019C28(unsigned int idx)
{
    if (0xC9 > idx)
    {
        return &speciesSkills_8007A9F8[idx];
    }
    return sub_800B3274(idx - 0x39);
}
MinionModelDesc* GetSpeciesModelDesc_80019C70(int idx)

{
    return &speciesModelDescs_8007BD30[idx];
}
int PickArpatronOrVatolka_80019C84(void)
{
    int species = 0x24;
    int seed = minionVariantSeed_8008D4DC & 0xFF;
    if (unknownFlags_8008D678 & 0x1000)
    {
        species = seed % 4 + 0x25;
    }
    return species;
}
extern short screenOffset_8008D474[2];
extern unsigned short padPrevHeld_800918C8[];
extern unsigned short padRepeat_800918CC[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padPressed_8009194C[];
extern unsigned short padHoldFrames_80091950[][16];
extern signed char padAnalog_800918D8[][4];
extern unsigned char padAnalogMax_800918E0[][4];
// index of the camera point nearest to pos (XZ plane)
int FindNearestCameraPoint_80019CC4(int* pos)
{
    unsigned int i;
    unsigned int best;
    int found;
    best = -1;
    found = 0;
    if (unknownFlags_8008D678 & 0x8000)
    {
        return found;
    }
    for (i = 0; i < 8; i++)
    {
        if (cameraState_8008D4F0.ent_44[i].range_14 == 0)
        {
            break;
        }
        if (DistanceSquaredXZ_8003B860((int*)&cameraState_8008D4F0.ent_44[i].pos_0, pos) < best)
        {
            best = DistanceSquaredXZ_8003B860((int*)&cameraState_8008D4F0.ent_44[i].pos_0, pos);
            found = i;
        }
    }
    return found;
}
extern int pointLightRange_8008D3F0;      // range of the global point light (0: none)
// Sets the GTE light and colour matrices for a model at pos + ofs, lit by the scene light (lightMatrix_80087114 row 0,
// colour from cameraState), the global point light and the given point light; m is the model's rotation.
void SetModelLighting_80019D84(VECTOR* pos, VECTOR* ofs, PointLight* light, MATRIX* m)
{
    MATRIX* sm;
    int* delta;
    CameraView* cam;
    int sq[3];
    int dist;
    int intensity;
    int dirX;
    int dirY;
    int dirZ;

    delta = (int*)((MATRIX*)getScratchAddr(0))->t; // the scratch matrix's translation
    cam = &cameraState_8008D4F0;
    sm = (MATRIX*)getScratchAddr(0);
    sm->m[0][0] = lightMatrix_80087114.m[0][0];
    sm->m[0][1] = lightMatrix_80087114.m[0][1];
    sm->m[0][2] = lightMatrix_80087114.m[0][2];
    sm->m[2][0] = -lightMatrix_80087114.m[0][0];
    sm->m[2][1] = -lightMatrix_80087114.m[0][1];
    sm->m[2][2] = -lightMatrix_80087114.m[0][2];
    colorMatrix_80087134.m[0][2] = cam->lightColor_3C.vx / 4;
    colorMatrix_80087134.m[1][2] = cam->lightColor_3C.vy / 4;
    colorMatrix_80087134.m[2][2] = cam->lightColor_3C.vz / 4;
    if (pointLightRange_8008D3F0 != 0)
    {
        delta[0] = pointLightPos_8008D680[0] - (ofs->vx + pos->vx);
        delta[1] = pointLightPos_8008D680[1] - (ofs->vy + pos->vy);
        delta[2] = pointLightPos_8008D680[2] - (ofs->vz + pos->vz);
        if (abs(delta[0]) < pointLightRange_8008D3F0 && abs(delta[1]) < pointLightRange_8008D3F0 && abs(delta[2]) < pointLightRange_8008D3F0)
        {
            gte_ldlvl(delta);
            gte_sqr0();
            gte_stlvnl(sq);
            dist = ISqrt_8003B918(sq[0] + sq[1] + sq[2]);
            if (dist <= pointLightRange_8008D3F0)
            {
                sm->m[2][0] = (delta[0] << 12) / dist;
                sm->m[2][1] = (delta[1] << 12) / dist;
                sm->m[2][2] = (delta[2] << 12) / dist;
                if (unknownFlags_8008D678 & 0x400)
                {
                    intensity = (((pointLightRange_8008D3F0 - dist) << 12) / pointLightRange_8008D3F0) * sceneBrightness_8008D40C >> 12;
                }
                else
                {
                    intensity = ((pointLightRange_8008D3F0 - dist) << 12) / pointLightRange_8008D3F0;
                }
                gte_lddp(intensity);
                gte_ldsv(&pointLightColor_8008D418);
                gte_gpf12();
                gte_stclmv(&colorMatrix_80087134.m[0][2]);
            }
        }
    }
    delta[0] = light->pos_0.x - (ofs->vx + pos->vx);
    delta[1] = light->pos_0.y - (ofs->vy + pos->vy);
    delta[2] = light->pos_0.z - (ofs->vz + pos->vz);
    gte_ldlvl(delta);
    gte_sqr0();
    gte_stlvnl(sq);
    dist = ISqrt_8003B918(sq[0] + sq[1] + sq[2]);
    if (light->range_14 < dist)
    {
        colorMatrix_80087134.m[0][1] = 0;
        colorMatrix_80087134.m[1][1] = 0;
        colorMatrix_80087134.m[2][1] = 0;
    }
    else
    {
        dirX = (delta[0] << 12) / dist;
        dirY = (delta[1] << 12) / dist;
        dirZ = (delta[2] << 12) / dist;
        ((MATRIX*)getScratchAddr(0))->m[1][0] = dirX;
        ((MATRIX*)getScratchAddr(0))->m[1][1] = dirY;
        ((MATRIX*)getScratchAddr(0))->m[1][2] = dirZ;
        if (unknownFlags_8008D678 & 0x400)
        {
            intensity = (((light->range_14 - dist) << 12) / light->range_14 * (light->range_14 - dist) / light->range_14) * sceneBrightness_8008D40C >> 12;
        }
        else
        {
            intensity = ((light->range_14 - dist) << 12) / light->range_14 * (light->range_14 - dist) / light->range_14;
        }
        gte_lddp(intensity);
        gte_ldsv(&light->color_C);
        gte_gpf12();
        gte_stclmv(&colorMatrix_80087134.m[0][1]);
    }
    gte_SetRotMatrix((MATRIX*)getScratchAddr(0));
    gte_ldclmv(&m->m[0][0]);
    gte_rtir();
    gte_stclmv(&((MATRIX*)getScratchAddr(0))->m[0][0]);
    gte_ldclmv(&m->m[0][1]);
    gte_rtir();
    gte_stclmv(&((MATRIX*)getScratchAddr(0))->m[0][1]);
    gte_ldclmv(&m->m[0][2]);
    gte_rtir();
    gte_stclmv(&((MATRIX*)getScratchAddr(0))->m[0][2]);
    gte_SetLightMatrix((MATRIX*)getScratchAddr(0));
    gte_SetColorMatrix(&colorMatrix_80087134);
}
void InitSceneFade_8001A38C(void)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    CameraView* cam;
    fade->flags = 0;
    fade->count = 0;
    cam = &cameraState_8008D4F0;
    lightMatrix_80087114.m[2][0] = -(unsigned short)cam->lightDir_34.vx;
    lightMatrix_80087114.m[2][1] = -(unsigned short)cam->lightDir_34.vy;
    lightMatrix_80087114.m[2][2] = -(unsigned short)cam->lightDir_34.vz;
    colorMatrix_80087134.m[0][2] = cam->lightColor_3C.vx / 4;
    colorMatrix_80087134.m[1][2] = cam->lightColor_3C.vy / 4;
    colorMatrix_80087134.m[2][2] = cam->lightColor_3C.vz / 4;
}
void SceneFadeTask_8001A41C(EventEntry* entry, SceneFade* fade)
{
    OT_TYPE* ot;
    POLY_F4 poly;
    DR_TPAGE tp;
    int shade;
    SVECTOR* sv;
    CameraView* cam;
    unsigned char flash;
    if (fade->flags & 0x20)
    {
        ot = pOT_8008D4AC;
    }
    else
    {
        ot = pOT_8008D5F4;
    }
    if (fade->flags & 0x10)
    {
        flash = fade->count * 255 / 8;
        SetPolyF4(&poly);
        poly.r0 = flash;
        poly.g0 = flash;
        poly.b0 = flash;
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.w_C;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.h_E;
        poly.x3 = display_8008B4D8.w_C;
        poly.y3 = display_8008B4D8.h_E;
        SetSemiTrans(&poly, 1);
        AddPrimCopy_80040298(&ot[3], &poly, sizeof(poly) / 4);
        setlen(&tp, 1);
        tp.code[0] = 0xE1000220;
        AddPrimCopy_80040298(&ot[3], &tp, sizeof(tp) / 4);
        if (--fade->count < 0)
        {
            fade->flags &= ~0x10;
        }
    }
    else if (fade->flags & 1)
    {
        sceneBrightness_8008D40C += 0x1000 / fade->duration;
        if (sceneBrightness_8008D40C >= 0x1000)
        {
            sceneBrightness_8008D40C = 0x1000;
            unknownFlags_8008D678 &= ~0x400;
            fade->flags &= ~1;
        }
    }
    else if (fade->flags & 2)
    {
        sceneBrightness_8008D40C -= 0x1000 / fade->duration;
        if (sceneBrightness_8008D40C < 0)
        {
            fade->flags &= ~2;
            sceneBrightness_8008D40C = 0;
        }
    }
    else if (fade->flags & 4)
    {
        shade = fade->count << 8;
        shade -= fade->count;
        shade /= fade->duration;
        SetPolyF4(&poly);
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.w_C;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.h_E;
        poly.x3 = display_8008B4D8.w_C;
        poly.y3 = display_8008B4D8.h_E;
        poly.r0 = shade;
        poly.g0 = shade;
        poly.b0 = shade;
        SetSemiTrans(&poly, 1);
        AddPrimCopy_80040298(&ot[3], &poly, sizeof(poly) / 4);
        setlen(&tp, 1);
        tp.code[0] = 0xE1000220;
        AddPrimCopy_80040298(&ot[3], &tp, sizeof(tp) / 4);
        if (++fade->count > fade->duration)
        {
            fade->count = fade->duration;
        }
    }
    else if (fade->flags & 8)
    {
        shade = (fade->duration - fade->count) << 8;
        shade -= fade->duration - fade->count;
        shade /= fade->duration;
        SetPolyF4(&poly);
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.w_C;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.h_E;
        poly.x3 = display_8008B4D8.w_C;
        poly.y3 = display_8008B4D8.h_E;
        poly.r0 = shade;
        poly.g0 = shade;
        poly.b0 = shade;
        SetSemiTrans(&poly, 1);
        AddPrimCopy_80040298(&ot[3], &poly, sizeof(poly) / 4);
        setlen(&tp, 1);
        tp.code[0] = 0xE1000220;
        AddPrimCopy_80040298(&ot[3], &tp, sizeof(tp) / 4);
        if (++fade->count > fade->duration)
        {
            fade->flags &= ~8;
            fade->count = fade->duration;
        }
    }
    sv = &cameraState_8008D4F0.lightDir_34;
    VectorNormalSS(sv, sv);
    cam = &cameraState_8008D4F0;
    lightMatrix_80087114.m[0][0] = cam->lightDir_34.vx;
    lightMatrix_80087114.m[0][1] = cam->lightDir_34.vy;
    lightMatrix_80087114.m[0][2] = cam->lightDir_34.vz;
    if (unknownFlags_8008D678 & 0x400)
    {
        colorMatrix_80087134.m[0][0] = cam->lightColor_3C.vx * sceneBrightness_8008D40C >> 12;
        colorMatrix_80087134.m[1][0] = cam->lightColor_3C.vy * sceneBrightness_8008D40C >> 12;
        colorMatrix_80087134.m[2][0] = cam->lightColor_3C.vz * sceneBrightness_8008D40C >> 12;
    }
    else
    {
        colorMatrix_80087134.m[0][0] = cam->lightColor_3C.vx;
        colorMatrix_80087134.m[1][0] = cam->lightColor_3C.vy;
        colorMatrix_80087134.m[2][0] = cam->lightColor_3C.vz;
    }
    lightMatrix_80087114.m[1][0] = 0;
    lightMatrix_80087114.m[1][1] = 0;
    lightMatrix_80087114.m[1][2] = 0;
    lightMatrix_80087114.m[2][0] = -lightMatrix_80087114.m[0][0];
    lightMatrix_80087114.m[2][1] = -lightMatrix_80087114.m[0][1];
    lightMatrix_80087114.m[2][2] = -lightMatrix_80087114.m[0][2];
    colorMatrix_80087134.m[0][1] = 0;
    colorMatrix_80087134.m[1][1] = 0;
    colorMatrix_80087134.m[2][1] = 0;
    colorMatrix_80087134.m[0][2] = colorMatrix_80087134.m[0][0] / 4;
    colorMatrix_80087134.m[1][2] = colorMatrix_80087134.m[1][0] / 4;
    colorMatrix_80087134.m[2][2] = colorMatrix_80087134.m[2][0] / 4;
    if (unknownFlags_8008D678 & 0x400)
    {
        backColor_8008D460[0] = cameraState_8008D4F0.ambientR_30 * sceneBrightness_8008D40C >> 12;
        backColor_8008D460[1] = cameraState_8008D4F0.ambientG_31 * sceneBrightness_8008D40C >> 12;
        backColor_8008D460[2] = cameraState_8008D4F0.ambientB_32 * sceneBrightness_8008D40C >> 12;
    }
    else
    {
        backColor_8008D460[0] = cameraState_8008D4F0.ambientR_30;
        backColor_8008D460[1] = cameraState_8008D4F0.ambientG_31;
        backColor_8008D460[2] = cameraState_8008D4F0.ambientB_32;
    }
}
void ResetSceneFade_8001A9A4(void)
{
    SceneFade* fade;
    unsigned short flags;
    sceneBrightness_8008D40C = 0x1000;
    fade = fadeTask_8008D628->entry.buffer;
    flags = fade->flags;
    unknownFlags_8008D678 &= ~0x400;
    fade->count = 0;
    fade->flags = flags & 0xFFF0;
}
void SetSceneDark_8001A9E4(void)
{
    unknownFlags_8008D678 |= 0x400;
    sceneBrightness_8008D40C = 0;
}
void StartSceneFadeIn_8001AA04(int duration)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    fade->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    fade->count = 0;
    fade->flags |= 1;
    SceneFadeTask_8001A41C(task, fade);
}
void StartSceneFadeOut_8001AA50(int duration)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    unknownFlags_8008D678 |= 0x400;
    fade->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    fade->count = 0;
    fade->flags |= 2;
    SceneFadeTask_8001A41C(task, fade);
}
void StartSceneDarken_8001AAA8(int duration)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    fade->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    fade->count = 0;
    fade->flags |= 4;
    SceneFadeTask_8001A41C(task, fade);
}
void StopSceneDarken_8001AAF4(void)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    fade->flags &= ~4;
}
void StartSceneBrighten_8001AB1C(int duration)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    fade->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    fade->count = 0;
    fade->flags |= 8;
    SceneFadeTask_8001A41C(task, fade);
}
void StartSceneFlash_8001AB68(void)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    fade->count = 8;
    fade->flags |= 0x10;
}
int IsSceneFadeDone_8001AB94(void)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    unsigned short flags = fade->flags;
    if (flags & 0x1B)
    {
        return 0;
    }
    if (flags & 4)
    {
        return fade->count == fade->duration;
    }
    return 1;
}
void SetSceneFadeFrontOT_8001ABEC(int on)
{
    SceneFade* fade = fadeTask_8008D628->entry.buffer;
    if (on)
    {
        fade->flags |= 0x20;
    }
    else
    {
        fade->flags &= ~0x20;
    }
}
const char* GetMagicName_8001AC2C(int idx)
{
    if (idx >= 0x1E)
    {
        return 0;
    }
    return magicNames_8007C348[idx * 2];
}
int GetMagicMpCost_8001AC58(int idx)
{
    if (idx < 0x1E)
    {
        return magicData_8007C438[idx].mpCost_4;
    }
    return 0;
}
int GetMagicEffect_8001AC8C(int idx)
{
    if (idx < 0x1E)
    {
        return magicData_8007C438[idx].effect_6;
    }
    return 0x1A;
}
int GetMagicField5_8001ACC0(int idx)
{
    return magicData_8007C438[idx].field_5;
}
int GetMagicTargetFlags_8001ACE4(int idx)
{
    unsigned int flags = magicData_8007C438[idx].flags_0;
    int targetFlags = (flags >> 5) & 2;
    if (flags & 0x80)
    {
        targetFlags |= 4;
    }
    if (flags & 4)
    {
        targetFlags |= 1;
    }
    return targetFlags;
}
int GetMagicElement_8001AD30(int idx)
{
    if (idx < 0x1E)
    {
        return magicData_8007C438[idx].element_8;
    }
    return 0xB;
}
ActionData* GetMagicAction_8001AD64(unsigned int idx)
{
    if (idx < 0x1E)
    {
        return &magicActions_8007C5A0[idx];
    }
    return 0;
}
void ClearMagicBits_8001AD90(unsigned int* bits)
{
    int i;
    for (i = 0; i < 1; i++)
    {
        bits[i] = 0;
    }
}
void SetMagicBit_8001ADAC(unsigned int* bits, unsigned int idx)
{
    unsigned int* word = bits + (idx >> 5);
    *word |= 1 << (idx & 0x1F);
}
void OrMagicBits_8001ADD4(unsigned int* dst, unsigned int* src)
{
    int i;
    for (i = 0; i < 1; i++)
    {
        *dst++ |= *src++;
    }
}
void ClearMagicBit_8001AE00(unsigned int* bits, unsigned int idx)
{
    unsigned int* word = bits + (idx >> 5);
    *word &= ~(1 << (idx & 0x1F));
}
int TestMagicBit_8001AE2C(unsigned int* bits, unsigned int idx)
{
    unsigned int* word = bits + (idx >> 5);
    return (*word & (1 << (idx & 0x1F))) != 0;
}
int CountMagicBits_8001AE54(unsigned int* bits)
{
    int i = 0;
    int count = i;
    for (; i < 0x1E; i++)
    {
        if (TestMagicBit_8001AE2C(bits, i))
        {
            count++;
        }
    }
    return count;
}
// called by MENU's OnMinionLevelUp_800BCF74 with the minion's dominant species, status and magic bits
void MinionLevelUpHook_8001AEB8(int species, UnitStatus* status, int magicBits)
{
}
int FindNthMagicBit_8001AEC0(unsigned int* bits, int n)
{
    int cnt = 0;
    int i;
    for (i = 0; i < 0x1E; i++)
    {
        if (TestMagicBit_8001AE2C(bits, i))
        {
            if (cnt == n)
            {
                return i;
            }
            cnt++;
        }
    }
    return 0x1E;
}
int GetMagicIcon_8001AF3C(int idx)
{
    if (idx < 0x1E)
    {
        return magicIcons_8007C708[idx];
    }
    return 0;
}
void DrawIntroMovie_8001AF64(void* descs)
{
    void* list;
    DRAWENV* e0;
    DRAWENV* e1;
    int r;
    int g;
    int b;
    SetDispMask(0);
    InitMovie_8001B1B0();
    list = CreateEventList_800435B4(descs);
    e0 = drawEnv_8008D698;
    do
    {
        if (unknownFlags_8008D678 & 0x40)
        {
            StartDisplay_8001B714();
        }
        bDoubleBuffer_8008D428 = bDoubleBuffer_8008D428 == 0;
        ClearOTagRAll_8001B260();
        AddPrimsAll_8001B3C8();
        InitPrimBuffers_8001BF90();
        frameCount_8008D3FC++;
        ProcessPads_8001BF50();
        RunEventList_80043898(list);
        e1 = e0 + 1;
        r = drawEnvRed_8008D448[0];
        g = drawEnvRed_8008D448[1];
        b = drawEnvRed_8008D448[2];
        e0->r0 = r;
        e0->g0 = g;
        e0->b0 = b;
        e1->r0 = r;
        e1->g0 = g;
        e1->b0 = b;
        DrawFrozenFrame_8001B540();
        if (motionBlurOn_800918C4)
        {
            DrawMotionBlur_8001BCE4(bDoubleBuffer_8008D428);
        }
        Draw_8001B5EC();
        if (unknownFlags_8008D678 & 0x10)
        {
            SetDispMask(1);
        }
        else
        {
            SetDispMask(0);
        }
        PutDispEnv(&dispEnv_8008D750[bDoubleBuffer_8008D428]);
        PutDrawEnv((DRAWENV*)(bDoubleBuffer_8008D428 * sizeof(DRAWENV) + (long)e0));
        if (unknownFlags_8008D678 & 8)
        {
            DrawOTag(pOT_8008D78C);
            DrawOTag(&pOT_8008D454[15]);
            frozenFrames_800918B8++;
        }
        else
        {
            if (!(unknownFlags_8008D678 & 2) && (unknownFlags_8008D678 & 0x800))
            {
                LoadDecodedImage_8001BEC8();
                unknownFlags_8008D678 &= ~0x800;
            }
            DrawOTag(&pOT_8008D788[7]);
        }
    } while (bStopDrawingMovie_8008D45C == 0);
    RunEventListFreeCallbacks_800438F8(list);
    DrawSync(0);
    FreeEventList_80043A5C(list);
}
void InitMovie_8001B1B0(void)
{
    bStopDrawingMovie_8008D45C = 0;
    frameCount_8008D3FC = 0;
    geomScreenDistance_8008B548 = 0xA0;
    cameraZoom_8008B4F8 = 0x1000;
    drawEnvRed_8008D448[0] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[2] = 0;
    bDoubleBuffer_8008D428 = 0;
    motionBlurOn_800918C4 = 0;
    unknownFlags_8008D678 &= ~0x200;
    RestartDisplay_8001B230();
}
void RestartDisplay_8001B230(void)
{
    unknownFlags_8008D678 &= ~0x10;
    displayStartFrames_800918BC = 0;
    unknownFlags_8008D678 |= 0x40;
}
void ClearOTagRAll_8001B260(void)
{
    ResetFtgSpriteVtx_8004D924();
    pOT_8008D788 = OT_8008D798[bDoubleBuffer_8008D428];
    pOT_8008D4AC = OT_80091868[bDoubleBuffer_8008D428];
    pOT_8008D454 = OT_800917D8[bDoubleBuffer_8008D428];
    pOT_8008D5F4 = OT_80091888[bDoubleBuffer_8008D428];
    pOT_8008D690 = OT_8008D7D8[bDoubleBuffer_8008D428];
    pOT_8008B4C8 = OT_8008F7D8[bDoubleBuffer_8008D428];
    pOT_8008D78C = OT_800918A8[bDoubleBuffer_8008D428];
    pOT_8008D3EC = OT_80091858[bDoubleBuffer_8008D428];

    ClearOTagR(pOT_8008D788, 8);
    ClearOTagR(pOT_8008D4AC, 4);
    ClearOTagR(pOT_8008D454, 16);
    ClearOTagR(pOT_8008D5F4, 4);
    ClearOTagR(pOT_8008D690, 1024);
    ClearOTagR(pOT_8008B4C8, 1024);
    ClearOTagR(pOT_8008D78C, 1);
    ClearOTagR(pOT_8008D3EC, 1);
}
void AddPrimsAll_8001B3C8(void)
{
    char pad[20];

    if ((unknownFlags_8008D678 & 2) != 0)
    {
        AddPrims(&pOT_8008D788[7], pOT_8008D78C, pOT_8008D78C);
        AddPrims(&pOT_8008D788[6], pOT_8008D3EC, pOT_8008D3EC);
        AddPrims(&pOT_8008D788[3], &pOT_8008D5F4[3], pOT_8008D5F4);
        AddPrims(&pOT_8008D788[2], &pOT_8008D454[15], pOT_8008D454);
        AddPrims(&pOT_8008D788[0], &pOT_8008D4AC[3], pOT_8008D4AC);
    }
    else
    {
        AddPrims(&pOT_8008D788[7], pOT_8008D78C, pOT_8008D78C);
        AddPrims(&pOT_8008D788[6], pOT_8008D3EC, pOT_8008D3EC);
        AddPrims(&pOT_8008D788[4], &pOT_8008D690[1023], pOT_8008D690);
        AddPrims(&pOT_8008D788[3], &pOT_8008D5F4[3], pOT_8008D5F4);
        AddPrims(&pOT_8008D788[2], &pOT_8008D454[15], pOT_8008D454);
        AddPrims(&pOT_8008D788[0], &pOT_8008D4AC[3], pOT_8008D4AC);
        if ((unknownFlags_8008D678 & 0x10000) != 0)
        {
            AddPrims(&pOT_8008D788[1], &pOT_8008B4C8[1023], pOT_8008B4C8);
        }
        else
        {
            AddPrims(&pOT_8008D788[5], &pOT_8008B4C8[1023], pOT_8008B4C8);
        }
    }
}
void DrawFrozenFrame_8001B540(void)
{
    if (unknownFlags_8008D678 & 8)
    {
        InitSprt_8001B9A0(bDoubleBuffer_8008D428);
    }
    else if (unknownFlags_8008D678 & 0x82)
    {
        int fadeFlags = fadeFlags_800918B0;
        if (fadeFlags & 2)
        {
            FadeToWhiteStep_8001BC00();
        }
        else if (fadeFlags & 1)
        {
            FadeToBlackStep_8001BB28();
        }
        InitSprt_8001B9A0(bDoubleBuffer_8008D428);
        unknownFlags_8008D678 &= ~0x80;
    }
}
void Draw_8001B5EC(void)
{
    int ode;
    if (!(unknownFlags_8008D678 & 0x20))
    {
        DrawSync(0);
    }
    SetGeomOffset(display_8008B4D8.w_C / 2 + screenOffset_8008D474[0], display_8008B4D8.h_E / 2 + screenOffset_8008D474[1]);
    SetGeomScreen(geomScreenDistance_8008B548);
    do
    {
        WAIT_INTERRUPT();
    } while (vsyncCounter_8008B4B4 < display_8008B4D8.vsyncsPerFrame_4);
    if (unknownFlags_8008D678 & 0x20)
    {
        ResetGraph(1);
#ifdef __psyz /* no interlaced fields to wait for (PSY-Z's GPU status has no odd/even bit) */
        ode = !ODEIsEvenAddressDrawn_800918C0;
#else
        do
        {
            ode = GetODE();
        } while (ODEIsEvenAddressDrawn_800918C0 == ode);
#endif
        ODEIsEvenAddressDrawn_800918C0 = ode;
    }
    vsyncCounter_8008B4B4 = 0;
    vsyncCounter_8008B4B4 = 0;
}
int WaitVSync_8001B6E8()
{
    int snapshot = vsyncCounter_8008B4B4;
    do
    {
        WAIT_INTERRUPT();
    } while (vsyncCounter_8008B4B4 <= snapshot);
    return gnFrame_8008D610;
}
void StartDisplay_8001B714(void)
{
    if ((unsigned int)displayStartFrames_800918BC < 2)
    {
        if (displayStartFrames_800918BC == 0)
        {
            InitEnvironments_8001B7B4();
            WaitVSync_8001B6E8(0);
            ODEIsEvenAddressDrawn_800918C0 = GetODE() == 0;
        }
        displayStartFrames_800918BC = displayStartFrames_800918BC + 1;
        unknownFlags_8008D678 &= ~0x10;
    }
    else
    {
        unknownFlags_8008D678 &= ~0x40;
        unknownFlags_8008D678 |= 0x10;
    }
}
extern DRAWENV drawEnv_8008D698[2];
extern DISPENV dispEnv_8008D750[2];
void InitEnvironments_8001B7B4(void)
{
    int interlace;
    int off;
    display_8008B4D8.w_C = screenModes_8007C728[display_8008B4D8.mode_0][0];
    display_8008B4D8.h_E = screenModes_8007C728[display_8008B4D8.mode_0][1];
    if (display_8008B4D8.h_E == 480)
    {
        off = 0;
        interlace = 1;
        unknownFlags_8008D678 |= 0x20;
    }
    else
    {
        off = 240;
        interlace = 0;
        unknownFlags_8008D678 &= ~0x20;
    }
    SetDefDrawEnv(&drawEnv_8008D698[0], display_8008B4D8.x_8, display_8008B4D8.y_A, display_8008B4D8.w_C, display_8008B4D8.h_E);
    SetDefDispEnv(&dispEnv_8008D750[0], display_8008B4D8.x_8, display_8008B4D8.y_A + off, display_8008B4D8.w_C, display_8008B4D8.h_E);
    SetDefDrawEnv(&drawEnv_8008D698[1], display_8008B4D8.x_8, display_8008B4D8.y_A + off, display_8008B4D8.w_C, display_8008B4D8.h_E);
    SetDefDispEnv(&dispEnv_8008D750[1], display_8008B4D8.x_8, display_8008B4D8.y_A, display_8008B4D8.w_C, display_8008B4D8.h_E);
    drawEnv_8008D698[1].isbg = 1;
    drawEnv_8008D698[0].isbg = 1;
    drawEnv_8008D698[1].dtd = 1;
    drawEnv_8008D698[0].dtd = 1;
    dispEnv_8008D750[1].isinter = interlace;
    dispEnv_8008D750[0].isinter = interlace;
    dispEnv_8008D750[1].isrgb24 = 0;
    dispEnv_8008D750[0].isrgb24 = 0;
    screenOffset_8008D474[0] = display_8008B4D8.x_8;
    screenOffset_8008D474[1] = display_8008B4D8.y_A;
    SetGeomOffset(display_8008B4D8.w_C / 2 + screenOffset_8008D474[0], display_8008B4D8.h_E / 2 + screenOffset_8008D474[1]);
    SetGeomScreen(geomScreenDistance_8008B548);
    SetFarColor(0, 0, 0);
}
void InitSprt_8001B9A0(int buffer)
{
    SPRT sprt;
    DR_TPAGE tpage;
    int x;
    int y;
    int top;
    int tp;
    if (unknownFlags_8008D678 & 0x20)
    {
        return;
    }
    SetSprt(&sprt);
    sprt.r0 = 0x80;
    sprt.g0 = 0x80;
    sprt.b0 = 0x80;
    sprt.w = 0x40;
    sprt.h = 0x40;
    SetShadeTex(&sprt, 1);
    if (buffer)
    {
        top = display_8008B4D8.y_A;
    }
    else
    {
        top = 0x100;
    }
    for (y = 0; y < display_8008B4D8.h_E; y += 0x40)
    {
        for (x = 0; x < display_8008B4D8.w_C; x += 0x40)
        {
            sprt.x0 = x;
            sprt.y0 = y;
            sprt.u0 = (display_8008B4D8.x_8 + x) % 64;
            sprt.v0 = y + top;
            AddPrimCopy_80040298(pOT_8008D78C, &sprt, sizeof(sprt) / 4);
            tp = GetTPage(2, 0, (display_8008B4D8.x_8 + x) / 64 * 64, top);
            setDrawTPage(&tpage, 0, 0, tp);
            AddPrimCopy_80040298(pOT_8008D78C, &tpage, sizeof(tpage) / 4);
        }
    }
}
void FadeToBlackStep_8001BB28(void)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* display;
    unsigned short w;
    unsigned short h;
    SetPolyF4(&poly);
    display = (unsigned short*)&display_8008B4D8;
    w = display[6];
    h = display[7];
    poly.r0 = 8;
    poly.g0 = 8;
    poly.b0 = 8;
    poly.x0 = 0;
    poly.y0 = 0;
    poly.x1 = w;
    poly.y1 = 0;
    poly.x2 = 0;
    poly.y2 = h;
    poly.x3 = w;
    poly.y3 = h;
    SetSemiTrans(&poly, 1);
    AddPrimCopy_80040298(pOT_8008D78C, &poly, sizeof(poly) / 4);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000240;
    AddPrimCopy_80040298(pOT_8008D78C, &dr, sizeof(dr) / 4);
    fadeFrame_800918B4++;
    if ((unsigned int)fadeFrame_800918B4 > 0x20)
    {
        fadeFlags_800918B0 &= ~1;
    }
}
void FadeToWhiteStep_8001BC00(void)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* display;
    unsigned short w;
    unsigned short h;
    SetPolyF4(&poly);
    display = (unsigned short*)&display_8008B4D8;
    w = display[6];
    h = display[7];
    poly.r0 = 8;
    poly.g0 = 8;
    poly.b0 = 8;
    poly.x0 = 0;
    poly.y0 = 0;
    poly.x1 = w;
    poly.y1 = 0;
    poly.x2 = 0;
    poly.y2 = h;
    poly.x3 = w;
    poly.y3 = h;
    SetSemiTrans(&poly, 1);
    AddPrimCopy_80040298(pOT_8008D78C, &poly, sizeof(poly) / 4);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000220;
    AddPrimCopy_80040298(pOT_8008D78C, &dr, sizeof(dr) / 4);
    fadeFrame_800918B4++;
    if ((unsigned int)fadeFrame_800918B4 > 0x20)
    {
        fadeFlags_800918B0 &= ~2;
    }
}
void SetMotionBlur_8001BCD8(int on)
{
    motionBlurOn_800918C4 = on;
}
void DrawMotionBlur_8001BCE4(int buffer)
{
    SPRT sprt;
    DR_TPAGE tpage;
    DR_STP stp;
    int x;
    int y;
    int top;
    int tp;
    if (unknownFlags_8008D678 & 0x20)
    {
        return;
    }
    SetDrawStp(&stp, 1);
    AddPrimCopy_80040298(pOT_8008D4AC + 3, &stp, sizeof(stp) / 4);
    SetDrawStp(&stp, 0);
    AddPrimCopy_80040298(pOT_8008D4AC, &stp, sizeof(stp) / 4);
    SetSprt(&sprt);
    sprt.r0 = 0x80;
    sprt.g0 = 0x80;
    sprt.b0 = 0x80;
    sprt.w = 0x40;
    sprt.h = 0x40;
    SetShadeTex(&sprt, 1);
    SetSemiTrans(&sprt, 1);
    if (buffer)
    {
        top = display_8008B4D8.y_A;
    }
    else
    {
        top = 0x100;
    }
    for (y = 0; y < display_8008B4D8.h_E; y += 0x40)
    {
        for (x = 0; x < display_8008B4D8.w_C; x += 0x40)
        {
            sprt.x0 = x;
            sprt.y0 = y;
            sprt.u0 = (display_8008B4D8.x_8 + x) % 64;
            sprt.v0 = y + top;
            AddPrimCopy_80040298(pOT_8008D4AC + 1, &sprt, sizeof(sprt) / 4);
            tp = GetTPage(2, 0, (display_8008B4D8.x_8 + x) / 64 * 64, top);
            setDrawTPage(&tpage, 0, 0, tp);
            AddPrimCopy_80040298(pOT_8008D4AC + 1, &tpage, sizeof(tpage) / 4);
        }
    }
}
void LoadDecodedImage_8001BEC8(void)
{
    RECT rect;
    unsigned int* data = decodedImageData_8008B4A0; // MDEC output words
    rect.w = 0x10;
    rect.h = 0x40;
    rect.y = 0x100;
    rect.x = 0x240;
    do
    {
        DecDCTout((void*)data, 0x200);
        DecDCToutSync(0);
        LoadImage(&rect, (void*)data);
        rect.x += 0x10;
        data += 0x200;
    } while (rect.x < 0x280);
}
void ProcessPads_8001BF50(void)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        ProcessPad_8001C8E8(i);
        UpdatePadVibration_80036820(i);
    }
}
void InitPrimBuffers_8001BF90(void)
{
    if (unknownFlags_8008D678 & 0x200)
    {
        primAllocPtr_800960A8[0] = PRIM_RAM(primBufferOffset_8008B550 + 0x801B9250);
        primBufferStart_800960A0[0] = PRIM_RAM(primBufferOffset_8008B550 + 0x801B9250);
        primAllocPtr_800960A8[1] = PRIM_RAM(0x801FC000 - ((unsigned int)(0x42DB0 - primBufferOffset_8008B550) >> 1));
        primBufferStart_800960A0[1] = PRIM_RAM(0x801FC000 - ((unsigned int)(0x42DB0 - primBufferOffset_8008B550) >> 1));
    }
    else
    {
        primAllocPtr_800960A8[0] = PRIM_RAM(0x801D4000);
        primBufferStart_800960A0[0] = PRIM_RAM(0x801D4000);
        primAllocPtr_800960A8[1] = PRIM_RAM(0x801E8000);
        primBufferStart_800960A0[1] = PRIM_RAM(0x801E8000);
    }
}
void StartScreenFlash_8001C02C(unsigned char* rgb)
{
    EventEntry* entry = AllocEventEntry_80043AF8(screenFlashTasks_8008D61C);
    if (entry != 0)
    {
        unsigned char* buf = (unsigned char*)entry->buffer;
        entry->flags = (entry->flags | 1) & ~0x8000;
        *(int*)buf = 0;
        buf[4] = rgb[0];
        buf[5] = rgb[1];
        buf[6] = rgb[2];
        entry->cb_8 = (EventEntryFn)ScreenFlashTask_8001C0B4;
    }
}
void ScreenFlashTask_8001C0B4(EventEntry* entry, int* state)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* display;
    unsigned short w;
    unsigned short h;
    unsigned char* bytes = (unsigned char*)state;
    state[0]++;
    if (state[0] >= 4)
    {
        entry->flags = (entry->flags & ~1) | 0x8000;
        return;
    }
    SetPolyF4(&poly);
    poly.r0 = bytes[4];
    poly.g0 = bytes[5];
    poly.b0 = bytes[6];
    display = (unsigned short*)&display_8008B4D8;
    w = display[6];
    h = display[7];
    poly.x0 = 0;
    poly.y0 = 0;
    poly.x1 = w;
    poly.y1 = 0;
    poly.x2 = 0;
    poly.y2 = h;
    poly.x3 = w;
    poly.y3 = h;
    SetSemiTrans(&poly, 0);
    AddPrimCopy_80040298(pOT_8008D5F4, &poly, sizeof(poly) / 4);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000220;
    AddPrimCopy_80040298(pOT_8008D5F4, &dr, sizeof(dr) / 4);
}
void SetFadeMode_8001C19C(unsigned int mode, int frames) // frames is unused
{
    switch (mode)
    {
    case 0:
        BeginFade_8001C260();
        break;
    case 1:
        BeginFade_8001C260();
        StartFadeToBlack_8001C2CC();
        break;
    case 2:
        BeginFade_8001C260();
        StartFadeToWhite_8001C2E4();
        break;
    case 3:
        EndFade_8001C290();
        break;
    }
}
void FreezeScreen_8001C224(void)
{
    unknownFlags_8008D678 |= 8;
    frozenFrames_800918B8 = 0;
}
void CancelFade_8001C244(void)
{
    unknownFlags_8008D678 &= ~2;
}
void BeginFade_8001C260(void)
{
    if (!(unknownFlags_8008D678 & 2))
    {
        unknownFlags_8008D678 |= 2;
    }
}
void EndFade_8001C290(void)
{
    unknownFlags_8008D678 &= ~2;
    unknownFlags_8008D678 |= 0x10;
    unknownFlags_8008D678 |= 0x80;
}
void StartFadeToBlack_8001C2CC(void)
{
    fadeFlags_800918B0 = 1;
    fadeFrame_800918B4 = 0;
}
void StartFadeToWhite_8001C2E4(void)
{
    fadeFlags_800918B0 = 2;
    fadeFrame_800918B4 = 0;
}
int IsFadeDone_8001C2FC()
{
    return (fadeFlags_800918B0 & 3) == 0;
}
IdEntry* FindItemById_8001C314(IdEntryList* list, int id)
{
    IdEntry* found = 0;
    int i;
    for (i = 0; i < list->count; i++)
    {
        if (id == list->items[i].id)
        {
            found = &list->items[i];
        }
    }
    return found;
}
void PlayAnimFrameSfx_8001C364(Model* model, int idx, int frame)
{
    ModelAnim* anim = &model->anims_54[idx];
    int i;
    for (i = 0; i < anim->cueCount_C; i++)
    {
        ModelAnimCue* cue = (ModelAnimCue*)(i * sizeof(ModelAnimCue) + (long)anim->cues_10); // integer sum: the original adds the base second
        if (frame == cue->frame_0 && cue->kind_2 == 0)
        {
            unsigned int cueIdx = (unsigned short)cue->arg_4;
            if (cueIdx < 0x6E)
            {
                SoundCue* sound = &soundCues_8007C750[(short)cueIdx];
                if (sound->kind == 0)
                {
                    PlaySfx_80031494(sound->arg);
                }
            }
        }
    }
}
void RunAnimFrameCues_8001C440(Model* model, int idx, int frame)
{
    ModelAnim* anim = (ModelAnim*)(idx * sizeof(ModelAnim) + (long)model->anims_54); // integer sum: the original adds the base second
    ModelAnimCue* cue = anim->cues_10;
    int n = anim->cueCount_C;
    int i;
    short arg;
    for (i = 0; i < n; i++, cue++)
    {
        if (frame != cue->frame_0)
        {
            continue;
        }
        switch (cue->kind_2)
        {
        case 0:
            if ((unsigned short)cue->arg_4 < 0x6E)
            {
                if (soundCues_8007C750[cue->arg_4].kind == 0)
                {
                    PlaySfx_80031494(soundCues_8007C750[cue->arg_4].arg);
                }
                if (soundCues_8007C750[cue->arg_4].kind == 1)
                {
                    PlayMusic_800300E0(soundCues_8007C750[cue->arg_4].arg, 1);
                }
                if (soundCues_8007C750[cue->arg_4].kind == 2)
                {
                    arg = soundCues_8007C750[cue->arg_4].arg;
                    if (soundCues_8007C750[cue->arg_4].arg == 3)
                    {
                        arg = (char)saveData_8008B570.levantStatus_7C8.level_44 >> 2;
                        if (arg > 4)
                        {
                            arg = 4;
                        }
                        arg = levelSeqsCue3_8007CACC[arg];
                    }
                    else if (soundCues_8007C750[cue->arg_4].arg == 2)
                    {
                        arg = (char)saveData_8008B570.levantStatus_7C8.level_44 >> 2;
                        if (arg > 4)
                        {
                            arg = 4;
                        }
                        arg = levelSeqsCue2_8007CAC0[arg];
                    }
                    PlaySeqSlot_80031160(arg, 1);
                }
                if (soundCues_8007C750[cue->arg_4].kind == 3)
                {
                    if (systemSound_80091D40.seqNum_4 >= 0)
                    {
                        SsSepSetDecrescendo(systemSound_80091D40.sepAccessNum_C, systemSound_80091D40.seqNum_4, 0x7F, 0x78);
                        systemSound_80091D40.seqNum_4 = -1;
                    }
                }
            }
            break;
        case 1:
            SetModelFtg_80025B5C(model, cue->arg_4, cue->arg_6);
            break;
        }
    }
}
void ResetPadAnalogMax_8001C69C(void)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        padAnalogMax_800918E0[i][1] = 0;
        padAnalogMax_800918E0[i][0] = 0;
    }
}
void ResetButtonConfig_8001C6C8(void)
{
    unsigned short* config = saveData_8008B570.buttonConfig_8;
    int i = 0;
    unsigned short* defaults = defaultButtonConfig_8007CAF4;
    for (; i < 10; i++)
    {
        SetButtonConfigEntry_8001C810((short*)config++, *defaults++);
    }
}
int TestAnyBits_8001C72C(unsigned int value, unsigned int mask)
{
    return (value & (unsigned short)mask) != 0;
}
int TestAllBits_8001C73C(unsigned int value, unsigned int mask)
{
    mask = (unsigned short)mask;
    if (mask == 0)
    {
        return 0;
    }
    return (value & mask) == mask;
}
int FindButtonConfig_8001C75C(unsigned int button)
{
    unsigned short* config = saveData_8008B570.buttonConfig_8;
    int i = 0;
    unsigned int value = (unsigned short)button;
    for (; i < 10; i++)
    {
        if (*config == value)
        {
            return i;
        }
        config++;
    }
    return -1;
}
void SwapButtonConfig_8001C79C(int i, int j)
{
    unsigned short* base = saveData_8008B570.buttonConfig_8;
    unsigned short* entryI = &base[i];
    unsigned short bi = GetButtonConfigEntry_8001C818(entryI);
    unsigned short* entryJ = &base[j];
    unsigned short bj = GetButtonConfigEntry_8001C818(entryJ);
    SetButtonConfigEntry_8001C810((short*)entryI, bj);
    SetButtonConfigEntry_8001C810((short*)entryJ, bi);
}
void SetButtonConfigEntry_8001C810(short* entry, unsigned short button)
{
    *entry = button;
}
unsigned short GetButtonConfigEntry_8001C818(unsigned short* entry)
{
    return *entry;
}
int GetButtonConfigBitIndex_8001C824(int idx)
{
    int i;
    unsigned short button = GetButtonConfig_8001C874(idx);
    for (i = 0; i < 14; i++)
    {
        if (padButtonBits_8007CAD8[i] == button)
        {
            break;
        }
    }
    return i;
}
unsigned int GetButtonConfig_8001C874(int idx)
{
    unsigned short* config = saveData_8008B570.buttonConfig_8;
    int i;
    for (i = 0; i < idx; i++)
    {
        config++;
    }
    return *config;
}
unsigned int FirstPadButtonBit_8001C8A0(short mask)
{
    unsigned int found = 1;
    int i = 0;
    unsigned short* bits;
    int buttons = mask;
    bits = padButtonBits_8007CAD8;
    do
    {
        unsigned int bit = *bits;
        i++;
        if (buttons & bit)
        {
            found = bit;
            break;
        }
        bits++;
    } while (i < 10);
    return found;
}
void ProcessPad_8001C8E8(int port)
{
    int i;
    unsigned short delay;
    unsigned short rate;
    pads_800918E8[port][8] = 0;
    if (pads_800918E8[port][0] != 0xFF)
    {
        padPrevHeld_800918C8[port] = padHeld_800918D0[port];
        padHeld_800918D0[port] = ~((pads_800918E8[port][2] << 8) | pads_800918E8[port][3]);
        if (display_8008B4D8.vsyncsPerFrame_4 >= 2)
        {
            delay = 0x14;
            rate = 1;
        }
        else
        {
            delay = 0x28;
            rate = 2;
        }
        switch (pads_800918E8[port][1] >> 4)
        {
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 8:
            break;
        case 7:
            UpdatePadAnalog_8001CC04(port);
            if (pads_800918E8[port][8] == 1)
            {
                delay *= 2;
                rate = 0x10;
            }
            else if (pads_800918E8[port][8] == 2)
            {
                delay = delay * 1.5;
                rate = 8;
            }
        case 4:
            UpdatePadRepeat_8001CAF0(port, delay, rate);
            break;
        }
    }
    else
    {
        padHeld_800918D0[port] = 0;
        padPrevHeld_800918C8[port] = 0;
        padPressed_8009194C[port] = 0;
        padReleased_800918D4[port] = 0;
        padRepeat_800918CC[port] = 0;
        for (i = 0; i < 16; i++)
        {
            padHoldFrames_80091950[port][i] = 0;
        }
    }
}
// .rdata that follows the jump table of ProcessPad_8001C8E8 (the compiler's table is emitted between)
const char emptyName_80073234[4] = "";
const char aKlarrgas_80073238[20] = "\202j\202\214\202\201\202\222\202\222\202\207\202\201\202\223"; // Klarrgas
const char aYolga_8007324C[12] = "\202x\202\217\202\214\202\207\202\201"; // Yolga
const char aTimaios_80073258[16] = "\202s\202\211\202\215\202\201\202\211\202\217\202\223"; // Timaios
const char aSicanjal_80073268[20] = "\202r\202\211\202\203\202\201\202\216\202\212\202\201\202\214"; // Sicanjal
const char aKolna_8007327C[12] = "\202j\202\217\202\214\202\216\202\201"; // Kolna
const char aJeechwo_80073288[16] = "\202i\202\205\202\205\202\203\202\210\202\227\202\217"; // Jeechwo
const char aTicker_80073298[16] = "\202s\202\211\202\203\202\213\202\205\202\222"; // Ticker
const char aPalooja_800732A8[16] = "\202o\202\201\202\214\202\217\202\217\202\212\202\201"; // Palooja
const char aAttractSpores_800732B8[32] = "\202`\202\224\202\224\202\222\202\201\202\203\202\224\201@\202r\202\220\202\217\202\222\202\205\202\223"; // Attract Spores
const char aSleepSpores_800732D8[28] = "\202r\202\214\202\205\202\205\202\220\201@\202r\202\220\202\217\202\222\202\205\202\223"; // Sleep Spores
const char aSkeletonKey_800732F4[28] = "\202r\202\213\202\205\202\214\202\205\202\224\202\217\202\216\201@\202j\202\205\202\231"; // Skeleton Key
const char aMoonlightSilk_80073310[32] = "\202l\202\217\202\217\202\216\202\214\202\211\202\207\202\210\202\224\201@\202r\202\211\202\214\202\213"; // Moonlight Silk
const char aAngelwingSilk_80073330[32] = "\202`\202\216\202\207\202\205\202\214\202\227\202\211\202\216\202\207\201@\202r\202\211\202\214\202\213"; // Angelwing Silk
const char aFirstSnowSilk_80073350[32] = "\202e\202\211\202\222\202\223\202\224\201@\202r\202\216\202\217\202\227\201@\202r\202\211\202\214\202\213"; // First Snow Silk
const char aPearlSilk_80073370[24] = "\202o\202\205\202\201\202\222\202\214\201@\202r\202\211\202\214\202\213"; // Pearl Silk
const char aLilySilk_80073388[20] = "\202k\202\211\202\214\202\231\201@\202r\202\211\202\214\202\213"; // Lily Silk
const char aThunderSilk_8007339C[28] = "\202s\202\210\202\225\202\216\202\204\202\205\202\222\201@\202r\202\211\202\214\202\213"; // Thunder Silk
const char aCloudSilk_800733B8[24] = "\202b\202\214\202\217\202\225\202\204\201@\202r\202\211\202\214\202\213"; // Cloud Silk
const char aMaltySSeal2_800733D0[32] = "\202l\202\201\202\214\202\224\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Malty's Seal 2
const char aMaltySSeal1_800733F0[32] = "\202l\202\201\202\214\202\224\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Malty's Seal 1
const char aAgniSSeal2_80073410[28] = "\202`\202\207\202\216\202\211\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Agni's Seal 2
const char aAgniSSeal1_8007342C[28] = "\202`\202\207\202\216\202\211\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Agni's Seal 1
const char aVarySSeal2_80073448[28] = "\202u\202\201\202\222\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Vary's Seal 2
const char aVarySSeal1_80073464[28] = "\202u\202\201\202\222\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Vary's Seal 1
const char aUrvySSeal2_80073480[28] = "\202t\202\222\202\226\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Urvy's Seal 2
const char aUrvySSeal1_8007349C[28] = "\202t\202\222\202\226\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Urvy's Seal 1
const char aMaltySBlessing_800734B8[36] = "\202l\202\201\202\214\202\224\202\231\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Malty's Blessing
const char aAgniSBlessing_800734DC[32] = "\202`\202\207\202\216\202\211\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Agni's Blessing
const char aVarySBlessing_800734FC[32] = "\202u\202\201\202\222\202\231\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Vary's Blessing
const char aUrvySBlessing_8007351C[32] = "\202t\202\222\202\226\202\231\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Urvy's Blessing
const char aMirrorOfDeva_8007353C[32] = "\202l\202\211\202\222\202\222\202\217\202\222\201@\202\217\202\206\201@\202c\202\205\202\226\202\201"; // Mirror of Deva
const char aRingOfDeath_8007355C[28] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202c\202\205\202\201\202\224\202\210"; // Ring of Death
const char aRingOfStoning_80073578[32] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202r\202\224\202\217\202\216\202\211\202\216\202\207"; // Ring of Stoning
const char aRingOfSleep_80073598[28] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202r\202\214\202\205\202\205\202\220"; // Ring of Sleep
const char aRingOfVenom_800735B4[28] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202u\202\205\202\216\202\217\202\215"; // Ring of Venom
const char aIkariPowder_800735D0[28] = "\202h\202\213\202\201\202\222\202\211\201@\202o\202\217\202\227\202\204\202\205\202\222"; // Ikari Powder
const char aValerianPowder_800735EC[32] = "\202u\202\201\202\214\202\205\202\222\202\211\202\201\202\216\201@\202o\202\217\202\227\202\204\202\205\202\222"; // Valerian Powder
const char aTendaiUyaku_8007360C[28] = "\202s\202\205\202\216\202\204\202\201\202\211\201@\202t\202\231\202\201\202\213\202\225"; // Tendai Uyaku
const char aSpecialLiquor_80073628[32] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Special Liquor
const char aExcellentLiquor_80073648[36] = "\202d\202\230\202\203\202\205\202\214\202\214\202\205\202\216\202\224\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Excellent Liquor
const char aFineLiquor_8007366C[24] = "\202e\202\211\202\216\202\205\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Fine Liquor
const char aShabLiquor_80073684[24] = "\202r\202\210\202\201\202\202\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Shab Liquor
const char aIchishiOil_8007369C[24] = "\202h\202\203\202\210\202\211\202\223\202\210\202\211\201@\202n\202\211\202\214"; // Ichishi Oil
const char aBletillaOil_800736B4[28] = "\202a\202\214\202\205\202\224\202\211\202\214\202\214\202\201\201@\202n\202\211\202\214"; // Bletilla Oil
const char aKukumiraOil_800736D0[28] = "\202j\202\225\202\213\202\225\202\215\202\211\202\222\202\201\201@\202n\202\211\202\214"; // Kukumira Oil
const char aShishiudoOil_800736EC[28] = "\202r\202\210\202\211\202\223\202\210\202\211\202\225\202\204\202\217\201@\202n\202\211\202\214"; // Shishiudo Oil
const char aChestnutOil_80073708[28] = "\202b\202\210\202\205\202\223\202\224\202\216\202\225\202\224\201@\202n\202\211\202\214"; // Chestnut Oil
const char aGreatWalnut_80073724[28] = "\202f\202\222\202\205\202\201\202\224\201@\202v\202\201\202\214\202\216\202\225\202\224"; // Great Walnut
const char aBitterMugwort_80073740[32] = "\202a\202\211\202\224\202\224\202\205\202\222\201@\202l\202\225\202\207\202\227\202\217\202\222\202\224"; // Bitter Mugwort
const char aMetaMugwort_80073760[28] = "\202l\202\205\202\224\202\201\201|\202l\202\225\202\207\202\227\202\217\202\222\202\224"; // Meta-Mugwort
const char aMugwort_8007377C[16] = "\202l\202\225\202\207\202\227\202\217\202\222\202\224"; // Mugwort
const char aSecret3_8007378C[20] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202R"; // Secret 3
const char aSecret2_800737A0[20] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202Q"; // Secret 2
const char aSecret1_800737B4[20] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202P"; // Secret 1
const char aMerging3_800737C8[20] = "\202l\202\205\202\222\202\207\202\211\202\216\202\207\201@\202R"; // Merging 3
const char aMerging2_800737DC[20] = "\202l\202\205\202\222\202\207\202\211\202\216\202\207\201@\202Q"; // Merging 2
const char aMerging1_800737F0[20] = "\202l\202\205\202\222\202\207\202\211\202\216\202\207\201@\202P"; // Merging 1
const char aMagicUsage2_80073804[28] = "\202l\202\201\202\207\202\211\202\203\201@\202t\202\223\202\201\202\207\202\205\201@\202Q"; // Magic Usage 2
const char aMagicUsage1_80073820[28] = "\202l\202\201\202\207\202\211\202\203\201@\202t\202\223\202\201\202\207\202\205\201@\202P"; // Magic Usage 1
const char aKnowledge5_8007383C[24] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202T"; // Knowledge 5
const char aKnowledge4_80073854[24] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202S"; // Knowledge 4
const char aKnowledge3_8007386C[24] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202R"; // Knowledge 3
const char aKnowledge2_80073884[24] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202Q"; // Knowledge 2
const char aKnowledge1_8007389C[24] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202P"; // Knowledge 1
const char aSecretOfKilling_800738B4[36] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202\217\202\206\201@\202j\202\211\202\214\202\214\202\211\202\216\202\207"; // Secret of Killing
const char aSpiderWarp_800738D8[24] = "\202r\202\220\202\211\202\204\202\205\202\222\201@\202v\202\201\202\222\202\220"; // Spider Warp
const char aDragonflyWarp_800738F0[32] = "\202c\202\222\202\201\202\207\202\217\202\216\202\206\202\214\202\231\201@\202v\202\201\202\222\202\220"; // Dragonfly Warp
const char aBeetleWarp_80073910[24] = "\202a\202\205\202\205\202\224\202\214\202\205\201@\202v\202\201\202\222\202\220"; // Beetle Warp
const char aPupaKey_80073928[20] = "\202o\202\225\202\220\202\201\201@\202j\202\205\202\231"; // Pupa Key
const char aLarvaKey_8007393C[20] = "\202k\202\201\202\222\202\226\202\201\201@\202j\202\205\202\231"; // Larva Key
const char aMinionFang_80073950[24] = "\202l\202\211\202\216\202\211\202\217\202\216\201@\202e\202\201\202\216\202\207"; // Minion Fang
const char aKickleberry_80073968[24] = "\202j\202\211\202\203\202\213\202\214\202\205\202\202\202\205\202\222\202\222\202\231"; // Kickleberry
const char aDivineTablet_80073980[28] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202s\202\201\202\202\202\214\202\205\202\224"; // Divine Tablet
const char aJewelOfWind_8007399C[28] = "\202i\202\205\202\227\202\205\202\214\201@\202\217\202\206\201@\202v\202\211\202\216\202\204"; // Jewel of Wind
const char aJewelOfFire_800739B8[28] = "\202i\202\205\202\227\202\205\202\214\201@\202\217\202\206\201@\202e\202\211\202\222\202\205"; // Jewel of Fire
const char aJewelOfWater_800739D4[32] = "\202i\202\205\202\227\202\205\202\214\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222"; // Jewel of Water
const char aMahbuSCocoon_800739F4[32] = "\202l\202\201\202\210\202\202\202\225\201f\202\223\201@\202b\202\217\202\203\202\217\202\217\202\216"; // Mahbu's Cocoon
const char aMothKey_80073A14[20] = "\202l\202\217\202\224\202\210\201@\202j\202\205\202\231"; // Moth Key
const char aCaptureAmulet_80073A28[32] = "\202b\202\201\202\220\202\224\202\225\202\222\202\205\201@\202`\202\215\202\225\202\214\202\205\202\224"; // Capture Amulet
const char aChampionSBelt_80073A48[32] = "\202b\202\210\202\201\202\215\202\220\202\211\202\217\202\216\201f\202\223\201@\202a\202\205\202\214\202\224"; // Champion's Belt
const char aCalabasHerb_80073A68[28] = "\202b\202\201\202\214\202\201\202\202\202\201\202\223\201@\202g\202\205\202\222\202\202"; // Calabas Herb
const char aOcarina_80073A84[16] = "\202n\202\203\202\201\202\222\202\211\202\216\202\201"; // Ocarina
const char aSpiderKey_80073A94[24] = "\202r\202\220\202\211\202\204\202\205\202\222\201@\202j\202\205\202\231"; // Spider Key
const char aCalabasPowder_80073AAC[32] = "\202b\202\201\202\214\202\201\202\202\202\201\202\223\201@\202o\202\217\202\227\202\204\202\205\202\222"; // Calabas Powder
const char aDragonflyKey_80073ACC[28] = "\202c\202\222\202\201\202\207\202\217\202\216\202\206\202\214\202\231\201@\202j\202\205\202\231"; // Dragonfly Key
const char aBeetleKey_80073AE8[24] = "\202a\202\205\202\205\202\224\202\214\202\205\201@\202j\202\205\202\231"; // Beetle Key
const char aTearsOfReese_80073B00[32] = "\202s\202\205\202\201\202\222\202\223\201@\202\217\202\206\201@\202q\202\205\202\205\202\223\202\205"; // Tears of Reese
const char aFluteOfCapture_80073B20[36] = "\202e\202\214\202\225\202\224\202\205\201@\202\217\202\206\201@\202b\202\201\202\220\202\224\202\225\202\222\202\205"; // Flute of Capture
const char aHunterSEarring_80073B44[36] = "\202g\202\225\202\216\202\224\202\205\202\222\201f\202\223\201@\202d\202\201\202\222\202\222\202\211\202\216\202\207"; // Hunter's Earring
const char aIcicle_80073B68[16] = "\202h\202\203\202\211\202\203\202\214\202\205"; // Icicle
const char aAutumnMoon_80073B78[24] = "\202`\202\225\202\224\202\225\202\215\202\216\201@\202l\202\217\202\217\202\216"; // Autumn Moon
const char aDrainer_80073B90[16] = "\202c\202\222\202\201\202\211\202\216\202\205\202\222"; // Drainer
const char aReaper_80073BA0[16] = "\202q\202\205\202\201\202\220\202\205\202\222"; // Reaper
const char aPalemoon_80073BB0[20] = "\202o\202\201\202\214\202\205\202\215\202\217\202\217\202\216"; // Palemoon
const char aCloudcover_80073BC4[24] = "\202b\202\214\202\217\202\225\202\204\202\203\202\217\202\226\202\205\202\222"; // Cloudcover
const char aDragoncrest_80073BDC[24] = "\202c\202\222\202\201\202\207\202\217\202\216\202\203\202\222\202\205\202\223\202\224"; // Dragoncrest
const char aSpringBlossom_80073BF4[32] = "\202r\202\220\202\222\202\211\202\216\202\207\201@\202a\202\214\202\217\202\223\202\223\202\217\202\215"; // Spring Blossom
const char aTsunami_80073C14[16] = "\202s\202\223\202\225\202\216\202\201\202\215\202\211"; // Tsunami
const char aThunderbolt_80073C24[24] = "\202s\202\210\202\225\202\216\202\204\202\205\202\222\202\202\202\217\202\214\202\224"; // Thunderbolt
const char aBluePhantom_80073C3C[28] = "\202a\202\214\202\225\202\205\201@\202o\202\210\202\201\202\216\202\224\202\217\202\215"; // Blue Phantom
const char aNightglow_80073C58[20] = "\202m\202\211\202\207\202\210\202\224\202\207\202\214\202\217\202\227"; // Nightglow
const char aWhistler_80073C6C[20] = "\202v\202\210\202\211\202\223\202\224\202\214\202\205\202\222"; // Whistler
const char aLittleBird_80073C80[24] = "\202k\202\211\202\224\202\224\202\214\202\205\201@\202a\202\211\202\222\202\204"; // Little Bird
const char aWhiteHorn_80073C98[24] = "\202v\202\210\202\211\202\224\202\205\201@\202g\202\217\202\222\202\216"; // White Horn
const char aLifeStealer_80073CB0[28] = "\202k\202\211\202\206\202\205\201@\202r\202\224\202\205\202\201\202\214\202\205\202\222"; // Life Stealer
const char aIronAxe_80073CCC[20] = "\202h\202\222\202\217\202\216\201@\202`\202\230\202\205"; // Iron Axe
const char aIronSword_80073CE0[24] = "\202h\202\222\202\217\202\216\201@\202r\202\227\202\217\202\222\202\204"; // Iron Sword
const char aSwordOfSpeed_80073CF8[32] = "\202r\202\227\202\217\202\222\202\204\201@\202\217\202\206\201@\202r\202\220\202\205\202\205\202\204"; // Sword of Speed
const char aBronzeSword_80073D18[28] = "\202a\202\222\202\217\202\216\202\232\202\205\201@\202r\202\227\202\217\202\222\202\204"; // Bronze Sword
const char aAquazor_80073D34[16] = "\202`\202\221\202\225\202\201\202\232\202\217\202\222"; // Aquazor
const char aDagger_80073D44[16] = "\202c\202\201\202\207\202\207\202\205\202\222"; // Dagger
const char aKnife_80073D54[12] = "\202j\202\216\202\211\202\206\202\205"; // Knife
const char aDivineGarb2_80073D60[28] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202f\202\201\202\222\202\202\201@\202Q"; // Divine Garb 2
const char aDivineGarb1_80073D7C[28] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202f\202\201\202\222\202\202\201@\202P"; // Divine Garb 1
const char aForestGarb_80073D98[24] = "\202e\202\217\202\222\202\205\202\223\202\224\201@\202f\202\201\202\222\202\202"; // Forest Garb
const char aNavyBlueGarb_80073DB0[32] = "\202m\202\201\202\226\202\231\201@\202a\202\214\202\225\202\205\201@\202f\202\201\202\222\202\202"; // Navy Blue Garb
const char aBloodyGarb_80073DD0[24] = "\202a\202\214\202\217\202\217\202\204\202\231\201@\202f\202\201\202\222\202\202"; // Bloody Garb
const char aNagiGarb_80073DE8[20] = "\202m\202\201\202\207\202\211\201@\202f\202\201\202\222\202\202"; // Nagi Garb
const char aRiketzGarb_80073DFC[28] = "\202q\202\211\202\213\202\205\202\224\202\232\201f\201@\202f\202\201\202\222\202\202"; // Riketz' Garb
const char aDivineVest_80073E18[24] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202u\202\205\202\223\202\224"; // Divine Vest
const char aSilverVest_80073E30[24] = "\202r\202\211\202\214\202\226\202\205\202\222\201@\202u\202\205\202\223\202\224"; // Silver Vest
const char aReflectingVest_80073E48[32] = "\202q\202\205\202\206\202\214\202\205\202\203\202\224\202\211\202\216\202\207\201@\202u\202\205\202\223\202\224"; // Reflecting Vest
const char aPlateMailVest_80073E68[32] = "\202o\202\214\202\201\202\224\202\205\201@\202l\202\201\202\211\202\214\201@\202u\202\205\202\223\202\224"; // Plate Mail Vest
const char aWireVest_80073E88[20] = "\202v\202\211\202\222\202\205\201@\202u\202\205\202\223\202\224"; // Wire Vest
const char aChainMailVest_80073E9C[32] = "\202b\202\210\202\201\202\211\202\216\201@\202l\202\201\202\211\202\214\201@\202u\202\205\202\223\202\224"; // Chain Mail Vest
const char aLeatherVest_80073EBC[28] = "\202k\202\205\202\201\202\224\202\210\202\205\202\222\201@\202u\202\205\202\223\202\224"; // Leather Vest
const char aHunterSVest_80073ED8[28] = "\202g\202\225\202\216\202\224\202\205\202\222\201f\202\223\201@\202u\202\205\202\223\202\224"; // Hunter's Vest
const char aNagiBelt_80073EF4[20] = "\202m\202\201\202\207\202\211\201@\202a\202\205\202\214\202\224"; // Nagi Belt
const char aSuperChoker_80073F08[28] = "\202r\202\225\202\220\202\205\202\222\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Super Choker
const char aStoneChoker_80073F24[28] = "\202r\202\224\202\217\202\216\202\205\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Stone Choker
const char aSleepChoker_80073F40[28] = "\202r\202\214\202\205\202\205\202\220\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Sleep Choker
const char aPoisonChoker_80073F5C[28] = "\202o\202\217\202\211\202\223\202\217\202\216\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Poison Choker
const char aHawkRuff_80073F78[20] = "\202g\202\201\202\227\202\213\201@\202q\202\225\202\206\202\206"; // Hawk Ruff
const char aHollyRuff_80073F8C[24] = "\202g\202\217\202\214\202\214\202\231\201@\202q\202\225\202\206\202\206"; // Holly Ruff
const char aSilverCrown_80073FA4[28] = "\202r\202\211\202\214\202\226\202\205\202\222\201@\202b\202\222\202\217\202\227\202\216"; // Silver Crown
const char aIronBracelet_80073FC0[28] = "\202h\202\222\202\217\202\216\201@\202a\202\222\202\201\202\203\202\205\202\214\202\205\202\224"; // Iron Bracelet
const char aSparrowRuff_80073FDC[28] = "\202r\202\220\202\201\202\222\202\222\202\217\202\227\201@\202q\202\225\202\206\202\206"; // Sparrow Ruff
const char aRedBead_80073FF8[20] = "\202q\202\205\202\204\201@\202a\202\205\202\201\202\204"; // Red Bead
const char aYellowBead_8007400C[24] = "\202x\202\205\202\214\202\214\202\217\202\227\201@\202a\202\205\202\201\202\204"; // Yellow Bead
const char aGreenBead_80074024[24] = "\202f\202\222\202\205\202\205\202\216\201@\202a\202\205\202\201\202\204"; // Green Bead
const char aBlueBead_8007403C[20] = "\202a\202\214\202\225\202\205\201@\202a\202\205\202\201\202\204"; // Blue Bead
const char aSilverHeadband_80074050[32] = "\202r\202\211\202\214\202\226\202\205\202\222\201@\202g\202\205\202\201\202\204\202\202\202\201\202\216\202\204"; // Silver Headband
const char aIronHeadband_80074070[28] = "\202h\202\222\202\217\202\216\201@\202g\202\205\202\201\202\204\202\202\202\201\202\216\202\204"; // Iron Headband
const char aLeatherHeadband_8007408C[] = "\202k\202\205\202\201\202\224\202\210\202\205\202\222\201@\202g\202\205\202\201\202\204\202\202\202\201\202\216\202\204"; // Leather Headband
void UpdatePadRepeat_8001CAF0(int port, unsigned short delay, unsigned short rate)
{
    int i;
    unsigned short changed;
    unsigned short held;
    unsigned short bit;
    int tick;
    changed = padHeld_800918D0[port] ^ padPrevHeld_800918C8[port];
    padPressed_8009194C[port] = changed & padHeld_800918D0[port];
    padReleased_800918D4[port] = changed & ~padHeld_800918D0[port];
    padRepeat_800918CC[port] = padPressed_8009194C[port];
    held = padHeld_800918D0[port] & padPrevHeld_800918C8[port];
    tick = frameCount_8008D3FC & (rate - 1);
    for (i = 0; i < 16; i++)
    {
        bit = held & 1;
        held >>= 1;
        if (bit)
        {
            if (++padHoldFrames_80091950[port][i] >= delay && tick == 0)
            {
                padRepeat_800918CC[port] |= bit << i;
            }
        }
        else
        {
            padHoldFrames_80091950[port][i] = 0;
        }
    }
}
void UpdatePadAnalog_8001CC04(int port)
{
    signed char* stick;
    unsigned char* max;
    int value;
    int maxValue;
    padAnalog_800918D8[port][0] = pads_800918E8[port][4] + 0x80;
    padAnalog_800918D8[port][1] = 0x7F - pads_800918E8[port][5];
    padAnalog_800918D8[port][2] = pads_800918E8[port][6] + 0x80;
    padAnalog_800918D8[port][3] = 0x7F - pads_800918E8[port][7];
    stick = padAnalog_800918D8[port];
    max = padAnalogMax_800918E0[port];
    value = stick[0];
    maxValue = max[0];
    if (value < 0)
    {
        value = -value;
    }
    if (maxValue < value)
    {
        max[0] = value;
    }
    value = stick[1];
    maxValue = max[0];
    if (value < 0)
    {
        value = -value;
    }
    if (maxValue < value)
    {
        max[0] = value;
    }
    value = stick[2];
    maxValue = max[1];
    if (value < 0)
    {
        value = -value;
    }
    if (maxValue < value)
    {
        max[1] = value;
    }
    value = stick[3];
    maxValue = max[1];
    if (value < 0)
    {
        value = -value;
    }
    if (maxValue < value)
    {
        max[1] = value;
    }
}
void ResetPadHoldFrames_8001CD04(int port)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        padHoldFrames_80091950[port][i] = 0;
    }
}
int ReturnZero_8001CD34(void)
{
    return 0;
}
const char* GetPersonName_8001CD3C(int idx)
{
    return personNames_8007CB20[idx];
}
unsigned char* GetPersonMergeInfo_8001CD58(int idx)
{
    return personMergeInfo_8007CB4C[idx];
}
int GetPersonIcon_8001CD6C(int idx)
{
    return 0x36;
}
unsigned char* GetAccessoryModifiers_8001CD74(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return accessoryModifiers_8007D848[idx];
}
unsigned char* GetArmorModifiers_8001CDA0(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return armorModifiers_8007D598[idx];
}
unsigned char GetItemEffect_8001CDCC(unsigned int idx)
{
    if (idx < 0x2B)
    {
        return itemEffects_8007CC24[idx];
    }
    return 0x22;
}
ActionData* GetItemData_8001CDF4(unsigned int idx)
{
    if (idx < 0x2B)
    {
        return &itemData_8007CCA8[idx];
    }
    return 0;
}
const char* GetItemName_8001CE20(unsigned int idx)
{
    if (idx >= 0x2B)
    {
        return 0;
    }
    return itemNames_8007CB78[idx];
}
int ReturnZero_8001CE4C(void)
{
    return 0;
}
int GetItemPrice_8001CE54(int idx)
{
    return itemPrices_8007CED8[idx];
}
unsigned short GetItemFlags_8001CE70(int idx)
{
    return itemFlags_8007CC50[idx];
}
int GetItemTargetFlags_8001CE8C(int idx)
{
    unsigned short flags = itemFlags_8007CC50[idx];
    int targetFlags = (flags >> 5) & 2;
    if (flags & 0x80)
    {
        targetFlags |= 4;
    }
    if (flags & 4)
    {
        targetFlags |= 1;
    }
    return targetFlags;
}
unsigned char GetItemFlagsLow_8001CED0(int idx)
{
    return *(unsigned char*)&itemFlags_8007CC50[idx];
}
int ReturnOne_8001CEEC(void)
{
    return 1;
}
int* GetWeaponStatBonus_8001CEF4(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return (int*)weaponData_8007D04C[idx].statBonus_4;
}
const char* GetWeaponName_8001CF20(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return weaponNames_8007CFF0[idx];
}
int GetWeaponPrice_8001CF4C(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return weaponPrices_8007D388[idx] * 10;
}
EquipmentData* GetWeaponData_8001CF84(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return &weaponData_8007D04C[idx];
}
int* GetArmorStatBonus_8001CFB0(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return (int*)armorData_8007D420[idx].statBonus_4;
}
const char* GetArmorName_8001CFDC(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return armorNames_8007D3E4[idx];
}
int GetArmorPrice_8001D008(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return armorPrices_8007D64C[idx];
}
EquipmentData* GetArmorData_8001D034(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return &armorData_8007D420[idx];
}
int GetArmorOutfit_8001D060(int idx)
{
    return armorOutfits_8007D588[idx];
}
int* GetAccessoryStatBonus_8001D078(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return (int*)accessoryData_8007D6B0[idx].statBonus_4;
}
const char* GetAccessoryName_8001D0A4(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return accessoryNames_8007D66C[idx];
}
int GetAccessoryPrice_8001D0D0(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return accessoryPrices_8007D914[idx];
}
EquipmentData* GetAccessoryData_8001D0FC(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return &accessoryData_8007D6B0[idx];
}
const char* GetEquipmentName_8001D128(int idx, unsigned int kind)
{
    const char* name = NULL;
    switch (kind)
    {
    case 0:
        name = GetWeaponName_8001CF20(idx);
        break;
    case 1:
        name = GetArmorName_8001CFDC(idx);
        break;
    case 2:
        name = GetAccessoryName_8001D0A4(idx);
        break;
    }
    return name;
}
EquipmentData* GetEquipmentData_8001D190(unsigned int idx, unsigned int kind)
{
    EquipmentData* data = 0;
    switch (kind)
    {
    case 0:
        data = GetWeaponData_8001CF84(idx);
        break;
    case 1:
        data = GetArmorData_8001D034(idx);
        break;
    case 2:
        data = GetAccessoryData_8001D0FC(idx);
        break;
    }
    return data;
}
int GetEquipmentPrice_8001D1F8(int idx, unsigned int kind)
{
    int price = 0;
    switch (kind)
    {
    case 0:
        price = GetWeaponPrice_8001CF4C(idx);
        break;
    case 1:
        price = GetArmorPrice_8001D008(idx);
        break;
    case 2:
        price = GetAccessoryPrice_8001D0D0(idx);
        break;
    }
    return price;
}
ActionData* GetLevantWeaponAction_8001D260(void)
{
    unsigned int weapon = GetEquippedId_800AD990(0);
    if (weapon < 0x17)
    {
        return &weaponActions_8007D274[weapon];
    }
    return 0;
}
int GetItemIcon_8001D2AC(int idx)
{
    if (idx < 0x2B)
    {
        return itemIcons_8007CEAC[idx];
    }
    return 0xFF;
}
int GetEquipmentIcon_8001D2D4(int idx, int kind)
{
    EquipmentData* data = GetEquipmentData_8001D190(idx, kind);
    if (data != 0)
    {
        return equipmentIcons_8007D938[data->icon_0];
    }
    return 0x24;
}
char* GetKeyItemName_8001D318(unsigned int idx)
{
    if (idx >= 0x26)
    {
        return 0;
    }
    return keyItemNames_8007CF30[idx];
}
int GetKeyItemIcon_8001D344(int idx)
{
    if (idx < 0x26)
    {
        return keyItemIcons_8007CFC8[idx];
    }
    return 0x24;
}
int IsKnowledgeKeyItem_8001D36C(int id)
{
    return (unsigned int)(id - 0x19) < 0xD;
}
void InitActors_8001D378(void)
{
    ResetModelLoader_800204D0();
    StopModelLoader_800205F0();
    ClearModelAnimRefs_800201A4();
    ListInit_8003FDB0(&actorHeap_80091990);
    StopAllEventEntries_80043B40(actorTasks_8008D43C);
}
void FreeActors_8001D3C4(int freeModels)
{
    if (freeModels != 0)
    {
        StopModelLoader_800205F0();
        FreeModelLoaderList_8002052C();
        ResetModelLoader_800204D0();
    }
    ListFreeAll_8003FEC8(&actorHeap_80091990);
    StopAllEventEntries_80043B40(actorTasks_8008D43C);
    ClearModelAnimRefs_800201A4();
}
void UpdateActorCb_8001D41C(EventEntry* entry, void* actor)
{
    UpdateActorScript_8001EA28(actor);
    UpdateActorMotion_8001F354(actor);
    UpdateActorAnimLoad_8001F918(actor);
    UpdateActor_8001F9AC(actor);
}
Actor* CreateActor_8001D45C(ActorDesc* desc)
{
    EventEntry* entry = AllocEventEntry_80043AF8(actorTasks_8008D43C);
    Actor* actor;
    if (entry != 0)
    {
        actor = entry->buffer;
        entry->cb_8 = UpdateActorCb_8001D41C;
        entry->flags = (entry->flags | 1) & ~0x8000;
        actor->task_0 = entry;
        InitActor_8001E574(actor, desc);
        return actor;
    }
    return 0;
}
Actor* CloneActor_8001D4DC(Actor* src, int kind, int clutRow, int hasMatrices)
{
    ActorDesc desc;
    Actor* clone;
    desc.model_48 = src->model_15C;
    desc.modelId_0 = -1;
    desc.kind_4 = kind;
    desc.pos_8[0] = src->pos_38[0];
    desc.pos_8[1] = src->pos_38[1];
    desc.pos_8[2] = src->pos_38[2];
    desc.rot_14[0] = src->rot_5C[0];
    desc.rot_14[1] = src->rot_5C[1];
    desc.rot_14[2] = src->rot_5C[2];
    desc.clutRow_1C = clutRow;
    desc.animIdx_20 = src->animIdx_C2;
    desc.frame_24 = src->frame_90;
    desc.frameSpeed_28 = src->frameSpeed_1E;
    desc.blendDiv_2C = src->blendDiv_24;
    desc.visible_30 = ((src->flags_4 >> 13) ^ 1) & 1;
    desc.bones_34 = src->bones_134;
    desc.baseScale_38 = src->baseScale_138;
    desc.boneScale_3C = src->boneScale_144;
    desc.anims_40 = src->anims_148;
    desc.effectTbl_44 = src->effectTbl_14C;
    desc.hasMatrices_4C = hasMatrices;
    clone = CreateActor_8001D45C(&desc);
    SetActorGroundMove_8001D68C(clone, (src->flags_4 >> 18) & 1);
    return clone;
}
void DestroyActor_8001D600(Actor* actor)
{
    EventEntry* entry = actor->task_0;
    ReleaseModelAnimRef_80020278(actor->modelRef_16, entry->index_4);
    FreeActorBones_8001EA00(actor);
    entry->flags = (entry->flags & ~1) | 0x8000;
}
void SetActorActive_8001D658(Actor* actor, int on)
{
    EventEntry* entry = actor->task_0;
    if (on)
    {
        entry->flags &= 0xFFFF7FFF;
    }
    else
    {
        entry->flags |= 0x8000;
    }
}
void SetActorGroundMove_8001D68C(Actor* actor, int on)
{
    if (on)
    {
        actor->flags_4 |= 0x40000;
    }
    else
    {
        actor->flags_4 &= ~0x40000;
    }
}
void SetActorRootMotion_8001D6BC(Actor* actor, int on)
{
    if (on)
    {
        actor->flags_4 |= 0x1000000;
    }
    else
    {
        actor->flags_4 &= ~0x1000000;
    }
}
void SetActorAnimPaused_8001D6EC(Actor* actor, int on)
{
    if (on)
    {
        actor->flags_4 |= 4;
    }
    else
    {
        actor->flags_4 &= ~4;
    }
}
void RestartActorMotion_8001D71C(Actor* actor)
{
    actor->flags_4 |= 8;
}
void SetActorVisible_8001D730(Actor* actor, int on)
{
    if (on)
    {
        actor->flags_4 &= ~0x2000;
    }
    else
    {
        actor->flags_4 |= 0x2000;
    }
}
void SetActorAnim_8001D760(Actor* actor, int idx, int mode, int restart)
{
    int base;
    actor->animIdx_C2 = idx;
    actor->prevAnim_A0 = actor->anim_9C;
    actor->anim_9C = actor->anims_148[idx].id_0;
    actor->loopFrame_18 = actor->anims_148[idx].loop_4;
    actor->endFrame_1A = actor->anims_148[idx].end_6;
    actor->prevFrame_94 = actor->frame_90;
    if (mode == -1)
    {
        actor->frame_90 = actor->anims_148[idx].start_2;
    }
    else if (mode == -2)
    {
        actor->frame_90 = actor->anims_148[idx].loop_4;
    }
    else if (mode == -3)
    {
        int rnd = rand();
        base = actor->anims_148[idx].start_2;
        actor->frame_90 = base + rnd % (actor->anims_148[idx].loop_4 - base);
    }
    else
    {
        actor->frame_90 = mode % actor->endFrame_1A;
    }
    actor->frameFrac_1C = 0;
    actor->blend_AC = 0;
    actor->flags_4 |= 8;
    if (restart)
    {
        actor->flags_4 |= 0x10;
    }
}
int IsActorAnimLoadIdle_8001D8A8(Actor* actor)
{
    return actor->animLoadState_10 == 0;
}
void RequestActorAnim_8001D8B4(Actor* actor, int idx)
{
    if (actor->anims_148[idx].kind_1 == 0)
    {
        if (RequestModelAnim_8002032C(actor->modelRef_16, actor->task_0->index_4, actor->anims_148[idx].id_0))
        {
            actor->animLoading_14 = idx;
            actor->animLoadState_10 = 2;
        }
    }
}
void ReleaseActorAnim_8001D92C(Actor* actor, int idx)
{
    ActorAnim* anim;
    int i;
    int key;
    int count;
    anim = actor->anims_148;
    key = anim[idx].id_0;
    count = ((int*)anim)[-1];
    for (i = 0; i < count; i++)
    {
        if (key == anim->id_0 && anim->kind_1 == 1)
        {
            return;
        }
        anim++;
    }
    ReleaseModelAnim_800203B0(actor->modelRef_16, actor->task_0->index_4, key);
}
void SkipActorAnimToEnd_8001D9B0(Actor* actor)
{
    if (!(actor->flags_D4 & 2))
    {
        actor->frame_90 = actor->endFrame_1A;
        actor->frameFrac_1C = 0;
        actor->flags_4 |= 0x4000;
    }
}
void StartActorFadeIn_8001D9E4(Actor* actor, int div, int flags)
{
    actor->fade_20 = 0;
    actor->fadeDiv_22 = div;
    actor->flags_4 |= 0x20;
    actor->flags_4 |= flags;
    actor->flags_4 &= ~0x40;
}
void StartActorFadeOut_8001DA08(Actor* actor, int div, int flags)
{
    actor->fade_20 = 0;
    actor->fadeDiv_22 = div;
    actor->flags_4 |= 0x40;
    actor->flags_4 |= flags;
    actor->flags_4 &= ~0x20;
}
void StopActorFade_8001DA2C(Actor* actor)
{
    actor->fade_20 = 0;
    actor->fadeDiv_22 = 0;
    actor->flags_4 &= 0xBFFFF81F;
}
void StartActorScale_8001DA4C(Actor* actor, int div, int from, int to)
{
    if (from < 0)
    {
        from = actor->scale_26;
    }
    if (to < from)
    {
        actor->scaleStep_28 = (from - to) / div;
        actor->scale_26 = from;
        actor->scaleTarget_2A = to;
        actor->flags_4 |= 1;
    }
    else
    {
        actor->scaleStep_28 = (to - from) / div;
        actor->scale_26 = from;
        actor->scaleTarget_2A = to;
        actor->flags_4 |= 3;
    }
}
void SetActorTint_8001DAAC(Actor* actor, short* tint)
{
    if (tint != 0)
    {
        actor->flags_4 |= 0x800;
        TintVramImage_800292D0(&actor->image_150, actor->clut_158, tint);
    }
    else
    {
        actor->flags_4 &= ~0x800;
    }
}
void SetActorTurnTarget_8001DB00(Actor* actor, int* target, int step)
{
    if (target != 0)
    {
        actor->target_70.vx = target[0];
        actor->target_70.vy = target[1];
        actor->target_70.vz = target[2];
        actor->target_70.pad = step;
        actor->flags_4 |= 0x4000000;
    }
    else
    {
        actor->flags_4 &= ~0x4000000;
    }
}
void SetActorSpeedScale_8001DB58(Actor* actor, int scale, int on)
{
    if (on)
    {
        actor->speedScale_8C = scale;
        actor->flags_4 |= 0x20000000;
    }
    else
    {
        actor->speedScale_8C = 0x1000;
        actor->flags_4 &= ~0x20000000;
    }
}
void SetActorScript_8001DB98(Actor* actor, unsigned char* script)
{
    unsigned char* cmd;
    short old = actor->animIdx_C2;
    actor->animIdx_C2 = -1;
    actor->scriptPos_C4 = 0;
    actor->scriptLen_C6 = 1;
    actor->wait_C8 = 0;
    actor->waitLen_CA = 0;
    actor->fCC = -1;
    actor->fCE = -1;
    actor->script_D0 = (ActorScriptCmd*)script;
    actor->flags_4 &= ~0x8000;
    actor->flags_4 |= 0x4000;
    actor->prevAnimIdx_C0 = old;
    cmd = script;
    while (cmd[0] != 0)
    {
        actor->scriptLen_C6 += cmd[1];
        cmd += cmd[1] * 4;
    }
}
void StartActorScript_8001DC34(void* actor, void* script)
{
    SetActorScript_8001DB98(actor, script);
    RunActorScript_8001EA48(actor);
}
int ApproachActorTarget_8001DC60(Actor* actor, VECTOR* target, int turnStep, int range)
{
    unsigned int dist;
    int curZ = actor->pos_38[2];
    int prevZ = actor->prevPos_44[2];
    int dz;
    int nearDist;
    dist = 0xFFF;
    if (prevZ < curZ)
    {
        dz = curZ - prevZ;
    }
    else
    {
        dz = prevZ - curZ;
    }
    if (IsWithinDistance_8003B740(actor->pos_38, (int*)&target->vx, &dist))
    {
        if (dist < dz * dz)
        {
            return 1;
        }
    }
    nearDist = dz + 0x32;
    if (dist < nearDist * nearDist)
    {
        if (IsActorNear_8001DFC8(actor, target, range, 1))
        {
            return 1;
        }
    }
    TurnActorTowards_8001DDFC(actor, target, turnStep);
    return 0;
}
int TurnActorBy_8001DD44(Actor* actor, int dir, int amount, int maxStep)
{
    int step;
    int left;
    step = amount;
    if (amount >= maxStep)
    {
        step = maxStep;
    }
    if (dir == 1)
    {
        actor->turn_194.input_8 = step;
    }
    else
    {
        actor->turn_194.input_8 = -step;
    }
    RestartActorMotion_8001D71C(actor);
    FirFilterStep_80014588(actor->turnFilterBuf_1A4, &actor->turn_194, frameCount_8008D3FC);
    actor->rot_5C[1] += actor->turn_194.output_C.low;
    left = amount - maxStep;
    return left < 0 ? 0 : (amount < left ? amount : left);
}
int TurnActorTowards_8001DDFC(Actor* actor, VECTOR* target, int step)
{
    VECTOR delta;
    int angle;
    delta.vx = target->vx - actor->pos_38[0];
    delta.vz = target->vz - actor->pos_38[2];
    angle = (ratan2_8003B548(delta.vx, delta.vz) - actor->rot_5C[1]) & 0xFFF;
    actor->turn_194.input_8 = 0;
    if (angle < step || angle >= 0x1000 - step)
    {
        actor->rot_5C[1] += angle;
        return 1;
    }
    if (angle < 0x800)
    {
        actor->turn_194.input_8 = step;
    }
    else
    {
        actor->turn_194.input_8 = -step;
    }
    FirFilterStep_80014588(actor->turnFilterBuf_1A4, &actor->turn_194, frameCount_8008D3FC);
    actor->rot_5C[1] += actor->turn_194.output_C.low;
    return 0;
}
int FindActorInFront_8001DECC(Actor* actor, int range, int checkLevant)
{
    EventNode* node;
    EventEntry* entry;
    int count;
    int i;
    int found = 0;
    range = range * range;
    if (checkLevant)
    {
        found = IsInFrontWithinRange_8001E0F4((VECTOR*)actor->pos_38, actor->rot_5C[1], (VECTOR*)&levantPos_8008BD18.pos, range);
    }
    if (found == 0)
    {
        node = actorTasks_8008D43C;
        count = node->count;
        for (i = 0; i < count; i++)
        {
            entry = &node->entry;
            if ((entry->flags & 0x8001) == 1 && actor->task_0 != ((Actor*)entry->buffer)->task_0)
            {
                found = IsInFrontWithinRange_8001E0F4((VECTOR*)actor->pos_38, actor->rot_5C[1], (VECTOR*)((Actor*)entry->buffer)->pos_38, range);
                if (found)
                {
                    break;
                }
            }
            node = node->next;
        }
    }
    return found;
}
int IsActorNear_8001DFC8(Actor* actor, VECTOR* target, int range, int checkLevant)
{
    EventNode* node;
    EventEntry* entry;
    Actor* other;
    int count;
    int i;
    unsigned int dist;
    if (checkLevant)
    {
        dist = 0xFFF;
        if (IsWithinDistance_8003B740(actor->pos_38, &levantPos_8008BD18.pos.x, &dist) != 0 && dist < range * range)
        {
            return 1;
        }
    }
    node = actorTasks_8008D43C;
    count = node->count;
    for (i = 0; i < count; i++)
    {
        entry = &node->entry;
        if ((entry->flags & 0x8001) == 1 && actor->task_0 != (other = (Actor*)entry->buffer)->task_0)
        {
            dist = 0xFFF;
            if (IsWithinDistance_8003B740(actor->pos_38, other->pos_38, &dist) != 0 && dist < range * range)
            {
                return 1;
            }
        }
        node = node->next;
    }
    return 0;
}
int IsInFrontWithinRange_8001E0F4(VECTOR* from, int angle, VECTOR* to, unsigned int range)
{
    VECTOR delta;
    unsigned int dist;
    int angleDiff;
    dist = 0xFFF;
    if (IsWithinDistance_8003B740((int*)&from->vx, (int*)&to->vx, &dist) == 1 && dist < range)
    {
        delta.vx = to->vx - from->vx;
        delta.vz = to->vz - from->vz;
        angleDiff = (ratan2_8003B548(delta.vx, delta.vz) - angle) & 0xFFF;
        if (angleDiff < 0x400)
        {
            return 2;
        }
        if (angleDiff > 0xC00 && angleDiff < 0x1000)
        {
            return 1;
        }
    }
    return 0;
}
int IsActorIdle_8001E1C8(Actor* actor)
{
    return (actor->flags_4 & 0x280000) == 0;
}
int IsActorActionReady_8001E1DC(Actor* actor)
{
    if (actor->effect_130 >= 0)
    {
        if (IsEffectReady_80014954() == 0)
        {
            return 0;
        }
    }
    if (actor->flags_4 & 0x80000)
    {
        if (actor->kind_C < 3)
        {
            return 0;
        }
    }
    if (actor->flags_4 & 0x400000)
    {
        return 0;
    }
    return 1;
}
int StartActorAction_8001E254(Actor* actor, void* desc)
{
    actor->flags_4 = (actor->flags_4 & 0xFFFDFFFF) | 0x600000;
    return SetActorAction_8001E34C(actor, desc);
}
void TriggerActorEffect_8001E28C(Actor* actor)
{
    ActorEffectReq req;
    if (actor->effect_130 >= 0)
    {
        req.effect_0 = actor->effect_130;
        req.hitTimes_4 = actor->hitTimes_108;
        req.tbl_8 = actor->effectTbl_14C;
        req.pos_C = actor->pos_38;
        req.bonePos_10 = actor->bonePos_1C4;
        req.boneMatrices_14 = actor->boneMatrices_1C8;
        req.boneScale_34 = actor->boneScale_144;
        req.scale_38 = actor->scale_2C;
        CollectEffectTargets_800182B8(&req, actor->effectKinds_EC);
        PlayActorEffect_800184DC(&req, LowestSetBit_80014358(actor->effectMask_E8));
        actor->effect_130 = -1;
    }
    actor->flags_4 |= 0x20000;
    if (actor->stopScriptAtEnd_100 != 0)
    {
        StopActorScript_8001EFC4(actor);
    }
}
int SetActorAction_8001E34C(Actor* actor, ActorActionDesc* desc)
{
    int hitStart;
    int effect;
    int flags;
    actor->flags_D4 = desc->flags_0;
    actor->turnStep_E0 = desc->turnStep_C;
    actor->effectMask_E8 = desc->effectMask_14;
    actor->effectKinds_EC = desc->effectKinds_18;
    actor->loopCount_F4 = desc->loopCount_20;
    actor->scaleTarget_F6 = desc->scaleTarget_22;
    actor->anim_FC = desc->anim_28;
    actor->queuedAnim_FE = desc->queuedAnim_2A;
    actor->turnStep_E0 = desc->turnStep_C;
    actor->stopScriptAtEnd_100 = desc->stopScriptAtEnd_2C;
    hitStart = 0;
    if (desc->script_4)
    {
        StartActorScript_8001DC34(actor, desc->script_4);
    }
    if (desc->hitAnim_E >= 0)
    {
        hitStart = GetActorHitTimes_8001F268(actor, actor->hitTimes_108, actor->script_D0, desc->hitAnim_E);
    }
    effect = desc->effect_10;
    if (effect >= 0)
    {
        actor->effect_130 = effect;
        RequestEffect_800148F4(effect);
    }
    if (desc->target_8)
    {
        actor->pathTarget_DC = desc->target_8;
        actor->target_70.vx = desc->target_8[0];
        actor->target_70.vy = desc->target_8[1];
        actor->target_70.vz = desc->target_8[2];
        effect = desc->turnStep_C;
        actor->flags_4 |= 0x80000;
        actor->target_70.pad = effect;
        if (desc->nextAnim_24 >= 0)
        {
            actor->nextAnim_A4 = desc->nextAnim_24;
            StartActorScript_8001DC34(actor, moveToScript_8007D95C);
        }
        else
        {
            actor->nextAnim_A4 = desc->nextAnim_26;
            StartActorScript_8001DC34(actor, moveToScriptAlt_8007D980);
        }
    }
    if (desc->path_30)
    {
        actor->pathStep_98 = 0;
        actor->flags_4 |= 0x2000000;
        actor->path_160 = desc->path_30;
    }
    if (desc->queuedAnim_2A >= 0)
    {
        actor->nextAnim_A4 = desc->anim_28;
        actor->startMode_A8 = desc->turnStep_C;
        StartActorScript_8001DC34(actor, playQueuedAnimScript_8007D9C0);
    }
    else if (desc->anim_28 >= 0)
    {
        actor->nextAnim_A4 = desc->anim_28;
        actor->startMode_A8 = desc->turnStep_C;
        StartActorScript_8001DC34(actor, playAnimScript_8007D9A4);
    }
    flags = actor->flags_4;
    if (desc->field_1C)
    {
        flags |= 0x800000;
    }
    actor->flags_4 = flags;
    return hitStart;
}
void InitActor_8001E574(Actor* actor, ActorDesc* desc)
{
    Model* m;
    int v;
    int f;
    int anim;
    ModelList* list;
    if (desc->modelId_0 >= 0)
    {
        m = AcquireLoaderModel_80020734(desc->modelId_0);
    }
    else
    {
        m = desc->model_48;
    }
    v = AddModelAnimRef_800201EC(m);
    actor->flags_4 = 0x40000;
    f = actor->flags_4;
    if (desc->visible_30 != 1)
    {
        f |= 0x2000;
    }
    actor->flags_4 = f;
    if (desc->kind_4 == 2)
    {
        f |= 0x1000;
        actor->flags_4 = f;
    }
    actor->drawMode_8 = 0;
    actor->kind_C = desc->kind_4;
    actor->animLoadState_10 = 0;
    actor->animRequest_12 = -1;
    actor->animLoading_14 = -1;
    actor->modelRef_16 = v;
    actor->loopFrame_18 = 0;
    actor->endFrame_1A = 0;
    actor->frameFrac_1C = 0;
    actor->frameSpeed_1E = *(short*)&desc->frameSpeed_28;
    actor->scale_26 = 0x1000;
    actor->fade_20 = 0;
    actor->fadeDiv_22 = 0;
    actor->scaleStep_28 = 0;
    actor->scaleTarget_2A = actor->scale_26;
    actor->blendDiv_24 = *(short*)&desc->blendDiv_2C;
    actor->prevPos_44[0] = actor->basePos_50[0] = actor->pos_38[0] = desc->pos_8[0];
    actor->prevPos_44[1] = actor->basePos_50[1] = actor->pos_38[1] = desc->pos_8[1];
    actor->prevPos_44[2] = actor->basePos_50[2] = actor->pos_38[2] = desc->pos_8[2];
    actor->rot_5C[0] = desc->rot_14[0];
    actor->rot_5C[1] = desc->rot_14[1];
    actor->rot_5C[2] = desc->rot_14[2];
    actor->animDelta_64[0] = 0;
    actor->animDelta_64[1] = 0;
    actor->animDelta_64[2] = 0;
    actor->ground_80 = 0;
    actor->prevGround_84 = 0;
    actor->f88 = 0;
    actor->speedScale_8C = 0x1000;
    actor->frame_90 = 0;
    actor->prevFrame_94 = 0;
    actor->pathStep_98 = 0;
    anim = desc->animIdx_20;
    actor->startMode_A8 = -1;
    actor->blend_AC = 0;
    actor->waitCount_B0 = 0;
    actor->fB4 = 0;
    actor->fB8 = 0;
    actor->scriptPos_C4 = 0;
    actor->scriptLen_C6 = 0;
    actor->wait_C8 = 0;
    actor->waitLen_CA = 0;
    actor->fCC = -1;
    actor->fCE = -1;
    actor->anim_9C = anim;
    actor->prevAnim_A0 = anim;
    actor->nextAnim_A4 = actor->anim_9C;
    actor->animIdx_C2 = actor->prevAnimIdx_C0 = *(short*)&actor->anim_9C;
    actor->effect_130 = -1;
    list = m->list_0;
    actor->model_15C = m;
    actor->image_150.x = actorImageRect_8007DC8C[0];
    actor->image_150.y = actorImageRect_8007DC8C[1] + list->vram_C[m->slot_30].reloc_4[5];
    actor->image_150.w = actorImageRect_8007DC8C[2];
    actor->image_150.h = actorImageRect_8007DC8C[3];
    actor->clut_158[0] = actorClutPos_8007DC94[0];
    actor->clut_158[1] = actorClutPos_8007DC94[1] + *(short*)&desc->clutRow_1C;
    actor->path_160 = 0;
    AllocActorBones_8001E7F0(actor, desc);
    FirFilterInit_8001450C(actor->turnFilterBuf_1A4, &actor->turn_194, turnFilterCoeffs_800795A0, 8);
    SetActorAnim_8001D760(actor, desc->animIdx_20, desc->frame_24, 0);
}
void AllocActorBones_8001E7F0(Actor* actor, ActorDesc* desc)
{
    short* bones;
    int count;
    int size;
    int i;
    char* mem;
    SVECTOR* src;
    int sz0;
    int sz1;
    bones = desc->bones_34;
    count = 0;
    while (bones[count * 4] != -1)
    {
        count++;
    }
    sz0 = (count + 1) << 3;
    sz1 = count << 3;
    size = sz0;
    size += sz1;
    size += count * 12;
    if (desc->hasMatrices_4C)
    {
        size += count * 32;
    }
    mem = ListAlloc_8003FDC0(&actorHeap_80091990, size);
    actor->bones_134 = (short*)mem;
    MemCopy_800403E8(mem, desc->bones_34, sz0);
    actor->baseScale_138[0] = desc->baseScale_38[0];
    actor->baseScale_138[1] = desc->baseScale_38[1];
    actor->baseScale_138[2] = desc->baseScale_38[2];
    mem += sz0;
    {
        SVECTOR def = {0x1000, 0x1000, 0x1000, 0};
        actor->boneScale_144 = (SVECTOR*)mem;
        mem += sz1;
        actor->flags_4 |= 0x8000000;
        for (i = 0; i < count; i++)
        {
            if (desc->boneScale_3C)
            {
                src = &desc->boneScale_3C[i];
            }
            else
            {
                src = &def;
            }
            actor->boneScale_144[i].vx = src->vx;
            actor->boneScale_144[i].vy = src->vy;
            actor->boneScale_144[i].vz = src->vz;
            actor->boneScale_144[i].pad = src->pad;
        }
    }
    actor->anims_148 = desc->anims_40;
    actor->effectTbl_14C = desc->effectTbl_44;
    actor->bonePos_1C4 = (int*)mem;
    mem += count * 12;
    if (desc->hasMatrices_4C)
    {
        actor->boneMatrices_1C8 = (MATRIX*)mem;
        actor->flags_4 |= 0x10000000;
    }
    else
    {
        actor->boneMatrices_1C8 = 0;
    }
}
void FreeActorBones_8001EA00(Actor* actor)
{
    int mem = (int)actor->bones_134;
    ListFree_8003FE38(&actorHeap_80091990, (void*)mem);
}
void UpdateActorScript_8001EA28(void* actor)
{
    RunActorScript_8001EA48(actor);
}

char* primBufferStart_800960A0[2] BSS = { 0 };
char* primAllocPtr_800960A8[2] BSS = { 0 };
