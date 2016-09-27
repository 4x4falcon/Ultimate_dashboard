/*
* Ultimate Dashboard
* there should only be setup and loop functions in this file
*
* all other functions should be in the included .h files below
*
*
* 2015-05-23
*/

#define MEGA

/*
 * what parts to inlcude
 * 
 * TODO setup the ifdefs throughout the remainder of the code
 * 
 */

#define INCLUDE_SPEEDO
#define INCLUDE_TACHO
#define INCLUDE_GAUGES

/*
 * include bluetooth
 */

#define INCLUDE_BLUETOOTH

/*
 * include atitude heading reference system (AHRS)
 */

#define INCLUDE_AHRS

/*
 * include debugging code other than those set from serial command
 */

#define DEBUGGING

// if using 16x2 lcd for odometer (preffered)
#define ODOMETER_1602
// if using 0.96 128x64 oled for odometer
//#define ODOMETER_OLED_128x64

#include "Arduino.h"

//generic include files
#include <Wire.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>
#include <MicroLCD.h>


#ifdef INCLUDE_BLUETOOTH
#include "Bluetooth.h"
#endif

#ifdef INCLUDE_AHRS
#include <Adafruit_Sensor.h>

// adafruit adxl345 library for 3-axis accelerometer
#include <Adafruit_ADXL345_U.h>

// adafruit hmc5883 library for 3-axis magnetometer
#include <Adafruit_HMC5883_U.h>

// adafruit l3gd20 library for 3-axis gyroscope
#include <Adafruit_L3GD20_U.h>

// adafruit bmp085 library for barometer and temperature
#include <Adafruit_BMP085.h>

#include "Ahrs.h"
#endif


//program specific include files

#include "Defines.h"
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


/*
* Initialization
*/
void setup() {
  Serial.begin(9600);

  getEepromAddresses();

  getEepromValues();

  Serial.println(title);
  Serial.print("Version ");
  Serial.print(versionHigh);
  Serial.print(".");
  Serial.println(versionLow);

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

#ifdef ODOMETER_OLED_128x64
  // Initialize the oled odometer if used
  oledOdometer.begin();

  oledOdometer.clear();
  oledOdometer.setFontSize(FONT_SIZE_SMALL);
  oledOdometer.println(title);
  delay(500);
  oledOdometer.clear();
#endif


  // Initialize the neo pixels
  speedoPixels.begin();
  tachoPixels.begin();

  // Update the speedo and odometer display every 100ms
  timer.every(100, updateSpeedoDisplay);

  // update the meters every second (1000ms)
  timer2.every(1000, updateDisplay);

// TODO rename these for new button library

  // Set up trip button handlers
//  buttonTrip.setPressHandler(buttonTripPressed);
//  buttonTrip.setLongPressHandler(buttonTripLongPressed);
  buttonTrip.pressHandler(buttonTripPressed);
//  buttonTrip.releaseHandler(onRelease);
  buttonTrip.holdHandler(buttonTripLongPressed, 3000); // must be held for at least 3000 ms to trigger

  // Set up speedo mode button handlers
//  buttonSpeedoMode.setPressHandler(buttonSpeedoModePressed);
//  buttonSpeedoMode.setLongPressHandler(buttonSpeedoModeLongPressed);
  buttonSpeedoMode.pressHandler(buttonSpeedoModePressed);
//  buttonTrip.releaseHandler(onRelease);
  buttonSpeedoMode.holdHandler(buttonSpeedoModeLongPressed, 3000); // must be held for at least 3000 ms to trigger

  // Set up speedo mode button handlers
//  buttonTachoMode.setPressHandler(buttonTachoModePressed);
//  buttonTachoMode.setLongPressHandler(buttonTachoModeLongPressed);
  buttonSpeedoMode.pressHandler(buttonTachoModePressed);
//  buttonTrip.releaseHandler(onRelease);
  buttonSpeedoMode.holdHandler(buttonTachoModeLongPressed, 3000); // must be held for at least 3000 ms to trigger

  setBrightness();

  //setup speedo
  setupSpeedoDisplay();

  // Initialize ODOMETER and TRIPMETER(s) display
  setupOdometerDisplay();

  setupTachoDisplay();

  // Initialize GAUGE displays
  setupMetersDisplay();

  delay(100);

  updateDisplay();

// TODO see if this is necessary
  updateMetersDisplay();


  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(0, sensorTriggered_2, RISING);
  // attach interrupt for the tachometer
  attachInterrupt(1, tachoTriggered, RISING);


// Setup bluetooth
#ifdef INCLUDE_BLUETOOTH

  Serial1.begin(9600);
  Serial1.print("AT");
  if (Serial1.available() > 0)
   {
    Serial.println("bluetooth connected");

    bluetoothAvailable = true;
   }
  else
   {
    bluetoothAvailable = false;
   }



#endif

byte error = 0;

// Setup AHRS
#ifdef INCLUDE_AHRS
  Wire.beginTransmission(I2C_ADDRESS_MAGNETOMETER);
  error = Wire.endTransmission();

  if (error == 0)
   {
    Serial.println("AHRS connected");

    magnetometerAvailable = true;
   }
  else
   {
    magnetometerAvailable = false;
   }

#endif

#ifndef ODOMETER_OLED_128x64
// Setup oled diagnostics display
  Wire.beginTransmission(I2C_ADDRESS_OLED);
  error = Wire.endTransmission();

  if (error == 0)
   {
    Serial.println("oled connected");

    oledDiagnostic.begin();

    oledDiagnostic.clear();
    oledDiagnostic.setFontSize(FONT_SIZE_SMALL);
    oledDiagnostic.println(title);

    delay(1000);
    oledDiagnostic.clear();

    oledAvailable = true;
   }
  else
   {
    oledAvailable = false;
   }
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

  loopTime = micros();

  if ((modeSpeedoFunc != FUNC_CAL) && (modeTachoFunc != FUNC_TACHO_CAL))
   {
    timer.update();       // update speedo display
    timer2.update();      // update tacho and meters display

// TODO rename these for new library

//    buttonTrip.check();
//    buttonSpeedoMode.check();
//    buttonTachoMode.check();
    buttonTrip.process();
    buttonSpeedoMode.process();
    buttonTachoMode.process();


    writeOdometer();

//    checkForSpeedoTimeout();
//    checkForTachoTimeout();
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

#ifdef INCLUDE_AHRS
  if (magnetometerAvailable)
   {
    getAHRS();
   }
#endif

#ifdef INCLUDE_BLUETOOTH
  if (bluetoothAvailable)
   {
    printBluetooth();
   }
#endif
 }

