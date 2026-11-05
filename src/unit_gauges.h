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

#endif
