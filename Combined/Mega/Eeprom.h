/*
 * Eeprom.h
 */

void getEepromAddresses()
 {
  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitleAddress = EEPROM.getAddress(sizeof(title));
  eepromVersionHigh = EEPROM.getAddress(sizeof(byte));
  eepromVersionLow = EEPROM.getAddress(sizeof(byte));

  eepromOdoAddress = EEPROM.getAddress(sizeof(long));
  eepromTrip1Address = EEPROM.getAddress(sizeof(long));
  eepromTrip2Address = EEPROM.getAddress(sizeof(long));

  eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(long));
  eepromSpeedoModeFuncAddress = EEPROM.getAddress(sizeof(byte));

/*
#ifdef DEBUGGING
  Serial.println("in getEepromAddresses");
  sprintf(buffer, "%6d", eepromSpeedoCalibrateAddress);
  Serial.print("eepromSpeedoCalibrateAddress = ");
  Serial.println(buffer);
  Serial.println("");
#endif
*/
  eepromTachoPPRAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoTypeAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoRedlineAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoShiftAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoMaximumAddress = EEPROM.getAddress(sizeof(int));
  eepromTachoCalibrateAddress = EEPROM.getAddress(sizeof(int));

  eepromVoltLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltMinAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromVoltWarnLowAddress = EEPROM.getAddress(sizeof(byte));

  eepromOilLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromOilUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromOilMinAddress = EEPROM.getAddress(sizeof(int));
  eepromOilMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromOilWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromOilWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  eepromOilInvertedAddress = EEPROM.getAddress(sizeof(byte));
  
  eepromTempLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromTempUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromTempMinAddress = EEPROM.getAddress(sizeof(int));
  eepromTempMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromTempWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromTempWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempInvertedAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempCelciusAddress = EEPROM.getAddress(sizeof(byte));
  eepromTempFanOneOnAddress = EEPROM.getAddress(sizeof(int));
  eepromTempFanOneOffAddress = EEPROM.getAddress(sizeof(int));
  eepromTempFanTwoOnAddress = EEPROM.getAddress(sizeof(int));
  eepromTempFanTwoOffAddress = EEPROM.getAddress(sizeof(int));

  eepromFuelLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelMinAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  eepromFuelInvertedAddress = EEPROM.getAddress(sizeof(byte));

#ifdef INCLUDE_EGT
  eepromEgtLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromEgtUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromEgtMinAddress = EEPROM.getAddress(sizeof(int));
  eepromEgtMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromEgtWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromEgtWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  eepromEgtInvertedAddress = EEPROM.getAddress(sizeof(byte));
  eepromEgtCelciusAddress = EEPROM.getAddress(sizeof(byte));
#endif

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

 }

#ifdef MEGA
/*
 * read values stored in eeprom and calculate values based on these
 */

