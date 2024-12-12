/**
 * @file I2C_com.h
 * @brief This header contains the declaration of functions and tools for the I2C communication.
 */

#ifndef I2C_COM_H
#define I2C_COM_H

//Headers.
#include <stdint.h>
#include <math.h>
#include "derivative.h"


//Enums and macros.

typedef enum { OK, ERROR, ARBITRATIONL } status;    ///< Status type for functions.


//Functions.
status I2C_write( uint8_t *const write_inst, uint8_t size );
status I2C_read( uint8_t *const read_inst, uint8_t *const answer_buffer, uint8_t size );
status IMU_com( float *angle );

#endif