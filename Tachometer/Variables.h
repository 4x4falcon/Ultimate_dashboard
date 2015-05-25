// Current millis updated on each loop
unsigned long loopTime = 0;

// The last time the tacho sensor was triggered
volatile unsigned long lastTachoTrigger = 0;

// Revolutions (rpm) per second, set by the tacho ISR
volatile float rpm = 0.0;

// current mode
volatile byte modeFunc = 0;

// Current calibrate function mode
volatile byte modeCalibrate = FUNC_CAL_REDLINE;

volatile byte startCalibrateRpm;

volatile int calibrateCounter;

// PPR, redline and shift
// PPR = pulses per revolution

volatile byte tachoPPR;
volatile int tachoRedline;
volatile int tachoShift;


// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);

// Helper class for processing at intervals
Timer timer = Timer();

// EEPROM storage address for title, version high and low

volatile int eepromTitleAddress;
volatile int eepromVersionHighAddress;
volatile int eepromVersionLowAddress;

// EEPROM storage addresses for calibration data
// PPR = pulses per revolution

volatile int eepromTachoPPRAddress;

// EEPROM storage address for redline

volatile int eepromTachoRedlineAddress;

// EEPROM storage address for shift light

volatile int eepromTachoShiftAddress;


// The soft serial for the speedometer display
SoftwareSerial tachoSerial(pinSerialRX, pinTachoSerialTX);



