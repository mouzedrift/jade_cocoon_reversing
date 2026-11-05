#ifndef _TU_8002AAF0_H_
#define _TU_8002AAF0_H_

#include "effect_data.h" // Pos16
#include "menu_draw.h"

typedef struct
{
    short s[8];
} Block16;

// the initialiser of DrawElementIconsRow_8002B1B0's local
extern const Block16 elementIconRowOffsets_800741C4;

// a button help bar entry (DrawButtonHelpBar_8002B004), icon -1 ends the list
typedef struct ButtonHelpEntry
{
    int icon_0;
    const char* text_4;
} ButtonHelpEntry;

// the exe's button help bars (effect_data.c)
extern ButtonHelpEntry helpBarSelectQuit_80082680[3];     // Select / Quit
extern ButtonHelpEntry helpBarSelectDesc_80082698[3];     // Select / Description
extern ButtonHelpEntry helpBarSelectQuitDesc_800826B0[4]; // Select / Quit / Description
extern ButtonHelpEntry helpBarSelectQuit2_800826D0[3];    // Select / Quit
extern ButtonHelpEntry helpBarSelect_800826E8[2];         // Select


void DrawMenuItemWindow_8002AAF0(MenuWindowList* list, int i, int j, RECT* rect);
void DrawMenuItemWithWindow_8002ADB4(MenuWindowItem* item, void* window, int ot, int time); // window: a DrawWindow_80042460 style
void DrawButtonHelpBar_8002B004(ButtonHelpEntry* entries, Pos16* origin, int ot);
void DrawElementIconsRow_8002B1B0(short mask, int pos, int ot);
void GetMenuItemColor_8002ACE8(int flags, unsigned char* out);
void SetMenuItemDigitColor_8002AD80(int flags);
void SetMenuItemFont1Clut_8002AD08(int flags);
void SetMenuItemFont2Clut_8002AD44(int flags);
void DrawTextBox_8002AFA0(const char** text, Pos16* pos, int ot, RECT* rect, int count);
void DrawLargeTextBox_8002AF10(const char** text, Pos16* pos, int ot);
void DrawSmallTextBox_8002AF58(const char** text, Pos16* pos, int ot);
void DrawTextLinesWindow_8002AE38(const char** lines, Pos16* pos, int ot, RECT* rect, int count);
#endif
