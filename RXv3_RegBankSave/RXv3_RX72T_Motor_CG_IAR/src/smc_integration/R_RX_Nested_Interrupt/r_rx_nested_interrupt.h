#ifndef R_RX_NESTED_INTERRUPT_H
#define R_RX_NESTED_INTERRUPT_H

#include "mcu/all/r_rx_compiler.h"
#undef R_BSP_PRAGMA_STATIC_INTERRUPT
#undef R_BSP_ATTRIB_STATIC_INTERRUPT

#if defined(__RXV1) || defined(__RXV2) || defined(BSP_BOARD_GENERIC_RX66T)
#define MY_BSP_CFG_UNNESTED_IPL_MAX  9 // 0 <= defined value <= 15 (default value is BSP_CFG_FIT_IPL_MAX)
#else
/*
 * Register save banks of MY_BSP_CFG_UNNESTED_IPL_MAX ... maximum interrupt priority level among IPRs are used.
 * Moreover,  in case of CC-RX, additional register save bank of MY_BSP_CFG_REG_BANK_SCRATCH is temporally used.
 */
#define MY_BSP_CFG_UNNESTED_IPL_MAX  9 // 0 <= defined value <= 15 (default value is BSP_CFG_FIT_IPL_MAX)
#define MY_BSP_CFG_REG_BANK_SCRATCH 15 // 0 <= defined value < MY_BSP_CFG_UNNESTED_IPL_MAX or maximum interrupt priority level among IPRs <= defined value <= 15 (default value is 15)
#endif

#if defined(__RXV1) || defined(__RXV2) || defined(BSP_BOARD_GENERIC_RX66T)

#if defined(__CCRX__)

#define R_BSP_ASM_TOKEN_SHARP  #
#define R_BSP_ASM_IMM(imm) R_BSP_ASM_TOKEN_SHARP (imm)

#define R_BSP_PRAGMA_INTERRUPT_Helper_concat(t1, t2) t1##t2

