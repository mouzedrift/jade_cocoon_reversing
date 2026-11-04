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
#include "tiy.h"
#include "tu_8001EA48.h"
#include "tu_80040718.h"
#include "main.h"

const char dword_80074A24[] = "\202v\202\201\202\222\202\216\202\211\202\216\202\207"; // Warning
const char dword_80074A34[] = "\202s\202\210\202\211\202\223\201@\202\204\202\205\202\215\202\217\201@\202\226\202\205\202\222\202\223\202\211\202\217\202\216\201@\202\217\202\206\201@\202i\202\201\202\204\202\205\201@\202b\202\217\202\203\202\217\202\217\202\216\201@\202\211\202\223\201@\202\223\202\224\202\211\202\214\202\214"; // This demo version of Jade Cocoon is still
const char dword_80074A88[] = "\202\211\202\216\201@\202\204\202\205\202\226\202\205\202\214\202\217\202\220\202\215\202\205\202\216\202\224\201D"; // in development.
const char dword_80074AA8[] = "\202c\202\225\202\205\201@\202\224\202\217\201@\202\206\202\225\202\224\202\225\202\222\202\205\201@\202\215\202\217\202\204\202\211\202\206\202\211\202\203\202\201\202\224\202\211\202\217\202\216\202\223\201@\202\201\202\216\202\204\201@\202\203\202\210\202\201\202\216\202\207\202\205\202\223\201C\201@\202\211\202\224\201@\202\215\202\201\202\231\201@\202\202\202\205"; // Due to future modifications and changes, it may be
const char dword_80074B10[] = "\202\223\202\211\202\207\202\216\202\211\202\206\202\211\202\203\202\201\202\216\202\224\202\214\202\231\201@\202\204\202\211\202\206\202\206\202\205\202\222\202\205\202\216\202\224\201@\202\206\202\222\202\217\202\215\201@\202\224\202\210\202\205\201@\202\222\202\205\202\224\202\201\202\211\202\214\201@\202\226\202\205\202\222\202\223\202\211\202\217\202\216\201D"; // significantly different from the retail version.

extern int geomScreenDistance_8008B548;
// Matched
void InitGameDefaults_80040718(void)
{
    int i;
    int j;
    unknownFlags_8008D678 = 0;
    geomScreenDistance_8008B548 = 0;
    saveData_8008B570.settings_1C.word &= 0xFFFFC07F;
    saveData_8008B570.settings_1C.word |= 0x2800;
    saveData_8008B570.settings_1C.word &= 0xFFE03FFF;
    saveData_8008B570.settings_1C.word |= 0x100000;
    saveData_8008B570.settings_1C.word |= 0x200038;
    saveData_8008B570.settings_1C.word &= 0xFFFFFFF8;
    saveData_8008B570.settings_1C.word |= 0x400002;
    saveData_8008B570.settings_1C.word |= 0x800000;
    saveData_8008B570.settings_1C.word |= 0x1000000;
    saveData_8008B570.settings_1C.word &= 0xFFFFFFBF;
    j = 14;
    for (i = 0; i < 15; i++)
    {
        saveData_8008B570.minions[j].id = 4;
        j--;
    }
    ResetButtonConfig_8001C6C8();
    word_8008B558[1] = 0;
}

// Matched
void LoadPublicTiyAndFtg_800407D0(void)
{
    int* pFile = (int*)Data001Reader_LoadIntoGlobal_8003CB40(9);
    numFilesInsideTiy_8008B4BC = GetTiyFileCount_80028E68(pFile);
    LoadTiy_80028E74(&publicTiySprts_8008D434, &publicTiyPolyFT4s_8008D430, &publicTiyTPages_8008D440, pFile, 1);
    pFile = (int*)Data001Reader_LoadIntoGlobal_8003CB40(10);
    AllocFtgObjects_80021744(&publicFtg_8008D4D0, GetFtgObjectCount_80021738(pFile), 1);
    LoadFtgObjects_80021824(pFile, publicFtg_8008D4D0, GetFtgObjectCount_80021738(pFile), 1, 0);
    LoadSound_80030A84(0, &systemSound_80091D40);
    InitFonts_8003DA70();
}
// Matched
void ReloadPublicTiy_80040898(void)
{
    void* pFile = Data001Reader_LoadIntoGlobal_8003CB40(9);
    numFilesInsideTiy_8008B4BC = GetTiyFileCount_80028E68((int*)pFile);
    LoadTiy_80028E74(0, 0, 0, pFile, 1);
    InitFonts_8003DA70();
}


