#ifndef GTE_H
#define GTE_H

#ifdef __psyz
/* PSY-Z's libgte.h has the macros, on its GTE emulation; the ones it lacks (the same register loads and
   commands as INLINE_C.H) */
#include <libgte.h>
#include <psyz/gte.h>
#ifndef gte_ldsv
#define gte_ldsv(r0)                                                                                                  \
    (Psyz_GteDataWrite(9, (unsigned short)((short*)(r0))[0]), Psyz_GteDataWrite(10, (unsigned short)((short*)(r0))[1]), \
     Psyz_GteDataWrite(11, (unsigned short)((short*)(r0))[2]))
#endif
#ifndef gte_ldlvl
#define gte_ldlvl(r0)                                                                                                 \
    (Psyz_GteDataWrite(9, ((int*)(r0))[0]), Psyz_GteDataWrite(10, ((int*)(r0))[1]), Psyz_GteDataWrite(11, ((int*)(r0))[2]))
#endif
#ifndef gte_sqr0
#define gte_sqr0() Psyz_GteCommand(0x0A00428)
#endif
#ifndef gte_ncds
#define gte_ncds() Psyz_GteCommand(0x0E80413)
#endif
#ifndef gte_ncdt
#define gte_ncdt() Psyz_GteCommand(0x0F80416)
#endif
#ifndef gte_dpct
#define gte_dpct() Psyz_GteCommand(0x0F8002A)
#endif
#ifndef gte_MulMatrix0
#define gte_MulMatrix0(r1, r2, r3) MulMatrix0(r1, r2, r3)
#endif
#ifndef gte_gpf12
#define gte_gpf12() Psyz_GteCommand(0x198003D)
#endif
#else

/* PSY-Q GTE macros: INLINE_C.H with the GTE commands as their real cop2 words (what DMPSX would
   patch the .word placeholders to; values as in the DMPSX-less inline_n.h). */
#include <inline_c.h>

#undef gte_rtps
#define gte_rtps() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A180001;" )

#undef gte_rtpt
#define gte_rtpt() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A280030;" )

#undef gte_rt
#define gte_rt() __asm__ volatile (                             \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A480012;" )

#undef gte_rtv0
#define gte_rtv0() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A486012;" )

#undef gte_rtv1
#define gte_rtv1() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A48E012;" )

#undef gte_rtv2
#define gte_rtv2() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A496012;" )

#undef gte_rtir
#define gte_rtir() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A49E012;" )

#undef gte_rtir_sf0
#define gte_rtir_sf0() __asm__ volatile (                       \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A41E012;" )

#undef gte_rtv0tr
#define gte_rtv0tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A480012;" )

#undef gte_rtv1tr
#define gte_rtv1tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A488012;" )

#undef gte_rtv2tr
#define gte_rtv2tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A490012;" )

#undef gte_rtirtr
#define gte_rtirtr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A498012;" )

#undef gte_rtv0bk
#define gte_rtv0bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A482012;" )

#undef gte_rtv1bk
#define gte_rtv1bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A48A012;" )

#undef gte_rtv2bk
#define gte_rtv2bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A492012;" )

#undef gte_rtirbk
#define gte_rtirbk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A49A012;" )

#undef gte_ll
#define gte_ll() __asm__ volatile (                             \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4A6412;" )

#undef gte_llv0
#define gte_llv0() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4A6012;" )

#undef gte_llv1
#define gte_llv1() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4AE012;" )

#undef gte_llv2
#define gte_llv2() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4B6012;" )

#undef gte_llir
#define gte_llir() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4BE012;" )

#undef gte_llv0tr
#define gte_llv0tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4A0012;" )

#undef gte_llv1tr
#define gte_llv1tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4A8012;" )

#undef gte_llv2tr
#define gte_llv2tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4B0012;" )

#undef gte_llirtr
#define gte_llirtr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4B8012;" )

#undef gte_llv0bk
#define gte_llv0bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4A2012;" )

#undef gte_llv1bk
#define gte_llv1bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4AA012;" )

#undef gte_llv2bk
#define gte_llv2bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4B2012;" )

