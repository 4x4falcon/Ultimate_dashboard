// Current millis updated on each loop
volatile unsigned long loopTime = 0;

// time between pulses
volatile unsigned long duration = 0;

// last speed displayed
//volatile byte lastSpeed = 0;

// speed
volatile int speed = 0;

// pulses counted for duration
volatile byte pulseCount = 0;

// max count pulses reached
volatile byte doSpeed = 0;

// timeout
volatile unsigned long lastTrigger = 0;

// The last time the vss sensor was triggered
volatile unsigned long lastVssTrigger = 0;

// Rotations (rps) per second, set by the speedo ISR
volatile float rps = 0.0;

// Odometer value, set by the speedo ISR
volatile unsigned long totalOdometer = 0UL;

// TripMeter 1 value, set by the speedo ISR
volatile unsigned long totalTrip_1 = 0UL;

// TripMeter 2 value, set by the speedo ISR
volatile unsigned long totalTrip_2 = 0UL;

// Current trip mode
volatile byte modeTrip = MODE_TRIPMETER_1;

// Current function mode
volatile byte modeFunc = FUNC_KPH;

// Current calibrate function mode
volatile byte modeCalibrate = FUNC_CAL_SPD;

volatile byte startCalibrateSpeed;

volatile byte calibrateCounter;

// The last time the odometer value was written to memory
volatile unsigned long lastOdometerWrite = 0;


// Helper class for handling TRIP button presses
Button buttonTrip = Button(pinTripButton, LOW, 3000);

// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);


// Helper class for processing at intervals
Timer timer = Timer();


// EEPROM storage address for title, version high and low

volatile int eepromTitleAddress;
volatile int eepromVersionHighAddress;
volatile int eepromVersionLowAddress;

// EEPROM storage addresses for odometer and tripmeters

volatile int eepromOdoAddress;
volatile int eepromTrip1Address;
volatile int eepromTrip2Address;

// EEPROM storage addresses for mode

volatile byte eepromModeFuncAddress;

// EEPROM storage addresses for calibration data

volatile int eepromSpeedoCalibrateAddress;



// The distance travelled in one pulse from the vehicle speed sensor
volatile float pulseDistance = 0.0;


// The soft serial for the speedometer display
SoftwareSerial speedoSerial(pinSerialRX, pinSpeedoSerialTX);

// The soft serial for the odometer/tripmeter display
SoftwareSerial odoSerial(pinSerialRX,pinOdoSerialTX);


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel speedoPixels = Adafruit_NeoPixel(numSpeedoLeds, pinSpeedoNeopixel, NEO_GRB + NEO_KHZ800);


// the led on pin 13 state
volatile byte arduinoLed = LOW;

// whether or not to save the tripmeters and odometer

volatile byte tripNotSaved = 1;
volatile byte odoNotSaved = 1;

// headlights on
volatile byte lightsOn = 0;

