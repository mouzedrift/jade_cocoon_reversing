#ifndef _TU_8003D198_H_
#define _TU_8003D198_H_

#include "globals.h"

typedef struct
{
    unsigned short s[11];
} TextBuf22;
extern const unsigned short emptyText_80074994[];
extern const TextBuf22 emptyNameBuf_80074998;

extern const int unused_800749B0;

extern int font2CharCodes_800865BC[168];

// cursor over a grid of menu items (UpdateMenuCursor_8003D794)
typedef struct MenuCursor
{
    short columns_0;
    short rows_2;           // visible rows
    unsigned short count_4; // items
    unsigned short flags_6; // 1/2: wrap columns/rows, 4..0x20: leave on right/left/up/down, 0x40: scroll
    short cursor_8;         // index on the page (MoveGridCursor_8003D4C0's m[4])
    short scroll_A;         // first shown item
} MenuCursor;

int MenuCursorInput_8003D830(MenuCursor* menu, int pad);

int MeasureTextWidth_8003E4C8(const char* str);
/* a cursor on a cols_8 x rows_A grid (MoveGridCursorP1_8003D630) */
typedef struct GridCursor
{
    int flags_0;
    short field_4;
    short pos_6;
    short cols_8;
    short rows_A;
} GridCursor;

/* MeasureTextLines_8003E3B4's result */
typedef struct
{
    short w;
    short h;
} TextSize;

/* a paged text window (UpdateTextWindow_8003DB74 / DrawTextWindow_8003DCA4), e.g. MsgWindow.text_1B8 */
typedef struct TextWindow
{
    short x_0; // text origin, also the DrawMsgWindowNextPrompt_8003E268 position
    short y_2;
    RECT clip_4;
    int* lines_C;           // the page's lines
    int ot_10;
    unsigned int field_14;  // 0: everything shown at once
    unsigned int field_18;  // 1: a button press shows the rest
    unsigned int limit_1C;  // characters shown
    unsigned int shown_20;
    unsigned int timer_24;  // frames since the last character
    unsigned int state_28;  // 10: page done
    signed char marks_2C[0x30];
} TextWindow;

int IsCircleHeld_8003D45C(int idx);
int IsConfirmPressedP1_8003D380(int playSfx);
int IsConfirmPressedP2_8003D3A0(int playSfx);
int IsCancelPressedP1_8003D41C(int playSfx);
int IsCancelPressedP2_8003D43C(int playSfx);
int IsCircleHeldP1_8003D480(void);
int IsCircleHeldP2_8003D4A0(void);
int IsConfirmPressed_8003D288(int playSfx, int pad);
int IsCancelPressed_8003D3C0(int playSfx, int pad);
void DrawMsgWindowNextPrompt_8003E268(unsigned short* pos);
int IsTextMarkerLine_8003E484(const char* text);
void InitFonts_8003DA70(void);
int MeasureTextWidthFont1_8003E6B0(const char* str);
TextSize MeasureTextLines_8003E3B4(const char** list);
TextSize MeasureTextLinesMasked_8003E2A8(const char** list, unsigned int mask);
int MoveGridCursorP1_8003D630(GridCursor* grid);
int UpdateTextWindow_8003DB74(TextWindow* w, int draw);
int AdjustByLeftRight_8003D210(int limit, int pos, int step, int idx);
int AdjustByShoulderButtons_8003D198(int limit, int pos, int step, int idx);
int GetMenuCursorIndex_8003DA54(MenuCursor* menu);
int UpdateMenuCursor_8003D794(MenuCursor* menu, int pad);
void DrawTextWindow_8003DCA4(int draw, TextWindow* w);
#endif
