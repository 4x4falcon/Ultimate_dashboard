//Gauges.ino

/*
*	Gauge reading and display
*
* Using Arduino Nano
*/

// echo to serial for debugging

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
#include "Functions.h"


// These are the Arduino pins required to create a software seiral
//  instance. We'll actually only use the TX pin.
//const int softwareTx = 6;
//const int softwareRx = 7;
//SoftwareSerial s7s(softwareRx, softwareTx);

void setup() {
  Serial.begin(9600);

// Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitle = EEPROM.getAddress(sizeof(char)*sizeof(title));
  eepromVersionHigh = EEPROM.getAddress(sizeof(byte));
  eepromVersionLow = EEPROM.getAddress(sizeof(byte));

  EEPROM.readBlock(eepromTitle, title);
  versionHigh = EEPROM.readByte(eepromVersionHigh);
  versionLow  = EEPROM.readByte(eepromVersionLow);

// Voltmeter
  eepromVoltLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromVoltMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromVoltWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromVoltWarnLowAddress = EEPROM.getAddress(sizeof(byte));

  voltLower = EEPROM.readInt(eepromVoltLowerAddress);
  voltUpper = EEPROM.readInt(eepromVoltUpperAddress);
  voltMin = EEPROM.readInt(eepromVoltMinAddress);
  voltMax = EEPROM.readInt(eepromVoltMaxAddress);
  
  voltWarn = EEPROM.readInt(eepromVoltWarnAddress);
  voltWarnLow = EEPROM.readByte(eepromVoltWarnLowAddress);


// Oil pressure meter  
  eepromOilLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromOilUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromOilMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromOilMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromOilWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromOilWarnLowAddress = EEPROM.getAddress(sizeof(byte));

  oilLower = EEPROM.readInt(eepromOilLowerAddress);
  oilUpper = EEPROM.readInt(eepromOilUpperAddress);
  oilMin = EEPROM.readInt(eepromOilMinAddress);
  oilMax = EEPROM.readInt(eepromOilMaxAddress);
  
  oilWarn = EEPROM.readInt(eepromOilWarnAddress);
  oilWarnLow = EEPROM.readByte(eepromOilWarnLowAddress);


// Water Temperature meter
  eepromTempLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromTempUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromTempMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempWarnLowAddress = EEPROM.getAddress(sizeof(byte));

  tempLower = EEPROM.readInt(eepromTempLowerAddress);
  tempUpper = EEPROM.readInt(eepromTempUpperAddress);
  tempMin = EEPROM.readInt(eepromTempMinAddress);
  tempMax = EEPROM.readInt(eepromTempMaxAddress);
  
  tempWarn = EEPROM.readInt(eepromTempWarnAddress);
  tempWarnLow = EEPROM.readByte(eepromTempWarnLowAddress);


// Fuel level meter
  eepromFuelLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelSensorTypeAddress = EEPROM.getAddress(sizeof(byte));

  fuelLower = EEPROM.readInt(eepromFuelLowerAddress);
  fuelUpper = EEPROM.readInt(eepromFuelUpperAddress);
  fuelMin = EEPROM.readInt(eepromFuelMinAddress);
  fuelMax = EEPROM.readInt(eepromFuelMaxAddress);
  
  fuelWarn = EEPROM.readInt(eepromFuelWarnAddress);
  fuelWarnLow = EEPROM.readByte(eepromFuelWarnLowAddress);
  fuelSenderType = EEPROM.readByte(eepromFuelSensorTypeAddress);


  eepromGaugesDebugAddress = EEPROM.getAddress(sizeof(byte));
  debug = EEPROM.readByte(eepromGaugesDebugAddress);

  // timer to update the gauges display every 5000ms (5s)
  timer.every(timeUpdate, updateDisplay);

  // Set up mode button handlers
//  buttonMode.setPressHandler(buttonModePressed);
//  buttonMode.setLongPressHandler(buttonModeLongPressed);

  buttonBrightness.setPressHandler(buttonBrightnessPressed);
  buttonBrightness.setLongPressHandler(buttonBrightnessLongPressed);
  
  // set the led on pin 13 to off
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, !arduinoLed);

  // set the button pins to be INPUT_PULLUP
//  pinMode(pinModeButton, INPUT_PULLUP);
  pinMode(pinBrightnessSw, INPUT_PULLUP);


  
  // set the lights on button to INPUT_PULLUP
  pinMode(pinLightsOn, INPUT_PULLUP);

  pinMode(voltSerialTX, OUTPUT);
  pinMode(oilSerialTX, OUTPUT);
  pinMode(tempSerialTX, OUTPUT);
  pinMode(fuelSerialTX, OUTPUT);

// Setup the volt meter

  voltSerial.begin(9600);
  oilSerial.begin(9600);
  tempSerial.begin(9600);
  fuelSerial.begin(9600);

  setBrightness();

  delay(100);
  voltSerial.write(0x76);    // clear the display
  delay(1);
  voltSerial.print("UOLT");  // Displays VOLT on all digits
  delay(1);
  voltSerial.write(0x77);
  voltSerial.write(0b00000100);  // sets digit 3 decimal on

  oilSerial.write(0x76);    // clear the display
  delay(1);
  oilSerial.print("OIL ");  // Displays OIL on all digits
  delay(1);
  oilSerial.write(0x77);
  oilSerial.write(0b00000100);  // sets digit 3 decimal on

  tempSerial.write(0x76);    // clear the display
  delay(1);
  tempSerial.print("TENP");  // Displays TEMP on all digits
  delay(1);
  tempSerial.write(0x77);
  tempSerial.write(0b00000100);  // sets digit 3 decimal on

  fuelSerial.write(0x76);    // clear the display
  delay(1);
  fuelSerial.print("FUEL");  // Displays FUEL on all digits
  delay(1);
  fuelSerial.write(0x77);
  fuelSerial.write(0b00000100);  // sets digit 3 decimal on

  delay(1000);

//  setBrightness();
  updateDisplay();

}


void loop() {

  // see if there are serial commands

  while (Serial.available()) {
    char c = Serial.read();     //gets one byte from serial buffer
    readString += c;            //makes the string readString
    delay(2);                   //slow looping to allow buffer to fill with next character
  }

  // act on serial commands

  if (readString.length() >0) {
    doSerialCommand(readString);
    readString="";              //empty for next input
  } 

  loopTime = millis();

//  if (modeFunc != FUNC_CAL)
//   {
    timer.update();

//    buttonMode.check();
    buttonBrightness.check();

//    checkForTimeout();
//   }

}

