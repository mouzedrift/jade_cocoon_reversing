#ifndef _TU_8002ECE0_H_
#define _TU_8002ECE0_H_

/* a status icon menu item drawn by DrawStatusIcons_8002F480 (DrawMenuItemWithWindow_8002ADB4) */
typedef struct
{
    char pad_0[0x10];
    RECT r;
    int field_18;
} StatusIcon;
typedef struct
{
    int m[3];
} StatusIconMasks;
extern const StatusIcon statusIcon0_800743D4;
extern const StatusIcon statusIcon1_800743F0;
extern const StatusIcon statusIcon2_8007440C;
extern const StatusIconMasks statusIconMasks_80074428;

#endif
