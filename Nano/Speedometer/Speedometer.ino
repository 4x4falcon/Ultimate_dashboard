//Speedometer.ino

/*
*	Speedometer
*
*	Reads from vss and displays
*
*	speed (kph or mph)
*
*	odometer (can not be reset by user)
*
*	tripmeters (individually resetable)
*
* Using Arduino Nano
*/

#define NANO

//#define DEBUGGING

#define ODOMETER_1602
//#define ODOMETER_OLED_128X64


//library includes
#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>



//local includes for helpers
#include <Button.h>
#include <Timer.h>

//local includes for global constants and variables
#include "Defines.h"
#include "Constants.h"
#include "Variables.h"


//local includes for functions
#include "Version.h"
#include "Eeprom.h"
#include "I2c.h"
#include "Display_Functions.h"
#include "Speedo_Functions.h"
#include "Functions.h"


void setup() {
  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order

  getEepromAddresses();
  
  getEepromValues();

  // timer to update the speedo and odometer display every 100ms
  timer.every(updateTime, updateSpeedoDisplay);

  setBrightness();

  // Set up trip button handlers
  buttonTrip.pressHandler(buttonTripPressed);
  buttonTrip.releaseHandler(buttonTripReleased);
  buttonTrip.holdHandler(buttonTripLongPressed, 1000); // must be held for at least 1000 ms to trigger

  // Set up speedo mode button handlers
  buttonSpeedoMode.pressHandler(buttonSpeedoModePressed);
  buttonSpeedoMode.releaseHandler(buttonSpeedoModeReleased);
  buttonSpeedoMode.holdHandler(buttonSpeedoModeLongPressed, 1000); // must be held for at least 1000 ms to trigger

  pinMode(pinSpeedoNeopixel, OUTPUT);

  // Initialize the i2c communications
  Wire.begin();

//  speedoSerial.begin(9600);
  speedoPixels.begin(); // This initializes the NeoPixel library.
  delay(500);

#ifdef ODOMETER_1602
  // Initialize the 1602 lcd odometer
  odo1602.begin(16,2);
  odo1602.noBacklight();                             // backlight off
  delay(500);

// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  odo1602.setCursor(0,0);                            //Start at character 0 on line 0
  odo1602.print(title);
  odo1602.backlight();                               // backlight on
  delay(500);
  odo1602.clear();
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  //setup speedo
  setupSpeedoDisplay();

  displaySpeed(0);

  //setup odometer
  setupOdometerDisplay();
  displayOdometer();

  delay(1000);
  
  // set the led on pin 13 to off
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, arduinoLed);

  // set the button and vss pins to be INPUT_PULLUP
  
  pinMode(pinTripButton, INPUT_PULLUP);
  pinMode(pinModeButton, INPUT_PULLUP);
  pinMode(pinBrightnessSw, INPUT_PULLUP);

  pinMode(pinVss, INPUT_PULLUP);
  pinMode(pinLightsOn, INPUT_PULLUP);    // need to confirm this when completing circuit

  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(speedoInterrupt, sensorTriggered_2, FALLING);

}


void loop() {

  // see if there are serial commands

  while ((Serial.available()) && (speed == 0)) {
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

  if (modeSpeedoFunc != FUNC_CAL)
   {
    timer.update();

    buttonTrip.process();
    buttonSpeedoMode.process();
    buttonBrightness.process();

    writeOdometer();

//    checkForTimeout();
    checkForEepromWrite();

    if (demoSpeedo > 0)
     {
      demoSpeedo = speedoDemo(demoSpeedo);
     }
   }
}

