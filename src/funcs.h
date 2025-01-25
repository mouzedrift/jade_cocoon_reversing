#ifndef _FUNCS_H_
#define _FUNCS_H_

#define _SIZE_T

#include "SYS/TYPES.H"
#include "LIBDS.H"

typedef struct
{
    DslLOC field_0_position;
    int field_4_sectors;
    int field_8_size;
} Data001File;

// Stubs
void InitGame_80010110(void);
void sub_8003FDB0(int*);
void sub_80010228(void);
void sub_8004DE00(void);
void CloseEvents_80010328(void);
int LoadOverlay_80020BF8(int mode, enum OverlayIds overlayIdx);
enum GameStates ExecOverlay_80040DDC(enum OverlayIds overlayId);
void sub_80040718(void);
void LoadPublicTiyAndFtg_800407D0(void);
void sub_80040A84(void);
void sub_80040AEC(void);
void sub_80040B54(void);
void sub_80040C8C(void);
void sub_80040CCC(void);
int sub_80040D5C(void);

extern void* malloc3_8003FC4C(unsigned int s);
extern void free3_8003FC6C(void* block);
extern int sub_80012178(int arg0);
extern int sub_80012140(int arg0);
extern int sub_8003BA58(int arg0);
extern int sub_800125B8();
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

#endif