#include "common.h"
#include "funcs.h"
#include "sdk.h"
#include "globals.h"
#include "sound.h"
#include "data_decls.h"
#include "engine.h"


void SetDisplayMode_80040658(int mode)
{
    RestartDisplay_8001B230();
    switch (mode)
    {
        case 0:
            display_8008B4D8.mode_0 = 5;
            display_8008B4D8.x_8 = 0;
            display_8008B4D8.y_A = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 1;
            break;
        case 2:
            display_8008B4D8.mode_0 = 1;
            display_8008B4D8.x_8 = 0;
            display_8008B4D8.y_A = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 2;
            break;
        case 1:
            display_8008B4D8.mode_0 = 1;
            display_8008B4D8.x_8 = 0;
            display_8008B4D8.y_A = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 1;
            break;
        case 3:
            display_8008B4D8.mode_0 = 7;
            display_8008B4D8.x_8 = 0;
            display_8008B4D8.y_A = 16;
            display_8008B4D8.vsyncsPerFrame_4 = 1;
            break;
        case 4:
            break;
    }
}
