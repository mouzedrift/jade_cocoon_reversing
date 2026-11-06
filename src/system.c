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
#include "model.h"
#include "party.h"
#include "cd.h"


extern unsigned long SpuSetTransferStartAddr(unsigned long addr);
extern unsigned long SpuWrite0(unsigned long size);
extern void McxStopCom(void);
extern void MemCardEnd(void);
void ShutdownSystems_80010228(void)
{
    SsEnd();
    SpuSetTransferStartAddr(0x1010);
    SpuWrite0(0x7EFF0);
    SsQuit();
    ResetGraph(3);
    StopCallback();
    McxStopCom();
    PadStopCom();
    MemCardEnd();
}
void InitEvents_8001028C(void)
{
    cdRomEventDescError_8008B490 = OpenEvent(HwCdRom, EvSpERROR, EvMdINTR, cdRomEventErrorHandler_8003BBAC);
    EnableEvent(cdRomEventDescError_8008B490);

    vsyncEventDesc_8008B494 = OpenEvent(RCntCNT3, EvSpINT, EvMdINTR, vsyncEventHandler_800103AC);
    EnableEvent(vsyncEventDesc_8008B494);

    SetRCnt(RCntCNT3, RCntMdSC, RCntMdINTR);
    StartRCnt(RCntCNT3);

    vsyncCounter_8008B4B4 = 0;
    gnFrame_8008D610 = 0;
}
void CloseEvents_80010328(void)
{
    DisableEvent(cdRomEventDescError_8008B490);
    DisableEvent(vsyncEventDesc_8008B494);
    CloseEvent(cdRomEventDescError_8008B490);
    CloseEvent(vsyncEventDesc_8008B494);
    StopRCnt(RCntCNT0);
    StopRCnt(RCntCNT1);
    StopRCnt(RCntCNT2);
    StopRCnt(RCntCNT3);
}
long vsyncEventHandler_800103AC(void)
{
    ++vsyncCounter_8008B4B4;
    ++gnFrame_8008D610;
    --xaTimer_8008D450;
    if (!(unknownFlags_8008D678 & 8))
    {
        unpausedFrames_8008D404++;
        saveData_8008B570.playTime_4++;
    }

    return vsyncCounter_8008B4B4;
}
void InitImage_80010428(void)
{
    RECT rect;

    rect.w = 1024;
    rect.x = 0;
    rect.y = 0;
    rect.h = 512;
    ClearImage(&rect, 0, 0, 0);
    DrawSync(0);
}
