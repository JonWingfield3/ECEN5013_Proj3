/*
 * spi.c
 *
 *  Created on: Mar 24, 2017
 *      Author: jonathanwingfield
 */
#include "spi.h"

	/*SPI_Type SPI = {.C1 = (SPI_C1_SPE_MASK|SPI_C1_MSTR_MASK),
					.C2 = 0x00,
					.BR = 0x1, // divide bus clock freq by 4, default bus clock = 20.97152 Mhz/*
					.S  = 0x00,
					.D  = 0x00,
					.M  = 0x00};

	spi_init(SPI_CH0, &SPI);*/

error_t spi_init(spi_channel_t channel, SPI_Type* SPI){

	// init spi in sim
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA_PCR16 |= 0x200;

	SPI_Type* spi_ch_base_ptr;
	spi_ch_base_ptr = (channel == SPI_CH0) ? SPI0 : SPI1;

	SPI_C1_REG(spi_ch_base_ptr) = SPI->C1;
	SPI_C2_REG(spi_ch_base_ptr) = SPI->C2;
	SPI_BR_REG(spi_ch_base_ptr) = SPI->BR;
	SPI_M_REG(spi_ch_base_ptr)  = SPI->M;
}

error_t spi_transfer_byte(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data){

	SPI_Type* spi_ch_base_ptr;
	spi_ch_base_ptr = (channel == SPI_CH0) ? SPI0 : SPI1;

	CS_LOW();
	while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPTEF_MASK));
	SPI_D_REG(spi_ch_base_ptr) = *tx_data;
	CS_HIGH();
	while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPRF_MASK));
	*rx_data = SPI_D_REG(spi_ch_base_ptr);

}

error_t spi_transfer_byte_n(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data, uint32_t n){

	SPI_Type* spi_ch_base_ptr;
	spi_ch_base_ptr = (channel == SPI_CH0) ? SPI0 : SPI1;

	uint32_t i;
	for(i = 0; i < n; ++i){
		CS_LOW();
		while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPTEF_MASK));
		SPI_D_REG(spi_ch_base_ptr) = *(tx_data + i);
		CS_HIGH();
		while(!(SPI_S_REG(spi_ch_base_ptr) & SPI_S_SPRF_MASK));
		*(rx_data + i) = SPI_D_REG(spi_ch_base_ptr);
	}

}


error_t spi_close(spi_channel_t channel){

}
