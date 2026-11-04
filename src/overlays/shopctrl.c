// SHOPCTRL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "shopctrl.h"

extern int shopCtrlTask_8008D438;
extern int shopMenuTask_8008D670;
extern int eventDispatchHalt_8008B540;
extern short word_8008D474[2];
extern int cameraState_8008D4F0;
extern // restores the map camera GAME saved before the shop and recentres the geometry offset
void RestoreMapCamera_800B6720();
extern void ShopCtrlLoadOverlay_800B6840(EventEntry* task, void* buffer);
extern void ShopCtrlWaitOverlay_800B6898(EventEntry* task, void* buffer);
extern void ShopCtrlWaitUiReload_800B6900(EventEntry* task, void* buffer);
extern void ShopCtrlStartMode_800B6AE0(EventEntry* task, void* buffer);
extern // waits for a mode request: 0 shop, 1 name entry, 2 resume, 3 leave the shop (reload the area)
void ShopCtrlIdle_800B6964(EventEntry* task, void* buffer);
extern void ShopCtrlWaitMapReload_800B6A6C(EventEntry* task, void* buffer);
extern void ShopCtrlInit_800B67C0(EventEntry* task, void* buffer);
extern void ShopCtrlWaitUiTiy_800B681C(EventEntry* task, void* buffer);
extern void StartNameEntry_800B6E4C(int, int);
extern void CommitShopMinionList_800B9DA8();
extern void StartShop_800BB058(int);
extern void SuspendFieldMinions_800A7B00(int);
extern void ResumeFieldMinions_800A7BF0(int);
extern void RequestGameMode_800A6D30(int);
extern void* GetEventDataSlot_800A55B0(int);
extern void SetFadeMode_8001C19C(int, int);
extern void LoadUiTiy_8002BF74();
extern void DrawMenuBackground_8002BE10();
extern void SetLoadFadeFlag_80027478(int, int);
extern void UpdateCameraFollow_80037918(void* camera);
extern void FreeActiveOverlay_8002C014();

int dword_800B66C0 SDATA = 30;

// starts the shop controller task: it loads SHOP (or NAME for a rename) into the slot behind it
void StartShopCtrl_800B66C4(int shopId)
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)shopCtrlTask_8008D438);
    if (e)
    {
        shopCtrlShopId_800B6CEA = shopId;
        e->flags = (e->flags | 1) & ~0x8000;
        RestoreMapCamera_800B6720();
    }
}

// restores the map camera GAME saved before the shop and recentres the geometry offset
void RestoreMapCamera_800B6720()
{
    unsigned short* disp;
    unsigned int* buf = GetEventDataSlot_800A55B0(3);
    MemCopy_800403E8(&cameraState_8008D4F0, buf, 0x104);
    UpdateCameraFollow_80037918(cameraTask_8008D4A0->entry.buffer);
    disp = (unsigned short*)&display_8008B4D8;
    SetGeomOffset((short)disp[6] / 2 + word_8008D474[0], (short)disp[7] / 2 + word_8008D474[1]);
}

void ShopCtrlInit_800B67C0(EventEntry* task, void* buffer)
{
    SetFadeMode_8001C19C(0, 0x20);
    SuspendFieldMinions_800A7B00(-1);
    shopCtrlPrevMode_800B6CE8 = 0;
    shopCtrlMode_800B6CEC = 0;
    shopCtrlReloadUi_800B6CF8 = 0;
    LoadUiTiy_8002BF74();
    task->cb_8 = ShopCtrlWaitUiTiy_800B681C;
}

void ShopCtrlWaitUiTiy_800B681C(EventEntry* task, void* buffer)
{
    if (uiTiyLoaded_8008B4E8)
    {
        task->cb_8 = ShopCtrlLoadOverlay_800B6840;
    }
}

void ShopCtrlLoadOverlay_800B6840(EventEntry* task, void* buffer)
{
    shopCtrlOverlayReq_800B6CF4 = LoadOverlay_80020BF8(1, shopOverlayIds_800B6CD8[shopCtrlMode_800B6CEC]);
    task->cb_8 = ShopCtrlWaitOverlay_800B6898;
}

void ShopCtrlWaitOverlay_800B6898(EventEntry* task, void* buffer)
{
    if (GetFileRequestStatus_8003BE30(shopCtrlOverlayReq_800B6CF4) == 0)
    {
        if (shopCtrlReloadUi_800B6CF8)
        {
            LoadUiTiy_8002BF74();
            task->cb_8 = ShopCtrlWaitUiReload_800B6900;
        }
        else
        {
            task->cb_8 = ShopCtrlStartMode_800B6AE0;
        }
    }
}

void ShopCtrlWaitUiReload_800B6900(EventEntry* task, void* buffer)
{
    if (uiTiyLoaded_8008B4E8)
    {
        DrawMenuBackground_8002BE10();
        if (shopCtrlReloadUi_800B6CF8)
        {
            task->cb_8 = ShopCtrlStartMode_800B6AE0;
        }
        else
        {
            task->cb_8 = ShopCtrlLoadOverlay_800B6840;
        }
        shopCtrlReloadUi_800B6CF8 = 0;
    }
}