#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect_no)         R_BSP_PRAGMA(interrupt _##function_name(vect=vect_no, no_acc))\
                                                                      R_BSP_PRAGMA(interrupt R_BSP_PRAGMA_INTERRUPT_Helper_concat(_##function_name##__vect, vect_no))\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_111)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_112)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_113)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_114)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_115)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_201)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_202)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_203)\
                                                                      static void _##function_name##_asm_111(void){ MVFC PSW, R1  }\
                                                                      static void _##function_name##_asm_112(void){ SHLR R_BSP_ASM_IMM(24), R1 }\
                                                                      static void _##function_name##_asm_113(void){ AND R_BSP_ASM_IMM(15), R1  }\
                                                                      static uint32_t _##function_name##_asm_114(void){ /* Non */ }/* return R1(i.e. return PSW.IPL) */\
                                                                      static void _##function_name##_asm_115(void){ SETPSW I      }\
                                                                      static void _##function_name##_asm_201(void){ POP R1        }\
                                                                      static void _##function_name##_asm_202(void){ ADD R_BSP_ASM_IMM((7 - 1) * 4), R0 }\
                                                                      static void _##function_name##_asm_203(void){ BRA.W R_BSP_PRAGMA_INTERRUPT_Helper_concat(__##function_name##__vect, vect_no) }\
                                                                      /* The above BRA.`W` is necessary because _func and _func__vectXXX may be far from each other in this case. */\
                                                                      static void _##function_name(void)\
                                                                      {\
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          _##function_name##_asm_111();\
                                                                          _##function_name##_asm_112();\
                                                                          _##function_name##_asm_113();\
                                                                          if(MY_BSP_CFG_UNNESTED_IPL_MAX > _##function_name##_asm_114())/* label is unavailable in inline_asm code in macro. */\
                                                                          {\
                                                                              R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);/* MVTIPL #IMM:4 */\
                                                                          }\
                                                                          _##function_name##_asm_115();\
                                                                          _##function_name##_asm_201();\
                                                                          _##function_name##_asm_202();\
                                                                          /* The following function never return. */\
                                                                          _##function_name##_asm_203();\
                                                                      }\
                                                                      R_BSP_PRAGMA(inline function_name)\
                                                                      void R_BSP_PRAGMA_INTERRUPT_Helper_concat(_##function_name##__vect, vect_no)(void)\
                                                                      {\
                                                                          static void function_name(void);\
                                                                          function_name();\
                                                                      }

#define R_BSP_ATTRIB_STATIC_INTERRUPT                                 static

#elif defined(__GNUC__)

#define U_BSP_SECNAME_ISRTEXT ".isrtext"
#define U_BSP_ASM_END_WITH_NO_RETURN );

#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect_no)         static void _##function_name(void) __attribute__((interrupt(R_BSP_SECNAME_INTVECTTBL, vect_no), naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      static void function_name(void) __attribute__((interrupt, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      static void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1    \n"\
                                                                          "MVFC PSW, R1 \n"\
                                                                          "SHLR #24, R1 \n"\
                                                                          "AND #15, R1  \n"\
                                                                          "CMP %0, R1   \n"\
                                                                          "BGEU ?+      \n"\
                                                                          "MVTIPL %0    \n"\
                                                                          "?:           \n"\
                                                                          "SETPSW I     \n"\
                                                                          "POP R1       \n"\
                                                                          "BRA.B _" #function_name " \n"/* BRA.B may not be necessary but it is intended for the safe. */\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }

#define R_BSP_ATTRIB_STATIC_INTERRUPT                                 static

#elif defined(__ICCRX__)

#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect_no)         static __interrupt void function_name(void);\
                                                                      R_BSP_PRAGMA(required=function_name)\
                                                                      R_BSP_PRAGMA(vector=vect_no)\
                                                                      static __interrupt void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1    \n"\
                                                                          "MVFC PSW, R1 \n"\
                                                                          "SHLR #24, R1 \n"\
                                                                          "AND #15, R1  \n"\
                                                                          "CMP %0, R1   \n"\
                                                                          "BGEU _lab1   \n"\
                                                                          "MVTIPL %0    \n"\
                                                                          "_lab1:       \n"\
                                                                          "SETPSW I     \n"\
                                                                          "POP R1       \n"\
                                                                          "BRA.W _" #function_name " \n"/* BRA.`W` is necessary because _func and func may be far from each other in this case. */\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      R_BSP_ASM_END \
                                                                      }/* RTE is here. */

#define R_BSP_ATTRIB_STATIC_INTERRUPT                                 static __interrupt

#endif

#if defined(__CCRX__)

#define _R_CG_ATTRIB_INTERRUPT_EHI(function_name, ...)
#define _R_CG_ATTRIB_INTERRUPT_EHI_vect(...) vect __VA_ARGS__, save, no_acc)
#define R_CG_ATTRIB_INTERRUPT_EHI_vect _R_CG_ATTRIB_INTERRUPT_EHI_vect(
#define R_CG_ATTRIB_INTERRUPT_EHI_void_R_CG_ATTRIB_INTERRUPT_EHI(function_name, ...) void);\
                                                                      R_BSP_PRAGMA(interrupt _##function_name##__vectXXX)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_111)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_112)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_113)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_114)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_115)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_201)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_202)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_203)\
                                                                      static void _##function_name##_asm_111(void){ MVFC PSW, R1  }\
                                                                      static void _##function_name##_asm_112(void){ SHLR R_BSP_ASM_IMM(24), R1 }\
                                                                      static void _##function_name##_asm_113(void){ AND R_BSP_ASM_IMM(15), R1  }\
                                                                      static uint32_t _##function_name##_asm_114(void){ /* Non */ }/* return R1(i.e. return PSW.IPL) */\
                                                                      static void _##function_name##_asm_115(void){ SETPSW I      }\
                                                                      static void _##function_name##_asm_201(void){ POP R1        }\
                                                                      static void _##function_name##_asm_202(void){ ADD R_BSP_ASM_IMM((7 - 1) * 4), R0 }\
                                                                      static void _##function_name##_asm_203(void){ BRA.S __##function_name##__vectXXX }\
                                                                      /* The above BRA.S is intended to skip POPM R1-R5, POPM R14-R15, RTE at the end of the following interrupt function. */\
                                                                      static void _##function_name(void)\
                                                                      {\
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          _##function_name##_asm_111();\
                                                                          _##function_name##_asm_112();\
                                                                          _##function_name##_asm_113();\
                                                                          if(MY_BSP_CFG_UNNESTED_IPL_MAX > _##function_name##_asm_114())/* label is unavailable in inline_asm code in macro. */\
                                                                          {\
                                                                              R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);/* MVTIPL #IMM:4 */\
                                                                          }\
                                                                          _##function_name##_asm_115();\
                                                                          _##function_name##_asm_201();\
                                                                          _##function_name##_asm_202();\
                                                                          /* The following function never return. */\
                                                                          _##function_name##_asm_203();\
                                                                      }\
                                                                      R_BSP_PRAGMA(inline function_name)\
                                                                      void _##function_name##__vectXXX(void)\
                                                                      {\
                                                                          static void function_name(void);\
                                                                          function_name();\
                                                                      }\
                                                                      static void function_name(void
#define R_CG_ATTRIB_INTERRUPT_EHI(function_name, ...) _##function_name(R_CG_ATTRIB_INTERRUPT_EHI_##__VA_ARGS__##_R_CG_ATTRIB_INTERRUPT_EHI(function_name, __VA_ARGS__))

#define _R_CG_ATTRIB_INTERRUPT_EI_vect(...) enable, vect __VA_ARGS__)
#define R_CG_ATTRIB_INTERRUPT_EI_vect _R_CG_ATTRIB_INTERRUPT_EI_vect(
#define R_CG_ATTRIB_INTERRUPT_EI_void void
#define R_CG_ATTRIB_INTERRUPT_EI(function_name, ...) function_name(R_CG_ATTRIB_INTERRUPT_EI_##__VA_ARGS__)

#elif defined(__GNUC__)

#define R_CG_ATTRIB_INTERRUPT_EHI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      function_name(void) __attribute__((naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      void _##function_name(void) __attribute__((interrupt, section(U_BSP_SECNAME_ISRTEXT "." #function_name)));\
                                                                      void function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1    \n"\
                                                                          "MVFC PSW, R1 \n"\
                                                                          "SHLR #24, R1 \n"\
                                                                          "AND #15, R1  \n"\
                                                                          "CMP %0, R1   \n"\
                                                                          "BGEU ?+      \n"\
                                                                          "MVTIPL %0    \n"\
                                                                          "?:           \n"\
                                                                          "SETPSW I     \n"\
                                                                          "POP R1       \n"\
                                                                          "BRA.B __" #function_name " \n"/* BRA.B may not be necessary but it is intended for the safe. */\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }\
                                                                      void _##function_name(void)/* Be aware that the leading `_` is necessary here. */

#define R_CG_ATTRIB_INTERRUPT_EI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      function_name(void) __attribute__((naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      void _##function_name(void) __attribute__((interrupt, section(U_BSP_SECNAME_ISRTEXT "." #function_name)));\
                                                                      void function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          "SETPSW I     \n"\
                                                                          "BRA.B __" #function_name " \n"/* BRA.B may not be necessary but it is intended for the safe. */\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }\
                                                                      void _##function_name(void)/* Be aware that the leading `_` is necessary here. */

#elif defined(__ICCRX__)

#define R_CG_ATTRIB_INTERRUPT_EHI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      _##function_name(void);\
                                                                      static __interrupt void function_name(void);\
                                                                      R_BSP_PRAGMA(required=function_name)\
                                                                      static __interrupt void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1    \n"\
                                                                          "MVFC PSW, R1 \n"\
                                                                          "SHLR #24, R1 \n"\
                                                                          "AND #15, R1  \n"\
                                                                          "CMP %0, R1   \n"\
                                                                          "BGEU _lab1   \n"\
                                                                          "MVTIPL %0    \n"\
                                                                          "_lab1:       \n"\
                                                                          "SETPSW I     \n"\
                                                                          "POP R1       \n"\
                                                                          "BRA.S _" #function_name " \n"/* BRA.S is intended to skip RTE at the end of this interrupt function. */\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      R_BSP_ASM_END \
                                                                      }/* RTE is here. */\
                                                                      static __interrupt void function_name(void)

#define R_CG_ATTRIB_INTERRUPT_EI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      _##function_name(void);\
                                                                      static __interrupt void function_name(void);\
                                                                      R_BSP_PRAGMA(required=function_name)\
                                                                      static __interrupt void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          "SETPSW I     \n"\
                                                                          "BRA.S _" #function_name " \n"/* BRA.S is intended to skip RTE at the end of this interrupt function. */\
                                                                      R_BSP_ASM_END \
                                                                      }/* RTE is here. */\
                                                                      static __interrupt void function_name(void)

#endif

#else

#if defined(__CCRX__)

#define R_BSP_ASM_TOKEN_SHARP #
#define R_BSP_ASM_IMM(imm) R_BSP_ASM_TOKEN_SHARP (imm)

#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect_no)         R_BSP_PRAGMA(interrupt _##function_name(vect=vect_no, bank=MY_BSP_CFG_REG_BANK_SCRATCH))\
                                                                      R_BSP_PRAGMA(noinline function_name)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_101)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_111)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_112)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_113)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_114)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_201)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_202)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_203)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_204)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_301)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_302)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_303)\
                                                                      static void _##function_name##_asm_101(void){ PUSH.L R1     }\
                                                                      static void _##function_name##_asm_111(void){ MVFC PSW, R1  }\
                                                                      static void _##function_name##_asm_112(void){ BFMOVZ R_BSP_ASM_IMM(24), R_BSP_ASM_IMM(0), R_BSP_ASM_IMM(4), R1, R1 }\
                                                                      static uint32_t _##function_name##_asm_113(void){ /* Non */ }/* return R1(i.e. return PSW.IPL) */\
                                                                      static void _##function_name##_asm_114(void){ SETPSW I      }\
                                                                      static void _##function_name##_asm_201(void){ MVFC PSW, R1  }\
                                                                      static void _##function_name##_asm_202(void){ BFMOVZ R_BSP_ASM_IMM(24), R_BSP_ASM_IMM(0), R_BSP_ASM_IMM(4), R1, R1 }\
                                                                      static void _##function_name##_asm_203(void){ SAVE R1       }\
                                                                      static void _##function_name##_asm_204(void){ MOV.L R1, R6  }/* R6 is either unmodified or saved/restored in any function. */\
                                                                      static void _##function_name##_asm_301(void){ RSTR R6       }\
                                                                      static void _##function_name##_asm_302(void){ POP R1        }\
                                                                      static void _##function_name##_asm_303(void){ RTE           }\
                                                                      static void _##function_name(void)\
                                                                      {\
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          _##function_name##_asm_101();\
                                                                          _##function_name##_asm_111();\
                                                                          _##function_name##_asm_112();\
                                                                          if(MY_BSP_CFG_UNNESTED_IPL_MAX > _##function_name##_asm_113())/* label is unavailable in inline_asm code in macro. */\
                                                                          {\
                                                                              R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);/* MVTIPL #IMM:4 */\
                                                                          }\
                                                                          _##function_name##_asm_114();\
                                                                          /* Basic concept of Register Save Bank usage: */\
                                                                          /* __SAVE(PSW.IPL); */\
                                                                          /* function();      */\
                                                                          /* __RSTR(PSW.IPL); */\
                                                                          _##function_name##_asm_201();\
                                                                          _##function_name##_asm_202();\
                                                                          _##function_name##_asm_203();\
                                                                          _##function_name##_asm_204();\
                                                                          static void function_name(void);\
                                                                          function_name();\
                                                                          _##function_name##_asm_301();\
                                                                          _##function_name##_asm_302();\
                                                                          _##function_name##_asm_303();\
                                                                      }

