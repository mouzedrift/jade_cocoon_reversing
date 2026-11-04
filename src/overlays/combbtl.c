// COMBBTL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "camera.h"

typedef struct CombBtlTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombBtlTask;

typedef struct CombBtlNode
{
    unsigned int flags;
} CombBtlNode;

extern CombBtlNode* dword_800A82DC;

// a battle command (same layout as BATTLE.BIN's BatCmd_a)
typedef struct CombBtlCmd
{
    int kind_0; // 0x14: none
    int arg_4;
    int mask_8; // acting unit bits
    int targets_C; // target unit bits
} CombBtlCmd;

extern short word_800A82E0[4];
extern EventNode* dword_8008B564;
extern int dword_800A85A0;
extern CombBtlCmd dword_800A8600;
extern CombBtlCmd dword_800A85A8;
extern int dword_800A4078[2];
extern unsigned char byte_800A3A98[2];
extern short word_800A84D0[2];
extern void sub_800A0D1C(int);
extern void sub_800A0B70(int);
extern void StartScreenFlash_8001C02C(void*);
extern void sub_800376A0(void* a, void* b);
typedef Minion CombBtlUnit;

typedef struct CombBtlHist
{
    int unit_0;
    CombBtlCmd cmd_4;
} CombBtlHist;

extern CombBtlUnit dword_800A3AA0[2][3];
extern CombBtlHist dword_800A84D8[];
extern EventNode* hitNumberTasks_8008D778;
extern void InitSceneFade_8001A38C();
extern void SceneFadeTask_8001A41C();
extern int sub_800A1958(void*);
extern int* sub_800A10DC(int); // COMBAT: the slot actor pos_38
extern void sub_800A7EFC();
// a side's unit window task (sub_800A75F8, sub_800A7694)
typedef struct CombBtlObj
{
    int a;      // side
    int b;      // frame of the open animation
    RECT dst_8;  // the final window rect
    RECT cur_10; // the window rect being opened (InterpolateWindowRect_8004196C)
} CombBtlObj;

typedef struct CombBtlPair
{
    short lo;
    short hi;
} CombBtlPair;

extern short word_800A82D4[][2];
extern void sub_800A7694();
typedef struct CombBtlA24
{
    int pos_0[2][3]; // per side
} CombBtlA24;

typedef struct CombBtlB16
{
    unsigned char f0[2][8]; // per side
} CombBtlB16;

extern CombBtlA24 dword_800A4AD4;
extern CombBtlB16 dword_800A4AEC;
extern void sub_800A0BA8(int, void*, void*);
// a command's result (same layout as BATTLE.BIN's BatResult_a)
typedef struct CombBtlResult
{
    unsigned short kind_0;
    short arg_2;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    short f24;
    short f26;
} CombBtlResult;

extern CombBtlResult dword_800A85C8;
extern int dword_800A85B8;
extern int dword_800A8620;
extern int xarr_800A85B8[];
extern int xarr_800A8620[];
extern CombBtlCmd dword_800A8610;
extern int dword_800A84C0;
extern int dword_800A84A0;
extern int dword_800A8498;
extern int dword_800A849C;
extern unsigned char byte_800A38DC;
extern int dword_800A84B8;
extern int dword_800A85F8;
extern short word_800A8488;
extern void sub_800A4C40();
extern void sub_800A4D48();
extern void sub_800A68E0();
extern void sub_800A616C();
extern void sub_800A5000();
extern void SetBattleStageId_80039FA4(int);
extern void sub_800A0A28();
extern int PlayMusic_800300E0(int, int);
extern void sub_800A5EF8();
extern void sub_800A5F60();
extern void sub_800A50E4();
extern void sub_800A5544();
extern void sub_800A5BB4();
extern void sub_800A5080();
extern EventEntry* dword_800A848C;
extern int dword_800A84D4;
extern int dword_800A84B0[2];
extern short word_80091CE0[];
extern char dword_80091D40[];
extern short word_800A84A4;
extern short word_800A84A6;
extern short word_800A84BC;
extern short word_800A84C4;
extern short word_800A8470[2];
extern short word_800A8474[2];
extern int dword_800A8480[2];
extern int dword_800A85F0[2];
extern EventEntry* sub_800CB7AC(void*, int);
extern int sub_800A0B3C(int);
extern void StopSeqSlot_80031334(int);
extern void StopSoundSeqs_80030D68(int);
extern void FreeSeqSlotSound_80030664();
extern void SsSepSetDecrescendo(int, int, int, int);
extern void StartSceneFadeOut_8001AA50(int);
extern void PlaySeqSlot_80031160(int, int);

INCLUDE_OVERLAY_ASM(combbtl, dword_800A4088);

void sub_800A4B8C(CombBtlTask* t, int a)
{
    dword_800A85A0 = LoadOverlay_80020BF8(1, 6);
    dword_800A84C0 = (unsigned int)gnFrame_8008D610 % 39;
    t->next_8 = sub_800A4C40;
    t->next_8(t, a);
    StopSoundSeqs_80030D68((int)word_80091CE0);
    PlayMusic_800300E0(0, 1);
}

void sub_800A4C40(CombBtlTask* t, int a)
{
    if (GetFileRequestStatus_8003BE30(dword_800A85A0) == 0)
    {
        dword_800A84A0 = -1;
        dword_800A8498 = -1;
        dword_800A849C = -1;
        byte_800A38DC = 2;
        dword_800A85B8 = -1;
        dword_800A8620 = -1;
        SetBattleStageId_80039FA4(dword_800A84C0);
        sub_800A0A28();
        dword_800A84B8 = 0;
        dword_800A85F8 = -1;
        sub_800A4CFC();
        t->next_8 = sub_800A4D48;
        t->next_8(t, a);
    }
}

