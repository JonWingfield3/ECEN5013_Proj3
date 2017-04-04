/*
 * timer.h
 *
 *  Created on: Apr 1, 2017
 *      Author: jonathanwingfield
 */

#ifndef SOURCES_TIMER_H_
#define SOURCES_TIMER_H_

#include "MKL25Z4.h"

typedef uint32_t time_t;

typedef struct{
	__IO uint32_t SYST_CSR;
	__IO uint32_t SYST_RVR;
	__IO uint32_t SYST_CVR;
	__I  uint32_t SYST_CALIB;
}SYST_Type;

#define SYST_CSR_COUNTFLAG       ((uint32_t)(0x00010000))
#define SYST_CSR_CLKSOURCE       ((uint32_t)(0x00000004))
#define SYST_CSR_TICKINT         ((uint32_t)(0x00000002))
#define SYST_CSR_ENABLE          ((uint32_t)(0x00000001))
#define SYST_RVR_RELOAD_MASK     ((uint32_t)(0x00FFFFFF))
#define SYST_RVR_RELOAD_MAX      SYST_RVR_RELOAD_MASK
#define SYST_CVR_CURRENT_MASK    ((uint32_t)(0x00FFFFFF))
#define SYSTICK_BASE     	     ((uint32_t)(0xE000E010))
#define SYSTICK                  ((SYST_Type*) SYSTICK_BASE)
#define TICKS_TO_SEC(TICKS)      ((uint32_t)((TICKS >> 20) / 20))
#define TICKS_TO_mSEC(TICKS)     ((uint32_t)((TICKS >> 20) * 50))
#define TICKS_TO_uSEC(TICKS)     ((uint32_t)((TICKS >> 20) * 5000))

// counts at ~ 20.971 MHz.
// one tick is ~ 49.7 nsec

void systick_init(void);

time_t systick_get_ticks(void);

uint32_t systick_get_time_ms(void);

uint32_t systick_get_time_us(void);

time_t systick_get_ticks_since(time_t previous_time);

uint32_t systick_get_time_since_ms(time_t previous_time);

uint32_t systick_get_time_since_us(time_t previous_time);

#endif /* SOURCES_TIMER_H_ */
