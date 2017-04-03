// Include files
#include "main.h"

int main(void){
	uint8_t txBuffer = 'A';
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	USART2_Enable_IRQ();
	init_spi();
	
	while(1){
		USART_Write(USART2, (uint8_t*)"While!\n\r", strlen("While!\n\r"));
		spi_write(&txBuffer, 1);
	}
}
