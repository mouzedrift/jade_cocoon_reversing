#ifndef _UI_SPRITES_H_
#define _UI_SPRITES_H_

#include "globals.h"
#include "minion_menu.h"
#include "effect_data.h" // Pos16

unsigned int GetTime30Hz_8002C64C(void);
void SetLargeDigitColor_8002C5D0(int color);
void OnUiTiyLoaded_8002BFCC(void* params, int* data);
void DrawLargeNumber_8002C100(unsigned short* origin, int value, int ot);
void DrawUiTiySprt_8002C06C(unsigned short* pos, int idx, int ot);
void FreeActiveOverlay_8002C014(void);
void LoadUiTiy_8002BF74(void);
int DrawAbilityDescription_8002C670(char* minion, Pos16* pos, const char* (*texts)[4], short slot, short ot); // texts: 4 lines per ability
void DrawItemList_8002C728(ListMenuState* menu);
void DrawMagicList_8002CAC8(ListMenuState* menu, unsigned short* origin);
void DrawSmallNumber3_8002C290(unsigned short* origin, int value, int ot);
void DrawMenuBackground_8002BE10(void);
void DrawScrollArrow_8002C6DC(short* pos, short dir, short ot);
void DrawSmallNumber9_8002C414(unsigned short* origin, int value, int ot);
void DrawAnimatedWindow_8002BEC8(RECT* outRect, RECT* rect, short step, short ot, int highlight, int time);
#endif
