/*
 * Initalize eeprom for gauges
 *
 * This only needs to be run on initial construction of the gauges
 *
 *
 */

#define INITIALIZE_GAUGES


#include <EEPROMex.h>
#include <EEPROMVar.h>

#include "Variables.h"
#include "Version.h"
#include "Eeprom.h"

void setup () {

  Serial.begin(115200);

/*
  // Get eeprom storage addresses MUST be before anything else and in the same order
  int eepromGaugesTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  int eepromGaugesVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVersionLowAddress = EEPROM.getAddress(sizeof(byte));

// Voltmeter
  int eepromGaugesVoltLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesVoltHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesVoltMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVoltMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVoltWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesVoltWarnLowAddress = EEPROM.getAddress(sizeof(byte));

// Oil pressure meter  
  int eepromGaugesOilLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesOilHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesOilMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesOilMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesOilWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesOilWarnLowAddress = EEPROM.getAddress(sizeof(byte));


// Water Temperature meter
  int eepromGaugesTempLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesTempHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesTempMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesTempMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesTempWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesTempWarnLowAddress = EEPROM.getAddress(sizeof(byte));


// Fuel level meter
  int eepromGaugesFuelLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelHighAddress = EEPROM.getAddress(sizeof(int));
  int eepromGaugesFuelMinAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelMaxAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelWarnAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  int eepromGaugesFuelSensorTypeAddress = EEPROM.getAddress(sizeof(byte));

  int eepromGaugesDebugAddress = EEPROM.getAddress(sizeof(byte));

  int eepromGaugesDemoAddress = EEPROM.getAddress(sizeof(byte));

*/

  getEepromAddresses();

  EEPROM.writeBlock(eepromTitleAddress, title);
  EEPROM.writeByte(eepromVersionHighAddress, versionHigh);
  EEPROM.writeByte(eepromVersionLowAddress, versionLow);

  EEPROM.writeInt(eepromVoltLowerAddress, 0);
  EEPROM.writeInt(eepromVoltUpperAddress, 1023);
  EEPROM.writeByte(eepromVoltMinAddress, 8);
  EEPROM.writeByte(eepromVoltMaxAddress, 16);
  EEPROM.writeByte(eepromVoltWarnAddress, 11);
  EEPROM.writeByte(eepromVoltWarnLowAddress, 1);

  EEPROM.writeInt(eepromOilLowerAddress, 0);
  EEPROM.writeInt(eepromOilUpperAddress, 1023);
  EEPROM.writeByte(eepromOilMinAddress, 0);
  EEPROM.writeByte(eepromOilMaxAddress, 100);
  EEPROM.writeByte(eepromOilWarnAddress, 60);
  EEPROM.writeByte(eepromOilWarnLowAddress, 1);

  EEPROM.writeInt(eepromTempLowerAddress, 0);
  EEPROM.writeInt(eepromTempUpperAddress, 1023);
  EEPROM.writeByte(eepromTempMinAddress, 40);
  EEPROM.writeByte(eepromTempMaxAddress, 200);
  EEPROM.writeByte(eepromTempWarnAddress, 110);
  EEPROM.writeByte(eepromTempWarnLowAddress, 0);

  EEPROM.writeInt(eepromFuelLowerAddress, 0);
  EEPROM.writeInt(eepromFuelUpperAddress, 1023);
  EEPROM.writeByte(eepromFuelMinAddress, 0);
  EEPROM.writeByte(eepromFuelMaxAddress, 100);
  EEPROM.writeByte(eepromFuelWarnAddress, 10);
  EEPROM.writeByte(eepromFuelWarnLowAddress, 1);
  EEPROM.writeByte(eepromFuelSensorTypeAddress, 0);

								// This is
								// type	empty	full	description
								// 0	70	10	Ford pre 1986
								// 1	10	180	
								//
								//
								//

  EEPROM.writeByte(eepromGaugesDebugAddress, 0);

  EEPROM.writeByte(eepromGaugesDemoAddress, 0);

  // confirm eeprom has been written to


  Serial.print("Gauges title address = ");
  Serial.print(eepromTitleAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  EEPROM.readBlock(eepromTitleAddress, title);
  Serial.println(title);

  Serial.print("Gauges Version High address = ");
  Serial.print(eepromVersionHighAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVersionHighAddress));    

  Serial.print("Gauges Version Low address = ");
  Serial.print(eepromVersionLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVersionLowAddress));    

// Voltmeter
  Serial.println();
  Serial.println("Voltmeter");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromVoltLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromVoltLowerAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromVoltUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromVoltUpperAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromVoltMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVoltMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromVoltMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVoltMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromVoltWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVoltWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromVoltWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVoltWarnLowAddress));    

// Oil Pressure Meter
  Serial.println();
  Serial.println("Oil Pressure");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromOilLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromOilLowerAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromOilUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromOilUpperAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromOilMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromOilMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromOilMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromOilMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromOilWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromOilWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromOilWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromOilWarnLowAddress));    

// Water Temperature Meter
  Serial.println();
  Serial.println("Water Temperature");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromTempLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromTempLowerAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromTempUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromTempUpperAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromTempMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTempMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromTempMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTempMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromTempWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTempWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromTempWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTempWarnLowAddress));    

// Fuel Level Meter
  Serial.println();
  Serial.println("Fuel Level");
  Serial.println();
  Serial.print(" Address = ");
  Serial.print(eepromFuelLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromFuelLowerAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromFuelUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readInt(eepromFuelUpperAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromFuelMinAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromFuelMinAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromFuelMaxAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromFuelMaxAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromFuelWarnAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromFuelWarnAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromFuelWarnLowAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromFuelWarnLowAddress));    
  Serial.print(" Address = ");
  Serial.print(eepromFuelSensorTypeAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromFuelSensorTypeAddress));

  Serial.print("Gauges Debug address = ");
  Serial.print(eepromGaugesDebugAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesDebugAddress));

  Serial.print("Gauges Demo address = ");
  Serial.print(eepromGaugesDemoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromGaugesDemoAddress));


}

void loop () {

}


