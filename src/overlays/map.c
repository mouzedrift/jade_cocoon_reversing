// MAP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "map.h"

#define SEL mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area]

MapDest lastDest_800B8C94 = { -1, -1 };
short destCounts_800B8C98[6] = { 13, 13, 3, 4, 5, 6 };
int openDestCount_800B8CA4 = 0;
MapElem villageDests0_800B8CA8[13] = {
    { 8, 12, 18, 1, 246, 166, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 62 },
    { 6, 12, 18, 1, 182, 201, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 63 },
    { 0, 216, 18, 1, 140, 109, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 64 },
    { 3, 216, 18, 1, 101, 130, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 65 },
    { 4, 216, 18, 1, 64, 90, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 68 },
    { 7, 12, 18, 1, 204, 133, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 66 },
    { 12, 216, 18, 1, 295, 186, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 67 },
    { 9, 12, 18, 1, 184, 116, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 71 },
    { 10, 12, 18, 1, 184, 80, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 72 },
    { 11, 216, 18, 1, 98, 73, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 73 },
    { 13, 12, 18, 1, 243, 87, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 69 },
    { 2, 216, 18, 1, 120, 98, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 70 },
    { 5, 216, 18, 1, 266, 226, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 74 },
};
MapElem villageDests1_800B8E14[13] = {
    { 3, 12, 18, 12, 246, 166, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 77 },
    { 2, 12, 18, 12, 182, 201, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 78 },
    { 8, 216, 18, 12, 140, 109, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 79 },
    { 10, 216, 18, 12, 101, 130, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 80 },
    { 11, 216, 18, 12, 64, 90, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 83 },
    { 1, 12, 18, 12, 204, 133, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 81 },
    { 4, 216, 18, 12, 295, 186, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 82 },
    { 5, 12, 18, 12, 184, 116, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 86 },
    { 6, 12, 18, 12, 184, 80, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 87 },
    { 7, 216, 18, 12, 98, 73, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 88 },
    { 13, 12, 18, 12, 243, 87, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 84 },
    { 9, 216, 18, 12, 120, 98, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 85 },
    { 0, 216, 18, 12, 266, 226, { 32, 64, 64, 0 }, { 64, 128, 128, 0 }, 89 },
};
MapElem forestDests0_800B8F80[6] = {
    { 5, 216, 18, 0, 115, 63, { 32, 16, 0, 0 }, { 128, 32, 0, 0 }, 60 },
    { 4, 216, 18, 1, 156, 103, { 16, 24, 24, 0 }, { 16, 96, 96, 0 }, 98 },
    { 3, 216, 18, 2, 202, 149, { 24, 24, 0, 0 }, { 64, 64, 0, 0 }, 99 },
};
MapElem forestDests1_800B9028[6] = {
    { 4, 216, 18, 2, 170, 72, { 32, 16, 0, 0 }, { 128, 32, 0, 0 }, 60 },
    { 5, 216, 18, 3, 196, 96, { 16, 24, 24, 0 }, { 16, 96, 96, 0 }, 98 },
    { 1, 216, 18, 6, 228, 132, { 24, 24, 0, 0 }, { 64, 64, 0, 0 }, 99 },
    { 0, 216, 18, 7, 67, 92, { 0, 16, 16, 0 }, { 0, 80, 80, 0 }, 101 },
};
MapElem forestDests2_800B90D0[6] = {
    { 3, 216, 18, 5, 135, 52, { 32, 16, 0, 0 }, { 128, 32, 0, 0 }, 60 },
    { 4, 216, 18, 6, 157, 74, { 16, 24, 24, 0 }, { 16, 96, 96, 0 }, 98 },
    { 2, 216, 18, 7, 184, 103, { 24, 24, 0, 0 }, { 64, 64, 0, 0 }, 99 },
    { 0, 216, 18, 8, 53, 72, { 0, 16, 16, 0 }, { 0, 80, 80, 0 }, 101 },
    { 1, 216, 18, 9, 244, 155, { 24, 0, 24, 0 }, { 96, 0, 96, 0 }, 100 },
};
MapElem forestDests3_800B9178[6] = {
    { 0, 216, 18, 6, 142, 86, { 32, 16, 0, 0 }, { 128, 32, 0, 0 }, 60 },
    { 1, 216, 18, 7, 164, 108, { 16, 24, 24, 0 }, { 16, 96, 96, 0 }, 98 },
    { 5, 216, 18, 8, 188, 135, { 24, 24, 0, 0 }, { 64, 64, 0, 0 }, 99 },
    { 2, 216, 18, 9, 66, 109, { 0, 16, 16, 0 }, { 0, 80, 80, 0 }, 101 },
    { 3, 216, 18, 10, 239, 179, { 24, 0, 24, 0 }, { 96, 0, 96, 0 }, 100 },
    { 4, 216, 18, 11, 160, 22, { 32, 16, 16, 0 }, { 96, 32, 32, 0 }, 102 },
};
MapRow mapAreas_800B9220[6] = {
    { 60, 61, aSyrus_800B66E0, 0xA0, 0x14, 14, villageDests0_800B8CA8 },
    { 75, 76, aSyrus_800B66E0, 0xA0, 0x14, 13, villageDests1_800B8E14 },
    { 90, 91, aParelForest_800B66C4, 0x32, 0x14, 29, forestDests0_800B8F80 },
    { 92, 93, aParelForest_800B66C4, 0x32, 0x14, 29, forestDests1_800B9028 },
    { 94, 95, aParelForest_800B66C4, 0x32, 0x14, 29, forestDests2_800B90D0 },
    { 96, 97, aParelForest_800B66C4, 0x32, 0x14, 29, forestDests3_800B9178 },
};
char *villageDestNames_800B92B0[13] = {
    aMyHome_800B6818, aGaraiSHome_800B67FC, aBlacksmith_800B67E4, aTownShop_800B67D0,
    aChiefSEstate_800B67B0, aSilkMill_800B679C, aWatchtower_800B6784, aNamSHome_800B676C,
    aMusaSHome_800B6754, aWenSHome_800B673C, aCemetery_800B6728, aVillageSquare_800B6708,
    aForestGates_800B66EC,
};
char *forestDestNames_800B92E4[6] = { aSyrus_800B66E0, aBarrierGate_800B689C, aBeetleForest_800B6880, aDragonflyForest_800B685C, aSpiderForest_800B6840, aMothForest_800B6828 };
char **destNames_800B92FC[6] = { villageDestNames_800B92B0, villageDestNames_800B92B0, forestDestNames_800B92E4, forestDestNames_800B92E4, forestDestNames_800B92E4, forestDestNames_800B92E4 };
SPRT *areaBgSprts_800B9314 = 0;
DR_TPAGE *areaBgTPages_800B9318 = 0;
SPRT *areaSprts_800B931C = 0;
DR_TPAGE *areaTPages_800B9320 = 0;
MenuCursor confirmCursor_800B9324 = { 2, 1, 2, 1 };
unsigned char villageDestMaps_800B9330[16] = { 0, 1, 2, 3, 6, 4, 5, 9, 10, 11, 7, 8, 255 };
unsigned char forestDestMaps_800B9340[8] = { 254, 0, 240, 241, 242, 243 };
unsigned char *destMaps_800B9348[6] = { villageDestMaps_800B9330, villageDestMaps_800B9330, forestDestMaps_800B9340, forestDestMaps_800B9340, forestDestMaps_800B9340, forestDestMaps_800B9340 };
unsigned char areaMapGroups_800B9360[8] = { 1, 2, 4, 4, 4, 4 };
unsigned char destMapCounts_800B9368[8] = { 13, 13, 6, 6, 6, 6 };
char *debugGroupNames_800B9370[6] = { aOthers_800B6A5C, aSyrus1_800B6A4C, aSyrus2_800B6A3C, aSyrus3_800B6A2C, aField1_800B6A1C, aField2_800B6A0C };
char *debugSceneNames0_800B9388[5] = { aOpening_800B6AA0, aDummy_800B6A94, aDream_800B6A88, aHunting_800B6A78, aClear_800B6A6C };
char *debugSceneNames1_800B939C[12] = {
    aLebant_800B6B44, aGarai_800B6B38, aKaji_800B6B2C, aDougu_800B6B20,
    aMayu_800B6B14, aMihari_800B6B04, aZokuchou_800B6AF0, aHakaba_800B6AE0,
    aHiroba_800B6AD0, aNam_800B6AC8, aMussa_800B6ABC, aGuen_800B6AB0,
};
char *debugSceneNames2_800B93CC[5] = { aKekkai_800B6B88, aTamamusi_800B6B74, aTombo_800B6B68, aKumo_800B6B5C, aGa_800B6B54 };
char **debugSceneNames_800B93E0[6] = { debugSceneNames0_800B9388, debugSceneNames1_800B939C, debugSceneNames1_800B939C, debugSceneNames1_800B939C, debugSceneNames2_800B93CC, debugSceneNames2_800B93CC };
unsigned char debugGroupVariants_800B93F8[8] = { 0, 0, 1, 2, 0, 2 };
FileRequestDesc mapFileRequest_800B9400[1] = { { 0 } };
MapSelState sceneSelect_800B9420 = { 0 };
int mapFileLoaded_800B9430 = 0;
int mapFileStage_800B9434 = 0;
int chapterSel_800B9438 = 0;

