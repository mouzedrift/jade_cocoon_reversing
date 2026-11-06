#ifndef _FUNCS_H_
#define _FUNCS_H_

struct Actor;
struct FtgPolyF3List;
struct FtgPolyG3List;
struct FtgPolyFT3List;
struct FtgPolyGT3List;
struct FtgPolyF4List;
struct FtgPolyG4List;
struct FtgPolyFT4List;
struct FtgPolyGT4List;
struct FtgPolyF3;
struct FtgSrcPolyG3;
struct FtgSrcPolyFT3;
struct FtgSrcPolyGT3;
struct FtgPolyF4;
struct FtgSrcPolyG4;
struct FtgSrcPolyFT4;
struct FtgSrcPolyGT4;
struct FtgSrcSprites9;
struct FtgObject;
struct ModelLoader;
struct ModelLoadParams;
struct ModelAnim;
struct ModelAnimRef;
struct ModelVramSlot;
struct FtgMatList;
struct ModelTaskState;
struct OverlayLoader;
struct SceneFade;
struct XaTask;
struct ActorDesc;
struct SoundStruct;
struct EffectObj;
struct ActorEffectReq;
struct CameraCtrl;
struct MsgWindow;
struct ModelDesc;
struct EffectFile;
struct TimInfo;

#include "SYS/TYPES.H"
#include "LIBDS.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBSPU.H"
#include "enums.h"
#include "globals.h"

typedef struct
{
    DslLOC field_0_position;
    int field_4_sectors;
    int field_8_size;
} Data001File;

// Stubs
extern void ShutdownSystems_80010228(void);
extern void CloseEvents_80010328(void);
extern enum GameStates ExecOverlay_80040DDC(enum OverlayIds overlayId);

// Matches
extern void InitImage_80010428(void);
extern void SetDisplayMode_80040658(int mode);
extern void InitEvents_8001028C(void);
extern long vsyncEventHandler_800103AC(void);

struct Pool;
extern UnitStatus* GetUnitStatus_80014390(int arg0);
extern EventEntry* FindModelTask_8001091C();
struct Pool;
extern int DsControlB(unsigned char com, unsigned char* param, unsigned char* result);
extern void AddStatus_80012794(UnitStatus* status, int bits);
extern void SeVibOn(void);
extern void SetVib(void);
extern void SsUtVibrateOn(void);
extern void SsUtVibrateOff(void);

extern unsigned int GetEquippedId_800AD990(int a0);
extern void StopAllEventEntries_80043B40(EventNode* p);

extern void SetHitVariantForCommand_800BFAF8(int a0);


extern Minion* GetSlotMinion_800A11D8(int a0);
extern int GetInventorySlotId_800AD288(int a0, int a1);
extern int GetInventorySlotCount_800AD2C8(int a0, int a1);
extern void GetPortraitSprt_800A61CC(int a0, void* a1, void* a2);

extern int* sub_800B3260(int a0);


extern int GetEnemyAliveMask_800A248C(void);
extern UnitStats* GetEnemyStats_800A2B20(int idx);


extern void ClearScriptActorBusy_800A5BCC(int a0);

extern void SetPointLight_800C4090(int pos, int rgb, int range, int intensity);
extern void ClearPointLight_800C410C(void);

extern EventEntry* AllocEventEntry_80043AF8(EventNode* n);

extern void KillUnit_800127B8(UnitStatus* status);
extern UnitStatus* GetEnemyStatus_800A2B60(int idx);
extern UnitStatus* GetSlotStatus_800A10C0(int a0);
extern UnitStats* GetUnitStats_8001449C(int unit);
extern int SpawnModelAnim_800C32DC(int* pos, int modelId, int clip, int rotY);


#endif

