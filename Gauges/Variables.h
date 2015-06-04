// Variables.h

// Current millis updated on each loop
unsigned long loopTime = 0;

// Current function mode
volatile byte modeFunc = FUNC_NORMAL;

// create a voltmeter
//Gauge volt_meter(voltAnalogPin, voltSerialTX, serialRX, voltDisplayType, "FUEL");
SoftwareSerial volt_serial(serialRX, voltSerialTX);
//Gauge volt_meter(voltAnalogPin, volt_serial, voltDisplayType, "Uolt");

// create an oil pressure gauge
//Gauge oil_meter(oilAnalogPin, oilSerialTX, serialRX, oilDisplayType, " OIL");
SoftwareSerial oil_serial(serialRX, oilSerialTX);

// create a water temperature gauge
//Gauge temp_meter(tempAnalogPin, tempSerialTX, serialRX, tempDisplayType, "TEMP");
SoftwareSerial temp_serial(serialRX, tempSerialTX);

// create a fuel level guage
//Gauge fuel_meter(fuelAnalogPin, fuelSerialTX, serialRX, fuelDisplayType, "FUEL");
SoftwareSerial fuel_serial(serialRX, fuelSerialTX);

// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);


// Helper class for processing at intervals
Timer timer = Timer();


// arduino onboard led state

volatile byte arduinoLed = LOW;

// EEPROM storage address for title, version high and low

volatile int eepromGaugesTitleAddress;
volatile int eepromGaugesVersionHighAddress;
volatile int eepromGaugesVersionLowAddress;


// EEPROM storate addresses for voltmeter calibrations

volatile int eepromGaugesVoltLowAddress;
volatile int eepromGaugesVoltHighAddress;
volatile int eepromGaugesVoltLowWarnAddress;
volatile int eepromGaugesVoltHighWarnAddress;

volatile int voltLow;
volatile int voltHigh;
volatile int voltLowWarn;
volatile int voltHighWarn;


// EEPROM storate addresses for oil pressure meter calibrations

volatile int eepromGaugesOilLowAddress;
volatile int eepromGaugesOilHighAddress;
volatile int eepromGaugesOilLowWarnAddress;
volatile int eepromGaugesOilHighWarnAddress;

volatile int oilLow;
volatile int oilHigh;
volatile int oilLowWarn;
volatile int oilHighWarn;


// EEPROM storate addresses for water temperature meter calibrations

volatile int eepromGaugesTempLowAddress;
volatile int eepromGaugesTempHighAddress;
volatile int eepromGaugesTempLowWarnAddress;
volatile int eepromGaugesTempHighWarnAddress;

volatile int tempLow;
volatile int tempHigh;
volatile int tempLowWarn;
volatile int tempHighWarn;


// EEPROM storate addresses for fuel level meter calibrations

volatile int eepromGaugesFuelLowAddress;
volatile int eepromGaugesFuelHighAddress;
volatile int eepromGaugesFuelLowWarnAddress;
volatile int eepromGaugesFuelHighWarnAddress;
volatile int eepromGaugesFuelSensorTypeAddress;

volatile int fuelLow;
volatile int fuelHigh;
volatile int fuelLowWarn;
volatile int fuelHighWarn;
volatile byte fuelSensorType;
						// This is
						// type	empty	full	description
						// 0	70	10	Ford pre 1986
						// 1	10	180	
						//
						//
						// 99                    

