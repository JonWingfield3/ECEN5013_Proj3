/*
 * nordic.c
 *
 *  Created on: Apr 4, 2017
 *      Author: jacob
 */
#include "nordic.h"

void nrf_init(spi_channel_t c) {
	nrf_channel = c;
	spi_init(nrf_channel, &SPI); // Initialize SPI on channel 0
	stall(100); // wait 100ms
}

uint8_t nrf_read_register(uint8_t reg) {
	uint8_t data;
	uint8_t nop = NRF24_NOP;
	reg = NRF24_W_REGISTER|(reg & NRF24_REGISTER_MASK); // Modify register to pass into spi
	CS_LOW();
	spi_transfer_byte(nrf_channel, &reg, &data); // Send register address
	spi_transfer_byte(nrf_channel, &nop, &data); // Send nop to pull register value
	CS_HIGH();
	return data;
}

void nrf_write_register(uint8_t reg, uint8_t value) {
	uint8_t status;
	reg = NRF24_W_REGISTER|(reg & NRF24_REGISTER_MASK); // Modify register to pass into spi
	CS_LOW();
	spi_transfer_byte(nrf_channel, &reg, &status); // Send register address
	spi_transfer_byte(nrf_channel, &value, &status); // Send value to register
	CS_HIGH();
}

uint8_t nrf_read_status() {
	return nrf_read_register(NRF24_STATUS); // Read status register
}

void nrf_write_config(uint8_t config) {
	nrf_write_register(NRF24_CONFIG, config); // Write config data to config register
}

uint8_t nrf_read_config() {
	return nrf_read_register(NRF24_CONFIG); // Read config register
}

uint8_t nrf_read_rf_setup() {
	return nrf_read_register(NRF24_RF_SETUP); // Read RF setup register
}

void nrf_write_rf_setup(uint8_t config) {
	nrf_write_register(NRF24_RF_SETUP, config); // Write config data to RF setup register
}

uint8_t nrf_read_rf_ch() {
	return nrf_read_register(NRF24_RF_CH); // Read RF channel register
}

void nrf_write_rf_ch(uint8_t channel) {
	nrf_write_register(NRF24_RF_CH, channel); // Write channel to RF channel register
}

void nrf_read_TX_ADDR(uint8_t * data) { // THIS NEEDS TO CHANGED
	uint8_t nop = NRF24_NOP;
	uint8_t reg = NRF24_W_REGISTER|(NRF24_TX_ADDR & NRF24_REGISTER_MASK); // Modify register to pass into spi
	CS_LOW();
	spi_transfer_byte(nrf_channel, &reg, data); // Send register address
	spi_transfer_byte(nrf_channel, &nop, (data)); // Send nop to pull register value
	spi_transfer_byte(nrf_channel, &nop, (data)); // Send nop to pull register value
	spi_transfer_byte(nrf_channel, &nop, (data)); // Send nop to pull register value
	spi_transfer_byte(nrf_channel, &nop, (data)); // Send nop to pull register value
	CS_HIGH();
}

void nrf_write_TX_ADDR(uint8_t * tx_addr) { // THIS NEEDS TO BE CHANGED
	nrf_write_register(NRF24_TX_ADDR, *(tx_addr + 0));
	nrf_write_register(NRF24_TX_ADDR, *(tx_addr + 1));
	nrf_write_register(NRF24_TX_ADDR, *(tx_addr + 2));
	nrf_write_register(NRF24_TX_ADDR, *(tx_addr + 3));
}

uint8_t nrf_read_fifo_status() {
	return nrf_read_register(NRF24_FIFO_STATUS); // Read FIFO status from register
}

void nrf_flush_tx_fifo() {
	nrf_write_register(NRF24_FLUSH_TX, NRF24_NOP); // Send flush command to TX fifo
}

void nrf_flush_rx_fifo() {
	nrf_write_register(NRF24_FLUSH_RX, NRF24_NOP); // Send flush command to RX fifo
}


