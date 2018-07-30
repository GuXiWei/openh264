/*!
 * \copy
 *     Copyright (c)  2013, Loongson Technology Co.,Ltd.
 *     All rights reserved.
 *
 *     Redistribution and use in source and binary forms, with or without
 *     modification, are permitted provided that the following conditions
 *     are met:
 *
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in
 *          the documentation and/or other materials provided with the
 *          distribution.
 *
 *     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *     "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *     COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *     BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *     CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *     LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *     ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *     POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef ASMDEFS_MMI_H_
#define ASMDEFS_MMI_H_

#define CACHE_LINE_SIZE 32

#if defined(__mips64) && defined(__LP64__)
# define mips_reg       int64_t
# define PTR_ADDU       "daddu "
# define PTR_ADDIU      "daddiu "
# define PTR_ADDI       "daddi "
# define PTR_SUBU       "dsubu "
# define PTR_L          "ld "
# define PTR_SRA        "dsra "
# define PTR_SRL        "dsrl "
# define PTR_SLL        "dsll "
# define PTR_MTC1       "dmtc1 "
# define PTR_LI         "dli "
#else
# define mips_reg       int32_t
# define PTR_ADDU       "addu "
# define PTR_ADDIU      "addiu "
# define PTR_ADDI       "addi "
# define PTR_SUBU       "subu "
# define PTR_L          "lw "
# define PTR_SRA        "sra "
# define PTR_SRL        "srl "
# define PTR_SLL        "sll "
# define PTR_MTC1       "mtc1 "
# define PTR_LI         "li "
#endif

/* *
 * SSE2_XSawp(bw, xmm0, xmm1, xmm2) to
 * MMI_XSawp_BH(f0, f2, f4, f6, f8, f10)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2
 * xmm1  l64->$f4, h64->$f6
 * xmm2  l64->$f8, h64->$f10
 * */
#define MMI_XSawp_BH(f0, f2, f4, f6, f8, f10) \
           "mov.d      "#f8", "#f2"                \n\t" \
           "punpckhbh  "#f2", "#f0", "#f4"         \n\t" \
           "punpcklbh  "#f0", "#f0", "#f4"         \n\t" \
           "punpckhbh  "#f10", "#f8", "#f6"        \n\t" \
           "punpcklbh  "#f8", "#f8", "#f6"         \n\t"

/* *
 * SSE2_XSawp(wd, xmm0, xmm1, xmm2) to
 * MMI_XSawp_HW(f0, f2, f4, f6, f8, f10)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2
 * xmm1  l64->$f4, h64->$f6
 * xmm2  l64->$f8, h64->$f10
 * */
#define MMI_XSawp_HW(f0, f2, f4, f6, f8, f10) \
           "mov.d      "#f8", "#f2"                \n\t" \
           "punpckhhw  "#f2", "#f0", "#f4"         \n\t" \
           "punpcklhw  "#f0", "#f0", "#f4"         \n\t" \
           "punpckhhw  "#f10", "#f8", "#f6"        \n\t" \
           "punpcklhw  "#f8", "#f8", "#f6"         \n\t"

/* *
 * SSE2_XSawp(dq, xmm0, xmm1, xmm2) to
 * MMI_XSawp_WD(f0, f2, f4, f6, f8, f10)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2
 * xmm1  l64->$f4, h64->$f6
 * xmm2  l64->$f8, h64->$f10
 * */
#define MMI_XSawp_WD(f0, f2, f4, f6, f8, f10) \
           "mov.d      "#f8", "#f2"                \n\t" \
           "punpckhwd  "#f2", "#f0", "#f4"         \n\t" \
           "punpcklwd  "#f0", "#f0", "#f4"         \n\t" \
           "punpckhwd  "#f10", "#f8", "#f6"        \n\t" \
           "punpcklwd  "#f8", "#f8", "#f6"         \n\t"

/* *
 * SSE2_XSawp(qdq, xmm0, xmm1, xmm2) to
 * MMI_XSawp_DQ(f0, f2, f4, f6, f8, f10)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2
 * xmm1  l64->$f4, h64->$f6
 * xmm2  l64->$f8, h64->$f10
 * */
#define MMI_XSawp_DQ(f0, f2, f4, f6, f8, f10) \
           "mov.d      "#f8", "#f2"                \n\t" \
           "mov.d      "#f2", "#f4"                \n\t" \
           "mov.d      "#f10", "#f6"               \n\t"

