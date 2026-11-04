#ifndef _TU_8003D198_H_
#define _TU_8003D198_H_

typedef struct
{
    unsigned short s[11];
} TextBuf22;
extern const unsigned short emptyText_80074994[];
extern const TextBuf22 emptyNameBuf_80074998;

extern const int dword_800749B0;

extern int fontDef2_800865A4[5];
extern int font2CharCodes_800865B8[169];

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

int UpdateMenuCursor_8003D794(MenuCursor* menu, int pad);
int MenuCursorInput_8003D830(MenuCursor* menu, int pad);
int GetMenuCursorIndex_8003DA54(MenuCursor* menu);

#endif
