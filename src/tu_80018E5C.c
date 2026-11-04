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
#include "tu_80019BF0.h"
#include "tu_80018E5C.h"
#include "tu_80014954.h"

const char dword_80072310[] = "\202j\202\214\202\201\202\222\202\222\202\207\202\201\202\223"; // Klarrgas
const char dword_80072324[] = "\202x\202\217\202\214\202\207\202\201"; // Yolga
const char aTimaios_80072330[] = "\202s\202\211\202\215\202\201\202\211\202\217\202\223"; // Timaios
const char aSicanjal_80072340[] = "\202r\202\211\202\203\202\201\202\216\202\212\202\201\202\214"; // Sicanjal
const char dword_80072354[] = "\202j\202\217\202\214\202\216\202\201"; // Kolna
const char aJeechwo_80072360[] = "\202i\202\205\202\205\202\203\202\210\202\227\202\217"; // Jeechwo
const char aTicker_80072370[] = "\202s\202\211\202\203\202\213\202\205\202\222"; // Ticker
const char dword_80072380[] = "\202o\202\201\202\214\202\217\202\217\202\212\202\201"; // Palooja
const char aTyton_80072390[] = "\202s\202\231\202\224\202\217\202\216"; // Tyton
const char aSbarse_8007239C[] = "\202r\202\202\202\201\202\222\202\223\202\205"; // Sbarse
const char dword_800723AC[] = "\202r\202\205\202\224\202\217\202\214\202\213\202\201"; // Setolka
const char aLakshel_800723BC[] = "\202k\202\201\202\213\202\223\202\210\202\205\202\214"; // Lakshel
const char aKetow_800723CC[] = "\202j\202\205\202\224\202\217\202\227"; // Ketow
const char aIbdamia_800723D8[] = "\202h\202\202\202\204\202\201\202\215\202\211\202\201"; // Ibdamia
const char aShakures_800723E8[] = "\202r\202\210\202\201\202\213\202\225\202\222\202\205\202\223"; // Shakures
const char dword_800723FC[] = "\202b\202\217\202\214\202\225\202\216\202\211\202\225\202\223"; // Colunius
const char dword_80072410[] = "\202m\202\201\202\222\202\201\202\204\202\205"; // Narade
const char dword_80072420[] = "\202j\202\201\202\222\202\222\202\217"; // Karro
const char aSaramoon_8007242C[] = "\202r\202\201\202\222\202\201\202\215\202\217\202\217\202\216"; // Saramoon
const char dword_80072440[] = "\202m\202\225\202\220\202\201\202\216\202\204\202\222\202\201"; // Nupandra
const char dword_80072454[] = "\202`\202\207\202\207\202\210\202\201\202\211"; // Agghai
const char dword_80072464[] = "\202f\202\222\202\205\202\231\202\204\202\217\202\216"; // Greydon
const char aArmijar_80072474[] = "\202`\202\222\202\215\202\211\202\212\202\201\202\222"; // Armijar
const char aBauback_80072484[] = "\202a\202\201\202\225\202\202\202\201\202\203\202\213"; // Bauback
const char aKamra_80072494[] = "\202j\202\201\202\215\202\222\202\201"; // Kamra
const char aFedelco_800724A0[] = "\202e\202\205\202\204\202\205\202\214\202\203\202\217"; // Fedelco
const char aArvalzak_800724B0[] = "\202`\202\222\202\226\202\201\202\214\202\232\202\201\202\213"; // Arvalzak
const char dword_800724C4[] = "\202r\202\220\202\211\202\222\202\201\202\214"; // Spiral
const char dword_800724D4[] = "\202n\202\210\202\232\202\201\202\231"; // Ohzay
const char aAiona_800724E0[] = "\202`\202\211\202\217\202\216\202\201"; // Aiona
const char aNevan_800724EC[] = "\202m\202\205\202\226\202\201\202\216"; // Nevan
const char aYates_800724F8[] = "\202x\202\201\202\224\202\205\202\223"; // Yates
const char aRainster_80072504[] = "\202q\202\201\202\211\202\216\202\223\202\224\202\205\202\222"; // Rainster
const char dword_80072518[] = "\202s\202\225\202\222\202\205\202\216"; // Turen
const char aFintan_80072524[] = "\202e\202\211\202\216\202\224\202\201\202\216"; // Fintan
const char dword_80072534[] = "\202a\202\201\202\227\202\216\202\211"; // Bawni
const char aId_80072540[] = "\202h\202\204"; // Id
const char dword_80072548[] = "\202e\202\225\202\207\202\207\202\205\202\222"; // Fugger
const char dword_80072558[] = "\202b\202\201\202\222\202\214\202\211\202\204\202\207\202\205"; // Carlidge
const char dword_8007256C[] = "\202r\202\227\202\201\202\226"; // Swav
const char dword_80072578[] = "\202n\202\210\202\215\202\201"; // Ohma
const char dword_80072584[] = "\202f\202\201\202\214\202\211\202\201"; // Galia
const char aAnkoo_80072590[] = "\202`\202\216\202\213\202\217\202\217"; // Ankoo
const char aWardon_8007259C[] = "\202v\202\201\202\222\202\204\202\217\202\216"; // Wardon
const char dword_800725AC[] = "\202s\202\211\202\217\202\217\202\224\202\232"; // Tiootz
const char dword_800725BC[] = "\202r\202\207\202\201\202\212"; // Sgaj
const char dword_800725C8[] = "\202r\202\217\202\227\202\214"; // Sowl
const char dword_800725D4[] = "\202e\202\222\202\205\202\231"; // Frey
const char dword_800725E0[] = "\202q\202\217\202\202\202\225\202\216"; // Robun
const char aElu_800725EC[] = "\202d\202\214\202\225"; // Elu
const char aShowven_800725F4[] = "\202r\202\210\202\217\202\227\202\226\202\205\202\216"; // Showven
const char aFrigg_80072604[] = "\202e\202\222\202\211\202\207\202\207"; // Frigg
const char aZulmoo_80072610[] = "\202y\202\225\202\214\202\215\202\217\202\217"; // Zulmoo
const char dword_80072620[] = "\202o\202\205\202\204\202\211\202\216\202\207\202\217"; // Pedingo
const char aTuloon_80072630[] = "\202s\202\225\202\214\202\217\202\217\202\216"; // Tuloon
const char dword_80072640[] = "\202f\202\201\202\202\202\205\202\205"; // Gabee
const char aEmbla_8007264C[] = "\202d\202\215\202\202\202\214\202\201"; // Embla
const char aEavun_80072658[] = "\202d\202\201\202\226\202\225\202\216"; // Eavun
const char aOajin_80072664[] = "\202n\202\201\202\212\202\211\202\216"; // Oajin
const char aUsk_80072670[] = "\202t\202\223\202\213"; // Usk
const char aUld_80072678[] = "\202t\202\214\202\204"; // Uld
const char aScul_80072680[] = "\202r\202\203\202\225\202\214"; // Scul
const char dword_8007268C[] = "\202s\202\205\202\214\202\215\202\201"; // Telma
const char aKarn_80072698[] = "\202j\202\201\202\222\202\216"; // Karn
const char dword_800726A4[] = "\202e\202\201\202\214"; // Fal
const char aShee_800726AC[] = "\202r\202\210\202\205\202\205"; // Shee
const char dword_800726B8[] = "\202r\202\210\202\225\202\214\202\211\202\201"; // Shulia
const char dword_800726C8[] = "\202`\202\216\202\201\202\223\202\210"; // Anash
const char aRadmine_800726D4[] = "\202q\202\201\202\204\202\215\202\211\202\216\202\205"; // Radmine
const char aTeramine_800726E4[] = "\202s\202\205\202\222\202\201\202\215\202\211\202\216\202\205"; // Teramine
const char dword_800726F8[] = "\202r\202\213\202\227\202\215\202\201\202\211\202\216\202\205"; // Skwmaine
const char dword_8007270C[] = "\202b\202\201\202\222\202\215\202\211\202\216\202\205"; // Carmine
const char aRadmoaj_8007271C[] = "\202q\202\201\202\204\202\215\202\217\202\201\202\212"; // Radmoaj
const char aTeramoaj_8007272C[] = "\202s\202\205\202\222\202\201\202\215\202\217\202\201\202\212"; // Teramoaj
const char dword_80072740[] = "\202r\202\213\202\227\202\215\202\217\202\201\202\212"; // Skwmoaj
const char aPatamoaj_80072750[] = "\202o\202\201\202\224\202\201\202\215\202\217\202\201\202\212"; // Patamoaj
const char dword_80072764[] = "\202q\202\201\202\204\202\217\202\217\202\224"; // Radoot
const char dword_80072774[] = "\202s\202\205\202\222\202\201\202\217\202\217\202\224"; // Teraoot
const char aSkwoot_80072784[] = "\202r\202\213\202\227\202\217\202\217\202\224"; // Skwoot
const char dword_80072794[] = "\202o\202\201\202\224\202\201\202\217\202\217\202\224"; // Pataoot
const char aRadkooga_800727A4[] = "\202q\202\201\202\204\202\213\202\217\202\217\202\207\202\201"; // Radkooga
const char dword_800727B8[] = "\202s\202\205\202\222\202\213\202\217\202\217\202\207\202\201"; // Terkooga
const char dword_800727CC[] = "\202r\202\213\202\227\202\217\202\217\202\207\202\201"; // Skwooga
const char aPatakuga_800727DC[] = "\202o\202\201\202\224\202\201\202\213\202\225\202\207\202\201"; // Patakuga
const char dword_800727F0[] = "\202q\202\201\202\204\202\224\202\217\202\204\202\217\202\216"; // Radtodon
const char dword_80072804[] = "\202s\202\205\202\222\202\224\202\217\202\204\202\217\202\216"; // Tertodon
const char dword_80072818[] = "\202r\202\213\202\201\202\224\202\217\202\204\202\217\202\216"; // Skatodon
const char dword_8007282C[] = "\202o\202\201\202\224\202\217\202\204\202\217\202\216"; // Patodon
const char aRadeeb_8007283C[] = "\202q\202\201\202\204\202\205\202\205\202\202"; // Radeeb
const char dword_8007284C[] = "\202s\202\205\202\222\202\205\202\205\202\202"; // Tereeb
const char dword_8007285C[] = "\202r\202\213\202\201\202\205\202\205\202\202"; // Skaeeb
const char dword_8007286C[] = "\202o\202\201\202\224\202\205\202\205\202\202"; // Pateeb
const char dword_8007287C[] = "\202q\202\201\202\204\202\215\202\217\202\214\202\205"; // Radmole
const char aTermole_8007288C[] = "\202s\202\205\202\222\202\215\202\217\202\214\202\205"; // Termole
const char aSkumole_8007289C[] = "\202r\202\213\202\225\202\215\202\217\202\214\202\205"; // Skumole
const char aPatamole_800728AC[] = "\202o\202\201\202\224\202\201\202\215\202\217\202\214\202\205"; // Patamole
const char dword_800728C0[] = "\202q\202\201\202\204\202\215\202\201\202\216\202\224\202\231"; // Radmanty
const char dword_800728D4[] = "\202s\202\205\202\222\202\215\202\201\202\216\202\224\202\231"; // Termanty
const char dword_800728E8[] = "\202r\202\213\202\201\202\215\202\201\202\216\202\224\202\231"; // Skamanty
const char dword_800728FC[] = "\202o\202\201\202\224\202\215\202\201\202\216\202\224\202\231"; // Patmanty
const char dword_80072910[] = "\202q\202\201\202\204\202\227\202\201\202\223\202\220"; // Radwasp
const char aTerwasp_80072920[] = "\202s\202\205\202\222\202\227\202\201\202\223\202\220"; // Terwasp
const char aSkawasp_80072930[] = "\202r\202\213\202\201\202\227\202\201\202\223\202\220"; // Skawasp
const char aPatawasp_80072940[] = "\202o\202\201\202\224\202\201\202\227\202\201\202\223\202\220"; // Patawasp
const char dword_80072954[] = "\202`\202\215\202\201\202\223\202\201\202\207"; // Amasag
const char dword_80072964[] = "\202l\202\217\202\222\202\211\202\223\202\201\202\207"; // Morisag
const char aTagosag_80072974[] = "\202s\202\201\202\207\202\217\202\223\202\201\202\207"; // Tagosag
const char aHikisag_80072984[] = "\202g\202\211\202\213\202\211\202\223\202\201\202\207"; // Hikisag
const char aRadbeker_80072994[] = "\202q\202\201\202\204\202\202\202\205\202\213\202\205\202\222"; // Radbeker
const char dword_800729A8[] = "\202s\202\205\202\222\202\202\202\205\202\213\202\205\202\222"; // Terbeker
const char dword_800729BC[] = "\202r\202\213\202\202\202\205\202\213\202\205\202\222"; // Skbeker
const char aPatbecker_800729CC[] = "\202o\202\201\202\224\202\202\202\205\202\203\202\213\202\205\202\222"; // Patbecker
const char aRaddlco_800729E0[] = "\202q\202\201\202\204\202\204\202\214\202\203\202\217"; // Raddlco
const char aTeralco_800729F0[] = "\202s\202\205\202\222\202\201\202\214\202\203\202\217"; // Teralco
const char aSkalco_80072A00[] = "\202r\202\213\202\201\202\214\202\203\202\217"; // Skalco
const char dword_80072A10[] = "\202o\202\201\202\224\202\201\202\214\202\203\202\217"; // Patalco
const char aDogpara_80072A20[] = "\202c\202\217\202\207\202\220\202\201\202\222\202\201"; // Dogpara
const char aTerpara_80072A30[] = "\202s\202\205\202\222\202\220\202\201\202\222\202\201"; // Terpara
const char aSkapara_80072A40[] = "\202r\202\213\202\201\202\220\202\201\202\222\202\201"; // Skapara
const char aPatapara_80072A50[] = "\202o\202\201\202\224\202\201\202\220\202\201\202\222\202\201"; // Patapara
const char dword_80072A64[] = "\202c\202\217\202\207\202\207\202\222\202\211\202\220"; // Doggrip
const char aTergrip_80072A74[] = "\202s\202\205\202\222\202\207\202\222\202\211\202\220"; // Tergrip
const char aSkagrip_80072A84[] = "\202r\202\213\202\201\202\207\202\222\202\211\202\220"; // Skagrip
const char aPatagrip_80072A94[] = "\202o\202\201\202\224\202\201\202\207\202\222\202\211\202\220"; // Patagrip
const char dword_80072AA8[] = "\202q\202\201\202\204\202\222\202\201\202\223\202\210"; // Radrash
const char aTerash_80072AB8[] = "\202s\202\205\202\222\202\201\202\223\202\210"; // Terash
const char dword_80072AC8[] = "\202r\202\213\202\201\202\223\202\210"; // Skash
const char aPatash_80072AD4[] = "\202o\202\201\202\224\202\201\202\223\202\210"; // Patash
const char dword_80072AE4[] = "\202c\202\217\202\207\202\207\202\201\202\222\202\217\202\216"; // Doggaron
const char dword_80072AF8[] = "\202s\202\222\202\201\202\207\202\201\202\222\202\217\202\216"; // Tragaron
const char dword_80072B0C[] = "\202r\202\213\202\201\202\207\202\201\202\222\202\217\202\216"; // Skagaron
const char dword_80072B20[] = "\202o\202\201\202\224\202\207\202\201\202\222\202\217\202\216"; // Patgaron
const char dword_80072B34[] = "\202q\202\201\202\204\202\225\202\216\202\207\202\201"; // Radunga
const char aTerunga_80072B44[] = "\202s\202\205\202\222\202\225\202\216\202\207\202\201"; // Terunga
const char aSkarunga_80072B54[] = "\202r\202\213\202\201\202\222\202\225\202\216\202\207\202\201"; // Skarunga
const char dword_80072B68[] = "\202c\202\222\202\225\202\216\202\207\202\201"; // Drunga
const char dword_80072B78[] = "\202q\202\201\202\204\202\207\202\217\202\222\202\205"; // Radgore
const char aTergore_80072B88[] = "\202s\202\205\202\222\202\207\202\217\202\222\202\205"; // Tergore
const char aSkgore_80072B98[] = "\202r\202\213\202\207\202\217\202\222\202\205"; // Skgore
const char dword_80072BA8[] = "\202o\202\201\202\224\202\201\202\207\202\217\202\222\202\205"; // Patagore
const char dword_80072BBC[] = "\202f\202\205\202\211\202\202\202\214\202\205"; // Geible
const char dword_80072BCC[] = "\202b\202\214\202\201\202\231\202\202\202\214\202\205"; // Clayble
const char aHackaroo_80072BDC[] = "\202g\202\201\202\203\202\213\202\201\202\222\202\217\202\217"; // Hackaroo
const char dword_80072BF0[] = "\202i\202\211\202\224\202\201\202\215\202\202\202\214\202\205"; // Jitamble
const char dword_80072C04[] = "\202k\202\201\202\204\202\202\202\201\202\222\202\201\202\216"; // Ladbaran
const char dword_80072C18[] = "\202s\202\205\202\222\202\202\202\201\202\222\202\201\202\216"; // Terbaran
const char dword_80072C2C[] = "\202r\202\213\202\202\202\201\202\222\202\201\202\216"; // Skbaran
const char aPatbaran_80072C3C[] = "\202o\202\201\202\224\202\202\202\201\202\222\202\201\202\216"; // Patbaran
const char dword_80072C50[] = "\202q\202\201\202\207\202\211\202\206\202\222\202\201\202\231\202\204"; // Ragifrayd
const char aTerfrayd_80072C64[] = "\202s\202\205\202\222\202\206\202\222\202\201\202\231\202\204"; // Terfrayd
const char dword_80072C78[] = "\202l\202\201\202\206\202\222\202\201\202\231\202\204"; // Mafrayd
const char aPataraid_80072C88[] = "\202o\202\201\202\224\202\201\202\222\202\201\202\211\202\204"; // Pataraid
const char dword_80072C9C[] = "\202b\202\225\202\223\202\210\202\211\202\204\202\222\202\201"; // Cushidra
const char dword_80072CB0[] = "\202b\202\210\202\217\202\223\202\205\202\216\201@\202n\202\216\202\205"; // Chosen One
const char dword_80072CC8[] = "\202f\202\211\202\207\202\217\202\201\202\224"; // Gigoat
const char dword_80072CD8[] = "\202k\202\201\202\207\202\217\202\201\202\224"; // Lagoat
const char dword_80072CE8[] = "\202f\202\217\202\201\202\224"; // Goat
const char dword_80072CF4[] = "\202o\202\217\202\201\202\203\202\210\202\205\202\222"; // Poacher
const char aMaskedBoy_80072D04[] = "\202l\202\201\202\223\202\213\202\205\202\204\201@\202a\202\217\202\231"; // Masked Boy
const char dword_80072D1C[] = "\202j\202\211\202\213\202\211\202\216\202\201\202\213"; // Kikinak
const char aWindBoss_80072D2C[] = "\202v\202\211\202\216\202\204\201@\202a\202\217\202\223\202\223"; // Wind Boss
const char aSeterian_80072D40[] = "\202r\202\205\202\224\202\205\202\222\202\211\202\201\202\216"; // Seterian
const char dword_80072D54[] = "\202e\202\211\202\222\202\205\201@\202a\202\217\202\223\202\223"; // Fire Boss
const char aTuturis_80072D68[] = "\202s\202\225\202\224\202\225\202\222\202\211\202\223"; // Tuturis
const char aEarthBoss_80072D78[] = "\202d\202\201\202\222\202\224\202\210\201@\202a\202\217\202\223\202\223"; // Earth Boss
const char dword_80072D90[] = "\202c\202\205\202\214\202\206\202\201\202\216\202\205\202\214"; // Delfanel
const char dword_80072DA4[] = "\202l\202\211\202\216\202\211\202\217\202\216"; // Minion
const char dword_80072DB4[] = "\202c\202\222\202\205\202\201\202\215\201@\202l\202\201\202\216"; // Dream Man
const char aVatolka_80072DC8[] = "\202u\202\201\202\224\202\217\202\214\202\213\202\201"; // Vatolka
const char aArpatron_80072DD8[] = "\202`\202\222\202\220\202\201\202\224\202\222\202\217\202\216"; // Arpatron
const char dword_80072DEC[] = "\202r\202\210\202\205\202\222\202\211\202\203\202\213"; // Sherick
const char aTweengo_80072DFC[] = "\202s\202\227\202\205\202\205\202\216\202\207\202\217"; // Tweengo
const char aRashaba_80072E0C[] = "\202q\202\201\202\223\202\210\202\201\202\202\202\201"; // Rashaba
const char aEhsp_80072E1C[] = "\202d\202\210\202\223\202\220"; // Ehsp
const char dword_80072E28[] = "\202i\202\211\202\222\202\201\202\210\202\214"; // Jirahl
const char dword_80072E38[] = "\202x\202\217\202\201\202\214\202\213"; // Yoalk
const char aUglam_80072E44[] = "\202t\202\207\202\214\202\201\202\215"; // Uglam
const char aSrikarta_80072E50[] = "\202r\202\222\202\211\202\213\202\201\202\222\202\224\202\201"; // Srikarta
const char dword_80072E64[] = "\202q\202\211\202\207\202\207\202\225"; // Riggu
const char aOjiae_80072E70[] = "\202n\202\212\202\211\202\201\202\205"; // Ojiae
const char aNoobwee_80072E7C[] = "\202m\202\217\202\217\202\202\202\227\202\205\202\205"; // Noobwee
const char aMugoo_80072E8C[] = "\202l\202\225\202\207\202\217\202\217"; // Mugoo
const char aMaryen_80072E98[] = "\202l\202\201\202\222\202\231\202\205\202\216"; // Maryen
const char dword_80072EA8[] = "\202f\202\205\202\205\202\216\202\227\202\205\202\205"; // Geenwee
const char aAsha_80072EB8[] = "\202`\202\223\202\210\202\201"; // Asha
const char dword_80072EC4[] = "\202l\202\225\202\213\202\223\202\210\202\201\202\202"; // Mukshab
const char aRashab_80072ED4[] = "\202q\202\201\202\223\202\210\202\201\202\202"; // Rashab
const char dword_80072EE4[] = "\202m\202\225\202\223\202\210\202\201\202\202"; // Nushab
const char dword_80072EF4[] = "\202c\202\217\202\207\202\214\202\203\202\210\202\225"; // Doglchu
const char aRaddlchu_80072F04[] = "\202q\202\201\202\204\202\204\202\214\202\203\202\210\202\225"; // Raddlchu
const char dword_80072F18[] = "\202o\202\201\202\224\202\201\202\214\202\203\202\210\202\225"; // Patalchu
const char dword_80072F2C[] = "\202q\202\201\202\204\202\217\202\211\202\215\202\205\202\214"; // Radoimel
const char dword_80072F40[] = "\202r\202\213\202\227\202\211\202\215\202\205\202\214"; // Skwimel
const char aPataimel_80072F50[] = "\202o\202\201\202\224\202\201\202\211\202\215\202\205\202\214"; // Pataimel
const char dword_80072F64[] = "\202g\202\211\202\222\202\201\202\223\202\201\202\207"; // Hirasag
const char aMaskhira_80072F74[] = "\202l\202\201\202\223\202\213\202\210\202\211\202\222\202\201"; // Maskhira
const char dword_80072F88[] = "\202g\202\211\202\222\202\201\202\214\202\203\202\217"; // Hiralco
const char aTerhambu_80072F98[] = "\202s\202\205\202\222\202\210\202\201\202\215\202\202\202\225"; // Terhambu
const char dword_80072FAC[] = "\202c\202\217\202\207\202\210\202\201\202\215\202\202\202\225"; // Doghambu
const char dword_80072FC0[] = "\202l\202\225\202\213\202\210\202\201\202\215\202\202\202\225"; // Mukhambu
const char dword_80072FD4[] = "\202a\202\205\202\222\202\202\202\201\202\216\202\223\202\201"; // Berbansa
const char dword_80072FE8[] = "\202c\202\217\202\207\202\214\202\205"; // Dogle
const char aRugdogle_80072FF4[] = "\202q\202\225\202\207\202\204\202\217\202\207\202\214\202\205"; // Rugdogle
const char dword_80073008[] = "\202o\202\201\202\224\202\204\202\222\202\205\202\207"; // Patdreg
const char aRaddreg_80073018[] = "\202q\202\201\202\204\202\204\202\222\202\205\202\207"; // Raddreg
const char dword_80073028[] = "\202l\202\201\202\222\202\222\202\204\202\222\202\205\202\207"; // Marrdreg