// Matched
void DrawCopyrightScreen_800408F4(void)
{
    if ((unsigned int)frameCount_8008D3FC < 0x190)
    {
        int i;
        SPRT* e = copyrightSprts_8008D47C;
        e[0].x0 = 0;
        e[0].y0 = 0;
        e[1].x0 = 0x100;
        e[1].y0 = 0;
        e[2].x0 = 0x200;
        e[2].y0 = 0;
        e[3].x0 = 0;
        e[3].y0 = 0x100;
        e[4].x0 = 0x100;
        e[4].y0 = 0x100;
        e[5].x0 = 0x200;
        e[5].y0 = 0x100;
        for (i = 0; i < 6; i++)
        {
            AddPrimCopy_80040298(pOT_8008D3EC, &copyrightSprts_8008D47C[i], 5);
            AddPrimCopy_80040298(pOT_8008D3EC, &copyrightTPages_8008B4EC[i], 2);
        }
    }
    else
    {
        free3_8003FC6C(copyrightSprts_8008D47C);
        free3_8003FC6C(copyrightTPages_8008B4EC);
        ReloadPublicTiy_80040898();
        bStopDrawingMovie_8008D45C = 1;
    }
}
extern void DrawCopyrightScreen_800408F4(void);
// Matched
void InitCopyrightScreen_80040A10(int* a0)
{
    void* pFile = DATA_GetFileBuffer_8003CAA0(0x38);
    copyrightSprts_8008D47C = 0;
    copyrightTPages_8008B4EC = 0;
    LoadTiy_80028E74(&copyrightSprts_8008D47C, 0, &copyrightTPages_8008B4EC, pFile, 1);
    free3_8003FC6C(pFile);
    a0[2] = (int)DrawCopyrightScreen_800408F4;
}
// Matched
void ShowCopyright_80040A84(void)
{
    EndFade_8001C290();
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
    EndFade_8001C290();
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
    EndFade_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(craveEntertainmentMovie_80086988);
}
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);
extern const char dword_80074A24[];
extern const char dword_80074A34[];
extern const char dword_80074A88[];
extern const char dword_80074AA8[];
extern const char dword_80074B10[];

// Matched
void DrawDemoDisclaimer_80040B94(void)
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
        DrawText_8003E91C(2, dword_80074A24, p0, 0);
        p1[0] = 0x10;
        p1[1] = 0xAE;
        DrawText_8003E91C(2, dword_80074A34, p1, 0);
        p2[0] = 0x10;
        p2[1] = 0xBA;
        DrawText_8003E91C(2, dword_80074A88, p2, 0);
        p3[0] = 0x10;
        p3[1] = 0xC6;
        DrawText_8003E91C(2, dword_80074AA8, p3, 0);
        p4[0] = 0x10;
        p4[1] = 0xD2;
        DrawText_8003E91C(2, dword_80074B10, p4, 0);
    }
    else
    {
        bStopDrawingMovie_8008D45C = 1;
    }
}

char copyright_80086948[8] = { 48, 105, 8, 128 };
int genkiMovieData_80086950[6] = { 1, 1, 0, 0, 0x80040AC4 };
char genkiMovie_80086968[8] = { 80, 105, 8, 128 };
int craveEntertainmentData_80086970[6] = { 1, 1, 0, 0, 0x80040B2C };
char craveEntertainmentMovie_80086988[8] = { 112, 105, 8, 128 };
int demoDisclaimerData_80086990[6] = { 1, 1, 0, 0, 0x80040B94 };
