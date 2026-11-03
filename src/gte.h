#ifndef _GTE_H_
#define _GTE_H_

// GTE macros in the form of the PSY-Q 4.4 INLINE_C.H (DMPSX version 3). The build does not run DMPSX,
// so the command macros carry the real cop2 words that DMPSX would put in place of the placeholders.

#define gte_ldlvl(r0) __asm__ volatile( \
    "lwc2	$9, 0( %0 );"              \
    "lwc2	$10, 4( %0 );"             \
    "lwc2	$11, 8( %0 )"              \
    :                                  \
    : "r"(r0))

#define gte_ldsv(r0) __asm__ volatile( \
    "lhu	$12, 0( %0 );"              \
    "lhu	$13, 2( %0 );"              \
    "lhu	$14, 4( %0 );"              \
    "mtc2	$12, $9;"                  \
    "mtc2	$13, $10;"                 \
    "mtc2	$14, $11"                  \
    :                                 \
    : "r"(r0)                         \
    : "$12", "$13", "$14")

#define gte_ldclmv(r0) __asm__ volatile( \
    "lhu	$12, 0( %0 );"                \
    "lhu	$13, 6( %0 );"                \
    "lhu	$14, 12( %0 );"               \
    "mtc2	$12, $9;"                    \
    "mtc2	$13, $10;"                   \
    "mtc2	$14, $11"                    \
    :                                   \
    : "r"(r0)                           \
    : "$12", "$13", "$14")

#define gte_lddp(r0) __asm__ volatile( \
    "mtc2	%0, $8"                    \
    :                                 \
    : "r"(r0))

#define gte_SetRotMatrix(r0) __asm__ volatile( \
    "lw	$12, 0( %0 );"                       \
    "lw	$13, 4( %0 );"                       \
    "ctc2	$12, $0;"                         \
    "ctc2	$13, $1;"                         \
    "lw	$12, 8( %0 );"                       \
    "lw	$13, 12( %0 );"                      \
    "lw	$14, 16( %0 );"                      \
    "ctc2	$12, $2;"                         \
    "ctc2	$13, $3;"                         \
    "ctc2	$14, $4"                          \
    :                                        \
    : "r"(r0)                                \
    : "$12", "$13", "$14")

#define gte_SetLightMatrix(r0) __asm__ volatile( \
    "lw	$12, 0( %0 );"                         \
    "lw	$13, 4( %0 );"                         \
    "ctc2	$12, $8;"                           \
    "ctc2	$13, $9;"                           \
    "lw	$12, 8( %0 );"                         \
    "lw	$13, 12( %0 );"                        \
    "lw	$14, 16( %0 );"                        \
    "ctc2	$12, $10;"                          \
    "ctc2	$13, $11;"                          \
    "ctc2	$14, $12"                           \
    :                                          \
    : "r"(r0)                                  \
    : "$12", "$13", "$14")

#define gte_SetColorMatrix(r0) __asm__ volatile( \
    "lw	$12, 0( %0 );"                         \
    "lw	$13, 4( %0 );"                         \
    "ctc2	$12, $16;"                          \
    "ctc2	$13, $17;"                          \
    "lw	$12, 8( %0 );"                         \
    "lw	$13, 12( %0 );"                        \
    "lw	$14, 16( %0 );"                        \
    "ctc2	$12, $18;"                          \
    "ctc2	$13, $19;"                          \
    "ctc2	$14, $20"                           \
    :                                          \
    : "r"(r0)                                  \
    : "$12", "$13", "$14")

#define gte_stlvnl(r0) __asm__ volatile( \
    "swc2	$25, 0( %0 );"               \
    "swc2	$26, 4( %0 );"               \
    "swc2	$27, 8( %0 )"                \
    :                                   \
    : "r"(r0)                           \
    : "memory")

#define gte_stclmv(r0) __asm__ volatile( \
    "mfc2	$12, $9;"                    \
    "mfc2	$13, $10;"                   \
    "mfc2	$14, $11;"                   \
    "sh	$12, 0( %0 );"                  \
    "sh	$13, 6( %0 );"                  \
    "sh	$14, 12( %0 )"                  \
    :                                   \
    : "r"(r0)                           \
    : "$12", "$13", "$14", "memory")

#define gte_rtir() __asm__ volatile( \
    "nop;"                          \
    "nop;"                          \
    ".word 0x4a49e012")

#define gte_sqr0() __asm__ volatile( \
    "nop;"                          \
    "nop;"                          \
    ".word 0x4aa00428")

#define gte_gpf12() __asm__ volatile( \
    "nop;"                           \
    "nop;"                           \
    ".word 0x4b98003d")

#endif
