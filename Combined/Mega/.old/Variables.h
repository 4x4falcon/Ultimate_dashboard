// Variables.h

// Current micros updated on each loop
unsigned long loopTime = 0;

// Display variables
// Helper class for handling MODE button presses
Button buttonBrightness = Button(pinBrightnessSw, LOW, 3000);

volatile byte brightnessBoost = 5;

// the brightness of the pixels initially set to daytime 15
volatile byte pixelBrightness = 3 * brightnessBoost;

// current value of gauge
volatile float val = 0.0;

// a buffer for storing displays
char buffer[20];

// SPEEDO variables
// speed
volatile int speed = 0;
volatile int previousSpeed = 0;

// duration between max counts
volatile unsigned long durationSpeedo = 0;

// pulses counted for duration
volatile byte pulseCount = 0;

// max count pulses reached
volatile byte doSpeed = 0;

// timeout
//volatile unsigned long lastTrigger = 0;

// The last time the vss sensor was triggered
volatile unsigned long lastVssTrigger = 0;

// Current speedo function mode
volatile byte modeSpeedoFunc = FUNC_KPH;

// Current calibrate function mode
volatile byte modeSpeedoCalibrate = FUNC_CAL_SPD;

volatile byte startCalibrateSpeed = 0;

volatile byte odoNotSaved = 0;
volatile byte tripNotSaved = 0;


// speedo calibration =  pulses per kilometer / SPEEDO_CALIBRATE_DIVIDER
// set in getEepromValues as pulses per kilometer * SPEEDO_CALIBRATE_DIVIDER
volatile float speedoCalibrate = 0;

// TACHO variables
// rpm
volatile int rpm = 0;
volatile int previousRpm = 0;

// duration between max counts
volatile unsigned long durationTacho = 0;

// max count pulses reached
volatile byte doTacho = 0;

// Current speedo function mode
volatile byte modeTachoFunc = FUNC_KPH;


// The last time the tacho sensor was triggered
volatile unsigned long lastTachoTrigger = 0;

// value of the tacho step per neopixel
volatile unsigned int tachoStep = 1000;

// PPR, redline and shift
// PPR = pulses per revolution

volatile byte tachoPPR;
volatile byte tachoType;
volatile int tachoRedline;
volatile int tachoShift;
volatile int tachoMaximum;
volatile int tachoCalibrate;


// ODOMETER variables
// these are a count of pulses for fast math
// distance is determined in display function
// Odometer value, incremented by the ISR
volatile unsigned long totalOdometer = 0;

// TripMeter 1 value
volatile unsigned long totalTrip_1 = 0;

// TripMeter 2 value
volatile unsigned long totalTrip_2 = 0;

// Current trip mode
volatile byte modeTrip = MODE_TRIPMETER_1;

// The last time the odometer value was written to memory
volatile unsigned long lastOdometerWrite = 0;


// lights on
volatile byte lightsOn = 0;


// TODO redo these for new library

// Helper class for handling TRIP button presses
//Button buttonTrip = Button(pinTripButton, LOW, 3000);

Button buttonTrip = Button(pinTripButton, BUTTON_PULLUP_INTERNAL, true, 50);

// Helper class for handling MODE button presses
//Button buttonSpeedoMode = Button(pinSpeedoModeButton, LOW, 3000);

Button buttonSpeedoMode = Button(pinSpeedoModeButton, BUTTON_PULLUP_INTERNAL, true, 50);

// Helper class for handling TACHO MODE button presses
//Button buttonTachoMode = Button(pinTachoModeButton, LOW, 3000);

Button buttonTachoMode = Button(pinTachoModeButton, BUTTON_PULLUP_INTERNAL, true, 50);


bool buttonTripLongPress = false;
bool buttonSpeedoModeLongPress = false;
bool buttonTachoModeLongPress = false;


// Helper class for processing at intervals
Timer timer = Timer();
Timer timer2 = Timer();


// EEPROM storage addresses for odometer and tripmeters
volatile int eepromOdoAddress = 0;
volatile int eepromTrip1Address = 0;
volatile int eepromTrip2Address = 0;


// EEPROM storage addresses for calibration data
// SPEEDO
volatile int eepromSpeedoCalibrateAddress = 0;
volatile int eepromSpeedoModeFuncAddress = 0;

// TACHO
  // This sets up the tacho
  // default is petrol 8 cylinders
  // for petrol engines set to number of cylinders/2 = Pulses per revolution
  // for diesel engines
  // -  if using a Dakota Digital converter then set to 8
  // -  set to number of pulses per revoulution from W terminal of alternator
  // can be calculated from
  // number of altenator pole pairs multiplied by the crank to altenator pulley ratio
  // eg 2 pole pairs
  //    crank pulley 200mm dia
  //    altenator pulley 50mm dia
  //    PPR = pole pairs * (crank pulley/altenator pulley)
  //    PPR = 2 * (200/50)
  //    PPR = 8

volatile int eepromTachoPPRAddress = 0;
volatile int eepromTachoTypeAddress = 0;
volatile int eepromTachoRedlineAddress = 0;
volatile int eepromTachoShiftAddress = 0;
volatile int eepromTachoMaximumAddress = 0;
volatile int eepromTachoCalibrateAddress = 0;

// the tacho calibration number


