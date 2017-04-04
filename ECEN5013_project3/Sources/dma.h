/*
 * dma.h
 *
 *  Created on: Mar 19, 2017
 *      Author: jonathanwingfield
 */

#ifndef DMA_H_
#define DMA_H_

#include "MKL25Z4.h"
#include "error_codes.h"
#include "proj_defines.h"

/* DMAn_SCR bits
 * use these to macros to create a transfer control descriptor (tcd) for DMA channel ctl field*/

/* DMA_EINT used to enable interrupts from DMA after completion of transfer*/
#define DMA_EINT                     ((uint32_t)0x80000000)

/* DMA_ERQ used to allow peripheral requests to initiate DMA transfers*/
#define DMA_ERQ                      ((uint32_t)0x40000000)

/* DMA_CS selects between cycle-stealing(   =1) and continuous mode(   =0) */
#define DMA_CS                       ((uint32_t)0x20000000)

/* DMA_AA sets auto-alignment feature */
#define DMA_AA                       ((uint32_t)0x10000000)

/* DMA_EADRQ enables asynchronous DMA requests when MCU is in STOP mode */
#define DMA_EADRQ                    ((uint32_t)0x00800000)

/* DMA_SINC configures DMA to auto-increment source address after each read */
#define DMA_SINC                     ((uint32_t)0x00400000)

/* DMA_SSIZE bits indicate size of data pointed at by source address */
#define DMA_SSIZE__32BIT             ((uint32_t)0x00000000)
#define DMA_SSIZE__16BIT             ((uint32_t)0x00200000)
#define DMA_SSIZE__8BIT              ((uint32_t)0x00100000)
#define DMA_SSIZE_MASK               ((uint32_t)0x00300000)

/* DMA_DINC configures DMA to auto-increment destination address after each write */
#define DMA_DINC                     ((uint32_t)0x00080000)
#define DMA_DSIZE__32BIT             ((uint32_t)0x00000000)
#define DMA_DSIZE__16BIT             ((uint32_t)0x00040000)
#define DMA_DSIZE__8BIT              ((uint32_t)0x00020000)
#define DMA_DSIZE_MASK               ((uint32_t)0x00060000)

/* DMA_START initiates a DMA transfer */
#define DMA_START                    ((uint32_t)0x00010000)

/* DMA_SMOD sets size of DMA's internal source circular buffer */
#define DMA_SMOD__0                  ((uint32_t)0x00000000)
#define DMA_SMOD_DISABLE_BUF         ((uint32_t)0x00000000)
#define DMA_SMOD__1                  ((uint32_t)0x00001000)
#define DMA_SMOD_16B_BUF             ((uint32_t)0x00001000)
#define DMA_SMOD__2                  ((uint32_t)0x00002000)
#define DMA_SMOD_32B_BUF             ((uint32_t)0x00002000)
#define DMA_SMOD__3                  ((uint32_t)0x00003000)
#define DMA_SMOD_64B_BUF             ((uint32_t)0x00003000)
#define DMA_SMOD__4                  ((uint32_t)0x00004000)
#define DMA_SMOD_128B_BUF            ((uint32_t)0x00004000)
#define DMA_SMOD__5                  ((uint32_t)0x00005000)
#define DMA_SMOD_256B_BUF            ((uint32_t)0x00005000)
#define DMA_SMOD__6                  ((uint32_t)0x00006000)
#define DMA_SMOD_512B_BUF            ((uint32_t)0x00006000)
#define DMA_SMOD__7                  ((uint32_t)0x00007000)
#define DMA_SMOD_1KB_BUF             ((uint32_t)0x00007000)
#define DMA_SMOD__8                  ((uint32_t)0x00008000)
#define DMA_SMOD_2KB_BUF             ((uint32_t)0x00008000)
#define DMA_SMOD__9                  ((uint32_t)0x00009000)
#define DMA_SMOD_4KB_BUF             ((uint32_t)0x00009000)
#define DMA_SMOD__10                 ((uint32_t)0x0000A000)
#define DMA_SMOD_8KB_BUF             ((uint32_t)0x0000A000)
#define DMA_SMOD__11                 ((uint32_t)0x0000B000)
#define DMA_SMOD_16KB_BUF            ((uint32_t)0x0000B000)
#define DMA_SMOD__12                 ((uint32_t)0x0000C000)
#define DMA_SMOD_32KB_BUF            ((uint32_t)0x0000C000)
#define DMA_SMOD__13                 ((uint32_t)0x0000D000)
#define DMA_SMOD_64KB_BUF            ((uint32_t)0x0000D000)
#define DMA_SMOD__14                 ((uint32_t)0x0000E000)
#define DMA_SMOD_128KB_BUF           ((uint32_t)0x0000E000)
#define DMA_SMOD__15                 ((uint32_t)0x0000F000)
#define DMA_SMOD_256KB_BUF           ((uint32_t)0x0000F000)