int dword_800B66C0 SDATA = 25;
const char aParelForest_800B66C4[] = "\202o\202\201\202\222\202\205\202\214\201@\202e\202\217\202\222\202\205\202\223\202\224"; // Parel Forest
const char aSyrus_800B66E0[12] = "\202r\202\231\202\222\202\225\202\223";
const char aForestGates_800B66EC[28] = "\202e\202\217\202\222\202\205\202\223\202\224\201@\202f\202\201\202\224\202\205\202\223";
const char aVillageSquare_800B6708[32] = "\202u\202\211\202\214\202\214\202\201\202\207\202\205\201@\202r\202\221\202\225\202\201\202\222\202\205";
const char aCemetery_800B6728[20] = "\202b\202\205\202\215\202\205\202\224\202\205\202\222\202\231";
const char aWenSHome_800B673C[24] = "\202v\202\205\202\216\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aMusaSHome_800B6754[24] = "\202l\202\225\202\223\202\201\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aNamSHome_800B676C[24] = "\202m\202\201\202\215\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aWatchtower_800B6784[24] = "\202v\202\201\202\224\202\203\202\210\202\224\202\217\202\227\202\205\202\222";
const char aSilkMill_800B679C[20] = "\202r\202\211\202\214\202\213\201@\202l\202\211\202\214\202\214";
const char aChiefSEstate_800B67B0[32] = "\202b\202\210\202\211\202\205\202\206\201f\202\223\201@\202d\202\223\202\224\202\201\202\224\202\205";
const char aTownShop_800B67D0[20] = "\202s\202\217\202\227\202\216\201@\202r\202\210\202\217\202\220";
const char aBlacksmith_800B67E4[24] = "\202a\202\214\202\201\202\203\202\213\202\223\202\215\202\211\202\224\202\210";
const char aGaraiSHome_800B67FC[28] = "\202f\202\201\202\222\202\201\202\211\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aMyHome_800B6818[16] = "\202l\202\231\201@\202g\202\217\202\215\202\205";
const char aMothForest_800B6828[24] = "\202l\202\217\202\224\202\210\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aSpiderForest_800B6840[28] = "\202r\202\220\202\211\202\204\202\205\202\222\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aDragonflyForest_800B685C[36] = "\202c\202\222\202\201\202\207\202\217\202\216\202\206\202\214\202\231\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aBeetleForest_800B6880[28] = "\202a\202\205\202\205\202\224\202\214\202\205\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aBarrierGate_800B689C[28] = "\202a\202\201\202\222\202\222\202\211\202\205\202\222\201@\202f\202\201\202\224\202\205";
const MapWin destListRow0_800B68B8 = { {
    { 8, 3, 0, 0, 0, 16, 152, 116, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
} };
const MapWin destListRow1_800B68F0 = { {
    { 8, 3, 0, 0, 0, 16, 170, 116, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
} };
const MapWin destListRow2_800B6928 = { {
    { 8, 3, 0, 0, 0, 16, 188, 116, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
} };
const MenuWindowList menuTemplate_800B6960 = { 2, 0, 8 };
const char aProceed_800B6978[] = "\202o\202\222\202\217\202\203\202\205\202\205\202\204\201H"; // Proceed?
const char aYes_800B698C[] = "\202x\202\205\202\223"; // Yes
const MapWin yesRow_800B6994 = { {
    { 8, 3, aYes_800B698C, 0, 0, 114, 184, 46, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
} };
const char aNo_800B69CC[] = "\202m\202\217"; // No
const MapWin noRow_800B69D4 = { {
    { 8, 3, aNo_800B69CC, 0, 0, 160, 184, 46, 18, 2, 2 },
    { 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1 },
} };
const char aField2_800B6A0C[16] = "\202e\202\211\202\205\202\214\202\204\202Q";
const char aField1_800B6A1C[16] = "\202e\202\211\202\205\202\214\202\204\202P";
const char aSyrus3_800B6A2C[16] = "\202r\202\231\202\222\202\225\202\223\202R";
const char aSyrus2_800B6A3C[16] = "\202r\202\231\202\222\202\225\202\223\202Q";
const char aSyrus1_800B6A4C[16] = "\202r\202\231\202\222\202\225\202\223\202P";
const char aOthers_800B6A5C[16] = "\202n\202\224\202\210\202\205\202\222\202\223";
const char aClear_800B6A6C[12] = "\202b\202\214\202\205\202\201\202\222";
const char aHunting_800B6A78[16] = "\202g\202\225\202\216\202\224\202\211\202\216\202\207";
const char aDream_800B6A88[12] = "\202c\202\222\202\205\202\201\202\215";
const char aDummy_800B6A94[12] = "\202c\202\225\202\215\202\215\202\231";
const char aOpening_800B6AA0[16] = "\202n\202\220\202\205\202\216\202\211\202\216\202\207";
const char aGuen_800B6AB0[12] = "\202f\202\225\202\205\202\216";
const char aMussa_800B6ABC[12] = "\202l\202\225\202\223\202\223\202\201";
const char aNam_800B6AC8[8] = "\202m\202\201\202\215";
const char aHiroba_800B6AD0[16] = "\202g\202\211\202\222\202\217\202\202\202\201";
const char aHakaba_800B6AE0[16] = "\202g\202\201\202\213\202\201\202\202\202\201";
const char aZokuchou_800B6AF0[20] = "\202y\202\217\202\213\202\225\202\203\202\210\202\217\202\225";
const char aMihari_800B6B04[16] = "\202l\202\211\202\210\202\201\202\222\202\211";
const char aMayu_800B6B14[12] = "\202l\202\201\202\231\202\225";
const char aDougu_800B6B20[12] = "\202c\202\217\202\225\202\207\202\225";
const char aKaji_800B6B2C[12] = "\202j\202\201\202\212\202\211";
const char aGarai_800B6B38[12] = "\202f\202\201\202\222\202\201\202\211";
const char aLebant_800B6B44[16] = "\202k\202\205\202\202\202\201\202\216\202\224";
const char aGa_800B6B54[8] = "\202f\202\201";
const char aKumo_800B6B5C[12] = "\202j\202\225\202\215\202\217";
const char aTombo_800B6B68[12] = "\202s\202\217\202\215\202\202\202\217";
const char aTamamusi_800B6B74[20] = "\202s\202\201\202\215\202\201\202\215\202\225\202\223\202\211";
const char aKekkai_800B6B88[16] = "\202j\202\205\202\213\202\213\202\201\202\211";
const char aSelKind_800B6B98[] = "\202r\202\205\202\214\201@\202\213\202\211\202\216\202\204"; // Sel kind
const char aSelSceneGroup_800B6BAC[] = "\202r\202\205\202\214\201@\202\223\202\203\202\205\202\216\202\205\201@\202\207\202\222\202\217\202\225\202\220"; // Sel scene group
const char aSelScene_800B6BCC[] = "\202r\202\205\202\214\201@\202\223\202\203\202\205\202\216\202\205"; // Sel scene
const char aSelChapter_800B6BE0[28] = "\202r\202\205\202\214\201@\202\203\202\210\202\201\202\220\202\224\202\205\202\222\201@\000\000im";

void MapSelectStart_800B6BFC(MapTask* task, int work)
{
    void (*next)();
    lastDest_800B8C94.area = mapSelect_800AEBF8.area;
    lastDest_800B8C94.dest = mapSelect_800AEBF8.dest;
    GetCurrentDest_800B8448(&mapSelect_800AEBF8);
    next = StartAreaFadeOut_800B6C7C;
    task->next_8 = next;
    next(task, work);
    task->flags_0 = (task->flags_0 | 4) & 0xFFFF7FFF;
}

void StartAreaFadeOut_800B6C7C(MapTask* task)
{
    SetFadeMode_8001C19C(0, 0x20);
    task->next_8 = LoadAreaPicture_800B6CB4;
}

void LoadAreaPicture_800B6CB4(MapTask* task)
{
    int music;
    openDestCount_800B8CA4 = CountOpenDests_800B7E54(mapSelect_800AEBF8.area);
    InitDestCursor_800B7EE0();
    if (GetEventVar_800AD154(0xC) == 1)
    {
        music = 0xF;
    }
    else if (GetEventVar_800AD154(0xC) == 2)
    {
        music = 0x91;
    }
    else
    {
        music = mapAreas_800B9220[mapSelect_800AEBF8.area].music_10;
    }
    PlayMusic_800300E0(music, 1);
    mapFileStage_800B9434 = 0;
    RequestMapFile_800B6D90(mapFileRequest_800B9400, mapAreas_800B9220[mapSelect_800AEBF8.area].bgFile_0);
    task->next_8 = WaitAreaPicture_800B6E5C;
}

void RequestMapFile_800B6D90(FileRequestDesc* req, int fileId)
{
    mapFileLoaded_800B9430 = 0;
    req->flags_0 = 0x2C;
    req->fileId_4 = fileId;
    req->offset_8 = 0;
    req->size_C = 0;
    req->dest_10 = 0;
    req->params_14 = 0;
    req->paramsSize_18 = 0;
    req->callback_1C = OnMapFileLoaded_800B6DE0;
    QueueFileRequest_8003BC84(req);
}

void OnMapFileLoaded_800B6DE0(MapTask* task, int* data)
{
    FreeMapTiys_800B6FAC(task);
    if (mapFileStage_800B9434 == 1)
    {
        LoadTiy_80028E74(&areaSprts_800B931C, 0, &areaTPages_800B9320, data, 1);
    }
    else
    {
        LoadTiy_80028E74(&areaBgSprts_800B9314, 0, &areaBgTPages_800B9318, data, 1);
    }
    mapFileLoaded_800B9430 = 1;
}

void WaitAreaPicture_800B6E5C(MapTask* task)
{
    if (mapFileLoaded_800B9430)
    {
        task->next_8 = LoadAreaSprites_800B6E80;
    }
}

void LoadAreaSprites_800B6E80(MapTask* task)
{
    mapFileStage_800B9434 = 1;
    RequestMapFile_800B6D90(mapFileRequest_800B9400, mapAreas_800B9220[mapSelect_800AEBF8.area].spritesFile_4);
    task->next_8 = WaitAreaFadeIn_800B6EE8;
}

void WaitAreaFadeIn_800B6EE8(MapTask* task, int work)
{
    if (mapFileLoaded_800B9430 && IsFadeDone_8001C2FC())
    {
        task->next_8 = DestinationSelect_800B7044;
        ResetPadHoldFrames_8001CD04(0);
        task->next_8(task, work);
        SetFadeMode_8001C19C(3, 0x20);
    }
}

void MapSelectEnd_800B6F60(MapTask* task, int work)
{
    FreeMapTiys_800B6FAC(task);
    task->flags_0 &= ~4;
    unknownFlags_8008D678 &= 0xFBFFFFFF;
}

void FreeMapTiys_800B6FAC(MapTask* task)
{
    if (areaBgSprts_800B9314)
    {
        free3_8003FC6C(areaBgSprts_800B9314);
        areaBgSprts_800B9314 = 0;
    }
    if (areaBgTPages_800B9318)
    {
        free3_8003FC6C(areaBgTPages_800B9318);
        areaBgTPages_800B9318 = 0;
    }
    if (areaSprts_800B931C)
    {
        free3_8003FC6C(areaSprts_800B931C);
        areaSprts_800B931C = 0;
    }
    if (areaTPages_800B9320)
    {
        free3_8003FC6C(areaTPages_800B9320);
        areaTPages_800B9320 = 0;
    }
}

// the destination list of a map area: the area picture, the blinking marker of the selected destination
// and the scrolling list of names
void DestinationSelect_800B7044(MapTask* task, int work)
{
    MapDest sel;
    DR_MOVE mv;
    RECT r0;
    RECT box;
    short tp[2];
    MapDest listDest;
    MapWin w0;
    MapWin w1;
    MapWin w2;
    MenuWindowItem* list[4];
    MenuWindowList menu;
    MapXY arrow;
    MapXY pos[2];
    MapElem* elem;
    int y;
    int wd;
    int id;
    int id2;
    int i;
    int destIdx;
    MapDest* p;
    short* area = &mapSelect_800AEBF8.area;
    GetNthOpenDest_800B8128((short)GetMenuCursorIndex_8003DA54(&mapSelectCursors_800AEBFC[*area]), *area, &sel);
    elem = mapAreas_800B9220[*area].dests_14 + sel.dest;
    if (openDestCount_800B8CA4 > 0)
    {
        UpdateMenuCursor_8003D794(&mapSelectCursors_800AEBFC[*area], 0);
    }
    if (display_8008B4D8.vsyncsPerFrame_4 == 1)
    {
        y = display_8008B4D8.y_A;
    }
    else
    {
        y = dispEnv_8008D750[bDoubleBuffer_8008D428 ^ 1].disp.y;
    }
    r0.x = 0x140;
    r0.w = 0x140;
    r0.y = 0;
    r0.h = 0xF0;
    SetDrawMove(&mv, &r0, 0, y);
    AddPrimCopy_80040298(pOT_8008D3EC, &mv, 6);
    wd = MeasureTextWidth_8003E4C8(mapAreas_800B9220[mapSelect_800AEBF8.area].name_8);
    tp[0] = mapAreas_800B9220[mapSelect_800AEBF8.area].x_C - (short)wd / 2;
    tp[1] = mapAreas_800B9220[mapSelect_800AEBF8.area].y_E;
    box.x = tp[0] - 2;
    box.y = tp[1] - 2;
    box.w = wd + 4;
    box.h = 0x12;
    tp[1] += 2;
    DrawText_8003E91C(2, mapAreas_800B9220[mapSelect_800AEBF8.area].name_8, tp, 0);
    DrawUiColorWindow_800424C0(&box, 0, pOT_8008D454, 0);
    if (openDestCount_800B8CA4 > 0)
    {
        id = elem->sprite_0;
        areaSprts_800B931C[id].x0 = elem->x_4;
        areaSprts_800B931C[id].y0 = elem->y_6;
        AddPrimCopy_80040298(&pOT_8008D454[10], &areaSprts_800B931C[id], 5);
        AddPrimCopy_80040298(&pOT_8008D454[10], &areaTPages_800B9320[id], 2);
        if (openDestCount_800B8CA4 > 0)
        {
            id2 = elem->marker_8;
            areaSprts_800B931C[id2].x0 = elem->x_C;
            areaSprts_800B931C[id2].y0 = elem->y_E;
            PulseColor_80033394(&areaSprts_800B931C[id2].r0, elem->c0_10, elem->c1_14, GetTime30Hz_8002C64C(), 0x28, 0xA);
            if ((unsigned short)mapSelect_800AEBF8.area < 2)
            {
                SetSemiTrans(&areaSprts_800B931C[id2], 0);
            }
            else
            {
                SetSemiTrans(&areaSprts_800B931C[id2], 1);
            }
            AddPrimCopy_80040298(&pOT_8008D454[9], &areaSprts_800B931C[id2], 5);
            if ((unsigned short)mapSelect_800AEBF8.area >= 2)
            {
                // the original reads this word here without using it
                areaTPages_800B9320[id2].code[0] = areaTPages_800B9320[id2].code[0];
            }
            AddPrimCopy_80040298(&pOT_8008D454[9], &areaTPages_800B9320[id2], 2);
            if (openDestCount_800B8CA4 > 0)
            {
                w0 = destListRow0_800B68B8;
                w1 = destListRow1_800B68F0;
                w2 = destListRow2_800B6928;
                memset(list, 0, 0x10);
                menu = menuTemplate_800B6960;
                list[0] = w0.items;
                list[1] = w1.items;
                list[2] = w2.items;
                menu.items_10 = list;
                for (i = mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area].scroll_A;
                     i < mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area].scroll_A + mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area].rows_2; i++)
                {
                    GetNthOpenDest_800B8128((short)i, mapSelect_800AEBF8.area, &listDest);
                    list[i - mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area].scroll_A][0].text_4.str = destNames_800B92FC[listDest.area][listDest.dest];
                }
                if (openDestCount_800B8CA4 < 3)
                {
                    list[openDestCount_800B8CA4] = 0;
                }
                menu.time_4 = GetTime30Hz_8002C64C();
                menu.cursor_C = mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area].cursor_8;
                DrawMenuWindows_8002A5A4(&menu);
            }
        }
    }
    arrow.x = 2;
    arrow.y = 1;
    pos[0].x = 0x4A;
    pos[0].y = 0x93;
    pos[1].x = 0x4A;
    pos[1].y = mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area].rows_2 * 18 + 0x9D;
    DrawScrollArrows_8002B8DC(arrow, &mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area], pos, 0);
    p = &mapSelect_800AEBF8;
    if (openDestCount_800B8CA4 > 0 && (IsConfirmPressedP1_8003D380(1) || (padPressed_8009194C[0] & 0x80)))
    {
        GetNthOpenDest_800B8128((short)GetMenuCursorIndex_8003DA54(&mapSelectCursors_800AEBFC[mapSelect_800AEBF8.area]), mapSelect_800AEBF8.area, p);
        lastDest_800B8C94.area = mapSelect_800AEBF8.area;
        lastDest_800B8C94.dest = p->dest;
        if ((unsigned short)mapSelect_800AEBF8.area < 2)
        {
            destIdx = p->dest;
            if (destIdx == 0xC)
            {
                mapSelect_800AEBF8.area = 5;
                p->dest = 5;
                if (IsDestOpen_800B8290(p))
                {
                    p->dest = 0;
                    task->next_8 = StartAreaFadeOut_800B6C7C;
                    task->next_8(task, work);
                    return;
                }
                mapSelect_800AEBF8.area = 4;
                p->dest = 4;
                if (IsDestOpen_800B8290(p))
                {
                    p->dest = 0;
                    task->next_8 = StartAreaFadeOut_800B6C7C;
                    task->next_8(task, work);
                    return;
                }
                mapSelect_800AEBF8.area = 3;
                p->dest = 3;
                if (IsDestOpen_800B8290(p))
                {
                    p->dest = 0;
                    task->next_8 = StartAreaFadeOut_800B6C7C;
                    task->next_8(task, work);
                    return;
                }
                mapSelect_800AEBF8.area = 2;
                p->dest = 2;
                if (IsDestOpen_800B8290(p))
                {
                    p->dest = 0;
                    task->next_8 = StartAreaFadeOut_800B6C7C;
                    task->next_8(task, work);
                    return;
                }
                mapSelect_800AEBF8.area = 0;
                p->dest = destIdx;
                if (padPressed_8009194C[0] & 0x80)
                {
                    GoToDest_800B8338(p);
                    MapSelectEnd_800B6F60(task, work);
                    task->next_8 = StartMapOverlay_800A75F8;
                }
                else
                {
                    task->next_8 = StartDestFadeOut_800B7948;
                    task->next_8(task, work);
                }
            }
            else if (padPressed_8009194C[0] & 0x80)
            {
                GoToDest_800B8338(p);
                MapSelectEnd_800B6F60(task, work);
                task->next_8 = StartMapOverlay_800A75F8;
            }
            else
            {
                task->next_8 = StartDestFadeOut_800B7948;
                task->next_8(task, work);
            }
        }
        else if (mapSelect_800AEBF8.dest == 0)
        {
            if (!saveData_8008B570.mapVariant_2E0)
            {
                mapSelect_800AEBF8.area = 0;
                lastDest_800B8C94.area = 0;
            }
            else
            {
                mapSelect_800AEBF8.area = 1;
                lastDest_800B8C94.area = 1;
            }
            mapSelect_800AEBF8.dest = 0xC;
            lastDest_800B8C94.dest = 0xC;
            task->next_8 = StartAreaFadeOut_800B6C7C;
            task->next_8(task, work);
        }
        else if (padPressed_8009194C[0] & 0x80)
        {
            GoToDest_800B8338(p);
            MapSelectEnd_800B6F60(task, work);
            task->next_8 = StartMapOverlay_800A75F8;
        }
        else
        {
            task->next_8 = StartDestFadeOut_800B7948;
            task->next_8(task, work);
        }
    }
}

