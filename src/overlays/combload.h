// COMBLOAD.BIN: declarations shared by its source files
#ifndef _COMBLOAD_H_
#define _COMBLOAD_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombLoadDlg
{
    int f0;
    int f4;
    int f8;
    int fC;
} CombLoadDlg;

typedef struct CombLoadObj
{
    int f0;
    int f4;
    short f8;
    short fA;
} CombLoadObj;

extern int dword_800A4088;
extern const char aCheckingMEMORYC_800A408C[];
extern const char aSelectMEMORYCAR_800A40BC[];
extern const char aSelectData_800A40E4[];
extern CombLoadObj cardSlotCursor_800A468C[1];
extern CombLoadObj dataCursor_800A4698;
extern int dataRow0_800A46A4[14];
extern int dataRow1_800A46DC[14];
extern int dataRow2_800A4714[14];
extern int dataRow3_800A474C[14];
extern int dataRow4_800A4784[14];
extern void *dataRows_800A47BC[6];
extern CombLoadDlg dataMenuWin_800A47D4;
extern void *dataMenuWinItems_800A47E4[3];
extern int cardSelectState_800A47F0;
extern int loadOvlRequest_800A47F4;

#endif
