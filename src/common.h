#ifndef _COMMON_H
#define _COMMON_H

#define COUNTOF(x) (sizeof(x) / sizeof(*(x)))

/*
if this countof version is used then the original code was probably
something like:

enum foo
{
    foo_1,
    foo_2,
    foo_count
}
*/
#define COUNTOF_S(x) (int)(sizeof(x) / sizeof(*(x)))

#define MAX_PLAYER_NAME_LENGTH 10

typedef struct
{
    int field_0;
    short field_4_seq_num;
    short field_6_sound_idx;
    int field_8;
    int field_C_sep_access_num;
    int field_10_ptr;
    int field_14_sep_access_num;
    int field_18_ptr;
} SoundStruct;

#endif
