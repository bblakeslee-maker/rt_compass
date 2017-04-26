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
#define OUT_X_L_A (0x28)
#define OUT_X_H_A (0x29)
#define OUT_Y_L_A (0x2A)
#define OUT_Y_H_A (0x2B)
#define OUT_Z_L_A (0x2C)
#define OUT_Z_H_A (0x2D)

// Accelerometer data ready line mask
#define ACCEL_DATA_READY_FLAG (0x1000)

// Accelerometer triaxial data ready
#define ZYXDA_A (0x08)

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

// Accelerometer data ready interrupt
#define INT_XL_DRDY (0x01)

// Accelerometer reset
#define A_BOOT (0x80)

// Accelerometer read/write toggle
#define A_WRITE (0x00)
#define A_READ (0x80)

// Accelerometer scale factor for count to mG conversion
extern const float COUNT_TO_MG;

// Axis channels
enum accel_axis_E{
	X_AXIS_A,
	Y_AXIS_A,
	Z_AXIS_A
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
int16_t read_accel_axis(accel_axis axis);

/*
 * Get status register contents from accelerometer.
 *
 * @return Contents of status register.
 */
uint8_t check_accel_status(void);

/*
 * Activates accel chip select line.
 */
void select_accel(void);

/*
 * Deactivates accel chip select line.
 */
void deselect_accel(void);

#endif
