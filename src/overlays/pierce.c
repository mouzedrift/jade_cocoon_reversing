// PIERCE.BIN: linked for 0x800C6F40, and its calls into the executable land inside functions
// (0x80027724 is in LoadMapFtg_80027708): it was built against an older executable and looks unused.
#include "common.h"
#include "funcs.h"
#include "globals.h"

INCLUDE_OVERLAY_ASM(pierce, dword_800C6F40);

typedef struct PierceTask
{
    int pad_0[2];
    void (*next_8)();
} PierceTask;

typedef struct PierceMsg
{
    int a_0;
    int b_4;
    int c_8;
    int d_C;
    int e_10;
    int f_14;
    int pad_18[4];
} PierceMsg;

typedef struct PierceCam
{
    char pad_0[0x31C];
    short x_31C;
    short pad_31E;
    short y_320;
    short pad_322;
    short z_324;
    short pad_326;
    short f_328;
} PierceCam;

extern void fn_800AD070();
extern void fn_800B7C04();
extern void fn_800B7DD8();
extern void fn_800BC570(int a, int b);
extern int fn_800BC484();
extern int fn_800B7C74();
extern int fn_800B7C9C();
extern void fn_800B76AC(PierceMsg* m);
extern void fn_80027724(int a);
extern int fn_800277E8();
extern void fn_800BC604(int a);
extern void fn_800B7C30();
extern void fn_800BD348(int a, int b);
extern void fn_800BD734(short* v, int b);
extern void fn_80028E04();
extern void fn_800B60FC();
extern PierceCam cam_80092F30;
extern int dword_8009DCAC;
extern int dword_8009DC7C;
extern int dword_80092F00;
extern int dword_800C124C;

// Matched
void sub_800C6F58(PierceTask* t, int* st)
{
    PierceMsg m;
    PierceMsg m2;
    short v[4];
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
            fn_800BD734(v, 0x63);
            cam_80092F30.f_328 = 0;
            dword_8009DCAC = 1;
            dword_8009DC7C = 0;
            cam_80092F30.x_31C = v[0];
            cam_80092F30.y_320 = v[1];
            cam_80092F30.z_324 = v[2];
            fn_80028E04();
            dword_80092F00 = 1;
            dword_800C124C = 1;
            t->next_8 = fn_800B60FC;
        }
        break;
    }
}

// Matched
void sub_800C7124(PierceTask* t, int* st)
{
    st[0] = 0;
    st[1] = 0x1C;
    sub_800C6F58(t, st);
    t->next_8 = sub_800C6F58;
}
