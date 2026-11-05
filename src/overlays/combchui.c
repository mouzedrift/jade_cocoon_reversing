// COMBCHUI.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combchui.h"

int dword_800A4088 SDATA = 18; // first word of the overlay

MenuCursor p2PadYesNoMenu_800A45B0 = { 2, 1, 2, 1, 0, 0 };
// the arena intro (DrawTextLines_800A450C), 0-terminated
const char* introTextLines_800A45BC[12] = {
    "\202v\202\205\202\214\202\203\202\217\202\215\202\205\201@\202\224\202\217\201@\202\224\202\210\202\205\201@\202`\202\222\202\205\202\216\202\201\201@\202\217\202\206\201@\202r\202\220\202\201\202\203\202\205\201@\202\201\202\216\202\204\201@\202s\202\211\202\215\202\205\201D", // Welcome to the Arena of Space and Time.
    "\202g\202\205\202\222\202\205\201@\202\224\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202c\202\201\202\227\202\216\201@\201i\202o\202\214\202\201\202\231\202\205\202\222\201@\202P\201j", // Here the Minions of the Dawn (Player 1)
    "\202\201\202\216\202\204\201@\202\224\202\210\202\205\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201@\202\217\202\206\201@\202\224\202\210\202\205\201@\202r\202\225\202\216\202\223\202\205\202\224\201@\201i\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201j", // and the Minions of the Sunset (Player 2)
    "\202\206\202\211\202\207\202\210\202\224\201@\202\205\202\201\202\203\202\210\201@\202\217\202\224\202\210\202\205\202\222\201@\202\225\202\223\202\211\202\216\202\207\201@\202\203\202\222\202\205\202\201\202\224\202\225\202\222\202\205\202\223\201@\202\203\202\201\202\220\202\224\202\225\202\222\202\205\202\204", // fight each other using creatures captured
    "\202\204\202\225\202\222\202\211\202\216\202\207\201@\202\224\202\210\202\205\201@\202\215\202\201\202\211\202\216\201@\202\207\202\201\202\215\202\205\201D\201@\202d\202\201\202\203\202\210\201@\202\220\202\214\202\201\202\231\202\205\202\222\201@\202\203\202\201\202\216", // during the main game. Each player can
    "\202\223\202\205\202\214\202\205\202\203\202\224\201@\202\225\202\220\201@\202\224\202\217\201@\202\224\202\210\202\222\202\205\202\205\201D\201@\202x\202\217\202\225\201@\202\227\202\211\202\216\201@\202\217\202\216\202\203\202\205\201@\202\231\202\217\202\225", // select up to three. You win once you
    "\202\204\202\205\202\206\202\205\202\201\202\224\201@\202\201\202\214\202\214\201@\202\205\202\216\202\205\202\215\202\211\202\205\202\223\201@\202\217\202\222\201@\202\227\202\210\202\205\202\216\201@\202\231\202\217\202\225\202\222", // defeat all enemies or when your
    "\202\217\202\220\202\220\202\217\202\216\202\205\202\216\202\224\201@\202\207\202\211\202\226\202\205\202\223\201@\202\225\202\220\201D\201@\202x\202\217\202\225\201@\202\203\202\201\202\216\201@\202\217\202\216\202\214\202\231\201@\202\220\202\214\202\201\202\231\201@\202\211\202\206", // opponent gives up. You can only play if
    "\202\231\202\217\202\225\201@\202\210\202\201\202\226\202\205\201@\202\201\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\227\202\211\202\224\202\210\201@\202\223\202\201\202\226\202\205\202\204\201@\202\204\202\201\202\224\202\201\201D", // you have a MEMORY CARD with saved data.
    "", // (blank line)
    "\202v\202\211\202\214\202\214\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201@\202\225\202\223\202\205\201@\202b\202n\202m\202s\202q\202n\202k\202k\202d\202q\201@\202Q\201H\000,", // Will Player 2 use CONTROLLER 2? (the "\000," tail is in the original data)
};

// Arena intro text; asks whether player 2 uses controller 2 (forced "no" when pad 2 is absent)
void VersusIntroTask_800A4394(CombatTask* task, int arg)
{
    short rect[4];
    int menuY;
    UpdateMenuCursor_8003D794(&p2PadYesNoMenu_800A45B0, 0);
    if (pads_800918E8[1][0] == 0xFF)
    {
        p2PadYesNoMenu_800A45B0.cursor_8 = 1;
    }
    if (IsConfirmPressedP1_8003D380(1))
    {
        if ((short)GetMenuCursorIndex_8003DA54(&p2PadYesNoMenu_800A45B0) == 0)
        {
            player2Pad_800A38D8 = 1;
        }
        else
        {
            player2Pad_800A38D8 = 0;
        }
        task->next_8 = CombatNextStage_800A16FC;
        task->next_8(task, arg);
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        player2Pad_800A38D8 = 0;
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
        dword_80082784.time_4 = GetTime30Hz_8002C64C();
        dword_80082784.anim_8 = 8;
        dword_80082784.ot_14 = 0;
        dword_80082708.x_10 = 0x72;
        dword_80082708.y_12 = menuY;
        dword_80082740.x_10 = 0xA0;
        dword_80082740.y_12 = menuY;
        dword_80082784.cursor_C = p2PadYesNoMenu_800A45B0.cursor_8;
        DrawMenuWindows_8002A5A4(&dword_80082784);
        DrawMenuBackground_8002BE10();
    }
}

// Draws a 0-terminated list of text lines, centred in the box, one 16px line apart
void DrawTextLines_800A450C(const char** lines, unsigned short* box)
{
    short rect[4];
    const char* item;
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
