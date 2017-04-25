#ifndef _MAIN_H_
#define _MAIN_H_

// Include files
#include "stm32l476xx.h"
#include "SysClock.h"
#include <math.h>
#include <stdio.h>
#include "UART.h"
#include "string.h"
#include "spi.h"
#include "accel.h"

// Define pi (can't find it in math.h)
extern const float PI;

// Radian to degree scale factor
extern const float RADIAN_TO_DEGREE;

#endif
