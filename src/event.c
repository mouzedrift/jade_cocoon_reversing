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
#include "event.h"
#include "winframe.h"
#include "util.h"
#include "unit_query.h"


const char aDWorkPsusEvent[] = "D:/WORK/PSUS/EVENT.C";
extern const char aDWorkPsusEvent[];
#define malloc3_dbg ((void* (*)(int, const char*, int))malloc3_8003FC4C)
#define free3_dbg ((void (*)(void*, const char*, int))free3_8003FC6C)

extern short uiColor_8008B590;
extern void GetWindowColors_8004226C(int colorSet, RECT* rgbOut, int time, int colorIdx);

extern unsigned char** windowColorSets_80087064[];
extern unsigned char* windowPulseColors_80087050[];
extern int windowPulseScale_80086FB0[][3];
// Matched
void GetWindowColors_8004226C(int colorSet, RECT* rgbOut, int time, int colorIdx)
{
    unsigned char* out = (unsigned char*)rgbOut;
    unsigned char c0[4];
    unsigned char c1[4];
    int cr;
    int cg;
    int cb;

    out[0] = windowColorSets_80087064[(short)colorSet][colorIdx][0];
    out[1] = windowColorSets_80087064[(short)colorSet][colorIdx][1];
    out[2] = windowColorSets_80087064[(short)colorSet][colorIdx][2];
    if ((short)colorSet == 1)
    {
        cr = out[0] * windowPulseScale_80086FB0[colorIdx][0] / 100;
        cg = out[1] * windowPulseScale_80086FB0[colorIdx][1] / 100;
        cb = out[2] * windowPulseScale_80086FB0[colorIdx][2] / 100;
        if (cr > 0xFF)
        {
            cr = 0xFF;
        }
        if (cg > 0xFF)
        {
            cg = 0xFF;
        }
        if (cb > 0xFF)
        {
            cb = 0xFF;
        }
        if (cr < 0)
        {
            cr = 0;
        }
        if (cg < 0)
        {
            cg = 0;
        }
        if (cb < 0)
        {
            cb = 0;
        }
        c0[0] = cr;
        c0[1] = cg;
        c0[2] = cb;
        c1[0] = windowPulseColors_80087050[colorIdx][0];
        c1[1] = windowPulseColors_80087050[colorIdx][1];
        c1[2] = windowPulseColors_80087050[colorIdx][2];
        PulseColor_80033394(out, c0, c1, time, 40, 10);
    }
}
// Matched
void DrawWindow_80042460(int rect, unsigned char* style, int ot, int time)
{
    RECT rgb;
    GetWindowColors_8004226C(style[2], &rgb, time, *(short*)style);
    DrawWindowFrame_80041ED0(rect, &rgb, ot, style[3]);
}
// Matched
void DrawUiColorWindow_800424C0(int rect, short colorSet, int ot, int time)
{
    RECT rgb;
    GetWindowColors_8004226C(colorSet, &rgb, time, uiColor_8008B590);
    DrawWindowFrame_80041ED0(rect, &rgb, ot, 1);
}
// Matched
void DrawGouraudRect_8004251C(RECT* rect, unsigned char (*rgb)[4], unsigned char abr, unsigned long* ot)
{
    POLY_G4 poly;
    DR_TPAGE dt;

    SetPolyG4(&poly);
    if (abr)
    {
        setSemiTrans(&poly, 1);
    }
    setRGB0(&poly, rgb[0][0], rgb[0][1], rgb[0][2]);
    setRGB1(&poly, rgb[1][0], rgb[1][1], rgb[1][2]);
    setRGB2(&poly, rgb[2][0], rgb[2][1], rgb[2][2]);
    setRGB3(&poly, rgb[3][0], rgb[3][1], rgb[3][2]);
    setXY4(&poly, rect->x, rect->y, rect->x + rect->w, rect->y, rect->x, rect->y + rect->h, rect->x + rect->w, rect->y + rect->h);
    AddPrimCopy_80040298(ot, &poly, 9);
    if (abr)
    {
        SetDrawTPage(&dt, 0, 1, GetTPage(0, abr - 1, 0, 0));
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = dt.tag;
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = dt.code[0];
        addPrim(ot, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
    }
}
extern void DrawLine_80042870(DVECTOR* from, DVECTOR* to, unsigned char* rgb, void* ot);
// Matched
void DrawRectOutline_80042750(RECT* rect, unsigned char* rgb, void* ot)
{
    LINE_F4 line;
    DVECTOR from;
    DVECTOR to;
    setLineF4(&line);
    setRGB0(&line, rgb[0], rgb[1], rgb[2]);
    setXY4(&line, rect->x, rect->y, rect->x + rect->w, rect->y, rect->x + rect->w, rect->y + rect->h, rect->x, rect->y + rect->h);
    AddPrimCopy_80040298(ot, &line, 7);
    from.vx = line.x0;
    from.vy = line.y0;
    to.vx = line.x3;
    to.vy = line.y3;
    DrawLine_80042870(&from, &to, rgb, ot);
}
// Matched
void DrawLine_80042870(DVECTOR* from, DVECTOR* to, unsigned char* rgb, void* ot)
{
    LINE_F2 line;
    DR_TPAGE dt;
    setLineF2(&line);
    setRGB0(&line, rgb[0], rgb[1], rgb[2]);
    setXY2(&line, from->vx, from->vy, to->vx, to->vy);
    AddPrimCopy_80040298(ot, &line, 4);
    SetDrawTPage(&dt, 0, 1, GetTPage(0, 0, 0, 0));
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = dt.tag;
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = dt.code[0];
    addPrim(ot, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
// Matched
int IsWindowFrameFit_800429A8(short* rect)
{
    SPRT* sprts = publicTiySprts_8008D434;
    if (rect[2] >= *(short*)&sprts[79].w + *(short*)&sprts[82].w && rect[3] >= *(short*)&sprts[79].h + *(short*)&sprts[82].h)
    {
        return 1;
    }
    return 0;
}
extern unsigned char* windowBgColors_80087028[];
// Matched
void DrawWindowBackground_800429F8(int rect, int ot)
{
    short* box = (short*)rect;
    SPRT* sprts = publicTiySprts_8008D434;
    unsigned char rgb[4][4];
    RECT inner;
    short i;

    if (box[2] >= *(short*)&sprts[79].w + *(short*)&sprts[82].w && box[3] >= *(short*)&sprts[79].h + *(short*)&sprts[82].h)
    {
        inner.x = box[0] + 3;
        inner.y = box[1] + 2;
        inner.w = box[2] - 6;
        inner.h = box[3] - 4;
        for (i = 0; i < 4; i++)
        {
            rgb[i][0] = windowBgColors_80087028[(short)saveData_8008B570.uiColor_20.i][0];
            rgb[i][1] = windowBgColors_80087028[(short)saveData_8008B570.uiColor_20.i][1];
            rgb[i][2] = windowBgColors_80087028[(short)saveData_8008B570.uiColor_20.i][2];
        }
        DrawGouraudRect_8004251C(&inner, rgb, 1, pOT_8008D454 + (short)ot);
    }
}
#define EVT_SPRT publicTiySprts_8008D434
// Matched
void DrawWindowBorder_80042B38(int rect, int ot)
{
    short* box = (short*)rect;
    RECT parts[8];
    short w;
    short h;

    if (box[2] >= EVT_SPRT[79].w + EVT_SPRT[82].w && box[3] >= EVT_SPRT[79].h + EVT_SPRT[82].h)
    {
        parts[0].w = EVT_SPRT[79].w;
        parts[0].h = EVT_SPRT[79].h;
        parts[1].w = EVT_SPRT[82].w;
        parts[1].h = EVT_SPRT[82].h;
        parts[2].w = EVT_SPRT[80].w;
        parts[2].h = EVT_SPRT[80].h;
        parts[3].w = EVT_SPRT[81].w;
        parts[3].h = EVT_SPRT[81].h;
        parts[4].w = EVT_SPRT[86].w;
        parts[4].h = EVT_SPRT[86].h;
        parts[5].w = EVT_SPRT[83].w;
        parts[5].h = EVT_SPRT[83].h;
        parts[6].w = EVT_SPRT[84].w;
        parts[6].h = EVT_SPRT[84].h;
        parts[7].w = EVT_SPRT[85].w;
        parts[7].h = EVT_SPRT[85].h;

        w = box[2] - (parts[0].w + parts[1].w);
        h = box[3] - (parts[0].h + parts[2].h);
        parts[0].x = box[0];
        parts[0].y = box[1];
        parts[4].x = parts[0].x + parts[0].w;
        parts[4].y = box[1];
        parts[4].w = w;
        parts[1].x = parts[4].x + parts[4].w;
        parts[1].y = box[1];
        parts[6].x = box[0];
        parts[6].y = parts[0].y + parts[0].h;
        parts[6].w = parts[6].w - 1;
        parts[6].h = h;
        parts[7].x = box[0] + box[2] - parts[7].w;
        parts[7].y = parts[1].y + parts[1].h;
        parts[7].w = parts[7].w - 1;
        parts[7].h = parts[6].h;
        parts[2].x = box[0];
        parts[2].y = parts[6].y + parts[6].h;
        parts[5].x = parts[2].x + parts[2].w;
        parts[5].y = box[1] + box[3] - parts[5].h;
        parts[5].w = parts[4].w;
        parts[3].x = parts[5].x + parts[5].w;
        parts[3].y = parts[2].y;

        EVT_SPRT[79].x0 = parts[0].x;
        EVT_SPRT[79].y0 = parts[0].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &EVT_SPRT[79], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyTPages_8008D440[79], 2);
        EVT_SPRT[82].x0 = parts[1].x;
        EVT_SPRT[82].y0 = parts[1].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &EVT_SPRT[82], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyTPages_8008D440[82], 2);
        EVT_SPRT[80].x0 = parts[2].x;
        EVT_SPRT[80].y0 = parts[2].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &EVT_SPRT[80], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyTPages_8008D440[80], 2);
        EVT_SPRT[81].x0 = parts[3].x;
        EVT_SPRT[81].y0 = parts[3].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &EVT_SPRT[81], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyTPages_8008D440[81], 2);
        setXYWH(&publicTiyPolyFT4s_8008D430[86], parts[4].x, parts[4].y, parts[4].w, parts[4].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyPolyFT4s_8008D430[86], 10);
        setXYWH(&publicTiyPolyFT4s_8008D430[83], parts[5].x, parts[5].y, parts[5].w, parts[5].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyPolyFT4s_8008D430[83], 10);
        setXYWH(&publicTiyPolyFT4s_8008D430[84], parts[6].x, parts[6].y, parts[6].w, parts[6].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyPolyFT4s_8008D430[84], 10);
        setXYWH(&publicTiyPolyFT4s_8008D430[85], parts[7].x, parts[7].y, parts[7].w, parts[7].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)ot, &publicTiyPolyFT4s_8008D430[85], 10);
    }
}
extern int SetCdXaLock_8003C0A4(int lock);
extern int XaStartRead_800434C4(int pos);
extern int xaStartPos_80096108;
extern int xaEndPos_8009610C;
extern void XaIdleTask_800430E8();
extern void XaMonitorTask_800432EC();

