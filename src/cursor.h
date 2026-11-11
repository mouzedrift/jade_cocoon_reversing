#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "globals.h"

void DrawNextPrompt_8003CF88(short x, short y, int idx);
void DrawCursorHand_8003D034(unsigned short* pPos, int ot);
void DrawBobbingCursorHand_8003D090(short x, short y, int a2, int a3, int idx);
#endif