// waits for a mode request: 0 shop, 1 name entry, 2 resume, 3 leave the shop (reload the area)
void ShopCtrlIdle_800B6964(EventEntry* task, void* buffer)
{
    if (shopCtrlMode_800B6CEC != shopCtrlPrevMode_800B6CE8)
    {
        if (shopCtrlMode_800B6CEC != 3)
        {
            SuspendFieldMinions_800A7B00(-1);
            if (shopCtrlMode_800B6CEC == 2 && settingsFlags_8008B58C.bits.d_5 == 1)
            {
                SetFadeMode_8001C19C(0, 0x20);
                task->cb_8 = ShopCtrlStartMode_800B6AE0;
            }
            else
            {
                task->cb_8 = ShopCtrlLoadOverlay_800B6840;
                if (shopCtrlMode_800B6CEC == 1 && settingsFlags_8008B58C.bits.d_5 == 1)
                {
                    SetFadeMode_8001C19C(0, 0x20);
                }
            }
        }
        else
        {
            CommitShopMinionList_800B9DA8();
            SetLoadFadeFlag_80027478(0x40, 1);
            FreeActiveOverlay_8002C014();
            RequestAreaReload_80027314();
            task->cb_8 = ShopCtrlWaitMapReload_800B6A6C;
        }
    }
}

void ShopCtrlWaitMapReload_800B6A6C(EventEntry* task, void* buffer)
{
    if (IsMapLoading_800272D0() == 0)
    {
        ResumeFieldMinions_800A7BF0(-1);
        task->cb_8 = ShopCtrlInit_800B67C0;
        task->flags = (task->flags & ~1) | 0x8000;
        SetLoadFadeFlag_80027478(0x40, 0);
        RequestGameMode_800A6D30(1);
        eventDispatchHalt_8008B540 = 1;
    }
}

void ShopCtrlStartMode_800B6AE0(EventEntry* task, void* buffer)
{
    EventEntry* e;
    switch (shopCtrlMode_800B6CEC)
    {
    case 0:
        if (shopCtrlPrevMode_800B6CE8 == 0)
        {
            StartShop_800BB058(shopCtrlShopId_800B6CEA);
        }
        else
        {
            e = AllocEventEntry_80043AF8((EventNode*)shopMenuTask_8008D670);
            if (settingsFlags_8008B58C.bits.d_5 == 1)
            {
                RestoreMapCamera_800B6720();
            }
            if (e)
            {
                e->flags = (e->flags | 1) & ~0x8000;
            }
        }
        break;
    case 1:
        StartNameEntry_800B6E4C(shopCtrlNameTarget_800B6CFC, 0x10);
        SetFadeMode_8001C19C(3, 0x20);
        break;
    case 2:
        e = AllocEventEntry_80043AF8((EventNode*)shopMenuTask_8008D670);
        if (settingsFlags_8008B58C.bits.d_5 == 1)
        {
            RestoreMapCamera_800B6720();
        }
        if (e)
        {
            shopCtrlMode_800B6CEC = 0;
            shopCtrlPrevMode_800B6CE8 = 0;
            e->flags = (e->flags | 1) & ~0x8000;
        }
        break;
    }
    task->cb_8 = ShopCtrlIdle_800B6964;
    shopCtrlPrevMode_800B6CE8 = shopCtrlMode_800B6CEC;
}

void ShopCtrlRequestNameEntry_800B6C6C(int name, int reloadUi)
{
    short prevMode;
    shopCtrlNameTarget_800B6CFC = name;
    prevMode = shopCtrlMode_800B6CEC;
    shopCtrlMode_800B6CEC = 1;
    shopCtrlPrevMode_800B6CE8 = prevMode;
    if (reloadUi)
    {
        shopCtrlReloadUi_800B6CF8 = reloadUi;
    }
}

void ShopCtrlRequestShop_800B6CA0()
{
    short prevMode = shopCtrlMode_800B6CEC;
    shopCtrlMode_800B6CEC = 0;
    shopCtrlPrevMode_800B6CE8 = prevMode;
}

void ShopCtrlRequestExit_800B6CB8()
{
    shopCtrlMode_800B6CEC = 3;
}

void ShopCtrlRequestResume_800B6CC8()
{
    shopCtrlMode_800B6CEC = 2;
}

int shopOverlayIds_800B6CD8[3] = { eShop_13, eName_17, eShop_13 }; // per shopCtrlMode_800B6CEC
int shopMinionCount_800B6CE4 = 0; // SHOP's minion list, kept here across a name entry

short shopCtrlPrevMode_800B6CE8 = 0;
short shopCtrlShopId_800B6CEA = 0;
short shopCtrlMode_800B6CEC = 0;
Minion* shopMinions_800B6CF0 = 0;
int shopCtrlOverlayReq_800B6CF4 = 0;
int shopCtrlReloadUi_800B6CF8 = 0;
int shopCtrlNameTarget_800B6CFC = 0;
