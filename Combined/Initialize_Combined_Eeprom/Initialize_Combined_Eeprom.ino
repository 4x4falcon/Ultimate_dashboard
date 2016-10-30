/*
 * Initalize eeprom for speedometer
 *
 * This only needs to be run on initial construction of speedometer
 *
 *
 */

#define INITIALIZE_COMBINED_EEPROM

// include egt gauge
#define INCLUDE_EGT

#include <Wire.h>
#include <EEPROMex.h>
#include <extEEPROM.h>

#include "Constants.h"
#include "Defines.h"
#include "Version.h"
#include "Variables.h"
#include "Eeprom.h"

void setup () {

  Serial.begin(9600);

  getEepromAddresses();

  EEPROM.writeBlock(eepromTitleAddress, title);
  EEPROM.writeByte(eepromVersionHigh, versionHigh);
  EEPROM.writeByte(eepromVersionLow, versionLow);

  EEPROM.writeLong(eepromOdoAddress, extEepromOdometer.totalOdometer);
  EEPROM.writeLong(eepromTrip1Address, totalTrip_1);
  EEPROM.writeLong(eepromTrip2Address, totalTrip_1);

  // This is the distance per pulse in km
  // the value here is calculated from the following
  // wheel/tyre combination is 33x12.5R15 or (315/75R15)
  //
  // pulses per revolution of vehicle speed sensor = ppr =	15
  // this needs to have hardware /10 circuit
  // circumference of wheel/tyre in meters = cir =		2.63144
  // final drive ratio of diff = ratio =			3.5
  // formula is
  // (1000m/cir) * ratio * ppr
  // for each kilometer there are (1000/cir) turns of the wheel
  // for each turn of the wheel the drive shaft turns ratio times
  // for each turn of the driveshaft there are ppr pulses
  // therefore for this tyre/wheel diff combo the result is:
  // (1000/2.63144) * 3.5 * 15
  // equals
  // 19951.05 pulses per kilometer
  // 19951.05341562

  // this is then multiplied by 100 and stored as pulses per kilometer * 100
  
  // NOTE if you are using a sensor that is on the wheel/tyre the final drive ratio is 1

//  EEPROM.writeFloat(eepromSpeedoCalibrateAddress, 0.0501227);
  unsigned long speedoCalibrate = 19951.05 * SPEEDO_CALIBRATE_DIVIDER;
  EEPROM.writeLong(eepromSpeedoCalibrateAddress, speedoCalibrate);

  Serial.print("calibrate divider = ");
  Serial.println(SPEEDO_CALIBRATE_DIVIDER);
  Serial.print("calibrate = ");
  Serial.println(speedoCalibrate);

  EEPROM.writeByte(eepromSpeedoModeFuncAddress, modeSpeedoFunc);


  EEPROM.writeByte(eepromTachoPPRAddress, tachoPPR);
  EEPROM.writeByte(eepromTachoTypeAddress, tachoType);
  EEPROM.writeInt(eepromTachoRedlineAddress, tachoRedline);
  EEPROM.writeInt(eepromTachoShiftAddress, tachoShift);
  EEPROM.writeInt(eepromTachoMaximumAddress, tachoMaximum);
  EEPROM.writeInt(eepromTachoCalibrateAddress, tachoCalibrate);


  // Setup voltmeter

  EEPROM.writeInt(eepromVoltLowerAddress, voltLower);
  EEPROM.writeInt(eepromVoltUpperAddress, voltUpper);
  EEPROM.writeInt(eepromVoltMinAddress, voltMin);
  EEPROM.writeInt(eepromVoltMaxAddress, voltMax);
  EEPROM.writeInt(eepromVoltWarnAddress, voltWarn);
  EEPROM.writeByte(eepromVoltWarnLowAddress, voltWarnLow);

  // Setup oil pressure meter
  EEPROM.writeInt(eepromOilLowerAddress, oilLower);
  EEPROM.writeInt(eepromOilUpperAddress, oilUpper);
  EEPROM.writeInt(eepromOilMinAddress, oilMin);
  EEPROM.writeInt(eepromOilMaxAddress, oilMax);
  EEPROM.writeInt(eepromOilWarnAddress, oilWarn);
  EEPROM.writeByte(eepromOilWarnLowAddress, oilWarnLow);
  EEPROM.writeByte(eepromOilInvertedAddress, oilInverted);

  // Setup water temperature meter
  EEPROM.writeInt(eepromTempLowerAddress, tempLower);
  EEPROM.writeInt(eepromTempUpperAddress, tempUpper);
  EEPROM.writeInt(eepromTempMinAddress, tempMin);
  EEPROM.writeInt(eepromTempMaxAddress, tempMax);
  EEPROM.writeInt(eepromTempWarnAddress, tempWarn);
  EEPROM.writeInt(eepromTempFanOneOnAddress, tempFanOneOn);
  EEPROM.writeInt(eepromTempFanOneOffAddress, tempFanOneOff);
  EEPROM.writeInt(eepromTempFanTwoOnAddress, tempFanTwoOn);
  EEPROM.writeInt(eepromTempFanTwoOffAddress, tempFanTwoOff);
  EEPROM.writeByte(eepromTempWarnLowAddress, tempWarnLow);
  EEPROM.writeByte(eepromTempCelciusAddress, tempCelcius);
  EEPROM.writeByte(eepromTempInvertedAddress, tempInverted);

  // Setup fuel level meter
  EEPROM.writeInt(eepromFuelLowerAddress, fuelLower);
  EEPROM.writeInt(eepromFuelUpperAddress, fuelUpper);
  EEPROM.writeInt(eepromFuelMinAddress, fuelMin);
  EEPROM.writeInt(eepromFuelMaxAddress, fuelMax);
  EEPROM.writeInt(eepromFuelWarnAddress, fuelWarn);
  EEPROM.writeByte(eepromFuelWarnLowAddress, fuelWarnLow);
  EEPROM.writeByte(eepromFuelInvertedAddress, fuelInverted);

#ifdef INCLUDE_EGT
  // Setup egt meter
  EEPROM.writeInt(eepromEgtLowerAddress, egtLower);
  EEPROM.writeInt(eepromEgtUpperAddress, egtUpper);
  EEPROM.writeInt(eepromEgtMinAddress, egtMin);
  EEPROM.writeInt(eepromEgtMaxAddress, egtMax);
  EEPROM.writeInt(eepromEgtWarnAddress, egtWarn);
  EEPROM.writeByte(eepromEgtWarnLowAddress, egtWarnLow);
  EEPROM.writeByte(eepromEgtInvertedAddress, egtInverted);
  EEPROM.writeByte(eepromEgtCelciusAddress, egtCelcius);
#endif

  // debug values
  EEPROM.writeByte(eepromDebugSpeedoAddress, debugSpeedo);
  EEPROM.writeByte(eepromDebugTachoAddress, debugTacho);
  EEPROM.writeByte(eepromDebugGaugesAddress, debugGauges);
  EEPROM.writeByte(eepromDebugAllAddress, debugAll);

  // demo values
  EEPROM.writeByte(eepromDemoSpeedoAddress, demoSpeedo);
  EEPROM.writeByte(eepromDemoTachoAddress, demoTacho);
  EEPROM.writeByte(eepromDemoGaugesAddress, demoGauges);
  EEPROM.writeByte(eepromDemoAllAddress, demoAll);


  // confirm eeprom has been written to

  Serial.println(F("Setting up values"));
  delay(1000);

  Serial.print(F("Speedo title address = "));
  Serial.print(eepromTitleAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  EEPROM.readBlock(eepromTitleAddress, title);
  Serial.println(title);

  Serial.print(F("Speedo Version High address = "));
  Serial.print(eepromVersionHigh);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromVersionHigh));    

  Serial.print(F("Speedo Version Low address = "));
  Serial.print(eepromVersionLow);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromVersionLow));

  Serial.println();
  Serial.print(F("Odometer address = "));
  Serial.print(eepromOdoAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readLong(eepromOdoAddress));    
  Serial.print(F("Tripmeter 1 address = "));
  Serial.print(eepromTrip1Address);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readLong(eepromTrip1Address));    
  Serial.print(F("Tripmeter 2 address = "));
  Serial.print(eepromTrip2Address);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readLong(eepromTrip2Address));

  Serial.print(F("Calibration address = "));
  Serial.print(eepromSpeedoCalibrateAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readLong(eepromSpeedoCalibrateAddress));    


  Serial.print(F("Tacho PPR address = "));
  Serial.print(eepromTachoTypeAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromTachoPPRAddress));
  Serial.print(F("Tacho type address = "));
  Serial.print(eepromTachoTypeAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromTachoTypeAddress));
  Serial.print(F("Tacho redline address = "));
  Serial.print(eepromTachoRedlineAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTachoRedlineAddress));
  Serial.print(F("Tacho shift address = "));
  Serial.print(eepromTachoShiftAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTachoShiftAddress));
  Serial.print(F("Tacho maximum address = "));
  Serial.print(eepromTachoMaximumAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTachoMaximumAddress));
  Serial.print(F("Tacho calibrate address = "));
  Serial.print(eepromTachoCalibrateAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTachoCalibrateAddress));


  Serial.print(F("Volt lower address = "));
  Serial.print(eepromVoltLowerAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
  Serial.print(F("Volt upper address = "));
  Serial.print(eepromVoltUpperAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
  Serial.print(F("Volt Min address = "));
  Serial.print(eepromVoltMinAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromVoltMinAddress));
  Serial.print(F("Volt Max address = "));
  Serial.print(eepromVoltMaxAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromVoltMaxAddress));
  Serial.print(F("Volt Warn address = "));
  Serial.print(eepromVoltWarnAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromVoltWarnAddress));
  Serial.print(F("Volt Warn Low address = "));
  Serial.print(eepromVoltWarnLowAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromVoltWarnLowAddress));

  Serial.print(F("Oil lower address = "));
  Serial.print(eepromOilLowerAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromOilLowerAddress));
  Serial.print(F("Oil upper address = "));
  Serial.print(eepromOilUpperAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromOilUpperAddress));
  Serial.print(F("Oil Min address = "));
  Serial.print(eepromOilMinAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromOilMinAddress));
  Serial.print(F("Oil Max address = "));
  Serial.print(eepromOilMaxAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromOilMaxAddress));
  Serial.print(F("Oil Warn address = "));
  Serial.print(eepromOilWarnAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromOilWarnAddress));
  Serial.print(F("Oil Warn Low address = "));
  Serial.print(eepromOilWarnLowAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromOilWarnLowAddress));
  Serial.print(F("Oil Inverted address = "));
  Serial.print(eepromOilInvertedAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromOilInvertedAddress));

  Serial.print(F("Temp lower address = "));
  Serial.print(eepromTempLowerAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempLowerAddress));
  Serial.print(F("Temp upper address = "));
  Serial.print(eepromTempUpperAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempUpperAddress));
  Serial.print(F("Temp Min address = "));
  Serial.print(eepromTempMinAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempMinAddress));
  Serial.print(F("Temp Max address = "));
  Serial.print(eepromTempMaxAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempMaxAddress));
  Serial.print(F("Temp Warn address = "));
  Serial.print(eepromTempWarnAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempWarnAddress));
  Serial.print(F("Temp Warn Low address = "));
  Serial.print(eepromTempWarnLowAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromTempWarnLowAddress));

  Serial.print(F("Temp Celcius address = "));
  Serial.print(eepromTempCelciusAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromTempCelciusAddress));

  Serial.print(F("Temp Inverted address = "));
  Serial.print(eepromTempInvertedAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromTempInvertedAddress));

  Serial.print(F("Temp Fan One on address = "));
  Serial.print(eepromTempFanOneOnAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempFanOneOnAddress));
  Serial.print(F("Temp Fan One off address = "));
  Serial.print(eepromTempFanOneOffAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempFanOneOffAddress));

  Serial.print(F("Temp Fan Two on address = "));
  Serial.print(eepromTempFanTwoOnAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempFanTwoOnAddress));
  Serial.print(F("Temp Fan Two off address = "));
  Serial.print(eepromTempFanTwoOffAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromTempFanTwoOffAddress));


  Serial.print(F("Fuel lower address = "));
  Serial.print(eepromFuelLowerAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
  Serial.print(F("Fuel upper address = "));
  Serial.print(eepromFuelUpperAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
  Serial.print(F("Fuel Min address = "));
  Serial.print(eepromFuelMinAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromFuelMinAddress));
  Serial.print(F("Fuel Max address = "));
  Serial.print(eepromFuelMaxAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
  Serial.print(F("Fuel Warn address = "));
  Serial.print(eepromFuelWarnAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
  Serial.print(F("Fuel Warn Low address = "));
  Serial.print(eepromFuelWarnLowAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromFuelWarnLowAddress));
  Serial.print(F("Fuel Inverted address = "));
  Serial.print(eepromFuelInvertedAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromFuelInvertedAddress));


#ifdef INCLUDE_EGT
  Serial.print(F("Egt lower address = "));
  Serial.print(eepromEgtLowerAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromEgtLowerAddress));
  Serial.print(F("Egt upper address = "));
  Serial.print(eepromEgtUpperAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromEgtUpperAddress));
  Serial.print(F("Egt Min address = "));
  Serial.print(eepromEgtMinAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromEgtMinAddress));
  Serial.print(F("Egt Max address = "));
  Serial.print(eepromEgtMaxAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromEgtMaxAddress));
  Serial.print(F("Egt Warn address = "));
  Serial.print(eepromEgtWarnAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readInt(eepromEgtWarnAddress));
  Serial.print(F("Egt Warn Low address = "));
  Serial.print(eepromEgtWarnLowAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromEgtWarnLowAddress));
  Serial.print(F("Egt Inverted address = "));
  Serial.print(eepromEgtInvertedAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromEgtInvertedAddress));
