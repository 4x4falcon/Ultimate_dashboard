// Constant values

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

// the tachometer lcd serial pin
static const byte pinTachoSerialTX = 8;

// the tachometer neopixel led
static const byte pinTachoNeopixel = 9;

// ignition on digital input
static const byte pinIgnOn = 3;

// brightness switch
static const byte pinBrightnessSwitch = 11;

// the headlight on pin
static const byte pinLightsOn = 12;

// timeout for setting to zero 1.5s
static const int timeoutValue = 1500;

// EEPROM has a limited life span; be careful how often we write to it
static const int eepromWriteFrequency = 5000;

// maximum pulses counted
static int pulseMaxCount = 100;

// The TACHO LED screen has 4 digits
static const byte numTachoDigits = 4;
// The TACHO LED arc has 15 leds
static const byte numTachoLeds = 16;

// the tachometer sensor interrupt

static const byte tachoInterrupt = 0;