/* DMA_DMOD sets size of DMA's internal destination circular buffer */
#define DMA_DMOD__0                  ((uint32_t)0x00000000)
#define DMA_DMOD_DISABLE_BUF         ((uint32_t)0x00000000)
#define DMA_DMOD__1                  ((uint32_t)0x00000100)
#define DMA_DMOD_16B_BUF             ((uint32_t)0x00000100)
#define DMA_DMOD__2                  ((uint32_t)0x00000200)
#define DMA_DMOD_32B_BUF             ((uint32_t)0x00000200)
#define DMA_DMOD__3                  ((uint32_t)0x00000300)
#define DMA_DMOD_64B_BUF             ((uint32_t)0x00000300)
#define DMA_DMOD__4                  ((uint32_t)0x00000400)
#define DMA_DMOD_128B_BUF            ((uint32_t)0x00000400)
#define DMA_DMOD__5                  ((uint32_t)0x00000500)
#define DMA_DMOD_256B_BUF            ((uint32_t)0x00000500)
#define DMA_DMOD__6                  ((uint32_t)0x00000600)
#define DMA_DMOD_512B_BUF            ((uint32_t)0x00000600)
#define DMA_DMOD__7                  ((uint32_t)0x00000700)
#define DMA_DMOD_1KB_BUF             ((uint32_t)0x00000700)
#define DMA_DMOD__8                  ((uint32_t)0x00000800)
#define DMA_DMOD_2KB_BUF             ((uint32_t)0x00000800)
#define DMA_DMOD__9                  ((uint32_t)0x00000900)
#define DMA_DMOD_4KB_BUF             ((uint32_t)0x00000900)
#define DMA_DMOD__10                 ((uint32_t)0x00000A00)
#define DMA_DMOD_8KB_BUF             ((uint32_t)0x00000A00)
#define DMA_DMOD__11                 ((uint32_t)0x00000B00)
#define DMA_DMOD_16KB_BUF            ((uint32_t)0x00000B00)
#define DMA_DMOD__12                 ((uint32_t)0x00000C00)
#define DMA_DMOD_32KB_BUF            ((uint32_t)0x00000C00)
#define DMA_DMOD__13                 ((uint32_t)0x00000D00)
#define DMA_DMOD_64KB_BUF            ((uint32_t)0x00000D00)
#define DMA_DMOD__14                 ((uint32_t)0x00000E00)
#define DMA_DMOD_128KB_BUF           ((uint32_t)0x00000E00)
#define DMA_DMOD__15                 ((uint32_t)0x00000F00)
#define DMA_DMOD_256KB_BUF           ((uint32_t)0x00000F00)

/* DMA_D_REQ configures DMA to clear ERQ bit after completing transfer */
#define DMA_D_REQ                    ((uint32_t)0x00000080)

/* DMA_LINKCC configures link channels behavior */
#define DMA_LINKCC__0                ((uint32_t)0x00000000)
#define DMA_LINKCC_NO_LINK           ((uint32_t)0x00000000)
#define DMA_LINKCC__1                ((uint32_t)0x00000010)
#define DMA_LINKCC__2                ((uint32_t)0x00000020)
#define DMA_LINKCC__3                ((uint32_t)0x00000030)

