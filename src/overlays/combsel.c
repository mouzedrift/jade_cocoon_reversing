// COMBSEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "combsel.h"

typedef struct CombSelTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombSelTask;

typedef struct CombSelUnit
{
    char pad_0[0xF8];
} CombSelUnit;

typedef struct CombSelItem
{
    char pad_0[0x10];
    short field_10;
} CombSelItem;

extern unsigned char byte_800A38D9;
extern void sub_800A4E4C();
typedef struct CombSelState
{
    char pad_0[8];
    short field_8;
} CombSelState;

extern CombSelState dword_800A1BBC;
extern CombSelUnit dword_800A1BC8[][15];
extern short word_800A1BC4;
extern CombSelUnit dword_800A3AA0[2][3];
extern int dword_800A3A94;
extern unsigned char byte_800A38DB;
extern void sub_800A16FC();
extern int sub_800A1934(void*);
extern void sub_800A4D64(CombSelUnit*);
extern void sub_800A197C(void*);
extern void sub_800A5538();
extern int sub_800A5560(CombSelUnit*, int);
extern int GetMenuCursorIndex_8003DA54(void*);
extern void PlaySfx_80031494(int);

int dword_800A4088 SDATA = 19;
const char aReturnToTitleSc_800A408C[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201D"; // Return to title screen.
const char aDeleteEnteredMi_800A40BC[] = "\202c\202\205\202\214\202\205\202\224\202\205\201@\202\205\202\216\202\224\202\205\202\222\202\205\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // Delete entered minion.
const char aEnterMinionFrom_800A40EC[] = "\202d\202\216\202\224\202\205\202\222\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\206\202\222\202\217\202\215\201@\202\214\202\211\202\223\202\224\201D"; // Enter minion from list.
const char aReadMinionDataF_800A411C[] = "\202q\202\205\202\201\202\204\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\204\202\201\202\224\202\201\201@\202\206\202\222\202\217\202\215\201@\202l\202d\202l\202n\202q\202x\201@\202b\202`\202q\202c\201D"; // Read minion data from MEMORY CARD.
const char aReturnToTitleSc_800A4164[] = "\202q\202\205\202\224\202\225\202\222\202\216\201@\202\224\202\217\201@\202\224\202\211\202\224\202\214\202\205\201@\202\223\202\203\202\222\202\205\202\205\202\216\201H"; // Return to title screen?
const char aEnterPlayer2SMi_800A4194[] = "\202d\202\216\202\224\202\205\202\222\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201f\202\223\201@\202\215\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // Enter Player 2's minions.
const char aStartFighting_800A41C8[] = "\202r\202\224\202\201\202\222\202\224\201@\202\206\202\211\202\207\202\210\202\224\202\211\202\216\202\207\201D"; // Start fighting.
const char aEnterPlayer2SMi_800A41E8[] = "\202d\202\216\202\224\202\205\202\222\201@\202o\202\214\202\201\202\231\202\205\202\222\201@\202Q\201f\202\223\201@\202l\202\211\202\216\202\211\202\217\202\216\202\223\201D"; // Enter Player 2's Minions.
const char aQuit_800A421C[] = "\202p\202\225\202\211\202\224"; // Quit
const char aSelect_800A4228[] = "\202r\202\205\202\214\202\205\202\203\202\224"; // Select
const int dword_800A4238[7] = { 0x10008, 15, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x14006A, 0x12006C, 0x20002 };
const int dword_800A4254[14] = {
    0x10008, 0, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x14000A, 0x12004D, 0x20002, 0x10010,
    1, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x27000A, 0x130090, 0x20002,
};
const int dword_800A428C[7] = { 0x10008, 1, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x37009B, 0x120032, 0x20002 };
const char aSelectSpaceToEn_800A42A8[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\223\202\220\202\201\202\203\202\205\201@\202\224\202\217\201@\202\205\202\216\202\224\202\205\202\222\201@\202\215\202\211\202\216\202\211\202\217\202\216\201D"; // Select space to enter minion.
const char aSelectMinionToD_800A42E4[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\224\202\217\201@\202\204\202\205\202\214\202\205\202\224\202\205\201D"; // Select minion to delete.
const char aSelectMinionToE_800A4318[] = "\202r\202\205\202\214\202\205\202\203\202\224\201@\202\215\202\211\202\216\202\211\202\217\202\216\201@\202\224\202\217\201@\202\205\202\216\202\224\202\205\202\222\201D"; // Select minion to enter.
const int dword_800A4348 = 0;

INCLUDE_OVERLAY_ASM(combsel, sub_800A4360);

void sub_800A4C74()
{
    short v[2];
    int i;
    for (i = 0; i < 3; i++)
    {
        v[0] = 0xA;
        v[1] = 0xA6;
        dword_800A566C[i][8] = v[*(volatile unsigned char*)&byte_800A38D9];
    }
    for (i = 0; i < 6; i++)
    {
        v[0] = 0x9B;
        v[1] = 0x15;
        dword_800A57E4[i][8] = v[*(volatile unsigned char*)&byte_800A38D9];
    }
    for (i = 0; i < 5; i++)
    {
        v[0] = 0xA;
        v[1] = 0xCA;
        dword_800A5930[i][8] = v[*(volatile unsigned char*)&byte_800A38D9];
    }
}

void sub_800A4D64(CombSelUnit* base)
{
    int i;
    int j;
    for (i = 0; i < 2; i++)
    {
        if (sub_800A1934(&base[i]) == 1)
        {
            for (j = i + 1; j < 3; j++)
            {
                if (sub_800A1934(&base[j]) == 0)
                {
                    MemCopy_800403E8(&base[i], &base[j], 0xF8);
                    sub_800A197C(&base[j]);
                    break;
                }
            }
            if (j >= 3)
            {
                return;
            }
        }
    }
}

void sub_800A4E4C()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        sub_800A4D64(dword_800A3AA0[i]);
    }
}


void sub_800A4E94(CombSelTask* t, int a)
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 0:
            PlaySfx_80031494(0x7E);
            t->next_8 = sub_800A16FC;
            t->next_8(t, a);
            break;
        case 1:
            if (sub_800A5560(dword_800A1BC8[byte_800A38D9], 6) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                byte_800A38DB = 2;
            }
            break;
        case 2:
            if (sub_800A5560(dword_800A3AA0[byte_800A38D9], 3) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                byte_800A38DB = 1;
            }
            break;
        case 3:
            sub_800A5080(t, a);
            break;
        case 4:
            PlaySfx_80031494(0x7E);
            byte_800A38DB = 3;
            word_800A5980 = 1;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        switch (byte_800A38D9)
        {
        case 0:
            word_800A1BC4 = 4;
            break;
        case 1:
            word_800A1BC4 = 1;
            word_800A5968 = 0;
            byte_800A38D9 = 0;
            word_800A5974 = 0;
            break;
        }
    }
}

