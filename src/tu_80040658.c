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
void sub_80040658(int arg1)
{
    sub_8001B230();
    switch (arg1)
    {
        case 0:
            stru_8008B4D8.field_0 = 5;
            stru_8008B4D8.field_8_x = 0;
            stru_8008B4D8.field_A_y = 16;
            stru_8008B4D8.field_4 = 1;
            break;
        case 2:
            stru_8008B4D8.field_0 = 1;
            stru_8008B4D8.field_8_x = 0;
            stru_8008B4D8.field_A_y = 16;
            stru_8008B4D8.field_4 = 2;
            break;
        case 1:
            stru_8008B4D8.field_0 = 1;
            stru_8008B4D8.field_8_x = 0;
            stru_8008B4D8.field_A_y = 16;
            stru_8008B4D8.field_4 = 1;
            break;
        case 3:
            stru_8008B4D8.field_0 = 7;
            stru_8008B4D8.field_8_x = 0;
            stru_8008B4D8.field_A_y = 16;
            stru_8008B4D8.field_4 = 1;
            break;
        case 4:
            break;
    }
}
