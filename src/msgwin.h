#ifndef MSGWIN_H
#define MSGWIN_H

/* message windows (msg_window.c): the buffer of a messageWindowTask_8008D640 entry */

typedef struct
{
    unsigned short promptX_0; // DrawMsgWindowNextPrompt_8003E268 position
    unsigned short promptY_2;
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} MsgTextClip;

/* 0x18..0x27, copied out by GetMsgWindowResultIfDone_800349B4 / GetMsgWindowResult_80034A00 */
typedef struct
{
    short count_18;
    short sel_1A;
    short pageCount_1C;
    unsigned short advances_1E; // confirmations
    int result_20;
    int field_24;
} MsgResult;

typedef struct
{
    int type;
    int id;
    int count;
    int pad[2];
} ItemMsgEntry;

/* OpenItemMessageWindow_80035AC8's argument (0x50 bytes, copied to MsgWindow.item_214) */
typedef struct
{
    int pad_0[2];
    int field_8;
    ItemMsgEntry entries_C[3];
    int mode_48;
    int* text_4C;
} ItemMsgInit;

/* OpenMessageWindow_8003422C's argument */
typedef struct
{
    int posMode_0; // window position preset when pos_4 is 0
    short* pos_4; // speaker position (x, height)
    int* text_8; // pages, see FindTextResumePage_80034900
    char* title_C;
    int field_10;
    int cancelable_14;
    unsigned int mask_18;
    int* lines_1C; // choice lines
    int portraitKind_20; // 1: portrait, 7: combat portrait
    int portraitId_24;
    int style_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int voiced_44;
} MsgWindowCfg;

typedef struct MsgWindow
{
    int self_0; // EventEntry* of the window
    unsigned int flags_4;
    unsigned int mode_8;
    int field_C;
    int field_10;
    unsigned int mask_14; // which lines of lines_1B4 are shown
    MsgResult res_18;
    int cancelable_28; // cancel picks the last choice
    int field_2C;
    int field_30;
    int field_34;
    short x_38;
    short y_3A;
    short w_3C;
    short h_3E;
    short field_40;
    short field_42;
    short field_44;
    short field_46;
    int field_48;
    unsigned short x_4C;
    unsigned short y_4E;
    short w_50;
    short h_52;
    int ot_54;
    char pad_58[0xC];
    unsigned short x_64;
    unsigned short y_66;
    int portraitFlip_68; // portrait drawn mirrored
    short pulse_6C; // 0x6C..: passed to DrawPulsingWindow_8002F6F8 as the cursor state
    unsigned short titleX_6E;
    unsigned short titleY_70;
    short pad_72;
    char* title_74;
    int page_78; // current page of list_B4
    int count_7C;
    int field_80;
    int portraitKind_84; // 1: portrait poly prim_88 is drawn
    POLY_FT4 prim_88;
    unsigned short choiceCount_B0; // shown lines of lines_1B4
    short choice_B2;
    int* list_B4[0x40];
    unsigned short** lines_1B4;
    MsgTextClip clip_1B8;
    int field_1C4;
    int field_1C8;
    int field_1CC;
    int field_1D0;
    int field_1D4;
    int field_1D8;
    int field_1DC;
    int field_1E0;
    signed char marks_1E4[0x30];
    ItemMsgInit item_214;
    int pad_264[0x10];
    int voiced_2A4; // 1: advances by itself when the XA voice ends
} MsgWindow;

/* an EventEntry of messageWindowTask_8008D640, with its buffer typed */
typedef struct
{
    int flags_0;
    int field_4;
    EventEntryFn cb_8;
    EventEntryFn cb_C;
    int size_10;
    MsgWindow* win_14;
} MsgWindowEntry;

#endif
