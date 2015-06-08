// Constants.h

// update the display every number of milliseconds
static const long updateTime = 500;

// number of counts to average speed
//static const byte maxCount = 5;

// maximum number of counts for pulseCount
static const byte pulseMaxCount = 100;

// decimal points to use 100 = 2, 1000 = 3, etc
static const long decimals = 100;

// vss sensor interrupt
static const byte speedoInterrupt = 0;

// these are the trip button constants

static const byte MODE_TRIPMETER_1 = 0;
static const byte MODE_TRIPMETER_2 = 1;

// these are the mode button constants
static const byte FUNC_KPH = 0;
static const byte FUNC_MPH = 1;
static const byte FUNC_CAL = 2;

// these are the calibrate constants
static const byte FUNC_CAL_SPD = 0;

// the arduino led pin
static const byte pinLed = 13;

// the vss pin
static const byte pinVss = 2;

// the trip button pin
static const byte pinTripButton = 4;

// the mode button pin
static const byte pinModeButton = 5;

// rx pin for all serial displays
static const byte pinSerialRX = 6;

// the odometer lcd serial pin
static const byte pinOdoSerialTX = 7;

// the speedo led serial pin
static const byte pinSpeedoSerialTX = 8;

// the speedo neopixel pin
static const byte pinSpeedoNeopixel = 9;

// timeout for setting to zero 1.5s
static const int timeoutValue = 1500;

// EEPROM has a limited life span; be careful how often we write to it
static const long odometerWriteFrequency = 60000;

// timeout for updating info in EEPROM
static const unsigned long odoTimeout = odometerWriteFrequency * 10;

// active tripmeter indicator
// this is a small square in the centre of the lcd character
// from datasheet
static const char tripActive = B10100101;

// lights on digital input
static const byte pinLightsOn = 3;

// ignition on digital input
static const byte pinIgnOn = 3;

// The SPEEDO LED screen has 4 digits
static const byte numSpeedoDigits = 4;
// The SPEEDO LED arc has 15 leds
static const byte numSpeedoLeds = 15;


// The Odometer LCD screen has 16 digits by 2 lines
static const byte numOdoDigits = 16;
static const byte numOdoLines = 2;