// Matched
int sub_80018E5C(Actor* a0, unsigned int a1)
{
    struct_4s* t = a0->hitTimes_108;
    int v = 0;
    switch (a1)
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
        v = t[a1].field_0;
        break;
    case 10:
        v = sub_8001F03C((int)a0, (int)a0->script_D0, -1, 0x10);
        break;
    }
    return v;
}
// Matched
void sub_80018EBC(int a0, UnitStatus* a1)
{
    unsigned int f = a1->status_0;
    int* r = 0;
    if (f & 0x200)
    {
        r = (f & 1) ? dword_8007A14C : dword_8007A0EC;
    }
    else if (f & 0x100)
    {
        r = (f & 1) ? dword_8007A140 : dword_8007A0E0;
    }
    else if (f & 0x80)
    {
        r = (f & 1) ? dword_8007A134 : dword_8007A0D4;
    }
    else if (f & 0x40)
    {
        r = (f & 1) ? dword_8007A128 : dword_8007A0C8;
    }
    else if (f & 0x20)
    {
        r = (f & 1) ? dword_8007A11C : dword_8007A0BC;
    }
    else if (f & 0x10)
    {
        r = (f & 1) ? dword_8007A110 : dword_8007A0B0;
    }
    else if (f & 0x8)
    {
        r = (f & 1) ? sub_8007A104 : dword_8007A0A4;
    }
    else if (f & 1)
    {
        r = dword_8007A0F8;
    }
    SetActorTint_8001DAAC(a0, r);
}
extern MinionBaseStats* sub_800B32A4(int a0);
extern unsigned char* sub_800B32F0(int a0);
extern void EncodeName_8003F7C8(void* a0, unsigned char* a1);
extern void sub_8001980C(unsigned char* p, MinionBaseStats* s);
extern void sub_800199A0(UnitStats* p);
extern void sub_80019A20(UnitStats* a0);
// Matched
int InitMinionData_8001900C(UnitStats* m, int* a1)
{
    MinionBaseStats st;
    void** name;
    int r;
    unsigned int id;
    unsigned int id2;
    int e;
    int i;
    int j;
    int k;
    int l;
    int n;
    int v;

    n = a1[0];
    m->species_5C = n;
    name = &minionSpeciesNames_8007A170[n];
    r = dword_8008D4DC;
    EncodeName_8003F7C8(*name, m->st_0.name_10);
    EncodeName_8003F7C8(*name, m->name_60);
    id = m->species_5C;
    if (id < 0x39)
    {
        st = minionBaseStats_8007A4B4[id];
        if (m->species_5C - 0x25 < 4)
        {
            st.attack += (r % 5) * 10 - 20;
            st.magicAttack += (r / 10 % 5) * 10 - 20;
            st.defense += (r / 100 % 5) * 10 - 20;
            st.magicDefense += (r / 1000 % 5) * 10 - 20;
            st.speed += (r / 10000 % 5) * 10 - 20;
            st.critical += (r / 100000 % 5) * 10 - 20;
        }
    }
    else if (id < 0xC9)
    {
        id = (id - 0x39) / 4;
        st = minionBaseStats_8007A4B4[id];
        e = (m->species_5C - 0x39) & 3;
        if (st.element != e)
        {
            st.element = e;
            switch (e)
            {
            case 0:
                st.attack += 10;
                st.magicAttack += 10;
                st.defense -= 10;
                st.magicDefense -= 10;
                break;
            case 1:
                st.defense -= 10;
                st.magicDefense -= 10;
                st.speed += 10;
                st.critical += 10;
                break;
            case 2:
                st.defense += 10;
                st.magicDefense += 10;
                st.speed -= 10;
                st.critical -= 10;
                break;
            case 3:
                st.attack -= 10;
                st.magicAttack += 10;
                st.defense -= 10;
                st.magicDefense += 10;
                break;
            }
        }
    }
    else
    {
        st = *sub_800B32A4(id - 0xC9);
    }
    sub_8001980C(m->st_0.stats_2C, &st);
    m->st_0.status_0 = 0;
    if (st.element != -1)
    {
        m->st_0.elementMask_42 = 1 << st.element;
        for (j = 0; j < 4; j++)
        {
            m->st_0.element_3E[j] = 0;
        }
        m->st_0.element_3E[st.element] = 0x20;
    }
    else
    {
        m->st_0.elementMask_42 = 0;
        for (l = 0; l < 4; l++)
        {
            m->st_0.element_3E[l] = 8;
        }
    }
    m->st_0.exp_4 = 0x4000000;
    m->st_0.level_44 = 0;
    m->st_0.field_1C[0] = 0xFF;
    m->st_0.field_1C[1] = 0xFF;
    m->st_0.field_1C[2] = 0xFF;
    m->st_0.field_1C[3] = 0xFF;
    m->st_0.field_45 = 0;
    id2 = m->species_5C;
    if (id2 < 0x39)
    {
        MemCopy_800403E8((unsigned int*)m->st_0.field_20, (unsigned int*)(dword_8007BA84 + id2 * 12), 12);
    }
    else if (id2 < 0xC9)
    {
        id2 = (id2 - 0x39) / 4;
        MemCopy_800403E8((unsigned int*)m->st_0.field_20, (unsigned int*)(dword_8007BA84 + id2 * 12), 12);
    }
    else
    {
        MemCopy_800403E8((unsigned int*)m->st_0.field_20, (unsigned int*)sub_800B32F0(id2 - 0xC9), 12);
    }
    if (m->species_5C - 0x25 < 4)
    {
        v = r;
        for (i = 4; i < 9; i++)
        {
            m->st_0.field_20[i] = (v % 9) * 4 + 8;
            v /= 10;
        }
    }
    if (st.element != -1)
    {
        id2 = m->species_5C;
        if (!(id2 - 0x2B < 0xE) && !(id2 - 0xC9 < 0xA))
        {
            MemCopy_800403E8((unsigned int*)m->st_0.field_20, (unsigned int*)(dword_8007BA74 + st.element * 4), 4);
        }
    }
    m->st_0.exp_4 += a1[1];
    sub_80012188(&m->st_0);
    FillHpMp_80011C0C(&m->st_0, &m->st_0);
    sub_800199A0(m);
    if (m->species_5C - 0x25 < 4)
    {
        m->skills_6C.slot[r % 4].field_3 = 1;
        m->skills_6C.slot[r % 4].bonus_2 = r % 3 + 2;
        k = r % 3 + 1;
        m->skills_6C.slot[k].id_1 = r % 10 + 6;
        m->skills_6C.slot[4].id_1 = 12;
    }
    sub_80019A20(m);
    if (m->species_5C - 0x25 < 4)
    {
        if (r / 11 % 3)
        {
            m->magicBits_80 |= dword_8007A67C[st.element];
        }
        if (r / 70 & 1)
        {
            m->magicBits_80 |= dword_8007A68C[st.element];
        }
        if (r / 500 & 1)
        {
            m->magicBits_80 |= dword_8007A69C[st.element];
        }
    }
    return sub_80019A80(*(char*)&m->st_0.level_44);
}
// Matched
void sub_8001980C(unsigned char* p, MinionBaseStats* s)
{
    int i;
    int j;
    int v;
    p[6] = (s->attack < 200) ? s->attack : 200;
    p[8] = (s->magicAttack < 200) ? s->magicAttack : 200;
    p[10] = (s->speed < 200) ? s->speed : 200;
    p[7] = (s->defense < 200) ? s->defense : 200;
    p[9] = (s->magicDefense < 200) ? s->magicDefense : 200;
    p[11] = (s->critical < 200) ? s->critical : 200;
    for (i = 0; i < 6; i++)
    {
        int r;
        unsigned char* q = p + i;
        v = (unsigned char)(q[6] / 10) + 10;
        if (v >= 0)
        {
            int t = v;
            if (t > 100)
            {
                t = 100;
            }
            r = t;
        }
        else
        {
            r = 0;
        }
        q[0] = r;
    }
    for (j = 0; j < 6; j++)
    {
        (p + j)[12] = rand() % 100;
    }
}
// Matched
void sub_800199A0(UnitStats* p)
{
    p->skills_6C = *sub_80019C28(p->species_5C);
}
// Matched
void sub_80019A20(UnitStats* a0)
{
    unsigned int idx = a0->species_5C;
    if (idx < 0xC9)
    {
        a0->magicBits_80 = dword_8007A6AC[idx];
    }
    else
    {
        a0->magicBits_80 = *sub_800B3260(idx - 0x39);
    }
}
extern unsigned char dword_8007C2E4[];
// Matched
int sub_80019A80(int a0)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (a0 < dword_8007C2E4[i])
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
int sub_80019AD0(UnitStats* p)
{
    sub_80019A80(p->st_0.level_44);
    return 4;
}
// Matched
void sub_80019AF4(unsigned int* arg0, unsigned int* arg1)
{
    MemCopy_800403E8(arg0, arg1, 12);
}
// Matched
void sub_80019B14(short* p, unsigned short* a1, unsigned short* a2)
{
    struct_int3 masks;
    int k;
    int i;
    masks = dword_8007303C;
    for (k = 0; k < 3; k++)
    {
        int set = 0;
        int clr = 0;
        if (a1[k] < 2)
        {
            clr = masks.m[k];
        }
        if (a2[k] == 0)
        {
            set = masks.m[k];
        }
        for (i = 0; i < 25; i++)
        {
            int bit = 1 << i;
            if (clr & bit)
            {
                p[i * 4 + 3] &= ~2;
            }
            if (set & bit)
            {
                p[i * 4 + 3] |= 0x10;
            }
        }
    }
}
