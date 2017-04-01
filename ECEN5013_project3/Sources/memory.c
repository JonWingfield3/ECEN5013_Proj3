#include "memory.h"

#define PTR_ERROR -1
#define SUCCESS    0
int8_t my_memmove_dma_byte(uint8_t* src, uint8_t* dst, uint32_t length){

	if(!src || !dst) return PTR_ERROR;

	dma_tcd_t tcd = {.sar = (uint32_t)src,
					 .dar = (uint32_t)dst,
				     .dsr_bcr = length,
				     .dcr = (DMA_EINT|DMA_SINC|DMA_SSIZE__8BIT|DMA_DINC|DMA_DSIZE__8BIT)};

	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED5, &tcd);
	return SUCCESS;
}

int8_t my_memmove_dma_halfword(uint16_t* src, uint16_t* dst, uint32_t length){

	if(!src || !dst) return PTR_ERROR;

	dma_tcd_t tcd = {.sar = (uint32_t)src,
				     .dar = (uint32_t)dst,
				     .dsr_bcr = length,
				     .dcr = (DMA_EINT|DMA_SINC|DMA_SSIZE__16BIT|DMA_DINC|DMA_DSIZE__16BIT)};

	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED5, &tcd);
	return SUCCESS;
}

int8_t my_memmove_dma_word(uint32_t* src, uint32_t* dst, uint32_t length){

	if(!src || !dst) return PTR_ERROR;

	dma_tcd_t tcd = {.sar = (uint32_t)src,
				     .dar = (uint32_t)dst,
				     .dsr_bcr = length,
				     .dcr = (DMA_EINT|DMA_SINC|DMA_SSIZE__32BIT|DMA_DINC|DMA_DSIZE__32BIT)};

	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED5, &tcd);
	return SUCCESS;
}

int8_t my_memset_dma(uint8_t* dst, uint32_t length){

	if(!dst) return PTR_ERROR;

	uint8_t zero_ptr = 0;

	dma_tcd_t tcd = {.sar = (uint32_t)&zero_ptr,
				     .dar = (uint32_t)dst,
				     .dsr_bcr = length,
				     .dcr = (DMA_EINT|DMA_SSIZE__8BIT|DMA_DINC|DMA_DSIZE__8BIT)};

	dma_init_ch(DMA_CH3, DMAMUX_ALWAYS_ENABLED5, &tcd);
	return SUCCESS;
}


int8_t my_memmove(uint8_t* src, uint8_t* dst, uint32_t length)
{

	uint32_t i;
	if( !src || !dst ) return PTR_ERROR;

	if(src > dst)
	{
		for(i = 0; i < length; i++)
			*(dst + i) = *(src + i);
	}
	else if(src < dst)
	{
		for(i = length; i > 0; i--)
			*(dst + i - 1) =  *(src + i - 1);
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
