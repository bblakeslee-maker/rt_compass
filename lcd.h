/* 
 * STM32L476VGTx LCD display driver.
 * Author:  Bryan Blakeslee
 */

#ifndef _LCD_H_
#define _LCD_H_

// Include files
#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"
#include "stdio.h"
#include "string.h"

// Mask for mapping pin to alternate function 11
#define AF11 (0xBU)

// Masks for extracting letter_map segmentbits
#define MM (0x01U)
#define MG (0x02U)
#define MF (0x04U)
#define ME (0x08U)
#define MD (0x10U)
#define MC (0x20U)
#define MB (0x40U)
#define MA (0x80U)

// Number of 32 bit words in LCD_RAM
#define MAX_LCD_RAM (16)

// Mask for clearing the LCD_RAM
#define RAM_CLEAR 0x00

// Offset for mapping into individual bits
#define B0  (0)
#define B1  (1)
#define B2  (2)
#define B3  (3)
#define B4  (4)
#define B5  (5)
#define B6  (6)
#define B7  (7)
#define B8  (8)
#define B9  (9)
#define B10 (10)
#define B11 (11)
#define B12 (12)
#define B13 (13)
#define B14 (14)
#define B15 (15)
#define B16 (16)
#define B17 (17)
#define B18 (18)
#define B19 (19)
#define B20 (20)
#define B21 (21)
#define B22 (22)
#define B23 (23)
#define B24 (24)
#define B25 (25)
#define B26 (26)
#define B27 (27)
#define B28 (28)
#define B29 (29)
#define B30 (30)
#define B31 (31)

// Shift macro for alternate function configuration on pins 0 to 7
#define BSL(x) (4 * (x))

// Shift macro for alternate function configuration on pins 8 to 15
#define BSH(x) (4 * ((x) - 8))

// Character slot addresses
enum display_slot_E{
	SLOT1 = 0,
	SLOT2 = 1,
	SLOT3 = 2,
	SLOT4 = 3,
	SLOT5 = 4,
	SLOT6 = 5,
} typedef display_slot;

/* 
 * Predefined character maps.  Each map is an uint32_t.
 * SEGA = BIT 7
 * SEGB = BIT 6
 * SEGC = BIT 5
 * SEGD = BIT 4
 * SEGE = BIT 3
 * SEGF = BIT 2
 * SEGG = BIT 1
 * SEGM = BIT 0
 */
enum letter_map_E{
	ZERO    = 0x000000FCU,	 // 0b11111100
	ONE     = 0x00000060U, 	 // 0b01100000
	TWO     = 0x000000DBU,   // 0b11011011
	THREE   = 0x000000F3U,   // 0b11110011
	FOUR    = 0x00000067U,   // 0b01100111
	FIVE    = 0x000000B7U,   // 0b10110111
	SIX     = 0x000000BFU,   // 0b10111111
	SEVEN   = 0x000000E0U,   // 0b11100000
	EIGHT   = 0x000000FFU,   // 0b11111111
	NINE    = 0x000000E7U,   // 0b11100111
	UPPER_A = 0x000000EFU,   // 0b11101111
	LOWER_B = 0x0000003FU,   // 0b00111111
	UPPER_C = 0x0000009CU,   // 0b10011100
	UPPER_D = 0x0000007BU, 	 // 0b01111011
	UPPER_E = 0x0000009FU,   // 0b10011111
	UPPER_F = 0x0000008FU, 	 // 0b10001111
	UPPER_H = 0x0000006FU,   // 0b01101111
	UPPER_L = 0x0000001CU,   // 0b00011100
	UPPER_O = 0x000000FCU,	 // 0b11111100
	UPPER_S = 0x000000B7U,   // 0b10110111
	RUNNING = 0x0000000BU,   // 0b00001011
	PAUSED  = 0x000000CFU, 	 // 0b11001111
	ERROR   = 0x0000009FU,	 // 0b10011111
	NESTED  = 0x0000002BU,   // 0b00101011
} typedef letter_map;

/*
 * LCD initialization function.
 */
void init_lcd(void);

/*
 * LCD GPIO initialization function.  Called by init_lcd().
 */
void init_lcd_gpio(void);

/*
 * LCD clock initialization function.  Called by init_lcd().
 */
void init_lcd_clock(void);

/*
 * LCD parameters initialzation.  
 * Sets frame rate and contrast.
 */
void init_lcd_params(void);

/*
 * Write to specified display slot on LCD.
 *
 * @param slot Character slot to write to.
 * @param map RAM map describing character to display.
 */
void write_slot(display_slot slot, letter_map map);

/*
 * Send a screen update event.
 */
void screen_update(void);

/*
 * Clears a specific slot in memory.
 * 
 * @param slot Display slot to clear.
 */
void clear_slot(display_slot slot);

/*
 * Clears entire display.
 */
void clear_display(void);

/*
 * Turns on one pixel at a time in RAM.
 * Outputs pixel location to terminal.
 * Not used in normal operation.
 */
 void dump_map(void);
#endif
