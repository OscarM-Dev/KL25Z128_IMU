/**
 * @file main.c
 * @brief This project uses the onboard IMU MMA8451Q for calculating the board inclination in real time, 
 * using I2C standard communication with a bit rate of 100Kbps, and a LPTMR timer using a temporization of 100ms
 * for calculating the inclination. 
 * 
 * @note The inclination values are rounded and sent to the PC terminal via UART-USB every 300ms.
 * 
 */
//Headers.
#include "derivative.h" /* include peripheral declarations */
#include "mcu_conf.h"

//Global data.
volatile float board_inclination[3]; //Board inclination in deg from x, y and z plane, check direction axis of IMU in data sheet.

int main( void ){
	//local data
	const uint32_t conf_func_addrs[4] = { ( uint32_t ) Clk_conf, ( uint32_t ) I2C0_conf , ( uint32_t ) UART0_conf, ( uint32_t ) Lpt_conf };	
	void ( *conf ) ( void ) = 0;	//Pointer to function.
	uint8_t i = 0;

	//Mcu configuration.
	for ( i = 0; i < 4; i++ ) {
		conf = ( void* ) conf_func_addrs[i];
		conf();
	}
	
	for(;;) {
	}
	
	return 0;
}
