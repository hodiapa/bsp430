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

#include <bsp430/periph/timer_.h>

#if defined(__MSP430_HAS_MSP430XV2_CPU__)
#define TA_OVERFLOW 0x0E
#else /* 5xx */
/* Pre-5xx Timer_A only supported 5 CCs and used 0x0A to denote
 * overflow. */
#define TA_OVERFLOW 0x0A
#endif /* 5xx */
/* All families use 0x0E for overflow in Timer_B */
#define TB_OVERFLOW 0x0E

/* !BSP430! periph=timer */
/* !BSP430! instance=TA0,TA1,TA2,TA3,TB0,TB1,TB2 */

/* Declares additional callback pointers that immediately follow the
 * one in the base type.  This allows us to use only the amount of
 * space necessary to support the CC blocks on the target MCU. */
#define DECLARE_AUX_CCS(_n) \
	struct xBSP430callbackISRIndexed * _aux_cc_cbs[_n]

#if configBSP430_PERIPH_TA0 - 0
static struct {
	struct xBSP430timerState state;
	/* State includes one CC record.  Add more as required. */
#if defined(__MSP430_HAS_TA2__) || defined(__MSP430_HAS_T0A2__)
	DECLARE_AUX_CCS(1);			/* 2 total */
#elif defined(__MSP430_HAS_TA3__) || defined(__MSP430_HAS_T0A3__)
	DECLARE_AUX_CCS(2);			/* 3 total */
#else
	DECLARE_AUX_CCS(4);			/* 5 total */
#endif /* TA0 */
} state_TA0_ = {
	.state = { .timer = (xBSP430periphTIMER *)_BSP430_PERIPH_TA0_BASEADDRESS }
};

xBSP430timerHandle const xBSP430timer_TA0 = &state_TA0_.state;
#endif /* configBSP430_PERIPH_TA0 */

#if configBSP430_PERIPH_TA1 - 0
static struct {
	struct xBSP430timerState state;
	/* State includes one CC record.  Add more as required. */
#if defined(__MSP430_HAS_T1A2__)
	DECLARE_AUX_CCS(1);			/* 2 total */
#elif defined(__MSP430_HAS_T1A3__)
	DECLARE_AUX_CCS(2);			/* 3 total */
#else
	DECLARE_AUX_CCS(4);			/* 5 total */
#endif /* TA1 */
} state_TA1_ = {
	.state = { .timer = (xBSP430periphTIMER *)_BSP430_PERIPH_TA1_BASEADDRESS }
};

xBSP430timerHandle const xBSP430timer_TA1 = &state_TA1_.state;
#endif /* configBSP430_PERIPH_TA1 */

#if configBSP430_PERIPH_TA2 - 0
static struct {
	struct xBSP430timerState state;
	/* State includes one CC record.  Add more as required. */
#if defined(__MSP430_HAS_T2A2__)
	DECLARE_AUX_CCS(1);			/* 2 total */
#elif defined(__MSP430_HAS_T2A3__)
	DECLARE_AUX_CCS(2);			/* 3 total */
#else
	DECLARE_AUX_CCS(4);			/* 5 total */
#endif /* TA2 */
} state_TA2_ = {
	.state = { .timer = (xBSP430periphTIMER *)_BSP430_PERIPH_TA2_BASEADDRESS }
};

xBSP430timerHandle const xBSP430timer_TA2 = &state_TA2_.state;
#endif /* configBSP430_PERIPH_TA2 */

#if configBSP430_PERIPH_TA3 - 0
static struct {
	struct xBSP430timerState state;
	/* State includes one CC record.  Add more as required. */
#if defined(__MSP430_HAS_T3A2__)
	DECLARE_AUX_CCS(1);			/* 2 total */
#elif defined(__MSP430_HAS_T3A3__)
	DECLARE_AUX_CCS(2);			/* 3 total */
#else
	DECLARE_AUX_CCS(4);			/* 5 total */
#endif /* TA3 */
} state_TA3_ = {
	.state = { .timer = (xBSP430periphTIMER *)_BSP430_PERIPH_TA3_BASEADDRESS }
};

xBSP430timerHandle const xBSP430timer_TA3 = &state_TA3_.state;
#endif /* configBSP430_PERIPH_TA3 */

