/**
 * @file main.c
 * @brief This project uses the onboard IMU MMA8451Q for calculating the board inclination in real time, 
 * using I2C standard communication with a bit rate of 100Kbps, and a LPTMR timer using a temporization of 50ms
 * for calculating the inclination. 
 * 
 * 
 */
//Headers.
#include "derivative.h" /* include peripheral declarations */
#include "mcu_conf.h"


int main( void ){
	//local data
	const uint32_t conf_func_addrs[3] = { ( uint32_t ) Clk_conf, ( uint32_t ) I2C0_conf , ( uint32_t ) Lpt_conf };	
	void ( *conf ) ( void ) = 0;	//Pointer to function.
	uint8_t i = 0;



	//Mcu configuration.
	for ( i = 0; i < 3; i++ ) {
		conf = ( void* ) conf_func_addrs[i];
		conf();
	}
	
	for(;;) {
	}
	
	return 0;
}
