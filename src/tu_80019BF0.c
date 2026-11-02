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
INCLUDE_ASM(sub_8001A38C);
INCLUDE_ASM(sub_8001A41C);
#if 0
// Not matched
void sub_8001A9A4(void)
{
    unsigned short* p;
    dword_8008D40C = 0x1000;
    p = (unsigned short*)dword_8008D628[9];
    unknownFlags_8008D678 &= ~0x400;
    p[1] = 0;
    p[0] &= 0xFFF0;
}
#endif
INCLUDE_ASM(sub_8001A9A4);
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
unsigned char sub_8001AC58(int idx)
{
    if (idx < 0x1E)
    {
        return dword_8007C438[idx].field_4;
    }
    return 0;
}
INCLUDE_ASM(sub_8001AC8C);
INCLUDE_ASM(sub_8001AD64);
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
INCLUDE_ASM(sub_8001AEC0);
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
INCLUDE_ASM(InitMovie_8001B1B0);
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
INCLUDE_ASM(sub_8001B540);
INCLUDE_ASM(Draw_8001B5EC);
#if 0
// Not matched: same logic, the compiler addresses dword_8008B4B4 differently
int sub_8001B6E8(void)
{
    int snapshot = dword_8008B4B4;
    while (dword_8008B4B4 <= snapshot)
    {
    }
    return gnFrame_8008D610;
}
#endif
INCLUDE_ASM(sub_8001B6E8);
INCLUDE_ASM(sub_8001B714);
INCLUDE_ASM(InitEnvironments_8001B7B4);
INCLUDE_ASM(InitSprt_8001B9A0);
INCLUDE_ASM(sub_8001BB28);
INCLUDE_ASM(sub_8001BC00);
INCLUDE_ASM(sub_8001BCE4);
INCLUDE_ASM(sub_8001BEC8);
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
INCLUDE_ASM(sub_8001C02C);
INCLUDE_ASM(sub_8001C0B4);
INCLUDE_ASM(sub_8001C19C);
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
INCLUDE_ASM(sub_8001C364);
INCLUDE_ASM(sub_8001C440);
INCLUDE_ASM(sub_8001C6C8);
#if 0
// Not matched
void sub_8001C79C(int a0, int a1)
{
    unsigned short* p = &dword_8008B578[a0];
    unsigned short r1 = sub_8001C818(p);
    unsigned short* q = &dword_8008B578[a1];
    unsigned short r2 = sub_8001C818(q);
    sub_8001C810((short*)p, r2);
    sub_8001C810((short*)q, r1);
}
#endif
INCLUDE_ASM(sub_8001C79C);
// Matched
void sub_8001C810(short* p, short v)
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
INCLUDE_ASM(sub_8001C874);
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
INCLUDE_ASM(sub_8001CE70);
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
unsigned short sub_8001D008(unsigned int idx)
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
unsigned short sub_8001D0D0(unsigned int idx)
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
#if 0
// Not matched
int sub_8001D128(int a0, int a1)
{
    int r = 0;
    if (a1 == 1)
    {
        r = sub_8001CFDC(a0);
    }
    else if (a1 == 0)
    {
        r = sub_8001CF20(a0);
    }
    else if (a1 == 2)
    {
        r = sub_8001D0A4(a0);
    }
    return r;
}
#endif
INCLUDE_ASM(sub_8001D128);
#if 0
short* sub_8001D190(void)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8001D190);
INCLUDE_ASM(sub_8001D1F8);
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
#if 0
// Not matched (close)
int sub_8001D2D4(void)
{
    short* p = sub_8001D190();
    short idx;
    if (0 != p)
    {
        idx = *p;
    }
    else
    {
        idx = 0x24;
    }
    return dword_8007D938[idx];
}
#endif
INCLUDE_ASM(sub_8001D2D4);
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
#if 0
// Not matched
int* sub_8001D45C(int a0)
{
    struct_cb* r = sub_80043AF8(dword_8008D43C);
    int* p;
    if (r == 0)
    {
        p = 0;
    }
    else
    {
        p = r->field_14;
        r->fn_8 = (void (*)(struct_cb*, int*))sub_8001D41C;
        r->flags_0 = (r->flags_0 | 1) & ~0x8000;
        p[0] = (int)r;
        sub_8001E574(p, a0);
    }
    return p;
}
#endif
INCLUDE_ASM(sub_8001D45C);
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
INCLUDE_ASM(sub_8001DC60);
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
    sub_8003FE38(dword_80091990, v);
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
#if 0
// Not matched
void sub_8001EFC4(struct_obj_F* p)
{
    unsigned int f = p->flags_4;
    int n;
    if (f & 0x800000)
    {
        n = p->field_C;
        if (n < 0 || n >= 3)
        {
            if (f & 0x200000)
            {
                sub_800A5BCC(n - 2);
            }
        }
    }
    p->flags_4 &= 0xFF17FFFF;
}
#endif
INCLUDE_ASM(sub_8001EFC4);
INCLUDE_ASM(sub_8001F03C);
INCLUDE_ASM(sub_8001F268);
#if 0
void sub_8001F354(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001F354);
#if 0
void sub_8001F918(void* a0)
{
}
#endif
INCLUDE_ASM(sub_8001F918);
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
INCLUDE_ASM(sub_8001FC90);
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
INCLUDE_ASM(sub_800201EC);
INCLUDE_ASM(sub_80020278);
INCLUDE_ASM(sub_8002032C);
INCLUDE_ASM(sub_800203B0);
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
#if 0
// Not matched
void sub_800204D0(void)
{
    int* p = dword_8008B54C[9];
    struct_20* e = (struct_20*)(p + 3);
    int i;
    p[0] = 0;
    p[1] = 1;
    p[2] = 0;
    for (i = 0; i < 4; i++)
    {
        e[i].field_0 = 0;
        e[i].field_4 = -1;
        e[i].field_8 = 0;
        e[i].field_C = 0;
        e[i].field_10 = -1;
    }
}
#endif
INCLUDE_ASM(sub_800204D0);
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
INCLUDE_ASM(sub_80020768);
INCLUDE_ASM(sub_80020814);
INCLUDE_ASM(sub_80020898);
INCLUDE_ASM(sub_80020924);
INCLUDE_ASM(sub_800209AC);
INCLUDE_ASM(sub_80020A38);
INCLUDE_ASM(sub_80020B70);
#if 0
int LoadOverlay_80020BF8(int mode, enum OverlayIds overlayIdx)
{
    return 0;
}
#endif
INCLUDE_ASM(LoadOverlay_80020BF8);
#if 0
// Not matched (close)
void sub_80020CD8(int a0, int* p)
{
    int v = p[0];
    if (v != p[1])
    {
        p[1] = v;
        p[2] = LoadOverlay_80020BF8(2, v);
    }
}
#endif
INCLUDE_ASM(sub_80020CD8);
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
INCLUDE_ASM(sub_80021784);
// Matched
void sub_80021804(int* p)
{
    sub_800229B0(p);
}
INCLUDE_ASM(sub_80021824);
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
void sub_80021E24(volatile int* p)
{
    p[0] = 0;
    sub_8003FD18(p[1]);
}
// Matched
void sub_80021E4C(char* a0, int* a1, unsigned int n)
{
    unsigned short* src = (unsigned short*)(a0 + *(int*)(a0 + 0xC));
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        unsigned short* d = (unsigned short*)(a1[1] + i * 16);
        d[0] = src[0];
        d[1] = src[1];
        d[2] = src[2];
        d[3] = src[3];
        d[4] = src[4];
        d[5] = src[5];
        d[6] = src[6];
        d[7] = src[7];
        src += 8;
    }
}
INCLUDE_ASM(sub_80021EDC);
INCLUDE_ASM(sub_800221DC);
INCLUDE_ASM(sub_80022458);
INCLUDE_ASM(sub_80022634);
INCLUDE_ASM(sub_800228F8);
// Matched
void sub_800229B0(int* p)
{
    int a = p[1];
    if (a)
    {
        sub_8003FD18(a);
    }
}
INCLUDE_ASM(sub_800229E0);
#if 0
void sub_80022AE8(void* arg0, void* arg1, int arg2)
{
}
#endif
INCLUDE_ASM(sub_80022AE8);
INCLUDE_ASM(sub_80022B84);
INCLUDE_ASM(sub_80022CC4);
INCLUDE_ASM(sub_8002300C);
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
INCLUDE_ASM(sub_80023514);
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
INCLUDE_ASM(sub_800236AC);
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
INCLUDE_ASM(sub_80023934);
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
INCLUDE_ASM(sub_80023BD0);
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
INCLUDE_ASM(sub_80023F34);
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
INCLUDE_ASM(sub_80024104);
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
INCLUDE_ASM(sub_8002441C);
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
INCLUDE_ASM(sub_80024730);
// Matched
void sub_80024AB8(unsigned short* p, int arg1)
{
    sub_80022AE8(p, p + 1, arg1);
}
INCLUDE_ASM(sub_80024ADC);
#if 0
void sub_80024BB0(int* a0)
{
}
#endif
INCLUDE_ASM(sub_80024BB0);
INCLUDE_ASM(sub_80024C48);
// Matched
int sub_80024D70(int a0, int a1)
{
    struct_112_list* p = (struct_112_list*)a0;
    struct_112* q;
    int i = sub_80026630(p, a1);
    if (i >= 0)
    {
        q = &p->items[i];
        q->field_3A++;
        return (int)q;
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
// Not matched: result lands in a2 instead of v0, loop counter init differs
char* sub_80024FA8(void* a0, int n)
{
    char* result = 0;
    int* hdr = ((struct_obj_E*)a0)->field_4C;
    int i;
    char* q;
    if (hdr != 0 && hdr[2] != 0)
    {
        q = (char*)hdr + hdr[2] + 8;
        for (i = 0; i < n; i++)
        {
            q += *(int*)(q + 0x14);
        }
        result = q;
    }
    return result;
}
#endif
INCLUDE_ASM(sub_80024FA8);
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
INCLUDE_ASM(sub_80025200);
INCLUDE_ASM(sub_80025440);
// Matched
void sub_8002556C(struct_112* p, int i)
{
    if (((unsigned char*)p->field_44)[i] != 0)
    {
        sub_800269C4(p->field_54, p->field_3E, i, ((int*)p->field_0)[1]);
        ((unsigned char*)p->field_44)[i] = 0;
    }
}
// Matched
int sub_800255D8(struct_112* p, int i)
{
    return ((unsigned char*)p->field_44)[i] != 0;
}
INCLUDE_ASM(sub_800255F0);
INCLUDE_ASM(sub_800256B8);
INCLUDE_ASM(sub_80025780);
INCLUDE_ASM(sub_80025884);
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
INCLUDE_ASM(sub_80025974);
// Matched
void sub_80025AB0(struct_112* p)
{
    int h = ((int*)p->field_0)[1];
    if (p->field_68 != 0)
    {
        sub_80021784(&p->field_68, p->field_42, h);
        p->field_42 = 0;
        p->field_68 = 0;
    }
    if (p->field_6C != 0)
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
INCLUDE_ASM(sub_80025B5C);
INCLUDE_ASM(sub_80025C38);
extern int sub_8003BC84(int* p);
typedef struct
{
    int field_0;
    int count;
    int items[10];
} struct_25D00;
// Matched
int sub_80025D00(struct_25D00* p, int* q)
{
    if (p->count < 10)
    {
        q[2] <<= 11;
        q[3] <<= 11;
        p->items[p->count] = sub_8003BC84(q);
        p->count++;
        return 1;
    }
    return 0;
}
INCLUDE_ASM(sub_80025D7C);
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
INCLUDE_ASM(sub_80025F14);
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
    struct_112* p;
    if (a0[2] != -1)
    {
        p = (struct_112*)a0[5];
        sub_80028FDC(0, 0, 0, a0[8], GetTiyFileCount_80028E68((int*)a0[8]), a0[6] + 4, a0[2]);
        p->field_34 = a0[2];
    }
}
INCLUDE_ASM(sub_800260FC);
INCLUDE_ASM(sub_800261C8);
// Matched
void sub_800263CC(int* p)
{
    int* tmp27;
    int** q = (int**)p[5];
    tmp27 = *(q + 0);
    sub_80026A8C((char*)q[0x54 / 4] + p[4] * 28, *(p + 0xB), tmp27[1]);
}
INCLUDE_ASM(sub_80026410);
#if 0
// Not matched: a0 and q get swapped callee-saved registers (s1/s2)
void sub_8002651C(int* a0)
{
    int q = a0[6];
    struct_112* p = (struct_112*)a0[5];
    int h = ((int*)p->field_0)[1];
    q += 4;
    p->field_42 = sub_80021738((int*)a0[13]);
    sub_80021744(&p->field_68, p->field_42, h);
    sub_80021824((int*)a0[13], p->field_68, p->field_42, h, q);
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
INCLUDE_ASM(sub_8002679C);
// Matched
void sub_80026870(int* a0, int a1, int a2)
{
    int r = sub_80026724((int*)a1);
    sub_80026730((struct_28**)a0, r, a2);
    sub_800268E8(a0[0], a1, r, a2, -1);
}
INCLUDE_ASM(sub_800268E8);
INCLUDE_ASM(sub_800269C4);
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
        sub_80026EF8(a0, (char*)a1 + a1[i + 1], a2);
        a0++;
    }
}
INCLUDE_ASM(sub_80026EF8);
INCLUDE_ASM(sub_80026FAC);
INCLUDE_ASM(sub_80027118);
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
INCLUDE_ASM(sub_80027358);
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
INCLUDE_ASM(sub_80027478);
INCLUDE_ASM(sub_80027540);
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
INCLUDE_ASM(sub_80027650);
// Matched
void sub_80027708(int* a0, int a1)
{
    int n = sub_80021738(a0);
    dword_8008B500[14] = n;
    if (n != 0)
    {
        sub_80021744(&dword_8008B500[15], n, a1);
        sub_80021824(a0, dword_8008B500[15], dword_8008B500[14], a1, 0);
    }
}
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
void sub_8002830C(struct_obj_D* p)
{
    saveData_8008B570.field_2E4[0].field_2 = -1;
    saveData_8008B570.field_2E4[1].field_2 = -1;
    saveData_8008B570.field_2E4[2].field_2 = -1;
    saveData_8008B570.field_2E4[3].field_2 = -1;
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
