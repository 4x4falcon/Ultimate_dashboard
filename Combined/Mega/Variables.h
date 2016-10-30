/* 
 * Variables.h
 */

#ifdef MEGA
// Current micros updated on each loop
unsigned long loopTime = 0;

// Display variables
// Helper class for handling MODE button presses
Button buttonBrightness = Button(pinBrightnessSw, BUTTON_PULLUP_INTERNAL, true, 50);

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

// Current calibrate function mode
volatile byte modeSpeedoCalibrate = FUNC_CAL_SPD;


volatile bool startCalibrateSpeed = false;
volatile bool endCalibrateSpeed = false;

volatile bool odoNotSaved = false;
volatile bool tripNotSaved = false;


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

// ODOMETER variables
volatile unsigned long odometerCounter = 0;

// The last time the odometer value was written to memory
volatile unsigned long lastOdometerWrite = 0;

// lights on
volatile byte lightsOn = 0;

// Helper class for handling TRIP button presses

Button buttonTrip = Button(pinTripButton, BUTTON_PULLUP_INTERNAL, true, 50);

// Helper class for handling MODE button presses

Button buttonSpeedoMode = Button(pinSpeedoModeButton, BUTTON_PULLUP_INTERNAL, true, 50);

// Helper class for handling TACHO MODE button presses

Button buttonTachoMode = Button(pinTachoModeButton, BUTTON_PULLUP_INTERNAL, true, 50);

// Helper class for handling GAUGES MODE button presses

Button buttonGaugesMode = Button(pinGaugesModeButton, BUTTON_PULLUP_INTERNAL, true, 50);

bool buttonTripLongPress = false;
bool buttonSpeedoModeLongPress = false;
bool buttonTachoModeLongPress = false;
bool buttonGaugesModeLongPress = false;


// Helper class for processing at intervals
Timer timer = Timer();
Timer timer2 = Timer();

// The distance travelled in one pulse from the vehicle speed sensor in km for miles multiply by .58 in display function
volatile float pulseDistance = 0.0;

volatile unsigned long calibrateCounter = 0;  // this permits pulse number up to 4,294,967,295

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

// for future use to output to bluetooth
volatile int voltVal = 0;
volatile int oilVal = 0;
volatile int tempVal = 0;
volatile int fuelVal = 0;

#ifdef INCLUDE_EGT
volatile int egtVal = 0;
#endif

#ifdef INCLUDE_BOOST
volatile int boostVal = 0;
#endif

// oled diagnostics screen

#ifndef ODOMETER_OLED_128x64
LCD_SSD1306 oledDiagnostic;                  // for SSD1306 OLED module
bool oledAvailable = false;
#endif

