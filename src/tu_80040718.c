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

INCLUDE_DATA(dword_80074A24);
INCLUDE_DATA(dword_80074A34);
INCLUDE_DATA(dword_80074A88);
INCLUDE_DATA(dword_80074AA8);
INCLUDE_DATA(dword_80074B10);

extern int geomScreenDistance_8008B548;
#if 0
void sub_80040718(void)
{
    int i;
    unknownFlags_8008D678 = 0;
    geomScreenDistance_8008B548 = 0;
    saveData_8008B570.field_1C_settings &= 0xFFFFC07F;
    saveData_8008B570.field_1C_settings |= 0x2800;
    saveData_8008B570.field_1C_settings &= 0xFFE03FFF;
    saveData_8008B570.field_1C_settings |= 0x100000;
    saveData_8008B570.field_1C_settings |= 0x200038;
    saveData_8008B570.field_1C_settings &= 0xFFFFFFF8;
    saveData_8008B570.field_1C_settings |= 0x400002;
    saveData_8008B570.field_1C_settings |= 0x800000;
    saveData_8008B570.field_1C_settings |= 0x1000000;
    saveData_8008B570.field_1C_settings &= 0xFFFFFFBF;
    i = 14;
    while (i >= 0)
    {
        saveData_8008B570.minions[i].id = 4;
        i--;
    }
    sub_8001C6C8();
    word_8008B558[1] = 0;
}
#endif
INCLUDE_ASM(sub_80040718);
extern int dword_8008D430;
extern int dword_8008D434;
extern int dword_8008D440;
extern int dword_8008D4D0;
extern void sub_80021824(int* p, int a, int b, int c, int d);

// Matched
void LoadPublicTiyAndFtg_800407D0(void)
{
    int* pFile = (int*)Data001Reader_LoadIntoGlobal_8003CB40(9);
    numFilesInsideTiy_8008B4BC = GetTiyFileCount_80028E68(pFile);
    sub_80028E74(&dword_8008D434, (int)&dword_8008D430, &dword_8008D440, (int)pFile, 1);
    pFile = (int*)Data001Reader_LoadIntoGlobal_8003CB40(10);
    sub_80021744(&dword_8008D4D0, sub_80021738(pFile), 1);
    sub_80021824(pFile, dword_8008D4D0, sub_80021738(pFile), 1, 0);
    sub_80030A84(0, &stru_80091D40);
    sub_8003DA70();
}
// Matched
void sub_80040898(void)
{
    void* pFile = Data001Reader_LoadIntoGlobal_8003CB40(9);
    numFilesInsideTiy_8008B4BC = GetTiyFileCount_80028E68((int*)pFile);
    sub_80028E74(0, 0, 0, (int)pFile, 1);
    sub_8003DA70();
}
extern int dword_8008D47C;
extern int dword_8008B4EC;


// Matched
void sub_800408F4(void)
{
    if ((unsigned int)frameCount_8008D3FC < 0x190)
    {
        int i;
        short* e = (short*)dword_8008D47C;
        e[4] = 0;
        e[5] = 0;
        e[0xE] = 0x100;
        e[0xF] = 0;
        e[0x18] = 0x200;
        e[0x19] = 0;
        e[0x22] = 0;
        e[0x23] = 0x100;
        e[0x2C] = 0x100;
        e[0x2D] = 0x100;
        e[0x36] = 0x200;
        e[0x37] = 0x100;
        for (i = 0; i < 6; i++)
        {
            sub_80040298(pOT_8008D3EC, (char*)dword_8008D47C + i * 0x14, 5);
            sub_80040298(pOT_8008D3EC, (char*)dword_8008B4EC + i * 8, 2);
        }
    }
    else
    {
        free3_8003FC6C((void*)dword_8008D47C);
        free3_8003FC6C((void*)dword_8008B4EC);
        sub_80040898();
        bStopDrawingMovie_8008D45C = 1;
    }
}
extern void sub_800408F4(void);
// Matched
void sub_80040A10(int* a0)
{
    void* pFile = DATA_GetFileBuffer_8003CAA0(0x38);
    dword_8008D47C = 0;
    dword_8008B4EC = 0;
    sub_80028E74(&dword_8008D47C, 0, &dword_8008B4EC, (int)pFile, 1);
    free3_8003FC6C(pFile);
    a0[2] = (int)sub_800408F4;
}
// Matched
void ShowCopyright_80040A84(void)
{
    sub_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(copyright_80086948);
}
// Matched
void PlayGenkiMovie_80040AC4(void)
{
    PlayMovie_80040EB4(0);
    bStopDrawingMovie_8008D45C = 1;
}
// Matched
void PlayGenkiMovie_80040AEC(void)
{
    sub_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(genkiMovie_80086968);
}
// Matched
void PlayCraveMovie_80040B2C(void)
{
    PlayMovie_80040EB4(0x19);
    bStopDrawingMovie_8008D45C = 1;
}
// Matched
void PlayCraveEntertainmentMovie_80040B54(void)
{
    sub_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(craveEntertainmentMovie_80086988);
}
extern void sub_8003E91C(int mode, void* str, void* pos, int z);
extern char dword_80074A24[];
extern char dword_80074A34[];
extern char dword_80074A88[];
extern char dword_80074AA8[];
extern char dword_80074B10[];

// Matched
void sub_80040B94(void)
{
    if ((unsigned int)frameCount_8008D3FC < 0xC8)
    {
        short p0[2];
        short p1[2];
        short p2[2];
        short p3[2];
        short p4[2];
        p0[0] = 0x10;
        p0[1] = 0xA2;
        sub_8003E91C(2, dword_80074A24, p0, 0);
        p1[0] = 0x10;
        p1[1] = 0xAE;
        sub_8003E91C(2, dword_80074A34, p1, 0);
        p2[0] = 0x10;
        p2[1] = 0xBA;
        sub_8003E91C(2, dword_80074A88, p2, 0);
        p3[0] = 0x10;
        p3[1] = 0xC6;
        sub_8003E91C(2, dword_80074AA8, p3, 0);
        p4[0] = 0x10;
        p4[1] = 0xD2;
        sub_8003E91C(2, dword_80074B10, p4, 0);
    }
    else
    {
        bStopDrawingMovie_8008D45C = 1;
    }
}
