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
#include "tu_8001EA48.h"
#include "unit.h"
#include "tiy.h"
#include "tu_80036528.h"
#include "main.h"

const char name[] = "cdrom:\\SLUS_008.54;1";
const char aAssertionFaile[] = "Assertion failed: file \"%s\", line %d\n";
const char aMainC[] = "MAIN.C";
int dword_8008B484 BSS = 0;
int dword_8008B488[2] BSS = { 0 };
long cdRomEventDescError_8008B490 BSS = 0;
long vsyncEventDesc_8008B494 BSS = 0;
int dword_8008B498[2] BSS = { 0 };
unsigned long *decodedImageData_8008B4A0 BSS = 0;
EventNode *dword_8008B4A4 BSS = 0;
EventNode *effectObjects_8008B4A8 BSS = 0;
int dword_8008B4AC[2] BSS = { 0 };
volatile int vsyncCounter_8008B4B4 BSS = 0;
int dword_8008B4B8 BSS = 0;
int numFilesInsideTiy_8008B4BC BSS = 0;
int dword_8008B4C0[2] BSS = { 0 };
unsigned long *pOT_8008B4C8 BSS = 0;
int dword_8008B4CC[3] BSS = { 0 };
DisplayConfig display_8008B4D8 BSS = { 0 };
int uiTiyLoaded_8008B4E8 BSS = 0;
DR_TPAGE *copyrightTPages_8008B4EC BSS = 0;
int dword_8008B4F0[2] BSS = { 0 };
int dword_8008B4F8 BSS = 0;
int dword_8008B4FC BSS = 0;
MapState dword_8008B500 BSS = { 0 };
int eventDispatchHalt_8008B540 BSS = 0;
EventNode *fileRequestTask_8008B544 BSS = 0;
int geomScreenDistance_8008B548 BSS = 0;
EventNode *modelLoaderTask_8008B54C BSS = 0;
int dword_8008B550 BSS = 0;
int dword_8008B554 BSS = 0;
short word_8008B558[2] BSS = { 0 };
int dword_8008B55C BSS = 0;
EventNode *xaTask_8008B560 BSS = 0;
int dword_8008B564[3] BSS = { 0 };
SaveData saveData_8008B570 BSS = { 0 };
int dword_8008D3E0 BSS = 0;
int dword_8008D3E4[2] BSS = { 0 };
unsigned long *pOT_8008D3EC BSS = 0;
int dword_8008D3F0 BSS = 0;
DR_TPAGE *uiTiyTPages_8008D3F4 BSS = 0;
EventNode *effectTask_8008D3F8 BSS = 0;
int frameCount_8008D3FC BSS = 0;
EventNode *dword_8008D400 BSS = 0;
volatile int dword_8008D404 BSS = 0;
int dword_8008D408 BSS = 0;
int dword_8008D40C BSS = 0;
int dword_8008D410[2] BSS = { 0 };
short word_8008D418 BSS = 0;
short word_8008D41A BSS = 0;
short word_8008D41C[2] BSS = { 0 };
int stru_8008D420[2] BSS = { 0 };
unsigned long bDoubleBuffer_8008D428 BSS = 0;
unsigned long *mdecEffectVlcBuffer_8008D42C BSS = 0;
POLY_FT4 *publicTiyPolyFT4s_8008D430 BSS = 0;
SPRT *publicTiySprts_8008D434 BSS = 0;
int dword_8008D438 BSS = 0;
EventNode *actorTasks_8008D43C BSS = 0;
DR_TPAGE *publicTiyTPages_8008D440 BSS = 0;
int dword_8008D444 BSS = 0;
unsigned char drawEnvRed_8008D448[3] BSS = { 0 };
int dword_8008D44C BSS = 0;
volatile int xaTimer_8008D450 BSS = 0;
unsigned long *pOT_8008D454 BSS = 0;
int dword_8008D458 BSS = 0;
int bStopDrawingMovie_8008D45C BSS = 0;
unsigned char byte_8008D460[3] BSS = { 0 };
EventNode *dword_8008D464 BSS = 0;
int dword_8008D468[3] BSS = { 0 };
int dword_8008D474[2] BSS = { 0 };
SPRT *copyrightSprts_8008D47C BSS = 0;
int dword_8008D480[2] BSS = { 0 };
EventNode *fileRequestTasks_8008D488 BSS = 0;
int dword_8008D48C[4] BSS = { 0 };
EventNode *dword_8008D49C BSS = 0;
EventNode *cameraTask_8008D4A0 BSS = 0;
EventNode *soundTask_8008D4A4 BSS = 0;
int dword_8008D4A8 BSS = 0;
unsigned long *pOT_8008D4AC BSS = 0;
int dword_8008D4B0 BSS = 0;
enum GameStates currentGameState_8008D4B4 BSS = 0;
EventNode *vibrationTasks_8008D4B8 BSS = 0;
int dword_8008D4BC BSS = 0;
EventNode *overlayLoaderTask_8008D4C0 BSS = 0;
int dword_8008D4C4 BSS = 0;
SVECTOR word_8008D4C8 BSS = { 0 };
FtgObject *publicFtg_8008D4D0 BSS = 0;
int dword_8008D4D4 BSS = 0;
int memCardInfo_8008D4D8 BSS = 0;
int dword_8008D4DC BSS = 0;
int dword_8008D4E0[4] BSS = { 0 };
int cameraState_8008D4F0[5] BSS = { 0 };
int stru_8008D504[4] BSS = { 0 };
int dword_8008D514 BSS = 0;
int dword_8008D518 BSS = 0;
short word_8008D51C BSS = 0;
short word_8008D51E BSS = 0;
unsigned char byte_8008D520 BSS = 0;
unsigned char byte_8008D521 BSS = 0;
unsigned char byte_8008D522 BSS = 0;
unsigned char byte_8008D523 BSS = 0;
int dword_8008D524 BSS = 0;
int dword_8008D528 BSS = 0;
int dword_8008D52C BSS = 0;
int dword_8008D530 BSS = 0;
CamEntry stru_8008D534[8] BSS = { 0 };
unsigned long *pOT_8008D5F4 BSS = 0;
int dword_8008D5F8[2] BSS = { 0 };
VECTOR dword_8008D600 BSS = { 0 };
volatile int gnFrame_8008D610 BSS = 0;
int dword_8008D614 BSS = 0;
EventNode *modelTasks_8008D618 BSS = 0;
EventNode *screenFlashTasks_8008D61C BSS = 0;
SPRT *uiTiySprts_8008D620 BSS = 0;
int dword_8008D624 BSS = 0;
EventNode *dword_8008D628 BSS = 0;
int dword_8008D62C BSS = 0;
int DsReadSyncResult_8008D630 BSS = 0;
int dword_8008D634[3] BSS = { 0 };
EventNode *messageWindowTask_8008D640 BSS = 0;
int dword_8008D644 BSS = 0;
struct_8008D648 dword_8008D648 BSS = { 0 };
int dword_8008D664 BSS = 0;
short word_8008D668 BSS = 0;
short word_8008D66A BSS = 0;
int dword_8008D66C BSS = 0;
int dword_8008D670 BSS = 0;
EventNode *dword_8008D674 BSS = 0;
volatile int unknownFlags_8008D678 BSS = 0;
int dword_8008D67C BSS = 0;
int dword_8008D680 BSS = 0;
int dword_8008D684 BSS = 0;
int dword_8008D688[2] BSS = { 0 };
unsigned long *pOT_8008D690 BSS = 0;
int dword_8008D694 BSS = 0;
DRAWENV drawEnv_8008D698[2] BSS = { 0 };
DISPENV dispEnv_8008D750[2] BSS = { 0 };
int dword_8008D778[2] BSS = { 0 };
short effectOutcomeFlag_8008D780 BSS = 0;
int dword_8008D784 BSS = 0;
unsigned long *pOT_8008D788 BSS = 0;
unsigned long *pOT_8008D78C BSS = 0;
int dword_8008D790[2] BSS = { 0 };
unsigned long OT_8008D798[2][8] BSS = { 0 };
unsigned long OT_8008D7D8[2][1024] BSS = { 0 };
unsigned long OT_8008F7D8[2][1024] BSS = { 0 };
unsigned long OT_800917D8[2][16] BSS = { 0 };
unsigned long OT_80091858[2][1] BSS = { 0 };
int dword_80091860[2] BSS = { 0 };
unsigned long OT_80091868[2][4] BSS = { 0 };
unsigned long OT_80091888[2][4] BSS = { 0 };
unsigned long OT_800918A8[2][1] BSS = { 0 };
int fadeFlags_800918B0 BSS = 0;
int fadeFrame_800918B4 BSS = 0;
int dword_800918B8 BSS = 0;
int dword_800918BC BSS = 0;
int ODEIsEvenAddressDrawn_800918C0 BSS = 0;
int dword_800918C4 BSS = 0;
unsigned short padPrevHeld_800918C8[2] BSS = { 0 };
unsigned short padRepeat_800918CC[2] BSS = { 0 };
unsigned short padHeld_800918D0[2] BSS = { 0 };
unsigned short padReleased_800918D4[2] BSS = { 0 };
signed char padAnalog_800918D8[2][4] BSS = { 0 };
unsigned char padAnalogMax_800918E0[2][4] BSS = { 0 };
unsigned char pads_800918E8[2][9] BSS = { 0 };
int dword_800918FC[20] BSS = { 0 };
unsigned short padPressed_8009194C[2] BSS = { 0 };
unsigned short padHoldFrames_80091950[2][16] BSS = { 0 };
int dword_80091990[4] BSS = { 0 };
ModelAnimRef modelAnimRefs_800919A0[7] BSS = { 0 };
EffectFile effectFile_80091BD0 BSS = { 0 };
int dword_80091C0C BSS = 0;
int dword_80091C10 BSS = 0;
int dword_80091C14[3] BSS = { 0 };
int dword_80091C20 BSS = 0;
int dword_80091C24[3] BSS = { 0 };
int dword_80091C30[1] BSS = { 0 };
int dword_80091C34 BSS = 0;
int dword_80091C38 BSS = 0;
int dword_80091C3C BSS = 0;
short word_80091C40[2] BSS = { 0 };
int dword_80091C44 BSS = 0;
int dword_80091C48 BSS = 0;
int dword_80091C4C[2] BSS = { 0 };
int dword_80091C54 BSS = 0;
int dword_80091C58 BSS = 0;
int dword_80091C5C BSS = 0;
MapList16 dword_80091C60 BSS = { 0 };
int dword_80091C68[3] BSS = { 0 };
int dword_80091C74 BSS = 0;
int stru_80091C78[4] BSS = { 0 };
int dword_80091C88 BSS = 0;
int dword_80091C8C BSS = 0;
int dword_80091C90 BSS = 0;
int dword_80091C94 BSS = 0;
int dword_80091C98 BSS = 0;
int dword_80091C9C BSS = 0;
int dword_80091CA0 BSS = 0;
int dword_80091CA4 BSS = 0;
short dword_80091CA8[2] BSS = { 0 };
short word_80091CAC[2] BSS = { 0 };
int dword_80091CB0 BSS = 0;
int dword_80091CB4 BSS = 0;
short word_80091CB8[2] BSS = { 0 };
short word_80091CBC BSS = 0;
short word_80091CBE BSS = 0;
short word_80091CC0 BSS = 0;
short word_80091CC2 BSS = 0;
short word_80091CC4 BSS = 0;
short word_80091CC6 BSS = 0;
SpuReverbAttr reverbAttr_80091CC8 BSS = { 0 };
int dword_80091CDC BSS = 0;
SoundStruct bgmSound_80091CE0 BSS = { 0 };
int dword_80091CFC BSS = 0;
SoundStruct seqSlotSound_80091D00 BSS = { 0 };
int dword_80091D1C BSS = 0;
SoundStruct sfxSound_80091D20 BSS = { 0 };
int dword_80091D3C BSS = 0;
SoundStruct systemSound_80091D40 BSS = { 0 };
int dword_80091D5C BSS = 0;
char SEQDataAttributeTable_80091D60[(176 * 5) * 16] BSS = { 0 };
PadVibration padVibration_80095460[2] BSS = { 0 };
EffectFile dword_80095468 BSS = { 0 };
int dword_800954A4 BSS = 0;
DslFILE Data001File_800954A8 BSS = { 0 };
unsigned char fileRequestParams_800954C0[20][0x64] BSS = { 0 };
FileRequest fileRequests_80095C90[0x14] BSS = { 0 };
Font fonts_80095FB0[1] BSS = { 0 };
int dword_80095FDC BSS = 0;
int dword_80095FE0 BSS = 0;
int dword_80095FE4 BSS = 0;
int dword_80095FE8 BSS = 0;
int dword_80095FEC BSS = 0;
int dword_80095FF0 BSS = 0;
unsigned char byte_80095FF4[2] BSS = { 0 };
unsigned char byte_80095FF6 BSS = 0;
unsigned char byte_80095FF7 BSS = 0;
short word_80095FF8[2] BSS = { 0 };
short word_80095FFC BSS = 0;
short word_80095FFE BSS = 0;
short word_80096000 BSS = 0;
short word_80096002 BSS = 0;
short word_80096004 BSS = 0;
short word_80096006 BSS = 0;
int dword_80096008 BSS = 0;
int dword_8009600C BSS = 0;
int dword_80096010 BSS = 0;
int dword_80096014 BSS = 0;
int dword_80096018 BSS = 0;
int dword_8009601C BSS = 0;
unsigned char byte_80096020[2] BSS = { 0 };
unsigned char byte_80096022 BSS = 0;
unsigned char byte_80096023 BSS = 0;
short word_80096024[2] BSS = { 0 };
short word_80096028 BSS = 0;
short word_8009602A BSS = 0;
short word_8009602C BSS = 0;
short word_8009602E BSS = 0;
short word_80096030 BSS = 0;
short word_80096032 BSS = 0;
short word_80096034 BSS = 0;
short word_80096036 BSS = 0;
int textNumberArgs_80096038[22] BSS = { 0 };
int defaultAllocList_80096090[4] BSS = { 0 };