#undef gte_llirbk
#define gte_llirbk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4BA012;" )

#undef gte_lc
#define gte_lc() __asm__ volatile (                             \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4DA412;" )

#undef gte_lcv0
#define gte_lcv0() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4C6012;" )

#undef gte_lcv1
#define gte_lcv1() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4CE012;" )

#undef gte_lcv2
#define gte_lcv2() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4D6012;" )

#undef gte_lcir
#define gte_lcir() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4DE012;" )

#undef gte_lcv0tr
#define gte_lcv0tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4C0012;" )

#undef gte_lcv1tr
#define gte_lcv1tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4C8012;" )

#undef gte_lcv2tr
#define gte_lcv2tr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4D0012;" )

#undef gte_lcirtr
#define gte_lcirtr() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4D8012;" )

#undef gte_lcv0bk
#define gte_lcv0bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4C2012;" )

#undef gte_lcv1bk
#define gte_lcv1bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4CA012;" )

#undef gte_lcv2bk
#define gte_lcv2bk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4D2012;" )

#undef gte_lcirbk
#define gte_lcirbk() __asm__ volatile (                         \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A4DA012;" )

#undef gte_dpcl
#define gte_dpcl() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A680029;" )

#undef gte_dpcs
#define gte_dpcs() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A780010;" )

#undef gte_dpct
#define gte_dpct() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4AF8002A;" )

#undef gte_intpl
#define gte_intpl() __asm__ volatile (                          \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4A980011;" )

#undef gte_sqr12
#define gte_sqr12() __asm__ volatile (                          \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4AA80428;" )

#undef gte_sqr0
#define gte_sqr0() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4AA00428;" )

#undef gte_ncs
#define gte_ncs() __asm__ volatile (                            \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4AC8041E;" )

#undef gte_nct
#define gte_nct() __asm__ volatile (                            \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4AD80420;" )

#undef gte_ncds
#define gte_ncds() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4AE80413;" )

#undef gte_ncdt
#define gte_ncdt() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4AF80416;" )

#undef gte_nccs
#define gte_nccs() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B08041B;" )

#undef gte_ncct
#define gte_ncct() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B18043F;" )

#undef gte_cdp
#define gte_cdp() __asm__ volatile (                            \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B280414;" )

#undef gte_cc
#define gte_cc() __asm__ volatile (                             \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B38041C;" )

#undef gte_nclip
#define gte_nclip() __asm__ volatile (                          \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B400006;" )

#undef gte_avsz3
#define gte_avsz3() __asm__ volatile (                          \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B58002D;" )

#undef gte_avsz4
#define gte_avsz4() __asm__ volatile (                          \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B68002E;" )

#undef gte_op12
#define gte_op12() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B78000C;" )

#undef gte_op0
#define gte_op0() __asm__ volatile (                            \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B70000C;" )

#undef gte_gpf12
#define gte_gpf12() __asm__ volatile (                          \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B98003D;" )

#undef gte_gpf0
#define gte_gpf0() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4B90003D;" )

#undef gte_gpl12
#define gte_gpl12() __asm__ volatile (                          \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4BA8003E;" )

#undef gte_gpl0
#define gte_gpl0() __asm__ volatile (                           \
        "nop;"                                                  \
        "nop;"                                                  \
        ".word 0x4BA0003E;" )

#undef gte_mvmva_core
#define gte_mvmva_core( r0 ) __asm__ volatile (                 \
        "nop;"                                                  \
        "nop;"                                                  \
        "cop2 %0"                                               \
        :                                                       \
        : "g"( r0 ) )

#undef gte_rtps_b
#define gte_rtps_b()            __asm__ volatile ( ".word 0x4A180001;" )

#undef gte_rtpt_b
#define gte_rtpt_b()            __asm__ volatile ( ".word 0x4A280030;" )

#undef gte_rt_b
#define gte_rt_b()              __asm__ volatile ( ".word 0x4A480012;" )

#undef gte_rtv0_b
#define gte_rtv0_b()            __asm__ volatile ( ".word 0x4A486012;" )

