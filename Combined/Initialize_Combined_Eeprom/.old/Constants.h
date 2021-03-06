// Constants.h
// Constant values


// these are the trip button constants

static const byte MODE_TRIPMETER_1 = 0;
static const byte MODE_TRIPMETER_2 = 1;

// these are the mode button constants
static const byte FUNC_KPH = 0;
static const byte FUNC_MPH = 1;
static const byte FUNC_CAL = 2;

static const byte FUNC_CAL_SPD = 0;
static const byte FUNC_CAL_TAC = 1;
static const byte FUNC_CAL_VOLT = 2;
static const byte FUNC_CAL_OIL = 3;
static const byte FUNC_CAL_TEMP = 4;
static const byte FUNC_CAL_FUEL = 5;

// tacho mode constants
static const byte FUNC_TACHO_NOR = 0;
static const byte FUNC_TACHO_CAL = 1;

// tacho types
static const byte TACHO_PETROL = 0;
static const byte TACHO_DIESEL = 1;

// EEPROM has a limited life span; be careful how often we write to it
static const long odometerWriteFrequency = 60000;
// odometer write to eeprom timeout
static const unsigned long odoTimeout = odometerWriteFrequency * 10;

/*
 * Pin assignments with constants, description and connection point on shield
 *
Digital pins

D2	 pinSpeedoInterrupt   speedoInterrupt = 0	 Vehicle Speed sensor
D3	 pinTachoInterrupt	  tachoInterrupt =  1	 Tacho input
D4
D5
D6
D7	 pinLightsOn         Lights on input         
D8	 pinBrigthnessSw     Brightness switch       
D9   pinIgnOn            Ignition on             
D10  pinSpeedoModeButton Speedo Mode Button
D11  pinTripButton       Trip Button
D12  pinTachoModeButton  Tacho Mode Button
D13
D14  pinTachoNeopixel    txdata to tacho neopixel
D15
D16	 pinSpeedoNeopixel   tx data to speedo neopixel
D17
D18
D19
D20  pinSDA
D21  pinSCL

D22	- D53   N/C

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
static const byte pinSpeedoInterrupt = 2;
static const byte speedoInterrupt = 0;

// tacho input interrupt pin
static const byte pinTachoInterrupt = 3;
static const byte tachoInterrupt = 1;

// button inputs
static const byte pinTripButton = 11;		//	trip button
static const byte pinSpeedoModeButton = 10;	//	Speedo Mode Button
static const byte pinTachoModeButton = 12;	//	Tacho Mode Button

// digital inputs from 12V
static const byte pinLightsOn = 7;		//	Lights on input
static const byte pinBrightnessSw = 8;		//	Brightness switch
static const byte pinIgnOn = 9;		//	Ignition on

// Voltmeter

static const byte voltAnalogPin = 12;
// values of resistors in divider network on voltAnalogPin
static const float r1 = 100000.0;
static const float r2 = 10000.0;


// Oil pressure meter

static const byte oilAnalogPin = 13;


// Water Temperature meter

static const byte tempAnalogPin = 14;


// Fuel Level meter

static const byte fuelAnalogPin = 15;




// OUTPUTS will depend on display type, these are for neopixels

// speedometer
static const byte pinSpeedoNeopixel =  16;	//	Speedo neopixel tx

// tachometer
static const byte pinTachoNeopixel = 14;	//	Tacho neopixel tx


// SPEEDO constants

// maximum number of counts for pulseCount
static const byte pulseMaxCount = 100;

// timeout for setting to zero 1.5s
static const int timeoutValue = 1500;


// The SPEEDO LED screen has 4 digits
static const byte numSpeedoDigits = 4;
// The SPEEDO LED arc has 15 leds
static const byte numSpeedoLeds = 15;


// TACHO constants
// The tacho led screen has 4 digits
static const byte numTachoDigits = 4;
// The tacho led arc has 16 leds
static const byte numTachoLeds = 18;
// start the pixel display further around the ring
static const byte tachoPixelOffset = 5;



// ODOMETER constants
// active tripmeter indicator
// this is a small square in the centre of the lcd character
// from datasheet
static const char tripActive = B10100101;



/*
 * defines
 */


#define I2C_ADDRESS_VOLT 0x63
#define I2C_ADDRESS_OIL  0x61
#define I2C_ADDRESS_TEMP 0x62
#define I2C_ADDRESS_FUEL 0x60

#define I2C_ADDRESS_TACHO 0x40

#define I2C_ADDRESS_SPEEDO 0x30

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


#define I2C_ADDRESS_ODO_1602 0x31

// TODO need to change this if want diagnostics as well
#define I2C_ADDRESS_ODO_OLED 0x3C

#define I2C_ADDRESS_OLED 0x3C


#define SPEEDO_CALIBRATE_DIVIDER 100UL


