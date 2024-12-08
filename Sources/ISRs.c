/**
 * @file ISRs.c
 * @brief This file contains the definition of the ISRs of the peripherals used.
 * 
 */

//Headers.
#include<stdint.h>
#include "derivative.h"

//ISRs.

/**
 * @brief LPTMR ISR. 
 * @note Only TCF can generate an interrupt, also the counter is restarted automatically.
 */
void LPTimer_IRQHandler(){
    
    
    LPTMR0_CSR |= 128;  //Clear flag. 
}


