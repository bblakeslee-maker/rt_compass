#ifndef _SPI_H_
#define _SPI_H_

// Include files
#include "stm32l476xx.h"
#include "UART.h"
#include "string.h"

// Alternate function pin mappings
// Format: AF[PinNumber]_[FunctionNumber]
#define AF1_5 (0x5 << 4)
#define AF4_5 (0x5 << 16)

// Dummy byte for SPI read
#define DUMMY (0xFF)

/*
 * Initialize SPI1 hardware.
 * Configuration hardcoded in half duplex mode for Accel sensor.
 */
void init_spi(void);

/*
 * Initialize SPI hardware GPIO pins.
 */
static void init_gpio(void);

/*
 * Write byte of data over SPI.
 *
 * @param data Data byte to write.
 */
void spi_write(uint8_t data);

/* 
 * Read byte of data over SPI.
 *
 * @return Byte of data from device.
 */
uint8_t spi_read(void);

#endif
