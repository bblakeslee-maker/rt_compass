#ifndef _COMPASS_H_
#define _COMPASS_H_

// Include files
#include "stm32l476xx.h"
#include <math.h>
#include <stdio.h>
#include "UART.h"
#include "string.h"

// Stability constant for roll
extern const float ALPHA;

// Define pi (can't find it in math.h)
extern const float PI;

// Radian to degree scale factor
extern const float RADIAN_TO_DEGREE;

// Angle ranges for decoding angle into compass heading
extern const float N_NE_BOUND;
extern const float NE_E_BOUND;
extern const float E_SE_BOUND;
extern const float SE_S_BOUND;
extern const float S_SW_BOUND;
extern const float SW_W_BOUND;
extern const float W_NW_BOUND;
extern const float NW_N_BOUND;

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

/*
 * Compute yaw angle (compass heading) of board in radians.
 *
 * @param roll_rad Roll angle in radians.
 * @param pitch_rad Pitch angle in radians.
 * @param mGauss_x X-axis magnetic vector in milligauss.
 * @param mGauss_y Y-axis magnetic vector in milligauss.
 * @param mGauss_z Z-axis magnetic vector in milligauss.
 * @return Yaw (heading angle) in radians.
 */
double compute_yaw(double roll_rad, double pitch_rad, \
									 double mGauss_x, double mGauss_y, double mGauss_z);

/*
 * Prints out magnetic vectors in milligauss over USART2.
 *
 * @param mGauss_x X-axis magnetic vector in milligauss.
 * @param mGauss_y Y-axis magnetic vector in milligauss.
 * @param mGauss_z Z-axis magnetic vector in milligauss.
 * @param yaw_rad Yaw angle (compass heading) in radians.
 */
void print_mag_telemetry(double mGauss_x, double mGauss_y, \
												 double mGauss_z, double yaw_rad);

#endif
