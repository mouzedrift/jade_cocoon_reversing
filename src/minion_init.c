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
#include "actor.h"
#include "unit.h"
#include "engine.h"
#include "minion_init.h"
#include "effect_data.h"

const char aKlarrgas_80072310[] = "\202j\202\214\202\201\202\222\202\222\202\207\202\201\202\223"; // Klarrgas
const char aYolga_80072324[] = "\202x\202\217\202\214\202\207\202\201"; // Yolga
const char aTimaios_80072330[] = "\202s\202\211\202\215\202\201\202\211\202\217\202\223"; // Timaios
const char aSicanjal_80072340[] = "\202r\202\211\202\203\202\201\202\216\202\212\202\201\202\214"; // Sicanjal
const char aKolna_80072354[] = "\202j\202\217\202\214\202\216\202\201"; // Kolna
const char aJeechwo_80072360[] = "\202i\202\205\202\205\202\203\202\210\202\227\202\217"; // Jeechwo
const char aTicker_80072370[] = "\202s\202\211\202\203\202\213\202\205\202\222"; // Ticker
const char aPalooja_80072380[] = "\202o\202\201\202\214\202\217\202\217\202\212\202\201"; // Palooja
const char aTyton_80072390[] = "\202s\202\231\202\224\202\217\202\216"; // Tyton
const char aSbarse_8007239C[] = "\202r\202\202\202\201\202\222\202\223\202\205"; // Sbarse
const char aSetolka_800723AC[] = "\202r\202\205\202\224\202\217\202\214\202\213\202\201"; // Setolka
const char aLakshel_800723BC[] = "\202k\202\201\202\213\202\223\202\210\202\205\202\214"; // Lakshel
const char aKetow_800723CC[] = "\202j\202\205\202\224\202\217\202\227"; // Ketow
const char aIbdamia_800723D8[] = "\202h\202\202\202\204\202\201\202\215\202\211\202\201"; // Ibdamia
const char aShakures_800723E8[] = "\202r\202\210\202\201\202\213\202\225\202\222\202\205\202\223"; // Shakures
const char aColunius_800723FC[] = "\202b\202\217\202\214\202\225\202\216\202\211\202\225\202\223"; // Colunius
const char aNarade_80072410[] = "\202m\202\201\202\222\202\201\202\204\202\205"; // Narade
const char aKarro_80072420[] = "\202j\202\201\202\222\202\222\202\217"; // Karro
const char aSaramoon_8007242C[] = "\202r\202\201\202\222\202\201\202\215\202\217\202\217\202\216"; // Saramoon
const char aNupandra_80072440[] = "\202m\202\225\202\220\202\201\202\216\202\204\202\222\202\201"; // Nupandra
const char aAgghai_80072454[] = "\202`\202\207\202\207\202\210\202\201\202\211"; // Agghai
const char aGreydon_80072464[] = "\202f\202\222\202\205\202\231\202\204\202\217\202\216"; // Greydon
const char aArmijar_80072474[] = "\202`\202\222\202\215\202\211\202\212\202\201\202\222"; // Armijar
const char aBauback_80072484[] = "\202a\202\201\202\225\202\202\202\201\202\203\202\213"; // Bauback
const char aKamra_80072494[] = "\202j\202\201\202\215\202\222\202\201"; // Kamra
const char aFedelco_800724A0[] = "\202e\202\205\202\204\202\205\202\214\202\203\202\217"; // Fedelco
const char aArvalzak_800724B0[] = "\202`\202\222\202\226\202\201\202\214\202\232\202\201\202\213"; // Arvalzak
const char aSpiral_800724C4[] = "\202r\202\220\202\211\202\222\202\201\202\214"; // Spiral
const char aOhzay_800724D4[] = "\202n\202\210\202\232\202\201\202\231"; // Ohzay
const char aAiona_800724E0[] = "\202`\202\211\202\217\202\216\202\201"; // Aiona
const char aNevan_800724EC[] = "\202m\202\205\202\226\202\201\202\216"; // Nevan
const char aYates_800724F8[] = "\202x\202\201\202\224\202\205\202\223"; // Yates
const char aRainster_80072504[] = "\202q\202\201\202\211\202\216\202\223\202\224\202\205\202\222"; // Rainster
const char aTuren_80072518[] = "\202s\202\225\202\222\202\205\202\216"; // Turen
const char aFintan_80072524[] = "\202e\202\211\202\216\202\224\202\201\202\216"; // Fintan
const char aBawni_80072534[] = "\202a\202\201\202\227\202\216\202\211"; // Bawni
const char aId_80072540[] = "\202h\202\204"; // Id
const char aFugger_80072548[] = "\202e\202\225\202\207\202\207\202\205\202\222"; // Fugger
const char aCarlidge_80072558[] = "\202b\202\201\202\222\202\214\202\211\202\204\202\207\202\205"; // Carlidge
const char aSwav_8007256C[] = "\202r\202\227\202\201\202\226"; // Swav
const char aOhma_80072578[] = "\202n\202\210\202\215\202\201"; // Ohma
const char aGalia_80072584[] = "\202f\202\201\202\214\202\211\202\201"; // Galia
const char aAnkoo_80072590[] = "\202`\202\216\202\213\202\217\202\217"; // Ankoo
const char aWardon_8007259C[] = "\202v\202\201\202\222\202\204\202\217\202\216"; // Wardon
const char aTiootz_800725AC[] = "\202s\202\211\202\217\202\217\202\224\202\232"; // Tiootz
const char aSgaj_800725BC[] = "\202r\202\207\202\201\202\212"; // Sgaj
const char aSowl_800725C8[] = "\202r\202\217\202\227\202\214"; // Sowl
const char aFrey_800725D4[] = "\202e\202\222\202\205\202\231"; // Frey
const char aRobun_800725E0[] = "\202q\202\217\202\202\202\225\202\216"; // Robun
const char aElu_800725EC[] = "\202d\202\214\202\225"; // Elu
const char aShowven_800725F4[] = "\202r\202\210\202\217\202\227\202\226\202\205\202\216"; // Showven
const char aFrigg_80072604[] = "\202e\202\222\202\211\202\207\202\207"; // Frigg
const char aZulmoo_80072610[] = "\202y\202\225\202\214\202\215\202\217\202\217"; // Zulmoo
const char aPedingo_80072620[] = "\202o\202\205\202\204\202\211\202\216\202\207\202\217"; // Pedingo
const char aTuloon_80072630[] = "\202s\202\225\202\214\202\217\202\217\202\216"; // Tuloon
const char aGabee_80072640[] = "\202f\202\201\202\202\202\205\202\205"; // Gabee
const char aEmbla_8007264C[] = "\202d\202\215\202\202\202\214\202\201"; // Embla
const char aEavun_80072658[] = "\202d\202\201\202\226\202\225\202\216"; // Eavun
const char aOajin_80072664[] = "\202n\202\201\202\212\202\211\202\216"; // Oajin
const char aUsk_80072670[] = "\202t\202\223\202\213"; // Usk
const char aUld_80072678[] = "\202t\202\214\202\204"; // Uld
const char aScul_80072680[] = "\202r\202\203\202\225\202\214"; // Scul
const char aTelma_8007268C[] = "\202s\202\205\202\214\202\215\202\201"; // Telma
const char aKarn_80072698[] = "\202j\202\201\202\222\202\216"; // Karn
const char aFal_800726A4[] = "\202e\202\201\202\214"; // Fal
const char aShee_800726AC[] = "\202r\202\210\202\205\202\205"; // Shee
const char aShulia_800726B8[] = "\202r\202\210\202\225\202\214\202\211\202\201"; // Shulia
const char aAnash_800726C8[] = "\202`\202\216\202\201\202\223\202\210"; // Anash
const char aRadmine_800726D4[] = "\202q\202\201\202\204\202\215\202\211\202\216\202\205"; // Radmine
const char aTeramine_800726E4[] = "\202s\202\205\202\222\202\201\202\215\202\211\202\216\202\205"; // Teramine
const char aSkwmaine_800726F8[] = "\202r\202\213\202\227\202\215\202\201\202\211\202\216\202\205"; // Skwmaine
const char aCarmine_8007270C[] = "\202b\202\201\202\222\202\215\202\211\202\216\202\205"; // Carmine
const char aRadmoaj_8007271C[] = "\202q\202\201\202\204\202\215\202\217\202\201\202\212"; // Radmoaj
const char aTeramoaj_8007272C[] = "\202s\202\205\202\222\202\201\202\215\202\217\202\201\202\212"; // Teramoaj
const char aSkwmoaj_80072740[] = "\202r\202\213\202\227\202\215\202\217\202\201\202\212"; // Skwmoaj
const char aPatamoaj_80072750[] = "\202o\202\201\202\224\202\201\202\215\202\217\202\201\202\212"; // Patamoaj
const char aRadoot_80072764[] = "\202q\202\201\202\204\202\217\202\217\202\224"; // Radoot
const char aTeraoot_80072774[] = "\202s\202\205\202\222\202\201\202\217\202\217\202\224"; // Teraoot
const char aSkwoot_80072784[] = "\202r\202\213\202\227\202\217\202\217\202\224"; // Skwoot
const char aPataoot_80072794[] = "\202o\202\201\202\224\202\201\202\217\202\217\202\224"; // Pataoot
const char aRadkooga_800727A4[] = "\202q\202\201\202\204\202\213\202\217\202\217\202\207\202\201"; // Radkooga
const char aTerkooga_800727B8[] = "\202s\202\205\202\222\202\213\202\217\202\217\202\207\202\201"; // Terkooga
const char aSkwooga_800727CC[] = "\202r\202\213\202\227\202\217\202\217\202\207\202\201"; // Skwooga
const char aPatakuga_800727DC[] = "\202o\202\201\202\224\202\201\202\213\202\225\202\207\202\201"; // Patakuga
const char aRadtodon_800727F0[] = "\202q\202\201\202\204\202\224\202\217\202\204\202\217\202\216"; // Radtodon
const char aTertodon_80072804[] = "\202s\202\205\202\222\202\224\202\217\202\204\202\217\202\216"; // Tertodon
const char aSkatodon_80072818[] = "\202r\202\213\202\201\202\224\202\217\202\204\202\217\202\216"; // Skatodon
const char aPatodon_8007282C[] = "\202o\202\201\202\224\202\217\202\204\202\217\202\216"; // Patodon
const char aRadeeb_8007283C[] = "\202q\202\201\202\204\202\205\202\205\202\202"; // Radeeb
const char aTereeb_8007284C[] = "\202s\202\205\202\222\202\205\202\205\202\202"; // Tereeb
const char aSkaeeb_8007285C[] = "\202r\202\213\202\201\202\205\202\205\202\202"; // Skaeeb
const char aPateeb_8007286C[] = "\202o\202\201\202\224\202\205\202\205\202\202"; // Pateeb
const char aRadmole_8007287C[] = "\202q\202\201\202\204\202\215\202\217\202\214\202\205"; // Radmole
const char aTermole_8007288C[] = "\202s\202\205\202\222\202\215\202\217\202\214\202\205"; // Termole
const char aSkumole_8007289C[] = "\202r\202\213\202\225\202\215\202\217\202\214\202\205"; // Skumole
const char aPatamole_800728AC[] = "\202o\202\201\202\224\202\201\202\215\202\217\202\214\202\205"; // Patamole
const char aRadmanty_800728C0[] = "\202q\202\201\202\204\202\215\202\201\202\216\202\224\202\231"; // Radmanty
const char aTermanty_800728D4[] = "\202s\202\205\202\222\202\215\202\201\202\216\202\224\202\231"; // Termanty
const char aSkamanty_800728E8[] = "\202r\202\213\202\201\202\215\202\201\202\216\202\224\202\231"; // Skamanty
const char aPatmanty_800728FC[] = "\202o\202\201\202\224\202\215\202\201\202\216\202\224\202\231"; // Patmanty
const char aRadwasp_80072910[] = "\202q\202\201\202\204\202\227\202\201\202\223\202\220"; // Radwasp
const char aTerwasp_80072920[] = "\202s\202\205\202\222\202\227\202\201\202\223\202\220"; // Terwasp
const char aSkawasp_80072930[] = "\202r\202\213\202\201\202\227\202\201\202\223\202\220"; // Skawasp
const char aPatawasp_80072940[] = "\202o\202\201\202\224\202\201\202\227\202\201\202\223\202\220"; // Patawasp
const char aAmasag_80072954[] = "\202`\202\215\202\201\202\223\202\201\202\207"; // Amasag
const char aMorisag_80072964[] = "\202l\202\217\202\222\202\211\202\223\202\201\202\207"; // Morisag
const char aTagosag_80072974[] = "\202s\202\201\202\207\202\217\202\223\202\201\202\207"; // Tagosag
const char aHikisag_80072984[] = "\202g\202\211\202\213\202\211\202\223\202\201\202\207"; // Hikisag
const char aRadbeker_80072994[] = "\202q\202\201\202\204\202\202\202\205\202\213\202\205\202\222"; // Radbeker
const char aTerbeker_800729A8[] = "\202s\202\205\202\222\202\202\202\205\202\213\202\205\202\222"; // Terbeker
const char aSkbeker_800729BC[] = "\202r\202\213\202\202\202\205\202\213\202\205\202\222"; // Skbeker
const char aPatbecker_800729CC[] = "\202o\202\201\202\224\202\202\202\205\202\203\202\213\202\205\202\222"; // Patbecker
const char aRaddlco_800729E0[] = "\202q\202\201\202\204\202\204\202\214\202\203\202\217"; // Raddlco
const char aTeralco_800729F0[] = "\202s\202\205\202\222\202\201\202\214\202\203\202\217"; // Teralco
const char aSkalco_80072A00[] = "\202r\202\213\202\201\202\214\202\203\202\217"; // Skalco
const char aPatalco_80072A10[] = "\202o\202\201\202\224\202\201\202\214\202\203\202\217"; // Patalco
const char aDogpara_80072A20[] = "\202c\202\217\202\207\202\220\202\201\202\222\202\201"; // Dogpara
const char aTerpara_80072A30[] = "\202s\202\205\202\222\202\220\202\201\202\222\202\201"; // Terpara
const char aSkapara_80072A40[] = "\202r\202\213\202\201\202\220\202\201\202\222\202\201"; // Skapara
const char aPatapara_80072A50[] = "\202o\202\201\202\224\202\201\202\220\202\201\202\222\202\201"; // Patapara
const char aDoggrip_80072A64[] = "\202c\202\217\202\207\202\207\202\222\202\211\202\220"; // Doggrip
const char aTergrip_80072A74[] = "\202s\202\205\202\222\202\207\202\222\202\211\202\220"; // Tergrip
const char aSkagrip_80072A84[] = "\202r\202\213\202\201\202\207\202\222\202\211\202\220"; // Skagrip
const char aPatagrip_80072A94[] = "\202o\202\201\202\224\202\201\202\207\202\222\202\211\202\220"; // Patagrip
const char aRadrash_80072AA8[] = "\202q\202\201\202\204\202\222\202\201\202\223\202\210"; // Radrash
const char aTerash_80072AB8[] = "\202s\202\205\202\222\202\201\202\223\202\210"; // Terash
const char aSkash_80072AC8[] = "\202r\202\213\202\201\202\223\202\210"; // Skash
const char aPatash_80072AD4[] = "\202o\202\201\202\224\202\201\202\223\202\210"; // Patash
const char aDoggaron_80072AE4[] = "\202c\202\217\202\207\202\207\202\201\202\222\202\217\202\216"; // Doggaron
const char aTragaron_80072AF8[] = "\202s\202\222\202\201\202\207\202\201\202\222\202\217\202\216"; // Tragaron
const char aSkagaron_80072B0C[] = "\202r\202\213\202\201\202\207\202\201\202\222\202\217\202\216"; // Skagaron
const char aPatgaron_80072B20[] = "\202o\202\201\202\224\202\207\202\201\202\222\202\217\202\216"; // Patgaron
const char aRadunga_80072B34[] = "\202q\202\201\202\204\202\225\202\216\202\207\202\201"; // Radunga
const char aTerunga_80072B44[] = "\202s\202\205\202\222\202\225\202\216\202\207\202\201"; // Terunga
const char aSkarunga_80072B54[] = "\202r\202\213\202\201\202\222\202\225\202\216\202\207\202\201"; // Skarunga
const char aDrunga_80072B68[] = "\202c\202\222\202\225\202\216\202\207\202\201"; // Drunga
const char aRadgore_80072B78[] = "\202q\202\201\202\204\202\207\202\217\202\222\202\205"; // Radgore
const char aTergore_80072B88[] = "\202s\202\205\202\222\202\207\202\217\202\222\202\205"; // Tergore
const char aSkgore_80072B98[] = "\202r\202\213\202\207\202\217\202\222\202\205"; // Skgore
const char aPatagore_80072BA8[] = "\202o\202\201\202\224\202\201\202\207\202\217\202\222\202\205"; // Patagore
const char aGeible_80072BBC[] = "\202f\202\205\202\211\202\202\202\214\202\205"; // Geible
const char aClayble_80072BCC[] = "\202b\202\214\202\201\202\231\202\202\202\214\202\205"; // Clayble
const char aHackaroo_80072BDC[] = "\202g\202\201\202\203\202\213\202\201\202\222\202\217\202\217"; // Hackaroo
const char aJitamble_80072BF0[] = "\202i\202\211\202\224\202\201\202\215\202\202\202\214\202\205"; // Jitamble
const char aLadbaran_80072C04[] = "\202k\202\201\202\204\202\202\202\201\202\222\202\201\202\216"; // Ladbaran
const char aTerbaran_80072C18[] = "\202s\202\205\202\222\202\202\202\201\202\222\202\201\202\216"; // Terbaran
const char aSkbaran_80072C2C[] = "\202r\202\213\202\202\202\201\202\222\202\201\202\216"; // Skbaran
const char aPatbaran_80072C3C[] = "\202o\202\201\202\224\202\202\202\201\202\222\202\201\202\216"; // Patbaran
const char aRagifrayd_80072C50[] = "\202q\202\201\202\207\202\211\202\206\202\222\202\201\202\231\202\204"; // Ragifrayd
const char aTerfrayd_80072C64[] = "\202s\202\205\202\222\202\206\202\222\202\201\202\231\202\204"; // Terfrayd
const char aMafrayd_80072C78[] = "\202l\202\201\202\206\202\222\202\201\202\231\202\204"; // Mafrayd
const char aPataraid_80072C88[] = "\202o\202\201\202\224\202\201\202\222\202\201\202\211\202\204"; // Pataraid
const char aCushidra_80072C9C[] = "\202b\202\225\202\223\202\210\202\211\202\204\202\222\202\201"; // Cushidra
const char aChosenOne_80072CB0[] = "\202b\202\210\202\217\202\223\202\205\202\216\201@\202n\202\216\202\205"; // Chosen One
const char aGigoat_80072CC8[] = "\202f\202\211\202\207\202\217\202\201\202\224"; // Gigoat
const char aLagoat_80072CD8[] = "\202k\202\201\202\207\202\217\202\201\202\224"; // Lagoat
const char aGoat_80072CE8[] = "\202f\202\217\202\201\202\224"; // Goat
const char aPoacher_80072CF4[] = "\202o\202\217\202\201\202\203\202\210\202\205\202\222"; // Poacher
const char aMaskedBoy_80072D04[] = "\202l\202\201\202\223\202\213\202\205\202\204\201@\202a\202\217\202\231"; // Masked Boy
const char aKikinak_80072D1C[] = "\202j\202\211\202\213\202\211\202\216\202\201\202\213"; // Kikinak
const char aWindBoss_80072D2C[] = "\202v\202\211\202\216\202\204\201@\202a\202\217\202\223\202\223"; // Wind Boss
const char aSeterian_80072D40[] = "\202r\202\205\202\224\202\205\202\222\202\211\202\201\202\216"; // Seterian
const char aFireBoss_80072D54[] = "\202e\202\211\202\222\202\205\201@\202a\202\217\202\223\202\223"; // Fire Boss
const char aTuturis_80072D68[] = "\202s\202\225\202\224\202\225\202\222\202\211\202\223"; // Tuturis
const char aEarthBoss_80072D78[] = "\202d\202\201\202\222\202\224\202\210\201@\202a\202\217\202\223\202\223"; // Earth Boss
const char aDelfanel_80072D90[] = "\202c\202\205\202\214\202\206\202\201\202\216\202\205\202\214"; // Delfanel
const char aMinion_80072DA4[] = "\202l\202\211\202\216\202\211\202\217\202\216"; // Minion
const char aDreamMan_80072DB4[] = "\202c\202\222\202\205\202\201\202\215\201@\202l\202\201\202\216"; // Dream Man
const char aVatolka_80072DC8[] = "\202u\202\201\202\224\202\217\202\214\202\213\202\201"; // Vatolka
const char aArpatron_80072DD8[] = "\202`\202\222\202\220\202\201\202\224\202\222\202\217\202\216"; // Arpatron
const char aSherick_80072DEC[] = "\202r\202\210\202\205\202\222\202\211\202\203\202\213"; // Sherick
const char aTweengo_80072DFC[] = "\202s\202\227\202\205\202\205\202\216\202\207\202\217"; // Tweengo
const char aRashaba_80072E0C[] = "\202q\202\201\202\223\202\210\202\201\202\202\202\201"; // Rashaba
const char aEhsp_80072E1C[] = "\202d\202\210\202\223\202\220"; // Ehsp
const char aJirahl_80072E28[] = "\202i\202\211\202\222\202\201\202\210\202\214"; // Jirahl
const char aYoalk_80072E38[] = "\202x\202\217\202\201\202\214\202\213"; // Yoalk
const char aUglam_80072E44[] = "\202t\202\207\202\214\202\201\202\215"; // Uglam
const char aSrikarta_80072E50[] = "\202r\202\222\202\211\202\213\202\201\202\222\202\224\202\201"; // Srikarta
const char aRiggu_80072E64[] = "\202q\202\211\202\207\202\207\202\225"; // Riggu
const char aOjiae_80072E70[] = "\202n\202\212\202\211\202\201\202\205"; // Ojiae
const char aNoobwee_80072E7C[] = "\202m\202\217\202\217\202\202\202\227\202\205\202\205"; // Noobwee
const char aMugoo_80072E8C[] = "\202l\202\225\202\207\202\217\202\217"; // Mugoo
const char aMaryen_80072E98[] = "\202l\202\201\202\222\202\231\202\205\202\216"; // Maryen
const char aGeenwee_80072EA8[] = "\202f\202\205\202\205\202\216\202\227\202\205\202\205"; // Geenwee
const char aAsha_80072EB8[] = "\202`\202\223\202\210\202\201"; // Asha
const char aMukshab_80072EC4[] = "\202l\202\225\202\213\202\223\202\210\202\201\202\202"; // Mukshab
const char aRashab_80072ED4[] = "\202q\202\201\202\223\202\210\202\201\202\202"; // Rashab
const char aNushab_80072EE4[] = "\202m\202\225\202\223\202\210\202\201\202\202"; // Nushab
const char aDoglchu_80072EF4[] = "\202c\202\217\202\207\202\214\202\203\202\210\202\225"; // Doglchu
const char aRaddlchu_80072F04[] = "\202q\202\201\202\204\202\204\202\214\202\203\202\210\202\225"; // Raddlchu
const char aPatalchu_80072F18[] = "\202o\202\201\202\224\202\201\202\214\202\203\202\210\202\225"; // Patalchu
const char aRadoimel_80072F2C[] = "\202q\202\201\202\204\202\217\202\211\202\215\202\205\202\214"; // Radoimel
const char aSkwimel_80072F40[] = "\202r\202\213\202\227\202\211\202\215\202\205\202\214"; // Skwimel
const char aPataimel_80072F50[] = "\202o\202\201\202\224\202\201\202\211\202\215\202\205\202\214"; // Pataimel
const char aHirasag_80072F64[] = "\202g\202\211\202\222\202\201\202\223\202\201\202\207"; // Hirasag
const char aMaskhira_80072F74[] = "\202l\202\201\202\223\202\213\202\210\202\211\202\222\202\201"; // Maskhira
const char aHiralco_80072F88[] = "\202g\202\211\202\222\202\201\202\214\202\203\202\217"; // Hiralco
const char aTerhambu_80072F98[] = "\202s\202\205\202\222\202\210\202\201\202\215\202\202\202\225"; // Terhambu
const char aDoghambu_80072FAC[] = "\202c\202\217\202\207\202\210\202\201\202\215\202\202\202\225"; // Doghambu
const char aMukhambu_80072FC0[] = "\202l\202\225\202\213\202\210\202\201\202\215\202\202\202\225"; // Mukhambu
const char aBerbansa_80072FD4[] = "\202a\202\205\202\222\202\202\202\201\202\216\202\223\202\201"; // Berbansa
const char aDogle_80072FE8[] = "\202c\202\217\202\207\202\214\202\205"; // Dogle
const char aRugdogle_80072FF4[] = "\202q\202\225\202\207\202\204\202\217\202\207\202\214\202\205"; // Rugdogle
const char aPatdreg_80073008[] = "\202o\202\201\202\224\202\204\202\222\202\205\202\207"; // Patdreg
const char aRaddreg_80073018[] = "\202q\202\201\202\204\202\204\202\222\202\205\202\207"; // Raddreg
const char aMarrdreg_80073028[] = "\202l\202\201\202\222\202\222\202\204\202\222\202\205\202\207"; // Marrdreg

