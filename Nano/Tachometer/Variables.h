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
volatile byte tachoType;
volatile int tachoRedline;
volatile int tachoShift;
volatile int tachoMaximum;
volatile int tachoCalibrate;
volatile int tachoStep;


// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);

// Helper class for processing at intervals
Timer timer = Timer();

// EEPROM storage address for title, version high and low

volatile int eepromTitle;
volatile int eepromVersionHigh;
volatile int eepromVersionLow;

// EEPROM storage addresses for calibration data
// PPR = pulses per revolution

volatile int eepromTachoPPR;
volatile int eepromTachoType;

// EEPROM storage address for redline

volatile int eepromTachoRedline;

// EEPROM storage address for shift light

volatile int eepromTachoShift;

//EEPROM storage address for tacho maximum

volatile int eepromTachoMaximum;

//EEPROM storage address for tacho calibration

volatile int eepromTachoCalibrate;

// The soft serial for the speedometer display
SoftwareSerial tachoSerial(pinSerialRX, pinTachoSerialTX);

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel tachoPixels = Adafruit_NeoPixel(numTachoLeds, pinTachoNeopixel, NEO_GRB + NEO_KHZ800);

// the led on pin 13
volatile byte arduinoLed = LOW;


// Helper class for handling MODE button presses
Button buttonBrightness = Button(pinBrightnessSw, LOW, 3000);

volatile byte brightnessBoost = 5;


// the brightness of the pixels initially set to daytime 15
volatile byte pixelBrightness = 3 * brightnessBoost;

int passCode = 9009;
String readString;



