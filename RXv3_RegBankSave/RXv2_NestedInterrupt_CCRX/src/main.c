#include "r_smc_entry.h"

void main(void);

#define VECT_TRAP_0 0
#define VECT_TRAP_1 1
#define VECT_TRAP_2 2

void main(void)
{
    R_BSP_SET_IPL( MY_BSP_CFG_FIT_UNNESTED_IPL_MAX - 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );

    R_BSP_SET_IPL( MY_BSP_CFG_FIT_UNNESTED_IPL_MAX );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );

    R_BSP_SET_IPL( MY_BSP_CFG_FIT_UNNESTED_IPL_MAX + 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );

#if 0 /* later */
    R_BSP_SET_IPL( BSP_CFG_FIT_IPL_MAX - 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );

    R_BSP_SET_IPL( BSP_CFG_FIT_IPL_MAX );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );

    R_BSP_SET_IPL( BSP_CFG_FIT_IPL_MAX + 1 );
    R_BSP_INT( VECT( TRAP, 0 ) );
    R_BSP_INT( VECT( TRAP, 1 ) );
    R_BSP_INT( VECT( TRAP, 2 ) );
#endif

    R_BSP_NOP();

    for(;;);
}

uint32_t debug = 0x5a5a5a5a;

R_BSP_PRAGMA_STATIC_INTERRUPT(trap0_isr, VECT(TRAP, 0))
R_BSP_ATTRIB_STATIC_INTERRUPT void trap0_isr(void)
{
    debug = 0;
}

#if defined(__CCRX__) /*----------------------------------------------------*/

#define trap1_isr(...) R_CG_ATTRIB_INTERRUPT_FIT_IPL_MAX_EI(trap1_isr, __VA_ARGS__)
/**/
#pragma interrupt trap1_isr(vect = VECT(TRAP, 1))
static void trap1_isr(void)
{
    debug = 1;
}

#define trap2_isr(...) R_CG_ATTRIB_INTERRUPT_EI(trap2_isr, __VA_ARGS__)
/**/
#pragma interrupt trap2_isr(vect = VECT(TRAP, 2))
static void trap2_isr(void)
{
    debug = 2;
}

#elif defined(__GNUC__) /*--------------------------------------------------*/

void trap1_isr(void) __attribute__ ((interrupt(".rvectors", VECT(TRAP, 1))));
/**/
#define trap1_isr(...) R_CG_ATTRIB_INTERRUPT_FIT_IPL_MAX_EI(trap1_isr, __VA_ARGS__)
/**/
void trap1_isr(void)
{
    debug = 1;
}

void trap2_isr(void) __attribute__ ((interrupt(".rvectors", VECT(TRAP, 2))));
/**/
#define trap2_isr(...) R_CG_ATTRIB_INTERRUPT_EI(trap2_isr, __VA_ARGS__)
/**/
void trap2_isr(void)
{
    debug = 2;
}

#elif defined(__ICCRX__) /*-------------------------------------------------*/

#define trap1_isr(...) R_CG_ATTRIB_INTERRUPT_FIT_IPL_MAX_EI(trap1_isr, __VA_ARGS__)
/**/
#pragma vector = VECT(TRAP, 1)
__interrupt static void trap1_isr(void) // Remark[Pe082]: storage class is not first
{
    debug = 1;
}

#define trap2_isr(...) R_CG_ATTRIB_INTERRUPT_EI(trap2_isr, __VA_ARGS__)
/**/
#pragma vector = VECT(TRAP, 2)
__interrupt static void trap2_isr(void) // Remark[Pe082]: storage class is not first
{
    debug = 2;
}

#endif /*-------------------------------------------------------------------*/
