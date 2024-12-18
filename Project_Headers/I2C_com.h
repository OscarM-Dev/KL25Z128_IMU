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
#define IMU_SLAVE_ADDR 0x1D ///< IMU slave address.
#define IMU_W_CONTROL 0x3A ///< IMU write control byte.
#define IMU_R_CONTROL 0x3B ///< IMU read control byte. 
#define IMU_ACT_ADDR 0x2A   ///< IMU activation address.
#define IMU_OUTX_MSB_ADDR 0x01  ///< IMU out x msb address.
#define IMU_OUTX_LSB_ADDR 0x02  ///< IMU out x lsb address.
#define IMU_OUTY_MSB_ADDR 0x03  ///< IMU out y msb address.
#define IMU_OUTY_LSB_ADDR 0x04  ///< IMU out y lsb address.
#define IMU_OUTZ_MSB_ADDR 0x05  ///< IMU out z msb address.
#define IMU_OUTZ_LSB_ADDR 0x06  ///< IMU out z lsb address.


typedef enum { OK, ERROR, ARBITRATIONL } status;    ///< Status type for functions.

//Global data.
extern volatile float board_inclination[3];    //Board inclination in deg from x, y and z plane, check direction axis of IMU in data sheet.

//Functions.
status I2C_write( uint8_t *const write_inst, uint8_t size );
status I2C_read( uint8_t *const read_inst, uint8_t *const answer_buffer, uint8_t size );
status IMU_com( volatile float *const angle );

#endif