/* *
 * WELS_AbsW(xmm0, xmm1) to
 * WELS_AbsH(f0, f2, f4, f6, f8, f10)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2 for dst
 * xmm1  l64->$f4, h64->$f6 for src
 *       f8, f10 for tmp store
 * */
#define WELS_AbsH(f0, f2, f4, f6, f8, f10) \
           "xor        "#f8", "#f8", "#f8"         \n\t" \
           "psubh      "#f10", "#f8", "#f6"        \n\t" \
           "psubh      "#f8", "#f8", "#f4"         \n\t" \
           "pmaxsh     "#f0", "#f4", "#f8"         \n\t" \
           "pmaxsh     "#f2", "#f6", "#f10"        \n\t"

//; m2 = m1 + m2, m1 = m1 - m2
/* *
 * SSE2_SumSub(xmm0, xmm1, xmm2) to
 * MMI_SumSub(f0, f2, f4, f6, f8, f10)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2
 * xmm1  l64->$f4, h64->$f6
 * xmm2  l64->$f8, h64->f10
 * */
#define MMI_SumSub(f0, f2, f4, f6, f8, f10) \
           "mov.d      "#f8", "#f4"                    \n\t" \
           "mov.d      "#f10", "#f6"                   \n\t" \
           "paddh      "#f4", "#f4", "#f0"             \n\t" \
           "paddh      "#f6", "#f6", "#f2"             \n\t" \
           "psubh      "#f0", "#f0", "#f8"             \n\t" \
           "psubh      "#f2", "#f2", "#f10"            \n\t"

/* *
 * SSE2_LoadDiff8P(xmm0, xmm1, xmm2, r0, r1) to
 * MMI_LoadDiff8P(f0, f2, f4, f6, f8, r0, r1)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2
 * xmm1  l64->$f4, h64->$f6
 * xmm2  l64->$f8
 * */
#define MMI_LoadDiff8P(f0, f2, f4, f6, f8, r0, r1) \
           "gsldlc1    "#f0", 0x7("#r0")               \n\t" \
           "gsldlc1    "#f4", 0x7("#r1")               \n\t" \
           "gsldrc1    "#f0", 0x0("#r0")               \n\t" \
           "gsldrc1    "#f4", 0x0("#r1")               \n\t" \
           "punpckhbh  "#f2", "#f0", "#f8"             \n\t" \
           "punpcklbh  "#f0", "#f0", "#f8"             \n\t" \
           "punpckhbh  "#f6", "#f4", "#f8"             \n\t" \
           "punpcklbh  "#f4", "#f4", "#f8"             \n\t" \
           "psubh      "#f0", "#f0", "#f4"             \n\t" \
           "psubh      "#f2", "#f2", "#f6"             \n\t"

/* *
 * SSE2_TransTwo4x4W(xmm0, xmm1, xmm2, xmm3, xmm4) to
 * MMI_TransTwo4x4H(f0, f2, f4, f6, f8, f10, f12, f14, f16, f18)
 * register mapping:
 * xmm0  l64->$f0, h64->$f2
 * xmm1  l64->$f4, h64->$f6
 * xmm2  l64->$f8, h64->$f10
 * xmm3  l64->$f12, h64->$f14
 * xmm4  l64->$f16, h64->$f18
 * */
#define MMI_TransTwo4x4H(f0, f2, f4, f6, f8, f10, f12, f14, f16, f18) \
           MMI_XSawp_HW(f0, f2, f4, f6, f16, f18)  \
           MMI_XSawp_HW(f8, f10, f12, f14, f4, f6) \
           MMI_XSawp_WD(f0, f2, f8, f10, f12, f14) \
           MMI_XSawp_WD(f16, f18, f4, f6, f8, f10) \
           MMI_XSawp_DQ(f0, f2, f16, f18, f4, f6)  \
           MMI_XSawp_DQ(f12, f14, f8, f10, f16, f18)

