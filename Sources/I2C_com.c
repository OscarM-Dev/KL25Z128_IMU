/**
 * @file I2C_com.c
 * @brief This file contains the definition of the functions for the I2C communication.
 * 
 */

//Headers
#include "I2C_com.h"

//Functions.
/**
 * @brief This function transmits a given write instruction of n bytes.
 * 
 * @param write_inst Pointer to array with write instruction to send.
 * @param size Number of bytes of the given write instruction.
 * @return status Status of the operation.
 */
status I2C_write( uint8_t *const write_inst, uint8_t size ) {
    //local data.
    status result = OK;
    uint8_t i = 0;

    I2C0_C1 |= 0x10;    //Transmit mode -->shift register is output.

    //Insert loop checking if bus is available -->in this case is not necessary.

    I2C0_C1 |= 0x20;    //Controller in master mode and start sent, SCL available in bus.

    for ( i = 0; i < size; i++ ) {  //Transmission byte by byte.
        //Insert start of timeout timer.

        I2C0_D = write_inst[i]; //Writing byte i in data register -->starting byte transmission.
        while ( ( !( I2C0_S & 0x80 ) ) || ( !( I2C0_S & 0x02 ) ) ){  //Waiting for transmission of byte i, until both TCF and IICIF are activated.
            //Insert if checking arbitration lost flag and bus blocked flag.
        }

        //Analizing if byte was transmitted correctly.
        //Insert if checking if bus is blocked.
        //Insert stop of timeout timer.
        //Restart timeout timer.

        //Insert if checking if arbitration was lost.

        I2C0_S |= 0x02; //Clear flag IICIF, TCF is cleared automatically in the next transmission.

        //Checking ACK of byte i.
        if ( I2C0_S & 0x01 ) { //NACK detected.
            //Insert for of retransmission attempt.
            //Insert if checking numer of loops of for.

            //NACK flag is not necessary to clear.
            I2C0_C1 &= ~0x20;   //Controller in slave mode and stop sent, end of communication with slave.
            result = ERROR;
            break; 
        }
    }

    if ( result == OK ) {   //Instruction transmited correctly.
        I2C0_C1 &= ~0x20;   //Controller in slave mode and stop sent, end of communication with slave.
    }
    
    return result;
}

/**
 * @brief This function transmits a given read instruction and stores the answer of the slave.
 * @note The read instruction follows the repeated start format.
 * 
 * @param read_inst Pointer to array with read instruction to send.
 * @param answer_buffer Pointer to buffer (array) to store instruction answer.
 * @param size Number of bytes to read.
 * @return status Status of the operation.
 */
status I2C_read( uint8_t *const read_inst, uint8_t *const answer_buffer, uint8_t size ) {
    //local data.
    uint8_t i = 0;
    status result = OK;

    I2C0_C1 |= 0x10;    //Transmit mode -->shift register is output.

    //Insert loop checking if bus is available -->in this case is not necessary.

    I2C0_C1 |= 0x20;    //Controller in master mode and start sent, SCL available in bus.

    for ( i = 0; i < 3; i++ ) {  //Transmission byte by byte.
        if ( i == 2 ) { //Last iteration.
            I2C0_C1 |= 0x04;    //Repeated start sent.
        }        
        
        //Insert start of timeout timer.

        I2C0_D = read_inst[i]; //Writing byte i in data register -->starting byte transmission.
        while ( ( !( I2C0_S & 0x80 ) ) || ( !( I2C0_S & 0x02 ) ) ) {  //Waiting for transmission of byte i, until both TCF and IICIF are activated.
            //Insert if checking arbitration lost flag and bus blocked flag.
        }

        //Analizing if byte was transmitted correctly.
        //Insert if checking if bus is blocked.
        //Insert stop of timeout timer.
        //Restart timeout timer.

        //Insert if checking if arbitration was lost.

        I2C0_S |= 0x02; //Clear flag IICIF, TCF is cleared automatically in the next transmission.

        //Checking ACK of byte i.
        if ( I2C0_S & 0x01 ) { //NACK detected.
            //Insert for of retransmission attempt.
            //Insert if checking numer of loops of for.

            //NACK flag is not necessary to clear.
            I2C0_C1 &= ~0x20;   //Controller in slave mode and stop sent, end of communication with slave.
            result = ERROR;
            break; 
        }
    }

    if ( result == OK ) {   //Instruction transmited correctly, prepare for receiving answer.
        I2C0_C1 &= ~0x18;   //Receive mode -->shift register is input, clock stretch generated, bus in pause. Also automatica ACK transmit for each byte received.
        
        answer_buffer[0] = I2C0_D;  //Dummy read for initializing data reception, clock stretch deactivated, bus running.

        for ( i = 0; i < size; i++ ) {  //Answer reception, byte by byte.
            if ( i == size - 1 ) {  //Final iteration, last byte to receive.
                I2C0_C1 |= 0x08;    //Automatic NACK transmit for received byte.
            }

            while ( ( !( I2C0_S & 0x80 ) ) || ( !( I2C0_S & 0x02 ) ) );   //Waiting for byte i reception, until both TCF and IICIF are activated.

            //Byte i received, ACK or NACK transmited, and clock stretch generated, bus in pause.
            I2C0_S |= 0x02; //Clear flag IICIF, TCF is cleared automatically in the next reception.

            if ( i == size - 1 ) {  //Final iteration, last byte received.
                I2C0_C1 &= ~0x20;   //Controller in slave mode and stop sent, end of communication with slave.
            }

            answer_buffer[i] = I2C0_D;  //Storing byte i received and initializing reception of next byte, clock stretch deactivated, bus running.
        }        
    }
    
    return result;
}

