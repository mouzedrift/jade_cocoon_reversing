#ifndef _TU_8003C6C8_H_
#define _TU_8003C6C8_H_

#include "LIBDS.H"

// state of the sector reader (CdSeekStart_8003C8A0 / CdReadStart_8003C944 / CdReadReadyCallback_8003CA30)
typedef struct CdReadState
{
    int idle_0;    // 1 when no command is in flight
    char* buf_4;   // next sector goes here
    DslLOC* loc_8;
    int sectors_C; // sectors still to read
    int packet_10; // DsPacket id
} CdReadState;
extern CdReadState cdReadState_80086550;

extern int CdSeekStart_8003C8A0(DslLOC* loc);
extern int CdReadStart_8003C944(DslLOC* loc, void* buf, int sectors);
extern const int dword_80074960;

typedef struct
{
    int v[14];
} Ints14_8003CD5C;
extern const Ints14_8003CD5C loadingIconFrames_8007490C;

extern int cdXaLock_80086568;

#endif
