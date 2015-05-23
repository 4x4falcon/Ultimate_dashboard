#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>
#include "Button.h"
#include "Timer.h"
#include "Constants.h"
#include "Variables.h"
#include "Speedo_Functions.h"

/*
* Ultimate Dashboard
* This is the speedo section of the programming
* It will hold all parts of the programming eventually
*
*
* 2015-05-23
*/


/*
* Initialization
*/
void setup() {
  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order

  eepromOdoAddress = EEPROM.getAddress(sizeof(float));
  eepromTrip1Address = EEPROM.getAddress(sizeof(float));
  eepromTrip2Address = EEPROM.getAddress(sizeof(float));
  eepromCalibrateAddress = EEPROM.getAddress(sizeof(float));

  // Attach interrupt for the hall effect sensor 
  // RKS changed this to RISING
  attachInterrupt(0, sensorTriggered, RISING);

  // Read odometer value from flash memory
  totalMiles = EEPROM.readFloat(eepromOdoAddress);

  // Read tripmeter 1 value from flash memory
  totalTrip_1 = EEPROM.readFloat(eepromTrip1Address);

  // Read tripmeter 2 value from flash memory
  totalTrip_2 = EEPROM.readFloat(eepromTrip2Address);

  // calculate pulse distance
  // calibration is over 2 kilometers or miles but is stored as for 1 kilometer or mile
  // formula is 1 / (calibration value in eeprom)
  // this gives distance travelled in one pulse from the sensor
  // as fraction of kilometer or mile

  pulseDistance = 1 / (EEPROM.readFloat(eepromCalibrateAddress);

  // Intialize SPEEDO display
  alpha.begin(0x70);
  alpha.writeDisplay();

  // TODO Initialize ODOMETER display

  // TODO Initialize TRIP displays


  // Update the display every 100ms
  timer.every(100, updateDisplay);

  // Set up trip button handlers
  buttonTrip.setPressHandler(buttonTripPressed);
  buttonTrip.setLongPressHandler(buttonTripLongPressed);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);
  buttonMode.setLongPressHandler(buttonModeLongPressed);

}

/*
* Main loop
*/
void loop() {
  loopTime = millis();

  timer.update();

  buttonTrip.check();
  buttonMode.check();

  writeOdometer();
  writeTripmeter(1);
  writeTripmeter(2);

  checkForTimeout();
}


