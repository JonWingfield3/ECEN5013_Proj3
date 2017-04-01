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




int main(void)
{
	systick_init();
	uint8_t array1[256]; // source
	uint8_t array2[256]; // dest
	uint32_t i;

	for(i = 0; i < 256; ++i){
		array1[i] = i;
		array2[i] = 0;
	}
	dma_tcd_t ch0_tcd = {.sar = (uint32_t)array1,
						.dar = (uint32_t)array2,
						.dsr_bcr = 256,
						.dcr = (DMA_EINT|DMA_SINC|DMA_SSIZE__8BIT|DMA_DINC|DMA_DSIZE__8BIT)};

	__enable_irq();
	NVIC_EnableIRQ(DMA0_IRQn);
	dma_init_ch(DMA_CH0, DMAMUX_ALWAYS_ENABLED1, &ch0_tcd);
	dma_start_transfer(DMA_CH0);

	/*SPI_Type SPI = {.C1 = (SPI_C1_SPE_MASK|SPI_C1_MSTR_MASK|SPI_C1_SSOE_MASK),
					.C2 = 0x00,
					.BR = ((0x03 << SPI_BR_SPPR_SHIFT)|0x3), // default bus clock = 24 Mhz/*
					.S  = 0x00,
					.D  = 0x00,
					.M  = 0x00};

	spi_init(SPI_CH0, &SPI);*/


	while(1);

}

extern void DMA0_IRQHandler(void){

	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
}

