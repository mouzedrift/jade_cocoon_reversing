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

extern void FirFilterInit_8001450C(int* buf, FirFilter* f, int* coefs, int taps);
extern void FirFilterSetup_80014574(FirFilter* p, int* coefs, int taps);
extern void FirFilterStep_80014588(int* buf, FirFilter* f, unsigned int t);

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

#endif
