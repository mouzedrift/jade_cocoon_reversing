#ifndef TU_80010B90_H
#define TU_80010B90_H

/* the buffer of the task dword_8008D464 (an EventNode*; declared int** in globals.h) */
typedef struct
{
    int mode_0;
    int timer_4;
} Task8008D464Buf;
#define TASK_8008D464_BUF ((Task8008D464Buf*)((EventNode*)dword_8008D464)->entry.buffer)

#endif