// Matched
void XaInitTask_80043054(EventEntry* entry, XaTask* task)
{
    SsSetSerialAttr(0, 0, 1);
    xaRequestPending_80096118 = -1;
    task->flags_0 = 0;
    task->state_8 = 0;
    entry->cb_8 = (EventEntryFn)XaIdleTask_800430E8;
}
// Matched
void XaStop_800430B0(void)
{
    SsSetSerialVol(0, 0, 0);
    DsControlB(9, 0, 0);
}
extern int DsSystemStatus(void);
void XaSetup_800433FC(XaTask* task);
// Matched
void XaIdleTask_800430E8(EventEntry* entry, XaTask* buffer)
{
    XaTask* task = buffer;
    int status;
    int lock;
    if (task->flags_0 & 1)
    {
        task->flags_0 &= ~1;
        xaRequestPending_80096118 = -1;
    }
    if ((int)xaRequestPending_80096118 >= 0 && (status = DsSystemStatus()) == 1 && (lock = SetCdXaLock_8003C0A4(status)) == status)
    {
        XaSetup_800433FC(task);
        xaRequestPending_80096118 = -1;
        task->state_8 = lock;
        task->flags_0 &= ~1;
        entry->cb_8 = (EventEntryFn)XaWaitFilterTask_800431C4;
    }
}
// Matched
void XaWaitFilterTask_800431C4(EventEntry* entry, XaTask* task)
{
    char buf[8];
    if (DsSync(task->cmd_4, buf) == 2)
    {
        entry->cb_8 = (EventEntryFn)XaStartReadTask_80043204;
    }
}
// Matched
void XaStartReadTask_80043204(EventEntry* entry, XaTask* task)
{
    if (XaStartRead_800434C4(xaStartPos_80096108))
    {
        task->cmd_4 = DsControlF(0x11, 0);
        task->state_8 = 2;
        entry->cb_8 = (EventEntryFn)XaMonitorTask_800432EC;
    }
}
// Matched
void XaFadeOutTask_80043264(EventEntry* entry, XaTask* task)
{
    short vol = task->vol_A - 14;
    task->vol_A = vol;
    if (vol < 0)
    {
        task->state_8 = 0;
        entry->cb_8 = (EventEntryFn)XaIdleTask_800430E8;
        SsSetSerialVol(0, 0, 0);
        DsControlB(9, 0, 0);
        SetCdXaLock_8003C0A4(0);
    }
    else
    {
        SsSetSerialVol(0, vol, vol);
    }
}
// Matched
void XaMonitorTask_800432EC(EventEntry* entry, XaTask* task)
{
    u_char result[8];
    DslLOC loc;
    if (DsSync(task->cmd_4, result) == 2 && task->cmd_4)
    {
        loc.minute = result[5];
        loc.second = result[6];
        loc.sector = result[7];
        if (DsPosToInt(&loc) > xaEndPos_8009610C || (int)xaRequestPending_80096118 >= 0)
        {
            task->vol_A = 0x70;
            entry->cb_8 = (EventEntryFn)XaFadeOutTask_80043264;
            return;
        }
        SsSetSerialVol(0, 0x70, 0x70);
        task->cmd_4 = DsControlF(0x11, 0);
    }
    if (xaTimer_8008D450 < -1000 || (task->flags_0 & 1))
    {
        task->vol_A = 0x70;
        task->flags_0 &= ~1;
        entry->cb_8 = (EventEntryFn)XaFadeOutTask_80043264;
    }
}
extern int DsCommand(u_char com, u_char* param, DslCB cbsync, int count); /* DsCommand */
// Matched
void XaSetup_800433FC(XaTask* task)
{
    Data001File file;
    u_char result[8];
    u_char param[4];
    int cmd;
    DATA_GetFile_8003C7CC(&file, 0x439);
    param[0] = 1;
    param[1] = xaRequest_80096110.channel_2;
    do
    {
        cmd = DsCommand(0xD, param, 0, -1);
        task->cmd_4 = cmd;
    } while (cmd == 0);
    xaStartPos_80096108 = DsPosToInt(&file.field_0_position);
    xaStartPos_80096108 += xaRequest_80096110.startSector_4 * 32;
    xaEndPos_8009610C = xaStartPos_80096108 + xaRequest_80096110.length_6 * 32;
    xaTimer_8008D450 = xaRequest_80096110.length_6 * 1920 / 150;
}
// Matched
int XaStartRead_800434C4(int pos)
{
    unsigned char loc[4];
    int id;
    int mode = 0xC9;
    int com = 0x1B;
    DsIntToPos(pos, loc);
    do
    {
        id = DsPacket(mode, (DslLOC*)loc, com, 0, -1);
    } while (id == 0);
    return id;
}
// Matched
int XaRequestStop_80043524(void)
{
    XaTask* task;
    if ((int)xaRequestPending_80096118 >= 0)
    {
        return 0;
    }
    task = xaTask_8008B560->entry.buffer;
    task->flags_0 |= 1;
    return 1;
}
// Matched
void XaRequestPlay_80043564(short channel, short startSector, short length)
{
    xaRequestPending_80096118 = 0;
    xaRequest_80096110.channel_2 = channel;
    xaRequest_80096110.startSector_4 = startSector;
    xaRequest_80096110.length_6 = length;
}
// Matched
int XaIsIdle_80043584(void)
{
    return ((XaTask*)xaTask_8008B560->entry.buffer)->state_8 == 0;
}
// Matched
unsigned int XaNoRequestPending_800435A4(void)
{
    return xaRequestPending_80096118 >> 31;
}
// Matched
EventNode* CreateEventList_800435B4(EventDesc** list)
{
    EventDesc** descs;
    EventDesc* desc;
    EventNode* next;
    EventNode* head;
    int idx;
    char* buf;
    EventNode* node;
    EventNode* next2;
    EventNode* prev;
    EventNode* last;
    unsigned int i;
    unsigned int flags;

    buf = NULL;
    idx = 0;
    for (descs = list; *descs != NULL; descs++)
    {
        desc = *descs;
        idx += desc->count;
    }
    head = malloc3_dbg((idx + 1) * sizeof(EventNode), aDWorkPsusEvent, 0xDC);
    prev = NULL;
    node = head;
    next = head + 1;
    head->prev_0 = (int)prev;
    next2 = next;
    head->next = next;
    next2++;
    last = head;
    head->entry.size = 0;
    head->entry.buffer = NULL;
    head->entry.flags = 0;
    head->entry.index_4 = 0;
    head->index_8 = 0;
    head->count = 0;
    head->entry.cb_8 = NULL;
    head->entry.cb_C = NULL;
    for (idx = 0, descs = list; *descs != NULL; descs++)
    {
        desc = *descs;
        if (desc->out != NULL)
        {
            *desc->out = node;
        }
        if (desc->size != 0)
        {
            buf = malloc3_dbg(desc->size * desc->count, aDWorkPsusEvent, 0xF1);
        }
        for (i = 0; i < desc->count; i++)
        {
            node->prev_0 = (int)prev;
            node->next = next;
            node->entry.size = 0;
            node->entry.buffer = NULL;
            node->entry.flags = 0;
            node->entry.index_4 = 0;
            node->index_8 = 0;
            node->count = 0;
            node->entry.cb_8 = NULL;
            node->entry.cb_C = NULL;
            if (desc->size != 0)
            {
                node->entry.buffer = buf;
                node->entry.size = desc->size;
                buf += desc->size;
            }
            node->entry.cb_8 = desc->cb_8;
            node->entry.cb_C = desc->cb_C;
            flags = desc->flags;
            node->index_8 = idx++;
            node->entry.flags = flags;
            node->count = desc->count;
            node->entry.index_4 = i;
            prev = last = node;
            node = next;
            next = next2;
            next2++;
        }
    }
    last->next = NULL;
    return head;
}
// Matched
void* EventEntryAllocBuffer_800437E8(int* entry, int size)
{
    void* buffer = malloc3_dbg(size, aDWorkPsusEvent, 0x2C);
    if (buffer == 0)
    {
        return 0;
    }
    entry[5] = (int)buffer;
    entry[4] = size;
    return buffer;
}
// Matched
int EventEntryFreeBuffer_80043840(int* entry)
{
    if (entry[5])
    {
        if (entry[1] == 0)
        {
            free3_dbg((void*)entry[5], aDWorkPsusEvent, 0x45);
        }
        entry[5] = 0;
        entry[4] = 0;
    }
    return 1;
}
// Matched
void RunEventList_80043898(EventNode* node)
{
    do
    {
        if ((node->entry.flags & 0x8001) == 1)
        {
            node->entry.cb_8(&node->entry, node->entry.buffer);
        }
        node = node->next;
    } while (node);
}
// Matched
void RunEventListFreeCallbacks_800438F8(EventNode* node)
{
    do
    {
        if ((node->entry.flags & 0x8004) == 4)
        {
            node->entry.cb_C(&node->entry, node->entry.buffer);
        }
        node = node->next;
    } while (node);
}
// Matched
void RunEventListUntilAbort_80043958(EventNode* node)
{
    if (eventDispatchHalt_8008B540 == 0)
    {
        do
        {
            if ((node->entry.flags & 0x8001) == 1)
            {
                node->entry.cb_8(&node->entry, node->entry.buffer);
            }
            node = node->next;
        } while (node && eventDispatchHalt_8008B540 == 0);
    }
}
// Matched
void ResetEventListFromDescs_800439E0(unsigned int** descs, unsigned int* nodes)
{
    unsigned int* desc;
    unsigned int i;
    while (*descs)
    {
        desc = *descs;
        for (i = 0; i < desc[0]; i++)
        {
            nodes[6] = desc[4];
            nodes[7] = desc[5];
            nodes[4] = desc[1];
        }
        descs++;
        nodes += 10;
    }
}
// Matched
int FreeEventList_80043A5C(EventNode* head)
{
    EventNode* node = head;
    do
    {
        EventEntry* entry = &node->entry;
        if (entry->buffer)
        {
            if (entry->index_4 == 0)
            {
                free3_dbg(entry->buffer, aDWorkPsusEvent, 0x45);
            }
            entry->buffer = 0;
            entry->size = 0;
        }
        node = node->next;
    } while (node);
    free3_dbg(head, aDWorkPsusEvent, 0x143);
    return 0;
}

