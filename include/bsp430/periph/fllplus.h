/* Copyright (c) 2012, Peter A. Bigot
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the software nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** @file
 *
 * @brief Hardware presentation/abstraction for FLL Plus (FLLPLUS).
 *
 * The FLLPLUS and FLLPLUS_SMALL peripherals are present in 4xx-family
 * devices.
 *
 * FLLPLUS_SMALL differs from FLLPLUS in lack of support for XT2 and
 * for SELM/SELS.  The difference is not reflected in this
 * implementation.
 *
 * @section h_periph_fllplus_opt Module Configuration Options
 *
 * None supported.
 *
 * @section h_periph_fllplus_hpl Hardware Presentation Layer
 *
 * As there can be only one instance of FLLPLUS on any MCU, there is no
 * structure supporting a FLLPLUS @HPL.  Manipulate the peripheral through its
 * registers directly.
 *
 * @section h_periph_fllplus_hal Hardware Adaptation Layer
 *
 * As there can be only one instance of FLLPLUS on any MCU, there is no
 * structure supporting a FLLPLUS @HAL.
 *
 * The standard set of capabilities in the bsp430/clocks.h header are
 * supported, with the following details:
 *
 * @li The peripheral requires LFXT1 be available and running at a
 * stable #BSP430_CLOCK_NOMINAL_XT1CLK_HZ.  The value for that crystal
 * rate defaults to 32 KiHz.
 *
 * @li This peripheral does not support dividing SMCLK.  Attempts to
 * configure an alternative divisor will result in a zero divisor.

 * @li The implementation does not support configuring ACLK to
 * anything other than #eBSP430clockSRC_XT1CLK or a fallback from that
 * clock.  (The issue is that not all chips with FLLPLUS support
 * selecting the #eBSP430clockSRC_VLOCLK.)
 *
 * @homepage http://github.com/pabigot/bsp430
 * @copyright Copyright 2012, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_PERIPH_FLLPLUS_H
#define BSP430_PERIPH_FLLPLUS_H

#include <bsp430/clock.h>
#include <bsp430/periph.h>

/** @def BSP430_MODULE_FLLPLUS
 *
 * Defined on inclusion of <bsp430/periph/fllplus.h>.  The value
 * evaluates to true if the target MCU supports the FLL Plus module,
 * and false if it does not.
 *
 * @cppflag
 */
#define BSP430_MODULE_FLLPLUS (defined(__MSP430_HAS_FLLPLUS__)          \
                               || defined(__MSP430_HAS_FLLPLUS_SMALL__))

#if defined(BSP430_DOXYGEN) || (BSP430_MODULE_FLLPLUS - 0)

#undef BSP430_CLOCK_LFXT1_IS_FAULTED_NI
/** Check whether the LFXT1 crystal has a fault condition.
 *
 * This definition overrides the generic definition to test the
 * crystal-specific flags.
 *
 * @warning MSP430F41x2 devices support an FLL_CTL2 register which can
 * select an alternative source for LFXT1.  This macro does not verify
 * whether that register exists and is in fact selecting the external
 * crystal.  In all other MCUs with FLLPLUS, it is believed that the
 * crystal is mandatory and cannot be deselected. */
#define BSP430_CLOCK_LFXT1_IS_FAULTED_NI() (FLL_CTL0 & LFOF)

#undef BSP430_CLOCK_LFXT1_CLEAR_FAULT_NI
/** Clear the fault associated with LFXT1.
 *
 * This definition overrides the generic definition to clear the
 * crystal-specific flags as well as the system flag. */
#define BSP430_CLOCK_LFXT1_CLEAR_FAULT_NI() do {           \
    /* User's guide says FLL_CTL0.LFOF is read-only. */ \
    IFG1 &= ~OFIFG;                                     \
  } while (0)

/** @def BSP430_FLLPLUS_XCAPxPF
 *
 * Oscillator capacitor section to be applied to FLL_CTL0 by
 * #iBSP430clockConfigureLFXT1_ni.
 *
 * @note Most examples use XCAP14PF, but my crude tests suggest that
 * of the capacitances available 0pF produces the closest to 32768 Hz,
 * at least on the EXP430FG4618 board.  This also happens to be the
 * power-up default.
 *
 * @defaulted */
#ifndef BSP430_FLLPLUS_XCAPxPF
#define BSP430_FLLPLUS_XCAPxPF XCAP0PF
#endif /* BSP430_FLLPLUS_XCAPxPF */

/** Unconditional define for peripheral-specific constant */
#define BSP430_CLOCK_NOMINAL_VLOCLK_HZ 12000U

/** Unconditional define for peripheral-specific constant */
#define BSP430_CLOCK_PUC_MCLK_HZ 1048576UL

#endif /* BSP430_MODULE_FLLPLUS */

#endif /* BSP430_PERIPH_FLLPLUS_H */