void StartDestFadeOut_800B7948(MapTask* task)
{
    SetFadeMode_8001C19C(0, 0x20);
    task->next_8 = LoadDestPicture_800B7980;
}

void LoadDestPicture_800B7980(MapTask* task)
{
    MapDest sel;
    MapElem* elem;
    MapDest* cur = &mapSelect_800AEBF8;
    int idx = GetMenuCursorIndex_8003DA54(&mapSelectCursors_800AEBFC[cur->area]);
    GetNthOpenDest_800B8128((short)idx, cur->area, &sel);
    mapFileStage_800B9434 = 0;
    elem = mapAreas_800B9220[mapSelect_800AEBF8.area].dests_14 + sel.dest;
    RequestMapFile_800B6D90(mapFileRequest_800B9400, elem->file_18);
    task->next_8 = WaitDestPicture_800B7A38;
}

void WaitDestPicture_800B7A38(MapTask* task)
{
    if (mapFileLoaded_800B9430 && IsFadeDone_8001C2FC())
    {
        task->next_8 = ConfirmDestination_800B7A90;
        SetFadeMode_8001C19C(3, 0x20);
        confirmCursor_800B9324.cursor_8 = 0;
    }
}

void ConfirmDestination_800B7A90(MapTask* task, int work)
{
    MapDest sel;
    DR_MOVE mv;
    RECT r0;
    RECT box;
    short tp[4];
    RECT box2;
    short tp2[4];
    MapWin w0;
    MapWin w1;
    MenuWindowItem* list[3];
    MenuWindowList menu;
    int y;
    int wd;
    MapDest* cur = &mapSelect_800AEBF8;
    GetNthOpenDest_800B8128((short)GetMenuCursorIndex_8003DA54(&mapSelectCursors_800AEBFC[cur->area]), cur->area, &sel);
    UpdateMenuCursor_8003D794(&confirmCursor_800B9324, 0);
    if (display_8008B4D8.vsyncsPerFrame_4 == 1)
    {
        y = display_8008B4D8.y_A;
    }
    else
    {
        y = dispEnv_8008D750[bDoubleBuffer_8008D428 ^ 1].disp.y;
    }
    r0.x = 0x140;
    r0.w = 0x140;
    r0.y = 0;
    r0.h = 0xF0;
    SetDrawMove(&mv, &r0, 0, y);
    AddPrimCopy_80040298(pOT_8008D3EC, &mv, 6);
    wd = MeasureTextWidth_8003E4C8(destNames_800B92FC[mapSelect_800AEBF8.area][mapSelect_800AEBF8.dest]);
    box.x = 0x9E - (short)wd / 2;
    box.y = 0x12;
    box.w = wd + 4;
    box.h = 0x12;
    tp[0] = 0xA0 - (short)wd / 2;
    tp[1] = 0x16;
    DrawText_8003E91C(2, destNames_800B92FC[mapSelect_800AEBF8.area][mapSelect_800AEBF8.dest], tp, 0);
    DrawUiColorWindow_800424C0(&box, 0, pOT_8008D454, 0);
    box2.x = 0x74;
    box2.y = 0xA6;
    box2.w = 0x58;
    box2.h = 0x12;
    tp2[0] = 0x76;
    tp2[1] = 0xA8;
    tp2[0] = 0x86;
    tp2[1] = 0xAA;
    DrawText_8003E91C(2, aProceed_800B6978, tp2, 0);
    DrawUiColorWindow_800424C0(&box2, 0, pOT_8008D454, 0);
    w0 = yesRow_800B6994;
    w1 = noRow_800B69D4;
    memset(list, 0, 0xC);
    menu = menuTemplate_800B6960;
    list[0] = w0.items;
    list[1] = w1.items;
    menu.time_4 = GetTime30Hz_8002C64C();
    menu.items_10 = list;
    menu.cursor_C = confirmCursor_800B9324.cursor_8;
    DrawMenuWindows_8002A5A4(&menu);
    if (IsConfirmPressedP1_8003D380(1))
    {
        if ((short)GetMenuCursorIndex_8003DA54(&confirmCursor_800B9324) == 0)
        {
            GoToDest_800B8338(&mapSelect_800AEBF8);
            MapSelectEnd_800B6F60(task, work);
            task->next_8 = StartMapOverlay_800A75F8;
        }
        else
        {
            task->next_8 = StartAreaFadeOut_800B6C7C;
        }
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        task->next_8 = StartAreaFadeOut_800B6C7C;
    }
}

