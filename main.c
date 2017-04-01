// Include files
#include "main.h"

int main(void){
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	USART2_Enable_IRQ();
}
