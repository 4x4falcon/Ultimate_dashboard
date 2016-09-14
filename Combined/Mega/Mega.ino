/*
* Ultimate Dashboard
* there should only be setup and loop functions in this file
*
* all other functions should be in the included .h files below
*
*
* 2015-05-23
*/

#define INCLUDE_BLUETOOTH
#define INCLUDE_AHRS


//generic include files
#include <Wire.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>

//program specific include files


#include "I2c.h"
#include "Version.h"
#include "Button.h"
#include "Timer.h"
#include "Constants.h"
#include "Variables.h"
#include "Display.h"
#include "Speedo_Functions.h"
#include "Tacho_Functions.h"
#include "Functions.h"
#include "Demo.h"
#include "Eeprom.h"

#ifdef INCLUDE_BLUETOOTH
#include "Bluetooth.h"
#endif

#ifdef INCLUDE_AHRS
#include "Ahrs.h"
#endif



/*
* Initialization
*/
void setup() {
  Serial.begin(9600);

  getEepromAddresses();
  getEepromValues();

  // set the brightness to be INPUT_PULLUP
  pinMode(pinBrightnessSw, INPUT_PULLUP);
  
  // set the lights on to INPUT_PULLUP
  pinMode(pinLightsOn, INPUT_PULLUP);

  // set the ignition on to INPUT_PULLUP
  pinMode(pinIgnOn, INPUT_PULLUP);

  // set the speedo mode button on to INPUT_PULLUP
  pinMode(pinSpeedoModeButton, INPUT_PULLUP);

  // set the trip button to INPUT_PULLUP
  pinMode(pinTripButton, INPUT_PULLUP);

  // set the tacho mode button to INPUT_PULLUP
  pinMode(pinTachoModeButton, INPUT_PULLUP);

  // set the vss input to INPUT_PULLUP
  pinMode(pinSpeedoInterrupt, INPUT_PULLUP);

  // set the tacho input to INPUT_PULLUP
  pinMode(pinTachoInterrupt, INPUT_PULLUP);

  // Initialize the i2c communications
  Wire.begin();

  // Initialize the neo pixels
  speedoPixels.begin();
  tachoPixels.begin();

  // Update the speedo and odometer display every 101ms
  timer.every(101, updateSpeedoDisplay);

  // update the meters every second (1030ms)
  timer2.every(1030, updateDisplay);

  // Set up trip button handlers
  buttonTrip.setPressHandler(buttonTripPressed);
  buttonTrip.setLongPressHandler(buttonTripLongPressed);

  // Set up speedo mode button handlers
  buttonSpeedoMode.setPressHandler(buttonSpeedoModePressed);
  buttonSpeedoMode.setLongPressHandler(buttonSpeedoModeLongPressed);

  // Set up speedo mode button handlers
  buttonTachoMode.setPressHandler(buttonTachoModePressed);
  buttonTachoMode.setLongPressHandler(buttonTachoModeLongPressed);

  setBrightness();

  //setup speedo
  setupSpeedoDisplay();

  // Initialize ODOMETER and TRIPMETER(s) display
  setupOdometerDisplay();

  setupTachoDisplay();

  // Initialize GAUGE displays
  setupMetersDisplay();

  delay(1000);

  updateDisplay();
  updateMetersDisplay();


  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(0, sensorTriggered_2, RISING);
  // attach interrupt for the tachometer
  attachInterrupt(1, tachoTriggered, RISING);


// Setup bluetooth
#ifdef INCLUDE_BLUETOOTH

#endif

// Setup AHRS
#ifdef INCLUDE_AHRS

#endif


}

/*
* Main loop
*/
void loop() {

  // see if there are serial commands
  while ((Serial.available() >0) && (speed == 0))
   {
    char c = Serial.read();     //gets one byte from serial buffer
    readString += c;            //makes the string readString
    delay(2);                   //slow looping to allow buffer to fill with next character
   }

  // act on serial commands
  if (readString.length() >0)
   {
    doSerialCommand(readString);
    readString="";              //empty for next input
   } 

  loopTime = millis();

  if ((modeSpeedoFunc != FUNC_CAL) && (modeTachoFunc != FUNC_TACHO_CAL))
   {
    timer.update();
    timer2.update();

    buttonTrip.check();
    buttonSpeedoMode.check();
    buttonTachoMode.check();

    writeOdometer();

    checkForSpeedoTimeout();
    checkForTachoTimeout();
   }

  if (demoGauges > 0)
   {
    gaugesDemo(demoGauges);
    demoGauges = 0;
   }
  if (demoTacho > 0)
   {
    tachoDemo(demoTacho);
    demoTacho = 0;
   }
  if (demoSpeedo > 0)
   {
    speedoDemo(demoSpeedo);
    demoSpeedo = 0;
   }
  if (demoAll > 0)
   {
    gaugesDemo(10);
    tachoDemo(10);
    speedoDemo(10);

    if (demoAll != 2)
     {
      demoAll = 0;
      EEPROM.writeByte(eepromDemoAllAddress, 0);
     }
    else
     {
      if (Serial.available() >0)
       {
        demoAll = 0;
        EEPROM.writeByte(eepromDemoAllAddress, 0);
       }
     }
   }

#ifdef INCLUDE_BLUETOOTH

#endif
 
#ifdef INCLUDE_AHRS

#endif
 
 }

