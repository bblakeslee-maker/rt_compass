// Include files
#include "mag.h"

void init_mag(void){
	// Initialize GPIO clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	// Initialize chip select line PE10
	GPIOE->MODER &= ~GPIO_MODER_MODER10_1;		// Set output mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10;// Set high speed mode
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT_10;			// Set output type push-pull
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR10;			// Disable pullup/pulldown
	deselect_mag();	
	
	// Initialize input for mag data ready line PE11
	GPIOE->MODER &= ~GPIO_MODER_MODER11;			// Set input mode
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR11;			// Disable pullup/pulldown
	
	// Enable SPI read/write
	select_mag();
	spi_write(M_WRITE | CTRL_REG3_M);
	spi_write(I2C_DISABLE | SIM);
	deselect_mag();
	
	// Configure data rate at 10Hz, XY ultra high performance mode
	select_mag();
	spi_write(M_WRITE | CTRL_REG1_M);
	spi_write(OM1 | OM0 | DO2);
	deselect_mag();
	
	// Configure Z axis performance mode
	select_mag();
	spi_write(M_WRITE | CTRL_REG4_M);
	spi_write(OMZ1 | OMZ0);
	deselect_mag();
	
	// Configure full scale at +/-16 Gauss
	select_mag();
	spi_write(M_WRITE | CTRL_REG2_M);
	spi_write(FS1 | FS0);
	deselect_mag();
	
	// Enable block data update
	select_mag();
	spi_write(M_WRITE | CTRL_REG5_M);
	spi_write(BDU);
	deselect_mag();
	
	// Enable mag data ready interrupt
	select_mag();
	spi_write(M_WRITE | INT_CFG_M);
	spi_write(XIEN | YIEN | ZIEN | IEN);
	deselect_mag();
}

int16_t read_mag_axis(mag_axis axis){
	uint8_t address;
	int16_t data_low, data_high;
	
	// Address decode
	if(axis == X_AXIS_M){
		address = OUT_X_L_M;
	}else if(axis == Y_AXIS_M){
		address = OUT_Y_L_M;
	}else if(axis == Z_AXIS_M){
		address = OUT_Z_L_M;
	}
	
	// Get low then high data byte
	select_mag();
	spi_write(M_READ | M_MULTIBYTE | address);
	data_low = spi_read();
	data_high = spi_read();
	deselect_mag();
	
	return ((data_high << 8) | data_low);
}

uint8_t check_mag_status(void){
	uint8_t data;
	
	select_mag();
	spi_write(M_READ | STATUS_REG_M);
	data = spi_read();
	deselect_mag();
	
	return data;
}

bool mag_data_ready(){
	return (GPIOE->IDR & MAG_DATA_READY_FLAG);
}

void select_mag(void){
	GPIOE->ODR &= ~GPIO_ODR_ODR_10;
}

void deselect_mag(void){
	GPIOE->ODR |= GPIO_ODR_ODR_10;
}
