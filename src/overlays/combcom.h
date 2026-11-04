// COMBCOM.BIN: declarations shared by its source files
#ifndef _COMBCOM_H_
#define _COMBCOM_H_

#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "minion_menu.h"
#include "effect_data.h"
#include "common_tu.h"
#include "msg_window.h"
#include "combat.h"

// up to four text lines of a large text box (DrawLargeTextBox_8002AF10)
typedef struct CombComDlg
{
    const char* line0_0;
    const char* line1_4;
    const char* line2_8;
    const char* line3_C;
} CombComDlg;

// a menu entry / window (0x38 bytes)
typedef struct CombComItem
{
    unsigned short flags;
    short type_2;
    void* text_4; // string, or sprite index for type 1
    int sprts_8;
    int tpages_C;
    short x_10;
    short y_12;
    int rest[9];
} CombComItem;

// a window list drawn by DrawMenuWindows_8002A5A4 (CombSelMenu)
typedef struct CombComMenu
{
    int flags_0;
    unsigned int time_4;
    unsigned int anim_8; // open animation step, 8: open
    int sel_C;
    CombComItem** items_10;
    int ot_14;
} CombComMenu;

// a top command's description and the message shown when it cannot be chosen (0: it can)
typedef struct CombComMsg
{
    const char** desc_0;
    const char** error_4;
} CombComMsg;

// a button help bar entry (DrawButtonHelpBar_8002B004), icon -1 ends the list
typedef struct CombComHelp
{
    int icon_0;
    const char* text_4;
} CombComHelp;

typedef struct CombComMsgs3
{
    const char* m[3];
} CombComMsgs3;

typedef struct CombComPos2
{
    short xy[2][2];
} CombComPos2;

// the window colour DrawWindow_80042460 takes (CombSelBox)
typedef struct CombComColor
{
    unsigned short color;
    unsigned char state_2;
    unsigned char frame_3;
} CombComColor;

extern int dword_800C9E88;

/* .data */
extern short cmdCursor_800CD28C[4];
extern short cmdCursorSel_800CD294;
extern short skillCursor_800CD298[6];
extern short magicCursor_800CD2A4[2];
extern short magicCursorCount_800CD2A8;
extern short magicCursorFlags_800CD2AA;
extern short magicCursorSel_800CD2AC;
extern short magicCursorScroll_800CD2AE;
extern short targetCursor_800CD2B0[6];
extern short changeCursor_800CD2BC[6];
extern char pauseCursor_800CD2C8[8];
extern short pauseCursorSel_800CD2D0;
extern short* stateCursors_800CD2D4[6];
extern CombComItem cmdItemAttack_800CD2EC[1];
extern CombComItem cmdItemDefend_800CD324[1];
extern CombComItem cmdItemSpecial_800CD35C[1];
extern CombComItem cmdItemMagic_800CD394[1];
extern CombComItem cmdItemChange_800CD3CC;
extern CombComItem* cmdItems_800CD404[6];
extern CombComMenu cmdMenuWin_800CD41C;
extern short cmdItemX_800CD434[6];
extern const char* descAttack_800CD440[1];
extern const char* descDefend_800CD444[1];
extern const char* descSpecial_800CD448[1];
extern const char* descMagic_800CD44C[1];
extern const char* descChange_800CD450[1];
extern const char* errCannotSummon_800CD454[1];
extern const char* errNotEnoughMana_800CD458[1];
extern const char* errBlank_800CD45C[1];
extern const char* errNoNeedToUse_800CD460[1];
extern const char* errCannotSelect_800CD464[1];
extern const char* errNoDivineMinions_800CD468[1];
extern CombComMsg cmdInfo_800CD46C[5];
extern unsigned char cmdTargetFlags_800CD494[8];
extern unsigned char cmdNextState_800CD49C[8];
extern CombComHelp helpBarCmd_800CD4A4[4];
extern CombComHelp helpBarList_800CD4C4[5];
extern CombComHelp helpBarTarget_800CD4EC[4];
extern CombComHelp* stateHelpBars_800CD50C[6];
extern int cmdKinds_800CD524[5];
extern CombComDlg magicDescs_800CD538[30];
extern CombComDlg skillDescs_800CD718[16];
extern void (*inputHandlers_800CD818[2])(EventEntry*, void*);
extern unsigned short stateDrawFlags_800CD820[6][2];
extern unsigned char msgShown_800CD838;
extern unsigned char side_800CD839;
extern unsigned char menuState_800CD83A;
extern unsigned char msgTimer_800CD83B;
extern int targetSlot_800CD83C;
extern unsigned char targetSlotLo_800CD83C; // low byte of targetSlot_800CD83C (SetFocusedMinion_800CBAD4 reads it with lbu)
extern BattleCmd* cmd_800CD840;
extern unsigned char targetFlags_800CD844;
extern unsigned char byte_800CD845;
extern int padIndex_800CD848;
extern const char* errorMsg_800CD84C;
extern unsigned char prevState_800CD850;
extern short* activeCursor_800CD854;

