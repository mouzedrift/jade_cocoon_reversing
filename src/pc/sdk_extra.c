/* PC only: the PSY-Q functions the game uses that PSY-Z does not have (yet). libds on top of PSY-Z's libcd, the
   heap on the C library, memory cards on PSY-Z's host filesystem, the rest as on the PlayStation. */
#include <psyz.h>
#include <sanitizer/asan_interface.h>
#define DIRENTRY DIRENTRY /* libapi.h has it (see sdk.h) */
#include <psyz/log.h>
#include <libapi.h>
#include <libcd.h>
#include <libds.h>
#include <libetc.h>
#include <libgpu.h>
#include <libgte.h>
/* psyz.h brings the host's <fcntl.h>; libmcrd.h has the memory card's O_RDONLY / O_WRONLY */
#undef O_RDONLY
#undef O_WRONLY
#include <libmcrd.h>
#include <libmcx.h>
#include <libpress.h>
#include <libsnd.h>
#include <libspu.h>
#include <stdlib.h>
#include <string.h>

/* libds: the same commands as libcd, with a command queue the game only uses one entry of at a time */

static u_char locPResult[8]; /* DsControlF's CdlGetlocP */
static int locPValid;

int DsInit(void) { return CdInit(); }
int DsSetDebug(int level) { return CdSetDebug(level); }
int DsPosToInt(DslLOC* p) { return CdPosToInt((CdlLOC*)p); }
DslLOC* DsIntToPos(int i, DslLOC* p) { return (DslLOC*)CdIntToPos(i, (CdlLOC*)p); }
int DsControl(u_char com, u_char* param, u_char* result) { return CdControl(com, param, result); }
int DsControlB(u_char com, u_char* param, u_char* result)
{
    locPValid = 0;
    return CdControlB(com, param, result);
}
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
/* PSY-Z has no CdlGetlocP, which the XA player polls for the playing sector (the absolute position in result[5..7])
   to stop at the end of a voice: it is made from CdlGetlocL's position, and DsSync hands it back */