#endif

  // debug values
  Serial.print(F("Debug Speedo address = "));
  Serial.print(eepromDebugSpeedoAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDebugSpeedoAddress));
  Serial.print(F("Debug Tacho address = "));
  Serial.print(eepromDebugTachoAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDebugTachoAddress));
  Serial.print(F("Debug Gauges address = "));
  Serial.print(eepromDebugGaugesAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDebugGaugesAddress));
  Serial.print(F("Debug All address = "));
  Serial.print(eepromDebugAllAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDebugAllAddress));

  // demo values
  Serial.print(F("Demo Speedo address = "));
  Serial.print(eepromDemoSpeedoAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDemoSpeedoAddress));
  Serial.print(F("Demo Tacho address = "));
  Serial.print(eepromDemoTachoAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDemoTachoAddress));
  Serial.print(F("Demo Gauges address = "));
  Serial.print(eepromDemoGaugesAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDemoGaugesAddress));
  Serial.print(F("Demo All address = "));
  Serial.print(eepromDemoAllAddress);
  Serial.print(F(" \t\t "));
  Serial.print(F("value = "));
  Serial.println(EEPROM.readByte(eepromDemoAllAddress));

  if ( speedoEeprom.begin(twiClock400kHz) != 0 )
   {
    //there was a problem
    Serial.println("No external Eeprom");

    extEepromAvailable = false;
   }

  if (extEepromAvailable)
   {
    extEepromOdometer.totalOdometer = 180114;
    speedoEeprom.write(EXT_EEPROM_ADDRESS_ODOMETER, (byte *)&extEepromOdometer.extEepromTotalOdometer, 4);

    speedoEeprom.read(EXT_EEPROM_ADDRESS_ODOMETER, (byte *)&extEepromOdometer.extEepromTotalOdometer, 4);
    Serial.print("external eeprom odometer = ");
    Serial.println(extEepromOdometer.totalOdometer);

    extEepromValidate.extEepromValid = EXT_EEPROM_VALIDATE;
    speedoEeprom.write(EXT_EEPROM_ADDRESS_VALIDATE, (byte *)&extEepromValidate.extEepromValidByte, 4);    

    speedoEeprom.read(EXT_EEPROM_ADDRESS_VALIDATE, (byte *)&extEepromValidate.extEepromValidByte, 4);
    Serial.print("external eeprom odometer = ");
    Serial.println(extEepromValidate.extEepromValid);
    
   
   }


}

void loop () {

}


