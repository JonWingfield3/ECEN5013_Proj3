/*
 * rtc.h
 *
 *  Created on: Apr 8, 2017
 *      Author: jonathanwingfield
 */

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include "MKL25Z4.h"
#include "proj_defines.h"
#include "error_codes.h"

#define __RTC_INIT_TIME__ __RTC_TIME__

error_t rtc_init(void);

error_t rtc_get_time(uint32_t* rtc_time);

#endif /* SOURCES_RTC_H_ */