int DsControlF(u_char com, u_char* param)
{
    u_char loc[8] = { 0 };
    if (com == CdlGetlocP)
    {
        CdControlB(CdlGetlocL, NULL, loc);
        memset(locPResult, 0, sizeof(locPResult));
        locPResult[0] = CdStatus();
        locPResult[1] = 1; /* track */
        locPResult[2] = 1; /* index */
        locPResult[5] = loc[0];
        locPResult[6] = loc[1];
        locPResult[7] = loc[2];
        locPValid = 1;
        return ++dsLastId;
    }
    locPValid = 0;
    CdControlF(com, param);
    return ++dsLastId;
}
int DsCommand(u_char com, u_char* param, DslCB cbsync, int count)
{
    u_char result[8];
    locPValid = 0;
    CdControlB(com, param, result);
    if (cbsync)
        cbsync(CdlComplete, result);
    return ++dsLastId;
}
/* setmode, setloc and the command */
int DsPacket(u_char mode, DslLOC* pos, u_char com, DslCB cbsync, int count)
{
    u_char result[8] = { 0 };
    locPValid = 0;
    if (com == CdlReadN && pos && !(mode & CdlModeRT))
    {
        packetSector = CdPosToInt((CdlLOC*)pos);
        packetMode = mode & ~(CdlModeSize0 | CdlModeSize1); /* DsGetSector takes the 2048 data bytes */
        if (cbsync)
            cbsync(CdlComplete, result);
        DeliverSectors();
        return ++dsLastId;
    }
    /* the XA player sets CdlModeDA too, which only matters to CdlPlay; PSY-Z would mix CD-DA instead of the XA */
    if ((com == CdlReadN || com == CdlReadS) && (mode & CdlModeRT))
        mode &= ~CdlModeDA;
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
    int r;
    if (locPValid)
    {
        if (result)
            memcpy(result, locPResult, sizeof(locPResult));
        return DslComplete;
    }
    r = CdSync(1, result);
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
/* and is preceded by a header: HeapFree_8003FD18 reads the PoolBlock before a block to tell pool blocks from malloc3
   ones (IsPoolBlock_80040274); a zeroed one never has the pool magic (32 bytes keep the 16-byte alignment) */
#define HEAP3_HEADER 32
void* malloc3(size_t size)
{
    char* p = calloc(1, HEAP3_HEADER + size + HEAP3_SLACK);
    ASAN_POISON_MEMORY_REGION(p + HEAP3_HEADER + size, HEAP3_SLACK); /* AddressSanitizer still reports reads past the block */
    return p + HEAP3_HEADER;
}
void free3(void* p)
{
    if (p)
        free((char*)p - HEAP3_HEADER);
}

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

static long memCardCmd;
static long memCardResult;
static int memCardPending;

static int MapMemCardFilename(const char* file, char* mapped, size_t mappedSize)
{
    /* PSY-Z limits host filenames to 19 characters; keep Jade Cocoon's 20-character slots distinct. */
    static const char savePrefix[] = "BASLUS-00854";
    size_t len = strlen(file);
    if (len <= 19)
    {
        if (len + 1 > mappedSize)
        {
            return 0;
        }
        memcpy(mapped, file, len + 1);
        return 1;
    }
    if (len == 20 && mappedSize >= 16 && memcmp(file, savePrefix, sizeof(savePrefix) - 1) == 0 &&
        (memcmp(file + 12, "GAME04", 6) == 0 || memcmp(file + 12, "COMB04", 6) == 0) &&
        file[18] >= '0' && file[18] <= '1' && file[19] >= '0' && file[19] <= '9')
    {
        memcpy(mapped, savePrefix, sizeof(savePrefix) - 1);
        mapped[12] = file[15] == 'E' ? 'G' : 'C';
        mapped[13] = file[18];
        mapped[14] = file[19];
        mapped[15] = '\0';
        return 1;
    }
    return 0;
}

static void RestoreMemCardFilename(const char* file, char* restored, size_t restoredSize)
{
    static const char savePrefix[] = "BASLUS-00854";
    size_t len = strlen(file);
    if (len == 15 && memcmp(file, savePrefix, sizeof(savePrefix) - 1) == 0 &&
        (file[12] == 'G' || file[12] == 'C') && file[13] >= '0' && file[13] <= '1' && file[14] >= '0' &&
        file[14] <= '9' && restoredSize >= 21)
    {
        memcpy(restored, savePrefix, sizeof(savePrefix) - 1);
        memcpy(restored + 12, file[12] == 'G' ? "GAME04" : "COMB04", 6);
        restored[18] = file[13];
        restored[19] = file[14];
        restored[20] = '\0';
        return;
    }
    if (len >= restoredSize)
    {
        len = restoredSize - 1;
    }
    memcpy(restored, file, len);
    restored[len] = '\0';
}

static int GetMemCardPath(long chan, const char* file, char* path, size_t pathSize)
{
    char mapped[20];
    int port;
    if ((chan & 0x0F) != 0 || (chan != 0 && chan != 0x10))
    {
        return 0;
    }
    port = chan >> 4;
    if (file)
    {
        if (!MapMemCardFilename(file, mapped, sizeof(mapped)))
        {
            return 0;
        }
        snprintf(path, pathSize, "bu%d0:%s", port, mapped);
    }
    else
    {
        snprintf(path, pathSize, "bu%d0:*", port);
    }
    return 1;
}

static int IsValidMemCard(long chan)
{
    char source[16];
    char path[16];
    if (!GetMemCardPath(chan, NULL, source, sizeof(source)))
    {
        return 0;
    }
    Psyz_AdjustPath(path, source, sizeof(path));
    return 1;
}

static int MemCardNameMatches(const char* pattern, const char* name)
{
    if (*pattern == '\0')
    {
        return *name == '\0';
    }
    if (*pattern == '*')
    {
        do
        {
            if (MemCardNameMatches(pattern + 1, name))
            {
                return 1;
            }
        } while (*name++ != '\0');
        return 0;
    }
    if (*name == '\0' || (*pattern != '?' && *pattern != *name))
    {
        return 0;
    }
    return MemCardNameMatches(pattern + 1, name + 1);
}

static int CountMemCardBlocks(long chan)
{
    struct DIRENTRY entry;
    char path[16];
    int blocks = 0;
    if (!GetMemCardPath(chan, NULL, path, sizeof(path)))
    {
        return 15;
    }
    path[4] = '\0';
    for (struct DIRENTRY* file = firstfile(path, &entry); file; file = nextfile(file))
    {
        if (file->size > 0)
        {
            blocks += (file->size + 0x1FFF) / 0x2000;
        }
    }
    return blocks;
}

static int MemCardFileExists(long chan, const char* filename)
{
    char dir[16];
    char mapped[20];
    struct DIRENTRY entry;
    int found = 0;
    if (!GetMemCardPath(chan, NULL, dir, sizeof(dir)) ||
        !MapMemCardFilename(filename, mapped, sizeof(mapped)))
    {
        return 0;
    }
    dir[4] = '\0';
    for (struct DIRENTRY* current = firstfile(dir, &entry); current; current = nextfile(current))
    {
        if (strcmp(current->name, mapped) == 0)
        {
            found = 1;
        }
    }
    return found;
}

static void SetMemCardCompletion(long cmd, long result)
{
    memCardCmd = cmd;
    memCardResult = result;
    memCardPending = 1;
}

static long MemCardFileIo(long chan, char* file, unsigned long* buffer, long offset, long bytes, int writing)
{
    char path[128];
    int fd;
    long transferred;
    if (!GetMemCardPath(chan, file, path, sizeof(path)) || offset < 0 || bytes <= 0 || bytes % 128 != 0)
    {
        return McErrCardInvalid;
    }
    fd = open(path, writing ? FWRITE : FREAD);
    if (fd < 0)
    {
        return McErrFileNotExist;
    }
    if (lseek(fd, (unsigned int)offset, SEEK_SET) == (unsigned long)-1)
    {
        close(fd);
        return McErrCardInvalid;
    }
    if (writing)
    {
        transferred = write(fd, (char*)buffer, (int)bytes);
    }
    else
    {
        transferred = read(fd, buffer, bytes);
    }
    close(fd);
    return transferred == bytes ? McErrNone : McErrCardInvalid;
}

/* PSY-Z stores each card as a host directory (bu00, bu10) and translates the
   PlayStation-style paths through its filesystem wrappers. */
void MemCardInit(long val)
{
    (void)val;
    IsValidMemCard(0);
    IsValidMemCard(0x10);
}
void MemCardEnd(void) {}
void MemCardStart(void) {}
void MemCardStop(void) {}
long MemCardExist(long chan)
{
    if (memCardPending)
    {
        return 0;
    }
    SetMemCardCompletion(McFuncExist, IsValidMemCard(chan) ? McErrNone : McErrCardNotExist);
    return 1;
}
long MemCardAccept(long chan)
{
    if (memCardPending)
    {
        return 0;
    }
    SetMemCardCompletion(McFuncAccept, IsValidMemCard(chan) ? McErrNone : McErrCardNotExist);
    return 1;
}
long MemCardSync(long mode, long* cmd, long* result)
{
    (void)mode;
    if (!memCardPending)
    {
        return -1;
    }
    if (cmd)
    {
        *cmd = memCardCmd;
    }
    if (result)
    {
        *result = memCardResult;
    }
    memCardPending = 0;
    return 1;
}
long MemCardReadFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
    if (memCardPending)
    {
        return 0;
    }
    SetMemCardCompletion(McFuncReadFile, MemCardFileIo(chan, file, adrs, ofs, bytes, 0));
    return 1;
}
long MemCardWriteFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
    if (memCardPending)
    {
        return 0;
    }
    SetMemCardCompletion(McFuncWriteFile, MemCardFileIo(chan, file, adrs, ofs, bytes, 1));
    return 1;
}
long MemCardCreateFile(long chan, char* file, long blocks)
{
    char path[128];
    unsigned char block[0x2000];
    int fd;
    long i;
    if (!GetMemCardPath(chan, file, path, sizeof(path)) || blocks <= 0)
    {
        return McErrCardInvalid;
    }
    if (blocks + CountMemCardBlocks(chan) > 15)
    {
        return McErrBlockFull;
    }
    if (MemCardFileExists(chan, file))
    {
        return McErrAlreadyExist;
    }
    fd = open(path, FCREAT);
    if (fd < 0)
    {
        return McErrCardInvalid;
    }
    memset(block, 0xFF, sizeof(block));
    for (i = 0; i < blocks; i++)
    {
        if (write(fd, (char*)block, sizeof(block)) != sizeof(block))
        {
            close(fd);
            erase(path);
            return McErrCardInvalid;
        }
    }
    close(fd);
    return McErrNone;
}
long MemCardDeleteFile(long chan, char* file)
{
    char path[128];
    if (!GetMemCardPath(chan, file, path, sizeof(path)))
    {
        return McErrCardInvalid;
    }
    if (!MemCardFileExists(chan, file))
    {
        return McErrFileNotExist;
    }
    return erase(path) ? McErrNone : McErrCardInvalid;
}
long MemCardFormat(long chan)
{
    char dir[16];
    char path[128];
    struct DIRENTRY entry;
    if (!GetMemCardPath(chan, NULL, dir, sizeof(dir)))
    {
        return McErrCardNotExist;
    }
    dir[4] = '\0';
    for (struct DIRENTRY* current = firstfile(dir, &entry); current; current = nextfile(current))
    {
        if (!GetMemCardPath(chan, current->name, path, sizeof(path)))
        {
            return McErrCardInvalid;
        }
        if (!erase(path))
        {
            return McErrCardInvalid;
        }
    }
    return McErrNone;
}
long MemCardGetDirentry(long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max)
{
    struct DIRENTRY entry;
    char path[16];
    long count = 0;
    long stored = 0;
    if (files)
    {
        *files = 0;
    }
    if (!GetMemCardPath(chan, NULL, path, sizeof(path)))
    {
        return McErrCardNotExist;
    }
    path[4] = '\0';
    if (ofs < 0 || max < 0)
    {
        return McErrCardInvalid;
    }
    for (struct DIRENTRY* current = firstfile(path, &entry); current; current = nextfile(current))
    {
        char restored[21];
        RestoreMemCardFilename(current->name, restored, sizeof(restored));
        if (!MemCardNameMatches(name, restored))
        {
            continue;
        }
        if (count >= ofs && stored < max && dir)
        {
            dir[stored] = *current;
            memset(dir[stored].name, 0, sizeof(dir[stored].name));
            memcpy(dir[stored].name, restored, strlen(restored));
            dir[stored].attr = 0;
            dir[stored].next = NULL;
            stored++;
        }
        count++;
    }
    if (files)
    {
        *files = count;
    }
    return McErrNone;
}
static long mcxCmd;
static long mcxResult;
static int mcxPending;

