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
*
*/

// echo to serial for debugging
//#define ECHO_SERIAL 1
//#define ECHO_SERIAL_2 1
//#define ECHO_SERIAL_3 1

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
#include "Display_Functions.h"
#include "Speedo_Functions.h"
#include "Version.h"
//#include "Calibrate_Functions.h"

void setup() {
  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  
  eepromTitleAddress = EEPROM.getAddress(sizeof(title));
  eepromVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  eepromVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  eepromOdoAddress = EEPROM.getAddress(sizeof(long));
  eepromTrip1Address = EEPROM.getAddress(sizeof(long));
  eepromTrip2Address = EEPROM.getAddress(sizeof(long));

  eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(float));

  eepromModeFuncAddress = EEPROM.getAddress(sizeof(byte));



  // Read odometer value from flash memory
  totalOdometer = EEPROM.readLong(eepromOdoAddress);

  // Read tripmeter 1 value from flash memory
  totalTrip_1 = EEPROM.readLong(eepromTrip1Address);

  // Read tripmeter 2 value from flash memory
  totalTrip_2 = EEPROM.readLong(eepromTrip2Address);

  // pulse distance
  // calibration is over 2 kilometers or miles but is stored as for 1 kilometer or mile
  // this gives distance travelled in one pulse

  pulseDistance = EEPROM.readFloat(eepromSpeedoCalibrateAddress);

#ifdef ECHO_SERIAL
  Serial.print("setup pulseDistance =   ");
  char setupBuffer[25];
  dtostrf(pulseDistance, 20, 12, setupBuffer);
  Serial.println(setupBuffer);
#endif


  // get mode function set this should only be FUNC_KPH or FUNC_MPH
  // if set to FUNC_CAL then reset to FUNC_KPH
  modeFunc = EEPROM.readByte(eepromModeFuncAddress);
  if (modeFunc == FUNC_CAL)
   {
    modeFunc = FUNC_KPH;
   }

  // timer to update the speedo and odometer display every 100ms
  timer.every(updateTime, updateDisplay);

  // Set up trip button handlers
  buttonTrip.setPressHandler(buttonTripPressed);
  buttonTrip.setLongPressHandler(buttonTripLongPressed);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);
  buttonMode.setLongPressHandler(buttonModeLongPressed);

  // Set up brightness button handlers
  buttonBrightness.setPressHandler(buttonBrightnessPressed);
  buttonBrightness.setLongPressHandler(buttonBrightnessLongPressed);

  //setup speedo and odo software serial baud

  speedoSerial.begin(9600);
  odoSerial.begin(9600);
  speedoPixels.begin(); // This initializes the NeoPixel library.
  delay(500);

  // 
  speedoSerial.write(0x76);
  
  // Initialize ODOMETER and TRIPMETER(s) display
  setupOdometerDisplay();
  displayOdometer();
  displaySpeed(0);
  
  // set the led on pin 13 to off
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, arduinoLed);

  // set the button and vss pins to be INPUT_PULLUP
  
  pinMode(pinTripButton, INPUT_PULLUP);
  pinMode(pinModeButton, INPUT_PULLUP);
  pinMode(pinBrightnessSw, INPUT_PULLUP);

  pinMode(pinVss, INPUT_PULLUP);
  pinMode(pinLightsOn, INPUT_PULLUP);    // need to confirm this when completing circuit

  setBrightness();

  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(speedoInterrupt, sensorTriggered_2, FALLING);

}


void loop() {
  loopTime = millis();

  if (modeFunc != FUNC_CAL)
   {
    timer.update();

    buttonTrip.check();
    buttonMode.check();
    buttonBrightness.check();

    writeOdometer();

    checkForTimeout();
    checkForEepromWrite();
   }


}

