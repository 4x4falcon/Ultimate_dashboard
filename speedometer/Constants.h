// Constant values
static const int MODE_SPEEDOMETER = 0;
static const int MODE_ODOMETER = 1;

static const int pinButton = 3;

static const int timeoutValue = 1500;

// EEPROM has a limited life span; be careful how often we write to it
static const int odometerWriteFrequency = 5000;

// The LED screen has 4 digits
static const int numDigits = 4;

// Circumference of wheel used to calculate speed and distance
static const float wheelCircumference = 5.125;

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
