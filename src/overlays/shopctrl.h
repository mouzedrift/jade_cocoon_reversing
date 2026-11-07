// SHOPCTRL.BIN: declarations shared by its source files
#ifndef _SHOPCTRL_H_
#define _SHOPCTRL_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "engine.h"
#include "camera.h"
#include "model_ftg.h"
#include "util.h"
#include "model.h"
#include "cd.h"
#include "ui_sprites.h"

/* SHOPCTRL functions */
void StartShopCtrl_800B66C4(int shopId);
void RestoreMapCamera_800B6720(); // restores the map camera GAME saved before the shop and recentres the geometry offset
void ShopCtrlInit_800B67C0(EventEntry* task, void* buffer);
void ShopCtrlWaitUiTiy_800B681C(EventEntry* task, void* buffer);
void ShopCtrlLoadOverlay_800B6840(EventEntry* task, void* buffer);
void ShopCtrlWaitOverlay_800B6898(EventEntry* task, void* buffer);
void ShopCtrlWaitUiReload_800B6900(EventEntry* task, void* buffer);
void ShopCtrlIdle_800B6964(EventEntry* task, void* buffer); // waits for a mode request: 0 shop, 1 name entry, 2 resume, 3 leave the shop (reload the area)
void ShopCtrlWaitMapReload_800B6A6C(EventEntry* task, void* buffer);
void ShopCtrlStartMode_800B6AE0(EventEntry* task, void* buffer);
void ShopCtrlRequestNameEntry_800B6C6C(char* name, int reloadUi);
void ShopCtrlRequestShop_800B6CA0();
void ShopCtrlRequestExit_800B6CB8();
void ShopCtrlRequestResume_800B6CC8();

/* SHOPCTRL data */
extern int shopctrlHeader_800B66C0;
extern int shopOverlayIds_800B6CD8[3];
extern int shopMinionCount_800B6CE4;
extern short shopCtrlPrevMode_800B6CE8;
extern short shopCtrlShopId_800B6CEA;
extern short shopCtrlMode_800B6CEC;
extern Minion* shopMinions_800B6CF0;
extern int shopCtrlOverlayReq_800B6CF4;
extern int shopCtrlReloadUi_800B6CF8;
extern char* shopCtrlNameTarget_800B6CFC; // the name StartNameEntry_800B6E4C edits

/* other overlays */
void StartNameEntry_800B6E4C(char* nameDest, int flags); // NAME.BIN (name.c: nameDest is typed int there)
int CommitShopMinionList_800B9DA8(void);                 // SHOP.BIN (shop.h)
void StartShop_800BB058(int shopId);                      // SHOP.BIN (shop.h)
void* GetEventDataSlot_800A55B0(int a);                   // GAME.BIN (eventfnc.h)
void RequestGameMode_800A6D30(int mode);                  // GAME.BIN (game.h)
void SuspendFieldMinions_800A7B00(int idx);               // GAME.BIN (game.h)
void ResumeFieldMinions_800A7BF0(int idx);                // GAME.BIN (game.h)

/* exe-side, to move to <exe header> (named in the comment) */
extern short screenOffset_8008D474[2];    // game.h / eventfnc.h

#endif
