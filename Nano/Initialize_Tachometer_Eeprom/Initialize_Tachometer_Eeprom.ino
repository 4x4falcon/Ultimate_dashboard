/*
 * Initalize eeprom for tachometer
 *
 * This only needs to be run on initial construction of speedometer
 *
 *
 */

#include <EEPROMex.h>
#include <EEPROMVar.h>

#include "Version.h"

void setup () {

  Serial.begin(115200);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  int eepromTachoTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  int eepromTachoVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  int eepromTachoVersionLowAddress = EEPROM.getAddress(sizeof(byte));
  int eepromTachoPPRAddress = EEPROM.getAddress(sizeof(byte));
  int eepromTachoTypeAddress = EEPROM.getAddress(sizeof(byte));
  int eepromTachoRedlineAddress = EEPROM.getAddress(sizeof(int));
  int eepromTachoShiftAddress = EEPROM.getAddress(sizeof(int));
  int eepromTachoMaximumAddress = EEPROM.getAddress(sizeof(int));
  int eepromTachoCalibrateAddress = EEPROM.getAddress(sizeof(int));
  int eepromTachoDebugAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeBlock(eepromTachoTitleAddress, title);
  EEPROM.writeByte(eepromTachoVersionHighAddress, versionHigh);
  EEPROM.writeByte(eepromTachoVersionLowAddress, versionLow);

  // This sets up the tacho
  // default is petrol 8 cylinders
  // for petrol engines set to number of cylinders/2 = Pulses per revolution
  // for diesel engines
  // -  if using a Dakota Digital converter then set to 8
  // -  set to number of pulses per revoulution from W terminal of alternator
  // can be calculated from
  // number of altenator pole pairs multiplied by the crank to altenator pulley ratio
  // eg 2 pole pairs
  //    crank pulley 200mm dia
  //    altenator pulley 50mm dia
  //    calibration = pole pairs * (crank pulley/altenator pulley)
  //    calibration = 2 * (200/50)
  //    calibration = 8

  EEPROM.writeByte(eepromTachoPPRAddress, 4);
  EEPROM.writeByte(eepromTachoTypeAddress, 1);
  EEPROM.writeInt(eepromTachoRedlineAddress, 3300);
  EEPROM.writeInt(eepromTachoShiftAddress, 2800);
  EEPROM.writeInt(eepromTachoMaximumAddress, 4500);
  EEPROM.writeInt(eepromTachoCalibrateAddress, 0);
  EEPROM.writeByte(eepromTachoDebugAddress, 0);
  
  // confirm eeprom has been written to

  Serial.print("Tacho title address = ");
  Serial.print(eepromTachoTitleAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  EEPROM.readBlock(eepromTachoTitleAddress, title);
  Serial.println(title);

  Serial.print("Tacho Version High address = ");
  Serial.print(eepromTachoVersionHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoVersionHighAddress));    

  Serial.print("Tacho Version High address = ");
  Serial.print(eepromTachoVersionLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoVersionLowAddress));    

  Serial.print("Tacho Calibration address = ");
  Serial.print(eepromTachoPPRAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoPPRAddress));    
  Serial.print("Tacho Type address = ");
  Serial.print(eepromTachoTypeAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoTypeAddress));    

  Serial.print("Tacho Redline address = ");
  Serial.print(eepromTachoRedlineAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromTachoRedlineAddress));    
  Serial.print("Tacho Shift address = ");
  Serial.print(eepromTachoShiftAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromTachoShiftAddress));
  Serial.print("Tacho Maximum address = ");
  Serial.print(eepromTachoMaximumAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromTachoMaximumAddress));
  Serial.print("Tacho Calibrate address = ");
  Serial.print(eepromTachoCalibrateAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromTachoCalibrateAddress));

  Serial.print("Tacho Debug address = ");
  Serial.print(eepromTachoDebugAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoDebugAddress));

}

void loop () {

}


