#ifndef TU_80018430_H
#define TU_80018430_H

/* the object Actor.f148 points to (sub_80018A4C) */
typedef struct
{
    char pad_0[0x24];
    short field_24;
    short field_26;
} ActorRec65C;

typedef struct
{
    char pad_0[0x656];
    short field_656;
    char pad_658[4];
    ActorRec65C rec_65C;
} ActorData148;

#endif
