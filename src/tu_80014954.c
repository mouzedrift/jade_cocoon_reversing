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
#include "effect_obj.h"

INCLUDE_DATA(dword_80079708);
INCLUDE_DATA(dword_80079754);
INCLUDE_DATA(dword_80079A2C);
INCLUDE_DATA(dword_80079AC0);
INCLUDE_DATA(dword_80079B44);
INCLUDE_DATA(dword_80079B6C);
INCLUDE_DATA(dword_80079C04);
INCLUDE_DATA(dword_80079CE0);
INCLUDE_DATA(dword_80079DE4);
INCLUDE_DATA(dword_80079F50);
INCLUDE_DATA(off_8007A024);
INCLUDE_DATA(dword_8007A0A4);
INCLUDE_DATA(dword_8007A0B0);
INCLUDE_DATA(dword_8007A0BC);
INCLUDE_DATA(dword_8007A0C8);
INCLUDE_DATA(dword_8007A0D4);
INCLUDE_DATA(dword_8007A0E0);
INCLUDE_DATA(dword_8007A0EC);
INCLUDE_DATA(dword_8007A0F8);
INCLUDE_DATA(sub_8007A104);
INCLUDE_DATA(dword_8007A110);
INCLUDE_DATA(dword_8007A11C);
INCLUDE_DATA(dword_8007A128);
INCLUDE_DATA(dword_8007A134);
INCLUDE_DATA(dword_8007A140);
INCLUDE_DATA(dword_8007A14C);
INCLUDE_DATA(minionSpeciesNames_8007A170);
INCLUDE_DATA(minionBaseStats_8007A4B4);
INCLUDE_DATA(dword_8007A67C);
INCLUDE_DATA(dword_8007A68C);
INCLUDE_DATA(dword_8007A69C);
INCLUDE_DATA(dword_8007A6AC);
INCLUDE_DATA(dword_8007A9F8);
INCLUDE_DATA(dword_8007BA74);
INCLUDE_DATA(dword_8007BA84);
INCLUDE_DATA(dword_8007BD30);
INCLUDE_DATA(dword_8007C2E4);
INCLUDE_DATA(sub_8007C30C);
INCLUDE_DATA(magicNames_8007C348);
INCLUDE_DATA(magicData_8007C438);
INCLUDE_DATA(dword_8007C5A0);
INCLUDE_DATA(dword_8007C708);
INCLUDE_DATA(dword_8007C728);
INCLUDE_DATA(dword_8007C750);
INCLUDE_DATA(dword_8007CAC0);
INCLUDE_DATA(dword_8007CACC);
INCLUDE_DATA(padButtonBits_8007CAD8);
INCLUDE_DATA(defaultButtonConfig_8007CAF4);
INCLUDE_DATA(nameGetters_8007CB08);
INCLUDE_DATA(personNames_8007CB20);
INCLUDE_DATA(dword_8007CB4C);
INCLUDE_DATA(itemNames_8007CB78);
INCLUDE_DATA(dword_8007CC24);
INCLUDE_DATA(itemFlags_8007CC50);
INCLUDE_DATA(itemData_8007CCA8);
INCLUDE_DATA(itemIcons_8007CEAC);
INCLUDE_DATA(itemPrices_8007CED8);
INCLUDE_DATA(keyItemNames_8007CF30);
INCLUDE_DATA(keyItemIcons_8007CFC8);
INCLUDE_DATA(weaponNames_8007CFF0);
INCLUDE_DATA(weaponData_8007D04C);
INCLUDE_DATA(dword_8007D050);
INCLUDE_DATA(dword_8007D274);
INCLUDE_DATA(weaponPrices_8007D388);
INCLUDE_DATA(armorNames_8007D3E4);
INCLUDE_DATA(armorData_8007D420);
INCLUDE_DATA(dword_8007D424);
INCLUDE_DATA(dword_8007D588);
INCLUDE_DATA(armorModifiers_8007D598);
INCLUDE_DATA(armorPrices_8007D64C);
INCLUDE_DATA(accessoryNames_8007D66C);
INCLUDE_DATA(accessoryData_8007D6B0);
INCLUDE_DATA(dword_8007D6B4);
INCLUDE_DATA(accessoryModifiers_8007D848);
INCLUDE_DATA(accessoryPrices_8007D914);
INCLUDE_DATA(equipmentIcons_8007D938);
INCLUDE_DATA(dword_8007D95C);
INCLUDE_DATA(dword_8007D980);
INCLUDE_DATA(dword_8007D9A4);
INCLUDE_DATA(dword_8007D9C0);
INCLUDE_DATA(overlays_8007D9E8);
INCLUDE_DATA(ftgPrimLoaders_8007DAE0);
INCLUDE_DATA(ftgPrimRelocators_8007DB08);
INCLUDE_DATA(dword_8007DB30);
INCLUDE_DATA(dword_8007DB50);
INCLUDE_DATA(dword_8007DB84);
INCLUDE_DATA(dword_8007DBC4);
INCLUDE_DATA(dword_8007DC10);
INCLUDE_DATA(off_8007DC70);
INCLUDE_DATA(word_8007DC8C);
INCLUDE_DATA(word_8007DC8E);
INCLUDE_DATA(word_8007DC90);
INCLUDE_DATA(word_8007DC92);
INCLUDE_DATA(word_8007DC94);
INCLUDE_DATA(word_8007DC96);
INCLUDE_DATA(dword_8007DCCC);
INCLUDE_DATA(dword_8007DD64);
INCLUDE_DATA(dword_8007DDFC);
INCLUDE_DATA(dword_8007DE78);
INCLUDE_DATA(dword_8007DEA0);
INCLUDE_DATA(dword_8007DFC4);
INCLUDE_DATA(dword_8007DFEC);
INCLUDE_DATA(dword_8007E08C);
INCLUDE_DATA(dword_8007E0EC);
INCLUDE_DATA(dword_8007E114);
INCLUDE_DATA(dword_8007E198);
INCLUDE_DATA(dword_8007E34C);
INCLUDE_DATA(dword_8007E378);
INCLUDE_DATA(dword_8007E44C);
INCLUDE_DATA(dword_8007E4E4);
INCLUDE_DATA(dword_8007E57C);
INCLUDE_DATA(dword_8007E5E0);
INCLUDE_DATA(dword_8007E654);
INCLUDE_DATA(dword_8007E6EC);
INCLUDE_DATA(dword_8007E784);
INCLUDE_DATA(dword_8007E81C);
INCLUDE_DATA(dword_8007E8B4);
INCLUDE_DATA(dword_8007E99C);
INCLUDE_DATA(dword_8007E9D8);
INCLUDE_DATA(dword_8007EAF0);
INCLUDE_DATA(dword_8007EB88);
INCLUDE_DATA(dword_8007EC20);
INCLUDE_DATA(dword_8007ECB8);
INCLUDE_DATA(dword_8007ED50);
INCLUDE_DATA(dword_8007EDE8);
INCLUDE_DATA(dword_8007EE80);
INCLUDE_DATA(byte_8007EF18);
INCLUDE_DATA(byte_8007EFB0);
INCLUDE_DATA(byte_8007F048);
INCLUDE_DATA(byte_8007F0E0);
INCLUDE_DATA(dword_8007F178);
INCLUDE_DATA(byte_8007F210);
INCLUDE_DATA(dword_8007F268);
INCLUDE_DATA(dword_8007F404);
INCLUDE_DATA(dword_8007F42C);
INCLUDE_DATA(dword_8007F600);
INCLUDE_DATA(dword_8007FE44);
INCLUDE_DATA(dword_80080328);
INCLUDE_DATA(dword_800803C0);
INCLUDE_DATA(dword_80080458);
INCLUDE_DATA(byte_80080558);
INCLUDE_DATA(byte_800805C4);
INCLUDE_DATA(byte_80080618);
INCLUDE_DATA(byte_800806D8);
INCLUDE_DATA(aHp);
INCLUDE_DATA(dword_80080700);
INCLUDE_DATA(dword_80080768);
INCLUDE_DATA(dword_800807BC);
INCLUDE_DATA(dword_80080844);
INCLUDE_DATA(dword_800808DC);
INCLUDE_DATA(dword_80080918);
INCLUDE_DATA(dword_800809C0);
INCLUDE_DATA(aL);
INCLUDE_DATA(dword_80080A48);
INCLUDE_DATA(dword_80080AA0);
INCLUDE_DATA(dword_80080B90);
INCLUDE_DATA(dword_80080C68);
INCLUDE_DATA(dword_80080CB0);
INCLUDE_DATA(dword_80080D78);
INCLUDE_DATA(dword_80080E88);
INCLUDE_DATA(dword_80080F0C);
INCLUDE_DATA(dword_80080F50);
INCLUDE_DATA(dword_80081064);
INCLUDE_DATA(dword_80081090);
INCLUDE_DATA(dword_80081158);
INCLUDE_DATA(dword_800811F0);
INCLUDE_DATA(dword_80081288);
INCLUDE_DATA(dword_80081320);
INCLUDE_DATA(dword_800813B8);
INCLUDE_DATA(dword_800813DC);
INCLUDE_DATA(dword_80081410);
INCLUDE_DATA(dword_800814B8);
INCLUDE_DATA(dword_800815E0);
INCLUDE_DATA(dword_80081620);
INCLUDE_DATA(dword_80081724);
INCLUDE_DATA(dword_80081854);
INCLUDE_DATA(dword_80081874);
INCLUDE_DATA(dword_800818C4);
INCLUDE_DATA(dword_8008198C);
INCLUDE_DATA(dword_80081A24);
INCLUDE_DATA(dword_80081ABC);
INCLUDE_DATA(dword_80081B54);
INCLUDE_DATA(dword_80081BEC);
INCLUDE_DATA(dword_80081C84);
INCLUDE_DATA(dword_80081D1C);
INCLUDE_DATA(dword_80081DB4);
INCLUDE_DATA(dword_80081E4C);
INCLUDE_DATA(dword_80081EE4);
INCLUDE_DATA(dword_80081F7C);
INCLUDE_DATA(dword_80082014);
INCLUDE_DATA(dword_800820AC);
INCLUDE_DATA(dword_800820F4);
INCLUDE_DATA(aSE);
INCLUDE_DATA(dword_800821A4);
INCLUDE_DATA(aXB);
INCLUDE_DATA(dword_800821E0);
INCLUDE_DATA(byte_8008229C);
INCLUDE_DATA(byte_80082334);
INCLUDE_DATA(byte_800823A0);
INCLUDE_DATA(dword_800823E8);
INCLUDE_DATA(byte_80082480);
INCLUDE_DATA(modelDescs_800824CC);
INCLUDE_DATA(dword_80082668);
INCLUDE_DATA(dword_8008266C);
INCLUDE_DATA(dword_80082670);
INCLUDE_DATA(dword_80082674);
INCLUDE_DATA(dword_80082678);
INCLUDE_DATA(largeDigitColors_800826F8);
INCLUDE_DATA(aRx);
INCLUDE_DATA(dword_8008276C);
INCLUDE_DATA(dword_8008279C);
INCLUDE_DATA(elementIcons_800827BC);
INCLUDE_DATA(elementIconsUnlit_800827D0);
INCLUDE_DATA(dword_800827E0);
INCLUDE_DATA(aFb);
INCLUDE_DATA(dword_800827EC);
INCLUDE_DATA(dword_800827F0);
INCLUDE_DATA(dword_800827F8);
INCLUDE_DATA(off_8008280C);
INCLUDE_DATA(dword_80082820);
INCLUDE_DATA(dword_80082824);
INCLUDE_DATA(dword_80082828);
INCLUDE_DATA(aH6p);
INCLUDE_DATA(dword_8008288C);
INCLUDE_DATA(aH6p_0);
INCLUDE_DATA(dword_800828FC);
INCLUDE_DATA(aH6p_1);
INCLUDE_DATA(dword_8008296C);
INCLUDE_DATA(aH6p_2);
INCLUDE_DATA(off_800829E8);
INCLUDE_DATA(word_800829FC);
INCLUDE_DATA(word_800829FE);
INCLUDE_DATA(word_80082A00);
INCLUDE_DATA(word_80082A02);
INCLUDE_DATA(dword_80082A04);
INCLUDE_DATA(aU6k);
INCLUDE_DATA(dword_80082A4C);
INCLUDE_DATA(aU6k_0);
INCLUDE_DATA(dword_80082AA0);
INCLUDE_DATA(aU6k_1);
INCLUDE_DATA(dword_80082AF4);
INCLUDE_DATA(aU6k_2);
INCLUDE_DATA(off_80082B54);
INCLUDE_DATA(dword_80082B68);
INCLUDE_DATA(a8);
INCLUDE_DATA(dword_80082BCC);
INCLUDE_DATA(a8_0);
INCLUDE_DATA(dword_80082C3C);
INCLUDE_DATA(a8_1);
INCLUDE_DATA(dword_80082CAC);
INCLUDE_DATA(a8_2);
INCLUDE_DATA(dword_80082D1C);
INCLUDE_DATA(a8_3);
INCLUDE_DATA(off_80082D98);
INCLUDE_DATA(aKumu);
INCLUDE_DATA(dword_80082DBC);
INCLUDE_DATA(off_80082DCC);
INCLUDE_DATA(aHroto);
INCLUDE_DATA(aNrutu);
INCLUDE_DATA(aNrdmnrdm);
INCLUDE_DATA(dword_80082E58);
INCLUDE_DATA(off_80082E90);
INCLUDE_DATA(dword_80082E9C);
INCLUDE_DATA(dword_80082EA0);
INCLUDE_DATA(dword_80082EA4);
INCLUDE_DATA(dword_80082EA8);
INCLUDE_DATA(dword_80082EB8);
INCLUDE_DATA(dword_80082EBC);
INCLUDE_DATA(rankNames_80082EC4);
INCLUDE_DATA(off_80082EE4);
INCLUDE_DATA(a1ftf);
INCLUDE_DATA(dword_80082EF0);
INCLUDE_DATA(dword_80082F04);
SoundInfo soundFiles_80082F0C[155] =
{
  { SOUND_PUBLIC_SND, 0, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 1, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 2, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 3, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 4, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 5, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, 6, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, -1, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, -1, 7u, 0u, -1 },
  { SOUND_PUBLIC_SND, -1, 7u, 0u, -1 },
  { SOUND_PUBLIC2_SND, -1, 16u, 16u, -1 },
  { SOUND_NAME_SND, 0, 1u, 0u, -1 },
  { SOUND_SABAKI_SND, 0, 1u, 0u, -1 },
  { SOUND_SAINIGHT_SND, 0, 1u, 0u, 44 },
  { SOUND_SAIRASU_SND, 0, 1u, 0u, 44 },
  { SOUND_SAISTONE_SND, 0, 2u, 0u, 44 },
  { SOUND_SHUUGEKI_SND, 0, 1u, 0u, 52 },
  { SOUND_TAMA_SND, 0, 1u, 0u, 64 },
  { SOUND_YAMU_SND, 0, 1u, 0u, 59 },
  { SOUND_ARUKANA_SND, 0, 1u, 0u, -1 },
  { SOUND_IJIGEN_SND, 0, 1u, 0u, 44 },
  { SOUND_IKENIE_SND, 0, 1u, 0u, 44 },
  { SOUND_KEKKAI_SND, 0, 1u, 0u, 63 },
  { SOUND_KEKKON_SND, 0, 1u, 0u, -1 },
  { SOUND_KIKINA_SND, 0, 1u, 0u, 58 },
  { SOUND_KORISU_SND, 0, 1u, 0u, 121 },
  { SOUND_KUMO_SND, 0, 1u, 0u, 115 },
  { SOUND_MTITLE_SND, 0, 1u, 0u, -1 },
  { SOUND_GOSHIN_SND, 0, 2u, 0u, 61 },
  { SOUND_MAP_SND, 0, 1u, 0u, -1 },
  { SOUND_MIKKAI_SND, 0, 3u, 0u, 51 },
  { SOUND_GA_SND, 0, 1u, 0u, 117 },
  { SOUND_TOMBO_SND, 0, 1u, 0u, 113 },
  { SOUND_NAGI_SND, 0, 1u, 0u, 62 },
  { SOUND_DREAM_SND, 0, 1u, 0u, 57 },
  { SOUND_LUI_SND, 0, 1u, 0u, 119 },
  { SOUND_MBOSS_SND, 0, 1u, 0u, 119 },
  { SOUND_IJIKIKI_SND, 0, 1u, 0u, 58 },
  { SOUND_IJIKORI_SND, 0, 1u, 0u, 121 },
  { SOUND_IJIKUMO_SND, 0, 1u, 0u, 115 },
  { SOUND_IJISHIN_SND, 0, 1u, 0u, 61 },
  { SOUND_IJITAMA_SND, 0, 1u, 0u, 64 },
  { SOUND_IJITOMBO_SND, 0, 1u, 0u, 113 },
  { SOUND_IJIYAMU_SND, 0, 1u, 0u, 59 },
  { SOUND_SE_SAI_SND, -1, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 0, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 1, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 2, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 3, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 4, 7u, 0u, -1 },
  { SOUND_SE_SAI_SND, 5, 7u, 0u, -1 },
  { SOUND_SE_MIHA1_SND, -1, 1u, 0u, -1 },
  { SOUND_SE_REBA3_SND, -1, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 0, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 1, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 2, 4u, 0u, -1 },
  { SOUND_SE_REBA3_SND, 3, 4u, 0u, -1 },
  { SOUND_SE_YUME1_SND, -1, 0u, 0u, -1 },
  { SOUND_SE_KIKI_SND, -1, 1u, 0u, -1 },
  { SOUND_SE_YAMU_SND, -1, 0u, 0u, -1 },
  { SOUND_SE_MBOSS_SND, -1, 1u, 0u, -1 },
  { SOUND_SE_SHIN_SND, -1, 5u, 0u, -1 },
  { SOUND_SE_NAGI_SND, -1, 1u, 0u, -1 },
  { SOUND_SE_MON_SND, -1, 0u, 0u, -1 },
  { SOUND_SE_TAMA_SND, -1, 3u, 0u, -1 },
  { SOUND_PUBTST2_SND, 0, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 1, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 2, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 3, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 4, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 5, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 6, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 7, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 8, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 9, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 10, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 11, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 12, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 13, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 14, 16u, 0u, -1 },
  { SOUND_PUBTST2_SND, 15, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 0, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 1, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 2, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 3, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 4, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 5, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 6, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 7, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 8, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 9, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 10, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 11, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 12, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 13, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 14, 16u, 0u, -1 },
  { SOUND_PUBTST3_SND, 15, 16u, 0u, -1 },
  { SOUND_SE_MBOSS_SND, 0, 1u, 0u, -1 },
  { SOUND_SE_SAI_SND, 6, 7u, 0u, -1 },
  { SOUND_SE_MIHA1_SND, 0, 1u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 0, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 1, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 2, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 3, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 4, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 5, 7u, 0u, -1 },
  { SOUND_SE_YAMU_SND, 6, 7u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 0, 5u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 1, 5u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 2, 5u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 3, 5u, 0u, -1 },
  { SOUND_SE_NAGI_SND, 0, 1u, 0u, -1 },
  { SOUND_SE_TAMA_SND, 0, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, -1, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, 0, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, -1, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, 0, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, -1, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, 0, 3u, 0u, -1 },
  { SOUND_SE_BTL_SND, -1, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 0, 7u, 0u, -1 },
  { SOUND_SE_KORI_SND, -1, 0u, 0u, -1 },
  { SOUND_NAGIZ_SND, 0, 1u, 0u, 123 },
  { SOUND_SE_NAGIZ_SND, -1, 0u, 0u, -1 },
  { SOUND_SAISTONE_SND, 1, 2u, 0u, 44 },
  { SOUND_GOSHIN_SND, 1, 2u, 0u, 61 },
  { SOUND_MIKKAI_SND, 1, 3u, 0u, 51 },
  { SOUND_SE_MRB_SND, 0, 1u, 0u, -1 },
  { SOUND_SYOU_SND, 0, 1u, 0u, -1 },
  { SOUND_SE_TAMA_SND, 1, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, 1, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, 1, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, 1, 3u, 0u, -1 },
  { SOUND_SE_BTL_SND, 1, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 2, 7u, 0u, -1 },
  { SOUND_SE_SHIN_SND, 4, 5u, 0u, -1 },
  { SOUND_SE_TAMA_SND, 2, 3u, 0u, -1 },
  { SOUND_SE_TOMBO_SND, 2, 3u, 0u, -1 },
  { SOUND_SE_KUMO_SND, 2, 3u, 0u, -1 },
  { SOUND_SE_GA_SND, 2, 3u, 0u, -1 },
  { SOUND_SE_MON_SND, 0, 1u, 0u, -1 },
  { SOUND_HORAGAI_SND, 0, 1u, 0u, -1 },
  { SOUND_ZAKKA_SND, 0, 1u, 0u, -1 },
  { SOUND_MATSURI_SND, 0, 1u, 0u, -1 },
  { SOUND_MIKKAI_SND, 2, 3u, 0u, 51 },
  { SOUND_BRACKMRC_SND, 0, 1u, 0u, 44 },
  { SOUND_LBOSS_SND, 0, 1u, 0u, 119 },
  { SOUND_SE_BTL_SND, 3, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 4, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 5, 7u, 0u, -1 },
  { SOUND_SE_BTL_SND, 6, 7u, 0u, -1 },
  { SOUND_SYOU_SND, -1, 1u, 0u, 123 },
  { SOUND_SE_KIKI_SND, 0, 1u, 0u, -1 },
  { SOUND_TAISEN_SND, 0, 1u, 0u, -1 },
  { SOUND_SAIRASU_SND, -1, 1u, 0u, 44 }
};
INCLUDE_DATA(seqSlots_800833E4);
INCLUDE_DATA(abilityNames_800834E4);
INCLUDE_DATA(abilityBonusNames_80083580);
INCLUDE_DATA(dword_80083594);
INCLUDE_DATA(dword_80083784);
INCLUDE_DATA(dword_80083788);
INCLUDE_DATA(dword_800837C4);
INCLUDE_DATA(off_800837D8);
INCLUDE_DATA(dword_800837EC);
INCLUDE_DATA(off_80083800);
INCLUDE_DATA(itemMessageSuffixes_80083818);
INCLUDE_DATA(off_80083820);
INCLUDE_DATA(dword_80083844);
INCLUDE_DATA(dword_8008384C);
INCLUDE_DATA(vibrationPatterns_80083B30);
INCLUDE_DATA(dword_80083BD0);
INCLUDE_DATA(dword_80083BD4);
INCLUDE_DATA(dword_80083BE4);
INCLUDE_DATA(dword_80083C0C);
INCLUDE_DATA(dword_80083C70);
INCLUDE_DATA(dword_80083CE8);
INCLUDE_DATA(dword_80083D00);
INCLUDE_DATA(dword_80084330);
INCLUDE_DATA(asc_80084350);
INCLUDE_DATA(word_80084540);

