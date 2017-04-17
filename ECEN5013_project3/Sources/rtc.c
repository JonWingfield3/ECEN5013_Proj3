/*
 * rtc.c
 *
 *  Created on: Apr 8, 2017
 *      Author: jonathanwingfield
 */

#include "proj_defines.h"
#include "rtc.h"

error_t rtc_init(void){

	uint32_t prev_ctl = __get_CONTROL();
	__set_CONTROL(0x2);

	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK|SIM_SCGC5_PORTC_MASK;

	MCG_C1 |= MCG_C1_IRCLKEN_MASK;
	MCG_C2 &= ~MCG_C2_IRCS_MASK;
	PORTC_PCR1 |= PORT_PCR_MUX(0x1);
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x2);
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0x4);
	PORTC_PCR3 |= (PORT_PCR_MUX(0x5));

	RTC->CR = RTC_CR_SWR_MASK; // reset all values in RTC
	RTC->CR &= ~RTC_CR_SWR_MASK; // get out of reset state to initialize
	RTC->CR = RTC_CR_OSCE_MASK|RTC_CR_UM_MASK|RTC_CR_SUP_MASK;
	//delay for oscillator start up


	RTC->TSR = 0;//__RTC_INIT_TIME__; // set seconds value based on epoch time
	// possibly set calibration values

	RTC->SR = RTC_SR_TCE_MASK; // enable timer counter in RTC
	RTC->LR = 0x00; // disable all writes to RTC unless POR occurs
	__set_CONTROL(prev_ctl);
}

error_t rtc_get_time(uint32_t* rtc_time){
	*rtc_time = RTC->TSR;
}

extern void RTC_Seconds_IRQHandler(void){

}