// Matched
int main(void)
{
    int* pHeapIter;
    unsigned int heapSize;
    unsigned int i;

    InitGame_80010110();
    EnterCriticalSection();
    SetMem(2);

    // calc heap size in multiple of 8
    heapSize = ((0x801B9250 - (unsigned int)heapStart_800CD858));
    heapSize = (heapSize / 8) * 8;

    InitHeap3(heapStart_800CD858, heapSize);

    pHeapIter = heapStart_800CD858;
    for (i = 2; i < (heapSize / 4) - 2; i++)
    {
        pHeapIter[i] = 0x55555555;
    }

    InitEvents_8001028C();
    ExitCriticalSection();
    ListInit_8003FDB0(defaultAllocList_80096090);
    InitImage_80010428();
    SetGameBootState_80040470();
    GameLoop_8004047C();
    EnterCriticalSection();
    CloseEvents_80010328();
    ExitCriticalSection();
    ShutdownSystems_80010228();
    _96_remove();
    _96_init();
    LoadExec(name, 0x801FFFF0, 0);
    exit();
}
// Matched
void InitGame_80010110(void)
{
    ResetCallback();
    SetVideoMode(0);

    if (!DsInit())
    {
        printf(aAssertionFaile, aMainC, 200);
        exit(1);
    }

    LoadData001File_8003CD1C();
    DecDCTReset(0);
    ResetGraph(0);
    InitGeom();
    MemCardInit(1);
    McxStartCom();
    PadInitDirect(pads_800918E8[0], pads_800918E8[1]);
    PadStartCom();
    ChangeClearPAD(0);
    SetGraphDebug(0);
    DsSetDebug(0);
    InitSounds_8002FE7C();
    SsInit();
    SsSetTableSize(SEQDataAttributeTable_80091D60, 5, 16);
    SsSetTickMode(1);
    SsStart2();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 112, 112);
    SsUtSetReverbType(SS_REV_TYPE_STUDIO_C);
    SsUtReverbOn();
}
