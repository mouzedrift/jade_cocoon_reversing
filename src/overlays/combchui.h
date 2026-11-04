// COMBCHUI.BIN: declarations shared by its source files
#ifndef _COMBCHUI_H_
#define _COMBCHUI_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombChuiMenu
{
    char pad_0[8];
    short sel_8;
} CombChuiMenu;

extern int dword_800A4088;
extern const char dword_800A408C[68];
extern const int dword_800A40D0;
extern const char aYouHaveAMEMORYC_800A40D4[];
extern const char aOpponentGivesUp_800A4124[];
extern const char aDefeatAllEnemie_800A4174[];
extern const char aSelectUpToThree_800A41B4[];
extern const char aDuringTheMainGa_800A4200[];
extern const char aFightEachOtherU_800A424C[];
extern const char aAndTheMinionsOf_800A42A0[];
extern const char aHereTheMinionsO_800A42F4[];
extern const char aWelcomeToTheAre_800A4344[];
extern CombChuiMenu dword_800A45B0;
extern int dword_800A45BC[12];

#endif
