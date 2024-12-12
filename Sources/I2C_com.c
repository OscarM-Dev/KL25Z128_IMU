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

    I2C0_C1 |= 0x10;    //Transmit mode -->shift register is output.

    //Insert loop checking if bus is available -->in this case is not necessary.

    I2C0_C1 |= 0x20;    //Controller in master mode and start sent, SCL available in bus.

    for ( uint8_t i = 0; i < size; i++ ) {  //Transmission byte by byte.
        //Insert start of timeout timer.

        I2C0_D = write_inst[i]; //Writing byte i in data register -->starting byte transmission.
        while ( !( I2C0_S & 0x80 ) ) {  //Waiting for transmission of byte i.
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
        while ( !( I2C0_S & 0x80 ) ) {  //Waiting for transmission of byte i.
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

            while ( !( I2C0_S & 0x80 ) );   //Waiting for byte i reception.

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

