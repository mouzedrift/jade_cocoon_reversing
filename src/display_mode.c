#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"


// Matched
void SetDisplayMode_80040658(int mode)
{
    RestartDisplay_8001B230();
    switch (mode)
    {
        case 0:
            display_8008B4D8.field_0 = 5;
            display_8008B4D8.field_8_x = 0;
            display_8008B4D8.field_A_y = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 1;
            break;
        case 2:
            display_8008B4D8.field_0 = 1;
            display_8008B4D8.field_8_x = 0;
            display_8008B4D8.field_A_y = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 2;
            break;
        case 1:
            display_8008B4D8.field_0 = 1;
            display_8008B4D8.field_8_x = 0;
            display_8008B4D8.field_A_y = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 1;
            break;
        case 3:
            display_8008B4D8.field_0 = 7;
            display_8008B4D8.field_8_x = 0;
            display_8008B4D8.field_A_y = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 1;
            break;
        case 4:
            break;
    }
}
