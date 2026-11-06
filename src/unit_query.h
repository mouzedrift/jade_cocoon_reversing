#ifndef _TU_80031A94_H_
#define _TU_80031A94_H_

#include "globals.h"
#include "minion_menu.h"
#include "msg_window.h" // TargetQuery

void AddPolyFT4FlipXY_80032D34(unsigned short* poly, void* ot);
void AddPolyFT4FlipX_80032DFC(short* poly, void* ot);
void AddPolyFT4FlipY_80032E78(unsigned short* poly, void* ot);
void AddPolyFT4Rot90Ccw_80032EF4(unsigned short* poly, void* ot);
void AddPolyFT4Rot90Cw_80032F88(unsigned short* poly, void* ot);

int CheckSkillUsable_80033C98(ListMenuState* menu);
int CheckItemOnTarget_80033DF4(TargetQuery* use);
void DrawPublicTiySprt_80033080(unsigned short* pos, int idx, int otIdx);
void CalcEffectiveStatus_800335D0(UnitStatus* src, UnitStatus* dst);
void PulseColor_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int tick, int period, int half);
void GetElementLevels_80033864(Minion* m, unsigned char* out);
int GetAncestorElementMask_80033848(Minion* m, int idx);
unsigned char* GetAncestorName_80033830(Minion* m, int idx);
unsigned char GetStat_80033528(UnitStatus* status, int idx);
int HasSkill_80033A70(UnitStats* stats, int idx);
void AddPolyFT4Copy_8003301C(void* poly, void* ot);
int GetDominantSpecies_800338B0(Minion* m);
int GetTopSpecies_800338DC(unsigned char* history, unsigned char* ids, int* ratios);
short GetMaxHp_800334CC(UnitStatus* status);
short GetHp_800334D8(UnitStatus* status);
short GetMaxMp_800334E4(UnitStatus* status);
short GetMp_800334F0(UnitStatus* status);
int GetExp_800334FC(int* status);
short GetElementMask_80033508(UnitStatus* status);
short GetMinionId_80033858(Minion* minion);
int GetItemId_80033AB0(UnitStats* stats);
int HasMagic_80033A90(UnitStats* stats, unsigned int idx);
int CalcEquippedStats_80033624(unsigned char* out, UnitStatus* status);
void SetDrTPageAbr_80033048(unsigned short* tpage, int abr);
void SetPolyFT4Abr_80033064(unsigned short* poly, int abr);
UnitStatus* GetLevantStatus_80033ABC(SaveData* save);
char* GetSaveDataField7BC_80033AC4(SaveData* save);
Minion* GetSaveMinion_80033ACC(SaveData* save, int idx);
UnitStats* GetSaveItem_80033AE4(SaveData* save, int idx);
int ReturnZero_80033DEC(void);
void* GetStatsStatus_80033A60(void* stats);
unsigned char* GetStats_80033520(UnitStatus* status);
UnitStatus* GetMinionStatusOf_80033818(Minion* minion);
unsigned char* GetMinionStatBlockOf_80033820(Minion* minion);
unsigned char* GetMinionNameOf_80033828(Minion* minion);
char* NextUnitStatus_80033A68(char* stats);
unsigned char GetByteAt_800334BC(unsigned char* arr, int idx);
int HasStatusFlag_80033548(UnitStatus* status, int mask);
short GetLevel_80033514(UnitStatus* status);
int MenuIndexToSkillSlot_80031BDC(int index);
void AddDrawAreaPrim_8003326C(RECT* bounds, void* ot);
void AddClipDrawAreaPrim_80033308(void* ot);
void AddSprtWithTPage_800331C4(unsigned short* pos, SPRT* sprt, void* tpage, void* ot, unsigned char* col);
void GetPublicTiySprt_80032470(int idx, SPRT* pOut20, DR_TPAGE* pOut8);
int CheckItemUsable_80033AFC(ListMenuState* menu);
int CheckMagicCastable_80033C08(ListMenuState* menu);
int GetSkillTargetFlags_80031B0C(UnitSkill* base, int idx);
int GetEquipmentId_8003356C(UnitStatus* status, unsigned int idx);
int AddScaledPolyFT4_80031BE4(POLY_FT4* poly, unsigned long* ot, short x, short y, int scaleX, int scaleY, short* offset, int anchorFlags);
void DrawRotatedPublicSprite_80031FF4(int idx, unsigned long* ot, unsigned short* pos, int angle);
void ApplyEquipmentModifiers_80033754(unsigned char* dst, UnitStatus* src);
#endif