int CountOpenDests_800B7E54(short area)
{
    int i;
    int count = 0;
    MapDest cur;
    cur.area = area;
    for (i = 0; i < destCounts_800B8C98[area]; i++)
    {
        cur.dest = i;
        if (IsDestOpen_800B8290(&cur))
        {
            count++;
        }
    }
    return count;
}

void InitDestCursor_800B7EE0(void)
{
    MapDest sel;
    int idx;
    int rank;
    int maxScroll;
    if (openDestCount_800B8CA4 < 4)
    {
        SEL.rows_2 = openDestCount_800B8CA4;
        SEL.flags_6 = 0;
    }
    else
    {
        SEL.rows_2 = 3;
        SEL.flags_6 = 0x40;
    }
    SEL.count_4 = openDestCount_800B8CA4;
    if (mapSelect_800AEBF8.area != lastDest_800B8C94.area || mapSelect_800AEBF8.dest != lastDest_800B8C94.dest)
    {
        SEL.cursor_8 = 0;
        SEL.scroll_A = 0;
    }
    else
    {
        idx = GetMenuCursorIndex_8003DA54(&SEL);
        GetNthOpenDest_800B8128((short)idx, mapSelect_800AEBF8.area, &sel);
        if (!IsDestOpen_800B8290(&sel))
        {
            SEL.cursor_8 = 0;
            SEL.scroll_A = 0;
        }
        else
        {
            rank = GetOpenDestRank_800B81D0(&mapSelect_800AEBF8);
            if (openDestCount_800B8CA4 < 4)
            {
                SEL.cursor_8 = rank;
                SEL.scroll_A = 0;
            }
            else
            {
                maxScroll = (unsigned short)openDestCount_800B8CA4 - 3;
                if ((short)maxScroll < SEL.scroll_A)
                {
                    SEL.cursor_8 = rank - maxScroll;
                    SEL.scroll_A = maxScroll;
                }
            }
        }
    }
}

