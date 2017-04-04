/*
 * dma.c
 *
 *  Created on: Mar 19, 2017
 *      Author: jonathanwingfield
 */
#include "dma.h"

error_t dma_init_ch(dma_channel_t channel, dmamux_peripheral_slot_t slot,  dma_tcd_t* tcd){

	uint32_t upper_addr;

	// enable clock for DMA and DMAMUX modules
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	if(dma_ch_is_open(channel)){ // check if ch is already enabled
		while(DMA0->DMA[(uint32_t)channel].DSR_BCR & DMA_DSR_BCR_BSY_MASK); // wait any xfer on ch to finish
		DMA0->DMA[(uint32_t)channel].DSR_BCR |= DMA_DSR_BCR_DONE_MASK; // clear status bits and ifg
	} // reconfigure channel for new tcd


/*	if(tcd->dsr_bcr == 0 || tcd->dsr_bcr > 0x100000) return DMA_INVALID_BCR;

	upper_addr = tcd->sar & 0xFFF00000;
	if(upper_addr != 0x10000000 ||
	   upper_addr != 0x1FF00000 ||
	   upper_addr != 0x20000000 ||
	   upper_addr != 0x40000000) return DMA_INVALID_SAR;

	upper_addr = tcd->dar & 0xFFF00000;
	if(upper_addr != 0x10000000 ||
	   upper_addr != 0x1FF00000 ||
	   upper_addr != 0x20000000 ||
	   upper_addr != 0x40000000) return DMA_INVALID_DAR;

	if(tcd->dcr & DMA_DSIZE_MASK == DMA_DSIZE_MASK ||
	   tcd->dcr & DMA_SSIZE_MASK == DMA_SSIZE_MASK ) return DMA_INVALID_DATA_SIZES;

	// check allignment of src and dst
*/

	// zero out CHCFG reg in DMAMUX[channel]
	DMAMUX0->CHCFG[(uint32_t)channel] = 0x00;

	// init DMA[channel] with TCD
	DMA0->DMA[(uint32_t)channel].SAR = (uint32_t)tcd->sar;
	DMA0->DMA[(uint32_t)channel].DAR = (uint32_t)tcd->dar;
	DMA0->DMA[(uint32_t)channel].DSR_BCR = tcd->dsr_bcr & 0x00FFFFFF;
	DMA0->DMA[(uint32_t)channel].DCR = tcd->dcr;

	// init DMAMUX[channel]
	DMAMUX0->CHCFG[(uint32_t)channel] = (DMAMUX_CHCFG_ENBL_MASK | slot);
	return SUCCESS;
}

error_t dma_start_transfer(dma_channel_t channel){

	if(!(dma_ch_is_open(channel)))
		return ERROR;

	DMA0->DMA[(uint32_t)channel].DCR |= DMA_DCR_START_MASK;

	if(DMA0->DMA[(uint32_t)channel].DSR_BCR & DMA_DSR_BCR_CE_MASK)
		return ERROR;
	else
		return SUCCESS;
}

__attribute__((always_inline))
error_t dma_ch_is_open(dma_channel_t channel){
	return (DMAMUX0->CHCFG[(uint32_t)channel] & DMAMUX_CHCFG_ENBL_MASK);
}