/**
 * @brief This function comunicates with the IMU MMA8451Q for calculating the inclination of the board in deg from the x, y an z planes.
 * @note Once the IMU is activated you need to wait at least 100ms for comunicating with it.
 * @note The max SDA holdtime value supported by the IMU is 2us.
 * @note The 3 axis outputs are of 14bits 2´s complement, which measure the aceleration in G of the axis in real time with a frequency of 800Hz.
 * @note The G output of each axis is divided in 2 registers with the MSB and LSB part.
 * @note By default the acelaration measurement range is 2G, so G values of each axis will range -2g to 2g.
 * @note Remember that the G outputs are in terms of increments (raw values), you will need to convert them in order to know the actual G value of the axis.
 * 
 * @note Convertion notes; 
 *  -In the default configuration with a measurement range of 2G, with 14 bits 2´s complement, 
 *      -You have a range of values from -8192 (-2G) to 8191 (2G).
 *      -Around 8192 increments in both ways.
 *      -In this case 4196 increments in both ways is equal to 1G.
 *      -Each increment in both ways is equal to .25mG. 
 * 
 * @note In this case the calculus of the inclination will be taking the aceleration magnitude (G) of each axis but all in increments terms.
 * 
 * @param angle Pointer to array to store the inclination values of each axis.
 * @return status Status of the operation.
 */
status IMU_com( volatile float *const angle ) {
    //local data
    static uint8_t first_call = 1;
    static uint8_t IMU_reception_buffer[32];    //Reception buffer for answers.
    static uint16_t IMU_axis_magnitudes[3];     //Array for x, y and z axis aceleration magnitudes (increments) of the actual measurement.

    //Instructions for slave.
    uint8_t IMU_write_activation[3] = { IMU_W_CONTROL, IMU_ACT_ADDR, 0x01 };   //Write instruction to put IMU in active mode.
    uint8_t IMU_read_activation[3] = { IMU_W_CONTROL, IMU_ACT_ADDR, IMU_R_CONTROL };   //Read instruction to read activation register.    
    uint8_t IMU_read_outputs[3] = { IMU_W_CONTROL, IMU_OUTX_MSB_ADDR, IMU_R_CONTROL };  //Read instruction for IMU 3 axis outputs.
    status result = OK;
    uint8_t i = 0;
    int16_t negative_output;    //Dummy variable for storing a negative output in 16 bits 2´s complement.
    
    if ( first_call ) { //Only the IMU is activated.
        I2C_write( IMU_write_activation, 3 );
        first_call = 0;
    }

    else {  //Calculating inclination, always the shortest angle from 0.
        I2C_read( IMU_read_outputs, IMU_reception_buffer, 6 );  //Reading the axises aceleration outputs.

        for ( i = 0; i < 3; i++ ) { //Obtaning magnitudes values of each axis.
            IMU_axis_magnitudes[i] = ( ( ( uint16_t ) IMU_reception_buffer[i + i] << 8 ) | ( IMU_reception_buffer[i + i + 1] ) ) >> 2;  //Joining the 14 bits of each axis aceleration output.

            if ( ( IMU_axis_magnitudes[i] >> 13 ) == 1 ) { //Output has negative sign bit, negative axis aceleration output.
                IMU_axis_magnitudes[i] |= ( uint16_t ) -8192;    //Transforming data from 14 bits 2´s complement to 16 bits 2´s complement.
                negative_output = ( int16_t ) IMU_axis_magnitudes[i];   //Storing 16 bits 2´s complement data as int16.
                IMU_axis_magnitudes[i] = ( uint16_t ) ( negative_output * -1 ); //Obtaining magnitude value.
            }   //If output is positive (sign bit == 0), directly the output is the magnitude value, it doesn´t require a transformation to 16 bits.          
        }

        angle[0] = 90 - ( atan2( IMU_axis_magnitudes[2], IMU_axis_magnitudes[1] ) * ( 18000 / 314 ) );  //Inclination from X plane.
        angle[1] = 90 - ( atan2( IMU_axis_magnitudes[2], IMU_axis_magnitudes[0] ) * ( 18000 / 314 ) );  //Inclination from Y plane.
        angle[2] = 90 - ( atan2( IMU_axis_magnitudes[1], IMU_axis_magnitudes[0] ) * ( 18000 / 314 ) );  //Inclination form Z plane.
    }


    return result;
}
