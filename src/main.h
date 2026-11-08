#ifndef _MAIN_H_
#define _MAIN_H_
#include "globals.h"
#include "model.h"
#include "util.h"

extern int gpBase_8008B484;
extern int unused_8008B498[2];
extern EventNode* gameTask_8008B4A4;
extern EventNode* taskSlots_8008B4AC[2];
extern EventNode* configTask_8008B4B8;
extern EventNode* actionTask_8008B4C0;
extern int unused_8008B4C4;
extern EventNode* levantControlTask_8008B4CC;
extern EventNode* encounterWatchTask_8008B4D0;
extern int unused_8008B4D4;
extern DR_TPAGE* copyrightTPages_8008B4EC;
extern int unused_8008B4F0[2];
extern int unused_8008B4FC;
extern EventNode* fileRequestTask_8008B544;
extern int encounterVariantToggle_8008B554;
extern EventNode* enemyWindowTasks_8008B564;
extern EventNode* enemyWindowsLayoutTask_8008B568;
extern int unused_8008B56C;
extern EventNode* storeTask_8008D3E0;
extern int dword_8008D3E4[2];
extern int pointLightRange_8008D3F0;
extern EventNode* eventEntities_8008D400;
extern int unused_8008D408;
extern int eventScripts_8008D410[2];
extern SVECTOR pointLightColor_8008D418; // colour of the global point light
extern EventNode* shopCtrlTask_8008D438;
extern EventNode* taskSlot_8008D444;
extern int unused_8008D44C;
extern EventNode* announcerTasks_8008D458;
extern unsigned char backColor_8008D460[3];
extern EventNode* battleMenuTask_8008D468;
extern EventNode* gameMainTask_8008D46C; // the GAME main task (GameMainInit_800A68CC)
extern EventNode* idleTask_8008D470;
extern SPRT* copyrightSprts_8008D47C;
extern EventNode* loadMenuTask_8008D480;
extern EventNode* nameEntryTask_8008D484;
extern EventNode* fileRequestTasks_8008D488;
extern EventNode* taskSlots_8008D48C[3];
extern EventNode* fieldMenuTask_8008D498;
extern EventNode* enemyAiTasks_8008D49C;
extern EventNode* shelfMenuTask_8008D4A8;
extern EventNode* actorWindowTask_8008D4B0;
extern EventNode* vibrationTasks_8008D4B8;
extern int prevCameraZoom_8008D4BC;
extern EventNode* equipTask_8008D4C4;
extern SVECTOR cameraRot_8008D4C8;
extern int unused_8008D4D4;
extern int unused_8008D4E0[4];
extern EventNode* taskSlots_8008D5F8[2];
extern EventNode* cmdMenuTask_8008D614;
extern EventNode* battleTask_8008D624;
extern EventNode* taskSlot_8008D62C;
extern int unused_8008D634;
extern EventNode* newGameTask_8008D638;
extern EventNode* helpWindowTask_8008D63C;
extern EventNode* messageWindowTask_8008D640;
extern int unused_8008D644;
extern TileAnimLayers tileAnim_8008D648;
extern int unused_8008D664;
extern short cameraTargetScreenY_8008D66A;
extern int zoomLimit_8008D66C;
extern EventNode* shopMenuTask_8008D670;
extern EventNode* encounterTask_8008D674;
extern int unused_8008D67C;
extern int pointLightPos_8008D680[3]; // position of the global point light
extern int unused_8008D68C;
extern int unused_8008D694;
extern DRAWENV drawEnv_8008D698[2];
extern DISPENV dispEnv_8008D750[2];
extern EventNode* hitNumberTasks_8008D778;
extern int unused_8008D77C;
extern int effectSfxStarted_8008D784;
extern int unused_8008D790[2];
extern int unused_80091860[2];
extern unsigned short padPrevHeld_800918C8[];
extern unsigned short padRepeat_800918CC[];
extern unsigned short padReleased_800918D4[];
extern signed char padAnalog_800918D8[][4];
extern unsigned char padAnalogMax_800918E0[][4];
extern int unused_800918FC[20];
extern unsigned short padPressed_8009194C[];
extern unsigned short padHoldFrames_80091950[][16];
extern int unused_80091C0C;
extern List actorHeap_80091990;
extern List eventHeap_80091C10;
extern List areaHeap_80091C20;
extern List mapHeap_80091C68;
extern List defaultAllocList_80096090;
extern List heap_80091C48;
extern int mapStartMode_80091C54;
extern int dword_80091C58;
extern int dword_80091C5C;
extern int levantAnimSet_80091C74;
extern int dword_80091C8C;
extern int dword_80091C90;
extern int useMapStartPos_80091C94;
extern int useSavedLevantPos_80091C98;
extern int forceMapReload_80091C9C;
extern int unused_80091CA4;
extern short savedLevantRot_80091CA8[];
extern short unused_80091CAC[2];
extern int mapAreaCount_80091CB0;
extern short areaLoadIds_80091CB8[];
extern SpuReverbAttr reverbAttr_80091CC8;
extern int unused_80091CDC;
extern int unused_80091D1C;
extern int unused_80091D3C;
extern int unused_80091D5C;
extern int unused_800954A4;
/* a copy of each file request's parameters (FileRequestDesc.params_14), up to FILE_REQUEST_PARAMS bytes */
#ifdef __psyz
#define FILE_REQUEST_PARAMS 0xC8
#else
#define FILE_REQUEST_PARAMS 0x64
#endif
extern unsigned char fileRequestParams_800954C0[][FILE_REQUEST_PARAMS];
extern short unused_80096034;
extern short unused_80096036;
extern int textNumberArgs_80096038[];

#endif