// Matched
int GetActorHitFrame_80018E5C(Actor* actor, unsigned int idx)
{
    struct_4s* hitTimes = actor->hitTimes_108;
    int frame = 0;
    switch (idx)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        frame = hitTimes[idx].field_0;
        break;
    case 10:
        frame = GetActorScriptTime_8001F03C((int)actor, (int)actor->script_D0, -1, 0x10);
        break;
    }
    return frame;
}
// Matched
void SetActorStatusTint_80018EBC(int actor, UnitStatus* status)
{
    unsigned int flags = status->status_0;
    int* tint = 0;
    if (flags & 0x200)
    {
        tint = (flags & 1) ? statusTintPoisonLevel7_8007A14C : statusTintLevel7_8007A0EC;
    }
    else if (flags & 0x100)
    {
        tint = (flags & 1) ? statusTintPoisonLevel6_8007A140 : statusTintLevel6_8007A0E0;
    }
    else if (flags & 0x80)
    {
        tint = (flags & 1) ? statusTintPoisonLevel5_8007A134 : statusTintLevel5_8007A0D4;
    }
    else if (flags & 0x40)
    {
        tint = (flags & 1) ? statusTintPoisonLevel4_8007A128 : statusTintLevel4_8007A0C8;
    }
    else if (flags & 0x20)
    {
        tint = (flags & 1) ? statusTintPoisonLevel3_8007A11C : statusTintLevel3_8007A0BC;
    }
    else if (flags & 0x10)
    {
        tint = (flags & 1) ? statusTintPoisonLevel2_8007A110 : statusTintLevel2_8007A0B0;
    }
    else if (flags & 0x8)
    {
        tint = (flags & 1) ? statusTintPoisonLevel1_8007A104 : statusTintLevel1_8007A0A4;
    }
    else if (flags & 1)
    {
        tint = statusTintPoison_8007A0F8;
    }
    SetActorTint_8001DAAC(actor, tint);
}

