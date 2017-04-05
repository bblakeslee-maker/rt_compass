// Include files
#include "accel.h"

void init_accel(void){
	// Initialize chip select line PE0
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;			// Enable clock
	GPIOE->MODER &= ~GPIO_MODER_MODER0_1;			// Set output mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;	// Set high speed mode
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT_0;				// Set output type push-pull
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR0;				// Disable pullup/pulldown
	deselect_accel();													// Initialize CS line at high
	
	// Reset accelerometer -- Uncomment and insert delay after if there are problems
	// spi_write(A_WRITE | CTRL_REG6_A);
	// spi_write(A_BOOT);
	
	// Configure full scale sensing at +-4g
	spi_write(A_WRITE | CTRL_REG4_A);
	spi_write(A_FS_1);
	
	// Configure block data update, output data rate (10Hz), and enable axes
	spi_write(A_WRITE | CTRL_REG1_A);
	spi_write(A_BDU | A_X_EN | A_Y_EN | A_Z_EN | A_ODR_0);
}

uint16_t read_accel_axis(accel_axis axis){
	spi_write(A_READ | 
}

void select_accel(void){
	GPIOE->ODR &= ~GPIO_ODR_ODR_0;
}

void deselect_accel(void){
	GPIOE->ODR |= GPIO_ODR_ODR_0;
}