#ifdef ODOMETER_1602
byte odoAddress = I2C_ADDRESS_ODO_1602;

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C odo1602(I2C_ADDRESS_ODO_1602, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

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
bool sendBluetooth = false;
#endif

#ifdef INCLUDE_EGT

Adafruit_MAX31855 egtThermocouple(EGT_CS_PIN);

#endif

#endif                                     // ifdef MEGA


// Current speedo function mode
volatile byte modeSpeedoFunc = FUNC_KPH;

// TripMeter 1 value
volatile unsigned long totalTrip_1 = 0;

// TripMeter 2 value
volatile unsigned long totalTrip_2 = 0;

// Current trip mode
volatile byte modeTrip = MODE_TRIPMETER_1;


// external i2c linked eeprom
extEEPROM speedoEeprom(kbits_256, 1, 64, I2C_ADDRESS_EXT_EEPROM);

bool extEepromAvailable = true;

// ext eeprom validation (not yet used but initialized in Initialize_Combined_Eeprom)
union
 {
  unsigned long extEepromValid = 0;
  byte extEepromValidByte[4];
 } extEepromValidate;


// ODO variables
union
 {
  unsigned long totalOdometer = 0;
  byte extEepromTotalOdometer[4];
 } extEepromOdometer;


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
// PPR, redline and shift
// PPR = pulses per revolution

volatile byte tachoPPR = 4;
volatile byte tachoType = TACHO_PETROL;
volatile int tachoRedline = 3300;
volatile int tachoShift = 2800;
volatile int tachoMaximum = 4500;
volatile int tachoCalibrate = 0;


// EEPROM storage addresses
volatile int eepromTitleAddress = 0;
volatile int eepromVersionHigh = 0;
volatile int eepromVersionLow = 0;


// EEPROM storage addresses for odometer and tripmeters
volatile int eepromOdoAddress = 0;
volatile int eepromTrip1Address = 0;
volatile int eepromTrip2Address = 0;


// EEPROM storage addresses for calibration data
// SPEEDO
volatile int eepromSpeedoCalibrateAddress = 0;
volatile int eepromSpeedoModeFuncAddress = 0;


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
volatile int eepromOilInvertedAddress = 0;

// WATER TEMPERATURE METER
volatile int eepromTempLowerAddress = 0;
volatile int eepromTempUpperAddress = 0;
volatile int eepromTempMinAddress = 0;
volatile int eepromTempMaxAddress = 0;
volatile int eepromTempWarnAddress = 0;
volatile int eepromTempWarnLowAddress = 0;
volatile int eepromTempInvertedAddress = 0;
volatile int eepromTempCelciusAddress = 0;

volatile int eepromTempFanOneOnAddress = 0;
volatile int eepromTempFanOneOffAddress = 0;
volatile int eepromTempFanTwoOnAddress = 0;
volatile int eepromTempFanTwoOffAddress = 0;

// FUEL LEVEL METER
volatile int eepromFuelLowerAddress = 0;
volatile int eepromFuelUpperAddress = 0;
volatile int eepromFuelMinAddress = 0;
volatile int eepromFuelMaxAddress = 0;
volatile int eepromFuelWarnAddress = 0;
volatile int eepromFuelWarnLowAddress = 0;
volatile int eepromFuelInvertedAddress = 0;

#ifdef INCLUDE_EGT
// EGT METER
volatile int eepromEgtLowerAddress = 0;
volatile int eepromEgtUpperAddress = 0;
volatile int eepromEgtMinAddress = 0;
volatile int eepromEgtMaxAddress = 0;
volatile int eepromEgtWarnAddress = 0;
volatile int eepromEgtWarnLowAddress = 0;
volatile int eepromEgtInvertedAddress = 0;
volatile int eepromEgtCelciusAddress = 0;
#endif

#ifdef INCLUDE_BOOST
// EGT METER
volatile int eepromBoostLowerAddress = 0;
volatile int eepromBoostUpperAddress = 0;
volatile int eepromBoostMinAddress = 0;
volatile int eepromBoostMaxAddress = 0;
volatile int eepromBoostWarnAddress = 0;
volatile int eepromBoostWarnLowAddress = 0;
volatile int eepromBoostInvertedAddress = 0;
#endif

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
volatile bool voltWarnLow = true;  // warn for volts low
volatile bool voltColonOn = false;


volatile int oilLower = 140;    // suits Ford 73-10R sender (max-min)
volatile int oilUpper = 430;
volatile int oilMin = 0;       // 0 psi
volatile int oilMax = 100;		 // 200 psi
volatile int oilWarn = 50;		 // 20 psi warn when below this
volatile bool oilWarnLow = true;   // warn for oil pressure low
volatile bool oilColonOn = false;
volatile bool oilInverted = true;    // true = sensor is high resistance at low pressure.


volatile int tempLower = 0;
volatile int tempUpper = 1023;
volatile int tempMin = 0;      // 0deg C
volatile int tempMax = 150;		 // 150deg C
volatile int tempWarn = 100;	 // 100deg C warn when above this
volatile int tempFanOneOn = 95;   // 95deg C turn fan on
volatile int tempFanOneOff = 90;  // 90deg C turn fan off must be less than tempFanOn
volatile int tempFanTwoOn = 95;   // 95deg C turn fan on
volatile int tempFanTwoOff = 90;  // 90deg C turn fan off must be less than tempFanOn
volatile bool tempWarnLow = false;  // warn for temp high
volatile bool tempCelcius = true;
volatile bool tempColonOn = false;
volatile bool tempInverted = true;    // true = sensor is high resistance at low temperature.


volatile int fuelLower = 110;   // suits 10R - 180R (empty - full) sender
volatile int fuelUpper = 580;
volatile int fuelMin = 0;      // 0%
volatile int fuelMax = 100;    // 100%
volatile int fuelWarn = 5;     // warn when below this
volatile bool fuelWarnLow = true; // warn for fuel low
volatile bool fuelColonOn = false;
volatile bool fuelInverted = true;    // true = sensor is high resistance at low level.

#ifdef INCLUDE_EGT
volatile int egtLower = 0;
volatile int egtUpper = 1023;
volatile int egtMin = 0;
volatile int egtMax = 1200;
volatile int egtWarn = 600;       // warn when above this
volatile bool egtWarnLow = false; // warn for egt high
volatile bool egtCelcius = true;
volatile bool egtColonOn = false;
volatile bool egtInverted = false;    // true = sensor is high resistance at low level.
#endif

#ifdef INCLUDE_BOOST
volatile int boostLower = 0;
volatile int boostUpper = 1023;
volatile int boostMin = -10;
volatile int boostMax = 45;
volatile int boostWarn = 40;       // warn when above this
volatile bool boostWarnLow = false; // warn for egt high
volatile bool boostColonOn = false;
volatile bool boostInverted = false;    // true = sensor is high resistance at low level.
#endif


volatile byte debugAll = 0;
volatile byte debugSpeedo = 0;
volatile byte debugTacho = 0;
volatile byte debugGauges = 0;

volatile byte demoAll = 0;
volatile byte demoSpeedo = 0;
volatile byte demoTacho = 0;
volatile byte demoGauges = 0;



