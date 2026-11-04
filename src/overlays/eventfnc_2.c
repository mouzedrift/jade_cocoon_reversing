// EVENTFNC.BIN, source file 2 of 2 from 0x800BCB3C (.rdata from 0x800B6D98)
#include "eventfnc.h"

const int dword_800B6D98[10] = {
    0, 0, 0, 0, 0, 5, 7, 6,
    8,
};
INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6DC0);

#if 0
// Not matched: with this file's own .rdata the initializer and jump table land where the original's are;
// the code is 1 word short: case 4 keeps the saveData address in a0 (dead across the calls, recomputed
// for the stores) and shares the constant 4 of sub_800AD16C's first argument with word_8008B858 + 4
extern int dword_800B0EC0;
void sub_800BCB3C(TaskEventfnc* t, int* st)
{
    EvMsgEventfnc m;
    unsigned short v[3];
    SaveData* s;
    int k;
    switch (st[0])
    {
    case 0:
        sub_800A1904();
        sub_800A8E0C();
        sub_800A8DEC();
        sub_800AC604(st[1], 0);
        st[0] = 1;
        break;
    case 1:
        if (sub_800AC768())
        {
            st[0] = 2;
        }
        break;
    case 2:
        if (sub_800A8E7C())
        {
            st[0] = 3;
        }
        break;
    case 3:
        if (sub_800A8FE0())
        {
            m.m0_0 = 0;
            m.m4_4 = 9;
            m.m8_8 = 0;
            m.mC_C = st[1];
            m.m10_10 = 0;
            m.m14_14 = 1;
            sub_800A8EC4((int*)&m);
            StartSceneDarken_8001AAA8(0x3C);
            st[0] = 4;
        }
        break;
    case 4:
        if (IsSceneFadeDone_8001AB94())
        {
            sub_800AC6A8(st[1]);
            sub_800A8E38();
            s = &saveData_8008B570;
            if (s->mapId_2E4[0].field_0 == 4 && s->mapId_2E4[1].field_0 == 0 && mapTable_800B0608[4][0][s->mapId_2E4[2].field_0].f4_4 == 0)
            {
                int tbl2[9] = {0, 0, 0, 0, 0, 5, 7, 6, 8};
                k = tbl2[pendingArea_8008B860];
            }
            else
            {
                k = word_8008B858 + 4;
            }
            sub_800AD16C(4, k);
            sub_800ADCEC(v, sub_800A683C(-1));
            forceMapReload_80091C9C = 1;
            useMapStartPos_80091C94 = 1;
            dword_80091C54 = 0;
            dword_80091C8C = 0;
            dword_800B0EC0 = 1;
            s = &saveData_8008B570;
            s->mapId_2E4[3].field_0 = 0;
            s->mapId_2E4[0].field_0 = v[0];
            s->mapId_2E4[1].field_0 = v[1];
            s->mapId_2E4[2].field_0 = v[2];
            unknownFlags_8008D678 &= ~0x20000;
            t->next_8 = sub_800A7720;
        }
        break;
    }
}
#endif

INCLUDE_OVERLAY_ASM(eventfnc, sub_800BCB3C);


int (*eventFuncs_800BCDBC[157])() = {
    sub_800B89A8, sub_800B89C0, sub_800B89A8, sub_800B89F4,
    (int (*)())sub_800B8A34, (int (*)())sub_800B8BE8, sub_800B8CB0, sub_800B8D08,
    sub_800B8DDC, sub_800B89A8, sub_800B8E9C, sub_800B8F14,
    sub_800B8F44, sub_800B8F88, sub_800B8FB8, sub_800B9020,
    sub_800B9110, sub_800B91CC, sub_800B9218, sub_800B9260,
    sub_800B93A8, sub_800B942C, sub_800B93A8, sub_800B942C,
    sub_800B95BC, sub_800B962C, sub_800B96D8, sub_800B9720,
    sub_800B9768, sub_800B97B0, sub_800B97F8, sub_800B9840,
    sub_800B98C4, sub_800B990C, sub_800B9954, sub_800B99D8,
    sub_800B9A20, sub_800B9A68, sub_800B9AB4, sub_800B9B00,
    sub_800B9B4C, (int (*)())sub_800B9B98, sub_800B9CC0, sub_800B9D08,
    sub_800B9D50, sub_800B9C5C, sub_800B9DE0, sub_800B9E48,
    sub_800B9EB0, sub_800B9EDC, sub_800B9F0C, sub_800B9F5C,
    sub_800B9F84, sub_800B9FB4, sub_800B9FD8, sub_800BA020,
    sub_800BA020, sub_800BA020, sub_800BA020, sub_800BA020,
    sub_800BA020, sub_800BA020, sub_800BA020, sub_800BA020,
    sub_800B89A8, sub_800BA1DC, sub_800BA238, sub_800BA28C,
    sub_800BA2E8, sub_800BA338, sub_800BA40C, sub_800BA45C,
    sub_800BA4F0, sub_800BA554, sub_800BA5CC, sub_800BA678,
    sub_800BA6D0, sub_800BA714, sub_800BA7A4, (int (*)())sub_800BA82C,
    sub_800BA880, sub_800BA8AC, sub_800BA930, sub_800BA9E4,
    sub_800B89A8, sub_800BAA6C, sub_800BAAC0, sub_800BAB14,
    (int (*)())sub_800BAB5C, sub_800BABB0, sub_800BAC60, sub_800BACE0,
    sub_800BAD3C, sub_800BAD88, sub_800BADF8, sub_800BAEBC,
    sub_800BAF08, sub_800BAF68, sub_800BAFAC, sub_800BB180,
    sub_800BB214, (int (*)())sub_800BB27C, sub_800BB45C, sub_800BB4A4,
    sub_800BB7D8,
};
