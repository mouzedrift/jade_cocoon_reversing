#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "effect.h"
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
#include "effect_obj.h"
#include "effect.h"
#include "unit_query.h"
#include "model.h"

const char aAssertionFaile_3[] = "Assertion failed: file \"%s\", line %d\n";
const char aEffectC[] = "EFFECT.C";
const int dword_80072134 = 0x80E8E8;
int turnFilterCoeffs_800795A0[12] = {
    0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200,
    0x400, 0x400, 0x400, 0x400,
};
short effectVramOrigin_800795D0[2] = { 0 };
SVECTOR zeroSvector_800795D4 = { 0 };
int effectColorWhite_800795DC = 0xFFD6D6;
int effectColorRed_800795E0 = 0x6B00FF;
int effectColorBlue_800795E4 = 0xFF0015;
int effectColorGreen_800795E8 = 0x94FF00;
int effectColorYellow_800795EC = 0xFFEB;
short effectFileTable_800795F0[140] = {
    0x404, 0, 0x405, 0, 0x402, 0, 0x40A, 0,
    0x40B, 0, 0x401, 0, 0x400, 0, 0x407, 0,
    0x403, 0, 0x408, 0, 0x406, 0, 0x3FD, 0,
    0x3FE, 0, 0x3FF, 0, 0x40E, 0, 0x40D, 0,
    0x409, 0, 0x40C, 0, 0x433, 0, 0x3CA, 0,
    0x40F, 0, 0x411, 0, 0x419, 0, 0x41C, 0,
    0x421, 0, 0x3F8, -30, 0x3E9, 0, 0x3DF, 0,
    0x3E5, -30, 0x41F, 0, 0x41F, 0, 0x41F, 0,
    0x41F, 0, 0x3E1, 0, 0x3EB, 0, 0x428, 0,
    0x429, 0, 0x424, 0, 0x410, 0, 0x412, 0,
    0x41A, 0, 0x41D, 0, 0x3F5, 0, 0x3EF, 0,
    0x3F9, 0, 0x3EA, 0, 0x3E0, 0, 0x3E6, -10,
    0x3F6, 0, 0x3F4, 0, 0x3F3, 0, 0x3DE, 0,
    0x3EC, 0, 0x3E4, -93, 0x3F0, 0, 0x3E2, 0,
    0x3DD, 0, 0x42A, 0, 0x42B, 0, 0x41B, 0,
    0x418, 0, 0x417, 0, 0x3E7, -48, 0x415, 0,
    0x413, 0, 0x414, 0, 0x416, 0, 0x3F1, 0,
    0x3EE, 0, 0x3F2,
};

