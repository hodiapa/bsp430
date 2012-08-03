/* Copyright (c) 2012, Peter A. Bigot <bigotp@acm.org>
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
 * @brief Hardware presentation/abstraction for Clock System (CS).
 *
 * This module supports the Clock System (CS) peripheral present in
 * FR5xx-family devices.
 *
 * The peripheral supports only a few factory-trimmed frequencies:
 * 5.33, 6.67, and 8 MHz on low-speed devices.  On high-speed--capable
 * devices the speed may also be set to 16, 20 and 24 MHz.
 *
 * Other refinements in this module:
 * <ul>
 * <li> ulBSP430clockMCLK_Hz_ni() assumes that DCOCLK is the selected
 * source for MCLK, and returns the divided trimmed DCOCLK frequency.
 * </ul>
 *
 * @author Peter A. Bigot <bigotp@acm.org>
 * @homepage http://github.com/pabigot/freertos-mspgcc
 * @date 2012
 * @copyright <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_PERIPH_CS_H
#define BSP430_PERIPH_CS_H

#include <bsp430/clock.h>
#include <bsp430/periph.h>

#if ! (defined(__MSP430_HAS_CS__) || defined(__MSP430_HAS_CS_A__))
#warning Peripheral not supported by configured MCU
#endif /* __MSP430_HAS_CS__ */

#undef BSP430_CLOCK_LFXT1_IS_FAULTED_NI
/** Check whether the LFXT1 crystal has a fault condition.
 *
 * This definition overrides the generic definition to test the
 * crystal-specific flags.  Note that if somebody has turned off the
 * crystal by setting CSCTL4.XT1OFF, the crystal is assumed to be
 * faulted. */
#define BSP430_CLOCK_LFXT1_IS_FAULTED_NI() ((CSCTL4 & XT1OFF) || (CSCTL5 & XT1OFFG))

#undef BSP430_CLOCK_LFXT1_CLEAR_FAULT_NI
/** Clear the fault associated with LFXT1.
 *
 * This definition overrides the generic definition to clear the
 * crystal-specific flags as well as the system flag.
 *
 * @warning Because the CS registers must be unlocked when being
 * modified, this macro will unlock and then re-lock them.  It should
 * not be invoked in a situation where the CS registers are already
 * locked. */
#define BSP430_CLOCK_LFXT1_CLEAR_FAULT_NI() do {	\
    CSCTL0_H = 0xA5;                                    \
    CSCTL5 &= ~XT1OFFG;                                 \
    CSCTL0_H = !0xA5;                                   \
    SFRIFG1 &= ~OFIFG;                                  \
  } while (0)

/** Unconditional define for peripheral-specific constant */
#define BSP430_CLOCK_NOMINAL_VLOCLK_HZ 10000U

/** Unconditional define for peripheral-specific constant */
#define BSP430_CLOCK_PUC_MCLK_HZ 1048576UL

#endif /* BSP430_PERIPH_CS_H */