#define R_BSP_ATTRIB_STATIC_INTERRUPT                                 static

#elif defined(__GNUC__)

#define U_BSP_SECNAME_ISRTEXT ".isrtext"
#define U_BSP_ASM_END_WITH_NO_RETURN );

#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect_no)         static void _##function_name(void) __attribute__((interrupt(R_BSP_SECNAME_INTVECTTBL, vect_no), naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      static void function_name(void) __attribute__((section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      static void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1                   \n"\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "CMP %0, R1                  \n"\
                                                                          "BGEU ?+                     \n"\
                                                                          "MVTIPL %0                   \n"\
                                                                          "?:                          \n"\
                                                                          "SETPSW I                    \n"\
                                                                          /* Basic concept of Register Save Bank usage: */\
                                                                          /* __SAVE(PSW.IPL); */\
                                                                          /* function();      */\
                                                                          /* __RSTR(PSW.IPL); */\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "SAVE R1                     \n"\
                                                                          "MOV.L R1, R6                \n"/* R6 is either unmodified or saved/restored in any function. */\
                                                                          "BSR.W _" #function_name   " \n"/* BSR.`W` is necessary because neither BSR.S nor BSR.B exist. */\
                                                                          "RSTR R6                     \n"\
                                                                          "POP R1                      \n"\
                                                                          "RTE                         \n"\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }

