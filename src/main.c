#include "STDLIB.H"
#include "STDIO.H"
#include "LIBAPI.H"
#include "MALLOC.H"
#include "globals.h"
#include "funcs.h"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBMCRD.H"

char heapStart_800CD858;

unsigned char pads_800918E8[2][9];

char SEQDataAttributeTable_80091D60[SS_SEQ_TABSIZ * 5 * 16];

// Matched
void InitGame_80010110(void)
{
    ResetCallback();
    SetVideoMode(0);

    if (!DsInit())
    {
        printf("Assertion failed: file \"%s\", line %d\n", "MAIN.C", 200);
        exit(1);
    }

    LoadData001File_8003CD1C();
    DecDCTReset(0);
    ResetGraph(0);
    InitGeom();
    MemCardInit(1);
    McxStartCom();
    PadInitDirect(pads_800918E8[0], pads_800918E8[1]);
    PadStartCom();
    ChangeClearPAD(0);
    SetGraphDebug(0);
    DsSetDebug(0);
    sub_8002FE7C();
    SsInit();
    SsSetTableSize(SEQDataAttributeTable_80091D60, 5, 16);
    SsSetTickMode(1);
    SsStart2();
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 112, 112);
    SsUtSetReverbType(SS_REV_TYPE_STUDIO_C);
    SsUtReverbOn();
}

// Matched
int main(void)
{
    int* pHeapIter;
    unsigned int heapSize;
    unsigned int i;

    InitGame_80010110();
    EnterCriticalSection();
    SetMem(2);

    // calc heap size in multiple of 8
    heapSize = ((0x801B9250 - (unsigned int)(&heapStart_800CD858 + sizeof(int) * 2)));
    heapSize = (heapSize / 8) * 8;

    InitHeap3((&heapStart_800CD858 + sizeof(int) * 2), heapSize);

    pHeapIter = &heapStart_800CD858 + sizeof(int) * 2;
    for (i = 2; i < (heapSize / 4) - 2; i++)
    {
        pHeapIter[i] = 0x55555555;
    }

    InitEvents_8001028C();
    ExitCriticalSection();
    sub_8003FDB0(dword_80096090);
    InitImage_80010428();
    SetGameBootState_80040470();
    GameLoop_8004047C();
    EnterCriticalSection();
    CloseEvents_80010328();
    ExitCriticalSection();
    sub_80010228();
    sub_8004DE00();
    _96_init();
    LoadExec("cdrom:\\SLUS_008.54;1", 0x801FFFF0, 0);
    exit();
}