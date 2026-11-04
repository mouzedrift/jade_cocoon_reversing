#ifndef EVENT_H
#define EVENT_H

/* the buffer of the XA streaming task (xaTask_8008B560->entry.buffer) */
typedef struct XaTask
{
    int flags_0; // bit 0: stop requested
    int cmd_4;   // DsCommand / DsControlF id to DsSync on
    short state_8; // 0 idle, 2 playing
    short vol_A;   // fade-out volume
} XaTask;

extern unsigned char byte_80086FEC;
extern unsigned char byte_80086FED;
extern unsigned char byte_80086FEE;
extern unsigned char byte_80086FEF;
extern int dword_80086FF0[9];
extern int dword_80087014[5];
extern void *off_8008703C[5];
extern int dword_80087070[][8];
extern int dword_80087110;
extern MATRIX dword_80087114;
extern MATRIX dword_80087134;

extern int dword_8009611C;

/* how CreateEventList_800435B4 makes an event list (eventDescs_80078EB8) */
typedef struct
{
    unsigned int count;
    unsigned int flags;
    int size;
    EventNode** out;
    EventEntryFn cb_8;
    EventEntryFn cb_C;
} EventDesc;

void XaInitTask_80043054();

#endif
