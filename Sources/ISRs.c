/**
 * @file ISRs.c
 * @brief This file contains the definition of the ISRs of the peripherals used.
 * 
 */

//Headers.
#include <stdint.h>
#include "derivative.h"
#include "I2C_com.h"

//ISRs.

/**
 * @brief LPTMR ISR. 
 * @note Only TCF can generate an interrupt, also the counter is restarted automatically.
 */
void LPTimer_IRQHandler() {
    IMU_com( &board_inclination );  //Calculating board inclination.
    
    LPTMR0_CSR |= 128;  //Clear flag. 
}