extern MinionBaseStats* sub_800B32A4(int a0);
extern unsigned char* sub_800B32F0(int a0);
extern void EncodeName_8003F7C8(void* text, unsigned char* out);
extern void InitStatsFromBase_8001980C(unsigned char* stats, MinionBaseStats* base);
extern void InitSpeciesSkills_800199A0(UnitStats* unit);
extern void InitSpeciesMagic_80019A20(UnitStats* a0);
// Matched
int InitMinionData_8001900C(UnitStats* unit, int* params)
{
    MinionBaseStats base;
    char** name;
    int seed;
    unsigned int id;
    unsigned int id2;
    int e;
    int i;
    int j;
    int k;
    int l;
    int species;
    int digits;

    species = params[0];
    unit->species_5C = species;
    name = &minionSpeciesNames_8007A170[species];
    seed = minionVariantSeed_8008D4DC;
    EncodeName_8003F7C8(*name, unit->st_0.name_10);
    EncodeName_8003F7C8(*name, unit->name_60);
    id = unit->species_5C;
    if (id < 0x39)
    {
        base = minionBaseStats_8007A4B4[id];
        if (unit->species_5C - 0x25 < 4)
        {
            base.attack += (seed % 5) * 10 - 20;
            base.magicAttack += (seed / 10 % 5) * 10 - 20;
            base.defense += (seed / 100 % 5) * 10 - 20;
            base.magicDefense += (seed / 1000 % 5) * 10 - 20;
            base.speed += (seed / 10000 % 5) * 10 - 20;
            base.critical += (seed / 100000 % 5) * 10 - 20;
        }
    }
    else if (id < 0xC9)
    {
        id = (id - 0x39) / 4;
        base = minionBaseStats_8007A4B4[id];
        e = (unit->species_5C - 0x39) & 3;
        if (base.element != e)
        {
            base.element = e;
            switch (e)
            {
            case 0:
                base.attack += 10;
                base.magicAttack += 10;
                base.defense -= 10;
                base.magicDefense -= 10;
                break;
            case 1:
                base.defense -= 10;
                base.magicDefense -= 10;
                base.speed += 10;
                base.critical += 10;
                break;
            case 2:
                base.defense += 10;
                base.magicDefense += 10;
                base.speed -= 10;
                base.critical -= 10;
                break;
            case 3:
                base.attack -= 10;
                base.magicAttack += 10;
                base.defense -= 10;
                base.magicDefense += 10;
                break;
            }
        }
    }
    else
    {
        base = *sub_800B32A4(id - 0xC9);
    }
    InitStatsFromBase_8001980C(unit->st_0.stats_2C.cur_0, &base);
    unit->st_0.status_0 = 0;
    if (base.element != -1)
    {
        unit->st_0.elementMask_42 = 1 << base.element;
        for (j = 0; j < 4; j++)
        {
            unit->st_0.element_3E[j] = 0;
        }
        unit->st_0.element_3E[base.element] = 0x20;
    }
    else
    {
        unit->st_0.elementMask_42 = 0;
        for (l = 0; l < 4; l++)
        {
            unit->st_0.element_3E[l] = 8;
        }
    }
    unit->st_0.exp_4 = 0x4000000;
    unit->st_0.level_44 = 0;
    unit->st_0.equipment_1C[0] = 0xFF;
    unit->st_0.equipment_1C[1] = 0xFF;
    unit->st_0.equipment_1C[2] = 0xFF;
    unit->st_0.equipment_1C[3] = 0xFF;
    unit->st_0.fixedStats_45 = 0;
    id2 = unit->species_5C;
    if (id2 < 0x39)
    {
        MemCopy_800403E8(unit->st_0.modifiers_20, speciesModifiers_8007BA84 + id2 * 12, 12);
    }
    else if (id2 < 0xC9)
    {
        id2 = (id2 - 0x39) / 4;
        MemCopy_800403E8(unit->st_0.modifiers_20, speciesModifiers_8007BA84 + id2 * 12, 12);
    }
    else
    {
        MemCopy_800403E8(unit->st_0.modifiers_20, sub_800B32F0(id2 - 0xC9), 12);
    }
    if (unit->species_5C - 0x25 < 4)
    {
        digits = seed;
        for (i = 4; i < 9; i++)
        {
            unit->st_0.modifiers_20[i] = (digits % 9) * 4 + 8;
            digits /= 10;
        }
    }
    if (base.element != -1)
    {
        id2 = unit->species_5C;
        if (!(id2 - 0x2B < 0xE) && !(id2 - 0xC9 < 0xA))
        {
            MemCopy_800403E8(unit->st_0.modifiers_20, elementModifiers_8007BA74 + base.element * 4, 4);
        }
    }
    unit->st_0.exp_4 += params[1];
    ApplyLevelUpsPlain_80012188(&unit->st_0);
    FillHpMp_80011C0C(&unit->st_0, &unit->st_0);
    InitSpeciesSkills_800199A0(unit);
    if (unit->species_5C - 0x25 < 4)
    {
        unit->skills_6C.slot[seed % 4].field_3 = 1;
        unit->skills_6C.slot[seed % 4].bonus_2 = seed % 3 + 2;
        k = seed % 3 + 1;
        unit->skills_6C.slot[k].id_1 = seed % 10 + 6;
        unit->skills_6C.slot[4].id_1 = 12;
    }
    InitSpeciesMagic_80019A20(unit);
    if (unit->species_5C - 0x25 < 4)
    {
        if (seed / 11 % 3)
        {
            unit->magicBits_80 |= elementBonusMagic1_8007A67C[base.element];
        }
        if (seed / 70 & 1)
        {
            unit->magicBits_80 |= elementBonusMagic2_8007A68C[base.element];
        }
        if (seed / 500 & 1)
        {
            unit->magicBits_80 |= elementBonusMagic3_8007A69C[base.element];
        }
    }
    return GetRankForLevel_80019A80(*(char*)&unit->st_0.level_44);
}
// Matched
void InitStatsFromBase_8001980C(unsigned char* stats, MinionBaseStats* base)
{
    int i;
    int j;
    int value;
    stats[6] = (base->attack < 200) ? base->attack : 200;
    stats[8] = (base->magicAttack < 200) ? base->magicAttack : 200;
    stats[10] = (base->speed < 200) ? base->speed : 200;
    stats[7] = (base->defense < 200) ? base->defense : 200;
    stats[9] = (base->magicDefense < 200) ? base->magicDefense : 200;
    stats[11] = (base->critical < 200) ? base->critical : 200;
    for (i = 0; i < 6; i++)
    {
        int clamped;
        unsigned char* stat = stats + i;
        value = (unsigned char)(stat[6] / 10) + 10;
        if (value >= 0)
        {
            int capped = value;
            if (capped > 100)
            {
                capped = 100;
            }
            clamped = capped;
        }
        else
        {
            clamped = 0;
        }
        stat[0] = clamped;
    }
    for (j = 0; j < 6; j++)
    {
        (stats + j)[12] = rand() % 100;
    }
}
// Matched
void InitSpeciesSkills_800199A0(UnitStats* unit)
{
    unit->skills_6C = *GetSpeciesSkills_80019C28(unit->species_5C);
}
// Matched
void InitSpeciesMagic_80019A20(UnitStats* unit)
{
    unsigned int idx = unit->species_5C;
    if (idx < 0xC9)
    {
        unit->magicBits_80 = speciesMagicBits_8007A6AC[idx];
    }
    else
    {
        unit->magicBits_80 = *sub_800B3260(idx - 0x39);
    }
}
extern unsigned char rankLevelThresholds_8007C2E4[];
// Matched
int GetRankForLevel_80019A80(int level)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (level < rankLevelThresholds_8007C2E4[i])
        {
            break;
        }
    }
    i--;
    if (i == 5)
    {
        return 4;
    }
    return i;
}
// Matched
int GetUnitRank_80019AD0(UnitStats* unit)
{
    GetRankForLevel_80019A80(unit->st_0.level_44);
    return 4;
}
// Matched
void CopyName_80019AF4(unsigned int* dst, unsigned int* src)
{
    MemCopy_800403E8(dst, src, 12);
}
// Matched
void SetBoneGroupFlags_80019B14(short* bones, unsigned short* levels, unsigned short* flags)
{
    struct_int3 masks;
    int k;
    int i;
    masks = boneGroupMasks_8007303C;
    for (k = 0; k < 3; k++)
    {
        int set = 0;
        int clr = 0;
        if (levels[k] < 2)
        {
            clr = masks.m[k];
        }
        if (flags[k] == 0)
        {
            set = masks.m[k];
        }
        for (i = 0; i < 25; i++)
        {
            int bit = 1 << i;
            if (clr & bit)
            {
                bones[i * 4 + 3] &= ~2;
            }
            if (set & bit)
            {
                bones[i * 4 + 3] |= 0x10;
            }
        }
    }
}