#undef gte_rtv1_b
#define gte_rtv1_b()            __asm__ volatile ( ".word 0x4A48E012;" )

#undef gte_rtv2_b
#define gte_rtv2_b()            __asm__ volatile ( ".word 0x4A496012;" )

#undef gte_rtir_b
#define gte_rtir_b()            __asm__ volatile ( ".word 0x4A49E012;" )

#undef gte_rtir_sf0_b
#define gte_rtir_sf0_b()        __asm__ volatile ( ".word 0x4A41E012;" )

#undef gte_rtv0tr_b
#define gte_rtv0tr_b()          __asm__ volatile ( ".word 0x4A480012;" )

#undef gte_rtv1tr_b
#define gte_rtv1tr_b()          __asm__ volatile ( ".word 0x4A488012;" )

#undef gte_rtv2tr_b
#define gte_rtv2tr_b()          __asm__ volatile ( ".word 0x4A490012;" )

#undef gte_rtirtr_b
#define gte_rtirtr_b()          __asm__ volatile ( ".word 0x4A498012;" )

#undef gte_rtv0bk_b
#define gte_rtv0bk_b()          __asm__ volatile ( ".word 0x4A482012;" )

#undef gte_rtv1bk_b
#define gte_rtv1bk_b()          __asm__ volatile ( ".word 0x4A48A012;" )

#undef gte_rtv2bk_b
#define gte_rtv2bk_b()          __asm__ volatile ( ".word 0x4A492012;" )

#undef gte_rtirbk_b
#define gte_rtirbk_b()          __asm__ volatile ( ".word 0x4A49A012;" )

#undef gte_ll_b
#define gte_ll_b()              __asm__ volatile ( ".word 0x4A4A6412;" )

#undef gte_llv0_b
#define gte_llv0_b()            __asm__ volatile ( ".word 0x4A4A6012;" )

#undef gte_llv1_b
#define gte_llv1_b()            __asm__ volatile ( ".word 0x4A4AE012;" )

#undef gte_llv2_b
#define gte_llv2_b()            __asm__ volatile ( ".word 0x4A4B6012;" )

#undef gte_llir_b
#define gte_llir_b()            __asm__ volatile ( ".word 0x4A4BE012;" )

#undef gte_llv0tr_b
#define gte_llv0tr_b()          __asm__ volatile ( ".word 0x4A4A0012;" )

#undef gte_llv1tr_b
#define gte_llv1tr_b()          __asm__ volatile ( ".word 0x4A4A8012;" )

#undef gte_llv2tr_b
#define gte_llv2tr_b()          __asm__ volatile ( ".word 0x4A4B0012;" )

#undef gte_llirtr_b
#define gte_llirtr_b()          __asm__ volatile ( ".word 0x4A4B8012;" )

#undef gte_llv0bk_b
#define gte_llv0bk_b()          __asm__ volatile ( ".word 0x4A4A2012;" )

#undef gte_llv1bk_b
#define gte_llv1bk_b()          __asm__ volatile ( ".word 0x4A4AA012;" )

#undef gte_llv2bk_b
#define gte_llv2bk_b()          __asm__ volatile ( ".word 0x4A4B2012;" )

#undef gte_llirbk_b
#define gte_llirbk_b()          __asm__ volatile ( ".word 0x4A4BA012;" )

#undef gte_lc_b
#define gte_lc_b()              __asm__ volatile ( ".word 0x4A4DA412;" )

#undef gte_lcv0_b
#define gte_lcv0_b()            __asm__ volatile ( ".word 0x4A4C6012;" )

#undef gte_lcv1_b
#define gte_lcv1_b()            __asm__ volatile ( ".word 0x4A4CE012;" )

#undef gte_lcv2_b
#define gte_lcv2_b()            __asm__ volatile ( ".word 0x4A4D6012;" )

#undef gte_lcir_b
#define gte_lcir_b()            __asm__ volatile ( ".word 0x4A4DE012;" )

#undef gte_lcv0tr_b
#define gte_lcv0tr_b()          __asm__ volatile ( ".word 0x4A4C0012;" )

