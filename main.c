// Include files
#include "main.h"

int main(void){
	uint8_t status;	// Holder for status register info
	
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	
	while(1){
		while(!(GPIOE->IDR & ACCEL_DATA_READY_FLAG));
		status = check_accel_status();
		if(status & ZYXDA){
			read_accel_axis(X_AXIS);
			read_accel_axis(Y_AXIS);
			read_accel_axis(Z_AXIS);
		}
	}
}