#define R_BSP_ATTRIB_STATIC_INTERRUPT                                 static

#elif defined(__ICCRX__)

#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect_no)         static void function_name(void);\
                                                                      R_BSP_PRAGMA(required=function_name)\
                                                                      R_BSP_PRAGMA(vector=vect_no)\
                                                                      static __interrupt void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1                   \n"\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "CMP %0, R1                  \n"\
                                                                          "BGEU _lab1                  \n"\
                                                                          "MVTIPL %0                   \n"\
                                                                          "_lab1:                      \n"\
                                                                          "SETPSW I                    \n"\
                                                                          /* Basic concept of Register Save Bank usage: */\
                                                                          /* __SAVE(PSW.IPL); */\
                                                                          /* function();      */\
                                                                          /* __RSTR(PSW.IPL); */\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "SAVE R1                     \n"\
                                                                          "MOV.L R1, R6                \n"/* R6 is either unmodified or saved/restored in any function. */\
                                                                          "BSR.W _" #function_name   " \n"/* BSR.`W` is necessary because neither BSR.S nor BSR.B exist. */\
                                                                          "RSTR R6                     \n"\
                                                                          "POP R1                      \n"\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      R_BSP_ASM_END \
                                                                      }/* RTE is here. */

#define R_BSP_ATTRIB_STATIC_INTERRUPT                                 static

