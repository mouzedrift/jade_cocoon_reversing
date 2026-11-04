// MAP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "map.h"

typedef struct MapTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MapTask;

typedef struct MapQuery
{
    short a;
    short b;
    short c;
} MapQuery;

extern int sub_800AD0D4(int);
extern int sub_800ADC1C(MapQuery*);
extern int sub_800B8290(MapPos*);
typedef struct MapEntry
{
    short id;
    char pad_2[14];
} MapEntry;

extern MapEntry** mapTable_800B0608[];
extern int dword_800B0624[];
extern int dword_80091C54;
extern void DrawCursorHand_8003D034(void*, int);
#define SEL dword_800AEBFC[word_800AEBF8.a]
extern int GetMenuCursorIndex_8003DA54(void*);
extern void sub_800A8DEC();
extern void sub_800A6D30(int);
extern void sub_800AD16C(int, int);
extern int useMapStartPos_80091C94;
extern MapSel dword_800AEBFC[];
extern unsigned short padRepeat_800918CC;
extern void DrawText_8003E91C(int, void*, void*, int);
extern void DrawNumber_8003EF74(void*, int, int);
extern int sub_800AD154(int);
extern void PlayMusic_800300E0(int, int);
extern void sub_800B6E5C();
extern int sub_800B81D0(MapPos*);
// state of the map select (sub_800B860C)
extern MapPos word_800AEBF8;  // the selected destination (GAME data)
extern void sub_800B8448();
extern short word_800B932C;
extern void SetFadeMode_8001C19C(int, int);
extern void ResetPadHoldFrames_8001CD04(int);
extern void QueueFileRequest_8003BC84(FileRequestDesc* req);
extern void sub_800B6CB4();
extern void sub_800B6C7C();
extern void sub_800B6DE0(MapTask*, int*);
extern void sub_800B6E80();
extern void sub_800B6EE8();
extern void sub_800B6FAC(MapTask*);
extern void sub_800B7044();
extern void sub_800B7980();
extern void sub_800B7A90();
extern void sub_800B7A38();
extern void sub_800B860C();
extern void sub_800B8B5C();

