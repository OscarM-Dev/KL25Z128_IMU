/**
 * @file UART_com.h
 * @brief This header contains the declaration of the functions and tools related to the UART0 communication.
 * 
 */

#ifndef UART_COM_H
#define UART_COM_H

//Headers.
#include <stdint.h>
#include "derivative.h"
#include "status.h"

//Enums and macros.

//Global data.

//Functions.
status Numeric_to_ASCII( uint8_t *const numeric_data, uint32_t *const ASCII_data, uint8_t *const data_n_digits, uint8_t size );
status UART_Transmit( uint8_t *const data, uint8_t size );
status Terminal_com( volatile float *const angles );



#endif
