#ifndef _TU_80014954_H_
#define _TU_80014954_H_
#include "actor.h"
#include "engine.h"
#include "menu_draw.h"

// the files the overlays are loaded from, and where their addresses go
typedef struct
{
    int fileIdx;
    unsigned int** ppDest;
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
extern unsigned short actorImageRect_8007DC8C[];
extern short unused_8007DC90;
extern short unused_8007DC92;
extern unsigned short actorClutPos_8007DC94[];
extern int modelDesc341_8007DCCC[38];
extern int modelDesc342_8007DD64[38];
extern int modelDesc343_8007DDFC[31];
extern int modelDesc344_8007DE78[10];
extern int modelDesc345_8007DEA0[73];
extern int modelDesc346_8007DFC4[10];
extern int modelDesc347_8007DFEC[40];
extern int modelDesc348_8007E08C[24];
extern int modelDesc349_8007E0EC[10];
extern int modelDesc34A_8007E114[33];
extern int modelDesc34B_8007E198[109];
extern int modelDesc34C_8007E34C[11];
extern int modelDesc34D_8007E378[53];
extern int modelDesc34E_8007E44C[38];
extern int modelDesc34F_8007E4E4[38];
extern int modelDesc350_8007E57C[25];
extern int modelDesc351_8007E5E0[29];
extern int modelDesc352_8007E654[38];
extern int modelDesc353_8007E6EC[38];
extern int modelDesc354_8007E784[38];
extern int modelDesc355_8007E81C[38];
extern int modelDesc356_8007E8B4[58];
extern int modelDesc357_8007E99C[15];
extern int modelDesc358_8007E9D8[70];
extern int modelDesc359_8007EAF0[38];
extern int modelDesc35A_8007EB88[38];
extern int modelDesc35B_8007EC20[38];
extern int modelDesc35C_8007ECB8[38];
extern int modelDesc35D_8007ED50[38];
extern int modelDesc35E_8007EDE8[38];
extern int modelDesc35F_8007EE80[38];
extern unsigned char modelDesc360_8007EF18[152];
extern unsigned char modelDesc361_8007EFB0[152];
extern unsigned char modelDesc362_8007F048[152];
extern unsigned char modelDesc363_8007F0E0[152];
extern int modelDesc364_8007F178[38];
extern unsigned char modelDesc365_8007F210[88];
extern int modelDesc366_8007F268[103];
extern int modelDesc367_8007F404[10];
extern int modelDesc340_8007F42C[117];
extern int modelDesc33F_8007F600[529];
extern int modelDesc368_8007FE44[313];
extern int modelDesc369_80080328[38];
extern int modelDesc36A_800803C0[38];
extern int modelDesc36B_80080458[64];
extern unsigned char modelDesc36C_80080558[108];
extern unsigned char modelDesc36D_800805C4[84];
extern unsigned char modelDesc36E_80080618[192];
extern unsigned char modelDesc36F_800806D8[32];
extern int aHp[2];
extern int modelDesc370_80080700[26];
extern int modelDesc371_80080768[21];
extern int modelDesc372_800807BC[34];
extern int modelDesc373_80080844[38];
extern int modelDesc374_800808DC[15];
extern int modelDesc375_80080918[42];
extern int modelDesc376_800809C0[32];
extern int aL[2];
extern int modelDesc377_80080A48[22];
extern int modelDesc378_80080AA0[60];
extern int modelDesc379_80080B90[54];
extern int modelDesc37A_80080C68[18];
extern int modelDesc37B_80080CB0[50];
extern int modelDesc37C_80080D78[68];
extern int modelDesc37D_80080E88[33];
extern int modelDesc37E_80080F0C[17];
extern int modelDesc37F_80080F50[69];
extern int modelDesc380_80081064[11];
extern int modelDesc381_80081090[50];
extern int modelDesc382_80081158[38];
extern int modelDesc383_800811F0[38];
extern int modelDesc384_80081288[38];
extern int modelDesc385_80081320[38];
extern int modelDesc386_800813B8[9];
extern int modelDesc387_800813DC[13];
extern int modelDesc388_80081410[42];
extern int modelDesc389_800814B8[74];
extern int modelDesc38A_800815E0[16];
extern int modelDesc38B_80081620[65];
extern int modelDesc38C_80081724[76];
extern int modelDesc38E_80081854[8];
extern int modelDesc38F_80081874[20];
extern int modelDesc390_800818C4[50];
extern int modelDesc391_8008198C[38];
extern int modelDesc392_80081A24[38];
extern int modelDesc393_80081ABC[38];
extern int modelDesc394_80081B54[38];
extern int modelDesc395_80081BEC[38];
extern int modelDesc396_80081C84[38];
extern int modelDesc397_80081D1C[38];
extern int modelDesc398_80081DB4[38];
extern int modelDesc399_80081E4C[38];
extern int modelDesc39A_80081EE4[38];
extern int modelDesc39B_80081F7C[38];
extern int modelDesc39C_80082014[38];
extern int modelDesc39D_800820AC[18];
extern int modelDesc39E_800820F4[40];
extern int aSE[4];
extern int modelDesc39F_800821A4[12];
extern int aXB[3];
extern int modelDesc3A0_800821E0[47];
extern unsigned char modelDesc3A1_8008229C[152];
extern unsigned char modelDesc3A2_80082334[108];
extern unsigned char modelDesc3A3_800823A0[72];
extern int modelDesc3A4_800823E8[38];
extern unsigned char modelDesc3A5_80082480[76];
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
extern int itemListRowData_80082828[11];
extern int aH6p[14];
extern int itemListRowData_8008288C[14];
extern int aH6p_0[14];
extern int itemListRowData_800828FC[14];
extern int aH6p_1[14];
extern int itemListRowData_8008296C[14];
extern int aH6p_2[17];
extern MenuWindowItem* itemListRows_800829E8[];
extern unsigned short magicScrollUpPos_800829FC[];
extern unsigned short magicScrollDownPos_80082A00[];
extern int magicListRowData_80082A04[11];
extern int aU6k[7];
extern int magicListRowData_80082A4C[14];
extern int aU6k_0[7];
extern int magicListRowData_80082AA0[14];
extern int aU6k_1[7];
extern int magicListRowData_80082AF4[14];
extern int aU6k_2[10];
extern MenuWindowItem* magicListRows_80082B54[];
extern int abilityListRowData_80082B68[4];
extern int a8[21];
extern int abilityListRowData_80082BCC[7];
extern int a8_0[21];
extern int abilityListRowData_80082C3C[7];
extern int a8_1[21];
extern int abilityListRowData_80082CAC[7];
extern int a8_2[21];
extern int abilityListRowData_80082D1C[7];
extern int a8_3[24];
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