int dword_800B66C0 SDATA = 25;
const char aParelForest_800B66C4[] = "\202o\202\201\202\222\202\205\202\214\201@\202e\202\217\202\222\202\205\202\223\202\224"; // Parel Forest
const char aSyrus_800B66E0[12] = "\202r\202\231\202\222\202\225\202\223";
const char aForestGates_800B66EC[28] = "\202e\202\217\202\222\202\205\202\223\202\224\201@\202f\202\201\202\224\202\205\202\223";
const char aVillageSquare_800B6708[32] = "\202u\202\211\202\214\202\214\202\201\202\207\202\205\201@\202r\202\221\202\225\202\201\202\222\202\205";
const char aCemetery_800B6728[20] = "\202b\202\205\202\215\202\205\202\224\202\205\202\222\202\231";
const char aWenSHome_800B673C[24] = "\202v\202\205\202\216\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aMusaSHome_800B6754[24] = "\202l\202\225\202\223\202\201\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aNamSHome_800B676C[24] = "\202m\202\201\202\215\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aWatchtower_800B6784[24] = "\202v\202\201\202\224\202\203\202\210\202\224\202\217\202\227\202\205\202\222";
const char aSilkMill_800B679C[20] = "\202r\202\211\202\214\202\213\201@\202l\202\211\202\214\202\214";
const char aChiefSEstate_800B67B0[32] = "\202b\202\210\202\211\202\205\202\206\201f\202\223\201@\202d\202\223\202\224\202\201\202\224\202\205";
const char aTownShop_800B67D0[20] = "\202s\202\217\202\227\202\216\201@\202r\202\210\202\217\202\220";
const char aBlacksmith_800B67E4[24] = "\202a\202\214\202\201\202\203\202\213\202\223\202\215\202\211\202\224\202\210";
const char aGaraiSHome_800B67FC[28] = "\202f\202\201\202\222\202\201\202\211\201f\202\223\201@\202g\202\217\202\215\202\205";
const char aMyHome_800B6818[16] = "\202l\202\231\201@\202g\202\217\202\215\202\205";
const char aMothForest_800B6828[24] = "\202l\202\217\202\224\202\210\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aSpiderForest_800B6840[28] = "\202r\202\220\202\211\202\204\202\205\202\222\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aDragonflyForest_800B685C[36] = "\202c\202\222\202\201\202\207\202\217\202\216\202\206\202\214\202\231\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aBeetleForest_800B6880[28] = "\202a\202\205\202\205\202\224\202\214\202\205\201@\202e\202\217\202\222\202\205\202\223\202\224";
const char aBarrierGate_800B689C[28] = "\202a\202\201\202\222\202\222\202\211\202\205\202\222\201@\202f\202\201\202\224\202\205";
const int dword_800B68B8[14] = {
    0x30008, 0, 0, 0, 0x980010, 0x120074, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
const int dword_800B68F0[14] = {
    0x30008, 0, 0, 0, 0xAA0010, 0x120074, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
const int dword_800B6928[14] = {
    0x30008, 0, 0, 0, 0xBC0010, 0x120074, 0x20002, 1,
    0, 0, 0, -1, -1, -1,
};
const MapMenu name_800B6960 = { 2, 0, 8 };
const char name_800B6978[] = "\202o\202\222\202\217\202\203\202\205\202\205\202\204\201H"; // Proceed?
const char aYes_800B698C[] = "\202x\202\205\202\223"; // Yes
const MapWin name_800B6994 = {
    {
        0x30008, (int)aYes_800B698C, 0, 0, 0xB80072, 0x12002E, 0x20002, 1,
        0, 0, 0, -1, -1, -1,
    },
};
const char aNo_800B69CC[] = "\202m\202\217"; // No
const MapWin name_800B69D4 = {
    {
        0x30008, (int)aNo_800B69CC, 0, 0, 0xB800A0, 0x12002E, 0x20002, 1,
        0, 0, 0, -1, -1, -1,
    },
};
const char aField2_800B6A0C[16] = "\202e\202\211\202\205\202\214\202\204\202Q";
const char aField1_800B6A1C[16] = "\202e\202\211\202\205\202\214\202\204\202P";
const char aSyrus3_800B6A2C[16] = "\202r\202\231\202\222\202\225\202\223\202R";
const char aSyrus2_800B6A3C[16] = "\202r\202\231\202\222\202\225\202\223\202Q";
const char aSyrus1_800B6A4C[16] = "\202r\202\231\202\222\202\225\202\223\202P";
const char aOthers_800B6A5C[16] = "\202n\202\224\202\210\202\205\202\222\202\223";
const char aClear_800B6A6C[12] = "\202b\202\214\202\205\202\201\202\222";
const char aHunting_800B6A78[16] = "\202g\202\225\202\216\202\224\202\211\202\216\202\207";
const char aDream_800B6A88[12] = "\202c\202\222\202\205\202\201\202\215";
const char aDummy_800B6A94[12] = "\202c\202\225\202\215\202\215\202\231";
const char aOpening_800B6AA0[16] = "\202n\202\220\202\205\202\216\202\211\202\216\202\207";
const char aGuen_800B6AB0[12] = "\202f\202\225\202\205\202\216";
const char aMussa_800B6ABC[12] = "\202l\202\225\202\223\202\223\202\201";
const char aNam_800B6AC8[8] = "\202m\202\201\202\215";
const char aHiroba_800B6AD0[16] = "\202g\202\211\202\222\202\217\202\202\202\201";
const char aHakaba_800B6AE0[16] = "\202g\202\201\202\213\202\201\202\202\202\201";
const char aZokuchou_800B6AF0[20] = "\202y\202\217\202\213\202\225\202\203\202\210\202\217\202\225";
const char aMihari_800B6B04[16] = "\202l\202\211\202\210\202\201\202\222\202\211";
const char aMayu_800B6B14[12] = "\202l\202\201\202\231\202\225";
const char aDougu_800B6B20[12] = "\202c\202\217\202\225\202\207\202\225";
const char aKaji_800B6B2C[12] = "\202j\202\201\202\212\202\211";
const char aGarai_800B6B38[12] = "\202f\202\201\202\222\202\201\202\211";
const char aLebant_800B6B44[16] = "\202k\202\205\202\202\202\201\202\216\202\224";
const char aGa_800B6B54[8] = "\202f\202\201";
const char aKumo_800B6B5C[12] = "\202j\202\225\202\215\202\217";
const char aTombo_800B6B68[12] = "\202s\202\217\202\215\202\202\202\217";
const char aTamamusi_800B6B74[20] = "\202s\202\201\202\215\202\201\202\215\202\225\202\223\202\211";
const char aKekkai_800B6B88[16] = "\202j\202\205\202\213\202\213\202\201\202\211";
const char aSelKind_800B6B98[] = "\202r\202\205\202\214\201@\202\213\202\211\202\216\202\204"; // Sel kind
const char aSelSceneGroup_800B6BAC[] = "\202r\202\205\202\214\201@\202\223\202\203\202\205\202\216\202\205\201@\202\207\202\222\202\217\202\225\202\220"; // Sel scene group
const char aSelScene_800B6BCC[] = "\202r\202\205\202\214\201@\202\223\202\203\202\205\202\216\202\205"; // Sel scene
const char aSelChapter_800B6BE0[28] = "\202r\202\205\202\214\201@\202\203\202\210\202\201\202\220\202\224\202\205\202\222\201@\000\000im";

// Matched
void sub_800B6BFC(MapTask* t, int a1)
{
    void (*f)();
    dword_800B8C94.a = word_800AEBF8.a;
    dword_800B8C94.b = word_800AEBF8.b;
    sub_800B8448(&word_800AEBF8);
    f = sub_800B6C7C;
    t->next_8 = f;
    f(t, a1);
    t->flags_0 = (t->flags_0 | 4) & 0xFFFF7FFF;
}

// Matched
void sub_800B6C7C(MapTask* t)
{
    SetFadeMode_8001C19C(0, 0x20);
    t->next_8 = sub_800B6CB4;
}

// Matched
void sub_800B6CB4(MapTask* t)
{
    int a;
    dword_800B8CA4 = sub_800B7E54(word_800AEBF8.a);
    sub_800B7EE0();
    if (sub_800AD154(0xC) == 1)
    {
        a = 0xF;
    }
    else if (sub_800AD154(0xC) == 2)
    {
        a = 0x91;
    }
    else
    {
        a = dword_800B9220[word_800AEBF8.a].f10;
    }
    PlayMusic_800300E0(a, 1);
    dword_800B9434 = 0;
    sub_800B6D90(dword_800B9400, dword_800B9220[word_800AEBF8.a].f0);
    t->next_8 = sub_800B6E5C;
}

// Matched
void sub_800B6D90(FileRequestDesc* p, int a1)
{
    dword_800B9430 = 0;
    p->flags_0 = 0x2C;
    p->fileId_4 = a1;
    p->offset_8 = 0;
    p->size_C = 0;
    p->dest_10 = 0;
    p->params_14 = 0;
    p->paramsSize_18 = 0;
    p->callback_1C = sub_800B6DE0;
    QueueFileRequest_8003BC84(p);
}

// Matched
void sub_800B6DE0(MapTask* t, int* a1)
{
    sub_800B6FAC(t);
    if (dword_800B9434 == 1)
    {
        LoadTiy_80028E74(&dword_800B931C, 0, &dword_800B9320, a1, 1);
    }
    else
    {
        LoadTiy_80028E74(&dword_800B9314, 0, &dword_800B9318, a1, 1);
    }
    dword_800B9430 = 1;
}

// Matched
void sub_800B6E5C(MapTask* t)
{
    if (dword_800B9430)
    {
        t->next_8 = sub_800B6E80;
    }
}

// Matched
void sub_800B6E80(MapTask* t)
{
    dword_800B9434 = 1;
    sub_800B6D90(dword_800B9400, dword_800B9220[word_800AEBF8.a].f4);
    t->next_8 = sub_800B6EE8;
}

// Matched
void sub_800B6EE8(MapTask* t, int a1)
{
    if (dword_800B9430 && IsFadeDone_8001C2FC())
    {
        t->next_8 = sub_800B7044;
        ResetPadHoldFrames_8001CD04(0);
        t->next_8(t, a1);
        SetFadeMode_8001C19C(3, 0x20);
    }
}

// Matched
void sub_800B6F60(MapTask* t, int a1)
{
    sub_800B6FAC(t);
    t->flags_0 &= ~4;
    unknownFlags_8008D678 &= 0xFBFFFFFF;
}

// Matched
void sub_800B6FAC(MapTask* t)
{
    if (dword_800B9314)
    {
        free3_8003FC6C(dword_800B9314);
        dword_800B9314 = 0;
    }
    if (dword_800B9318)
    {
        free3_8003FC6C(dword_800B9318);
        dword_800B9318 = 0;
    }
    if (dword_800B931C)
    {
        free3_8003FC6C(dword_800B931C);
        dword_800B931C = 0;
    }
    if (dword_800B9320)
    {
        free3_8003FC6C(dword_800B9320);
        dword_800B9320 = 0;
    }
}

INCLUDE_OVERLAY_ASM(map, sub_800B7044);

// Matched
void sub_800B7948(MapTask* t)
{
    SetFadeMode_8001C19C(0, 0x20);
    t->next_8 = sub_800B7980;
}

// Not matched: register allocation of the table base (v0/v1 swapped)
void sub_800B7980(MapTask* t)
{
    MapPos q;
    MapElem* e;
    MapPos* w = &word_800AEBF8;
    int r = GetMenuCursorIndex_8003DA54(&dword_800AEBFC[w->a]);
    sub_800B8128((short)r, w->a, &q);
    dword_800B9434 = 0;
    e = dword_800B9220[word_800AEBF8.a].f14 + q.b;
    sub_800B6D90(dword_800B9400, e->f18);
    t->next_8 = sub_800B7A38;
}

// Matched
void sub_800B7A38(MapTask* t)
{
    if (dword_800B9430 && IsFadeDone_8001C2FC())
    {
        t->next_8 = sub_800B7A90;
        SetFadeMode_8001C19C(3, 0x20);
        word_800B932C = 0;
    }
}

// what DrawMenuWindows_8002A5A4 takes (struct_A5A4 in ability_menu.c)
extern DISPENV dispEnv_8008D750[2];
extern void name_800A75F8();
extern int MeasureTextWidth_8003E4C8(void* p);
extern void DrawUiColorWindow_800424C0(void* r, int a, void* ot, int b);
extern void DrawMenuWindows_8002A5A4(void* p);
extern void* memset(void* p, int c, unsigned int n);
extern void UpdateMenuCursor_8003D794(void* p, int a);
extern void sub_800B8338(MapPos* p);
extern void SetDrawMove(DR_MOVE* p, RECT* r, int x, int y);
void sub_800B7A90(MapTask* t, int a)
{
    MapPos q;
    DR_MOVE mv;
    RECT r0;
    RECT box;
    short tp[4];
    RECT box2;
    short tp2[4];
    MapWin w0;
    MapWin w1;
    MapWin* list[3];
    MapMenu m;
    int y;
    int wd;
    MapPos* w = &word_800AEBF8;
    sub_800B8128((short)GetMenuCursorIndex_8003DA54(&dword_800AEBFC[w->a]), w->a, &q);
    UpdateMenuCursor_8003D794(&name_800B9324, 0);
    if (display_8008B4D8.vsyncsPerFrame_4 == 1)
    {
        y = display_8008B4D8.field_A_y;
    }
    else
    {
        y = dispEnv_8008D750[bDoubleBuffer_8008D428 ^ 1].disp.y;
    }
    r0.x = 0x140;
    r0.w = 0x140;
    r0.y = 0;
    r0.h = 0xF0;
    SetDrawMove(&mv, &r0, 0, y);
    AddPrimCopy_80040298(pOT_8008D3EC, &mv, 6);
    wd = MeasureTextWidth_8003E4C8(dword_800B92FC[word_800AEBF8.a][word_800AEBF8.b]);
    box.x = 0x9E - (short)wd / 2;
    box.y = 0x12;
    box.w = wd + 4;
    box.h = 0x12;
    tp[0] = 0xA0 - (short)wd / 2;
    tp[1] = 0x16;
    DrawText_8003E91C(2, dword_800B92FC[word_800AEBF8.a][word_800AEBF8.b], tp, 0);
    DrawUiColorWindow_800424C0(&box, 0, pOT_8008D454, 0);
    box2.x = 0x74;
    box2.y = 0xA6;
    box2.w = 0x58;
    box2.h = 0x12;
    tp2[0] = 0x76;
    tp2[1] = 0xA8;
    tp2[0] = 0x86;
    tp2[1] = 0xAA;
    DrawText_8003E91C(2, name_800B6978, tp2, 0);
    DrawUiColorWindow_800424C0(&box2, 0, pOT_8008D454, 0);
    w0 = name_800B6994;
    w1 = name_800B69D4;
    memset(list, 0, 0xC);
    m = name_800B6960;
    list[0] = &w0;
    list[1] = &w1;
    m.time_4 = GetTime30Hz_8002C64C();
    m.windows_10 = list;
    m.sel_C = name_800B9324.s8;
    DrawMenuWindows_8002A5A4(&m);
    if (IsConfirmPressedP1_8003D380(1))
    {
        if ((short)GetMenuCursorIndex_8003DA54(&name_800B9324) == 0)
        {
            sub_800B8338(&word_800AEBF8);
            sub_800B6F60(t, a);
            t->next_8 = name_800A75F8;
        }
        else
        {
            t->next_8 = sub_800B6C7C;
        }
    }
    else if (IsCancelPressedP1_8003D41C(1))
    {
        t->next_8 = sub_800B6C7C;
    }
}

// Matched
int sub_800B7E54(short a)
{
    int i;
    int cnt = 0;
    MapPos pos;
    pos.a = a;
    for (i = 0; i < word_800B8C98[a]; i++)
    {
        pos.b = i;
        if (sub_800B8290(&pos))
        {
            cnt++;
        }
    }
    return cnt;
}

// Matched
void sub_800B7EE0()
{
    MapPos q;
    int r;
    int n;
    int k;
    if (dword_800B8CA4 < 4)
    {
        SEL.s2 = dword_800B8CA4;
        SEL.s6 = 0;
    }
    else
    {
        SEL.s2 = 3;
        SEL.s6 = 0x40;
    }
    SEL.s4 = dword_800B8CA4;
    if (word_800AEBF8.a != dword_800B8C94.a || word_800AEBF8.b != dword_800B8C94.b)
    {
        SEL.s8 = 0;
        SEL.sA = 0;
    }
    else
    {
        r = GetMenuCursorIndex_8003DA54(&SEL);
        sub_800B8128((short)r, word_800AEBF8.a, &q);
        if (!sub_800B8290(&q))
        {
            SEL.s8 = 0;
            SEL.sA = 0;
        }
        else
        {
            n = sub_800B81D0(&word_800AEBF8);
            if (dword_800B8CA4 < 4)
            {
                SEL.s8 = n;
                SEL.sA = 0;
            }
            else
            {
                k = (unsigned short)dword_800B8CA4 - 3;
                if ((short)k < SEL.sA)
                {
                    SEL.s8 = n - k;
                    SEL.sA = k;
                }
            }
        }
    }
}

// Matched
void sub_800B8128(short a, short b, MapPos* out)
{
    int cnt = 0;
    int i;
    out->a = b;
    for (i = 0; i < word_800B8C98[b]; i++)
    {
        out->b = i;
        if (sub_800B8290(out))
        {
            if (cnt++ == a)
            {
                break;
            }
        }
    }
}

int sub_800B81D0(MapPos* p)
{
    int i;
    short cnt = 0;
    MapPos q;
    q.a = p->a;
    for (i = 0; i < word_800B8C98[p->a]; i++)
    {
        q.b = i;
        if (sub_800B8290(&q))
        {
            cnt++;
            if (q.b == p->b)
            {
                break;
            }
        }
    }
    return cnt;
}

// Matched
int sub_800B8290(MapPos* p)
{
    int idx = p->a;
    unsigned char c = dword_800B9348[idx][p->b];
    MapQuery q;
    int r;
    if (c == 0xFF)
    {
        return sub_800AD0D4(1) != 0;
    }
    if (c == 0xFE)
    {
        return 1;
    }
    if (c >= 0xF0)
    {
        c += 0x11;
    }
    q.a = dword_800B9360[idx];
    q.b = c;
    q.c = 0;
    r = sub_800ADC1C(&q);
    return r != -1;
}

void sub_800B8338(MapPos* p)
{
    unsigned char c = dword_800B9348[p->a][p->b];
    if (c == 0xFE || c == 0xFF)
    {
        saveData_8008B570.mapId_2E4[0].field_0 = 4;
        saveData_8008B570.mapId_2E4[1].field_0 = 0;
        saveData_8008B570.mapId_2E4[2].field_0 = 0;
        saveData_8008B570.mapId_2E4[2].field_2 = -1;
    }
    else if (c >= 0xF0)
    {
        sub_800AD16C(4, c - 0xEF);
        saveData_8008B570.mapId_2E4[0].field_0 = 4;
        saveData_8008B570.mapId_2E4[1].field_0 = 0;
        saveData_8008B570.mapId_2E4[2].field_0 = 0;
        saveData_8008B570.mapId_2E4[2].field_2 = -1;
    }
    else
    {
        saveData_8008B570.mapId_2E4[0].field_0 = dword_800B9360[p->a];
        saveData_8008B570.mapId_2E4[1].field_0 = dword_800B9348[p->a][p->b];
        saveData_8008B570.mapId_2E4[2].field_0 = 0;
        saveData_8008B570.mapId_2E4[2].field_2 = -1;
    }
    sub_800A8DEC();
    SetFadeMode_8001C19C(0, 0x20);
    sub_800A6D30(1);
    useMapStartPos_80091C94 = 1;
    eventDispatchHalt_8008B540 = 1;
}

// Matched
void sub_800B8448(MapPos* out)
{
    unsigned short t = saveData_8008B570.mapId_2E4[0].field_0;
    MapQuery q;
    unsigned char* tbl;
    unsigned char cnt;
    if ((unsigned short)(t - 4) < 2)
    {
        if (saveData_8008B570.mapId_2E4[1].field_0 == 0)
        {
            int f = saveData_8008B570.field_2E0;
            out->b = 12;
            out->a = f == 1;
            return;
        }
        q.a = t;
        q.c = 0;
        q.b = 1;
        do
        {
            if (sub_800ADC1C(&q) == -1)
            {
                break;
            }
            q.b++;
        } while (q.b < 5);
        if (q.b == 5)
        {
            q.b--;
        }
        out->a = q.b + 1;
    }
    else if ((unsigned short)(t - 1) >= 3)
    {
        int f = saveData_8008B570.field_2E0;
        out->b = 0;
        out->a = f == 1;
        return;
    }
    else
    {
        out->a = saveData_8008B570.field_2E0 == 1;
    }
    tbl = dword_800B9348[out->a];
    cnt = dword_800B9368[out->a];
    for (out->b = 0; out->b < cnt; out->b++)
    {
        if (saveData_8008B570.mapId_2E4[1].field_0 == tbl[out->b])
        {
            return;
        }
    }
    out->b = 0;
}

// Matched
void sub_800B85CC(MapTask* t)
{
    MapSelState* p;
    void (*f)() = sub_800B860C;
    dword_800B9420.step_0 = 0;
    p = &dword_800B9420;
    p->area_4 = 0;
    p->map_8 = 0;
    p->entry_C = 0;
    t->next_8 = f;
    f();
}

void sub_800B860C()
{
    MapSelState* m = &dword_800B9420;
    int a = m->area_4;
    int b = m->map_8;
    MapEntry* list = mapTable_800B0608[a][b];
    RECT r1;
    RECT r2;
    RECT r3;
    int y;
    int i;
    int n;
    int d;
    char* str;
    int v;
    int c;
    switch (m->step_0)
    {
    case 0:
        if (padRepeat_800918CC & 0x1000)
        {
            m->area_4 = a - 1;
        }
        else if (padRepeat_800918CC & 0x4000)
        {
            m->area_4 = a + 1;
        }
        m->area_4 = m->area_4 < 0 ? 0 : m->area_4 < 6 ? m->area_4 : 5;
        if (IsConfirmPressedP1_8003D380(1) == 1)
        {
            m->step_0++;
        }
        r1.x = 0x1E;
        r1.y = 0x14;
        DrawText_8003E91C(2, aSelKind_800B6B98, &r1, 0);
        for (i = 0; i < 6; i++)
        {
            str = dword_800B9370[i];
            d = i == m->area_4 ? (frameCount_8008D3FC & 0xF) : 0;
            r2.x = 0x1E + d;
            r2.y = 0x32 + i * 14;
            DrawText_8003E91C(2, str, &r2, 0);
        }
        if (frameCount_8008D3FC & 3)
        {
            r2.x = 0x1E;
            r2.y = m->area_4 * 14 + 0x32;
            DrawCursorHand_8003D034(&r2, 0);
        }
        break;
    case 1:
        if (padRepeat_800918CC & 0x1000)
        {
            m->map_8 = b - 1;
        }
        else if (padRepeat_800918CC & 0x4000)
        {
            m->map_8 = b + 1;
        }
        m->map_8 = m->map_8 < 0 ? 0 : (dword_800B0624[m->area_4] - 1 < m->map_8 ? dword_800B0624[m->area_4] - 1 : m->map_8);
        if (IsConfirmPressedP1_8003D380(1) == 1)
        {
            m->step_0++;
        }
        else if (IsCancelPressedP1_8003D41C(1) == 1)
        {
            m->map_8 = 0;
            m->step_0--;
        }
        r2.x = 0x1E;
        r2.y = 0x14;
        DrawText_8003E91C(2, aSelSceneGroup_800B6BAC, &r2, 0);
        for (i = 0; i < dword_800B0624[m->area_4]; i++)
        {
            str = dword_800B93E0[m->area_4][i];
            d = i == m->map_8 ? (frameCount_8008D3FC & 0xF) : 0;
            r3.x = 0x1E + d;
            r3.y = 0x32 + i * 14;
            DrawText_8003E91C(2, str, &r3, 0);
        }
        if (frameCount_8008D3FC & 3)
        {
            r3.x = 0x1E;
            r3.y = m->map_8 * 14 + 0x32;
            DrawCursorHand_8003D034(&r3, 0);
        }
        break;
    case 2:
        if (padRepeat_800918CC & 0x1000)
        {
            m->entry_C--;
        }
        else if (padRepeat_800918CC & 0x4000)
        {
            m->entry_C++;
        }
        n = 0;
        while (list[n].id != -1)
        {
            n++;
        }
        m->entry_C = m->entry_C < 0 ? 0 : (n - 1 < m->entry_C ? n - 1 : m->entry_C);
        if (IsConfirmPressedP1_8003D380(1) == 1)
        {
            saveData_8008B570.field_2E0 = dword_800B93F8[m->area_4];
            saveData_8008B570.mapId_2E4[0].field_0 = m->area_4;
            saveData_8008B570.mapId_2E4[1].field_0 = m->map_8;
            saveData_8008B570.mapId_2E4[2].field_0 = m->entry_C;
            saveData_8008B570.field_2E2 = -1;
            saveData_8008B570.mapId_2E4[0].field_2 = -1;
            saveData_8008B570.mapId_2E4[1].field_2 = -1;
            saveData_8008B570.mapId_2E4[2].field_2 = -1;
            useMapStartPos_80091C94 = 1;
            dword_80091C54 = 0;
            sub_800A8DEC();
            sub_800A6D30(1);
            SetFadeMode_8001C19C(0, 0x20);
            eventDispatchHalt_8008B540 = 1;
        }
        else if (IsCancelPressedP1_8003D41C(1) == 1)
        {
            m->entry_C = 0;
            m->step_0--;
        }
        r3.x = 0x1E;
        r3.y = 0x14;
        DrawText_8003E91C(2, aSelScene_800B6BCC, &r3, 0);
        break;
    }
}


// Matched
void sub_800B8B2C(MapTask* t)
{
    void (*f)() = sub_800B8B5C;
    dword_800B9438 = 0;
    t->next_8 = f;
    f();
}

void sub_800B8B5C()
{
    int* sel = &dword_800B9438;
    unsigned short pad = padRepeat_800918CC;
    RECT a;
    RECT b;
    RECT c;
    int r;
    if (pad & 0x1000)
    {
        dword_800B9438--;
    }
    else if (pad & 0x4000)
    {
        dword_800B9438++;
    }
    *sel = *sel < 0 ? 0 : *sel < 7 ? *sel : 6;
    r = IsConfirmPressedP1_8003D380(1);
    if (r == 1)
    {
        SaveData* sv = &saveData_8008B570;
        sv->chapterNext_2DE = -5;
        sv->chapter_2DC = *sel;
        sub_800A6D30(0);
        eventDispatchHalt_8008B540 = r;
    }
    IsCancelPressedP1_8003D41C(1);
    a.x = 0x6E;
    a.y = 0x78;
    b.x = a.x + 10;
    b.y = a.y + 10;
    DrawText_8003E91C(2, aSelChapter_800B6BE0, &b, 0);
    c.x = a.x + 0x50;
    c.y = a.y + 0xA;
    DrawNumber_8003EF74(&c, *sel + 1, 0);
}

MapPos dword_800B8C94 = { -1, -1 };
short word_800B8C98[6] = { 13, 13, 3, 4, 5, 6 };
int dword_800B8CA4 = 0;
MapElem dword_800B8CA8[13] = {
    { { 8, 0, 0, 0, 12, 0, 18, 0, 1, 0, 0, 0, 246, 0, 166, 0, 32, 64, 64, 0, 64, 128, 128 }, 62 },
    { { 6, 0, 0, 0, 12, 0, 18, 0, 1, 0, 0, 0, 182, 0, 201, 0, 32, 64, 64, 0, 64, 128, 128 }, 63 },
    { { 0, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 140, 0, 109, 0, 32, 64, 64, 0, 64, 128, 128 }, 64 },
    { { 3, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 101, 0, 130, 0, 32, 64, 64, 0, 64, 128, 128 }, 65 },
    { { 4, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 64, 0, 90, 0, 32, 64, 64, 0, 64, 128, 128 }, 68 },
    { { 7, 0, 0, 0, 12, 0, 18, 0, 1, 0, 0, 0, 204, 0, 133, 0, 32, 64, 64, 0, 64, 128, 128 }, 66 },
    { { 12, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 39, 1, 186, 0, 32, 64, 64, 0, 64, 128, 128 }, 67 },
    { { 9, 0, 0, 0, 12, 0, 18, 0, 1, 0, 0, 0, 184, 0, 116, 0, 32, 64, 64, 0, 64, 128, 128 }, 71 },
    { { 10, 0, 0, 0, 12, 0, 18, 0, 1, 0, 0, 0, 184, 0, 80, 0, 32, 64, 64, 0, 64, 128, 128 }, 72 },
    { { 11, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 98, 0, 73, 0, 32, 64, 64, 0, 64, 128, 128 }, 73 },
    { { 13, 0, 0, 0, 12, 0, 18, 0, 1, 0, 0, 0, 243, 0, 87, 0, 32, 64, 64, 0, 64, 128, 128 }, 69 },
    { { 2, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 120, 0, 98, 0, 32, 64, 64, 0, 64, 128, 128 }, 70 },
    { { 5, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 10, 1, 226, 0, 32, 64, 64, 0, 64, 128, 128 }, 74 },
};
MapElem dword_800B8E14[13] = {
    { { 3, 0, 0, 0, 12, 0, 18, 0, 12, 0, 0, 0, 246, 0, 166, 0, 32, 64, 64, 0, 64, 128, 128 }, 77 },
    { { 2, 0, 0, 0, 12, 0, 18, 0, 12, 0, 0, 0, 182, 0, 201, 0, 32, 64, 64, 0, 64, 128, 128 }, 78 },
    { { 8, 0, 0, 0, 216, 0, 18, 0, 12, 0, 0, 0, 140, 0, 109, 0, 32, 64, 64, 0, 64, 128, 128 }, 79 },
    { { 10, 0, 0, 0, 216, 0, 18, 0, 12, 0, 0, 0, 101, 0, 130, 0, 32, 64, 64, 0, 64, 128, 128 }, 80 },
    { { 11, 0, 0, 0, 216, 0, 18, 0, 12, 0, 0, 0, 64, 0, 90, 0, 32, 64, 64, 0, 64, 128, 128 }, 83 },
    { { 1, 0, 0, 0, 12, 0, 18, 0, 12, 0, 0, 0, 204, 0, 133, 0, 32, 64, 64, 0, 64, 128, 128 }, 81 },
    { { 4, 0, 0, 0, 216, 0, 18, 0, 12, 0, 0, 0, 39, 1, 186, 0, 32, 64, 64, 0, 64, 128, 128 }, 82 },
    { { 5, 0, 0, 0, 12, 0, 18, 0, 12, 0, 0, 0, 184, 0, 116, 0, 32, 64, 64, 0, 64, 128, 128 }, 86 },
    { { 6, 0, 0, 0, 12, 0, 18, 0, 12, 0, 0, 0, 184, 0, 80, 0, 32, 64, 64, 0, 64, 128, 128 }, 87 },
    { { 7, 0, 0, 0, 216, 0, 18, 0, 12, 0, 0, 0, 98, 0, 73, 0, 32, 64, 64, 0, 64, 128, 128 }, 88 },
    { { 13, 0, 0, 0, 12, 0, 18, 0, 12, 0, 0, 0, 243, 0, 87, 0, 32, 64, 64, 0, 64, 128, 128 }, 84 },
    { { 9, 0, 0, 0, 216, 0, 18, 0, 12, 0, 0, 0, 120, 0, 98, 0, 32, 64, 64, 0, 64, 128, 128 }, 85 },
    { { 0, 0, 0, 0, 216, 0, 18, 0, 12, 0, 0, 0, 10, 1, 226, 0, 32, 64, 64, 0, 64, 128, 128 }, 89 },
};
MapElem dword_800B8F80[6] = {
    { { 5, 0, 0, 0, 216, 0, 18, 0, 0, 0, 0, 0, 115, 0, 63, 0, 32, 16, 0, 0, 128, 32 }, 60 },
    { { 4, 0, 0, 0, 216, 0, 18, 0, 1, 0, 0, 0, 156, 0, 103, 0, 16, 24, 24, 0, 16, 96, 96 }, 98 },
    { { 3, 0, 0, 0, 216, 0, 18, 0, 2, 0, 0, 0, 202, 0, 149, 0, 24, 24, 0, 0, 64, 64 }, 99 },
};
MapElem dword_800B9028[6] = {
    { { 4, 0, 0, 0, 216, 0, 18, 0, 2, 0, 0, 0, 170, 0, 72, 0, 32, 16, 0, 0, 128, 32 }, 60 },
    { { 5, 0, 0, 0, 216, 0, 18, 0, 3, 0, 0, 0, 196, 0, 96, 0, 16, 24, 24, 0, 16, 96, 96 }, 98 },
    { { 1, 0, 0, 0, 216, 0, 18, 0, 6, 0, 0, 0, 228, 0, 132, 0, 24, 24, 0, 0, 64, 64 }, 99 },
    { { 0, 0, 0, 0, 216, 0, 18, 0, 7, 0, 0, 0, 67, 0, 92, 0, 0, 16, 16, 0, 0, 80, 80 }, 101 },
};
MapElem dword_800B90D0[6] = {
    { { 3, 0, 0, 0, 216, 0, 18, 0, 5, 0, 0, 0, 135, 0, 52, 0, 32, 16, 0, 0, 128, 32 }, 60 },
    { { 4, 0, 0, 0, 216, 0, 18, 0, 6, 0, 0, 0, 157, 0, 74, 0, 16, 24, 24, 0, 16, 96, 96 }, 98 },
    { { 2, 0, 0, 0, 216, 0, 18, 0, 7, 0, 0, 0, 184, 0, 103, 0, 24, 24, 0, 0, 64, 64 }, 99 },
    { { 0, 0, 0, 0, 216, 0, 18, 0, 8, 0, 0, 0, 53, 0, 72, 0, 0, 16, 16, 0, 0, 80, 80 }, 101 },
    { { 1, 0, 0, 0, 216, 0, 18, 0, 9, 0, 0, 0, 244, 0, 155, 0, 24, 0, 24, 0, 96, 0, 96 }, 100 },
};
MapElem dword_800B9178[6] = {
    { { 0, 0, 0, 0, 216, 0, 18, 0, 6, 0, 0, 0, 142, 0, 86, 0, 32, 16, 0, 0, 128, 32 }, 60 },
    { { 1, 0, 0, 0, 216, 0, 18, 0, 7, 0, 0, 0, 164, 0, 108, 0, 16, 24, 24, 0, 16, 96, 96 }, 98 },
    { { 5, 0, 0, 0, 216, 0, 18, 0, 8, 0, 0, 0, 188, 0, 135, 0, 24, 24, 0, 0, 64, 64 }, 99 },
    { { 2, 0, 0, 0, 216, 0, 18, 0, 9, 0, 0, 0, 66, 0, 109, 0, 0, 16, 16, 0, 0, 80, 80 }, 101 },
    { { 3, 0, 0, 0, 216, 0, 18, 0, 10, 0, 0, 0, 239, 0, 179, 0, 24, 0, 24, 0, 96, 0, 96 }, 100 },
    { { 4, 0, 0, 0, 216, 0, 18, 0, 11, 0, 0, 0, 160, 0, 22, 0, 32, 16, 16, 0, 96, 32, 32 }, 102 },
};
MapRow dword_800B9220[6] = {
    { 60, 61, (int)aSyrus_800B66E0, 0x1400A0, 14, dword_800B8CA8 },
    { 75, 76, (int)aSyrus_800B66E0, 0x1400A0, 13, dword_800B8E14 },
    { 90, 91, (int)aParelForest_800B66C4, 0x140032, 29, dword_800B8F80 },
    { 92, 93, (int)aParelForest_800B66C4, 0x140032, 29, dword_800B9028 },
    { 94, 95, (int)aParelForest_800B66C4, 0x140032, 29, dword_800B90D0 },
    { 96, 97, (int)aParelForest_800B66C4, 0x140032, 29, dword_800B9178 },
};
char *dword_800B92B0[13] = {
    aMyHome_800B6818, aGaraiSHome_800B67FC, aBlacksmith_800B67E4, aTownShop_800B67D0,
    aChiefSEstate_800B67B0, aSilkMill_800B679C, aWatchtower_800B6784, aNamSHome_800B676C,
    aMusaSHome_800B6754, aWenSHome_800B673C, aCemetery_800B6728, aVillageSquare_800B6708,
    aForestGates_800B66EC,
};
char *dword_800B92E4[6] = { aSyrus_800B66E0, aBarrierGate_800B689C, aBeetleForest_800B6880, aDragonflyForest_800B685C, aSpiderForest_800B6840, aMothForest_800B6828 };
char **dword_800B92FC[6] = { dword_800B92B0, dword_800B92B0, dword_800B92E4, dword_800B92E4, dword_800B92E4, dword_800B92E4 };
SPRT *dword_800B9314 = 0;
DR_TPAGE *dword_800B9318 = 0;
SPRT *dword_800B931C = 0;
DR_TPAGE *dword_800B9320 = 0;
MapSel name_800B9324 = { 2, 1, 2, 1 };
unsigned char dword_800B9330[16] = { 0, 1, 2, 3, 6, 4, 5, 9, 10, 11, 7, 8, 255 };
unsigned char dword_800B9340[8] = { 254, 0, 240, 241, 242, 243 };
unsigned char *dword_800B9348[6] = { dword_800B9330, dword_800B9330, dword_800B9340, dword_800B9340, dword_800B9340, dword_800B9340 };
unsigned char dword_800B9360[8] = { 1, 2, 4, 4, 4, 4 };
unsigned char dword_800B9368[8] = { 13, 13, 6, 6, 6, 6 };
char *dword_800B9370[6] = { aOthers_800B6A5C, aSyrus1_800B6A4C, aSyrus2_800B6A3C, aSyrus3_800B6A2C, aField1_800B6A1C, aField2_800B6A0C };
char *dword_800B9388[5] = { aOpening_800B6AA0, aDummy_800B6A94, aDream_800B6A88, aHunting_800B6A78, aClear_800B6A6C };
char *dword_800B939C[12] = {
    aLebant_800B6B44, aGarai_800B6B38, aKaji_800B6B2C, aDougu_800B6B20,
    aMayu_800B6B14, aMihari_800B6B04, aZokuchou_800B6AF0, aHakaba_800B6AE0,
    aHiroba_800B6AD0, aNam_800B6AC8, aMussa_800B6ABC, aGuen_800B6AB0,
};
char *dword_800B93CC[5] = { aKekkai_800B6B88, aTamamusi_800B6B74, aTombo_800B6B68, aKumo_800B6B5C, aGa_800B6B54 };
char **dword_800B93E0[6] = { dword_800B9388, dword_800B939C, dword_800B939C, dword_800B939C, dword_800B93CC, dword_800B93CC };
unsigned char dword_800B93F8[8] = { 0, 0, 1, 2, 0, 2 };
FileRequestDesc dword_800B9400[1] = { { 0 } };
MapSelState dword_800B9420 = { 0 };
int dword_800B9430 = 0;
int dword_800B9434 = 0;
int dword_800B9438 = 0;