int windowPulseScale_80086FB0[5][3] = {
    { 100, 100, 160 },
    { 130, 100, 130 },
    { 100, 124, 113 },
    { 150, 140, 100 },
    { 100, 100, 100 },
};
unsigned char windowBgColor0_80086FEC = 42;
unsigned char byte_80086FED = 38;
unsigned char byte_80086FEE = 110;
unsigned char byte_80086FEF = 0;
int windowBgColorData_80086FF0[9] = {
    0x5A266E, 0x666E26, 0x254470, 0x293A55, 0xD81FF, 0xFFFF0A, 0xD81FF, 0x73FF0A,
    0x254470,
};
int windowPulseColorData_80087014[5] = { 0xFFFF0A, 0x5161FF, 0xA5FF4B, 0x25E1FF, 0x427595 };
unsigned char *windowBgColors_80087028[5] = { &windowBgColor0_80086FEC, (void *)windowBgColorData_80086FF0, (void *)&windowBgColorData_80086FF0[1], (void *)&windowBgColorData_80086FF0[2], (void *)&windowBgColorData_80086FF0[3] };
void *windowColorsAlt_8008703C[5] = { (void *)&windowBgColorData_80086FF0[4], (void *)&windowBgColorData_80086FF0[5], (void *)&windowBgColorData_80086FF0[6], (void *)&windowBgColorData_80086FF0[7], (void *)&windowBgColorData_80086FF0[8] };
unsigned char *windowPulseColors_80087050[5] = { (void *)windowPulseColorData_80087014, (void *)&windowPulseColorData_80087014[1], (void *)&windowPulseColorData_80087014[2], (void *)&windowPulseColorData_80087014[3], (void *)&windowPulseColorData_80087014[4] };
unsigned char **windowColorSets_80087064[3] = { windowBgColors_80087028, windowBgColors_80087028, (void *)windowColorsAlt_8008703C };
int windowFrameQuadEdges_80087070[5][8] = {
    { 0, 0, 3, 0, 1, 1, 2, 1 },
    { 0, 0, 1, 1, 0, 3, 1, 2 },
    { 1, 2, 2, 2, 0, 3, 3, 3 },
    { 2, 1, 3, 0, 2, 2, 3, 3 },
    { 1, 1, 2, 1, 1, 2, 2, 2 },
};
int dword_80087110 = 0x439;
MATRIX lightMatrix_80087114 = { {
        { 0x50F, 0, 0xF2E },
        { 0x446, -0xCD4, 0x88D },
        { -0x446, 0xCD4, -0x88D },
    } };
MATRIX colorMatrix_80087134 = { {
        { 0x800, 0x400, 0x200 },
        { 0x800, 0x400, 0x200 },
        { 0x800, 0x400, 0x200 },
    } };

int xaStartPos_80096108 BSS = 0;
int xaEndPos_8009610C BSS = 0;
XaRequest xaRequest_80096110 BSS = { 0 };
unsigned int xaRequestPending_80096118 BSS = 0;
int dword_8009611C BSS = 0;
