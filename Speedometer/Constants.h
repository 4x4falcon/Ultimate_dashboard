// Constant values


// RKS
// these are the trip button constants
// MODE_SPEEDOMETER is not needed
//static const int MODE_SPEEDOMETER = 0;
// MODE_ODOMETER is not needed
//static const int MODE_ODOMETER = 1;

static const int MODE_TRIPMETER_1 = 0;
static const int MODE_TRIPMETER_2 = 1;

// RKS
// these are the mode button constants
static const int FUNC_KPH = 0;
static const int FUNC_MPH = 1;
static const int FUNC_CAL = 2;


// RKS
// the trip button pin

static const int pinTripButton = 4;

// RKS
// the mode button pin
static const int pinModeButton = 5;

// rx pin for all serial displays
static const int pinSerialRX = 7;

// the odometer lcd serial pins
static const int pinOdoSerialTX = 6;

// the speedo led serial pins
static const int pinSpeedoSerialTX = 8;

// timeout for setting to zero 1.5s
static const int timeoutValue = 1500;


// EEPROM has a limited life span; be careful how often we write to it
static const int odometerWriteFrequency = 5000;

// The SPEEDO LED screen has 3 digits
static const int numSpeedoDigits = 3;
// The SPEEDO LED arc has 15 leds
static const int numSpeedoLeds = 15;







