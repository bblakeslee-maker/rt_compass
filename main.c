// Include files
#include "main.h"

int main(void){
	uint8_t status;											// Holder for status register info
	int16_t count_x, count_y, count_z;	// Gravity levels in counts
	double mg_x, mg_y, mg_z;						// Gravity levels in mG's
	double roll_rad, pitch_rad;					// Roll and pitch in radians
	
#ifdef DEBUG
	int i;
#endif
	
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	init_mag();
	
#ifdef DEBUG
	for(i = 0; i < 10; i++){
#else
	while(1){
#endif
		while(!(GPIOE->IDR & ACCEL_DATA_READY_FLAG));
		status = check_accel_status();
		if(status & ZYXDA_A){
			// Get data if data is ready on all three axes
			count_x = read_accel_axis(X_AXIS_A);
			count_y = read_accel_axis(Y_AXIS_A);
			count_z = read_accel_axis(Z_AXIS_A);
			
			mg_x = count_to_mg(count_x);
			mg_y = count_to_mg(count_y);
			mg_z = count_to_mg(count_z);

			roll_rad = compute_roll(mg_y, mg_z);
			pitch_rad = compute_pitch(roll_rad, mg_x, mg_y, mg_z);
			
#ifdef DEBUG
			print_accel_telemetry(mg_x, mg_y, mg_z, roll_rad, pitch_rad);
#endif
		}
	}
}
