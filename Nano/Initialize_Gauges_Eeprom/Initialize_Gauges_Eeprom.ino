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

  Serial.begin(115200);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  int eepromGaugesTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  int eepromGaugesVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeBlock(eepromGaugesTitleAddress, title);
  EEPROM.writeByte(eepromGaugesVersionHighAddress, versionHigh);
  EEPROM.writeByte(eepromGaugesVersionLowAddress, versionLow);

// Voltmeter
  int eepromGaugesVoltLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesVoltHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesVoltMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVoltMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVoltWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVoltWarnLowAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeInt(eepromGaugesVoltLowAddress, 0);
  EEPROM.writeInt(eepromGaugesVoltHighAddress, 1023);
  EEPROM.writeByte(eepromGaugesVoltMinAddress, 8);
  EEPROM.writeByte(eepromGaugesVoltMaxAddress, 16);
  EEPROM.writeByte(eepromGaugesVoltWarnAddress, 11);
  EEPROM.writeByte(eepromGaugesVoltWarnLowAddress, 1);


// Oil pressure meter  
  int eepromGaugesOilLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesOilHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesOilMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesOilMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesOilWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesOilWarnLowAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeInt(eepromGaugesOilLowAddress, 0);
  EEPROM.writeInt(eepromGaugesOilHighAddress, 1023);
  EEPROM.writeByte(eepromGaugesOilMinAddress, 0);
  EEPROM.writeByte(eepromGaugesOilMaxAddress, 100);
  EEPROM.writeByte(eepromGaugesOilWarnAddress, 60);
  EEPROM.writeByte(eepromGaugesOilWarnLowAddress, 1);

// Water Temperature meter
  int eepromGaugesTempLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesTempHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesTempMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesTempMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesTempWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesTempWarnLowAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeInt(eepromGaugesTempLowAddress, 0);
  EEPROM.writeInt(eepromGaugesTempHighAddress, 1023);
  EEPROM.writeByte(eepromGaugesTempMinAddress, 40);
  EEPROM.writeByte(eepromGaugesTempMaxAddress, 200);
  EEPROM.writeByte(eepromGaugesTempWarnAddress, 110);
  EEPROM.writeByte(eepromGaugesTempWarnLowAddress, 0);

// Fuel level meter
  int eepromGaugesFuelLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelSensorTypeAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeInt(eepromGaugesFuelLowAddress, 0);
  EEPROM.writeInt(eepromGaugesFuelHighAddress, 1023);
  EEPROM.writeByte(eepromGaugesFuelMinAddress, 0);
  EEPROM.writeByte(eepromGaugesFuelMaxAddress, 100);
  EEPROM.writeByte(eepromGaugesFuelWarnAddress, 10);
  EEPROM.writeByte(eepromGaugesFuelWarnLowAddress, 1);
  EEPROM.writeByte(eepromGaugesFuelSensorTypeAddress, 0);

								// This is
								// type	empty	full	description
								// 0	70	10	Ford pre 1986
								// 1	10	180	
								//
								//
								//

  int eepromGaugesDebugAddress = EEPROM.getAddress(sizeof(byte));
  EEPROM.writeByte(eepromGaugesDebugAddress, 0);

  // confirm eeprom has been written to


  Serial.print("Gauges title address = ");
  Serial.print(eepromGaugesTitleAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  EEPROM.readBlock(eepromGaugesTitleAddress, title);
  Serial.println(title);

  Serial.print("Gauges Version High address = ");
  Serial.print(eepromGaugesVersionHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesVersionHighAddress));    

  Serial.print("Gauges Version High address = ");
  Serial.print(eepromGaugesVersionLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesVersionLowAddress));    

// Voltmeter
  Serial.println();
  Serial.println("Voltmeter");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromGaugesVoltLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesVoltLowAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesVoltHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesVoltHighAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesVoltMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesVoltMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesVoltMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesVoltMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesVoltWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesVoltWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesVoltWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesVoltWarnLowAddress));    

// Oil Pressure Meter
  Serial.println();
  Serial.println("Oil Pressure");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromGaugesOilLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesOilLowAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesOilHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesOilHighAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesOilMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesOilMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesOilMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesOilMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesOilWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesOilWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesOilWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesOilWarnLowAddress));    

// Water Temperature Meter
  Serial.println();
  Serial.println("Water Temperature");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromGaugesTempLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesTempLowAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesTempHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesTempHighAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesTempMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesTempMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesTempMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesTempMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesTempWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesTempWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesTempWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesTempWarnLowAddress));    

// Fuel Level Meter
  Serial.println();
  Serial.println("Fuel Level");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesFuelLowAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesFuelHighAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesFuelMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesFuelMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesFuelWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesFuelWarnLowAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelSensorTypeAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesFuelSensorTypeAddress));

  Serial.print("Gauges Debug address = ");
  Serial.print(eepromGaugesDebugAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesDebugAddress));



}

void loop () {

}


