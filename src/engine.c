#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "engine.h"
#include "gte.h"
#include "model.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"
#include "effect_data.h"
#include "effect.h"
#include "event.h"
#include "main.h"

// the bit masks SetBoneGroupFlags_80019B14 (minion_init.c) copies: the first .rdata of this file, which has to start at 4 mod 8
// for its switch tables (.align 3), so SetBoneGroupFlags_80019B14 is probably the first function of this TU
const struct_int3 boneGroupMasks_8007303C = { { 0x1F8, 0xF000, 0x7E0000 } };
const int dword_80073048 = 0;
const char aDevaMalti_8007304C[] = "\202c\202\205\202\226\202\201\201@\202l\202\201\202\214\202\224\202\211"; // Deva Malti
const char aDevaUlvi_80073064[] = "\202c\202\205\202\226\202\201\201@\202t\202\214\202\226\202\211"; // Deva Ulvi
const char aDevaVali_80073078[] = "\202c\202\205\202\226\202\201\201@\202u\202\201\202\214\202\211"; // Deva Vali
const char aDevaAgni_8007308C[] = "\202c\202\205\202\226\202\201\201@\202`\202\207\202\216\202\211"; // Deva Agni
const char aAdMumuls_800730A0[] = "\202`\202\204\201@\202l\202\225\202\215\202\225\202\214\202\223"; // Ad Mumuls
const char aAdRoqua_800730B4[] = "\202`\202\204\201@\202q\202\217\202\221\202\225\202\201"; // Ad Roqua
const char aAdSlahm_800730C8[] = "\202`\202\204\201@\202r\202\214\202\201\202\210\202\215"; // Ad Slahm
const char aAdVenon_800730DC[] = "\202`\202\204\201@\202u\202\205\202\216\202\217\202\216"; // Ad Venon
const char aSelSelahm_800730F0[] = "\202r\202\205\202\214\201@\202r\202\205\202\214\202\201\202\210\202\215"; // Sel Selahm
const char aSelahm_80073108[] = "\202r\202\205\202\214\202\201\202\210\202\215"; // Selahm
const char aMedinia_80073118[] = "\202l\202\205\202\204\202\211\202\216\202\211\202\201"; // Medinia
const char aMedina_80073128[] = "\202l\202\205\202\204\202\211\202\216\202\201"; // Medina
const char aSelahmVenon_80073138[] = "\202r\202\205\202\214\202\201\202\210\202\215\201@\202u\202\205\202\216\202\217\202\216"; // Selahm Venon
const char aMaltia_80073154[] = "\202l\202\201\202\214\202\224\202\211\202\201"; // Maltia
const char aMaltis_80073164[] = "\202l\202\201\202\214\202\224\202\211\202\223"; // Maltis
const char aMalti_80073174[] = "\202l\202\201\202\214\202\224\202\211"; // Malti
const char aUlvia_80073180[] = "\202t\202\214\202\226\202\211\202\201"; // Ulvia
const char aUlvis_8007318C[] = "\202t\202\214\202\226\202\211\202\223"; // Ulvis
const char aUlvi_80073198[] = "\202t\202\214\202\226\202\211"; // Ulvi
const char aVahlia_800731A4[] = "\202u\202\201\202\210\202\214\202\211\202\201"; // Vahlia
const char aVahlis_800731B4[] = "\202u\202\201\202\210\202\214\202\211\202\223"; // Vahlis
const char aVahli_800731C4[] = "\202u\202\201\202\210\202\214\202\211"; // Vahli
const char aAgnia_800731D0[] = "\202`\202\207\202\216\202\211\202\201"; // Agnia
const char aAgnis_800731DC[] = "\202`\202\207\202\216\202\211\202\223"; // Agnis
const int dword_800731E8 = 0;
const char aAgni_800731EC[] = "\202`\202\207\202\216\202\211"; // Agni
const int overlayAdrr1_800731F8 = 0x800C9E88;
const int overlayAddr2_800731FC = 0x800A4088;
const int overlayAddr3_80073200 = 0x800A05A0;
const int overlayAddr4_80073204 = 0x800B66C0;
const int overlayAddr5_80073208 = 0x800C29D0;
const int overlayAddr6_8007320C = 0x800B6D00;
unsigned int *const mapCodeAddr_80073210 = (unsigned int *)0x800B22C0;
/* char* data001Path_80086570 = "\\DATA\\DATA.001;1"; (the string literal would be emitted into .rdata, not owned yet) */

// Matched
signed char GetMinionElement_80019BF0(int idx)
{
    return minionBaseStats_8007A4B4[idx].element;
}
// Matched
unsigned char GetMinionEnhancementBody_80019C0C(int idx)
{
    return minionBaseStats_8007A4B4[idx].enhancementBody;
}
// Matched
UnitSkills* GetSpeciesSkills_80019C28(unsigned int idx)
{
    if (0xC9 > idx)
    {
        return &speciesSkills_8007A9F8[idx];
    }
    return sub_800B3274(idx - 0x39);
}
// Matched
MinionModelDesc* GetSpeciesModelDesc_80019C70(int idx)