// Matched
int IsEffectReady_80014954(void)
{
    return ((EffectTaskState*)effectTask_8008D3F8->entry.buffer)->state_2C == 2;
}
// Matched
void StartEffect_8001497C(void)
{
    EffectTaskState* p = effectTask_8008D3F8->entry.buffer;
    p->flags_28 |= 1;
}
void sub_80015478(EventEntry* e, void* buf);
// Matched
void sub_800149A4(EffectArgs* p)
{
    EffectTaskState* q = effectTask_8008D3F8->entry.buffer;
    EventEntry* e;
    EffectObj* b;
    int n;
    int m;
    n = p->field_1E;
    m = q->timer_3C;
    effectOutcomeFlag_8008D780 = 0;
    if (m < n)
    {
        q->timer_3C = n;
    }
    e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b = e->buffer;
        b->field_E = *(short*)&p->field_0;
        b->field_14 = p->field_4;
        b->field_18 = p->field_8;
        b->field_1C = p->field_C;
        b->field_20 = p->field_10;
        b->field_2C = p->field_18;
        b->field_C = p->field_1C;
        b->field_A = p->field_1E;
        b->field_0 = 0;
        b->field_4 = 0;
        b->field_8 = 0;
        b->field_98 = p->field_24;
        b->field_9C = p->field_28;
        b->field_A0 = p->field_2C;
        *(unsigned char*)&b->field_A5 = *(unsigned char*)&q->field_40;
        b->field_A6 = q->field_42;
        b->field_AC = p->field_30;
        b->field_24.vx = p->scale_14[0] * ((SVECTOR*)p->field_28)[b->field_98].vx / 4096;
        b->field_24.vy = p->scale_14[1] * ((SVECTOR*)p->field_28)[b->field_98].vy / 4096;
        b->field_24.vz = p->scale_14[2] * ((SVECTOR*)p->field_28)[b->field_98].vz / 4096;
        if (p->field_2C)
        {
            b->field_24.vx = b->field_24.vx * ((int*)p->field_2C)[0] / 4096;
            b->field_24.vy = b->field_24.vy * ((int*)p->field_2C)[1] / 4096;
            b->field_24.vz = b->field_24.vz * ((int*)p->field_2C)[2] / 4096;
        }
        e->cb_8 = sub_80015478;
    }
}
// Matched
void sub_80014C28(int* a0, EffectObj* a1)
{
    if (effectOutcomeFlag_8008D780 == 1)
    {
        StopSoundSeqById_800306FC(6);
        *a0 = (*a0 & ~1) | 0x8000;
    }
    if (++a1->field_4 % 10 == 0)
    {
        sub_800C32DC(a1->field_1C, 30, 0, 0);
    }
}
typedef struct
{
    int pad_0[5];
    int pos_14[3];
    int field_20[3];
    short field_2C;
    short field_2E;
} CamView;
extern CamView cameraState_8008D4F0;
extern void sub_80044010(POLY_FT4* a0, int* pos, void* a2, short* uv, short* wh, short* a5, short* sz, short* col,
                         unsigned char* rgb, int a9, int a10, unsigned long* ot);