#define MMI_TransTwo8x8B(f0, f2, f4, f6, f8, f10, f12, f14, f16, f18, f20, f22, f24, f26, f28, f30, r0, r1) \
           "dmfc1      "#r0", "#f28"                   \n\t" \
           "dmfc1      "#r1", "#f30"                   \n\t" \
           MMI_XSawp_BH(f0, f2, f4, f6, f28, f30)            \
           MMI_XSawp_BH(f8, f10, f12, f14, f4, f6)           \
           MMI_XSawp_BH(f16, f18, f20, f22, f12, f14)        \
           "dmtc1      "#r0", "#f20"                   \n\t" \
           "dmtc1      "#r1", "#f22"                   \n\t" \
           "dmfc1      "#r0", "#f12"                   \n\t" \
           "dmfc1      "#r1", "#f14"                   \n\t" \
           MMI_XSawp_BH(f24, f26, f20, f22, f12, f14)        \
           MMI_XSawp_HW(f0, f2, f8, f10, f20, f22)           \
           MMI_XSawp_HW(f28, f30, f4, f6, f8, f10)           \
           MMI_XSawp_HW(f16, f18, f24, f26, f4, f6)          \
           "dmtc1      "#r0", "#f24"                   \n\t" \
           "dmtc1      "#r1", "#f26"                   \n\t" \
           "dmfc1      "#r0", "#f8"                    \n\t" \
           "dmfc1      "#r1", "#f10"                   \n\t" \
           MMI_XSawp_HW(f24, f26, f12, f14, f8, f10)         \
           MMI_XSawp_WD(f0, f2, f16, f18, f12, f14)          \
           MMI_XSawp_WD(f20, f22, f4, f6, f16, f18)          \
           MMI_XSawp_WD(f28, f30, f24, f26, f4, f6)          \
           "dmtc1      "#r0", "#f24"                   \n\t" \
           "dmtc1      "#r1", "#f26"                   \n\t" \
           "dmfc1      "#r0", "#f16"                   \n\t" \
           "dmfc1      "#r1", "#f18"                   \n\t" \
           MMI_XSawp_WD(f24, f26, f8, f10, f16, f18)         \
           MMI_XSawp_DQ(f0, f2, f28, f30, f8, f10)           \
           MMI_XSawp_DQ(f12, f14, f4, f6, f28, f30)          \
           MMI_XSawp_DQ(f20, f22, f24, f26, f4, f6)          \
           "dmtc1      "#r0", "#f24"                   \n\t" \
           "dmtc1      "#r1", "#f26"                   \n\t" \
           "dmfc1      "#r0", "#f0"                    \n\t" \
           "dmfc1      "#r1", "#f2"                    \n\t" \
           MMI_XSawp_DQ(f24, f26, f16, f18, f0, f2)          \
           "dmtc1      "#r0", "#f16"                   \n\t" \
           "dmtc1      "#r1", "#f18"                   \n\t"

/* *
 * MMX_XSwap (wd, mm0, mm1, mm2) to
 * MMI_XSwap_HW_SINGLE(f0, f2, f4)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * */
#define MMI_XSwap_HW_SINGLE(f0, f2, f4) \
           "mov.d      "#f4", "#f0"                    \n\t" \
           "punpckhhw  "#f4", "#f4", "#f2"             \n\t" \
           "punpcklhw  "#f0", "#f0", "#f2"             \n\t"

/* *
 * MMX_XSwap (dq, mm0, mm1, mm2) to
 * MMI_XSwap_WD_SINGLE(f0, f2, f4)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * */
#define MMI_XSwap_WD_SINGLE(f0, f2, f4) \
           "mov.d      "#f4", "#f0"                    \n\t" \
           "punpckhwd  "#f4", "#f4", "#f2"             \n\t" \
           "punpcklwd  "#f0", "#f0", "#f2"             \n\t"

/* *
 * MMX_Trans4x4W(mm0, mm1, mm2, mm3, mm4) to
 * MMI_Trans4x4H_SINGLE(f0, f2, f4, f6, f8)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * mm3  ->$f6
 * mm4  ->$f8
 * */
#define MMI_Trans4x4H_SINGLE(f0, f2, f4, f6, f8) \
           MMI_XSwap_HW_SINGLE(f0, f2, f8)              \
           MMI_XSwap_HW_SINGLE(f4, f6, f2)              \
           MMI_XSwap_WD_SINGLE(f0, f4, f6)              \
           MMI_XSwap_WD_SINGLE(f8, f2, f4)

/* *
 * MMX_SumSub(mm0, mm1, mm2) to
 * MMI_SumSub_SINGLE(f0, f2, f4)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * */
