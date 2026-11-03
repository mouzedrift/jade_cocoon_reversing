#ifndef _ACTOR_H_
#define _ACTOR_H_

// actor (CreateActor_8001D45C, actorTasks_8008D43C); field names by offset until their meaning is known
typedef struct Actor
{
    int task_0; // 0x0
    unsigned int flags_4; // 0x4
    int f8; // 0x8
    int fC; // 0xC
    short f10; // 0x10
    short f12; // 0x12
    short f14; // 0x14
    short f16; // 0x16
    short f18; // 0x18
    short f1A; // 0x1A
    short f1C; // 0x1C
    short f1E; // 0x1E
    short f20; // 0x20
    short f22; // 0x22
    short f24; // 0x24
    short f26; // 0x26
    short f28; // 0x28
    short f2A; // 0x2A
    int f2C; // 0x2C
    int f30; // 0x30
    int f34; // 0x34
    int pos_38[3]; // 0x38
    int prevPos_44[3]; // 0x44
    int f50[3]; // 0x50
    short rot_5C[3]; // 0x5C
    short pad_62; // 0x62
    int animDelta_64[3]; // 0x64
    int target_70[3]; // 0x70
    int f7C; // 0x7C
    int f80; // 0x80
    int f84; // 0x84
    int f88; // 0x88
    int f8C; // 0x8C
    int f90; // 0x90
    int f94; // 0x94
    int f98; // 0x98
    int f9C; // 0x9C
    int fA0; // 0xA0
    int fA4; // 0xA4
    int fA8; // 0xA8
    int fAC; // 0xAC
    int fB0; // 0xB0
    int fB4; // 0xB4
    int fB8; // 0xB8
    short fBC; // 0xBC
    short fBE; // 0xBE
    short fC0; // 0xC0
    short fC2; // 0xC2
    int fC4; // 0xC4
    int fC8; // 0xC8
    int fCC; // 0xCC
    int fD0; // 0xD0
    int fD4; // 0xD4
    int fD8; // 0xD8
    int* fDC; // 0xDC
    short fE0; // 0xE0
    short fE2; // 0xE2
    int fE4; // 0xE4
    int fE8; // 0xE8
    int fEC; // 0xEC
    int fF0; // 0xF0
    short fF4; // 0xF4
    short fF6; // 0xF6
    int fF8; // 0xF8
    short fFC; // 0xFC
    short fFE; // 0xFE
    int f100; // 0x100
    int f104; // 0x104
    int f108; // 0x108
    int f10C; // 0x10C
    int f110; // 0x110
    int f114; // 0x114
    int f118; // 0x118
    int f11C; // 0x11C
    int f120; // 0x120
    int f124; // 0x124
    int f128; // 0x128
    int f12C; // 0x12C
    int f130; // 0x130
    int f134; // 0x134
    int f138[3]; // 0x138
    char* f144; // 0x144
    int f148; // 0x148
    int f14C; // 0x14C
    short f150; // 0x150
    short f152; // 0x152
    int f154; // 0x154
    short f158; // 0x158
    short f15A; // 0x15A
    char* desc_15C; // 0x15C
    char* anim_160; // 0x160
    int f164; // 0x164
    char* f168; // 0x168
    char* f16C; // 0x16C
    int f170; // 0x170
    int f174; // 0x174
    unsigned int* f178; // 0x178
    unsigned int f17C; // 0x17C
    int f180; // 0x180
    int f184; // 0x184
    char* f188; // 0x188
    unsigned long* f18C; // 0x18C
    int f190; // 0x190
    int f194; // 0x194
    int f198; // 0x198
    int f19C; // 0x19C
    short f1A0; // 0x1A0
    short f1A2; // 0x1A2
    int f1A4; // 0x1A4
    int f1A8; // 0x1A8
    int f1AC; // 0x1AC
    int f1B0; // 0x1B0
    int f1B4; // 0x1B4
    int f1B8; // 0x1B8
    int f1BC; // 0x1BC
    int f1C0; // 0x1C0
    char* f1C4; // 0x1C4
    char* f1C8; // 0x1C8
} Actor;

#endif