#if configBSP430_PERIPH_TB0 - 0
static struct {
	struct xBSP430timerState state;
	/* State includes one CC record.  Add more as required. */
#if defined(__MSP430_HAS_TB3__) || defined(__MSP430_HAS_T0B3__)
	DECLARE_AUX_CCS(2);			/* 3 total */
#else
	DECLARE_AUX_CCS(6);			/* 7 total */
#endif /* TB0 */
} state_TB0_ = {
	.state = { .timer = (xBSP430periphTIMER *)_BSP430_PERIPH_TB0_BASEADDRESS }
};

xBSP430timerHandle const xBSP430timer_TB0 = &state_TB0_.state;
#endif /* configBSP430_PERIPH_TB0 */

#if configBSP430_PERIPH_TB1 - 0
static struct {
	struct xBSP430timerState state;
	/* State includes one CC record.  Add more as required. */
#if defined(__MSP430_HAS_T1B3__)
	DECLARE_AUX_CCS(2);			/* 3 total */
#else
	DECLARE_AUX_CCS(6);			/* 7 total */
#endif /* TB1 */
} state_TB1_ = {
	.state = { .timer = (xBSP430periphTIMER *)_BSP430_PERIPH_TB1_BASEADDRESS }
};

xBSP430timerHandle const xBSP430timer_TB1 = &state_TB1_.state;
#endif /* configBSP430_PERIPH_TB1 */

#if configBSP430_PERIPH_TB2 - 0
static struct {
	struct xBSP430timerState state;
	/* State includes one CC record.  Add more as required. */
#if defined(__MSP430_HAS_T2B3__)
	DECLARE_AUX_CCS(2);			/* 3 total */
#else
	DECLARE_AUX_CCS(6);			/* 7 total */
#endif /* TB2 */
} state_TB2_ = {
	.state = { .timer = (xBSP430periphTIMER *)_BSP430_PERIPH_TB2_BASEADDRESS }
};

xBSP430timerHandle const xBSP430timer_TB2 = &state_TB2_.state;
#endif /* configBSP430_PERIPH_TB2 */

#if (((configBSP430_PERIPH_TA0 - 0) && (configBSP430_HAL_TA0_CC0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TA1 - 0) && (configBSP430_HAL_TA1_CC0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TA2 - 0) && (configBSP430_HAL_TA2_CC0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TA3 - 0) && (configBSP430_HAL_TA3_CC0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TB0 - 0) && (configBSP430_HAL_TB0_CC0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TB1 - 0) && (configBSP430_HAL_TB1_CC0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TB2 - 0) && (configBSP430_HAL_TB2_CC0_ISR - 0)))
/* static */ int
#if __MSP430X__
__attribute__((__c16__))
#endif /* CPUX */
/* __attribute__((__always_inline__)) */
cc0_isr (xBSP430timerHandle timer,
		 int iv)
{
	return iBSP430callbackInvokeISRVoid(&timer->cc0_cb, timer, 0);
}
#endif /* TA0 CC0 ISR */

#define TIMER_ISR_BODY(_timer, _iv, _OVERFLOW) do {						\
		int rv = 0;														\
		if (0 != _iv) {													\
			if (_OVERFLOW == _iv) {										\
				rv = iBSP430callbackInvokeISRVoid(&_timer->overflow_cb, timer, rv); \
			} else {													\
				int cc = (_iv - 4) / 2;									\
				rv = iBSP430callbackInvokeISRVoid(cc + _timer->cc_cb, timer, cc, rv); \
			}															\
		}																\
		return rv;														\
	} while (0)

#if (((configBSP430_PERIPH_TA0 - 0) && (configBSP430_HAL_TA0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TA1 - 0) && (configBSP430_HAL_TA1_ISR - 0)) \
	 || ((configBSP430_PERIPH_TA2 - 0) && (configBSP430_HAL_TA2_ISR - 0)) \
	 || ((configBSP430_PERIPH_TA3 - 0) && (configBSP430_HAL_TA3_ISR - 0)))

/* static */ int
#if __MSP430X__
__attribute__((__c16__))
#endif /* CPUX */
/* __attribute__((__always_inline__)) */
ta_isr (xBSP430timerHandle timer,
		int iv)
{
	TIMER_ISR_BODY(timer, iv, TA_OVERFLOW);
}
#endif /* TAx ISR */

#if (((configBSP430_PERIPH_TB0 - 0) && (configBSP430_HAL_TB0_ISR - 0)) \
	 || ((configBSP430_PERIPH_TB1 - 0) && (configBSP430_HAL_TB1_ISR - 0)) \
	 || ((configBSP430_PERIPH_TB2 - 0) && (configBSP430_HAL_TB2_ISR - 0)))

