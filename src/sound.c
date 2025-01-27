#include "sound.h"
#include "globals.h"

SoundStruct stru_80091CE0;
SoundStruct stru_80091D20;
SoundStruct stru_80091D00;
SoundStruct stru_80091D40;

// Matched
void InitSound_8002FE54(SoundStruct* arg1)
{
    arg1->field_0_vab_id = -1;
    arg1->field_4_seq_num = -1;
    arg1->field_6_sound_idx = -1;
    arg1->field_C_sep_access_num = -1;
    arg1->field_14_sep_access_num = -1;
    arg1->field_8 = 0;
    arg1->field_10_sep_data_ptr = 0;
    arg1->field_18_vab_header_ptr = 0;
}

void PlaySfx_80031494(int a1)
{
    if (a1 < 63)
    {
        SsVoKeyOn((stru_80091D20.field_0_vab_id << 8) + a1,
                  0x3C00u,
                  (settingsFlags_8008B58C >> 14) & 0x7F,
                  (settingsFlags_8008B58C >> 14) & 0x7F);
    }
    else
    {
        SsVoKeyOn((stru_80091D40.field_0_vab_id << 8) + a1,
                  0x3C00u,
                  (settingsFlags_8008B58C >> 14) & 0x7F,
                  (settingsFlags_8008B58C >> 14) & 0x7F);
    }
}
