// Include files
#include "main.h"

int main(void){
	uint8_t txBuffer = 'A';
	// Hardware configuration
	System_Clock_Init();
	init_spi();
	
	while(1){
		spi_write(&txBuffer, 1);
	}
}
