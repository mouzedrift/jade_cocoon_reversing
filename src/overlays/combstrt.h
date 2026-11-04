// COMBSTRT.BIN: declarations shared by its source files
#ifndef _COMBSTRT_H_
#define _COMBSTRT_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

extern int dword_800A4088;
extern const char aShufflingMinion_800A408C[];
extern const char aStartFight_800A40C0[];
extern const char aShuffleMinionOr_800A40DC[];
extern const char aAllowMinionChan_800A4108[];
extern const int titleItem_800A4138[7];
extern const int minionLabelItem_800A4154[7];
extern int yesNoCursor_800A4BF0[2];
extern short yesNoSel_800A4BF8;
extern int stateDefaultSel_800A4BFC;
extern int stateDefaultSelStart_800A4C00;
extern const char *stateQuestions_800A4C04[4];
extern unsigned char setupState_800A4C14;
extern int playerLabelItemP1_800A4C18[7];
extern int playerLabelItemP2_800A4C34[7];
extern void *playerLabelItems_800A4C50[2];
extern int slotLabelSprites_800A4C58[3];
extern int minionSlotPos_800A4C64[6];
extern void (*setupStateHandlers_800A4C7C[4])();
extern int windowAnimStep_800A4C8C;
extern short shuffleLimit_800A4C90;
extern short shufflePhase_800A4C92;
extern short shuffleTimer_800A4C94;
extern short shuffleDelay_800A4C96;

#endif
