/*
 * defines.h
 *
 */

/*
 * this only contains defines that are values within the program
 */


// these are the trip button constants

#define MODE_TRIPMETER_1 0
#define MODE_TRIPMETER_2 1

// these are the mode button constants
#define FUNC_KPH 0
#define FUNC_MPH 1
#define FUNC_CAL 2

#define FUNC_CAL_SPD 0
#define FUNC_CAL_TAC 1
#define FUNC_CAL_VOLT 2
#define FUNC_CAL_OIL 3
#define FUNC_CAL_TEMP 4
#define FUNC_CAL_FUEL 5

// tacho mode constants
#define FUNC_TACHO_NOR 0
#define FUNC_TACHO_CAL 1

// tacho types
#define TACHO_PETROL 0
#define TACHO_DIESEL 1



/*
 * Pin assignments with constants, description and connection point on shield
 *
Digital pins

D2   pinSpeedoInterrupt   speedoInterrupt = 0  Vehicle Speed sensor
D3   pinTachoInterrupt    tachoInterrupt =  1  Tacho input
D4
D5
D6   pinBacklight         1602 lcd backlightbrightness control
D7   pinLightsOn         Lights on input         
D8   pinBrigthnessSw     Brightness switch       
D9   pinIgnOn            Ignition on             
D10  pinSpeedoModeButton Speedo Mode Button
D11  pinTripButton       Trip Button
D12  pinTachoModeButton  Tacho Mode Button
D13
D14  pinTachoNeopixel    txdata to tacho neopixel
D15
D16  pinSpeedoNeopixel   tx data to speedo neopixel
D17
D18
D19
D20  pinSDA
D21  pinSCL

D22 - D53   N/C

Analog pins

A0
A1
A2
A3
A4
A5
A6
A7
A8
A9
A10
A11
A12     pinVoltInput    voltmeter analog input
A13     pinOilInput     oil pressure sender input
A14     pinTempInput    temperature sender input
A15     pinFuelInput    fuel sender input


*/

// INPUTS

// vss interrupt pin
#define pinSpeedoInterrupt 2
#define speedoInterrupt 0

// tacho input interrupt pin
#define pinTachoInterrupt 3
#define tachoInterrupt 1

// button inputs
#define pinTripButton 11                //  trip button
#define pinSpeedoModeButton 10          //  Speedo Mode Button
#define pinTachoModeButton 12           //  Tacho Mode Button

// digital inputs from 12V
#define pinLightsOn 7                   //  Lights on input
#define pinBrightnessSw 8               //  Brightness switch
#define pinIgnOn 9                      //  Ignition on

// digital output to control lcd backlight brightness
#define pinBacklight 6

// Voltmeter

#define voltAnalogPin 12

// Oil pressure meter

#define oilAnalogPin 13


// Water Temperature meter

#define tempAnalogPin 14


// Fuel Level meter

#define fuelAnalogPin 15




// OUTPUTS will depend on display type, these are for neopixels

// speedometer
#define pinSpeedoNeopixel  16  //  Speedo neopixel tx

// tachometer
#define pinTachoNeopixel 14  //  Tacho neopixel tx


// SPEEDO constants

// maximum number of counts for pulseCount
#define pulseMaxCount 100

// timeout for setting to zero this is approximate needs to be tested in actual use
// works fine with tester.ino
#define timeoutValue 5000000UL


// The SPEEDO LED screen has 4 digits
#define numSpeedoDigits 4
// The SPEEDO LED arc has 15 leds
#define numSpeedoLeds 15


// TACHO constants
// The tacho led screen has 4 digits
#define numTachoDigits 4
// The tacho led arc has 16 leds
#define numTachoLeds 16
// start the pixel display further around the ring
#define tachoPixelOffset 5







/*
 * i2c addresses
 */

#define I2C_ADDRESS_VOLT 0x63
#define I2C_ADDRESS_OIL  0x61
#define I2C_ADDRESS_TEMP 0x62
#define I2C_ADDRESS_FUEL 0x60

#define I2C_ADDRESS_TACHO 0x40

#define I2C_ADDRESS_SPEEDO 0x30

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

#define ODO_POSITION_01  0
#define ODO_POSITION_02  45
#define ODO_POSITION_03  ODO_POSITION_02 * 2


/*
 * 16x2 lcd odometer
 */



/*
 * external i2c eeprom
 */

#define I2C_ADDRESS_EXT_EEPROM 0x50
#define EXT_EEPROM_ADDRESS_VALIDATE 0x00
#define EXT_EEPROM_ADDRESS_ODOMETER 0x10


