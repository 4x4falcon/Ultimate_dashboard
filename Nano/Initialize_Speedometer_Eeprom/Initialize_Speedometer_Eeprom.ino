/*
 * Initalize eeprom for speedometer
 *
 * This only needs to be run on initial construction of speedometer
 *
 *
 */

#include <EEPROMex.h>
#include <EEPROMVar.h>

#include "Version.h";

void setup () {

  Serial.begin(115200);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  int eepromSpeedoTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  int eepromSpeedoVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  int eepromSpeedoVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  int eepromOdoAddress = EEPROM.getAddress(sizeof(long));
  int eepromTrip1Address = EEPROM.getAddress(sizeof(long));
  int eepromTrip2Address = EEPROM.getAddress(sizeof(long));

  int eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(float));

  int eepromModeFuncAddress = EEPROM.getAddress(sizeof(byte));

  int eepromDebugAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeBlock(eepromSpeedoTitleAddress, title);
  EEPROM.writeByte(eepromSpeedoVersionHighAddress, versionHigh);
  EEPROM.writeByte(eepromSpeedoVersionLowAddress, versionLow);

  EEPROM.writeLong(eepromOdoAddress, 0UL);
  EEPROM.writeLong(eepromTrip1Address, 0UL);
  EEPROM.writeLong(eepromTrip2Address, 0UL);

  // This is the distance per pulse in km
  // the value here is calculated from the following
  // wheel/tyre combination is 33x12.5R15 or (318/72R5)
  //
  // pulses per revolution of vehicle speed sensor = ppr =	10
  // this needs to have hardware /10 circuit
  // circumference of wheel/tyre in meters = cir =		2.63144
  // final drive ratio of diff = ratio =			3.5
  // formula is
  // (1000m/cir) * ratio * ppr
  // for each kilometer there are (1000/cir) turns of the wheel
  // for each turn of the wheel the drive shaft turns ratio times
  // for each turn of the driveshaft there are ppr pulses
  // therefore for this tyre/wheel diff combo the result is:
  // (1000/2.63144) * 3.5 * 10
  // equals
  // 13300.7 pulses per kilometer
  // 13293.0549211603
  //
  // this is
  // 0.075227m per pulse
  //
  // to get odometer or trip reading multiply this by the number in eeprom
  //
  // 
  //
  // when calibrated in the speedo program it is for 1 kilometer or mile

  // NOTE if you are using a sensor that is on the wheel/tyre the final drive ratio is 1

  EEPROM.writeFloat(eepromSpeedoCalibrateAddress, 0.075227);  

  EEPROM.writeByte(eepromModeFuncAddress, 0);

  EEPROM.writeByte(eepromDebugAddress, 0);

  // confirm eeprom has been written to

  Serial.print("Speedo title address = ");
  Serial.print(eepromSpeedoTitleAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  EEPROM.readBlock(eepromSpeedoTitleAddress, title);
  Serial.println(title);

  Serial.print("Speedo Version High address = ");
  Serial.print(eepromSpeedoVersionHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromSpeedoVersionHighAddress));    

  Serial.print("Speedo Version Low address = ");
  Serial.print(eepromSpeedoVersionLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromSpeedoVersionLowAddress));    

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
  Serial.println(EEPROM.readFloat(eepromSpeedoCalibrateAddress));    

  Serial.print("Speedo Mode address = ");
  Serial.print(eepromModeFuncAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromModeFuncAddress));    

  Serial.print("Speedo debug address = ");
  Serial.print(eepromDebugAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromDebugAddress));    

}

void loop () {

}