void GetNthOpenDest_800B8128(short nth, short area, MapDest* out)
{
    int count = 0;
    int i;
    out->area = area;
    for (i = 0; i < destCounts_800B8C98[area]; i++)
    {
        out->dest = i;
        if (IsDestOpen_800B8290(out))
        {
            if (count++ == nth)
            {
                break;
            }
        }
    }
}

int GetOpenDestRank_800B81D0(MapDest* want)
{
    int i;
    short rank = 0;
    MapDest cur;
    cur.area = want->area;
    for (i = 0; i < destCounts_800B8C98[want->area]; i++)
    {
        cur.dest = i;
        if (IsDestOpen_800B8290(&cur))
        {
            rank++;
            if (cur.dest == want->dest)
            {
                break;
            }
        }
    }
    return rank;
}

int IsDestOpen_800B8290(MapDest* sel)
{
    int area = sel->area;
    unsigned char map = destMaps_800B9348[area][sel->dest];
    MapQuery query;
    int var;
    if (map == 0xFF)
    {
        return TestEventFlag_800AD0D4(1) != 0;
    }
    if (map == 0xFE)
    {
        return 1;
    }
    if (map >= 0xF0)
    {
        map += 0x11;
    }
    query.group_0 = areaMapGroups_800B9360[area];
    query.map_2 = map;
    query.entry_4 = 0;
    var = GetMapVar_800ADC1C(&query);
    return var != -1;
}

