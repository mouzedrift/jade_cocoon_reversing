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

INCLUDE_DATA(dword_80073040);
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
INCLUDE_DATA(dword_800740B0);
INCLUDE_DATA(dword_800740B4);
INCLUDE_DATA(dword_80086540);
INCLUDE_DATA(dword_80086544);
INCLUDE_DATA(dword_80086548);
INCLUDE_DATA(dword_8008654C);
INCLUDE_DATA(dword_80086550);
INCLUDE_DATA(dword_80086554);
INCLUDE_DATA(dword_80086558);
INCLUDE_DATA(dword_8008655C);
INCLUDE_DATA(dword_80086560);
INCLUDE_DATA(dword_80086564);
INCLUDE_DATA(dword_80086568);
INCLUDE_DATA(dword_8008656C);
/* char* off_80086570 = "\\DATA\\DATA.001;1"; (the string literal would be emitted into .rdata, not owned yet) */
INCLUDE_DATA(off_80086570);
INCLUDE_DATA(dword_80086574);
INCLUDE_DATA(dword_800865B8);
INCLUDE_DATA(dword_8008685C);
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
signed char sub_80019BF0(int idx)
{
    return dword_8007A4B4[idx].field_6;
}
// Matched
unsigned char sub_80019C0C(int idx)
{
    return dword_8007A4B4[idx].field_7;
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
INCLUDE_ASM(sub_80019CC4);
INCLUDE_ASM(sub_80019D84);
// Matched
extern short dword_80087114[];
extern short dword_80087134[];
extern char dword_8008D4F0[];
void sub_8001A38C(void)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    unsigned short* g;
    p[0] = 0;
    p[1] = 0;
    g = (unsigned short*)dword_8008D4F0;
    dword_80087114[6] = -g[0x34 / 2];
    dword_80087114[7] = -g[0x36 / 2];
    dword_80087114[8] = -g[0x38 / 2];
    dword_80087134[2] = (short)g[0x3C / 2] / 4;
    dword_80087134[5] = (short)g[0x3E / 2] / 4;
    dword_80087134[8] = (short)g[0x40 / 2] / 4;
}
INCLUDE_ASM(sub_8001A41C);
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
#if 0
// Not matched
void sub_8001AA04(short a0)
{
    unsigned short* p = (unsigned short*)dword_8008D628[9];
    int** q;
    p[3] = a0;
    q = dword_8008D4A0 + 4;
    p[1] = 0;
    p[0] |= 1;
    sub_8001A41C(q);
}
#endif
INCLUDE_ASM(sub_8001AA04);
INCLUDE_ASM(sub_8001AA50);
INCLUDE_ASM(sub_8001AAA8);
INCLUDE_ASM(sub_8001AB1C);
// Matched
int sub_8001AC2C(int idx)
{
    if (idx >= 0x1E)
    {
        return 0;
    }
    return off_8007C348[idx * 2];
}
// Matched
int sub_8001AC58(int idx)
{
    if (idx < 0x1E)
    {
        return dword_8007C438[idx].field_4;
    }
    return 0;
}
// Matched
int sub_8001AC8C(int idx)
{
    if (idx < 0x1E)
    {
        return dword_8007C438[idx].field_6;
    }
    return 0x1A;
}
// Matched
int sub_8001ACC0(int idx)
{
    return dword_8007C438[idx].field_5;
}
// Matched
int sub_8001ACE4(int idx)
{
    unsigned int v = dword_8007C438[idx].field_0;
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
int sub_8001AD30(int idx)
{
    if (idx < 0x1E)
    {
        return dword_8007C438[idx].field_8;
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
void sub_8001AD90(unsigned int* bits)
{
    int i;
    for (i = 0; i < 1; i++)
    {
        bits[i] = 0;
    }
}
// Matched
void sub_8001ADAC(unsigned int* bits, unsigned int idx)
{
    unsigned int* p = bits + (idx >> 5);
    *p |= 1 << (idx & 0x1F);
}
// Matched
void sub_8001ADD4(unsigned int* dst, unsigned int* src)
{
    int i;
    for (i = 0; i < 1; i++)
    {
        *dst++ |= *src++;
    }
}
// Matched
void sub_8001AE00(unsigned int* bits, unsigned int idx)
{
    unsigned int* p = bits + (idx >> 5);
    *p &= ~(1 << (idx & 0x1F));
}
// Matched
int sub_8001AE2C(unsigned int* bits, unsigned int idx)
{
    unsigned int* p = bits + (idx >> 5);
    return (*p & (1 << (idx & 0x1F))) != 0;
}
// Matched
int sub_8001AE54(unsigned int* a0)
{
    int i = 0;
    int n = i;
    for (; i < 0x1E; i++)
    {
        if (sub_8001AE2C(a0, i))
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
int sub_8001AEC0(unsigned int* bits, int n)
{
    int cnt = 0;
    int i;
    for (i = 0; i < 0x1E; i++)
    {
        if (sub_8001AE2C(bits, i))
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
unsigned char sub_8001AF3C(int idx)
{
    if (idx < 0x1E)
    {
        return dword_8007C708[idx];
    }
    return 0;
}
#if 0
void DrawIntroMovie_8001AF64(void* a0)
{
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
        int f = dword_800918B0;
        if (f & 2)
        {
            sub_8001BC00();
        }
        else if (f & 1)
        {
            sub_8001BB28();
        }
        InitSprt_8001B9A0(bDoubleBuffer_8008D428);
        unknownFlags_8008D678 &= ~0x80;
    }
}
INCLUDE_ASM(Draw_8001B5EC);
// Matched
int sub_8001B6E8()
{
    int snapshot = dword_8008B4B4;
    do
    {
    } while (dword_8008B4B4 <= snapshot);
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
            sub_8001B6E8(0);
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
INCLUDE_ASM(InitEnvironments_8001B7B4);
INCLUDE_ASM(InitSprt_8001B9A0);
// Matched
void sub_8001BB28(void)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* s;
    unsigned short w;
    unsigned short h;
    SetPolyF4(&poly);
    s = (unsigned short*)&stru_8008B4D8;
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
    sub_80040298(pOT_8008D78C, &poly, 6);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000240;
    sub_80040298(pOT_8008D78C, &dr, 2);
    dword_800918B4++;
    if ((unsigned int)dword_800918B4 > 0x20)
    {
        dword_800918B0 &= ~1;
    }
}
// Matched
void sub_8001BC00(void)
{
    POLY_F4 poly;
    DR_TPAGE dr;
    unsigned short* s;
    unsigned short w;
    unsigned short h;
    SetPolyF4(&poly);
    s = (unsigned short*)&stru_8008B4D8;
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
    sub_80040298(pOT_8008D78C, &poly, 6);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000220;
    sub_80040298(pOT_8008D78C, &dr, 2);
    dword_800918B4++;
    if ((unsigned int)dword_800918B4 > 0x20)
    {
        dword_800918B0 &= ~2;
    }
}
// Matched
void sub_8001BCD8(int a0)
{
    dword_800918C4 = a0;
}
INCLUDE_ASM(sub_8001BCE4);
// Matched
void sub_8001BEC8(void)
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
        sub_80036820(i);
    }
}
INCLUDE_ASM(sub_8001BF90);
// Matched
void sub_8001C02C(unsigned char* a0)
{
    struct_cb* r = sub_80043AF8(dword_8008D61C);
    if (r != 0)
    {
        unsigned char* p = (unsigned char*)r->field_14;
        r->flags_0 = (r->flags_0 | 1) & ~0x8000;
        *(int*)p = 0;
        p[4] = a0[0];
        p[5] = a0[1];
        p[6] = a0[2];
        r->fn_8 = (void (*)(struct_cb*, int*))sub_8001C0B4;
    }
}
// Matched
void sub_8001C0B4(struct_cb* p, int* q)
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
    s = (unsigned short*)&stru_8008B4D8;
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
    sub_80040298(pOT_8008D5F4, &poly, 6);
    setlen(&dr, 1);
    dr.code[0] = 0xE1000220;
    sub_80040298(pOT_8008D5F4, &dr, 2);
}
// Matched
void sub_8001C19C(a0)
unsigned int a0;
{
    switch (a0)
    {
    case 0:
        sub_8001C260();
        break;
    case 1:
        sub_8001C260();
        sub_8001C2CC();
        break;
    case 2:
        sub_8001C260();
        sub_8001C2E4();
        break;
    case 3:
        sub_8001C290();
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
void sub_8001C260(void)
{
    if (!(unknownFlags_8008D678 & 2))
    {
        unknownFlags_8008D678 |= 2;
    }
}
// Matched
void sub_8001C290(void)
{
    unknownFlags_8008D678 &= ~2;
    unknownFlags_8008D678 |= 0x10;
    unknownFlags_8008D678 |= 0x80;
}
// Matched
void sub_8001C2CC(void)
{
    dword_800918B0 = 1;
    dword_800918B4 = 0;
}
// Matched
void sub_8001C2E4(void)
{
    dword_800918B0 = 2;
    dword_800918B4 = 0;
}
// Matched
int sub_8001C2FC()
{
    return (dword_800918B0 & 3) == 0;
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
// Matched
extern char dword_8007C750[];
void sub_8001C364(char* a0, int idx, int a2)
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
INCLUDE_ASM(sub_8001C440);
// Matched
void sub_8001C6C8(void)
{
    unsigned short* p = dword_8008B578;
    int i = 0;
    unsigned short* q = dword_8007CAF4;
    for (; i < 10; i++)
    {
        sub_8001C810((short*)p++, *q++);
    }
}
// Matched
int sub_8001C72C(unsigned int a0, unsigned int a1)
{
    return (a0 & (unsigned short)a1) != 0;
}
// Matched
int sub_8001C73C(unsigned int a0, unsigned int a1)
{
    a1 = (unsigned short)a1;
    if (a1 == 0)
    {
        return 0;
    }
    return (a0 & a1) == a1;
}
// Matched
int sub_8001C75C(unsigned int a0)
{
    unsigned short* p = dword_8008B578;
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
void sub_8001C79C(int a0, int a1)
{
    unsigned short* base = dword_8008B578;
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
int sub_8001C824(void)
{
    int i;
    unsigned short v = sub_8001C874();
    for (i = 0; i < 14; i++)
    {
        if (dword_8007CAD8[i] == v)
        {
            break;
        }
    }
    return i;
}
// Matched
unsigned int sub_8001C874(int a0)
{
    unsigned short* p = dword_8008B578;
    int i;
    for (i = 0; i < a0; i++)
    {
        p++;
    }
    return *p;
}
// Matched
unsigned int sub_8001C8A0(short mask)
{
    unsigned int r = 1;
    int i = 0;
    unsigned short* p;
    int m = mask;
    p = dword_8007CAD8;
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
#if 0
void ProcessPad_8001C8E8(int a0)
{
}
#endif
INCLUDE_ASM(ProcessPad_8001C8E8);
INCLUDE_ASM(sub_8001CAF0);
INCLUDE_ASM(sub_8001CC04);
// Matched
int sub_8001CD34(void)
{
    return 0;
}
// Matched
int sub_8001CD3C(int idx)
{
    return off_8007CB20[idx];
}
// Matched
int* sub_8001CD58(int idx)
{
    return &dword_8007CB4C[idx];
}
// Matched
int sub_8001CD6C(void)
{
    return 0x36;
}
// Matched
struct_12* sub_8001CD74(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return &stru_8007D848[idx];
}
// Matched
struct_12* sub_8001CDA0(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return &stru_8007D598[idx];
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
struct_12* sub_8001CDF4(unsigned int idx)
{
    if (idx < 0x2B)
    {
        return &stru_8007CCA8[idx];
    }
    return 0;
}
// Matched
int sub_8001CE20(unsigned int idx)
{
    if (idx >= 0x2B)
    {
        return 0;
    }
    return dword_8007CB78[idx];
}
// Matched
int sub_8001CE4C(void)
{
    return 0;
}
// Matched
unsigned short sub_8001CE54(int idx)
{
    return word_8007CED8[idx];
}
// Matched
unsigned short sub_8001CE70(int idx)
{
    return aKkkiqqqqqssssZ[idx];
}
// Matched
int sub_8001CE8C(int idx)
{
    unsigned short v = aKkkiqqqqqssssZ[idx];
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
    return *(unsigned char*)&aKkkiqqqqqssssZ[idx];
}
// Matched
int sub_8001CEEC(void)
{
    return 1;
}
// Matched
int* sub_8001CEF4(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return &stru_8007D04C[idx].field_4;
}
// Matched
int sub_8001CF20(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return dword_8007CFF0[idx];
}
// Matched
int sub_8001CF4C(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return dword_8007D388[idx] * 10;
}
// Matched
struct_24* sub_8001CF84(unsigned int idx)
{
    if (idx >= 0x17)
    {
        return 0;
    }
    return &stru_8007D04C[idx];
}
// Matched
int* sub_8001CFB0(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return &stru_8007D420[idx].field_4;
}
// Matched
int sub_8001CFDC(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return dword_8007D3E4[idx];
}
// Matched
int sub_8001D008(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return word_8007D64C[idx];
}
// Matched
struct_24* sub_8001D034(unsigned int idx)
{
    if (idx >= 0xF)
    {
        return 0;
    }
    return &stru_8007D420[idx];
}
// Matched
unsigned char sub_8001D060(int idx)
{
    return byte_8007D588[idx];
}
// Matched
int* sub_8001D078(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return &stru_8007D6B0[idx].field_4;
}
// Matched
int sub_8001D0A4(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return dword_8007D66C[idx];
}
// Matched
int sub_8001D0D0(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return word_8007D914[idx];
}
// Matched
struct_24* sub_8001D0FC(unsigned int idx)
{
    if (idx >= 0x11)
    {
        return 0;
    }
    return &stru_8007D6B0[idx];
}
// Matched
int sub_8001D128(int a0, unsigned int a1)
{
    int r = 0;
    switch (a1)
    {
    case 0:
        r = sub_8001CF20(a0);
        break;
    case 1:
        r = sub_8001CFDC(a0);
        break;
    case 2:
        r = sub_8001D0A4(a0);
        break;
    }
    return r;
}
// Matched
short* sub_8001D190(a0, a1)
unsigned int a0;
unsigned int a1;
{
    short* r = 0;
    switch (a1)
    {
    case 0:
        r = (short*)sub_8001CF84(a0);
        break;
    case 1:
        r = (short*)sub_8001D034(a0);
        break;
    case 2:
        r = (short*)sub_8001D0FC(a0);
        break;
    }
    return r;
}
// Matched
int sub_8001D1F8(int a0, unsigned int a1)
{
    int r = 0;
    switch (a1)
    {
    case 0:
        r = sub_8001CF4C(a0);
        break;
    case 1:
        r = sub_8001D008(a0);
        break;
    case 2:
        r = sub_8001D0D0(a0);
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
int sub_8001D2AC(int idx)
{
    if (idx < 0x2B)
    {
        return byte_8007CEAC[idx];
    }
    return 0xFF;
}
// Matched
int sub_8001D2D4(void)
{
    short* p = sub_8001D190();
    if (p != 0)
    {
        return dword_8007D938[*p];
    }
    return 0x24;
}
// Matched
int sub_8001D318(unsigned int idx)
{
    if (idx >= 0x26)
    {
        return 0;
    }
    return off_8007CF30[idx];
}
// Matched
int sub_8001D344(int idx)
{
    if (idx < 0x26)
    {
        return byte_8007CFC8[idx];
    }
    return 0x24;
}
// Matched
int sub_8001D36C(int v)
{
    return (unsigned int)(v - 0x19) < 0xD;
}
// Matched
void sub_8001D378(void)
{
    sub_800204D0();
    sub_800205F0();
    sub_800201A4();
    sub_8003FDB0(dword_80091990);
    sub_80043B40(dword_8008D43C);
}
// Matched
void sub_8001D3C4(int a0)
{
    if (a0 != 0)
    {
        sub_800205F0();
        sub_8002052C();
        sub_800204D0();
    }
    sub_8003FEC8(dword_80091990);
    sub_80043B40(dword_8008D43C);
    sub_800201A4();
}
// Matched
void sub_8001D41C(int a0, void* a1)
{
    sub_8001EA28(a1);
    sub_8001F354(a1);
    sub_8001F918(a1);
    sub_8001F9AC(a1);
}
// Matched
int* sub_8001D45C(int a0)
{
    struct_cb* r = sub_80043AF8(dword_8008D43C);
    int* p;
    if (r != 0)
    {
        p = r->field_14;
        r->fn_8 = (void (*)(struct_cb*, int*))sub_8001D41C;
        r->flags_0 = (r->flags_0 | 1) & ~0x8000;
        p[0] = (int)r;
        sub_8001E574(p, a0);
        return p;
    }
    return 0;
}
INCLUDE_ASM(sub_8001D4DC);
// Matched
void sub_8001D600(char* a0)
{
    int* q = *(int**)a0;
    sub_80020278(*(short*)(a0 + 0x16), q[1]);
    sub_8001EA00(a0);
    q[0] = (q[0] & ~1) | 0x8000;
}
// Matched
void sub_8001D658(int** pp, int on)
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
INCLUDE_ASM(sub_8001D760);
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
        if (sub_8002032C(*(short*)(a0 + 0x16), ((int*)*(int*)a0)[1], *(signed char*)q))
        {
            *(short*)(a0 + 0x14) = a1;
            *(short*)(a0 + 0x10) = 2;
        }
    }
}
INCLUDE_ASM(sub_8001D92C);
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
void sub_8001D9E4(struct_obj_A* p, short a1, int a2)
{
    p->field_20 = 0;
    p->field_22 = a1;
    p->flags_4 |= 0x20;
    p->flags_4 |= a2;
    p->flags_4 &= ~0x40;
}
// Matched
void sub_8001DA08(struct_obj_A* p, short a1, int a2)
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
INCLUDE_ASM(sub_8001DA4C);
INCLUDE_ASM(sub_8001DAAC);
INCLUDE_ASM(sub_8001DB00);
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
void sub_8001DB98(void* arg0)
{
}
#endif
INCLUDE_ASM(sub_8001DB98);
// Matched
void sub_8001DC34(void* p)
{
    sub_8001DB98(p);
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
    if (sub_8003B740(p + 0x38, a1, &dist))
    {
        if (dist < d * d)
        {
            return 1;
        }
    }
    t = d + 0x32;
    if (dist < t * t)
    {
        if (sub_8001DFC8(p, a1, a3, 1))
        {
            return 1;
        }
    }
    sub_8001DDFC(p, a1, a2);
    return 0;
}
INCLUDE_ASM(sub_8001DD44);
INCLUDE_ASM(sub_8001DDFC);
INCLUDE_ASM(sub_8001DECC);
INCLUDE_ASM(sub_8001DFC8);
INCLUDE_ASM(sub_8001E0F4);
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
        if (sub_80014954() == 0)
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
void sub_8001E254(struct_obj_A* p)
{
    p->flags_4 = (p->flags_4 & 0xFFFDFFFF) | 0x600000;
    sub_8001E34C(p);
}
INCLUDE_ASM(sub_8001E28C);
#if 0
void sub_8001E34C(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001E34C);
INCLUDE_ASM(sub_8001E574);
INCLUDE_ASM(sub_8001E7F0);
// Matched
void sub_8001EA00(char* p)
{
    int v = *(int*)(p + 0x134);
    sub_8003FE38(dword_80091990, (void*)v);
}
// Matched
void sub_8001EA28(void* arg0)
{
    sub_8001EA48(arg0);
}
#if 0
void sub_8001EA48(void* arg0)
{
}
#endif
INCLUDE_ASM(sub_8001EA48);
// Matched
void sub_8001EFC4(struct_obj_F* p)
{
    unsigned int f = p->flags_4;
    int n;
    if (f & 0x800000)
    {
        n = p->field_C;
        if (n < 0)
        {
            if (f & 0x200000)
            {
                sub_800A5BCC(n - 2);
            }
        }
        else if (n >= 3)
        {
            if (f & 0x200000)
            {
                sub_800A5BCC(n - 2);
            }
        }
    }
    p->flags_4 &= 0xFF17FFFF;
}
INCLUDE_ASM(sub_8001F03C);
INCLUDE_ASM(sub_8001F268);
#if 0
void sub_8001F354(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001F354);
// Matched
void sub_8001F918(void* a0)
{
    char* p = a0;
    switch (*(short*)(p + 0x10))
    {
    case 0:
        break;
    case 1:
        sub_8002032C(*(short*)(p + 0x16), ((int*)*(int*)p)[1], *(short*)(p + 0x12));
        *(unsigned short*)(p + 0x14) = *(unsigned short*)(p + 0x12);
        *(short*)(p + 0x12) = -1;
        *(short*)(p + 0x10) = 2;
        break;
    case 2:
        if (sub_80024DC4((int*)*(int*)(p + 0x15C)))
        {
            *(short*)(p + 0x10) = 0;
        }
        break;
    }
}
// Matched
void sub_8001F9AC(void* p)
{
    sub_8001F9F0(p);
    sub_8001FB00(p);
    sub_8001FD08(p);
    sub_8001FF48(p);
    sub_800200F8(p);
}
#if 0
void sub_8001F9F0(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001F9F0);
#if 0
void sub_8001FB00(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001FB00);
// Matched
int sub_8001FC90(char* a0)
{
    SVECTOR v;
    long sxy;
    long p;
    long flag;
    v.vx = *(unsigned short*)(a0 + 0x38);
    v.vy = *(unsigned short*)(a0 + 0x3C);
    v.vz = *(unsigned short*)(a0 + 0x40);
    v.vx -= dword_8008D600[0].field_0;
    v.vy -= dword_8008D600[1].field_0;
    v.vz -= dword_8008D600[2].field_0;
    RotTransPers(&v, &sxy, &p, &flag);
    return flag >= 0;
}
#if 0
void sub_8001FD08(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001FD08);
#if 0
void sub_8001FF48(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001FF48);
#if 0
void sub_800200F8(void* a0)
{
}
#endif
INCLUDE_ASM(sub_800200F8);
// Matched
void sub_800201A4(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        sub_800204AC(&dword_800919A0[i]);
    }
}
// Matched
int sub_800201EC(int a0)
{
    int i;
    struct_obj_C* p = dword_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (a0 == p->field_0)
        {
            p->field_4++;
            return i;
        }
    }
    p = dword_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (p->field_0 == 0)
        {
            p->field_0 = a0;
            p->field_4 = 1;
            return i;
        }
    }
    return -1;
}
INCLUDE_ASM(sub_80020278);
// Matched
int sub_8002032C(int a0, int a1, int a2)
{
    struct_obj_C* e = &dword_800919A0[a0];
    unsigned short* s = (unsigned short*)((char*)e + a2 * 2);
    int r = 0;
    if (s[4] == 0)
    {
        sub_80025440(e->field_0, a2, r);
        r = 1;
    }
    s[4] |= 1 << a1;
    return r;
}
INCLUDE_ASM(sub_800203B0);
INCLUDE_ASM(sub_80020410);
// Matched
void sub_800204AC(struct_obj_C* p)
{
    int i;
    for (i = 0x22; i >= 0; i--)
    {
        p->field_8[i] = 0;
    }
    p->field_0 = 0;
    p->field_4 = 0;
}
// Matched
void sub_800204D0(void)
{
    int* p = (int*)dword_8008B54C[9];
    int* q = p + 3;
    int i;
    p[0] = 0;
    p[1] = 1;
    p[2] = 0;
    for (i = 0; i < 4; i++)
    {
        q[0] = 0;
        q[1] = -1;
        q[2] = 0;
        q[3] = 0;
        q[4] = -1;
        q += 5;
    }
}
// Matched
void sub_8002052C(void)
{
    int* p = dword_8008B54C[0x24 / 4];
    if (p[2])
    {
        sub_80024BB0(p + 2);
    }
}
// Matched
void sub_8002056C(void)
{
    struct_cb* q = (struct_cb*)((char*)dword_8008B54C + 0x10);
    q->fn_8 = sub_800209AC;
    q->flags_0 = (q->flags_0 | 1) & ~0x8000;
    *q->field_14 = 0;
    q->fn_8(q, q->field_14);
}
// Matched
int sub_800205D0(void)
{
    return dword_8008B54C[0x24 / 4][1];
}
INCLUDE_ASM(sub_800205F0);
// Matched
void sub_80020734(int arg)
{
    sub_80024D70(dword_8008B54C[0x24 / 4][2], arg);
}
// Matched
void sub_80020768(int a0)
{
    int* base = (int*)dword_8008B54C[9];
    int* p = base + 4;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[0] >= 0 && p[3] >= 0)
        {
            if (a0 == sub_80024D70(base[2], p[0]))
            {
                sub_80024C48(a0);
                p[0] = -1;
                return;
            }
        }
        p += 5;
    }
}
// Matched
void sub_80020814(void)
{
    int* base = (int*)dword_8008B54C[9];
    int* p = base + 7;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[-3] >= 0 && p[0] >= 0)
        {
            sub_80025884(sub_80024D70(base[2], p[-3]));
        }
        p += 5;
    }
}
// Matched
void sub_80020898(void)
{
    int* base = (int*)dword_8008B54C[9];
    int* p = base + 7;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[-3] >= 0 && p[0] >= 0)
        {
            sub_80025780(sub_80024D70(base[2], p[-3]), p[0], 1);
        }
        p += 5;
    }
}
// Matched
int sub_80020924(void)
{
    int* base = (int*)dword_8008B54C[9];
    int* p = base + 3;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[1] >= 0)
        {
            if (sub_80024DC4(sub_80024D70(base[2], p[1])) == 0)
            {
                return 0;
            }
        }
        p += 5;
    }
    return 1;
}
INCLUDE_ASM(sub_800209AC);
INCLUDE_ASM(sub_80020A38);
// Matched
int sub_80020B70(int* a0)
{
    int* p = a0 + 3;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[0] != 0)
        {
            if (sub_80024DC4(sub_80024D70(a0[2], p[1])) == 0)
            {
                return 0;
            }
        }
        p += 5;
    }
    a0[1] = 1;
    return 1;
}
#if 0
int LoadOverlay_80020BF8(int mode, enum OverlayIds overlayIdx)
{
    return 0;
}
#endif
INCLUDE_ASM(LoadOverlay_80020BF8);
// Matched
void sub_80020CD8(int a0, int* p)
{
    if (p[0] != p[1])
    {
        p[1] = p[0];
        p[2] = LoadOverlay_80020BF8(2, p[0]);
    }
}
#if 0
// Not matched
int sub_80020D1C(int a0, int a1)
{
    int v = a1;
    int* p = dword_8008D4C0[9];
    if (p[0] == v)
    {
        return -1;
    }
    p[0] = v;
    p[1] = v;
    return LoadOverlay_80020BF8(a0, v);
}
#endif
INCLUDE_ASM(sub_80020D1C);
// Matched
void sub_80020D68(void)
{
    *dword_8008D4C0[0x24 / 4] = 0x1D;
}
// Matched
int sub_80020D84(void)
{
    int* p = dword_8008D4C0[9];
    int r;
    if (p[0] == 0x1D)
    {
        r = sub_8003BE30(p[2]) == 0;
    }
    else
    {
        sub_80020D68();
        r = 0;
    }
    return r;
}
INCLUDE_ASM(sub_80020DDC);
// Matched
int sub_80020EBC(int* p)
{
    return sub_8003BE30(*p) == 0;
}
// Matched
void sub_80020EE0(int* p)
{
    sub_8003FEC8(p + 1);
}
// Matched
int sub_80020F00(struct_list_14* p, int a, int b)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].field_0 == a && p->items[i].field_4 == b)
        {
            return p->items[i].field_8;
        }
    }
    return -1;
}
INCLUDE_ASM(sub_80020F5C);
INCLUDE_ASM(sub_80021298);
INCLUDE_ASM(sub_80021464);
INCLUDE_ASM(sub_800215E8);
// Matched
void sub_800216E8(int* a0, int a1, int a2)
{
    a0[0] = sub_8003FDC0(a2, (a1 + 1) * 4);
    a0[1] = sub_8003FDC0(a2, 0x2000);
}
// Matched
int sub_80021738(int* p)
{
    return p[1];
}
// Matched
void sub_80021744(int* p, int idx, int a2)
{
    *p = sub_8003FC8C(idx * 0x54, a2);
}
// Matched
void sub_80021784(int** a0, unsigned int n, int heap)
{
    char* p = (char*)*a0;
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        sub_800229B0((int*)p, heap);
        p += 0x54;
    }
    sub_8003FD18(*a0, heap);
    *a0 = 0;
}
// Matched
void sub_80021804(int* p, int heap)
{
    sub_800229B0(p, heap);
}
// Matched
void sub_80021824(int* a0, char* a1, int a2, int a3, int a4)
{
    unsigned int n = sub_80021738(a0);
    int r = (int)(a0 + 4);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        r = sub_80022458(a1, r, a3, a4);
        a1 += 0x54;
    }
}
INCLUDE_ASM(sub_800218A8);
// Matched
int sub_80021DE4(int* p)
{
    return p[2];
}
// Matched
void sub_80021DF0(int* p, int a1, int a2)
{
    p[0] = a1;
    p[1] = sub_8003FC8C(a1 * 16, a2);
}
// Matched
// p is volatile to keep the store before the load
void sub_80021E24(volatile int* p, int h)
{
    p[0] = 0;
    sub_8003FD18(p[1]);
}
// Matched
void sub_80021E4C(int* a0, int* a1, unsigned int n)
{
    unsigned short* src = (unsigned short*)((char*)a0 + a0[3]);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        unsigned short* dst = (unsigned short*)((char*)a1[1] + i * 16);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
        dst[6] = src[6];
        dst[7] = src[7];
        src += 8;
    }
}
// r2 is unused (the original frame has room for it)
// Matched
void sub_80021EDC(unsigned char* p, unsigned char* d)
{
    RECT r;
    RECT r2;
    r.x = p[4];
    r.y = p[5];
    r.w = p[0xE];
    r.h = p[0xF];
    if (p[8] < r.x)
    {
        r.x = p[8];
    }
    if (r.x > p[0xC])
    {
        r.x = p[0xC];
    }
    if (r.x > p[0xE])
    {
        r.x = p[0xE];
    }
    if (p[9] < r.y)
    {
        r.y = p[9];
    }
    if (r.y > p[0xD])
    {
        r.y = p[0xD];
    }
    if (r.y > p[0xF])
    {
        r.y = p[0xF];
    }
    if (r.w < p[0xC])
    {
        r.w = p[0xC];
    }
    if (r.w < p[8])
    {
        r.w = p[8];
    }
    if (r.w < p[4])
    {
        r.w = p[4];
    }
    if (r.h < p[0xD])
    {
        r.h = p[0xD];
    }
    if (r.h < p[9])
    {
        r.h = p[9];
    }
    if (r.h < p[5])
    {
        r.h = p[5];
    }
    d[3] = 9;
    d[7] = 0x2C;
    d[4] = p[0];
    d[5] = p[1];
    d[6] = p[2];
    d[0xC] = r.x;
    d[0xD] = r.y;
    d[0x14] = r.w;
    d[0x15] = r.y;
    d[0x1C] = r.x;
    d[0x1D] = r.h;
    d[0x24] = r.w;
    d[0x25] = r.h;
    *(short*)(d + 8) = 0;
    *(short*)(d + 0xA) = 0;
    *(short*)(d + 0x10) = r.w - r.x;
    *(short*)(d + 0x12) = 0;
    *(short*)(d + 0x18) = 0;
    *(short*)(d + 0x1A) = r.h - r.y;
    *(short*)(d + 0x20) = r.w - r.x;
    *(short*)(d + 0x22) = r.h - r.y;
    d[7] = p[3];
    *(unsigned short*)(d + 0x16) = *(unsigned short*)(p + 0xA);
    *(unsigned short*)(d + 0xE) = *(unsigned short*)(p + 6);
}
// Matched
void sub_800221DC(unsigned char* p, unsigned char* d, DR_TPAGE* tp)
{
    RECT r;
    r.x = p[4];
    r.y = p[5];
    r.w = p[0xE];
    r.h = p[0xF];
    if (p[8] < r.x)
    {
        r.x = p[8];
    }
    if (r.x > p[0xC])
    {
        r.x = p[0xC];
    }
    if (r.x > p[0xE])
    {
        r.x = p[0xE];
    }
    if (p[9] < r.y)
    {
        r.y = p[9];
    }
    if (r.y > p[0xD])
    {
        r.y = p[0xD];
    }
    if (r.y > p[0xF])
    {
        r.y = p[0xF];
    }
    if (r.w < p[0xC])
    {
        r.w = p[0xC];
    }
    if (r.w < p[8])
    {
        r.w = p[8];
    }
    if (r.w < p[4])
    {
        r.w = p[4];
    }
    if (r.h < p[0xD])
    {
        r.h = p[0xD];
    }
    if (r.h < p[9])
    {
        r.h = p[9];
    }
    if (r.h < p[5])
    {
        r.h = p[5];
    }
    d[3] = 4;
    d[7] = 0x64;
    d[4] = p[0];
    d[5] = p[1];
    d[6] = p[2];
    d[0xC] = r.x;
    d[0xD] = r.y;
    *(short*)(d + 8) = 0;
    *(short*)(d + 0xA) = 0;
    *(short*)(d + 0x10) = r.w - r.x;
    *(short*)(d + 0x12) = r.h - r.y;
    *(unsigned short*)(d + 0xE) = *(unsigned short*)(p + 6);
    SetDrawTPage(tp, 0, 1, *(unsigned short*)(p + 0xA));
}
typedef void (*fn_80022458_a)(unsigned char* p, int a3);
typedef int (*fn_80022458_b)(unsigned char* hdr, unsigned char* p, int a0, int k, int h);
extern fn_80022458_a dword_8007DB08[];
extern fn_80022458_b off_8007DAE0[];
typedef struct
{
    short n;
    short pad;
    int p;
} struct_22634;
void sub_80022B84(int* c, int* x, int* y);
int sub_80022634(struct_22634* out, int* c, int h);
int sub_8002300C(unsigned char* hdr, unsigned char* p, int* a, int k, int h);
int sub_8002320C(unsigned char* hdr, unsigned char* p, int* b, int k, int h);
void sub_80022CC4(int a0, int* a, int* b, int h);
// Matched
int sub_80022458(int a0, unsigned char* a1, int h, int a3)
{
    int cnt[10];
    int A[2];
    int B[2];
    unsigned int i;
    unsigned int n;
    unsigned char* hdr;
    unsigned char* p;
    unsigned int type;
    unsigned int j;
    int k;
    for (j = 0; j < 10; j++)
    {
        cnt[j] = 0;
    }
    hdr = a1;
    a1 += 0x28;
    n = sub_80022634((struct_22634*)a0, (int*)hdr, h);
    sub_800228F8(A, B, (char*)hdr, h);
    for (i = 0; i < n; i++)
    {
        p = a1;
        a1 += 4;
        type = *p;
        k = cnt[type];
        cnt[type] = k + 1;
        if (a3 != 0 && dword_8007DB08[type] != 0)
        {
            dword_8007DB08[type](a1, a3);
        }
        switch (type)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            a1 += off_8007DAE0[type](p, a1, a0, k, h);
            break;
        case 8:
            a1 += sub_8002300C(p, a1, A, k, h);
            break;
        case 9:
            a1 += sub_8002320C(p, a1, B, k, h);
            break;
        }
    }
    sub_80022CC4(a0, A, B, h);
    sub_800229E0(A, B, h);
    return (int)a1;
}
// Matched
int sub_80022634(struct_22634* out, int* c, int h)
{
    int x;
    int y;
    int size;
    int total;
    char* p;
    p = 0;
    sub_80022B84(c, &x, &y);
    size = c[0] * 0x24 + c[1] * 0x3C;
    total = c[0] + c[1];
    size += c[2] * 0x30;
    total += c[2];
    size += c[3] * 0x48;
    total += c[3];
    size += c[4] * 0x2C;
    total += c[4];
    size += c[5] * 0x50;
    total += c[5];
    size += c[6] * 0x38;
    total += c[6];
    size += c[7] * 0x5C;
    total += c[7];
    size += x * 0x14;
    total += c[8];
    size += y * 0x14;
    total += c[9];
    if (size != 0)
    {
        p = (char*)sub_8003FC8C(size, h);
    }
    out[0].n = c[0];
    out[0].p = (int)p;
    p += c[0] * 0x24;
    out[1].n = c[1];
    out[1].p = (int)p;
    p += c[1] * 0x3C;
    out[2].n = c[2];
    out[2].p = (int)p;
    p += c[2] * 0x30;
    out[3].n = c[3];
    out[3].p = (int)p;
    p += c[3] * 0x48;
    out[4].n = c[4];
    out[4].p = (int)p;
    p += c[4] * 0x2C;
    out[5].n = c[5];
    out[5].p = (int)p;
    p += c[5] * 0x50;
    out[6].n = c[6];
    out[6].p = (int)p;
    p += c[6] * 0x38;
    out[7].n = c[7];
    out[7].p = (int)p;
    p += c[7] * 0x5C;
    ((int*)out)[0x40 / 4] = x;
    ((int*)out)[0x44 / 4] = (int)p;
    p += x * 0x14;
    ((int*)out)[0x48 / 4] = y;
    ((int*)out)[0x50 / 4] = (int)p;
    return total;
}
typedef struct
{
    unsigned short count;
    int ptr;
} struct_cnt_ptr;
// Matched
int sub_800228F8(struct_cnt_ptr* a0, struct_cnt_ptr* a1, int* a2, int heap)
{
    int n;
    int m;
    a0->count = a2[8];
    n = a2[8];
    if (n)
    {
        a0->ptr = sub_8003FC8C(n << 3, (struct Heap*)heap);
    }
    else
    {
        a0->ptr = 0;
    }
    a1->count = a2[9];
    m = a2[9];
    n += m;
    if (m)
    {
        a1->ptr = sub_8003FC8C(m * 12, (struct Heap*)heap);
    }
    else
    {
        a1->ptr = 0;
    }
    return n;
}
// Matched
void sub_800229B0(int* p, int heap)
{
    int a = p[1];
    if (a)
    {
        sub_8003FD18(a, heap);
    }
}
// Matched
void sub_800229E0(int* a0, int* a1, int h)
{
    int i;
    if (a0[1] != 0)
    {
        for (i = 0; i < *(short*)a0; i++)
        {
            if (((int*)a0[1])[i * 2 + 1] != 0)
            {
                sub_8003FD18(((int*)a0[1])[i * 2 + 1], h);
            }
        }
        sub_8003FD18(a0[1], h);
    }
    if (a1[1] != 0)
    {
        for (i = 0; i < *(short*)a1; i++)
        {
            if (((struct_12*)a1[1])[i].field_8 != 0)
            {
                sub_8003FD18(((struct_12*)a1[1])[i].field_8, h);
            }
        }
        sub_8003FD18(a1[1], h);
    }
}
// Matched
void sub_80022AE8(unsigned short* a0, unsigned short* a1, short* a2)
{
    int u = a2[0] / 64;
    int v = a2[1] / 256;
    int tp = v * 16 + u;
    unsigned short t = *a1;
    u = (t & 0x3F) * 16;
    v = (t >> 6) & 0x1FF;
    if (((*a0 >> 7) & 3) == 0)
    {
        u += a2[2];
        v += a2[3];
    }
    else
    {
        u += a2[4];
        v += a2[5];
    }
    *a0 += tp;
    *a1 = v * 64 + (u >> 4);
}
INCLUDE_ASM(sub_80022B84);
INCLUDE_ASM(sub_80022CC4);
#if 0
// Not matched: source pointer becomes a biased induction variable; s2/s3 swapped
int sub_8002300C(unsigned char* hdr, unsigned char* p, int* a, int k, int h)
{
    int r = 4;
    int i;
    unsigned char* q;
    ((struct_8_20b*)a[1])[k].count = *(int*)p;
    ((struct_8_20b*)a[1])[k].items = (struct_20_b*)sub_8003FC8C(*(int*)p * 20, h);
    q = p + r;
    for (i = 0; i < *(int*)p; i++)
    {
        ((struct_8_20b*)a[1])[k].items[i].f4 = *(unsigned short*)(q + 0);
        ((struct_8_20b*)a[1])[k].items[i].f6 = *(unsigned short*)(q + 2);
        ((struct_8_20b*)a[1])[k].items[i].f8 = *(unsigned short*)(q + 4);
        ((struct_8_20b*)a[1])[k].items[i].fA = 0;
        ((struct_8_20b*)a[1])[k].items[i].fC = *(unsigned short*)(q + 8);
        ((struct_8_20b*)a[1])[k].items[i].fE = *(unsigned short*)(q + 0xA);
        ((struct_8_20b*)a[1])[k].items[i].f10 = *(unsigned short*)(q + 0xC);
        ((struct_8_20b*)a[1])[k].items[i].f12 = 0;
        ((struct_8_20b*)a[1])[k].items[i].b0 = q[0x10];
        ((struct_8_20b*)a[1])[k].items[i].b1 = q[0x11];
        ((struct_8_20b*)a[1])[k].items[i].b2 = q[0x12];
        ((struct_8_20b*)a[1])[k].items[i].b3 = 0;
        r += 20;
        q += 20;
    }
    return r;
}
#endif
INCLUDE_ASM(sub_8002300C);
#if 0
// Not matched: same issues as sub_8002300C plus register assignment
int sub_8002320C(unsigned char* hdr, unsigned char* p, int* b, int k, int h)
{
    int r = 8;
    int i;
    unsigned char* q;
    ((struct_12_20b*)b[1])[k].count = *(int*)p;
    ((struct_12_20b*)b[1])[k].items = (struct_20_b*)sub_8003FC8C(*(int*)p * 20, h);
    ((struct_12_20b*)b[1])[k].f4 = *(unsigned short*)(p + 4);
    ((struct_12_20b*)b[1])[k].f6 = *(unsigned short*)(p + 6);
    q = p + r;
    for (i = 0; i < *(int*)p; i++)
    {
        ((struct_12_20b*)b[1])[k].items[i].f4 = *(unsigned short*)(q + 0);
        ((struct_12_20b*)b[1])[k].items[i].f6 = *(unsigned short*)(q + 2);
        ((struct_12_20b*)b[1])[k].items[i].f8 = *(unsigned short*)(q + 4);
        ((struct_12_20b*)b[1])[k].items[i].fA = 0;
        ((struct_12_20b*)b[1])[k].items[i].fC = *(unsigned short*)(q + 8);
        ((struct_12_20b*)b[1])[k].items[i].fE = *(unsigned short*)(q + 0xA);
        ((struct_12_20b*)b[1])[k].items[i].f10 = *(unsigned short*)(q + 0xC);
        ((struct_12_20b*)b[1])[k].items[i].f12 = 0;
        ((struct_12_20b*)b[1])[k].items[i].b0 = q[0x10];
        ((struct_12_20b*)b[1])[k].items[i].b1 = q[0x11];
        ((struct_12_20b*)b[1])[k].items[i].b2 = q[0x12];
        ((struct_12_20b*)b[1])[k].items[i].b3 = hdr[3];
        ((struct_12_20b*)b[1])[k].items[i].f12 = q[0xE] + (q[0xF] << 8);
        r += 20;
        q += 20;
    }
    return r;
}
#endif
INCLUDE_ASM(sub_8002320C);
// Matched
void sub_80023460(char* p, int arg1)
{
    sub_80022AE8(p + 4, p + 6, arg1);
}
// Matched
int sub_8002348C(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[1] + a3 * 0x24, 1);
    }
    sub_80023514(a2, a1, a0[3], a3);
    return 0x24;
}
// Matched
void sub_80023514(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x24;
    ((unsigned char*)(o + a0[1]))[0] = s[0];
    ((unsigned char*)(o + a0[1]))[1] = s[1];
    ((unsigned char*)(o + a0[1]))[2] = s[2];
    ((unsigned char*)(o + a0[1]))[3] = a2;
    *(unsigned short*)(o + a0[1] + 0xC) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 4) = *(unsigned short*)(s + 4);
    *(unsigned short*)(o + a0[1] + 6) = *(unsigned short*)(s + 6);
    *(unsigned short*)(o + a0[1] + 8) = *(unsigned short*)(s + 8);
}
// Matched
int sub_80023624(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[3] + a3 * 0x3C, 1);
    }
    sub_800236AC(a2 + 2, a1, a0[3], a3);
    return 0x3C;
}
// Matched
void sub_800236AC(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x3C;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)s;
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x1);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x34);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned short*)(s + 0x36);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0xC) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x2E);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x30);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
}
// Matched
int sub_800238AC(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[5] + a3 * 0x30, 1);
    }
    sub_80023934(a2 + 4, a1, a0[3], a3);
    return 0x24;
}
// Matched
void sub_80023934(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x30;
    *(unsigned short*)(o + a0[1] + 0xA) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0x6) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x12);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x13);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned char*)(o + a0[1] + 0x4) + (*(unsigned char*)(o + a0[1] + 0x5) << 8);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x1A);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x1B);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned char*)(o + a0[1] + 0x8) + (*(unsigned char*)(o + a0[1] + 0x9) << 8);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x22);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x23);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned char*)(o + a0[1] + 0xC) + (*(unsigned char*)(o + a0[1] + 0xD) << 8);
    *(unsigned char*)(o + a0[1]) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x1) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x2) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x4);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x6);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x8);
}
// Matched
void sub_80023B24(unsigned short* p, int arg1)
{
    sub_80022AE8(p, p + 1, arg1);
}
// Matched
int sub_80023B48(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[7] + a3 * 0x48, 1);
    }
    sub_80023BD0(a2 + 6, a1, a0[3], a3);
    return 0x40;
}
// Matched
void sub_80023BD0(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x48;
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x1E);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x1F);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned char*)(o + a0[1] + 0xC) + (*(unsigned char*)(o + a0[1] + 0xD) << 8);
    *(unsigned char*)(o + a0[1] + 0x10) = *(unsigned char*)(s + 0x2E);
    *(unsigned char*)(o + a0[1] + 0x11) = *(unsigned char*)(s + 0x2F);
    *(unsigned short*)(o + a0[1] + 0x3E) = *(unsigned char*)(o + a0[1] + 0x10) + (*(unsigned char*)(o + a0[1] + 0x11) << 8);
    *(unsigned char*)(o + a0[1] + 0x14) = *(unsigned char*)(s + 0x3E);
    *(unsigned char*)(o + a0[1] + 0x15) = *(unsigned char*)(s + 0x3F);
    *(unsigned short*)(o + a0[1] + 0x46) = *(unsigned char*)(o + a0[1] + 0x14) + (*(unsigned char*)(o + a0[1] + 0x15) << 8);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0xC);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0xD);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x32) = *(unsigned short*)(s + 0x1A);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x3A) = *(unsigned short*)(s + 0x2A);
    *(unsigned short*)(o + a0[1] + 0x3C) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x40) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0x42) = *(unsigned short*)(s + 0x3A);
    *(unsigned short*)(o + a0[1] + 0x44) = *(unsigned short*)(s + 0x3C);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0x12);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x22);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x30);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x32);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x34);
}
// Matched
void sub_80023E80(unsigned short* p, int arg1)
{
    sub_80022AE8(p, p + 1, arg1);
}
// Matched
int sub_80023EA4(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[9] + a3 * 0x2C, 1);
    }
    sub_80023F34(a2 + 8, a1, a0[3], a3);
    return 0x2C;
}
// Matched
void sub_80023F34(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x2C;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)s;
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x1);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0xC) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x4) = *(unsigned short*)(s + 0x4);
    *(unsigned short*)(o + a0[1] + 0x6) = *(unsigned short*)(s + 0x6);
    *(unsigned short*)(o + a0[1] + 0x8) = *(unsigned short*)(s + 0x8);
}
// Matched
int sub_8002407C(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[11] + a3 * 0x50, 1);
    }
    sub_80024104(a2 + 10, a1, a0[3], a3);
    return 0x50;
}
// Matched
void sub_80024104(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x50;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)s;
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x1);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0xC);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0xD);
    *(unsigned char*)(o + a0[1] + 0xE) = *(unsigned char*)(s + 0xE);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x32) = *(unsigned short*)(s + 0x1A);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x3A) = *(unsigned short*)(s + 0x2A);
    *(unsigned short*)(o + a0[1] + 0x3C) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x40) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0x42) = *(unsigned short*)(s + 0x3A);
    *(unsigned short*)(o + a0[1] + 0x44) = *(unsigned short*)(s + 0x3C);
    *(unsigned short*)(o + a0[1] + 0x48) = *(unsigned short*)(s + 0x48);
    *(unsigned short*)(o + a0[1] + 0x4A) = *(unsigned short*)(s + 0x4A);
    *(unsigned short*)(o + a0[1] + 0x4C) = *(unsigned short*)(s + 0x4C);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x12);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0x22);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x30);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x32);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x34);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x40);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x42);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x44);
}
// Matched
int sub_80024394(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[13] + a3 * 0x38, 1);
    }
    sub_8002441C(a2 + 12, a1, a0[3], a3);
    return 0x2C;
}
// Matched
void sub_8002441C(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x38;
    *(unsigned short*)(o + a0[1] + 0xA) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0x6) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x12);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x13);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned char*)(o + a0[1] + 0x4) + (*(unsigned char*)(o + a0[1] + 0x5) << 8);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x1A);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x1B);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned char*)(o + a0[1] + 0x8) + (*(unsigned char*)(o + a0[1] + 0x9) << 8);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x22);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x23);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned char*)(o + a0[1] + 0xC) + (*(unsigned char*)(o + a0[1] + 0xD) << 8);
    *(unsigned char*)(o + a0[1] + 0xE) = *(unsigned char*)(s + 0x2A);
    *(unsigned char*)(o + a0[1] + 0xF) = *(unsigned char*)(s + 0x2B);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned char*)(o + a0[1] + 0xE) + (*(unsigned char*)(o + a0[1] + 0xF) << 8);
    *(unsigned char*)(o + a0[1]) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x1) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x2) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x32) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x4);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x6);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x8);
}
// Matched
void sub_8002467C(unsigned short* p, int arg1)
{
    sub_80022AE8(p, p + 1, arg1);
}
// Matched
int sub_800246A0(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[15] + a3 * 0x5C, 1);
    }
    sub_80024730(a2 + 14, a1, a0[3], a3);
    return 0x54;
}
// Matched
void sub_80024730(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x5C;
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x10) = *(unsigned char*)(s + 0x22);
    *(unsigned char*)(o + a0[1] + 0x11) = *(unsigned char*)(s + 0x23);
    *(unsigned short*)(o + a0[1] + 0x42) = *(unsigned char*)(o + a0[1] + 0x10) + (*(unsigned char*)(o + a0[1] + 0x11) << 8);
    *(unsigned char*)(o + a0[1] + 0x14) = *(unsigned char*)(s + 0x32);
    *(unsigned char*)(o + a0[1] + 0x15) = *(unsigned char*)(s + 0x33);
    *(unsigned short*)(o + a0[1] + 0x4A) = *(unsigned char*)(o + a0[1] + 0x14) + (*(unsigned char*)(o + a0[1] + 0x15) << 8);
    *(unsigned char*)(o + a0[1] + 0x18) = *(unsigned char*)(s + 0x42);
    *(unsigned char*)(o + a0[1] + 0x19) = *(unsigned char*)(s + 0x43);
    *(unsigned short*)(o + a0[1] + 0x52) = *(unsigned char*)(o + a0[1] + 0x18) + (*(unsigned char*)(o + a0[1] + 0x19) << 8);
    *(unsigned char*)(o + a0[1] + 0x1A) = *(unsigned char*)(s + 0x52);
    *(unsigned char*)(o + a0[1] + 0x1B) = *(unsigned char*)(s + 0x53);
    *(unsigned short*)(o + a0[1] + 0x5A) = *(unsigned char*)(o + a0[1] + 0x1A) + (*(unsigned char*)(o + a0[1] + 0x1B) << 8);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0xC);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0xD);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xE);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x10);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x11);
    *(unsigned char*)(o + a0[1] + 0xE) = *(unsigned char*)(s + 0x12);
    *(unsigned short*)(o + a0[1] + 0x3C) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x3E) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x40) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x44) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x46) = *(unsigned short*)(s + 0x2E);
    *(unsigned short*)(o + a0[1] + 0x48) = *(unsigned short*)(s + 0x30);
    *(unsigned short*)(o + a0[1] + 0x4C) = *(unsigned short*)(s + 0x3C);
    *(unsigned short*)(o + a0[1] + 0x4E) = *(unsigned short*)(s + 0x3E);
    *(unsigned short*)(o + a0[1] + 0x50) = *(unsigned short*)(s + 0x40);
    *(unsigned short*)(o + a0[1] + 0x54) = *(unsigned short*)(s + 0x4C);
    *(unsigned short*)(o + a0[1] + 0x56) = *(unsigned short*)(s + 0x4E);
    *(unsigned short*)(o + a0[1] + 0x58) = *(unsigned short*)(s + 0x50);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x34);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned short*)(s + 0x36);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x44);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned short*)(s + 0x46);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x48);
}
// Matched
void sub_80024AB8(unsigned short* p, int arg1)
{
    sub_80022AE8(p, p + 1, arg1);
}
// Matched
void sub_80024ADC(struct_112_list** a0, void* a1, int heap)
{
    struct_112_list* l;
    int i;
    l = *a0 = (struct_112_list*)sub_8003FC8C(0x10, (struct Heap*)heap);
    l->count = sub_80026600(a1);
    l->field_4 = heap;
    l->items = (struct_112*)sub_8003FC8C(l->count * 0x70, (struct Heap*)heap);
    l->field_C = a1;
    for (i = 0; i < l->count; i++)
    {
        l->items[i].field_0 = (int)l;
        l->items[i].field_30 = i;
        sub_800266CC(&l->items[i]);
    }
}
// Matched
void sub_80024BB0(struct_112_list** a0)
{
    struct_112_list* l = *a0;
    int i;
    for (i = 0; i < l->count; i++)
    {
        sub_80024C48(&l->items[i]);
    }
    sub_8003FD18(l->items, l->field_4);
    sub_8003FD18(l, l->field_4);
    *a0 = 0;
}
// Matched
void sub_80024C48(struct_112* p)
{
    int h;
    sub_80025AB0(p);
    sub_80025C38(p, 1);
    h = ((int*)p->field_0)[1];
    if (p->field_44 != 0)
    {
        sub_8003FD18(p->field_44, h);
    }
    if (p->field_4C != 0)
    {
        sub_8003FD18(p->field_4C, h);
    }
    if (p->field_50 != 0)
    {
        sub_80021784((int**)&p->field_50, p->field_3C, h);
    }
    if (p->field_54 != 0)
    {
        sub_8002679C((struct_28**)&p->field_54, p->field_3E, h);
    }
    if (p->field_58 != 0)
    {
        sub_8003FD18(p->field_58, h);
    }
    if (p->field_60 != 0)
    {
        sub_80021E24(&p->field_5C, h);
    }
    if (p->field_64 != 0)
    {
        sub_8003FD18(p->field_64, h);
    }
    if (p->field_68 != 0)
    {
        sub_80021784((int**)&p->field_68, p->field_42, h);
    }
    if (p->field_6C != 0)
    {
        sub_8003FD18(p->field_6C, h);
    }
    sub_800266CC(p);
}
// Matched
struct_112* sub_80024D70(struct_112_list* p, unsigned int id)
{
    int i = sub_80026630(p, id);
    if (i >= 0)
    {
        struct_112* r = &p->items[i];
        r->field_3A++;
        return r;
    }
    return 0;
}
#if 0
// Not matched
int sub_80024DC4(int* p)
{
    int i;
    int r = 1;
    for (i = 0; i < p[1]; i++)
    {
        if (sub_8003BE30(p[2 + i]) != 0)
        {
            r = 0;
            break;
        }
    }
    if (r)
    {
        p[1] = 0;
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80024DC4);
// Matched
char* sub_80024E38(struct_obj_E* p)
{
    char* result = 0;
    int* hdr = p->field_4C;
    if (hdr && hdr[0])
    {
        result = (char*)hdr + hdr[0] + 4;
    }
    return result;
}
// Matched
char* sub_80024E64(struct_obj_E* p)
{
    char* result = 0;
    int* hdr = p->field_4C;
    if (hdr && hdr[1])
    {
        result = (char*)hdr + hdr[1];
    }
    return result;
}
// Matched
char* sub_80024E90(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)r;
    }
    return r;
}
// Matched
char* sub_80024EC8(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 4);
    }
    return r;
}
// Matched
char* sub_80024F00(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 8);
    }
    return r;
}
// Matched
char* sub_80024F38(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 0xC);
    }
    return r;
}
// Matched
char* sub_80024F70(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 0x10);
    }
    return r;
}
#if 0
// Not matched
char* sub_80024FA8(void* a0, int n)
{
    char* r = 0;
    int i = 0;
    char* hdr = *(char**)((char*)a0 + 0x4C);
    if (hdr)
    {
        int off = *(int*)(hdr + 8);
        if (off)
        {
            r = hdr + off + 8;
            for (; i < n; i++)
            {
                r += *(int*)(r + 0x14);
            }
        }
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80024FA8);
#if 0
// Not matched: induction variables for ids[] and the 0x58 offset created in swapped order
void sub_80024FFC(struct_112* p, int* ids)
{
    int n;
    for (n = 0; ids[n] >= 0; n++)
    {
    }
    p->field_40 = n;
    p->field_64 = sub_8003FC8C(n * sizeof(struct_58), ((int*)p->field_0)[1]);
    for (n--; n >= 0; n--)
    {
        ((struct_58*)p->field_64)[n].id = ids[n];
        ((struct_58*)p->field_64)[n].d = ((struct_54*)p->field_50)[ids[n]];
    }
}
#endif
INCLUDE_ASM(sub_80024FFC);
// Matched
void sub_8002512C(unsigned int* a0, char* a1, int a2)
{
    int i;
    for (i = 0; i < *(unsigned short*)(a1 + 0x40); i++)
    {
        int* e = (int*)(i * 0x58 + *(int*)(a1 + 0x64));
        if (a2 == e[0])
        {
            sub_800403E8(a0, (unsigned int*)(e + 1), 0x54);
            break;
        }
    }
}
// Matched
void sub_800251A0(void* dst, struct_obj_E* src, int a2, int idx)
{
    sub_800403E8((unsigned int*)dst, (unsigned int*)&src->field_50[idx], sizeof(struct_54));
}
// Matched
void nullsub_4(void)
{
}
// Matched
int sub_800251E4(int idx)
{
    return off_800824CC[idx];
}
// Matched
int sub_80025200(struct_112_list* a0, int id, int sel, int a3, int flag)
{
    int b[16];
    int c[8];
    int two = 1;
    int i;
    unsigned short* e;
    struct_112* it;
    int x;
    int u;
    int v;
    i = sub_80026630(a0, id);
    if (i >= 0)
    {
        return sub_80024DC4((int*)&a0->items[i]) == 0;
    }
    i = sub_8002667C(a0);
    if (i >= 0)
    {
        e = (unsigned short*)off_800824CC[id];
        it = &a0->items[i];
        x = ((int*)a0)[3] + i * 16;
        sub_80025ED0(b);
        if (sel != -1)
        {
            b[0] |= 3;
        }
        b[0] |= 0xC;
        v = 0;
        b[5] = (int)it;
        b[6] = x;
        b[1] = (int)e;
        b[2] = sel;
        b[3] = a3;
        if (sel != -1)
        {
            two = 0;
            v += e[2];
            v += e[4];
            u = e[1];
        }
        else
        {
            u = e[5];
        }
        v += e[6];
        v += e[8];
        c[1] = e[0];
        c[0] = 0x68;
        if (flag == 1)
        {
            c[0] = 0x6C;
        }
        else
        {
            c[0] = 0x69;
        }
        c[2] = u;
        c[3] = v;
        c[4] = 0;
        c[5] = (int)b;
        c[6] = 0x3C;
        c[7] = (int)sub_80025D7C;
        sub_80025D00((struct_list10*)it, c);
        if (two != 0)
        {
            sub_80025ED0(b);
            b[0] = 1;
            b[5] = (int)it;
            b[1] = (int)e;
            c[1] = e[0];
            c[0] = 0x68;
            if (flag == 1)
            {
                c[0] = 0x6C;
            }
            else
            {
                c[0] = 0x69;
            }
            c[2] = e[1];
            c[3] = e[2];
            c[5] = (int)b;
            c[6] = 0x3C;
            c[4] = 0;
            c[7] = (int)sub_80025D7C;
            sub_80025D00((struct_list10*)it, c);
        }
        it->id_38 = id;
        return 1;
    }
    return 2;
}
#if 0
// Not matched: table-entry address arithmetic: operand order and scheduling differ
int sub_80025440(struct_112* p, int idx, int flag)
{
    int b[16];
    int c[8];
    unsigned short* e;
    unsigned short* t;
    int u;
    int v;
    unsigned char* f = (unsigned char*)p->field_44 + idx;
    if (*f == 0)
    {
        e = (unsigned short*)off_800824CC[p->id_38];
        t = e + (e[9] + (idx * 2 + 10));
        u = t[0];
        v = t[1];
        *f = 1;
        sub_80025ED0(b);
        b[0] = 0x10;
        b[5] = (int)p;
        b[1] = (int)e;
        b[4] = idx;
        c[0] = 0x68;
        if (flag != 0)
        {
            c[0] = 0x6C;
        }
        else
        {
            c[0] = 0x69;
        }
        c[1] = e[0];
        c[2] = u;
        c[3] = v;
        c[4] = 0;
        c[5] = (int)b;
        c[6] = 0x3C;
        c[7] = (int)sub_80025D7C;
        sub_80025D00((struct_list10*)p, c);
        return 1;
    }
    return sub_80024DC4((int*)p) == 0;
}
#endif
INCLUDE_ASM(sub_80025440);
// Matched
void sub_8002556C(struct_112* p, int idx)
{
    if (((char*)p->field_44)[idx])
    {
        sub_800269C4(p->field_54, p->field_3E, idx, ((int*)p->field_0)[1]);
        ((char*)p->field_44)[idx] = 0;
    }
}
// Matched
int sub_800255D8(struct_112* p, int idx)
{
    return ((char*)p->field_44)[idx] != 0;
}
#if 0
// Not matched: a2 and a0[2] swap callee-saved registers (s2/s3)
int sub_800255F0(int* a0, int idx, int a2)
{
    int b[16];
    int c[8];
    int x = a0[2];
    int y = a0[3];
    unsigned short* e = (unsigned short*)off_800824CC[idx];
    sub_80025ED0(b);
    b[0] = 2;
    b[2] = a2;
    c[0] = 0x69;
    b[5] = x;
    b[6] = y;
    b[1] = (int)e;
    c[1] = e[0];
    c[2] = e[3];
    c[3] = e[4];
    c[5] = (int)b;
    c[6] = 0x3C;
    c[4] = 0;
    c[7] = (int)sub_80025D7C;
    sub_80025D00((struct_list10*)x, c);
    return 1;
}
#endif
INCLUDE_ASM(sub_800255F0);
#if 0
// Not matched: item pointer and table entry swap callee-saved registers (s0/s1)
int sub_800256B8(struct_112_list* a0, int id)
{
    int b[16];
    int c[8];
    struct_112* it = &a0->items[sub_80026630(a0, id)];
    unsigned short* e = (unsigned short*)off_800824CC[it->id_38];
    sub_80025ED0(b);
    b[0] = 8;
    b[3] = 3;
    c[0] = 0x69;
    b[5] = (int)it;
    b[1] = (int)e;
    c[1] = e[0];
    c[2] = e[7];
    c[3] = e[8];
    c[5] = (int)b;
    c[6] = 0x3C;
    c[4] = 0;
    c[7] = (int)sub_80025D7C;
    sub_80025D00((struct_list10*)it, c);
    return 1;
}
#endif
INCLUDE_ASM(sub_800256B8);
// Matched
int sub_80025780(struct_112* p, int idx, int flag)
{
    int b[16];
    int c[8];
    unsigned short* e;
    char* t;
    int u;
    int v;
    sub_80025884(p);
    e = (unsigned short*)off_800824CC[p->id_38];
    t = (char*)e + (e[9] * 6 + 0x14);
    u = ((unsigned short*)t)[idx * 2 + 1];
    v = ((unsigned short*)t)[idx * 2 + 2];
    sub_80025ED0(b);
    b[0] = 0x20;
    b[5] = (int)p;
    b[1] = (int)e;
    c[0] = 0x68;
    if (flag != 0)
    {
        c[0] = 0x6C;
    }
    else
    {
        c[0] = 0x69;
    }
    c[1] = e[0];
    c[2] = u;
    c[3] = v;
    c[4] = 0;
    c[5] = (int)b;
    c[6] = 0x3C;
    c[7] = (int)sub_80025D7C;
    sub_80025D00((struct_list10*)p, c);
    return 1;
}
// Matched
void sub_80025884(struct_112* p)
{
    int* list = (int*)p->field_58;
    if (list)
    {
        int heap = ((int*)p->field_0)[1];
        int n = list[0];
        int i;
        for (i = 0; i < n; i++)
        {
            int id = ((int*)p->field_58)[i + 1];
            if (id >= 0)
            {
                sub_8002556C(p, id);
            }
        }
        sub_8003FD18(p->field_58, heap);
        p->field_58 = 0;
    }
}
// Matched
int sub_80025924(int* p, int id)
{
    int* list = (int*)p[0x58 / 4];
    int i;
    int n;
    if (list != 0)
    {
        n = list[0];
        for (i = 0; i < n; i++)
        {
            if (id == list[i + 1])
            {
                return 1;
            }
        }
    }
    return 0;
}
// Matched
int sub_80025974(struct_112* p, int idx, int flag)
{
    int b[16];
    int c[8];
    unsigned short* e;
    char* t;
    int u;
    int v;
    int* g;
    sub_80025AB0(p);
    e = (unsigned short*)off_800824CC[p->id_38];
    t = (char*)e + (e[9] * 6 + 0x14);
    t += *(unsigned short*)t * 4 + 2;
    g = (int*)p->field_0;
    u = ((unsigned short*)t)[idx * 2 + 1];
    v = ((unsigned short*)t)[idx * 2 + 2];
    sub_80025ED0(b);
    b[0] = 0x40;
    b[5] = (int)p;
    b[6] = g[3] + p->field_30 * 16;
    b[2] = p->field_34;
    b[1] = (int)e;
    c[0] = 0x68;
    if (flag != 0)
    {
        c[0] = 0x6C;
    }
    else
    {
        c[0] = 0x69;
    }
    c[1] = e[0];
    c[2] = u;
    c[3] = v;
    c[4] = 0;
    c[5] = (int)b;
    c[6] = 0x3C;
    c[7] = (int)sub_80025D7C;
    sub_80025D00((struct_list10*)p, c);
    return 1;
}
// Matched
void sub_80025AB0(struct_112* p)
{
    struct Heap* h = (struct Heap*)((int*)p->field_0)[1];
    if (p->field_68)
    {
        sub_80021784((int**)&p->field_68, p->field_42, h);
        p->field_42 = 0;
        p->field_68 = 0;
    }
    if (p->field_6C)
    {
        sub_8003FD18(p->field_6C, h);
        p->field_43 = 0;
        p->field_6C = 0;
    }
}
// Matched
void sub_80025B20(void* dst, struct_obj_E* src, int idx)
{
    sub_800403E8((unsigned int*)dst, (unsigned int*)&src->field_68[idx], sizeof(struct_54));
}
// Matched
void sub_80025B5C(struct_obj_E* p, int idx, int sel)
{
    struct_54 tmp;
    if (idx == sel)
    {
        sub_8002512C((unsigned int*)&tmp, (char*)p, idx);
    }
    else if (sel < p->field_3C)
    {
        sub_800251A0(&tmp, p, idx, sel);
    }
    else
    {
        sub_80025B20(&tmp, p, sel - p->field_3C);
    }
    p->field_50[idx] = tmp;
}
// Matched
void sub_80025C38(struct_112* p, int flag)
{
    int i;
    for (i = 0; i < p->field_40; i++)
    {
        int* e = (int*)(i * 0x58 + p->field_64);
        sub_80025B5C(p, e[0], e[0]);
    }
    if (flag)
    {
        for (i = 0; i < p->field_43; i++)
        {
            short* s = (short*)(i * 4 + p->field_6C);
            sub_80025B5C(p, s[0], s[1]);
        }
    }
}
// Matched
int sub_80025D00(struct_list10* a0, int* a1)
{
    if (a0->count < 10)
    {
        a1[2] <<= 11;
        a1[3] <<= 11;
        a0->items[a0->count] = sub_8003BC84(a1);
        a0->count += 1;
        return 1;
    }
    return 0;
}
// Matched
void sub_80025D7C(int* a0, int b)
{
    if (a0[0] & 1)
    {
        a0[7] = b;
        b += *(unsigned short*)(a0[1] + 4) << 11;
    }
    if (a0[0] & 2)
    {
        a0[8] = b;
        b += *(unsigned short*)(a0[1] + 8) << 11;
    }
    if (a0[0] & 4)
    {
        a0[9] = b;
        b += *(unsigned short*)(a0[1] + 0xC) << 11;
    }
    if (a0[0] & 8)
    {
        a0[10] = b;
        b += *(unsigned short*)(a0[1] + 0x10) << 11;
    }
    if (a0[0] & 0x10)
    {
        a0[11] = b;
    }
    if (a0[0] & 0x20)
    {
        a0[12] = b;
    }
    if (a0[0] & 0x40)
    {
        a0[0] |= 0x80;
        a0[14] = b + ((int*)b)[1];
        a0[0] |= 0x40;
        a0[13] = b + ((int*)b)[2];
        a0[0] |= 2;
        a0[8] = b + ((int*)b)[3];
    }
    sub_80025F14(a0);
}
// Matched
void sub_80025ED0(int* p)
{
    p[2] = -1;
    p[0] = 0;
    p[1] = 0;
    p[3] = 2;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0;
    p[11] = 0;
    p[13] = 0;
    p[14] = 0;
}
// Matched
void sub_80025F14(int* a0)
{
    if (a0[0] & 1)
    {
        sub_80026014((char*)a0);
    }
    if (a0[0] & 2)
    {
        sub_8002607C(a0);
    }
    if (a0[0] & 4)
    {
        sub_800260FC(a0);
    }
    if (a0[0] & 8)
    {
        sub_800261C8(a0);
    }
    if (a0[0] & 0x10)
    {
        sub_800263CC(a0);
    }
    if (a0[0] & 0x20)
    {
        sub_80026410(a0);
    }
    if (a0[0] & 0x40)
    {
        sub_8002651C(a0);
    }
    if (a0[0] & 0x80)
    {
        sub_8002659C((char*)a0);
    }
}
typedef struct
{
    char pad_0[0x14];
    struct_112* owner_14;
    int* data_18;
    int* data_1C;
    char pad_20[0x14];
    int* list_34;
    unsigned char* data_38;
} struct_loader;
// Matched
void sub_80026014(char* a0)
{
    int* q = *(int**)(a0 + 0x1C);
    struct_112* p = *(struct_112**)(a0 + 0x14);
    int h = ((int*)p->field_0)[1];
    int n = q[0];
    int r;
    p->field_48 = n;
    r = sub_8003FC8C(n, h);
    p->field_4C = r;
    sub_800403E8((unsigned int*)r, (unsigned int*)(*(int*)(a0 + 0x1C) + 4), n);
}
// Matched
void sub_8002607C(int* a0)
{
    if (a0[2] != -1)
    {
        int* p = (int*)a0[5];
        sub_80028FDC(0, 0, 0, a0[8], GetTiyFileCount_80028E68((int*)a0[8]), a0[6] + 4, a0[2]);
        p[0x34 / 4] = a0[2];
    }
}
#if 0
// Not matched: load of a0[9] and a0[6] scheduled in swapped order
void sub_800260FC(int* a0)
{
    int q = a0[6];
    struct_112* p = (struct_112*)a0[5];
    int h = ((int*)p->field_0)[1];
    q += 4;
    p->field_3C = sub_80021738((int*)a0[9]);
    sub_80021744(&p->field_50, p->field_3C, h);
    sub_80021824((int*)a0[9], (char*)p->field_50, p->field_3C, h, q);
    if (sub_80021DE4((int*)a0[9]) != 0)
    {
        sub_80021DF0(&p->field_5C, sub_80021DE4((int*)a0[9]), h);
        sub_80021E4C((char*)a0[9], &p->field_5C, sub_80021DE4((int*)a0[9]));
    }
}
#endif
INCLUDE_ASM(sub_800260FC);
// Matched
void sub_800261C8(int* a0)
{
    struct_112* p = (struct_112*)a0[5];
    int h = ((int*)p->field_0)[1];
    int i;
    int j;
    int mode;
    p->field_3E = *(unsigned short*)(a0[1] + 0x12);
    if (p->field_54 == 0)
    {
        sub_80026730((struct_28**)&p->field_54, p->field_3E, h);
    }
    if (p->field_44 != 0)
    {
        sub_8003FD18(p->field_44, h);
    }
    p->field_44 = sub_8003FC8C(p->field_3E, h);
    for (i = 0; i < p->field_3E; i++)
    {
        mode = a0[3];
        if (mode == 0)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 1;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = 0;
            }
        }
        else if (mode == 1)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 1;
            }
            else if (i == 1)
            {
                ((unsigned char*)p->field_44)[1] = 1;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = 0;
            }
        }
        else if (mode == 3)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 0;
            }
            else if (i == 1)
            {
                ((unsigned char*)p->field_44)[1] = 0;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = *(unsigned char*)(a0[1] + 0x14 + i * 2);
            }
        }
        else
        {
            ((unsigned char*)p->field_44)[i] = *(unsigned char*)(a0[1] + 0x14 + i * 2);
        }
    }
    for (i = 0, j = 0; i < p->field_3E; i++)
    {
        if (((unsigned short*)(a0[1] + 0x14))[i] != 0)
        {
            if (((unsigned char*)p->field_44)[i] != 0)
            {
                sub_80026A8C((char*)p->field_54 + i * 28, a0[10] + ((int*)a0[10])[j + 1], h);
            }
            j++;
        }
    }
}
// Matched
void sub_800263CC(int* p)
{
    int* tmp27;
    int** q = (int**)p[5];
    tmp27 = *(q + 0);
    sub_80026A8C((char*)q[0x54 / 4] + p[4] * 28, *(p + 0xB), tmp27[1]);
}
// Matched
void sub_80026410(int* a0)
{
    int* q = (int*)a0[12];
    struct_112* p = (struct_112*)a0[5];
    int n = q[0];
    int h = ((int*)p->field_0)[1];
    int* list = (int*)sub_8003FC8C((n + 1) * 4, h);
    int i;
    int id;
    int src;
    p->field_58 = (int)list;
    list[0] = n;
    for (i = 0; i < n; i++)
    {
        id = q[i * 2 + 1];
        src = (int)q + q[i * 2 + 2];
        if (((unsigned char*)p->field_44)[id] == 0)
        {
            ((int*)p->field_58)[i + 1] = id;
            ((unsigned char*)p->field_44)[id] = 1;
            sub_80026A8C((char*)p->field_54 + id * 28, src, h);
        }
        else
        {
            ((int*)p->field_58)[i + 1] = -1;
        }
    }
}
#if 0
// Not matched
void sub_8002651C(struct_loader* a0)
{
    struct_112* p = a0->owner_14;
    int* list = a0->list_34;
    int heap = ((int*)p->field_0)[1];
    int* q = a0->data_18 + 1;
    p->field_42 = sub_80021738(list);
    sub_80021744(&p->field_68, p->field_42, heap);
    sub_80021824(a0->list_34, (char*)p->field_68, p->field_42, heap, (int)q);
}
#endif
INCLUDE_ASM(sub_8002651C);
// Matched
void sub_8002659C(char* a0)
{
    unsigned char* q = *(unsigned char**)(a0 + 0x38);
    struct_112* p = *(struct_112**)(a0 + 0x14);
    int h = ((int*)p->field_0)[1];
    int r;
    p->field_43 = *q;
    q += 4;
    r = sub_8003FC8C(p->field_43 << 2, h);
    p->field_6C = r;
    sub_800403E8((unsigned int*)r, (unsigned int*)q, p->field_43 << 2);
}
// Matched
int sub_80026600(struct_16_b* p)
{
    int n = 0;
    if (p->field_2 != -1)
    {
        do
        {
            p++;
            n++;
        } while (p->field_2 != -1);
    }
    return n;
}
// Matched
int sub_80026630(struct_112_list* p, unsigned int id)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].id_38 == id)
        {
            return i;
        }
    }
    return -1;
}
// Matched
int sub_8002667C(struct_112_list* p)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].id_38 == 0xFFFF)
        {
            return i;
        }
    }
    return -1;
}
// Matched
void sub_800266CC(struct_112* p)
{
    p->id_38 = 0xFFFF;
    p->field_4 = 0;
    p->field_34 = 0;
    p->field_3A = 0;
    p->field_3C = 0;
    p->field_3E = 0;
    p->field_40 = 0;
    p->field_42 = 0;
    p->field_43 = 0;
    p->field_44 = 0;
    p->field_48 = 0;
    p->field_4C = 0;
    p->field_50 = 0;
    p->field_54 = 0;
    p->field_58 = 0;
    p->field_5C = 0;
    p->field_60 = 0;
    p->field_64 = 0;
    p->field_68 = 0;
    p->field_6C = 0;
}
// Matched
int sub_80026724(int* p)
{
    return p[0];
}
// Matched
void sub_80026730(struct_28** a0, int a1, int a2)
{
    struct_28* p = (struct_28*)sub_8003FC8C(a1 * 28, a2);
    int i;
    *a0 = p;
    for (i = 0; i < a1; i++)
    {
        p[i].field_10 = 0;
        p[i].field_14 = 0;
        p[i].field_18 = 0;
    }
}
#if 0
// Not matched
void sub_8002679C(struct_28** a0, int n, int heap)
{
    struct_28* arr;
    struct_28* e;
    int i;
    arr = *a0;
    if (arr)
    {
        i = 0;
        e = arr;
        while (i < n)
        {
            if (e->field_10)
            {
                sub_8003FD18(e->field_10, heap);
            }
            if (e->field_14)
            {
                sub_8003FD18(e->field_14, heap);
            }
            if (e->field_18)
            {
                sub_8003FD18(e->field_18, heap);
            }
            i++;
            e++;
        }
        sub_8003FD18(arr, heap);
        *a0 = 0;
    }
}
#endif
INCLUDE_ASM(sub_8002679C);
// Matched
void sub_80026870(int* a0, int a1, int a2)
{
    int r = sub_80026724((int*)a1);
    sub_80026730((struct_28**)a0, r, a2);
    sub_800268E8(a0[0], a1, r, a2, -1);
}
#if 0
// Not matched: mask test becomes srav/andi, register assignment differs
void sub_800268E8(int a0, int a1, int n, int h, int mask)
{
    struct_28* p = (struct_28*)a0;
    int* q = (int*)a1;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if ((mask & (1 << i)) && p->field_14 == 0 && p->field_18 == 0)
        {
            sub_80026A8C(p, a1 + q[i + 1], h);
        }
    }
}
#endif
INCLUDE_ASM(sub_800268E8);
// Matched
void sub_800269C4(int a0, int n, int sel, int h)
{
    struct_28* p = (struct_28*)a0;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (sel == i && p->field_14 != 0 && p->field_18 != 0)
        {
            if (p->field_10 != 0)
            {
                sub_8003FD18(p->field_10, h);
            }
            sub_8003FD18(p->field_14, h);
            sub_8003FD18(p->field_18, h);
            p->field_10 = 0;
            p->field_14 = 0;
            p->field_18 = 0;
        }
    }
}
#if 0
void sub_80026A8C(void* a0, int a1, int a2)
{
}
#endif
INCLUDE_ASM(sub_80026A8C);
// Matched
int sub_80026D6C(int* p)
{
    return p[0];
}
// Matched
void sub_80026D78(struct_12** a0, int a1, int a2)
{
    struct_12* p = (struct_12*)sub_8003FC8C(a1 * 12, a2);
    int i;
    for (i = 0; i < a1; i++)
    {
        p[i].field_0 = 0;
        p[i].field_4 = 0;
        p[i].field_8 = 0;
    }
    *a0 = p;
}
// Matched
void sub_80026DE8(struct_12** a0, int n, int h)
{
    struct_12* p = *a0;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (p->field_8 != 0)
        {
            sub_8003FD18(p->field_8, h);
        }
    }
    sub_8003FD18(*a0, h);
    *a0 = 0;
}
// Matched
void sub_80026E74(struct_12* a0, int* a1, int a2)
{
    int i;
    for (i = 0; i < sub_80026D6C(a1); i++)
    {
        sub_80026EF8(a0, (unsigned short*)((char*)a1 + a1[i + 1]), a2);
        a0++;
    }
}
// Matched
typedef struct
{
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
} struct_4h;
// Matched
void sub_80026EF8(struct_12* p, unsigned short* s, int a2)
{
    unsigned short* d;
    int i;
    p->field_0 = *(int*)s;
    s += 2;
    p->field_4 = *(int*)s;
    s += 2;
    d = (unsigned short*)sub_8003FC8C(p->field_0 * 8, a2);
    p->field_8 = (int)d;
    for (i = 0; i < p->field_0; i++)
    {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d += 4;
        s += 4;
    }
}
extern int dword_8008D648[];
extern int dword_80082674;
extern int dword_80091C98;
extern int dword_80091C94;
extern int dword_80091C5C;
extern int dword_80091C58;
extern int dword_80091C90;
extern int dword_80091C9C;
extern int dword_80091C8C;
extern int stru_80091C78[];
extern int dword_800B1DC8;
extern int dword_80091C54;
extern short word_80091CB8[];
extern int dword_80091C10;
extern int dword_80091C68;
extern int dword_80091C48;
// Matched
void sub_80026FAC(void)
{
    sub_8003FDB0(&dword_80091C68);
    sub_8003FDB0(&dword_80091C20);
    sub_8003FDB0(&dword_80091C10);
    sub_8003FDB0(&dword_80091C48);
    dword_80091C30[0] = 0x3A;
    dword_80091C30[1] = 0;
    dword_80091C30[2] = 0;
    dword_80091C30[3] = -1;
    dword_8008B500[1] = 0;
    dword_8008B500[2] = 0;
    dword_8008B500[3] = 0;
    dword_8008B500[10] = 0;
    dword_8008B500[14] = 0;
    dword_8008B500[15] = 0;
    dword_8008D648[0] = 0;
    dword_8008D648[1] = 0;
    dword_8008D648[2] = 0;
    dword_8008D648[3] = 0;
    dword_8008D648[1] = 0;
    dword_8008D648[2] = 0;
    dword_8008D648[4] = 0;
    dword_8008D648[5] = 0;
    dword_8008D648[6] = 0;
    dword_80091C88 = -1;
    dword_80091C44 = -1;
    dword_80082674 = 0;
    dword_80091C98 = 0;
    dword_80091C94 = 0;
    dword_80091C5C = 1;
    dword_80091C58 = 1;
    dword_80091C90 = 0;
    dword_80091CA0 = 0;
    dword_80091C9C = 0;
    dword_80091C8C = 0;
    stru_80091C78[3] = -1;
    dword_80091C54 = dword_800B1DC8;
    word_80091CB8[7] = -1;
    word_80091CB8[6] = -1;
    word_80091CB8[5] = -1;
    word_80091CB8[4] = -1;
    word_80091CB8[3] = -1;
    word_80091CB8[2] = -1;
    word_80091CB8[1] = -1;
    word_80091C40 = -1;
    word_80091CB8[0] = -1;
    (&word_80091C40)[1] = -1;
    dword_80082678 = 0;
    sub_8001D378();
}
extern int dword_80091C74;
extern int dword_80091CB4;
extern int dword_80082668;
extern int dword_8008266C;
extern int* dword_800B1DA8;
extern int* dword_8008D400;
extern int* dword_8008D640;
extern int* dword_8008D49C;
extern int* dword_8008D674;
extern int* dword_8008D488;
extern void sub_8001D3C4(int a0);
extern void sub_800AC73C(void);
extern void sub_800A54A0(void);
extern void sub_800A58B4(void);
extern void sub_800A7784(void);
extern void sub_800A170C(void);
extern void sub_800A1794(void);
// Matched
void sub_80027118(void)
{
    word_80091CB8[7] = -1;
    word_80091CB8[6] = -1;
    word_80091CB8[5] = -1;
    word_80091CB8[4] = -1;
    word_80091CB8[3] = -1;
    word_80091CB8[2] = -1;
    word_80091CB8[1] = -1;
    word_80091C40 = -1;
    word_80091CB8[0] = -1;
    (&word_80091C40)[1] = -1;
    sub_8002741C();
    dword_80082678 = 0;
    dword_80091C74 = -1;
    dword_80091CB4 = 0;
    dword_80091C88 = -1;
    dword_80082668 = 0;
    dword_8008266C = 0;
    if (dword_80091C8C == 0)
    {
        sub_80043B40(dword_800B1DA8);
        sub_80043B40(dword_8008D400);
    }
    sub_800AC73C();
    sub_80043B40(dword_8008D640);
    sub_80043B40(dword_8008D49C);
    sub_80043B40(dword_8008D674);
    sub_80043B40(dword_8008D488);
    sub_800A54A0();
    sub_800A58B4();
    sub_8001D3C4(dword_80091CA0);
    sub_800A7784();
    sub_800A170C();
    sub_800A1794();
    sub_8003FEC8(&dword_80091C10);
    sub_8003FEC8(&dword_80091C68);
    if (!(unknownFlags_8008D678 & 0x20000))
    {
        sub_8003FEC8(&dword_80091C48);
    }
}
// Matched
void sub_8002728C(void)
{
    dword_80091C44 = -1;
    sub_8003FEC8(&dword_80091C20);
}
// Matched
void sub_800272BC(int a0, int a1)
{
    dword_80091C88 = a0;
    dword_80091C44 = a1;
}
#if 0
// Not matched (close)
int sub_800272D0(void)
{
    int* a = dword_800B1DC4[0x24 / 4];
    int* b = dword_800B1DB8[0x24 / 4];
    if (*a != 0)
    {
        return 1;
    }
    if (*b == 0)
    {
        return 0;
    }
    return 1;
}
#endif
// Matched
int sub_800272D0(void)
{
    int* a = dword_800B1DC4[9];
    int* b = dword_800B1DB8[9];
    if (a[0] != 0 || b[0] != 0)
    {
        return 1;
    }
    return 0;
}
// Matched
void sub_80027314(void)
{
    dword_80082670 = 1;
    word_8008B862 = -1;
}
// Matched
int sub_80027330(short a0)
{
    if (dword_80082678 == 0)
    {
        word_80091C40 = a0;
        return 1;
    }
    return 0;
}
// Matched
// Matched
int sub_80027358(int id)
{
    int* p;
    short* s;
    if (dword_80082678 == 1)
    {
        if (word_80091C40 != id)
        {
            word_8008B860 = id;
            return 0;
        }
        p = dword_800B1DB8[9];
        if (sub_8003BE30(p[1]) != 3)
        {
            return 0;
        }
        sub_8002728C();
        sub_8003BFD0(p[1], 0);
        sub_80028DC0();
        s = (short*)&saveData_8008B570;
        s[0x2F0 / 2] = id;
        s[0x2F2 / 2] = id;
        dword_80082678 = 0;
        return 1;
    }
    word_8008B860 = id;
    return 0;
}
// Matched
void sub_8002741C(void)
{
    int* p;
    if (dword_80082678 == 1)
    {
        p = dword_800B1DB8[9];
        sub_8003C060(p[1]);
        dword_80082678 = 0;
        p[0] = 0;
    }
}
// Matched
void sub_80027478(int mask, int set)
{
    int f;
    int code;
    if (set)
    {
        dword_80091C30[2] |= mask;
    }
    else
    {
        dword_80091C30[2] &= ~mask;
    }
    f = dword_80091C30[2];
    if (f && !(f & 1))
    {
        code = 0;
        if (!(f & 0x40))
        {
            if (dword_80091C30[0] & f)
            {
                code = 1;
            }
            else if (dword_80091C30[1] & f)
            {
                code = 2;
            }
        }
        dword_80091C30[2] |= 1;
        sub_8001C19C(code, 0x20);
    }
}
// Matched
int sub_80027540(void)
{
    int* g = dword_80091C30;
    if (g[2] & 0x40)
    {
        return 1;
    }
    if (g[2] & 1)
    {
        if (g[2] == 1 && sub_8001C2FC())
        {
            g[3] = 2;
            g[2] &= ~1;
            return 1;
        }
        return 0;
    }
    if (g[3] > 0)
    {
        g[3]--;
        if (g[3] <= 0)
        {
            sub_8001C19C(3, 0);
        }
    }
    return 1;
}
// Matched
void sub_800275E8(char** a0, int a1, int a2)
{
    char* p;
    char* q;
    int i;
    if (a1 != 0)
    {
        p = (char*)sub_8003FDC0(a2, a1);
        *a0 = p;
        q = p;
        for (i = 0; i < a1; i++)
        {
            q[i] = 1;
        }
    }
}
// Matched
int* sub_80027650(int* a0, int a1, int h)
{
    int* src;
    int* d;
    int n;
    int i;
    int* g = dword_80091C60;
    a0 += 1;
    n = *a0++;
    src = a0;
    g[0] = n;
    if (n != 0)
    {
        d = (int*)sub_8003FDC0(h, n * 16);
        g[1] = (int)d;
        for (i = 0; i < g[0]; i++)
        {
            d[0] = src[0];
            d[1] = src[1];
            d[2] = src[2];
            d[3] = src[3];
            d += 4;
            src += 4;
        }
    }
    return src;
}
// Matched
void sub_80027708(int* a0, int a1)
{
    int r = sub_80021738(a0);
    dword_8008B500[0x38 / 4] = r;
    if (r != 0)
    {
        sub_80021744(&dword_8008B500[0x3C / 4], r, a1);
        sub_80021824(a0, dword_8008B500[0x3C / 4], dword_8008B500[0x38 / 4], a1, 0);
    }
}
#if 0
// Not matched: inner copy loop: original copies the entry pointer to a temp register (a2)
void sub_80027778(int* a0, int h)
{
    struct_27778* arr;
    struct_27778* e;
    unsigned int i;
    int j;
    int* src;
    unsigned short* q;
    int n;
    dword_8008D648[1] = a0[0];
    dword_8008D648[2] = a0[1];
    n = a0[2];
    dword_8008D648[0] = n;
    arr = (struct_27778*)sub_8003FDC0(h, n * 16);
    for (i = 0; i < dword_8008D648[0]; i++)
    {
        src = (int*)((char*)a0 + a0[i + 3]);
        e = &arr[i];
        e->field_0 = *src++;
        e->count = *src++;
        q = (unsigned short*)src;
        e->field_8 = *q++;
        e->field_A = *q++;
        e->items = (unsigned short*)sub_8003FDC0(h, e->count * 2);
        for (j = 0; j < e->count; j++)
        {
            e->items[j] = *q++;
        }
    }
    dword_8008D648[3] = (int)arr;
}
#endif
INCLUDE_ASM(sub_80027778);
INCLUDE_ASM(sub_800278BC);
INCLUDE_ASM(sub_80027A88);
// Matched
void sub_80027CC0(struct_obj_D* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    sub_80027CF8(p, q);
    p->field_8 = (void (*)(void))sub_80027CF8;
}
#if 0
void sub_80027CF8(void* a0, int* a1)
{
}
#endif
INCLUDE_ASM(sub_80027CF8);
// Matched
// Matched
void sub_8002830C(struct_obj_D* p)
{
    short* s = (short*)&saveData_8008B570;
    s[0x2E6 / 2] = -1;
    s[0x2EA / 2] = -1;
    s[0x2EE / 2] = -1;
    s[0x2F2 / 2] = -1;
    unknownFlags_8008D678 &= ~0x20000;
    dword_80091CA0 = 1;
    sub_80027118();
    sub_8002728C();
    p->field_8 = (void (*)(void))sub_80027CC0;
}
// Matched
void sub_80028388(struct_obj_D* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    sub_800283C0(p, q);
    p->field_8 = (void (*)(void))sub_800283C0;
}
#if 0
void sub_800283C0(void* a0, int* a1)
{
}
#endif
INCLUDE_ASM(sub_800283C0);
INCLUDE_ASM(sub_80028808);
