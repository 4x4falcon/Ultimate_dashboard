// Constants.h

// function modes

static const byte FUNC_NORMAL = 0;
static const byte FUNC_CAL = 1;

// this is the serial pin for all displays

static const byte serialRX = 12;

// Voltmeter

static const byte voltAnalogPin = 0;
static const byte voltSerialTX = 6;
static const byte voltDisplayType = 1;
// values of resistors in divider network on voltAnalogPin
static const float r1 = 100000.0;
static const float r2 = 10000.0;


// Oil pressure meter

static const byte oilAnalogPin = 1;
static const byte oilSerialTX = 7;
static const byte oilDisplayType = 0;


// Water Temperature meter

static const byte tempAnalogPin = 2;
static const byte tempSerialTX = 8;
static const byte tempDisplayType = 0;


// Fuel Level meter

static const byte fuelAnalogPin = 3;
static const byte fuelSerialTX = 9;
static const byte fuelDisplayType = 0;

static const byte pinModeButton = 5;

// digital inputs from 12V
static const byte pinLightsOn = 10;		//	Lights on input
static const byte pinBrightnessSw = 3;		//	Brightness switch
static const byte pinIgnOn = 11;		//	Ignition on

// arduino onboard led pin
static const byte pinLed = 13;


// times in ms
static const unsigned long timeUpdate = 2000;


/*
 * defines
 */


#define I2C_ADDRESS_VOLT 0x63
#define I2C_ADDRESS_OIL  0x61
#define I2C_ADDRESS_TEMP 0x62
#define I2C_ADDRESS_FUEL 0x60

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


