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
  int eepromGaugesTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  int eepromGaugesVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVersionLowAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeBlock(eepromGaugesTitleAddress, title);
  EEPROM.writeByte(eepromGaugesVersionHighAddress, versionHigh);
  EEPROM.writeByte(eepromGaugesVersionLowAddress, versionLow);

// Voltmeter
  int eepromGaugesVoltLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesVoltHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesVoltLowWarnAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesVoltHighWarnAddress = EEPROM.getAddress(sizeof(int));

  EEPROM.writeInt(eepromGaugesVoltLowAddress, 0);
  EEPROM.writeInt(eepromGaugesVoltHighAddress, 1023);
  EEPROM.writeInt(eepromGaugesVoltLowWarnAddress, 102);
  EEPROM.writeInt(eepromGaugesVoltHighWarnAddress, 921);


// Oil pressure meter  
  int eepromGaugesOilLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesOilHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesOilLowWarnAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesOilHighWarnAddress = EEPROM.getAddress(sizeof(int));

  EEPROM.writeInt(eepromGaugesOilLowAddress, 0);
  EEPROM.writeInt(eepromGaugesOilHighAddress, 1023);
  EEPROM.writeInt(eepromGaugesOilLowWarnAddress, 102);
  EEPROM.writeInt(eepromGaugesOilHighWarnAddress, 921);

// Water Temperature meter
  int eepromGaugesTempLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesTempHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesTempLowWarnAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesTempHighWarnAddress = EEPROM.getAddress(sizeof(int));

  EEPROM.writeInt(eepromGaugesTempLowAddress, 0);
  EEPROM.writeInt(eepromGaugesTempHighAddress, 0);
  EEPROM.writeInt(eepromGaugesTempLowWarnAddress, -1);
  EEPROM.writeInt(eepromGaugesTempHighWarnAddress, 921);

// Fuel level meter
  int eepromGaugesFuelLowAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelLowWarnAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelHighWarnAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelSensorTypeAddress = EEPROM.getAddress(sizeof(byte));

  EEPROM.writeInt(eepromGaugesFuelLowAddress, 0);
  EEPROM.writeInt(eepromGaugesFuelHighAddress, 1023);
  EEPROM.writeInt(eepromGaugesFuelLowWarnAddress, 102);
  EEPROM.writeInt(eepromGaugesFuelHighWarnAddress, -1);
  EEPROM.writeByte(eepromGaugesFuelSensorTypeAddress, 0);

								// This is
								// type	empty	full	description
								// 0	70	10	Ford pre 1986
								// 1	10	180	
								//
								//
								//

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
  Serial.print(eepromGaugesVoltLowWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesVoltLowWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesVoltHighWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesVoltHighWarnAddress));    

// Oil Pressure Meter
  Serial.println();
  Serial.println("Oil Pressure meter");
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
  Serial.print(eepromGaugesOilLowWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesOilLowWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesOilHighWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesOilHighWarnAddress));    

// Water Temperature Meter
  Serial.println();
  Serial.println("Water Temperature meter");
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
  Serial.print(eepromGaugesTempLowWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesTempLowWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesTempHighWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesTempHighWarnAddress));    

// Fuel Level Meter
  Serial.println();
  Serial.println("Fuel Level meter");
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
  Serial.print(eepromGaugesFuelLowWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesFuelLowWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelHighWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromGaugesFuelHighWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromGaugesFuelSensorTypeAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesFuelSensorTypeAddress));

}

void loop () {

}


