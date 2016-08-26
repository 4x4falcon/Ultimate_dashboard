// Variables.h

// Current millis updated on each loop
unsigned long loopTime = 0;


// Current function mode
volatile byte modeFunc = FUNC_NORMAL;

// current value
volatile float val = 0.0;

// a buffer for the values
char buffer[50];

// create a voltmeter
//Gauge volt_meter(voltAnalogPin, voltSerialTX, serialRX, voltDisplayType, "FUEL");
SoftwareSerial voltSerial(serialRX, voltSerialTX);

// create an oil pressure gauge
SoftwareSerial oilSerial(serialRX, oilSerialTX);

// create a water temperature gauge
SoftwareSerial tempSerial(serialRX, tempSerialTX);

// create a fuel level guage
SoftwareSerial fuelSerial(serialRX, fuelSerialTX);

// Helper class for handling MODE button presses
//Button buttonMode = Button(pinModeButton, LOW, 3000);

// Helper class for handling MODE button presses
Button buttonBrightness = Button(pinBrightnessSw, LOW, 3000);

volatile byte brightnessBoost = 5;

// Helper class for processing at intervals
Timer timer = Timer();


// arduino onboard led state

volatile byte arduinoLed = LOW;


// EEPROM storage address for title, version high and low

volatile int eepromTitle;
volatile int eepromVersionHigh;
volatile int eepromVersionLow;


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
volatile int eepromFuelSensorTypeAddress = 0;

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
volatile byte voltMin = 0;      // 0 volts
volatile byte voltMax = 16;     // 16 volts
volatile byte voltWarn = 11;    // 11 volts warn when below this
volatile byte voltWarnLow = 1;  // warn for volts low

volatile int oilLower = 0;
volatile int oilUpper = 1023;
volatile byte oilMin = 0;       // 0 psi
volatile byte oilMax = 200;     // 200 psi
volatile byte oilWarn = 20;     // 20 psi warn when below this
volatile byte oilWarnLow = 1;   // warn for oil pressure low


volatile int tempLower = 0;
volatile int tempUpper = 1023;
volatile byte tempMin = 0;      // 0deg C
volatile byte tempMax = 150;    // 150deg C
volatile byte tempWarn = 100;   // 100deg C warn when above this
volatile byte tempWarnLow = 0;  // warn for temp high

volatile int fuelLower = 0;
volatile int fuelUpper = 1023;
volatile byte fuelMin = 0;      // 0%
volatile byte fuelMax = 100;    // 100%
volatile byte fuelWarn = 10;     // warn when below this
volatile byte fuelWarnLow = 1; // warn for fuel low
volatile byte fuelSenderType = 0; // fuel sender type 

						// This is
						// type	empty	full	description
						// 0	70	10	Ford pre 1986
						// 1	10	180	
						//
						//
						// 99


String readString;


