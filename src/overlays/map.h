// MAP.BIN: declarations shared by its source files
#ifndef _MAP_H_
#define _MAP_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

// a destination of a map area (MapRow.dests_14[])
typedef struct MapElem
{
    int sprite_0; // areaSprts_800B931C / areaTPages_800B9320 index of its picture
    short x_4;
    short y_6;
    int marker_8; // index of its blinking marker sprite
    short x_C;
    short y_E;
    unsigned char c0_10[4]; // the marker's PulseColor_80033394 colors
    unsigned char c1_14[4];
    int file_18; // the destination's picture, shown when it is picked
} MapElem;

// a map area (village / forest): its picture files, name, music and destinations
typedef struct MapRow
{
    int bgFile_0;     // the area picture (areaBgSprts_800B9314)
    int spritesFile_4; // the destination pictures and markers (areaSprts_800B931C)
    const char* name_8; // the area name, centred on x_C
    short x_C;
    short y_E;
    int music_10;
    MapElem* dests_14;
} MapRow;

typedef struct MapPos
{
    short a;
    short b;
} MapPos;

// a menu cursor (UpdateMenuCursor_8003D794 / GetMenuCursorIndex_8003DA54)
typedef struct MapSel
{
    short cols_0;
    short rows_2;
    short count_4;
    short flags_6; // 0x40: scrolls
    short index_8; // on screen
    short scroll_A;
} MapSel;

typedef struct MapSelState
{
    int step_0;
    int area_4;
    int map_8;
    int entry_C;
} MapSelState;

// a menu item drawn by DrawMenuWindows_8002A5A4 (DrawMenuWindowContents_8002A710)
typedef struct MapItem
{
    unsigned short flags_0; // 1: ends the row
    unsigned short type_2;  // 3: text (font 2)
    const char* text_4;
    SPRT** sprts_8;
    DR_TPAGE** tpages_C;
    short x_10; // the window rect
    short y_12;
    short w_14;
    short h_16;
    short mx_18;
    short my_1A;
} MapItem;

// a menu row: one item and the end marker
typedef struct MapWin
{
    MapItem items[2];
} MapWin;

// a window list drawn by DrawMenuWindows_8002A5A4
typedef struct MapMenu
{
    int flags_0;
    int time_4;
    int anim_8;
    int sel_C;
    MapWin** windows_10; // NULL terminated
    int ot_14;
} MapMenu;

extern int dword_800B66C0;
extern const char aParelForest_800B66C4[];
extern const char aSyrus_800B66E0[12];
extern const char aForestGates_800B66EC[28];
extern const char aVillageSquare_800B6708[32];
extern const char aCemetery_800B6728[20];
extern const char aWenSHome_800B673C[24];
extern const char aMusaSHome_800B6754[24];
extern const char aNamSHome_800B676C[24];
extern const char aWatchtower_800B6784[24];
extern const char aSilkMill_800B679C[20];
extern const char aChiefSEstate_800B67B0[32];
extern const char aTownShop_800B67D0[20];
extern const char aBlacksmith_800B67E4[24];
extern const char aGaraiSHome_800B67FC[28];
extern const char aMyHome_800B6818[16];
extern const char aMothForest_800B6828[24];
extern const char aSpiderForest_800B6840[28];
extern const char aDragonflyForest_800B685C[36];
extern const char aBeetleForest_800B6880[28];
extern const char aBarrierGate_800B689C[28];
extern const MapWin destListRow0_800B68B8;
extern const MapWin destListRow1_800B68F0;
extern const MapWin destListRow2_800B6928;
extern const MapMenu menuTemplate_800B6960;
extern const char aProceed_800B6978[];
extern const char aYes_800B698C[];
extern const MapWin yesRow_800B6994;
extern const char aNo_800B69CC[];
extern const MapWin noRow_800B69D4;
extern const char aField2_800B6A0C[16];
extern const char aField1_800B6A1C[16];
extern const char aSyrus3_800B6A2C[16];
extern const char aSyrus2_800B6A3C[16];
extern const char aSyrus1_800B6A4C[16];
extern const char aOthers_800B6A5C[16];
extern const char aClear_800B6A6C[12];
extern const char aHunting_800B6A78[16];
extern const char aDream_800B6A88[12];
extern const char aDummy_800B6A94[12];
extern const char aOpening_800B6AA0[16];
extern const char aGuen_800B6AB0[12];
extern const char aMussa_800B6ABC[12];
extern const char aNam_800B6AC8[8];
extern const char aHiroba_800B6AD0[16];
extern const char aHakaba_800B6AE0[16];
extern const char aZokuchou_800B6AF0[20];
extern const char aMihari_800B6B04[16];
extern const char aMayu_800B6B14[12];
extern const char aDougu_800B6B20[12];
extern const char aKaji_800B6B2C[12];
extern const char aGarai_800B6B38[12];
extern const char aLebant_800B6B44[16];
extern const char aGa_800B6B54[8];
extern const char aKumo_800B6B5C[12];
extern const char aTombo_800B6B68[12];
extern const char aTamamusi_800B6B74[20];
extern const char aKekkai_800B6B88[16];
extern const char aSelKind_800B6B98[];
extern const char aSelSceneGroup_800B6BAC[];
extern const char aSelScene_800B6BCC[];
extern const char aSelChapter_800B6BE0[28];
extern MapPos lastDest_800B8C94;
extern short destCounts_800B8C98[6];
extern int openDestCount_800B8CA4;
extern MapElem villageDests0_800B8CA8[13];
extern MapElem villageDests1_800B8E14[13];
extern MapElem forestDests0_800B8F80[6];
extern MapElem forestDests1_800B9028[6];
extern MapElem forestDests2_800B90D0[6];
extern MapElem forestDests3_800B9178[6];
extern MapRow mapAreas_800B9220[6];
extern char *villageDestNames_800B92B0[13];
extern char *forestDestNames_800B92E4[6];
extern char **destNames_800B92FC[6];
extern SPRT *areaBgSprts_800B9314;
extern DR_TPAGE *areaBgTPages_800B9318;
extern SPRT *areaSprts_800B931C;
extern DR_TPAGE *areaTPages_800B9320;
extern MapSel confirmCursor_800B9324;
extern unsigned char villageDestMaps_800B9330[16];
extern unsigned char forestDestMaps_800B9340[8];
extern unsigned char *destMaps_800B9348[6];
extern unsigned char areaMapGroups_800B9360[8];
extern unsigned char destMapCounts_800B9368[8];
extern char *debugGroupNames_800B9370[6];
extern char *debugSceneNames0_800B9388[5];
extern char *debugSceneNames1_800B939C[12];
extern char *debugSceneNames2_800B93CC[5];
extern char **debugSceneNames_800B93E0[6];
extern unsigned char debugGroupVariants_800B93F8[8];
extern FileRequestDesc mapFileRequest_800B9400[1];
extern MapSelState sceneSelect_800B9420;
extern int mapFileLoaded_800B9430;
extern int mapFileStage_800B9434;
extern int chapterSel_800B9438;

typedef struct MapTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MapTask;

// a map id (area group, map, entry) as GAME's map table lookup sub_800ADC1C takes it
typedef struct MapQuery
{
    short group_0;
    short map_2;
    short entry_4;
} MapQuery;

typedef struct MapEntry
{
    short id;
    char pad_2[14];
} MapEntry;

#endif
