// Include files
#include "main.h"
#include <stdio.h>

int main(void){
	uint8_t status;											// Holder for status register info
	uint16_t count_x, count_y, count_z;	// Gravity levels in counts
	float mg_x, mg_y, mg_z;								// Gravity levels in mG's
	
	char prompt[20];
	char buffer_x[20];
	char buffer_y[20];
	char buffer_z[20];
	int i;
	
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	
	for(i = 0; i < 10; i++){
		while(!(GPIOE->IDR & ACCEL_DATA_READY_FLAG));
		status = check_accel_status();
		if(status & ZYXDA){
			// Get data if data is ready on all three axes
			count_x = read_accel_axis(X_AXIS);
			count_y = read_accel_axis(Y_AXIS);
			count_z = read_accel_axis(Z_AXIS);
			
			// Convert to mG
			mg_x = (float)count_x * COUNT_TO_MG;
			mg_y = (float)count_y * COUNT_TO_MG;
			mg_z = (float)count_z * COUNT_TO_MG;
			sprintf(prompt, "i = %d\n\r", i);
			sprintf(buffer_x, "%f", mg_x);
			sprintf(buffer_y, "%f", mg_y);
			sprintf(buffer_z, "%f", mg_z);
			USART_Write(USART2, (uint8_t*)prompt, strlen(prompt));
			USART_Write(USART2, (uint8_t*)"mg_x = ", strlen("mg_x = "));
			USART_Write(USART2, (uint8_t*)buffer_x, strlen(buffer_x));
			USART_Write(USART2, (uint8_t*)"\n\r", strlen("\n\r"));
			USART_Write(USART2, (uint8_t*)"mg_y = ", strlen("mg_y = "));
			USART_Write(USART2, (uint8_t*)buffer_y, strlen(buffer_y));
			USART_Write(USART2, (uint8_t*)"\n\r", strlen("\n\r"));
			USART_Write(USART2, (uint8_t*)"mg_z = ", strlen("mg_z = "));
			USART_Write(USART2, (uint8_t*)buffer_z, strlen(buffer_z));
			USART_Write(USART2, (uint8_t*)"\n\r", strlen("\n\r"));
		}
	}
}
