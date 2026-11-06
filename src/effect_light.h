#ifndef _TU_80016BF4_H_
#define _TU_80016BF4_H_

extern const int unused_80072274;

void SpawnLightFlash_80017158(int* pos, unsigned char* rgb);
void SpawnGlowModel_80017290(EffectObj* parent, int modelId);
void RadialBurstTask_80016E20(int* flags, void* buf);
void QuadBurstTask_80016FC8(int* flags, EffectObj* obj);
void LightFlashTask_80017208(int* flags, EffectObj* obj);
void GlowModelTask_800173A8(int* flags, void* buf);
void CountdownTask_80016BF4(EventEntry* entry, EffectObj* obj);
#endif
