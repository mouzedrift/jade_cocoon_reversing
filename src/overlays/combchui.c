// COMBCHUI.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combchui.h"

extern int MeasureTextWidth_8003E4C8(int);
extern void AlignMenuItem_8002AC88(int, void*, int, void*);
extern void DrawText_8003E91C(int, int, void*, int);

int dword_800A4088 SDATA = 18;
const char aWillPlayer2UseC_800A408C[68] = "\202v\202\211\202\214\202\214\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201@\202\225\202\223\202\205\201@\202b\202n\202m\202s\202q\202n\202k\202k\202d\202q\201@\202Q\201H\000,";
const int aBlankLine_800A40D0 = 0;
const char aYouHaveAMEMORYC_800A40D4[] = "\202\231\202\217\202\225\201@\202\210\202\201\202\226\202\205\201@\202\201\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\227\202\211\202\224\202\210\201@\202\223\202\201\202\226\202\205\202\204\201@\202\204\202\201\202\224\202\201\201D"; // you have a MEMORY CARD with saved data.
const char aOpponentGivesUp_800A4124[] = "\202\217\202\220\202\220\202\217\202\216\202\205\202\216\202\224\201@\202\207\202\211\202\226\202\205\202\223\201@\202\225\202\220\201D\201@\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\217\202\216\202\214\202\231\201@\202\220\202\214\202\201\202\231\201@\202\211\202\206"; // opponent gives up. You can only play if
const char aDefeatAllEnemie_800A4174[] = "\202\204\202\205\202\206\202\205\202\201\202\224\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\217\202\222\201@\202\227\202\210\202\205\202\216\201@\202\231\202\217\202\225\202\222"; // defeat all enemies or when your
const char aSelectUpToThree_800A41B4[] = "\202\223\202\205\202\214\202\205\202\203\202\224\201@\202\225\202\220\201@\202\224\202\217\201@\202\224\202\210\202\222\202\205\202\205\201D\201@\202x\202\217\202\225\201@\202\227\202\211\202\216\201@\202\217\202\216\202\203\202\205\201@\202\231\202\217\202\225"; // select up to three. You win once you
const char aDuringTheMainGa_800A4200[] = "\202\204\202\225\202\222\202\211\202\216\202\207\201@\202\224\202\210\202\205\201@\202\215\202\201\202\211\202\216\201@\202\207\202\201\202\215\202\205\201D\201@\202d\202\201\202\203\202\210\201@\202\220\202\214\202\201\202\231\202\205\202\222\201@\202\203\202\201\202\216"; // during the main game. Each player can
const char aFightEachOtherU_800A424C[] = "\202\206\202\211\202\207\202\210\202\224\201@\202\205\202\201\202\203\202\210\201@\202\217\202\224\202\210\202\205\202\222\201@\202\225\202\223\202\211\202\216\202\207\201@\202\203\202\222\202\205\202\201\202\224\202\225\202\222\202\205\202\223\201@\202\203\202\201\202\220\202\224\202\225\202\222\202\205\202\204"; // fight each other using creatures captured
const char aAndTheMinionsOf_800A42A0[] = "\202\201\202\216\202\204\201@\202\224\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202r\202\225\202\216\202\223\202\205\202\224\201@\201i\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201j"; // and the Minions of the Sunset (Player 2)
const char aHereTheMinionsO_800A42F4[] = "\202g\202\205\202\222\202\205\201@\202\224\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202c\202\201\202\227\202\216\201@\201i\202o\202\214\202\201\202\231\202\205\202\222\201@\202P\201j"; // Here the Minions of the Dawn (Player 1)
const char aWelcomeToTheAre_800A4344[] = "\202v\202\205\202\214\202\203\202\217\202\215\202\205\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202`\202\222\202\205\202\216\202\201\201@\202\217\202\206\201@\202r\202\220\202\201\202\203\202\205\201@\202\201\202\216\202\204\201@\202s\202\211\202\215\202\205\201D"; // Welcome to the Arena of Space and Time.

