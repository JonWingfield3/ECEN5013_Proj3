/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "dma.h"
#include "spi.h"
#include "timer.h"
#include "proj_defines.h"
#include  "memory.h"
#include "rtc.h"
#include <string.h>

#define TSIZE 000//0x500

uint32_t t[3];


int main(void)
{
	rtc_init();
	systick_init();
	__enable_irq();

	uint32_t _time, sys_t;
	uint32_t i = 0;
while(1){
	rtc_get_time(&_time);
	delay_ms(10000);
}


	SPI_Type SPI = {.C1 = (SPI_C1_SPE_MASK|SPI_C1_MSTR_MASK),
						.C2 = 0x00,
						.BR = 0x01, // divide bus clock freq by 4, default bus clock = 20.97152 Mhz/*
						.M  = 0x00};
	uint8_t tx_data = 0x44;
	uint8_t rx_data = 0;
	spi_init(SPI_CH0, &SPI);

	while(1){
		spi_transfer_byte(SPI_CH0, &tx_data, &rx_data);
	}

#ifdef PROFILING
	uint8_t array1[TSIZE]; // source
	uint8_t array2[TSIZE]; // dest
	uint32_t i;
	for(i = 0; i < TSIZE; ++i){
		array1[i] = i%256;
		array2[i] = 0;
	}
	__enable_irq();
	NVIC_EnableIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA1_IRQn);
	NVIC_EnableIRQ(DMA2_IRQn);
	NVIC_EnableIRQ(DMA3_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);
	systick_init();

/*** TEST 1: string.h implementation ***/
/*	start_time(t[0]);
	memmove(array1, array2, TSIZE);
	stop_time(t[0]);

	for(i = 0; i < TSIZE; ++i){
		array1[i] = i%256;
		array2[i] = 0;
	}
*/
/*** TEST 2: my implementation without DMA ***/
	start_time(t[1]);
	my_memmove(array1, array2, TSIZE);
	stop_time(t[1]);

	for(i = 0; i < TSIZE; ++i){
		array1[i] = i%256;
		array2[i] = 0;
	}

/*** TEST 3: DMA ***/
	/*start_time(t[2]);
	my_memmove_dma_word(array1, array2, 5000);
*/

	while(1);
#endif
}

extern void DMA0_IRQHandler(void){

	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
}

extern void DMA1_IRQHandler(void){

	DMA0->DMA[1].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
}

extern void DMA2_IRQHandler(void){

	DMA0->DMA[2].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
}

extern void DMA3_IRQHandler(void){

	//stop_time(t[2]);
	DMA0->DMA[3].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
}




