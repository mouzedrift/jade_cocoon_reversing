// PIERCE.BIN: linked for 0x800C6F40, and its calls into the executable land inside functions
// (0x80027724 is in LoadMapFtg_80027708): it was built against an older executable and looks unused.
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "pierce.h"

int unused_800C6F40 SDATA = 216;





void PierceEventTask_800C6F58(PierceTask* task, int* st)
{
    PierceMsg m;
    PierceMsg m2;
    short pos[4];
    switch (st[0])
    {
    case 0:
        fn_800AD070();
        fn_800B7C04();
        fn_800B7DD8();
        fn_800BC570(st[1], 0);
        st[0] = 1;
        break;
    case 1:
        if (fn_800BC484())
        {
            st[0] = 2;
        }
        break;
    case 2:
        if (fn_800B7C74())
        {
            m.a_0 = 0;
            m.b_4 = 9;
            m.c_8 = 0;
            m.d_C = st[1];
            m.e_10 = 0;
            m.f_14 = 5;
            fn_800B76AC(&m);
            st[0] = 3;
        }
        break;
    case 3:
        if (fn_800B7C9C())
        {
            m2.a_0 = 0;
            m2.b_4 = 9;
            m2.c_8 = 0;
            m2.d_C = st[1];
            m2.e_10 = 0;
            m2.f_14 = 5;
            fn_800B76AC(&m2);
            fn_80027724(0x3C);
            st[0] = 4;
        }
        break;
    case 4:
        if (fn_800277E8())
        {
            fn_800BC604(st[1]);
            fn_800B7C30();
            fn_800BD348(0, cam_80092F30.y_320 + 4);
            fn_800BD734(pos, 0x63);
            cam_80092F30.f_328 = 0;
            dword_8009DCAC = 1;
            dword_8009DC7C = 0;
            cam_80092F30.x_31C = pos[0];
            cam_80092F30.y_320 = pos[1];
            cam_80092F30.z_324 = pos[2];
            fn_80028E04();
            dword_80092F00 = 1;
            dword_800C124C = 1;
            task->next_8 = fn_800B60FC;
        }
        break;
    }
}

void PierceEventStart_800C7124(PierceTask* task, int* st)
{
    st[0] = 0;
    st[1] = 0x1C;
    PierceEventTask_800C6F58(task, st);
    task->next_8 = PierceEventTask_800C6F58;
}
