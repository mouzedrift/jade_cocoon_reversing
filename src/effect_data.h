#ifndef _TU_80014954_H_
#define _TU_80014954_H_
#include "actor.h"
#include "engine.h"
#include "menu_draw.h"

// the files the overlays are loaded from, and where their addresses go
typedef struct
{
    int fileIdx;
    unsigned int* const* ppDest;
} OverlayEntry;
extern OverlayEntry overlays_8007D9E8[];


// camera offsets (camera)
typedef struct
{
    short x0;
    short y0;
    short z0;
    short pad_6;
    int geomScreen_8; // projection distance
    short x1;
    short y1;
    short z1;
    short pad_12;
} CamOffset;

// a step of a pad vibration pattern (vibrationPatterns_80083B30, camera)
typedef struct
{
    unsigned short frames_0; // how long the step lasts (negative: the pattern ends)
    unsigned char motor0_2;  // actuator values (PadVibration.motor_2)
    unsigned char motor1_3;
} PadVibEntry;

typedef struct
{
    unsigned short x;
    unsigned short y;
} Pos16;

extern int commandScriptData_80079754[182];
extern int commandScriptData_80079A2C[37];
extern int commandScriptData_80079AC0[33];
extern int commandScriptData_80079B44[10];
extern int commandScriptData_80079B6C[38];
extern int commandScriptData_80079C04[55];
extern int commandScriptData_80079CE0[65];
extern int commandScriptData_80079DE4[91];
extern int commandScriptData_80079F50[53];
extern ActorScriptCmd* commandScripts_8007A024[];
extern int elementBonusMagic1_8007A67C[];
extern int elementBonusMagic2_8007A68C[];
extern int elementBonusMagic3_8007A69C[];
extern signed char elementModifiers_8007BA74[16];
extern unsigned char speciesModifiers_8007BA84[];
extern MATRIX defaultLightMatrix_8007C2EC; // default scene light direction (row 0)
extern MATRIX defaultColorMatrix_8007C30C; // default scene light colour (column 0)
extern int defaultAmbientColor_8007C32C;
extern void* defaultLightTable_8007C330[6];
extern short screenModes_8007C728[][2];
extern SoundCue soundCues_8007C750[];
extern short levelSeqsCue2_8007CAC0[];
extern short levelSeqsCue3_8007CACC[];
extern char* (*nameGetters_8007CB08[])(int id);
extern ActorScriptCmd moveToScript_8007D95C[];
extern ActorScriptCmd moveToScriptAlt_8007D980[];
extern ActorScriptCmd playAnimScript_8007D9A4[];
extern int unused_8007D9BC;
extern ActorScriptCmd playQueuedAnimScript_8007D9C0[];
extern int unused_8007D9E4;
extern unsigned short actorImageRect_8007DC8C[4];
extern unsigned short actorClutPos_8007DC94[2];
extern unsigned short modelDescData_8007DCCC[9216];
extern int mapJustLoaded_80082668;
extern int mapHasCode_8008266C;
extern int* mapAreas_80082674;
extern int unused_8008267C;
extern unsigned char largeDigitColors_800826F8[4][4];
extern short scrollArrowIcons_8008279C[];
extern int elementIcons_800827BC[];
extern int elementIconsUnlit_800827D0[];
extern int unused_800827E0;
extern char portraitWindowRect_800827E4[];
extern unsigned short portraitWindowPos_800827EC[];
extern unsigned char abilityIconsNoType_800827F0[];
extern int abilityTypeIcons_800827F8[5];
extern unsigned char* abilityIconsByType_8008280C[];
extern short itemScrollUpPos_80082820[2];
extern short itemScrollDownPos_80082824[2];
extern MenuWindowItem itemListRowItems_80082828[4][4];
extern MenuWindowItem* itemListRows_800829E8[];
extern unsigned short magicScrollUpPos_800829FC[];
extern unsigned short magicScrollDownPos_80082A00[];
extern MenuWindowItem magicListRowItems_80082A04[4][3];
extern MenuWindowItem* magicListRows_80082B54[];
extern MenuWindowItem abilityListRowItems_80082B68[5][4];
extern MenuWindowItem* abilityListRows_80082D98[];
extern int aKumu[3];
extern int familyTreeBoxPosData_80082DBC[4];
extern Pos16* familyTreeBoxPos_80082DCC[7];
extern Pos16 familyTreeLineFrom_80082DE8[12];
extern Pos16 familyTreeLineTo_80082E18[12];
extern int aNrdmnrdm[4];
extern int partyWindowRectData_80082E58[14];
extern RECT* partyWindowRects_80082E90[];
extern unsigned char statGridOuterColor_80082E9C[];
extern unsigned char statGridInnerColor_80082EA0[];
extern unsigned char elementChartIcons_80082EA4[];
extern unsigned char elementChartColors_80082EA8[][4];
extern unsigned char elementChartOrder_80082EB8[];
extern unsigned char statIcons_80082EBC[];
extern char* rankNames_80082EC4[];
extern char* developerRankName_80082EE4;
extern unsigned char statRowY_80082EE8[];
extern unsigned char elementChartSizes_80082EF0[];
extern unsigned char levantStatRowY_80082F04[];
extern const char* abilityNames_800834E4[];
extern const char* abilityBonusNames_80083580[];
extern int mapListAny_80083784;
extern int mapListData_80083788[15];
extern void *mapLists0_800837C4[5];
extern unsigned char* mapLists4_800837D8;
extern void *unused_800837DC[4];
extern void *mapLists5_800837EC[5];
extern unsigned char** mapListTable_80083800[];
extern char* itemMessageSuffixes_80083818[];
extern char* itemMessageDefaultSuffix_80083820;
extern const char *unused_80083824[8];
extern unsigned char padActAlign_80083844[];
extern int vibrationPatternData_8008384C[185];
extern PadVibEntry* vibrationPatterns_80083B30[];
extern signed char cameraShakeOffsets_80083BD4[];
extern CamOffset battleCamIntroPresets_80083BE4[];
extern CamOffset battleCamPresets_80083C0C[];
extern CamOffset battleCamFocusPresets_80083C70[];
extern unsigned short battleCamFocusIndex_80083CE8[][4];
extern int battleCamSpline0_80083D00[];
extern int battleCamSpline1_80084330[];
extern short battleCamSpline1Tail_80084350[];

extern void (*polyFT4Transforms_80083768[7])();

void SpawnEffectObject_800149A4(EffectArgs* args);
void EffectObjectTask_80015478(EventEntry* entry, void* buf);
void StartEffect_8001497C(void);
int IsEffectReady_80014954(void);
extern ModelVramSlot vramSlots_8007DB30[2];
extern ModelVramSlot vramSlots_8007DB50[5];
extern ModelVramSlot vramSlots_8007DBA0[4];
extern ModelVramSlot vramSlots_8007DBE0[4];
extern ModelVramSlot vramSlots_8007DC20[4];
extern ModelList* gameModelList_8007DC60;
extern ModelVramSlot* gameModelVramSlots_8007DC6C;
extern ModelVramSlot* modelLoaderVram_8007DC70;
extern ModelVramSlot* modelVramSlotLists_8007DC74[3];
extern RECT tintImageRect_8007DC80;
extern short tintClutRect_8007DC88[2];
#endif
