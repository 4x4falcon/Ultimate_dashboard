// Current millis updated on each loop
unsigned long loopTime = 0;

// The last time the vss sensor was triggered
volatile unsigned long lastVssTrigger = 0;

// The last time the tacho sensor was triggered
volatile unsigned long lastTachoTrigger = 0;

// Rotations (pps) per second, set by the speedo ISR
volatile float rps = 0.0;

// rpm, set by the tacho ISR
volatile unsigned long rpm = 0;

// Odometer value, set by the ISR
volatile float totalOdometer = 0.0;

// TripMeter 1 value
volatile float totalTrip_1 = 0.0;

// TripMeter 2 value
volatile float totalTrip_2 = 0.0;

// Current trip mode
byte modeTrip = MODE_TRIPMETER_1;

// Current function mode
byte modeFunc = FUNC_KPH;

// Current calibrate function mode
byte modeCalibrate = FUNC_CAL_SPD;

byte startCalibrateSpeed = 0;

// The last time the odometer value was written to memory
unsigned long lastOdometerWrite = 0;


// Helper class for handling TRIP button presses
Button buttonTrip = Button(pinTripButton, LOW, 3000);

// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);


// Helper class for processing at intervals
Timer timer = Timer();
Timer timer2 = Timer();


// EEPROM storage addresses for odometer and tripmeters

volatile int eepromOdoAddress = 0;
volatile int eepromTrip1Address = 0;
volatile int eepromTrip2Address = 0;


// EEPROM storage addresses for calibration data

volatile int eepromCalibrateAddress;
volatile int eepromTachoCalibrateAddress;
volatile int eepromTachoTypeAddress = 0;
volatile int eepromModeFuncAddress = 0;

volatile int eepromVoltLowerAddress = 0;
volatile int eepromVoltUpperAddress = 0;
volatile int eepromVoltMaxAddress = 0;
volatile int eepromVoltWarnAddress = 0;
  
volatile int eepromOilLowerAddress = 0;
volatile int eepromOilUpperAddress = 0;
volatile int eepromOilMaxAddress = 0;
volatile int eepromOilWarnAddress = 0;
  
volatile int eepromTempLowerAddress = 0;
volatile int eepromTempUpperAddress = 0;
volatile int eepromTempMaxAddress = 0;
volatile int eepromTempWarnAddress = 0;
  
volatile int eepromFuelLowerAddress = 0;
volatile int eepromFuelUpperAddress = 0;
volatile int eepromFuelMaxAddress = 0;
volatile int eepromFuelWarnAddress = 0;


// meter calibration limits
volatile int voltLower = 0;
volatile int voltUpper = 1023;
volatile int voltMax = 16;        // 16 volts
volatile int voltWarn = 11;       // 11 volts warn when below this
volatile int oilLower = 0;
volatile int oilUpper = 1023;
volatile int oilMax = 200;        // 200 psi
volatile int oilWarn = 20;     // 20 psi warn when below this
volatile int tempLower = 0;
volatile int tempUpper = 1023;
volatile int tempMax = 150;      // 150deg C
volatile int tempWarn = 100;  // 100deg C warn when above this
volatile int fuelLower = 0;
volatile int fuelUpper = 1023;
                                 // no max for fuel as it is displayed as percentage
volatile int fuelWarn = 5;    // warn when below this


// The distance travelled in one pulse from the vehicle speed sensor
volatile float pulseDistance = 0;

// the tacho calibration number
volatile float tachoCalibrate = 0;
                                                // for petrol engines number of cylinders
                                                // for diesel engines 8 if using Dakota Digital converter
                                                // otherwise number of pulses from alternator W signal per revolution

volatile unsigned long calibrateCounter = 0;    // this permits pulse number up to 4,294,967,295

// Gauge soft serial connections

// The soft serial for the speedometer display
SoftwareSerial speedoSerial(pinSerialRX, pinSpeedoSerialTX);

// The soft serial for the odometer/tripmeter display
SoftwareSerial odoSerial(pinSerialRX,pinOdoSerialTX);

// The soft serial for the tachometer display
SoftwareSerial tachoSerial(pinSerialRX,pinTachoSerialTX);

// The soft serial for the voltmeter display
SoftwareSerial voltSerial(pinSerialRX,pinVoltSerialTX);

// The soft serial for the oil pressure display
SoftwareSerial oilSerial(pinSerialRX,pinOilSerialTX);

// The soft serial for the water temperature display
SoftwareSerial tempSerial(pinSerialRX,pinTempSerialTX);

// The soft serial for the fuel level display
SoftwareSerial fuelSerial(pinSerialRX,pinFuelSerialTX);


