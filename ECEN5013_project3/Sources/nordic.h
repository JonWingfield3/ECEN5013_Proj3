/*
 * nordic.h
 *
 *  Created on: Apr 4, 2017
 *      Author: jacob
 */

#ifndef SOURCES_NORDIC_H_
#define SOURCES_NORDIC_H_


#include <stdint.h>
#include "spi.h"
#include "timer.h"

/** nRF24l01+ Memory Mapped Registers **/
#define NRF24_CONFIG                  0x00
#define NRF24_EN_AA                   0x01
#define NRF24_EN_RXADDR               0x02
#define NRF24_SETUP_AW                0x03
#define NRF24_SETUP_RETR              0x04
#define NRF24_RF_CH                   0x05
#define NRF24_RF_SETUP                0x06
#define NRF24_STATUS                  0x07
#define NRF24_OBSERVE_TX              0x08
#define NRF24_RPD                     0x09
#define NRF24_RX_ADDR_P0              0x0A
#define NRF24_RX_ADDR_P1              0x0B
#define NRF24_RX_ADDR_P2              0x0C
#define NRF24_RX_ADDR_P3              0x0D
#define NRF24_RX_ADDR_P4              0x0E
#define NRF24_RX_ADDR_P5              0x0F
#define NRF24_TX_ADDR                 0x10
#define NRF24_RX_PW_P0                0x11
#define NRF24_RX_PW_P1                0x12
#define NRF24_RX_PW_P2                0x13
#define NRF24_RX_PW_P3                0x14
#define NRF24_RX_PW_P4                0x15
#define NRF24_RX_PW_P5                0x16
#define NRF24_FIFO_STATUS             0x17
#define NRF24_DYNPD                   0x1C
#define NRF24_FEATURE                 0x1D

