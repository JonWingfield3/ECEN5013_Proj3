/*
 * spi.h
 *
 *  Created on: Mar 24, 2017
 *      Author: jonathanwingfield
 */

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

#include "MKL25Z4.h"
#include "circbuf.h"

typedef enum{
	ERROR,
	NO_ERROR,
	ETC
}spi_status_t;

typedef enum{
	SPI_CH0,
	SPI_CH1
}spi_channel_t;


/*Thoughts:
 * have SPI optionally configured for polling based, interrupt based, or DMA based
 */

/************************************************************************************************
 * spi_status_t spi_init(spi_channel_t channel, SPI_Type* SPI)
 *
 * Description: initializes SPI comm at channel 0 or 1 as specified by channel param
 * 				The initialization values are copied from SPI param. See macros above for more
 * 				info on how to configure SPI channel
 * Parameters:
 * 	- spi_channel_t channel: specifies SPI_CH0 or SPI_CH1
 * 	- SPI_Type* SPI: pointer to structure containing all SPI register initialization values
 *
 * 	Return Value:
 * 	- SPI_INIT_SUCCESS:
 * 	- SPI_INIT_FAILURE:
 *
 ************************************************************************************************/
spi_status_t spi_init(spi_channel_t channel, SPI_Type* SPI);


spi_status_t spi_transfer_byte(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data);


spi_status_t spi_transfer_byte_n(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data, uint32_t n);


spi_status_t spi_close(spi_channel_t channel);


#endif /* SOURCES_SPI_H_ */
