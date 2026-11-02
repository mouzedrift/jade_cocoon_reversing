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


#if 0
void sub_80010228(void)
{
}
#endif
INCLUDE_ASM(sub_80010228);
// Matched
void InitEvents_8001028C(void)
{
    cdRomEventDescError_8008B490 = OpenEvent(HwCdRom, EvSpERROR, EvMdINTR, cdRomEventErrorHandler_8003BBAC);
    EnableEvent(cdRomEventDescError_8008B490);

    vsyncEventDesc_8008B494 = OpenEvent(RCntCNT3, EvSpINT, EvMdINTR, vsyncEventHandler_800103AC);
    EnableEvent(vsyncEventDesc_8008B494);

    SetRCnt(RCntCNT3, RCntMdSC, RCntMdINTR);
    StartRCnt(RCntCNT3);

    dword_8008B4B4 = 0;
    gnFrame_8008D610 = 0;
}
#if 0
void CloseEvents_80010328(void)
{
}
#endif
INCLUDE_ASM(CloseEvents_80010328);
// Matched
long vsyncEventHandler_800103AC(void)
{
    ++dword_8008B4B4;
    ++gnFrame_8008D610;
    --dword_8008D450;
    if (!(unknownFlags_8008D678 & 8))
    {
        dword_8008D404++;
        saveData_8008B570.field_4++;
    }

    return dword_8008B4B4;
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
INCLUDE_ASM(__main);
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
            sub_800403E8((unsigned int*)&saveData_8008B570.items[i], (unsigned int*)pItem, sizeof(Item));
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
INCLUDE_ASM(sub_80010850);
#if 0
int* sub_8001091C(void)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8001091C);
#if 0
void sub_8001098C(int arg0)
{
}
#endif
INCLUDE_ASM(sub_8001098C);
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
#if 0
void sub_80010AD8(int arg0)
{
}
#endif
INCLUDE_ASM(sub_80010AD8);
