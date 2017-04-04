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
#include "error_codes.h"


#define SPI_CS_PIN

#define CS_LOW() /* pull CS_PIN low */
#define CS_HIGH()

typedef enum{
	SPI_CH0,
	SPI_CH1
}spi_channel_t;


/************************************************************************************************
 * error_t spi_init(spi_channel_t channel, SPI_Type* SPI)
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
error_t spi_init(spi_channel_t channel, SPI_Type* SPI);


error_t spi_transfer_byte(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data);


error_t spi_transfer_byte_n(spi_channel_t channel, uint8_t* tx_data, uint8_t* rx_data, uint32_t n);


error_t spi_close(spi_channel_t channel);


#endif /* SOURCES_SPI_H_ */
