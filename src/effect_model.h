#ifndef _TU_800174F8_H_
#define _TU_800174F8_H_

extern const int unused_80072278[0];

// effect is unused (the GAME caller passes the effect id)
HitTimes* RepeatHitTimes_80018200(HitTimes* src, unsigned short loopStart, unsigned short loopEnd, short loops, int effect);

void SpawnMdecEffect_80017A6C(void* parent, int frames);
void SpawnPulseModel_800174F8(EffectObj* parent, int modelId);
void MorphInModelTask_80017E30(EventEntry* entry, void* buf);
void PulseModelTask_8001761C(int* flags, EffectObj* obj);
void MorphModelTask_800178C0(int* flags, EffectObj* obj);
void MdecEffectTask_80017B10(unsigned int* flags, EffectObj* obj);
void WaveModelTask_80017CE4(EventEntry* entry, void* buf);
void FadeOutModelTask_80017FF8(EventEntry* entry, void* buf);
int GetMdecEffectLength_800181E8(void);
void CollectEffectTargets_800182B8(ActorEffectReq* req, int mask);
#endif
