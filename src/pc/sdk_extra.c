/* PC only: the PSY-Q functions the game uses that PSY-Z does not have (yet). libds on top of PSY-Z's libcd, the
   heap on the C library, memory cards absent, the rest as on the PlayStation. */
#include <psyz.h>
#define DIRENTRY DIRENTRY /* libapi.h has it (see sdk.h) */
#include <psyz/log.h>
#include <libapi.h>
#include <libcd.h>
#include <libds.h>
#include <libetc.h>
#include <libgpu.h>
#include <libgte.h>
#include <libmcrd.h>
#include <libmcx.h>
#include <libpress.h>
#include <libsnd.h>
#include <libspu.h>
#include <stdlib.h>
#include <string.h>

/* libds: the same commands as libcd, with a command queue the game only uses one entry of at a time */

int DsInit(void) { return CdInit(); }
int DsSetDebug(int level) { return CdSetDebug(level); }
int DsPosToInt(DslLOC* p) { return CdPosToInt((CdlLOC*)p); }
DslLOC* DsIntToPos(int i, DslLOC* p) { return (DslLOC*)CdIntToPos(i, (CdlLOC*)p); }
int DsControl(u_char com, u_char* param, u_char* result) { return CdControl(com, param, result); }
int DsControlB(u_char com, u_char* param, u_char* result) { return CdControlB(com, param, result); }
/* PSY-Q's values (DslReady 1, DslBusy 2): PSY-Z's libds.h has 0 and 1 */
int DsSystemStatus(void) { return CdSync(1, NULL) == CdlComplete || CdSync(1, NULL) == CdlNoIntr ? 1 : 2; }
int DsRead(DslLOC* pos, int sectors, u_long* buf, int mode)
{
    return CdControlB(CdlSetloc, (u_char*)pos, NULL) && CdRead(sectors, buf, mode);
}
int DsRead2(DslLOC* pos, int mode) { return CdControlB(CdlSetloc, (u_char*)pos, NULL) && CdRead2(mode); }
int DsReadSync(u_char* result) { return CdReadSync(0, result); }
DslFILE* DsSearchFile(DslFILE* fp, char* name) { return (DslFILE*)CdSearchFile((CdlFILE*)fp, name); }

/* DsPacket's CdlReadN without CdlModeRT (PSY-Z only streams XA): the sectors are read here, one per DsGetSector,
   and handed to the DsStartReadySystem callback until it calls DsEndReadySystem */
static int packetSector = -1;
static u_char packetMode;
static DslRCB readyFunc;
int DsGetSector(void* madr, int size)
{
    static u_long sector[2048 / 4];
    CdlLOC pos;
    if (packetSector < 0)
        return CdGetSector(madr, size);
    CdIntToPos(packetSector++, &pos);
    CdControlB(CdlSetloc, (u_char*)&pos, NULL);
    CdRead(1, sector, packetMode);
    CdReadSync(0, NULL);
    memcpy(madr, sector, size * 4);
    return 1;
}
static void DeliverSectors(void)
{
    u_char result[8] = { 0 };
    while (packetSector >= 0 && readyFunc)
        readyFunc(CdlDataReady, result);
}

static int dsLastId;
int DsControlF(u_char com, u_char* param)
{
    CdControlF(com, param);
    return ++dsLastId;
}
int DsCommand(u_char com, u_char* param, DslCB cbsync, int count)
{
    u_char result[8];
    CdControlB(com, param, result);
    if (cbsync)
        cbsync(CdlComplete, result);
    return ++dsLastId;
}
/* setmode, setloc and the command */
int DsPacket(u_char mode, DslLOC* pos, u_char com, DslCB cbsync, int count)
{
    u_char result[8] = { 0 };
    if (com == CdlReadN && pos && !(mode & CdlModeRT))
    {
        packetSector = CdPosToInt((CdlLOC*)pos);
        packetMode = mode & ~(CdlModeSize0 | CdlModeSize1); /* DsGetSector takes the 2048 data bytes */
        if (cbsync)
            cbsync(CdlComplete, result);
        DeliverSectors();
        return ++dsLastId;
    }
    CdControlB(CdlSetmode, &mode, NULL);
    if (pos)
        CdControlB(CdlSetloc, (u_char*)pos, NULL);
    CdControl(com, (u_char*)pos, result);
    if (cbsync)
        cbsync(CdlComplete, result);
    return ++dsLastId;
}
int DsSync(int id, u_char* result)
{
    int r = CdSync(1, result);
    return r == CdlNoIntr ? DslComplete : r;
}
int DsStartReadySystem(DslRCB func, int count)
{
    readyFunc = func;
    if (packetSector < 0)
        CdReadyCallback((CdlCB)func);
    return 1;
}
void DsEndReadySystem(void)
{
    readyFunc = NULL;
    packetSector = -1;
    CdReadyCallback(NULL);
}

