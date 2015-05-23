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

static const int pinTripButton = 3;

// RKS
// the mode button pin
static const int pinModeButton = 4;

static const int timeoutValue = 1500;

// EEPROM has a limited life span; be careful how often we write to it
static const int odometerWriteFrequency = 5000;

// The SPEEDO LED screen has 3 digits
static const int numSpeedoDigits = 3;
// The SPEEDO LED arc has 15 leds
static const int numSpeedoLeds = 15;

// The ODOMETER LCD screen has 8 digits
static const int numOdoDigits = 8;

// The TRIPMETER LCD screen has 4 digits
static const int numTripDigits = 4;




// Below this is probably not needed

// 14-segment display characters
static const uint16_t segmentValues[] = {
  0b0000000000111111, // 0
  0b0000000000000110, // 1
  0b0000000011011011, // 2
  0b0000000010001111, // 3
  0b0000000011100110, // 4
  0b0000000011101101, // 5
  0b0000000011111101, // 6
  0b0000000000000111, // 7
  0b0000000011111111, // 8
  0b0000000011101111, // 9
  0b0000000000000000, // blank
  0b0100000000000000  // decimal
};

static const int BLANK  = 10;
static const int DECIMAL = 11;
