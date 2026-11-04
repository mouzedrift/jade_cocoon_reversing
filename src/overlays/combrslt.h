// COMBRSLT.BIN: declarations shared by its source files
#ifndef _COMBRSLT_H_
#define _COMBRSLT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombRsltText
{
    unsigned short flags_0;
    short s_2;
    int ptr_4;
    int pad_8[2];
    short x_10;
    short y_12;
    int pad_14[2];
} CombRsltText;

typedef struct CombRsltEnt
{
    char pad_0[0xA];
    short idx_A;
} CombRsltEnt;

typedef struct CombRsltPos
{
    unsigned short x;
    unsigned short y;
} CombRsltPos;

extern int dword_800A4088;
extern const CombRsltText dword_800A408C;
extern const CombRsltText dword_800A40A8;
extern const CombRsltText dword_800A40C4;
extern CombRsltEnt dword_800A47E8[1];
extern int dword_800A47F4;
extern int dword_800A47F8[7];
extern int dword_800A4814[7];
extern int *dword_800A4830[2];
extern int dword_800A4838[7];
extern int dword_800A4854[7];
extern int *dword_800A4870[2];
extern unsigned short dword_800A4878[14];
extern unsigned short dword_800A4894[14];
extern unsigned short *dword_800A48B0[2];
extern int dword_800A48B8[3];
extern CombRsltPos dword_800A48C4[6];

#endif
