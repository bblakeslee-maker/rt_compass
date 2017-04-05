// Include files
#include "main.h"

int main(void){
	//uint8_t txBuffer = 'A';
	// Hardware configuration
	System_Clock_Init();
	init_spi();
	
	spi_read();
	while(1);
}
