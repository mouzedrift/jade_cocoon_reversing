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
INCLUDE_ASM(sub_800408F4);
extern int dword_8008D47C;
extern int dword_8008B4EC;
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
INCLUDE_ASM(sub_80040B94);
