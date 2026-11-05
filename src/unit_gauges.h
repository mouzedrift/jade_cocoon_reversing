#ifndef _TU_8002ECE0_H_
#define _TU_8002ECE0_H_

#include "menu_draw.h"

/* the status icon menu items drawn by DrawStatusIcons_8002F480 (DrawMenuItemWithWindow_8002ADB4) */
typedef struct
{
    int m[3];
} StatusIconMasks;
extern const MenuWindowItem statusIcon0_800743D4;
extern const MenuWindowItem statusIcon1_800743F0;
extern const MenuWindowItem statusIcon2_8007440C;
extern const StatusIconMasks statusIconMasks_80074428;

short ElementLevelsToMask_8002F424(unsigned char* levels);
void DrawUnitStatusWindow_8002F1C8(UnitStatus* unit, int gaugeArg, int highlight, int time, RECT* rect, int ot, int flags);
void DrawMpGauge_8002F120(UnitStatus* unit, unsigned short* pos, int gaugeArg, short ot);
void DrawHpGauge_8002F078(UnitStatus* unit, unsigned short* pos, int gaugeArg, short ot);
void DrawUnitStatusExp_8002ECE0(UnitStatus* unit, unsigned short* pos, int unused, short ot);
void DrawValueGauge_8002EFC4(UnitGauge* values, int gaugeArg, int time, void* origin_, int ot, int showNumbers);
void DrawCurMaxValue_8002EE28(UnitGauge* values, unsigned short* pos, short ot, int showNumbers);
void DrawUnitStatus_8002F23C(UnitStatus* unit, int gaugeArg, int time, unsigned short* pos, int ot, int flags);
void DrawUiTiySprtRow_8002EF5C(unsigned short* pos, short count, short ot);
#endif
