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
extern void sub_8004D924(void);
extern void ShutdownSystems_80010228(void);
extern void CloseEvents_80010328(void);
extern enum GameStates ExecOverlay_80040DDC(enum OverlayIds overlayId);
extern void InitGameDefaults_80040718(void);
extern void LoadPublicTiyAndFtg_800407D0(void);
extern void ShowCopyright_80040A84(void);
extern void PlayGenkiMovie_80040AEC(void);
extern void PlayCraveEntertainmentMovie_80040B54(void);

// Matches
extern int LoadData001File_8003CD1C(void);
extern void InitImage_80010428(void);
extern void DATA_GetFile_8003C7CC(Data001File* pOutFile, enum FileIds idx);
extern int ReadFileIntoBuffer_8003CC54(DslLOC* fileLoc, int sectors, unsigned long* pFileBuffer);
extern void LoadFileIntoBuffer_8003CB7C(DslLOC* fileLoc, unsigned long* pFileBuffer, int sectors);
extern void* DATA_GetFileBuffer_8003CAA0(int idx);
extern void SetDisplayMode_80040658(int mode);
extern void InitEvents_8001028C(void);
extern long vsyncEventHandler_800103AC(void);
extern void SetCurrentArea_800272BC(int a0, int a1);
extern void SetReverbDepthLeft_8002A2E8(SpuReverbAttr* p, short depth);
extern void SetReverbDepthRight_8002A2FC(SpuReverbAttr* p, short depth);
extern int IsSkillLearned_80031954(void* skills, int idx);
extern void SetCameraTarget_80037AC8(int target);
extern int InitMinionData_8001900C(UnitStats* m, int* params); // returns the rank (GetRankForLevel_80019A80)
extern void CopyName_80019AF4(unsigned int* dst, unsigned int* src);
extern void FreeFtgObjectData_80021804(struct FtgObject* p, int heap);
extern void SetReverbMode_8002A280(SpuReverbAttr* p, short mode);
extern void GetMenuItemColor_8002ACE8(int flags, unsigned char* out);

