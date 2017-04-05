// Include files
#include "main.h"

int main(void){
	uint32_t i;
	// Hardware configuration
	System_Clock_Init();
	init_spi();
	init_accel();
	
	while(1){
		select_accel();
		spi_write('A');
		deselect_accel();
	}
}
