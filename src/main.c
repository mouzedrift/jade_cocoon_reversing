#include "LIBAPI.H"
#include "MALLOC.H"
#include "globals.h"
#include "stubs.h"

extern char __heap_start, __sp;

int main(int argc, char* argv[])
{
    unsigned int heapSize; // $s0
    unsigned int v4; // $v1
    unsigned __int8* v5; // $a0
    int v6; // $a0

    InitGame_80010110();
    EnterCriticalSection();
    SetMem(2u);
    //heapSize = 8 * ((unsigned int)((char*)&loadedBinaryFile_801B9250 - (char*)heapStart_800CD858) >> 3);// 2048 bytes
    //InitHeap3(heapStart_800CD858, heapSize);
    heapSize = (&__sp - 0x800) - &__heap_start;
    InitHeap3((unsigned long*)&(__heap_start), heapSize);

    /*
    v4 = 2;
    if ((heapSize >> 2) - 2 > 2)                // init heap with 0x55555555
    {
        v5 = &heapStart_800CD858[8];
        do
        {
            *(_DWORD*)v5 = 0x55555555;
            ++v4;
            v5 += 4;
        } while (v4 < (heapSize >> 2) - 2);
    }
    */

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

    exit(0);
}
