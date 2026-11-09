#ifndef _TU_80019BF0_H_
#define _TU_80019BF0_H_

#include "actor.h"
#include "effect_obj.h"
#include "unit.h"

// each species' starting skills: 0xC9 in the exe, the rest from the overlay (sub_800B3274)
extern UnitSkills speciesSkills_8007A9F8[];
extern UnitSkills* sub_800B3274(int idx);
extern UnitSkills* GetSpeciesSkills_80019C28(unsigned int idx);
// each species' name (plain text, EncodeName_8003F7C8 converts it); species from 0xC9 on come from sub_800B32D4
extern const char* minionSpeciesNames_8007A170[];
extern char* sub_800B32D4(int idx);

extern ActionData* GetMagicAction_8001AD64(unsigned int idx); // magic
extern ActionData* GetItemData_8001CDF4(unsigned int idx);
extern ActionData* GetLevantWeaponAction_8001D260(void); // Levant's weapon attack
extern unsigned char* GetAccessoryModifiers_8001CD74(unsigned int idx);
extern unsigned char* GetArmorModifiers_8001CDA0(unsigned int idx);

// per-species model description (speciesModelDescs_8007BD30, GetSpeciesModelDesc_80019C70)
typedef struct
{
    unsigned short modelId_0;
    unsigned char field_2; // angles in units of 2 degrees (BuildMinionModelReq_800C064C)
    unsigned char field_3;
} MinionModelDesc;
extern MinionModelDesc speciesModelDescs_8007BD30[];
extern MinionModelDesc* GetSpeciesModelDesc_80019C70(int idx);
extern Actor* CloneActor_8001D4DC(Actor* src, int kind, int clutRow, int hasMatrices);



// sound cue table soundCues_8007C750 (ModelAnimCue.arg_4 indexes it)
typedef struct
{
    int kind; // 0: sfx, 1: music, 2: sequence, 3: fade out the system sequence
    short arg;
    short pad;
} SoundCue;


// a point light passed to SetModelLighting_80019D84
// (also the camera's light list cameraState_8008D4F0.ent_44 / cameraState_8008D4F0.ent_44)
typedef struct
{
    Vec3i pos_0;
    SVECTOR color_C;   // only vx/vy/vz used
    int range_14;
} PointLight;
extern void SetModelLighting_80019D84(VECTOR* pos, VECTOR* ofs, PointLight* light, MATRIX* m);

// screen fade task state (the fadeTask_8008D628 task buffer, run by SceneFadeTask_8001A41C)
typedef struct SceneFade
{
    unsigned short flags; // 0x10: flash, 1: fade in, 2: fade out, 4: darken, 8: brighten, 0x20: front OT
    short count;
    short pad_4;
    unsigned short duration;
} SceneFade;