#define MMI_SumSub_SINGLE(f0, f2, f4) \
           "mov.d      "#f4", "#f2"                    \n\t" \
           "psubh      "#f2", "#f2", "#f0"             \n\t" \
           "paddh      "#f0", "#f0", "#f4"             \n\t"

/* *
 * MMX_SumSubMul2(mm0, mm1, mm2) to
 * MMI_SumSubMul2_SINGLE(f0, f2, f4, f6)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * */
#define MMI_SumSubMul2_SINGLE(f0, f2, f4, f6) \
           "mov.d      "#f4", "#f0"                    \n\t" \
           "psllh      "#f0", "#f0", "#f6"             \n\t" \
           "paddh      "#f0", "#f0", "#f2"             \n\t" \
           "psllh      "#f2", "#f2", "#f6"             \n\t" \
           "psubh      "#f4", "#f4", "#f2"             \n\t"

//f4 should be 0x0
#define MMI_Copy8Times(f0, f2, f4, r0) \
           "dmtc1      "#r0", "#f0"                    \n\t" \
           "pshufh     "#f0", "#f0", "#f4"             \n\t" \
           "mov.d      "#f2", "#f0"                    \n\t"

//f4 should be 0x0
#define MMI_Copy16Times(f0, f2, f4, r0) \
           "dmtc1      "#r0", "#f0"                    \n\t" \
           "punpcklbh  "#f0", "#f0", "#f0"             \n\t" \
           "pshufh     "#f0", "#f0", "#f4"             \n\t" \
           "mov.d      "#f2", "#f0"                    \n\t"

/* *
 * MMX_SumSubDiv2(mm0, mm1, mm2) to
 * MMI_SumSubDiv2_SINGLE(f0, f2, f4, f6)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * */
#define MMI_SumSubDiv2_SINGLE(f0, f2, f4, f6) \
           "psrah      "#f4", "#f2", "#f6"             \n\t" \
           "paddh      "#f4", "#f4", "#f0"             \n\t" \
           "psrah      "#f0", "#f0", "#f6"             \n\t" \
           "psubh      "#f0", "#f0", "#f2"             \n\t"

/* *
 * MMX_IDCT(mm0, mm1, mm2, mm3, mm4, mm5) to
 * MMI_IDCT_SINGLE(f0, f2, f4, f6, f8, f10, f12)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * mm3  ->$f6
 * mm4  ->$f8
 * mm5  ->$f10
 *      $f12 is 0x1
 * */
#define MMI_IDCT_SINGLE(f0, f2, f4, f6, f8, f10, f12) \
           MMI_SumSub_SINGLE(f6, f8, f10)             \
           MMI_SumSubDiv2_SINGLE(f4, f2, f0, f12)     \
           MMI_SumSub_SINGLE(f0, f6, f10)             \
           MMI_SumSub_SINGLE(f4, f8, f10)

/* *
 * MMX_StoreDiff4P(mm0, mm1, mm2, mm3, r0, r1) to
 * MMI_StoreDiff4P_SIGLE(f0, f2, f4, f6, r0, r1)
 * register mapping:
 * mm0  ->$f0
 * mm1  ->$f2
 * mm2  ->$f4
 * f8 is 0x6
 * */
#define MMI_StoreDiff4P_SINGLE(f0, f2, f4, f6, r0, r1, f8) \
           "gsldlc1    "#f2", 0x7("#r1")               \n\t" \
           "gsldrc1    "#f2", 0x0("#r1")               \n\t" \
           "punpcklbh  "#f2", "#f2", "#f6"             \n\t" \
           "paddh      "#f0", "#f0", "#f4"             \n\t" \
           "psrah      "#f0", "#f0", "#f8"             \n\t" \
           "paddsh     "#f0", "#f0", "#f2"             \n\t" \
           "packushb   "#f0", "#f0", "#f2"             \n\t" \
           "gsswlc1    "#f0", 0x3("#r0")               \n\t" \
           "gsswrc1    "#f0", 0x0("#r0")               \n\t"

#define SUMH_HORIZON(f0, f2, f4, f6, f8) \
           "paddh      "#f0", "#f0", "#f2"                       \n\t" \
           "punpckhhw  "#f2", "#f0", "#f8"                       \n\t" \
           "punpcklhw  "#f0", "#f0", "#f8"                       \n\t" \
           "paddw      "#f0", "#f0", "#f2"                       \n\t" \
           "punpckhwd  "#f2", "#f0", "#f0"                       \n\t" \
           "paddw      "#f0", "#f0", "#f2"                       \n\t"