void sub_800A4CFC()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        dword_800A4078[i] = -1;
        byte_800A3A98[i] = 0;
        word_800A84D0[i] = 0;
    }
}

extern int LoadSeqSlotSound_800303E8();
extern int IsSoundTaskReady_80030688();
extern int sub_800BC8E8();
extern void sub_800BC878();
extern void SetCameraBattleMode_80037720();
extern void StartBattleCamera_80037748();
extern void SetFadeMode_8001C19C();
extern void LoadUiTiy_8002BF74();
extern int uiTiyLoaded_8008B4E8;
extern int subInt_800378F8();
extern void sub_800A7290();
extern void sub_800A7420();
extern void sub_800A4EC8();

void sub_800A4D48(CombBtlTask* t, int a)
{
    switch (dword_800A84B8)
    {
    case 0:
        if (!LoadSeqSlotSound_800303E8())
        {
            break;
        }
        dword_800A84B8 = 1;
    case 1:
        if (!IsSoundTaskReady_80030688())
        {
            break;
        }
        FreeBgmAndSfx_800315F4();
        dword_800A84B8 = 2;
    case 2:
        if (!PlayMusic_800300E0(0x99, 1))
        {
            break;
        }
        dword_800A84B8 = 3;
    case 3:
        sub_800BC878();
        dword_800A84B8 = 4;
    case 4:
        if (!sub_800BC8E8())
        {
            break;
        }
        dword_800A84B8 = 5;
    case 5:
        sub_800A7290();
        sub_800A7420();
        SetCameraBattleMode_80037720();
        StartBattleCamera_80037748();
        dword_800A84B8 = 9;
        break;
    case 6:
        SetFadeMode_8001C19C(3, 0x20);
        dword_800A84B8 = 7;
    case 7:
        LoadUiTiy_8002BF74();
        dword_800A84B8 = 8;
    case 8:
        if (!uiTiyLoaded_8008B4E8)
        {
            break;
        }
        dword_800A84B8 = 9;
    case 9:
        if (subInt_800378F8() != 4)
        {
            t->next_8 = sub_800A4EC8;
            t->next_8(t, a);
        }
        break;
    }
}
INCLUDE_OVERLAY_ASM(combbtl, dword_800A4A54);

extern void sub_800A5638();

void sub_800A4EC8(CombBtlTask* t, int a)
{
    int ok[2];
    unsigned int i;
    unsigned int j;
    for (i = 0; i < 2; i++)
    {
        ok[i] = 1;
        for (j = 0; j < 3; j++)
        {
            if (sub_800A1934(&dword_800A3AA0[i][j]) == 0 && sub_800A1958(&dword_800A3AA0[i][j]) == 0)
            {
                ok[i] = 0;
                break;
            }
        }
        if (ok[i] == 1)
        {
            dword_800A85F8 = i;
            break;
        }
    }
    if (dword_800A85F8 >= 0)
    {
        t->next_8 = sub_800A5000;
    }
    else
    {
        dword_800A84B8 = 10;
        t->next_8 = sub_800A5638;
    }
    t->next_8(t, a);
}

