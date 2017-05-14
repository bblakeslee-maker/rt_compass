// Include files
#include "main.h"

int main(void){
	uint8_t status;												// Holder for status register info
	int16_t count_x, count_y, count_z;		// Gravity levels in counts
	double mGauss_x, mGauss_y, mGauss_z;	// Magnetic levels in milligauss
	double mGauss_x_debias, 							// Debiased magnetic levels
				 mGauss_y_debias,
				 mGauss_z_debias;
	double yaw_rad;												// Yaw angle in radians
	double yaw_deg;												// Yaw angle in degrees
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
	init_lcd();
	clear_display();
	screen_update();
	
	#ifdef DEBUG
	for(i = 0; i < 10; i++){
	#else
	while(1){
	#endif
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
			
			// Correct for bias
			mGauss_x_debias = mGauss_x - x_axis_offset;
			mGauss_y_debias = mGauss_y - y_axis_offset;
			mGauss_z_debias = mGauss_z - z_axis_offset;
			
			// Compute compass heading
			yaw_rad = compute_yaw(roll_rad, pitch_rad, 
														mGauss_x_debias, mGauss_y_debias, mGauss_z_debias);
			
			#ifdef DEBUG
			print_mag_telemetry(mGauss_x, mGauss_y, mGauss_z, yaw_rad);
			#endif
			
			// Display compass heading on LCD
			yaw_deg = yaw_rad * RADIAN_TO_DEGREE;
			clear_display();
			if((yaw_deg > NW_N_BOUND) && (yaw_deg < N_NE_BOUND)){
				// North
				write_slot(SLOT1, NORTH);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"NORTH\n\r", strlen("NORTH\n\r"));
				#endif
			}else if((yaw_deg > N_NE_BOUND) && (yaw_deg < NE_E_BOUND)){
				// Northeast
				write_slot(SLOT1, NORTH);
				write_slot(SLOT2, EAST);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"NORTHEAST\n\r", strlen("NORTHEAST\n\r"));
				#endif
			}else if((yaw_deg > NE_E_BOUND) && (yaw_deg < E_SE_BOUND)){
				// East
				write_slot(SLOT1, EAST);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"EAST\n\r", strlen("EAST\n\r"));
				#endif
			}else if((yaw_deg > E_SE_BOUND) && (yaw_deg < SE_S_BOUND)){
				// Southeast
				write_slot(SLOT1, SOUTH);
				write_slot(SLOT2, EAST);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"SOUTHEAST\n\r", strlen("SOUTHEAST\n\r"));
				#endif
			}else if((yaw_deg > SE_S_BOUND) || (yaw_deg < S_SW_BOUND)){
				// South
				write_slot(SLOT1, SOUTH);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"SOUTH\n\r", strlen("SOUTH\n\r"));
				#endif
			}else if((yaw_deg > S_SW_BOUND) && (yaw_deg < SW_W_BOUND)){
				// Southwest
				write_slot(SLOT1, SOUTH);
				write_slot(SLOT2, WEST);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"SOUTHWEST\n\r", strlen("SOUTHWEST\n\r"));
				#endif
			}else if((yaw_deg > SW_W_BOUND) && (yaw_deg < W_NW_BOUND)){
				// West
				write_slot(SLOT1, WEST);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"WEST\n\r", strlen("WEST\n\r"));
				#endif
			}else if((yaw_deg > W_NW_BOUND) && (yaw_deg < NW_N_BOUND)){
				// Northwest
				write_slot(SLOT1, NORTH);
				write_slot(SLOT2, WEST);
				#ifdef DEBUG
				USART_Write(USART2, (uint8_t*)"NORTHWEST\n\r", strlen("NORTHWEST\n\r"));
				#endif
			}
			screen_update();
			
			#ifdef DEBUG
			USART_Write(USART2, (uint8_t*)"**********\n\r", strlen("**********\n\r"));
			#endif
		}
	}
}
