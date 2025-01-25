#include "LIBAPI.H"
#include "MALLOC.H"
#include "globals.h"
#include "funcs.h"

char heapStart_800CD858;

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