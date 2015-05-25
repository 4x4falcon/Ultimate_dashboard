// Constant values

// these are the mode constants
static const byte FUNC_TACHO = 0;
static const byte FUNC_CAL = 1;

// these are the calibrate constants
static const byte FUNC_CAL_CYLINDERS = 0;
static const byte FUNC_CAL_REDLINE = 1;
static const byte FUNC_CAL_SHIFT = 2;

// the mode button pin
static const byte pinModeButton = 6;

// rx pin for all serial displays
static const byte pinSerialRX = 7;

// the tachometer lcd serial pin
static const byte pinTachoSerialTX = 9;

// timeout for setting to zero 1.5s
static const int timeoutValue = 1500;

// EEPROM has a limited life span; be careful how often we write to it
static const int eepromWriteFrequency = 5000;

// The TACHO LED screen has 4 digits
static const byte numTachoDigits = 4;
// The TACHO LED arc has 15 leds
static const byte numTachoLeds = 15;

// the tachometer sensor interrupt

static const byte tachoInterrupt = 1;


