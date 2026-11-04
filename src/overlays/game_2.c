// GAME.BIN, source file 2 of 3 from 0x800A55B0 (.rdata from 0x800A061C)
#include "game.h"

void* GetEventDataSlot_800A55B0(int a)
{
    void* r = 0;
    switch (a)
    {
    case 0:
        r = eventEffects_800AEB80;
        break;
    case 1:
        r = eventReloc_800AEBBC;
        break;
    case 2:
        r = eventTiy_800AEBC0;
        break;
    case 3:
        r = eventDataBuf_800AEBC8;
        break;
    case 4:
        r = eventRecords_800AEBCC;
        break;
    }
    return r;
}

INCLUDE_OVERLAY_ASM(game, dword_800A0630);

extern void LoadEventEffectFile_800BC7A8(int a, int b);
extern void LoadRelocBlob_800BC854(int a, int b);
extern void LoadEventTiy_800BC98C(int a, int b);
extern void CopyEventData_800BCA18(int a, int b);
extern void LoadEventRecordTables_800BCA68(int a, int b);

void LoadEventData_800A5628(int kind, int a, int b)
{
    switch (kind)
    {
    case 0:
        LoadEventEffectFile_800BC7A8(a, b);
        break;
    case 1:
        LoadRelocBlob_800BC854(a, b);
        break;
    case 2:
        LoadEventTiy_800BC98C(a, b);
        break;
    case 3:
        CopyEventData_800BCA18(a, b);
        break;
    case 4:
        LoadEventRecordTables_800BCA68(a, b);
        break;
    }
}
INCLUDE_OVERLAY_ASM(game, dword_800A0648);

void FreeEventData_800A56BC(int kind)
{
    switch (kind)
    {
    case 0:
        if (mdecBufferMode_800AEB7C != 2)
            FreeMdecBuffer_800A5854();
        if (eventEffects_800AEB80[1])
            ListFreeAll_8003FEC8(&eventEffects_800AEB80[1]);
        break;
    case 1:
        if (eventReloc_800AEBBC)
        {
            ListFree_8003FE38(name_80091C10, eventReloc_800AEBBC);
            eventReloc_800AEBBC = 0;
        }
        break;
    case 2:
        if (eventTiy_800AEBC0[0])
        {
            ListFree_8003FE38(name_80091C10, eventTiy_800AEBC0[0]);
            eventTiy_800AEBC0[0] = 0;
        }
        if (eventTiy_800AEBC0[1])
        {
            ListFree_8003FE38(name_80091C10, eventTiy_800AEBC0[1]);
            eventTiy_800AEBC0[1] = 0;
        }
        break;
    case 3:
        if (eventDataBuf_800AEBC8)
        {
            ListFree_8003FE38(name_80091C10, eventDataBuf_800AEBC8);
            eventDataBuf_800AEBC8 = 0;
        }
        break;
    case 4:
        if (eventRecords_800AEBCC[1])
        {
            FreeRecordTables_80026DE8(&eventRecords_800AEBCC[1], eventRecords_800AEBCC[0], name_80091C10);
            eventRecords_800AEBCC[0] = 0;
        }
        break;
    }
}
