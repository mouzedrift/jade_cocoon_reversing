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

#if 0
void sub_80040718(void)
{
}
#endif
INCLUDE_ASM(sub_80040718);
#if 0
void LoadPublicTiyAndFtg_800407D0(void)
{
}
#endif
INCLUDE_ASM(LoadPublicTiyAndFtg_800407D0);
// Matched
void sub_80040898(void)
{
    void* pFile = Data001Reader_LoadIntoGlobal_8003CB40(9);
    numFilesInsideTiy_8008B4BC = GetTiyFileCount_80028E68((int*)pFile);
    sub_80028E74(0, 0, 0, (int)pFile, 1);
    sub_8003DA70();
}
INCLUDE_ASM(sub_800408F4);
INCLUDE_ASM(sub_80040A10);
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
