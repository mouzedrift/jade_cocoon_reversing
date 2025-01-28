#include "sound.h"
#include "globals.h"
#include "enums.h"

SoundStruct stru_80091CE0;
SoundStruct stru_80091D20;
SoundStruct stru_80091D00;
SoundStruct stru_80091D40;

SoundInfo soundFiles_80082F0C[155] =
{
  { SOUND_PUBLIC_SND, 0u, 0u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 1u, 0u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 2u, 0u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 3u, 0u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 4u, 0u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 5u, 0u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 6u, 0u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 255u, 255u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 255u, 255u, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 255u, 255u, 7u, 0u, -1 },
  { SOUND_PUBLIC2_SND, 255u, 255u, 16u, 16u, -1 },
  { SOUND_NAME_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SABAKI_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SAINIGHT_SND, 0u, 0u, 1u, 0u, 44 },
  { SOUND_SAIRASU_SND, 0u, 0u, 1u, 0u, 44 },
  { SOUND_SAISTONE_SND, 0u, 0u, 2u, 0u, 44 },
  { SOUND_SHUUGEKI_SND, 0u, 0u, 1u, 0u, 52 },
  { SOUND_TAMA_SND, 0u, 0u, 1u, 0u, 64 },
  { SOUND_YAMU_SND, 0u, 0u, 1u, 0u, 59 },
  { SOUND_ARUKANA_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_IJIGEN_SND, 0u, 0u, 1u, 0u, 44 },
  { SOUND_IKENIE_SND, 0u, 0u, 1u, 0u, 44 },
  { SOUND_KEKKAI_SND, 0u, 0u, 1u, 0u, 63 },
  { SOUND_KEKKON_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_KIKINA_SND, 0u, 0u, 1u, 0u, 58 },
  { SOUND_KORISU_SND, 0u, 0u, 1u, 0u, 121 },
  { SOUND_KUMO_SND, 0u, 0u, 1u, 0u, 115 },
  { SOUND_MTITLE_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_GOSHIN_SND, 0u, 0u, 2u, 0u, 61 },
  { SOUND_MAP_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_MIKKAI_SND, 0u, 0u, 3u, 0u, 51 },
  { SOUND_GA_SND, 0u, 0u, 1u, 0u, 117 },
  { SOUND_TOMBO_SND, 0u, 0u, 1u, 0u, 113 },
  { SOUND_NAGI_SND, 0u, 0u, 1u, 0u, 62 },
  { SOUND_DREAM_SND, 0u, 0u, 1u, 0u, 57 },
  { SOUND_LUI_SND, 0u, 0u, 1u, 0u, 119 },
  { SOUND_MBOSS_SND, 0u, 0u, 1u, 0u, 119 },
  { SOUND_IJIKIKI_SND, 0u, 0u, 1u, 0u, 58 },
  { SOUND_IJIKORI_SND, 0u, 0u, 1u, 0u, 121 },
  { SOUND_IJIKUMO_SND, 0u, 0u, 1u, 0u, 115 },
  { SOUND_IJISHIN_SND, 0u, 0u, 1u, 0u, 61 },
  { SOUND_IJITAMA_SND, 0u, 0u, 1u, 0u, 64 },
  { SOUND_IJITOMBO_SND, 0u, 0u, 1u, 0u, 113 },
  { SOUND_IJIYAMU_SND, 0u, 0u, 1u, 0u, 59 },
  { SOUND_SE_SAI_SND, 255u, 255u, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 0u, 0u, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 1u, 0u, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 2u, 0u, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 3u, 0u, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 4u, 0u, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 5u, 0u, 7u, 0u, -1 },
  { SOUND_SE_MIHA1_SND, 255u, 255u, 1u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 255u, 255u, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 0u, 0u, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 1u, 0u, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 2u, 0u, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 3u, 0u, 4u, 0u, -1 },
  { SOUND_SE_YUME1_SND, 255u, 255u, 0u, 0u, -1 },
  { SOUND_SE_KIKI_SND, 255u, 255u, 1u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 255u, 255u, 0u, 0u, -1 },
  { SOUND_SE_MBOSS_SND, 255u, 255u, 1u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 255u, 255u, 5u, 0u, -1 },
  { SOUND_SE_NAGI_SND, 255u, 255u, 1u, 0u, -1 },
  { SOUND_SE_MON_SND, 255u, 255u, 0u, 0u, -1 },
  { SOUND_SE_TAMA_SND, 255u, 255u, 3u, 0u, -1 },
  { SOUND_PUBTST2_SND, 0u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 1u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 2u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 3u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 4u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 5u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 6u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 7u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 8u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 9u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 10u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 11u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 12u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 13u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 14u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 15u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 0u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 1u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 2u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 3u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 4u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 5u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 6u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 7u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 8u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 9u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 10u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 11u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 12u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 13u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 14u, 0u, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 15u, 0u, 16u, 0u, -1 },
  { SOUND_SE_MBOSS_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SE_SAI_SND, 6u, 0u, 7u, 0u, -1 },
  { SOUND_SE_MIHA1_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 0u, 0u, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 1u, 0u, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 2u, 0u, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 3u, 0u, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 4u, 0u, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 5u, 0u, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 6u, 0u, 7u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 0u, 0u, 5u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 1u, 0u, 5u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 2u, 0u, 5u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 3u, 0u, 5u, 0u, -1 },
  { SOUND_SE_NAGI_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SE_TAMA_SND, 0u, 0u, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, 255u, 255u, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, 0u, 0u, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, 255u, 255u, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, 0u, 0u, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, 255u, 255u, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, 0u, 0u, 3u, 0u, -1 },
  { SOUND_SE_BTL_SND, 255u, 255u, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 0u, 0u, 7u, 0u, -1 },
  { SOUND_SE_KORI_SND, 255u, 255u, 0u, 0u, -1 },
  { SOUND_NAGIZ_SND, 0u, 0u, 1u, 0u, 123 },
  { SOUND_SE_NAGIZ_SND, 255u, 255u, 0u, 0u, -1 },
  { SOUND_SAISTONE_SND, 1u, 0u, 2u, 0u, 44 },
  { SOUND_GOSHIN_SND, 1u, 0u, 2u, 0u, 61 },
  { SOUND_MIKKAI_SND, 1u, 0u, 3u, 0u, 51 },
  { SOUND_SE_MRB_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SYOU_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SE_TAMA_SND, 1u, 0u, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, 1u, 0u, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, 1u, 0u, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, 1u, 0u, 3u, 0u, -1 },
  { SOUND_SE_BTL_SND, 1u, 0u, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 2u, 0u, 7u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 4u, 0u, 5u, 0u, -1 },
  { SOUND_SE_TAMA_SND, 2u, 0u, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, 2u, 0u, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, 2u, 0u, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, 2u, 0u, 3u, 0u, -1 },
  { SOUND_SE_MON_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_HORAGAI_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_ZAKKA_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_MATSURI_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_MIKKAI_SND, 2u, 0u, 3u, 0u, 51 },
  { SOUND_BRACKMRC_SND, 0u, 0u, 1u, 0u, 44 },
  { SOUND_LBOSS_SND, 0u, 0u, 1u, 0u, 119 },
  { SOUND_SE_BTL_SND, 3u, 0u, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 4u, 0u, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 5u, 0u, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 6u, 0u, 7u, 0u, -1 },
  { SOUND_SYOU_SND, 255u, 255u, 1u, 0u, 123 },
  { SOUND_SE_KIKI_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_TAISEN_SND, 0u, 0u, 1u, 0u, -1 },
  { SOUND_SAIRASU_SND, 255u, 255u, 1u, 0u, 44 }
};

