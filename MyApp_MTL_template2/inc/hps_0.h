#ifndef _ALTERA_HPS_0_H_
#define _ALTERA_HPS_0_H_

/*
 * This file was automatically generated by the swinfo2header utility.
 * 
 * Created from SOPC Builder system 'soc_system' in
 * file './soc_system.sopcinfo'.
 */

/*
 * This file contains macros for module 'hps_0' and devices
 * connected to the following masters:
 *   h2f_axi_master
 *   h2f_lw_axi_master
 * 
 * Do not include this header file and another header file created for a
 * different module or master group at the same time.
 * Doing so may result in duplicate macro names.
 * Instead, use the system header file which has macros with unique names.
 */

/*
 * Macros for device 'sysid_qsys', class 'altera_avalon_sysid_qsys'
 * The macros are prefixed with 'SYSID_QSYS_'.
 * The prefix is the slave descriptor.
 */
#define SYSID_QSYS_COMPONENT_TYPE altera_avalon_sysid_qsys
#define SYSID_QSYS_COMPONENT_NAME sysid_qsys
#define SYSID_QSYS_BASE 0x1000
#define SYSID_QSYS_SPAN 8
#define SYSID_QSYS_END 0x1007
#define SYSID_QSYS_ID 2899645186
#define SYSID_QSYS_TIMESTAMP 1554059344

/*
 * Macros for device 'jtag_uart', class 'altera_avalon_jtag_uart'
 * The macros are prefixed with 'JTAG_UART_'.
 * The prefix is the slave descriptor.
 */
#define JTAG_UART_COMPONENT_TYPE altera_avalon_jtag_uart
#define JTAG_UART_COMPONENT_NAME jtag_uart
#define JTAG_UART_BASE 0x2000
#define JTAG_UART_SPAN 8
#define JTAG_UART_END 0x2007
#define JTAG_UART_IRQ 2
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8

/*
 * Macros for device 'led_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'LED_PIO_'.
 * The prefix is the slave descriptor.
 */
#define LED_PIO_COMPONENT_TYPE altera_avalon_pio
#define LED_PIO_COMPONENT_NAME led_pio
#define LED_PIO_BASE 0x3000
#define LED_PIO_SPAN 16
#define LED_PIO_END 0x300f
#define LED_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define LED_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_PIO_CAPTURE 0
#define LED_PIO_DATA_WIDTH 7
#define LED_PIO_DO_TEST_BENCH_WIRING 0
#define LED_PIO_DRIVEN_SIM_VALUE 0
#define LED_PIO_EDGE_TYPE NONE
#define LED_PIO_FREQ 50000000
#define LED_PIO_HAS_IN 0
#define LED_PIO_HAS_OUT 1
#define LED_PIO_HAS_TRI 0
#define LED_PIO_IRQ_TYPE NONE
#define LED_PIO_RESET_VALUE 127

/*
 * Macros for device 'dipsw_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'DIPSW_PIO_'.
 * The prefix is the slave descriptor.
 */
#define DIPSW_PIO_COMPONENT_TYPE altera_avalon_pio
#define DIPSW_PIO_COMPONENT_NAME dipsw_pio
#define DIPSW_PIO_BASE 0x4000
#define DIPSW_PIO_SPAN 16
#define DIPSW_PIO_END 0x400f
#define DIPSW_PIO_IRQ 0
#define DIPSW_PIO_BIT_CLEARING_EDGE_REGISTER 1
#define DIPSW_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DIPSW_PIO_CAPTURE 1
#define DIPSW_PIO_DATA_WIDTH 4
#define DIPSW_PIO_DO_TEST_BENCH_WIRING 0
#define DIPSW_PIO_DRIVEN_SIM_VALUE 0
#define DIPSW_PIO_EDGE_TYPE ANY
#define DIPSW_PIO_FREQ 50000000
#define DIPSW_PIO_HAS_IN 1
#define DIPSW_PIO_HAS_OUT 0
#define DIPSW_PIO_HAS_TRI 0
#define DIPSW_PIO_IRQ_TYPE EDGE
#define DIPSW_PIO_RESET_VALUE 0