// VOLTMETER
volatile int eepromVoltLowerAddress = 0;
volatile int eepromVoltUpperAddress = 0;
volatile int eepromVoltMinAddress = 0;
volatile int eepromVoltMaxAddress = 0;
volatile int eepromVoltWarnAddress = 0;
volatile int eepromVoltWarnLowAddress = 0;

// OIL PRESSURE METER
volatile int eepromOilLowerAddress = 0;
volatile int eepromOilUpperAddress = 0;
volatile int eepromOilMinAddress = 0;
volatile int eepromOilMaxAddress = 0;
volatile int eepromOilWarnAddress = 0;
volatile int eepromOilWarnLowAddress = 0;

// WATER TEMPERATURE METER
volatile int eepromTempLowerAddress = 0;
volatile int eepromTempUpperAddress = 0;
volatile int eepromTempMinAddress = 0;
volatile int eepromTempMaxAddress = 0;
volatile int eepromTempWarnAddress = 0;
volatile int eepromTempWarnLowAddress = 0;

// FUEL LEVEL METER
volatile int eepromFuelLowerAddress = 0;
volatile int eepromFuelUpperAddress = 0;
volatile int eepromFuelMinAddress = 0;
volatile int eepromFuelMaxAddress = 0;
volatile int eepromFuelWarnAddress = 0;
volatile int eepromFuelWarnLowAddress = 0;

// debug addresses
volatile int eepromDebugSpeedoAddress = 0;
volatile int eepromDebugTachoAddress = 0;
volatile int eepromDebugGaugesAddress = 0;
volatile int eepromDebugAllAddress = 0;

// demo addresses
volatile int eepromDemoSpeedoAddress = 0;
volatile int eepromDemoTachoAddress = 0;
volatile int eepromDemoGaugesAddress = 0;
volatile int eepromDemoAllAddress = 0;

/* 
 *  meter calibration limits
 *  these are the values from the adc on the analog pins
 *  if inverted (Lower>Higher) then this will work with negative coefficent sensors
 *  Min is minimum of the gauge (this allows for expanded scale meters
 *  Max is the full scale of the gauge
 *  Warn is the warning level trigger
 *  WarnLow determines if to check for below Warn (Warn=1) or above Warn (Warn=0)
 *  
 */

volatile int voltLower = 0;
volatile int voltUpper = 1023;
volatile int voltMin = 0;      // 0 volts
volatile int voltMax = 16;		 // 16 volts
volatile int voltWarn = 11;		 // 11 volts warn when below this
volatile byte voltWarnLow = 1;  // warn for volts low
volatile int oilLower = 0;
volatile int oilUpper = 1023;
volatile int oilMin = 0;       // 0 psi
volatile int oilMax = 200;		 // 200 psi
volatile int oilWarn = 20;		 // 20 psi warn when below this
volatile byte oilWarnLow = 1;   // warn for oil pressure low
volatile int tempLower = 0;
volatile int tempUpper = 1023;
volatile int tempMin = 0;      // 0deg C
volatile int tempMax = 150;		 // 150deg C
volatile int tempWarn = 100;	 // 100deg C warn when above this
volatile byte tempWarnLow = 0;  // warn for temp high
volatile int fuelLower = 0;
volatile int fuelUpper = 1023;
volatile int fuelMin = 0;      // 0%
volatile int fuelMax = 100;    // 100%
volatile int fuelWarn = 5;     // warn when below this
volatile byte fuelWarnLow = 1; // warn for fuel low


// The distance travelled in one pulse from the vehicle speed sensor in km for miles multiply by .58 in display function
volatile float pulseDistance = 0.0;

volatile unsigned long calibrateCounter = 0;	// this permits pulse number up to 4,294,967,295

// The neopixel for the speedo display
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel speedoPixels = Adafruit_NeoPixel(numSpeedoLeds, pinSpeedoNeopixel, NEO_GRB + NEO_KHZ800);

// The neopixel for the tacho display
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel tachoPixels = Adafruit_NeoPixel(numTachoLeds + tachoPixelOffset, pinTachoNeopixel, NEO_GRB + NEO_KHZ800);

// the state of the arduino led on pin 13
volatile byte arduinoLed = 0;

int passCode = 9009;
String readString;

volatile byte debugAll = 0;
volatile byte debugSpeedo = 0;
volatile byte debugTacho = 0;
volatile byte debugGauges = 0;

volatile byte demoAll = 0;
volatile byte demoSpeedo = 0;
volatile byte demoTacho = 0;
volatile byte demoGauges = 0;


// for future use to output to bluetooth
int voltVal = 0;
int oilVal = 0;
int tempVal = 0;
int fuelVal = 0;

// oled diagnostics screen

#ifndef ODOMETER_OLED_128x64
LCD_SSD1306 oledDiagnostic;                  // for SSD1306 OLED module
bool oledAvailable = false;
#endif

#ifdef ODOMETER_1602
byte odoAddress = I2C_ADDRESS_ODO_1602;
#endif

#ifdef ODOMETER_OLED_128x64
byte odoAddress = I2C_ADDRESS_ODO_OLED;
LCD_SSD1306 oledOdometer;                  // for SSD1306 OLED module
#endif

#ifdef INCLUDE_AHRS
bool magnetometerAvailable = false;
#endif

#ifdef INCLUDE_BLUETOOTH
bool bluetoothAvailable = false;
#endif


