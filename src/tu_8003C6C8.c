#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"

INCLUDE_DATA(dword_8007490C);
INCLUDE_DATA(dword_8007493C);

extern EventNode* dword_8008D488;
extern int QueueFileRequest_8003BC84(int* p);
extern EventEntry* AllocEventEntry_80043AF8(EventNode* n);
extern void sub_8003C76C(int* a0, int* a1);

// Matched
int sub_8003C6C8(int* a0)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D488);
    int* buf;
    if (e)
    {
        buf = (int*)e->buffer;
        e->cb_8 = (EventEntryFn)sub_8003C76C;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        buf[0] = QueueFileRequest_8003BC84(a0);
        buf[1] = ((unsigned int)a0[0] >> 2) & 1;
        if (buf[1])
        {
            eventDispatchHalt_8008B540 = 1;
        }
        return buf[0];
    }
    return 0;
}
// Matched
void sub_8003C76C(int* a0, int* a1)
{
    if (a1[1])
    {
        eventDispatchHalt_8008B540 = 1;
    }
    if (GetFileRequestStatus_8003BE30(a1[0]) == 0)
    {
        a0[0] = (a0[0] & ~1) | 0x8000;
    }
}
// Matched
void DATA_GetFile_8003C7CC(Data001File* pOutFile, enum FileIds idx)
{
    int dataStartOffsetPos;
    Data001File* pReadFile;
    int data001Pos;
    int targetFilePos;
    Data001File* dataStartOffsetFile;

    dataStartOffsetFile = &Data001Files_80075AA0[2];
    pReadFile = &Data001Files_80075AA0[idx];

    pOutFile->field_0_position.minute = pReadFile->field_0_position.minute;
    pOutFile->field_0_position.second = pReadFile->field_0_position.second;
    pOutFile->field_0_position.sector = pReadFile->field_0_position.sector;
    pOutFile->field_0_position.track = pReadFile->field_0_position.track;
    pOutFile->field_4_sectors = pReadFile->field_4_sectors;

    data001Pos = DsPosToInt(&Data001File_800954A8.pos);
    targetFilePos = DsPosToInt(&pOutFile->field_0_position);
    dataStartOffsetPos = DsPosToInt(&dataStartOffsetFile->field_0_position);

    DsIntToPos(data001Pos + targetFilePos - dataStartOffsetPos, &pOutFile->field_0_position);
}
// Matched
int DATA_GetFileSize_8003C87C(int idx)
{
    return Data001Files_80075AA0[idx].field_8_size;
}
extern int sub_8005384C(int a, int b, int c, int d, int e);
// Matched
int CdSeekStart_8003C8A0(int a0)
{
    if (cdReadState_80086550[0] != 0)
    {
        cdReadState_80086550[0] = 0;
        cdReadState_80086550[2] = a0;
        cdReadState_80086550[4] = sub_8005384C(0xA0, a0, 0x15, 0, -1);
        return 1;
    }
    return 0;
}

// Matched
int CdSeekIsComplete_8003C900(void)
{
    if (sub_80053B9C(cdReadState_80086550[4], 0) == 2)
    {
        cdReadState_80086550[0] = 1;
        return 1;
    }
    return 0;
}
extern int sub_80053EB0(void);

// Matched
int CdReadStart_8003C944(int a, int b, int c)
{
    if (cdReadState_80086550[0] != 0)
    {
        if (sub_80053EB0() == 1)
        {
            cdReadState_80086550[0] = 0;
            cdReadState_80086550[1] = b;
            cdReadState_80086550[2] = a;
            cdReadState_80086550[3] = c;
            cdReadState_80086550[4] = sub_8005384C(0xA0, a, 6, (int)CdReadSyncCallback_8003C9FC, -1);
            return 1;
        }
    }
    return 0;
}
// Matched
int CdReadIsIdle_8003C9EC(void)
{
    return cdReadState_80086550[0];
}
// Matched
void CdReadSyncCallback_8003C9FC(unsigned char mode)
{
    if (mode == 2)
    {
        DsStartReadySystem(CdReadReadyCallback_8003CA30, -1);
    }
}
// Matched
void CdReadReadyCallback_8003CA30(unsigned char mode)
{
    if (mode == 1)
    {
        DsGetSector((void*)cdReadState_80086550[1], 0x200);
        cdReadState_80086550[1] += 0x800;
        cdReadState_80086550[3]--;
        if (cdReadState_80086550[3] == 0)
        {
            cdReadState_80086550[0] = mode;
            DsEndReadySystem();
        }
    }
}
// Matched
void* DATA_GetFileBuffer_8003CAA0(int idx)
{
    unsigned long* pFileBuffer;
    Data001File dataFile;
    int pad[2];

    DATA_GetFile_8003C7CC(&dataFile, idx);
    pFileBuffer = malloc3_8003FC4C(dataFile.field_4_sectors * 2048);
    LoadFileIntoBuffer_8003CB7C(&dataFile.field_0_position, pFileBuffer, dataFile.field_4_sectors);
    return pFileBuffer;
}
// Matched
void DATA_ReadFileInto_8003CAEC(int idx, unsigned int* pDest)
{
    void* pBuffer = DATA_GetFileBuffer_8003CAA0(idx);
    MemCopy_800403E8(pDest, pBuffer, DATA_GetFileSize_8003C87C(idx));
    free3_8003FC6C(pBuffer);
}
// Matched
void* Data001Reader_LoadIntoGlobal_8003CB40(int idx)
{
    Data001File file;
    int pad[2]; // the original frame has 8 more bytes of locals
    DATA_GetFile_8003C7CC(&file, idx);
    LoadFileIntoBuffer_8003CB7C(&file.field_0_position, (unsigned long*)0x801B9250, file.field_4_sectors);
    return (void*)0x801B9250;
}
// Matched
void LoadFileIntoBuffer_8003CB7C(DslLOC* fileLoc, unsigned long* pFileBuffer, int sectors)
{
    int var_s0;
    int seekSuccess;

    seekSuccess = 1;
    var_s0 = 0;
    dword_8008B55C &= ~0x10;
    do
    {
        switch (var_s0)
        {
            case 0:
                if (DsControl(0x15, (u_char*)fileLoc, 0) != 0)
                {
                    var_s0 = 1;
                }
                break;
            case 1:
                if (ReadFileIntoBuffer_8003CC54(fileLoc, sectors, pFileBuffer) == 0)
                {
                    var_s0 = 0;
                }
                else
                {
                    seekSuccess = 0;
                }
                break;
        }
    } while (seekSuccess != 0);

    dword_8008B55C |= 0x10;
}
// Matched
int ReadFileIntoBuffer_8003CC54(DslLOC* fileLoc, int sectors, unsigned long* pFileBuffer)
{
    do
    {
        do
        {
            unknownFlags_8008D678 &= ~0x100u;
        } while (!DsRead(fileLoc, sectors, pFileBuffer, DslModeSpeed));

        while (1)
        {
            DsReadSyncResult_8008D630 = DsReadSync(0);

            // read finished or an error occurred
            if (DsReadSyncResult_8008D630 <= 0)
            {
                break;
            }

            if ((unknownFlags_8008D678 & 0x100) != 0)
            {
                return 0;
            }
        }
    } while ((unknownFlags_8008D678 & 0x100) != 0);

    return 1;
}
// Matched
int LoadData001File_8003CD1C(void)
{
    while (DsSearchFile(&Data001File_800954A8, off_80086570) == 0)
    {
    }

    return 1;
}
INCLUDE_ASM(sub_8003CD5C);
