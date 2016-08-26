// Constants.h
// Constant values


// these are the trip button constants

static const byte MODE_TRIPMETER_1 = 0;
static const byte MODE_TRIPMETER_2 = 1;

// these are the mode button constants
static const byte FUNC_KPH = 0;
static const byte FUNC_MPH = 1;
static const byte FUNC_CAL = 2;

static const byte FUNC_CAL_SPD = 0;
static const byte FUNC_CAL_TAC = 1;
static const byte FUNC_CAL_VOLT = 2;
static const byte FUNC_CAL_OIL = 3;
static const byte FUNC_CAL_TEMP = 4;
static const byte FUNC_CAL_FUEL = 5;

// tacho mode constants
static const byte FUNC_TACHO_NOR = 0;
static const byte FUNC_TACHO_CAL = 1;

// tacho types
static const byte TACHO_PETROL = 0;
static const byte TACHO_DIESEL = 1;

// EEPROM has a limited life span; be careful how often we write to it
static const long odometerWriteFrequency = 60000;
// odometer write to eeprom timeout
static const unsigned long odoTimeout = odometerWriteFrequency * 10;

/*
 * Pin assignments with constants, description and connection point on shield
 *
2	 pinSpeedoInterrupt	speedoInterrupt = 0	Vehicle Speed sensor		J14 pin 2
3	 pinTachoInterrupt	tachoInterrupt = 1	Tacho input			        J18 pin 2
4 	
5	 pinTripButton		   Trip Button				     J24 pin 1                  gnd J25 pin 1
6	 pinTachoModeButton	 Tacho Mode Button			 J24 pin 2                  gnd J25 pin 2  
7  pinSpeedoModeButton Speedo Mode Button      J24 pin 3                  gnd J25 pin 3
8	 pinLightsOn         Lights on input         J12 pin 1
9	 pinBrigthnessSw     Brightness switch       J12 pin 2
10 pinIgnOn            Ignition on             J12 pin 3

11
12
13

14	pinSerialRX        soft serial rx (not actually used or wired)	J19	pin 1
15	pinOdoSerialTX     Odo LCD soft serial tx       J19 pin 2
16	pinSpeedoSerialTX  Speedo LED soft serial tx    J19 pin 3
17	pinSpeedoNeopixel  Speedo neopixel tx           J19 pin 4
18	pinTachoSerialTX   Tacho LED soft serial tx     J19 pin 5
19	pinTachoNeopixel   Tacho neopixel tx            J19 pin 6

22	voltSerialTX       voltmeter display serial TX           J22 pin 1

24	oilSerialTX        oil pressure meter display serial TX  J22 pin 2

28	tempSerialTX       water temperature display serial TX   J22 pin 3

30	fuelSerialTX       fuel level display serial TX          J22 pin 4

*/

// INPUTS

// vss interrupt pin
static const byte pinSpeedoInterrupt = 2;
static const byte speedoInterrupt = 0;

// tacho input interrupt pin
static const byte pinTachoInterrupt = 3;
static const byte tachoInterrupt = 1;

// button inputs
static const byte pinTripButton = 5;		//	trip button
static const byte pinSpeedoModeButton = 7;	//	Speedo Mode Button
static const byte pinTachoModeButton = 6;	//	Tacho Mode Button

// digital inputs from 12V
static const byte pinLightsOn = 8;		//	Lights on input
static const byte pinBrigthnessSw = 9;		//	Brightness switch
static const byte pinIgnOn = 10;		//	Ignition on

// serial RX for displays not used in hardware
static const byte pinSerialRX = 14;


// Voltmeter

static const byte voltAnalogPin = 0;
// values of resistors in divider network on voltAnalogPin
static const float r1 = 100000.0;
static const float r2 = 10000.0;


// Oil pressure meter

static const byte oilAnalogPin = 1;


// Water Temperature meter

static const byte tempAnalogPin = 2;


// Fuel Level meter

static const byte fuelAnalogPin = 3;




// OUTPUTS will depend on display type, these are for software serial

// these could be used with SPI and then these would become the CS lines

// odometer
static const byte pinOdoSerialTX = 14;		//	Odo LCD soft serial tx

// speedometer
static const byte pinSpeedoSerialTX = 15;	//	Speedo LED soft serial tx
static const byte pinSpeedoNeopixel =  16;	//	Speedo neopixel tx

// tachometer
static const byte pinTachoSerialTX = 36;	//	Tacho LED soft serial tx
static const byte pinTachoNeopixel = 34;	//	Tacho neopixel tx

// voltmeter
static const byte pinVoltSerialTX = 22;		//	voltmeter display serial TX  

// oil pressure meter
static const byte pinOilSerialTX = 24;		//	oil pressure meter display serial TX

static const byte pinTempSerialTX = 30;		//	water temperature display serial TX

static const byte pinFuelSerialTX = 28;		//	fuel level display serial TX



// SPEEDO constants

// maximum number of counts for pulseCount
static const byte pulseMaxCount = 100;

// timeout for setting to zero 1.5s
static const int timeoutValue = 1500;


// The SPEEDO LED screen has 4 digits
static const byte numSpeedoDigits = 4;
// The SPEEDO LED arc has 15 leds
static const byte numSpeedoLeds = 15;


// TACHO constants
// The tacho led screen has 4 digits
static const byte numTachoDigits = 4;
// The tacho led arc has 16 leds
static const byte numTachoLeds = 16;


// ODOMETER constants
// active tripmeter indicator
// this is a small square in the centre of the lcd character
// from datasheet
static const char tripActive = B10100101;






