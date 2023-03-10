#if !defined(NO_RENESAS_SIMULATOR_DEBUGGING)

#if !defined(RENESAS_SIMULATOR_DEBUGGING)

#define RENESAS_SIMULATOR_DEBUGGING 1

#endif

#endif

#if defined(RENESAS_SIMULATOR_DEBUGGING)

/* Switch Key for Renesas Simulator Debugging
 *
 * non 0x00000001 : Emulator or No debugger
 * 0x00000001     : Renesas RX Simulator
 */
#include "stdint.h"
const uint32_t renesas_simulator_debugging_key = 0xFFFFFFFF;

#endif