/* the heap (InitHeap3 gets the area above the overlays, the C library's heap stands in for it) */
void InitHeap3(unsigned long* head, unsigned long size) {}
/* on the PlayStation a block is always followed by more heap (the next block's header), and the game reads a little
   past some of its blocks (sprites projected three at a time); the slack stands in for that */
#define HEAP3_SLACK 64
void* malloc3(size_t size) { return calloc(1, size + HEAP3_SLACK); }
void free3(void* p) { free(p); }

void SetMem(unsigned long n) {}
void _96_init(void) {}
void LoadExec(char* name, unsigned long sp, unsigned long sp_size)
{
    INFOF("LoadExec(%s): end", name);
    exit(0);
}

/* pads: PadInitDirect is InitPAD with the 34 byte buffers */
void PadInitDirect(unsigned char* pad1, unsigned char* pad2) { InitPAD((char*)pad1, 34, (char*)pad2, 34); }
void PadStopCom(void) {}

/* memory cards: none inserted */
void MemCardInit(long val) {}
void MemCardEnd(void) {}
void MemCardStart(void) {}
void MemCardStop(void) {}
long MemCardExist(long chan) { return 0; }
long MemCardAccept(long chan) { return 0; }
long MemCardSync(long mode, long* cmd, long* result)
{
    if (cmd)
        *cmd = 0;
    if (result)
        *result = McErrCardNotExist;
    return 1;
}
long MemCardReadFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes) { return McErrCardNotExist; }
long MemCardWriteFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes) { return McErrCardNotExist; }
long MemCardCreateFile(long chan, char* file, long blocks) { return McErrCardNotExist; }
long MemCardFormat(long chan) { return McErrCardNotExist; }
long MemCardGetDirentry(long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max)
{
    if (files)
        *files = 0;
    return McErrCardNotExist;
}
void McxStartCom(void) {}
void McxStopCom(void) {}
int McxSync(int mode, long* cmd, long* result)
{
    if (cmd)
        *cmd = 0;
    if (result)
        *result = McErrCardNotExist;
    return 1;
}
int McxAllInfo(int port, unsigned char* state) { return 0; }

/* libgte */
long Lzc(long data)
{
    unsigned int v = (unsigned int)data;
    int n = 0;
    if ((int)v < 0)
        v = ~v;
    while (n < 32 && !(v & 0x80000000u))
    {
        v <<= 1;
        n++;
    }
    return n;
}
MATRIX* MulMatrix0(MATRIX* m0, MATRIX* m1, MATRIX* m2)
{
    MATRIX r;
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            r.m[i][j] = (m0->m[i][0] * m1->m[0][j] + m0->m[i][1] * m1->m[1][j] + m0->m[i][2] * m1->m[2][j]) >> 12;
    memcpy(m2->m, r.m, sizeof(r.m));
    return m2;
}
int IsIdMatrix(MATRIX* m)
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (m->m[i][j] != (i == j ? 4096 : 0))
                return 0;
    return 1;
}

/* libgpu */
void SetDrawStp(DR_STP* p, int pbw)
{
    setlen(p, 2);
    p->code[0] = 0xE6000000 | (pbw ? 1 : 0);
    p->code[1] = 0;
}

/* sound */
u_long SpuWrite0(u_long size) { return size; }
void SsSepSetDecrescendo(short sep_acc_num, short seq_num, short vol, long v_time) {}
long SsVoKeyOn(long vab_pro, long pitch, u_short volL, u_short volR) { return 0; }

/* movies (MDEC): not decoded yet */
void DecDCTvlcBuild(u_short* table) {}
int DecDCTvlc2(unsigned long* bs, unsigned long* buf, DECDCTTAB table) { return 0; }
