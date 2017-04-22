// Include files
#include "main.h"

int main(void){
	/* uint16_t data_x = 0;
	uint16_t data_y = 0;
	uint16_t data_z = 0;
	uint8_t reg; */
	
	int i;
	uint8_t test_data = 'B';
	
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	
	// Read test code (Read currently broken)
	select_accel();
	spi_write(A_WRITE | CTRL_REG3_A);
	spi_write((uint8_t)'A');
	deselect_accel();
	
	for(i = 0; i < 100; i++);
	
	select_accel();
	spi_write(A_READ | CTRL_REG3_A);
	test_data = spi_read();
	deselect_accel();
	
	USART_Write(USART2, (uint8_t*)"Test!\n\r", strlen("Test!\n\r"));
	USART_Write(USART2, &test_data, 1);
	
	while(1);
}