/* .rdata */
extern const CombComItem pauseTitleItem_800CB4F0;
extern const CombComItem pauseItemStart_800CB528;
extern const CombComItem pauseItemGiveUp_800CB560;
extern const CombComItem pauseItemReturn_800CB598;
extern const CombComMenu menuWinTmpl_800CB5D0;
extern const char aStartFight_800CB5E8[];
extern const char aGiveUpResultsIn_800CB600[];
extern const char aReturnToStartOf_800CB638[];
extern const CombComMsgs3 pauseOptionDescs_800CB674;
extern const CombComPos2 skillListPos_800CB680;
extern const CombComPos2 magicListPos_800CB688;
extern const CombComItem targetItem0_800CB690;
extern const CombComItem targetItem1_800CB6C8;
extern const CombComItem targetItem2_800CB700;

EventEntry* CombComStart_800CB7AC(int cmd, int side);
void SetupCmdMenu_800CB88C(void);
void DisableChangeIfAlone_800CB924(void);
short* GetStateCursor_800CB974(int state);
void UpdateCmdMenuWin_800CBA20(int state);
void SetFocusedMinion_800CBAD4(int state);
void DrawCmdMessage_800CBB4C(const char* text);
void DrawLargeMessage_800CBBE0(const char* text);
int GetSelectedSkill_800CBC28(void);
int GetSelectedMagic_800CBC58(void);
void DrawPauseMenu_800CBCA0(void);
void DrawCmdMenu_800CBEA4(void);
void PreviewCmdEffect_800CC40C(void);
int DrawTargetList_800CC674(short* target, int mode, int sel, int ot);
void FinishCmd_800CC9FC(void);
int CheckCmdSelectable_800CCA94(void);
int GetDefaultTargets_800CCD84(void);
void AdvanceCmdMenu_800CCDD0(void);
void CmdMenuInput_800CCFCC(EventEntry* e);
void CmdMenuMessage_800CD0C8(void);
void CmdMenuTask_800CD16C(EventEntry* e, void* buf);

/* COMBBTL-side (COMBBTL.BIN is loaded together with COMBCOM.BIN; combbtl.h's prototypes clash with these types) */
extern short previewHp_800A82D0;
extern short previewMp_800A82D2;
extern unsigned char exchangeFlags_800A84A8;
extern unsigned char swapSlot_800A85BC;
extern unsigned char actorSlot_800A85BD;

/* exe-side, to move to <exe header> */
extern EventNode* cmdMenuTask_8008D614;          // -> main.h (declared int there)
extern unsigned short padPressed_8009194C[];     // -> main.h
extern unsigned short uiColor_8008B590;          // -> globals.h
extern void* memset(void* p, int c, unsigned int n);
extern int GetMenuCursorIndex_8003DA54(void* cursor);        // -> pad_text.h (MenuCursor*)
extern int UpdateMenuCursor_8003D794(void* cursor, int pad); // -> pad_text.h: defined (MenuCursor*) but a1 (pad) passes through to MenuCursorInput_8003D830
extern int MeasureTextWidth_8003E4C8(const char* str);       // -> pad_text.h
extern int CountMagicBits_8001AE54(int bits);                // -> engine.h (unsigned int* bits)
extern int FindNthMagicBit_8001AEC0(int bits, int n);        // -> engine.h (unsigned int* bits)
extern int GetMagicTargetFlags_8001ACE4(int idx);            // -> engine.h
extern void DrawMenuItemWithWindow_8002ADB4(void* item, void* col, int ot, int time); // -> menu_window.h
extern void DrawMenuWindows_8002A5A4(void* list);            // -> menu_draw.h
extern void DrawButtonHelpBar_8002B004(void* entries, void* origin, int ot); // -> menu_window.h
extern int DrawAbilityDescription_8002C670();                // -> tiy.h (ui_sprites.c): (char* minion, int pos, int texts, short slot, short ot)
extern void DrawAbilityList_8002CE28(ListMenuState* menu, void* origin); // -> ability_menu
extern void DrawMagicList_8002CAC8(ListMenuState* menu, void* origin);   // -> tiy.h (ui_sprites.c)
extern int GetSkillMpCost_80031A04(void* skills, int slot);  // -> skills.h
extern int GetSkillTargetFlags_80031B0C(int skills, int idx); // -> unit_query.h
extern int CheckSkillUsable_80033C98(ListMenuState* menu);   // -> unit_query.h
extern int CheckMagicCastable_80033C08(ListMenuState* menu); // -> unit_query.h

#endif
