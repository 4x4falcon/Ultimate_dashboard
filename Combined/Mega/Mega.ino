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
//#define DEBUGGING

/*
 * include serial debugging code
 */
#define SERIAL_DEBUG

// if using 16x2 lcd for odometer (preffered)
#define ODOMETER_1602
// if using 0.96 128x64 oled for odometer
//#define ODOMETER_OLED_128x64

/*
 * include egt gauge using thermocouple connected via spi
 */

//#define INCLUDE_EGT

/*
 * include boost gauge using 5V absolute map sensor
 */

//#define INCLUDE_BOOST

/*
 * include clock if not boost gauge
 */

//#ifndef INCLUDE_BOOST
//#define INCLUDE_CLOCK
//#endif

#include "Arduino.h"

//generic include files
#include <Wire.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <MicroLCD.h>
#include <extEEPROM.h>



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

#ifdef INCLUDE_EGT

#include <SPI.h>
#include "Adafruit_MAX31855.h"

#endif

//program specific include files

#include "Defines.h"
#include "I2c.h"
#include "Version.h"
#include "Button.h"
#include "Timer.h"
#include "Constants.h"
#include "Variables.h"

#ifdef INCLUDE_BLUETOOTH
#include "Bluetooth.h"
#endif

#include "Display.h"
#include "Speedo_Functions.h"
#include "Tacho_Functions.h"
#include "Gauges_Functions.h"
#include "Eeprom.h"
#include "Functions.h"
#include "Demo.h"



/*
* Initialization
*/
void setup() {
  Serial.begin(115200);

  getEepromAddresses();

  getEepromValues();

  if ( speedoEeprom.begin(twiClock400kHz) != 0 )
   {
    //there was a problem
    Serial.println("No external Eeprom");

    extEepromAvailable = false;
   }

  if (extEepromAvailable)
   {
    getExtEepromValues();
   }

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

  // set the fan control pins to output
  pinMode(pinFanOne, OUTPUT);
  pinMode(pinFanTwo, OUTPUT);

  // Initialize the i2c communications
  Wire.begin();

#ifdef ODOMETER_1602
  // Initialize the 1602 lcd odometer
  odo1602.begin(16,2);
  odo1602.noBacklight();                             // backlight off

// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  odo1602.setCursor(0,0);                            //Start at character 0 on line 0
  odo1602.print(title);
  odo1602.backlight();                               // backlight on
  delay(500);
  odo1602.clear();
//  Serial.println("Writing to odo1602");
#endif

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

  // Set up trip button handlers
  buttonTrip.pressHandler(buttonTripPressed);
  buttonTrip.releaseHandler(buttonTripReleased);
  buttonTrip.holdHandler(buttonTripLongPressed, 1000); // must be held for at least 3000 ms to trigger

  // Set up speedo mode button handlers
  buttonSpeedoMode.pressHandler(buttonSpeedoModePressed);
  buttonSpeedoMode.releaseHandler(buttonSpeedoModeReleased);
  buttonSpeedoMode.holdHandler(buttonSpeedoModeLongPressed, 1000); // must be held for at least 1000 ms to trigger

  // Set up tacho mode button handlers
  buttonTachoMode.pressHandler(buttonTachoModePressed);
  buttonTachoMode.releaseHandler(buttonTachoModeReleased);
  buttonTachoMode.holdHandler(buttonTachoModeLongPressed, 1000); // must be held for at least 1000 ms to trigger

  // Set up gauges mode button handlers
  buttonGaugesMode.pressHandler(buttonGaugesModePressed);
  buttonGaugesMode.releaseHandler(buttonGaugesModeReleased);
  buttonGaugesMode.holdHandler(buttonGaugesModeLongPressed, 1000); // must be held for at least 1000 ms to trigger

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

// TODO see if this is necessary
  updateMetersDisplay();


  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(0, sensorTriggered_2, RISING);
  // attach interrupt for the tachometer
  attachInterrupt(1, tachoTriggered, RISING);


// Setup bluetooth
#ifdef INCLUDE_BLUETOOTH

// set bluetooth status pin to input
  pinMode(BLUETOOTH_STATE_PIN, INPUT_PULLUP);

// check pin to see if already connected to bluetooth low is connected

  bluetoothAvailable = !digitalRead(BLUETOOTH_STATE_PIN);

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

// TODO look for serial commands from bluetooth
  // see if there are serial commands

#ifdef INCLUDE_BLUETOOTH

  bluetoothAvailable = !digitalRead(BLUETOOTH_STATE_PIN);

/*  

  while ((Serial1.available() >0) && (speed == 0))
   {
    char c = Serial1.read();     //gets one byte from serial buffer
    readString += c;            //makes the string readString
    delay(5);                   //slow looping to allow buffer to fill with next character
    sendBluetooth = true;       // send output to bluetooth rather than serial
   }
*/

#endif

  if (readString.length() == 0)
   {
  // see if there are serial commands
    while ((Serial.available() >0) && (speed == 0))
     {
      char c = Serial.read();     //gets one byte from serial buffer
      readString += c;            //makes the string readString
      delay(5);                   //slow looping to allow buffer to fill with next character
     }
//    sendBluetooth = false;       // send output to serial rather than bluetooth
   }

  // act on serial commands
  if (readString.length() >0)
   {
    doSerialCommand(readString);
    readString="";              //empty for next input
   } 

  loopTime = micros();

//  if ((modeSpeedoFunc != FUNC_CAL) && (modeTachoFunc != FUNC_TACHO_CAL))
   {
    timer.update();       // update speedo display
    timer2.update();      // update tacho and meters display

    buttonTrip.process();
    buttonSpeedoMode.process();
    buttonTachoMode.process();

    writeOdometer();
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
  if ((demoSpeedo > 0) && (demoSpeedo < 20))
   {
    speedoDemo(demoSpeedo);
    demoSpeedo = 0;
   }

  if (demoSpeedo == 20)
   {
    odometerDemo(demoSpeedo);
    demoSpeedo = 0;
    
   }

  
  if (demoAll > 0)
   {
    gaugesDemo(10);
    tachoDemo(10);
    speedoDemo(10);
    odometerDemo(10);

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

 }

