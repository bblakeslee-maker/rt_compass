// Include files
#include "main.h"

int main(void){
	//uint16_t data_x = 0;
	//uint16_t data_y = 0;
	//uint16_t data_z = 0;
	uint8_t reg;
	int i;
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	
	USART_Write(USART2, (uint8_t*)"Press a key.\n\r", strlen("Press a key.\n\r"));
	USART_Read(USART2);
	
	for(i = 0; i < 1000; i++){
		spi_write(A_READ | STATUS_REG_A);
		reg = spi_read();
		if(reg != 0x20){
			USART_Write(USART2, &reg, 1);
		}
	}
	
	/*data_x = read_accel_axis(X_AXIS);
	data_y = read_accel_axis(Y_AXIS);
	data_z = read_accel_axis(Z_AXIS);
	
	USART_Write(USART2, (uint8_t*)&data_x, 2);
	USART_Write(USART2, (uint8_t*)&data_y, 2);
	USART_Write(USART2, (uint8_t*)&data_z, 2);*/
	USART_Write(USART2, (uint8_t*)"Done!", strlen("Done!"));
	USART_Write(USART2, (uint8_t*)"\n\r", 2);
	while(1);
}
