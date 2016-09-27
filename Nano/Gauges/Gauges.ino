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
#include <Wire.h>

// includes for helpers
#include <Button.h>
#include <Timer.h>

// local includes
#include "Constants.h"
#include "Variables.h"
#include "Version.h"
#include "Eeprom.h"
#include "I2c.h"
#include "Display_Functions.h"
#include "Gauges_Functions.h"
#include "Calibrate_Functions.h"
#include "Functions.h"
#include "Demo.h"

// These are the Arduino pins required to create a software seiral
//  instance. We'll actually only use the TX pin.
//const int softwareTx = 6;
//const int softwareRx = 7;
//SoftwareSerial s7s(softwareRx, softwareTx);

void setup() {
  Serial.begin(9600);

  getEepromAddresses();
  getEepromValues();

  // timer to update the gauges display every 5000ms (5s)
  timer.every(timeUpdate, updateMetersDisplay);

  // Set up mode button handlers
  buttonMode.pressHandler(buttonModePressed);
  buttonMode.holdHandler(buttonModeLongPressed);

  buttonBrightness.pressHandler(buttonBrightnessPressed);
  buttonBrightness.holdHandler(buttonBrightnessLongPressed);

  // set the led on pin 13 to off
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, !arduinoLed);

  // set the button pins to be INPUT_PULLUP
  pinMode(pinBrightnessSw, INPUT_PULLUP);
  pinMode(pinModeButton, INPUT_PULLUP);
  
  // set the lights on button to INPUT_PULLUP
  pinMode(pinLightsOn, INPUT_PULLUP);

  Wire.begin();

  setBrightness();

  delay(100);

  setupMetersDisplay();

  delay(1000);

  updateMetersDisplay();

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

  timer.update();

  buttonMode.process();
  buttonBrightness.process();

  if (demo > 0)
   {
    gaugesDemo(demoGauges);
   }
}

