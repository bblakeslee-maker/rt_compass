#ifndef _ACCEL_H_
#define _ACCEL_H_

// Include files
#include "stm32l476xx.h"
#include "spi.h"

// Accelerometer control registers
#define CTRL_REG1_A (0x20)
#define CTRL_REG2_A (0x21)
#define CTRL_REG3_A (0x22)
#define CTRL_REG4_A (0x23)
#define CTRL_REG5_A (0x24)
#define CTRL_REG6_A (0x25)
#define CTRL_REG7_A (0x26)

// Accelerometer status register
#define STATUS_REG_A (0x27)

// Accelerometer data registers
#define A_OUT_X_L (0x28)
#define A_OUT_X_H (0x29)
#define A_OUT_Y_L (0x2A)
#define A_OUT_Y_H (0x2B)
#define A_OUT_Z_L (0x2C)
#define A_OUT_Z_H (0x2D)

// Accelerometer address auto increment enable
#define A_IF_ADD_INC (0x04)

// Accelerometer I2C disable
#define A_I2C_DISABLE (0x02)

// Accelerometer SPI read/write enable
#define A_SIM (0x01)

// Accelerometer full scale settings
#define A_FS_0 (0x10)
#define A_FS_1 (0x20)

// Accelerometer block data update
#define A_BDU (0x08)

// Accelerometer axis enables
#define A_X_EN (0x01)
#define A_Y_EN (0x02)
#define A_Z_EN (0x04)

// Accelerometer output data rate
#define A_ODR_0 (0x10)
#define A_ODR_1 (0x20)
#define A_ODR_2 (0x40)

// Accelerometer reset
#define A_BOOT (0x80)

// Accelerometer read/write toggle
#define A_WRITE (0x00)
#define A_READ (0x80)

// Axis channels
enum accel_axis_E{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
} typedef accel_axis;

/*
 * Initialize accelerometer.
 */
void init_accel(void);

/*
 * Read from specified accel axis.
 *
 * @param axis Axis to read from.
 * @return Binary value of axis.
 */
uint16_t read_accel_axis(accel_axis axis);

/*
 * Activates accel chip select line.
 */
void select_accel(void);

/*
 * Deactivates accel chip select line.
 */
void deselect_accel(void);

#endif
