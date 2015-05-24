/*
* Ultimate Dashboard
* This is the speedo section of the programming
* It will hold all parts of the programming eventually
* there should only be setup and loop functions in this file
*
* all other functions should be in the included .h files below
*
*
* 2015-05-23
*/

//generic include files

#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>


//program specific include files

#include "Button.h"
#include "Timer.h"
#include "Constants.h"
#include "Variables.h"
#include "Calibrate.h"
#include "Display_Functions.h"
#include "Speedo_Functions.h"


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
  eepromTachoCalibrateAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoTypeAddress = EEPROM.getAddress(sizeof(byte));
  eepromModeFuncAddress = EEPROM.getAddress(sizeof(byte));

  eepromVoltLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltWarnAddress = EEPROM.getAddress(sizeof(int));

  eepromOilLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromOilUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromOilMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromOilWarnAddress = EEPROM.getAddress(sizeof(int));
  
  eepromTempLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromTempUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromTempMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromTempWarnAddress = EEPROM.getAddress(sizeof(int));
  
  eepromFuelLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelWarnAddress = EEPROM.getAddress(sizeof(int));


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

  pulseDistance = 1 / (EEPROM.readFloat(eepromCalibrateAddress));

  // calibration for tachometer
  if (EEPROM.readByte(eepromTachoTypeAddress) == TACHO_PETROL)
   {
    tachoCalibrate = int(EEPROM.readByte(eepromTachoCalibrateAddress)/2);
   }
  else
   {
    tachoCalibrate = EEPROM.readByte(eepromTachoCalibrateAddress);
   }

  // get mode function set this should only be FUNC_KPH or FUNC_MPH
  // if set to FUNC_CAL then reset to FUNC_KPH
  modeFunc = EEPROM.readByte(eepromModeFuncAddress);
  if (modeFunc == FUNC_CAL)
   {
    modeFunc = FUNC_KPH;
   }

  // get constants for gauges
  
  voltLower = EEPROM.readInt(eepromVoltLowerAddress);
  voltUpper = EEPROM.readInt(eepromVoltUpperAddress);
  voltMax = EEPROM.readInt(eepromVoltMaxAddress);
  voltWarn = EEPROM.readInt(eepromVoltWarnAddress);

  oilLower = EEPROM.readInt(eepromOilLowerAddress);
  oilUpper = EEPROM.readInt(eepromOilUpperAddress);
  oilMax = EEPROM.readInt(eepromOilMaxAddress);
  oilWarn = EEPROM.readInt(eepromOilWarnAddress);

  tempLower = EEPROM.readInt(eepromTempLowerAddress);
  tempUpper = EEPROM.readInt(eepromTempUpperAddress);
  tempMax = EEPROM.readInt(eepromTempMaxAddress);
  tempWarn = EEPROM.readInt(eepromTempWarnAddress);

  fuelLower = EEPROM.readInt(eepromFuelLowerAddress);
  fuelUpper = EEPROM.readInt(eepromFuelUpperAddress);
  fuelWarn = EEPROM.readInt(eepromFuelWarnAddress);


  // Update the speedo and odometer display every 100ms
  timer.every(100, updateDisplay);

  // update the meters every second (1000ms)
  timer2.every(1000, updateMeters);

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

  // attach interrupt for the tachometer
  attachInterrupt(1, tachoTriggered, RISING);




}

/*
* Main loop
*/
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


