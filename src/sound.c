#include "sound.h"

SoundStruct stru_80091CE0;
SoundStruct stru_80091D20;
SoundStruct stru_80091D00;

// Matched
void InitSound_8002FE54(SoundStruct* arg1)
{
    arg1->field_0 = -1;
    arg1->field_4_seq_num = -1;
    arg1->field_6_sound_idx = -1;
    arg1->field_C_sep_access_num = -1;
    arg1->field_14_sep_access_num = -1;
    arg1->field_8 = 0;
    arg1->field_10_ptr = 0;
    arg1->field_18_ptr = 0;
}
