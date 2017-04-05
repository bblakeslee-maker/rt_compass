#include "spi.h"

void init_spi(void){
	init_gpio();
	
	// SPI2 clock configuration
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_SPI2RST;
	
	SPI2->CR1 |= SPI_CR1_BR_2;			// Set SPI2 SCLK rate f / 32
	SPI2->CR1 |= SPI_CR1_CPOL;			// Set SPI2 polarity high
	SPI2->CR1 |= SPI_CR1_CPHA;			// Set SPI2 phase transition on first edge.  If it doesn't work, check me first!
	SPI2->CR1 |= SPI_CR1_BIDIMODE;	// Set SPI2 bidirectional mode.  Works with BIDIOE in write function
	SPI2->CR1 &= ~SPI_CR1_RXONLY;		// Disable receive only mode
	SPI2->CR1 &= ~SPI_CR1_LSBFIRST;	// Transmit MSB first
	SPI2->CR1 &= ~SPI_CR1_SSM;			// Disable software slave management
	SPI2->CR1 |= SPI_CR1_MSTR;			// Set SPI2 Master Mode
	SPI2->CR1 |= SPI_CR1_BIDIOE;		// Set single data line to output mode

	
	SPI2->CR2 &= ~SPI_CR2_DS;
	SPI2->CR2 |= (SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0);	// Set 8 bit data transfers
	SPI2->CR2 |= SPI_CR2_SSOE;			// Set slave select output enable
	SPI2->CR1 |= SPI_CR1_SPE;				// Enable SPI interface
}

static void init_gpio(void){
	// Clock configuration
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
	
	// Alternate function configuration
	GPIOD->MODER &= ~GPIO_MODER_MODER1_0;		// PD1 -> SPI2_SCLK
	GPIOD->AFR[0] |= AF1_5;
	GPIOD->MODER &= ~GPIO_MODER_MODER4_0;		// PD4 -> SPI2_MOSI (Bidirectional Mode)
	GPIOD->AFR[0] |= AF4_5;
}

void spi_write(uint8_t data){
	// Set single data line to output mode
	SPI2->CR1 |= SPI_CR1_BIDIOE;
	
	while(!(SPI2->SR & SPI_SR_TXE));				// Wait until TX buffer empty
	*((volatile uint8_t*)&SPI2->DR) = data;	// Write into SPI data register in 8 bit mode
	while(SPI2->SR & SPI_SR_BSY);						// Wait until device not busy
}

uint8_t spi_read(void){
	uint8_t data;
	
	// Set single data line to input mode
	SPI2->CR1 &= ~SPI_CR1_BIDIOE;
	
	while(!(SPI2->SR & SPI_SR_TXE));					// Wait until TX buffer empty
	data = (uint8_t)(SPI2->DR);								// Get lower 8 bits of data register
	
	// Set single data line to output mode to stop clock
	SPI2->CR1 |= SPI_CR1_BIDIOE;
	
	return data;
}