extern const char emptyName_80073048[4];
extern const char aDevaMalti_8007304C[];
extern const char aDevaUlvi_80073064[];
extern const char aDevaVali_80073078[];
extern const char aDevaAgni_8007308C[];
extern const char aAdMumuls_800730A0[];
extern const char aAdRoqua_800730B4[];
extern const char aAdSlahm_800730C8[];
extern const char aAdVenon_800730DC[];
extern const char aSelSelahm_800730F0[];
extern const char aSelahm_80073108[];
extern const char aMedinia_80073118[];
extern const char aMedina_80073128[];
extern const char aSelahmVenon_80073138[];
extern const char aMaltia_80073154[];
extern const char aMaltis_80073164[];
extern const char aMalti_80073174[];
extern const char aUlvia_80073180[];
extern const char aUlvis_8007318C[];
extern const char aUlvi_80073198[];
extern const char aVahlia_800731A4[];
extern const char aVahlis_800731B4[];
extern const char aVahli_800731C4[];
extern const char aAgnia_800731D0[];
extern const char aAgnis_800731DC[];
extern const char emptyName_800731E8[4];
extern const char aAgni_800731EC[];
extern unsigned int* const overlayAddr1_800731F8; /* where the overlays load (PSX_RAM) */
extern unsigned int* const overlayAddr2_800731FC; /* where the overlays load (PSX_RAM) */
extern unsigned int* const overlayAddr3_80073200; /* where the overlays load (PSX_RAM) */
extern unsigned int* const overlayAddr4_80073204; /* where the overlays load (PSX_RAM) */
extern unsigned int* const overlayAddr5_80073208; /* where the overlays load (PSX_RAM) */
extern unsigned int* const overlayAddr6_8007320C; /* where the overlays load (PSX_RAM) */
extern unsigned int *const mapCodeAddr_80073210;
extern const char emptyName_80073234[4];
extern const char aKlarrgas_80073238[];
extern const char aYolga_8007324C[];
extern const char aTimaios_80073258[];
extern const char aSicanjal_80073268[];
extern const char aKolna_8007327C[];
extern const char aJeechwo_80073288[];
extern const char aTicker_80073298[];
extern const char aPalooja_800732A8[];
extern const char aAttractSpores_800732B8[];
extern const char aSleepSpores_800732D8[];
extern const char aSkeletonKey_800732F4[];
extern const char aMoonlightSilk_80073310[];
extern const char aAngelwingSilk_80073330[];
extern const char aFirstSnowSilk_80073350[];
extern const char aPearlSilk_80073370[];
extern const char aLilySilk_80073388[];
extern const char aThunderSilk_8007339C[];
extern const char aCloudSilk_800733B8[];
extern const char aMaltySSeal2_800733D0[];
extern const char aMaltySSeal1_800733F0[];
extern const char aAgniSSeal2_80073410[];
extern const char aAgniSSeal1_8007342C[];
extern const char aVarySSeal2_80073448[];
extern const char aVarySSeal1_80073464[];
extern const char aUrvySSeal2_80073480[];
extern const char aUrvySSeal1_8007349C[];
extern const char aMaltySBlessing_800734B8[];
extern const char aAgniSBlessing_800734DC[];
extern const char aVarySBlessing_800734FC[];
extern const char aUrvySBlessing_8007351C[];
extern const char aMirrorOfDeva_8007353C[];
extern const char aRingOfDeath_8007355C[];
extern const char aRingOfStoning_80073578[];
extern const char aRingOfSleep_80073598[];
extern const char aRingOfVenom_800735B4[];
extern const char aIkariPowder_800735D0[];
extern const char aValerianPowder_800735EC[];
extern const char aTendaiUyaku_8007360C[];
extern const char aSpecialLiquor_80073628[];
extern const char aExcellentLiquor_80073648[];
extern const char aFineLiquor_8007366C[];
extern const char aShabLiquor_80073684[];
extern const char aIchishiOil_8007369C[];
extern const char aBletillaOil_800736B4[];
extern const char aKukumiraOil_800736D0[];
extern const char aShishiudoOil_800736EC[];
extern const char aChestnutOil_80073708[];
extern const char aGreatWalnut_80073724[];
extern const char aBitterMugwort_80073740[];
extern const char aMetaMugwort_80073760[];
extern const char aMugwort_8007377C[];
extern const char aSecret3_8007378C[];
extern const char aSecret2_800737A0[];
extern const char aSecret1_800737B4[];
extern const char aMerging3_800737C8[];
extern const char aMerging2_800737DC[];
extern const char aMerging1_800737F0[];
extern const char aMagicUsage2_80073804[];
extern const char aMagicUsage1_80073820[];
extern const char aKnowledge5_8007383C[];
extern const char aKnowledge4_80073854[];
extern const char aKnowledge3_8007386C[];
extern const char aKnowledge2_80073884[];
extern const char aKnowledge1_8007389C[];
extern const char aSecretOfKilling_800738B4[];
extern const char aSpiderWarp_800738D8[];
extern const char aDragonflyWarp_800738F0[];
extern const char aBeetleWarp_80073910[];
extern const char aPupaKey_80073928[];
extern const char aLarvaKey_8007393C[];
extern const char aMinionFang_80073950[];
extern const char aKickleberry_80073968[];
extern const char aDivineTablet_80073980[];
extern const char aJewelOfWind_8007399C[];
extern const char aJewelOfFire_800739B8[];
extern const char aJewelOfWater_800739D4[];
extern const char aMahbuSCocoon_800739F4[];
extern const char aMothKey_80073A14[];
extern const char aCaptureAmulet_80073A28[];
extern const char aChampionSBelt_80073A48[];
extern const char aCalabasHerb_80073A68[];
extern const char aOcarina_80073A84[];
extern const char aSpiderKey_80073A94[];
extern const char aCalabasPowder_80073AAC[];
extern const char aDragonflyKey_80073ACC[];
extern const char aBeetleKey_80073AE8[];
extern const char aTearsOfReese_80073B00[];
extern const char aFluteOfCapture_80073B20[];
extern const char aHunterSEarring_80073B44[];
extern const char aIcicle_80073B68[];
extern const char aAutumnMoon_80073B78[];
extern const char aDrainer_80073B90[];
extern const char aReaper_80073BA0[];
extern const char aPalemoon_80073BB0[];
extern const char aCloudcover_80073BC4[];
extern const char aDragoncrest_80073BDC[];
extern const char aSpringBlossom_80073BF4[];
extern const char aTsunami_80073C14[];
extern const char aThunderbolt_80073C24[];
extern const char aBluePhantom_80073C3C[];
extern const char aNightglow_80073C58[];
extern const char aWhistler_80073C6C[];
extern const char aLittleBird_80073C80[];
extern const char aWhiteHorn_80073C98[];
extern const char aLifeStealer_80073CB0[];
extern const char aIronAxe_80073CCC[];
extern const char aIronSword_80073CE0[];
extern const char aSwordOfSpeed_80073CF8[];
extern const char aBronzeSword_80073D18[];
extern const char aAquazor_80073D34[];
extern const char aDagger_80073D44[];
extern const char aKnife_80073D54[];
extern const char aDivineGarb2_80073D60[];
extern const char aDivineGarb1_80073D7C[];
extern const char aForestGarb_80073D98[];
extern const char aNavyBlueGarb_80073DB0[];
extern const char aBloodyGarb_80073DD0[];
extern const char aNagiGarb_80073DE8[];
extern const char aRiketzGarb_80073DFC[];
extern const char aDivineVest_80073E18[];
extern const char aSilverVest_80073E30[];
extern const char aReflectingVest_80073E48[];
extern const char aPlateMailVest_80073E68[];
extern const char aWireVest_80073E88[];
extern const char aChainMailVest_80073E9C[];
extern const char aLeatherVest_80073EBC[];
extern const char aHunterSVest_80073ED8[];
extern const char aNagiBelt_80073EF4[];
extern const char aSuperChoker_80073F08[];
extern const char aStoneChoker_80073F24[];
extern const char aSleepChoker_80073F40[];
extern const char aPoisonChoker_80073F5C[];
extern const char aHawkRuff_80073F78[];
extern const char aHollyRuff_80073F8C[];
extern const char aSilverCrown_80073FA4[];
extern const char aIronBracelet_80073FC0[];
extern const char aSparrowRuff_80073FDC[];
extern const char aRedBead_80073FF8[];
extern const char aYellowBead_8007400C[];
extern const char aGreenBead_80074024[];
extern const char aBlueBead_8007403C[];
extern const char aSilverHeadband_80074050[];
extern const char aIronHeadband_80074070[];
extern const char aLeatherHeadband_8007408C[];

