// LOAD.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "load.h"
#include "tiy.h"

LoadTextPos saveSlotFieldPos_800BD93C[9] = {
    { 170, 54 },
    { 144, 68 },
    { 172, 68 },
    { 222, 68 },
    { 244, 68 },
    { 225, 54 },
    { 39, 55 },
    { 39, 68 },
    { 0x122, 52 },
};
LoadUiSprite saveSlotSprites_800BD960[7] = {
    { 13, 52, 119, 1 },
    { 104, 52, 227, 1 },
    { 100, 66, 118, 1 },
    { 180, 65, 203, 1 },
    { 180, 52, 122, 1 },
    { 13, 66, 150, 1 },
    { -1, -1, -1, -1 },
};
LoadUiSprite modeTitleSprites_800BD998[2] = {
    { 80, 21, 190, 1 },
    { 69, 21, 197, 1 },
};
LoadUiSprite cardSlotSprites_800BD9A8[8] = {
    { 108, 21, 39, 1 },
    { 39, 95, 39, 1 },
    { 59, 109, 178, 1 },
    { 106, 109, 0, 1 },
    { 188, 95, 39, 1 },
    { 208, 109, 178, 1 },
    { 255, 109, 2, 1 },
    { -1, -1, -1, -1 },
};
LoadUiSprite saveIconSprites_800BD9E8[4] = {
    { 0x110, 52, 78, 1 },
    { 0x110, 52, 52, 1 },
    { 0x110, 52, 58, 1 },
    { -1, -1, -1, -1 },
};
char *saveListPrompts_800BDA08[2] = { aSelectSaveLocat_800B66F0, aSelectGameToLoa_800B66C4 };
RECT saveListClip_800BDA10 = { 10, 49, 0x12C, 129 };
MenuWindowItem saveListRow0_800BDA18[2] = {
    { 64, 0, 0, NULL, NULL, 10, 49, 300, 31, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem saveListRow1_800BDA50[2] = {
    { 64, 0, 0, NULL, NULL, 10, 82, 300, 31, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem saveListRow2_800BDA88[2] = {
    { 64, 0, 0, NULL, NULL, 10, 115, 300, 31, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem saveListRow3_800BDAC0[2] = {
    { 64, 0, 0, NULL, NULL, 10, 148, 300, 31, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem *saveListRows_800BDAF8[5] = { saveListRow0_800BDA18, saveListRow1_800BDA50, saveListRow2_800BDA88, saveListRow3_800BDAC0 };
MenuWindowList saveListWin_800BDB0C = { 2, 0, 8, 0, saveListRows_800BDAF8, 5 };
MenuWindowItem cardSlot1Item_800BDB24[2] = {
    { 64, 0, 0, NULL, NULL, 33, 90, 105, 36, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem *cardSlot1Items_800BDB5C[2] = { cardSlot1Item_800BDB24 };
MenuWindowList cardSlot1Win_800BDB64 = { 2, 0, 8, 0, cardSlot1Items_800BDB5C, 5 };
MenuWindowItem cardSlot2Item_800BDB7C[2] = {
    { 64, 0, 0, NULL, NULL, 182, 90, 105, 36, 0, 0 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem *cardSlot2Items_800BDBB4[2] = { cardSlot2Item_800BDB7C };
MenuWindowList cardSlot2Win_800BDBBC = { 2, 0, 8, 0, cardSlot2Items_800BDBB4, 5 };
MenuWindowList *cardSlotWins_800BDBD4[2] = { &cardSlot1Win_800BDB64, &cardSlot2Win_800BDBBC };
MenuWindowItem topMenuSave_800BDBDC[2] = {
    { 8, 1, 190, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 106, 69, 108, 19, 0, 4 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem topMenuLoad_800BDC14[2] = {
    { 8, 1, 197, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 106, 90, 108, 19, 0, 4 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem topMenuExit_800BDC4C[2] = {
    { 8, 1, 198, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 106, 111, 108, 19, 0, 4 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem topMenuTitle_800BDC84[2] = {
    { 8, 1, 196, &uiTiySprts_8008D620, &uiTiyTPages_8008D3F4, 106, 132, 108, 19, 0, 4 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem *topMenuItems_800BDCBC[5] = { topMenuSave_800BDBDC, topMenuLoad_800BDC14, topMenuExit_800BDC4C, topMenuTitle_800BDC84 };
MenuWindowList topMenuWin_800BDCD0 = { 2, 0, 8, 0, topMenuItems_800BDCBC, 5 };
MenuWindowItem formatYes_800BDCE8[2] = {
    { 8, 3, (int)aYES_800B671C, NULL, NULL, 126, 106, 56, 18, 2, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem formatNo_800BDD20[2] = {
    { 8, 3, (int)aNO_800B6724, NULL, NULL, 126, 126, 56, 18, 2, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem *formatItems_800BDD58[3] = { formatYes_800BDCE8, formatNo_800BDD20 };
MenuWindowList formatWin_800BDD64 = { 2, 0, 8, 1, formatItems_800BDD58 };
MenuWindowItem confirmYes_800BDD7C[2] = {
    { 8, 3, (int)aYES_800B671C, NULL, NULL, 215, 193, 46, 19, 2, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem confirmNo_800BDDB4[2] = {
    { 8, 3, (int)aNO_800B6724, NULL, NULL, 0x105, 193, 48, 19, 2, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem *confirmItems_800BDDEC[3] = { confirmYes_800BDD7C, confirmNo_800BDDB4 };
MenuWindowList confirmWin_800BDDF8 = { 2, 0, 8, 1, confirmItems_800BDDEC };
MenuWindowItem titleYes_800BDE10[2] = {
    { 8, 3, (int)aYES_800B671C, NULL, NULL, 106, 121, 52, 19, 2, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem titleNo_800BDE48[2] = {
    { 8, 3, (int)aNO_800B6724, NULL, NULL, 163, 121, 52, 19, 2, 2 },
    { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
};
MenuWindowItem *titleItems_800BDE80[3] = { titleYes_800BDE10, titleNo_800BDE48 };
MenuWindowList titleWin_800BDE8C = { 2, 0, 8, 1, titleItems_800BDE80 };
ButtonHelpEntry loadMenuButtonHelp_800BDEA4[3] = { { 16, aSelect_800B6738 }, { 167, aExit_800B672C }, { -1 } };
char *msgCardFull_800BDEBC[4] = { aMEMORYCARDFull_800B6748 };
char *msgFormatting_800BDECC[4] = { aFormattingMEMOR_800B67A4, aDoNotRemoveMEMO_800B676C };
char *msgLoading_800BDEDC[4] = { aLoading_800B67D8, aDoNotRemoveMEMO_800B676C };
char *msgSaving_800BDEEC[4] = { aSaving_800B67F0, aDoNotRemoveMEMO_800B676C };
char *msgNoSaveData_800BDEFC[8] = { aNoSaveGameData_800B6804, 0, 0, 0, aMEMORYCARDNotFo_800B682C };
char *msgFormatFailed_800BDF1C[4] = { aFormattingFaile_800B6864 };
char *msgSaveFailed_800BDF2C[4] = { aSaveFailed_800B688C };
char *msgLoadFailed_800BDF3C[4] = { aLoadFailed_800B68A8 };
LoadMenuRow loadMenuRows_800BDF4C[6] = {
    { { 68, 0, 116, 0, 0, 14 }, 1, 4, 4 },
    { { 68, 0, 116, 0, 0, 14 }, 2, 1, 2 },
    { { 18, 0, 72, 0, 0, 14 }, 1, 2, 2, 1 },
    { { 10, 0, 64, 0, 0, 33 }, 1, 4, 15, 0, 0, 0x40 },
    { { 10, 0, 64, 0, 0, 33 }, 2, 1, 2, 0, 0, 1 },
    { { 10, 0, 64, 0, 0, 33 }, 2, 1, 2, 1 },
};
SaveTitle *saveTitle_800BDFAC = (void *)aJadeCocoonLevel_800B6BAC;
char *cardTitles_800BDFB0[30] = {
    aJadeCocoon01_800B6F88, aJadeCocoon02_800B6F6C, aJadeCocoon03_800B6F50, aJadeCocoon04_800B6F34,
    aJadeCocoon05_800B6F18, aJadeCocoon06_800B6EFC, aJadeCocoon07_800B6EE0, aJadeCocoon08_800B6EC4,
    aJadeCocoon09_800B6EA8, aJadeCocoon10_800B6E8C, aJadeCocoon11_800B6E70, aJadeCocoon12_800B6E54,
    aJadeCocoon13_800B6E38, aJadeCocoon14_800B6E1C, aJadeCocoon15_800B6E00, aCombDataTitle01_800B6DE4,
    aCombDataTitle02_800B6DC8, aCombDataTitle03_800B6DAC, aCombDataTitle04_800B6D90, aCombDataTitle05_800B6D74,
    aCombDataTitle06_800B6D58, aCombDataTitle07_800B6D3C, aCombDataTitle08_800B6D20, aCombDataTitle09_800B6D04,
    aCombDataTitle10_800B6CE8, aCombDataTitle11_800B6CCC, aCombDataTitle12_800B6CB0, aCombDataTitle13_800B6C94,
    aCombDataTitle14_800B6C78, aCombDataTitle15_800B6C5C,
};
char *saveFileNames_800BE028[2][15] = {
    {
        aBASLUS00854GAME_800B725C, aBASLUS00854GAME_800B7244, aBASLUS00854GAME_800B722C, aBASLUS00854GAME_800B7214,
        aBASLUS00854GAME_800B71FC, aBASLUS00854GAME_800B71E4, aBASLUS00854GAME_800B71CC, aBASLUS00854GAME_800B71B4,
        aBASLUS00854GAME_800B719C, aBASLUS00854GAME_800B7184, aBASLUS00854GAME_800B716C, aBASLUS00854GAME_800B7154,
        aBASLUS00854GAME_800B713C, aBASLUS00854GAME_800B7124, aBASLUS00854GAME_800B710C,
    },
    {
        aBASLUS00854COMB_800B70F4, aBASLUS00854COMB_800B70DC, aBASLUS00854COMB_800B70C4, aBASLUS00854COMB_800B70AC,
        aBASLUS00854COMB_800B7094, aBASLUS00854COMB_800B707C, aBASLUS00854COMB_800B7064, aBASLUS00854COMB_800B704C,
        aBASLUS00854COMB_800B7034, aBASLUS00854COMB_800B701C, aBASLUS00854COMB_800B7004, aBASLUS00854COMB_800B6FEC,
        aBASLUS00854COMB_800B6FD4, aBASLUS00854COMB_800B6FBC, aBASLUS00854COMB_800B6FA4,
    },
};
SaveIconSrc saveIconSrc_800BE0A0[3] = {
    { 75, 0x380, 254 },
    { 76, 0x3F0, 0x143 },
    { 77, 0x380, 252 },
};
CardHeaderTail cardHeaderTail_800BE0B8 = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 28, 0, 0, 62, 126, 0, 0, 119, 227, 0, 0, 227, 193, 0, 0, 192, 1, 0, 0, 255, 255, 0, 192, 243, 239, 3, 224, 224, 3, 7, 48, 195, 1, 14, 152, 199, 113, 28, 220, 207, 252, 24, 204, 204, 252, 25, 206, 204, 254, 57, 206, 207, 182, 59, 142, 199, 54, 59, 142, 199, 182, 59, 206, 207, 252, 57, 206, 204, 248, 16, 206, 204, 48, 0, 196, 15, 56, 63, 128, 7, 156, 63, 0, 3, 206, 1, 192, 15, 230, 0, 224, 31, 126, 0, 112, 59, 60, 0, 48, 51, 24, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { aNoMemoryCardJp_800B7274, aCardSlotJp_800B7290, aCardSlot1Jp_800B72A8, aCardSlot2Jp_800B72C0, aInsertMemoryCardJp_800B72D8 },
};
int cardFreeBlocks_800BE14C = 0;
int cardSaveCount_800BE150 = 0;

int loadMenuActive_800BE184 BSS = 0;
char *cardSaveNames_800BE188[15] BSS = { 0 };

int dword_800B66C0 SDATA = 24;
const char aSelectGameToLoa_800B66C4[44] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\207\202\201\202\215\202\205\201@\202\224\202\217\201@\202\214\202\217\202\201\202\204\201D";
const char aSelectSaveLocat_800B66F0[44] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\223\202\201\202\226\202\205\201@\202\214\202\217\202\203\202\201\202\224\202\211\202\217\202\216\201D";
const char aYES_800B671C[] = "\202x\202d\202r"; // YES
const char aNO_800B6724[] = "\202m\201@\202n"; // N O
const char aExit_800B672C[] = "\202d\202\230\202\211\202\224"; // Exit
const char aSelect_800B6738[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const char aMEMORYCARDFull_800B6748[36] = "\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\206\202\225\202\214\202\214\201D";
const char aDoNotRemoveMEMO_800B676C[56] = "\202c\202\217\201@\202\216\202\217\202\224\201@\202\222\202\205\202\215\202\217\202\226\202\205\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D";
const char aFormattingMEMOR_800B67A4[52] = "\202e\202\217\202\222\202\215\202\201\202\224\202\224\202\211\202\216\202\207\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D\201D\201D";
const char aLoading_800B67D8[24] = "\202k\202\217\202\201\202\204\202\211\202\216\202\207\201D\201D\201D";
const char aSaving_800B67F0[20] = "\202r\202\201\202\226\202\211\202\216\202\207\201D\201D\201D";
const char aNoSaveGameData_800B6804[40] = "\202m\202\217\201@\202\223\202\201\202\226\202\205\201@\202\207\202\201\202\215\202\205\201@\202\204\202\201\202\224\202\201\201D";
const char aMEMORYCARDNotFo_800B682C[56] = "\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\216\202\217\202\224\201@\202\206\202\217\202\222\202\215\202\201\202\224\202\224\202\205\202\204\201D";
const char aFormattingFaile_800B6864[40] = "\202e\202\217\202\222\202\215\202\201\202\224\202\224\202\211\202\216\202\207\201@\202\206\202\201\202\211\202\214\202\205\202\204\201D";
const char aSaveFailed_800B688C[28] = "\202r\202\201\202\226\202\205\201@\202\206\202\201\202\211\202\214\202\205\202\204\201D";
const char aLoadFailed_800B68A8[28] = "\202k\202\217\202\201\202\204\201@\202\206\202\201\202\211\202\214\202\205\202\204\201D";

void LoadMenuStart_800B7650(void)
{
    LoadMenuInit_800B7674(4, 0);
}

// Matched
void LoadMenuInit_800B7674(int mode, int b)
{
    int i;
    LoadMenuTaskEntry* task;
    LoadMenuWork* work;
    MemCardStart();
    task = (LoadMenuTaskEntry*)&loadMenuTask_8008D480->entry;
    work = (LoadMenuWork*)task->work_14;
    task->flags_0 = (task->flags_0 | 1) & ~0x8000;
    for (i = 0; i < 6; i++)
    {
        ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[i]);
    }
    work->loaded_8 = 0;
    work->nextScreen_24 = -1;
    work->phase_28 = 0;
    switch (mode)
    {
    case 0:
        work->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 0;
        work->flags_54 = 4;
        LoadUiTiy_8002BF74();
        task->next_8 = LoadMenuWaitUiTiy_800B7894;
        break;
    case 1:
        work->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 1;
        work->flags_54 = 4;
        LoadUiTiy_8002BF74();
        task->next_8 = LoadMenuWaitUiTiy_800B7894;
        break;
    case 2:
        work->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 1;
        work->flags_54 = 0xC;
        task->next_8 = LoadMenuTask_800B794C;
        break;
    case 3:
        work->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 1;
        work->flags_54 = 0x4C;
        task->next_8 = LoadMenuTask_800B794C;
        break;
    default:
        work->screen_30 = 0;
        loadMenuRows_800BDF4C[0].cursor_C = 0;
        work->flags_54 = 0;
        LoadUiTiy_8002BF74();
        task->next_8 = LoadMenuWaitUiTiy_800B7894;
        break;
    }
    if (dword_8008BD80 == -1 && !(work->flags_54 & 8))
    {
        work->screen_30 = 1;
        loadMenuRows_800BDF4C[0].cursor_C = 0;
        work->flags_54 = 0x20;
    }
    work->field_5C = 0;
    work->nRead_20 = 0;
    work->field_14 = 0;
    work->field_32 = 0;
    work->field_2C = 0;
    work->field_3C = 0;
    work->field_40 = 0;
    work->rows_64[0] = &loadMenuRows_800BDF4C[0];
    work->rows_64[1] = &loadMenuRows_800BDF4C[1];
    work->rows_64[2] = &loadMenuRows_800BDF4C[2];
    work->rows_64[3] = &loadMenuRows_800BDF4C[3];
    work->rows_64[4] = &loadMenuRows_800BDF4C[4];
    work->rows_64[5] = &loadMenuRows_800BDF4C[5];
    work->summaries_0 = malloc3_8003FC4C(0x780);
    work->fileBuf_4 = malloc3_8003FC4C(sizeof(SaveFile));
    loadMenuActive_800BE184 = 1;
}

void LoadMenuWaitUiTiy_800B7894(LoadMenuTaskEntry* task)
{
    if (uiTiyLoaded_8008B4E8)
    {
        task->next_8 = LoadMenuTask_800B794C;
    }
}

void SetLoadMenuSavePlace_800B78B8(char* place)
{
    ((LoadMenuWork*)loadMenuTask_8008D480->entry.buffer)->place_58 = place;
}

void LoadMenuSetEndOfGame_800B78D0(void)
{
    LoadMenuWork* work;
    saveData_8008B570.field_810 = -1;
    saveData_8008B570.flags_0 |= 0x180;
    work = loadMenuTask_8008D480->entry.buffer;
    work->screen_30 = 1;
    loadMenuRows_800BDF4C[0].cursor_C = 0;
    work->flags_54 = 0x20;
}

int GetLoadMenuLoaded_800B7914(void)
{
    return ((LoadMenuWork*)loadMenuTask_8008D480->entry.buffer)->loaded_8;
}

void LoadMenuNop_800B7934(void)
{
}

int IsLoadMenuActive_800B793C(void)
{
    return loadMenuActive_800BE184;
}

void LoadMenuTask_800B794C(LoadMenuTaskEntry* task, LoadMenuWork* work)
{
    switch (work->phase_28)
    {
    case 0:
        LoadMenuScreen_800B79F8(work);
        break;
    case 2:
        PackSaveFile_800B9A8C(work);
        task->next_8 = WriteSaveTask_800B98C4;
        work->field_2C = 0;
        break;
    case 3:
        task->next_8 = LoadSaveTask_800BA234;
        break;
    case 4:
        task->next_8 = FormatCardWait1_800BA968;
        break;
    case 5:
    case 6:
        task->next_8 = LoadMenuExit_800BAAE0;
        break;
    }
}
const char aLoadGame_800B68E0[] = "\202k\202\217\202\201\202\204\201@\202\207\202\201\202\215\202\205\201H"; // Load game?
const char aOverwriteGame_800B68F8[] = "\202n\202\226\202\205\202\222\202\227\202\222\202\211\202\224\202\205\201@\202\207\202\201\202\215\202\205\201H"; // Overwrite game?
const char aSaveGame_800B6918[] = "\202r\202\201\202\226\202\205\201@\202\207\202\201\202\215\202\205\201H"; // Save game?
const LoadWinRect confirmTextWin_800B6930 = { { 10, 0, 193, 0, 204, 0, 20 } };
const char aReturnToTitle_800B6938[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201H"; // Return to title screen?
const LoadWinRect titlePromptWin_800B6968 = { { 92, 0, 100, 0, 140, 0, 19 } };
const int dword_800B6970 = 0;

// draws the current screen (LoadMenuWork.screen_30) and handles its input:
//  0 top menu (Save / Load / Exit / Title), 1 card slot select, 2 format the card?, 3 the save list,
//  4 load / save / overwrite?, 5 return to the title?, 6 no card in the slot, 7 card full, 8 no save data,
//  9 no empty blocks, 10 damaged data, 11 card not formatted, 13..15 format / save / load failed,
//  18 checking the card
// Matched
void LoadMenuScreen_800B79F8(LoadMenuWork* work)
{
    union // the text position and the window colour share one slot (case 4)
    {
        LoadTextPos pos;
        WindowStyle tail;
    } shared;
    int r;
    UpdateLoadMenuCursor_800B80F8(work);
    switch (work->screen_30)
    {
    case 9:
    case 10:
        saveListWin_800BDB0C.time_4 = 0;
        saveListWin_800BDB0C.flags_0 = 1;
        DrawMenuWindows_8002A5A4(&saveListWin_800BDB0C);
        DrawSaveList_800B867C(work);
        DrawLoadMenuModeTitle_800B8984(work);
        DrawCardSlotLabel_800B8A20(work);
        DrawSaveListPosition_800B8AE4(work);
        DrawLoadMenuHelpText_800B877C(work);
        if (padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 3;
        }
        if (!ReadSaveSummaries_800B9724(work))
        {
            work->nextScreen_24 = 1;
        }
        break;
    case 7:
        DrawMessageBox_800BACBC(msgCardFull_800BDEBC);
        if (!ReadSaveSummaries_800B9724(work) || padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 1;
        }
        break;
    case 11:
        switch (PollCardExist_800BAF0C(loadMenuRows_800BDF4C[1].cursor_C))
        {
        case -1:
        case 0:
        case 2:
        case 3:
            break;
        case 1:
            work->nextScreen_24 = 1;
            break;
        }
        DrawCardSlotChosen_800B847C(work);
        DrawLoadMenuHelpText_800B877C(work);
        if (padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 1;
        }
        break;
    case 8:
        DrawMessageBox_800BACBC(msgNoSaveData_800BDEFC);
        switch (PollCardAccept_800BAE68(loadMenuRows_800BDF4C[1].cursor_C))
        {
        case -1:
        case 0:
        case 4:
            break;
        default:
            work->nextScreen_24 = 1;
            break;
        }
        if (padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 1;
        }
        break;
    case 0:
        topMenuWin_800BDCD0.time_4 = GetTime30Hz_8002C64C();
        topMenuWin_800BDCD0.cursor_C = loadMenuRows_800BDF4C[work->screen_30].cursor_C;
        DrawMenuWindows_8002A5A4(&topMenuWin_800BDCD0);
        DrawLoadMenuHelpText_800B877C(work);
        TopMenuInput_800B9220(work);
        break;
    case 1:
        DrawCardSlotSelect_800B82FC(work);
        DrawLoadMenuHelpText_800B877C(work);
        CardSlotInput_800B92C0(work);
        break;
    case 6:
        switch (PollCardExist_800BAF0C(loadMenuRows_800BDF4C[1].cursor_C))
        {
        case 0:
        case 3:
        case 4:
            WaitCardSync_800BADF4();
            work->nextScreen_24 = 0x12;
            break;
        }
        DrawCardSlotChosen_800B847C(work);
        DrawLoadMenuHelpText_800B877C(work);
        if (padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 1;
        }
        break;
    case 18:
        DrawCardSlotChosen_800B847C(work);
        DrawLoadMenuHelpText_800B877C(work);
        CheckCardTask_800B9360(work);
        break;
    case 2:
        formatWin_800BDD64.time_4 = GetTime30Hz_8002C64C();
        formatWin_800BDD64.cursor_C = loadMenuRows_800BDF4C[work->screen_30].cursor_C;
        DrawFormatPrompt_800B85AC(work);
        FormatPromptInput_800B9470(work);
        break;
    case 3:
        saveListWin_800BDB0C.time_4 = GetTime30Hz_8002C64C();
        saveListWin_800BDB0C.cursor_C = loadMenuRows_800BDF4C[work->screen_30].cursor_C;
        saveListWin_800BDB0C.flags_0 = 2;
        if (!ReadSaveSummaries_800B9724(work))
        {
            work->nextScreen_24 = 1;
        }
        DrawMenuWindows_8002A5A4(&saveListWin_800BDB0C);
        DrawSaveList_800B867C(work);
        DrawLoadMenuModeTitle_800B8984(work);
        DrawCardSlotLabel_800B8A20(work);
        DrawSaveListPosition_800B8AE4(work);
        DrawLoadMenuHelpText_800B877C(work);
        SaveListInput_800B952C(work);
        break;
    case 4:
        saveListWin_800BDB0C.time_4 = 0;
        saveListWin_800BDB0C.cursor_C = loadMenuRows_800BDF4C[3].cursor_C;
        saveListWin_800BDB0C.flags_0 = 4;
        confirmWin_800BDDF8.time_4 = GetTime30Hz_8002C64C();
        confirmWin_800BDDF8.cursor_C = loadMenuRows_800BDF4C[work->screen_30].cursor_C;
        if (!ReadSaveSummaries_800B9724(work))
        {
            work->nextScreen_24 = 1;
        }
        DrawMenuWindows_8002A5A4(&saveListWin_800BDB0C);
        DrawSaveList_800B867C(work);
        DrawLoadMenuModeTitle_800B8984(work);
        DrawCardSlotLabel_800B8A20(work);
        DrawSaveListPosition_800B8AE4(work);
        DrawMenuWindows_8002A5A4(&confirmWin_800BDDF8);
        if (loadMenuRows_800BDF4C[0].cursor_C == 1)
        {
            shared.pos.x_0 = 0xD;
            shared.pos.y_2 = 0xC4;
            DrawText_8003E91C(2, aLoadGame_800B68E0, &shared.pos, 5);
        }
        else if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            if (GetCardSaveName_800BAE4C(loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C))
            {
                shared.pos.x_0 = 0xD;
                shared.pos.y_2 = 0xC4;
                DrawText_8003E91C(2, aOverwriteGame_800B68F8, &shared.pos, 5);
            }
            else
            {
                shared.pos.x_0 = 0xD;
                shared.pos.y_2 = 0xC4;
                DrawText_8003E91C(2, aSaveGame_800B6918, &shared.pos, 5);
            }
        }
        {
            LoadWinRect rect;
            rect = confirmTextWin_800B6930;
            shared.tail.semiTrans_3 = 1;
            shared.tail.colorSet_2 = 0;
            shared.tail.color_0 = uiColor_8008B590;
            DrawWindow_80042460(&rect, &shared.tail, dword_8008D454 + 0x38, 0);
        }
        ConfirmPromptInput_800B9654(work);
        break;
    case 5:
        titleWin_800BDE8C.time_4 = GetTime30Hz_8002C64C();
        titleWin_800BDE8C.cursor_C = loadMenuRows_800BDF4C[work->screen_30].cursor_C;
        shared.pos.x_0 = 0x66;
        shared.pos.y_2 = 0x69;
        DrawText_8003E91C(2, aReturnToTitle_800B6938, &shared.pos, 5);
        {
        LoadWinRect rect;
        WindowStyle color;
        rect = titlePromptWin_800B6968;
        color.semiTrans_3 = 1;
        color.colorSet_2 = 0;
        color.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
        }
        DrawMenuWindows_8002A5A4(&titleWin_800BDE8C);
        if (IsConfirmPressed_8003D288(0, (work->flags_54 >> 6) & 1))
        {
            if (loadMenuRows_800BDF4C[work->screen_30].cursor_C == 0)
            {
                work->flags_54 = 0x10;
                work->phase_28 = 5;
                PlaySfx_80031494(0x7E);
                break;
            }
            work->nextScreen_24 = 0;
            PlaySfx_80031494(0x7D);
        }
        else if (IsCancelPressed_8003D3C0(0, (work->flags_54 >> 6) & 1))
        {
            work->nextScreen_24 = 0;
            PlaySfx_80031494(0x7D);
        }
        break;
    case 13:
        DrawMessageBox_800BACBC(msgFormatFailed_800BDF1C);
        if (padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 1;
        }
        break;
    case 14:
        DrawMessageBox_800BACBC(msgSaveFailed_800BDF2C);
        if (padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 1;
        }
        break;
    case 15:
        DrawMessageBox_800BACBC(msgLoadFailed_800BDF3C);
        if (padPressed_8009194C[(work->flags_54 >> 6) & 1])
        {
            work->nextScreen_24 = 1;
        }
        break;
    }
    DrawButtonHelpBar_8002B004(loadMenuButtonHelp_800BDEA4, 0, 1);
    DrawMenuBackground_8002BE10();
}

void UpdateLoadMenuCursor_800B80F8(LoadMenuWork* work)
{
    MenuCursor cursor;
    int move;
    if (work->nextScreen_24 != -1)
    {
        switch (work->nextScreen_24)
        {
        case 0:
            break;
        case 1:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[3]);
            break;
        case 2:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[2]);
            break;
        case 3:
            break;
        case 4:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[4]);
            if (loadMenuRows_800BDF4C[0].cursor_C == 0)
            {
                loadMenuRows_800BDF4C[4].cursor_C = 1;
            }
            break;
        case 5:
            ResetMenuRow_800BADE0(&loadMenuRows_800BDF4C[5]);
            break;
        }
        work->screen_30 = work->nextScreen_24;
        work->nextScreen_24 = -1;
    }
    if (work->screen_30 >= 6)
    {
        return;
    }
    if (work->screen_30 >= 0)
    {
        cursor.cursor_8 = loadMenuRows_800BDF4C[work->screen_30].cursor_C;
        cursor.scroll_A = loadMenuRows_800BDF4C[work->screen_30].scroll_D;
        cursor.columns_0 = loadMenuRows_800BDF4C[work->screen_30].cols_6;
        cursor.rows_2 = loadMenuRows_800BDF4C[work->screen_30].rows_7;
        cursor.count_4 = loadMenuRows_800BDF4C[work->screen_30].count_8;
        cursor.flags_6 = loadMenuRows_800BDF4C[work->screen_30].flags_B;
        move = UpdateMenuCursor_8003D794(&cursor, (work->flags_54 >> 6) & 1);
        if (loadMenuRows_800BDF4C[work->screen_30].cursor_C != cursor.cursor_8 || move == 8 || move == 7)
        {
            PlaySfx_80031494(0x7F);
        }
        loadMenuRows_800BDF4C[work->screen_30].cursor_C = cursor.cursor_8;
        loadMenuRows_800BDF4C[work->screen_30].scroll_D = cursor.scroll_A;
    }
}
const LoadWinRect cardSlotWin_800B69F4 = { { 93, 0, 18, 0, 124, 0, 18 } };
const char aFormatMemoryCard_800B69FC[] = "\202e\202\217\202\222\202\215\202\201\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201H"; // Format MEMORY CARD?
const LoadWinRect formatPromptWin_800B6A24 = { { 16, 0, 70, 0, 32, 1, 34 } };
const char aSelectMemoryCard_800B6A2C[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D"; // Select MEMORY CARD.
const char emptyText_800B6A54[4] = { 0 };
const char aNoEmptyBlocks_800B6A58[] = "\202m\202\217\201@\202\205\202\215\202\220\202\224\202\231\201@\202\202\202\214\202\217\202\203\202\213\202\223\201@\202\206\202\217\202\222\201@\202\223\202\201\202\226\202\211\202\216\202\207\201@\202\216\202\205\202\227\201@\202\207\202\201\202\215\202\205\202\223\201D"; // No empty blocks for saving new games.
const char aDamagedData_800B6AA4[] = "\202e\202\201\202\211\202\214\202\205\202\204\201@\202\204\202\225\202\205\201@\202\224\202\217\201@\202\204\202\201\202\215\202\201\202\207\202\205\202\204\201@\202\204\202\201\202\224\202\201\201D"; // Failed due to damaged data.
const char aNoMemoryCardInSlot_800B6ADC[] = "\202m\202\217\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\211\202\216\201@\202\223\202\214\202\217\202\224\201D"; // No MEMORY CARD in slot.
const char aCheckingMemoryCard_800B6B0C[] = "\202b\202\210\202\205\202\203\202\213\202\211\202\216\202\207\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D\201D\201D"; // Checking MEMORY CARD...
const LoadWinRect helpTextWin_800B6B3C = { { 10, 0, 193, 0, 44, 1, 20 } };

void DrawCardSlotSelect_800B82FC(LoadMenuWork* work)
{
    int i;
    LoadUiSprite* spr;
    LoadWinRect rect;
    WindowStyle color;
    if (work->screen_30 == 1)
    {
        for (i = 0; i < 2; i++)
        {
            cardSlotWins_800BDBD4[i]->flags_0 = 2;
            if (i == loadMenuRows_800BDF4C[1].cursor_C)
            {
                cardSlotWins_800BDBD4[i]->time_4 = GetTime30Hz_8002C64C();
            }
            else
            {
                cardSlotWins_800BDBD4[i]->time_4 = 0;
            }
        }
    }
    else
    {
        cardSlotWins_800BDBD4[0]->flags_0 = 1;
        cardSlotWins_800BDBD4[1]->flags_0 = 1;
    }
    DrawMenuWindows_8002A5A4(&cardSlot1Win_800BDB64);
    DrawMenuWindows_8002A5A4(&cardSlot2Win_800BDBBC);
    for (spr = cardSlotSprites_800BD9A8; spr->sprite_4 >= 0; spr++)
    {
        DrawUiTiySprt_8002C06C(spr, spr->sprite_4, spr->ot_6);
    }
    rect = cardSlotWin_800B69F4;
    color.semiTrans_3 = 1;
    color.colorSet_2 = 0;
    color.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
}

void DrawCardSlotChosen_800B847C(LoadMenuWork* work)
{
    int i;
    LoadUiSprite* spr;
    LoadWinRect rect;
    WindowStyle color;
    for (i = 0; i < 2; i++)
    {
        if (i == loadMenuRows_800BDF4C[1].cursor_C)
        {
            cardSlotWins_800BDBD4[i]->flags_0 = 4;
        }
        else
        {
            cardSlotWins_800BDBD4[i]->flags_0 = 1;
        }
    }
    DrawMenuWindows_8002A5A4(&cardSlot1Win_800BDB64);
    DrawMenuWindows_8002A5A4(&cardSlot2Win_800BDBBC);
    for (spr = cardSlotSprites_800BD9A8; spr->sprite_4 >= 0; spr++)
    {
        DrawUiTiySprt_8002C06C(spr, spr->sprite_4, spr->ot_6);
    }
    rect = cardSlotWin_800B69F4;
    color.semiTrans_3 = 1;
    color.colorSet_2 = 0;
    color.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
}

void DrawFormatPrompt_800B85AC(LoadMenuWork* work)
{
    LoadTextPos p0;
    LoadTextPos p1;
    LoadWinRect rect;
    WindowStyle color;
    p0.x_0 = 0x13;
    p0.y_2 = 0x49;
    DrawText_8003E91C(2, aMEMORYCARDNotFo_800B682C, &p0, 5);
    p1.x_0 = 0x13;
    p1.y_2 = 0x57;
    DrawText_8003E91C(2, aFormatMemoryCard_800B69FC, &p1, 5);
    rect = formatPromptWin_800B6A24;
    color.semiTrans_3 = 1;
    color.colorSet_2 = 0;
    color.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
    DrawMenuWindows_8002A5A4(&formatWin_800BDD64);
}

void DrawSaveList_800B867C(LoadMenuWork* work)
{
    ScrollArrowArg arrow;
    short arrowPos[4];
    short cursor[6];
    DrawSaveSlots_800B8BD4(work);
    cursor[0] = loadMenuRows_800BDF4C[work->screen_30].cols_6;
    cursor[1] = loadMenuRows_800BDF4C[work->screen_30].rows_7;
    cursor[2] = loadMenuRows_800BDF4C[work->screen_30].count_8;
    cursor[3] = loadMenuRows_800BDF4C[work->screen_30].flags_B;
    cursor[4] = loadMenuRows_800BDF4C[work->screen_30].cursor_C;
    cursor[5] = loadMenuRows_800BDF4C[work->screen_30].scroll_D;
    arrow.field_0 = 2;
    arrow.dir_2 = 1;
    arrowPos[0] = 0x9A;
    arrowPos[1] = 0x2C;
    arrowPos[2] = 0x9A;
    arrowPos[3] = 0xB7;
    DrawScrollArrows_8002B8DC(arrow, cursor, arrowPos, 1);
}

void DrawLoadMenuHelpText_800B877C(LoadMenuWork* work)
{
    switch (work->screen_30)
    {
    case 1:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, aSelectMemoryCard_800B6A2C, &pos, 5);
        break;
    }
    case 2:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, emptyText_800B6A54, &pos, 5);
        break;
    }
    case 3:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, saveListPrompts_800BDA08[loadMenuRows_800BDF4C[0].cursor_C], &pos, 5);
        break;
    }
    case 9:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, aNoEmptyBlocks_800B6A58, &pos, 5);
        break;
    }
    case 10:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, aDamagedData_800B6AA4, &pos, 5);
        break;
    }
    case 6:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, aNoMemoryCardInSlot_800B6ADC, &pos, 5);
        break;
    }
    case 18:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, aCheckingMemoryCard_800B6B0C, &pos, 5);
        break;
    }
    case 11:
    {
        LoadTextPos pos;
        pos.x_0 = 0xE;
        pos.y_2 = 0xC7;
        DrawText_8003E91C(2, aMEMORYCARDNotFo_800B682C, &pos, 5);
        break;
    }
    }
    {
        LoadWinRect rect;
        WindowStyle color;
        rect = helpTextWin_800B6B3C;
        color.semiTrans_3 = 1;
        color.colorSet_2 = 0;
        color.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
    }
}
const LoadWinRect modeTitleWin_800B6B8C = { { 63, 0, 18, 0, 108, 0, 18 } };
const LoadWinRect cardSlotLabelWin_800B6B94 = { { 187, 0, 18, 0, 122, 0, 18 } };
const char aSlash_800B6B9C[] = "\201^"; // /
const LoadWinRect listPositionWin_800B6BA0 = { { 10, 0, 33, 0, 44, 0, 14 } };
const char aMiddleDot_800B6BA8[] = "\201E"; // ・
const char aJadeCocoonLevel_800B6BAC[] = "\202i\202\201\202\204\202\205\201@\202b\202\217\202\203\202\217\202\217\202\216\201^\202k\202\205\202\226\202\205\202\214\201@\202X\202X\201^\202k\202\201\202\224\202\205\202\223\202\224\201@\202f\202\201\202\215\202\205"; // Jade Cocoon/Level 99/Latest Game
const char aCORRIDOR_800B6BF0[] = "\202b\202n\202q\202q\202h\202c\202n\202q"; // CORRIDOR
const char aEND_800B6C04[] = "\202d\202m\202c"; // END
const int dword_800B6C0C = 0;
const int dword_800B6C10 = 0;
const int dword_800B6C14 = 0;
const unsigned short aLatestGame_800B6C18[12] = {
    0x6B82, 0x8182, 0x9482, 0x8582, 0x9382, 0x9482, 0x4081, 0x6682,
    0x8182, 0x8D82, 0x8582,
};
const unsigned short aEndOfGame_800B6C30[12] = {
    0x6482, 0x8E82, 0x8482, 0x4081, 0x8F82, 0x8682, 0x4081, 0x6682,
    0x8182, 0x8D82, 0x8582,
};
const char aCorridor_800B6C48[20] = "\202b\202\217\202\222\202\222\202\211\202\204\202\217\202\222\000\000\015";
const char aCombDataTitle15_800B6C5C[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202T";
const char aCombDataTitle14_800B6C78[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202S";
const char aCombDataTitle13_800B6C94[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202R";
const char aCombDataTitle12_800B6CB0[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202Q";
const char aCombDataTitle11_800B6CCC[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202P";
const char aCombDataTitle10_800B6CE8[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202P\202O";
const char aCombDataTitle09_800B6D04[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202X";
const char aCombDataTitle08_800B6D20[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202W";
const char aCombDataTitle07_800B6D3C[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202V";
const char aCombDataTitle06_800B6D58[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202U";
const char aCombDataTitle05_800B6D74[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202T";
const char aCombDataTitle04_800B6D90[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202S";
const char aCombDataTitle03_800B6DAC[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202R";
const char aCombDataTitle02_800B6DC8[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202Q";
const char aCombDataTitle01_800B6DE4[28] = "\213\312\226\232\225\250\214\352\201^\223o\230^\203f\201[\203^\202O\202P";
const char aJadeCocoon15_800B6E00[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202T";
const char aJadeCocoon14_800B6E1C[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202S";
const char aJadeCocoon13_800B6E38[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202R";
const char aJadeCocoon12_800B6E54[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202Q";
const char aJadeCocoon11_800B6E70[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202P";
const char aJadeCocoon10_800B6E8C[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202P\202O";
const char aJadeCocoon09_800B6EA8[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202X";
const char aJadeCocoon08_800B6EC4[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202W";
const char aJadeCocoon07_800B6EE0[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202V";
const char aJadeCocoon06_800B6EFC[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202U";
const char aJadeCocoon05_800B6F18[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202T";
const char aJadeCocoon04_800B6F34[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202S";
const char aJadeCocoon03_800B6F50[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202R";
const char aJadeCocoon02_800B6F6C[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202Q";
const char aJadeCocoon01_800B6F88[28] = "\202i\202\201\202\204\202\205\202b\202\217\202\203\202\217\202\217\202\216\201^\202O\202P";
const char aBASLUS00854COMB_800B6FA4[] = "BASLUS-00854COMB0414";
const char aBASLUS00854COMB_800B6FBC[] = "BASLUS-00854COMB0413";
const char aBASLUS00854COMB_800B6FD4[] = "BASLUS-00854COMB0412";
const char aBASLUS00854COMB_800B6FEC[] = "BASLUS-00854COMB0411";
const char aBASLUS00854COMB_800B7004[] = "BASLUS-00854COMB0410";
const char aBASLUS00854COMB_800B701C[] = "BASLUS-00854COMB0409";
const char aBASLUS00854COMB_800B7034[] = "BASLUS-00854COMB0408";
const char aBASLUS00854COMB_800B704C[] = "BASLUS-00854COMB0407";
const char aBASLUS00854COMB_800B7064[] = "BASLUS-00854COMB0406";
const char aBASLUS00854COMB_800B707C[] = "BASLUS-00854COMB0405";
const char aBASLUS00854COMB_800B7094[] = "BASLUS-00854COMB0404";
const char aBASLUS00854COMB_800B70AC[] = "BASLUS-00854COMB0403";
const char aBASLUS00854COMB_800B70C4[] = "BASLUS-00854COMB0402";
const char aBASLUS00854COMB_800B70DC[] = "BASLUS-00854COMB0401";
const char aBASLUS00854COMB_800B70F4[] = "BASLUS-00854COMB0400";
const char aBASLUS00854GAME_800B710C[] = "BASLUS-00854GAME0414";
const char aBASLUS00854GAME_800B7124[] = "BASLUS-00854GAME0413";
const char aBASLUS00854GAME_800B713C[] = "BASLUS-00854GAME0412";
const char aBASLUS00854GAME_800B7154[] = "BASLUS-00854GAME0411";
const char aBASLUS00854GAME_800B716C[] = "BASLUS-00854GAME0410";
const char aBASLUS00854GAME_800B7184[] = "BASLUS-00854GAME0409";
const char aBASLUS00854GAME_800B719C[] = "BASLUS-00854GAME0408";
const char aBASLUS00854GAME_800B71B4[] = "BASLUS-00854GAME0407";
const char aBASLUS00854GAME_800B71CC[] = "BASLUS-00854GAME0406";
const char aBASLUS00854GAME_800B71E4[] = "BASLUS-00854GAME0405";
const char aBASLUS00854GAME_800B71FC[] = "BASLUS-00854GAME0404";
const char aBASLUS00854GAME_800B7214[] = "BASLUS-00854GAME0403";
const char aBASLUS00854GAME_800B722C[] = "BASLUS-00854GAME0402";
const char aBASLUS00854GAME_800B7244[] = "BASLUS-00854GAME0401";
const char aBASLUS00854GAME_800B725C[] = "BASLUS-00854GAME0400";
const char aNoMemoryCardJp_800B7274[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202\252\202\240\202\350\202\334\202\271\202\361"; // メモリーカードがありません
const char aCardSlotJp_800B7290[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373"; // メモリーカード差込口
const char aCardSlot1Jp_800B72A8[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373\202P"; // メモリーカード差込口１
const char aCardSlot2Jp_800B72C0[] = "\203\201\203\202\203\212\201[\203J\201[\203h\215\267\215\236\214\373\202Q"; // メモリーカード差込口２
const char aInsertMemoryCardJp_800B72D8[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202\360\203Z\203b\203g\202\265\202\304\202\255\202\276\202\263\202\242"; // メモリーカードをセットしてください
const char aDirWildcard_800B72FC[4] = { 42 };
const CardTag aCRD0_800B7300 = { "CRD0" };
const char aMemoryCard1Jp_800B7308[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202P"; // メモリーカード１
const LoadMenuItemPair cardSlotMenuItem1_800B731C = {
    {
        { 8, 3, (int)aMemoryCard1Jp_800B7308, NULL, NULL, 40, 100, 100, 34, 2, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const char aMemoryCard2Jp_800B7354[] = "\203\201\203\202\203\212\201[\203J\201[\203h\202Q"; // メモリーカード２
const LoadMenuItemPair cardSlotMenuItem2_800B7368 = {
    {
        { 8, 3, (int)aMemoryCard2Jp_800B7354, NULL, NULL, 180, 100, 100, 34, 2, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};

void DrawLoadMenuModeTitle_800B8984(LoadMenuWork* work)
{
    LoadWinRect rect;
    WindowStyle color;
    DrawUiTiySprt_8002C06C(&modeTitleSprites_800BD998[loadMenuRows_800BDF4C[0].cursor_C], modeTitleSprites_800BD998[loadMenuRows_800BDF4C[0].cursor_C].sprite_4, modeTitleSprites_800BD998[loadMenuRows_800BDF4C[0].cursor_C].ot_6);
    rect = modeTitleWin_800B6B8C;
    color.semiTrans_3 = 1;
    color.colorSet_2 = 0;
    color.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
}

// Matched
void DrawCardSlotLabel_800B8A20(LoadMenuWork* work)
{
    LoadTextPos p0 = { 0xBF, 0x15 };
    LoadTextPos p1;
    LoadWinRect rect;
    WindowStyle color;
    DrawUiTiySprt_8002C06C(&p0, 0x27, 1);
    p1.x_0 = 0x124;
    p1.y_2 = 0x15;
    DrawUiTiySprt_8002C06C(&p1, (loadMenuRows_800BDF4C[1].cursor_C == 1) << 1, 1);
    rect = cardSlotLabelWin_800B6B94;
    color.semiTrans_3 = 1;
    color.colorSet_2 = 0;
    color.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
}

void DrawSaveListPosition_800B8AE4(LoadMenuWork* work)
{
    LoadTextPos p0;
    LoadTextPos p1;
    LoadTextPos p2;
    LoadWinRect rect;
    WindowStyle color;
    p0.x_0 = 0x1C;
    p0.y_2 = 0x24;
    DrawNumberRightAlignedFont1_8003F264(&p0, loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C + 1, 5);
    p1.x_0 = 0x1C;
    p1.y_2 = 0x24;
    DrawText_8003E91C(1, aSlash_800B6B9C, &p1, 5);
    p2.x_0 = 0x32;
    p2.y_2 = 0x24;
    DrawNumberRightAlignedFont1_8003F264(&p2, 0xF, 5);
    rect = listPositionWin_800B6BA0;
    color.semiTrans_3 = 1;
    color.colorSet_2 = 0;
    color.color_0 = uiColor_8008B590;
    DrawWindow_80042460(&rect, &color, dword_8008D454 + 0x38, 0);
}

// Matched
void DrawSaveSlots_800B8BD4(LoadMenuWork* work)
{
    LoadTextPos p0;
    LoadTextPos p1;
    LoadTextPos p2;
    LoadTextPos p3;
    LoadTextPos p4;
    LoadTextPos p5;
    int i;
    int j;
    int save;
    int digits;
    int yan;
    LoadUiSprite* spr;
    LoadUiSprite* icon;
    for (i = -1; i < 5; i++)
    {
        save = loadMenuRows_800BDF4C[3].scroll_D + i;
        if (!((save >= 0 && save < 15) || i == 0 || i == 1))
        {
            continue;
        }
        if (save >= work->nRead_20 - 1)
        {
            p0.x_0 = 0x7D;
            p0.y_2 = i * 33 + 0x39;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p0, 0x9C, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
        }
        else if (!GetCardSaveName_800BAE4C(save))
        {
            p1.x_0 = 0x8B;
            p1.y_2 = i * 33 + 0x39;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p1, 0x74, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
        }
        else
        {
            for (j = 0; j < 9; j++)
            {
                if (j < 6)
                {
                    if (j == 5)
                    {
                        yan = work->summaries_0[save].vals_28[5];
                        digits = 0;
                        do
                        {
                            yan /= 10;
                            digits++;
                        } while (yan);
                        p2.x_0 = saveSlotFieldPos_800BD93C[j].x_0 + digits * 7;
                        p2.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawSmallNumber9_8002C414(&p2, work->summaries_0[save].vals_28[j], 1);
                    }
                    else
                    {
                        p2.x_0 = saveSlotFieldPos_800BD93C[j].x_0;
                        p2.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawSmallNumber3_8002C290(&p2, work->summaries_0[save].vals_28[j], 1);
                    }
                    if ((j == 3 || j == 4) && work->summaries_0[save].vals_28[j] < 10)
                    {
                        p2.x_0 = saveSlotFieldPos_800BD93C[j].x_0 - 8;
                        p2.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        DrawSmallNumber3_8002C290(&p2, 0, 1);
                    }
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                }
                else if (j == 6)
                {
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                    p3.x_0 = saveSlotFieldPos_800BD93C[6].x_0;
                    p3.y_2 = saveSlotFieldPos_800BD93C[6].y_2 + i * 33;
                    DrawSmallText_8002FAA0(0, &p3.x_0, work->summaries_0[save].name_0, 1);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                }
                else if (j == 7)
                {
                    p3.x_0 = saveSlotFieldPos_800BD93C[j].x_0;
                    p3.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                    DrawText_8003E91C(1, work->summaries_0[save].text_C, &p3, 1);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                    if (work->summaries_0[save].corridor_26 >= 0)
                    {
                        p3.x_0 = saveSlotFieldPos_800BD93C[j].x_0 + 0x38;
                        p3.y_2 = saveSlotFieldPos_800BD93C[j].y_2 + i * 33;
                        AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
                        DrawNumberRightAlignedFont1_8003F264(&p3, work->summaries_0[save].corridor_26, 1);
                        AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
                    }
                }
                else if (j == 8)
                {
                    icon = &saveIconSprites_800BD9E8[work->summaries_0[save].icon_24];
                    p3.x_0 = icon->x_0;
                    p3.y_2 = icon->y_2 + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + icon->ot_6 * 4);
                    DrawUiTiySprt_8002C06C(&p3, icon->sprite_4, icon->ot_6);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + icon->ot_6 * 4);
                }
                for (spr = saveSlotSprites_800BD960; spr->sprite_4 > 0; spr++)
                {
                    p3.x_0 = spr->x_0;
                    p3.y_2 = spr->y_2 + i * 33;
                    AddClipDrawAreaPrim_80033308(dword_8008D454 + spr->ot_6 * 4);
                    DrawUiTiySprt_8002C06C(&p3, spr->sprite_4, spr->ot_6);
                    AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + spr->ot_6 * 4);
                }
            }
            p2.x_0 = saveSlotFieldPos_800BD93C[1].x_0;
            p2.y_2 = saveSlotFieldPos_800BD93C[1].y_2 + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawUiTiySprt_8002C06C(&p2, 0xDA, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
            p4.x_0 = saveSlotFieldPos_800BD93C[3].x_0 + 2;
            p4.y_2 = (saveSlotFieldPos_800BD93C[3].y_2 - 4) + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawText_8003E91C(2, aMiddleDot_800B6BA8, &p4, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
            p5.x_0 = saveSlotFieldPos_800BD93C[3].x_0 + 2;
            p5.y_2 = saveSlotFieldPos_800BD93C[3].y_2 + i * 33;
            AddClipDrawAreaPrim_80033308(dword_8008D454 + 4);
            DrawText_8003E91C(2, aMiddleDot_800B6BA8, &p5, 1);
            AddDrawAreaPrim_8003326C(&saveListClip_800BDA10, dword_8008D454 + 4);
        }
    }
}

void TopMenuInput_800B9220(LoadMenuWork* work)
{
    if (IsConfirmPressed_8003D288(1, (work->flags_54 >> 6) & 1))
    {
        switch (loadMenuRows_800BDF4C[0].cursor_C)
        {
        case 0:
        case 1:
            work->nextScreen_24 = 1;
            break;
        case 2:
            work->phase_28 = 5;
            break;
        case 3:
            work->nextScreen_24 = 5;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, (work->flags_54 >> 6) & 1))
    {
        work->phase_28 = 5;
    }
}

#if 0
// Not matched: only a dead byte load (lbu $v1) of the options struct in the prologue is missing
void CardSlotInput_800B92C0(LoadMenuWork* work)
{
    if (IsConfirmPressed_8003D288(0, (work->flags_54 >> 6) & 1))
    {
        PlaySfx_80031494(0x7E);
        WaitCardSync_800BADF4();
        work->nextScreen_24 = 0x12;
    }
    else if (IsCancelPressed_8003D3C0(1, (work->flags_54 >> 6) & 1))
    {
        if (work->flags_54 & 0x24)
        {
            work->phase_28 = 5;
        }
        else
        {
            work->nextScreen_24 = 0;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(load, CardSlotInput_800B92C0);

void CheckCardTask_800B9360(LoadMenuWork* work)
{
    switch (PollCardAccept_800BAE68(loadMenuRows_800BDF4C[1].cursor_C))
    {
    case 0:
    case 3:
        ScanCardSaves_800BAFB0(loadMenuRows_800BDF4C[1].cursor_C);
        PlaySfx_80031494(0x7E);
        if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            if (GetCardFreeBlocks_800BAE2C() || GetCardSaveCount_800BAE3C())
            {
                work->nRead_20 = 0;
                work->nextScreen_24 = 3;
            }
            else
            {
                work->nextScreen_24 = 7;
            }
        }
        else if (GetCardSaveCount_800BAE3C())
        {
            work->nRead_20 = 0;
            work->nextScreen_24 = 3;
        }
        else
        {
            work->nextScreen_24 = 8;
        }
        break;
    case 4:
        if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            work->nextScreen_24 = 2;
        }
        else
        {
            work->nextScreen_24 = 0xB;
        }
        break;
    case -1:
        break;
    default:
        work->nextScreen_24 = 6;
        break;
    }
}

void FormatPromptInput_800B9470(LoadMenuWork* work)
{
    int status = PollCardAccept_800BAE68(loadMenuRows_800BDF4C[1].cursor_C);
    if (status < -1 || (status > 0 && status != 4))
    {
        work->nextScreen_24 = 1;
    }
    if (IsCancelPressed_8003D3C0(1, (work->flags_54 >> 6) & 1))
    {
        work->nextScreen_24 = 1;
    }
    if (IsConfirmPressed_8003D288(1, (work->flags_54 >> 6) & 1))
    {
        if (loadMenuRows_800BDF4C[2].cursor_C == 0)
        {
            work->phase_28 = 4;
        }
        if (loadMenuRows_800BDF4C[2].cursor_C == 1)
        {
            work->nextScreen_24 = 1;
        }
    }
}

void SaveListInput_800B952C(LoadMenuWork* work)
{
    int save = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    if (IsCancelPressed_8003D3C0(1, (work->flags_54 >> 6) & 1))
    {
        work->nextScreen_24 = 1;
    }
    if (IsConfirmPressed_8003D288(0, (work->flags_54 >> 6) & 1))
    {
        if (loadMenuRows_800BDF4C[0].cursor_C == 1)
        {
            if (save < work->nRead_20 - 1)
            {
                if (GetCardSaveName_800BAE4C(save))
                {
                    work->nextScreen_24 = 4;
                    PlaySfx_80031494(0x7E);
                }
                else
                {
                    PlaySfx_80031494(0x7C);
                }
            }
            else
            {
                PlaySfx_80031494(0x7C);
            }
        }
        else if (loadMenuRows_800BDF4C[0].cursor_C == 0)
        {
            if (save < work->nRead_20 - 1)
            {
                if (!GetCardSaveName_800BAE4C(save) && GetCardFreeBlocks_800BAE2C() <= 0)
                {
                    work->nextScreen_24 = 9;
                    PlaySfx_80031494(0x7C);
                }
                else
                {
                    work->nextScreen_24 = 4;
                    PlaySfx_80031494(0x7E);
                }
            }
            else
            {
                PlaySfx_80031494(0x7C);
            }
        }
    }
}

void ConfirmPromptInput_800B9654(LoadMenuWork* work)
{
    if (IsCancelPressed_8003D3C0(1, (work->flags_54 >> 6) & 1))
    {
        work->nextScreen_24 = 3;
    }
    if (IsConfirmPressed_8003D288(0, (work->flags_54 >> 6) & 1))
    {
        if (loadMenuRows_800BDF4C[4].cursor_C == 0)
        {
            PlaySfx_80031494(0x7E);
            if (loadMenuRows_800BDF4C[0].cursor_C == 1)
            {
                WaitCardSync_800BADF4();
                work->phase_28 = 3;
            }
            else if (loadMenuRows_800BDF4C[0].cursor_C == 0)
            {
                WaitCardSync_800BADF4();
                work->phase_28 = 2;
            }
        }
        else
        {
            PlaySfx_80031494(0x7D);
            work->nextScreen_24 = 3;
        }
    }
}

int ReadSaveSummaries_800B9724(LoadMenuWork* work)
{
    int ret = 1;
    int cmd = 0;
    int res = 0;
    int chan = loadMenuRows_800BDF4C[1].cursor_C << 4;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        if (work->nRead_20 < 15)
        {
            name = GetCardSaveName_800BAE4C(work->nRead_20);
            if (name)
            {
                MemCardReadFile(chan, name, &work->summaries_0[work->nRead_20], 0x280, 0x80);
            }
            else if (work->nRead_20 == 14)
            {
                work->nRead_20 = 15;
            }
            work->nRead_20++;
        }
        else
        {
            MemCardExist(chan);
        }
        break;
    case 1:
        switch (cmd)
        {
        case 3:
            switch (res)
            {
            case 0:
                if (work->nRead_20 == 15)
                {
                    work->nRead_20 = 16;
                }
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                ret = 0;
                break;
            }
            break;
        case 1:
            if (res != 0)
            {
                ret = 0;
            }
            break;
        }
        break;
    }
    return ret;
}

// the save task: writes the save file to the card, then back to the menu (task callback: void* params copied
// into typed locals)
// Matched
void WriteSaveTask_800B98C4(void* t, void* buf)
{
    LoadMenuTaskEntry* task = t;
    LoadMenuWork* work = buf;
    int cmd = 0;
    int res = 0;
    int chan = loadMenuRows_800BDF4C[1].cursor_C << 4;
    int save = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        name = GetCardSaveName_800BAE4C(save);
        if (!name)
        {
            MemCardCreateFile(chan, saveFileNames_800BE028[0][save], 1);
            name = saveFileNames_800BE028[0][save];
        }
        MemCardWriteFile(chan, name, work->fileBuf_4, 0, sizeof(SaveFile));
        break;
    case 1:
        if (cmd == 4)
        {
            switch (res)
            {
            case 0:
                task->next_8 = LoadMenuTask_800B794C;
                work->phase_28 = 0;
                work->nextScreen_24 = 3;
                PlaySfx_80031494(0x7E);
                MemCopy_800403E8(&work->summaries_0[save], &work->fileBuf_4->summary_280, 0x80);
                ScanCardSaves_800BAFB0(loadMenuRows_800BDF4C[1].cursor_C);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                task->next_8 = LoadMenuTask_800B794C;
                work->phase_28 = 0;
                work->nextScreen_24 = 0xE;
                break;
            }
        }
        break;
    }
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgSaving_800BDEEC);
    DrawMenuBackground_8002BE10();
}

// packs saveData_8008B570 into the save file to write, with its summary and title
// Matched
void PackSaveFile_800B9A8C(LoadMenuWork* work)
{
    unsigned short buf[12];
    SaveSummary* sm;
    SaveSummary* sm2;
    SaveBody* body;
    SaveTitle* title;
    unsigned int offset;
    int i;
    int j;
    int k;
    int l;
    int idx;
    int lv;
    Minion* minion;
    SaveMinion* packedMinion;
    UnitStats* unit;
    SaveStats* packedUnit;

    sm = &work->fileBuf_4->summary_280;
    sm->vals_28[0] = saveData_8008B570.levantStatus_7C8.level_44;
    sm->vals_28[1] = saveData_8008B570.levantStatus_7C8.hp_8.cur_0;
    sm->vals_28[2] = saveData_8008B570.levantStatus_7C8.hp_8.max_2;
    sm->vals_28[3] = PlayTimeHours_800BAC14(saveData_8008B570.playTime_4);
    sm->vals_28[4] = PlayTimeMinutes_800BAC68(saveData_8008B570.playTime_4);
    sm->vals_28[5] = saveData_8008B570.inv_24.yan_0;
    MemCopy_800403E8(sm->name_0, saveData_8008B570.levantStatus_7C8.name_10, 0xC);
    sm->corridor_26 = saveData_8008B570.field_810;
    if (saveData_8008B570.field_810 == -2)
    {
        sm->icon_24 = 0;
    }
    else if (saveData_8008B570.field_810 == -1)
    {
        sm->icon_24 = 1;
    }
    else
    {
        sm->icon_24 = 2;
    }
    if (sm->icon_24 == 2)
    {
        MemCopy_800403E8(sm->text_C, aCORRIDOR_800B6BF0, 0x18);
    }
    else if (sm->icon_24 == 1)
    {
        MemCopy_800403E8(sm->text_C, aEND_800B6C04, 0x18);
    }
    else
    {
        MemCopy_800403E8(sm->text_C, work->place_58, 0x18);
    }
    body = &work->fileBuf_4->body_300;
    MemCopy_800403E8(body, &saveData_8008B570, 0x988);
    for (i = 0; i < 15; i++)
    {
        minion = &saveData_8008B570.minions[i];
        packedMinion = &body->minions_988[i];
        packedMinion->id_0 = minion->id;
        packedMinion->species_2 = minion->species_2;
        packedMinion->field_3 = minion->field_3;
        for (j = 0; j < 0x30; j++)
        {
            packedMinion->species_4[j] = minion->species_4C[j];
        }
        for (j = 0; j < 8; j++)
        {
            packedMinion->field_34[j] = minion->ancestorElements_7C[j];
        }
        packedMinion->field_74 = minion->field_CC;
        packedMinion->skills_86 = minion->skills_DE;
        packedMinion->magicBits_9C = minion->magicBits_F4;
        packedMinion->status_3C.status_0 = minion->status_84.status_0;
        packedMinion->status_3C.exp_4 = minion->status_84.exp_4;
        packedMinion->status_3C.hp_8 = minion->status_84.hp_8;
        packedMinion->status_3C.mp_C = minion->status_84.mp_C;
        for (j = 0; j < 0xC; j++)
        {
            packedMinion->status_3C.modifiers_10[j] = minion->status_84.modifiers_20[j];
        }
        packedMinion->status_3C.stats_1C = minion->status_84.stats_2C;
        for (j = 0; j < 4; j++)
        {
            packedMinion->status_3C.element_2E[j] = minion->status_84.element_3E[j];
        }
        packedMinion->status_3C.elementMask_32 = minion->status_84.elementMask_42;
        packedMinion->status_3C.level_34 = minion->status_84.level_44;
        packedMinion->status_3C.field_35 = minion->status_84.fixedStats_45;
        for (j = 0; j < 6; j++)
        {
            for (k = 0; k < 10; k++)
            {
                body->ancestorNames_17F8[i][j][k] = minion->ancestors_4[j][k];
            }
        }
        for (k = 0; k < 10; k++)
        {
            body->minionNames_1B7C[i][k] = minion->status_84.name_10[k];
        }
    }
    for (l = 0; l < 12; l++)
    {
        unit = &saveData_8008B570.items[l];
        packedUnit = &body->items_12E8[l];
        packedUnit->species_4C = unit->species_5C;
        packedUnit->status_0.status_0 = unit->st_0.status_0;
        packedUnit->status_0.exp_4 = unit->st_0.exp_4;
        packedUnit->status_0.hp_8 = unit->st_0.hp_8;
        packedUnit->status_0.mp_C = unit->st_0.mp_C;
        for (j = 0; j < 0xC; j++)
        {
            packedUnit->status_0.modifiers_10[j] = unit->st_0.modifiers_20[j];
        }
        packedUnit->status_0.stats_1C = unit->st_0.stats_2C;
        for (j = 0; j < 4; j++)
        {
            packedUnit->status_0.element_2E[j] = unit->st_0.element_3E[j];
        }
        packedUnit->status_0.elementMask_32 = unit->st_0.elementMask_42;
        packedUnit->status_0.level_34 = unit->st_0.level_44;
        packedUnit->status_0.field_35 = unit->st_0.fixedStats_45;
        for (k = 0; k < 10; k++)
        {
            body->itemNames_1C30[l][k] = unit->st_0.name_10[k];
        }
    }
    sm->sum_40 = 0;
    for (offset = 0x300; offset < 0x1FC0; offset++)
    {
        sm->sum_40 += ((unsigned char*)work->fileBuf_4)[offset];
    }
    sm2 = &work->fileBuf_4->summary_280;
    idx = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    IntToText_8003F610(buf, sm2->vals_28[0]);
    lv = sm2->vals_28[0];
    title = saveTitle_800BDFAC;
    if (lv > 100)
    {
        lv = 99;
    }
    title->f.level_24[0] = 0x82;
    title->f.level_24[1] = lv / 10 + 0x4F;
    lv %= 10;
    title->f.level_24[2] = 0x82;
    title->f.level_24[3] = lv % 10 + 0x4F;
    switch (sm2->icon_24)
    {
    case 0:
        memcpy(saveTitle_800BDFAC->f.place_2A, aLatestGame_800B6C18, 23);
        break;
    case 1:
        memcpy(saveTitle_800BDFAC->f.place_2A, aEndOfGame_800B6C30, 23);
        break;
    case 2:
    default:
        memcpy(saveTitle_800BDFAC->f.place_2A, aCorridor_800B6C48, 17);
        break;
    }
    BuildCardHeader_800BB2AC(&work->fileBuf_4->header_0, idx, saveTitle_800BDFAC->str);
}

#if 0
// Not matched: prologue scheduling only: the original sets $a0 = 1 before saving $s1 / copying the second argument
void LoadSaveTask_800BA234(LoadMenuTaskEntry* task, LoadMenuWork* work)
{
    int cmd = 0;
    int res = 0;
    int chan = loadMenuRows_800BDF4C[1].cursor_C << 4;
    int save = loadMenuRows_800BDF4C[3].scroll_D + loadMenuRows_800BDF4C[3].cursor_C;
    char* name;
    switch (MemCardSync(1, &cmd, &res))
    {
    case 0:
        break;
    case -1:
        name = GetCardSaveName_800BAE4C(save);
        if (name)
        {
            MemCardReadFile(chan, name, work->fileBuf_4, 0, sizeof(SaveFile));
        }
        else
        {
            task->next_8 = LoadMenuTask_800B794C;
            work->phase_28 = 0;
            work->nextScreen_24 = 0xF;
        }
        break;
    case 1:
        if (cmd == 3)
        {
            switch (res)
            {
            case 0:
                if (UnpackSaveFile_800BA3EC(work))
                {
                    work->loaded_8 = 1;
                    task->next_8 = LoadMenuTask_800B794C;
                    work->phase_28 = 6;
                    work->flags_54 |= 1;
                }
                else
                {
                    task->next_8 = LoadMenuTask_800B794C;
                    work->phase_28 = 0;
                    work->nextScreen_24 = 0xA;
                }
                PlaySfx_80031494(0x7E);
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                task->next_8 = LoadMenuTask_800B794C;
                work->phase_28 = 0;
                work->nextScreen_24 = 0xF;
                break;
            }
        }
        break;
    }
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgLoading_800BDEDC);
    DrawMenuBackground_8002BE10();
}
#endif
INCLUDE_OVERLAY_ASM(load, LoadSaveTask_800BA234);

// unpacks the loaded save file into saveData_8008B570; 0 when the checksum or the version is wrong
// Matched
int UnpackSaveFile_800BA3EC(LoadMenuWork* work)
{
    int ret = 0;
    int sum = ret;
    unsigned int offset;
    int i;
    int j;
    int k;
    int l;
    struct UiColorBytes col = saveData_8008B570.uiColor_20.w;
    SaveSummary* sm = &work->fileBuf_4->summary_280;
    Settings set = saveData_8008B570.settings_1C;
    SaveBody* body;
    Minion* minion;
    SaveMinion* packedMinion;
    UnitStats* unit;
    SaveStats* packedUnit;

    for (offset = 0x300; offset < 0x1FC0; offset++)
    {
        sum += ((unsigned char*)work->fileBuf_4)[offset];
    }
    if (sum == sm->sum_40 && work->fileBuf_4->body_300.version_984 == 5)
    {
        body = &work->fileBuf_4->body_300;
        MemCopy_800403E8(&saveData_8008B570, body, 0x988);
        for (i = 0; i < 15; i++)
        {
            minion = &saveData_8008B570.minions[i];
            packedMinion = &body->minions_988[i];
            minion->id = packedMinion->id_0;
            minion->species_2 = packedMinion->species_2;
            minion->field_3 = packedMinion->field_3;
            for (j = 0; j < 0x30; j++)
            {
                minion->species_4C[j] = packedMinion->species_4[j];
            }
            for (j = 0; j < 8; j++)
            {
                minion->ancestorElements_7C[j] = packedMinion->field_34[j];
            }
            minion->field_CC = packedMinion->field_74;
            minion->skills_DE = packedMinion->skills_86;
            minion->magicBits_F4 = packedMinion->magicBits_9C;
            minion->status_84.status_0 = packedMinion->status_3C.status_0;
            minion->status_84.exp_4 = packedMinion->status_3C.exp_4;
            minion->status_84.hp_8 = packedMinion->status_3C.hp_8;
            minion->status_84.mp_C = packedMinion->status_3C.mp_C;
            for (j = 0; j < 0xC; j++)
            {
                minion->status_84.modifiers_20[j] = packedMinion->status_3C.modifiers_10[j];
            }
            minion->status_84.stats_2C = packedMinion->status_3C.stats_1C;
            for (j = 0; j < 4; j++)
            {
                minion->status_84.element_3E[j] = packedMinion->status_3C.element_2E[j];
            }
            minion->status_84.elementMask_42 = packedMinion->status_3C.elementMask_32;
            minion->status_84.level_44 = packedMinion->status_3C.level_34;
            minion->status_84.fixedStats_45 = packedMinion->status_3C.field_35;
            minion->status_84.equipment_1C[0] = 0xFF;
            minion->status_84.equipment_1C[1] = 0xFF;
            minion->status_84.equipment_1C[2] = 0xFF;
            minion->status_84.equipment_1C[3] = 0xFF;
            for (j = 0; j < 6; j++)
            {
                for (k = 0; k < sizeof(minion->ancestors_4[j]); k++)
                {
                    if (k < 10)
                    {
                        minion->ancestors_4[j][k] = body->ancestorNames_17F8[i][j][k];
                    }
                    else
                    {
                        minion->ancestors_4[j][k] = 0;
                    }
                }
            }
            for (k = 0; k < sizeof(minion->status_84.name_10); k++)
            {
                if (k < 10)
                {
                    minion->status_84.name_10[k] = body->minionNames_1B7C[i][k];
                }
                else
                {
                    minion->status_84.name_10[k] = 0;
                }
            }
        }
        for (l = 0; l < 12; l++)
        {
            unit = &saveData_8008B570.items[l];
            packedUnit = &body->items_12E8[l];
            unit->species_5C = packedUnit->species_4C;
            unit->st_0.status_0 = packedUnit->status_0.status_0;
            unit->st_0.exp_4 = packedUnit->status_0.exp_4;
            unit->st_0.hp_8 = packedUnit->status_0.hp_8;
            unit->st_0.mp_C = packedUnit->status_0.mp_C;
            for (j = 0; j < 0xC; j++)
            {
                unit->st_0.modifiers_20[j] = packedUnit->status_0.modifiers_10[j];
            }
            unit->st_0.stats_2C = packedUnit->status_0.stats_1C;
            for (j = 0; j < 4; j++)
            {
                unit->st_0.element_3E[j] = packedUnit->status_0.element_2E[j];
            }
            unit->st_0.elementMask_42 = packedUnit->status_0.elementMask_32;
            unit->st_0.level_44 = packedUnit->status_0.level_34;
            unit->st_0.fixedStats_45 = packedUnit->status_0.field_35;
            unit->st_0.equipment_1C[0] = 0xFF;
            unit->st_0.equipment_1C[1] = 0xFF;
            unit->st_0.equipment_1C[2] = 0xFF;
            unit->st_0.equipment_1C[3] = 0xFF;
            for (k = 0; k < sizeof(unit->st_0.name_10); k++)
            {
                if (k < 10)
                {
                    unit->st_0.name_10[k] = body->itemNames_1C30[l][k];
                }
                else
                {
                    unit->st_0.name_10[k] = 0;
                }
            }
        }
        if (work->flags_54 & 8)
        {
            saveData_8008B570.settings_1C = set;
            saveData_8008B570.uiColor_20.w = col;
        }
        ret = 1;
    }
    return ret;
}

void FormatCardWait1_800BA968(LoadMenuTaskEntry* task)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgFormatting_800BDECC);
    DrawMenuBackground_8002BE10();
    task->next_8 = FormatCardWait2_800BA9AC;
}

void FormatCardWait2_800BA9AC(LoadMenuTaskEntry* task)
{
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgFormatting_800BDECC);
    DrawMenuBackground_8002BE10();
    task->next_8 = FormatCardTask_800BA9F0;
}

void FormatCardTask_800BA9F0(LoadMenuTaskEntry* task, LoadMenuWork* work)
{
    switch (MemCardFormat(loadMenuRows_800BDF4C[1].cursor_C << 4))
    {
    case 0:
        task->next_8 = LoadMenuTask_800B794C;
        work->phase_28 = 0;
        work->nextScreen_24 = 3;
        work->nRead_20 = 0;
        ScanCardSaves_800BAFB0(loadMenuRows_800BDF4C[1].cursor_C);
        work->field_5C = 0;
        break;
    case 1:
        task->next_8 = LoadMenuTask_800B794C;
        work->phase_28 = 0;
        work->nextScreen_24 = 1;
        break;
    case 2:
        task->next_8 = LoadMenuTask_800B794C;
        work->phase_28 = 0;
        work->nextScreen_24 = 0xD;
        break;
    case -1:
        break;
    }
    WaitCardSync_800BADF4();
    DrawLoadingIcon_8003CD5C();
    DrawMessageBox_800BACBC(msgFormatting_800BDECC);
    DrawMenuBackground_8002BE10();
}

void LoadMenuExit_800BAAE0(LoadMenuTaskEntry* task, LoadMenuWork* work)
{
    free3_8003FC6C(work->summaries_0);
    free3_8003FC6C(work->fileBuf_4);
    loadMenuActive_800BE184 = 0;
    task->flags_0 = (task->flags_0 & ~1) | 0x8000;
    MemCardStop();
    task->next_8 = LoadMenuStart_800B7650;
    if (!(work->flags_54 & 8))
    {
        FreeActiveOverlay_8002C014();
        if (work->flags_54 & 0x20)
        {
            RequestAreaReload_80027314();
            RequestGameMode_800A6D30(GetGameMode_800A6D50(1));
        }
        else if (!(work->flags_54 & 4))
        {
            RequestAreaReload_80027314();
            RequestGameMode_800A6D30(GetGameMode_800A6D50(1));
        }
        if (work->flags_54 & 1)
        {
            SaveData* save = &saveData_8008B570;
            save->field_2E2 = -1;
            save->mapId_2E4[0].field_2 = -1;
            save->mapId_2E4[1].field_2 = -1;
            save->mapId_2E4[2].field_2 = -1;
            save->mapId_2E4[3].field_2 = -1;
            mapStartMode_80091C54 = 0;
            if (!(work->flags_54 & 4))
            {
                unknownFlags_8008D678 |= 0x18000000;
            }
        }
        if (work->flags_54 & 0x10)
        {
            HaltEventsFadeStopMovie_80011BCC();
        }
    }
}

int PlayTimeHours_800BAC14(int frames)
{
    return frames / 216000 % 60;
}

int PlayTimeMinutes_800BAC68(int frames)
{
    return frames / 3600 % 60;
}

void DrawMessageBox_800BACBC(char** lines)
{
    TextSize sz;
    MsgBoxRect box;
    int i;
    sz = MeasureTextLines_8003E3B4((int*)lines);
    box.x_0 = (0x13A - sz.w) / 2;
    box.y_2 = (0xEA - sz.h) / 2;
    box.w_4 = sz.w + 6;
    box.h_6 = sz.h + 3;
    if (sz.h >= 0x10)
    {
        box.h_6 = sz.h + 6;
    }
    for (i = 0; i < 3; i++)
    {
        if (lines[i])
        {
            LoadTextPos pos;
            pos.x_0 = box.x_0 + 3;
            pos.y_2 = box.y_2 + 5 + i * 13;
            DrawText_8003E91C(2, lines[i], &pos, 5);
        }
    }
    {
        WindowStyle color;
        color.semiTrans_3 = 1;
        color.colorSet_2 = 0;
        color.color_0 = uiColor_8008B590;
        DrawWindow_80042460(&box, &color, dword_8008D454 + 0x38, 0);
    }
}

void ResetMenuRow_800BADE0(LoadMenuRow* row)
{
    row->cursor_C = row->initCursor_9;
    row->scroll_D = row->initScroll_A;
}

void WaitCardSync_800BADF4(void)
{
    int result = 0;
    int cmd = 0;
    MemCardSync(0, &cmd, &result);
}

int IsCardReady_800BAE24(void)
{
    return 1;
}

int GetCardFreeBlocks_800BAE2C(void)
{
    return cardFreeBlocks_800BE14C;
}

int GetCardSaveCount_800BAE3C(void)
{
    return cardSaveCount_800BE150;
}

char* GetCardSaveName_800BAE4C(int i)
{
    char** names = cardSaveNames_800BE188;
    return names[i];
}

int PollCardAccept_800BAE68(int slot)
{
    int sync[2]; // the MemCardSync command and result
    int ret = -1;
    int state;
    int chan = slot << 4;
    sync[0] = 0;
    sync[1] = 0;
    state = MemCardSync(1, &sync[0], &sync[1]);
    switch (state)
    {
    case 0:
        break;
    case -1:
        MemCardAccept(chan);
        break;
    case 1:
        if (sync[0] == 2)
        {
            ret = sync[1];
        }
        break;
    }
    return ret;
}

int PollCardExist_800BAF0C(int slot)
{
    int sync[2]; // the MemCardSync command and result
    int ret = -1;
    int state;
    int chan = slot << 4;
    sync[0] = 0;
    sync[1] = 0;
    state = MemCardSync(1, &sync[0], &sync[1]);
    switch (state)
    {
    case 0:
        break;
    case -1:
        MemCardExist(chan);
        break;
    case 1:
        if (sync[0] == 1)
        {
            ret = sync[1];
        }
        break;
    }
    return ret;
}

// Matched
void ScanCardSaves_800BAFB0(int slot)
{
    CardDirEntry dir[15];
    long files;
    int blocks;
    int found;
    int i;
    i = found = blocks = 0;
    files = 0;
    MemCardGetDirentry(slot << 4, aDirWildcard_800B72FC, dir, &files, 0, 15);
    for (i = found; i < files; i++)
    {
        int fullBlocks = dir[i].size_18 / 0x2000;
        if (dir[i].size_18 & 0x1FFF)
        {
            blocks += fullBlocks + 1;
        }
        else
        {
            blocks += fullBlocks;
        }
    }
    for (i = 0; i < 15; i++)
    {
        if (FindDirEntry_800BB23C(files, saveFileNames_800BE028[0][i], dir))
        {
            found++;
            cardSaveNames_800BE188[i] = saveFileNames_800BE028[0][i];
        }
        else
        {
            cardSaveNames_800BE188[i] = 0;
        }
    }
    cardFreeBlocks_800BE14C = 15 - blocks;
    cardSaveCount_800BE150 = found;
}

// Matched
void ScanCardSavesComb_800BB0E4(int slot)
{
    CardDirEntry dir[15];
    long files;
    int blocks;
    int found;
    int i;
    i = found = blocks = 0;
    files = 0;
    MemCardGetDirentry(slot << 4, aDirWildcard_800B72FC, dir, &files, 0, 15);
    for (i = found; i < files; i++)
    {
        int fullBlocks = dir[i].size_18 / 0x2000;
        if (dir[i].size_18 & 0x1FFF)
        {
            blocks += fullBlocks + 1;
        }
        else
        {
            blocks += fullBlocks;
        }
    }
    for (i = 0; i < 15; i++)
    {
        if (FindDirEntry_800BB23C(files, saveFileNames_800BE028[0][i], dir))
        {
            found++;
            cardSaveNames_800BE188[i] = saveFileNames_800BE028[0][i];
        }
        else if (FindDirEntry_800BB23C(files, saveFileNames_800BE028[1][i], dir))
        {
            found++;
            cardSaveNames_800BE188[i] = saveFileNames_800BE028[1][i];
        }
        else
        {
            cardSaveNames_800BE188[i] = 0;
        }
    }
    cardFreeBlocks_800BE14C = 15 - blocks;
    cardSaveCount_800BE150 = found;
}

// 1 when name is one of the nFiles directory entries (CardDirEntry, 0x28 bytes each)
int FindDirEntry_800BB23C(int nFiles, unsigned char* name, unsigned char* dir)
{
    int i;
    int j;
    int diff;
    int res = 0;
    for (i = 0; i < nFiles; i++, dir += 0x28)
    {
        diff = 0;
        for (j = 0; j < 0x15; j++)
        {
            if (name[j] == 0)
            {
                break;
            }
            if (name[j] != dir[j])
            {
                diff++;
                break;
            }
        }
        if (diff == 0)
        {
            res = 1;
            break;
        }
    }
    return res;
}

#if 0
// Not matched: register allocation (h/i/table pointer in $s0/$s1/$s2 in the original) and the clearing loops are not strength-reduced to a decrementing pointer here
void BuildCardHeader_800BB2AC(CardHeader* header, int idx, char* title)
{
    int i;
    int j;
    RECT rect;
    for (i = 0; i < 3; i++)
    {
        POLY_FT4* poly = &publicTiyPolyFT4s_8008D430[saveIconSrc_800BE0A0[i].poly_0];
        int tp = poly->tpage & 0x1F;
        rect.x = (poly->u0 >> 2) + ((tp << 6) & 0x3FF);
        rect.y = poly->v0 + ((tp / 16) << 8);
        rect.w = 4;
        rect.h = 0x10;
        StoreImage(&rect, (u_long*)header->icon_80[i]);
        DrawSync(0);
        rect.x = saveIconSrc_800BE0A0[i].clutX_4;
        rect.y = saveIconSrc_800BE0A0[i].clutY_6;
        rect.w = 0x10;
        rect.h = 1;
        StoreImage(&rect, (u_long*)header->clut_60);
        DrawSync(0);
    }
    header->magic_0[0] = 'S';
    header->magic_0[1] = 'C';
    header->type_2 = 0x13;
    header->blocks_3 = 1;
    {
        char* titleBuf = header->title_4;
        for (j = 63; j >= 0; j--)
        {
            titleBuf[j] = 0;
        }
    }
    if (title)
    {
        strcpy_8004E2D8(header->title_4, title);
    }
    else
    {
        strcpy_8004E2D8(header->title_4, cardTitles_800BDFB0[idx]);
    }
    for (i = 11; i >= 0; i--)
    {
        header->field_44[i] = 0;
    }
    header->field_50 = 1;
    header->tag_52 = aCRD0_800B7300;
    header->tag_52.c[4] = 0;
    header->field_57 = 0;
    header->field_5C = 0;
    MemCopy_800403E8(header->field_200, cardHeaderTail_800BE0B8.icon_0, 0x80);
}
#endif
INCLUDE_OVERLAY_ASM(load, BuildCardHeader_800BB2AC);

void DrawCardSlotMenu_800BB4A8(short sel)
{
    LoadMenuItemPair slot1 = cardSlotMenuItem1_800B731C;
    LoadMenuItemPair slot2 = cardSlotMenuItem2_800B7368;
    MenuWindowItem* list[3];
    MenuWindowList win;
    int i;
    list[0] = slot1.items_0;
    list[1] = slot2.items_0;
    list[2] = 0;
    win.flags_0 = 2;
    win.time_4 = 0;
    win.open_8 = 8;
    win.cursor_C = 0;
    win.items_10 = list;
    win.ot_14 = 0;
    for (i = 0; i < 2; i++)
    {
        list[i]->flags_0 |= 2;
    }
    win.time_4 = frameCount_8008D3FC;
    win.cursor_C = sel;
    DrawMenuWindows_8002A5A4(&win);
}

// 0x800BB5DC..0x800BD93C: PSY-Q 4.4 LIBMCRD.LIB modules LIBMCRD, USERFUNC and BIOS, linked from the library
// (config/ovl_lib_objs.txt), as are their .rdata, .data and .bss.
