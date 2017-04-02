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

/*
 * Initialize SPI2 hardware.
 * Configuration hardcoded in half duplex mode for Accel sensor.
 */
void init_spi(void);

/*
 * Initialize SPI hardware GPIO pins.
 */
static void init_gpio(void);

/*
 * Write buffer of specified size over SPI.
 *
 * @param buffer Pointer to buffer to data to transmit.
 * @param size Size of buffer to write in bytes.
 */
void spi_write(uint8_t* buffer, uint16_t size);

/* 
 * Read buffer of specified size over SPI.
 *
 * @param buffer Pointer to buffer to read data into.
 * @param size Amount of data to read in bytes.
 */
void spi_read(uint8_t* buffer, uint16_t size);

#endif