/*
 * Macros for device 'button_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'BUTTON_PIO_'.
 * The prefix is the slave descriptor.
 */
#define BUTTON_PIO_COMPONENT_TYPE altera_avalon_pio
#define BUTTON_PIO_COMPONENT_NAME button_pio
#define BUTTON_PIO_BASE 0x5000
#define BUTTON_PIO_SPAN 16
#define BUTTON_PIO_END 0x500f
#define BUTTON_PIO_IRQ 1
#define BUTTON_PIO_BIT_CLEARING_EDGE_REGISTER 1
#define BUTTON_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_PIO_CAPTURE 1
#define BUTTON_PIO_DATA_WIDTH 2
#define BUTTON_PIO_DO_TEST_BENCH_WIRING 0
#define BUTTON_PIO_DRIVEN_SIM_VALUE 0
#define BUTTON_PIO_EDGE_TYPE FALLING
#define BUTTON_PIO_FREQ 50000000
#define BUTTON_PIO_HAS_IN 1
#define BUTTON_PIO_HAS_OUT 0
#define BUTTON_PIO_HAS_TRI 0
#define BUTTON_PIO_IRQ_TYPE EDGE
#define BUTTON_PIO_RESET_VALUE 0

/*
 * Macros for device 'lcd_touch_int', class 'altera_avalon_pio'
 * The macros are prefixed with 'LCD_TOUCH_INT_'.
 * The prefix is the slave descriptor.
 */
#define LCD_TOUCH_INT_COMPONENT_TYPE altera_avalon_pio
#define LCD_TOUCH_INT_COMPONENT_NAME lcd_touch_int
#define LCD_TOUCH_INT_BASE 0x6000
#define LCD_TOUCH_INT_SPAN 16
#define LCD_TOUCH_INT_END 0x600f
#define LCD_TOUCH_INT_IRQ 4
#define LCD_TOUCH_INT_BIT_CLEARING_EDGE_REGISTER 0
#define LCD_TOUCH_INT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LCD_TOUCH_INT_CAPTURE 1
#define LCD_TOUCH_INT_DATA_WIDTH 1
#define LCD_TOUCH_INT_DO_TEST_BENCH_WIRING 0
#define LCD_TOUCH_INT_DRIVEN_SIM_VALUE 0
#define LCD_TOUCH_INT_EDGE_TYPE FALLING
#define LCD_TOUCH_INT_FREQ 50000000
#define LCD_TOUCH_INT_HAS_IN 1
#define LCD_TOUCH_INT_HAS_OUT 0
#define LCD_TOUCH_INT_HAS_TRI 0
#define LCD_TOUCH_INT_IRQ_TYPE EDGE
#define LCD_TOUCH_INT_RESET_VALUE 0


/*
 * Macros for device 'i2c_opencores_0', class 'i2c_opencores'
 * The macros are prefixed with 'I2C_OPENCORES_0_'.
 * The prefix is the slave descriptor.
 */
#define I2C_OPENCORES_0_COMPONENT_TYPE i2c_opencores
#define I2C_OPENCORES_0_COMPONENT_NAME i2c_opencores_0
#define I2C_OPENCORES_0_BASE 0x7000
#define I2C_OPENCORES_0_SPAN 32
#define I2C_OPENCORES_0_END 0x701f
#define I2C_OPENCORES_0_IRQ 5

/*
 * Macros for device 'alt_vip_vfr_0', class 'alt_vip_vfr'
 * The macros are prefixed with 'ALT_VIP_VFR_0_'.
 * The prefix is the slave descriptor.
 */
#define ALT_VIP_VFR_0_COMPONENT_TYPE alt_vip_vfr
#define ALT_VIP_VFR_0_COMPONENT_NAME alt_vip_vfr_0
#define ALT_VIP_VFR_0_BASE 0x8000
#define ALT_VIP_VFR_0_SPAN 128
#define ALT_VIP_VFR_0_END 0x807f
#define ALT_VIP_VFR_0_IRQ 3

