#include "r_smc_entry.h"

#if defined(__RXV3) && !defined(BSP_BOARD_GENERIC_RX66T)
#define __BANK 1
#endif

void main(void);
#if defined(__RXV3)
void Check_Using_DSQRT_FSQRT(void);
void Check_Not_Using_DSQRT_FSQRT(void);
void (*fp_Check_Using_DSQRT_FSQRT)(void);
void (*fp_Check_Not_Using_DSQRT_FSQRT)(void);
#endif

#define VECT_TRAP_0 0
#define VECT_TRAP_1 1
#define VECT_TRAP_2 2
#if defined(__BANK)
#define VECT_TRAP_3 3
#define VECT_TRAP_4 4
#endif

void main(void)
{
    R_BSP_SET_IPL( MY_BSP_CFG_UNNESTED_IPL_MAX - 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );
#if defined(__BANK)
    R_BSP_INT( VECT( TRAP, 3 ) );
    R_BSP_INT( VECT( TRAP, 4 ) );
#endif

    R_BSP_SET_IPL( MY_BSP_CFG_UNNESTED_IPL_MAX );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );
#if defined(__BANK)
    R_BSP_INT( VECT( TRAP, 3 ) );
    R_BSP_INT( VECT( TRAP, 4 ) );
#endif

    R_BSP_SET_IPL( MY_BSP_CFG_UNNESTED_IPL_MAX + 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );
#if defined(__BANK)
    R_BSP_INT( VECT( TRAP, 3 ) );
    R_BSP_INT( VECT( TRAP, 4 ) );
#endif

#if 0 /* later */
    R_BSP_SET_IPL( BSP_CFG_FIT_IPL_MAX - 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );
#if defined(__BANK)
    R_BSP_INT( VECT( TRAP, 3 ) );
    R_BSP_INT( VECT( TRAP, 4 ) );
#endif

    R_BSP_SET_IPL( BSP_CFG_FIT_IPL_MAX );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );
#if defined(__BANK)
    R_BSP_INT( VECT( TRAP, 3 ) );
    R_BSP_INT( VECT( TRAP, 4 ) );
#endif

    R_BSP_SET_IPL( BSP_CFG_FIT_IPL_MAX + 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );
#if defined(__BANK)
    R_BSP_INT( VECT( TRAP, 3 ) );
    R_BSP_INT( VECT( TRAP, 4 ) );
#endif
#endif

    R_BSP_NOP();

#if defined(__RXV3)
    fp_Check_Using_DSQRT_FSQRT = &Check_Using_DSQRT_FSQRT;
    fp_Check_Not_Using_DSQRT_FSQRT = &Check_Not_Using_DSQRT_FSQRT;
#endif

    for(;;);
}

#if defined(__CCRX__)
#pragma inline_asm _acc_
static void _acc_(void){/* Nothing is enough for debugging with the `-save_acc` compiler option. */}
#else
#define _acc_() do{}while(0)/* This is enough as of today. */
#if 0
static void _acc_(void){/* T.B.D. */}
#endif
#endif

uint32_t debug = 0x5a5a5a5a;

R_BSP_PRAGMA_STATIC_INTERRUPT(trap0_isr, VECT(TRAP, 0))
R_BSP_ATTRIB_STATIC_INTERRUPT void trap0_isr(void)
{
    debug = 0; _acc_();
}

#if defined(__CCRX__) /*----------------------------------------------------*/

#define trap1_isr(...) R_CG_ATTRIB_INTERRUPT_EHI(trap1_isr, __VA_ARGS__)
/**/
#pragma interrupt trap1_isr(vect = VECT(TRAP, 1))
static void trap1_isr(void)
{
    debug = 1; _acc_();
}

#define trap2_isr(...) R_CG_ATTRIB_INTERRUPT_EI(trap2_isr, __VA_ARGS__)
/**/
#pragma interrupt trap2_isr(vect = VECT(TRAP, 2))
static void trap2_isr(void)
{
    debug = 2; _acc_();
}

#if defined(__BANK)

#define trap3_isr(...) R_CG_ATTRIB_INTERRUPT_BANK(trap3_isr, 15, __VA_ARGS__)
/**/
#pragma interrupt trap3_isr(vect = VECT(TRAP, 3))
static void trap3_isr(void)
{
    debug = 3; _acc_();
}

#define trap4_isr(...) R_CG_ATTRIB_INTERRUPT_BANK_EI(trap4_isr, 15, __VA_ARGS__)
/**/
#pragma interrupt trap4_isr(vect = VECT(TRAP, 4))
static void trap4_isr(void)
{
    debug = 4; _acc_();
}

#endif

#elif defined(__GNUC__) /*--------------------------------------------------*/

void trap1_isr(void) __attribute__ ((interrupt(".rvectors", VECT(TRAP, 1))));
/**/
#define trap1_isr(...) R_CG_ATTRIB_INTERRUPT_EHI(trap1_isr, __VA_ARGS__)
/**/
void trap1_isr(void)
{
    debug = 1; _acc_();
}

void trap2_isr(void) __attribute__ ((interrupt(".rvectors", VECT(TRAP, 2))));
/**/
#define trap2_isr(...) R_CG_ATTRIB_INTERRUPT_EI(trap2_isr, __VA_ARGS__)
/**/
void trap2_isr(void)
{
    debug = 2; _acc_();
}

#if defined(__BANK)

void trap3_isr(void) __attribute__ ((interrupt(".rvectors", VECT(TRAP, 3))));
/**/
#define trap3_isr(...) R_CG_ATTRIB_INTERRUPT_BANK(trap3_isr, 15, __VA_ARGS__)
/**/
void trap3_isr(void)
{
    debug = 3; _acc_();
}

void trap4_isr(void) __attribute__ ((interrupt(".rvectors", VECT(TRAP, 4))));
/**/
#define trap4_isr(...) R_CG_ATTRIB_INTERRUPT_BANK_EI(trap4_isr, 15, __VA_ARGS__)
/**/
void trap4_isr(void)
{
    debug = 4; _acc_();
}

#endif

#elif defined(__ICCRX__) /*-------------------------------------------------*/

#define trap1_isr(...) R_CG_ATTRIB_INTERRUPT_EHI(trap1_isr, __VA_ARGS__)
/**/
#pragma vector = VECT(TRAP, 1)
__interrupt static void trap1_isr(void) // Remark[Pe082]: storage class is not first
{
    debug = 1; _acc_();
}

#define trap2_isr(...) R_CG_ATTRIB_INTERRUPT_EI(trap2_isr, __VA_ARGS__)
/**/
#pragma vector = VECT(TRAP, 2)
__interrupt static void trap2_isr(void) // Remark[Pe082]: storage class is not first
{
    debug = 2; _acc_();
}

#if defined(__BANK)

#define trap3_isr(...) R_CG_ATTRIB_INTERRUPT_BANK(trap3_isr, 15, __VA_ARGS__)
/**/
#pragma vector = VECT(TRAP, 3)
__interrupt static void trap3_isr(void) // Remark[Pe082]: storage class is not first
{
    debug = 3; _acc_();
}

#define trap4_isr(...) R_CG_ATTRIB_INTERRUPT_BANK_EI(trap4_isr, 15, __VA_ARGS__)
/**/
#pragma vector = VECT(TRAP, 4)
__interrupt static void trap4_isr(void) // Remark[Pe082]: storage class is not first
{
    debug = 4; _acc_();
}

#endif

#endif /*-------------------------------------------------------------------*/
