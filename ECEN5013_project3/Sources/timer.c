/*
 * timer.c
 *
 *  Created on: Apr 1, 2017
 *      Author: jonathanwingfield
 */
#include "timer.h"

static time_t sys_time; // can count without ovflw for ~ 27.8 thousand yrs

void systick_init(void){
	sys_time = 0;
	SYSTICK->SYST_CVR = 0x0;
	//clear systick timer
	SYSTICK->SYST_CSR = (~SYST_CSR_CLKSOURCE|SYST_CSR_TICKINT|SYST_CSR_ENABLE);
	// sets to freq of core clock and enables interrupts and timer
	SYSTICK->SYST_RVR = SYST_RVR_RELOAD_MASK;
	// set reload to be maximum value
}

time_t systick_get_time_now(void){
	return sys_time + SYSTICK->SYST_CVR;
}

time_t systick_get_time_since(time_t previous_time){
	return systick_get_time_now() - previous_time;
}

extern void SysTick_Handler(void){ // interrupts every 0.750 seconds
	sys_time += (SYST_RVR_RELOAD_MASK + 1);
	// update system time with number of ticks to have occurred
}