// Near miss: store order of the case 0 assignments
#if 0
void sub_800A5080(CombSelTask* t, int a)
{
    if (sub_800A5560(dword_800A3AA0[byte_800A38D9], 3) == 1)
    {
        PlaySfx_80031494(0x7C);
    }
    else
    {
        byte_800A38DB = 0;
        dword_800A1BBC.field_8 = 3;
        PlaySfx_80031494(0x7E);
        switch (byte_800A38D9)
        {
        case 0:
            dword_800A1BBC.field_8 = 0;
            word_800A5968 = 0;
            byte_800A38D9 = 1;
            word_800A5974 = 0;
            break;
        case 1:
            sub_800A4E4C();
            t->next_8 = sub_800A16FC;
            t->next_8(t, a);
            break;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(combsel, sub_800A5080);


void sub_800A5188()
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 1:
        {
            CombSelUnit* a = &dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A5960)];
            CombSelUnit* b = &dword_800A1BC8[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A596C)];
            MemCopy_800403E8(a, b, 0xF8);
            byte_800A38DB = 2;
            PlaySfx_80031494(0x7E);
            break;
        }
        case 2:
            if (sub_800A1934(&dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A5960)]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                sub_800A197C(&dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A5960)]);
                byte_800A38DB = 0;
            }
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 1:
            byte_800A38DB = 2;
            break;
        case 2:
            byte_800A38DB = 0;
            break;
        }
    }
}

void sub_800A53B0()
{
    short s;
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        s = word_800A1BC4;
        if (s == 1)
        {
            short r = GetMenuCursorIndex_8003DA54(dword_800A596C);
            if (sub_800A1934(&dword_800A1BC8[byte_800A38D9][r]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                byte_800A38DB = 1;
                PlaySfx_80031494(0x7E);
            }
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        byte_800A38DB = 0;
        if (sub_800A1AAC(byte_800A38D9))
        {
            word_800A1BC4 = 3;
        }
    }
}

void sub_800A54A0(CombSelTask* t)
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        PlaySfx_80031494(0x7E);
        if ((short)GetMenuCursorIndex_8003DA54(dword_800A5978) == 0)
        {
            XaRequestPlay_80043564(1, 0x678, 0x1F);
            t->next_8 = sub_800A5538;
        }
        else
        {
            byte_800A38DB = 0;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        byte_800A38DB = 0;
    }
}

