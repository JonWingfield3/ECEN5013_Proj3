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



#endif


#endif /* SOURCES_PROJ_DEFINES_H_ */
