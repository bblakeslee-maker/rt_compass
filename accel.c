// Include files
#include "accel.h"

void init_accel(void){
	// Initialize chip select line PE14
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;			// Enable clock
	GPIOE->MODER &= ~GPIO_MODER_MODER14_1;		// Set output mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14;// Set high speed mode
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT_14;			// Set output type push-pull
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR14;			// Disable pullup/pulldown
	deselect_accel();													// Initialize CS line at high
	
	// Reset accelerometer -- Uncomment and insert delay after if there are problems
	// spi_write(A_WRITE | CTRL_REG6_A);
	// spi_write(A_BOOT);
	
	// Enable auto increment, enable SPI read/write, full scale +/-4g
	select_accel();
	spi_write(A_WRITE | CTRL_REG4_A);
	spi_write(A_IF_ADD_INC | A_I2C_DISABLE | A_SIM | A_FS_1);
	deselect_accel();
	
	// Configure block data update, output data rate (10Hz), and enable axes
	select_accel();
	spi_write(A_WRITE | CTRL_REG1_A);
	spi_write(A_BDU | A_X_EN | A_Y_EN | A_Z_EN | A_ODR_0);
	deselect_accel();
}

uint16_t read_accel_axis(accel_axis axis){
	uint8_t addr_low, addr_high;
	uint16_t data_low, data_high;
	
	// Address decode
	if(axis == X_AXIS){
		addr_low = A_OUT_X_L;
		addr_high = A_OUT_X_H;
	}else if(axis == Y_AXIS){
		addr_low = A_OUT_Y_L;
		addr_high = A_OUT_Y_H;
	}else if(axis == Z_AXIS){
		addr_low = A_OUT_Z_L;
		addr_high = A_OUT_Z_H;
	}
	
	// Get low data byte
	select_accel();
	spi_write(A_READ | addr_low);
	data_low = spi_read();
	deselect_accel();
	
	// Get high data byte
	select_accel();
	spi_write(A_READ | addr_high);
	data_high = spi_read();
	deselect_accel();
	
	return ((data_high << 8) | data_low);
}

void select_accel(void){
	GPIOE->ODR &= ~GPIO_ODR_ODR_14;
}

void deselect_accel(void){
	GPIOE->ODR |= GPIO_ODR_ODR_14;
}