void sub_800A5538(CombSelTask* t)
{
    t->next_8 = sub_800A16FC;
    t->next_8(t);
}

int sub_800A5560(CombSelUnit* p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (sub_800A1934(p + i) == 0)
        {
            return 0;
        }
    }
    return 1;
}

short dword_800A55C4[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    10, 39, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A55FC[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    10, 59, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A5634[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    10, 79, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short *dword_800A566C[3] = { dword_800A55C4, dword_800A55FC, dword_800A5634 };
int dword_800A5678 = 0;
int dword_800A567C[6] = { 2, 0, 8, 0, (int)dword_800A566C };
short dword_800A5694[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    155, 74, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A56CC[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    155, 94, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A5704[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    155, 114, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A573C[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    155, 134, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A5774[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    155, 154, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A57AC[28] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    155, 174, 144, 19, 2, 4, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short *dword_800A57E4[6] = { dword_800A5694, dword_800A56CC, dword_800A5704, dword_800A573C, dword_800A5774, dword_800A57AC };
int dword_800A57FC = 0;
int dword_800A5800[6] = { 2, 0, 8, 0, (int)dword_800A57E4 };
short dword_800A5818[28] = {
    8, 1, 155, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    10, 99, 108, 18, 2, 2, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A5850[28] = {
    8, 1, 29, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    10, 118, 108, 18, 2, 2, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A5888[28] = {
    8, 1, 27, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    10, 137, 108, 18, 2, 2, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short dword_800A58C0[2] = { 8, 1 };
int dword_800A58C4[13] = {
    0, (int)&uiTiySprts_8008D620, (int)&uiTiyTPages_8008D3F4, 0x9C000A, 0x12006C, 0x20002, 1, 0,
    0, 0, -1, -1, -1,
};
short dword_800A58F8[28] = {
    8, 1, 28, 0, 0xD620, 0x8008, 0xD3F4, 0x8008,
    10, 175, 108, 18, 2, 2, 1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, -1, -1,
};
short *dword_800A5930[5] = { dword_800A5818, dword_800A5850, dword_800A5888, dword_800A58C0, dword_800A58F8 };
int dword_800A5944 = 0;
int dword_800A5948[6] = { 2, 0, 8, 0, (int)dword_800A5930 };
char dword_800A5960[8] = { 1, 0, 3, 0, 3, 0, 64 };
short word_800A5968 = 0;
char dword_800A596C[8] = { 1, 0, 6, 0, 15, 0, 64 };
short word_800A5974 = 0;
char dword_800A5978[8] = { 2, 0, 1, 0, 2 };
short word_800A5980 = 1;
int dword_800A5984[4] = { 0x800A1BBC, (int)dword_800A5960, (int)dword_800A596C, (int)dword_800A5978 };
void *dword_800A5994[4] = { (void *)dword_800A5948, (void *)dword_800A567C, (void *)dword_800A5800, (void *)((char *)&dword_8008276C + 24) };
int dword_800A59A4[2] = { 55, 56 };
int dword_800A59AC[2] = { 56, 36 };
void (*dword_800A59B4[4])() = { sub_800A4E94, sub_800A5188, sub_800A53B0, sub_800A54A0 };
const char *dword_800A59C4[3] = { aReadMinionDataF_800A411C, aEnterMinionFrom_800A40EC, aDeleteEnteredMi_800A40BC };
const char *dword_800A59D0[2] = { 0, aReturnToTitleSc_800A408C };
const char *dword_800A59D8[1] = { aReturnToTitleSc_800A4164 };
const char *dword_800A59DC[1] = { aEnterPlayer2SMi_800A4194 };
const char *dword_800A59E0[1] = { aStartFighting_800A41C8 };
int dword_800A59E4[8] = { 16, (int)aSelect_800A4228, 167, (int)aQuit_800A421C, 94, (int)aEnterPlayer2SMi_800A41E8, -1 };
int dword_800A5A04[8] = { 16, (int)aSelect_800A4228, 167, (int)aQuit_800A421C, 94, (int)aStartFighting_800A41C8, -1 };
