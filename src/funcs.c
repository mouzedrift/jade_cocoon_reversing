#include "globals.h"


// Match
int sub_80012178(int arg0)
{
    return (arg0 * 3) + 20;
}

// Match
int sub_80012140(int arg0)
{
    int result;
    int var_v0;
    int i;

    result = 20;

    for (i = 0; i < arg0; i++)
    {
        var_v0 = result + 9;
        result = var_v0 + (arg0 / 2);
        var_v0 = 29;
    }
    return result;
}

// Match
int sub_8003BA58(int arg0)
{
    int result;
    int var_v0;
    int i;

    result = 0;
    for (i = 0; i < 32; i++)
    {
        var_v0 = 1 << i;
        if (arg0 & var_v0)
        {
            result += 1;
        }
    }
    return result;
}

int sub_800125B8()
{
    int i;
    int result;

    result = 0;
    for (i = 0; i < 7; i++)
    {
        result += sub_8003BA58(dword_8008BD84[i]);
    }
    return result;
}

// Matched
int sub_8001C2FC()
{
    return (dword_800918B0 & 3) == 0;
}