void sub_800A5000(CombBtlTask* t)
{
    if (word_80091CE0[2] >= 0)
    {
        SsSepSetDecrescendo(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
    }
    StopSeqSlot_80031334(0);
    PlaySeqSlot_80031160(1, 1);
    dword_800A84D4 = 0x78;
    t->next_8 = sub_800A5080;
}

void sub_800A5080(CombBtlTask* t)
{
    if (--dword_800A84D4 <= 0)
    {
        FadeOutSeqSlot_800313C8(0);
        StopSeqSlot_80031334(0);
        StopSoundSeqs_80030D68(dword_80091D40);
        FreeSeqSlotSound_80030664();
        t->next_8 = sub_800A50E4;
    }
}

extern unsigned char byte_800A3A90[];
extern void sub_800A54CC();
extern void sub_800A51EC();
void sub_800A50E4(CombBtlTask* t)
{
    int r = IsEffectTaskIdle_800148D4();
    if (r == 1)
    {
        if (dword_800A85F8 < 0)
        {
            if (byte_800A38DC == r)
            {
                dword_800A85F8 = dword_800A85B8;
                byte_800A3A90[dword_800A85B8]++;
                if (byte_800A3A90[dword_800A85B8] >= 100)
                {
                    byte_800A3A90[dword_800A85B8] = 99;
                }
            }
            else
            {
                t->next_8 = sub_800A54CC;
                return;
            }
        }
        else
        {
            byte_800A38DC = 0;
            byte_800A3A98[dword_800A85F8] = r;
            byte_800A3A90[dword_800A85F8]++;
            if (byte_800A3A90[dword_800A85F8] >= 100)
            {
                byte_800A3A90[dword_800A85F8] = 99;
            }
        }
        t->next_8 = sub_800A51EC;
        dword_800A84D4 = 0x1E;
    }
}

extern void sub_800A8078(short, short, short);
extern int sub_800A8098();
extern void sub_800A5290();
extern void sub_800A54CC();
extern char dword_800A82EC[];
extern char dword_800A8300[];

void sub_800A51EC(CombBtlTask* t)
{
    if (--dword_800A84D4 <= 0)
    {
        if (dword_800A85F8 == 1)
        {
            sub_800A8078(7, 0x3BC, 0x1B);
            dword_800A82DC = sub_800A8098(0, dword_800A82EC, 1);
        }
        else
        {
            sub_800A8078(9, 0x3BF, 0x1F);
            dword_800A82DC = sub_800A8098(0, dword_800A8300, 0);
        }
        t->next_8 = sub_800A5290;
    }
}

// a menu item (DrawMenuItemWithWindow_8002ADB4)
typedef struct CombBtlA28
{
    int f0;
    int x_4;
    int f8;
    int fC;
    short x_10; // the window rect
    short y_12;
    short w_14;
    short h_16;
    int f18;
} CombBtlA28;

typedef struct CombBtlBox
{
    short col_0;
    char c_2;
    char c_3;
} CombBtlBox;

extern CombBtlA28 dword_800A4A54;
extern CombBtlA28 dword_800A4A70;
typedef struct CombBtlUi
{
    char pad_0[0x20];
    unsigned short col_20;
} CombBtlUi;

extern CombBtlUi ui_8008B570;
extern void DrawMenuItemWithWindow_8002ADB4(void*, void*, int, int);

void sub_800A5290(CombBtlTask* t)
{
    CombBtlBox box;
    CombBtlA28 a = dword_800A4A54;
    int pair[2];
    CombBtlA28 b;
    pair[0] = 0x33;
    pair[1] = 0xDF;
    a.x_4 = pair[dword_800A85F8 ^ 1];
    box.c_2 = 1;
    box.c_3 = 1;
    box.col_0 = ui_8008B570.col_20;
    DrawMenuItemWithWindow_8002ADB4(&a, &box, 0xF, GetTime30Hz_8002C64C());
    b = dword_800A4A70;
    box.c_2 = 1;
    box.c_3 = 1;
    box.col_0 = ui_8008B570.col_20;
    DrawMenuItemWithWindow_8002ADB4(&b, &box, 0xF, GetTime30Hz_8002C64C());
    if (dword_800A82DC == 0 || (dword_800A82DC->flags & 0x8001) != 1)
    {
        dword_800A82DC = 0;
        t->next_8 = sub_800A54CC;
    }
}

extern int dword_800A4A8C[];
extern int dword_800A4A94[];
// Matched
int sub_800A5408(int which, int text, int c)
{
    int cfg[18];
    int kinds[2] = {2, 3};
    int* tbl[2] = {dword_800A4A8C, dword_800A4A94};
    cfg[0] = 2;
    cfg[1] = 0;
    cfg[2] = text;
    cfg[4] = (settingsFlags_8008B58C.word & 7) != 3;
    cfg[5] = 0;
    cfg[6] = 0;
    cfg[7] = 0;
    cfg[8] = 7;
    cfg[9] = kinds[which];
    cfg[10] = c;
    cfg[11] = 1;
    cfg[12] = 0;
    cfg[13] = 0;
    cfg[14] = (settingsFlags_8008B58C.word >> 3) & 1;
    cfg[15] = 1;
    cfg[16] = 0;
    cfg[3] = (int)tbl[which];
    return (int)OpenMessageWindow_8003422C(cfg);
}

void sub_800A54CC(CombBtlTask* t)
{
    FadeOutSeqSlot_800313C8(0);
    if (word_80091CE0[2] >= 0)
    {
        SsSepSetDecrescendo(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
    }
    StartSceneFadeOut_8001AA50(0x1E);
    sub_800A7BE4();
    t->next_8 = sub_800A5544;
}

extern int IsSceneFadeDone_8001AB94();
extern void sub_800A73E4();
extern void sub_800A7478();
extern void sub_800A7560();
extern void sub_800A0A6C();
extern void SsUtAllKeyOff();
extern void sub_800A16FC();

void sub_800A5544(CombBtlTask* t)
{
    int i;
    if (IsSceneFadeDone_8001AB94() == 1)
    {
        sub_800A73E4();
        sub_800A7478();
        for (i = 0; i < 2; i++)
        {
            if (dword_800A4078[i] >= 0)
            {
                if (sub_800A1958(&dword_800A3AA0[i][dword_800A4078[i]]) == 0)
                {
                    sub_800A7560(i);
                }
            }
        }
        sub_800A0A6C();
        FreeSeqSlotSound_80030664();
        SsUtAllKeyOff(0);
        PlayMusic_800300E0(0x8E, 1);
        FreeStageEffects_80039FC0();
        t->next_8 = sub_800A16FC;
    }
}

extern void sub_800A58E8(int i);
extern void sub_800A0ACC(int i, void* u);
extern int sub_800A758C();
extern void sub_800A74A0(int i);
extern void sub_800A75F8(int i);
extern void sub_800A0E1C(int i, int v);
extern void sub_800A1068(int i);
extern void sub_800A599C();
extern unsigned char byte_800A85BD;
extern void sub_800A60F0();
void sub_800A5638(CombBtlTask* t, int a)
{
    int i;
    int any;
    switch ((unsigned int)dword_800A84B8)
    {
    case 10:
        any = 0;
        for (i = 0; i < 2; i++)
        {
            dword_800A84B0[i] = 0;
            if (dword_800A4078[i] < 0 || sub_800A1958(&dword_800A3AA0[i][dword_800A4078[i]]))
            {
                sub_800A58E8(i);
                sub_800A0ACC(i, &dword_800A3AA0[i][dword_800A4078[i]]);
                any = dword_800A84B0[i] = 1;
            }
        }
        if (any == 1)
        {
            dword_800A84B8 = 11;
        }
        else
        {
            void (*f)() = sub_800A599C;
            t->next_8 = f;
            f(t, a);
        }
        break;
    case 11:
        if (sub_800A758C() == 1)
        {
            for (i = 0; i < 2; i++)
            {
                if (dword_800A84B0[i] == 1)
                {
                    sub_800A74A0(i);
                    sub_800A75F8(i);
                }
            }
            for (i = 0; i < 2; i++)
            {
                sub_800A0E1C(i, sub_800A10DC(i ^ 1));
                sub_800A1068(i);
            }
            dword_800A84B8 = 12;
        }
        break;
    case 12:
        sub_800A5BB4();
        sub_800A60F0();
        dword_800A85B8 = 0;
        dword_800A8620 = 1;
        word_800A8488 = 0;
        byte_800A85BD = dword_800A4078[0];
        if (dword_800A84B0[0] == 1)
        {
            dword_800A84B0[0] = 0;
            dword_800A85A8.kind_0 = 2;
            dword_800A85A8.arg_4 = 0;
            dword_800A85A8.mask_8 = 0x100;
            dword_800A85A8.targets_C = 0;
        }
        if (dword_800A84B0[1] == 1)
        {
            dword_800A84B0[1] = 0;
            dword_800A8610.kind_0 = 2;
            dword_800A8610.arg_4 = 0;
            dword_800A8610.targets_C = 0;
            dword_800A8610.mask_8 = 1 << (dword_800A8620 + 8);
        }
        t->next_8 = sub_800A68E0;
        break;
    }
}

void sub_800A58E8(int i)
{
    CombBtlUnit* u;
    do
    {
        dword_800A4078[i]++;
        if (dword_800A4078[i] >= 3)
        {
            dword_800A4078[i] = 0;
        }
        u = &dword_800A3AA0[i][dword_800A4078[i]];
    } while (sub_800A1934(u) || sub_800A1958(u));
}

#if 0
// Not matched: the original has a jump to the loop increment right after the i == 1 block (one word longer) plus a t0/a3 swap; tried continue/while/switch forms
extern int sub_800A5B70(int a);
extern void MoveBattleCameraDefault_800378CC();
extern int dword_8008D610;
extern int dword_800A82E8;
extern unsigned char byte_800A85BD;
extern void sub_800A5C64();
void sub_800A599C(CombBtlTask* t, int a)
{
    int gauge[2];
    int i;
    dword_800A85B8 = -1;
    dword_800A8620 = -1;
    if (word_800A84D0[0] == 0 && word_800A84D0[1] == 0)
    {
        *(short*)((char*)word_800A84D0 + (dword_8008D610 & 2)) += 100;
    }
    for (i = 0; i < 2; i++)
    {
        gauge[i] = (short)sub_800A5B70(i);
    }
    while (dword_800A85B8 < 0)
    {
        for (i = 0; i < 2; i++)
        {
            word_800A84D0[i] += gauge[i];
            if (word_800A84D0[i] >= 1000)
            {
                word_800A84D0[i] -= 1000;
                dword_800A85B8 = i;
                dword_800A8620 = i ^ 1;
                if (i == 1)
                {
                    word_800A84D0[1] += gauge[1];
                }
            }
        }
    }
    if (dword_800A85B8 >= 0)
    {
        void (*f)();
        MoveBattleCameraDefault_800378CC();
        dword_800A82E8++;
        byte_800A85BD = dword_800A4078[dword_800A85B8];
        f = sub_800A5C64;
        t->next_8 = f;
        f(t, a);
    }
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A599C);

int sub_800A5B70(int a)
{
    UnitStatus* r;
    int v;
    unsigned char buf[0x18];
    r = GetUnitStatus_80014390((a + 8) & 0xFF);

    if (r)
    {
        CalcEquippedStats_80033624(buf, r);
        v = buf[4] + 0xA;
    }
    else
    {
        v = 0;
    }
    return v;
}

// Near miss: the original loads the two shift counts only after all the stores
#if 0
// Not matched: the original loads the two shift counts after all the stores (alias/scheduling), tried array/struct/pointer forms
void sub_800A5BB4()
{
    dword_800A8600.kind_0 = 0x14;
    dword_800A8600.arg_4 = 0;
    dword_800A85A8.kind_0 = 0x14;
    dword_800A85A8.arg_4 = 0;
    dword_800A8610.kind_0 = 0x14;
    dword_800A8610.arg_4 = 0;
    dword_800A85C8.kind_0 = 0;
    dword_800A85C8.f24 = -1;
    dword_800A85C8.f26 = -1;
    dword_800A85C8.arg_2 = 0;
    dword_800A85C8.f4 = 0;
    dword_800A85C8.f8 = 0;
    dword_800A85C8.fC = 0;
    dword_800A85C8.f10 = 0;
    dword_800A85C8.f14 = 0;
    dword_800A85C8.f18 = 0;
    dword_800A85C8.f1C = 0;
    dword_800A85C8.f20 = 0;
    dword_800A8600.mask_8 = 1 << (xarr_800A85B8[0] + 8);
    dword_800A8600.targets_C = 1 << (xarr_800A8620[0] + 8);
    dword_800A85A8.mask_8 = 1 << (xarr_800A85B8[0] + 8);
    dword_800A85A8.targets_C = 1 << (xarr_800A8620[0] + 8);
    dword_800A8610.mask_8 = 1 << (xarr_800A8620[0] + 8);
    dword_800A8610.targets_C = 1 << (xarr_800A85B8[0] + 8);
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A5BB4);

extern unsigned char byte_800A84A8;
extern unsigned char byte_800A85FC[];
extern int dword_800A8490;
extern void sub_800A5BB4();
extern void sub_800A60F0();
extern void sub_800A5EB8();
extern void name_800BF7C4(UnitStatus* u, short* a, short* b);
extern int name_800BFA4C(int a, int b);

void sub_800A5C64(CombBtlTask* t)
{
    UnitStatus* u;
    int flags0;
    int fl;
    int r;
    sub_800A5BB4();
    word_800A8488 = 0;
    byte_800A84A8 &= 0xFC;
    sub_800A60F0();
    u = GetUnitStatus_80014390((unsigned char)(dword_800A85B8 + 8));
    flags0 = u->status_0;
    name_800BF7C4(u, &word_800A84BC, &word_800A84C4);
    if (word_800A84BC != 0)
    {
        if (word_800A84C4 != 0)
        {
            byte_800A85FC[dword_800A85B8] = 3;
            dword_800A85C8.kind_0 = 3;
        }
        else
        {
            byte_800A85FC[dword_800A85B8] = 1;
            dword_800A85C8.kind_0 = 1;
        }
    }
    else if (word_800A8474)
    {
        byte_800A85FC[dword_800A85B8] = 2;
        dword_800A85C8.kind_0 = 2;
    }
    fl = u->status_0;
    r = name_800BFA4C(fl, flags0);
    dword_800A85A8.kind_0 = r;
    dword_800A85A8.targets_C = 0;
    if (fl & 0x200)
    {
        t->next_8 = sub_800A68E0;
        word_800A84A6 = 0x6F;
        byte_800A84A8 |= 1;
        dword_800A8490 = dword_800A85B8;
        byte_800A84A8 |= 2;
    }
    else if (u->hp_8.cur_0 - word_800A84BC <= 0)
    {
        dword_800A85A8.kind_0 = 0xB;
        word_800A84BC = u->hp_8.cur_0;
        t->next_8 = sub_800A68E0;
        word_800A84A6 = 0x6F;
        byte_800A84A8 |= 1;
        dword_800A8490 = dword_800A85B8;
    }
    else if (fl & 2)
    {
        t->next_8 = sub_800A4EC8;
    }
    else if (r == 0x14)
    {
        t->next_8 = sub_800A5EB8;
    }
    else
    {
        byte_800A84A8 |= 2;
        t->next_8 = sub_800A68E0;
    }
}

void sub_800A5EB8(CombBtlTask* t)
{
    dword_800A85A0 = LoadOverlay_80020BF8(1, 0x19);
    t->next_8 = sub_800A5EF8;
}

void sub_800A5EF8(CombBtlTask* t)
{
    if (GetFileRequestStatus_8003BE30(dword_800A85A0) == 0)
    {
        sub_800A5BB4();
        dword_800A848C = sub_800CB7AC(&dword_800A8600, dword_800A85B8);
        t->next_8 = sub_800A5F60;
    }
}

void sub_800A5F60(CombBtlTask* t, int a)
{
    if ((dword_800A848C->flags & 0x8001) != 1)
    {
        sub_800A601C();
        if (byte_800A38DC)
        {
            byte_800A3A98[dword_800A85B8] = 2;
            t->next_8 = sub_800A5000;
            t->next_8(t, a);
        }
        else
        {
            sub_800A60A4();
            sub_800A616C();
            word_800A8488 = 0;
            t->next_8 = sub_800A68E0;
        }
    }
}

void sub_800A601C()
{
    int i;
    for (i = 10; i > 0; i--)
    {
        MemCopy_800403E8(&dword_800A84D8[i], &dword_800A84D8[i - 1], 0x14);
    }
    dword_800A84D8[0].unit_0 = dword_800A85B8;
    MemCopy_800403E8(&dword_800A84D8[0].cmd_4, &dword_800A8600, 0x10);
}

void sub_800A60A4()
{
    int a = dword_800A8600.kind_0;
    dword_800A85A8.kind_0 = a;
    dword_800A85A8.arg_4 = dword_800A8600.arg_4;
    dword_800A85A8.mask_8 = dword_800A8600.mask_8;
    dword_800A85A8.targets_C = dword_800A8600.targets_C;
    if (a == 8)
    {
        dword_800A85A8.kind_0 = 3;
        dword_800A85A8.arg_4 = 0;
    }
}

void sub_800A60F0()
{
    unsigned int i;
    word_800A84A4 = -1;
    word_800A84A6 = -1;
    word_800A84BC = 0;
    word_800A84C4 = 0;
    for (i = 0; i < 2; i++)
    {
        word_800A8470[i] = 0;
        word_800A8474[i] = 0;
        dword_800A8480[i] = 0;
        dword_800A85F0[i] = 0;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A616C);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A68E0);

int sub_800A7164(int i)
{
    int cnt = 0;
    int j;
    for (j = 0; j < 3; j++)
    {
        if (sub_800A1958(&dword_800A3AA0[i][j]) == 0)
        {
            cnt++;
        }
    }
    return cnt;
}

CombBtlPair sub_800A71E4(int n, CombBtlPair* p)
{
    CombBtlPair r;
    short hi = 0;
    short lo = hi;
    int i;
    for (i = 0; i < n; i++)
    {
        p->hi = p->hi - p->lo;
        p->lo = -p->lo;
        if (p->lo < lo)
        {
            lo = p->lo;
        }
        if (hi < p->hi)
        {
            hi = p->hi;
        }
        p++;
    }
    r.lo = lo;
    r.hi = hi;
    return r;
}

#if 0
// Not matched: scheduling/regalloc around the 0x1000 store and the cb_C address (15 words); the flags store only stays ahead of the camera stores with e as int*
extern void ResetCameraToLevant_800376A8(void);
extern void InitCameraTask_800368F8(void);
extern int cameraState_8008D4F0[];
extern int cameraZoom_8008B4F8;
extern short dword_8007C2EC[];
extern short dword_8007C30C[];
extern short lightMatrix_80087114[];
extern short colorMatrix_80087134[];
void sub_800A7290()
{
    int* e = (int*)AllocEventEntry_80043AF8(cameraTask_8008D4A0);
    char* p;
    SaveData* q;
    if (e)
    {
        e[0] = (e[0] | 1) & ~0x8000;
        ResetCameraToLevant_800376A8();
        StartBattleCamera_80037748();
        e[2] = (int)InitCameraTask_800368F8;
        cameraZoom_8008B4F8 = 0x1000;
        e[3] = (int)nullsub_5;
        e[0] = (e[0] | 4) & ~0x8000;
        p = (char*)cameraState_8008D4F0;
        *(short*)(p + 0x2E) = 0;
        *(int*)(p + 0x20) = 0;
        *(int*)(p + 0x24) = 0;
        *(int*)(p + 0x28) = 0;
        *(int*)(p + 0x14) = 0;
        *(int*)(p + 0x18) = 0;
        *(int*)(p + 0x1C) = 0;
        *(short*)(p + 0x34) = 0;
        *(short*)(p + 0x36) = 0;
        *(short*)(p + 0x38) = 0;
        *(short*)(p + 0x3C) = 0;
        *(short*)(p + 0x3E) = 0;
        *(short*)(p + 0x40) = 0;
        q = &saveData_8008B570;
        q->levant_7A8.pos.x = 0;
        q->levant_7A8.pos.y = 0;
        q->levant_7A8.pos.z = 0;
        q->levant_7A8.rot.vx = 0;
        q->levant_7A8.rot.vy = 0;
        q->levant_7A8.rot.vz = 0;
        *(short*)(p + 0x34) = dword_8007C2EC[0];
        *(short*)(p + 0x36) = dword_8007C2EC[1];
        *(short*)(p + 0x38) = dword_8007C2EC[2];
        *(short*)(p + 0x3C) = dword_8007C30C[0];
        *(short*)(p + 0x3E) = dword_8007C30C[3];
        *(short*)(p + 0x40) = dword_8007C30C[6];
        lightMatrix_80087114[0] = dword_8007C2EC[0];
        lightMatrix_80087114[1] = dword_8007C2EC[1];
        lightMatrix_80087114[2] = dword_8007C2EC[2];
        colorMatrix_80087134[0] = dword_8007C30C[0];
        colorMatrix_80087134[3] = dword_8007C30C[3];
        colorMatrix_80087134[6] = dword_8007C30C[6];
    }
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A7290);

void sub_800A73E4()
{
    sub_800376A0(&cameraTask_8008D4A0->entry, cameraTask_8008D4A0->entry.buffer);
    StopAllEventEntries_80043B40(cameraTask_8008D4A0);
}

void sub_800A7420()
{
    EventEntry* e = AllocEventEntry_80043AF8(fadeTask_8008D628);
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        InitSceneFade_8001A38C();
        e->cb_8 = (EventEntryFn)SceneFadeTask_8001A41C;
    }
}

void sub_800A7478()
{
    StopAllEventEntries_80043B40(fadeTask_8008D628);
}

void sub_800A74A0(int i)
{
    CombBtlA24 a = dword_800A4AD4;
    CombBtlB16 b = dword_800A4AEC;
    sub_800A0BA8(i, a.pos_0[i], b.f0[i]);
}

void sub_800A7560(int a)
{
    sub_800A0D1C(a);
    sub_800A0B70(a);
}

int sub_800A758C()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        if (dword_800A84B0[i])
        {
            if (sub_800A0B3C(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void sub_800A75F8(int a)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008B564);
    CombBtlObj* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (CombBtlObj*)e->buffer;
        p->a = a;
        p->b = 0;
        p->dst_8.x = word_800A82D4[a][0];
        p->dst_8.y = word_800A82D4[a][1];
        p->dst_8.w = 0x64;
        p->dst_8.h = 0x29;
        e->cb_8 = (EventEntryFn)sub_800A7694;
    }
}

typedef struct CombBtlPos2
{
    CombBtlPair p[2]; // per side
} CombBtlPos2;
typedef struct CombBtlInt3
{
    int v[3];
} CombBtlInt3;
extern CombBtlA28 dword_800A4AFC;
extern CombBtlA28 dword_800A4B18;
extern CombBtlPos2 dword_800A4B34;
extern CombBtlA28 dword_800A4B3C;
extern CombBtlPos2 dword_800A4B58;
extern CombBtlInt3 dword_800A4B60;
extern CombBtlPos2 dword_800A4B6C;
extern short word_800A82D0;
extern short word_800A82D2;
extern void AddClipDrawAreaPrim_80033308(unsigned long* ot);
extern void AddDrawAreaPrim_8003326C(RECT* r, unsigned long* ot);
extern void InterpolateWindowRect_8004196C(RECT* d, RECT* s, int cur, int max, int mode);
extern void DrawUnitStatusWindow_8002F1C8(UnitStatus* unit, int gaugeArg, int highlight, int time, RECT* rect, int ot,
                                          int flags);
extern void DrawStatusIcons_8002F480(UnitStatus* status, CombBtlPair* pos, int ot, int reverse);
extern void DrawMpGauge_8002F120(UnitStatus* unit, CombBtlPair* pos, int gaugeArg, short ot);
extern void DrawWindow_80042460(void* a, void* b, void* c, int d);

// Matched
void sub_800A7694(EventEntry* e, void* buf)
{
    CombBtlA28 w0 = dword_800A4AFC;
    CombBtlA28 w1 = dword_800A4B18;
    CombBtlBox box60;
    CombBtlPair pt;
    CombBtlPos2 pos70 = dword_800A4B34;
    CombBtlBox box78;
    CombBtlA28 w2;
    union
    {
        CombBtlPos2 pos;
        CombBtlBox box;
    } uA0;
    union
    {
        CombBtlInt3 v;
        RECT r;
    } uA8;
    CombBtlPos2 posB8;
    int sel = 0;
    UnitStatus* st;
    CombBtlA28* w;
    CombBtlObj* o;

    if (byte_800A84A8 & 0xC)
    {
        return;
    }
    o = buf;
    if (o->a == dword_800A85B8)
    {
        st = GetMinionStatusOf_80033818(&dword_800A3AA0[o->a][byte_800A85BD]);
    }
    else
    {
        st = GetMinionStatusOf_80033818(&dword_800A3AA0[o->a][dword_800A4078[o->a]]);
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    SetFontClutOffset_8003F900(1, 0);
    InterpolateWindowRect_8004196C(&o->cur_10, &o->dst_8, o->b, 4, 9);
    if (dword_800A85F8 >= 0 && dword_800A85F8 != o->a)
    {
        sel = 1;
    }
    if (o->a == dword_800A85B8)
    {
        DrawUnitStatusWindow_8002F1C8(st, word_800A82D0, sel, GetTime30Hz_8002C64C(), &o->cur_10, 10, 0);
    }
    else
    {
        DrawUnitStatusWindow_8002F1C8(st, 0, sel, GetTime30Hz_8002C64C(), &o->cur_10, 10, 0);
    }
    o->b++;
    AddDrawAreaPrim_8003326C(&o->cur_10, pOT_8008D454);
    pt.lo = pos70.p[o->a].lo;
    pt.hi = pos70.p[o->a].hi;
    DrawStatusIcons_8002F480(st, &pt, 0xF, o->a);
    if (o->a)
    {
        w = &w1;
    }
    else
    {
        w = &w0;
    }
    if (dword_800A85F8 < 0)
    {
        if (o->a == dword_800A85B8)
        {
            box60.c_2 = 1;
        }
        else
        {
            box60.c_2 = 0;
        }
    }
    else if (o->a == dword_800A85F8)
    {
        box60.c_2 = 0;
    }
    else
    {
        box60.c_2 = 1;
    }
    box60.c_3 = 1;
    box60.col_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(w, &box60, 0xF, GetTime30Hz_8002C64C());
    w2 = dword_800A4B3C;
    uA0.pos = dword_800A4B58;
    uA8.v = dword_800A4B60;
    w2.x_4 = uA8.v.v[dword_800A4078[o->a]];
    w2.x_10 = uA0.pos.p[o->a].lo;
    w2.y_12 = uA0.pos.p[o->a].hi;
    box78.c_2 = 0;
    box78.c_3 = 1;
    box78.col_0 = saveData_8008B570.uiColor_20.h;
    DrawMenuItemWithWindow_8002ADB4(&w2, &box78, 0xF, 0);
    posB8 = dword_800A4B6C;
    pt.lo = posB8.p[o->a].lo;
    pt.hi = posB8.p[o->a].hi;
    uA8.r.w = 0x64;
    uA8.r.h = 0x14;
    uA8.r.x = pt.lo;
    uA8.r.y = pt.hi;
    if (o->a == dword_800A85B8)
    {
        DrawMpGauge_8002F120(st, &pt, word_800A82D2, 0xF);
    }
    else
    {
        DrawMpGauge_8002F120(st, &pt, 0, 0xF);
    }
    uA0.box.c_3 = 1;
    uA0.box.col_0 = saveData_8008B570.uiColor_20.h;
    uA0.box.c_2 = 0;
    DrawWindow_80042460(&uA8.r, &uA0.box, &pOT_8008D454[0xF], 0);
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
}

void sub_800A7BE4()
{
    StopAllEventEntries_80043B40(dword_8008B564);
}

extern unsigned char byte_800A38D8;
extern void StartCameraShake_80037BFC(int a);
extern void StartPadVibration_80036528(int pad, int kind);
extern void sub_800A7E34(int a, int b, int c);
typedef struct CombBtlHitNum
{
    int kind_0; // 1 hp, 2 mp
    int amount_4;
    int frame_8;
    int fC;
    int* pos_10;
    int f14;
    int side_18;
} CombBtlHitNum;
extern void sub_800A7ECC();
void PlayHitFeedback_800A7C0C(int side)
{
    int me;
    int other;
    if (side == 0)
    {
        other = byte_800A38D8;
        me = 0;
    }
    else
    {
        me = byte_800A38D8;
        other = 0;
    }
    switch (dword_800A85C8.kind_0)
    {
    case 0:
        break;
    case 1:
        sub_800A7E34(side, dword_800A85C8.kind_0, word_800A8470[side]);
        if (word_800A8470[side] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            StartPadVibration_80036528(me, 0);
            StartPadVibration_80036528(other, 2);
        }
        break;
    case 2:
        sub_800A7E34(side, dword_800A85C8.kind_0, word_800A8474[side]);
        if (word_800A8474[side] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            StartPadVibration_80036528(side ? byte_800A38D8 : 0, 0);
        }
        break;
    case 3:
        sub_800A7E34(side, 1, word_800A8470[side]);
        sub_800A7E34(side, 2, word_800A8474[side]);
        if (word_800A8470[side] > 0 || word_800A8474[side] > 0)
        {
            StartCameraShake_80037BFC(0x1E);
            StartPadVibration_80036528(side ? byte_800A38D8 : 0, 0);
        }
        break;
    case 4:
        sub_800A7E34(side, 1, word_800A8470[side]);
        StartCameraShake_80037BFC(0x1E);
        StartPadVibration_80036528(side ? byte_800A38D8 : 0, 1);
        sub_800A7ECC();
        break;
    case 5:
        StartPadVibration_80036528(0, 0x26);
        break;
    }
}

void sub_800A7E34(int a, int b, int c)
{
    EventEntry* e = AllocEventEntry_80043AF8(hitNumberTasks_8008D778);
    CombBtlHitNum* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = e->buffer;
        p->kind_0 = b;
        p->frame_8 = 0;
        p->amount_4 = c;
        p->side_18 = a;
        p->pos_10 = sub_800A10DC(a);
        e->cb_8 = (EventEntryFn)sub_800A7EFC;
    }
}

void sub_800A7ECC()
{
    unsigned char c[3];
    c[0] = 0xFF;
    c[1] = 0xFF;
    c[2] = 0xFF;
    StartScreenFlash_8001C02C(c);
}

extern void AdjustUnitStatById_800127D0(int a, int b, int c, int d);
void sub_800A7EFC(EventEntry* e, CombBtlHitNum* buf)
{
    CombBtlHitNum* p = buf;
    DVECTOR sxy;
    SVECTOR v;
    long z;
    long flag;
    int d;
    v.vx = buf->pos_10[0];
    v.vy = buf->pos_10[1];
    v.vz = buf->pos_10[2];
    v.vx -= cameraEye_8008D600.vx;
    v.vy -= cameraEye_8008D600.vy;
    v.vz -= cameraEye_8008D600.vz;
    RotTransPers(&v, (long*)&sxy, &z, &flag);
    if (++p->frame_8 > 16)
    {
        e->flags = (e->flags & ~1) | 0x8000;
        return;
    }
    d = p->amount_4 / (17 - p->frame_8);
    d = -d;
    p->amount_4 += d;
    if (p->kind_0 == 1)
    {
        UnitStatus* r = GetUnitStatus_80014390((unsigned char)(p->side_18 + 8));
        AdjustUnitStatById_800127D0(p->side_18 + 8, 0, d, 0);
        if (r->hp_8.cur_0 <= 0)
        {
            KillUnit_800127B8(GetUnitStatus_80014390((unsigned char)(p->side_18 + 8)));
        }
    }
    else if (p->kind_0 == 2)
    {
        AdjustUnitStatById_800127D0(p->side_18 + 8, 2, d, 0);
    }
}

void sub_800A8078(short a, short b, short c)
{
    word_800A82E0[0] = 1;
    word_800A82E0[1] = a;
    word_800A82E0[2] = b;
    word_800A82E0[3] = c;
}

extern EventNode* dword_8008D458;
extern int dword_800A8478;
extern unsigned int dword_800A3A88;
extern int sub_800A5408();
extern void sub_800A816C();

int sub_800A8098(int a, int b, int c)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D458);
    if (e)
    {
        e->cb_8 = (EventEntryFn)sub_800A816C;
        e->flags = (e->flags | 1) & ~0x8000;
        XaRequestPlay_80043564(word_800A82E0[1], word_800A82E0[2], word_800A82E0[3]);
        dword_800A8478 = sub_800A5408(a, b, c);
        dword_800A3A88 &= ~4;
        dword_800A3A88 &= ~8;
        dword_800A3A88 &= ~0x10;
    }
    return (int)e;
}

