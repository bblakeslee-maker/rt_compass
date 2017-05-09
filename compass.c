#include "compass.h"

const float COUNT_TO_MG = 0.1204238921;
const float PI = 3.14159265358979323846;
const float RADIAN_TO_DEGREE = 180 / PI;
const float ALPHA = 0.03;

double count_to_mg(int16_t count){
	return ((float)count * COUNT_TO_MG);
}

double compute_roll(double mg_y, double mg_z){
	return atan2(mg_y, mg_z);
}

double compute_pitch(double roll_rad, double mg_x, double mg_y, double mg_z){
	double mg_z2;
	
	mg_z2 = mg_y * sin(roll_rad) + mg_z * cos(roll_rad);	// Coordinate frame rotation
	return atan(-mg_x / mg_z2);											
}

void print_accel_telemetry(double mg_x, double mg_y, double mg_z, \
													 double roll_rad, double pitch_rad){
	char buffer[40];
	double roll_deg, pitch_deg;	// Roll and pitch in degrees
														 
	sprintf(buffer, "mg_x = %f\n\r", mg_x);
	USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
	sprintf(buffer, "mg_y = %f\n\r", mg_y);
	USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
	sprintf(buffer, "mg_z = %f\n\r", mg_z);
	USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
	roll_deg = roll_rad * RADIAN_TO_DEGREE;				// Convert to degree
	sprintf(buffer, "Roll = %f\n\r", roll_deg);
	USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
	pitch_deg = pitch_rad * RADIAN_TO_DEGREE;			// Convert to degree
	sprintf(buffer, "Pitch = %f\n\r", pitch_deg);
	USART_Write(USART2, (uint8_t*)buffer, strlen(buffer));
}
