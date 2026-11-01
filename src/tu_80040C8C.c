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


// Matched
void ShowDemoDisclaimer_80040C8C(void)
{
    sub_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(demoDisclaimer_800869A8);
}
// Matched
void PlayAnimeMovie_80040CCC(void)
{
    sub_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(introAnime_800869C8);
}
// Matched
void PlayAnimeMovie_80040D0C(void)
{
    PlayMovie_80040EB4(1);
    bStopDrawingMovie_8008D45C = 1;
}
// Matched
void sub_80040D34(struct_obj_D* p)
{
    if (!(unknownFlags_8008D678 & 0x20))
    {
        p->field_8 = PlayAnimeMovie_80040D0C;
    }
}
#if 0
int sub_80040D5C(void)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_80040D5C);
#if 0
enum GameStates ExecOverlay_80040DDC(enum OverlayIds overlayId)
{
    return 0;
}
#endif
INCLUDE_ASM(ExecOverlay_80040DDC);
INCLUDE_ASM(sub_80040E28);
#if 0
void PlayMovie_80040EB4(int arg0)
{
}
#endif
INCLUDE_ASM(PlayMovie_80040EB4);
INCLUDE_ASM(sub_80041240);
INCLUDE_ASM(sub_80041358);
INCLUDE_ASM(SkipMovieButtonPressed_800413BC);
INCLUDE_ASM(sub_80041424);
INCLUDE_ASM(sub_800415D8);
INCLUDE_ASM(sub_80041724);
INCLUDE_ASM(sub_800417BC);
// Matched
void AllocMdecVLCBuffer_80041848(void)
{
    if (!mdecVLCBuffer_80086F94)
    {
        mdecVLCBuffer_80086F94 = malloc3_8003FC4C(0x11000);
        DecDCTvlcBuild(mdecVLCBuffer_80086F94);
    }
}
// Matched
void sub_8004188C(void)
{
    if (!mdecVLCBuffer_80086F94)
    {
        mdecVLCBuffer_80086F94 = sub_8003BFB8(1);
        DecDCTvlcBuild(mdecVLCBuffer_80086F94);
    }
}
// Matched
void FreeMdecBuffer_800418CC(void)
{
    free3_8003FC6C(mdecVLCBuffer_80086F94);
    mdecVLCBuffer_80086F94 = 0;
}
// Matched
void sub_800418FC(void)
{
    sub_8003BFB8(0);
    mdecVLCBuffer_80086F94 = 0;
}
INCLUDE_ASM(DecodeMdec_80041920);
INCLUDE_ASM(sub_8004196C);