#define LOAD_COLUMN(f0, f2, f4, f6, f8, f10, f12, f14, r0, r1, r2) \
           "daddu      "#r2", "#r0", "#r1"                       \n\t" \
           "gsldlc1    "#f0", 0x7("#r0")                         \n\t" \
           "gsldlc1    "#f4", 0x7("#r2")                         \n\t" \
           "gsldrc1    "#f0", 0x0("#r0")                         \n\t" \
           "gsldrc1    "#f4", 0x0("#r2")                         \n\t" \
           "punpcklbh  "#f0", "#f0", "#f4"                       \n\t" \
           "daddu      "#r0", "#r2", "#r1"                       \n\t" \
           "daddu      "#r2", "#r0", "#r1"                       \n\t" \
           "gsldlc1    "#f8", 0x7("#r0")                         \n\t" \
           "gsldlc1    "#f4", 0x7("#r2")                         \n\t" \
           "gsldrc1    "#f8", 0x0("#r0")                         \n\t" \
           "gsldrc1    "#f4", 0x0("#r2")                         \n\t" \
           "punpcklbh  "#f8", "#f8", "#f4"                       \n\t" \
           "punpckhhw  "#f2", "#f0", "#f8"                       \n\t" \
           "punpcklhw  "#f0", "#f0", "#f8"                       \n\t" \
           "daddu      "#r0", "#r2", "#r1"                       \n\t" \
           "daddu      "#r2", "#r0", "#r1"                       \n\t" \
           "gsldlc1    "#f12", 0x7("#r0")                        \n\t" \
           "gsldlc1    "#f4", 0x7("#r2")                         \n\t" \
           "gsldrc1    "#f12", 0x0("#r0")                        \n\t" \
           "gsldrc1    "#f4", 0x0("#r2")                         \n\t" \
           "punpcklbh  "#f12", "#f12", "#f4"                     \n\t" \
           "daddu      "#r0", "#r2", "#r1"                       \n\t" \
           "daddu      "#r2", "#r0", "#r1"                       \n\t" \
           "gsldlc1    "#f8", 0x7("#r0")                         \n\t" \
           "gsldlc1    "#f4", 0x7("#r2")                         \n\t" \
           "gsldrc1    "#f8", 0x0("#r0")                         \n\t" \
           "gsldrc1    "#f4", 0x0("#r2")                         \n\t" \
           "punpcklbh  "#f8", "#f8", "#f4"                       \n\t" \
           "punpckhhw  "#f14", "#f12", "#f8"                     \n\t" \
           "punpcklhw  "#f12", "#f12", "#f8"                     \n\t" \
           "daddu      "#r0", "#r2", "#r1"                       \n\t" \
           "punpcklwd  "#f0", "#f2", "#f14"                      \n\t" \
           "punpckhwd  "#f2", "#f2", "#f14"                      \n\t"

#define LOAD_COLUMN_C(f0, f2, f4, f6, r0, r1, r2) \
           "daddu      "#r2", "#r0", "#r1"                       \n\t" \
           "gsldlc1    "#f0", 0x7("#r0")                         \n\t" \
           "gsldlc1    "#f2", 0x7("#r2")                         \n\t" \
           "gsldrc1    "#f0", 0x0("#r0")                         \n\t" \
           "gsldrc1    "#f2", 0x0("#r2")                         \n\t" \
           "punpcklbh  "#f0", "#f0", "#f2"                       \n\t" \
           "daddu      "#r0", "#r2", "#r1"                       \n\t" \
           "daddu      "#r2", "#r0", "#r1"                       \n\t" \
           "gsldlc1    "#f4", 0x7("#r0")                         \n\t" \
           "gsldlc1    "#f2", 0x7("#r2")                         \n\t" \
           "gsldrc1    "#f4", 0x0("#r0")                         \n\t" \
           "gsldrc1    "#f2", 0x0("#r2")                         \n\t" \
           "punpcklbh  "#f4", "#f4", "#f2"                       \n\t" \
           "punpckhhw  "#f0", "#f0", "#f4"                       \n\t" \
           "daddu      "#r0", "#r2", "#r1"                       \n\t"

# define OK             1
# define NOTOK          0

#endif  /* ASMDEFS_MMI_H_ */
