#ifndef _FUNCS_H_
#define _FUNCS_H_

#include "SYS/TYPES.H"
#include "LIBDS.H"
#include "enums.h"

typedef struct
{
    DslLOC field_0_position;
    int field_4_sectors;
    int field_8_size;
} Data001File;

// Stubs
extern void sub_8004D924(void);
extern void sub_8003FDB0(int*);
extern void sub_80010228(void);
extern void sub_8004DE00(void); // probably a lib function
extern void CloseEvents_80010328(void);
extern int LoadOverlay_80020BF8(int mode, enum OverlayIds overlayIdx);
extern enum GameStates ExecOverlay_80040DDC(enum OverlayIds overlayId);
extern void sub_80040718(void);
extern void LoadPublicTiyAndFtg_800407D0(void);
extern void sub_80040A84(void);
extern void sub_80040AEC(void);
extern void sub_80040B54(void);
extern void sub_80040C8C(void);
extern void sub_80040CCC(void);
extern int sub_80040D5C(void);

// Matches
extern void* malloc3_8003FC4C(unsigned int s);
extern void free3_8003FC6C(void* block);
extern int sub_80012178(int arg0);
extern int sub_80012140(int arg0);
extern int GetCapturedMinionsFromBitfield_8003BA58(int arg0);
extern int sub_8001C2FC();
extern void GameLoop_8004047C(void);
extern int LoadData001File_8003CD1C(void);
extern void InitImage_80010428(void);
extern void SetGameBootState_80040470(void);
extern void DATA_GetFile_8003C7CC(Data001File* pOutFile, enum FileIds idx);
extern int ReadFileIntoBuffer_8003CC54(DslLOC* fileLoc, int sectors, unsigned long* pFileBuffer);
extern void LoadFileIntoBuffer_8003CB7C(DslLOC* fileLoc, unsigned long* pFileBuffer, int sectors);
extern void* DATA_GetFileBuffer_8003CAA0(int idx);
extern void sub_8001C290(void);
extern void sub_8001B230(void);
extern void sub_80040658(int arg1);
extern void InitEvents_8001028C(void);
extern long cdRomEventErrorHandler_8003BBAC(void);
extern long vsyncEventHandler_800103AC(void);
extern unsigned int GetCapturedMinionsCount_800125B8(void);
extern int CopyPlayerName_8003F860(unsigned char* pPlayerIn, unsigned short* pPlayerOut);
extern void sub_8002FE7C(void);
extern void ClearOTagRAll_8001B260(void);
extern void AddPrimsAll_8001B3C8(void);
extern void ReadBytesInto_80040388(int* pOut, int* pSource, int count);
extern void sub_80040360(int *pOut, int *pDataToWrite, int fileSize);
extern void sub_800403E8(unsigned int *overlayAddr, unsigned int *fileBuffer, unsigned int fileSize);
extern void sub_800403C8(char *a1, unsigned char *fileBuffer, int fileSize);

#endif
