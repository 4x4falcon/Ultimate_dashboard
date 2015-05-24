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

// tacho types
static const byte TACHO_PETROL = 0;
static const byte TACHO_DIESEL = 1;


// the trip button pin
static const byte pinTripButton = 4;

// the mode button pin
static const byte pinModeButton = 5;

// rx pin for all serial displays
static const byte pinSerialRX = 7;

// the odometer lcd serial pin
static const byte pinOdoSerialTX = 6;

// the speedo led serial pin
static const byte pinSpeedoSerialTX = 8;

// the tacho led serial pin
static const byte pinTachoSerialTX = 13;

// VOLTMETER
// the voltmeter display serial pin
static const byte pinVoltSerialTX = 12;
// the voltmeter analog pin
static const byte pinVoltAnalog = 0;


// Oil pressure
// the oil pressure display serial pin
static const byte pinOilSerialTX = 12;
// the oil pressure analog pin
static const byte pinOilAnalog = 0;

// Water Temperature
// the water temperature display serial pin
static const byte pinTempSerialTX = 12;
// the water temperature analog pin
static const byte pinTempAnalog = 0;

// Fuel Level
// the fuel level display serial pin
static const byte pinFuelSerialTX = 12;
// the fuel level analog pin
static const byte pinFuelAnalog = 0;




// timeout for setting to zero 1.5s
static const int timeoutValue = 1500;


// EEPROM has a limited life span; be careful how often we write to it
static const int odometerWriteFrequency = 5000;

// The SPEEDO LED screen has 3 digits
static const byte numSpeedoDigits = 3;
// The SPEEDO LED arc has 15 leds
static const byte numSpeedoLeds = 15;

// active tripmeter indicator
// this is a small square in the centre of the lcd character
// from datasheet
static const char tripActive = B10100101;