void SetFadeMode_8001C19C(unsigned int mode, int frames);
int CountMagicBits_8001AE54(unsigned int* bits);
int GetMagicEffect_8001AC8C(int idx);
void InitMovie_8001B1B0(void);
void StartDisplay_8001B714(void);
void DrawFrozenFrame_8001B540(void);
void DrawMotionBlur_8001BCE4(int buffer);
void Draw_8001B5EC(void);
void LoadDecodedImage_8001BEC8(void);
void InitPrimBuffers_8001BF90(void);
int FindNearestCameraPoint_80019CC4(int* pos);
void RunAnimFrameCues_8001C440(Model* model, int idx, int frame);
void FreeActors_8001D3C4(int freeModels);
void TriggerActorEffect_8001E28C(Actor* actor);
void StopSceneDarken_8001AAF4(void);
int IsSceneFadeDone_8001AB94(void);
void StartScreenFlash_8001C02C(unsigned char* rgb);
void SetActorTurnTarget_8001DB00(Actor* actor, int* target, int step);
int GetItemTargetFlags_8001CE8C(int idx);
int GetMagicTargetFlags_8001ACE4(int idx);
void DestroyActor_8001D600(Actor* actor);
void InitActors_8001D378(void);
void InitSceneFade_8001A38C(void);
const char* GetEquipmentName_8001D128(int idx, unsigned int kind);
void SetMotionBlur_8001BCD8(int on);
void SetActorAnim_8001D760(Actor* actor, int idx, int mode, int restart);
int TurnActorBy_8001DD44(Actor* actor, int dir, int amount, int maxStep);
int FindActorInFront_8001DECC(Actor* actor, int range, int checkLevant);
void ResetPadHoldFrames_8001CD04(int port);
unsigned short GetItemFlags_8001CE70(int idx);
int GetMagicElement_8001AD30(int idx);
void ClearMagicBit_8001AE00(unsigned int* bits, unsigned int idx);
void PlayAnimFrameSfx_8001C364(Model* model, int idx, int frame);
int SetActorAction_8001E34C(Actor* actor, ActorActionDesc* desc);
int FindNthMagicBit_8001AEC0(unsigned int* bits, int n);
int IsFadeDone_8001C2FC();
void RestartDisplay_8001B230(void);
void ClearOTagRAll_8001B260(void);
void AddPrimsAll_8001B3C8(void);
void RestartActorMotion_8001D71C(Actor* actor);
int IsActorIdle_8001E1C8(Actor* actor);
int IsActorActionReady_8001E1DC(Actor* actor);
void StartFadeToBlack_8001C2CC(void);
void StartFadeToWhite_8001C2E4(void);
int GetArmorOutfit_8001D060(int idx);
void StopActorFade_8001DA2C(Actor* actor);
void UpdateActorScript_8001EA28(void* actor);
unsigned char GetItemEffect_8001CDCC(unsigned int idx);
const char* GetItemName_8001CE20(unsigned int idx);
int* GetWeaponStatBonus_8001CEF4(unsigned int idx);
const char* GetWeaponName_8001CF20(unsigned int idx);
int GetWeaponPrice_8001CF4C(unsigned int idx);
EquipmentData* GetWeaponData_8001CF84(unsigned int idx);
int* GetArmorStatBonus_8001CFB0(unsigned int idx);
const char* GetArmorName_8001CFDC(unsigned int idx);
int GetArmorPrice_8001D008(unsigned int idx);
EquipmentData* GetArmorData_8001D034(unsigned int idx);
int* GetAccessoryStatBonus_8001D078(unsigned int idx);
const char* GetAccessoryName_8001D0A4(unsigned int idx);
int GetAccessoryPrice_8001D0D0(unsigned int idx);
EquipmentData* GetAccessoryData_8001D0FC(unsigned int idx);
void StartActorFadeIn_8001D9E4(Actor* actor, int div, int flags);
void StartActorFadeOut_8001DA08(Actor* actor, int div, int flags);
const char* GetMagicName_8001AC2C(int idx);
int GetMagicIcon_8001AF3C(int idx);
int WaitVSync_8001B6E8();
void InitEnvironments_8001B7B4(void);
int GetItemIcon_8001D2AC(int idx);
const char* GetKeyItemName_8001D318(unsigned int idx);
void FreeActorBones_8001EA00(Actor* actor);
void StartActorScript_8001DC34(void* actor, void* script);
void SetActorScript_8001DB98(Actor* actor, unsigned char* script);
unsigned short GetButtonConfigEntry_8001C818(unsigned short* entry);
int IsActorAnimLoadIdle_8001D8A8(Actor* actor);
signed char GetMinionElement_80019BF0(int idx);
unsigned char GetMinionEnhancementBody_80019C0C(int idx);
const char* GetPersonName_8001CD3C(int idx);
unsigned char* GetPersonMergeInfo_8001CD58(int idx);
int ReturnZero_8001CD34(void);
int GetPersonIcon_8001CD6C(int idx);
int ReturnZero_8001CE4C(void);
int GetItemPrice_8001CE54(int idx);
void SetActorGroundMove_8001D68C(Actor* actor, int on);
void SetActorRootMotion_8001D6BC(Actor* actor, int on);
void SetActorAnimPaused_8001D6EC(Actor* actor, int on);
void SetActorVisible_8001D730(Actor* actor, int on);
int GetMagicMpCost_8001AC58(int idx);
int GetKeyItemIcon_8001D344(int idx);
int IsKnowledgeKeyItem_8001D36C(int id);
void SetActorActive_8001D658(Actor* actor, int on);
Actor* CreateActor_8001D45C(ActorDesc* desc);
void SkipActorAnimToEnd_8001D9B0(Actor* actor);
int StartActorAction_8001E254(Actor* actor, void* desc);
void CancelFade_8001C244(void);
void SetActorSpeedScale_8001DB58(Actor* actor, int scale, int on);
void UpdateActorCb_8001D41C(EventEntry* entry, void* actor);
void ProcessPad_8001C8E8(int port);
void MinionLevelUpHook_8001AEB8(int species, UnitStatus* status, unsigned int* magicBits);
void SetButtonConfigEntry_8001C810(short* entry, unsigned short button);
int ReturnOne_8001CEEC(void);
void ProcessPads_8001BF50(void);
EquipmentData* GetEquipmentData_8001D190(unsigned int idx, unsigned int kind);
int GetEquipmentPrice_8001D1F8(int idx, unsigned int kind);
int GetEquipmentIcon_8001D2D4(int idx, int kind);
void SceneFadeTask_8001A41C(EventEntry* entry, SceneFade* fade);
unsigned int GetButtonConfig_8001C874(int idx);
IdEntry* FindItemById_8001C314(IdEntryList* list, int id);
int PickArpatronOrVatolka_80019C84(void);
void ResetSceneFade_8001A9A4(void);
void SetSceneDark_8001A9E4(void);
void ScreenFlashTask_8001C0B4(EventEntry* entry, int* state);
void FadeToBlackStep_8001BB28(void);
void FadeToWhiteStep_8001BC00(void);
int IsActorNear_8001DFC8(Actor* actor, VECTOR* target, int range, int checkLevant);
int TurnActorTowards_8001DDFC(Actor* actor, VECTOR* target, int step);
int IsInFrontWithinRange_8001E0F4(VECTOR* from, int angle, VECTOR* to, unsigned int range);
void InitActor_8001E574(Actor* actor, ActorDesc* desc);
void EndFade_8001C290(void);
int TestMagicBit_8001AE2C(unsigned int* bits, unsigned int idx);
void BeginFade_8001C260(void);
void FreezeScreen_8001C224(void);
void DrawIntroMovie_8001AF64(void* descs);
void StartSceneFadeIn_8001AA04(int duration);
void StartSceneDarken_8001AAA8(int duration);
void StartSceneFadeOut_8001AA50(int duration);
void StartSceneBrighten_8001AB1C(int duration);
#endif