// Matched
void sub_80014CCC(int* a0, void* buf)
{
    EffectObj* a1 = buf;
    short sz[2];
    short col[4];
    int dir[3];
    int pos[3];
    int d[3];
    int pos2[3];
    unsigned char rgb[4];
    short sz2[2];
    int idx;
    EffectSprite* e1;
    EffectSprite* e2;
    EffectSpriteFrame* sp;
    int dot;
    int* c;
    int* t;

    a1->field_4++;
    PushMatrix();
    ApplyMatrix((MATRIX*)(a1->field_2C + a1->field_98 * 32), (SVECTOR*)&a1->field_24, (VECTOR*)a1->pos_44);
    PopMatrix();
    a1->pos_44[0] = ((int*)a1->field_20)[a1->field_98 * 3 + 0] + a1->pos_44[0];
    a1->pos_44[1] = ((int*)a1->field_20)[a1->field_98 * 3 + 1] + a1->pos_44[1];
    a1->pos_44[2] = ((int*)a1->field_20)[a1->field_98 * 3 + 2] + a1->pos_44[2];
    a1->pos_44[0] = ((int*)a1->field_1C)[0] + a1->pos_44[0];
    a1->pos_44[1] = ((int*)a1->field_1C)[1] + a1->pos_44[1];
    a1->pos_44[2] = ((int*)a1->field_1C)[2] + a1->pos_44[2];
    e1 = &effectFile_80091BD0.sprites_20[sub_80020F00(&effectFile_80091BD0, 0, 0x25)];
    idx = sub_80020F00(&effectFile_80091BD0, 0, 0x26);
    e2 = &effectFile_80091BD0.sprites_20[idx];
    sp = *e1->frames_8;
    sz[0] = sp->size_C[0] * (word_80084540[(a1->field_4 << 6) & 0xFC0] / 4 + 0x1000) / 4096;
    sz[1] = sp->size_C[1] * (word_80084540[(a1->field_4 << 6) & 0xFC0] / 4 + 0x1000) / 4096;
    col[0] = sp->pos_10[0];
    col[1] = sp->pos_10[1];
    col[2] = sp->pos_10[2];
    col[3] = a1->field_4 * 32;
    sub_80044010(&e1->poly_C, a1->pos_44, &a1->rot_80, &sp->u_0, &sp->w_4, &sp->f8, sz, col, sp->rgb_18, 2, 0x30,
                 pOT_8008D690);
    c = cameraState_8008D4F0.pos_14;
    rgb[0] = sp->rgb_18[0] >> 3;
    rgb[1] = sp->rgb_18[1] >> 3;
    rgb[2] = sp->rgb_18[1] >> 3;
    t = c + 3;
    pos[0] = a1->pos_44[0] - c[0];
    pos[1] = a1->pos_44[1] - c[1];
    pos[2] = a1->pos_44[2] - c[2];
    dir[0] = t[0] - c[0];
    dir[1] = t[1] - c[1];
    dir[2] = t[2] - c[2];
    VectorNormal((VECTOR*)dir, (VECTOR*)dir);
    dot = (dir[0] * pos[0] + dir[1] * pos[1] + dir[2] * pos[2]) / 4096;
    pos[0] = cameraState_8008D4F0.pos_14[0] + dir[0] * dot / 8192;
    pos[1] = cameraState_8008D4F0.pos_14[1] + dir[1] * dot / 8192;
    pos[2] = cameraState_8008D4F0.pos_14[2] + dir[2] * dot / 8192;
    if (cameraState_8008D4F0.field_2E < dot)
    {
        sz2[0] = sz[0] / 4;
        sz2[1] = sz[1] / 4;
        sub_80044010(&e2->poly_C, pos, &a1->rot_80, &sp->u_0, &sp->w_4, &sp->f8, sz2, col, rgb, 0, 0x30,
                     pOT_8008D690);
    }
    d[0] = a1->pos_44[0] - pos[0];
    d[1] = a1->pos_44[1] - pos[1];
    d[2] = a1->pos_44[2] - pos[2];
    if (cameraState_8008D4F0.field_2E * 4 / 3 < dot)
    {
        pos2[0] = pos[0] + d[0] / 2;
        pos2[1] = pos[1] + d[1] / 2;
        pos2[2] = pos[2] + d[2] / 2;
        sz2[0] = sz[0];
        sz2[1] = sz[1];
        sub_80044010(&e2->poly_C, pos2, &a1->rot_80, &sp->u_0, &sp->w_4, &sp->f8, sz2, col, rgb, 0, 0x30,
                     pOT_8008D690);
    }
    if (cameraState_8008D4F0.field_2E * 2 < dot)
    {
        pos2[0] = pos[0] - d[0] / 2;
        pos2[1] = pos[1] - d[1] / 2;
        pos2[2] = pos[2] - d[2] / 2;
        sz2[0] = sz[0] / 2;
        sz2[1] = sz[1] / 2;
        sub_80044010(&e2->poly_C, pos2, &a1->rot_80, &sp->u_0, &sp->w_4, &sp->f8, sz2, col, rgb, 0, 0x30,
                     pOT_8008D690);
    }
    if (cameraState_8008D4F0.field_2E * 4 / 3 < dot)
    {
        pos2[0] = pos[0] - d[0] / 4;
        pos2[1] = pos[1] - d[1] / 4;
        pos2[2] = pos[2] - d[2] / 4;
        sz2[0] = sz[0] * 2;
        sz2[1] = sz[1] * 2;
        sub_80044010(&e2->poly_C, pos2, &a1->rot_80, &sp->u_0, &sp->w_4, &sp->f8, sz2, col, rgb, 0, 0x30,
                     pOT_8008D690);
    }
    if (effectOutcomeFlag_8008D780 == 1)
    {
        *a0 = (*a0 & ~1) | 0x8000;
    }
}
extern SVECTOR dword_800795D4;
extern int dword_800795DC;
extern int dword_800795E0;
extern int dword_800795E4;
extern int dword_800795E8;
extern int dword_800795EC;
extern int dword_8008D784;
extern int DistanceSquared3D_8003B80C(int* a, int* b);
extern void sub_800C1A5C(void* a0, void* a1, int a2, int a3);
extern void sub_800C1C5C(void* a0, void* a1, int a2, int a3);
extern void sub_800C1654(void* a0, void* a1, int a2, int a3, int a4, int a5);
extern void sub_800C1FFC(void* a0, void* a1, int a2, int a3, int a4);
extern void sub_800C2E28(int a0, void* a1, int a2, int a3, int a4, int a5);
extern void sub_800C2914(void* a0, int a1);
extern void sub_800C1190(int a0, int a1);
extern void sub_800C10B8(int a0, int a1);
extern void PlayMusic_800300E0(int a, int b);
extern void PlaySeqSlot_80031160(int idx, int loops);
extern void PlaySfx_80031494(int a);
extern void SpawnMdecEffect_80017A6C(int a0, int a1);
extern void sub_80017158(int* a0, void* a1);
extern void sub_800174F8(void* a0, int a1);
extern void sub_80017290(void* a0, int a1);
extern void sub_80017E30(EventEntry* e, void* buf);
extern void sub_80016E20(int* a0, void* buf);
extern void sub_80016FC8(int* a0, int* a1);
extern void sub_800C371C(EventEntry* e, void* buf);
extern void sub_800C1450(EventEntry* e, void* buf);
#define EFF(i) ((int)&effectFile_80091BD0.sprites_20[i])
// Matched
void sub_80015478(EventEntry* e, void* buf)
{
    EffectObj* b = (EffectObj*)buf;
    int idx;
    int i;
    int n;
    int f;
    void* p;

    b->pos_50[0] = b->pos_44[0];
    b->pos_50[1] = b->pos_44[1];
    b->pos_50[2] = b->pos_44[2];
    PushMatrix();
    ApplyMatrix((MATRIX*)(b->field_2C + b->field_98 * 32), &b->field_24, (VECTOR*)b->pos_44);
    PopMatrix();
    b->pos_44[0] = ((int*)b->field_20)[b->field_98 * 3 + 0] + b->pos_44[0];
    b->pos_44[1] = ((int*)b->field_20)[b->field_98 * 3 + 1] + b->pos_44[1];
    b->pos_44[2] = ((int*)b->field_20)[b->field_98 * 3 + 2] + b->pos_44[2];
    b->pos_44[0] = ((int*)b->field_1C)[0] + b->pos_44[0];
    b->pos_44[1] = ((int*)b->field_1C)[1] + b->pos_44[1];
    b->pos_44[2] = ((int*)b->field_1C)[2] + b->pos_44[2];
    if (b->field_0 >= b->field_C)
    {
        switch (b->field_E)
        {
        case 0:
            if (b->field_0 != 0)
            {
                int v[3];
                int d[3];
                int k;
                int m;
                b->field_4 += ISqrt_8003B918(DistanceSquared3D_8003B80C(b->pos_44, b->pos_50));
                d[0] = b->pos_44[0] - b->pos_50[0];
                d[1] = b->pos_44[1] - b->pos_50[1];
                d[2] = b->pos_44[2] - b->pos_50[2];
                if (b->field_4 > 0x80)
                {
                    m = b->field_4 / 128;
                    for (k = 0; k < m; k++)
                    {
                        v[0] = b->pos_50[0] + d[0] * k / m;
                        v[1] = b->pos_50[1] + d[1] * k / m;
                        v[2] = b->pos_50[2] + d[2] * k / m;
                        b->field_4 -= 0x80;
                        sub_800C1A5C(v, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0)), 0x1000);
                    }
                }
            }
            break;
        case 19:
        case 44:
            if (b->field_0 == b->field_C)
            {
                sub_800C32DC(b->field_1C, 0x21, 0, 0);
                if (b->field_0 < b->field_A)
                {
                    PlayMusic_800300E0(6, 1);
                }
            }
            if (b->field_0 % 12 == 0)
            {
                sub_800C32DC(b->field_1C, 0x22, 0, 0);
            }
            if (b->field_0 % 9 == 3)
            {
                sub_800C32DC(b->field_1C, 0x23, 0, 0);
            }
            if (b->field_0 % 9 == 6)
            {
                sub_800C32DC(b->field_1C, 0x24, 0, 0);
            }
            if (b->field_0 >= b->field_A)
            {
                StopSoundSeqById_800306FC(6);
            }
            break;
        case 18:
            if (b->field_0 == 0)
            {
                if (b->field_A != 0)
                {
                    PlayMusic_800300E0(6, 1);
                }
                sub_800C32DC(b->field_1C, 0, 0, 0);
            }
            if (b->field_0 == b->field_A)
            {
                StopSoundSeqById_800306FC(6);
            }
            break;
        case 37:
            if (b->field_0 == 0)
            {
                PlayMusic_800300E0(6, 1);
                sub_800C32DC(b->field_1C, 3, 0, 0);
            }
            if (b->field_0 == b->field_A)
            {
                StopSoundSeqById_800306FC(6);
            }
            break;
        case 21:
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x27)), 0x1000);
            break;
        case 52:
            if (b->field_0 == 0 && dword_8008D784 == 0)
            {
                dword_8008D784 = 1;
                sub_800C1190(b->field_A - b->field_C, 0x45);
            }
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x1AC)), 0x1000);
            break;
        case 23:
            n = -1;
            if (b->field_0 == 0 && dword_8008D784 == 0)
            {
                dword_8008D784 = 1;
                sub_800C1190(b->field_A - b->field_C, 0x45);
            }
            switch (b->field_A5)
            {
            case 4:
                n = 0x1A;
                break;
            case 5:
                n = 0x1C;
                break;
            case 6:
                n = 0x20;
                break;
            case -1:
            case 7:
            case 8:
            case 9:
                n = 0x23;
                break;
            case 0:
                n = 0x14;
                break;
            case 3:
                n = 0x22;
                break;
            case 2:
                n = 0x11;
                break;
            case 1:
                n = 8;
                break;
            }
            if (n >= 0)
            {
                sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, n)), 0x2000);
            }
            break;
        case 26:
            PlayMusic_800300E0(6, 1);
            e->cb_8 = (EventEntryFn)sub_80014C28;
            return;
        case 25:
            PlaySfx_80031494(0x50);
            SpawnMdecEffect_80017A6C((int)b, 600);
            e->cb_8 = (EventEntryFn)sub_80014CCC;
            return;
        case 24:
            if (b->field_AC & 4)
            {
                break;
            }
            p = 0;
            n = -1;
            f = 0;
            switch (b->field_A5)
            {
            case -1:
                p = &dword_800795DC;
                n = 0x23;
                break;
            case 0:
                p = &dword_800795E0;
                n = 0x14;
                break;
            case 3:
                p = &dword_800795E4;
                n = 0x22;
                break;
            case 2:
                p = &dword_800795E8;
                n = 0x11;
                break;
            case 1:
                p = &dword_800795EC;
                n = 8;
                break;
            case 4:
                p = &dword_800795EC;
                n = 0x1A;
                break;
            case 5:
                p = &dword_800795EC;
                n = 0x1C;
                break;
            case 6:
                p = &dword_800795EC;
                n = 0x20;
                break;
            case 7:
                p = &dword_800795EC;
                n = 0xE;
                break;
            case 8:
                p = &dword_800795EC;
                n = 0x23;
                f = 1;
                break;
            case 9:
                p = &dword_800795E4;
                n = 0x23;
                f = 1;
                sub_800C32DC((int)b->pos_44, 0xC0, 0, 0);
                break;
            case 10:
                n = -1;
                sub_800C32DC((int)b->pos_44, 0xC0, 0, 0);
                break;
            }
            b->field_A5 = -1;
            if (n < 0)
            {
                break;
            }
            PlaySeqSlot_80031160(0x13, 1);
            if (f)
            {
                sub_800C1654(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, n)), 0x800, b->field_14, b->field_18 + 0x18);
            }
            else
            {
                sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, n)), 0, 0x1E);
            }
            sub_80017158(b->pos_44, p);
            break;
        case 1:
            if (b->field_AC & 2)
            {
                break;
            }
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 2)), 0x1000);
            sub_800C1C5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 1)), 0x1000);
            break;
        case 3:
        {
            short s[3];
            s[0] = dword_800795D4.vx;
            s[1] = dword_800795D4.vy;
            s[2] = dword_800795D4.vz;
            for (i = 0; i < 3; i++)
            {
                s[1] = (i << 12) / 3;
                sub_800C1A5C(b->pos_44, s, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x24)), 0x1000);
                sub_800C32DC((int)b->pos_44, 0xBF, 0, s[1]);
            }
            break;
        }
        case 4:
        {
            EventEntry* e2;
            EffectObj* q;
            EffectModel* t;
            e2 = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
            if (e2 == 0)
            {
                break;
            }
            q = (EffectObj*)e2->buffer;
            q->field_8 = 0;
            q->field_0 = 0;
            q->field_4 = 600;
            q->field_30 = 0;
            q->field_1C = b->field_1C;
            q->field_20 = b->field_20;
            q->field_A0 = b->field_A0;
            q->field_20 = b->field_20;
            q->field_98 = b->field_98;
            idx = sub_80020F00(&effectFile_80091BD0, 1, 0x1E);
            e2->flags = (e2->flags | 1) & 0xFFFF7FFF;
            t = &effectFile_80091BD0.models_28[idx];
            q->field_88 = (int)t;
            sub_800218A8(t->ftg_4, q->work_94 = malloc3_8003FC4C(0x54), 1);
            sub_80039FE4(t->ftg_4, t->ftg_4 + 1, q->work_94);
            PlaySeqSlot_80031160(9, 1);
            e2->cb_8 = sub_800C371C;
            break;
        }
        case 48:
            PlaySeqSlot_80031160(0x13, 1);
            SpawnMdecEffect_80017A6C((int)b, effectFile_80091BD0.sprites_20[sub_80020F00(&effectFile_80091BD0, 0, 0x1B)].count_0);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x1B)), 0x1000);
            if (b->field_AC & 4)
            {
                break;
            }
            sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x1A)), 0, 0x1E);
            break;
        case 50:
            PlaySeqSlot_80031160(0x13, 1);
            SpawnMdecEffect_80017A6C((int)b, effectFile_80091BD0.sprites_20[sub_80020F00(&effectFile_80091BD0, 0, 0x1E)].count_0);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x1E)), 0x1000);
            sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x1D)), 0, 0xC);
            if (b->field_AC & 4)
            {
                break;
            }
            sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x1C)), 0, 0x1E);
            break;
        case 49:
            PlaySeqSlot_80031160(0x13, 1);
            SpawnMdecEffect_80017A6C((int)b, sub_800C32DC((int)b->pos_44, 0x16, 0, 0));
            if (b->field_AC & 4)
            {
                break;
            }
            sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x20)), 0, 0x1E);
            break;
        case 30:
            sub_800174F8(b, 5);
            SpawnMdecEffect_80017A6C((int)b, 100);
            PlaySeqSlot_80031160(0x13, 1);
            sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0xD)), 0, 0xC);
            if (b->field_AC & 4)
            {
                break;
            }
            sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0xD)), 0, 0x1E);
            break;
        case 6:
            PlaySeqSlot_80031160(0xE, 1);
            sub_800C2914(b, 0x18);
            SpawnMdecEffect_80017A6C((int)b, 100);
            break;
        case 9:
        {
            short s[3];
            PlaySeqSlot_80031160(0x16, 1);
            s[0] = dword_800795D4.vx;
            s[1] = dword_800795D4.vy;
            s[2] = dword_800795D4.vz;
            for (i = 0; i < 5; i++)
            {
                s[1] = (i << 12) / 5;
                sub_800C1A5C(b->pos_44, s, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x12)), 0x1000);
                sub_800C32DC(b->field_1C, 0xB, 0, s[1]);
            }
            SpawnMdecEffect_80017A6C((int)b, effectFile_80091BD0.sprites_20[sub_80020F00(&effectFile_80091BD0, 0, 0x12)].count_0);
            break;
        }
        case 8:
            PlaySeqSlot_80031160(0x10, 1);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0xA)), 0x1000);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 9)), 0x1000);
            SpawnMdecEffect_80017A6C((int)b, effectFile_80091BD0.sprites_20[sub_80020F00(&effectFile_80091BD0, 0, 0xA)].count_0);
            break;
        case 20:
        {
            int t;
            PlaySeqSlot_80031160(0x14, 1);
            t = EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x18));
            idx = sub_80020F00(&effectFile_80091BD0, 1, 0x13);
            sub_800C2E28(b->field_1C, &dword_800795D4, t, (int)&effectFile_80091BD0.models_28[idx], 0x1000, 6);
            sub_800C32DC(b->field_1C, 0x12, 0, 0);
            break;
        }
        case 13:
            sub_800C1FFC(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x1F)), 0, 0x1E);
            break;
        case 12:
        {
            short s[3];
            s[0] = dword_800795D4.vx;
            s[1] = dword_800795D4.vy;
            s[2] = dword_800795D4.vz;
            SpawnMdecEffect_80017A6C((int)b, sub_800C32DC(b->field_1C, 0xB1, 0, 0));
            break;
        }
        case 11:
        case 15:
        case 16:
        case 17:
            PlaySfx_80031494(0x48);
            SpawnMdecEffect_80017A6C((int)b, sub_800C32DC(b->field_1C, 0x1C, 0, 0));
            break;
        case 27:
        {
            EffectModel* t;
            idx = sub_80020F00(&effectFile_80091BD0, 1, 0x15);
            t = &effectFile_80091BD0.models_28[idx];
            b->field_88 = (int)t;
            sub_800218A8(t->ftg_4, b->work_94 = malloc3_8003FC4C(0x54), 1);
            sub_80039FE4(t->ftg_4, t->ftg_4 + 1, b->work_94);
            b->field_30 = 0x1000;
            e->cb_8 = sub_80017E30;
            PlaySfx_80031494(0x4A);
            SpawnMdecEffect_80017A6C((int)b, 0x40);
            return;
        }
        case 28:
        case 34:
        case 35:
        case 36:
            PlaySeqSlot_80031160(0x15, 1);
            SpawnMdecEffect_80017A6C((int)b, sub_800C32DC(b->field_1C, 0x17, 0, 0));
            break;
        case 29:
            PlaySeqSlot_80031160(0x12, 1);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0xC)), 0x1000);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0xB)), 0x1000);
            SpawnMdecEffect_80017A6C((int)b, effectFile_80091BD0.sprites_20[sub_80020F00(&effectFile_80091BD0, 0, 0xC)].count_0);
            sub_800C32DC(b->field_1C, 4, 0, 0);
            break;
        case 7:
        {
            int r;
            r = sub_800C32DC(b->field_1C, 0x10, 0, 0);
            SpawnMdecEffect_80017A6C((int)b, r);
            sub_800C10B8(r, 0xD);
            break;
        }
        case 32:
            sub_80017290(b, 0x11);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x17)), 0x1000);
            sub_800C10B8(0x35, 0xD);
            break;
        case 33:
            PlaySeqSlot_80031160(0x17, 1);
            sub_800C1C5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x13)), 0x1000);
            sub_800C32DC(b->field_1C, 0xC, 0, 0);
            sub_800C32DC(b->field_1C, 0xD, 0, 0);
            break;
        case 31:
            PlaySeqSlot_80031160(0xF, 1);
            SpawnMdecEffect_80017A6C((int)b, sub_800C32DC(b->field_1C, 0x1A, 0, 0));
            break;
        case 38:
            PlaySfx_80031494(0x20);
            PlaySfx_80031494(0x21);
            PlaySfx_80031494(0x22);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 7)), 0x1000);
            sub_800C32DC(b->field_1C, 1, 0, 0);
            sub_800C32DC(b->field_1C, 2, 0, 0);
            break;
        case 39:
            sub_800C1190(0x14, 0x23);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 0x19)), 0x1000);
            sub_800C32DC(b->field_1C, 0x14, 0, ratan2Difference_8003B9E0((int*)b->field_1C, (int*)b->field_14));
            b->field_4 = 3;
            e->cb_8 = (EventEntryFn)sub_80016BF4;
            return;
        case 42:
            PlaySeqSlot_80031160(0x14, 1);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 6)), 0x1000);
            b->field_88 = EFF(sub_80020F00(&effectFile_80091BD0, 0, 6));
            b->field_8C = EFF(sub_80020F00(&effectFile_80091BD0, 0, 5));
            b->field_90 = EFF(sub_80020F00(&effectFile_80091BD0, 0, 5));
            b->field_8 = 0x1000;
            b->field_4 = 0;
            e->cb_8 = sub_800C1450;
            return;
        case 41:
            PlaySeqSlot_80031160(0x14, 1);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 4)), 0x1000);
            b->field_88 = EFF(sub_80020F00(&effectFile_80091BD0, 0, 4));
            b->field_8C = EFF(sub_80020F00(&effectFile_80091BD0, 0, 3));
            b->field_90 = EFF(sub_80020F00(&effectFile_80091BD0, 0, 3));
            b->field_8 = 0x1000;
            b->field_4 = 0;
            e->cb_8 = sub_800C1450;
            return;
        case 43:
            PlaySeqSlot_80031160(0x14, 1);
            sub_800C1A5C(b->pos_44, &dword_800795D4, EFF(sub_80020F00(&effectFile_80091BD0, 0, 4)), 0x1000);
            b->field_88 = EFF(sub_80020F00(&effectFile_80091BD0, 0, 4));
            b->field_8C = EFF(sub_80020F00(&effectFile_80091BD0, 0, 3));
            b->field_90 = EFF(sub_80020F00(&effectFile_80091BD0, 0, 5));
            b->field_8 = 0x1000;
            b->field_4 = 0;
            e->cb_8 = sub_800C1450;
            return;
        case 40:
            b->field_4 = 0;
            e->cb_8 = (EventEntryFn)sub_80016E20;
            return;
        case 47:
            SpawnMdecEffect_80017A6C((int)b, 100);
            b->field_4 = 0;
            e->cb_8 = (EventEntryFn)sub_80016FC8;
            return;
        case 51:
            if (b->field_AC & 0x38)
            {
                PlaySfx_80031494(0x49);
                b->field_4 = 0x10;
                sub_800C32DC((int)b->pos_44, 6, 0, 0);
            }
            break;
        }
    }
    if (b->field_0 >= b->field_A)
    {
        e->flags = (e->flags & ~1) | 0x8000;
    }
    b->field_0++;
}
#undef EFF