// Matched
int GetSoundFileId_80030D4C(int idx)
{
  return soundFiles_80082F0C[idx].field_0_file_id;
}

// Matched
void InitSound_8002FE54(SoundStruct* arg1)
{
    arg1->field_0_vab_id = -1;
    arg1->field_4_seq_num = -1;
    arg1->field_6_sound_idx = -1;
    arg1->field_C_sep_access_num = -1;
    arg1->field_14_sep_access_num = -1;
    arg1->field_8_sep_data_ptr = 0;
    arg1->field_10_sep_data_ptr = 0;
    arg1->field_18_vab_header_ptr = 0;
}

// Matched
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

// Matched
void sub_80030A84(short soundId, SoundStruct* sound)
{
    char* pSndFileBuffer;
    GenkiSoundHeader* pSndFileHeader;

    sound->field_6_sound_idx = soundId;

    pSndFileBuffer = DATA_GetFileBuffer_8003CAA0(GetSoundFileId_80030D4C(sound->field_6_sound_idx));
    pSndFileHeader = (GenkiSoundHeader*)pSndFileBuffer;

    sound->field_18_vab_header_ptr = (unsigned char*)malloc3_8003FC4C(pSndFileHeader->field_4_vab_header_size);

    ReadBytesInto_80040388((int*)sound->field_18_vab_header_ptr,
                           (int*)(pSndFileBuffer + pSndFileHeader->field_0_header_start),
                           pSndFileHeader->field_4_vab_header_size / sizeof(int));

    sound->field_0_vab_id = SsVabOpenHead(sound->field_18_vab_header_ptr, -1);
    if (sound->field_0_vab_id == -1)
    {
        printf("Assertion failed: file \"%s\", line %d\n", "SOUND.C", 631);
        exit(1);
    }

    if (SsVabTransBody((unsigned char*)(pSndFileBuffer + pSndFileHeader->field_8), sound->field_0_vab_id) == -1)
    {
        printf("Assertion failed: file \"%s\", line %d\n", "SOUND.C", 639);
        exit(1);
    }
    SsVabTransCompleted(1);

    if (pSndFileHeader->field_14_sep_size)
    {
        sound->field_8_sep_data_ptr = (unsigned long*)malloc3_8003FC4C(pSndFileHeader->field_14_sep_size);
        ReadBytesInto_80040388((int*)sound->field_8_sep_data_ptr,
                               (int*)(pSndFileBuffer + pSndFileHeader->field_10),
                               pSndFileHeader->field_14_sep_size / sizeof(int));

        sound->field_C_sep_access_num =
            SsSepOpen(sound->field_8_sep_data_ptr, sound->field_0_vab_id, soundFiles_80082F0C[sound->field_6_sound_idx].field_4_seq_count);
        if (sound->field_C_sep_access_num == -1)
        {
            printf("Assertion failed: file \"%s\", line %d\n", "SOUND.C", 652);
            exit(1);
        }
        SsSepSetVol(sound->field_C_sep_access_num, 1, 0, 0);
    }
    else
    {
        sound->field_8_sep_data_ptr = 0;
    }

    if (pSndFileHeader->field_1C_sep_size)
    {
        sound->field_10_sep_data_ptr = (unsigned long*)malloc3_8003FC4C(pSndFileHeader->field_1C_sep_size);
        ReadBytesInto_80040388((int*)sound->field_10_sep_data_ptr,
                               (int*)(pSndFileBuffer + pSndFileHeader->field_18_sep_data2_ptr),
                               pSndFileHeader->field_1C_sep_size / sizeof(int));
        sound->field_14_sep_access_num =
            SsSepOpen(sound->field_10_sep_data_ptr, sound->field_0_vab_id, soundFiles_80082F0C[sound->field_6_sound_idx].field_5_seq_count);
        if (sound->field_14_sep_access_num == -1)
        {
            printf("Assertion failed: file \"%s\", line %d\n", "SOUND.C", 667);
            exit(1);
        }
        SsSepSetVol(sound->field_14_sep_access_num, 1, 0, 0);
    }
    else
    {
        sound->field_10_sep_data_ptr = 0;
    }

    SsUtSetReverbDepth(50, 50);
    sound->field_4_seq_num = -1;

    free3_8003FC6C(pSndFileBuffer);
}