// TITLE.BIN - title screen, loaded at 0x800A05A0
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "title.h"

int unused_800A05A0 SDATA = 13;
const TitleColor nameCursorPulseColor_800A05A4 = { "$$$" };
const char aCaution_800A05A8[] = "\202b\202\201\202\225\202\224\202\211\202\217\202\216\201I"; // Caution!
const char str_800A05BC[] = "\202s\202\210\202\205\202\222\202\205\201@\202\211\202\223\201@\202\216\202\217\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\211\202\216\201@\202\224\202\210\202\205\201@\202r\202k\202n\202s"; // There is no MEMORY CARD in the SLOT
const char str_800A0604[] = "\202x\202\217\202\225\201@\202\227\202\211\202\214\202\214\201@\202\216\202\217\202\224\201@\202\202\202\205\201@\202\201\202\202\202\214\202\205\201@\202\224\202\217\201@\202\223\202\201\202\226\202\205"; // You will not be able to save
const char str_800A0640[] = "\202\207\202\201\202\215\202\205\201@\202\204\202\201\202\224\202\201\201D"; // game data.
const char aThereAreNoFreeB_800A0658[] = "\202s\202\210\202\205\202\222\202\205\201@\202\201\202\222\202\205\201@\202\216\202\217\201@\202\206\202\222\202\205\202\205\201@\202\202\202\214\202\217\202\203\202\213\202\223\201@\202\214\202\205\202\206\202\224\201@\202\217\202\216"; // There are no free blocks left on
const char aTheMEMORYCARDIn_800A069C[] = "\202\224\202\210\202\205\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201@\202\211\202\216\201@\202\224\202\210\202\211\202\223\201@\202r\202k\202n\202s\201D"; // the MEMORY CARD in this SLOT.
const TitleMenuWindow titleMenuWin0_800A06D8 = {
    {
        { 8, 1, { .num = 3 }, NULL, NULL, 106, 140, 108, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const TitleMenuWindow titleMenuWin1_800A0710 = {
    {
        { 8, 1, { .num = 4 }, NULL, NULL, 106, 157, 108, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const TitleMenuWindow titleMenuWin2_800A0748 = {
    {
        { 8, 1, { .num = 0 }, NULL, NULL, 106, 174, 108, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const TitleMenuWindow titleMenuWin3_800A0780 = {
    {
        { 8, 1, { .num = 1 }, NULL, NULL, 106, 191, 108, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const TitleMenuWindow titleMenuWin4_800A07B8 = {
    {
        { 8, 0, 0, NULL, NULL, 214, 140, 100, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const TitleMenuWindow titleMenuWin5_800A07F0 = {
    {
        { 8, 0, 0, NULL, NULL, 214, 157, 100, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const TitleMenuWindow titleMenuWin6_800A0828 = {
    {
        { 8, 0, 0, NULL, NULL, 214, 174, 100, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const TitleMenuWindow titleMenuWin7_800A0860 = {
    {
        { 8, 0, 0, NULL, NULL, 214, 191, 100, 16, 0, 2 },
        { 1, 0, 0, NULL, NULL, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, -1, -1 },
    },
};
const MenuWindowList titleMenuCfg_800A0898 = { 0x2102, 0, 8, 0, 0, 14 };
const TitleColor logoPulseColor_800A08B0 = { "ZZZ" };
const char debugLevantName_800A08B4[] = "\203\214\203o\203\223\203g"; // レバント
const int unused_800A08C0[2] = { 0, 0x8940000 };

void NewGameInit_800A08C8(TitleTask* t, NameEntryWork* c)
{
    RECT r;
    pulseMax_800A280C = 0x36;
    pulseMin_800A2810 = 0x18;
    c->pulseStep_64 = 0x1E;
    c->pulseTime_5C = 0;
    c->timer_68 = 0;
    c->pulsePeak_60 = 0x18;
    c->holding_6C = 0;
    r.x = 0x20;
    r.y = 0x20;
    r.w = display_8008B4D8.w_C - 0x20;
    r.h = display_8008B4D8.h_E - 0x20;
    t->next_8 = NewGameLoadSprites_800A093C;
}

void NewGameLoadSprites_800A093C(TitleTask* t, NameEntryWork* c)
{
    void* buf;
    if (GetFileRequestCount_8003BC34() == 0)
    {
        c->sprts_70 = 0;
        c->tpages_74 = 0;
        buf = DATA_GetFileBuffer_8003CAA0(0x39);
        LoadTiy_80028E74(&c->sprts_70, 0, &c->tpages_74, buf, HEAP_MALLOC3);
        free3_8003FC6C(buf);
        t->next_8 = NewGameOpeningMovie_800A09C0;
    }
}

void NewGameOpeningMovie_800A09C0(TitleTask* t)
{
    int done;
    if (saveData_8008B570.flags_0 & 0x80)
    {
        done = PlayMovie_80040EB4(8);
    }
    else
    {
        done = PlayMovie_80040EB4(6);
    }
    if (done)
    {
        LoadUiTiy_8002BF74();
        t->next_8 = NewGameLoadNameOvl_800A0A1C;
    }
}

void NewGameLoadNameOvl_800A0A1C(TitleTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        padPressed_8009194C[0] = 0;
        nameOvlRequest_800A2808 = LoadOverlay_80020BF8(1, 0x11);
        t->next_8 = NewGameStartNameEntry_800A0A70;
    }
}

void NewGameStartNameEntry_800A0A70(TitleTask* t)
{
    if (GetFileRequestStatus_8003BE30(nameOvlRequest_800A2808) == 0)
    {
        if (!(saveData_8008B570.flags_0 & 0x80))
        {
            EncodeName_8003F7C8(levantName_800A2718, saveData_8008B570.levantStatus_7C8.name_10);
        }
        StartNameEntry_800B6E4C(saveData_8008B570.levantStatus_7C8.name_10, 0);
        t->next_8 = NewGameNameEntry_800A0AE8;
    }
}

void NewGameNameEntry_800A0AE8(TitleTask* t, NameEntryWork* c)
{
    if (c->holding_6C == 0)
    {
        c->pulseTime_5C++;
        if (c->pulsePeak_60 == c->pulseTime_5C)
        {
            c->holding_6C = 1;
        }
    }
    else if (c->timer_68 < 0x18)
    {
        c->timer_68++;
    }
    else
    {
        c->timer_68 = 0;
        c->holding_6C = 0;
        c->pulsePeak_60 += c->pulseStep_64;
        if (c->pulseStep_64 == pulseMax_800A280C - pulseMin_800A2810)
        {
            c->pulseStep_64 = pulseMin_800A2810;
        }
        else
        {
            c->pulseStep_64 = pulseMax_800A280C - pulseMin_800A2810;
        }
    }
    DrawNameEntrySprites_800A0D18(c->sprts_70, c->tpages_74, 0, c);
    if (IsNameEntryActive_800B6FC8() == 0)
    {
        FreeActiveOverlay_8002C014();
        t->next_8 = NewGameAfterNameMovie_800A0C28;
    }
}

void NewGameFadeOut_800A0BCC(TitleTask* t, NameEntryWork* c)
{
    if (--c->timer_68 <= 0)
    {
        FreeSound_80030D00(&bgmSound_80091CE0);
        TitleExit_800A1AFC(t, 0xC);
        t->flags_0 = (t->flags_0 & ~1) | 0x8000;
    }
}

void NewGameAfterNameMovie_800A0C28(TitleTask* t, NameEntryWork* c)
{
    int done;
    SoundStruct* ss;
    if (saveData_8008B570.flags_0 & 0x80)
    {
        done = PlayMovie_80040EB4(9);
        saveData_8008B570.flags_0 &= ~0x80;
    }
    else
    {
        done = PlayMovie_80040EB4(7);
    }
    if (done)
    {
        FREE_PTR(c->sprts_70);
        FREE_PTR(c->tpages_74);
        c->timer_68 = 0x3C;
        t->next_8 = NewGameFadeOut_800A0BCC;
        ss = &bgmSound_80091CE0;
        if (ss->seqNum_4 >= 0)
        {
            SsSepSetDecrescendo(*(short*)&ss->sepAccessNum_C, ss->seqNum_4, 0x7F, 0x78);
            ss->seqNum_4 = -1;
        }
    }
}

// The redundant `case 0` next to `default` (both i = 0) is needed: the post-reload jump pass
// cross-jumps the two arms and hoists i = 0 in front of the first test after sched2, so it ends up
// in the beqz delay slot; an if/else-if chain gets jump-threaded or turned into a store-flag.
void DrawNameEntrySprites_800A0D18(SPRT* sprts, DR_TPAGE* tpages, int mode, NameEntryWork* c)
{
    short i;
    int y = 0;
    short j;
    char zero[4];
    TitleColor color;

    switch (mode)
    {
    case 0:
        i = 0;
        break;
    case 1:
        i = 2;
        break;
    default:
        i = 0;
    }
    if (mode != 1)
    {
        for (j = i; j < i + 2; j++)
        {
            sprts[j].x0 = ((j % 2) * 5) << 5;
            sprts[j].y0 = y;
            AddPrimCopy_80040298(pOT_8008D3EC, &sprts[j], sizeof(sprts[j]) / 4);
            AddPrimCopy_80040298(pOT_8008D3EC, &tpages[j], sizeof(tpages[j]) / 4);
        }
    }
    else
    {
        memset(zero, 0, 4);
        y = 0x17;
        color = nameCursorPulseColor_800A05A4;
        sprts[i].x0 = 0x6F;
        sprts[i].y0 = y;
        PulseColor_80033394(&sprts[i].r0, zero, &color, c->pulseTime_5C, pulseMax_800A280C, pulseMin_800A2810);
        SetSemiTrans(&sprts[i], 1);
        AddPrimCopy_80040298(pOT_8008D3EC, &sprts[i], sizeof(sprts[i]) / 4);
        AddPrimCopy_80040298(pOT_8008D3EC, &tpages[i], sizeof(tpages[i]) / 4);
    }
}

// TITLE overlay entry: runs the title tasks, returns the next GameStates value (titleResult_800A2818)
enum GameStates TitleMain_800A0EF0(void)
{
    SetFadeMode_8001C19C(3, 0x20);
    drawEnvRed_8008D448[0] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[2] = 0;
    LoadSound_80030A84(0x1B, &bgmSound_80091CE0);
    PlayMusicSeq_80031260(&bgmSound_80091CE0, 0x1B, 1);
    DrawIntroMovie_8001AF64(titleTaskList_800A27C0);
    FreeSound_80030D00(&bgmSound_80091CE0);
    return titleResult_800A2818;
}

void TitleInit_800A0F6C(TitleTask* t, TitleMenuWork* c)
{
    void* buf;
    if (unknownFlags_8008D678 & 0x20000000)
    {
        titleMenuState_8008B558[1] = 4;
        SetNewGameStartMap_800A2650();
        saveData_8008B570.flags_0 |= 0x80;
        StartNewGameTask_800A1B74(t);
    }
    else
    {
        c->cursor_1C[0] = 1;
        c->cursor_1C[1] = 4;
        c->cursor_1C[2] = 4;
        c->cursor_1C[3] = 2;
        c->field_4 = 0;
        c->field_8 = 0;
        c->selected_24 = (unsigned short)titleMenuState_8008B558[1];
        titleIdleTimer_800A2814 = 0;
        c->field_26 = 0;
        c->sprts_C = 0;
        c->tpages_14 = 0;
        buf = DATA_GetFileBuffer_8003CAA0(0x36);
        LoadTiy_80028E74(&c->sprts_C, 0, &c->tpages_14, buf, HEAP_MALLOC3);
        free3_8003FC6C(buf);
        (t->next_8 = TitleEnterScreen_800A1070)(t, c);
    }
}

void TitleEnterScreen_800A1070(TitleTask* t, TitleMenuWork* c)
{
    switch ((unsigned short)titleMenuState_8008B558[0])
    {
    case 0:
        t->next_8 = TitlePressStart_800A1174;
        break;
    case 1:
        c->frames_0 = 0;
        t->next_8 = TitleMenu_800A1310;
        break;
    }
    t->next_8(t, c);
}

void TitleFree_800A10D0(TitleTask* t, TitleMenuWork* c)
{
    TitleMenuWork* d = c;
    titleMenuState_8008B558[1] = c->selected_24;
    if (unknownFlags_8008D678 & 0x20000000)
    {
        titleMenuState_8008B558[1] = 4;
        unknownFlags_8008D678 &= ~0x20000000;
    }
    if (c->sprts_C)
    {
        free3_8003FC6C(c->sprts_C);
        c->sprts_C = 0;
    }
    if (d->tpages_14)
    {
        free3_8003FC6C(d->tpages_14);
        d->tpages_14 = 0;
    }
}

#define TITLE_TIMEOUT(t, c) \
    if (++titleIdleTimer_800A2814 >= 0x1771) \
    { \
        (c)->frames_0 = 0; \
        if (bgmSound_80091CE0.seqNum_4 >= 0) \
        { \
            SsSepSetDecrescendo(*(short*)&bgmSound_80091CE0.sepAccessNum_C, bgmSound_80091CE0.seqNum_4, 0x7F, 0x78); \
            bgmSound_80091CE0.seqNum_4 = -1; \
        } \
        SetFadeMode_8001C19C(0, 0x20); \
        SetFadeMode_8001C19C(1, 0x20); \
        (t)->next_8 = TitleIdleFadeOut_800A1AC0; \
    }
void TitlePressStart_800A1174(TitleTask* t, TitleMenuWork* c)
{
    WindowStyle style;
    RECT rect;
    TitleMenuWork* d = c;
    rect.x = 0x4D;
    rect.y = 0xA3;
    rect.w = 0xA6;
    rect.h = 0x12;
    style.colorSet_2 = 1;
    style.semiTrans_3 = 1;
    style.color_0 = 4;
    c->sprts_C[2].x0 = 0x54;
    c->sprts_C[2].y0 = 0xA7;
    AddPrimCopy_80040298(pOT_8008D454 + 14, &c->sprts_C[2], sizeof(c->sprts_C[2]) / 4);
    AddPrimCopy_80040298(pOT_8008D454 + 14, &c->tpages_14[2], sizeof(c->tpages_14[2]) / 4);
    DrawWindow_80042460(&rect, &style, pOT_8008D454 + 14, (unsigned int)frameCount_8008D3FC >> 1);
    DrawTitleBackground_800A1F98(c->sprts_C, c->tpages_14, c);
    if (padPressed_8009194C[0] & 0x800)
    {
        PlaySfx_80031494(0x7E);
        srand(gnFrame_8008D610);
        c->frames_0 = 0;
        t->next_8 = TitleMenu_800A1310;
        titleIdleTimer_800A2814 = 0;
    }
    TITLE_TIMEOUT(t, d)
}

void TitleMenu_800A1310(TitleTask* t, TitleMenuWork* c)
{
    DrawTitleBackground_800A1F98(c->sprts_C, c->tpages_14, c);
    UpdateMenuCursor_8003D794(c->cursor_1C, 0);
    if (padRepeat_800918CC[0] & 0x5000)
    {
        c->frames_0 = 0;
        titleIdleTimer_800A2814 = 0;
    }
    DrawTitleMenu_800A1760(c, c->selected_24, c->frames_0);
    c->frames_0 = c->frames_0 + 1;
    if (IsConfirmPressedP1_8003D380(1))
    {
        titleIdleTimer_800A2814 = 0;
        titleMenuHandlers_800A27E8[c->selected_24](t, c);
        if ((unsigned short)c->selected_24 < 2)
        {
            CheckMemCards_8003BB1C();
            if (c->selected_24 == 0)
            {
                LoadOverlay_80020BF8(2, 0x10);
                MemCardStart();
                t->next_8 = NewGameCheckMemCards_800A14A8;
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        titleIdleTimer_800A2814 = 0;
        t->next_8 = TitleEnterScreen_800A1070;
    }
    TITLE_TIMEOUT(t, c)
}

void NewGameCheckMemCards_800A14A8(TitleTask* t)
{
    int i;
    int a;
    int b;
    b = 0;
    a = 0;
    t->next_8 = NoMemCardWarning_800A158C;
    for (i = 0; i < 2; i++)
    {
        MemCardAccept(i << 4);
        MemCardSync(0, &a, &b);
        if (b != 0)
        {
            if (b < 0)
            {
                continue;
            }
            if (b >= 5)
            {
                continue;
            }
            if (b < 3)
            {
                continue;
            }
        }
        {
            ScanCardSaves_800BAFB0(i);
            if (GetCardFreeBlocks_800BAE2C() || GetCardSaveCount_800BAE3C())
            {
                t->next_8 = NewGameMemCardOk_800A1728;
                return;
            }
            else
            {
                t->next_8 = NoFreeBlocksWarning_800A166C;
            }
        }
    }
}

void NoMemCardWarning_800A158C(TitleTask* t)
{
    RECT r0;
    RECT r1;
    RECT r2;
    RECT r3;
    MemCardStop();
    r0.x = 0x10;
    r0.y = 0x5A;
    DrawText_8003E91C(2, aCaution_800A05A8, &r0, 0);
    r1.x = 0x10;
    r1.y = 0x6A;
    DrawText_8003E91C(2, str_800A05BC, &r1, 0);
    r2.x = 0x10;
    r2.y = 0x7A;
    DrawText_8003E91C(2, str_800A0604, &r2, 0);
    r3.x = 0x10;
    r3.y = 0x8A;
    DrawText_8003E91C(2, str_800A0640, &r3, 0);
    if (IsConfirmPressedP1_8003D380(1))
    {
        t->next_8 = TitleMenu_800A1310;
        StartNewGameTask_800A1B74(t);
    }
}

void NoFreeBlocksWarning_800A166C(TitleTask* t)
{
    TitleRect r1, r2, r3;
    MemCardStop();
    r1.x = 0x10;
    r1.y = 0x5A;
    DrawText_8003E91C(2, aCaution_800A05A8, &r1, 0);
    r2.x = 0x10;
    r2.y = 0x6A;
    DrawText_8003E91C(2, aThereAreNoFreeB_800A0658, &r2, 0);
    r3.x = 0x10;
    r3.y = 0x7A;
    DrawText_8003E91C(2, aTheMEMORYCARDIn_800A069C, &r3, 0);
    if (IsConfirmPressedP1_8003D380(1))
    {
        t->next_8 = TitleMenu_800A1310;
        StartNewGameTask_800A1B74(t);
    }
}

void NewGameMemCardOk_800A1728(TitleTask* t)
{
    MemCardStop();
    t->next_8 = TitleMenu_800A1310;
    StartNewGameTask_800A1B74(t);
}

void DrawTitleMenu_800A1760(TitleMenuWork* work, int sel, int frames)
{
    DrawTitleMenuWindows_800A1780(work, sel);
}

void DrawTitleMenuWindows_800A1780(TitleMenuWork* work, int sel)
{
    TitleMenuWindow b0, b1, b2, b3, b4, b5, b6, b7;
    MenuWindowItem* ptrs[5];
    MenuWindowList cfg;
    b0 = titleMenuWin0_800A06D8;
    b1 = titleMenuWin1_800A0710;
    b2 = titleMenuWin2_800A0748;
    b3 = titleMenuWin3_800A0780;
    b4 = titleMenuWin4_800A07B8;
    b5 = titleMenuWin5_800A07F0;
    b6 = titleMenuWin6_800A0828;
    b7 = titleMenuWin7_800A0860;
    memset(ptrs, 0, sizeof(ptrs));
    cfg = titleMenuCfg_800A0898;
    b0.items[0].sprts_8 = &work->sprts_C;
    b0.items[0].tpages_C = &work->tpages_14;
    b1.items[0].sprts_8 = &work->sprts_C;
    b1.items[0].tpages_C = &work->tpages_14;
    b2.items[0].sprts_8 = &work->sprts_C;
    b2.items[0].tpages_C = &work->tpages_14;
    b3.items[0].sprts_8 = &work->sprts_C;
    b3.items[0].tpages_C = &work->tpages_14;
    ptrs[0] = b0.items;
    ptrs[1] = b1.items;
    ptrs[2] = b2.items;
    ptrs[3] = b3.items;
    cfg.time_4 = GetTime30Hz_8002C64C();
    cfg.cursor_C = sel;
    cfg.items_10 = ptrs;
    DrawMenuWindows_8002A5A4(&cfg);
}

void TitleIdleFadeOut_800A1AC0(TitleTask* t, int* cnt)
{
    if (++*cnt >= 0x5B)
    {
        TitleExit_800A1AFC(t, 5);
    }
}

void TitleExit_800A1AFC(TitleTask* t, int result)
{
    SoundStruct* bgm = &bgmSound_80091CE0;
    titleResult_800A2818 = result;
    if (bgm->seqNum_4 >= 0)
    {
        SsSepSetDecrescendo((short)bgm->sepAccessNum_C, bgm->seqNum_4, 0x7F, 0x78);
        bgm->seqNum_4 = -1;
    }
    bStopDrawingMovie_8008D45C = 1;
    t->flags_0 &= ~1;
}

// stops the title menu task and enables newGameTaskDesc_800A2790 (name entry + opening movies)
void StartNewGameTask_800A1B74(TitleTask* t)
{
    EventEntry* e;
    t->flags_0 &= ~1;
    e = AllocEventEntry_80043AF8(newGameTask_8008D638);
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
    }
}

void InitNewGameData_800A1BCC(void)
{
    InitSaveData_800A211C();
    ClearCapturedMinions_800A2214();
    ClearMinionSlots_800A2450();
    if (titleStartMode_8008B55A == 1)
    {
        ResetMapIds_800A242C();
    }
}

void MenuLoadGame_800A1C18(TitleTask* t)
{
    titleStartMode_8008B55A = 1;
    LoadOverlay_80020BF8(2, 0x10);
    SetDisplayMode_80040658(1);
    saveData_8008B570.field_810 = -2;
    LoadMenuInit_800B7674(1, 0);
    t->next_8 = LoadGameWait_800A1CC0;
}

// menu entry 4: fresh save data, straight into the game (no name entry)
void MenuQuickStart_800A1C7C(TitleTask* t)
{
    titleStartMode_8008B55A = 4;
    InitNewGameData_800A1BCC();
    SetNewGameStartMap_800A2650();
    TitleExit_800A1AFC(t, 0xC);
}

void LoadGameWait_800A1CC0(TitleTask* t)
{
    if (!IsLoadMenuActive_800B793C())
    {
        if (GetLoadMenuLoaded_800B7914() == 1)
        {
            if (saveData_8008B570.flags_0 & 0x80)
            {
                titleStartMode_8008B55A = 4;
                SetNewGameStartMap_800A2650();
                saveData_8008B570.flags_0 |= 0x80;
                StartNewGameTask_800A1B74(t);
            }
            else
            {
                TitleExit_800A1AFC(t, 7);
            }
        }
        else
        {
            t->next_8 = TitleMenu_800A1310;
            SetDisplayMode_80040658(1);
        }
    }
}

void MenuNewGame_800A1D6C(void)
{
    InitNewGameData_800A1BCC();
}

void MenuConfig_800A1D8C(TitleTask* t)
{
    LoadOverlay_80020BF8(2, 0xF);
    SetFadeMode_8001C19C(0, 0x20);
    LoadUiTiy_8002BF74();
    t->next_8 = ConfigWaitUiTiy_800A1DD8;
}

void ConfigWaitUiTiy_800A1DD8(TitleTask* t)
{
    if (uiTiyLoaded_8008B4E8)
    {
        SetFadeMode_8001C19C(3, 0x20);
        StartConfigMenu_800C2EB4();
        t->next_8 = ConfigWait_800A1E24;
    }
}

void ConfigWait_800A1E24(TitleTask* t, TitleMenuWork* u)
{
    if (!IsConfigMenuActive_800C45D8())
    {
        u->frames_0 = 0;
        FreeActiveOverlay_8002C014();
        DrawTitleBackground_800A1F98(u->sprts_C, u->tpages_14, u);
        DrawTitleMenu_800A1760(u, u->selected_24, u->frames_0);
        SetFadeMode_8001C19C(0, 0x20);
        t->next_8 = ConfigReturn_800A1E9C;
    }
}

void ConfigReturn_800A1E9C(TitleTask* t, TitleMenuWork* u)
{
    SetFadeMode_8001C19C(3, 0x20);
    DrawTitleBackground_800A1F98(u->sprts_C, u->tpages_14, u);
    DrawTitleMenu_800A1760(u, u->selected_24, u->frames_0);
    t->next_8 = TitleMenu_800A1310;
}

// menu entry 2: GAME starts on the arena map and returns eBattleArenaMenu_8 (flag 0x40000000)
void MenuBattleArena_800A1F00(TitleTask* t)
{
    unknownFlags_8008D678 |= 0x40000000;
    TitleExit_800A1AFC(t, 0xC);
}

#define SDECL SaveData* s = &saveData_8008B570

void MenuSoundTest_800A1F38(void* task)
{
    TitleExit_800A1AFC(task, 9);
}

void MenuTstModel_800A1F58(void* task)
{
    TitleExit_800A1AFC(task, 10);
}

void MenuTstCompo_800A1F78(void* task)
{
    TitleExit_800A1AFC(task, 11);
}

void DrawTitleBackground_800A1F98(SPRT* sprts, DR_TPAGE* tpages, TitleMenuWork* work)
{
    char zero[4];
    TitleColor color;
    short i;
    short y;
    SPRT* sprt;
    SPRT* logo;

    memset(zero, 0, 4);
    y = 0x4A;
    logo = &sprts[5];
    color = logoPulseColor_800A08B0;
    logo->y0 = y;
    logo->x0 = 0x55;
    PulseColor_80033394(&sprts[5].r0, zero, &color, frameCount_8008D3FC, 0xB4, 0x5A);
    SetSemiTrans(logo, 1);
    AddPrimCopy_80040298((void*)pOT_8008D3EC, logo, sizeof(*logo) / 4);
    AddPrimCopy_80040298((void*)pOT_8008D3EC, &tpages[5], sizeof(tpages[5]) / 4);
    y = 0;
    for (i = 7; i < 9; i++)
    {
        sprt = (SPRT*)((int)i * sizeof(SPRT) + (long)sprts); // &sprts[i] does not match
        sprt->x0 = (i - 7) * 5 << 5;
        sprt->y0 = y;
        AddPrimCopy_80040298((void*)pOT_8008D3EC, sprt, sizeof(*sprt) / 4);
        AddPrimCopy_80040298((void*)pOT_8008D3EC, &tpages[i], sizeof(tpages[i]) / 4);
    }
}

void InitLevantEquipment_800A20F4(void)
{
    SDECL;
    s->levantStatus_7C8.equipment_1C[0] = 0;
    s->levantStatus_7C8.equipment_1C[1] = 0xFF;
    s->levantStatus_7C8.equipment_1C[2] = 0xFF;
}

void ClearMapVars_800A2110(void)
{
    saveData_8008B570.nMapVars_2F4 = 0;
}

void InitSaveData_800A211C(void)
{
    SDECL;
    s->field_984 = 5;
    saveData_8008B570.flags_0 = 0;
    s->chapterNext_2DE = -1;
    s->playTime_4 = 0;
    s->chapter_2DC = 0;
    s->levant_7A8.pos = levantStartPos_800B069C;
    s->levant_7A8.rot = levantStartRot_800B06A8;
    s->levantStatus_7C8 = levantInitStatus_800A2730;
    saveData_8008B570.field_810 = -2;
    ClearInventory_800A2358();
    InitLevantEquipment_800A20F4();
    ClearMapVars_800A2110();
    InitFlagTables_800A2540();
}

void ClearCapturedMinions_800A2214(void)
{
    int i;
    SDECL;
    for (i = 6; i >= 0; i--)
    {
        s->allMinionsBitfields_814[i] = 0;
    }
}

// unreferenced
void InitDebugSaveData_800A223C(void)
{
    {
        SDECL;
        s->levantStatus_7C8 = levantInitStatus_800A2730;
    }
    {
        int i;
        SDECL;
        for (i = 6; i >= 0; i--)
        {
            s->allMinionsBitfields_814[i] = 0;
        }
    }
    EncodeName_8003F7C8(debugLevantName_800A08B4, saveData_8008B570.levantStatus_7C8.name_10);
    ClearInventory_800A2358();
    GiveDebugStartItems_800A22FC();
    ClearMinionSlots_800A2450();
    InitStub_800A2424();
}

void GiveDebugStartItems_800A22FC(void)
{
    SaveInventory* b = &saveData_8008B570.inv_24;
    b->yan_0 = 0x64;
    b->inventory_4[0][0].count = 3;
    b->inventory_4[0][1].id = 0xE;
    b->inventory_4[0][0].id = 0;
    b->inventory_4[0][1].count = 1;
    saveData_8008B570.levantStatus_7C8.equipment_1C[0] = 1;
    saveData_8008B570.levantStatus_7C8.equipment_1C[1] = 0;
    saveData_8008B570.levantStatus_7C8.equipment_1C[2] = 0xFF;
    if ((unsigned int)b->emptyCocoons_284 < 10)
    {
        saveData_8008B570.inv_24.emptyCocoons_284 = 10;
    }
}

void ClearInventory_800A2358(void)
{
    SaveInventory* b;
    unsigned char* p;
    int i;
    int j;
    int k;
    playerYan_8008B594.yan_0 = 0;
    b = &playerYan_8008B594;
    for (i = 0; i < 0x40; i++)
    {
        b->inventory_4[0][i].id = 0xFF;
        b->inventory_4[0][i].count = 0;
    }
    for (i = 0; i < 0x40; i++)
    {
        b->inventory_4[4][i].id = 0xFF;
        b->inventory_4[4][i].count = 0;
    }
    for (i = 0; i < 0x40; i++)
    {
        b->inventory_4[3][i].id = 0xFF;
        b->inventory_4[2][i].id = 0xFF;
        b->inventory_4[1][i].id = 0xFF;
        b->inventory_4[3][i].count = 0;
        b->inventory_4[2][i].count = 0;
        b->inventory_4[1][i].count = 0;
    }
    b->emptyCocoons_284 = 0;
    b->flags_288[0] = 0;
    b->flags_288[1] = 0;
    // walked with a byte pointer (p = b + j; indexing bits_290[j] does not get the pointer decrement)
    for (j = 0x12, p = (unsigned char*)b + 0x12; j >= 0; j--, p--)
    {
        p[0x290] = 0;
    }
    for (k = 0x13, p = (unsigned char*)b + 0x13; k >= 0; k--, p--)
    {
        p[0x2A3] = 0;
    }
}

void InitStub_800A2424(void)
{
}

void ResetMapIds_800A242C(void)
{
    SDECL;
    s->field_2E2 = -1;
    s->mapId_2E4[0].prev_2 = -1;
    s->mapId_2E4[1].prev_2 = -1;
    s->mapId_2E4[2].prev_2 = -1;
    s->mapId_2E4[3].prev_2 = -1;
}

void ClearMinionSlots_800A2450(void)
{
    short i;
    for (i = 0; i < 15; i++)
    {
        saveData_8008B570.minions[i].id = 4;
    }
    for (i = 0; i < 12; i++)
    {
        saveData_8008B570.items[i].species_5C = 0xD3;
    }
}

void StoreAllPartyMinions_800A24E0(void)
{
    short i;
    for (i = 0; i < 15; i++)
    {
        if (saveData_8008B570.minions[i].id == 3)
        {
            saveData_8008B570.minions[i].id = 2;
        }
    }
}

#define FILL(arr, n) { int i; unsigned short v = 0x8000; SDECL; for (i = (n) - 1; i >= 0; i--) s->arr[i] = v; }

void InitFlagTables_800A2540(void)
{
    encounterVariantToggle_8008B554 = 1;
    FILL(tbl_838, 12)
    FILL(tbl_850, 18)
    FILL(tbl_874, 44)
    FILL(tbl_8CC, 22)
    FILL(tbl_8F8, 10)
    FILL(tbl_90C, 16)
    FILL(tbl_92C, 42)
}

void SetNewGameStartMap_800A2650(void)
{
    SDECL;
    s->chapterNext_2DE = -1;
    s->mapVariant_2E0 = 1;
    s->field_2E2 = -1;
    s->mapId_2E4[0].prev_2 = -1;
    s->mapId_2E4[1].prev_2 = -1;
    s->mapId_2E4[2].prev_2 = -1;
    s->mapId_2E4[3].prev_2 = -1;
    s->mapId_2E4[1].cur_0 = 4;
    useMapStartPos_80091C94 = 1;
    s->playTime_4 = 0;
    s->chapter_2DC = 0;
    s->field_810 = 0;
    s->mapId_2E4[0].cur_0 = 0;
    s->mapId_2E4[2].cur_0 = 0;
    s->mapId_2E4[3].cur_0 = 0;
    s->levant_7A8.pos = levantStartPos_800B069C;
    s->levant_7A8.rot = levantStartRot_800B06A8;
    ClearMapVars_800A2110();
    InitFlagTables_800A2540();
}

char levantName_800A2718[] = "\202k\202\205\202\226\202\201\202\216\202\224"; // Levant
int unused_800A2728 = 0;
int unused_800A272C = 0;
UnitStatus levantInitStatus_800A2730 = {
    0,
    0,
    { 100, 100 },
    { 0 },
    { 0 },
    { 255, 255, 255, 255 },
    { 56, 56, 56, 56, 32, 32, 32, 16, 32, 224, 32, 32 },
    { { 20, 23, 20, 23, 20 } },
    { 8, 8, 8, 8 },
    0,
    1,
    1,
};
EventDesc titleMenuTaskDesc_800A2778 = { 1, 5, 52, 0, (EventEntryFn)TitleInit_800A0F6C, (EventEntryFn)TitleFree_800A10D0 };
EventDesc newGameTaskDesc_800A2790 = { 1, 0x8000, 120, &newGameTask_8008D638, (EventEntryFn)NewGameInit_800A08C8 };
EventDesc titleSoundTaskDesc_800A27A8 = { 1, 5, 64, &soundTask_8008D4A4, (EventEntryFn)InitSoundTask_8002FF10, (EventEntryFn)FreeSoundTask_8003006C };
// the title's event lists (DrawIntroMovie_8001AF64), 0-terminated
EventDesc* titleTaskList_800A27C0[10] = {
    &eventDescs_80078EB8[0],
    &titleMenuTaskDesc_800A2778,
    &eventDescs_80078EB8[8],
    &eventDescs_80078EB8[13],
    &eventDescs_80078EB8[12],
    &titleSoundTaskDesc_800A27A8,
    &newGameTaskDesc_800A2790,
    &eventDescs_80078EB8[15],
    &eventDescs_80078EB8[11],
};
void (*titleMenuHandlers_800A27E8[8])() = { (void (*)())MenuNewGame_800A1D6C, (void (*)())MenuLoadGame_800A1C18, (void (*)())MenuBattleArena_800A1F00, (void (*)())MenuConfig_800A1D8C, (void (*)())MenuQuickStart_800A1C7C, (void (*)())MenuSoundTest_800A1F38, (void (*)())MenuTstModel_800A1F58, (void (*)())MenuTstCompo_800A1F78 };
int nameOvlRequest_800A2808 = 0;
int pulseMax_800A280C = 0;
int pulseMin_800A2810 = 0;
unsigned int titleIdleTimer_800A2814 = 0;
int titleResult_800A2818 = 0;
