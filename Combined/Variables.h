// Variables.h

// Current millis updated on each loop
unsigned long loopTime = 0;

// Display variables
// the brightness of the neopixels default daylight
volatile byte pixelBrightness = 12;

// current value of gauge
volatile float val = 0.0;

// a buffer for storing displays
char buffer[20];

// SPEEDO variables
// speed
volatile int speed = 0;

// duration between max counts
volatile unsigned long durationSpeedo = 0;

// pulses counted for duration
volatile byte pulseCount = 0;

// max count pulses reached
volatile byte doSpeed = 0;

// Rotations (rps) per second, set by the speedo ISR
//volatile float rps = 0.0;

// timeout
volatile unsigned long lastTrigger = 0;

// The last time the vss sensor was triggered
volatile unsigned long lastVssTrigger = 0;

// Current speedo function mode
volatile byte modeSpeedoFunc = FUNC_KPH;

// Current calibrate function mode
volatile byte modeSpeedoCalibrate = FUNC_CAL_SPD;

volatile byte startCalibrateSpeed = 0;

volatile byte odoNotSaved = 0;
volatile byte tripNotSaved = 0;


// TACHO variables
// rpm
volatile int rpm = 0;

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
volatile int tachoRedline;
volatile int tachoShift;
volatile int tachoMaximum;



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



// Helper class for handling TRIP button presses
Button buttonTrip = Button(pinTripButton, LOW, 3000);

// Helper class for handling MODE button presses
Button buttonSpeedoMode = Button(pinSpeedoModeButton, LOW, 3000);

// Helper class for handling TACHO MODE button presses
Button buttonTachoMode = Button(pinTachoModeButton, LOW, 3000);

// Helper class for processing at intervals
Timer timer = Timer();
Timer timer2 = Timer();


// EEPROM storage addresses for odometer and tripmeters
volatile int eepromOdoAddress = 0;
volatile int eepromTrip1Address = 0;
volatile int eepromTrip2Address = 0;


// EEPROM storage addresses for calibration data
// SPEEDO
volatile int eepromSpeedoCalibrateAddress;
volatile int eepromModeSpeedoFuncAddress = 0;

// TACHO
volatile int eepromTachoCalibrateAddress;
volatile int eepromTachoTypeAddress = 0;

// VOLTMETER
volatile int eepromVoltLowerAddress = 0;
volatile int eepromVoltUpperAddress = 0;
volatile int eepromVoltMinAddress = 0;
volatile int eepromVoltMaxAddress = 0;
volatile int eepromVoltWarnAddress = 0;
volatile byte eepromVoltWarnLowAddress = 0;

// OIL PRESSURE METER
volatile int eepromOilLowerAddress = 0;
volatile int eepromOilUpperAddress = 0;
volatile int eepromOilMinAddress = 0;
volatile int eepromOilMaxAddress = 0;
volatile int eepromOilWarnAddress = 0;
volatile byte eepromOilWarnLowAddress = 0;

// WATER TEMPERATURE METER
volatile int eepromTempLowerAddress = 0;
volatile int eepromTempUpperAddress = 0;
volatile int eepromTempMinAddress = 0;
volatile int eepromTempMaxAddress = 0;
volatile int eepromTempWarnAddress = 0;
volatile byte eepromTempWarnLowAddress = 0;

// FUEL LEVEL METER
volatile int eepromFuelLowerAddress = 0;
volatile int eepromFuelUpperAddress = 0;
volatile int eepromFuelMinAddress = 0;
volatile int eepromFuelMaxAddress = 0;
volatile int eepromFuelWarnAddress = 0;
volatile byte eepromFuelWarnLowAddress = 0;


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
volatile float pulseDistance = 0;

// the tacho calibration number
volatile float tachoCalibrate = 0;	// for petrol engines number of cylinders
					// for diesel engines 8 if using Dakota Digital converter
					// otherwise number of pulses from alternator W signal per revolution

volatile unsigned long calibrateCounter = 0;	// this permits pulse number up to 4,294,967,295

// Gauge soft serial connections

// The soft serial for the speedometer display
SoftwareSerial speedoSerial(pinSerialRX, pinSpeedoSerialTX);

// The neopixel for the speedo display
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel speedoPixels = Adafruit_NeoPixel(numSpeedoLeds, pinSpeedoNeopixel, NEO_GRB + NEO_KHZ800);


// The soft serial for the odometer/tripmeter display
SoftwareSerial odoSerial(pinSerialRX,pinOdoSerialTX);

// The soft serial for the tachometer display
SoftwareSerial tachoSerial(pinSerialRX,pinTachoSerialTX);

// The neopixel for the tacho display
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel tachoPixels = Adafruit_NeoPixel(numTachoLeds, pinTachoNeopixel, NEO_GRB + NEO_KHZ800);


// The soft serial for the voltmeter display
SoftwareSerial voltSerial(pinSerialRX,pinVoltSerialTX);

// The soft serial for the oil pressure display
SoftwareSerial oilSerial(pinSerialRX,pinOilSerialTX);

// The soft serial for the water temperature display
SoftwareSerial tempSerial(pinSerialRX,pinTempSerialTX);

// The soft serial for the fuel level display
SoftwareSerial fuelSerial(pinSerialRX,pinFuelSerialTX);


// the state of the arduino led on pin 13
volatile byte arduinoLed = 0;

int passCode = 9009;
String readString;

