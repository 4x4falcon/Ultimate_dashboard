// Current millis updated on each loop
unsigned long loopTime = 0;

// The last time the hall effect sensor was triggered
volatile unsigned long lastTrigger = 0;

// Rotations per second, set by the ISR
volatile float rps = 0.0;

// Pulses per km or mile, set by the calibration function and stored in EEPROM
// use a float as this is a calculated number
volatile float ppd = 0.0;

// Odometer value, set by the ISR
volatile float totalMiles = 0.0;

// TripMeter 1 value
volatile float totalTrip_1 = 0.0;

// TripMeter 2 value
volatile float totalTrip_2 = 0.0;

// Current trip mode
int modeTrip = MODE_TRIPMETER_1;

// Current function mode
int modeFunc = FUNC_KPH;

// The last time the odometer value was written to memory
unsigned long lastOdometerWrite = 0;

// Used to control the LED display
Adafruit_AlphaNum4 alpha = Adafruit_AlphaNum4();

// Helper class for handling TRIP button presses
Button buttonTrip = Button(pinTripButton, LOW, 3000);

// Helper class for handling TRIP button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);

// Helper class for processing at intervals
Timer timer = Timer();

// EEPROM storage addresses for odometer and tripmeters

volatile int eepromOdoAddress = 0;
volatile int eepromTrip1Address = 0;
volatile int eepromTrip2Address = 0;
volatile int eepromCalibrateAddress = 0;


// The distance travelled in one pulse from the vehicle speed sensor
volatile float pulseDistance = 0;


