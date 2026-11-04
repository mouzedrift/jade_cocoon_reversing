#ifndef MSGWIN_H
#define MSGWIN_H

/* message windows (msg_window.c): the buffer of a messageWindowTask_8008D640 entry */

typedef struct
{
    int field_0;
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} struct_rect_1B8;

/* 0x18..0x27, copied out by GetMsgWindowResultIfDone_800349B4 / GetMsgWindowResult_80034A00 */
typedef struct
{
    short count_18;
    short sel_1A;
    short field_1C;
    unsigned short field_1E;
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

typedef struct MsgWindow
{
    int self_0; // EventEntry* of the window
    unsigned int flags_4;
    unsigned int mode_8;
    int field_C;
    int field_10;
    unsigned int mask_14; // which lines of lines_1B4 are shown
    MsgResult res_18;
    int field_28;
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
    int field_68;
    short field_6C; // 0x6C..: passed to DrawPulsingWindow_8002F6F8 as the cursor state
    unsigned short titleX_6E;
    unsigned short titleY_70;
    short pad_72;
    char* title_74;
    int field_78;
    int count_7C;
    int field_80;
    int field_84;
    POLY_FT4 prim_88;
    unsigned short field_B0;
    short field_B2;
    int* list_B4[0x40];
    unsigned short** lines_1B4;
    struct_rect_1B8 clip_1B8;
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
    int field_2A4;
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
