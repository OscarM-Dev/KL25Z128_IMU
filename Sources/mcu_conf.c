/**
 * @file mcu_conf.c
 * @brief This is the file for the definition of the peripheral configuration functions.
 * 
 */

//Headers.
#include"mcu_conf.h"

//Functions.
/**
 * @brief This function configures the MCU clock sources.
 * @note This clks are configured for RUN mode.
 * 
 * Core CLK -->24 Mhz.
 * Sys CLK -->24 Mhz.
 * Platform CLK -->24 Mhz.
 * Bus CLK -->12 Mhz.
 * Flash CLK -->12 Mhz.
 * MCGIRCLK -->4 Mhz
 * MCGFLLCLK -->72 Mhz.
 * MCGPLLCLK -->Not used.
 * OSCERCLK -->Not used
 * ERCLK32K -->Not used
 * LPO -->Not used
 */
void Clk_conf( void ){
    MCG_SC = 0; //FIRC divider to 1, FIRC -->4Mhz.

    //MCGFLLCLK configuration.
    //IREFS by default SIRC -->32.768Khz.
    MCG_C4 |= 0xC0; //FLL factor of 2197, 72Mhz.
    //PLLS by default FLL.

    //MCGOUTCLK configuration.
    //CLKS by default PLLS (FLL) -->72Mhz

    //MCGIRCLK configuration.    
    MCG_C2 = 1; //IRCS -->FIRC.
    MCG_C1 |= 2;    //IRCLKEN.

    //Main clks configuration.
    SIM_CLKDIV1 = 0x20010000;   //Outdiv1 = 3 and Outdiv4 = 2.  
    //PLLFLLSEL by default is FLL.
}

/**
 * @brief This function configures the LPTMR with a temporization of 50ms.
 * 
 */
void Lpt_conf( void ){        
    SIM_SCGC5 = 1;  //Clock enabled for LPT module.
    LPTMR0_PSR |= ( uint8_t )0x28;  //MCGIRCLK selected, and prescaler of 64 -->sync Clk 62.5Khz, count period of 16us.
    LPTMR0_CMR = 6250;  //Compare value.
    
    //Interrupt configuration.
    LPTMR0_CSR = 64;    //Local enable.
    NVIC_ISER |= (1 << 28);  //Global enable.

    LPTMR0_CSR |= 1;    //Counter enabled.
}