extern int CountMinions_80010548(int id);
extern Minion* GetMinion_80010598(int id, int nth);
extern void ClearMinionsAndItems_80010600(void);
extern int AddItem_80010650(UnitStats* pItem);
extern int CountItems_800106B8(void);
extern unsigned char* GetMinionName_800106F8(int id, int nth);
extern unsigned char* GetMinionAncestorName_80010724(int id, int nth, int idx);
extern unsigned char GetMinionAncestorElement_80010768(int id, int nth, int idx);
extern UnitStatus* GetMinionStatus_800107A0(); // (int id, int nth); unprototyped: CalcMinionEquippedStats_80013EB4 calls it with one argument
extern unsigned char* GetMinionStatBlock_800107CC(int id, int nth);
extern UnitSkills* GetMinionSkills_800107F8(int id, int nth);
extern unsigned int* GetMinionMagicBits_80010824(int id, int nth);
extern void ModelTaskUpdateCb_80010A90(int arg0, int* arg1);
extern void ModelTaskFreeCb_80010AB4(int arg0, int* arg1);
extern int GetUnitRank_80019AD0(UnitStats* unit);
extern void RelocFtgPolyFT3_80023B24(struct FtgSrcPolyFT3* p, int reloc);
extern void RelocFtgPolyGT3_80023E80(struct FtgSrcPolyGT3* p, int reloc);
extern void RelocFtgPolyFT4_8002467C(struct FtgSrcPolyFT4* p, int reloc);
extern void RelocFtgPolyGT4_80024AB8(struct FtgSrcPolyGT4* p, int reloc);
extern void RelocFtgTexSprites_80023460(struct FtgSrcSprites9* p, int reloc);
extern void FreeFtgMatList_80021E24(volatile struct FtgMatList* p, int h);
extern void StopAllPadVibration_80036678(void);
extern void MoveBattleCameraDefault_800378CC(void);
extern int FreeModelTask_8001098C(int arg0);
extern int GetRankForLevel_80019A80(int level);
extern void RelocateTPageClut_80022AE8(unsigned short* tpage, unsigned short* clut, short* reloc);
struct Pool;
extern void MoveBattleCamera_800390F4(struct CameraCtrl* cam, int mode);
extern int GetFtgObjectCount_80021738(int* p);
extern int GetFtgMatCount_80021DE4(int* p);
extern int GetModelAnimCount_80026724(int* p);
extern int GetRecordTableCount_80026D6C(int* p);
extern int CdReadIsIdle_8003C9EC(void);
extern int GetSealResultFlags_80013358(int idx);
extern int GetCameraMode_800378F8(void);
extern short GetCameraBlend_80037A4C(void);
extern UnitStatus* GetUnitStatus_80014390(int arg0);
extern int StepModelTask_80010AD8(struct ModelTaskState* p);
extern EventEntry* FindModelTask_8001091C();
extern void PlayGenkiMovie_80040AC4(void);
extern void PlayCraveMovie_80040B2C(void);
extern struct ModelDesc* GetModelDesc_800251E4(int idx);
extern int DATA_GetFileSize_8003C87C(int idx);
extern void FreeFtgObject_800229B0(struct FtgObject* p, int heap);
extern int CountModelVramSlots_80026600(struct ModelVramSlot* p);
extern void FreeMapArea_8002728C(void);
extern int RunModelTask_80010A10(int key);
struct Pool;
extern void CdReadReadyCallback_8003CA30(unsigned char mode);
extern char* GetModelHeaderRecord_80024FA8(Model* model, int n);
extern void MapLoaderTask_80027CF8(void* a0, int* state);
extern void AreaLoaderTask_800283C0(void* a0, int* state);
extern void DrawNextPrompt_8003CF88(short a0, short a1, int idx);
extern int DsControlB(unsigned char com, unsigned char* param, unsigned char* result);
extern void AllocFtgMatList_80021DF0(struct FtgMatList* p, int count, int heap);
extern void AllocFtgObjects_80021744(struct FtgObject** p, int idx, int heap);
extern void FreeFtgObjects_80021784(struct FtgObject** a0, unsigned int n, int heap);
extern void LoadFtgObjects_80021824(int* file, struct FtgObject* out, int count, int heap, int reloc);
extern void SetMenuItemDigitColor_8002AD80(int flags);
extern void CdReadSyncCallback_8003C9FC(unsigned char mode);
extern void InitMapLoaderTask_80027CC0(EventEntry* p, int* q);
extern void InitAreaLoaderTask_80028388(EventEntry* p, int* q);
extern void AddStatus_80012794(UnitStatus* status, int bits);
extern void SetTargetHitFlag_800184A0(int arg, int bit);
extern void GetModelFtg_800251A0(void* dst, Model* src, int a2, int idx);
extern void GetModelAltFtg_80025B20(void* dst, Model* src, int idx);
extern void SetMenuItemFont1Clut_8002AD08(int flags);
extern void SetMenuItemFont2Clut_8002AD44(int flags);
extern void UpdatePadVibration_80036820(int port);
extern void FreeModelList_80024BB0(ModelList** list);
extern void InitModelList_80024ADC(ModelList** out, struct ModelVramSlot* vram, int heap);
extern int LoadModel_80025200(ModelList* list, int id, int sel, int animMode, int flag);
extern int LoadModelAnim_80025440(Model* p, int idx, int flag);
extern void FreeModelAnim_8002556C(Model* p, int idx);
extern int IsModelAnimLoaded_800255D8(Model* p, int idx);
extern int LoadModelAnimSet_80025780(Model* p, int idx, int flag);
extern void FreeModelAnimSet_80025884(Model* p);
extern int LoadModelAltFtgs_80025974(Model* p, int idx, int flag);
extern void FreeModelAltFtgs_80025AB0(Model* p);
extern void SetModelFtg_80025B5C(Model* p, int idx, int sel);
extern void SaveModelFtgs_80024FFC(Model* p, int* ids);
extern void GetSavedModelFtg_8002512C(unsigned int* out, Model* model, int id);
extern void AllocModelAnims_80026730(struct ModelAnim** out, int count, int heap);
extern Model* GetModelTaskModel_80010A44(int key);
extern void ShowCopyright_80040A84(void);
extern void PlayGenkiMovie_80040AEC(void);
extern void PlayCraveEntertainmentMovie_80040B54(void);
extern void EmptyCallback_800251DC(void);
extern void FreeCameraTask_800376A0(EventEntry* entry, void* buffer);
extern void SeVibOn(void);
extern void SetVib(void);
extern void SsUtVibrateOn(void);
extern void SsUtVibrateOff(void);
extern void* Data001Reader_LoadIntoGlobal_8003CB40(int idx);
extern void LoadModelAnimData_80026A8C(struct ModelAnim* anim, int src, int heap);
extern void RestoreCameraState_80039698(struct CameraCtrl* cam);
extern void DrawTextBox_8002AFA0(int text, int pos, int ot, RECT* rect, int count);
extern void InitModelLoadParams_80025ED0(struct ModelLoadParams* p);
extern void LoadSingleModelAnim_800263CC(struct ModelLoadParams* p);
extern void RequestAreaReload_80027314(void);
extern int RequestAreaPreload_80027330(short a0);
extern void EndBattleCamera_80037770(void);
extern int CdSeekIsComplete_8003C900(void);
extern void CountdownTask_80016BF4(EventEntry* entry, struct EffectObj* obj);
extern void SetReverbDepth_8002A2A0(SpuReverbAttr* p, short left, short right);
extern void DrawLargeTextBox_8002AF10(int text, int pos, int ot);
extern void DrawSmallTextBox_8002AF58(int text, int pos, int ot);
extern int IsTargetListed_8002D738(int idx, int self, int mode);

