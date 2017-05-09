#ifndef _COMPASS_H_
#define _COMPASS_H_

// Include files
#include "stm32l476xx.h"
#include <math.h>
#include <stdio.h>
#include "UART.h"
#include "string.h"

// Accelerometer scale factor for count to mG conversion
extern const float COUNT_TO_MG;

// Stability constant for roll
extern const float ALPHA;

// Define pi (can't find it in math.h)
extern const float PI;

// Radian to degree scale factor
extern const float RADIAN_TO_DEGREE;

/*
 * Converts accelerometer counts to milli-G's.
 *
 * @param count ADC value from accelerometer
 * @return Value in milli-G's
 */
double count_to_mg(int16_t count);

/*
 * Computes roll angle of board in radians.
 *
 * @param mg_y Y-axis gravity vector in milli-G's.
 * @param mg_z Z-axis gravity vector in milli-G's.
 * @return Roll angle in radians.
 */
double compute_roll(double mg_y, double mg_z);

/*
 * Computes pitch angle of board in radians.
 *
 * @param roll_rad Roll angle in radians.
 * @param mg_x X-axis gravity vector in milli-G's.
 * @param mg_y Y-axis gravity vector in milli-G's.
 * @param mg_z Z-axis gravity vector in milli-G's.
 * @return Pitch angle in radians.
 */
double compute_pitch(double roll_rad, double mg_x, double mg_y, double mg_z);

/*
 * Prints out gravity vectors and angles in degrees over USART2.
 *
 * @param mg_x X-axis gravity vector in milli-G's.
 * @param mg_y Y-axis gravity vector in milli-G's.
 * @param mg_z Z-axis gravity vector in milli-G's.
 * @param roll_rad Roll angle in radians.
 * @param pitch_rad Pitch angle in radians.
 */
void print_accel_telemetry(double mg_x, double mg_y, double mg_z, 
													 double roll_rad, double pitch_rad);
#endif
