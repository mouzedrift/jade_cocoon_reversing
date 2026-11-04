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
#include "tu_80031870.h"




// Matched
int SkillSlotToAnimIndex_80031870(int slot)
{
    switch (slot)
    {
    case 0:
        return 3;
    case 1:
        return 0;
    case 2:
        return 2;
    case 3:
        return 1;
    case 4:
        return 4;
    }
    return 0;
}
const int dword_800746D0 = 0;