extern unsigned int GetEquippedId_800AD990(int a0);
extern void StopAllEventEntries_80043B40(EventNode* p);

extern void SetHitVariantForCommand_800BFAF8(int a0);
extern void StartEffect_8001497C(void);


extern Minion* GetSlotMinion_800A11D8(int a0);
extern int GetInventorySlotId_800AD288(int a0, int a1);
extern int GetInventorySlotCount_800AD2C8(int a0, int a1);
extern void GetPortraitSprt_800A61CC(int a0, void* a1, void* a2);

extern int* sub_800B3260(int a0);


extern int GetEnemyAliveMask_800A248C(void);
extern UnitStats* GetEnemyStats_800A2B20(int idx);

extern void LoadModelAnimsMasked_800268E8(struct ModelAnim* anims, int section, int a2, int a3, int mask);

extern void ClearScriptActorBusy_800A5BCC(int a0);

extern void SetPointLight_800C4090(int pos, int rgb, int range, int intensity);
extern void ClearPointLight_800C410C(void);

extern EventEntry* AllocEventEntry_80043AF8(EventNode* n);
extern void DATA_ReadFileInto_8003CAEC(int idx, unsigned int* pDest);
extern int PlayActorEffect_800184DC(struct ActorEffectReq* req, int slot);

extern void KillUnit_800127B8(UnitStatus* status);
extern UnitStatus* GetEnemyStatus_800A2B60(int idx);
extern UnitStatus* GetSlotStatus_800A10C0(int a0);
extern UnitStats* GetUnitStats_8001449C(int unit);
extern int LoadModelListTextures_800255F0(ModelList* list, int idx, int sel);
extern int LoadAllModelAnims_800256B8(ModelList* list, int id);
extern int SpawnModelAnim_800C32DC(int* pos, int modelId, int clip, int rotY);
extern void CopyFtgObject_800218A8(struct FtgObject* s, struct FtgObject* d, int heap);
extern void DrawFtgObjectAtSlot0_8004D1EC(struct FtgObject* obj, unsigned long* ot, void* pos, void* rot, void* cam, int flags, void* scale);


void StopPadVibrationTask_800367F0(int entry, unsigned char* port);
void StopPadVibration_80036658(int idx);
Model* AcquireModel_80024D70(ModelList* list, unsigned int id);
int IsAnimInModelAnimSet_80025924(Model* model, int id);
int IsMapLoading_800272D0(void);
int AreFileRequestsDone_80024DC4(Model* model);
#endif

extern void UnloadMap_80027118(void);
extern void FreeModelAnimData_800269C4(struct ModelAnim* anims, int a1, int sel, int a3);
extern void LoadRecordTable_80026EF8(RecordTable* p, unsigned short* s, int heap);
extern void CopyFtgPolyF3_80023514(struct FtgPolyF3List* list, struct FtgPolyF3* s, int code, int idx);
extern void CopyFtgPolyG3_800236AC(struct FtgPolyG3List* list, struct FtgSrcPolyG3* s, int code, int idx);
extern void CopyFtgPolyFT3_80023934(struct FtgPolyFT3List* list, struct FtgSrcPolyFT3* s, int code, int idx);
extern void CopyFtgPolyGT3_80023BD0(struct FtgPolyGT3List* list, struct FtgSrcPolyGT3* s, int code, int idx);
extern void CopyFtgPolyG4_80024104(struct FtgPolyG4List* list, struct FtgSrcPolyG4* s, int code, int idx);
extern void CopyFtgPolyFT4_8002441C(struct FtgPolyFT4List* list, struct FtgSrcPolyFT4* s, int code, int idx);
extern void CopyFtgPolyF4_80023F34(struct FtgPolyF4List* list, struct FtgPolyF4* s, int code, int idx);
extern void CopyFtgPolyGT4_80024730(struct FtgPolyGT4List* list, struct FtgSrcPolyGT4* s, int code, int idx);
extern void ParseModelFile_80025F14(struct ModelLoadParams* params);
extern void LoadModelHeader_80026014(struct ModelLoadParams* params);
extern void LoadModelTextures_8002607C(struct ModelLoadParams* params);
extern void LoadModelFtg_800260FC(struct ModelLoadParams* params);
extern void LoadModelFtgSwaps_8002659C(struct ModelLoadParams* params);
extern void LoadModelAnims_800261C8(struct ModelLoadParams* params);
extern void LoadSingleModelAnim_800263CC(struct ModelLoadParams* p);
extern void LoadModelAnimSetSection_80026410(struct ModelLoadParams* params);
extern void LoadModelAltFtgSection_8002651C(struct ModelLoadParams* params);
extern void FreeModelAnims_8002679C(struct ModelAnim** anims, int n, int heap);
