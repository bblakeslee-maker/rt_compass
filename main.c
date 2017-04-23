// Include files
#include "main.h"

int main(void){
	uint8_t status;											// Holder for status register info
	uint16_t count_x, count_y, count_z;	// Gravity levels in counts
	float mg_x, mg_y, mg_z;								// Gravity levels in mG's
	
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	
	while(1){
		while(!(GPIOE->IDR & ACCEL_DATA_READY_FLAG));
		status = check_accel_status();
		if(status & ZYXDA){
			count_x = read_accel_axis(X_AXIS);
			count_y = read_accel_axis(Y_AXIS);
			count_z = read_accel_axis(Z_AXIS);
		}
	}
}
