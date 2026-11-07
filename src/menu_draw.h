#ifndef _TU_8002A1BC_H_
#define _TU_8002A1BC_H_

#include "globals.h"

extern const char aQuit_8007415C[];
extern const char aSelect_80074168[];
extern const char aDescription_80074178[];
extern const char aYes_80074190[];
extern const char aNo_80074198[];
extern const int unused_800741A0;

/* DrawUiWindow_8002A384's parameter block */
typedef struct UiWindowDesc
{
    RECT* rect_0;
    int time_4;
    short colorSet_8; // 1: highlighted
    short ot_A;
} UiWindowDesc;


typedef struct
{
    unsigned short x;
    unsigned short y;
    int text_4;
} TextListEntry;

void InitReverbTask_8002A1BC();

// an item of a menu window (DrawMenuWindowContents_8002A710 / DrawMenuItemWithWindow_8002ADB4), 0x1C bytes;
// a row of items ends with an item with flags_0 & 1
// what a menu window item shows: a text, or a number / sprite index
typedef union MenuText
{
    const char* str;
    int num;
} MenuText;

typedef struct MenuWindowItem
{
    unsigned short flags_0; // 1: end of the row, 2: greyed out, 0x20: no window, 0x40: no contents; 4/8: alignment
    unsigned short type_2;  // 0: none, 1: TIY sprite (text_4 indexes sprts_8), 2/3: text (font 1/2), 4/5: small/large text,
                            // 6/7: number (font 1/2), ...
    MenuText text_4;        // the text, the number, or the sprite index into sprts_8
    SPRT** sprts_8;         // a TIY sprite table (e.g. &uiTiySprts_8008D620)
    DR_TPAGE** tpages_C;
    unsigned short x_10;    // the window rect
    unsigned short y_12;
    unsigned short w_14;
    unsigned short h_16;
    short mx_18;            // the contents' margin
    short my_1A;
} MenuWindowItem;

// a window list drawn by DrawMenuWindows_8002A5A4
typedef struct MenuWindowList
{
    int flags_0;  // 1 inactive, 2 active (the cursor row blinks), 4 cursor row highlighted; 8..0x80: semi-transparency,
                  // 0x100..0x2000: window colour (DrawMenuItemWindow_8002AAF0)
    int time_4;   // blink timer
    int open_8;   // window open animation step, 8: open (InterpolateWindowRect_8004196C)
    int cursor_C; // highlighted row
    MenuWindowItem** items_10; // NULL-terminated list of rows
    int ot_14;
} MenuWindowList;

void DrawMenuWindows_8002A5A4(MenuWindowList* list);
void DrawMenuWindowContents_8002A710(void* item, int ot);

// the exe's yes/no window (effect_data.c)
extern MenuWindowItem yesNoItemYes_80082708[2]; // "Yes" + the row end
extern MenuWindowItem yesNoItemNo_80082740[2];  // "No" + the row end
extern MenuWindowItem* yesNoRows_80082778[3];
extern MenuWindowList yesNoWindow_80082784;

void DrawUiWindow_8002A384(UiWindowDesc* desc);
void DrawPortrait_8002A42C(unsigned short* pos, short id, RECT* drawArea, short ot);
void SetReverbDepthLeft_8002A2E8(SpuReverbAttr* attr, short depth);
void SetReverbDepthRight_8002A2FC(SpuReverbAttr* attr, short depth);
void SetReverbMode_8002A280(SpuReverbAttr* attr, short mode);
void SetReverbDepth_8002A2A0(SpuReverbAttr* attr, short left, short right);
void UpdateReverb_8002A218(void);
void DrawTextList_8002A310(TextListEntry* entries, int ot);
void DrawPortraitWindow_8002A4E4(short ot);
#endif
