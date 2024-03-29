/*************************************************
*
* Header file for myApp_MTL.h
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// PRE-PROCESSOR LINES ///
#ifndef MYAPP_MTL_H_
#define MYAPP_MTL_H_

/// INCLUDES ///
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#include "socal/alt_gpio.h"
#include "socal/hps.h"
#include "socal/socal.h"

#include "alt_clock_manager.h"
#include "alt_generalpurpose_io.h"
#include "alt_globaltmr.h"
#include "alt_interrupt.h"
#include "hps_0.h"

#include "../painter/picture.h"
#include "../painter/frame.h"
#include "../painter/geometry.h"


/// CONSTANTS DEFINITION ///

#define assert(e) ((e) ? (void)0 : printf("Error in %s, Line : %d\r\n", __FILE__, __LINE__))

// Comment next line if you have a MTL 1 screen //
// #define IS_MTL2

//#define MTL_TOUCH_I2C_BASE  0xa000
#define MTL_TOUCH_I2C_BASE  TOUCH_BASE



// |=============|==========|==============|==========|
// | Signal Name | HPS GPIO | Register/bit | Function |
// |=============|==========|==============|==========|
// |   HPS_LED   |  GPIO53  |   GPIO1[24]  |    I/O   |
// |=============|==========|==============|==========|
#define HPS_LED_IDX        (ALT_GPIO_1BIT_53)                      // GPIO53
#define HPS_LED_PORT       (alt_gpio_bit_to_pid(HPS_LED_IDX))      // ALT_GPIO_PORTB
#define HPS_LED_PORT_BIT   (alt_gpio_bit_to_port_pin(HPS_LED_IDX)) // 24 (from GPIO1[24])
#define HPS_LED_MASK       (1 << HPS_LED_PORT_BIT)

// |=============|==========|==============|==========|
// | Signal Name | HPS GPIO | Register/bit | Function |
// |=============|==========|==============|==========|
// |  HPS_KEY_N  |  GPIO54  |   GPIO1[25]  |    I/O   |
// |=============|==========|==============|==========|
#define HPS_KEY_N_IDX      (ALT_GPIO_1BIT_54)                        // GPIO54
#define HPS_KEY_N_PORT     (alt_gpio_bit_to_pid(HPS_KEY_N_IDX))      // ALT_GPIO_PORTB
#define HPS_KEY_N_PORT_BIT (alt_gpio_bit_to_port_pin(HPS_KEY_N_IDX)) // 25 (from GPIO1[25])
#define HPS_KEY_N_MASK     (1 << HPS_KEY_N_PORT_BIT)

#define MTC_STATUS     fpga_mtc + (2 * 4)

#define SPI_RXDATA     fpga_spi
#define SPI_TXDATA     fpga_spi + (1 * 4)
#define SPI_STATUS     fpga_spi + (2 * 4)
#define SPI_CONTROL    fpga_spi + (3 * 4)
#define SPI_EOP_VALUE  fpga_spi + (6 * 4)

#define SPI_STATUS_EOP    0x200
#define SPI_STATUS_E      0x100
#define SPI_STATUS_RRDY   0x80
#define SPI_STATUS_TRDY   0x40
#define SPI_STATUS_TMT    0x20
#define SPI_STATUS_TOE    0x10
#define SPI_STATUS_ROE    0x08

#define SPI_CONTROL_IEOP  0x200
#define SPI_CONTROL_IE    0x100
#define SPI_CONTROL_IRRDY 0x80
#define SPI_CONTROL_ITRDY 0x40
#define SPI_CONTROL_ITOE  0x10
#define SPI_CONTROL_IROE  0x08

// IRQ 
#define GPT_BUTTON_IRQ   ALT_INT_INTERRUPT_F2S_FPGA_IRQ0 + BUTTON_PIO_IRQ
#define GPT_MTC_IRQ      ALT_INT_INTERRUPT_F2S_FPGA_IRQ0 + LCD_TOUCH_INT_IRQ
#define GPT_SPI_IRQ      ALT_INT_INTERRUPT_F2S_FPGA_IRQ0 + SPI_RASPBERRYPI_IRQ

// PIO Registers
#define PIOdirection        1*4
#define PIOinterruptmask    2*4
#define PIOedgecapture      3*4
#define PIOoutset           4*4
#define PIOoutclear         5*4

// FGPA Button & MTL PIO
#define PIOdata_fpga_button             fpga_buttons
#define PIOdirection_fpga_button        fpga_buttons + PIOdirection
#define PIOinterruptmask_fpga_button    fpga_buttons + PIOinterruptmask
#define PIOedgecapture_fpga_button      fpga_buttons + PIOedgecapture

#define PIOdata_fpga_MTL                fpga_mtc
#define PIOdirection_fpga_MTL           fpga_mtc + PIOdirection
#define PIOinterruptmask_fpga_MTL       fpga_mtc + PIOinterruptmask
#define PIOedgecapture_fpga_MTL         fpga_mtc + PIOedgecapture

/// VARIABLES DEFINITION ///
void *fpga_leds = ALT_LWFPGASLVS_ADDR + LED_PIO_BASE;
void *fpga_buttons = ALT_LWFPGASLVS_ADDR + BUTTON_PIO_BASE;
void *fpga_mtc     = ALT_LWFPGASLVS_ADDR + LCD_TOUCH_INT_BASE;
#ifdef IS_MTL2
	void *fpga_i2c = ALT_LWFPGASLVS_ADDR + I2C_OPENCORES_0_BASE;
#else
	void *fpga_i2c = ALT_LWFPGASLVS_ADDR + MTL_TOUCH_I2C_BASE;
#endif
void *fpga_spi = ALT_LWFPGASLVS_ADDR + SPI_RASPBERRYPI_BASE;
void *fpga_pi = ALT_LWFPGASLVS_ADDR + PIO_GPIO2PI_BASE;


/// TASKS & ROUTINES DEFINITION ///
// mAbassi tasks //
void Task_HPS_Led(void);
void Task_GSENSOR(void);
void Task_TXRX(void);
void Task_MTL(void);
// Background routines //
void mtc_CallbackInterrupt (uint32_t icciar, void *context);
void setup_hps_gpio( void );
void toogle_hps_led( void );
void spi_ConfigureInterrupt( void );
void raisePiFlag(void);
// Definitions of global functions //
void load_picture(int height, int width, int bpp, PICT_STRUCT* pict_struct,int FdSrc);


#endif
