// Include files
#include "main.h"

const float PI = 3.14159265358979323846;
const float RADIAN_TO_DEGREE = 180 / PI;
const float ALPHA = 0.03;

int main(void){
	uint8_t status;											// Holder for status register info
	int16_t count_x, count_y, count_z;	// Gravity levels in counts
	double mg_x, mg_y, mg_z;						// Gravity levels in mG's
	double roll_rad, pitch_rad;					// Roll and pitch in radians
	double mg_z2;												// Intermediary pitch variable
	
#ifdef DEBUG
	// Debug
	int i;
	char buffer[40];
	double roll_deg, pitch_deg;					// Roll and pitch in degrees
#endif
	
	// Hardware configuration
	System_Clock_Init();
	UART2_Init();
	init_spi();
	init_accel();
	
#ifdef DEBUG
	for(i = 0; i < 10; i++){
#else
	while(1){
#endif
		while(!(GPIOE->IDR & ACCEL_DATA_READY_FLAG));
		status = check_accel_status();
		if(status & ZYXDA){
			// Get data if data is ready on all three axes
			count_x = read_accel_axis(X_AXIS);
			count_y = read_accel_axis(Y_AXIS);
			count_z = read_accel_axis(Z_AXIS);
			
			// Convert to mG
			mg_x = (float)count_x * COUNT_TO_MG;
			mg_y = (float)count_y * COUNT_TO_MG;
			mg_z = (float)count_z * COUNT_TO_MG;

			roll_rad = atan2(mg_y, mg_z);														// Compute roll
			mg_z2 = mg_y * sin(roll_rad) + mg_z * cos(roll_rad);	// Pitch intermediary
			pitch_rad = atan(-mg_x / mg_z2);												// Compute pitch
			
#ifdef DEBUG
			sprintf(buffer, "mg_x = %f\n\r", mg_x);
			USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
			sprintf(buffer, "mg_y = %f\n\r", mg_y);
			USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
			sprintf(buffer, "mg_z = %f\n\r", mg_z);
			USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
			sprintf(buffer, "mg_z2 = %f\n\r", mg_z2);
			USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
			roll_deg = roll_rad * RADIAN_TO_DEGREE;				// Convert to degree
			sprintf(buffer, "Roll = %f\n\r", roll_deg);
			USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
			pitch_deg = pitch_rad * RADIAN_TO_DEGREE;			// Convert to degree
			sprintf(buffer, "Pitch = %f\n\r", pitch_deg);
			USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
#endif
		}
	}
}