/*
 * Macros for device 'spi_raspberrypi', class 'altera_avalon_spi'
 * The macros are prefixed with 'SPI_RASPBERRYPI_'.
 * The prefix is the slave descriptor.
 */
#define SPI_RASPBERRYPI_COMPONENT_TYPE altera_avalon_spi
#define SPI_RASPBERRYPI_COMPONENT_NAME spi_raspberrypi
#define SPI_RASPBERRYPI_BASE 0x9000
#define SPI_RASPBERRYPI_SPAN 32
#define SPI_RASPBERRYPI_END 0x901f
#define SPI_RASPBERRYPI_IRQ 6
#define SPI_RASPBERRYPI_CLOCKMULT 1
#define SPI_RASPBERRYPI_CLOCKPHASE 0
#define SPI_RASPBERRYPI_CLOCKPOLARITY 0
#define SPI_RASPBERRYPI_CLOCKUNITS "Hz"
#define SPI_RASPBERRYPI_DATABITS 32
#define SPI_RASPBERRYPI_DATAWIDTH 32
#define SPI_RASPBERRYPI_DELAYMULT "1.0E-9"
#define SPI_RASPBERRYPI_DELAYUNITS "ns"
#define SPI_RASPBERRYPI_EXTRADELAY 0
#define SPI_RASPBERRYPI_INSERT_SYNC 1
#define SPI_RASPBERRYPI_ISMASTER 0
#define SPI_RASPBERRYPI_LSBFIRST 0
#define SPI_RASPBERRYPI_NUMSLAVES 1
#define SPI_RASPBERRYPI_PREFIX "spi_"
#define SPI_RASPBERRYPI_SYNC_REG_DEPTH 2
#define SPI_RASPBERRYPI_TARGETCLOCK 128000
#define SPI_RASPBERRYPI_TARGETSSDELAY "0.0"

/*
 * Macros for device 'TOUCH', class 'TERASIC_MULTI_TOUCH'
 * The macros are prefixed with 'TOUCH_'.
 * The prefix is the slave descriptor.
 */
#define TOUCH_COMPONENT_TYPE TERASIC_MULTI_TOUCH
#define TOUCH_COMPONENT_NAME TOUCH
#define TOUCH_BASE 0xa000
#define TOUCH_SPAN 128
#define TOUCH_END 0xa07f

/*
 * Macros for device 'pio_gpio2pi', class 'altera_avalon_pio'
 * The macros are prefixed with 'PIO_GPIO2PI_'.
 * The prefix is the slave descriptor.
 */
#define PIO_GPIO2PI_COMPONENT_TYPE altera_avalon_pio
#define PIO_GPIO2PI_COMPONENT_NAME pio_gpio2pi
#define PIO_GPIO2PI_BASE 0xb000
#define PIO_GPIO2PI_SPAN 16
#define PIO_GPIO2PI_END 0xb00f
#define PIO_GPIO2PI_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_GPIO2PI_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_GPIO2PI_CAPTURE 0
#define PIO_GPIO2PI_DATA_WIDTH 1
#define PIO_GPIO2PI_DO_TEST_BENCH_WIRING 0
#define PIO_GPIO2PI_DRIVEN_SIM_VALUE 0
#define PIO_GPIO2PI_EDGE_TYPE NONE
#define PIO_GPIO2PI_FREQ 50000000
#define PIO_GPIO2PI_HAS_IN 0
#define PIO_GPIO2PI_HAS_OUT 1
#define PIO_GPIO2PI_HAS_TRI 0
#define PIO_GPIO2PI_IRQ_TYPE NONE
#define PIO_GPIO2PI_RESET_VALUE 0

/*
 * Macros for device 'ILC', class 'interrupt_latency_counter'
 * The macros are prefixed with 'ILC_'.
 * The prefix is the slave descriptor.
 */
#define ILC_COMPONENT_TYPE interrupt_latency_counter
#define ILC_COMPONENT_NAME ILC
#define ILC_BASE 0x30000
#define ILC_SPAN 256
#define ILC_END 0x300ff


#endif /* _ALTERA_HPS_0_H_ */
