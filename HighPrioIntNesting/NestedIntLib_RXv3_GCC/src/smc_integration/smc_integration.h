#ifndef SMC_INTEGRATION_H
#define SMC_INTEGRATION_H

#include "CC_patch.h"
#include "IDE_patch.h"
#include "CG_patch.h"
#include "FIT_patch.h"

#if defined(__GNUC__)

/* Just for convenience.
 */
#define brk()               R_BSP_BRK()
#define int_exception(x)    R_BSP_INT(x)

#endif /* defined(__GNUC__) */

#if defined(__GNUC__) || defined(__ICCRX__)

/* Just for convenience.
 */
#define setpsw_i()  R_BSP_SETPSW_I()
#define clrpsw_i()  R_BSP_CLRPSW_I()
#define set_ipl(x)  R_BSP_SET_IPL(x)

#endif /* defined(__GNUC__) || defined(__ICCRX__) */

/* Just for convenience. For example, memcmp(), memcpy(), memset(), and so on.
 */
#include <string.h>

/* For convenience to port programs from CC-RX to GNURX or ICCRX.
 */
#define VOLATILE volatile R_BSP_EVENACCESS_SFR

/* For convenience to use e2 studio's Visual Expression View.
 */
#include "IDEDebugHelper/e2_studio_helper.h"

/* For convenience to use e2 studio's Virtual Debug Console or CS+'s Debug Console.
 */
#include "IDEDebugHelper/u_bsp_lowlvl_ext.h"

/* For Renesas RX Simulator Debugging.
 */
#include "RenesasSimDebug/sim_debug_mode_hook.h"

#endif /* SMC_INTEGRATION_H */
