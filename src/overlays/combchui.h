// COMBCHUI.BIN: declarations shared by its source files
#ifndef _COMBCHUI_H_
#define _COMBCHUI_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pad_text.h"
#include "combat.h"
#include "font.h"
#include "menu_draw.h"
#include "util.h"
#include "ui_sprites.h"


extern int dword_800A4088;
extern MenuCursor p2PadYesNoMenu_800A45B0;
extern const char* introTextLines_800A45BC[12];

void VersusIntroTask_800A4394(CombatTask* task, int arg);
void DrawTextLines_800A450C(const char** lines, unsigned short* box);

/* exe-side, to move to <exe header> */
extern unsigned char pads_800918E8[2][9]; // main.c; pads_800918E8[1][0]: pad 2 state, 0xFF: no controller
extern void AlignMenuItem_8002AC88(int flags, void* rect, int width, void* out); // -> menu_window.h

#endif
