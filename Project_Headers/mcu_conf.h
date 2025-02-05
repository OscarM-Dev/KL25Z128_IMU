/**
 * @file mcu_conf.h
 * @brief This is the header for the declaration of configuration macros and functions related
 * to peripheral configuration.
 * 
 * 
 */

#ifndef MCU_CONF_H
#define MCU_CONF_H

//Headers.
#include <stdint.h> 
#include "derivative.h" //Register macros declaration.

//Macros.


//Functions.
void Clk_conf( void );
void Lpt_conf( void );
void UART0_conf( void );
void I2C0_conf( void );





#endif