void GoToDest_800B8338(MapDest* sel)
{
    unsigned char map = destMaps_800B9348[sel->area][sel->dest];
    if (map == 0xFE || map == 0xFF)
    {
        saveData_8008B570.mapId_2E4[0].cur_0 = 4;
        saveData_8008B570.mapId_2E4[1].cur_0 = 0;
        saveData_8008B570.mapId_2E4[2].cur_0 = 0;
        saveData_8008B570.mapId_2E4[2].prev_2 = -1;
    }
    else if (map >= 0xF0)
    {
        SetEventVar_800AD16C(4, map - 0xEF);
        saveData_8008B570.mapId_2E4[0].cur_0 = 4;
        saveData_8008B570.mapId_2E4[1].cur_0 = 0;
        saveData_8008B570.mapId_2E4[2].cur_0 = 0;
        saveData_8008B570.mapId_2E4[2].prev_2 = -1;
    }
    else
    {
        saveData_8008B570.mapId_2E4[0].cur_0 = areaMapGroups_800B9360[sel->area];
        saveData_8008B570.mapId_2E4[1].cur_0 = destMaps_800B9348[sel->area][sel->dest];
        saveData_8008B570.mapId_2E4[2].cur_0 = 0;
        saveData_8008B570.mapId_2E4[2].prev_2 = -1;
    }
    ResetLevantActorToIdle_800A8DEC();
    SetFadeMode_8001C19C(0, 0x20);
    RequestGameMode_800A6D30(1);
    useMapStartPos_80091C94 = 1;
    eventDispatchHalt_8008B540 = 1;
}

