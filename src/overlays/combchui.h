// COMBCHUI.BIN: declarations shared by its source files
#ifndef _COMBCHUI_H_
#define _COMBCHUI_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pad_text.h"
#include "combat.h"

// a window list drawn by DrawMenuWindows_8002A5A4 (CombSelMenu)
typedef struct CombChuiWin
{
    int flags_0;
    int time_4;  // blink timer
    int anim_8;  // window open animation step
    int cursor_C;
    int rows_10;
    int ot_14;
} CombChuiWin;

typedef struct CombChuiPos
{
    char pad_0[0x10];
    short x_10;
    short y_12;
} CombChuiPos;

extern int dword_800A4088;
extern MenuCursor p2PadYesNoMenu_800A45B0;
extern const char* introTextLines_800A45BC[12];

void VersusIntroTask_800A4394(CombatTask* task, int arg);
void DrawTextLines_800A450C(const char** lines, unsigned short* box);

/* exe-side, to move to <exe header> */
extern unsigned char byte_800918F1;  // pad 2 state, 0xFF: no controller
extern CombChuiWin dword_80082784;   // -> menu data (the yes/no window list)
extern CombChuiPos dword_80082708;   // -> menu data (its "yes" item)
extern CombChuiPos dword_80082740;   // -> menu data (its "no" item)
extern int MeasureTextWidth_8003E4C8(const char* str);  // -> pad_text.h
extern void AlignMenuItem_8002AC88(int flags, void* rect, int width, void* out); // -> menu_window.h
extern void DrawText_8003E91C(int idx, const char* str, void* pos, int ot);       // -> font.h
extern void UpdateMenuCursor_8003D794(void* cursor, int pad); // -> pad_text.h (a1 passes through to MenuCursorInput_8003D830)
extern int GetMenuCursorIndex_8003DA54(void* cursor);        // -> pad_text.h (MenuCursor*)
extern void DrawMenuWindows_8002A5A4(void* list);            // -> menu_draw.h
extern void DrawMenuBackground_8002BE10(void);

#endif