#undef gte_lcv1tr_b
#define gte_lcv1tr_b()          __asm__ volatile ( ".word 0x4A4C8012;" )

#undef gte_lcv2tr_b
#define gte_lcv2tr_b()          __asm__ volatile ( ".word 0x4A4D0012;" )

#undef gte_lcirtr_b
#define gte_lcirtr_b()          __asm__ volatile ( ".word 0x4A4D8012;" )

#undef gte_lcv0bk_b
#define gte_lcv0bk_b()          __asm__ volatile ( ".word 0x4A4C2012;" )

#undef gte_lcv1bk_b
#define gte_lcv1bk_b()          __asm__ volatile ( ".word 0x4A4CA012;" )

#undef gte_lcv2bk_b
#define gte_lcv2bk_b()          __asm__ volatile ( ".word 0x4A4D2012;" )

#undef gte_lcirbk_b
#define gte_lcirbk_b()          __asm__ volatile ( ".word 0x4A4DA012;" )

#undef gte_dpcl_b
#define gte_dpcl_b()            __asm__ volatile ( ".word 0x4A680029;" )

#undef gte_dpcs_b
#define gte_dpcs_b()            __asm__ volatile ( ".word 0x4A780010;" )

#undef gte_dpct_b
#define gte_dpct_b()            __asm__ volatile ( ".word 0x4AF8002A;" )

#undef gte_intpl_b
#define gte_intpl_b()           __asm__ volatile ( ".word 0x4A980011;" )

#undef gte_sqr12_b
#define gte_sqr12_b()           __asm__ volatile ( ".word 0x4AA80428;" )

#undef gte_sqr0_b
#define gte_sqr0_b()            __asm__ volatile ( ".word 0x4AA00428;" )

#undef gte_ncs_b
#define gte_ncs_b()             __asm__ volatile ( ".word 0x4AC8041E;" )

#undef gte_nct_b
#define gte_nct_b()             __asm__ volatile ( ".word 0x4AD80420;" )

#undef gte_ncds_b
#define gte_ncds_b()            __asm__ volatile ( ".word 0x4AE80413;" )

#undef gte_ncdt_b
#define gte_ncdt_b()            __asm__ volatile ( ".word 0x4AF80416;" )

#undef gte_nccs_b
#define gte_nccs_b()            __asm__ volatile ( ".word 0x4B08041B;" )

#undef gte_ncct_b
#define gte_ncct_b()            __asm__ volatile ( ".word 0x4B18043F;" )

#undef gte_cdp_b
#define gte_cdp_b()             __asm__ volatile ( ".word 0x4B280414;" )

#undef gte_cc_b
#define gte_cc_b()              __asm__ volatile ( ".word 0x4B38041C;" )

#undef gte_nclip_b
#define gte_nclip_b()           __asm__ volatile ( ".word 0x4B400006;" )

#undef gte_avsz3_b
#define gte_avsz3_b()           __asm__ volatile ( ".word 0x4B58002D;" )

#undef gte_avsz4_b
#define gte_avsz4_b()           __asm__ volatile ( ".word 0x4B68002E;" )

#undef gte_op12_b
#define gte_op12_b()            __asm__ volatile ( ".word 0x4B78000C;" )

#undef gte_op0_b
#define gte_op0_b()             __asm__ volatile ( ".word 0x4B70000C;" )

#undef gte_gpf12_b
#define gte_gpf12_b()           __asm__ volatile ( ".word 0x4B98003D;" )

#undef gte_gpf0_b
#define gte_gpf0_b()            __asm__ volatile ( ".word 0x4B90003D;" )

#undef gte_gpl12_b
#define gte_gpl12_b()           __asm__ volatile ( ".word 0x4BA8003E;" )

#undef gte_gpl0_b
#define gte_gpl0_b()            __asm__ volatile ( ".word 0x4BA0003E;" )

#undef gte_mvmva_core_b
#define gte_mvmva_core_b( r0 )  __asm__ volatile (              \
        "cop2 %0"                                               \
        :                                                       \
        : "g"( r0 ) )

#include <gtemac.h>

#endif /* __psyz */

#endif