void GetCurrentDest_800B8448(MapDest* out)
{
    unsigned short area = saveData_8008B570.mapId_2E4[0].cur_0;
    MapQuery query;
    unsigned char* tbl;
    unsigned char cnt;
    if ((unsigned short)(area - 4) < 2)
    {
        if (saveData_8008B570.mapId_2E4[1].cur_0 == 0)
        {
            int variant = saveData_8008B570.mapVariant_2E0;
            out->dest = 12;
            out->area = variant == 1;
            return;
        }
        query.group_0 = area;
        query.entry_4 = 0;
        query.map_2 = 1;
        do
        {
            if (GetMapVar_800ADC1C(&query) == -1)
            {
                break;
            }
            query.map_2++;
        } while (query.map_2 < 5);
        if (query.map_2 == 5)
        {
            query.map_2--;
        }
        out->area = query.map_2 + 1;
    }
    else if ((unsigned short)(area - 1) >= 3)
    {
        int variant = saveData_8008B570.mapVariant_2E0;
        out->dest = 0;
        out->area = variant == 1;
        return;
    }
    else
    {
        out->area = saveData_8008B570.mapVariant_2E0 == 1;
    }
    tbl = destMaps_800B9348[out->area];
    cnt = destMapCounts_800B9368[out->area];
    for (out->dest = 0; out->dest < cnt; out->dest++)
    {
        if (saveData_8008B570.mapId_2E4[1].cur_0 == tbl[out->dest])
        {
            return;
        }
    }
    out->dest = 0;
}

void SceneSelectStart_800B85CC(MapTask* task)
{
    MapSelState* st;
    void (*next)() = SceneSelect_800B860C;
    sceneSelect_800B9420.step_0 = 0;
    st = &sceneSelect_800B9420;
    st->area_4 = 0;
    st->map_8 = 0;
    st->entry_C = 0;
    task->next_8 = next;
    next();
}

