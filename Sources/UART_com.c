/**
 * @file UART_com.c
 * @brief This file contains the definition of the functions and tools related to the UART0 communication.
 * 
 */

//Headers
#include "UART_com.h"

//Functions.
/**
 * @brief This function translates numeric data to the equivalent in ASCII.
 * 
 * @param numeric_data Pointer to numeric data array.  
 * @param ASCII_data Pointer to ASCII data array ( each element is a pointer to string, address to string ).
 * @param data_n_digits Pointer to array to store the number of digits of each numeric data.
 * @param size Number of elements to translate.
 * @return status Status of the operation.
 */
status Numeric_to_ASCII( uint8_t *const numeric_data, uint32_t *const ASCII_data, uint8_t *const data_n_digits, uint8_t size ) {
    //Local data.
    status result = OK;
    uint8_t i, j;
    uint8_t number_digits;  //Number of digits of actual value.
    uint8_t digit;   //Actual digit of data (LSB first).
    uint8_t dummy_data; //Dummy data to store the actual numeric value to convert.

    for ( i = 0; i < size; i++ ) {  //Translating data by data.
        dummy_data = numeric_data[i];
        number_digits = 0;

        do {    //Calculating number of digits of actual data.
            dummy_data /= 10;   //Shifting digits to the right.
            number_digits++;
        } while ( dummy_data > 0 );

        data_n_digits[i] = number_digits;   //Storing the number of digits of actual value.
        dummy_data = numeric_data[i];
        for ( j = number_digits; j > 0; j-- ) { //Obtaining ASCII value of each digit.
            digit = dummy_data % 10;    //Obtaining actual digit of data (LSB first).
            

            switch ( digit ) {  //Translating to ASCII LSB first.
                case 0: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '0'; break;
                case 1: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '1'; break;
                case 2: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '2'; break;
                case 3: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '3'; break;
                case 4: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '4'; break;
                case 5: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '5'; break;
                case 6: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '6'; break;
                case 7: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '7'; break;
                case 8: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '8'; break;
                default: *( ( uint8_t* ) ASCII_data[i] + ( j - 1 ) ) = '9'; break;
            }

            dummy_data /= 10;   //Shifting digits to the right.
        }
    }

    return result;
}

/**
 * @brief This function transmits a data of n bytes by UART. 
 * 
 * @param data Pointer to data array.
 * @param size Number of bytes to transmit.
 * @return status Status of the operation.
 */
status UART_Transmit( uint8_t *const data, uint8_t size ) {
    //local data.
    status result = OK;
    uint8_t i = 0;

    for ( i = 0; i < size; i++ ) { //Transmitting byte by byte.
        UART0_D = data[i];  //Writing byte i to transmit buffer.

        while ( !( UART0_S1 & 0x80 ) || !( UART0_S1 & 0x40 ) ); //Waiting for transmission of byte i, TDRE and TC activated.
        //TDRE and TC are automatically cleared in the next write.
        
        //Insert byte reception verification.
    }

    return result;

}

/**
 * @brief This function communicates with the Tera term terminal for showing the board inclination.
 * @note We are communicating with the OPENSDA MCU via UART, this MCU translates the data to USB.
 * 
 * @param angles Pointer to array of angles of the board
 * @return status Status of the operation
 */
status Terminal_com( volatile float *const angles ) {
    //local data.
    static uint8_t str_in_X[5];    //String to store X inclination.
    static uint8_t str_in_Y[5];    //String to store Y inclination.
    static uint8_t str_in_Z[5];    //String to store Z inclination.
    uint32_t string_add[3] = { ( uint32_t ) str_in_X, ( uint32_t ) str_in_Y, ( uint32_t ) str_in_Z }; //Array of base addresses of each string.
    uint8_t data_digits[3]; //Array of number of digits of each inclination value.
    const uint8_t board_inclination[3] = { ( uint8_t ) angles[0], ( uint8_t ) angles[1], ( uint8_t ) angles[2] };   //Rounded inclination values ( X, Y and Z ).
    const uint8_t str_pre_in[] = "The board inclination values in X, Y and Z are\t";
    const uint8_t str_chars_in[3] = { ',', '[', ']' };
    uint8_t str_post_in[] = "\tdegrees\n";
    status result = OK;

    Numeric_to_ASCII( board_inclination, string_add, data_digits, 3 );   //Translating inclination values to ASCII.
    
    //Transmiting results to terminal.
    UART_Transmit( str_pre_in, sizeof( str_pre_in ) - 1 );
    UART_Transmit( &str_chars_in[1], 1 );
    UART_Transmit( str_in_X, data_digits[0] );
    UART_Transmit( &str_chars_in[0], 1 );
    UART_Transmit( str_in_Y, data_digits[1] );
    UART_Transmit( &str_chars_in[0], 1 );
    UART_Transmit( str_in_Z, data_digits[2] );
    UART_Transmit( &str_chars_in[2], 1 );
    UART_Transmit( str_post_in, sizeof( str_post_in ) - 1 );

    return result;
}