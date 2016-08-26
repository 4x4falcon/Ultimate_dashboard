//Tachometer.ino

/*
*	Tachometer
*
*	Reads from tachometer input and display
*
*	rpm
*
*	redline and shift point (can be set by user)
*
*	
*/

// echo to serial for debugging
//#define ECHO_SERIAL 1
//#define ECHO_SERIAL_1 1

//library includes
#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>

//local includes for helpers
#include <Button.h>
#include <Timer.h>

//local includes for global constants and variables
#include "Constants.h"
#include "Variables.h"

//local includes for functions
#include "Calibrate_Functions.h"
#include "Display_Functions.h"
#include "Tacho_Functions.h"
#include "Version.h"
#include "Functions.h"

/*
 *
 * Setup
 *
 */


void setup() {
  Serial.begin(115200);


  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitle = EEPROM.getAddress(sizeof(title));
  eepromVersionHigh = EEPROM.getAddress(sizeof(byte));
  eepromVersionLow = EEPROM.getAddress(sizeof(byte));

  eepromTachoPPR = EEPROM.getAddress(sizeof(byte));
  eepromTachoType = EEPROM.getAddress(sizeof(byte));
  eepromTachoRedline = EEPROM.getAddress(sizeof(int));
  eepromTachoShift = EEPROM.getAddress(sizeof(int));
  eepromTachoMaximum = EEPROM.getAddress(sizeof(int));
  eepromTachoCalibrate = EEPROM.getAddress(sizeof(int));

  // Read ppr, redline and shift from EEPROM
  tachoPPR = EEPROM.readByte(eepromTachoPPR);
  tachoType = EEPROM.readByte(eepromTachoPPR);
  tachoRedline = EEPROM.readInt(eepromTachoRedline);
  tachoShift = EEPROM.readInt(eepromTachoShift);
  tachoMaximum = EEPROM.readInt(eepromTachoMaximum);
  tachoCalibrate = EEPROM.readInt(eepromTachoCalibrate);
  
  tachoStep = tachoMaximum / numTachoLeds;

#ifdef ECHO_SERIAL
  Serial.print("tachoPPR    ");
  Serial.println(tachoPPR);
  Serial.print("tachoType    ");
  Serial.println(tachoType);
  Serial.print("tachoRedline   ");
  Serial.println(tachoRedline);
  Serial.print("tachoShift    ");
  Serial.println(tachoShift);
  Serial.print("tachoMaximum    ");
  Serial.println(tachoMaximum);
  Serial.print("numTachoLeds    ");
  Serial.println(numTachoLeds);
  Serial.print("tachoStep    ");
  Serial.println(tachoStep);
#endif

  // timer to update the tachometer display every 1000ms (1s)
  timer.every(updateTime, updateDisplay);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);
  buttonMode.setLongPressHandler(buttonModeLongPressed);

  // Set up brightness button handlers
  buttonBrightness.setPressHandler(buttonBrightnessPressed);
  buttonBrightness.setLongPressHandler(buttonBrightnessLongPressed);

  //setup speedo and odo software serial baud

  tachoSerial.begin(9600);
  delay(500);
  tachoSerial.write(0x76);
  tachoPixels.begin();

//  tachoSerial.print(" RPM");
//  displayRpm(1101);
//  delay(5000);
  displayRpm(0);

  pinMode(tachoInterrupt, INPUT_PULLUP);
  
  // set up the lights on input and set brightness
  pinMode(pinLightsOn, INPUT_PULLUP);
  pinMode(pinModeButton, INPUT_PULLUP);
  pinMode(pinBrightnessSw, INPUT_PULLUP);

  pinMode(pinLightsOn, INPUT_PULLUP);

  setBrightness();

  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(tachoInterrupt, sensorTriggered, RISING);

  // turn the led on pin 13 off
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}


/*
 *
 * main loop
 *
 */

void loop() {

 // see if there are serial commands

  while ((Serial.available()) && (rpm == 0)) {
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

  if (modeFunc != FUNC_CAL)
   {
    timer.update();

    buttonMode.check();
    buttonBrightness.check();

    checkForTimeout();

   }

}

