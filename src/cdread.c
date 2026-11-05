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
#include "tiy.h"
#include "cdread.h"
#include "cd.h"
#include "util.h"
#include "unit_query.h"

const LoadingIconFrames loadingIconFrames_8007490C = { {
        7, 8, 9, 10, 11, 12, 13, 14,
        13, 12, 11, 10, 9, 8,
    } };

extern EventNode* fileRequestTasks_8008D488;
extern EventEntry* AllocEventEntry_80043AF8(EventNode* list);

// Matched
int StartFileRequestTask_8003C6C8(FileRequestDesc* req)
{
    EventEntry* entry = AllocEventEntry_80043AF8(fileRequestTasks_8008D488);
    int* buf;
    if (entry)
    {
        buf = (int*)entry->buffer;
        entry->cb_8 = (EventEntryFn)UpdateFileRequestTask_8003C76C;
        entry->flags = (entry->flags | 1) & 0xFFFF7FFF;
        buf[0] = QueueFileRequest_8003BC84(req);
        buf[1] = (req->flags_0 >> 2) & 1;
        if (buf[1])
        {
            eventDispatchHalt_8008B540 = 1;
        }
        return buf[0];
    }
    return 0;
}
// Matched
void UpdateFileRequestTask_8003C76C(int* entry, int* task)
{
    if (task[1])
    {
        eventDispatchHalt_8008B540 = 1;
    }
    if (GetFileRequestStatus_8003BE30(task[0]) == 0)
    {
        entry[0] = (entry[0] & ~1) | 0x8000;
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
// Matched
int CdSeekStart_8003C8A0(DslLOC* loc)
{
    if (cdReadState_80086550.idle_0 != 0)
    {
        cdReadState_80086550.idle_0 = 0;
        cdReadState_80086550.loc_8 = loc;
        cdReadState_80086550.packet_10 = DsPacket(0xA0, loc, 0x15, 0, -1);
        return 1;
    }
    return 0;
}

// Matched
int CdSeekIsComplete_8003C900(void)
{
    if (DsSync(cdReadState_80086550.packet_10, 0) == 2)
    {
        cdReadState_80086550.idle_0 = 1;
        return 1;
    }
    return 0;
}
extern int DsSystemStatus(void);

// Matched
int CdReadStart_8003C944(DslLOC* loc, void* buf, int sectors)
{
    if (cdReadState_80086550.idle_0 != 0)
    {
        if (DsSystemStatus() == 1)
        {
            cdReadState_80086550.idle_0 = 0;
            cdReadState_80086550.buf_4 = buf;
            cdReadState_80086550.loc_8 = loc;
            cdReadState_80086550.sectors_C = sectors;
            cdReadState_80086550.packet_10 = DsPacket(0xA0, loc, 6, (DslCB)CdReadSyncCallback_8003C9FC, -1);
            return 1;
        }
    }
    return 0;
}
// Matched
int CdReadIsIdle_8003C9EC(void)
{
    return cdReadState_80086550.idle_0;
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
        DsGetSector(cdReadState_80086550.buf_4, 0x200);
        cdReadState_80086550.buf_4 += 0x800;
        cdReadState_80086550.sectors_C--;
        if (cdReadState_80086550.sectors_C == 0)
        {
            cdReadState_80086550.idle_0 = mode;
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
    int state;
    int seekSuccess;

    seekSuccess = 1;
    state = 0;
    cdReadFlags_8008B55C &= ~0x10;
    do
    {
        switch (state)
        {
            case 0:
                if (DsControl(0x15, (u_char*)fileLoc, 0) != 0)
                {
                    state = 1;
                }
                break;
            case 1:
                if (ReadFileIntoBuffer_8003CC54(fileLoc, sectors, pFileBuffer) == 0)
                {
                    state = 0;
                }
                else
                {
                    seekSuccess = 0;
                }
                break;
        }
    } while (seekSuccess != 0);

    cdReadFlags_8008B55C |= 0x10;
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
    while (DsSearchFile(&Data001File_800954A8, data001Path_80086570) == 0)
    {
    }

    return 1;
}
// Matched
void DrawLoadingIcon_8003CD5C(void)
{
    unsigned short pos[2];
    LoadingIconFrames frames;
    int sprtIdx;

    frames = loadingIconFrames_8007490C;
    sprtIdx = frames.sprt[(unsigned int)frameCount_8008D3FC % 14];
    pos[0] = 0xF8;
    pos[1] = 0xBA;
    DrawPublicTiySprt_80033080(pos, sprtIdx, 0);
}
// Matched
void DrawBlinkSprite_8003CE18(short x, short y)
{
    SPRT* sprt;
    unsigned int phase = (unsigned int)frameCount_8008D3FC % 150;
    switch (phase)
    {
    case 0:
    case 6:
        sprt = publicTiySprts_8008D434;
        sprt += 71;
        sprt->x0 = x;
        sprt->y0 = y;
        SetSemiTrans(sprt, 1);
        AddPrimCopy_80040298(pOT_8008D454, &publicTiySprts_8008D434[71], 5);
        AddPrimCopy_80040298(pOT_8008D454, &publicTiyTPages_8008D440[71], 2);
        break;
    case 1:
    case 3:
    case 5:
        sprt = publicTiySprts_8008D434;
        sprt += 71;
        sprt->x0 = x;
        sprt->y0 = y;
        SetSemiTrans(sprt, 1);
        AddPrimCopy_80040298(pOT_8008D454, &publicTiySprts_8008D434[71], 5);
        AddPrimCopy_80040298(pOT_8008D454, &publicTiyTPages_8008D440[71], 2);
        break;
    case 2:
    case 4:
        sprt = publicTiySprts_8008D434;
        sprt += 72;
        sprt->x0 = x;
        sprt->y0 = y;
        SetSemiTrans(sprt, 1);
        AddPrimCopy_80040298(pOT_8008D454, &publicTiySprts_8008D434[72], 5);
        AddPrimCopy_80040298(pOT_8008D454, &publicTiyTPages_8008D440[72], 2);
        break;
    }
}
const int dword_80074960 = 0;

CdReadState cdReadState_80086550 = { 1 };
int fileBufferInUse_80086564 = 0;
int cdXaLock_80086568 = 0;
void *fileBuffer_8008656C = 0;
char *data001Path_80086570 = aDataData0011;
