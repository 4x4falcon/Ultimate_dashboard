/*
 * defines.h
 *
 */

/*
 * this only contains defines that are values within the program
 */


/*
 * i2c addresses
 */

#define I2C_ADDRESS_VOLT 0x63
#define I2C_ADDRESS_OIL  0x61
#define I2C_ADDRESS_TEMP 0x62
#define I2C_ADDRESS_FUEL 0x60

#define I2C_ADDRESS_TACHO 0x40

#define I2C_ADDRESS_SPEEDO 0x62

#define I2C_ADDRESS_ODO_1602 0x3F

// TODO need to change this if want diagnostics as well
#define I2C_ADDRESS_ODO_OLED 0x3C

#define I2C_ADDRESS_OLED 0x3C


/*
 * serial seven segment
 */

#define S7S_DIGIT_1_POINT 0b00000001
#define S7S_DIGIT_2_POINT 0b00000010
#define S7S_DIGIT_3_POINT 0b00000100
#define S7S_DIGIT_4_POINT 0b00001000
#define S7S_DIGIT_A_POINT 0b00001111

#define S7S_DIGIT_COLON 0b00010000
#define S7S_DIGIT_APOST 0b00100000

#define DIGIT_1_CONTROL 0x7B
#define DIGIT_2_CONTROL 0x7C
#define DIGIT_3_CONTROL 0x7D
#define DIGIT_4_CONTROL 0x7E



/*
 * speedo
 */

#define SPEEDO_CALIBRATE_DIVIDER 100UL


/* 
 * oled odometer positions 
 */
#ifdef ODOMETER_OLED_128X64

#define ODO_POSITION_01  0
#define ODO_POSITION_02  45
#define ODO_POSITION_03  ODO_POSITION_02 * 2

#endif

/*
 * 16x2 lcd odometer
 */


