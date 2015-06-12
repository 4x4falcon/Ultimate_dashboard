// Current millis updated on each loop
unsigned long loopTime = 0;

// The last time the tacho sensor was triggered
volatile unsigned long lastTachoTrigger = 0;

// Pulses per second set by the tacho ISR
//volatile float pps = 0.0;

// duration for pulseMaxCount pulses
volatile int duration = 0;

// pulse counter
volatile int pulseCount = 0;

// last time (millis()) that the isr was triggered
volatile unsigned long lastTrigger = 0;

// do the tacho output
volatile byte doTacho = 0;

// Revolutions (rpm) per second
volatile int rpm = 0;

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
volatile int tachoMaximum;
volatile int tachoStep;


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

//EEPROM storage address for tacho maximump

volatile int eepromTachoMaximumAddress;

// The soft serial for the speedometer display
SoftwareSerial tachoSerial(pinSerialRX, pinTachoSerialTX);

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel tachoPixels = Adafruit_NeoPixel(numTachoLeds, pinTachoNeopixel, NEO_GRB + NEO_KHZ800);

// the led on pin 13
volatile byte arduinoLed = LOW;

// the brightness of the pixels initially set to daytime 20
volatile byte pixelBrightness = 20;

// lights on
volatile byte lightsOn = 0;


