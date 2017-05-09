// Include files
#include "accel.h"

void init_accel(void){
	// Initialize GPIO clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	// Initialize chip select line PE14
	GPIOE->MODER &= ~GPIO_MODER_MODER14_1;		// Set output mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14;// Set high speed mode
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT_14;			// Set output type push-pull
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR14;			// Disable pullup/pulldown
	deselect_accel();													// Initialize CS line at high
	
	// Initialize input for accel data ready line PE12
	GPIOE->MODER &= ~GPIO_MODER_MODER12;			// Set input mode
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR12;			// Disable pullup/pulldown
	
	// Reset accelerometer -- Uncomment and insert delay after if there are problems
	// spi_write(A_WRITE | CTRL_REG6_A);
	// spi_write(A_BOOT);
	
	// Enable auto increment, enable SPI read/write, full scale +/-4g
	select_accel();
	spi_write(A_WRITE | CTRL_REG4_A);
	spi_write(A_IF_ADD_INC | A_I2C_DISABLE | A_SIM | A_FS_1);
	deselect_accel();
	
	// Enable accel data ready interrupt
	select_accel();
	spi_write(A_WRITE | CTRL_REG3_A);
	spi_write(INT_XL_DRDY);
	deselect_accel();
	
	// Configure block data update, output data rate (10Hz), and enable axes
	select_accel();
	spi_write(A_WRITE | CTRL_REG1_A);
	spi_write(A_BDU | A_X_EN | A_Y_EN | A_Z_EN | A_ODR_0);
	deselect_accel();
}

int16_t read_accel_axis(accel_axis axis){
	uint8_t address;
	int16_t data_low, data_high;
	
	// Address decode
	if(axis == X_AXIS_A){
		address = OUT_X_L_A;
	}else if(axis == Y_AXIS_A){
		address = OUT_Y_L_A;
	}else if(axis == Z_AXIS_A){
		address = OUT_Z_L_A;
	}
	
	// Get low then high data byte
	select_accel();
	spi_write(A_READ | address);
	data_low = spi_read();
	data_high = spi_read();
	deselect_accel();
	
	return ((data_high << 8) | data_low);
}

uint8_t check_accel_status(void){
	uint8_t data;
	
	select_accel();
	spi_write(A_READ | STATUS_REG_A);
	data = spi_read();
	deselect_accel();
	
	return data;
}

void select_accel(void){
	GPIOE->ODR &= ~GPIO_ODR_ODR_14;
}

void deselect_accel(void){
	GPIOE->ODR |= GPIO_ODR_ODR_14;
}
