#ifndef _ABILITY_MENU_H_
#define _ABILITY_MENU_H_

#include "globals.h"

int GetAbilityIcon_8002D1A4(int type, short slot);
int DrawTargetSelectMenu_8002D250(TargetQuery* req, int mode, int cursor, int ot);
void DrawAbilityList_8002CE28(ListMenuState* menu, unsigned short* origin);
#endif