void SceneSelect_800B860C()
{
    MapSelState* st = &sceneSelect_800B9420;
    int area = st->area_4;
    int map = st->map_8;
    MapEntry* list = mapTable_800B0608[area][map];
    RECT r1;
    RECT r2;
    RECT r3;
    int y;
    int i;
    int count;
    int shift;
    char* str;
    int v;
    int c;
    switch (st->step_0)
    {
    case 0:
        if (padRepeat_800918CC[0] & 0x1000)
        {
            st->area_4 = area - 1;
        }
        else if (padRepeat_800918CC[0] & 0x4000)
        {
            st->area_4 = area + 1;
        }
        st->area_4 = st->area_4 < 0 ? 0 : st->area_4 < 6 ? st->area_4 : 5;
        if (IsConfirmPressedP1_8003D380(1) == 1)
        {
            st->step_0++;
        }
        r1.x = 0x1E;
        r1.y = 0x14;
        DrawText_8003E91C(2, aSelKind_800B6B98, &r1, 0);
        for (i = 0; i < 6; i++)
        {
            str = debugGroupNames_800B9370[i];
            shift = i == st->area_4 ? (frameCount_8008D3FC & 0xF) : 0;
            r2.x = 0x1E + shift;
            r2.y = 0x32 + i * 14;
            DrawText_8003E91C(2, str, &r2, 0);
        }
        if (frameCount_8008D3FC & 3)
        {
            r2.x = 0x1E;
            r2.y = st->area_4 * 14 + 0x32;
            DrawCursorHand_8003D034(&r2.x, 0);
        }
        break;
    case 1:
        if (padRepeat_800918CC[0] & 0x1000)
        {
            st->map_8 = map - 1;
        }
        else if (padRepeat_800918CC[0] & 0x4000)
        {
            st->map_8 = map + 1;
        }
        st->map_8 = st->map_8 < 0 ? 0 : (areaMapCounts_800B0624[st->area_4] - 1 < st->map_8 ? areaMapCounts_800B0624[st->area_4] - 1 : st->map_8);
        if (IsConfirmPressedP1_8003D380(1) == 1)
        {
            st->step_0++;
        }
        else if (IsCancelPressedP1_8003D41C(1) == 1)
        {
            st->map_8 = 0;
            st->step_0--;
        }
        r2.x = 0x1E;
        r2.y = 0x14;
        DrawText_8003E91C(2, aSelSceneGroup_800B6BAC, &r2, 0);
        for (i = 0; i < areaMapCounts_800B0624[st->area_4]; i++)
        {
            str = debugSceneNames_800B93E0[st->area_4][i];
            shift = i == st->map_8 ? (frameCount_8008D3FC & 0xF) : 0;
            r3.x = 0x1E + shift;
            r3.y = 0x32 + i * 14;
            DrawText_8003E91C(2, str, &r3, 0);
        }
        if (frameCount_8008D3FC & 3)
        {
            r3.x = 0x1E;
            r3.y = st->map_8 * 14 + 0x32;
            DrawCursorHand_8003D034(&r3.x, 0);
        }
        break;
    case 2:
        if (padRepeat_800918CC[0] & 0x1000)
        {
            st->entry_C--;
        }
        else if (padRepeat_800918CC[0] & 0x4000)
        {
            st->entry_C++;
        }
        count = 0;
        while (list[count].id != -1)
        {
            count++;
        }
        st->entry_C = st->entry_C < 0 ? 0 : (count - 1 < st->entry_C ? count - 1 : st->entry_C);
        if (IsConfirmPressedP1_8003D380(1) == 1)
        {
            saveData_8008B570.mapVariant_2E0 = debugGroupVariants_800B93F8[st->area_4];
            saveData_8008B570.mapId_2E4[0].cur_0 = st->area_4;
            saveData_8008B570.mapId_2E4[1].cur_0 = st->map_8;
            saveData_8008B570.mapId_2E4[2].cur_0 = st->entry_C;
            saveData_8008B570.field_2E2 = -1;
            saveData_8008B570.mapId_2E4[0].prev_2 = -1;
            saveData_8008B570.mapId_2E4[1].prev_2 = -1;
            saveData_8008B570.mapId_2E4[2].prev_2 = -1;
            useMapStartPos_80091C94 = 1;
            mapStartMode_80091C54 = 0;
            ResetLevantActorToIdle_800A8DEC();
            RequestGameMode_800A6D30(1);
            SetFadeMode_8001C19C(0, 0x20);
            eventDispatchHalt_8008B540 = 1;
        }
        else if (IsCancelPressedP1_8003D41C(1) == 1)
        {
            st->entry_C = 0;
            st->step_0--;
        }
        r3.x = 0x1E;
        r3.y = 0x14;
        DrawText_8003E91C(2, aSelScene_800B6BCC, &r3, 0);
        break;
    }
}

void ChapterSelectStart_800B8B2C(MapTask* task)
{
    void (*next)() = ChapterSelect_800B8B5C;
    chapterSel_800B9438 = 0;
    task->next_8 = next;
    next();
}

void ChapterSelect_800B8B5C()
{
    int* sel = &chapterSel_800B9438;
    unsigned short pad = padRepeat_800918CC[0];
    RECT base;
    RECT textPos;
    RECT numPos;
    int confirmed;
    if (pad & 0x1000)
    {
        chapterSel_800B9438--;
    }
    else if (pad & 0x4000)
    {
        chapterSel_800B9438++;
    }
    *sel = *sel < 0 ? 0 : *sel < 7 ? *sel : 6;
    confirmed = IsConfirmPressedP1_8003D380(1);
    if (confirmed == 1)
    {
        SaveData* sd = &saveData_8008B570;
        sd->chapterNext_2DE = -5;
        sd->chapter_2DC = *sel;
        RequestGameMode_800A6D30(0);
        eventDispatchHalt_8008B540 = confirmed;
    }
    IsCancelPressedP1_8003D41C(1);
    base.x = 0x6E;
    base.y = 0x78;
    textPos.x = base.x + 10;
    textPos.y = base.y + 10;
    DrawText_8003E91C(2, aSelChapter_800B6BE0, &textPos, 0);
    numPos.x = base.x + 0x50;
    numPos.y = base.y + 0xA;
    DrawNumber_8003EF74(&numPos.x, *sel + 1, 0);
}