#endif

#if defined(__CCRX__)

#define _R_CG_ATTRIB_INTERRUPT_EHI(function_name, ...)
#define _R_CG_ATTRIB_INTERRUPT_EHI_vect(...) vect __VA_ARGS__, bank=MY_BSP_CFG_REG_BANK_SCRATCH)
#define R_CG_ATTRIB_INTERRUPT_EHI_vect _R_CG_ATTRIB_INTERRUPT_EHI_vect(
#define R_CG_ATTRIB_INTERRUPT_EHI_void_R_CG_ATTRIB_INTERRUPT_EHI(function_name, ...) void);\
                                                                      R_BSP_PRAGMA(noinline function_name)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_101)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_111)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_112)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_113)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_114)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_201)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_202)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_203)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_204)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_301)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_302)\
                                                                      R_BSP_PRAGMA(inline_asm _##function_name##_asm_303)\
                                                                      static void _##function_name##_asm_101(void){ PUSH.L R1     }\
                                                                      static void _##function_name##_asm_111(void){ MVFC PSW, R1  }\
                                                                      static void _##function_name##_asm_112(void){ BFMOVZ R_BSP_ASM_IMM(24), R_BSP_ASM_IMM(0), R_BSP_ASM_IMM(4), R1, R1 }\
                                                                      static uint32_t _##function_name##_asm_113(void){ /* Non */ }/* return R1(i.e. return PSW.IPL) */\
                                                                      static void _##function_name##_asm_114(void){ SETPSW I      }\
                                                                      static void _##function_name##_asm_201(void){ MVFC PSW, R1  }\
                                                                      static void _##function_name##_asm_202(void){ BFMOVZ R_BSP_ASM_IMM(24), R_BSP_ASM_IMM(0), R_BSP_ASM_IMM(4), R1, R1 }\
                                                                      static void _##function_name##_asm_203(void){ SAVE R1       }\
                                                                      static void _##function_name##_asm_204(void){ MOV.L R1, R6  }/* R6 is either unmodified or saved/restored in any function. */\
                                                                      static void _##function_name##_asm_301(void){ RSTR R6       }\
                                                                      static void _##function_name##_asm_302(void){ POP R1        }\
                                                                      static void _##function_name##_asm_303(void){ RTE           }\
                                                                      static void _##function_name(void)\
                                                                      {\
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          _##function_name##_asm_101();\
                                                                          _##function_name##_asm_111();\
                                                                          _##function_name##_asm_112();\
                                                                          if(MY_BSP_CFG_UNNESTED_IPL_MAX > _##function_name##_asm_113())/* label is unavailable in inline_asm code in macro. */\
                                                                          {\
                                                                              R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);/* MVTIPL #IMM:4 */\
                                                                          }\
                                                                          _##function_name##_asm_114();\
                                                                          /* Basic concept of Register Save Bank usage: */\
                                                                          /* __SAVE(PSW.IPL); */\
                                                                          /* function();      */\
                                                                          /* __RSTR(PSW.IPL); */\
                                                                          _##function_name##_asm_201();\
                                                                          _##function_name##_asm_202();\
                                                                          _##function_name##_asm_203();\
                                                                          _##function_name##_asm_204();\
                                                                          static void function_name(void);\
                                                                          function_name();\
                                                                          _##function_name##_asm_301();\
                                                                          _##function_name##_asm_302();\
                                                                          _##function_name##_asm_303();\
                                                                      }\
                                                                      static void function_name(void
#define R_CG_ATTRIB_INTERRUPT_EHI(function_name, ...) _##function_name(R_CG_ATTRIB_INTERRUPT_EHI_##__VA_ARGS__##_R_CG_ATTRIB_INTERRUPT_EHI(function_name, __VA_ARGS__))

#define _R_CG_ATTRIB_INTERRUPT_EI_vect(...) enable, vect __VA_ARGS__)
#define R_CG_ATTRIB_INTERRUPT_EI_vect _R_CG_ATTRIB_INTERRUPT_EI_vect(
#define R_CG_ATTRIB_INTERRUPT_EI_void void
#define R_CG_ATTRIB_INTERRUPT_EI(function_name, ...) function_name(R_CG_ATTRIB_INTERRUPT_EI_##__VA_ARGS__)

#define _R_CG_ATTRIB_INTERRUPT_BANK_bank(bank_no) , bank = bank_no
#define _R_CG_ATTRIB_INTERRUPT_BANK_vect(...) vect __VA_ARGS__)
#define R_CG_ATTRIB_INTERRUPT_BANK_vect _R_CG_ATTRIB_INTERRUPT_BANK_vect(
#define R_CG_ATTRIB_INTERRUPT_BANK_void_R_CG_ATTRIB_INTERRUPT_BANK_bank(...) void
#define R_CG_ATTRIB_INTERRUPT_BANK(function_name, bank_no, ...) function_name(R_CG_ATTRIB_INTERRUPT_BANK_##__VA_ARGS__##_R_CG_ATTRIB_INTERRUPT_BANK_bank(bank_no))

#define _R_CG_ATTRIB_INTERRUPT_BANK_EI_bank(bank_no) , bank = bank_no
#define _R_CG_ATTRIB_INTERRUPT_BANK_EI_vect(...) enable, vect __VA_ARGS__)
#define R_CG_ATTRIB_INTERRUPT_BANK_EI_vect _R_CG_ATTRIB_INTERRUPT_BANK_EI_vect(
#define R_CG_ATTRIB_INTERRUPT_BANK_EI_void_R_CG_ATTRIB_INTERRUPT_BANK_EI_bank(...) void
#define R_CG_ATTRIB_INTERRUPT_BANK_EI(function_name, bank_no, ...) function_name(R_CG_ATTRIB_INTERRUPT_BANK_EI_##__VA_ARGS__##_R_CG_ATTRIB_INTERRUPT_BANK_EI_bank(bank_no))

#elif defined(__GNUC__)

#define R_CG_ATTRIB_INTERRUPT_EHI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      function_name(void) __attribute__((naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      void _##function_name(void) __attribute__((section(U_BSP_SECNAME_ISRTEXT "." #function_name)));\
                                                                      void function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1                   \n"\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "CMP %0, R1                  \n"\
                                                                          "BGEU ?+                     \n"\
                                                                          "MVTIPL %0                   \n"\
                                                                          "?:                          \n"\
                                                                          "SETPSW I                    \n"\
                                                                          /* Basic concept of Register Save Bank usage: */\
                                                                          /* __SAVE(PSW.IPL); */\
                                                                          /* function();      */\
                                                                          /* __RSTR(PSW.IPL); */\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "SAVE R1                     \n"\
                                                                          "MOV.L R1, R6                \n"/* R6 is either unmodified or saved/restored in any function. */\
                                                                          "BSR.W __" #function_name  " \n"/* BSR.`W` is necessary because neither BSR.S nor BSR.B exist. */\
                                                                          "RSTR R6                     \n"\
                                                                          "POP R1                      \n"\
                                                                          "RTE                         \n"\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }\
                                                                      void _##function_name(void)/* Be aware that the leading `_` is necessary here. */

#define R_CG_ATTRIB_INTERRUPT_EI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      function_name(void) __attribute__((naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      void _##function_name(void) __attribute__((interrupt, section(U_BSP_SECNAME_ISRTEXT "." #function_name)));\
                                                                      void function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          "SETPSW I                    \n"\
                                                                          "BRA.B __" #function_name  " \n"/* BRA.B may not be necessary but it is intended for the safe. */\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }\
                                                                      void _##function_name(void)/* Be aware that the leading `_` is necessary here. */

#define R_CG_ATTRIB_INTERRUPT_BANK(function_name, bank_no, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      function_name(void) __attribute__((naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      void _##function_name(void) __attribute__((section(U_BSP_SECNAME_ISRTEXT "." #function_name)));\
                                                                      void function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          "SAVE %0                     \n"\
                                                                          "BSR.W __" #function_name  " \n"/* BSR.`W` is necessary because neither BSR.S nor BSR.B exist. */\
                                                                          "RSTR %0                     \n"\
                                                                          "RTE                         \n"\
                                                                          ::"i"(bank_no)\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }\
                                                                      void _##function_name(void)/* Be aware that the leading `_` is necessary here. */

#define R_CG_ATTRIB_INTERRUPT_BANK_EI(function_name, bank_no, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      function_name(void) __attribute__((naked, section(U_BSP_SECNAME_ISRTEXT "." #function_name), used));\
                                                                      void _##function_name(void) __attribute__((section(U_BSP_SECNAME_ISRTEXT "." #function_name)));\
                                                                      void function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          "SETPSW I                    \n"\
                                                                          "SAVE %0                     \n"\
                                                                          "BSR.W __" #function_name  " \n"/* BSR.`W` is necessary because neither BSR.S nor BSR.B exist. */\
                                                                          "RSTR %0                     \n"\
                                                                          "RTE                         \n"\
                                                                          ::"i"(bank_no)\
                                                                      U_BSP_ASM_END_WITH_NO_RETURN \
                                                                      }\
                                                                      void _##function_name(void)/* Be aware that the leading `_` is necessary here. */