/** nRF24l01+ Register Bits and Bitmasks **/
#define NRF24_CONFIG_MASK_RX_DR       0x40
#define NRF24_CONFIG_MASK_TX_DS       0x20
#define NRF24_CONFIG_MASK_MAX_RT      0x10
#define NRF24_CONFIG_EN_CRC           0x08
#define NRF24_CONFIG_CRCO             0x04
#define NRF24_CONFIG_PWR_UP           0x02
#define NRF24_CONFIG_PRIM_RX          0x01
#define NRF24_CONFIG_PRIM_TX          0x00
#define NRF24_EN_AA_ENAA_P5           0x20
#define NRF24_EN_AA_ENAA_P4           0x10
#define NRF24_EN_AA_ENAA_P3           0x08
#define NRF24_EN_AA_ENAA_P2           0x04
#define NRF24_EN_AA_ENAA_P1           0x02
#define NRF24_EN_AA_ENAA_P0           0x01
#define NRF24_EN_RXADDR_ERX_P5        0x20
#define NRF24_EN_RXADDR_ERX_P4        0x10
#define NRF24_EN_RXADDR_ERX_P3        0x08
#define NRF24_EN_RXADDR_ERX_P2        0x04
#define NRF24_EN_RXADDR_ERX_P1        0x02
#define NRF24_EN_RXADDR_ERX_P0        0x01
#define NRF24_EN_RXADDR_ERX_MASK      0x00
#define NRF24_SETUP_AW_AW__3          0x01
#define NRF24_SETUP_AW_AW__4          0x02
#define NRF24_SETUP_AW_AW__5          0x03
#define NRF24_SETUP_RETR_ARD__250     0x00
#define NRF24_SETUP_RETR_ARD__500     0x10
#define NRF24_SETUP_RETR_ARD__750     0x20
#define NRF24_SETUP_RETR_ARD__1000    0x30
#define NRF24_SETUP_RETR_ARD__1250    0x40
#define NRF24_SETUP_RETR_ARD__1500    0x50
#define NRF24_SETUP_RETR_ARD__1750    0x60
#define NRF24_SETUP_RETR_ARD__2000    0x70
#define NRF24_SETUP_RETR_ARD__2250    0x80
#define NRF24_SETUP_RETR_ARD__2500    0x90
#define NRF24_SETUP_RETR_ARD__2750    0xA0
#define NRF24_SETUP_RETR_ARD__3000    0xB0
#define NRF24_SETUP_RETR_ARD__3250    0xC0
#define NRF24_SETUP_RETR_ARD__3500    0xD0
#define NRF24_SETUP_RETR_ARD__3750    0xE0
#define NRF24_SETUP_RETR_ARD__4000    0xF0
#define NRF24_SETUP_RETR_ARC__0       0x00
#define NRF24_SETUP_RETR_ARC__1       0x01
#define NRF24_SETUP_RETR_ARC__2       0x02
#define NRF24_SETUP_RETR_ARC__3       0x03
#define NRF24_SETUP_RETR_ARC__4       0x04
#define NRF24_SETUP_RETR_ARC__5       0x05
#define NRF24_SETUP_RETR_ARC__6       0x06
#define NRF24_SETUP_RETR_ARC__7       0x07
#define NRF24_SETUP_RETR_ARC__8       0x08
#define NRF24_SETUP_RETR_ARC__9       0x09
#define NRF24_SETUP_RETR_ARC__10      0x0A
#define NRF24_SETUP_RETR_ARC__11      0x0B
#define NRF24_SETUP_RETR_ARC__12      0x0C
#define NRF24_SETUP_RETR_ARC__13      0x0D
#define NRF24_SETUP_RETR_ARC__14      0x0E
#define NRF24_SETUP_RETR_ARC__15      0x0F
#define NRF24_RF_CH_RF_CH_MASK        0x7F
#define NRF24_RF_SETUP_CONT_WAVE      0x80
#define NRF24_RF_SETUP_RF_DR_LOW      0x20
#define NRF24_RF_SETUP_PLL_LOCK       0x10
#define NRF24_RF_SETUP_RF_DR_HIGH     0x08
#define NRF24_RF_SETUP_RF_DR__1MBPS   0x00
#define NRF24_RF_SETUP_RF_DR__2MBPS   0x08
#define NRF24_RF_SETUP_RF_DR__250KBPS 0x20
#define NRF24_RF_SETUP_RF_PWR__18DBM  0x00
#define NRF24_RF_SETUP_RF_PWR__12DBM  0x02
#define NRF24_RF_SETUP_RF_PWR__6DBM   0x04
#define NRF24_RF_SETUP_RF_PWR__0DBM   0x06
#define NRF24_STATUS_RX_DR_IRQ        0x40
#define NRF24_STATUS_TX_DS_IRQ        0x20
#define NRF24_STATUS_MAX_RT_IRQ       0x10
#define NRF24_STATUS_IRQ_MASK         0x70
#define NRF24_STATUS_RX_P_NO          0x02
#define NRF24_STATUS_TX_FULL          0x01
#define NRF24_OBSERVE_TX_PLOS_CNT     0x10
#define NRF24_OBSERVE_TX_ARC_CNT      0x01
#define NRF24_RX_PW_Px_PIPE_NOT_USED  0x00
#define NRF24_RX_PW_Px__1BYTE         0x01
#define NRF24_RX_PW_Px__2BYTE         0x02
#define NRF24_RX_PW_Px__3BYTE         0x03
#define NRF24_RX_PW_Px__4BYTE         0x04
#define NRF24_RX_PW_Px__5BYTE         0x05
#define NRF24_RX_PW_Px__6BYTE         0x06
#define NRF24_RX_PW_Px__7BYTE         0x07
#define NRF24_RX_PW_Px__8BYTE         0x08
#define NRF24_RX_PW_Px__9BYTE         0x09
#define NRF24_RX_PW_Px__10BYTE        0x0A
#define NRF24_RX_PW_Px__11BYTE        0x0B
#define NRF24_RX_PW_Px__12BYTE        0x0C
#define NRF24_RX_PW_Px__13BYTE        0x0D
#define NRF24_RX_PW_Px__14BYTE        0x0E
#define NRF24_RX_PW_Px__15BYTE        0x0F
#define NRF24_RX_PW_Px__16BYTE        0x10
#define NRF24_RX_PW_Px__17BYTE        0x11
#define NRF24_RX_PW_Px__18BYTE        0x12
#define NRF24_RX_PW_Px__19BYTE        0x13
#define NRF24_RX_PW_Px__20BYTE        0x14
#define NRF24_RX_PW_Px__21BYTE        0x15
#define NRF24_RX_PW_Px__22BYTE        0x16
#define NRF24_RX_PW_Px__23BYTE        0x17
#define NRF24_RX_PW_Px__24BYTE        0x18
#define NRF24_RX_PW_Px__25BYTE        0x19
#define NRF24_RX_PW_Px__26BYTE        0x1A
#define NRF24_RX_PW_Px__27BYTE        0x1B
#define NRF24_RX_PW_Px__28BYTE        0x1C
#define NRF24_RX_PW_Px__29BYTE        0x1D
#define NRF24_RX_PW_Px__30BYTE        0x1E
#define NRF24_RX_PW_Px__31BYTE        0x1F
#define NRF24_RX_PW_Px__32BYTE        0x20
#define NRF24_FIFO_STATUS_TX_REUSE    0x40
#define NRF24_FIFO_STATUS_FIFO_FULL   0x20
#define NRF24_FIFO_STATUS_TX_EMPTY    0x10
#define NRF24_FIFO_STATUS_RX_FULL     0x02
#define NRF24_FIFO_STATUS_RX_EMPTY    0x01
#define NRF24_DYNPD_DPL_P5            0x40
#define NRF24_DYNPD_DPL_P4            0x20
#define NRF24_DYNPD_DPL_P3            0x10
#define NRF24_DYNPD_DPL_P2            0x04
#define NRF24_DYNPD_DPL_P1            0x02
#define NRF24_DYNPD_DPL_P0            0x01
#define NRF24_FEATURE_EN_DPL          0x04
#define NRF24_FEATURE_EN_ACK_PAY      0x02
#define NRF24_FEATURE_EN_DYN_ACK      0x01

