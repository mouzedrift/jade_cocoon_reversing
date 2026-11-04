// COMBRSLT.BIN: declarations shared by its source files
#ifndef _COMBRSLT_H_
#define _COMBRSLT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombRsltText
{
    unsigned short flags_0;
    short type_2;
    int text_4; // string, or sprite index for type 1
    int pad_8[2];
    short x_10;
    short y_12;
    int pad_14[2];
} CombRsltText;

// a menu cursor (UpdateMenuCursor_8003D794, CombSelCursor)
typedef struct CombRsltCursor
{
    char pad_0[0xA];
    short scroll_A;
} CombRsltCursor;

typedef struct CombRsltPos
{
    unsigned short x;
    unsigned short y;
} CombRsltPos;

extern int dword_800A4088;
extern const CombRsltText resultTitleItem_800A408C;
extern const CombRsltText minionLabelItem_800A40A8;
extern const CombRsltText minionHpItem_800A40C4;
extern CombRsltCursor slotCursor_800A47E8[1];
extern int dword_800A47F4;
extern int playerLabelItemP1_800A47F8[7];
extern int playerLabelItemP2_800A4814[7];
extern int *playerLabelItems_800A4830[2];
extern int resultItemP1_800A4838[7];
extern int resultItemP2_800A4854[7];
extern int *resultItems_800A4870[2];
extern unsigned short scoreWindowP1_800A4878[14];
extern unsigned short scoreWindowP2_800A4894[14];
extern unsigned short *scoreWindows_800A48B0[2];
extern int slotLabelSprites_800A48B8[3];
extern CombRsltPos minionSlotPos_800A48C4[6];

#endif