#elif defined(__ICCRX__)

#define R_CG_ATTRIB_INTERRUPT_EHI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      _##function_name(void);\
                                                                      static void function_name(void);\
                                                                      R_BSP_PRAGMA(required=function_name)\
                                                                      static __interrupt void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          /* Basic concept of unnested/nested interrupt: */\
                                                                          /* if(MY_BSP_CFG_UNNESTED_IPL_MAX > (((R_BSP_GET_PSW()) >> 24) & 0xF)) */\
                                                                          /* { */\
                                                                          /*     R_BSP_SET_IPL(MY_BSP_CFG_UNNESTED_IPL_MAX);*//* MVTIPL #IMM:4 */\
                                                                          /* } */\
                                                                          /* R_BSP_SETPSW_I(); */\
                                                                          "PUSH.L R1                   \n"\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "CMP %0, R1                  \n"\
                                                                          "BGEU _lab1                  \n"\
                                                                          "MVTIPL %0                   \n"\
                                                                          "_lab1:                      \n"\
                                                                          "SETPSW I                    \n"\
                                                                          /* Basic concept of Register Save Bank usage: */\
                                                                          /* __SAVE(PSW.IPL); */\
                                                                          /* function();      */\
                                                                          /* __RSTR(PSW.IPL); */\
                                                                          "MVFC PSW, R1                \n"\
                                                                          "BFMOVZ #18H, #0, #4, R1, R1 \n"\
                                                                          "SAVE R1                     \n"\
                                                                          "MOV.L R1, R6                \n"/* R6 is either unmodified or saved/restored in any function. */\
                                                                          "BSR.W _" #function_name   " \n"/* BSR.`W` is necessary because neither BSR.S nor BSR.B exist. */\
                                                                          "RSTR R6                     \n"\
                                                                          "POP R1                      \n"\
                                                                          ::"i"(MY_BSP_CFG_UNNESTED_IPL_MAX)\
                                                                      R_BSP_ASM_END \
                                                                      }/* RTE is here. */\
                                                                      static void function_name(void)

