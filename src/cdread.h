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
extern const int unused_80074960;

typedef struct
{
    int sprt[14]; // public TIY sprite per frame
} LoadingIconFrames;
extern const LoadingIconFrames loadingIconFrames_8007490C;

extern int cdXaLock_80086568;

void UpdateFileRequestTask_8003C76C(int* entry, int* task);
int StartFileRequestTask_8003C6C8(FileRequestDesc* req);
int LoadData001File_8003CD1C(void);
void DATA_GetFile_8003C7CC(Data001File* pOutFile, enum FileIds idx);
int ReadFileIntoBuffer_8003CC54(DslLOC* fileLoc, int sectors, unsigned long* pFileBuffer);
void LoadFileIntoBuffer_8003CB7C(DslLOC* fileLoc, unsigned long* pFileBuffer, int sectors);
void* DATA_GetFileBuffer_8003CAA0(int idx);
int CdReadIsIdle_8003C9EC(void);
int DATA_GetFileSize_8003C87C(int idx);
void CdReadReadyCallback_8003CA30(unsigned char mode);
void CdReadSyncCallback_8003C9FC(unsigned char mode);
void* Data001Reader_LoadIntoGlobal_8003CB40(int idx);
int CdSeekIsComplete_8003C900(void);
void DATA_ReadFileInto_8003CAEC(int idx, unsigned int* pDest);
void DrawLoadingIcon_8003CD5C(void);
#endif
