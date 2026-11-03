#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
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

INCLUDE_DATA(dword_80073044);
INCLUDE_DATA(dword_80073048);
INCLUDE_DATA(dword_8007304C);
INCLUDE_DATA(dword_80073064);
INCLUDE_DATA(dword_800730C8);
INCLUDE_DATA(dword_800730DC);
INCLUDE_DATA(dword_800730F0);
INCLUDE_DATA(dword_80073108);
INCLUDE_DATA(dword_80073118);
INCLUDE_DATA(dword_80073138);
INCLUDE_DATA(dword_80073154);
INCLUDE_DATA(dword_80073164);
INCLUDE_DATA(dword_80073174);
INCLUDE_DATA(dword_800731A4);
INCLUDE_DATA(dword_800731B4);
INCLUDE_DATA(dword_800731C4);
INCLUDE_DATA(dword_800731EC);
INCLUDE_DATA(overlayAdrr1_800731F8);
INCLUDE_DATA(overlayAddr2_800731FC);
INCLUDE_DATA(overlayAddr3_80073200);
INCLUDE_DATA(overlayAddr4_80073204);
INCLUDE_DATA(overlayAddr5_80073208);
INCLUDE_DATA(overlayAddr6_8007320C);
INCLUDE_DATA(dword_80073210);
INCLUDE_DATA(fileRequestQueue_80086540);
INCLUDE_DATA(dword_80086544);
INCLUDE_DATA(dword_80086548);
INCLUDE_DATA(dword_8008654C);
INCLUDE_DATA(cdReadState_80086550);
INCLUDE_DATA(dword_80086554);
INCLUDE_DATA(dword_80086558);
INCLUDE_DATA(dword_8008655C);
INCLUDE_DATA(dword_80086560);
INCLUDE_DATA(fileBufferInUse_80086564);
INCLUDE_DATA(dword_80086568);
INCLUDE_DATA(fileBuffer_8008656C);
/* char* data001Path_80086570 = "\\DATA\\DATA.001;1"; (the string literal would be emitted into .rdata, not owned yet) */
INCLUDE_DATA(data001Path_80086570);
INCLUDE_DATA(fontDefs_80086574);
INCLUDE_DATA(dword_800865B8);
INCLUDE_DATA(charTables_8008685C);
INCLUDE_DATA(dword_8008686C);
INCLUDE_DATA(dword_80086878);
INCLUDE_DATA(dword_80086898);
INCLUDE_DATA(copyrightData_80086930);
INCLUDE_DATA(copyright_80086948);
INCLUDE_DATA(genkiMovieData_80086950);
INCLUDE_DATA(genkiMovie_80086968);
INCLUDE_DATA(craveEntertainmentData_80086970);
INCLUDE_DATA(craveEntertainmentMovie_80086988);
INCLUDE_DATA(demoDisclaimerData_80086990);
INCLUDE_DATA(demoDisclaimer_800869A8);
INCLUDE_DATA(introAnimeData_800869B0);
INCLUDE_DATA(introAnime_800869C8);
INCLUDE_DATA(overlayCallbacks_800869D0);
INCLUDE_DATA(strMovies_80086A4C);
INCLUDE_DATA(mdecVLCBuffer_80086F94);
INCLUDE_DATA(movieWidth_80086F98);
INCLUDE_DATA(movieHeight_80086F9A);
INCLUDE_DATA(byte_80086F9C);
INCLUDE_DATA(dword_80086FB0);
INCLUDE_DATA(byte_80086FEC);
INCLUDE_DATA(byte_80086FED);
INCLUDE_DATA(byte_80086FEE);
INCLUDE_DATA(dword_80086FF0);
INCLUDE_DATA(dword_80087014);
INCLUDE_DATA(off_80087028);
INCLUDE_DATA(off_8008703C);
INCLUDE_DATA(off_80087050);
INCLUDE_DATA(off_80087064);
INCLUDE_DATA(dword_80087070);
INCLUDE_DATA(dword_80087114);
INCLUDE_DATA(dword_80087118);
INCLUDE_DATA(dword_8008711C);
INCLUDE_DATA(dword_80087120);
INCLUDE_DATA(dword_80087124);
INCLUDE_DATA(dword_80087134);
INCLUDE_DATA(dword_80087138);

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
struct_20* sub_80019C28(unsigned int idx)
{
    if (0xC9 > idx)
    {
        return &dword_8007A9F8[idx];
    }
    return sub_800B3274(idx - 0x39);
}
// Matched
int* sub_80019C70(int idx)
{
    return &dword_8007BD30[idx];
}
// Matched
int sub_80019C84(void)
{
    int v = 0x24;
    int c = dword_8008D4DC & 0xFF;
    if (unknownFlags_8008D678 & 0x1000)
    {
        v = c % 4 + 0x25;
    }
    return v;
}
// the block at 0x8008D4F0 (tu_80036528.c copies its first 0x68 bytes as Block104)
typedef struct
{
    VECTOR pos;
    int field_10;
    int active;
} struct_8008D4F0_point;
typedef struct
{
    char pad_0[0x44];
    struct_8008D4F0_point points[8];
} struct_8008D4F0;
extern VECTOR levantPos_8008BD18;
extern short dword_8008D474[2];
extern int off_8007DC70;
extern short asc_80084350[]; // a short table (indexed & 0xFFF) starts at +0x1F0 (0x80084540)
typedef struct
{
    int fileIdx;
    unsigned int** ppDest;
} OverlayEntry;
extern OverlayEntry overlays_8007D9E8[];
extern int QueueFileRequest_8003BC84(int* p);
extern int StartFileRequestTask_8003C6C8(int* req);
void OnEffectFileLoaded_80020F5C();
extern unsigned short padPrevHeld_800918C8[];
extern unsigned short padRepeat_800918CC[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padPressed_8009194C[];
extern unsigned short padHoldFrames_80091950[][16];
extern signed char padAnalog_800918D8[][4];
extern unsigned char padAnalogMax_800918E0[][4];
#if 0
// Not matched: loop counter i is set with move s1,zero in the original, the compiler copies found (s4) instead
typedef struct
{
    char pad[0x44];
    struct
    {
        int pos[5];
        int active;
    } points[8];
} CamState_80019CC4;
extern char cameraState_8008D4F0[];
extern int DistanceSquaredXZ_8003B860(int* a, int* b);
int sub_80019CC4(int* pos)
{
    unsigned int i;
    unsigned int best;
    int found;
    best = -1;
    found = 0;
    if (!(unknownFlags_8008D678 & 0x8000))
    {
        for (i = 0; i < 8; i++)
        {
            if (((CamState_80019CC4*)cameraState_8008D4F0)->points[i].active == 0)
            {
                break;
            }
            if (DistanceSquaredXZ_8003B860(((CamState_80019CC4*)cameraState_8008D4F0)->points[i].pos, pos) < best)
            {
                best = DistanceSquaredXZ_8003B860(((CamState_80019CC4*)cameraState_8008D4F0)->points[i].pos, pos);
                found = i;
            }
        }
    }
    return found;
}
#endif
INCLUDE_ASM(sub_80019CC4);
INCLUDE_ASM(sub_80019D84);
extern short dword_80087114[];
extern short dword_80087134[];
extern char cameraState_8008D4F0[];
// Matched
void sub_8001A38C(void)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    unsigned short* g;
    p[0] = 0;
    p[1] = 0;
    g = (unsigned short*)cameraState_8008D4F0;
    dword_80087114[6] = -g[0x34 / 2];
    dword_80087114[7] = -g[0x36 / 2];
    dword_80087114[8] = -g[0x38 / 2];
    dword_80087134[2] = (short)g[0x3C / 2] / 4;
    dword_80087134[5] = (short)g[0x3E / 2] / 4;
    dword_80087134[8] = (short)g[0x40 / 2] / 4;
}
extern unsigned char byte_8008D460[3];
typedef struct
{
    unsigned short flags; // 0x10: flash, 1: fade in, 2: fade out, 4: darken, 8: brighten, 0x20: front OT
    short count;
    short pad_4;
    unsigned short duration;
} Fade_8001A41C;
typedef struct
{
    char pad_0[0x30];
    unsigned char rgb[3];
} CamColor_8001A41C;
// Matched
void sub_8001A41C(int** p, unsigned short* q)
{
    Fade_8001A41C* f = (Fade_8001A41C*)q;
    unsigned long* ot;
    POLY_F4 poly;
    DR_TPAGE tp;
    int v;
    SVECTOR* sv;
    unsigned char* c;
    unsigned char b;
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
        b = f->count * 255 / 8;
        SetPolyF4(&poly);
        poly.r0 = b;
        poly.g0 = b;
        poly.b0 = b;
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
        dword_8008D40C += 0x1000 / f->duration;
        if (dword_8008D40C >= 0x1000)
        {
            dword_8008D40C = 0x1000;
            unknownFlags_8008D678 &= ~0x400;
            f->flags &= ~1;
        }
    }
    else if (f->flags & 2)
    {
        dword_8008D40C -= 0x1000 / f->duration;
        if (dword_8008D40C < 0)
        {
            f->flags &= ~2;
            dword_8008D40C = 0;
        }
    }
    else if (f->flags & 4)
    {
        v = f->count << 8;
        v -= f->count;
        v /= f->duration;
        SetPolyF4(&poly);
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.field_C_w;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.field_E_h;
        poly.x3 = display_8008B4D8.field_C_w;
        poly.y3 = display_8008B4D8.field_E_h;
        poly.r0 = v;
        poly.g0 = v;
        poly.b0 = v;
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
        v = (f->duration - f->count) << 8;
        v -= f->duration - f->count;
        v /= f->duration;
        SetPolyF4(&poly);
        poly.x0 = 0;
        poly.y0 = 0;
        poly.x1 = display_8008B4D8.field_C_w;
        poly.y1 = 0;
        poly.x2 = 0;
        poly.y2 = display_8008B4D8.field_E_h;
        poly.x3 = display_8008B4D8.field_C_w;
        poly.y3 = display_8008B4D8.field_E_h;
        poly.r0 = v;
        poly.g0 = v;
        poly.b0 = v;
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
    sv = (SVECTOR*)(cameraState_8008D4F0 + 0x34);
    VectorNormalSS(sv, sv);
    c = (unsigned char*)cameraState_8008D4F0;
    dword_80087114[0] = *(short*)(c + 0x34);
    dword_80087114[1] = *(short*)(c + 0x36);
    dword_80087114[2] = *(short*)(c + 0x38);
    if (unknownFlags_8008D678 & 0x400)
    {
        dword_80087134[0] = *(short*)(c + 0x3C) * dword_8008D40C >> 12;
        dword_80087134[3] = *(short*)(c + 0x3E) * dword_8008D40C >> 12;
        dword_80087134[6] = *(short*)(c + 0x40) * dword_8008D40C >> 12;
    }
    else
    {
        dword_80087134[0] = *(short*)(c + 0x3C);
        dword_80087134[3] = *(short*)(c + 0x3E);
        dword_80087134[6] = *(short*)(c + 0x40);
    }
    dword_80087114[3] = 0;
    dword_80087114[4] = 0;
    dword_80087114[5] = 0;
    dword_80087114[6] = -dword_80087114[0];
    dword_80087114[7] = -dword_80087114[1];
    dword_80087114[8] = -dword_80087114[2];
    dword_80087134[1] = 0;
    dword_80087134[4] = 0;
    dword_80087134[7] = 0;
    dword_80087134[2] = dword_80087134[0] / 4;
    dword_80087134[5] = dword_80087134[3] / 4;
    dword_80087134[8] = dword_80087134[6] / 4;
    if (unknownFlags_8008D678 & 0x400)
    {
        byte_8008D460[0] = ((CamColor_8001A41C*)cameraState_8008D4F0)->rgb[0] * dword_8008D40C >> 12;
        byte_8008D460[1] = ((CamColor_8001A41C*)cameraState_8008D4F0)->rgb[1] * dword_8008D40C >> 12;
        byte_8008D460[2] = ((CamColor_8001A41C*)cameraState_8008D4F0)->rgb[2] * dword_8008D40C >> 12;
    }
    else
    {
        byte_8008D460[0] = ((CamColor_8001A41C*)cameraState_8008D4F0)->rgb[0];
        byte_8008D460[1] = ((CamColor_8001A41C*)cameraState_8008D4F0)->rgb[1];
        byte_8008D460[2] = ((CamColor_8001A41C*)cameraState_8008D4F0)->rgb[2];
    }
}
// Matched
void sub_8001A9A4(void)
{
    unsigned short* p;
    unsigned short v;
    dword_8008D40C = 0x1000;
    p = (unsigned short*)dword_8008D628[9];
    v = p[0];
    unknownFlags_8008D678 &= ~0x400;
    p[1] = 0;
    p[0] = v & 0xFFF0;
}
// Matched
void sub_8001A9E4(void)
{
    unknownFlags_8008D678 |= 0x400;
    dword_8008D40C = 0;
}
// Matched
void sub_8001AA04(short a0)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    int** q;
    p[3] = a0;
    q = cameraTask_8008D4A0 + 4;
    p[1] = 0;
    p[0] |= 1;
    sub_8001A41C(q, p);
}
// Matched
void sub_8001AA50(short a0)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    int** q;
    unknownFlags_8008D678 |= 0x400;
    p[3] = a0;
    q = cameraTask_8008D4A0 + 4;
    p[1] = 0;
    p[0] |= 2;
    sub_8001A41C(q, p);
}
// Matched
void sub_8001AAA8(short a0)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    int** q;
    p[3] = a0;
    q = cameraTask_8008D4A0 + 4;
    p[1] = 0;
    p[0] |= 4;
    sub_8001A41C(q, p);
}
// Matched
void sub_8001AAF4(void)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    p[0] &= ~4;
}
// Matched
void sub_8001AB1C(short a0)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    int** q;
    p[3] = a0;
    q = cameraTask_8008D4A0 + 4;
    p[1] = 0;
    p[0] |= 8;
    sub_8001A41C(q, p);
}
// Matched
void sub_8001AB68(void)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    p[1] = 8;
    p[0] |= 0x10;
}
// Matched
int sub_8001AB94(void)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    unsigned short v = p[0];
    if (v & 0x1B)
    {
        return 0;
    }
    if (v & 4)
    {
        return ((short*)p)[1] == p[3];
    }
    return 1;
}
// Matched
void sub_8001ABEC(int on)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    if (on)
    {
        p[0] |= 0x20;
    }
    else
    {
        p[0] &= ~0x20;
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
int sub_8001AC8C(int idx)
{
    if (idx < 0x1E)
    {
        return magicData_8007C438[idx].field_6;
    }
    return 0x1A;
}
// Matched
int sub_8001ACC0(int idx)
{
    return magicData_8007C438[idx].field_5;
}
// Matched
int sub_8001ACE4(int idx)
{
    unsigned int v = magicData_8007C438[idx].field_0;
    int r = (v >> 5) & 2;
    if (v & 0x80)
    {
        r |= 4;
    }
    if (v & 4)
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
        return magicData_8007C438[idx].field_8;
    }
    return 0xB;
}
// Matched
struct_12* sub_8001AD64(unsigned int idx)
{
    if (idx < 0x1E)
    {
        return &dword_8007C5A0[idx];
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
int CountMagicBits_8001AE54(unsigned int* a0)
{
    int i = 0;
    int n = i;
    for (; i < 0x1E; i++)
    {
        if (TestMagicBit_8001AE2C(a0, i))
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
int sub_8001AF3C(int idx)
{
    if (idx < 0x1E)
    {
        return dword_8007C708[idx];
    }
    return 0;
}
extern void* CreateEventList_800435B4(void* list);
extern void RunEventList_80043898(void* n);
extern void RunEventListFreeCallbacks_800438F8(void* n);
extern int FreeEventList_80043A5C(void* head);
extern DRAWENV drawEnv_8008D698[2];
extern DISPENV dispEnv_8008D750[2];
extern void InitMovie_8001B1B0(void);
extern void sub_8001B714(void);
extern void sub_8001B540(void);
extern void sub_8001BCE4(int buffer);
extern void Draw_8001B5EC(void);
extern void LoadDecodedImage_8001BEC8(void);
extern void InitPrimBuffers_8001BF90(void);
#if 0
// Not matched: the flags address (lui s0) is scheduled after the drawEnv pointers instead of before, and PutDrawEnv's
// address is added as e0 + i*0x5C instead of i*0x5C + e0
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
            sub_8001B714();
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
        sub_8001B540();
        if (dword_800918C4)
        {
            sub_8001BCE4(bDoubleBuffer_8008D428);
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
            dword_800918B8++;
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
    dword_8008B4F8 = 0x1000;
    drawEnvRed_8008D448[0] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[2] = 0;
    bDoubleBuffer_8008D428 = 0;
    dword_800918C4 = 0;
    unknownFlags_8008D678 &= ~0x200;
    sub_8001B230();
}
// Matched
void sub_8001B230(void)
{
    unknownFlags_8008D678 &= ~0x10;
    dword_800918BC = 0;
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
void sub_8001B540(void)
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
    SetGeomOffset(display_8008B4D8.field_C_w / 2 + dword_8008D474[0], display_8008B4D8.field_E_h / 2 + dword_8008D474[1]);
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
void sub_8001B714(void)
{
    if ((unsigned int)dword_800918BC < 2)
    {
        if (dword_800918BC == 0)
        {
            InitEnvironments_8001B7B4();
            WaitVSync_8001B6E8(0);
            ODEIsEvenAddressDrawn_800918C0 = GetODE() == 0;
        }
        dword_800918BC = dword_800918BC + 1;
        unknownFlags_8008D678 &= ~0x10;
    }
    else
    {
        unknownFlags_8008D678 &= ~0x40;
        unknownFlags_8008D678 |= 0x10;
    }
}
extern short dword_8007C728[][2];
extern DRAWENV drawEnv_8008D698[2];
extern DISPENV dispEnv_8008D750[2];
extern DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h);
extern DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h);
// Matched
void InitEnvironments_8001B7B4(void)
{
    int interlace;
    int off;
    display_8008B4D8.field_C_w = dword_8007C728[display_8008B4D8.field_0][0];
    display_8008B4D8.field_E_h = dword_8007C728[display_8008B4D8.field_0][1];
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
    dword_8008D474[0] = display_8008B4D8.field_8_x;
    dword_8008D474[1] = display_8008B4D8.field_A_y;
    SetGeomOffset(display_8008B4D8.field_C_w / 2 + dword_8008D474[0], display_8008B4D8.field_E_h / 2 + dword_8008D474[1]);
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
void sub_8001BCD8(int a0)
{
    dword_800918C4 = a0;
}
// Matched
void sub_8001BCE4(int buffer)
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
        primAllocPtr_800960A8[0] = dword_8008B550 + 0x801B9250;
        primBufferStart_800960A0[0] = dword_8008B550 + 0x801B9250;
        primAllocPtr_800960A8[1] = 0x801FC000 - ((unsigned int)(0x42DB0 - dword_8008B550) >> 1);
        primBufferStart_800960A0[1] = 0x801FC000 - ((unsigned int)(0x42DB0 - dword_8008B550) >> 1);
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
void StartScreenFlash_8001C02C(unsigned char* a0)
{
    struct_cb* r = AllocEventEntry_80043AF8(screenFlashTasks_8008D61C);
    if (r != 0)
    {
        unsigned char* p = (unsigned char*)r->field_14;
        r->flags_0 = (r->flags_0 | 1) & ~0x8000;
        *(int*)p = 0;
        p[4] = a0[0];
        p[5] = a0[1];
        p[6] = a0[2];
        r->fn_8 = (void (*)(struct_cb*, int*))ScreenFlashTask_8001C0B4;
    }
}
// Matched
void ScreenFlashTask_8001C0B4(struct_cb* p, int* q)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* s;
    unsigned short w;
    unsigned short h;
    unsigned char* c = (unsigned char*)q;
    q[0]++;
    if (q[0] >= 4)
    {
        p->flags_0 = (p->flags_0 & ~1) | 0x8000;
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
void SetFadeMode_8001C19C(a0)
unsigned int a0;
{
    switch (a0)
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
void sub_8001C224(void)
{
    unknownFlags_8008D678 |= 8;
    dword_800918B8 = 0;
}
// Matched
void sub_8001C244(void)
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
struct_8_id* sub_8001C314(struct_8_list* p, int id)
{
    struct_8_id* r = 0;
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (id == p->items[i].id)
        {
            r = &p->items[i];
        }
    }
    return r;
}
extern char dword_8007C750[];
// Matched
void PlayAnimFrameSfx_8001C364(char* a0, int idx, int a2)
{
    int* e = (int*)(*(int*)(a0 + 0x54) + idx * 28);
    int i;
    for (i = 0; i < e[3]; i++)
    {
        short* q = (short*)(i * 8 + e[4]);
        if (a2 == q[0] && q[1] == 0)
        {
            unsigned int n = (unsigned short)q[2];
            if (n < 0x6E)
            {
                char* t = (char*)(((short)n << 3) + (int)dword_8007C750);
                if (*(int*)t == 0)
                {
                    PlaySfx_80031494(*(short*)(t + 4));
                }
            }
        }
    }
}
extern short dword_8007CAC0[];
extern short dword_8007CACC[];
extern int PlayMusic_800300E0(int idx, int a1);
extern void PlaySeqSlot_80031160(unsigned int idx, short loops);
extern void sub_80025B5C(void* p, int idx, int sel);
typedef struct
{
    int kind; // 0: sfx, 1: music, 2: sequence, 3: fade out the system sequence
    short arg;
    short pad;
} SoundCue_8007C750;
// Matched
void sub_8001C440(char* a0, int idx, int key)
{
    int* e = (int*)(idx * 28 + *(int*)(a0 + 0x54));
    short* q = (short*)e[4];
    int n = e[3];
    int i;
    short arg;
    for (i = 0; i < n; i++, q += 4)
    {
        if (key != q[0])
        {
            continue;
        }
        switch (q[1])
        {
        case 0:
            if ((unsigned short)q[2] < 0x6E)
            {
                if (((SoundCue_8007C750*)dword_8007C750)[q[2]].kind == 0)
                {
                    PlaySfx_80031494(((SoundCue_8007C750*)dword_8007C750)[q[2]].arg);
                }
                if (((SoundCue_8007C750*)dword_8007C750)[q[2]].kind == 1)
                {
                    PlayMusic_800300E0(((SoundCue_8007C750*)dword_8007C750)[q[2]].arg, 1);
                }
                if (((SoundCue_8007C750*)dword_8007C750)[q[2]].kind == 2)
                {
                    arg = ((SoundCue_8007C750*)dword_8007C750)[q[2]].arg;
                    if (((SoundCue_8007C750*)dword_8007C750)[q[2]].arg == 3)
                    {
                        arg = saveData_8008B570.pad_7E2[0x80C - 0x7E2] >> 2;
                        if (arg > 4)
                        {
                            arg = 4;
                        }
                        arg = dword_8007CACC[arg];
                    }
                    else if (((SoundCue_8007C750*)dword_8007C750)[q[2]].arg == 2)
                    {
                        arg = saveData_8008B570.pad_7E2[0x80C - 0x7E2] >> 2;
                        if (arg > 4)
                        {
                            arg = 4;
                        }
                        arg = dword_8007CAC0[arg];
                    }
                    PlaySeqSlot_80031160(arg, 1);
                }
                if (((SoundCue_8007C750*)dword_8007C750)[q[2]].kind == 3)
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
            sub_80025B5C(a0, q[2], q[3]);
            break;
        }
    }
}
// Matched
void sub_8001C69C(void)
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
        sub_8001C810((short*)p++, *q++);
    }
}
// Matched
int TestAnyBits_8001C72C(unsigned int a0, unsigned int a1)
{
    return (a0 & (unsigned short)a1) != 0;
}
// Matched
int TestAllBits_8001C73C(unsigned int a0, unsigned int a1)
{
    a1 = (unsigned short)a1;
    if (a1 == 0)
    {
        return 0;
    }
    return (a0 & a1) == a1;
}
// Matched
int FindButtonConfig_8001C75C(unsigned int a0)
{
    unsigned short* p = buttonConfig_8008B578;
    int i = 0;
    unsigned int v = (unsigned short)a0;
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
void SwapButtonConfig_8001C79C(int a0, int a1)
{
    unsigned short* base = buttonConfig_8008B578;
    unsigned short* p = &base[a0];
    unsigned short r1 = sub_8001C818(p);
    unsigned short* q = &base[a1];
    unsigned short r2 = sub_8001C818(q);
    sub_8001C810((short*)p, r2);
    sub_8001C810((short*)q, r1);
}
// Matched
void sub_8001C810(short* p, unsigned short v)
{
    *p = v;
}
// Matched
unsigned short sub_8001C818(unsigned short* p)
{
    return *p;
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
unsigned int GetButtonConfig_8001C874(int a0)
{
    unsigned short* p = buttonConfig_8008B578;
    int i;
    for (i = 0; i < a0; i++)
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
INCLUDE_DATA(dword_80073234);
INCLUDE_DATA(dword_80073238);
INCLUDE_DATA(dword_8007324C);
INCLUDE_DATA(dword_8007327C);
INCLUDE_DATA(dword_800732A8);
INCLUDE_DATA(dword_800732D8);
INCLUDE_DATA(dword_800732F4);
INCLUDE_DATA(dword_80073310);
INCLUDE_DATA(dword_80073330);
INCLUDE_DATA(dword_80073350);
INCLUDE_DATA(dword_80073388);
INCLUDE_DATA(dword_800733B8);
INCLUDE_DATA(dword_800733D0);
INCLUDE_DATA(dword_800733F0);
INCLUDE_DATA(dword_80073410);
INCLUDE_DATA(dword_800734DC);
INCLUDE_DATA(dword_8007355C);
INCLUDE_DATA(dword_800735EC);
INCLUDE_DATA(dword_80073628);
INCLUDE_DATA(dword_80073648);
INCLUDE_DATA(dword_8007366C);
INCLUDE_DATA(dword_800736D0);
INCLUDE_DATA(dword_800736EC);
INCLUDE_DATA(dword_80073724);
INCLUDE_DATA(dword_80073740);
INCLUDE_DATA(dword_80073760);
INCLUDE_DATA(dword_8007377C);
INCLUDE_DATA(dword_800737A0);
INCLUDE_DATA(dword_800737B4);
INCLUDE_DATA(dword_800737C8);
INCLUDE_DATA(dword_80073910);
INCLUDE_DATA(dword_8007393C);
INCLUDE_DATA(dword_800739F4);
INCLUDE_DATA(dword_80073A14);
INCLUDE_DATA(dword_80073A28);
INCLUDE_DATA(dword_80073A48);
INCLUDE_DATA(dword_80073A84);
INCLUDE_DATA(dword_80073AAC);
INCLUDE_DATA(dword_80073ACC);
INCLUDE_DATA(dword_80073B00);
INCLUDE_DATA(dword_80073B20);
INCLUDE_DATA(dword_80073B44);
INCLUDE_DATA(dword_80073B68);
INCLUDE_DATA(dword_80073B78);
INCLUDE_DATA(dword_80073BB0);
INCLUDE_DATA(dword_80073BC4);
INCLUDE_DATA(dword_80073BDC);
INCLUDE_DATA(dword_80073C14);
INCLUDE_DATA(dword_80073C58);
INCLUDE_DATA(dword_80073C80);
INCLUDE_DATA(dword_80073CB0);
INCLUDE_DATA(dword_80073CCC);
INCLUDE_DATA(dword_80073CE0);
INCLUDE_DATA(dword_80073CF8);
INCLUDE_DATA(dword_80073D18);
INCLUDE_DATA(dword_80073D34);
INCLUDE_DATA(dword_80073D54);
INCLUDE_DATA(dword_80073DD0);
INCLUDE_DATA(dword_80073E18);
INCLUDE_DATA(dword_80073ED8);
INCLUDE_DATA(dword_80073F24);
INCLUDE_DATA(dword_80073F40);
INCLUDE_DATA(dword_80073F5C);
INCLUDE_DATA(dword_80073FA4);
INCLUDE_DATA(dword_80073FC0);
INCLUDE_DATA(dword_80073FF8);
INCLUDE_DATA(dword_8007400C);
INCLUDE_DATA(dword_8007403C);
INCLUDE_DATA(dword_8007408C);
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
int* sub_8001CD58(int idx)
{
    return &dword_8007CB4C[idx];
}
// Matched
int GetPersonIcon_8001CD6C(void)
{
    return 0x36;
}
// Matched
struct_12* GetAccessoryModifiers_8001CD74(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return &accessoryModifiers_8007D848[idx];
}
// Matched
struct_12* GetArmorModifiers_8001CDA0(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return &armorModifiers_8007D598[idx];
}
// Matched
unsigned char sub_8001CDCC(unsigned int idx)
{
    if (idx < 0x2B)
    {
        return byte_8007CC24[idx];
    }
    return 0x22;
}
// Matched
struct_12* GetItemData_8001CDF4(unsigned int idx)
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
int sub_8001CE8C(int idx)
{
    unsigned short v = itemFlags_8007CC50[idx];
    int r = (v >> 5) & 2;
    if (v & 0x80)
    {
        r |= 4;
    }
    if (v & 4)
    {
        r |= 1;
    }
    return r;
}
// Matched
unsigned char sub_8001CED0(int idx)
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
unsigned char sub_8001D060(int idx)
{
    return byte_8007D588[idx];
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
int GetEquipmentName_8001D128(int a0, unsigned int a1)
{
    int r = 0;
    switch (a1)
    {
    case 0:
        r = GetWeaponName_8001CF20(a0);
        break;
    case 1:
        r = GetArmorName_8001CFDC(a0);
        break;
    case 2:
        r = GetAccessoryName_8001D0A4(a0);
        break;
    }
    return r;
}
// Matched
short* GetEquipmentData_8001D190(a0, a1)
unsigned int a0;
unsigned int a1;
{
    short* r = 0;
    switch (a1)
    {
    case 0:
        r = (short*)GetWeaponData_8001CF84(a0);
        break;
    case 1:
        r = (short*)GetArmorData_8001D034(a0);
        break;
    case 2:
        r = (short*)GetAccessoryData_8001D0FC(a0);
        break;
    }
    return r;
}
// Matched
int GetEquipmentPrice_8001D1F8(int a0, unsigned int a1)
{
    int r = 0;
    switch (a1)
    {
    case 0:
        r = GetWeaponPrice_8001CF4C(a0);
        break;
    case 1:
        r = GetArmorPrice_8001D008(a0);
        break;
    case 2:
        r = GetAccessoryPrice_8001D0D0(a0);
        break;
    }
    return r;
}
// Matched
struct_12* sub_8001D260(void)
{
    unsigned int i = sub_800AD990(0);
    if (i < 0x17)
    {
        return &dword_8007D274[i];
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
    short* p = GetEquipmentData_8001D190();
    if (p != 0)
    {
        return equipmentIcons_8007D938[*p];
    }
    return 0x24;
}
// Matched
int GetKeyItemName_8001D318(unsigned int idx)
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
int sub_8001D36C(int v)
{
    return (unsigned int)(v - 0x19) < 0xD;
}
// Matched
void InitActors_8001D378(void)
{
    ResetModelLoader_800204D0();
    StopModelLoader_800205F0();
    ClearModelAnimRefs_800201A4();
    ListInit_8003FDB0(dword_80091990);
    StopAllEventEntries_80043B40(actorTasks_8008D43C);
}
// Matched
void FreeActors_8001D3C4(int a0)
{
    if (a0 != 0)
    {
        StopModelLoader_800205F0();
        FreeModelLoaderList_8002052C();
        ResetModelLoader_800204D0();
    }
    ListFreeAll_8003FEC8(dword_80091990);
    StopAllEventEntries_80043B40(actorTasks_8008D43C);
    ClearModelAnimRefs_800201A4();
}
// Matched
void UpdateActorCb_8001D41C(int a0, void* a1)
{
    sub_8001EA28(a1);
    sub_8001F354(a1);
    sub_8001F918(a1);
    sub_8001F9AC(a1);
}
// Matched
int* CreateActor_8001D45C(int a0)
{
    struct_cb* r = AllocEventEntry_80043AF8(actorTasks_8008D43C);
    int* p;
    if (r != 0)
    {
        p = r->field_14;
        r->fn_8 = (void (*)(struct_cb*, int*))UpdateActorCb_8001D41C;
        r->flags_0 = (r->flags_0 | 1) & ~0x8000;
        p[0] = (int)r;
        sub_8001E574(p, a0);
        return p;
    }
    return 0;
}
// Matched
int* sub_8001D4DC(char* o, int a1, int a2, int a3)
{
    struct
    {
        int field_0;
        int field_4;
        int pos[3];
        short rot[3];
        short pad_1A;
        int field_1C;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        int field_30;
        int field_34;
        char* field_38;
        int field_3C;
        int field_40;
        int field_44;
        int field_48;
        int field_4C;
    } s;
    int* r;
    s.field_48 = *(int*)(o + 0x15C);
    s.field_0 = -1;
    s.field_4 = a1;
    s.pos[0] = *(int*)(o + 0x38);
    s.pos[1] = *(int*)(o + 0x3C);
    s.pos[2] = *(int*)(o + 0x40);
    s.rot[0] = *(short*)(o + 0x5C);
    s.rot[1] = *(short*)(o + 0x5E);
    s.rot[2] = *(short*)(o + 0x60);
    s.field_1C = a2;
    s.field_20 = *(short*)(o + 0xC2);
    s.field_24 = *(int*)(o + 0x90);
    s.field_28 = *(short*)(o + 0x1E);
    s.field_2C = *(short*)(o + 0x24);
    s.field_30 = ((*(unsigned int*)(o + 4) >> 13) ^ 1) & 1;
    s.field_34 = *(int*)(o + 0x134);
    s.field_38 = o + 0x138;
    s.field_3C = *(int*)(o + 0x144);
    s.field_40 = *(int*)(o + 0x148);
    s.field_44 = *(int*)(o + 0x14C);
    s.field_4C = a3;
    r = CreateActor_8001D45C((int)&s);
    sub_8001D68C((struct_obj_A*)r, (*(unsigned int*)(o + 4) >> 18) & 1);
    return r;
}
// Matched
void DestroyActor_8001D600(char* a0)
{
    int* q = *(int**)a0;
    ReleaseModelAnimRef_80020278(*(short*)(a0 + 0x16), q[1]);
    sub_8001EA00(a0);
    q[0] = (q[0] & ~1) | 0x8000;
}
// Matched
void SetActorActive_8001D658(int** pp, int on)
{
    int* p = *pp;
    if (on)
    {
        *p &= 0xFFFF7FFF;
    }
    else
    {
        *p |= 0x8000;
    }
}
// Matched
void sub_8001D68C(struct_obj_A* p, int on)
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
void sub_8001D6BC(struct_obj_A* p, int on)
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
void sub_8001D6EC(struct_obj_A* p, int on)
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
void sub_8001D71C(struct_obj_A* p)
{
    p->flags_4 |= 8;
}
// Matched
void sub_8001D730(struct_obj_A* p, int on)
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
void sub_8001D760(char* o, int idx, int mode, int a3)
{
    int base;
    *(short*)(o + 0xC2) = idx;
    *(int*)(o + 0xA0) = *(int*)(o + 0x9C);
    *(int*)(o + 0x9C) = *(signed char*)(idx * 60 + *(int*)(o + 0x148));
    *(short*)(o + 0x18) = *(short*)(idx * 60 + *(int*)(o + 0x148) + 4);
    *(short*)(o + 0x1A) = *(short*)(idx * 60 + *(int*)(o + 0x148) + 6);
    *(int*)(o + 0x94) = *(int*)(o + 0x90);
    if (mode == -1)
    {
        *(int*)(o + 0x90) = *(short*)(idx * 60 + *(int*)(o + 0x148) + 2);
    }
    else if (mode == -2)
    {
        *(int*)(o + 0x90) = *(short*)(idx * 60 + *(int*)(o + 0x148) + 4);
    }
    else if (mode == -3)
    {
        int r = rand();
        char* e = (char*)(idx * 60 + *(int*)(o + 0x148));
        base = *(short*)(e + 2);
        *(int*)(o + 0x90) = base + r % (*(short*)(e + 4) - base);
    }
    else
    {
        *(int*)(o + 0x90) = mode % *(short*)(o + 0x1A);
    }
    *(short*)(o + 0x1C) = 0;
    *(int*)(o + 0xAC) = 0;
    *(int*)(o + 4) |= 8;
    if (a3)
    {
        *(int*)(o + 4) |= 0x10;
    }
}
// Matched
int sub_8001D8A8(short* p)
{
    return p[8] == 0;
}
// Matched
void sub_8001D8B4(char* a0, int a1)
{
    unsigned char* q = (unsigned char*)(a1 * 60 + *(int*)(a0 + 0x148));
    if (q[1] == 0)
    {
        if (RequestModelAnim_8002032C(*(short*)(a0 + 0x16), ((int*)*(int*)a0)[1], *(signed char*)q))
        {
            *(short*)(a0 + 0x14) = a1;
            *(short*)(a0 + 0x10) = 2;
        }
    }
}
// Matched
void sub_8001D92C(char* obj, int idx)
{
    signed char* e;
    int i;
    int key;
    int n;
    e = *(signed char**)(obj + 0x148);
    key = e[idx * 0x3C];
    n = ((int*)e)[-1];
    for (i = 0; i < n; i++)
    {
        if (key == e[0] && ((unsigned char*)e)[1] == 1)
        {
            return;
        }
        e += 0x3C;
    }
    ReleaseModelAnim_800203B0(*(short*)(obj + 0x16), (*(int**)obj)[1], key);
}
// Matched
void sub_8001D9B0(struct_obj_A* p)
{
    if (!(p->field_D4 & 2))
    {
        p->field_90 = p->field_1A;
        p->field_1C = 0;
        p->flags_4 |= 0x4000;
    }
}
// Matched
void sub_8001D9E4(struct_obj_A* p, int a1, int a2)
{
    p->field_20 = 0;
    p->field_22 = a1;
    p->flags_4 |= 0x20;
    p->flags_4 |= a2;
    p->flags_4 &= ~0x40;
}
// Matched
void sub_8001DA08(struct_obj_A* p, int a1, int a2)
{
    p->field_20 = 0;
    p->field_22 = a1;
    p->flags_4 |= 0x40;
    p->flags_4 |= a2;
    p->flags_4 &= ~0x20;
}
// Matched
void sub_8001DA2C(struct_obj_A* p)
{
    p->field_20 = 0;
    p->field_22 = 0;
    p->flags_4 &= 0xBFFFF81F;
}
// Matched
void sub_8001DA4C(char* p, int div, int from, int to)
{
    if (from < 0)
    {
        from = *(short*)(p + 0x26);
    }
    if (to < from)
    {
        *(short*)(p + 0x28) = (from - to) / div;
        *(short*)(p + 0x26) = from;
        *(short*)(p + 0x2A) = to;
        *(int*)(p + 4) |= 1;
    }
    else
    {
        *(short*)(p + 0x28) = (to - from) / div;
        *(short*)(p + 0x26) = from;
        *(short*)(p + 0x2A) = to;
        *(int*)(p + 4) |= 3;
    }
}
// Matched
void SetActorTint_8001DAAC(char* o, int a1)
{
    if (a1 != 0)
    {
        *(int*)(o + 4) |= 0x800;
        TintVramImage_800292D0(o + 0x150, o + 0x158, a1);
    }
    else
    {
        *(int*)(o + 4) &= ~0x800;
    }
}
// Matched
void sub_8001DB00(char* o, int* v, int a2)
{
    if (v != 0)
    {
        *(int*)(o + 0x70) = v[0];
        *(int*)(o + 0x74) = v[1];
        *(int*)(o + 0x78) = v[2];
        *(int*)(o + 0x7C) = a2;
        *(int*)(o + 4) |= 0x4000000;
    }
    else
    {
        *(int*)(o + 4) &= ~0x4000000;
    }
}
// Matched
void sub_8001DB58(struct_obj_A* p, int a1, int a2)
{
    if (a2)
    {
        p->field_8C = a1;
        p->flags_4 |= 0x20000000;
    }
    else
    {
        p->field_8C = 0x1000;
        p->flags_4 &= ~0x20000000;
    }
}
#if 0
// Not matched: a1/a2 swapped between the saved 0xC2 value and the 0xFFFF7FFF mask (o is a macro for ((char*)arg0) to keep the funcs.h prototype)
#define o ((char*)arg0)
void sub_8001DB98(void* arg0, void* arg1)
{
    unsigned char* s = arg1;
    short old = *(short*)(o + 0xC2);
    *(short*)(o + 0xC2) = -1;
    *(short*)(o + 0xC4) = 0;
    *(short*)(o + 0xC6) = 1;
    *(short*)(o + 0xC8) = 0;
    *(short*)(o + 0xCA) = 0;
    *(short*)(o + 0xCC) = -1;
    *(short*)(o + 0xCE) = -1;
    *(unsigned char**)(o + 0xD0) = s;
    *(int*)(o + 4) &= ~0x8000;
    *(int*)(o + 4) |= 0x4000;
    *(short*)(o + 0xC0) = old;
    while (s[0] != 0)
    {
        *(short*)(o + 0xC6) += s[1];
        s += s[1] * 4;
    }
}
#undef o
#endif
INCLUDE_ASM(sub_8001DB98);
// Matched
void sub_8001DC34(void* p, void* s)
{
    sub_8001DB98(p, s);
    sub_8001EA48(p);
}
// Matched
int sub_8001DC60(char* p, int a1, int a2, int a3)
{
    unsigned int dist;
    int x = *(int*)(p + 0x40);
    int y = *(int*)(p + 0x4C);
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
    if (IsWithinDistance_8003B740(p + 0x38, a1, &dist))
    {
        if (dist < d * d)
        {
            return 1;
        }
    }
    t = d + 0x32;
    if (dist < t * t)
    {
        if (IsActorNear_8001DFC8(p, a1, a3, 1))
        {
            return 1;
        }
    }
    TurnActorTowards_8001DDFC(p, a1, a2);
    return 0;
}
// Matched
int sub_8001DD44(char* o, int mode, int a, int b)
{
    int m;
    int r;
    m = a;
    if (a >= b)
    {
        m = b;
    }
    if (mode == 1)
    {
        *(int*)(o + 0x19C) = m;
    }
    else
    {
        *(int*)(o + 0x19C) = -m;
    }
    sub_8001D71C((struct_obj_A*)o);
    FirFilterStep_80014588(o + 0x1A4, o + 0x194, frameCount_8008D3FC);
    *(short*)(o + 0x5E) += *(short*)(o + 0x1A0);
    r = a - b;
    return r < 0 ? 0 : (a < r ? a : r);
}
// Matched
int TurnActorTowards_8001DDFC(char* o, VECTOR* target, int step)
{
    VECTOR d;
    int a;
    d.vx = target->vx - *(int*)(o + 0x38);
    d.vz = target->vz - *(int*)(o + 0x40);
    a = (ratan2_8003B548(d.vx, d.vz) - *(short*)(o + 0x5E)) & 0xFFF;
    *(int*)(o + 0x19C) = 0;
    if (a < step || a >= 0x1000 - step)
    {
        *(short*)(o + 0x5E) += a;
        return 1;
    }
    if (a < 0x800)
    {
        *(int*)(o + 0x19C) = step;
    }
    else
    {
        *(int*)(o + 0x19C) = -step;
    }
    FirFilterStep_80014588(o + 0x1A4, o + 0x194, frameCount_8008D3FC);
    *(short*)(o + 0x5E) += *(short*)(o + 0x1A0);
    return 0;
}
// Matched
int FindActorInFront_8001DECC(char* o, int range, int checkLevant)
{
    EventNode* n;
    EventEntry* e;
    int count;
    int i;
    int found = 0;
    range = range * range;
    if (checkLevant)
    {
        found = IsInFrontWithinRange_8001E0F4((VECTOR*)(o + 0x38), *(short*)(o + 0x5E), &levantPos_8008BD18, range);
    }
    if (found == 0)
    {
        n = (EventNode*)actorTasks_8008D43C;
        count = n->count;
        for (i = 0; i < count; i++)
        {
            e = &n->entry;
            if ((e->flags & 0x8001) == 1 && *(int*)o != *(int*)e->buffer)
            {
                found = IsInFrontWithinRange_8001E0F4((VECTOR*)(o + 0x38), *(short*)(o + 0x5E), (VECTOR*)((char*)e->buffer + 0x38), range);
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
int IsActorNear_8001DFC8(char* o, VECTOR* target, int range, int checkLevant)
{
    EventNode* n;
    EventEntry* e;
    char* b;
    int count;
    int i;
    unsigned int dist;
    if (checkLevant)
    {
        dist = 0xFFF;
        if (IsWithinDistance_8003B740((VECTOR*)(o + 0x38), &levantPos_8008BD18, &dist) != 0 && dist < range * range)
        {
            return 1;
        }
    }
    n = (EventNode*)actorTasks_8008D43C;
    count = n->count;
    for (i = 0; i < count; i++)
    {
        e = &n->entry;
        if ((e->flags & 0x8001) == 1 && *(int*)o != *(int*)(b = e->buffer))
        {
            dist = 0xFFF;
            if (IsWithinDistance_8003B740((VECTOR*)(o + 0x38), (VECTOR*)(b + 0x38), &dist) != 0 && dist < range * range)
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
int sub_8001E1C8(struct_obj_A* p)
{
    return (p->flags_4 & 0x280000) == 0;
}
// Matched
int sub_8001E1DC(struct_obj_F* p)
{
    if (p->field_130 >= 0)
    {
        if (IsEffectReady_80014954() == 0)
        {
            return 0;
        }
    }
    if (p->flags_4 & 0x80000)
    {
        if (p->field_C < 3)
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
int sub_8001E254(struct_obj_A* p, void* desc)
{
    p->flags_4 = (p->flags_4 & 0xFFFDFFFF) | 0x600000;
    return sub_8001E34C(p, desc);
}
// Matched
void sub_8001E28C(char* o)
{
    int s[0x4A];
    if (*(int*)(o + 0x130) >= 0)
    {
        s[0] = *(int*)(o + 0x130);
        s[1] = (int)(o + 0x108);
        s[2] = *(int*)(o + 0x14C);
        s[3] = (int)(o + 0x38);
        s[4] = *(int*)(o + 0x1C4);
        s[5] = *(int*)(o + 0x1C8);
        s[13] = *(int*)(o + 0x144);
        s[14] = (int)(o + 0x2C);
        sub_800182B8(s, *(int*)(o + 0xEC));
        sub_800184DC((int)s, LowestSetBit_80014358(*(int*)(o + 0xE8)));
        *(int*)(o + 0x130) = -1;
    }
    *(int*)(o + 4) |= 0x20000;
    if (*(int*)(o + 0x100) != 0)
    {
        sub_8001EFC4((struct_obj_F*)o);
    }
}
extern int dword_8007D95C[];
extern int dword_8007D980[];
extern int dword_8007D9A4[];
extern int dword_8007D9C0[];
// Matched
int sub_8001E34C(char* o, char* d)
{
    int r;
    int f;
    int g;
    *(int*)(o + 0xD4) = *(int*)(d + 0);
    *(short*)(o + 0xE0) = *(short*)(d + 0xC);
    *(int*)(o + 0xE8) = *(int*)(d + 0x14);
    *(int*)(o + 0xEC) = *(int*)(d + 0x18);
    *(short*)(o + 0xF4) = *(short*)(d + 0x20);
    *(short*)(o + 0xF6) = *(short*)(d + 0x22);
    *(short*)(o + 0xFC) = *(short*)(d + 0x28);
    *(short*)(o + 0xFE) = *(short*)(d + 0x2A);
    *(short*)(o + 0xE0) = *(short*)(d + 0xC);
    *(int*)(o + 0x100) = *(int*)(d + 0x2C);
    r = 0;
    if (*(void**)(d + 4))
    {
        sub_8001DC34(o, *(void**)(d + 4));
    }
    if (*(short*)(d + 0xE) >= 0)
    {
        r = sub_8001F268(o, (short*)(o + 0x108), *(int*)(o + 0xD0), *(short*)(d + 0xE));
    }
    f = *(int*)(d + 0x10);
    if (f >= 0)
    {
        *(int*)(o + 0x130) = f;
        RequestEffect_800148F4(f);
    }
    if (*(int**)(d + 8))
    {
        *(int**)(o + 0xDC) = *(int**)(d + 8);
        *(int*)(o + 0x70) = (*(int**)(d + 8))[0];
        *(int*)(o + 0x74) = (*(int**)(d + 8))[1];
        *(int*)(o + 0x78) = (*(int**)(d + 8))[2];
        f = *(short*)(d + 0xC);
        *(int*)(o + 4) |= 0x80000;
        *(int*)(o + 0x7C) = f;
        if (*(short*)(d + 0x24) >= 0)
        {
            *(int*)(o + 0xA4) = *(short*)(d + 0x24);
            sub_8001DC34(o, dword_8007D95C);
        }
        else
        {
            *(int*)(o + 0xA4) = *(short*)(d + 0x26);
            sub_8001DC34(o, dword_8007D980);
        }
    }
    if (*(int*)(d + 0x30))
    {
        *(int*)(o + 0x98) = 0;
        *(int*)(o + 4) |= 0x2000000;
        *(int*)(o + 0x160) = *(int*)(d + 0x30);
    }
    if (*(short*)(d + 0x2A) >= 0)
    {
        *(int*)(o + 0xA4) = *(short*)(d + 0x28);
        *(int*)(o + 0xA8) = *(short*)(d + 0xC);
        sub_8001DC34(o, dword_8007D9C0);
    }
    else if (*(short*)(d + 0x28) >= 0)
    {
        *(int*)(o + 0xA4) = *(short*)(d + 0x28);
        *(int*)(o + 0xA8) = *(short*)(d + 0xC);
        sub_8001DC34(o, dword_8007D9A4);
    }
    g = *(int*)(o + 4);
    if (*(int*)(d + 0x1C))
    {
        g |= 0x800000;
    }
    *(int*)(o + 4) = g;
    return r;
}
extern unsigned short word_8007DC8C[];
extern unsigned short word_8007DC94[];
extern int dword_800795A0[];
#if 0
// Not matched: the original keeps the 0x9C..0xA4 and 0x130/0x15C stores after the 0xA8..0xCE block, here they are scheduled right after the d[8] load
void sub_8001E574(char* o, int* d)
{
    struct_112* m;
    int v;
    int f;
    if (d[0] >= 0)
    {
        m = AcquireLoaderModel_80020734(d[0]);
    }
    else
    {
        m = (struct_112*)d[0x48 / 4];
    }
    v = AddModelAnimRef_800201EC((int)m);
    *(int*)(o + 4) = 0x40000;
    f = *(int*)(o + 4);
    if (d[0x30 / 4] != 1)
    {
        f |= 0x2000;
        *(int*)(o + 4) = f;
    }
    if (d[1] == 2)
    {
        f |= 0x1000;
        *(int*)(o + 4) = f;
    }
    *(int*)(o + 8) = 0;
    *(int*)(o + 0xC) = d[1];
    *(short*)(o + 0x10) = 0;
    *(short*)(o + 0x12) = -1;
    *(short*)(o + 0x14) = -1;
    *(short*)(o + 0x16) = v;
    *(short*)(o + 0x18) = 0;
    *(short*)(o + 0x1A) = 0;
    *(short*)(o + 0x1C) = 0;
    *(short*)(o + 0x1E) = *(short*)((char*)d + 0x28);
    *(short*)(o + 0x26) = 0x1000;
    *(short*)(o + 0x20) = 0;
    *(short*)(o + 0x22) = 0;
    *(short*)(o + 0x28) = 0;
    *(short*)(o + 0x2A) = 0x1000;
    *(short*)(o + 0x24) = *(short*)((char*)d + 0x2C);
    *(int*)(o + 0x44) = *(int*)(o + 0x50) = *(int*)(o + 0x38) = d[2];
    *(int*)(o + 0x48) = *(int*)(o + 0x54) = *(int*)(o + 0x3C) = d[3];
    *(int*)(o + 0x4C) = *(int*)(o + 0x58) = *(int*)(o + 0x40) = d[4];
    *(short*)(o + 0x5C) = *(short*)((char*)d + 0x14);
    *(short*)(o + 0x5E) = *(short*)((char*)d + 0x16);
    *(short*)(o + 0x60) = *(short*)((char*)d + 0x18);
    *(int*)(o + 0x64) = 0;
    *(int*)(o + 0x68) = 0;
    *(int*)(o + 0x6C) = 0;
    *(int*)(o + 0x80) = 0;
    *(int*)(o + 0x84) = 0;
    *(int*)(o + 0x88) = 0;
    *(int*)(o + 0x8C) = 0x1000;
    *(int*)(o + 0x90) = 0;
    *(int*)(o + 0x94) = 0;
    *(int*)(o + 0x98) = 0;
    f = d[8];
    *(int*)(o + 0xA8) = -1;
    *(int*)(o + 0xAC) = 0;
    *(int*)(o + 0xB0) = 0;
    *(int*)(o + 0xB4) = 0;
    *(int*)(o + 0xB8) = 0;
    *(short*)(o + 0xC4) = 0;
    *(short*)(o + 0xC6) = 0;
    *(short*)(o + 0xC8) = 0;
    *(short*)(o + 0xCA) = 0;
    *(short*)(o + 0xCC) = -1;
    *(short*)(o + 0xCE) = -1;
    *(int*)(o + 0x9C) = f;
    *(int*)(o + 0xA0) = f;
    *(int*)(o + 0xA4) = *(int*)(o + 0xA0);
    *(short*)(o + 0xC2) = *(short*)(o + 0xC0) = *(short*)(o + 0x9C);
    *(int*)(o + 0x130) = -1;
    *(struct_112**)(o + 0x15C) = m;
    *(short*)(o + 0x150) = word_8007DC8C[0];
    *(short*)(o + 0x152) = word_8007DC8C[1] + *(short*)(*(char**)(m->field_0 + 0xC) + m->field_30 * 16 + 0xE);
    *(short*)(o + 0x154) = word_8007DC8C[2];
    *(short*)(o + 0x156) = word_8007DC8C[3];
    *(short*)(o + 0x158) = word_8007DC94[0];
    *(short*)(o + 0x15A) = word_8007DC94[1] + *(short*)((char*)d + 0x1C);
    *(int*)(o + 0x160) = 0;
    sub_8001E7F0(o, d);
    FirFilterInit_8001450C((int*)(o + 0x1A4), (struct_16*)(o + 0x194), (int)dword_800795A0, 8);
    sub_8001D760(o, d[8], d[9], 0);
}
#endif
INCLUDE_ASM(sub_8001E574);
// Matched
void sub_8001E7F0(char* o, int* d)
{
    short* p;
    int n;
    int size;
    int i;
    char* mem;
    short* src;
    int sz0;
    int sz1;
    p = (short*)d[0x34 / 4];
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
    if (d[0x4C / 4])
    {
        size += n * 32;
    }
    mem = ListAlloc_8003FDC0(dword_80091990, size);
    *(char**)(o + 0x134) = mem;
    MemCopy_800403E8((unsigned int*)mem, (unsigned int*)d[0x34 / 4], sz0);
    *(int*)(o + 0x138) = ((int*)d[0x38 / 4])[0];
    *(int*)(o + 0x13C) = ((int*)d[0x38 / 4])[1];
    *(int*)(o + 0x140) = ((int*)d[0x38 / 4])[2];
    mem += sz0;
    {
        short def[4] = {0x1000, 0x1000, 0x1000, 0};
        *(char**)(o + 0x144) = mem;
        mem += sz1;
        *(int*)(o + 4) |= 0x8000000;
        for (i = 0; i < n; i++)
        {
            if (d[0x3C / 4])
            {
                src = (short*)(d[0x3C / 4] + i * 8);
            }
            else
            {
                src = def;
            }
            ((short*)(*(char**)(o + 0x144) + i * 8))[0] = src[0];
            ((short*)(*(char**)(o + 0x144) + i * 8))[1] = src[1];
            ((short*)(*(char**)(o + 0x144) + i * 8))[2] = src[2];
            ((short*)(*(char**)(o + 0x144) + i * 8))[3] = src[3];
        }
    }
    *(int*)(o + 0x148) = d[0x40 / 4];
    *(int*)(o + 0x14C) = d[0x44 / 4];
    *(char**)(o + 0x1C4) = mem;
    mem += n * 12;
    if (d[0x4C / 4])
    {
        *(char**)(o + 0x1C8) = mem;
        *(int*)(o + 4) |= 0x10000000;
    }
    else
    {
        *(char**)(o + 0x1C8) = 0;
    }
}
// Matched
void sub_8001EA00(char* p)
{
    int v = *(int*)(p + 0x134);
    ListFree_8003FE38(dword_80091990, (void*)v);
}
// Matched
void sub_8001EA28(void* arg0)
{
    sub_8001EA48(arg0);
}
