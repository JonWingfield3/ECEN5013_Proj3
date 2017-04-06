/*
 * timer.c
 *
 *  Created on: Apr 1, 2017
 *      Author: jonathanwingfield
 */
#include "timer.h"

static time_t sys_time = 0; // can count without ovflw for ~ 27.8 thousand yrs
// holds time in 0.75 second granularity
// sys_time + SYSTICK->CVR gives system time with 47.6 ns resolution

void systick_init(void){
	sys_time = 0;
	SYSTICK->SYST_CVR = 0x0;
	//clear systick timer
	SYSTICK->SYST_CSR = (SYST_CSR_CLKSOURCE|SYST_CSR_TICKINT|SYST_CSR_ENABLE);
	// sets to freq of core clock and enables interrupts and timer
	SYSTICK->SYST_RVR = SYST_RVR_RELOAD_MAX;
	// set reload to be maximum value
}

time_t systick_get_ticks(void){
	return sys_time + (SYSTICK->SYST_RVR - SYSTICK->SYST_CVR);
}

uint32_t systick_get_time_ms(void){
	return TICKS_TO_mSEC(systick_get_ticks());
}

uint32_t systick_get_time_us(void){
	return TICKS_TO_uSEC(systick_get_ticks());
}

time_t systick_get_ticks_since(time_t previous_time){
	return systick_get_ticks() - previous_time;
}

uint32_t systick_get_time_since_ms(time_t previous_time){
	return TICKS_TO_mSEC(systick_get_ticks()) - previous_time;
}

uint32_t systick_get_time_since_us(time_t previous_time){
	return TICKS_TO_uSEC(systick_get_ticks()) - previous_time;
}

extern void SysTick_Handler(void){ // interrupts every 0.750 seconds
	sys_time += (SYST_RVR_RELOAD_MAX + 1);
	// update system time with number of ticks to have occurred
}

void stall(uint32_t t) {
	time_t start = systick_get_ticks(); // Get base ticks
	while(systick_get_time_since_ms(start) <= t); // Wait until t milliseconds have passed
}

