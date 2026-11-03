#ifndef EVENT_H
#define EVENT_H

/* the buffer of the XA streaming task (xaTask_8008B560; an EventNode*, declared int** in globals.h) */
typedef struct
{
    int flags_0; // bit 0: stop requested
    int cmd_4;   // DsCommand / DsControlF id to DsSync on
    short state_8; // 0 idle, 2 playing
    short vol_A;   // fade-out volume
} XaTask;
#define XA_TASK ((XaTask*)((EventNode*)xaTask_8008B560)->entry.buffer)

#endif