typedef struct CombChuiTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombChuiTask;

typedef struct CombChuiWin
{
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
} CombChuiWin;

typedef struct CombChuiPos
{
    char pad_0[0x10];
    short x_10;
    short y_12;
} CombChuiPos;

extern unsigned char byte_800A38D8;
extern unsigned char byte_800918F1;
extern CombChuiWin dword_80082784;
extern CombChuiPos dword_80082708;
extern CombChuiPos dword_80082740;
extern void UpdateMenuCursor_8003D794(void*, int);
extern int IsConfirmPressedP1_8003D380(int);
extern int IsCancelPressedP1_8003D41C(int);
extern int GetMenuCursorIndex_8003DA54(void*);
extern void DrawMenuWindows_8002A5A4(void*);
extern void DrawMenuBackground_8002BE10();
extern void CombatNextStage_800A16FC();
extern void DrawTextLines_800A450C();

// Arena intro text; asks whether player 2 uses controller 2 (forced "no" when pad 2 is absent)
void VersusIntroTask_800A4394(CombChuiTask* task, int arg)
{
    short rect[4];
    int menuY;
    UpdateMenuCursor_8003D794(&p2PadYesNoMenu_800A45B0, 0);
    if (byte_800918F1 == 0xFF)
    {
        p2PadYesNoMenu_800A45B0.sel_8 = 1;
    }
    if (IsConfirmPressedP1_8003D380(1))
    {
        if ((short)GetMenuCursorIndex_8003DA54(&p2PadYesNoMenu_800A45B0) == 0)
        {
            byte_800A38D8 = 1;
        }
        else
        {
            byte_800A38D8 = 0;
        }
        task->next_8 = CombatNextStage_800A16FC;
        task->next_8(task, arg);
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        byte_800A38D8 = 0;
        task->next_8 = CombatNextStage_800A16FC;
        task->next_8(task, arg);
    }
    else
    {
        rect[0] = 10;
        rect[1] = 0x14;
        rect[2] = 0x12C;
        menuY = 0xC8;
        rect[3] = menuY;
        DrawTextLines_800A450C(introTextLines_800A45BC, rect);
        dword_80082784.f4 = GetTime30Hz_8002C64C();
        dword_80082784.f8 = 8;
        dword_80082784.f14 = 0;
        dword_80082708.x_10 = 0x72;
        dword_80082708.y_12 = menuY;
        dword_80082740.x_10 = 0xA0;
        dword_80082740.y_12 = menuY;
        dword_80082784.fC = p2PadYesNoMenu_800A45B0.sel_8;
        DrawMenuWindows_8002A5A4(&dword_80082784);
        DrawMenuBackground_8002BE10();
    }
}

// Draws a 0-terminated list of text lines, centred in the box, one 16px line apart
void DrawTextLines_800A450C(int* lines, unsigned short* box)
{
    short rect[4];
    int item;
    unsigned short y;
    SetFontClutOffset_8003F900(2, 0);
    item = *lines;
    y = box[1];
    while (item)
    {
        AlignMenuItem_8002AC88(8, box, (short)MeasureTextWidth_8003E4C8(item), rect);
        rect[1] = y;
        DrawText_8003E91C(2, item, rect, 0);
        lines++;
        item = *lines;
        y += 0x10;
    }
}

CombChuiMenu p2PadYesNoMenu_800A45B0 = { { 2, 0, 1, 0, 2, 0, 1 } };
int introTextLines_800A45BC[12] = {
    (int)aWelcomeToTheAre_800A4344, (int)aHereTheMinionsO_800A42F4, (int)aAndTheMinionsOf_800A42A0, (int)aFightEachOtherU_800A424C, (int)aDuringTheMainGa_800A4200, (int)aSelectUpToThree_800A41B4, (int)aDefeatAllEnemie_800A4174, (int)aOpponentGivesUp_800A4124,
    (int)aYouHaveAMEMORYC_800A40D4, (int)&aBlankLine_800A40D0, (int)aWillPlayer2UseC_800A408C,
};
