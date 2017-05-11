// Include files
#include "mag.h"

float x_axis_cal_array[CALIBRATION_COUNT];
float y_axis_cal_array[CALIBRATION_COUNT];
float z_axis_cal_array[CALIBRATION_COUNT];
float x_axis_offset;
float y_axis_offset;
float z_axis_offset;
const float COUNT_TO_MILLIGAUSS = 0.48828125;

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

void calibrate_mag(void){
	int i;
	float x_total = 0;
	float y_total = 0;
	float z_total = 0;
	
	// Collect calibration samples
	for(i = 0; i < CALIBRATION_COUNT; i++){
		
	}
	
	// Average each calibration array
	for(i = 0; i < CALIBRATION_COUNT; i++){
		x_total += count_to_milligauss(x_axis_cal_array[i]);
	}
	x_axis_offset = x_total / CALIBRATION_COUNT;
	
	for(i = 0; i < CALIBRATION_COUNT; i++){
		y_total += count_to_milligauss(y_axis_cal_array[i]);
	}
	y_axis_offset = y_total / CALIBRATION_COUNT;
	
	for(i = 0; i < CALIBRATION_COUNT; i++){
		z_total += count_to_milligauss(z_axis_cal_array[i]);
	}
	z_axis_offset = z_total / CALIBRATION_COUNT;
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

double count_to_milligauss(int16_t count){
	return ((float)count * COUNT_TO_MILLIGAUSS);
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

void print_mag_cal(void){
	
}
