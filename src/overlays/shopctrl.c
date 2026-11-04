// SHOPCTRL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct ShopCtrlTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} ShopCtrlTask;

extern short word_800B6CE8;
extern short word_800B6CEA;
extern short word_800B6CEC;
extern int dword_800B6CD8[];
extern int dword_800B6CF4;
extern int dword_800B6CF8;
extern int dword_800B6CFC;
extern int dword_8008D438;
extern int dword_8008D670;
typedef struct { unsigned int pad:5; unsigned int f5:1; } ShopCtrlFlags;
extern ShopCtrlFlags dword_8008B58C;
extern int eventDispatchHalt_8008B540;
extern short word_8008D474[2];
extern int cameraState_8008D4F0;
extern void sub_800B6720();
extern void sub_800B6840();
extern void sub_800B6898();
extern void sub_800B6900();
extern void sub_800B6AE0();
extern void sub_800B6964();
extern void sub_800B6A6C();
extern void sub_800B67C0();
extern void sub_800B681C();
extern void StartNameEntry_800B6E4C(int, int);
extern void sub_800B9DA8();
extern void sub_800BB058(int);
extern void sub_800A7B00(int);
extern void sub_800A7BF0(int);
extern void sub_800A6D30(int);
extern void* sub_800A55B0(int);
extern void SetFadeMode_8001C19C(int, int);
extern void LoadUiTiy_8002BF74();
extern void DrawMenuBackground_8002BE10();
extern void SetLoadFadeFlag_80027478(int, int);
extern void sub_80037918(void* p);
extern void FreeActiveOverlay_8002C014();

INCLUDE_OVERLAY_ASM(shopctrl, dword_800B66C0);

void sub_800B66C4(int a)
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008D438);
    if (e)
    {
        word_800B6CEA = a;
        e->flags = (e->flags | 1) & ~0x8000;
        sub_800B6720();
    }
}

void sub_800B6720()
{
    unsigned short* s;
    unsigned int* buf = sub_800A55B0(3);
    MemCopy_800403E8(&cameraState_8008D4F0, buf, 0x104);
    sub_80037918(cameraTask_8008D4A0->entry.buffer);
    s = (unsigned short*)&display_8008B4D8;
    SetGeomOffset((short)s[6] / 2 + word_8008D474[0], (short)s[7] / 2 + word_8008D474[1]);
}

void sub_800B67C0(ShopCtrlTask* t)
{
    SetFadeMode_8001C19C(0, 0x20);
    sub_800A7B00(-1);
    word_800B6CE8 = 0;
    word_800B6CEC = 0;
    dword_800B6CF8 = 0;
    LoadUiTiy_8002BF74();
    t->next_8 = sub_800B681C;
}

void sub_800B681C(ShopCtrlTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        t->next_8 = sub_800B6840;
    }
}

void sub_800B6840(ShopCtrlTask* t)
{
    dword_800B6CF4 = LoadOverlay_80020BF8(1, dword_800B6CD8[word_800B6CEC]);
    t->next_8 = sub_800B6898;
}

void sub_800B6898(ShopCtrlTask* t)
{
    if (GetFileRequestStatus_8003BE30(dword_800B6CF4) == 0)
    {
        if (dword_800B6CF8)
        {
            LoadUiTiy_8002BF74();
            t->next_8 = sub_800B6900;
        }
        else
        {
            t->next_8 = sub_800B6AE0;
        }
    }
}

void sub_800B6900(ShopCtrlTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        DrawMenuBackground_8002BE10();
        if (dword_800B6CF8)
        {
            t->next_8 = sub_800B6AE0;
        }
        else
        {
            t->next_8 = sub_800B6840;
        }
        dword_800B6CF8 = 0;
    }
}

void sub_800B6964(ShopCtrlTask* t)
{
    if (word_800B6CEC != word_800B6CE8)
    {
        if (word_800B6CEC != 3)
        {
            sub_800A7B00(-1);
            if (word_800B6CEC == 2 && dword_8008B58C.f5 == 1)
            {
                SetFadeMode_8001C19C(0, 0x20);
                t->next_8 = sub_800B6AE0;
            }
            else
            {
                t->next_8 = sub_800B6840;
                if (word_800B6CEC == 1 && dword_8008B58C.f5 == 1)
                {
                    SetFadeMode_8001C19C(0, 0x20);
                }
            }
        }
        else
        {
            sub_800B9DA8();
            SetLoadFadeFlag_80027478(0x40, 1);
            FreeActiveOverlay_8002C014();
            RequestAreaReload_80027314();
            t->next_8 = sub_800B6A6C;
        }
    }
}

void sub_800B6A6C(ShopCtrlTask* t)
{
    if (IsMapLoading_800272D0() == 0)
    {
        sub_800A7BF0(-1);
        t->next_8 = sub_800B67C0;
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
        SetLoadFadeFlag_80027478(0x40, 0);
        sub_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
    }
}

void sub_800B6AE0(ShopCtrlTask* t)
{
    EventEntry* e;
    switch (word_800B6CEC)
    {
    case 0:
        if (word_800B6CE8 == 0)
        {
            sub_800BB058(word_800B6CEA);
        }
        else
        {
            e = AllocEventEntry_80043AF8((EventNode*)dword_8008D670);
            if (dword_8008B58C.f5 == 1)
            {
                sub_800B6720();
            }
            if (e)
            {
                e->flags = (e->flags | 1) & ~0x8000;
            }
        }
        break;
    case 1:
        StartNameEntry_800B6E4C(dword_800B6CFC, 0x10);
        SetFadeMode_8001C19C(3, 0x20);
        break;
    case 2:
        e = AllocEventEntry_80043AF8((EventNode*)dword_8008D670);
        if (dword_8008B58C.f5 == 1)
        {
            sub_800B6720();
        }
        if (e)
        {
            word_800B6CEC = 0;
            word_800B6CE8 = 0;
            e->flags = (e->flags | 1) & ~0x8000;
        }
        break;
    }
    t->next_8 = sub_800B6964;
    word_800B6CE8 = word_800B6CEC;
}

void sub_800B6C6C(int a, int b)
{
    short t;
    dword_800B6CFC = a;
    t = word_800B6CEC;
    word_800B6CEC = 1;
    word_800B6CE8 = t;
    if (b)
    {
        dword_800B6CF8 = b;
    }
}

void sub_800B6CA0()
{
    short t = word_800B6CEC;
    word_800B6CEC = 0;
    word_800B6CE8 = t;
}

void sub_800B6CB8()
{
    word_800B6CEC = 3;
}

void sub_800B6CC8()
{
    word_800B6CEC = 2;
}

INCLUDE_OVERLAY_ASM(shopctrl, dword_800B6CD8);