/* DMA_LCH1 maps DMA channel to link channel 1 */
#define DMA_LCH1__0                  ((uint32_t)0x00000000)
#define DMA_LCH1_CH0                 ((uint32_t)0x00000000)
#define DMA_LCH1__1                  ((uint32_t)0x00000004)
#define DMA_LCH1_CH1                 ((uint32_t)0x00000004)
#define DMA_LCH1__2                  ((uint32_t)0x00000008)
#define DMA_LCH1_CH2                 ((uint32_t)0x00000008)
#define DMA_LCH1__3                  ((uint32_t)0x0000000C)
#define DMA_LCH1_CH3                 ((uint32_t)0x0000000C)

/* DMA_LCH2 maps DMA channel to link channel 2 */
#define DMA_LCH2__0                  ((uint32_t)0x00000000)
#define DMA_LCH2_CH0                 ((uint32_t)0x00000000)
#define DMA_LCH2__1                  ((uint32_t)0x00000001)
#define DMA_LCH2_CH1                 ((uint32_t)0x00000001)
#define DMA_LCH2__2                  ((uint32_t)0x00000002)
#define DMA_LCH2_CH2                 ((uint32_t)0x00000002)
#define DMA_LCH2__3                  ((uint32_t)0x00000003)
#define DMA_LCH2_CH3                 ((uint32_t)0x00000003)

typedef enum{
	DMAMUX_UART0_RX         = 2,
	DMAMUX_UART0_TX         = 3,
	DMAMUX_UART1_RX         = 4,
	DMAMUX_UART1_TX         = 5,
	DMAMUX_UART2_RX         = 6,
	DMAMUX_UART2_TX         = 7,
	DMAMUX_SPI0_RX          = 16,
	DMAMUX_SPI0_TX          = 17,
	DMAMUX_SPI1_RX          = 18,
	DMAMUX_SPI1_TX          = 19,
	DMAMUX_I2C0             = 22,
	DMAMUX_I2C1             = 23,
	DMAMUX_TPM0_C0          = 24,
	DMAMUX_TPM0_C1          = 25,
	DMAMUX_TPM0_C2          = 26,
	DMAMUX_TPM0_C3          = 27,
	DMAMUX_TPM0_C4          = 28,
	DMAMUX_TPM0_C5          = 29,
	DMAMUX_TPM1_C0          = 32,
	DMAMUX_TPM1_C1          = 33,
	DMAMUX_TPM2_C0          = 34,
	DMAMUX_TPM2_C1          = 35,
	DMAMUX_ADC0             = 40,
	DMAMUX_CMP0             = 42,
	DMAMUX_DAC0             = 45,
	DMAMUX_PORTA            = 49,
	DMAMUX_PORTD            = 52,
	DMAMUX_TPM0_OVERFLOW    = 54,
	DMAMUX_TPM1_OVERFLOW    = 55,
	DMAMUX_TPM2_OVERFLOW    = 56,
	DMAMUX_TSI              = 57,
	DMAMUX_ALWAYS_ENABLED1  = 58,
	DMAMUX_ALWAYS_ENABLED2  = 59,
	DMAMUX_ALWAYS_ENABLED3  = 60,
	DMAMUX_ALWAYS_ENABLED4  = 61,
	DMAMUX_ALWAYS_ENABLED5  = 62,
	DMAMUX_ALWAYS_ENABLED6  = 63
}dmamux_peripheral_slot_t;

typedef enum{
	DMA_CH0,
	DMA_CH1,
	DMA_CH2,
	DMA_CH3
}dma_channel_t;

typedef struct{
	uint32_t sar;
	uint32_t dar;
	uint32_t dsr_bcr; // number of bytes for xfer
	uint32_t dcr;
}dma_tcd_t;

error_t dma_init_ch(dma_channel_t channel, dmamux_peripheral_slot_t slot, dma_tcd_t*tcd);
// initializes DMA CHn with DMA transfer control descriptor (TCD)
// doesn't start transfer (although ERQ and peripheral request assertion may)

error_t dma_start_transfer(dma_channel_t channel);
// sets START bit in DMA CHn

__attribute__((always_inline))
error_t dma_ch_is_open(dma_channel_t channel);
// returns 0 or 1 if dma channel is open


#endif /* DMA_H_ */