// Matched
int RollOilBonus_80013DB0(void)
{
    int bonus = rand() % 6;
    if (bonus)
    {
        bonus = 1;
    }
    else
    {
        bonus = 2;
    }
    return bonus;
}
// Matched
int GetStatGrowth_80013E00(unsigned int idx, int add)
{
    int result = 0;
    if (idx < 0x15)
    {
        result = statGrowthTable_80079348[idx] + add;
    }
    return result;
}
// Matched
int Rand100_80013E30(void)
{
    return rand() % 100;
}
// Matched
void CalcUnitEquippedStats_80013E80(unsigned char* out, int unit)
{
    CalcEquippedStats_80033624(out, GetUnitStatus_80014390(unit & 0xFF));
}
// Matched
void CalcMinionEquippedStats_80013EB4(unsigned char* out, int a1, int a2)
{
    CalcEquippedStats_80033624(out, GetMinionStatus_800107A0(a2)); // sic: one argument (GetMinionStatus_800107A0 is unprototyped)
}
int BaseSpeedRatio_80014200(unsigned char* stats);
// Matched
void CalcBattleStats_80013EE8(int* out, UnitStatus* status, unsigned char* action, int mode)
{
    int def;
    int magicDef;
    if (mode == 1)
    {
        out[0] = status->stats_2C.cur_0[0];
        out[2] = status->stats_2C.cur_0[2];
        out[4] = CalcHitBonus_80014114(10) + action[5];
        out[6] = CriticalRateTransform_80014164((unsigned char)(status->stats_2C.base_6[5] / 10));
        out[8] = 0;
        def = status->stats_2C.cur_0[1] * (status->stats_2C.cur_0[1] - 20) / 7;
        magicDef = status->stats_2C.cur_0[3] * (status->stats_2C.cur_0[3] - 20) / 7;
        out[1] = (def < 0) ? 0 : ((def < 0x7FFF) ? def : 0x7FFF);
        out[3] = (magicDef < 0) ? 0 : ((magicDef < 0x7FFF) ? magicDef : 0x7FFF);
        out[5] = CalcEvadeBonus_8001413C(10);
        out[7] = 0;
        out[9] = 100;
    }
    else
    {
        out[0] = status->stats_2C.cur_0[0];
        out[2] = status->stats_2C.cur_0[2];
        out[4] = CalcHitBonus_80014114(BaseSpeedRatio_80014200(status->stats_2C.cur_0) / 10) + action[5];
        out[6] = CriticalRateTransform_80014164((unsigned char)(status->stats_2C.base_6[5] / 10));
        out[8] = 0;
        out[1] = status->stats_2C.cur_0[1];
        out[3] = status->stats_2C.cur_0[3];
        out[5] = CalcEvadeBonus_8001413C(BaseSpeedRatio_80014200(status->stats_2C.cur_0) / 10);
        out[7] = 0;
        out[9] = BaseSpeedRatio_80014200(status->stats_2C.cur_0);

    }
}
// Matched
int CalcHitBonus_80014114(int value)
{
    return (value * value) / 10;
}
// Matched
int CalcEvadeBonus_8001413C(int value)
{
    return (value * value) / 5;
}
// Matched
int CriticalRateTransform_80014164(int value)
{
    return (value * value * value) / 400;
}
// Matched
void BaseStatRatios_8001419C(unsigned char* stats, short* out)
{
    int a = (stats[7] + stats[9]) >> 1;
    int speedRatio = stats[10] * 47 / (stats[10] + a);
    int magicRatio = stats[8] * 47 / (stats[8] + stats[6]);
    out[0] = speedRatio;
    out[1] = magicRatio;
}
// Matched
int BaseSpeedRatio_80014200(unsigned char* stats)
{
    int a = (stats[7] + stats[9]) >> 1;
    int ratio = stats[10] * 200 / (stats[10] + a);
    if (ratio > 0)
    {
        if (ratio > 200)
        {
            ratio = 200;
        }
    }
    else
    {
        ratio = 1;
    }
    return ratio;
}
// Matched
int BaseDefenseRatio_8001425C(unsigned char* stats)
{
    int a = (stats[7] + stats[9]) >> 1;
    int ratio = a * 200 / (a + stats[10]);
    if (ratio > 0)
    {
        if (ratio > 200)
        {
            ratio = 200;
        }
    }
    else
    {
        ratio = 1;
    }
    return ratio;
}
// Matched
int BaseMagicRatio_800142B8(unsigned char* stats)
{
    int ratio = stats[8] * 200 / (stats[8] + stats[6]);
    if (ratio > 0)
    {
        if (ratio > 200)
        {
            ratio = 200;
        }
    }
    else
    {
        ratio = 1;
    }
    return ratio;
}
// Matched
int BaseAttackRatio_80014308(unsigned char* stats)
{
    int ratio = stats[6] * 200 / (stats[6] + stats[8]);
    if (ratio > 0)
    {
        if (ratio > 200)
        {
            ratio = 200;
        }
    }
    else
    {
        ratio = 1;
    }
    return ratio;
}
// Matched
int LowestSetBit_80014358(unsigned int mask)
{
    unsigned int i;
    for (i = 0; i < 32; i++)
    {
        if (mask & (1 << i))
        {
            return i;
        }
    }
    return 0;
}
// Matched
UnitStatus* GetUnitStatus_80014390(unit)
    unsigned char unit;
{
    UnitStatus* status = 0;
    unsigned char idx;
    if (unit >= 8)
    {
        idx = unit - 8;
        status = GetSlotStatus_800A10C0(idx);
    }
    else if (unit >= 4)
    {
        int flags = GetEnemyAliveMask_800A248C();
        int m = 1 << unit;
        if (flags & m)
        {
            idx = unit - 4;
            status = GetEnemyStatus_800A2B60(idx);
        }
    }
    else if (unit != 0)
    {
        idx = unit - 1;
        status = GetMinionStatus_800107A0(3, idx);
    }
    else
    {
        status = &levantStatus_8008BD38; // == saveData_8008B570.levantStatus_7C8
    }
    return status;
}
// Matched
Minion* GetUnitMinion_80014444(int unit)
{
    unsigned int idx = unit & 0xFF;
    Minion* minion = 0;
    if (idx >= 8)
    {
        idx = unit - 8;
        minion = GetSlotMinion_800A11D8(idx & 0xFF);
    }
    else if (idx != 0)
    {
        idx = unit - 1;
        minion = GetMinion_80010598(3, idx & 0xFF);
    }
    return minion;
}
// Matched
UnitStats* GetUnitStats_8001449C(unit)
    unsigned char unit;
{
    UnitStats* stats = 0;
    if (unit >= 4 && unit < 7)
    {
        int flags = GetEnemyAliveMask_800A248C();
        int m = 1 << unit;
        if (flags & m)
        {
            unit -= 4;
            stats = GetEnemyStats_800A2B20(unit);
        }
    }
    return stats;
}

