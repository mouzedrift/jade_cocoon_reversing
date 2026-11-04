// MAP.BIN: declarations shared by its source files
#ifndef _MAP_H_
#define _MAP_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct MapElem
{
    char pad_0[0x18];
    int f18;
} MapElem;

typedef struct MapRow
{
    int f0;
    int f4;
    int f8;
    int fc;
    int f10;
    MapElem* f14;
} MapRow;

typedef struct MapPos
{
    short a;
    short b;
} MapPos;

typedef struct MapSel
{
    short s0;
    short s2;
    short s4;
    short s6;
    short s8;
    short sA;
} MapSel;

typedef struct MapSelState
{
    int step_0;
    int area_4;
    int map_8;
    int entry_C;
} MapSelState;

typedef struct MapWin
{
    int w[14];
} MapWin;

typedef struct MapMenu
{
    int f0;
    int time_4;
    int f8;
    int sel_C;
    MapWin** windows_10;
    int f14;
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
extern const int dword_800B68B8[14];
extern const int dword_800B68F0[14];
extern const int dword_800B6928[14];
extern const MapMenu name_800B6960;
extern const char name_800B6978[];
extern const char aYes_800B698C[];
extern const MapWin name_800B6994;
extern const char aNo_800B69CC[];
extern const MapWin name_800B69D4;
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
extern const char dword_800B6B98[];
extern const char dword_800B6BAC[];
extern const char dword_800B6BCC[];
extern const char dword_800B6BE0[28];
extern MapPos dword_800B8C94;
extern short word_800B8C98[6];
extern int dword_800B8CA4;
extern MapElem dword_800B8CA8[13];
extern MapElem dword_800B8E14[13];
extern MapElem dword_800B8F80[6];
extern MapElem dword_800B9028[6];
extern MapElem dword_800B90D0[6];
extern MapElem dword_800B9178[6];
extern MapRow dword_800B9220[6];
extern char *dword_800B92B0[13];
extern char *dword_800B92E4[6];
extern char **dword_800B92FC[6];
extern SPRT *dword_800B9314;
extern DR_TPAGE *dword_800B9318;
extern SPRT *dword_800B931C;
extern DR_TPAGE *dword_800B9320;
extern MapSel name_800B9324;
extern unsigned char dword_800B9330[16];
extern unsigned char dword_800B9340[8];
extern unsigned char *dword_800B9348[6];
extern unsigned char dword_800B9360[8];
extern unsigned char dword_800B9368[8];
extern char *dword_800B9370[6];
extern char *dword_800B9388[5];
extern char *dword_800B939C[12];
extern char *dword_800B93CC[5];
extern char **dword_800B93E0[6];
extern unsigned char dword_800B93F8[8];
extern FileRequestDesc dword_800B9400[1];
extern MapSelState dword_800B9420;
extern int dword_800B9430;
extern int dword_800B9434;
extern int dword_800B9438;

#endif
