/**
 * @file ISRs.c
 * @brief This file contains the definition of the ISRs of the peripherals used.
 * 
 */

//Headers.
#include <stdint.h>
#include "derivative.h"
#include "I2C_com.h"
#include "UART_com.h"

//ISRs.

/**
 * @brief LPTMR ISR. 
 * @note Only TCF can generate an interrupt, also the counter is restarted automatically.
 */
void LPTimer_IRQHandler() {
    //Local data.    
    static volatile uint8_t count = 0;

    IMU_com( board_inclination );  //Calculating board inclination.

    if ( ++count == 3 ) { //Communicating inclination values every 300ms.
        Terminal_com( board_inclination );  //Communicating with the Tera term terminal.
        count = 0;
    }
    
    LPTMR0_CSR |= 128;  //Clear flag. 
}


