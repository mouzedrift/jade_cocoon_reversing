#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "tiy.h"
#include "model.h"
#include "boot.h"
#include "main.h"
#include "font.h"
#include "util.h"
#include "pad_text.h"
#include "movie.h"
#include "tim.h"
#include "engine.h"
#include "model_ftg.h"
#include "cdread.h"

const char aWarning_80074A24[] = "\202v\202\201\202\222\202\216\202\211\202\216\202\207"; // Warning
const char aThisDemoVersion_80074A34[] = "\202s\202\210\202\211\202\223\201@\202\204\202\205\202\215\202\217\201@\202\226\202\205\202\222\202\223\202\211\202\217\202\216\201@\202\217\202\206\201@\202i\202\201\202\204\202\205\201@\202b\202\217\202\203\202\217\202\217\202\216\201@\202\211\202\223\201@\202\223\202\224\202\211\202\214\202\214"; // This demo version of Jade Cocoon is still
const char aInDevelopment_80074A88[] = "\202\211\202\216\201@\202\204\202\205\202\226\202\205\202\214\202\217\202\220\202\215\202\205\202\216\202\224\201D"; // in development.
const char aDueToFutureChanges_80074AA8[] = "\202c\202\225\202\205\201@\202\224\202\217\201@\202\206\202\225\202\224\202\225\202\222\202\205\201@\202\215\202\217\202\204\202\211\202\206\202\211\202\203\202\201\202\224\202\211\202\217\202\216\202\223\201@\202\201\202\216\202\204\201@\202\203\202\210\202\201\202\216\202\207\202\205\202\223\201C\201@\202\211\202\224\201@\202\215\202\201\202\231\201@\202\202\202\205"; // Due to future modifications and changes, it may be
const char aSignificantlyDifferent_80074B10[] = "\202\223\202\211\202\207\202\216\202\211\202\206\202\211\202\203\202\201\202\216\202\224\202\214\202\231\201@\202\204\202\211\202\206\202\206\202\205\202\222\202\205\202\216\202\224\201@\202\206\202\222\202\217\202\215\201@\202\224\202\210\202\205\201@\202\222\202\205\202\224\202\201\202\211\202\214\201@\202\226\202\205\202\222\202\223\202\211\202\217\202\216\201D"; // significantly different from the retail version.

extern int geomScreenDistance_8008B548;
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
    titleMenuState_8008B558[1] = 0;
}

void LoadPublicTiyAndFtg_800407D0(void)
{
    int* pFile = Data001Reader_LoadIntoGlobal_8003CB40(9);
    numFilesInsideTiy_8008B4BC = GetTiyFileCount_80028E68(pFile);
    LoadTiy_80028E74(&publicTiySprts_8008D434, &publicTiyPolyFT4s_8008D430, &publicTiyTPages_8008D440, pFile, 1);
    pFile = Data001Reader_LoadIntoGlobal_8003CB40(10);
    AllocFtgObjects_80021744(&publicFtg_8008D4D0, GetFtgObjectCount_80021738(pFile), 1);
    LoadFtgObjects_80021824(pFile, publicFtg_8008D4D0, GetFtgObjectCount_80021738(pFile), 1, 0);
    LoadSound_80030A84(0, &systemSound_80091D40);
    InitFonts_8003DA70();
}
void ReloadPublicTiy_80040898(void)
{
    void* pFile = Data001Reader_LoadIntoGlobal_8003CB40(9);
    numFilesInsideTiy_8008B4BC = GetTiyFileCount_80028E68((int*)pFile);
    LoadTiy_80028E74(0, 0, 0, pFile, 1);
    InitFonts_8003DA70();
}


void DrawCopyrightScreen_800408F4(void)
{
    if ((unsigned int)frameCount_8008D3FC < 0x190)
    {
        int i;
        SPRT* sprts = copyrightSprts_8008D47C;
        sprts[0].x0 = 0;
        sprts[0].y0 = 0;
        sprts[1].x0 = 0x100;
        sprts[1].y0 = 0;
        sprts[2].x0 = 0x200;
        sprts[2].y0 = 0;
        sprts[3].x0 = 0;
        sprts[3].y0 = 0x100;
        sprts[4].x0 = 0x100;
        sprts[4].y0 = 0x100;
        sprts[5].x0 = 0x200;
        sprts[5].y0 = 0x100;
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
void InitCopyrightScreen_80040A10(int* entry)
{
    void* pFile = DATA_GetFileBuffer_8003CAA0(0x38);
    copyrightSprts_8008D47C = 0;
    copyrightTPages_8008B4EC = 0;
    LoadTiy_80028E74(&copyrightSprts_8008D47C, 0, &copyrightTPages_8008B4EC, pFile, 1);
    free3_8003FC6C(pFile);
    entry[2] = (int)DrawCopyrightScreen_800408F4;
}
void ShowCopyright_80040A84(void)
{
    EndFade_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(copyright_80086948);
}
void PlayGenkiMovie_80040AC4(void)
{
    PlayMovie_80040EB4(0);
    bStopDrawingMovie_8008D45C = 1;
}
void PlayGenkiMovie_80040AEC(void)
{
    EndFade_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(genkiMovie_80086968);
}
void PlayCraveMovie_80040B2C(void)
{
    PlayMovie_80040EB4(0x19);
    bStopDrawingMovie_8008D45C = 1;
}
void PlayCraveEntertainmentMovie_80040B54(void)
{
    EndFade_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(craveEntertainmentMovie_80086988);
}
extern const char aWarning_80074A24[];
extern const char aThisDemoVersion_80074A34[];
extern const char aInDevelopment_80074A88[];
extern const char aDueToFutureChanges_80074AA8[];
extern const char aSignificantlyDifferent_80074B10[];

void DrawDemoDisclaimer_80040B94(void)
{
    if ((unsigned int)frameCount_8008D3FC < 0xC8)
    {
        short linePos0[2];
        short linePos1[2];
        short linePos2[2];
        short linePos3[2];
        short linePos4[2];
        linePos0[0] = 0x10;
        linePos0[1] = 0xA2;
        DrawText_8003E91C(2, aWarning_80074A24, linePos0, 0);
        linePos1[0] = 0x10;
        linePos1[1] = 0xAE;
        DrawText_8003E91C(2, aThisDemoVersion_80074A34, linePos1, 0);
        linePos2[0] = 0x10;
        linePos2[1] = 0xBA;
        DrawText_8003E91C(2, aInDevelopment_80074A88, linePos2, 0);
        linePos3[0] = 0x10;
        linePos3[1] = 0xC6;
        DrawText_8003E91C(2, aDueToFutureChanges_80074AA8, linePos3, 0);
        linePos4[0] = 0x10;
        linePos4[1] = 0xD2;
        DrawText_8003E91C(2, aSignificantlyDifferent_80074B10, linePos4, 0);
    }
    else
    {
        bStopDrawingMovie_8008D45C = 1;
    }
}

EventDesc* copyright_80086948[2] = { &copyrightData_80086930 };
EventDesc genkiMovieData_80086950 = { 1, 1, 0, 0, (EventEntryFn)PlayGenkiMovie_80040AC4 };
EventDesc* genkiMovie_80086968[2] = { &genkiMovieData_80086950 };
EventDesc craveEntertainmentData_80086970 = { 1, 1, 0, 0, (EventEntryFn)PlayCraveMovie_80040B2C };
EventDesc* craveEntertainmentMovie_80086988[2] = { &craveEntertainmentData_80086970 };
EventDesc demoDisclaimerData_80086990 = { 1, 1, 0, 0, (EventEntryFn)DrawDemoDisclaimer_80040B94 };
