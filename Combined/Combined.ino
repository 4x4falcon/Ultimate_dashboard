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
#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>


//program specific include files

#include "Version.h"
#include "Button.h"
#include "Timer.h"
#include "Constants.h"
#include "Variables.h"
#include "Calibrate.h"
#include "Speedo_Display_Functions.h"
//#include "Tacho_Display_Functions.h"
#include "Display.h"
#include "Speedo_Functions.h"
#include "Tacho_Functions.h"
#include "Functions.h"




/*
* Initialization
*/
void setup() {
  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitleAddress = EEPROM.getAddress(sizeof(title));
  eepromVersionHigh = EEPROM.getAddress(sizeof(byte));
  eepromVersionLow = EEPROM.getAddress(sizeof(byte));

  eepromOdoAddress = EEPROM.getAddress(sizeof(totalOdometer));
  eepromTrip1Address = EEPROM.getAddress(sizeof(totalTrip_1));
  eepromTrip2Address = EEPROM.getAddress(sizeof(totalTrip_2));
  eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(int));
  eepromModeSpeedoFuncAddress = EEPROM.getAddress(sizeof(byte));

  eepromTachoCalibrateAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoTypeAddress = EEPROM.getAddress(sizeof(byte));

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

  pulseDistance = 1 / (EEPROM.readFloat(eepromSpeedoCalibrateAddress));

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
  modeSpeedoFunc = EEPROM.readByte(eepromModeSpeedoFuncAddress);
  if (modeSpeedoFunc == FUNC_CAL)
   {
    modeSpeedoFunc = FUNC_KPH;
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


  //setup speedo and odo software serial baud

  speedoSerial.begin(9600);
  delay(500);
  speedoSerial.write(0x76);

  // Initialize ODOMETER and TRIPMETER(s) display
  odoSerial.begin(9600);
  delay(500);
  setupOdometerDisplay();
  updateDisplay();

  // Initialize GAUGE displays
  voltSerial.begin(9600);
  oilSerial.begin(9600);
  tempSerial.begin(9600);
  fuelSerial.begin(9600);
  updateMetersDisplay();



  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(0, sensorTriggered_2, RISING);
  // attach interrupt for the tachometer
  attachInterrupt(1, tachoTriggered, RISING);

}

/*
* Main loop
*/
void loop() {
  loopTime = millis();

  if ((modeSpeedoFunc != FUNC_CAL) && (modeTachoFunc != FUNC_TACHO_CAL))
   {
    timer.update();

    buttonTrip.check();
    buttonSpeedoMode.check();
    buttonTachoMode.check();

    writeOdometer();

    checkForSpeedoTimeout();
    checkForTachoTimeout();
   }
}


