#ifndef _MAG_H_
#define _MAG_H_

// Include files
#include "stm32l476xx.h"
#include "spi.h"

// Magnetometer control registers
#define CTRL_REG1_M (0x20)
#define CTRL_REG2_M (0x21)
#define CTRL_REG3_M (0x22)
#define CTRL_REG4_M	(0x23)
#define CTRL_REG5_M (0x24)

// Magnetometer status register
#define STATUS_REG_M (0x27)

// Magnetometer data registers
#define OUT_X_L_M	(0x28)
#define OUT_X_H_M (0x29)
#define OUT_Y_L_M (0x2A)
#define OUT_Y_H_M (0x2B)
#define OUT_Z_L_M (0x2C)
#define OUT_Z_H_M (0x2D)

// Magnetometer scale factor for count to mGauss convertion
extern const float COUNT_TO_MGAUSS;

// Axis channels
enum mag_axis_E{
	X_AXIS_M,
	Y_AXIS_M,
	Z_AXIS_M
}typedef mag_axis;

/*
 * Initialize magnetometer.
 */
void init_mag(void);

/*
 * Read from specified mag axis.
 *
 * @param axis Axis to read from.
 * @return Binary value of axis.
 */
int16_t read_mag_axis(mag_axis axis);

/*
 * Get status register contents from magnetometer.
 *
 * @return Contents of status register.
 */
uint8_t check_mag_status(void);

/*
 * Activates mag chip select line.
 */
void select_mag(void);

/*
 * Deactivates mag chip select line.
 */
void deselect_mag(void);

#endif
