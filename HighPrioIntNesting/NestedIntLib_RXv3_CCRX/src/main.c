#include "r_smc_entry.h"
#include "NestedIntLib.h"

void main(void);

#define VECT_TRAP_1 1
#define VECT_TRAP_9 9

void main(void)
{
    NESTEDINTLIB_INT_HOOK_init();

    int_exception( VECT( TRAP, 9 ) );

    set_ipl( MY_BSP_CFG_UNNESTED_IPL_MAX - 1 );
    int_exception( VECT( TRAP, 1 ) );

    set_ipl( MY_BSP_CFG_UNNESTED_IPL_MAX );
    int_exception( VECT( TRAP, 1 ) );

    set_ipl( MY_BSP_CFG_UNNESTED_IPL_MAX + 1 );
    int_exception( VECT( TRAP, 1 ) );

    for(;;);
}

uint32_t debug = 0x5a5a5a5a;

#if defined(__CCRX__) /*----------------------------------------------------*/

#pragma inline_asm _acc_
static void _acc_(void){/* nothing is enough for `#pragma interrupt function_name(acc)` */}

#pragma interrupt trap1_isr(vect = VECT(TRAP, 1), acc/* for debug purpose */)
static void trap1_isr(void)
{
    debug = 1; _acc_();
}

#pragma interrupt trap9_isr(vect = VECT(TRAP, 9), acc/* for debug purpose */)
static void trap9_isr(void)
{
    debug = 9; _acc_();
}

#elif defined(__GNUC__) /*--------------------------------------------------*/

static void trap1_isr(void) __attribute__ ((interrupt(R_BSP_SECNAME_INTVECTTBL, VECT(TRAP, 1)), used));
static void trap1_isr(void)
{
    debug = 1;
}

static void trap9_isr(void) __attribute__ ((interrupt(R_BSP_SECNAME_INTVECTTBL, VECT(TRAP, 9)), used));
static void trap9_isr(void)
{
    debug = 9;
}

#elif defined(__ICCRX__) /*-------------------------------------------------*/

#pragma vector = VECT(TRAP, 1)
static __interrupt void trap1_isr(void)
{
    debug = 1;
}

#pragma vector = VECT(TRAP, 9)
static __interrupt void trap9_isr(void)
{
    debug = 9;
}

#endif /*-------------------------------------------------------------------*/
