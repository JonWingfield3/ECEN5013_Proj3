/*
 * spi.c
 *
 *  Created on: Mar 24, 2017
 *      Author: jonathanwingfield
 */
#include "spi.h"

//#define SPI_INTERRUPTS
#define DEFAULT_SPI_BUF_SIZE 256
CircBuf SPI_TXBuf, SPI_RXBuf;
spi_status_t spi_init(spi_channel_t channel, SPI_Type* SPI){

	// init spi in sim
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	SPI_Type* spi_ch_base_ptr;
	spi_ch_base_ptr = (channel == SPI_CH0) ? SPI0 : SPI1;

	SPI_C1_REG(spi_ch_base_ptr) = SPI->C1;
	SPI_C2_REG(spi_ch_base_ptr) = SPI->C2;
	SPI_BR_REG(spi_ch_base_ptr) = SPI->BR;
	SPI_M_REG(spi_ch_base_ptr)  = SPI->M;

#ifdef SPI_INTERRUPTS

	BufferInit(&SPI_TXBuf, DEFAULT_SPI_BUF_SIZE);
	BufferInit(&SPI_RXBuf, DEFAULT_SPI_BUF_SIZE);
#endif
#ifdef SPI_DMA


#endif

}
#define SPI_DMA
#define SPI_POLLING
spi_status_t spi_transfer_byte(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data){

	SPI_Type* spi_ch_base_ptr;
	spi_ch_base_ptr = (channel == SPI_CH0) ? SPI0 : SPI1;

#ifdef SPI_POLLING
	while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPTEF_MASK));
	SPI_D_REG(spi_ch_base_ptr) = *tx_data;
	while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPRF_MASK));
	*rx_data = SPI_D_REG(spi_ch_base_ptr);
#endif

#ifdef SPI_INTERRUPTS
	if(BufferFull(&SPI_TXBuf) == BUFFER_NOT_FULL){
		BufferAddItem(&SPI_TXBuf, *tx_data);
	}
	// enable spi_tx interrupts

//	if(BufferEmpty(&SPI_RXBuf) == BUFFER_NOT_EMPTY){
//		*rx_data = BufferRemoveItem(&SPI_RXBuf);
//	}

#endif


}

spi_status_t spi_transfer_byte_n(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data, uint32_t n){

	SPI_Type* spi_ch_base_ptr;
	spi_ch_base_ptr = (channel == SPI_CH0) ? SPI0 : SPI1;

	uint32_t i;
	for(i = 0; i < n; ++i){
		while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPTEF_MASK));
		SPI_D_REG(spi_ch_base_ptr) = *(tx_data + i);
		while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPRF_MASK));
		*(rx_data + i) = SPI_D_REG(spi_ch_base_ptr);
	}

}


spi_status_t spi_close(spi_channel_t channel){

}

void SPI0_IRQHandler(void){

	if(SPI0->S & SPI_S_SPTEF_MASK){ // write into tx buffer



	}
	if(SPI0->S & SPI_S_SPRF_MASK){ // read from rx buffer


	}
	/* neither of the two below interrupts are going to occur
	if(SPI0->S & SPI_S_SPMF_MASK){ // match value detected

	}
	if(SPI0->S & SPI_S_MODF_MASK){ // mode fault detected
		// error handling
	}
*/
}

void SPI1_IRQHandler(void){

	if(SPI1->S & SPI_S_SPTEF_MASK){ // write into tx buffer



	}
	if(SPI1->S & SPI_S_SPRF_MASK){ // read from rx buffer


	}
	/* neither of the two below interrupts are going to occur
	if(SPI1->S & SPI_S_SPMF_MASK){ // match value detected

	}
	if(SPI1->S & SPI_S_MODF_MASK){ // mode fault detected
		// error handling
	}
*/
}
