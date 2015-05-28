// Current millis updated on each loop
unsigned long loopTime = 0;

// The last time the vss sensor was triggered
volatile unsigned long lastVssTrigger = 0;

// Rotations (rps) per second, set by the speedo ISR
volatile float rps = 0.0;

// Odometer value, set by the speedo ISR
volatile float totalOdometer = 0.0;

// TripMeter 1 value, set by the speedo ISR
volatile float totalTrip_1 = 0.0;

// TripMeter 2 value, set by the speedo ISR
volatile float totalTrip_2 = 0.0;

// Current trip mode
volatile byte modeTrip = MODE_TRIPMETER_1;

// Current function mode
volatile byte modeFunc = FUNC_KPH;

// Current calibrate function mode
volatile byte modeCalibrate = FUNC_CAL_SPD;

volatile byte startCalibrateSpeed;

volatile byte calibrateCounter;

// The last time the odometer value was written to memory
unsigned long lastOdometerWrite = 0;


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


// the led on pin 13 state
volatile byte arduinoLed = LOW;


// whether or not to save the tripmeters and odometer

volatile byte tripNotSaved = 1;
volatile byte odoNotSaved = 1;

