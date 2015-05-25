/*
 * Initalize eeprom for gauges
 *
 * This only needs to be run on initial construction of the gauges
 *
 *
 */

#include <EEPROMex.h>
#include <EEPROMVar.h>

#include "Version.h";

void setup () {

  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  int eepromTachoTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  int eepromTachoVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  int eepromTachoVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  int eepromOdoAddress = EEPROM.getAddress(sizeof(float));



  // confirm eeprom has been written to

  Serial.print("Speedo title address = ");
  Serial.print(eepromTachoTitleAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  EEPROM.readBlock(eepromTachoTitleAddress, title);
  Serial.println(title);

  Serial.print("Speedo Version High address = ");
  Serial.print(eepromTachoVersionHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoVersionHighAddress));    

  Serial.print("Speedo Version High address = ");
  Serial.print(eepromTachoVersionLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoVersionLowAddress));    

  Serial.println();
  Serial.print("Odometer address = ");
  Serial.print(eepromOdoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readFloat(eepromOdoAddress));    

}

void loop () {

}


