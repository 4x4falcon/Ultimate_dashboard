/*
 * Eeprom.h
 */

void getEepromAddresses()
 {
  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  eepromVersionHighAddress = EEPROM.getAddress(sizeof(byte));
  eepromVersionLowAddress = EEPROM.getAddress(sizeof(byte));

// Voltmeter
  eepromVoltLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromVoltMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromVoltWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromVoltWarnLowAddress = EEPROM.getAddress(sizeof(byte));

// Oil pressure meter  
  eepromOilLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromOilUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromOilMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromOilMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromOilWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromOilWarnLowAddress = EEPROM.getAddress(sizeof(byte));

// Water Temperature meter
  eepromTempLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromTempUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromTempMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempWarnLowAddress = EEPROM.getAddress(sizeof(byte));

// Fuel level meter
  eepromFuelLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelMinAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelMaxAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelWarnAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelSensorTypeAddress = EEPROM.getAddress(sizeof(byte));

  eepromGaugesDebugAddress = EEPROM.getAddress(sizeof(byte));

  eepromGaugesDemoAddress = EEPROM.getAddress(sizeof(byte));
 }


#ifdef GAUGES
void getEepromValues()
 {

  EEPROM.readBlock(eepromTitle, title);
  versionHigh = EEPROM.readByte(eepromVersionHigh);
  versionLow  = EEPROM.readByte(eepromVersionLow);

// Voltmeter
  voltLower = EEPROM.readInt(eepromVoltLowerAddress);
  voltUpper = EEPROM.readInt(eepromVoltUpperAddress);
  voltMin = EEPROM.readInt(eepromVoltMinAddress);
  voltMax = EEPROM.readInt(eepromVoltMaxAddress);
  
  voltWarn = EEPROM.readInt(eepromVoltWarnAddress);
  voltWarnLow = EEPROM.readByte(eepromVoltWarnLowAddress);

// Oil pressure meter  
  oilLower = EEPROM.readInt(eepromOilLowerAddress);
  oilUpper = EEPROM.readInt(eepromOilUpperAddress);
  oilMin = EEPROM.readInt(eepromOilMinAddress);
  oilMax = EEPROM.readInt(eepromOilMaxAddress);
  
  oilWarn = EEPROM.readInt(eepromOilWarnAddress);
  oilWarnLow = EEPROM.readByte(eepromOilWarnLowAddress);

// Water Temperature meter
  tempLower = EEPROM.readInt(eepromTempLowerAddress);
  tempUpper = EEPROM.readInt(eepromTempUpperAddress);
  tempMin = EEPROM.readInt(eepromTempMinAddress);
  tempMax = EEPROM.readInt(eepromTempMaxAddress);
  
  tempWarn = EEPROM.readInt(eepromTempWarnAddress);
  tempWarnLow = EEPROM.readByte(eepromTempWarnLowAddress);

// Fuel level meter
  fuelLower = EEPROM.readInt(eepromFuelLowerAddress);
  fuelUpper = EEPROM.readInt(eepromFuelUpperAddress);
  fuelMin = EEPROM.readInt(eepromFuelMinAddress);
  fuelMax = EEPROM.readInt(eepromFuelMaxAddress);
  
  fuelWarn = EEPROM.readInt(eepromFuelWarnAddress);
  fuelWarnLow = EEPROM.readByte(eepromFuelWarnLowAddress);
  fuelSenderType = EEPROM.readByte(eepromFuelSensorTypeAddress);

  debug = EEPROM.readByte(eepromGaugesDebugAddress);

  demo = EEPROM.readByte(eepromGaugesDemoAddress);
 }
#endif

