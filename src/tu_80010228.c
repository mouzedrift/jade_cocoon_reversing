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


extern unsigned long SpuSetTransferStartAddr(unsigned long addr);
extern unsigned long SpuWrite0(unsigned long size);
extern void sub_8006EC08(void);
extern void sub_8004EDB8(void);
// Matched
void ShutdownSystems_80010228(void)
{
    SsEnd();
    SpuSetTransferStartAddr(0x1010);
    SpuWrite0(0x7EFF0);
    SsQuit();
    ResetGraph(3);
    StopCallback();
    sub_8006EC08();
    PadStopCom();
    sub_8004EDB8();
}
// Matched
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
// Matched
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
// Matched
long vsyncEventHandler_800103AC(void)
{
    ++vsyncCounter_8008B4B4;
    ++gnFrame_8008D610;
    --xaTimer_8008D450;
    if (!(unknownFlags_8008D678 & 8))
    {
        dword_8008D404++;
        saveData_8008B570.playTime_4++;
    }

    return vsyncCounter_8008B4B4;
}
// Matched
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
// Matched
void __main(void)
{
}
INCLUDE_ASM(start);
INCLUDE_ASM(dword_80010528);
INCLUDE_ASM(dword_8001052C);
// Matched
int sub_80010548(int id)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < 15; i++)
    {
        if (saveData_8008B570.minions[i].id == 4)
        {
            continue;
        }
        if (saveData_8008B570.minions[i].id == id || id == 0)
        {
            count++;
        }
    }
    return count;
}
// Matched
Minion* sub_80010598(int id, int nth)
{
    Minion* result;
    int matches;
    int i;

    result = 0;
    matches = 0;
    for (i = 0; i < 15; i++)
    {
        if (id == saveData_8008B570.minions[i].id || id == 0)
        {
            matches++;
            if (nth < matches)
            {
                result = &saveData_8008B570.minions[i];
                break;
            }
        }
    }
    return result;
}
#if 0
// Not matched: only the order of the two constant loads (4 / 0xE) differs
void sub_80010600(void)
{
    int i;

    for (i = 14; i >= 0; i--)
    {
        saveData_8008B570.minions[i].id = 4;
    }
    for (i = 11; i >= 0; i--)
    {
        saveData_8008B570.items[i].id = 0xD3;
    }
}
#endif
// Matched
void sub_80010600(void)
{
    int i;
    int v = 4;

    for (i = 14; i >= 0; i--)
    {
        saveData_8008B570.minions[i].id = v;
    }
    v = 0xD3;
    for (i = 11; i >= 0; i--)
    {
        saveData_8008B570.items[i].id = v;
    }
}
// Matched
int sub_80010650(Item* pItem)
{
    int i;

    for (i = 0; i < 12; i++)
    {
        if (saveData_8008B570.items[i].id == 0xD3)
        {
            MemCopy_800403E8((unsigned int*)&saveData_8008B570.items[i], (unsigned int*)pItem, sizeof(Item));
            return 1;
        }
    }
    return 0;
}
// Matched
int sub_800106B8(void)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < 12; i++)
    {
        if (saveData_8008B570.items[i].id != 0xD3)
        {
            count++;
        }
    }
    return count;
}
// Matched
char* sub_800106F8(int id, int nth)
{
    Minion* m = sub_80010598(id, nth);
    if (m)
    {
        return m->field_94;
    }
    return 0;
}
// Matched
char* sub_80010724(int id, int nth, int idx)
{
    Minion* m = sub_80010598(id, nth);
    if (m)
    {
        return (char*)m + (idx * 12 + 4);
    }
    return 0;
}
// Matched
unsigned char sub_80010768(int id, int nth, int idx)
{
    Minion* m = sub_80010598(id, nth);
    if (m)
    {
        return m->field_7C[idx];
    }
    return 0;
}
// Matched
char* sub_800107A0(int id, int nth)
{
    Minion* m = sub_80010598(id, nth);
    if (m)
    {
        return m->field_84;
    }
    return 0;
}
// Matched
char* sub_800107CC(int id, int nth)
{
    Minion* m = sub_80010598(id, nth);
    if (m)
    {
        return m->field_CC;
    }
    return 0;
}
// Matched
char* sub_800107F8(int id, int nth)
{
    Minion* m = sub_80010598(id, nth);
    if (m)
    {
        return m->field_DE;
    }
    return 0;
}
// Matched
char* sub_80010824(int id, int nth)
{
    Minion* m = sub_80010598(id, nth);
    if (m)
    {
        return m->field_F4;
    }
    return 0;
}
extern EventNode* dword_8008D618;
// Matched
int sub_80010850(void* a0)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D618);
    int* buf;
    int* m;
    if (e != 0)
    {
        e->cb_8 = (EventEntryFn)sub_80010A90;
        buf = (int*)e->buffer;
        e->cb_C = (EventEntryFn)sub_80010AB4;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        e->flags = (e->flags | 4) & 0xFFFF7FFF;
        buf[0] = e->field_4;
        m = malloc3_8003FC4C(0x40);
        buf[1] = (int)m;
        MemCopy_800403E8((unsigned int*)(m + 1), (unsigned int*)a0, 0x34);
        m[0] = 0;
        m[0x38 / 4] = 1;
        m[0x3C / 4] = 1;
        sub_80010AD8((int)m);
        return buf[0];
    }
    return -1;
}
// Matched
int* sub_8001091C(key)
int key;
{
    EventNode* n = dword_8008D618;
    int count = n->count;
    EventEntry* e;
    int i;
    for (i = 0; i < count; i++)
    {
        e = &n->entry;
        if ((e->flags & 0x8001) == 1)
        {
            if (*(int*)e->buffer == key)
            {
                return (int*)e;
            }
        }
        n = n->next;
    }
    return 0;
}
// Matched
int sub_8001098C(int arg0)
{
    EventEntry* e = (EventEntry*)sub_8001091C();
    int* buf = (int*)e->buffer;
    int* q = (int*)buf[1];
    if (q[0x38 / 4] == 5)
    {
        sub_80024BB0((int*)buf[1]);
        free3_8003FC6C((void*)buf[1]);
        e->flags = (e->flags & ~1) | 0x8000;
        e->flags = (e->flags & ~4) | 0x8000;
        return 1;
    }
    return 0;
}
// Matched
void sub_80010A10(int arg0)
{
    int* p = sub_8001091C();
    sub_80010AD8(((int**)p)[0x14 / 4][1]);
}
// Matched
int sub_80010A44(void)
{
    int* p = (int*)((int*)sub_8001091C())[5];
    int* q = (int*)p[1];
    if (q[0x38 / 4] == 5)
    {
        return ((int*)q[0])[2];
    }
    return 0;
}
// Matched
void sub_80010A90(int arg0, int* arg1)
{
    sub_80010A10(*arg1);
}
// Matched
void sub_80010AB4(int arg0, int* arg1)
{
    sub_8001098C(*arg1);
}
// Matched
int sub_80010AD8(int arg0)
{
    struct_state_obj* p = (struct_state_obj*)arg0;
    int cont = 1;
    int r = 0;
    do
    {
        switch (p->state_38)
        {
        case 0:
            break;
        case 1:
            cont = sub_80010B90(p);
            break;
        case 2:
            cont = sub_80010DB0(p);
            break;
        case 3:
            cont = sub_80010CDC(p);
            break;
        case 4:
            cont = sub_80010C30(p);
            break;
        case 5:
            cont = 0;
            r = 1;
            break;
        }
    } while (cont);
    return r;
}
