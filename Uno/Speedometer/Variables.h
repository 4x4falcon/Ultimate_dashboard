// Current millis updated on each loop
volatile unsigned long loopTime = 0;

// time between pulses
volatile unsigned long duration = 0;

// a character output buffer
char buffer[20];

// last speed displayed
//volatile byte lastSpeed = 0;

// speed
volatile int speed = 0;

// pulses counted for duration
volatile byte pulseCount = 0;

// duration between max counts
volatile unsigned long durationSpeedo = 0;

// max count pulses reached
volatile byte doSpeed = 0;

// timeout
volatile unsigned long lastTrigger = 0;

// The last time the vss sensor was triggered
volatile unsigned long lastVssTrigger = 0;

// Odometer value, set by the speedo ISR
volatile unsigned long totalOdometer = 0UL;

// TripMeter 1 value, set by the speedo ISR
volatile unsigned long totalTrip_1 = 0UL;

// TripMeter 2 value, set by the speedo ISR
volatile unsigned long totalTrip_2 = 0UL;

// Current trip mode
volatile byte modeTrip = MODE_TRIPMETER_1;

// Current function mode
volatile byte modeSpeedoFunc = FUNC_KPH;

// Current calibrate function mode
volatile byte modeCalibrate = FUNC_CAL_SPD;

volatile byte startCalibrateSpeed;

volatile int calibrateCounter;

// The last time the odometer value was written to memory
volatile unsigned long lastOdometerWrite = 0;


// Helper class for handling TRIP button presses
Button buttonTrip = Button(pinTripButton, BUTTON_PULLUP_INTERNAL, true, 50);

bool buttonTripLongPress = false;

// Helper class for handling MODE button presses
Button buttonSpeedoMode = Button(pinModeButton, BUTTON_PULLUP_INTERNAL, true, 50);

bool buttonSpeedoModeLongPress = false;


// Helper class for processing at intervals
Timer timer = Timer();

#ifdef ODOMETER_1602
byte odoAddress = I2C_ADDRESS_ODO_1602;

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C odo1602(I2C_ADDRESS_ODO_1602, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

#endif
#ifdef ODOMETER_OLED_128X64
#endif

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel speedoPixels = Adafruit_NeoPixel(numSpeedoLeds + pixelOffset, pinSpeedoNeopixel, NEO_GRB + NEO_KHZ800);

// external i2c linked eeprom
extEEPROM speedoEeprom(kbits_256, 2, 64, 0X50);

// the led on pin 13 state
volatile byte arduinoLed = LOW;

// whether or not to save the tripmeters and odometer

volatile byte tripNotSaved = 1;
volatile byte odoNotSaved = 1;

// Helper class for handling MODE button presses
Button buttonBrightness = Button(pinBrightnessSw, BUTTON_PULLUP_INTERNAL, true, 50);

volatile byte brightnessBoost = 5;

// the brightness of the pixels initially set to daytime 15
volatile byte pixelBrightness = 3 * brightnessBoost;

//
int passCode = 9009;
String readString;

byte debugSpeedo = 0;
byte demoSpeedo = 0;


// EEPROM storage address for title, version high and low

volatile int eepromTitleAddress;
volatile int eepromVersionHighAddress;
volatile int eepromVersionLowAddress;

// EEPROM storage addresses for odometer and tripmeters

volatile int eepromOdoAddress;
volatile int eepromTrip1Address;
volatile int eepromTrip2Address;

// EEPROM storage addresses for mode

volatile byte eepromSpeedoModeFuncAddress;

// EEPROM storage addresses for calibration data

volatile int eepromSpeedoCalibrateAddress;

// EEPROM storage address for debug

volatile int eepromDebugSpeedoAddress;

// EEPROM storage address for demo

volatile int eepromDemoSpeedoAddress;

// The distance travelled in one pulse from the vehicle speed sensor
volatile float pulseDistance = 0.0;
volatile float speedoCalibrate = 0.0;