extern int GetMsgWindowResultIfDone_800349B4();
extern int XaRequestStop_80043524();
extern void CloseMsgWindow_80034A84();

void sub_800A816C(EventEntry* e)
{
    int buf[4];
    int v;
    if (!(dword_800A3A88 & 4))
    {
        if (GetMsgWindowResultIfDone_800349B4(dword_800A8478, buf) && buf[3])
        {
            dword_800A3A88 |= 4;
        }
    }
    v = XaNoRequestPending_800435A4();
    if (v == 1 && XaIsIdle_80043584() == v)
    {
        dword_800A3A88 |= 8;
    }
    if (!(dword_800A3A88 & 8))
    {
        v = (settingsFlags_8008B58C.word >> 3) & 1;
        if (v == 1 && (dword_800A3A88 & 4))
        {
            if (!(dword_800A3A88 & 0x10))
            {
                if (XaRequestStop_80043524() == v)
                {
                    dword_800A3A88 |= 0x10;
                }
            }
        }
    }
    if ((dword_800A3A88 & 0xC) == 0xC)
    {
        dword_800A3A88 &= ~4;
        dword_800A3A88 &= ~8;
        dword_800A3A88 &= ~0x10;
        CloseMsgWindow_80034A84(dword_800A8478);
        e->flags = (e->flags & ~1) | 0x8000;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, dword_800A82D0);
