/*
 * Initalize eeprom for speedometer
 *
 * This only needs to be run on initial construction of speedometer
 *
 *
 */

#define INITIALIZE

//#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>

#include "Button.h"
#include "Timer.h"
#include "Constants.h";
#include "Version.h";
#include "Variables.h";

void setup () {

  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  eepromVersionHigh = EEPROM.getAddress(sizeof(byte));
  eepromVersionLow = EEPROM.getAddress(sizeof(byte));

  eepromOdoAddress = EEPROM.getAddress(sizeof(long));
  eepromTrip1Address = EEPROM.getAddress(sizeof(long));
  eepromTrip2Address = EEPROM.getAddress(sizeof(long));

//  eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(float));
  eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(long));

  eepromSpeedoModeFuncAddress = EEPROM.getAddress(sizeof(byte));

  eepromTachoPPRAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoTypeAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoRedlineAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoShiftAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoMaximumAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoCalibrateAddress = EEPROM.getAddress(sizeof(int));

// VOLTMETER
  eepromVoltLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltUpperAddress =  EEPROM.getAddress(sizeof(int));
  eepromVoltMinAddress =  EEPROM.getAddress(sizeof(int));
  eepromVoltMaxAddress =  EEPROM.getAddress(sizeof(int));
  eepromVoltWarnAddress =  EEPROM.getAddress(sizeof(int));
  eepromVoltWarnLowAddress =  EEPROM.getAddress(sizeof(byte));

// OIL PRESSURE METER
  eepromOilLowerAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilUpperAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilMinAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilMaxAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilWarnAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilWarnLowAddress =  EEPROM.getAddress(sizeof(byte));

// WATER TEMPERATURE METER
  eepromTempLowerAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempUpperAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempMinAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempMaxAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempWarnAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempWarnLowAddress =  EEPROM.getAddress(sizeof(byte));

// FUEL LEVEL METER  
  eepromFuelLowerAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelUpperAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelMinAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelMaxAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelWarnAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelWarnLowAddress =  EEPROM.getAddress(sizeof(byte));

// debug addresses
  eepromDebugSpeedoAddress = EEPROM.getAddress(sizeof(byte));
  eepromDebugTachoAddress = EEPROM.getAddress(sizeof(byte));
  eepromDebugGaugesAddress = EEPROM.getAddress(sizeof(byte));
  eepromDebugAllAddress = EEPROM.getAddress(sizeof(byte));

// demo addresses
  eepromDemoSpeedoAddress = EEPROM.getAddress(sizeof(byte));
  eepromDemoTachoAddress = EEPROM.getAddress(sizeof(byte));
  eepromDemoGaugesAddress = EEPROM.getAddress(sizeof(byte));
  eepromDemoAllAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeBlock(eepromTitleAddress, title);
  EEPROM.writeByte(eepromVersionHigh, versionHigh);
  EEPROM.writeByte(eepromVersionLow, versionLow);

  EEPROM.writeLong(eepromOdoAddress, 0UL);
  EEPROM.writeLong(eepromTrip1Address, 0UL);
  EEPROM.writeLong(eepromTrip2Address, 0UL);




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

  EEPROM.writeByte(eepromSpeedoModeFuncAddress, 0);


  EEPROM.writeByte(eepromTachoPPRAddress, 4);
  EEPROM.writeByte(eepromTachoTypeAddress, TACHO_PETROL);
  EEPROM.writeInt(eepromTachoRedlineAddress, 3300);
  EEPROM.writeInt(eepromTachoShiftAddress, 2800);
  EEPROM.writeInt(eepromTachoMaximumAddress, 4500);
  EEPROM.writeInt(eepromTachoCalibrateAddress, 0);


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

  // Setup water temperature meter
  EEPROM.writeInt(eepromTempLowerAddress, tempLower);
  EEPROM.writeInt(eepromTempUpperAddress, tempUpper);
  EEPROM.writeInt(eepromTempMinAddress, tempMin);
  EEPROM.writeInt(eepromTempMaxAddress, tempMax);
  EEPROM.writeInt(eepromTempWarnAddress, tempWarn);
  EEPROM.writeByte(eepromTempWarnLowAddress, tempWarnLow);

  // Setup fuel level meter
  EEPROM.writeInt(eepromFuelLowerAddress, fuelLower);
  EEPROM.writeInt(eepromFuelUpperAddress, fuelUpper);
  EEPROM.writeInt(eepromFuelMinAddress, fuelMin);
  EEPROM.writeInt(eepromFuelMaxAddress, fuelMax);
  EEPROM.writeInt(eepromFuelWarnAddress, fuelWarn);
  EEPROM.writeByte(eepromFuelWarnLowAddress, fuelWarnLow);

  // debug values
  EEPROM.writeByte(eepromDebugSpeedoAddress, 0);
  EEPROM.writeByte(eepromDebugTachoAddress, 0);
  EEPROM.writeByte(eepromDebugGaugesAddress, 0);
  EEPROM.writeByte(eepromDebugAllAddress, 0);

  // demo values
  EEPROM.writeByte(eepromDemoSpeedoAddress, 0);
  EEPROM.writeByte(eepromDemoTachoAddress, 0);
  EEPROM.writeByte(eepromDemoGaugesAddress, 0);
  EEPROM.writeByte(eepromDemoAllAddress, 0);


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
  Serial.println(EEPROM.readInt(eepromVoltWarnLowAddress));

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
  Serial.println(EEPROM.readInt(eepromOilWarnLowAddress));
  
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
  Serial.println(EEPROM.readInt(eepromTempWarnLowAddress));

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
  Serial.println(EEPROM.readInt(eepromFuelWarnLowAddress));

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

}

void loop () {

}