// Matched
void FirFilterInit_8001450C(int* history, FirFilter* filter, int* coefs, int taps)
{
    unsigned int i;
    FirFilterSetup_80014574(filter, coefs, taps);
    for (i = 0; i < filter->taps_4; i++)
    {
        history[i] = 0;
    }
}
// Matched
void FirFilterSetup_80014574(FirFilter* filter, int* coefs, int taps)
{
    filter->coefs_0 = coefs;
    filter->taps_4 = taps;
    filter->input_8 = 0;
    filter->output_C.sum = 0;
}
// Matched
void FirFilterStep_80014588(int* history, FirFilter* filter, unsigned int t)
{
    unsigned int i;
    history[t % filter->taps_4] = filter->input_8;
    filter->output_C.sum = 0;
    for (i = 0; i < filter->taps_4; i++)
    {
        filter->output_C.sum += history[(t - i) % filter->taps_4] * filter->coefs_0[i];
    }
    filter->output_C.sum >>= 12;
}
void UpdateEffectTask_80014638(EventEntry* entry, void* buf);
// Matched
void InitEffectTask_80014618(EventEntry* entry, EffectTaskState* state)
{
    state->flags_28 = 2;
    state->timer_3C = 0;
    state->state_2C = 0;
    entry->cb_8 = (EventEntryFn)UpdateEffectTask_80014638;
}
extern short effectVramOrigin_800795D0[];
extern short effectFileTable_800795F0[];
int CountActiveEffectObjects_800147FC(void);
// Matched
void UpdateEffectTask_80014638(EventEntry* entry, void* buf)
{
    EffectTaskState* state = (EffectTaskState*)buf;
    int loaded;
    void* vlc;
    void* img;
    if (state->timer_3C > 0)
    {
        state->timer_3C--;
    }
    switch ((unsigned int)state->state_2C)
    {
    case 0:
        if (state->flags_28 & 4)
        {
            state->flags_28 &= ~2;
            state->flags_28 &= ~4;
            if (state->idx_38 >= 0x46)
            {
                state->idx_38 = 0x12;
            }
            LoadEffectFile_80020DDC(effectFileTable_800795F0[state->idx_38 * 2], &effectFile_80091BD0, effectVramOrigin_800795D0, effectVramOrigin_800795D0, 0, 0);
            state->state_2C = 1;
        }
        break;
    case 1:
        loaded = IsEffectFileLoaded_80020EBC(&effectFile_80091BD0);
        if (loaded == 1 && IsFileRequestQueueIdle_8003BF88() == loaded)
        {
            vlc = effectFile_80091BD0.mdec_34.dct_0;
            img = effectFile_80091BD0.mdec_34.work_4;
            state->state_2C = 2;
            mdecEffectVlcBuffer_8008D42C = vlc;
            decodedImageData_8008B4A0 = img;
        }
        break;
    case 2:
        if (state->flags_28 & 1)
        {
            state->flags_28 &= ~1;
            state->state_2C = 3;
        }
        break;
    case 3:
        if (CountActiveEffectObjects_800147FC() == 0 && state->timer_3C == 0 && !(state->flags_28 & 2))
        {
            FreeEffectFile_80020EE0(&effectFile_80091BD0);
            unknownFlags_8008D678 &= ~0x800;
            state->state_2C = 0;
            state->flags_28 |= 2;
        }
        break;
    }
}
// Matched
int CountActiveEffectObjects_800147FC(void)
{
    int i;
    int active;
    EventNode* head;
    EventNode* node;
    int count;
    EventNode* head2;
    EventNode* node2;
    int j;
    i = 0;
    head = effectObjects_8008B4A8;
    active = i;
    count = head->count;
    for (node = head; i < count; i++)
    {
        if ((node->entry.flags & 0x8001) == 1)
        {
            active++;
        }
        node = node->next;
    }
    head2 = miscTasks_8008D60C;
    j = 0;
    count = head2->count;
    for (node2 = head2; j < count; j++)
    {
        if ((node2->entry.flags & 0x8001) == 1)
        {
            active++;
        }
        node2 = node2->next;
    }
    return active;
}
// Matched
void FreeEffectTask_800148A0(void)
{
    FreeEffectFile_80020EE0(&effectFile_80091BD0);
    unknownFlags_8008D678 &= ~0x800;
}
// Matched
int IsEffectTaskIdle_800148D4(void)
{
    return ((EffectTaskState*)effectTask_8008D3F8->entry.buffer)->state_2C == 0;
}
// Matched
void RequestEffect_800148F4(int id)
{
    EffectTaskState* state = effectTask_8008D3F8->entry.buffer;
    state->flags_28 |= 4;
    state->idx_38 = id;
    if (state->state_2C != 0)
    {
        printf(aAssertionFaile_3, aEffectC, 0x124);
        exit(1);
    }
}
