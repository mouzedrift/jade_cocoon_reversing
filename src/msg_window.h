#ifndef _TU_80034068_H_
#define _TU_80034068_H_

#include "globals.h"
#include "msgwin.h"

extern const char aItSEmpty_8007474C[];
extern const char aItSLocked_80074764[];
extern const char aNeeded_80074780[];
extern const char aGiven_80074794[];
extern const char aHandedOver_800747A4[];
extern const char aUsed_800747C0[];
extern const char aReturned_800747D0[];
extern const char aReceived_800747E8[];
extern const char aPickedUp_80074800[];

void InitPadVibration_800364E4(EventEntry* entry);

// a target check of an item / magic command (CheckMagicUsable_80034068)
typedef struct TargetQuery
{
    short id_0;     // item / magic id (the command's arg_4)
    short actor_2;
    short target_4; // target unit
    short f6;
} TargetQuery;

int CheckUsableStub_80034124(TargetQuery* q);

int CheckMagicUsable_80034068(TargetQuery* q);
short** FindTextResumePage_80034900(short** list);
int NthMaskedIndex_80034B88(int n, unsigned int mask);
int IsCurrentMapListed_80034140(void);
int GetUnitElementMask_8003412C(UnitStatus* unit);
int CountUntilZero_80034B14(int* list);
void DrawMsgWindowBackground_80035898(MsgWindow* win, RECT* rect, int ot);
void DrawMsgWindowBorder_800358CC(MsgWindow* win, RECT* rect, int ot);
int CountMaskedUntilZero_80034B40(int* list, unsigned int mask);
void UpdateMessageWindow_80034BB8(EventEntry* entry, MsgWindow* win);
void UpdateMsgWindowState_80034C18(MsgWindow* w);
void HandleMsgWindowInput_800353A0(MsgWindow* win);
int DrawMsgWindowText_8003580C(MsgWindow* win, RECT* rect);
void DrawMsgWindowTitle_800359F8(MsgWindow* win);
void DrawMsgWindowPortrait_80035900(MsgWindow* win);
void DrawMsgWindowChoices_800355EC(MsgWindow* win, RECT* rect);
void UpdateItemMessageWindow_80035BD8(EventEntry* e, void* buf);
int IsMsgWindowAlive_80034AB8(MsgWindowEntry* entry);
int GetMsgWindowResultIfDone_800349B4(MsgWindowEntry* entry, MsgResult* out);
void CloseMsgWindow_80034A84(MsgWindowEntry* entry);
int ConsumeMsgWindowMark_80034ADC(MsgWindowEntry* entry, int idx);
int IsMsgWindowWaiting_80034A30(MsgWindowEntry* entry);
void EnableMsgWindowAdvance_80034A68(MsgWindowEntry* entry);
MsgWindowEntry* OpenMessageWindow_8003422C(MsgWindowCfg* cfg);
MsgWindowEntry* OpenItemMessageWindow_80035AC8(ItemMsgInit* init);
#endif
