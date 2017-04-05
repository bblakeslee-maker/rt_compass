// Include files
#include "main.h"

int main(void){
	uint16_t data_x = 0;
	uint16_t data_y = 0;
	uint16_t data_z = 0;
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	
	USART_Read(USART2);
	data_x = read_accel_axis(X_AXIS);
	data_y = read_accel_axis(Y_AXIS);
	data_z = read_accel_axis(Z_AXIS);
	while(1);
}