#define R_CG_ATTRIB_INTERRUPT_EI(function_name, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      _##function_name(void);\
                                                                      static __interrupt void function_name(void);\
                                                                      R_BSP_PRAGMA(required=function_name)\
                                                                      static __interrupt void _##function_name(void)\
                                                                      {\
                                                                      R_BSP_ASM_BEGIN \
                                                                          "SETPSW I                    \n"\
                                                                          "BRA.S _" #function_name   " \n"/* BRA.S is intended to skip RTE at the end of this interrupt function. */\
                                                                      R_BSP_ASM_END \
                                                                      }/* RTE is here. */\
                                                                      static __interrupt void function_name(void)

#define R_CG_ATTRIB_INTERRUPT_BANK(function_name, bank_no, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      function_name(void);\
                                                                      R_BSP_PRAGMA(bank=bank_no)\
                                                                      static __interrupt void function_name(void)

#define R_CG_ATTRIB_INTERRUPT_BANK_EI(function_name, bank_no, .../* This argument is unnecessary but for the compatibility between CC-RX and this compiler. */)\
                                                                      _##function_name(void);\
                                                                      R_BSP_PRAGMA(bank=bank_no)\
                                                                      static __interrupt void _##function_name(void)\
                                                                      {\
                                                                          R_BSP_SETPSW_I();\
                                                                          static void function_name(void);\
                                                                          function_name();\
                                                                      }\
                                                                      static void function_name(void)

#endif

#endif

#endif /* R_RX_NESTED_INTERRUPT_H */

