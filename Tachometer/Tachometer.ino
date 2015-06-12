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


/*
 *
 * Setup
 *
 */


void setup() {
  Serial.begin(9600);


  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitleAddress = EEPROM.getAddress(sizeof(title));
  eepromVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  eepromVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  eepromTachoPPRAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoRedlineAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoShiftAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoMaximumAddress = EEPROM.getAddress(sizeof(int));

  // Read ppr, redline and shift from EEPROM
  tachoPPR = EEPROM.readByte(eepromTachoPPRAddress);
  tachoRedline = EEPROM.readInt(eepromTachoRedlineAddress);
  tachoShift = EEPROM.readInt(eepromTachoShiftAddress);
  tachoMaximum = EEPROM.readInt(eepromTachoMaximumAddress);
  
  tachoStep = tachoMaximum / numTachoLeds;

#ifdef ECHO_SERIAL
  Serial.print("tachoPPR    ");
  Serial.println(tachoPPR);
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

  // timer to update the speedo and odometer display every 1000ms (1s)
  timer.every(1000, updateDisplay);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);
  buttonMode.setLongPressHandler(buttonModeLongPressed);

  //setup speedo and odo software serial baud

  tachoSerial.begin(9600);
  delay(500);
  tachoSerial.write(0x76);

  tachoPixels.begin();

  displayRpm(0);

  pinMode(tachoInterrupt, INPUT_PULLUP);
  
  // turn the led on pin 13 off
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // set up the lights on input and set brightness
  pinMode(pinLightsOn, INPUT_PULLUP);
  setBrightness();

  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(tachoInterrupt, sensorTriggered, RISING);

}


/*
 *
 * main loop
 *
 */

void loop() {
  loopTime = millis();

  if (modeFunc != FUNC_CAL)
   {
    timer.update();

    buttonMode.check();

    checkForTimeout();

   }

}