void getEepromValues ()
 {
  // title and version from eeprom

  EEPROM.readBlock(eepromTitleAddress, title);
  versionHigh = EEPROM.readByte(eepromVersionHigh);
  versionLow = EEPROM.readByte(eepromVersionLow);

  // Read odometer value from flash memory
  extEepromOdometer.totalOdometer = EEPROM.readLong(eepromOdoAddress);

  // Read tripmeter 1 value from flash memory
  totalTrip_1 = EEPROM.readLong(eepromTrip1Address);

  // Read tripmeter 2 value from flash memory
  totalTrip_2 = EEPROM.readLong(eepromTrip2Address);



  // calculate pulse distance
  // calibration is over 2 kilometers or miles but is stored as for 1 kilometer or mile
  // formula is 1 / (calibration value in eeprom)
  // this gives distance travelled in one pulse from the sensor
  // in meters if kilometer or part of mile

  speedoCalibrate = (float)EEPROM.readLong(eepromSpeedoCalibrateAddress) / (float)SPEEDO_CALIBRATE_DIVIDER;

  pulseDistance = 1000.0 / speedoCalibrate;

  // get mode function set this should only be FUNC_KPH or FUNC_MPH
  // if set to FUNC_CAL then reset to FUNC_KPH
  modeSpeedoFunc = EEPROM.readByte(eepromSpeedoModeFuncAddress);
  if (modeSpeedoFunc == FUNC_CAL)
   {
    modeSpeedoFunc = FUNC_KPH;
   }

  tachoPPR = EEPROM.readByte(eepromTachoPPRAddress);
  tachoType = EEPROM.readByte(eepromTachoTypeAddress);
  tachoRedline = EEPROM.readInt(eepromTachoRedlineAddress);
  tachoShift = EEPROM.readInt(eepromTachoShiftAddress);
  tachoMaximum = EEPROM.readInt(eepromTachoMaximumAddress);
  tachoCalibrate = EEPROM.readInt(eepromTachoCalibrateAddress);

  tachoStep = tachoMaximum / numTachoLeds;


  // get constants for gauges
  
  voltLower = EEPROM.readInt(eepromVoltLowerAddress);
  voltUpper = EEPROM.readInt(eepromVoltUpperAddress);
  voltMin = EEPROM.readInt(eepromVoltMinAddress);
  voltMax = EEPROM.readInt(eepromVoltMaxAddress);
  voltWarn = EEPROM.readByte(eepromVoltWarnAddress);
  voltWarnLow = EEPROM.readByte(eepromVoltWarnLowAddress);

  oilLower = EEPROM.readInt(eepromOilLowerAddress);
  oilUpper = EEPROM.readInt(eepromOilUpperAddress);
  oilMin = EEPROM.readInt(eepromOilMinAddress);
  oilMax = EEPROM.readInt(eepromOilMaxAddress);
  oilWarn = EEPROM.readByte(eepromOilWarnAddress);
  oilWarnLow = EEPROM.readByte(eepromOilWarnLowAddress);
  oilInverted = EEPROM.readByte(eepromOilInvertedAddress);

  tempLower = EEPROM.readInt(eepromTempLowerAddress);
  tempUpper = EEPROM.readInt(eepromTempUpperAddress);
  tempMin = EEPROM.readInt(eepromTempMinAddress);
  tempMax = EEPROM.readInt(eepromTempMaxAddress);
  tempWarn = EEPROM.readByte(eepromTempWarnAddress);
  tempFanOneOn = EEPROM.readInt(eepromTempFanOneOnAddress);
  tempFanOneOff = EEPROM.readInt(eepromTempFanOneOffAddress);
  tempFanTwoOn = EEPROM.readInt(eepromTempFanTwoOnAddress);
  tempFanTwoOff = EEPROM.readInt(eepromTempFanTwoOffAddress);
  tempWarnLow = EEPROM.readByte(eepromTempWarnLowAddress);
  tempCelcius = EEPROM.readByte(eepromTempCelciusAddress);
  tempInverted = EEPROM.readByte(eepromTempInvertedAddress);

  fuelLower = EEPROM.readInt(eepromFuelLowerAddress);
  fuelUpper = EEPROM.readInt(eepromFuelUpperAddress);
  fuelMin = EEPROM.readInt(eepromFuelMinAddress);
  fuelMax = EEPROM.readInt(eepromFuelMaxAddress);
  fuelWarn = EEPROM.readByte(eepromFuelWarnAddress);
  fuelWarnLow = EEPROM.readByte(eepromFuelWarnLowAddress);
  fuelInverted = EEPROM.readByte(eepromFuelInvertedAddress);

#ifdef INCLUDE_EGT
  egtLower = EEPROM.readInt(eepromEgtLowerAddress);
  egtUpper = EEPROM.readInt(eepromEgtUpperAddress);
  egtMin = EEPROM.readInt(eepromEgtMinAddress);
  egtMax = EEPROM.readInt(eepromEgtMaxAddress);
  egtWarn = EEPROM.readByte(eepromEgtWarnAddress);
  egtWarnLow = EEPROM.readByte(eepromEgtWarnLowAddress);
  egtInverted = EEPROM.readByte(eepromEgtInvertedAddress);
#endif

  debugAll = EEPROM.readByte(eepromDebugAllAddress);
  debugSpeedo = EEPROM.readByte(eepromDebugSpeedoAddress);
  debugTacho = EEPROM.readByte(eepromDebugTachoAddress);
  debugGauges = EEPROM.readByte(eepromDebugGaugesAddress);

  demoAll = EEPROM.readByte(eepromDemoAllAddress);
  demoSpeedo = EEPROM.readByte(eepromDemoSpeedoAddress);
  demoTacho = EEPROM.readByte(eepromDemoTachoAddress);
  demoGauges = EEPROM.readByte(eepromDemoGaugesAddress);

 }


/*
 * get odometer reading from external eeprom
 */

bool getExtEepromValues()
 {
  if (extEepromAvailable)
   {
    speedoEeprom.read(EXT_EEPROM_ADDRESS_ODOMETER, (byte *)&extEepromOdometer.extEepromTotalOdometer, 4); 
   
   }

#ifdef DEBUGGING
  Serial.println("bytes ");
  Serial.print(extEepromOdometer.extEepromTotalOdometer[3], HEX);
  Serial.print(" ");
  Serial.print(extEepromOdometer.extEepromTotalOdometer[2], HEX);
  Serial.print(" ");
  Serial.print(extEepromOdometer.extEepromTotalOdometer[1], HEX);
  Serial.print(" ");
  Serial.print(extEepromOdometer.extEepromTotalOdometer[0], HEX);
  Serial.print(" ");
  Serial.println();
#endif

 }
#endif    // MEGA

