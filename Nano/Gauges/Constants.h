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



