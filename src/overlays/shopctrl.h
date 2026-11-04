// SHOPCTRL.BIN: declarations shared by its source files
#ifndef _SHOPCTRL_H_
#define _SHOPCTRL_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int dword_800B66C0;
extern int shopOverlayIds_800B6CD8[3];
extern int shopMinionCount_800B6CE4;
extern short shopCtrlPrevMode_800B6CE8;
extern short shopCtrlShopId_800B6CEA;
extern short shopCtrlMode_800B6CEC;
extern Minion* shopMinions_800B6CF0;
extern int shopCtrlOverlayReq_800B6CF4;
extern int shopCtrlReloadUi_800B6CF8;
extern int shopCtrlNameTarget_800B6CFC;

#endif
