// Include files
#include "main.h"

int main(void){
	uint8_t status;												// Holder for status register info
	int16_t count_x, count_y, count_z;		// Gravity levels in counts
	double mGauss_x, mGauss_y, mGauss_z;	// Magnetic levels in milligauss
	double yaw_rad;												// Yaw angle in radians
	double mg_x, mg_y, mg_z;							// Gravity levels in mG's
	double roll_rad, pitch_rad;						// Roll and pitch in radians
	
#ifdef DEBUG
	int i;
#endif
	
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	init_mag();
	
	for(i = 0; i < 10; i++){
		while(!accel_data_ready());
		
		status = check_accel_status();
		if(status & ZYXDA_A){
			// Get accel data if data is ready on all three axes
			count_x = read_accel_axis(X_AXIS_A);
			count_y = read_accel_axis(Y_AXIS_A);
			count_z = read_accel_axis(Z_AXIS_A);
			
			// Convert to milliG
			mg_x = count_to_mg(count_x);
			mg_y = count_to_mg(count_y);
			mg_z = count_to_mg(count_z);

			// Compute tilt angles
			roll_rad = compute_roll(mg_y, mg_z);
			pitch_rad = compute_pitch(roll_rad, mg_x, mg_y, mg_z);
			
#ifdef DEBUG
			print_accel_telemetry(mg_x, mg_y, mg_z, roll_rad, pitch_rad);
#endif
		}
		
		while(!mag_data_ready());
		status = check_mag_status();
		if(status & ZYXDA_M){
			// Get mag data if data is ready on all three axes
			count_x = read_mag_axis(X_AXIS_M);
			count_y = read_mag_axis(Y_AXIS_M);
			count_z = read_mag_axis(Z_AXIS_M);
			
			// Convert to milligauss
			mGauss_x = count_to_milligauss(count_x);
			mGauss_y = count_to_milligauss(count_y);
			mGauss_z = count_to_milligauss(count_z);
			
			// Compute compass heading
			yaw_rad = compute_yaw(roll_rad, pitch_rad, mGauss_x, mGauss_y, mGauss_z);
			
#ifdef DEBUG
			print_mag_telemetry(mGauss_x, mGauss_y, mGauss_z, yaw_rad);
			USART_Write(USART2, (uint8_t*)"**********\n\r", strlen("**********\n\r"));
#endif
		}
	}
}
