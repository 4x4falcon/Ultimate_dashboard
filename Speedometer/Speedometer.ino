//Speedometer.ino

/*
*	Speedometer
*
*	Reads from vss and display
*
*	speed (kph or mph)
*
*	odometer (can not be reset by user)
*
*	tripmeters (individually resetable)
*
*	
*/

//library includes
#include <SoftwareSerial.h>
#include <EEPROMex.h>


//local includes for helpers
#include "Button.h"
#include "Timer.h"

//local includes for global constants and variables
#include "Constants.h"
#include "Variables.h"

//local includes for functions
#include "Calibrate_Functions.h"
#include "Display_Functions.h"
#include "Speedo_Functions.h"
#include "Version.h"

void setup() {
  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  
  eepromTitleAddress = EEPROM.getAddress(sizeof(title));
  eepromVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  eepromVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  eepromOdoAddress = EEPROM.getAddress(sizeof(float));
  eepromTrip1Address = EEPROM.getAddress(sizeof(float));
  eepromTrip2Address = EEPROM.getAddress(sizeof(float));
  eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(float));
  eepromModeFuncAddress = EEPROM.getAddress(sizeof(byte));

  // Read odometer value from flash memory
  totalOdometer = EEPROM.readFloat(eepromOdoAddress);

  // Read tripmeter 1 value from flash memory
  totalTrip_1 = EEPROM.readFloat(eepromTrip1Address);

  // Read tripmeter 2 value from flash memory
  totalTrip_2 = EEPROM.readFloat(eepromTrip2Address);

  // calculate pulse distance
  // calibration is over 2 kilometers or miles but is stored as for 1 kilometer or mile
  // formula is 1 / (calibration value in eeprom)
  // this gives distance travelled in one pulse from the sensor
  // as fraction of kilometer or mile

  pulseDistance = 1 / (EEPROM.readFloat(eepromSpeedoCalibrateAddress));

  // get mode function set this should only be FUNC_KPH or FUNC_MPH
  // if set to FUNC_CAL then reset to FUNC_KPH
  modeFunc = EEPROM.readByte(eepromModeFuncAddress);
  if (modeFunc == FUNC_CAL)
   {
    modeFunc = FUNC_KPH;
   }

  // timer to update the speedo and odometer display every 100ms
  timer.every(100, updateDisplay);

  // Set up trip button handlers
  buttonTrip.setPressHandler(buttonTripPressed);
  buttonTrip.setLongPressHandler(buttonTripLongPressed);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);
  buttonMode.setLongPressHandler(buttonModeLongPressed);

  //setup speedo and odo software serial baud

  speedoSerial.begin(9600);
  speedoSerial.write(0x76);

  // Initialize ODOMETER and TRIPMETER(s) display
  setupOdometerDisplay();

  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(0, sensorTriggered, RISING);


}


void loop() {
  loopTime = millis();

  if (modeFunc != FUNC_CAL)
   {
    timer.update();

    buttonTrip.check();
    buttonMode.check();

    writeOdometer();

    checkForTimeout();
   }


}

