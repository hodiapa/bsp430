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
 * @brief Support for maintaining a system uptime counter.
 *
 * This module provides routines to initialize and query a long-term
 * clock, using a platform-selected timer sourced by an undivided
 * ACLK.
 *
 * vBSP430uptimeStart_ni() must be invoked on hardware initialization
 * after configuring the system clocks.  This is done for you in
 * vBSP430platformInitialize_ni() if #configBSP430_UPTIME is true.
 *
 * See #configBSP430_UPTIME_USE_DEFAULT_RESOURCE if you want to
 * control the timer that will be used.
 *
 * @homepage http://github.com/pabigot/bsp430
 * @copyright Copyright 2012, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_UTILITY_UPTIME_H
#define BSP430_UTILITY_UPTIME_H

#include <bsp430/periph/timer.h>
#include <bsp430/clock.h>

/** @def configBSP430_UPTIME
 *
 * Define to a true value to enable the uptime infrastructure to
 * maintain a continuous system clock.  A timer that will support this
 * must be identified; see #configBSP430_UPTIME_USE_DEFAULT_RESOURCE.
 *
 * @cppflag
 * @affects #BSP430_UPTIME
 * @defaulted
 */
#ifndef configBSP430_UPTIME
#define configBSP430_UPTIME 0
#endif /* configBSP430_UPTIME */

/** @def BSP430_UPTIME
 *
 * Defined to a true value if #BSP430_UPTIME_TIMER_PERIPH_HANDLE has
 * been provided, making the uptime infrastructure available.
 *
 * @dependency #configBSP430_UPTIME
 * @platformdefault */
#if defined(BSP430_DOXYGEN)
#define BSP430_UPTIME include <bsp430/platform.h>
#endif /* BSP430_DOXYGEN */

/** @def configBSP430_UPTIME_USE_DEFAULT_RESOURCE
 *
 * The "best" timer to use for uptime management is probably
 * #BSP430_PERIPH_TA0, but if that time is the only one that can use
 * ACLK as a source another might be preferable, so that
 * #BSP430_TIMER_CCACLK can be used without conflicting with
 * #BSP430_UPTIME.  Where possible, selections of compatible timers
 * are made in the platform-specific headers.  See
 * #BSP430_UPTIME_USE_PLATFORM_RESOURCE.
 *
 * If you want control over the timer used for uptime monitoring, set
 * this to false.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_UPTIME_USE_DEFAULT_RESOURCE
#define configBSP430_UPTIME_USE_DEFAULT_RESOURCE (configBSP430_UPTIME - 0)
#endif /* configBSP430_UPTIME_USE_DEFAULT_RESOURCE */

/** @def BSP430_UPTIME_USE_PLATFORM_RESOURCE
 *
 * If #configBSP430_UPTIME_USE_DEFAULT_RESOURCE is enabled but the
 * platform-specific @c bsp430_config.h selects a different peripheral
 * (e.g., #BSP430_PERIPH_TA1) than the generic @c bsp430_config.h,
 * this flag is defined to a true value to prevent the generic
 * resource from being allocated as well.  You only need to make use
 * of this this if you're providing a platform that doesn't use
 * #BSP430_PERIPH_TA0 for the uptime clock.
 *
 * @cppflag
 * @dependency #configBSP430_UPTIME_USE_DEFAULT_RESOURCE
 * @affects #BSP430_UPTIME_TIMER_PERIPH_HANDLE
 * @platformdefault */
#if defined(BSP430_DOXYGEN)
#define BSP430_UPTIME_USE_PLATFORM_RESOURCE include <bsp430/platform/bsp430_config.h>
#endif /* configBSP430_UPTIME_USE_DEFAULT_RESOURCE */

/** @def BSP430_UPTIME_TIMER_PERIPH_HANDLE
 *
 * Define to the peripheral identifier for a timer that can be used to
 * maintain a continuous system clock sourced from ACLK.
 *
 * @warning If you set this, you must also set
 * #configBSP430_UPTIME_USE_DEFAULT_RESOURCE to be a false value.  You
 * must also ensure the corresponding peripheral HAL interface
 * (e.g. #configBSP430_HAL_TA1) and HAL interrupt that will count
 * overflows (e.g. #configBSP430_HAL_TA1_ISR) are enabled.
 *
 * @defaulted
 * @platformdefault */
#if defined(BSP430_DOXYGEN)
#define BSP430_UPTIME_TIMER_PERIPH_HANDLE include <bsp430/platform.h>
#endif /* BSP430_DOXYGEN */

/** @def configBSP430_UPTIME_USE_DEFAULT_CC0_ISR
 *
 * The dedicated CC0 ISR associated with the uptime timer is an ideal
 * place to support timeslicing for an RTOS.  Normally, when the HAL
 * timer infrastructure used for uptime management is enabled, the CC0
 * interrupt HAL ISR is left unmanaged by BSP430 (see
 * #configBSP430_HAL_TA1_CC0_ISR).
 *
 * Set this flag to 1 if you want BSP430 to provide an implementation for
 * the CC0 interrupt for the HAL timer that underlies the
 * implementation, thereby allowing BSP430 to dispatch CC0 events to
 * callbacks registered in #sBSP430halTIMER.
 *
 * Set this flag to 0 if you intend to implement your own CC0 ISR.
 *
 * @cppflag
 * @nodefault
 * @dependency #configBSP430_UPTIME_USE_DEFAULT_RESOURCE */