{
    return &speciesModelDescs_8007BD30[idx];
}
// Matched
int sub_80019C84(void)
{
    int v = 0x24;
    int c = minionVariantSeed_8008D4DC & 0xFF;
    if (unknownFlags_8008D678 & 0x1000)
    {
        v = c % 4 + 0x25;
    }
    return v;
}
extern CameraState cameraState_8008D4F0;
extern short screenOffset_8008D474[2];
extern int QueueFileRequest_8003BC84(FileRequestDesc* req);
extern int StartFileRequestTask_8003C6C8(FileRequestDesc* req);
void OnEffectFileLoaded_80020F5C();
extern unsigned short padPrevHeld_800918C8[];
extern unsigned short padRepeat_800918CC[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padPressed_8009194C[];
extern unsigned short padHoldFrames_80091950[][16];
extern signed char padAnalog_800918D8[][4];
extern unsigned char padAnalogMax_800918E0[][4];
extern int DistanceSquaredXZ_8003B860(int* a, int* b);
// index of the camera point nearest to pos (XZ plane)
// Matched
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
        if (cameraState_8008D4F0.points_44[i].active == 0)
        {
            break;
        }
        if (DistanceSquaredXZ_8003B860((int*)&cameraState_8008D4F0.points_44[i].pos, pos) < best)
        {
            best = DistanceSquaredXZ_8003B860((int*)&cameraState_8008D4F0.points_44[i].pos, pos);
            found = i;
        }
    }
    return found;
}
extern int pointLightRange_8008D3F0;      // range of the global point light (0: none)
// Sets the GTE light and colour matrices for a model at pos + ofs, lit by the scene light (lightMatrix_80087114 row 0,
// colour from cameraState), the global point light and the given point light; m is the model's rotation.
// Matched
void SetModelLighting_80019D84(VECTOR* pos, VECTOR* ofs, PointLight* light, MATRIX* m)
{
    MATRIX* sm;
    int* d;
    CameraState* g;
    int sq[3];
    int dist;
    int t;
    int x;
    int y;
    int z;

    d = (int*)0x1F800014;
    g = &cameraState_8008D4F0;
    sm = (MATRIX*)0x1F800000;
    sm->m[0][0] = lightMatrix_80087114.m[0][0];
    sm->m[0][1] = lightMatrix_80087114.m[0][1];
    sm->m[0][2] = lightMatrix_80087114.m[0][2];
    sm->m[2][0] = -lightMatrix_80087114.m[0][0];
    sm->m[2][1] = -lightMatrix_80087114.m[0][1];
    sm->m[2][2] = -lightMatrix_80087114.m[0][2];
    colorMatrix_80087134.m[0][2] = g->lightColor_3C[0] / 4;
    colorMatrix_80087134.m[1][2] = g->lightColor_3C[1] / 4;
    colorMatrix_80087134.m[2][2] = g->lightColor_3C[2] / 4;
    if (pointLightRange_8008D3F0 != 0)
    {
        d[0] = pointLightPos_8008D680[0] - (ofs->vx + pos->vx);
        d[1] = pointLightPos_8008D680[1] - (ofs->vy + pos->vy);
        d[2] = pointLightPos_8008D680[2] - (ofs->vz + pos->vz);
        if (abs(d[0]) < pointLightRange_8008D3F0 && abs(d[1]) < pointLightRange_8008D3F0 && abs(d[2]) < pointLightRange_8008D3F0)
        {
            gte_ldlvl(d);
            gte_sqr0();
            gte_stlvnl(sq);
            dist = ISqrt_8003B918(sq[0] + sq[1] + sq[2]);
            if (dist <= pointLightRange_8008D3F0)
            {
                sm->m[2][0] = (d[0] << 12) / dist;
                sm->m[2][1] = (d[1] << 12) / dist;
                sm->m[2][2] = (d[2] << 12) / dist;
                if (unknownFlags_8008D678 & 0x400)
                {
                    t = (((pointLightRange_8008D3F0 - dist) << 12) / pointLightRange_8008D3F0) * sceneBrightness_8008D40C >> 12;
                }
                else
                {
                    t = ((pointLightRange_8008D3F0 - dist) << 12) / pointLightRange_8008D3F0;
                }
                gte_lddp(t);
                gte_ldsv(&pointLightColor_8008D418);
                gte_gpf12();
                gte_stclmv(&colorMatrix_80087134.m[0][2]);
            }
        }
    }
    d[0] = light->pos_0.x - (ofs->vx + pos->vx);
    d[1] = light->pos_0.y - (ofs->vy + pos->vy);
    d[2] = light->pos_0.z - (ofs->vz + pos->vz);
    gte_ldlvl(d);
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
        x = (d[0] << 12) / dist;
        y = (d[1] << 12) / dist;
        z = (d[2] << 12) / dist;
        ((MATRIX*)0x1F800000)->m[1][0] = x;
        ((MATRIX*)0x1F800000)->m[1][1] = y;
        ((MATRIX*)0x1F800000)->m[1][2] = z;
        if (unknownFlags_8008D678 & 0x400)
        {
            t = (((light->range_14 - dist) << 12) / light->range_14 * (light->range_14 - dist) / light->range_14) * sceneBrightness_8008D40C >> 12;
        }
        else
        {
            t = ((light->range_14 - dist) << 12) / light->range_14 * (light->range_14 - dist) / light->range_14;
        }
        gte_lddp(t);
        gte_ldsv(&light->color_C);
        gte_gpf12();
        gte_stclmv(&colorMatrix_80087134.m[0][1]);
    }
    gte_SetRotMatrix((MATRIX*)0x1F800000);
    gte_ldclmv(&m->m[0][0]);
    gte_rtir();
    gte_stclmv(&((MATRIX*)0x1F800000)->m[0][0]);
    gte_ldclmv(&m->m[0][1]);
    gte_rtir();
    gte_stclmv(&((MATRIX*)0x1F800000)->m[0][1]);
    gte_ldclmv(&m->m[0][2]);
    gte_rtir();
    gte_stclmv(&((MATRIX*)0x1F800000)->m[0][2]);
    gte_SetLightMatrix((MATRIX*)0x1F800000);
    gte_SetColorMatrix(&colorMatrix_80087134);
}
// Matched
void InitSceneFade_8001A38C(void)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    CameraState* g;
    f->flags = 0;
    f->count = 0;
    g = &cameraState_8008D4F0;
    lightMatrix_80087114.m[2][0] = -(unsigned short)g->lightDir_34.vx;
    lightMatrix_80087114.m[2][1] = -(unsigned short)g->lightDir_34.vy;
    lightMatrix_80087114.m[2][2] = -(unsigned short)g->lightDir_34.vz;
    colorMatrix_80087134.m[0][2] = g->lightColor_3C[0] / 4;
    colorMatrix_80087134.m[1][2] = g->lightColor_3C[1] / 4;
    colorMatrix_80087134.m[2][2] = g->lightColor_3C[2] / 4;
}
// Matched
void SceneFadeTask_8001A41C(EventEntry* e, Fade_8001A41C* f)
{
    unsigned long* ot;
    POLY_F4 poly;
    DR_TPAGE tp;
    int shade;
    SVECTOR* sv;
    CameraState* c;
    unsigned char flash;
    if (f->flags & 0x20)
    {
        ot = pOT_8008D4AC;
    }
    else
    {
        ot = pOT_8008D5F4;
    }
    if (f->flags & 0x10)
    {
        flash = f->count * 255 / 8;
        SetPolyF4(&poly);
        poly.r0 = flash;
        poly.g0 = flash;
        poly.b0 = flash;
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.field_C_w;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.field_E_h;
        poly.x3 = display_8008B4D8.field_C_w;
        poly.y3 = display_8008B4D8.field_E_h;
        SetSemiTrans(&poly, 1);
        AddPrimCopy_80040298(&ot[3], &poly, 6);
        setlen(&tp, 1);
        tp.code[0] = 0xE1000220;
        AddPrimCopy_80040298(&ot[3], &tp, 2);
        if (--f->count < 0)
        {
            f->flags &= ~0x10;
        }
    }
    else if (f->flags & 1)
    {
        sceneBrightness_8008D40C += 0x1000 / f->duration;
        if (sceneBrightness_8008D40C >= 0x1000)
        {
            sceneBrightness_8008D40C = 0x1000;
            unknownFlags_8008D678 &= ~0x400;
            f->flags &= ~1;
        }
    }
    else if (f->flags & 2)
    {
        sceneBrightness_8008D40C -= 0x1000 / f->duration;
        if (sceneBrightness_8008D40C < 0)
        {
            f->flags &= ~2;
            sceneBrightness_8008D40C = 0;
        }
    }
    else if (f->flags & 4)
    {
        shade = f->count << 8;
        shade -= f->count;
        shade /= f->duration;
        SetPolyF4(&poly);
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.field_C_w;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.field_E_h;
        poly.x3 = display_8008B4D8.field_C_w;
        poly.y3 = display_8008B4D8.field_E_h;
        poly.r0 = shade;
        poly.g0 = shade;
        poly.b0 = shade;
        SetSemiTrans(&poly, 1);
        AddPrimCopy_80040298(&ot[3], &poly, 6);
        setlen(&tp, 1);
        tp.code[0] = 0xE1000220;
        AddPrimCopy_80040298(&ot[3], &tp, 2);
        if (++f->count > f->duration)
        {
            f->count = f->duration;
        }
    }
    else if (f->flags & 8)
    {
        shade = (f->duration - f->count) << 8;
        shade -= f->duration - f->count;
        shade /= f->duration;
        SetPolyF4(&poly);
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.field_C_w;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.field_E_h;
        poly.x3 = display_8008B4D8.field_C_w;
        poly.y3 = display_8008B4D8.field_E_h;
        poly.r0 = shade;
        poly.g0 = shade;
        poly.b0 = shade;
        SetSemiTrans(&poly, 1);
        AddPrimCopy_80040298(&ot[3], &poly, 6);
        setlen(&tp, 1);
        tp.code[0] = 0xE1000220;
        AddPrimCopy_80040298(&ot[3], &tp, 2);
        if (++f->count > f->duration)
        {
            f->flags &= ~8;
            f->count = f->duration;
        }
    }
    sv = &cameraState_8008D4F0.lightDir_34;
    VectorNormalSS(sv, sv);
    c = &cameraState_8008D4F0;
    lightMatrix_80087114.m[0][0] = c->lightDir_34.vx;
    lightMatrix_80087114.m[0][1] = c->lightDir_34.vy;
    lightMatrix_80087114.m[0][2] = c->lightDir_34.vz;
    if (unknownFlags_8008D678 & 0x400)
    {
        colorMatrix_80087134.m[0][0] = c->lightColor_3C[0] * sceneBrightness_8008D40C >> 12;
        colorMatrix_80087134.m[1][0] = c->lightColor_3C[1] * sceneBrightness_8008D40C >> 12;
        colorMatrix_80087134.m[2][0] = c->lightColor_3C[2] * sceneBrightness_8008D40C >> 12;
    }
    else
    {
        colorMatrix_80087134.m[0][0] = c->lightColor_3C[0];
        colorMatrix_80087134.m[1][0] = c->lightColor_3C[1];
        colorMatrix_80087134.m[2][0] = c->lightColor_3C[2];
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
        backColor_8008D460[0] = cameraState_8008D4F0.ambient_30[0] * sceneBrightness_8008D40C >> 12;
        backColor_8008D460[1] = cameraState_8008D4F0.ambient_30[1] * sceneBrightness_8008D40C >> 12;
        backColor_8008D460[2] = cameraState_8008D4F0.ambient_30[2] * sceneBrightness_8008D40C >> 12;
    }
    else
    {
        backColor_8008D460[0] = cameraState_8008D4F0.ambient_30[0];
        backColor_8008D460[1] = cameraState_8008D4F0.ambient_30[1];
        backColor_8008D460[2] = cameraState_8008D4F0.ambient_30[2];
    }
}
// Matched
void ResetSceneFade_8001A9A4(void)
{
    Fade_8001A41C* f;
    unsigned short flags;
    sceneBrightness_8008D40C = 0x1000;
    f = fadeTask_8008D628->entry.buffer;
    flags = f->flags;
    unknownFlags_8008D678 &= ~0x400;
    f->count = 0;
    f->flags = flags & 0xFFF0;
}
// Matched
void SetSceneDark_8001A9E4(void)
{
    unknownFlags_8008D678 |= 0x400;
    sceneBrightness_8008D40C = 0;
}
// Matched
void StartSceneFadeIn_8001AA04(short duration)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    f->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    f->count = 0;
    f->flags |= 1;
    SceneFadeTask_8001A41C(task, f);
}
// Matched
void StartSceneFadeOut_8001AA50(short duration)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    unknownFlags_8008D678 |= 0x400;
    f->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    f->count = 0;
    f->flags |= 2;
    SceneFadeTask_8001A41C(task, f);
}
// Matched
void StartSceneDarken_8001AAA8(short duration)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    f->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    f->count = 0;
    f->flags |= 4;
    SceneFadeTask_8001A41C(task, f);
}
// Matched
void StopSceneDarken_8001AAF4(void)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    f->flags &= ~4;
}
// Matched
void StartSceneBrighten_8001AB1C(short duration)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    EventEntry* task;
    f->duration = duration;
    task = &cameraTask_8008D4A0->entry;
    f->count = 0;
    f->flags |= 8;
    SceneFadeTask_8001A41C(task, f);
}
// Matched
void StartSceneFlash_8001AB68(void)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    f->count = 8;
    f->flags |= 0x10;
}
// Matched
int IsSceneFadeDone_8001AB94(void)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    unsigned short flags = f->flags;
    if (flags & 0x1B)
    {
        return 0;
    }
    if (flags & 4)
    {
        return f->count == f->duration;
    }
    return 1;
}
// Matched
void SetSceneFadeFrontOT_8001ABEC(int on)
{
    Fade_8001A41C* f = fadeTask_8008D628->entry.buffer;
    if (on)
    {
        f->flags |= 0x20;
    }
    else
    {
        f->flags &= ~0x20;
    }
}
// Matched
int GetMagicName_8001AC2C(int idx)
{
    if (idx >= 0x1E)
    {
        return 0;
    }
    return magicNames_8007C348[idx * 2];
}
// Matched
int GetMagicMpCost_8001AC58(int idx)
{
    if (idx < 0x1E)
    {
        return magicData_8007C438[idx].field_4;
    }
    return 0;
}
// Matched
int GetMagicEffect_8001AC8C(int idx)
{
    if (idx < 0x1E)
    {
        return magicData_8007C438[idx].effect_6;
    }
    return 0x1A;
}
// Matched
int sub_8001ACC0(int idx)
{
    return magicData_8007C438[idx].field_5;
}
// Matched
int GetMagicTargetFlags_8001ACE4(int idx)
{
    unsigned int flags = magicData_8007C438[idx].flags_0;
    int r = (flags >> 5) & 2;
    if (flags & 0x80)
    {
        r |= 4;
    }
    if (flags & 4)
    {
        r |= 1;
    }
    return r;
}
// Matched
int GetMagicElement_8001AD30(int idx)
{
    if (idx < 0x1E)
    {
        return magicData_8007C438[idx].element_8;
    }
    return 0xB;
}
// Matched
ActionData* GetMagicAction_8001AD64(unsigned int idx)
{
    if (idx < 0x1E)
    {
        return &magicActions_8007C5A0[idx];
    }
    return 0;
}
// Matched
void ClearMagicBits_8001AD90(unsigned int* bits)
{
    int i;
    for (i = 0; i < 1; i++)
    {
        bits[i] = 0;
    }
}
// Matched
void SetMagicBit_8001ADAC(unsigned int* bits, unsigned int idx)
{
    unsigned int* p = bits + (idx >> 5);
    *p |= 1 << (idx & 0x1F);
}
// Matched
void OrMagicBits_8001ADD4(unsigned int* dst, unsigned int* src)
{
    int i;
    for (i = 0; i < 1; i++)
    {
        *dst++ |= *src++;
    }
}
// Matched
void ClearMagicBit_8001AE00(unsigned int* bits, unsigned int idx)
{
    unsigned int* p = bits + (idx >> 5);
    *p &= ~(1 << (idx & 0x1F));
}
// Matched
int TestMagicBit_8001AE2C(unsigned int* bits, unsigned int idx)
{
    unsigned int* p = bits + (idx >> 5);
    return (*p & (1 << (idx & 0x1F))) != 0;
}
// Matched
int CountMagicBits_8001AE54(unsigned int* bits)
{
    int i = 0;
    int n = i;
    for (; i < 0x1E; i++)
    {
        if (TestMagicBit_8001AE2C(bits, i))
        {
            n++;
        }
    }
    return n;
}
// Matched
void nullsub_3(void)
{
}
// Matched
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
// Matched
int GetMagicIcon_8001AF3C(int idx)
{
    if (idx < 0x1E)
    {
        return magicIcons_8007C708[idx];
    }
    return 0;
}
extern void* CreateEventList_800435B4(void* list);
extern void RunEventList_80043898(void* n);
extern void RunEventListFreeCallbacks_800438F8(void* n);
extern int FreeEventList_80043A5C(void* head);
extern void InitMovie_8001B1B0(void);
extern void StartDisplay_8001B714(void);
extern void DrawFrozenFrame_8001B540(void);
extern void DrawMotionBlur_8001BCE4(int buffer);
extern void Draw_8001B5EC(void);
extern void LoadDecodedImage_8001BEC8(void);
extern void InitPrimBuffers_8001BF90(void);
#if 0
// Not matched (4 lines): only the flags address (lui s0) is scheduled after the drawEnv pointers instead of before.
// The int-arithmetic PutDrawEnv argument fixed the add order. Tried: e0/e1 set inside the loop or before
// CreateEventList, e1 = &drawEnv_8008D698[1], globals instead of e0/e1 (merges both into one base); permuter 1500 iters
void DrawIntroMovie_8001AF64(void* a0)
{
    void* list;
    DRAWENV* e0;
    DRAWENV* e1;
    int r;
    int g;
    int b;
    SetDispMask(0);
    InitMovie_8001B1B0();
    list = CreateEventList_800435B4(a0);
    e0 = drawEnv_8008D698;
    e1 = e0 + 1;
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
        PutDrawEnv((DRAWENV*)(bDoubleBuffer_8008D428 * sizeof(DRAWENV) + (int)e0));
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
#endif
INCLUDE_ASM(DrawIntroMovie_8001AF64);
// Matched
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
// Matched
void RestartDisplay_8001B230(void)
{
    unknownFlags_8008D678 &= ~0x10;
    displayStartFrames_800918BC = 0;
    unknownFlags_8008D678 |= 0x40;
}
// Matched
void ClearOTagRAll_8001B260(void)
{
    sub_8004D924();
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
// Matched
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
// Matched
void DrawFrozenFrame_8001B540(void)
{
    if (unknownFlags_8008D678 & 8)
    {
        InitSprt_8001B9A0(bDoubleBuffer_8008D428);
    }
    else if (unknownFlags_8008D678 & 0x82)
    {
        int f = fadeFlags_800918B0;
        if (f & 2)
        {
            FadeToWhiteStep_8001BC00();
        }
        else if (f & 1)
        {
            FadeToBlackStep_8001BB28();
        }
        InitSprt_8001B9A0(bDoubleBuffer_8008D428);
        unknownFlags_8008D678 &= ~0x80;
    }
}
// Matched
void Draw_8001B5EC(void)
{
    int r;
    if (!(unknownFlags_8008D678 & 0x20))
    {
        DrawSync(0);
    }
    SetGeomOffset(display_8008B4D8.field_C_w / 2 + screenOffset_8008D474[0], display_8008B4D8.field_E_h / 2 + screenOffset_8008D474[1]);
    SetGeomScreen(geomScreenDistance_8008B548);
    do
    {
    } while (vsyncCounter_8008B4B4 < display_8008B4D8.vsyncsPerFrame_4);
    if (unknownFlags_8008D678 & 0x20)
    {
        ResetGraph(1);
        do
        {
            r = GetODE();
        } while (ODEIsEvenAddressDrawn_800918C0 == r);
        ODEIsEvenAddressDrawn_800918C0 = r;
    }
    vsyncCounter_8008B4B4 = 0;
    vsyncCounter_8008B4B4 = 0;
}
// Matched
int WaitVSync_8001B6E8()
{
    int snapshot = vsyncCounter_8008B4B4;
    do
    {
    } while (vsyncCounter_8008B4B4 <= snapshot);
    return gnFrame_8008D610;
}
// Matched
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
extern DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h);
extern DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h);
// Matched
void InitEnvironments_8001B7B4(void)
{
    int interlace;
    int off;
    display_8008B4D8.field_C_w = screenModes_8007C728[display_8008B4D8.field_0][0];
    display_8008B4D8.field_E_h = screenModes_8007C728[display_8008B4D8.field_0][1];
    if (display_8008B4D8.field_E_h == 480)
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
    SetDefDrawEnv(&drawEnv_8008D698[0], display_8008B4D8.field_8_x, display_8008B4D8.field_A_y, display_8008B4D8.field_C_w, display_8008B4D8.field_E_h);
    SetDefDispEnv(&dispEnv_8008D750[0], display_8008B4D8.field_8_x, display_8008B4D8.field_A_y + off, display_8008B4D8.field_C_w, display_8008B4D8.field_E_h);
    SetDefDrawEnv(&drawEnv_8008D698[1], display_8008B4D8.field_8_x, display_8008B4D8.field_A_y + off, display_8008B4D8.field_C_w, display_8008B4D8.field_E_h);
    SetDefDispEnv(&dispEnv_8008D750[1], display_8008B4D8.field_8_x, display_8008B4D8.field_A_y, display_8008B4D8.field_C_w, display_8008B4D8.field_E_h);
    drawEnv_8008D698[1].isbg = 1;
    drawEnv_8008D698[0].isbg = 1;
    drawEnv_8008D698[1].dtd = 1;
    drawEnv_8008D698[0].dtd = 1;
    dispEnv_8008D750[1].isinter = interlace;
    dispEnv_8008D750[0].isinter = interlace;
    dispEnv_8008D750[1].isrgb24 = 0;
    dispEnv_8008D750[0].isrgb24 = 0;
    screenOffset_8008D474[0] = display_8008B4D8.field_8_x;
    screenOffset_8008D474[1] = display_8008B4D8.field_A_y;
    SetGeomOffset(display_8008B4D8.field_C_w / 2 + screenOffset_8008D474[0], display_8008B4D8.field_E_h / 2 + screenOffset_8008D474[1]);
    SetGeomScreen(geomScreenDistance_8008B548);
    SetFarColor(0, 0, 0);
}
// Matched
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
        top = display_8008B4D8.field_A_y;
    }
    else
    {
        top = 0x100;
    }
    for (y = 0; y < display_8008B4D8.field_E_h; y += 0x40)
    {
        for (x = 0; x < display_8008B4D8.field_C_w; x += 0x40)
        {
            sprt.x0 = x;
            sprt.y0 = y;
            sprt.u0 = (display_8008B4D8.field_8_x + x) % 64;
            sprt.v0 = y + top;
            AddPrimCopy_80040298(pOT_8008D78C, &sprt, 5);
            tp = GetTPage(2, 0, (display_8008B4D8.field_8_x + x) / 64 * 64, top);
            setDrawTPage(&tpage, 0, 0, tp);
            AddPrimCopy_80040298(pOT_8008D78C, &tpage, 2);
        }
    }
}
// Matched
void FadeToBlackStep_8001BB28(void)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* s;
    unsigned short w;
    unsigned short h;
    SetPolyF4(&poly);
    s = (unsigned short*)&display_8008B4D8;
    w = s[6];
    h = s[7];
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
    AddPrimCopy_80040298(pOT_8008D78C, &poly, 6);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000240;
    AddPrimCopy_80040298(pOT_8008D78C, &dr, 2);
    fadeFrame_800918B4++;
    if ((unsigned int)fadeFrame_800918B4 > 0x20)
    {
        fadeFlags_800918B0 &= ~1;
    }
}
// Matched
void FadeToWhiteStep_8001BC00(void)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* s;
    unsigned short w;
    unsigned short h;
    SetPolyF4(&poly);
    s = (unsigned short*)&display_8008B4D8;
    w = s[6];
    h = s[7];
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
    AddPrimCopy_80040298(pOT_8008D78C, &poly, 6);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000220;
    AddPrimCopy_80040298(pOT_8008D78C, &dr, 2);
    fadeFrame_800918B4++;
    if ((unsigned int)fadeFrame_800918B4 > 0x20)
    {
        fadeFlags_800918B0 &= ~2;
    }
}
// Matched
void SetMotionBlur_8001BCD8(int on)
{
    motionBlurOn_800918C4 = on;
}
// Matched
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
    AddPrimCopy_80040298(pOT_8008D4AC + 3, &stp, 3);
    SetDrawStp(&stp, 0);
    AddPrimCopy_80040298(pOT_8008D4AC, &stp, 3);
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
        top = display_8008B4D8.field_A_y;
    }
    else
    {
        top = 0x100;
    }
    for (y = 0; y < display_8008B4D8.field_E_h; y += 0x40)
    {
        for (x = 0; x < display_8008B4D8.field_C_w; x += 0x40)
        {
            sprt.x0 = x;
            sprt.y0 = y;
            sprt.u0 = (display_8008B4D8.field_8_x + x) % 64;
            sprt.v0 = y + top;
            AddPrimCopy_80040298(pOT_8008D4AC + 1, &sprt, 5);
            tp = GetTPage(2, 0, (display_8008B4D8.field_8_x + x) / 64 * 64, top);
            setDrawTPage(&tpage, 0, 0, tp);
            AddPrimCopy_80040298(pOT_8008D4AC + 1, &tpage, 2);
        }
    }
}
// Matched
void LoadDecodedImage_8001BEC8(void)
{
    RECT rect;
    unsigned long* p = decodedImageData_8008B4A0;
    rect.w = 0x10;
    rect.h = 0x40;
    rect.y = 0x100;
    rect.x = 0x240;
    do
    {
        DecDCTout(p, 0x200);
        DecDCToutSync(0);
        LoadImage(&rect, (unsigned long*)p);
        rect.x += 0x10;
        p += 0x200;
    } while (rect.x < 0x280);
}
// Matched
void ProcessPads_8001BF50(void)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        ProcessPad_8001C8E8(i);
        UpdatePadVibration_80036820(i);
    }
}
// Matched
void InitPrimBuffers_8001BF90(void)
{
    if (unknownFlags_8008D678 & 0x200)
    {
        primAllocPtr_800960A8[0] = primBufferOffset_8008B550 + 0x801B9250;
        primBufferStart_800960A0[0] = primBufferOffset_8008B550 + 0x801B9250;
        primAllocPtr_800960A8[1] = 0x801FC000 - ((unsigned int)(0x42DB0 - primBufferOffset_8008B550) >> 1);
        primBufferStart_800960A0[1] = 0x801FC000 - ((unsigned int)(0x42DB0 - primBufferOffset_8008B550) >> 1);
    }
    else
    {
        primAllocPtr_800960A8[0] = 0x801D4000;
        primBufferStart_800960A0[0] = 0x801D4000;
        primAllocPtr_800960A8[1] = 0x801E8000;
        primBufferStart_800960A0[1] = 0x801E8000;
    }
}
// Matched
void StartScreenFlash_8001C02C(unsigned char* rgb)
{
    EventEntry* r = AllocEventEntry_80043AF8(screenFlashTasks_8008D61C);
    if (r != 0)
    {
        unsigned char* p = (unsigned char*)r->buffer;
        r->flags = (r->flags | 1) & ~0x8000;
        *(int*)p = 0;
        p[4] = rgb[0];
        p[5] = rgb[1];
        p[6] = rgb[2];
        r->cb_8 = (EventEntryFn)ScreenFlashTask_8001C0B4;
    }
}
// Matched
void ScreenFlashTask_8001C0B4(EventEntry* e, int* state)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* s;
    unsigned short w;
    unsigned short h;
    unsigned char* c = (unsigned char*)state;
    state[0]++;
    if (state[0] >= 4)
    {
        e->flags = (e->flags & ~1) | 0x8000;
        return;
    }
    SetPolyF4(&poly);
    poly.r0 = c[4];
    poly.g0 = c[5];
    poly.b0 = c[6];
    s = (unsigned short*)&display_8008B4D8;
    w = s[6];
    h = s[7];
    poly.x0 = 0;
    poly.y0 = 0;
    poly.x1 = w;
    poly.y1 = 0;
    poly.x2 = 0;
    poly.y2 = h;
    poly.x3 = w;
    poly.y3 = h;
    SetSemiTrans(&poly, 0);
    AddPrimCopy_80040298(pOT_8008D5F4, &poly, 6);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000220;
    AddPrimCopy_80040298(pOT_8008D5F4, &dr, 2);
}
// Matched
void SetFadeMode_8001C19C(mode)
unsigned int mode;
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
// Matched
void FreezeScreen_8001C224(void)
{
    unknownFlags_8008D678 |= 8;
    frozenFrames_800918B8 = 0;
}
// Matched
void CancelFade_8001C244(void)
{
    unknownFlags_8008D678 &= ~2;
}
// Matched
void BeginFade_8001C260(void)
{
    if (!(unknownFlags_8008D678 & 2))
    {
        unknownFlags_8008D678 |= 2;
    }
}
// Matched
void EndFade_8001C290(void)
{
    unknownFlags_8008D678 &= ~2;
    unknownFlags_8008D678 |= 0x10;
    unknownFlags_8008D678 |= 0x80;
}
// Matched
void StartFadeToBlack_8001C2CC(void)
{
    fadeFlags_800918B0 = 1;
    fadeFrame_800918B4 = 0;
}
// Matched
void StartFadeToWhite_8001C2E4(void)
{
    fadeFlags_800918B0 = 2;
    fadeFrame_800918B4 = 0;
}
// Matched
int IsFadeDone_8001C2FC()
{
    return (fadeFlags_800918B0 & 3) == 0;
}
// Matched
struct_8_id* FindItemById_8001C314(struct_8_list* list, int id)
{
    struct_8_id* r = 0;
    int i;
    for (i = 0; i < list->count; i++)
    {
        if (id == list->items[i].id)
        {
            r = &list->items[i];
        }
    }
    return r;
}
// Matched
void PlayAnimFrameSfx_8001C364(Model* model, int idx, int frame)
{
    ModelAnim* anim = &model->anims_54[idx];
    int i;
    for (i = 0; i < anim->cueCount_C; i++)
    {
        ModelAnimCue* cue = (ModelAnimCue*)(i * sizeof(ModelAnimCue) + (int)anim->cues_10); // integer sum: the original adds the base second
        if (frame == cue->frame_0 && cue->kind_2 == 0)
        {
            unsigned int n = (unsigned short)cue->arg_4;
            if (n < 0x6E)
            {
                SoundCue_8007C750* t = &soundCues_8007C750[(short)n];
                if (t->kind == 0)
                {
                    PlaySfx_80031494(t->arg);
                }
            }
        }
    }
}
extern int PlayMusic_800300E0(int idx, int a1);
extern void PlaySeqSlot_80031160(unsigned int idx, short loops);
// Matched
void RunAnimFrameCues_8001C440(Model* model, int idx, int frame)
{
    ModelAnim* anim = (ModelAnim*)(idx * 28 + (int)model->anims_54); // integer sum: the original adds the base second
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
                    if (systemSound_80091D40.field_4_seq_num >= 0)
                    {
                        SsSepSetDecrescendo(systemSound_80091D40.field_C_sep_access_num, systemSound_80091D40.field_4_seq_num, 0x7F, 0x78);
                        systemSound_80091D40.field_4_seq_num = -1;
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
// Matched
void ResetPadAnalogMax_8001C69C(void)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        padAnalogMax_800918E0[i][1] = 0;
        padAnalogMax_800918E0[i][0] = 0;
    }
}
// Matched
void ResetButtonConfig_8001C6C8(void)
{
    unsigned short* p = buttonConfig_8008B578;
    int i = 0;
    unsigned short* q = defaultButtonConfig_8007CAF4;
    for (; i < 10; i++)
    {
        SetButtonConfigEntry_8001C810((short*)p++, *q++);
    }
}
// Matched
int TestAnyBits_8001C72C(unsigned int value, unsigned int mask)
{
    return (value & (unsigned short)mask) != 0;
}
// Matched
int TestAllBits_8001C73C(unsigned int value, unsigned int mask)
{
    mask = (unsigned short)mask;
    if (mask == 0)
    {
        return 0;
    }
    return (value & mask) == mask;
}
// Matched
int FindButtonConfig_8001C75C(unsigned int button)
{
    unsigned short* p = buttonConfig_8008B578;
    int i = 0;
    unsigned int v = (unsigned short)button;
    for (; i < 10; i++)
    {
        if (*p == v)
        {
            return i;
        }
        p++;
    }
    return -1;
}
// Matched
void SwapButtonConfig_8001C79C(int i, int j)
{
    unsigned short* base = buttonConfig_8008B578;
    unsigned short* p = &base[i];
    unsigned short bi = GetButtonConfigEntry_8001C818(p);
    unsigned short* q = &base[j];
    unsigned short bj = GetButtonConfigEntry_8001C818(q);
    SetButtonConfigEntry_8001C810((short*)p, bj);
    SetButtonConfigEntry_8001C810((short*)q, bi);
}
// Matched
void SetButtonConfigEntry_8001C810(short* entry, unsigned short button)
{
    *entry = button;
}
// Matched
unsigned short GetButtonConfigEntry_8001C818(unsigned short* entry)
{
    return *entry;
}
// Matched
int GetButtonConfigBitIndex_8001C824(void)
{
    int i;
    unsigned short v = GetButtonConfig_8001C874();
    for (i = 0; i < 14; i++)
    {
        if (padButtonBits_8007CAD8[i] == v)
        {
            break;
        }
    }
    return i;
}
// Matched
unsigned int GetButtonConfig_8001C874(int idx)
{
    unsigned short* p = buttonConfig_8008B578;
    int i;
    for (i = 0; i < idx; i++)
    {
        p++;
    }
    return *p;
}
// Matched
unsigned int FirstPadButtonBit_8001C8A0(short mask)
{
    unsigned int r = 1;
    int i = 0;
    unsigned short* p;
    int m = mask;
    p = padButtonBits_8007CAD8;
    do
    {
        unsigned int t = *p;
        i++;
        if (m & t)
        {
            r = t;
            break;
        }
        p++;
    } while (i < 10);
    return r;
}
// Matched
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
const int dword_80073234 = 0;
const char aKlarrgas_80073238[] = "\202j\202\214\202\201\202\222\202\222\202\207\202\201\202\223"; // Klarrgas
const char aYolga_8007324C[] = "\202x\202\217\202\214\202\207\202\201"; // Yolga
const char aTimaios_80073258[] = "\202s\202\211\202\215\202\201\202\211\202\217\202\223"; // Timaios
const char aSicanjal_80073268[] = "\202r\202\211\202\203\202\201\202\216\202\212\202\201\202\214"; // Sicanjal
const char aKolna_8007327C[] = "\202j\202\217\202\214\202\216\202\201"; // Kolna
const char aJeechwo_80073288[] = "\202i\202\205\202\205\202\203\202\210\202\227\202\217"; // Jeechwo
const char aTicker_80073298[] = "\202s\202\211\202\203\202\213\202\205\202\222"; // Ticker
const char aPalooja_800732A8[] = "\202o\202\201\202\214\202\217\202\217\202\212\202\201"; // Palooja
const char aAttractSpores_800732B8[] = "\202`\202\224\202\224\202\222\202\201\202\203\202\224\201@\202r\202\220\202\217\202\222\202\205\202\223"; // Attract Spores
const char aSleepSpores_800732D8[] = "\202r\202\214\202\205\202\205\202\220\201@\202r\202\220\202\217\202\222\202\205\202\223"; // Sleep Spores
const char aSkeletonKey_800732F4[] = "\202r\202\213\202\205\202\214\202\205\202\224\202\217\202\216\201@\202j\202\205\202\231"; // Skeleton Key
const char aMoonlightSilk_80073310[] = "\202l\202\217\202\217\202\216\202\214\202\211\202\207\202\210\202\224\201@\202r\202\211\202\214\202\213"; // Moonlight Silk
const char aAngelwingSilk_80073330[] = "\202`\202\216\202\207\202\205\202\214\202\227\202\211\202\216\202\207\201@\202r\202\211\202\214\202\213"; // Angelwing Silk
const char aFirstSnowSilk_80073350[] = "\202e\202\211\202\222\202\223\202\224\201@\202r\202\216\202\217\202\227\201@\202r\202\211\202\214\202\213"; // First Snow Silk
const char aPearlSilk_80073370[] = "\202o\202\205\202\201\202\222\202\214\201@\202r\202\211\202\214\202\213"; // Pearl Silk
const char aLilySilk_80073388[] = "\202k\202\211\202\214\202\231\201@\202r\202\211\202\214\202\213"; // Lily Silk
const char aThunderSilk_8007339C[] = "\202s\202\210\202\225\202\216\202\204\202\205\202\222\201@\202r\202\211\202\214\202\213"; // Thunder Silk
const char aCloudSilk_800733B8[] = "\202b\202\214\202\217\202\225\202\204\201@\202r\202\211\202\214\202\213"; // Cloud Silk
const char aMaltySSeal2_800733D0[] = "\202l\202\201\202\214\202\224\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Malty's Seal 2
const char aMaltySSeal1_800733F0[] = "\202l\202\201\202\214\202\224\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Malty's Seal 1
const char aAgniSSeal2_80073410[] = "\202`\202\207\202\216\202\211\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Agni's Seal 2
const char aAgniSSeal1_8007342C[] = "\202`\202\207\202\216\202\211\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Agni's Seal 1
const char aVarySSeal2_80073448[] = "\202u\202\201\202\222\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Vary's Seal 2
const char aVarySSeal1_80073464[] = "\202u\202\201\202\222\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Vary's Seal 1
const char aUrvySSeal2_80073480[] = "\202t\202\222\202\226\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202Q"; // Urvy's Seal 2
const char aUrvySSeal1_8007349C[] = "\202t\202\222\202\226\202\231\201f\202\223\201@\202r\202\205\202\201\202\214\201@\202P"; // Urvy's Seal 1
const char aMaltySBlessing_800734B8[] = "\202l\202\201\202\214\202\224\202\231\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Malty's Blessing
const char aAgniSBlessing_800734DC[] = "\202`\202\207\202\216\202\211\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Agni's Blessing
const char aVarySBlessing_800734FC[] = "\202u\202\201\202\222\202\231\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Vary's Blessing
const char aUrvySBlessing_8007351C[] = "\202t\202\222\202\226\202\231\201f\202\223\201@\202a\202\214\202\205\202\223\202\223\202\211\202\216\202\207"; // Urvy's Blessing
const char aMirrorOfDeva_8007353C[] = "\202l\202\211\202\222\202\222\202\217\202\222\201@\202\217\202\206\201@\202c\202\205\202\226\202\201"; // Mirror of Deva
const char aRingOfDeath_8007355C[] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202c\202\205\202\201\202\224\202\210"; // Ring of Death
const char aRingOfStoning_80073578[] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202r\202\224\202\217\202\216\202\211\202\216\202\207"; // Ring of Stoning
const char aRingOfSleep_80073598[] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202r\202\214\202\205\202\205\202\220"; // Ring of Sleep
const char aRingOfVenom_800735B4[] = "\202q\202\211\202\216\202\207\201@\202\217\202\206\201@\202u\202\205\202\216\202\217\202\215"; // Ring of Venom
const char aIkariPowder_800735D0[] = "\202h\202\213\202\201\202\222\202\211\201@\202o\202\217\202\227\202\204\202\205\202\222"; // Ikari Powder
const char aValerianPowder_800735EC[] = "\202u\202\201\202\214\202\205\202\222\202\211\202\201\202\216\201@\202o\202\217\202\227\202\204\202\205\202\222"; // Valerian Powder
const char aTendaiUyaku_8007360C[] = "\202s\202\205\202\216\202\204\202\201\202\211\201@\202t\202\231\202\201\202\213\202\225"; // Tendai Uyaku
const char aSpecialLiquor_80073628[] = "\202r\202\220\202\205\202\203\202\211\202\201\202\214\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Special Liquor
const char aExcellentLiquor_80073648[] = "\202d\202\230\202\203\202\205\202\214\202\214\202\205\202\216\202\224\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Excellent Liquor
const char aFineLiquor_8007366C[] = "\202e\202\211\202\216\202\205\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Fine Liquor
const char aShabLiquor_80073684[] = "\202r\202\210\202\201\202\202\201@\202k\202\211\202\221\202\225\202\217\202\222"; // Shab Liquor
const char aIchishiOil_8007369C[] = "\202h\202\203\202\210\202\211\202\223\202\210\202\211\201@\202n\202\211\202\214"; // Ichishi Oil
const char aBletillaOil_800736B4[] = "\202a\202\214\202\205\202\224\202\211\202\214\202\214\202\201\201@\202n\202\211\202\214"; // Bletilla Oil
const char aKukumiraOil_800736D0[] = "\202j\202\225\202\213\202\225\202\215\202\211\202\222\202\201\201@\202n\202\211\202\214"; // Kukumira Oil
const char aShishiudoOil_800736EC[] = "\202r\202\210\202\211\202\223\202\210\202\211\202\225\202\204\202\217\201@\202n\202\211\202\214"; // Shishiudo Oil
const char aChestnutOil_80073708[] = "\202b\202\210\202\205\202\223\202\224\202\216\202\225\202\224\201@\202n\202\211\202\214"; // Chestnut Oil
const char aGreatWalnut_80073724[] = "\202f\202\222\202\205\202\201\202\224\201@\202v\202\201\202\214\202\216\202\225\202\224"; // Great Walnut
const char aBitterMugwort_80073740[] = "\202a\202\211\202\224\202\224\202\205\202\222\201@\202l\202\225\202\207\202\227\202\217\202\222\202\224"; // Bitter Mugwort
const char aMetaMugwort_80073760[] = "\202l\202\205\202\224\202\201\201|\202l\202\225\202\207\202\227\202\217\202\222\202\224"; // Meta-Mugwort
const char aMugwort_8007377C[] = "\202l\202\225\202\207\202\227\202\217\202\222\202\224"; // Mugwort
const char aSecret3_8007378C[] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202R"; // Secret 3
const char aSecret2_800737A0[] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202Q"; // Secret 2
const char aSecret1_800737B4[] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202P"; // Secret 1
const char aMerging3_800737C8[] = "\202l\202\205\202\222\202\207\202\211\202\216\202\207\201@\202R"; // Merging 3
const char aMerging2_800737DC[] = "\202l\202\205\202\222\202\207\202\211\202\216\202\207\201@\202Q"; // Merging 2
const char aMerging1_800737F0[] = "\202l\202\205\202\222\202\207\202\211\202\216\202\207\201@\202P"; // Merging 1
const char aMagicUsage2_80073804[] = "\202l\202\201\202\207\202\211\202\203\201@\202t\202\223\202\201\202\207\202\205\201@\202Q"; // Magic Usage 2
const char aMagicUsage1_80073820[] = "\202l\202\201\202\207\202\211\202\203\201@\202t\202\223\202\201\202\207\202\205\201@\202P"; // Magic Usage 1
const char aKnowledge5_8007383C[] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202T"; // Knowledge 5
const char aKnowledge4_80073854[] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202S"; // Knowledge 4
const char aKnowledge3_8007386C[] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202R"; // Knowledge 3
const char aKnowledge2_80073884[] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202Q"; // Knowledge 2
const char aKnowledge1_8007389C[] = "\202j\202\216\202\217\202\227\202\214\202\205\202\204\202\207\202\205\201@\202P"; // Knowledge 1
const char aSecretOfKilling_800738B4[] = "\202r\202\205\202\203\202\222\202\205\202\224\201@\202\217\202\206\201@\202j\202\211\202\214\202\214\202\211\202\216\202\207"; // Secret of Killing
const char aSpiderWarp_800738D8[] = "\202r\202\220\202\211\202\204\202\205\202\222\201@\202v\202\201\202\222\202\220"; // Spider Warp
const char aDragonflyWarp_800738F0[] = "\202c\202\222\202\201\202\207\202\217\202\216\202\206\202\214\202\231\201@\202v\202\201\202\222\202\220"; // Dragonfly Warp
const char aBeetleWarp_80073910[] = "\202a\202\205\202\205\202\224\202\214\202\205\201@\202v\202\201\202\222\202\220"; // Beetle Warp
const char aPupaKey_80073928[] = "\202o\202\225\202\220\202\201\201@\202j\202\205\202\231"; // Pupa Key
const char aLarvaKey_8007393C[] = "\202k\202\201\202\222\202\226\202\201\201@\202j\202\205\202\231"; // Larva Key
const char aMinionFang_80073950[] = "\202l\202\211\202\216\202\211\202\217\202\216\201@\202e\202\201\202\216\202\207"; // Minion Fang
const char aKickleberry_80073968[] = "\202j\202\211\202\203\202\213\202\214\202\205\202\202\202\205\202\222\202\222\202\231"; // Kickleberry
const char aDivineTablet_80073980[] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202s\202\201\202\202\202\214\202\205\202\224"; // Divine Tablet
const char aJewelOfWind_8007399C[] = "\202i\202\205\202\227\202\205\202\214\201@\202\217\202\206\201@\202v\202\211\202\216\202\204"; // Jewel of Wind
const char aJewelOfFire_800739B8[] = "\202i\202\205\202\227\202\205\202\214\201@\202\217\202\206\201@\202e\202\211\202\222\202\205"; // Jewel of Fire
const char aJewelOfWater_800739D4[] = "\202i\202\205\202\227\202\205\202\214\201@\202\217\202\206\201@\202v\202\201\202\224\202\205\202\222"; // Jewel of Water
const char aMahbuSCocoon_800739F4[] = "\202l\202\201\202\210\202\202\202\225\201f\202\223\201@\202b\202\217\202\203\202\217\202\217\202\216"; // Mahbu's Cocoon
const char aMothKey_80073A14[] = "\202l\202\217\202\224\202\210\201@\202j\202\205\202\231"; // Moth Key
const char aCaptureAmulet_80073A28[] = "\202b\202\201\202\220\202\224\202\225\202\222\202\205\201@\202`\202\215\202\225\202\214\202\205\202\224"; // Capture Amulet
const char aChampionSBelt_80073A48[] = "\202b\202\210\202\201\202\215\202\220\202\211\202\217\202\216\201f\202\223\201@\202a\202\205\202\214\202\224"; // Champion's Belt
const char aCalabasHerb_80073A68[] = "\202b\202\201\202\214\202\201\202\202\202\201\202\223\201@\202g\202\205\202\222\202\202"; // Calabas Herb
const char aOcarina_80073A84[] = "\202n\202\203\202\201\202\222\202\211\202\216\202\201"; // Ocarina
const char aSpiderKey_80073A94[] = "\202r\202\220\202\211\202\204\202\205\202\222\201@\202j\202\205\202\231"; // Spider Key
const char aCalabasPowder_80073AAC[] = "\202b\202\201\202\214\202\201\202\202\202\201\202\223\201@\202o\202\217\202\227\202\204\202\205\202\222"; // Calabas Powder
const char aDragonflyKey_80073ACC[] = "\202c\202\222\202\201\202\207\202\217\202\216\202\206\202\214\202\231\201@\202j\202\205\202\231"; // Dragonfly Key
const char aBeetleKey_80073AE8[] = "\202a\202\205\202\205\202\224\202\214\202\205\201@\202j\202\205\202\231"; // Beetle Key
const char aTearsOfReese_80073B00[] = "\202s\202\205\202\201\202\222\202\223\201@\202\217\202\206\201@\202q\202\205\202\205\202\223\202\205"; // Tears of Reese
const char aFluteOfCapture_80073B20[] = "\202e\202\214\202\225\202\224\202\205\201@\202\217\202\206\201@\202b\202\201\202\220\202\224\202\225\202\222\202\205"; // Flute of Capture
const char aHunterSEarring_80073B44[] = "\202g\202\225\202\216\202\224\202\205\202\222\201f\202\223\201@\202d\202\201\202\222\202\222\202\211\202\216\202\207"; // Hunter's Earring
const char aIcicle_80073B68[] = "\202h\202\203\202\211\202\203\202\214\202\205"; // Icicle
const char aAutumnMoon_80073B78[] = "\202`\202\225\202\224\202\225\202\215\202\216\201@\202l\202\217\202\217\202\216"; // Autumn Moon
const char aDrainer_80073B90[] = "\202c\202\222\202\201\202\211\202\216\202\205\202\222"; // Drainer
const char aReaper_80073BA0[] = "\202q\202\205\202\201\202\220\202\205\202\222"; // Reaper
const char aPalemoon_80073BB0[] = "\202o\202\201\202\214\202\205\202\215\202\217\202\217\202\216"; // Palemoon
const char aCloudcover_80073BC4[] = "\202b\202\214\202\217\202\225\202\204\202\203\202\217\202\226\202\205\202\222"; // Cloudcover
const char aDragoncrest_80073BDC[] = "\202c\202\222\202\201\202\207\202\217\202\216\202\203\202\222\202\205\202\223\202\224"; // Dragoncrest
const char aSpringBlossom_80073BF4[] = "\202r\202\220\202\222\202\211\202\216\202\207\201@\202a\202\214\202\217\202\223\202\223\202\217\202\215"; // Spring Blossom
const char aTsunami_80073C14[] = "\202s\202\223\202\225\202\216\202\201\202\215\202\211"; // Tsunami
const char aThunderbolt_80073C24[] = "\202s\202\210\202\225\202\216\202\204\202\205\202\222\202\202\202\217\202\214\202\224"; // Thunderbolt
const char aBluePhantom_80073C3C[] = "\202a\202\214\202\225\202\205\201@\202o\202\210\202\201\202\216\202\224\202\217\202\215"; // Blue Phantom
const char aNightglow_80073C58[] = "\202m\202\211\202\207\202\210\202\224\202\207\202\214\202\217\202\227"; // Nightglow
const char aWhistler_80073C6C[] = "\202v\202\210\202\211\202\223\202\224\202\214\202\205\202\222"; // Whistler
const char aLittleBird_80073C80[] = "\202k\202\211\202\224\202\224\202\214\202\205\201@\202a\202\211\202\222\202\204"; // Little Bird
const char aWhiteHorn_80073C98[] = "\202v\202\210\202\211\202\224\202\205\201@\202g\202\217\202\222\202\216"; // White Horn
const char aLifeStealer_80073CB0[] = "\202k\202\211\202\206\202\205\201@\202r\202\224\202\205\202\201\202\214\202\205\202\222"; // Life Stealer
const char aIronAxe_80073CCC[] = "\202h\202\222\202\217\202\216\201@\202`\202\230\202\205"; // Iron Axe
const char aIronSword_80073CE0[] = "\202h\202\222\202\217\202\216\201@\202r\202\227\202\217\202\222\202\204"; // Iron Sword
const char aSwordOfSpeed_80073CF8[] = "\202r\202\227\202\217\202\222\202\204\201@\202\217\202\206\201@\202r\202\220\202\205\202\205\202\204"; // Sword of Speed
const char aBronzeSword_80073D18[] = "\202a\202\222\202\217\202\216\202\232\202\205\201@\202r\202\227\202\217\202\222\202\204"; // Bronze Sword
const char aAquazor_80073D34[] = "\202`\202\221\202\225\202\201\202\232\202\217\202\222"; // Aquazor
const char aDagger_80073D44[] = "\202c\202\201\202\207\202\207\202\205\202\222"; // Dagger
const char aKnife_80073D54[] = "\202j\202\216\202\211\202\206\202\205"; // Knife
const char aDivineGarb2_80073D60[] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202f\202\201\202\222\202\202\201@\202Q"; // Divine Garb 2
const char aDivineGarb1_80073D7C[] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202f\202\201\202\222\202\202\201@\202P"; // Divine Garb 1
const char aForestGarb_80073D98[] = "\202e\202\217\202\222\202\205\202\223\202\224\201@\202f\202\201\202\222\202\202"; // Forest Garb
const char aNavyBlueGarb_80073DB0[] = "\202m\202\201\202\226\202\231\201@\202a\202\214\202\225\202\205\201@\202f\202\201\202\222\202\202"; // Navy Blue Garb
const char aBloodyGarb_80073DD0[] = "\202a\202\214\202\217\202\217\202\204\202\231\201@\202f\202\201\202\222\202\202"; // Bloody Garb
const char aNagiGarb_80073DE8[] = "\202m\202\201\202\207\202\211\201@\202f\202\201\202\222\202\202"; // Nagi Garb
const char aRiketzGarb_80073DFC[] = "\202q\202\211\202\213\202\205\202\224\202\232\201f\201@\202f\202\201\202\222\202\202"; // Riketz' Garb
const char aDivineVest_80073E18[] = "\202c\202\211\202\226\202\211\202\216\202\205\201@\202u\202\205\202\223\202\224"; // Divine Vest
const char aSilverVest_80073E30[] = "\202r\202\211\202\214\202\226\202\205\202\222\201@\202u\202\205\202\223\202\224"; // Silver Vest
const char aReflectingVest_80073E48[] = "\202q\202\205\202\206\202\214\202\205\202\203\202\224\202\211\202\216\202\207\201@\202u\202\205\202\223\202\224"; // Reflecting Vest
const char aPlateMailVest_80073E68[] = "\202o\202\214\202\201\202\224\202\205\201@\202l\202\201\202\211\202\214\201@\202u\202\205\202\223\202\224"; // Plate Mail Vest
const char aWireVest_80073E88[] = "\202v\202\211\202\222\202\205\201@\202u\202\205\202\223\202\224"; // Wire Vest
const char aChainMailVest_80073E9C[] = "\202b\202\210\202\201\202\211\202\216\201@\202l\202\201\202\211\202\214\201@\202u\202\205\202\223\202\224"; // Chain Mail Vest
const char aLeatherVest_80073EBC[] = "\202k\202\205\202\201\202\224\202\210\202\205\202\222\201@\202u\202\205\202\223\202\224"; // Leather Vest
const char aHunterSVest_80073ED8[] = "\202g\202\225\202\216\202\224\202\205\202\222\201f\202\223\201@\202u\202\205\202\223\202\224"; // Hunter's Vest
const char aNagiBelt_80073EF4[] = "\202m\202\201\202\207\202\211\201@\202a\202\205\202\214\202\224"; // Nagi Belt
const char aSuperChoker_80073F08[] = "\202r\202\225\202\220\202\205\202\222\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Super Choker
const char aStoneChoker_80073F24[] = "\202r\202\224\202\217\202\216\202\205\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Stone Choker
const char aSleepChoker_80073F40[] = "\202r\202\214\202\205\202\205\202\220\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Sleep Choker
const char aPoisonChoker_80073F5C[] = "\202o\202\217\202\211\202\223\202\217\202\216\201@\202b\202\210\202\217\202\213\202\205\202\222"; // Poison Choker
const char aHawkRuff_80073F78[] = "\202g\202\201\202\227\202\213\201@\202q\202\225\202\206\202\206"; // Hawk Ruff
const char aHollyRuff_80073F8C[] = "\202g\202\217\202\214\202\214\202\231\201@\202q\202\225\202\206\202\206"; // Holly Ruff
const char aSilverCrown_80073FA4[] = "\202r\202\211\202\214\202\226\202\205\202\222\201@\202b\202\222\202\217\202\227\202\216"; // Silver Crown
const char aIronBracelet_80073FC0[] = "\202h\202\222\202\217\202\216\201@\202a\202\222\202\201\202\203\202\205\202\214\202\205\202\224"; // Iron Bracelet
const char aSparrowRuff_80073FDC[] = "\202r\202\220\202\201\202\222\202\222\202\217\202\227\201@\202q\202\225\202\206\202\206"; // Sparrow Ruff
const char aRedBead_80073FF8[] = "\202q\202\205\202\204\201@\202a\202\205\202\201\202\204"; // Red Bead
const char aYellowBead_8007400C[] = "\202x\202\205\202\214\202\214\202\217\202\227\201@\202a\202\205\202\201\202\204"; // Yellow Bead
const char aGreenBead_80074024[] = "\202f\202\222\202\205\202\205\202\216\201@\202a\202\205\202\201\202\204"; // Green Bead
const char aBlueBead_8007403C[] = "\202a\202\214\202\225\202\205\201@\202a\202\205\202\201\202\204"; // Blue Bead
const char aSilverHeadband_80074050[] = "\202r\202\211\202\214\202\226\202\205\202\222\201@\202g\202\205\202\201\202\204\202\202\202\201\202\216\202\204"; // Silver Headband
const char aIronHeadband_80074070[] = "\202h\202\222\202\217\202\216\201@\202g\202\205\202\201\202\204\202\202\202\201\202\216\202\204"; // Iron Headband
const char aLeatherHeadband_8007408C[] = "\202k\202\205\202\201\202\224\202\210\202\205\202\222\201@\202g\202\205\202\201\202\204\202\202\202\201\202\216\202\204"; // Leather Headband
// Matched
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
// Matched
void UpdatePadAnalog_8001CC04(int port)
{
    signed char* stick;
    unsigned char* mx;
    int v;
    int m;
    padAnalog_800918D8[port][0] = pads_800918E8[port][4] + 0x80;
    padAnalog_800918D8[port][1] = 0x7F - pads_800918E8[port][5];
    padAnalog_800918D8[port][2] = pads_800918E8[port][6] + 0x80;
    padAnalog_800918D8[port][3] = 0x7F - pads_800918E8[port][7];
    stick = padAnalog_800918D8[port];
    mx = padAnalogMax_800918E0[port];
    v = stick[0];
    m = mx[0];
    if (v < 0)
    {
        v = -v;
    }
    if (m < v)
    {
        mx[0] = v;
    }
    v = stick[1];
    m = mx[0];
    if (v < 0)
    {
        v = -v;
    }
    if (m < v)
    {
        mx[0] = v;
    }
    v = stick[2];
    m = mx[1];
    if (v < 0)
    {
        v = -v;
    }
    if (m < v)
    {
        mx[1] = v;
    }
    v = stick[3];
    m = mx[1];
    if (v < 0)
    {
        v = -v;
    }
    if (m < v)
    {
        mx[1] = v;
    }
}
// Matched
void ResetPadHoldFrames_8001CD04(int port)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        padHoldFrames_80091950[port][i] = 0;
    }
}
// Matched
int sub_8001CD34(void)
{
    return 0;
}
// Matched
int GetPersonName_8001CD3C(int idx)
{
    return personNames_8007CB20[idx];
}
// Matched
unsigned char* GetPersonMergeInfo_8001CD58(int idx)
{
    return personMergeInfo_8007CB4C[idx];
}
// Matched
int GetPersonIcon_8001CD6C(void)
{
    return 0x36;
}
// Matched
unsigned char* GetAccessoryModifiers_8001CD74(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return accessoryModifiers_8007D848[idx];
}
// Matched
unsigned char* GetArmorModifiers_8001CDA0(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return armorModifiers_8007D598[idx];
}
// Matched
unsigned char GetItemEffect_8001CDCC(unsigned int idx)
{
    if (idx < 0x2B)
    {
        return itemEffects_8007CC24[idx];
    }
    return 0x22;
}
// Matched
ActionData* GetItemData_8001CDF4(unsigned int idx)
{
    if (idx < 0x2B)
    {
        return &itemData_8007CCA8[idx];
    }
    return 0;
}
// Matched
int GetItemName_8001CE20(unsigned int idx)
{
    if (idx >= 0x2B)
    {
        return 0;
    }
    return itemNames_8007CB78[idx];
}
// Matched
int sub_8001CE4C(void)
{
    return 0;
}
// Matched
unsigned short GetItemPrice_8001CE54(int idx)
{
    return itemPrices_8007CED8[idx];
}
// Matched
unsigned short GetItemFlags_8001CE70(int idx)
{
    return itemFlags_8007CC50[idx];
}
// Matched
int GetItemTargetFlags_8001CE8C(int idx)
{
    unsigned short flags = itemFlags_8007CC50[idx];
    int r = (flags >> 5) & 2;
    if (flags & 0x80)
    {
        r |= 4;
    }
    if (flags & 4)
    {
        r |= 1;
    }
    return r;
}
// Matched
unsigned char GetItemFlagsLow_8001CED0(int idx)
{
    return *(unsigned char*)&itemFlags_8007CC50[idx];
}
// Matched
int sub_8001CEEC(void)
{
    return 1;
}
// Matched
int* GetWeaponStatBonus_8001CEF4(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return (int*)weaponData_8007D04C[idx].statBonus_4;
}
// Matched
int GetWeaponName_8001CF20(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return weaponNames_8007CFF0[idx];
}
// Matched
int GetWeaponPrice_8001CF4C(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return weaponPrices_8007D388[idx] * 10;
}
// Matched
EquipmentData* GetWeaponData_8001CF84(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return &weaponData_8007D04C[idx];
}
// Matched
int* GetArmorStatBonus_8001CFB0(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return (int*)armorData_8007D420[idx].statBonus_4;
}
// Matched
int GetArmorName_8001CFDC(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return armorNames_8007D3E4[idx];
}
// Matched
int GetArmorPrice_8001D008(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return armorPrices_8007D64C[idx];
}
// Matched
EquipmentData* GetArmorData_8001D034(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return &armorData_8007D420[idx];
}
// Matched
unsigned char GetArmorOutfit_8001D060(int idx)
{
    return armorOutfits_8007D588[idx];
}
// Matched
int* GetAccessoryStatBonus_8001D078(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return (int*)accessoryData_8007D6B0[idx].statBonus_4;
}
// Matched
int GetAccessoryName_8001D0A4(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return accessoryNames_8007D66C[idx];
}
// Matched
int GetAccessoryPrice_8001D0D0(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return accessoryPrices_8007D914[idx];
}
// Matched
EquipmentData* GetAccessoryData_8001D0FC(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return &accessoryData_8007D6B0[idx];
}
// Matched
int GetEquipmentName_8001D128(int idx, unsigned int kind)
{
    int r = 0;
    switch (kind)
    {
    case 0:
        r = GetWeaponName_8001CF20(idx);
        break;
    case 1:
        r = GetArmorName_8001CFDC(idx);
        break;
    case 2:
        r = GetAccessoryName_8001D0A4(idx);
        break;
    }
    return r;
}
// Matched
EquipmentData* GetEquipmentData_8001D190(idx, kind)
unsigned int idx;
unsigned int kind;
{
    EquipmentData* r = 0;
    switch (kind)
    {
    case 0:
        r = GetWeaponData_8001CF84(idx);
        break;
    case 1:
        r = GetArmorData_8001D034(idx);
        break;
    case 2:
        r = GetAccessoryData_8001D0FC(idx);
        break;
    }
    return r;
}
// Matched
int GetEquipmentPrice_8001D1F8(int idx, unsigned int kind)
{
    int r = 0;
    switch (kind)
    {
    case 0:
        r = GetWeaponPrice_8001CF4C(idx);
        break;
    case 1:
        r = GetArmorPrice_8001D008(idx);
        break;
    case 2:
        r = GetAccessoryPrice_8001D0D0(idx);
        break;
    }
    return r;
}
// Matched
ActionData* GetLevantWeaponAction_8001D260(void)
{
    unsigned int i = sub_800AD990(0);
    if (i < 0x17)
    {
        return &weaponActions_8007D274[i];
    }
    return 0;
}
// Matched
int GetItemIcon_8001D2AC(int idx)
{
    if (idx < 0x2B)
    {
        return itemIcons_8007CEAC[idx];
    }
    return 0xFF;
}
// Matched
int GetEquipmentIcon_8001D2D4(void)
{
    EquipmentData* p = GetEquipmentData_8001D190();
    if (p != 0)
    {
        return equipmentIcons_8007D938[p->icon_0];
    }
    return 0x24;
}
// Matched
char* GetKeyItemName_8001D318(unsigned int idx)
{
    if (idx >= 0x26)
    {
        return 0;
    }
    return keyItemNames_8007CF30[idx];
}
// Matched
int GetKeyItemIcon_8001D344(int idx)
{
    if (idx < 0x26)
    {
        return keyItemIcons_8007CFC8[idx];
    }
    return 0x24;
}
// Matched
int IsKnowledgeKeyItem_8001D36C(int v)
{
    return (unsigned int)(v - 0x19) < 0xD;
}
// Matched
void InitActors_8001D378(void)
{
    ResetModelLoader_800204D0();
    StopModelLoader_800205F0();
    ClearModelAnimRefs_800201A4();
    ListInit_8003FDB0(actorHeap_80091990);
    StopAllEventEntries_80043B40(actorTasks_8008D43C);
}
// Matched
void FreeActors_8001D3C4(int freeModels)
{
    if (freeModels != 0)
    {
        StopModelLoader_800205F0();
        FreeModelLoaderList_8002052C();
        ResetModelLoader_800204D0();
    }
    ListFreeAll_8003FEC8(actorHeap_80091990);
    StopAllEventEntries_80043B40(actorTasks_8008D43C);
    ClearModelAnimRefs_800201A4();
}
// Matched
void UpdateActorCb_8001D41C(EventEntry* e, void* actor)
{
    UpdateActorScript_8001EA28(actor);
    UpdateActorMotion_8001F354(actor);
    UpdateActorAnimLoad_8001F918(actor);
    UpdateActor_8001F9AC(actor);
}
// Matched
Actor* CreateActor_8001D45C(ActorDesc* desc)
{
    EventEntry* e = AllocEventEntry_80043AF8(actorTasks_8008D43C);
    Actor* actor;
    if (e != 0)
    {
        actor = e->buffer;
        e->cb_8 = UpdateActorCb_8001D41C;
        e->flags = (e->flags | 1) & ~0x8000;
        actor->task_0 = e;
        InitActor_8001E574(actor, desc);
        return actor;
    }
    return 0;
}
// Matched
Actor* CloneActor_8001D4DC(Actor* src, int kind, int clutRow, int hasMatrices)
{
    ActorDesc desc;
    Actor* r;
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
    r = CreateActor_8001D45C(&desc);
    SetActorGroundMove_8001D68C(r, (src->flags_4 >> 18) & 1);
    return r;
}
// Matched
void DestroyActor_8001D600(Actor* actor)
{
    EventEntry* e = actor->task_0;
    ReleaseModelAnimRef_80020278(actor->modelRef_16, e->field_4);
    FreeActorBones_8001EA00(actor);
    e->flags = (e->flags & ~1) | 0x8000;
}
// Matched
void SetActorActive_8001D658(Actor* a, int on)
{
    EventEntry* p = a->task_0;
    if (on)
    {
        p->flags &= 0xFFFF7FFF;
    }
    else
    {
        p->flags |= 0x8000;
    }
}
// Matched
void SetActorGroundMove_8001D68C(Actor* p, int on)
{
    if (on)
    {
        p->flags_4 |= 0x40000;
    }
    else
    {
        p->flags_4 &= ~0x40000;
    }
}
// Matched
void SetActorRootMotion_8001D6BC(Actor* p, int on)
{
    if (on)
    {
        p->flags_4 |= 0x1000000;
    }
    else
    {
        p->flags_4 &= ~0x1000000;
    }
}
// Matched
void SetActorAnimPaused_8001D6EC(Actor* p, int on)
{
    if (on)
    {
        p->flags_4 |= 4;
    }
    else
    {
        p->flags_4 &= ~4;
    }
}
// Matched
void RestartActorMotion_8001D71C(Actor* p)
{
    p->flags_4 |= 8;
}
// Matched
void SetActorVisible_8001D730(Actor* p, int on)
{
    if (on)
    {
        p->flags_4 &= ~0x2000;
    }
    else
    {
        p->flags_4 |= 0x2000;
    }
}
// Matched
void SetActorAnim_8001D760(Actor* actor, int idx, int mode, int a3)
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
        int r = rand();
        base = actor->anims_148[idx].start_2;
        actor->frame_90 = base + r % (actor->anims_148[idx].loop_4 - base);
    }
    else
    {
        actor->frame_90 = mode % actor->endFrame_1A;
    }
    actor->frameFrac_1C = 0;
    actor->blend_AC = 0;
    actor->flags_4 |= 8;
    if (a3)
    {
        actor->flags_4 |= 0x10;
    }
}
// Matched
int IsActorAnimLoadIdle_8001D8A8(Actor* p)
{
    return p->animLoadState_10 == 0;
}
// Matched
void RequestActorAnim_8001D8B4(Actor* actor, int idx)
{
    if (actor->anims_148[idx].kind_1 == 0)
    {
        if (RequestModelAnim_8002032C(actor->modelRef_16, actor->task_0->field_4, actor->anims_148[idx].id_0))
        {
            actor->animLoading_14 = idx;
            actor->animLoadState_10 = 2;
        }
    }
}
// Matched
void ReleaseActorAnim_8001D92C(Actor* actor, int idx)
{
    ActorAnim* e;
    int i;
    int key;
    int n;
    e = actor->anims_148;
    key = e[idx].id_0;
    n = ((int*)e)[-1];
    for (i = 0; i < n; i++)
    {
        if (key == e->id_0 && e->kind_1 == 1)
        {
            return;
        }
        e++;
    }
    ReleaseModelAnim_800203B0(actor->modelRef_16, actor->task_0->field_4, key);
}
// Matched
void SkipActorAnimToEnd_8001D9B0(Actor* p)
{
    if (!(p->flags_D4 & 2))
    {
        p->frame_90 = p->endFrame_1A;
        p->frameFrac_1C = 0;
        p->flags_4 |= 0x4000;
    }
}
// Matched
void StartActorFadeIn_8001D9E4(Actor* p, int div, int flags)
{
    p->fade_20 = 0;
    p->fadeDiv_22 = div;
    p->flags_4 |= 0x20;
    p->flags_4 |= flags;
    p->flags_4 &= ~0x40;
}
// Matched
void StartActorFadeOut_8001DA08(Actor* p, int div, int flags)
{
    p->fade_20 = 0;
    p->fadeDiv_22 = div;
    p->flags_4 |= 0x40;
    p->flags_4 |= flags;
    p->flags_4 &= ~0x20;
}
// Matched
void StopActorFade_8001DA2C(Actor* p)
{
    p->fade_20 = 0;
    p->fadeDiv_22 = 0;
    p->flags_4 &= 0xBFFFF81F;
}
// Matched
void StartActorScale_8001DA4C(Actor* p, int div, int from, int to)
{
    if (from < 0)
    {
        from = p->scale_26;
    }
    if (to < from)
    {
        p->scaleStep_28 = (from - to) / div;
        p->scale_26 = from;
        p->scaleTarget_2A = to;
        p->flags_4 |= 1;
    }
    else
    {
        p->scaleStep_28 = (to - from) / div;
        p->scale_26 = from;
        p->scaleTarget_2A = to;
        p->flags_4 |= 3;
    }
}
// Matched
void SetActorTint_8001DAAC(Actor* o, int tint)
{
    if (tint != 0)
    {
        o->flags_4 |= 0x800;
        TintVramImage_800292D0(&o->image_150, o->clut_158, tint);
    }
    else
    {
        o->flags_4 &= ~0x800;
    }
}
// Matched
void SetActorTurnTarget_8001DB00(Actor* o, int* target, int step)
{
    if (target != 0)
    {
        o->target_70.vx = target[0];
        o->target_70.vy = target[1];
        o->target_70.vz = target[2];
        o->target_70.pad = step;
        o->flags_4 |= 0x4000000;
    }
    else
    {
        o->flags_4 &= ~0x4000000;
    }
}
// Matched
void SetActorSpeedScale_8001DB58(Actor* p, int scale, int on)
{
    if (on)
    {
        p->speedScale_8C = scale;
        p->flags_4 |= 0x20000000;
    }
    else
    {
        p->speedScale_8C = 0x1000;
        p->flags_4 &= ~0x20000000;
    }
}
#if 0
// Not matched (5 words): the original stores 0xC0 after the flags and copies s to $a3 after the mask; with a saved
// "old" local stored at the end instead, old and the 0xFFFF7FFF mask swap $a1/$a2 (6 words)
void SetActorScript_8001DB98(Actor* o, unsigned char* s)
{
    o->prevAnimIdx_C0 = o->animIdx_C2;
    o->animIdx_C2 = -1;
    o->scriptPos_C4 = 0;
    o->scriptLen_C6 = 1;
    o->wait_C8 = 0;
    o->waitLen_CA = 0;
    o->fCC = -1;
    o->fCE = -1;
    o->script_D0 = (ActorScriptCmd*)s;
    o->flags_4 &= ~0x8000;
    o->flags_4 |= 0x4000;
    while (s[0] != 0)
    {
        o->scriptLen_C6 += s[1];
        s += s[1] * 4;
    }
}
#endif
INCLUDE_ASM(SetActorScript_8001DB98);
// Matched
void StartActorScript_8001DC34(void* actor, void* script)
{
    SetActorScript_8001DB98(actor, script);
    RunActorScript_8001EA48(actor);
}
// Matched
int ApproachActorTarget_8001DC60(Actor* actor, VECTOR* target, int turnStep, int range)
{
    unsigned int dist;
    int x = actor->pos_38[2];
    int y = actor->prevPos_44[2];
    int d;
    int t;
    dist = 0xFFF;
    if (y < x)
    {
        d = x - y;
    }
    else
    {
        d = y - x;
    }
    if (IsWithinDistance_8003B740(actor->pos_38, target, &dist))
    {
        if (dist < d * d)
        {
            return 1;
        }
    }
    t = d + 0x32;
    if (dist < t * t)
    {
        if (IsActorNear_8001DFC8(actor, target, range, 1))
        {
            return 1;
        }
    }
    TurnActorTowards_8001DDFC(actor, target, turnStep);
    return 0;
}
// Matched
int TurnActorBy_8001DD44(Actor* o, int dir, int a, int b)
{
    int m;
    int r;
    m = a;
    if (a >= b)
    {
        m = b;
    }
    if (dir == 1)
    {
        o->turn_194.input_8 = m;
    }
    else
    {
        o->turn_194.input_8 = -m;
    }
    RestartActorMotion_8001D71C(o);
    FirFilterStep_80014588(o->turnFilterBuf_1A4, &o->turn_194, frameCount_8008D3FC);
    o->rot_5C[1] += o->turn_194.output_C.low;
    r = a - b;
    return r < 0 ? 0 : (a < r ? a : r);
}
// Matched
int TurnActorTowards_8001DDFC(Actor* o, VECTOR* target, int step)
{
    VECTOR d;
    int a;
    d.vx = target->vx - o->pos_38[0];
    d.vz = target->vz - o->pos_38[2];
    a = (ratan2_8003B548(d.vx, d.vz) - o->rot_5C[1]) & 0xFFF;
    o->turn_194.input_8 = 0;
    if (a < step || a >= 0x1000 - step)
    {
        o->rot_5C[1] += a;
        return 1;
    }
    if (a < 0x800)
    {
        o->turn_194.input_8 = step;
    }
    else
    {
        o->turn_194.input_8 = -step;
    }
    FirFilterStep_80014588(o->turnFilterBuf_1A4, &o->turn_194, frameCount_8008D3FC);
    o->rot_5C[1] += o->turn_194.output_C.low;
    return 0;
}
// Matched
int FindActorInFront_8001DECC(Actor* o, int range, int checkLevant)
{
    EventNode* n;
    EventEntry* e;
    int count;
    int i;
    int found = 0;
    range = range * range;
    if (checkLevant)
    {
        found = IsInFrontWithinRange_8001E0F4((VECTOR*)o->pos_38, o->rot_5C[1], (VECTOR*)&levantPos_8008BD18.pos, range);
    }
    if (found == 0)
    {
        n = actorTasks_8008D43C;
        count = n->count;
        for (i = 0; i < count; i++)
        {
            e = &n->entry;
            if ((e->flags & 0x8001) == 1 && o->task_0 != ((Actor*)e->buffer)->task_0)
            {
                found = IsInFrontWithinRange_8001E0F4((VECTOR*)o->pos_38, o->rot_5C[1], (VECTOR*)((Actor*)e->buffer)->pos_38, range);
                if (found)
                {
                    break;
                }
            }
            n = n->next;
        }
    }
    return found;
}
// Matched
int IsActorNear_8001DFC8(Actor* o, VECTOR* target, int range, int checkLevant)
{
    EventNode* n;
    EventEntry* e;
    Actor* b;
    int count;
    int i;
    unsigned int dist;
    if (checkLevant)
    {
        dist = 0xFFF;
        if (IsWithinDistance_8003B740((VECTOR*)o->pos_38, (VECTOR*)&levantPos_8008BD18.pos, &dist) != 0 && dist < range * range)
        {
            return 1;
        }
    }
    n = actorTasks_8008D43C;
    count = n->count;
    for (i = 0; i < count; i++)
    {
        e = &n->entry;
        if ((e->flags & 0x8001) == 1 && o->task_0 != (b = (Actor*)e->buffer)->task_0)
        {
            dist = 0xFFF;
            if (IsWithinDistance_8003B740((VECTOR*)o->pos_38, (VECTOR*)b->pos_38, &dist) != 0 && dist < range * range)
            {
                return 1;
            }
        }
        n = n->next;
    }
    return 0;
}
#if 0
// Not matched: the final range test becomes a set-on-less-than here, the original branches to return 1 / 0
int IsInFrontWithinRange_8001E0F4(VECTOR* from, int angle, VECTOR* to, unsigned int range)
{
    VECTOR d;
    unsigned int dist;
    int a;
    dist = 0xFFF;
    if (IsWithinDistance_8003B740(from, to, &dist) != 1)
    {
        return 0;
    }
    if (dist >= range)
    {
        return 0;
    }
    d.vx = to->vx - from->vx;
    d.vz = to->vz - from->vz;
    a = (ratan2_8003B548(d.vx, d.vz) - angle) & 0xFFF;
    if (a < 0x400)
    {
        return 2;
    }
    if (a > 0xC00 && a < 0x1000)
    {
        return 1;
    }
    return 0;
}
#endif
INCLUDE_ASM(IsInFrontWithinRange_8001E0F4);
// Matched
int IsActorIdle_8001E1C8(Actor* p)
{
    return (p->flags_4 & 0x280000) == 0;
}
// Matched
int IsActorActionReady_8001E1DC(Actor* p)
{
    if (p->effect_130 >= 0)
    {
        if (IsEffectReady_80014954() == 0)
        {
            return 0;
        }
    }
    if (p->flags_4 & 0x80000)
    {
        if (p->kind_C < 3)
        {
            return 0;
        }
    }
    if (p->flags_4 & 0x400000)
    {
        return 0;
    }
    return 1;
}
// Matched
int StartActorAction_8001E254(Actor* actor, void* desc)
{
    actor->flags_4 = (actor->flags_4 & 0xFFFDFFFF) | 0x600000;
    return SetActorAction_8001E34C(actor, desc);
}
// Matched
void TriggerActorEffect_8001E28C(Actor* o)
{
    ActorEffectReq s;
    if (o->effect_130 >= 0)
    {
        s.effect_0 = o->effect_130;
        s.hitTimes_4 = o->hitTimes_108;
        s.tbl_8 = o->effectTbl_14C;
        s.pos_C = o->pos_38;
        s.bonePos_10 = o->bonePos_1C4;
        s.boneMatrices_14 = o->boneMatrices_1C8;
        s.boneScale_34 = o->boneScale_144;
        s.scale_38 = o->scale_2C;
        CollectEffectTargets_800182B8(&s, o->effectKinds_EC);
        PlayActorEffect_800184DC(&s, LowestSetBit_80014358(o->effectMask_E8));
        o->effect_130 = -1;
    }
    o->flags_4 |= 0x20000;
    if (o->f100 != 0)
    {
        StopActorScript_8001EFC4(o);
    }
}
// Matched
int SetActorAction_8001E34C(Actor* actor, ActorActionDesc* d)
{
    int r;
    int f;
    int g;
    actor->flags_D4 = d->flags_0;
    actor->fE0 = d->turnStep_C;
    actor->effectMask_E8 = d->effectMask_14;
    actor->effectKinds_EC = d->effectKinds_18;
    actor->loopCount_F4 = d->loopCount_20;
    actor->scaleTarget_F6 = d->scaleTarget_22;
    actor->fFC = d->field_28;
    actor->queuedAnim_FE = d->queuedAnim_2A;
    actor->fE0 = d->turnStep_C;
    actor->f100 = d->field_2C;
    r = 0;
    if (d->script_4)
    {
        StartActorScript_8001DC34(actor, d->script_4);
    }
    if (d->hitAnim_E >= 0)
    {
        r = GetActorHitTimes_8001F268(actor, actor->hitTimes_108, (int)actor->script_D0, d->hitAnim_E);
    }
    f = d->effect_10;
    if (f >= 0)
    {
        actor->effect_130 = f;
        RequestEffect_800148F4(f);
    }
    if (d->target_8)
    {
        actor->pathTarget_DC = d->target_8;
        actor->target_70.vx = d->target_8[0];
        actor->target_70.vy = d->target_8[1];
        actor->target_70.vz = d->target_8[2];
        f = d->turnStep_C;
        actor->flags_4 |= 0x80000;
        actor->target_70.pad = f;
        if (d->nextAnim_24 >= 0)
        {
            actor->nextAnim_A4 = d->nextAnim_24;
            StartActorScript_8001DC34(actor, moveToScript_8007D95C);
        }
        else
        {
            actor->nextAnim_A4 = d->nextAnim_26;
            StartActorScript_8001DC34(actor, moveToScriptAlt_8007D980);
        }
    }
    if (d->path_30)
    {
        actor->pathStep_98 = 0;
        actor->flags_4 |= 0x2000000;
        actor->path_160 = d->path_30;
    }
    if (d->queuedAnim_2A >= 0)
    {
        actor->nextAnim_A4 = d->field_28;
        actor->startMode_A8 = d->turnStep_C;
        StartActorScript_8001DC34(actor, playQueuedAnimScript_8007D9C0);
    }
    else if (d->field_28 >= 0)
    {
        actor->nextAnim_A4 = d->field_28;
        actor->startMode_A8 = d->turnStep_C;
        StartActorScript_8001DC34(actor, playAnimScript_8007D9A4);
    }
    g = actor->flags_4;
    if (d->field_1C)
    {
        g |= 0x800000;
    }
    actor->flags_4 = g;
    return r;
}
#if 0
// Not matched (18 lines): the original keeps the 0x9C..0xA4 and 0x130/0x15C stores after the 0xA8..0xCE block (with a
// register copy of the anim index for 0xA4), here they are scheduled right after the d->animIdx_20 load. Tried: separate
// anim variable, reading d->animIdx_20 directly / late, chained assignments, 0xA4 from f / 0x9C
void InitActor_8001E574(Actor* actor, ActorDesc* desc)
{
    Model* m;
    int v;
    int f;
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
    actor->scaleTarget_2A = 0x1000;
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
    f = desc->animIdx_20;
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
    actor->anim_9C = f;
    actor->prevAnim_A0 = f;
    actor->nextAnim_A4 = actor->prevAnim_A0;
    actor->animIdx_C2 = actor->prevAnimIdx_C0 = *(short*)&actor->anim_9C;
    actor->effect_130 = -1;
    actor->model_15C = m;
    actor->image_150.x = actorImageRect_8007DC8C[0];
    actor->image_150.y = actorImageRect_8007DC8C[1] + m->list_0->vram_C[m->slot_30].reloc_4[5];
    actor->image_150.w = actorImageRect_8007DC8C[2];
    actor->image_150.h = actorImageRect_8007DC8C[3];
    actor->clut_158[0] = actorClutPos_8007DC94[0];
    actor->clut_158[1] = actorClutPos_8007DC94[1] + *(short*)&desc->clutRow_1C;
    actor->path_160 = 0;
    AllocActorBones_8001E7F0(actor, desc);
    FirFilterInit_8001450C(actor->turnFilterBuf_1A4, &actor->turn_194, turnFilterCoeffs_800795A0, 8);
    SetActorAnim_8001D760(actor, desc->animIdx_20, desc->frame_24, 0);
}
#endif
INCLUDE_ASM(InitActor_8001E574);
// Matched
void AllocActorBones_8001E7F0(Actor* actor, ActorDesc* desc)
{
    short* p;
    int n;
    int size;
    int i;
    char* mem;
    SVECTOR* src;
    int sz0;
    int sz1;
    p = desc->bones_34;
    n = 0;
    while (p[n * 4] != -1)
    {
        n++;
    }
    sz0 = (n + 1) << 3;
    sz1 = n << 3;
    size = sz0;
    size += sz1;
    size += n * 12;
    if (desc->hasMatrices_4C)
    {
        size += n * 32;
    }
    mem = ListAlloc_8003FDC0(actorHeap_80091990, size);
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
        for (i = 0; i < n; i++)
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
    mem += n * 12;
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
// Matched
void FreeActorBones_8001EA00(Actor* actor)
{
    int v = (int)actor->bones_134;
    ListFree_8003FE38(actorHeap_80091990, (void*)v);
}
// Matched
void UpdateActorScript_8001EA28(void* actor)
{
    RunActorScript_8001EA48(actor);
}

int primBufferStart_800960A0[2] BSS = { 0 };
int primAllocPtr_800960A8[2] BSS = { 0 };
