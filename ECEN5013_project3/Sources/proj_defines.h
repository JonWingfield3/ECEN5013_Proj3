/*
 * proj_defines.h
 *
 *  Created on: Apr 1, 2017
 *      Author: jonathanwingfield
 */

#ifndef SOURCES_PROJ_DEFINES_H_
#define SOURCES_PROJ_DEFINES_H_

#define FRDM
#ifdef FRDM
/**************************************/
/*  	 Time-Profiling Functions	  */
/**************************************/

#define start_time(t)                   t = systick_get_ticks()
#define stop_time(t)                    t = systick_get_ticks_since(t) - PROFILER_OVERHEAD_CYCLES
#define PROFILER_OVERHEAD_CYCLES        56

#define __start_critical_section(x)     do{ \
											x = __get_PRIMASK(); \
											__set_PRIMASK(1);    \
										}while(0)

#define __end_critical_section(x)		__set_PRIMASK(x)

#define MAX_BINLOG_PAYLOAD_SIZE 16

#endif /* FRDM */


#endif /* SOURCES_PROJ_DEFINES_H_ */
