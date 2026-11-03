#ifndef SOUNDTASK_H
#define SOUNDTASK_H

/* the buffer of the sound task (soundTask_8008D4A4->entry.buffer); sound.c, tu_80030D00.c */

typedef struct
{
    short active;
    short timer;
    short access_num;
    short seq;
} SeqFade;

typedef struct
{
    short field_0;
    unsigned short state_2; // 2 = ready
    SoundStruct* bgm_4;
    SoundStruct* sfx_8;
    SoundStruct* seqSlot_C; // its address is the file request's params (LoadSeqSlotSound_800303E8)
    int request_10;
    int request_14;
    SeqFade fades_18[5];
} SoundTask;


#endif
