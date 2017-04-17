#include "memory.h"

#define PTR_ERROR -1
#define SUCCESS    0
int8_t my_memmove_dma_byte(uint8_t* src, uint8_t* dst, uint32_t length){

	if(!src || !dst) return PTR_ERROR;

	dma_tcd_t tcd = {.sar = (uint32_t)src,
					 .dar = (uint32_t)dst,
				     .dsr_bcr = length,
				     .dcr = (DMA_EINT|DMA_SINC|DMA_SSIZE__8BIT|DMA_DINC|DMA_DSIZE__8BIT)};

	NVIC_EnableIRQ(DMA3_IRQn);
	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED1, &tcd);
	dma_start_transfer(DMA_CH3);
	return SUCCESS;
}

int8_t my_memmove_dma_halfword(uint16_t* src, uint16_t* dst, uint32_t length){

	if(!src || !dst) return PTR_ERROR;

	dma_tcd_t tcd = {.sar = (uint32_t)src,
				     .dar = (uint32_t)dst,
				     .dsr_bcr = length,
				     .dcr = (DMA_EINT|DMA_SINC|DMA_SSIZE__16BIT|DMA_DINC|DMA_DSIZE__16BIT)};

	NVIC_EnableIRQ(DMA3_IRQn);
	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED1, &tcd);
	dma_start_transfer(DMA_CH3);
	return SUCCESS;
}

int8_t my_memmove_dma_word(uint32_t* src, uint32_t* dst, uint32_t length){

	if(!src || !dst) return PTR_ERROR;

	dma_tcd_t tcd = {.sar = (uint32_t)src,
				     .dar = (uint32_t)dst,
				     .dsr_bcr = length,
				     .dcr = (DMA_EINT|DMA_SINC|DMA_SSIZE__32BIT|DMA_DINC|DMA_DSIZE__32BIT)};

	NVIC_EnableIRQ(DMA3_IRQn);
	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED1, &tcd);
	dma_start_transfer(DMA_CH3);
	return SUCCESS;
}

int8_t my_memset_dma(uint8_t* dst, uint32_t length){

	if(!dst) return PTR_ERROR;

	uint8_t zero_ptr = 0;
	uint8_t i;

	dma_tcd_t tcd;

	tcd.sar = (uint32_t)&zero_ptr;
	tcd.dar = (uint32_t)dst;
	if(IS_WORD_ALLIGNED(dst)){ // check if dst address is word-alligned

		tcd.dcr = (DMA_EINT|DMA_SSIZE__32BIT|DMA_DINC|DMA_DSIZE__32BIT);

		if(IS_WORD_ALLIGNED(length))
			tcd.dsr_bcr = length;
		else{
			tcd.dsr_bcr = WORD_ALLIGN(length);
			// this makes sure that length is mod 4 so word transfer can be completed.
			for(i = 0; i < length % 4; ++i)
				*(dst + length - 1 - i) = 0;
			// manually zero-fill the last few parts of length
		}
	}
	else{ // dst is not word alligned
		tcd.dsr_bcr = length;
		tcd.dcr = (DMA_EINT|DMA_SSIZE__8BIT|DMA_DINC|DMA_DSIZE__8BIT);
	}

	NVIC_EnableIRQ(DMA3_IRQn);
	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED1, &tcd);
	dma_start_transfer(DMA_CH3);
	return SUCCESS;
}


int8_t my_memmove(uint8_t* src, uint8_t* dst, uint32_t length){

	uint32_t i;
	uint32_t *src32, *dst32;
	//if( !src || !dst ) return PTR_ERROR;

	if(src > dst)
	{
		if(length % 4 && (uint32_t)src % 4 && (uint32_t)dst % 4){
			for(i = 0; i < length; ++i)
				*(dst + i) = *(src + i);
		}
		else{
			src32 = (uint32_t*)src;
			dst32 = (uint32_t*)dst;
			length >>= 2;
			for(i = 0; i < length; ++i)
				*(dst32 + i) = *(src32 + i);
		}
	}
	else if(src < dst)
	{
		if(length % 4 && (uint32_t)src % 4 && (uint32_t)dst % 4){
			for(i = length - 1; i != 0xFFFFFFFF; --i)
				*(dst + i) =  *(src + i);
		}
		else{
			src32 = (uint32_t*)(src + length - 4);
			dst32 = (uint32_t*)(dst + length - 4);
			length >>= 2;
			for(i = 0; i < length; ++i)
				*(dst32 - i) = *(src32 - i);
		}
	}
	return SUCCESS;

}
int8_t my_memset(uint8_t* src, uint32_t length, uint8_t value)
{
	uint32_t i;
	if( !src ) return PTR_ERROR;

	for(i = 0; i < length; ++i)
		*(src + i) = value;

	return SUCCESS;
}

int8_t my_memzero(uint8_t* src, uint32_t length)
{
	uint32_t i;
	if( !src ) return PTR_ERROR;

	for(i = 0; i < length; ++i)
		*(src + i) = 0;

	return SUCCESS;
}

int8_t my_reverse(uint8_t* src, uint32_t length)
{
	if( !src ) return PTR_ERROR;
  uint32_t i;
	uint8_t temp;

	for(i = 0; i < length >> 1; ++i)
	{
		temp = *(src + i);
		*(src + i)= *(src + length - 1 - i);
		*(src + length -1 - i) = temp;
	}
	return SUCCESS;
}
