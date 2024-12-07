/**
 * @file main.c
 * @brief This project uses the onboard IMU MMA8451Q for calculating the board inclination in real time, 
 * using I2C standard communication with a bit rate of 100Kbps, and a LPTMR timer using a temporization of 50ms
 * for calculating the inclination. 
 * 
 * 
 */





#include "derivative.h" /* include peripheral declarations */
#include "mcu_conf.h"


int main( void ){
	//local data
	void ( *conf ) ( void ) = 0;	//Pointer to function.
	
	//Mcu configuration.
	conf = Clk_conf;
	conf();
	
	
	for(;;) {
	}
	
	return 0;
}