#if defined(BSP430_DOXYGEN)
#define configBSP430_UPTIME_USE_DEFAULT_CC0_ISR 0
#endif /* BSP430_DOXYGEN */

/** @def BSP430_UPTIME_SSEL
 *
 * Source selector for uptime clock.  This should be bits suitable for
 * storage into the TASSEL field of a timer control register.  (Note
 * that TASSEL and TBSSEL support the same values).
 *
 * @defaulted */
#ifndef BSP430_UPTIME_SSEL
#define BSP430_UPTIME_SSEL TASSEL_1 /* == TASSEL__ACLK */
#endif /* BSP430_UPTIME_SSEL */

/** @def BSP430_UPTIME_DIVIDING_SHIFT
 *
 * Shift value dividing #BSP430_UPTIME_SSEL for the uptime clock.
 *
 * @defaulted
 */
#ifndef BSP430_UPTIME_DIVIDING_SHIFT
#define BSP430_UPTIME_DIVIDING_SHIFT 0
#endif /* BSP430_UPTIME_DIVIDING_SHIFT */

/** @cond DOXYGEN_EXCLUDE */
extern hBSP430halTIMER xBSP430uptimeTIMER_;
/** @endcond */

/** Get access to the timer controlling the uptime infrastructure.
 *
 * You might need this if you want to hook into its callbacks.
 *
 * Don't hook into the overflow callback, please.
 */
#if defined(BSP430_DOXYGEN) || (BSP430_UPTIME - 0)
static hBSP430halTIMER
BSP430_CORE_INLINE
xBSP430uptimeTimer (void)
{
  return xBSP430uptimeTIMER_;
}
#endif /* DOXYGEN or function available */

/** Return the uptime clock conversion frequency.
 *
 * This is the number of uptime ticks in a standard second, and is
 * used when translating between tick measurements and second-based
 * durations.  The default value is the nominal frequency of the timer
 * underlying the uptime clock, but this may be overridden by
 * ulBSP430uptimeSetConversionFrequency_ni().
 *
 * @return The conversion frequency of the uptime clock, in Hz. */
unsigned long ulBSP430uptimeConversionFrequency_Hz_ni (void);

/** Set the uptime frequency that will be used for tick/time conversion.
 *
 * In cases where the uptime clock derives from #VLOCLK, the nominal
 * frequency used by default may be off by as much as 10% from the
 * actual frequency.  This function can be used when a more accurate
 * estimate of actual frequency is available to decrease the error in
 * converted times.
 *
 * @param frequency_Hz the frequency to be used when converting
 * durations in ticks to durations in seconds or related units.  If a
 * value of zero is provided, the current nominal frequency will be
 * used in subsequent conversions.
 *
 * @return the previous value of the conversion frequency, which may
 * be 0 if no conversions had occured. */
unsigned long ulBSP430uptimeSetConversionFrequency_ni (unsigned long frequency_Hz);

#if defined(BSP430_DOXYGEN) || (BSP430_UPTIME - 0)
/** Return system uptime in clock ticks with disabled interrupts. */
static unsigned long
BSP430_CORE_INLINE
ulBSP430uptime_ni (void)
{
  return ulBSP430timerCounter_ni(xBSP430uptimeTimer(), 0);
}

/** Return the system uptime in clock ticks. */
static unsigned long
BSP430_CORE_INLINE
ulBSP430uptime (void)
{
  return ulBSP430timerCounter(xBSP430uptimeTimer(), 0);
}
#endif /* BSP430_UPTIME */

/** Configure the system uptime clock.
 *
 * The timer associated with the uptime clock is reset to zero and
 * begins counting up. */
void vBSP430uptimeStart_ni (void);

/** Suspend the system uptime clock.
 *
 * Suspension means that the clocks are halted and interrupts from
 * them inhibited.  Counter values are not modified.
 * #vBSP430uptimeResume_ni should be invoked to release the clocks to
 * continue counting.
 *
 * The system clock may be suspended prior to entering certain low
 * power modes.
 */
void vBSP430uptimeSuspend_ni (void);

/** Resume the system uptime clock
 *
 * The clocks are re-enabled to continue counting from their last
 * recorded value.
 */
void vBSP430uptimeResume_ni (void);

/** Convert an uptime count to text HH:MM:SS.mmm format.
 *
 * At least the MM:SS.mmm portion is present, with minutes
 * space-padded on the left.  If the duration exceeds 59:59.999, then
 * space-padded hours will be included as well, and minutes will be
 * zero-padded.
 *
 * @param duration_utt a duration in uptime ticks
 * @return pointer to formatted time.  The pointer is to static storage. */
const char * xBSP430uptimeAsText_ni (unsigned long duration_utt);

#endif /* BSP430_UTILITY_UPTIME_H */
