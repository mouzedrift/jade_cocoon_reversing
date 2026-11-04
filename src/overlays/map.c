// MAP.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct MapTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} MapTask;

typedef struct MapElem
{
    char pad_0[0x18];
    int f18;
} MapElem;

typedef struct MapRow
{
    int f0;
    int f4;
    int f8;
    int fc;
    int f10;
    MapElem* f14;
} MapRow;

typedef struct MapPos
{
    short a;
    short b;
} MapPos;

typedef struct MapQuery
{
    short a;
    short b;
    short c;
} MapQuery;

extern unsigned char* dword_800B9348[];
extern unsigned char dword_800B9360[];
extern short word_800B8C98[];
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
extern char dword_800B6B98[];
extern char dword_800B6BAC[];
extern char dword_800B6BCC[];
extern char* dword_800B9370[];
extern char** dword_800B93E0[];
extern unsigned char dword_800B93F8[];
extern int dword_80091C54;
extern void sub_8003D034(void*, int);
#define SEL dword_800AEBFC[word_800AEBF8.a]
extern int GetMenuCursorIndex_8003DA54(void*);
extern void sub_800A8DEC();
extern void sub_800A6D30(int);
extern void sub_800AD16C(int, int);
extern int useMapStartPos_80091C94;
typedef struct MapSel
{
    short s0;
    short s2;
    short s4;
    short s6;
    short s8;
    short sA;
} MapSel;

extern MapSel dword_800AEBFC[];
extern unsigned short padRepeat_800918CC;
extern char dword_800B6BE0[];
extern void DrawText_8003E91C(int, void*, void*, int);
extern void DrawNumber_8003EF74(void*, int, int);
extern int dword_800B9438;
extern unsigned char dword_800B9368[];
extern int dword_800B8CA4;
extern int sub_800AD154(int);
extern void PlayMusic_800300E0(int, int);
extern void sub_800B6E5C();
extern int sub_800B81D0(MapPos*);
extern int dword_800B9430;
extern SPRT* dword_800B9314; // map TIY sprites / tpages (sub_800B6DE0)
extern DR_TPAGE* dword_800B9318;
extern SPRT* dword_800B931C;
extern DR_TPAGE* dword_800B9320;
extern int dword_800B9434;
extern int dword_800B9438;
// state of the map select (sub_800B860C)
typedef struct MapSelState
{
    int step_0;
    int area_4;
    int map_8;
    int entry_C;
} MapSelState;
extern MapSelState dword_800B9420;
extern FileRequestDesc dword_800B9400[];
extern MapRow dword_800B9220[];
extern MapPos word_800AEBF8;  // the selected destination (GAME data)
extern MapPos dword_800B8C94; // the one selected when the menu opened
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

INCLUDE_OVERLAY_ASM(map, dword_800B66C0);

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

typedef struct MapWin
{
    int w[14];
} MapWin;
// what DrawMenuWindows_8002A5A4 takes (struct_A5A4 in tu_8002CE28.c)
typedef struct MapMenu
{
    int f0;
    int time_4;
    int f8;
    int sel_C;
    MapWin** windows_10;
    int f14;
} MapMenu;
extern DISPENV dispEnv_8008D750[2];
extern char** dword_800B92FC[];
extern char name_800B6978[];
extern MapWin name_800B6994;
extern MapWin name_800B69D4;
extern MapMenu name_800B6960;
extern MapSel name_800B9324;
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
        DrawText_8003E91C(2, dword_800B6B98, &r1, 0);
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
            sub_8003D034(&r2, 0);
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
        DrawText_8003E91C(2, dword_800B6BAC, &r2, 0);
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
            sub_8003D034(&r3, 0);
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
        DrawText_8003E91C(2, dword_800B6BCC, &r3, 0);
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
    DrawText_8003E91C(2, dword_800B6BE0, &b, 0);
    c.x = a.x + 0x50;
    c.y = a.y + 0xA;
    DrawNumber_8003EF74(&c, *sel + 1, 0);
}

INCLUDE_OVERLAY_ASM(map, dword_800B8C94);
