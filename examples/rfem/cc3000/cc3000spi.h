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
 * @brief CC3000 Host Driver Interface for BSP430
 *
 * This file supports a Host Driver SPI interface for the <a
 * href="http://processors.wiki.ti.com/index.php/CC3000_Wi-Fi_for_MCU">Texas
 * Instruments SimpleLink(TM) CC3000 Wi-Fi SOC</a>.
 *
 * This file provides only the host driver interface.  The host driver
 * itself is a separate library provided by Texas Instruments.  A git
 * repository that repackages that driver in a format suitable for
 * linking with user applications is available at
 * http://github.com/pabigot/cc3000.
 *
 * @homepage http://github.com/pabigot/bsp430
 * @copyright Copyright 2012, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_UTILITY_CC3000SPI_H
#define BSP430_UTILITY_CC3000SPI_H

#include <bsp430/utility/rfem.h>
#include <cc3000/cc3000_common.h>

/** Size of the cc3000spi receive buffer, in octets.
 *
 * The value is an integer between #CC3000_MINIMAL_RX_SIZE=119 and
 * #CC3000_MAXIMAL_RX_SIZE=1520, unless #CC3000_TINY_DRIVER is defined
 * in which case #CC3000_MAXIMAL_RX_SIZE is 44.
 *
 * <cc3000/cc3000_common.h> unconditionally defines a
 * CC3000_RX_BUFFER_SIZE constant, but it is not referenced by the
 * driver and is not relevant to this implementation.
 *
 */
#ifndef BSP430_CC3000SPI_RX_BUFFER_SIZE
#define BSP430_CC3000SPI_RX_BUFFER_SIZE 400
#endif /* BSP430_CC3000SPI_RX_BUFFER_SIZE */

/** Size of the cc3000spi transmit buffer, in octets.
 *
 * The value is an integer between #CC3000_MINIMAL_TX_SIZE=119 and
 * #CC3000_MAXIMAL_TX_SIZE=1520, unless #CC3000_TINY_DRIVER is defined
 * in which case #CC3000_MAXIMAL_TX_SIZE is 59.
 *
 * <cc3000/cc3000_common.h> unconditionally defines a
 * CC3000_TX_BUFFER_SIZE constant, but it is not referenced by the
 * driver and is not relevant to this implementation.
 *
 */
#ifndef BSP430_CC3000SPI_TX_BUFFER_SIZE
#define BSP430_CC3000SPI_TX_BUFFER_SIZE 400
#endif /* BSP430_CC3000SPI_TX_BUFFER_SIZE */

/** BSP430 wrapper around CC3000 wlan_init().
 *
 * This interface provides access to user-level callbacks, and adds
 * the driver-level callbacks internally.
 *
 * @note While this function may be called with interrupts disabled,
 * it does nothing but store some configuration information.  All
 * other CC3000 operations including wlan_start() should be called
 * with interrupts enabled.
 *
 * @param wlan_cb see wlan_init() documentation.
 *
 * @param firmware_patch_fn see wlan_init() documentation.  Passing @c
 * NULL is generally appropriate.
 *
 * @param driver_patch_fn see wlan_init() documentation.  Passing @c
 * NULL is generally appropriate.
 *
 * @param boot_loader_patch_fn see wlan_init() documentation.  Passing
 * @c NULL is generally appropriate.
 *
 * @return 0 if all goes well; -1 if one of the underlying BSP430
 * resources could not be obtained.
 */
int iBSP430cc3000spiInitialize (tWlanCB wlan_cb,
                                tFWPatches firmware_patch_fn,
                                tDriverPatches driver_patch_fn,
                                tBootLoaderPatches boot_loader_patch_fn);

#endif /* BSP430_UTILITY_CC3000SPI_H */
