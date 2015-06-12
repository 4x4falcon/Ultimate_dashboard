//Gauges.ino

/*
*	Gauge reading and display
*
*
*/

// echo to serial for debugging
#define ECHO_SERIAL 1


// include libraries
#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

// includes for helpers
#include <Button.h>
#include <Timer.h>

// local includes
#include "Constants.h"
#include "Variables.h"
#include "Display_Functions.h"
#include "Gauges_Functions.h"
#include "Calibrate_Functions.h"
#include "Version.h"


// temporary storage for the value
int val;

// storage to format the value in
char tempstring[10];


// These are the Arduino pins required to create a software seiral
//  instance. We'll actually only use the TX pin.
//const int softwareTx = 6;
//const int softwareRx = 7;
//SoftwareSerial s7s(softwareRx, softwareTx);

void setup() {
  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromGaugesTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  eepromGaugesVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  eepromGaugesVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.readBlock(eepromGaugesTitleAddress, title);
  versionHigh = EEPROM.readByte(eepromGaugesVersionHighAddress);
  versionLow  = EEPROM.readByte(eepromGaugesVersionLowAddress);

// Voltmeter
  eepromGaugesVoltLowAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesVoltHighAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesVoltLowWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesVoltHighWarnAddress = EEPROM.getAddress(sizeof(int));

  voltLow = EEPROM.readInt(eepromGaugesVoltLowAddress);
  voltHigh = EEPROM.readInt(eepromGaugesVoltHighAddress);
  voltLowWarn = EEPROM.readInt(eepromGaugesVoltLowWarnAddress);
  voltHighWarn = EEPROM.readInt(eepromGaugesVoltHighWarnAddress);


// Oil pressure meter  
  eepromGaugesOilLowAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesOilHighAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesOilLowWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesOilHighWarnAddress = EEPROM.getAddress(sizeof(int));

  oilLow = EEPROM.readInt(eepromGaugesOilLowAddress);
  oilHigh = EEPROM.readInt(eepromGaugesOilHighAddress);
  oilLowWarn = EEPROM.readInt(eepromGaugesOilLowWarnAddress);
  oilHighWarn = EEPROM.readInt(eepromGaugesOilHighWarnAddress);

// Water Temperature meter
  eepromGaugesTempLowAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesTempHighAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesTempLowWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesTempHighWarnAddress = EEPROM.getAddress(sizeof(int));

  tempLow = EEPROM.readInt(eepromGaugesTempLowAddress);
  tempHigh = EEPROM.readInt(eepromGaugesTempHighAddress);
  tempLowWarn = EEPROM.readInt(eepromGaugesTempLowWarnAddress);
  tempHighWarn = EEPROM.readInt(eepromGaugesTempHighWarnAddress);

// Fuel level meter
  eepromGaugesFuelLowAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesFuelHighAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesFuelLowWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesFuelHighWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromGaugesFuelSensorTypeAddress = EEPROM.getAddress(sizeof(int));

  fuelLow = EEPROM.readInt(eepromGaugesFuelLowAddress);
  fuelHigh = EEPROM.readInt(eepromGaugesFuelHighAddress);
  fuelLowWarn = EEPROM.readInt(eepromGaugesFuelLowWarnAddress);
  fuelHighWarn = EEPROM.readInt(eepromGaugesFuelHighWarnAddress);
  fuelSensorType = EEPROM.readByte(eepromGaugesFuelSensorTypeAddress);

  // timer to update the speedo and odometer display every 5000ms (5s)
  timer.every(timeUpdate, updateDisplay);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);
  buttonMode.setLongPressHandler(buttonModeLongPressed);

  
  // set the led on pin 13 to off
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, arduinoLed);

  // set the button and vss pins to be INPUT_PULLUP
  pinMode(pinModeButton, INPUT_PULLUP);

  // set the lights on button to INPUT_PULLUP
  pinMode(pinLightsOn, INPUT_PULLUP);

//  pinMode(voltSerialTX, OUTPUT);
//  digitalWrite(voltSerialTX, LOW);
//  pinMode(oilSerialTX, OUTPUT);
//  pinMode(tempSerialTX, OUTPUT);
//  pinMode(fuelSerialTX, OUTPUT);


/*
 *
 * Setup the volt meter
 *
 */


  volt_serial.begin(9600);
  delay(1);
  volt_serial.write(0x76);    // clear the display
  delay(1);
  volt_serial.print("UOLT");  // Displays -HI- on all digits
  delay(1);
  volt_serial.write(0x77);
  volt_serial.write(0b00000100);  // sets digit 3 decimal on

  setBrightness();

}


void loop() {
  loopTime = millis();

  if (modeFunc != FUNC_CAL)
   {
    timer.update();

    buttonMode.check();

    checkForTimeout();
   }

}