/** nRF24l01+ SPI Instruction Set **/
#define NRF24_R_REGISTER              0x00
#define NRF24_W_REGISTER              0x20
#define NRF24_REGISTER_MASK           0x1F
#define NRF24_R_RX_PAYLOAD            0x61
#define NRF24_W_TX_PAYLOAD            0xA0
#define NRF24_FLUSH_TX                0xE1
#define NRF24_FLUSH_RX                0xE2
#define NRF24_REUSE_TX_PL             0xE3
#define NRF24_R_RX_PL_WID             0x60
#define NRF24_W_ACK_PAYLOAD           0xA8
#define NRF24_W_TX_PAYLOAD_NOACK      0xB0
#define NRF24_NOP                     0xFF

#define DEFAULT_ADDRESS_WIDTH         5
#define PIPE0                         0x00

/** Useful actions **/  /** REDEFINE THESE **/
#define __CE_LOW__				     MSP432_CE_PORT_OUT  &= ~MSP432_CE_PIN;
#define __CE_HIGH__				     MSP432_CE_PORT_OUT  |=  MSP432_CE_PIN;

SPI_Type SPI = {.C1 = (SPI_C1_SPE_MASK|SPI_C1_MSTR_MASK),
	.C2 = 0x00,
	.BR = 0x1, // divide bus clock freq by 4, default bus clock = 20.97152 Mhz/*
	.S  = 0x00,
	.D  = 0x00,
	.M  = 0x00};

spi_channel_t nrf_channel;

void nrf_init(spi_channel_t t);

uint8_t nrf_read_register(uint8_t reg);

void nrf_write_register(uint8_t reg, uint8_t value);

uint8_t nrf_read_status();

void nrf_write_config(uint8_t config);

uint8_t nrf_read_config();

uint8_t nrf_read_rf_setup();

void nrf_write_rf_setup(uint8_t config);

uint8_t nrf_read_rf_ch();

void nrf_write_rf_ch(uint8_t channel);

void nrf_read_TX_ADDR(uint8_t * data);

void nrf_write_TX_ADDR(uint8_t * tx_addr);

uint8_t nrf_read_fifo_status();

void nrf_flush_tx_fifo();

void nrf_flush_rx_fifo();

#endif /* SOURCES_NORDIC_H_ */
