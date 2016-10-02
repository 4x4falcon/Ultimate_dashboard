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
  
  eepromTempLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromTempUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromTempMinAddress = EEPROM.getAddress(sizeof(int));
  eepromTempMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromTempWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromTempWarnLowAddress = EEPROM.getAddress(sizeof(byte));
  
  eepromFuelLowerAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelUpperAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelMinAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelMaxAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelWarnAddress = EEPROM.getAddress(sizeof(int));
  eepromFuelWarnLowAddress = EEPROM.getAddress(sizeof(byte));


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
  totalOdometer = EEPROM.readLong(eepromOdoAddress);

/*
#ifdef DEBUGGING
  Serial.println("in getEepromValues");
  sprintf(buffer, "%20d", eepromOdoAddress);
  Serial.print("eepromOdoAddress = ");
  Serial.println(buffer);
  sprintf(buffer, "%20d", totalOdometer);
  Serial.print("totalOdometer = ");
  Serial.println(buffer);
  Serial.println("");
#endif
*/

  // Read tripmeter 1 value from flash memory
  totalTrip_1 = EEPROM.readLong(eepromTrip1Address);

  // Read tripmeter 2 value from flash memory
  totalTrip_2 = EEPROM.readLong(eepromTrip2Address);



  // calculate pulse distance
  // calibration is over 2 kilometers or miles but is stored as for 1 kilometer or mile
  // formula is 1 / (calibration value in eeprom)
  // this gives distance travelled in one pulse from the sensor
  // in meters if kilometer or part of mile

/*
#ifdef DEBUGGING
  Serial.println("in getEepromValues");
  sprintf(buffer, "%6d", eepromSpeedoCalibrateAddress);
  Serial.print("before eepromSpeedoCalibrateAddress = ");
  Serial.println(buffer);
#endif
*/

  speedoCalibrate = (float)EEPROM.readLong(eepromSpeedoCalibrateAddress) / (float)SPEEDO_CALIBRATE_DIVIDER;

  pulseDistance = 1000.0 / speedoCalibrate;

/*
#ifdef DEBUGGING
  Serial.println("in get eeprom data");
  sprintf(buffer, "%6d", eepromSpeedoCalibrateAddress);
  Serial.print("eepromSpeedoCalibrateAddress = ");
  Serial.println(buffer);
  dtostrf(speedoCalibrate,9,3,buffer);
  Serial.print("speedoCalibrate = ");
  Serial.println(buffer);
  dtostrf(pulseDistance,9,3,buffer);
  Serial.print("pulseDistance = ");
  Serial.println(buffer);
#endif
*/

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
  voltWarn = EEPROM.readInt(eepromVoltWarnAddress);
  voltWarnLow = EEPROM.readInt(eepromVoltWarnLowAddress);

  oilLower = EEPROM.readInt(eepromOilLowerAddress);
  oilUpper = EEPROM.readInt(eepromOilUpperAddress);
  oilMin = EEPROM.readInt(eepromOilMinAddress);
  oilMax = EEPROM.readInt(eepromOilMaxAddress);
  oilWarn = EEPROM.readInt(eepromOilWarnAddress);
  oilWarnLow = EEPROM.readInt(eepromOilWarnLowAddress);

  tempLower = EEPROM.readInt(eepromTempLowerAddress);
  tempUpper = EEPROM.readInt(eepromTempUpperAddress);
  tempMin = EEPROM.readInt(eepromTempMinAddress);
  tempMax = EEPROM.readInt(eepromTempMaxAddress);
  tempWarn = EEPROM.readInt(eepromTempWarnAddress);
  tempWarnLow = EEPROM.readInt(eepromTempWarnLowAddress);

  fuelLower = EEPROM.readInt(eepromFuelLowerAddress);
  fuelUpper = EEPROM.readInt(eepromFuelUpperAddress);
  fuelMin = EEPROM.readInt(eepromFuelMinAddress);
  fuelMax = EEPROM.readInt(eepromFuelMaxAddress);
  fuelWarn = EEPROM.readInt(eepromFuelWarnAddress);
  fuelWarnLow = EEPROM.readInt(eepromFuelWarnLowAddress);

  debugAll = EEPROM.readByte(eepromDebugAllAddress);
  debugSpeedo = EEPROM.readByte(eepromDebugSpeedoAddress);
  debugTacho = EEPROM.readByte(eepromDebugTachoAddress);
  debugGauges = EEPROM.readByte(eepromDebugGaugesAddress);

  demoAll = EEPROM.readByte(eepromDemoAllAddress);
  demoSpeedo = EEPROM.readByte(eepromDemoSpeedoAddress);
  demoTacho = EEPROM.readByte(eepromDemoTachoAddress);
  demoGauges = EEPROM.readByte(eepromDemoGaugesAddress);

 }
#endif

