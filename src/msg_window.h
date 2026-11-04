#ifndef _TU_80034068_H_
#define _TU_80034068_H_

extern const char aItSEmpty_8007474C[];
extern const char aItSLocked_80074764[];
extern const char aNeeded_80074780[];
extern const char aGiven_80074794[];
extern const char aHandedOver_800747A4[];
extern const char aUsed_800747C0[];
extern const char aReturned_800747D0[];
extern const char aReceived_800747E8[];
extern const char aPickedUp_80074800[];

void InitPadVibration_800364E4();

// a target check of an item / magic command (CheckMagicUsable_80034068)
typedef struct TargetQuery
{
    short id_0;     // item / magic id (the command's arg_4)
    short actor_2;
    short target_4; // target unit
    short f6;
} TargetQuery;

int CheckMagicUsable_80034068(TargetQuery* q);
int CheckUsableStub_80034124(TargetQuery* q);

#endif
