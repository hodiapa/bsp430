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
 * @brief Hardware presentation/abstraction for Power Management Module (PMM).
 *
 * The Power Management Module is present on 5xx/6xx/FR5xx devices,
 * and has differences in FRAM devices that are not reflected by this
 * interface.
 *
 * @section h_periph_pmm_opt Module Configuration Options
 *
 * None supported.
 *
 * @section h_periph_pmm_hpl Hardware Presentation Layer
 *
 * As there can be only one instance of PMM on any MCU, there is no
 * structure supporting a PMM @HPL.  Manipulate the peripheral through its
 * registers directly.
 *
 * @section h_periph_pmm_hal Hardware Adaptation Layer
 *
 * As there can be only one instance of PMM on any MCU, there is no
 * structure supporting a PMM @HAL.
 *
 * Inline functions defined in this module support forcing processor
 * resets that include a complete reset of all registers and
 * peripherals.
 *
 * @homepage http://github.com/pabigot/bsp430
 * @copyright Copyright 2012, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_PERIPH_PMM_H
#define BSP430_PERIPH_PMM_H

#include <bsp430/periph.h>

/** @def BSP430_MODULE_PMM
 *
 * Defined on inclusion of <bsp430/periph/pmm.h>.  The value evaluates
 * to true if the target MCU supports the Power Management Module, and
 * false if it does not.
 *
 * @cppflag
 */
#define BSP430_MODULE_PMM (defined(__MSP430_HAS_PMM__)          \
                           || defined(__MSP430_HAS_PMM_FR5xx__) \
                           || defined(__MSP430_HAS_PMM_FRAM__))

/** @def BSP430_MODULE_PMM_FRAM
 *
 * Defined on inclusion of <bsp430/periph/pmm.h>.  The value evaluates
 * to true if the target MCU supports the FRAM version of the Power
 * Management Module, and false if it does not.
 *
 * @cppflag
 */
#define BSP430_MODULE_PMM_FRAM (defined(__MSP430_HAS_PMM_FR5xx__)       \
                                || defined(__MSP430_HAS_PMM_FRAM__))

#if defined(BSP430_DOXYGEN) || (BSP430_MODULE_PMM - 0)

#if defined(BSP430_DOXYGEN) || defined(PM5CTL0)

/** Macro to enter LPMx.5 mode
 *
 * This should be invoked when #BSP430_CORE_LPM_LPMXp5 or some other
 * cue indicates that ultra-low-power sleep is desired.
 *
 * @note This macro is unavailable on 5xx/6xx chips for which PM5CTL0
 * is not provided by the MCU headers, possibly due to the presence of
 * erratum PMM8.  In particular, it is not available on the CC430F5137
 * used in the EM430 and SuRF platforms.  User code can test whether
 * the macro is defined in order to determine whether the feature is
 * supported.
 *
 * @warning The implementation assumes that the PMM control registers
 * are locked.  The macro will unlock the registers, set the bit for
 * LPMx.5, then lock the registers again.  If used in a context where
 * the PMM registers are already unlocked, this will probably not be
 * what you want. */
#define BSP430_PMM_ENTER_LPMXp5_NI() do {       \
    PMMCTL0_H = PMMPW_H;                        \
    PMMCTL0 = PMMPW | PMMREGOFF;                \
    PMMCTL0_H = !PMMPW_H;                       \
  } while (0)

#endif /* PM5CTL0 */

/** Cause a brown-out reset */
static void
BSP430_CORE_INLINE
vBSP430pmmInduceBOR (void)
{
  PMMCTL0 = PMMPW | PMMSWBOR;
}

/** Cause a power-on reset */
static void
BSP430_CORE_INLINE
vBSP430pmmInducePOR (void)
{
  PMMCTL0 = PMMPW | PMMSWPOR;
}

#if defined(BSP430_DOXYGEN) || ! (BSP430_MODULE_PMM_FRAM - 0)

/** Safely adjust the PMM core voltage to a desired level.
 *
 * This function gradually increases or decreases the PMM core voltage
 * to the desired level, or as close to it as can be achieved.  The
 * implementation is from <a
 * href="http://www.ti.com/tool/msp430ware">MSP430Ware</a>, and
 * includes a workaround for erratum FLASH37.  If supply voltage does
 * not support the requested voltage, the closest attainable level
 * will be configured and returned.
 *
 * @param target_level The power level to be entered.  This must be a
 * valid level, i.e. #PMMCOREV_0 through #PMMCOREV_3, or an error code
 * is returned.
 *
 * @return -1 if the @p target_level is invalid, otherwise the level
 * at which power is left.  This may be less than @p target_level if
 * the requested level could not be reached due to inadequate supply
 * voltage.
 *
 * @note This function is available only on non-FRAM 5xx PMM
 * implementations.
 */
int iBSP430pmmSetCoreVoltageLevel_ni (unsigned int target_level);

#endif /* PMM not FRAM */

#endif /* BSP430_MODULE_PMM */

#endif /* BSP430_PERIPH_PMM_H */
