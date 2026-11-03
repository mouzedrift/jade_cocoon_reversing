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
INCLUDE_DATA(off_8007C348);
INCLUDE_DATA(dword_8007C438);
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
INCLUDE_DATA(off_8007DAE0);
INCLUDE_DATA(dword_8007DB08);
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
INCLUDE_DATA(off_800824CC);
INCLUDE_DATA(dword_80082668);
INCLUDE_DATA(dword_8008266C);
INCLUDE_DATA(dword_80082670);
INCLUDE_DATA(dword_80082674);
INCLUDE_DATA(dword_80082678);
INCLUDE_DATA(dword_800826F8);
INCLUDE_DATA(aRx);
INCLUDE_DATA(dword_8008276C);
INCLUDE_DATA(dword_8008279C);
INCLUDE_DATA(dword_800827BC);
INCLUDE_DATA(dword_800827D0);
INCLUDE_DATA(dword_800827E0);
INCLUDE_DATA(aFb);
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
INCLUDE_DATA(off_80082EC4);
INCLUDE_DATA(off_80082EE4);
INCLUDE_DATA(a1ftf);
INCLUDE_DATA(dword_80082EF0);
INCLUDE_DATA(dword_80082F04);
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
INCLUDE_DATA(dword_800833E4);
INCLUDE_DATA(off_800834E4);
INCLUDE_DATA(off_80083580);
INCLUDE_DATA(dword_80083594);
INCLUDE_DATA(dword_80083784);
INCLUDE_DATA(dword_80083788);
INCLUDE_DATA(dword_800837C4);
INCLUDE_DATA(off_800837D8);
INCLUDE_DATA(dword_800837EC);
INCLUDE_DATA(off_80083800);
INCLUDE_DATA(off_80083818);
INCLUDE_DATA(off_80083820);
INCLUDE_DATA(dword_80083844);
INCLUDE_DATA(dword_8008384C);
INCLUDE_DATA(off_80083B30);
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
int sub_80014954(void)
{
    return ((int*)dword_8008D3F8[9])[0x2C / 4] == 2;
}
// Matched
void sub_8001497C(void)
{
    int* p = dword_8008D3F8[9];
    p[0x28 / 4] |= 1;
}
void sub_80015478(EventEntry* e, void* buf);
// Matched
void sub_800149A4(char* p)
{
    char* q = (char*)dword_8008D3F8[9];
    EventEntry* e;
    char* b;
    int n;
    int m;
    n = *(short*)(p + 0x1E);
    m = *(int*)(q + 0x3C);
    effectOutcomeFlag_8008D780 = 0;
    if (m < n)
    {
        *(int*)(q + 0x3C) = n;
    }
    e = AllocEventEntry_80043AF8(dword_8008B4A8);
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b = (char*)e->buffer;
        *(short*)(b + 0xE) = *(short*)(p + 0);
        *(int*)(b + 0x14) = *(int*)(p + 0x4);
        *(int*)(b + 0x18) = *(int*)(p + 0x8);
        *(int*)(b + 0x1C) = *(int*)(p + 0xC);
        *(int*)(b + 0x20) = *(int*)(p + 0x10);
        *(int*)(b + 0x2C) = *(int*)(p + 0x18);
        *(short*)(b + 0xC) = *(short*)(p + 0x1C);
        *(short*)(b + 0xA) = *(short*)(p + 0x1E);
        *(int*)(b + 0x0) = 0;
        *(int*)(b + 0x4) = 0;
        *(short*)(b + 0x8) = 0;
        *(int*)(b + 0x98) = *(int*)(p + 0x24);
        *(int*)(b + 0x9C) = *(int*)(p + 0x28);
        *(int*)(b + 0xA0) = *(int*)(p + 0x2C);
        *(unsigned char*)(b + 0xA5) = *(unsigned char*)(q + 0x40);
        *(short*)(b + 0xA6) = *(short*)(q + 0x42);
        *(int*)(b + 0xAC) = *(int*)(p + 0x30);
        *(short*)(b + 0x24) = (*(short**)(p + 0x14))[0] * ((short*)(*(int*)(p + 0x28) + *(int*)(b + 0x98) * 8))[0] / 4096;
        *(short*)(b + 0x26) = (*(short**)(p + 0x14))[1] * ((short*)(*(int*)(p + 0x28) + *(int*)(b + 0x98) * 8))[1] / 4096;
        *(short*)(b + 0x28) = (*(short**)(p + 0x14))[2] * ((short*)(*(int*)(p + 0x28) + *(int*)(b + 0x98) * 8))[2] / 4096;
        if (*(int*)(p + 0x2C))
        {
            *(short*)(b + 0x24) = *(short*)(b + 0x24) * (*(int**)(p + 0x2C))[0] / 4096;
            *(short*)(b + 0x26) = *(short*)(b + 0x26) * (*(int**)(p + 0x2C))[1] / 4096;
            *(short*)(b + 0x28) = *(short*)(b + 0x28) * (*(int**)(p + 0x2C))[2] / 4096;
        }
        e->cb_8 = sub_80015478;
    }
}
// Matched
void sub_80014C28(int* a0, int* a1)
{
    if (effectOutcomeFlag_8008D780 == 1)
    {
        sub_800306FC(6);
        *a0 = (*a0 & ~1) | 0x8000;
    }
    if (++a1[1] % 10 == 0)
    {
        sub_800C32DC(a1[7], 30, 0, 0);
    }
}
INCLUDE_ASM(sub_80014CCC);
INCLUDE_ASM(sub_80015478);
