// Constant values

// update the display every number of milliseconds
static const long updateTime = 1000;

// these are the mode constants
static const byte FUNC_TACHO = 0;
static const byte FUNC_CAL = 1;

// these are the calibrate constants
static const byte FUNC_CAL_CYLINDERS = 0;
static const byte FUNC_CAL_REDLINE = 1;
static const byte FUNC_CAL_SHIFT = 2;

// the mode button pin
static const byte pinModeButton = 5;

// rx pin for all serial displays
static const byte pinSerialRX = 6;

// tachometer
static const byte pinTachoSerialTX = 8;  //  Tacho LED soft serial tx
static const byte pinTachoNeopixel = 9;  //  Tacho neopixel tx

// digital inputs from 12V
static const byte pinLightsOn = 10;		//	Lights on input
static const byte pinBrightnessSw = 3;		//	Brightness switch
static const byte pinIgnOn = 11;		//	Ignition on

// timeout for setting to zero 1.5s
static const int timeoutValue = 1000;

// EEPROM has a limited life span; be careful how often we write to it
static const int eepromWriteFrequency = 5000;

// maximum pulses counted
static int pulseMaxCount = 100;

// The TACHO LED screen has 4 digits
static const byte numTachoDigits = 4;
// The TACHO LED arc has 16 leds
static const byte numTachoLeds = 16;

// the tachometer sensor interrupt

static const byte tachoInterrupt = 2;


