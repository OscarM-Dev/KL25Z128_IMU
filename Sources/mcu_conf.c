/**
 * @file mcu_conf.c
 * @brief This is the file for the definition of the peripheral configuration functions.
 * 
 */

//Headers.
#include "mcu_conf.h"

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
void Clk_conf( void ) {
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
 * @brief This function configures the LPTMR with a temporization of 100ms.
 * 
 */
void Lpt_conf( void ) {        
    SIM_SCGC5 = 1;  //Clock enabled for LPT module.
    LPTMR0_PSR = ( uint8_t ) 0x28;  //MCGIRCLK selected, and prescaler of 64 -->sync Clk 62.5Khz, count period of 16us.
    LPTMR0_CMR = 6250;  //Compare value.
    
    //Interrupt configuration.
    LPTMR0_CSR = 64;    //Local enable.
    NVIC_ISER |= (1 << 28);  //Global enable.
    
    LPTMR0_CSR |= 1;    //Counter enabled.
}


/**
 * @brief This function configures the I2C0 controller.
 * @note I2C0 is master, in standardad mode with maximum bit rate of 100Kbps, in reality 93.750Kbps.
 */
void I2C0_conf( void ) {
    SIM_SCGC4 = 64; //Clock enabled.
    I2C0_C1 = 0x80; //Module enabled.

    //Bus clk is the clk source for the module.

    //Pin configuration, PTE24 -->SCL, PTE25 -->SDA.
    SIM_SCGC5 |= 8192;  //Port E clock enable.
    PORTE_PCR24 = 1280; //ALT5
    PORTE_PCR25 = 1280; //ALT5

    /*Bit rate configuration, standard mode -->93.750Kbps,
    SCL divider -->128
    MUL -->1
    SDA hold time -->1.4us
    SCL start hold time -->5.1us
    SCL stop hold time -->5.4us
    */
    I2C0_F = 0x1B;

    //Insert timeout timer configuration.
}
