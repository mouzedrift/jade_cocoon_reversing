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
#include "model.h"
#include "unit.h"
#include "tiy.h"
#include "camera.h"
#include "main.h"
#include "util.h"
#include "cdread.h"

const char name[] = "cdrom:\\SLUS_008.54;1";
const char aAssertionFaile[] = "Assertion failed: file \"%s\", line %d\n";
const char aMainC[] = "MAIN.C";
// the only .sdata of the game, right behind the PSY-Q .data: the gp base (__SN_GP_BASE) is here; .sbss (linked
// into the data group) follows with 2MBYTE.OBJ's word for the start-up's saved ra, where its bss clear starts
int gpBase_8008B484 SDATA = 0;
long cdRomEventDescError_8008B490 BSS = 0;
long vsyncEventDesc_8008B494 BSS = 0;
int unused_8008B498[2] BSS = { 0 };
unsigned long *decodedImageData_8008B4A0 BSS = 0;
EventNode *gameTask_8008B4A4 BSS = 0;
EventNode *effectObjects_8008B4A8 BSS = 0;
EventNode* taskSlots_8008B4AC[2] BSS = { 0 };
volatile int vsyncCounter_8008B4B4 BSS = 0;
EventNode *configTask_8008B4B8 BSS = 0;
int numFilesInsideTiy_8008B4BC BSS = 0;
EventNode *actionTask_8008B4C0 BSS = 0;
int unused_8008B4C4 BSS = 0;
unsigned long *pOT_8008B4C8 BSS = 0;
EventNode *levantControlTask_8008B4CC BSS = 0;
EventNode *encounterWatchTask_8008B4D0 BSS = 0;
int unused_8008B4D4 BSS = 0;
DisplayConfig display_8008B4D8 BSS = { 0 };
int uiTiyLoaded_8008B4E8 BSS = 0;
DR_TPAGE *copyrightTPages_8008B4EC BSS = 0;
int unused_8008B4F0[2] BSS = { 0 };
int cameraZoom_8008B4F8 BSS = 0;
int unused_8008B4FC BSS = 0;
MapState mapState_8008B500 BSS = { 0 };
int eventDispatchHalt_8008B540 BSS = 0;
EventNode *fileRequestTask_8008B544 BSS = 0;
int geomScreenDistance_8008B548 BSS = 0;
EventNode *modelLoaderTask_8008B54C BSS = 0;
int primBufferOffset_8008B550 BSS = 0;
int encounterVariantToggle_8008B554 BSS = 0;
short titleMenuState_8008B558[2] BSS = { 0 };
int cdReadFlags_8008B55C BSS = 0;
EventNode *xaTask_8008B560 BSS = 0;
EventNode *enemyWindowTasks_8008B564 BSS = 0;
EventNode *enemyWindowsLayoutTask_8008B568 BSS = 0;
int unused_8008B56C BSS = 0;
SaveData saveData_8008B570 BSS = { 0 };
EventNode *storeTask_8008D3E0 BSS = 0;
int dword_8008D3E4[2] BSS = { 0 };
unsigned long *pOT_8008D3EC BSS = 0;
int pointLightRange_8008D3F0 BSS = 0;
DR_TPAGE *uiTiyTPages_8008D3F4 BSS = 0;
EventNode *effectTask_8008D3F8 BSS = 0;
int frameCount_8008D3FC BSS = 0;
EventNode *eventEntities_8008D400 BSS = 0;
volatile int unpausedFrames_8008D404 BSS = 0;
int unused_8008D408 BSS = 0;
int sceneBrightness_8008D40C BSS = 0;
int eventScripts_8008D410[2] BSS = { 0 };
SVECTOR pointLightColor_8008D418 BSS = { 0 };
int viewport_8008D420[2] BSS = { 0 };
unsigned long bDoubleBuffer_8008D428 BSS = 0;
unsigned long *mdecEffectVlcBuffer_8008D42C BSS = 0;
POLY_FT4 *publicTiyPolyFT4s_8008D430 BSS = 0;
SPRT *publicTiySprts_8008D434 BSS = 0;
EventNode *shopCtrlTask_8008D438 BSS = 0;
EventNode *actorTasks_8008D43C BSS = 0;
DR_TPAGE *publicTiyTPages_8008D440 BSS = 0;
EventNode* taskSlot_8008D444 BSS = 0;
unsigned char drawEnvRed_8008D448[3] BSS = { 0 };
int unused_8008D44C BSS = 0;
volatile int xaTimer_8008D450 BSS = 0;
unsigned long *pOT_8008D454 BSS = 0;
EventNode *announcerTasks_8008D458 BSS = 0;
int bStopDrawingMovie_8008D45C BSS = 0;
unsigned char backColor_8008D460[3] BSS = { 0 };
EventNode *sporeTask_8008D464 BSS = 0;
EventNode *battleMenuTask_8008D468 BSS = 0;
EventNode *gameMainTask_8008D46C BSS = 0;
EventNode* idleTask_8008D470 BSS = 0;
ShortPair screenOffset_8008D474 BSS = { 0 };
EventNode* taskSlot_8008D478 BSS = 0;
SPRT *copyrightSprts_8008D47C BSS = 0;
EventNode *loadMenuTask_8008D480 BSS = 0;
EventNode *nameEntryTask_8008D484 BSS = 0;
EventNode *fileRequestTasks_8008D488 BSS = 0;
EventNode* taskSlots_8008D48C[3] BSS = { 0 };
EventNode *fieldMenuTask_8008D498 BSS = 0;
EventNode *enemyAiTasks_8008D49C BSS = 0;
EventNode *cameraTask_8008D4A0 BSS = 0;
EventNode *soundTask_8008D4A4 BSS = 0;
EventNode *shelfMenuTask_8008D4A8 BSS = 0;
unsigned long *pOT_8008D4AC BSS = 0;
EventNode *actorWindowTask_8008D4B0 BSS = 0;
enum GameStates currentGameState_8008D4B4 BSS = 0;
EventNode *vibrationTasks_8008D4B8 BSS = 0;
int prevCameraZoom_8008D4BC BSS = 0;
EventNode *overlayLoaderTask_8008D4C0 BSS = 0;
EventNode *equipTask_8008D4C4 BSS = 0;
SVECTOR cameraRot_8008D4C8 BSS = { 0 };
FtgObject *publicFtg_8008D4D0 BSS = 0;
int unused_8008D4D4 BSS = 0;
int memCardInfo_8008D4D8 BSS = 0;
int minionVariantSeed_8008D4DC BSS = 0;
int unused_8008D4E0[4] BSS = { 0 };
CameraView cameraState_8008D4F0 BSS = { 0 };
unsigned long *pOT_8008D5F4 BSS = 0;
EventNode* taskSlots_8008D5F8[2] BSS = { 0 };
LVec3 cameraEye_8008D600 BSS = { 0 };
EventNode *miscTasks_8008D60C BSS = 0;
volatile int gnFrame_8008D610 BSS = 0;
EventNode *cmdMenuTask_8008D614 BSS = 0;
EventNode *modelTasks_8008D618 BSS = 0;
EventNode *screenFlashTasks_8008D61C BSS = 0;
SPRT *uiTiySprts_8008D620 BSS = 0;
EventNode *battleTask_8008D624 BSS = 0;
EventNode *fadeTask_8008D628 BSS = 0;
EventNode* taskSlot_8008D62C BSS = 0;
int DsReadSyncResult_8008D630 BSS = 0;
int unused_8008D634 BSS = 0;
EventNode *newGameTask_8008D638 BSS = 0;
EventNode *helpWindowTask_8008D63C BSS = 0;
EventNode *messageWindowTask_8008D640 BSS = 0;
int unused_8008D644 BSS = 0;
TileAnimLayers tileAnim_8008D648 BSS = { 0 };
int unused_8008D664 BSS = 0;
short cameraTargetScreenPos_8008D668 BSS = 0;
short cameraTargetScreenY_8008D66A BSS = 0;
int zoomLimit_8008D66C BSS = 0;
EventNode *shopMenuTask_8008D670 BSS = 0;
EventNode *encounterTask_8008D674 BSS = 0;
volatile int unknownFlags_8008D678 BSS = 0;
int unused_8008D67C BSS = 0;
int pointLightPos_8008D680[3] BSS = { 0 };
int unused_8008D68C BSS = 0;
unsigned long *pOT_8008D690 BSS = 0;
int unused_8008D694 BSS = 0;
DRAWENV drawEnv_8008D698[2] BSS = { 0 };
DISPENV dispEnv_8008D750[2] BSS = { 0 };
EventNode *hitNumberTasks_8008D778 BSS = 0;
int unused_8008D77C BSS = 0;
short effectOutcomeFlag_8008D780[2] BSS = { 0 }; // [0]: the outcome is known (1), [1]: the seal result flags
int effectSfxStarted_8008D784 BSS = 0;
unsigned long *pOT_8008D788 BSS = 0;
unsigned long *pOT_8008D78C BSS = 0;
int unused_8008D790[2] BSS = { 0 };
unsigned long OT_8008D798[2][8] BSS = { 0 };
unsigned long OT_8008D7D8[2][1024] BSS = { 0 };
unsigned long OT_8008F7D8[2][1024] BSS = { 0 };
unsigned long OT_800917D8[2][16] BSS = { 0 };
unsigned long OT_80091858[2][1] BSS = { 0 };
int unused_80091860[2] BSS = { 0 };
unsigned long OT_80091868[2][4] BSS = { 0 };
unsigned long OT_80091888[2][4] BSS = { 0 };
unsigned long OT_800918A8[2][1] BSS = { 0 };
int fadeFlags_800918B0 BSS = 0;
int fadeFrame_800918B4 BSS = 0;
int frozenFrames_800918B8 BSS = 0;
int displayStartFrames_800918BC BSS = 0;
int ODEIsEvenAddressDrawn_800918C0 BSS = 0;
int motionBlurOn_800918C4 BSS = 0;
unsigned short padPrevHeld_800918C8[2] BSS = { 0 };
unsigned short padRepeat_800918CC[2] BSS = { 0 };
unsigned short padHeld_800918D0[2] BSS = { 0 };
unsigned short padReleased_800918D4[2] BSS = { 0 };
signed char padAnalog_800918D8[2][4] BSS = { 0 };
unsigned char padAnalogMax_800918E0[2][4] BSS = { 0 };
unsigned char pads_800918E8[2][9] BSS = { 0 };
int unused_800918FC[20] BSS = { 0 };
unsigned short padPressed_8009194C[2] BSS = { 0 };
unsigned short padHoldFrames_80091950[2][16] BSS = { 0 };
List actorHeap_80091990 BSS = { 0 };
int actorHeapPad_8009199C BSS = 0;
ModelAnimRef modelAnimRefs_800919A0[7] BSS = { 0 };
EffectFile effectFile_80091BD0 BSS = { 0 };
int unused_80091C0C BSS = 0;
List eventHeap_80091C10 BSS = { 0 };
int eventHeapPad_80091C1C BSS = 0;
List areaHeap_80091C20 BSS = { 0 };
int areaHeapPad_80091C2C BSS = 0;
int loadFade_80091C30[4] BSS = { 0 };
short areaPreload_80091C40[2] BSS = { 0 };
int currentArea_80091C44 BSS = 0;
List heap_80091C48 BSS = { 0 };
int mapStartMode_80091C54 BSS = 0;
int dword_80091C58 BSS = 0;
int dword_80091C5C BSS = 0;
MapList16 mapSpawns_80091C60 BSS = { 0 };
List mapHeap_80091C68 BSS = { 0 };
int levantAnimSet_80091C74 BSS = 0;
int savedLevantPos_80091C78[4] BSS = { 0 };
int currentAreaMap_80091C88 BSS = 0;
int dword_80091C8C BSS = 0;
int dword_80091C90 BSS = 0;
int useMapStartPos_80091C94 BSS = 0;
int useSavedLevantPos_80091C98 BSS = 0;
int forceMapReload_80091C9C BSS = 0;
int freeActorModels_80091CA0 BSS = 0;
int unused_80091CA4 BSS = 0;
short savedLevantRot_80091CA8[2] BSS = { 0 };
short unused_80091CAC[2] BSS = { 0 };
int mapAreaCount_80091CB0 BSS = 0;
int mapCallback_80091CB4 BSS = 0;
short areaLoadIds_80091CB8[8] BSS = { 0 };
SpuReverbAttr reverbAttr_80091CC8 BSS = { 0 };
int unused_80091CDC BSS = 0;
SoundStruct bgmSound_80091CE0 BSS = { 0 };
int battleMusic_80091CFC BSS = 0;
SoundStruct seqSlotSound_80091D00 BSS = { 0 };
int unused_80091D1C BSS = 0;
SoundStruct sfxSound_80091D20 BSS = { 0 };
int unused_80091D3C BSS = 0;
SoundStruct systemSound_80091D40 BSS = { 0 };
int unused_80091D5C BSS = 0;
char SEQDataAttributeTable_80091D60[(176 * 5) * 16] BSS = { 0 };
PadVibration padVibration_80095460[2] BSS = { 0 };
EffectFile battleEffectFile_80095468 BSS = { 0 };
int unused_800954A4 BSS = 0;
DslFILE Data001File_800954A8 BSS = { 0 };
unsigned char fileRequestParams_800954C0[20][0x64] BSS = { 0 };
FileRequest fileRequests_80095C90[0x14] BSS = { 0 };
Font fonts_80095FB0[3] BSS = { 0 };
short unused_80096034 BSS = 0;
short unused_80096036 BSS = 0;
int textNumberArgs_80096038[22] BSS = { 0 };
List defaultAllocList_80096090 BSS = { 0 };
int defaultAllocListPad_8009609C BSS = 0;

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
    ListInit_8003FDB0(&defaultAllocList_80096090);
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
