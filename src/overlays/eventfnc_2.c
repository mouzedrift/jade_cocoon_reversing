// EVENTFNC.BIN, source file 2 of 2 from 0x800BCB3C (.rdata from 0x800B6D98)
#include "eventfnc.h"

INCLUDE_OVERLAY_ASM(eventfnc, dword_800B6D98);

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
            if (s->mapId_2E4[0].field_0 == 4 && s->mapId_2E4[1].field_0 == 0 && dword_800B0608[4][0][s->mapId_2E4[2].field_0].f4_4 == 0)
            {
                int tbl2[9] = {0, 0, 0, 0, 0, 5, 7, 6, 8};
                k = tbl2[word_8008B860];
            }
            else
            {
                k = word_8008B858 + 4;
            }
            sub_800AD16C(4, k);
            sub_800ADCEC(v, sub_800A683C(-1));
            dword_80091C9C = 1;
            dword_80091C94 = 1;
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


INCLUDE_OVERLAY_ASM(eventfnc, dword_800BCDBC);
