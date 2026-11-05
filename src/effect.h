#ifndef EFFECT_H
#define EFFECT_H

/* FIR smoothing filter (FirFilterInit_8001450C / FirFilterSetup_80014574 / FirFilterStep_80014588); the history
   buffer (taps_4 ints) is kept by the owner. The sum is formed as an int; the actors read its low half. */
typedef struct FirFilter
{
    int* coefs_0;
    unsigned int taps_4;
    int input_8;
    union
    {
        int sum;
        short low;
    } output_C;
} FirFilter;

extern void FirFilterInit_8001450C(int* history, FirFilter* filter, int* coefs, int taps);
extern void FirFilterSetup_80014574(FirFilter* filter, int* coefs, int taps);
extern void FirFilterStep_80014588(int* history, FirFilter* filter, unsigned int t);

extern const int dword_80072134;

extern int turnFilterCoeffs_800795A0[];
extern SVECTOR zeroSvector_800795D4;
extern int effectColorWhite_800795DC;
extern int effectColorRed_800795E0;
extern int effectColorBlue_800795E4;
extern int effectColorGreen_800795E8;
extern int effectColorYellow_800795EC;

void FreeEffectTask_800148A0();
void InitEffectTask_80014618();

int Rand100_80013E30(void);
void CalcBattleStats_80013EE8(int* out, UnitStatus* status, ActionData* action, int mode);
int BaseSpeedRatio_80014200(unsigned char* stats);
void UpdateEffectTask_80014638(EventEntry* entry, void* buf);
int CountActiveEffectObjects_800147FC(void);
int GetStatGrowth_80013E00(unsigned int idx, int add);
int CalcHitBonus_80014114(int value);
int CalcEvadeBonus_8001413C(int value);
void CalcUnitEquippedStats_80013E80(unsigned char* out, int unit);
void CalcMinionEquippedStats_80013EB4(unsigned char* out, int a1, int a2);
int CriticalRateTransform_80014164(int value);
int LowestSetBit_80014358(unsigned int mask);
int IsEffectTaskIdle_800148D4(void);
Minion* GetUnitMinion_80014444(int unit);
int RollOilBonus_80013DB0(void);
void RequestEffect_800148F4(int id);
void BaseStatRatios_8001419C(unsigned char* stats, short* out);
int BaseMagicRatio_800142B8(unsigned char* stats);
int BaseAttackRatio_80014308(unsigned char* stats);
#endif