/* static */ int
#if __MSP430X__
__attribute__((__c16__))
#endif /* CPUX */
/* __attribute__((__always_inline__)) */
tb_isr (xBSP430timerHandle timer,
		int iv)
{
	TIMER_ISR_BODY(timer, iv, TB_OVERFLOW);
}
#endif /* TBx ISR */

/* !BSP430! insert=periph_ba_hpl_defn */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [periph_ba_hpl_defn] */
#if configBSP430_PERIPH_TA0 - 0
volatile xBSP430periphTIMER * const xBSP430periph_TA0 = (volatile xBSP430periphTIMER *)_BSP430_PERIPH_TA0_BASEADDRESS;
#endif /* configBSP430_PERIPH_TA0 */

#if configBSP430_PERIPH_TA1 - 0
volatile xBSP430periphTIMER * const xBSP430periph_TA1 = (volatile xBSP430periphTIMER *)_BSP430_PERIPH_TA1_BASEADDRESS;
#endif /* configBSP430_PERIPH_TA1 */

#if configBSP430_PERIPH_TA2 - 0
volatile xBSP430periphTIMER * const xBSP430periph_TA2 = (volatile xBSP430periphTIMER *)_BSP430_PERIPH_TA2_BASEADDRESS;
#endif /* configBSP430_PERIPH_TA2 */

#if configBSP430_PERIPH_TA3 - 0
volatile xBSP430periphTIMER * const xBSP430periph_TA3 = (volatile xBSP430periphTIMER *)_BSP430_PERIPH_TA3_BASEADDRESS;
#endif /* configBSP430_PERIPH_TA3 */

#if configBSP430_PERIPH_TB0 - 0
volatile xBSP430periphTIMER * const xBSP430periph_TB0 = (volatile xBSP430periphTIMER *)_BSP430_PERIPH_TB0_BASEADDRESS;
#endif /* configBSP430_PERIPH_TB0 */

#if configBSP430_PERIPH_TB1 - 0
volatile xBSP430periphTIMER * const xBSP430periph_TB1 = (volatile xBSP430periphTIMER *)_BSP430_PERIPH_TB1_BASEADDRESS;
#endif /* configBSP430_PERIPH_TB1 */

#if configBSP430_PERIPH_TB2 - 0
volatile xBSP430periphTIMER * const xBSP430periph_TB2 = (volatile xBSP430periphTIMER *)_BSP430_PERIPH_TB2_BASEADDRESS;
#endif /* configBSP430_PERIPH_TB2 */

/* END AUTOMATICALLY GENERATED CODE [periph_ba_hpl_defn] */
/* !BSP430! end=periph_ba_hpl_defn */

volatile xBSP430periphTIMER *
xBSP430periphLookupTIMER (xBSP430periphHandle periph)
{
/* !BSP430! insert=periph_ba_hpl_demux */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [periph_ba_hpl_demux] */
#if configBSP430_PERIPH_TA0 - 0
	if (BSP430_PERIPH_TA0 == periph) {
		return xBSP430periph_TA0;
	}
#endif /* configBSP430_PERIPH_TA0 */

#if configBSP430_PERIPH_TA1 - 0
	if (BSP430_PERIPH_TA1 == periph) {
		return xBSP430periph_TA1;
	}
#endif /* configBSP430_PERIPH_TA1 */

#if configBSP430_PERIPH_TA2 - 0
	if (BSP430_PERIPH_TA2 == periph) {
		return xBSP430periph_TA2;
	}
#endif /* configBSP430_PERIPH_TA2 */

#if configBSP430_PERIPH_TA3 - 0
	if (BSP430_PERIPH_TA3 == periph) {
		return xBSP430periph_TA3;
	}
#endif /* configBSP430_PERIPH_TA3 */

#if configBSP430_PERIPH_TB0 - 0
	if (BSP430_PERIPH_TB0 == periph) {
		return xBSP430periph_TB0;
	}
#endif /* configBSP430_PERIPH_TB0 */

#if configBSP430_PERIPH_TB1 - 0
	if (BSP430_PERIPH_TB1 == periph) {
		return xBSP430periph_TB1;
	}
#endif /* configBSP430_PERIPH_TB1 */

#if configBSP430_PERIPH_TB2 - 0
	if (BSP430_PERIPH_TB2 == periph) {
		return xBSP430periph_TB2;
	}
#endif /* configBSP430_PERIPH_TB2 */

/* END AUTOMATICALLY GENERATED CODE [periph_ba_hpl_demux] */
/* !BSP430! end=periph_ba_hpl_demux */
	return NULL;
}