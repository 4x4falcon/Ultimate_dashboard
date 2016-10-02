/*
 * Initalize eeprom for speedometer
 *
 * This only needs to be run on initial construction of speedometer
 *
 *
 */

#include <EEPROMex.h>
#include <EEPROMVar.h>

#include "Defines.h"
#include "Variables.h"
#include "Version.h"
#include "Eeprom.h"

void setup () {

  Serial.begin(115200);

  // Get eeprom storage addresses MUST be before anything else and in the same order

  getEepromAddresses();

  EEPROM.writeBlock(eepromTitleAddress, title);
  EEPROM.writeByte(eepromVersionHighAddress, versionHigh);
  EEPROM.writeByte(eepromVersionLowAddress, versionLow);

  EEPROM.writeLong(eepromOdoAddress, 0UL);
  EEPROM.writeLong(eepromTrip1Address, 0UL);
  EEPROM.writeLong(eepromTrip2Address, 0UL);


  // This is the distance per pulse in km
  // the value here is calculated from the following
  // wheel/tyre combination is 33x12.5R15 or (315/75R15)
  //
  // pulses per revolution of vehicle speed sensor = ppr =  15
  // this needs to have hardware /10 circuit
  // circumference of wheel/tyre in meters = cir =    2.63144
  // final drive ratio of diff = ratio =      3.5
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

  unsigned long speedoCalibrate = 19951.05 * SPEEDO_CALIBRATE_DIVIDER;

  EEPROM.writeLong(eepromSpeedoCalibrateAddress, speedoCalibrate);

  EEPROM.writeByte(eepromSpeedoModeFuncAddress, 0);

  EEPROM.writeByte(eepromDebugSpeedoAddress, 0);
  EEPROM.writeByte(eepromDemoSpeedoAddress, 0);

  // confirm eeprom has been written to

  Serial.print("Speedo title address = ");
  Serial.print(eepromTitleAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  EEPROM.readBlock(eepromTitleAddress, title);
  Serial.println(title);

  Serial.print("Speedo Version High address = ");
  Serial.print(eepromVersionHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVersionHighAddress));    

  Serial.print("Speedo Version Low address = ");
  Serial.print(eepromVersionLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVersionLowAddress));    

  Serial.println();
  Serial.print("Odometer address = ");
  Serial.print(eepromOdoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readLong(eepromOdoAddress));    
  Serial.print("Tripmeter 1 address = ");
  Serial.print(eepromTrip1Address);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readLong(eepromTrip1Address));    
  Serial.print("Tripmeter 2 address = ");
  Serial.print(eepromTrip2Address);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readLong(eepromTrip2Address));    
  Serial.print("Calibration address = ");
  Serial.print(eepromSpeedoCalibrateAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readLong(eepromSpeedoCalibrateAddress));    

  Serial.print("Speedo Mode address = ");
  Serial.print(eepromSpeedoModeFuncAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromSpeedoModeFuncAddress));    

  Serial.print("Speedo debug address = ");
  Serial.print(eepromDebugSpeedoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromDebugSpeedoAddress));    

  Serial.print("Speedo demo address = ");
  Serial.print(eepromDemoSpeedoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromDemoSpeedoAddress));    

}

void loop () {

}