void McxStartCom(void) {}
void McxStopCom(void) {}
int McxSync(int mode, long* cmd, long* result)
{
    (void)mode;
    if (!mcxPending)
    {
        return -1;
    }
    if (cmd)
        *cmd = mcxCmd;
    if (result)
        *result = mcxResult;
    mcxPending = 0;
    return 1;
}
int McxAllInfo(int port, unsigned char* state)
{
    if (state)
    {
        memset(state, 0, 18);
    }
    mcxCmd = McxFuncAllInfo;
    mcxResult = IsValidMemCard(port) ? McxErrSuccess : McxErrNoCard;
    mcxPending = 1;
    return 1;
}

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
    /* as libgte's (and gte_MulMatrix0): m0 is left in the GTE rotation matrix, which callers go on to use
       (DrawAnimSkel_80046A58 rotates the bone offset by the parent's matrix with rtv0) */
    SetRotMatrix(m0);
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

/* MDEC: DecDCTvlc2 is DecDCTvlc with a table made by DecDCTvlcBuild; PSY-Z's DecDCTvlc decodes the same bitstream
   (the whole of it) and needs no table */
void DecDCTvlcBuild(u_short* table) {}
int DecDCTvlc2(unsigned long* bs, unsigned long* buf, DECDCTTAB table) { return DecDCTvlc((u_long*)bs, (u_long*)buf); }
