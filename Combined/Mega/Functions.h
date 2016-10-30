/* Functions.h
 *  
 */

/*
  TODO

  This is the sleep function
  It will be activated when the ignition is turned off.
  It needs to write odo and trip values to the eeprom
  Will wake up on ignition turned on

*/

void goToSleep() {

  // write the odometer to EEPROM

  if (extEepromOdometer.totalOdometer > EEPROM.readLong(eepromOdoAddress))
  {

#ifdef SERIAL_DEBUG
    if (debugAll > 0)
     {
      Serial.print(F("Saving odometer to EEPROM    "));
      Serial.println (extEepromOdometer.totalOdometer);
     }
    else
#endif
     {
      EEPROM.writeLong(eepromOdoAddress, extEepromOdometer.totalOdometer);
     }
  }

  // write the tripmeters to EEPROM
  writeTripmeter();

  // write the modeSpeedoFunc to EEPROM
  EEPROM.writeByte(eepromSpeedoModeFuncAddress, modeSpeedoFunc);

}


// scan i2c bus

void scanI2cBus(bool all)
 {
  byte error, address;
  int nDevices;

  Serial.println(F("Scanning..."));

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
   
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (all)
     {
      Serial.print(F("Address ... "));
      Serial.println(address,HEX);
     }

    if (error == 0)
    {
      Serial.print(F("I2C device found at address 0x"));
      if (address<16) 
        Serial.print(F("0"));
      Serial.print(address,HEX);
      Serial.println(F("  !"));

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print(F("Unknow error at address 0x"));
      if (address<16) 
        Serial.print(F("0"));
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
   {
    Serial.println(F("No I2C devices found\n"));
   }
  else
   {
    Serial.println(F("done\n"));
   }
 }


/* 
 * change or view variables
 */

void doVariables(String readString)
 {
  unsigned long p = 0;

  if (sendBluetooth)
   {
    unsigned long sp = &Serial1;
   }
  else
   {
    unsigned long sp = &Serial;
   }

  int pos = readString.indexOf("=");
  if (pos > 0)
  {

    String c = readString.substring(1, pos);
    int command = c.toInt();
    String parameter = readString.substring(pos + 1);
    p = parameter.toInt();

    switch (command)
    {
      case 100:
        if (parameter == "")
        {
          float c = (float)EEPROM.readLong(eepromSpeedoCalibrateAddress) / (float)SPEEDO_CALIBRATE_DIVIDER;
          dtostrf(c, 10, 8, buffer);
          Serial.print((char *)F("($100)Speedo calibration = "));
          Serial.println(EEPROM.readLong(eepromSpeedoCalibrateAddress));
          Serial.print((char *)F("($100)Speedo calibration as float = "));
          Serial.println(buffer);
        }
        else
        {
          Serial.print(F("Setting ($100) Speedo calibration = "));
          Serial.println(parameter);

          EEPROM.writeLong(eepromSpeedoCalibrateAddress, p);
//          getEepromValues();
        }
        break;
      case 102:
        if (parameter == "")
        {
          Serial.print(F("($102)Tripmeter 1 value = "));
          Serial.println(EEPROM.readLong(eepromTrip1Address));
        }
        else
        {
          Serial.print(F("Setting ($102) Tripmeter 1 value = "));
          Serial.println(parameter);
          EEPROM.writeLong(eepromTrip1Address, p);
        }
        break;
      case 103:
        if (parameter == "")
        {
          Serial.print(F("($103)Tripmeter 2 value = "));
          Serial.println(EEPROM.readLong(eepromTrip2Address));
        }
        else
        {
          Serial.print(F("Setting ($103) Tripmeter 2 value = "));
          Serial.println(parameter);
          EEPROM.writeLong(eepromTrip2Address, p);
        }
        break;

      case 104:
        if (parameter == "")
        {
          Serial.print(F("($104)Speedo Mode Function = "));
          Serial.println(EEPROM.readByte(eepromSpeedoModeFuncAddress));
        }
        else
         {
          if (p <= FUNC_CAL)
           {
            Serial.print(F("Setting ($104) Speedo Mode Function = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromSpeedoModeFuncAddress, p);
            modeSpeedoFunc = p;
           }
          else
           {
            Serial.println(F("ERROR: Invalid value"));
           }
        }
        break;



      // tacho
      case 200:
        if (parameter == "")
        {
          Serial.print(F("($200)Tachometer PPR value = "));
          Serial.println(EEPROM.readByte(eepromTachoPPRAddress));
        }
        else
        {
          Serial.print(F("Setting ($200) Tachometer PPR value = "));
          Serial.println(parameter);
          // EEPROM.writeByte(eepromTachoPPRAddress, p);
        }
        break;
      case 201:
        if (parameter == "")
        {
          Serial.print(F("($201)Tachometer type value = "));
          Serial.println(EEPROM.readByte(eepromTachoTypeAddress));
        }
        else
        {
          Serial.print(F("Setting ($201) Tacho type value = "));
          Serial.println(parameter);
          // EEPROM.writeByte(eepromTachoTypeAddress, p);
        }
        break;

      case 202:
        if (parameter == "")
        {
          Serial.print(F("($202)Tachometer Redline value = "));
          Serial.println(EEPROM.readInt(eepromTachoRedlineAddress));
        }
        else
        {
          Serial.print(F("Setting ($202) Tacho redline value = "));
          Serial.println(parameter);
          // EEPROM.writeInt(eepromTachoRedlineAddress, p);
        }
        break;

      case 203:
        if (parameter == "")
        {
          Serial.print(F("($203)Tacho Shift = "));
          Serial.println(EEPROM.readInt(eepromTachoShiftAddress));
        }
        else
        {
          Serial.print(F("Setting ($203) Tacho Shift value = "));
          Serial.println(parameter);
          // EEPROM.writeInt(eepromTachoShiftAddress, p);
        }
        break;

      case 204:
        if (parameter == "")
        {
          Serial.print(F("($204)Tacho Maximum = "));
          Serial.println(EEPROM.readInt(eepromTachoMaximumAddress));
        }
        else
        {
          Serial.print(F("Setting ($204) Tacho Maximum value = "));
          Serial.println(parameter);
          // EEPROM.writeInt(eepromTachoMaximumAddress, p);
        }
        break;

      case 205:
        if (parameter == "")
        {
          Serial.print(F("($205)Tacho calibrate value = "));
          Serial.println(EEPROM.readInt(eepromTachoCalibrateAddress));
        }
        else
        {
          Serial.print(F("Setting ($205) Tacho Calibrate value = "));
          Serial.println(parameter);
          // EEPROM.writeInt(eepromTachoCalibrateAddress, p);
        }
        break;



      // Voltmeter
      case 300:
        if (parameter == "")
        {
          Serial.print(F("($300)Voltmeter lower value = "));
          Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
        }
        else
        {
          Serial.print(F("Setting ($300) Voltmeter Lower value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromVoltLowerAddress, p);
        }
        break;
      case 301:
        if (parameter == "")
        {
          Serial.print(F("($301)Voltmeter upper value = "));
          Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
        }
        else
        {
          Serial.print(F("Setting ($301) Voltmeter Upper value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromVoltUpperAddress, p);
        }
        break;
      case 302:
        if (parameter == "")
        {
          Serial.print(F("($302)Voltmeter min value = "));
          Serial.println(EEPROM.readInt(eepromVoltMinAddress));
        }
        else
        {
          Serial.print(F("Setting ($302) Voltmeter min value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromVoltMinAddress, p);
        }
        break;
      case 303:
        if (parameter == "")
        {
          Serial.print(F("($303)Voltmeter max value = "));
          Serial.println(EEPROM.readInt(eepromVoltMaxAddress));
        }
        else
        {
          Serial.print(F("Setting ($303) Voltmeter max value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromVoltMaxAddress, p);
        }
        break;
      case 304:
        if (parameter == "")
        {
          Serial.print(F("($304)Voltmeter warn value = "));
          Serial.println(EEPROM.readInt(eepromVoltWarnAddress));
        }
        else
        {
          Serial.print(F("Setting ($304) Voltmeter warn value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromVoltWarnAddress, p);
        }
        break;
      case 305:
        if (parameter == "")
        {
          Serial.print(F("($305)Voltmeter warn low value = "));
          Serial.println(EEPROM.readInt(eepromVoltWarnLowAddress));
        }
        else
        {
          Serial.print(F("Setting ($305) Voltmeter warn low value = "));
          Serial.println(parameter);
          EEPROM.writeByte(eepromVoltWarnLowAddress, p);
        }
        break;


      // Oil pressure meter
      case 400:
        if (parameter == "")
        {
          Serial.print(F("($400)Oil Pressure meter lower value = "));
          Serial.println(EEPROM.readInt(eepromOilLowerAddress));
        }
        else
        {
          Serial.print(F("Setting ($400) Oil Pressure Lower value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromOilLowerAddress, p);
        }
        break;
      case 401:
        if (parameter == "")
        {
          Serial.print(F("($401)Oil Pressure upper value = "));
          Serial.println(EEPROM.readInt(eepromOilUpperAddress));
        }
        else
        {
          Serial.print(F("Setting ($401) Oil Pressure Upper value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromOilUpperAddress, p);
        }
        break;
      case 402:
        if (parameter == "")
        {
          Serial.print(F("($402) Oil Pressure min value = "));
          Serial.println(EEPROM.readInt(eepromOilMinAddress));
        }
        else
        {
          Serial.print(F("Setting ($402) Oil Pressure min value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromOilMinAddress, p);
        }
        break;
      case 403:
        if (parameter == "")
        {
          Serial.print(F("($403) Oil Pressure max value = "));
          Serial.println(EEPROM.readInt(eepromOilMaxAddress));
        }
        else
        {
          Serial.print(F("Setting ($403) Oil Pressure max value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromOilMaxAddress, p);
        }
        break;
      case 404:
        if (parameter == "")
        {
          Serial.print(F("($404) Oil Pressure warn value = "));
          Serial.println(EEPROM.readInt(eepromOilWarnAddress));
        }
        else
        {
          Serial.print(F("Setting ($404) Oil Pressure warn value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromOilWarnAddress, p);
        }
        break;
      case 405:
        if (parameter == "")
        {
          Serial.print(F("($405) Oil Pressure warn low value = "));
          Serial.println(EEPROM.readInt(eepromOilWarnLowAddress));
        }
        else
        {
          Serial.print(F("Setting ($404) Oil Pressure warn low value = "));
          Serial.println(parameter);
          EEPROM.writeByte(eepromOilWarnLowAddress, p);
        }
        break;
      case 406:
        if (parameter == "")
        {
          Serial.print(F("($406) Oil Pressure inverted value = "));
          Serial.println(EEPROM.readInt(eepromOilInvertedAddress));
        }
        else
        {
          Serial.print(F("Setting ($406) Oil Pressure inverted value = "));
          Serial.println(parameter);
          EEPROM.writeByte(eepromOilInvertedAddress, p);
        }
        break;


      // Water Temperature meter
      case 500:
        if (parameter == "")
        {
          Serial.print(F("($500) Water Temperature meter lower value = "));
          Serial.println(EEPROM.readInt(eepromTempLowerAddress));
        }
        else
        {
          Serial.print(F("Setting ($500) Water Temperature Lower value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempLowerAddress, p);
        }
        break;
      case 501:
        if (parameter == "")
        {
          Serial.print(F("($501) Water Temperature upper value = "));
          Serial.println(EEPROM.readInt(eepromTempUpperAddress));
        }
        else
        {
          Serial.print(F("Setting ($501) Water Temperature Upper value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempUpperAddress, p);
        }
        break;
      case 502:
        if (parameter == "")
        {
          Serial.print(F("($502) Water Temperature min value = "));
          Serial.println(EEPROM.readInt(eepromTempMinAddress));
        }
        else
        {
          Serial.print(F("Setting ($502) Water Temperature min value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempMinAddress, p);
        }
        break;
      case 503:
        if (parameter == "")
        {
          Serial.print(F("($503) Water Temperature max value = "));
          Serial.println(EEPROM.readInt(eepromTempMaxAddress));
        }
        else
        {
          Serial.print(F("Setting ($503) Water Temperature max value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempMaxAddress, p);
        }
        break;
      case 504:
        if (parameter == "")
        {
          Serial.print(F("($504) Water Temperature warn value = "));
          Serial.println(EEPROM.readInt(eepromTempWarnAddress));
        }
        else
        {
          Serial.print(F("Setting ($504) Water Temperature warn value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempWarnAddress, p);
        }
        break;
      case 505:
        if (parameter == "")
        {
          Serial.print(F("($505) Water Temperature warn low value = "));
          Serial.println(EEPROM.readInt(eepromTempWarnAddress));
        }
        else
        {
          Serial.print(F("Setting ($505) Water Temperature warn low value = "));
          Serial.println(parameter);
          EEPROM.writeByte(eepromTempWarnAddress, p);
        }
        break;
      case 506:
        if (parameter == "")
        {
          Serial.print(F("($506) Water Temperature inverted value = "));
          Serial.println(EEPROM.readByte(eepromTempInvertedAddress));
        }
        else
        {
          Serial.print(F("Setting ($506) Water Temperature inverted value = "));
//          Serial.println(parameter);
          EEPROM.writeByte(eepromTempInvertedAddress, p);
          Serial.println(EEPROM.readByte(eepromTempInvertedAddress));

Serial.print(" p = ");
sprintf(buffer, "%4d", p);
Serial.println(buffer);
        
        }
        break;

      case 507:
        if (parameter == "")
        {
          Serial.print(F("($507) Water Temperature celcius value = "));
          Serial.println(EEPROM.readInt(eepromTempCelciusAddress));
        }
        else
        {
          Serial.print(F("Setting ($507) Water Temperature celcius value = "));
          Serial.println(parameter);
          EEPROM.writeByte(eepromTempCelciusAddress, p);
        }
        break;

      case 510:
        if (parameter == "")
        {
          Serial.print(F("($510) Water Temperature Fan One on value = "));
          Serial.println(EEPROM.readInt(eepromTempFanOneOnAddress));
        }
        else
        {
          Serial.print(F("Setting ($510) Water Temperature Fan One on value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempFanOneOnAddress, p);
        }
        break;

      case 511:
        if (parameter == "")
        {
          Serial.print(F("($511) Water Temperature Fan One off value = "));
          Serial.println(EEPROM.readInt(eepromTempFanOneOffAddress));
        }
        else
        {
          Serial.print(F("Setting ($511) Water Temperature Fan One off value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempFanOneOffAddress, p);
        }
        break;

      case 512:
        if (parameter == "")
        {
          Serial.print(F("($512) Water Temperature Fan Two on value = "));
          Serial.println(EEPROM.readInt(eepromTempFanTwoOnAddress));
        }
        else
        {
          Serial.print(F("Setting ($512) Water Temperature Fan Two on value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempFanTwoOnAddress, p);
        }
        break;

      case 513:
        if (parameter == "")
        {
          Serial.print(F("($513) Water Temperature Fan Two off value = "));
          Serial.println(EEPROM.readInt(eepromTempFanTwoOffAddress));
        }
        else
        {
          Serial.print(F("Setting ($513) Water Temperature Fan Two off value = "));
          Serial.println(parameter);
          EEPROM.writeInt(eepromTempFanTwoOffAddress, p);
        }
        break;



      // Fuel Level meter
      case 600:
        if (parameter == "")
        {
          Serial.print(F("($600) Fuel Level meter lower value = "));
          Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
        }
        else
        {
          Serial.print(F("Setting ($500) Fuel Level Lower value = "));
          Serial.println(parameter);
          int p = parameter.toInt();
          EEPROM.writeInt(eepromFuelLowerAddress, p);
        }
        break;
      case 601:
        if (parameter == "")
        {
          Serial.print(F("($601) Fuel Level upper value = "));
          Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
        }
        else
        {
          Serial.print(F("Setting ($501) Fuel Level Upper value = "));
          Serial.println(parameter);
          int p = parameter.toInt();
          EEPROM.writeInt(eepromFuelUpperAddress, p);
        }
        break;
      case 602:
        if (parameter == "")
        {
          Serial.print(F("($602) Fuel Level min value = "));
          Serial.println(EEPROM.readInt(eepromFuelMinAddress));
        }
        else
        {
          Serial.print(F("Setting ($502) Fuel Level min value = "));
          Serial.println(parameter);
          int p = parameter.toInt();
          EEPROM.writeInt(eepromFuelMinAddress, p);
        }
        break;
      case 603:
        if (parameter == "")
        {
          Serial.print(F("($603) Fuel Level max value = "));
          Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
        }
        else
        {
          Serial.print(F("Setting ($503) Fuel Level max value = "));
          Serial.println(parameter);
          int p = parameter.toInt();
          EEPROM.writeInt(eepromFuelMaxAddress, p);
        }
        break;
      case 604:
        if (parameter == "")
        {
          Serial.print(F("($604) Fuel Level warn value = "));
          Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
        }
        else
        {
          Serial.print(F("Setting ($604) Fuel Level warn value = "));
          Serial.println(parameter);
          int p = parameter.toInt();
          EEPROM.writeInt(eepromFuelWarnAddress, p);
        }
        break;
      case 605:
        if (parameter == "")
        {
          Serial.print(F("($605) Fuel Level warn low value = "));
          Serial.println(EEPROM.readInt(eepromFuelWarnLowAddress));
        }
        else
        {
          Serial.print(F("Setting ($605) Fuel Level warn low value = "));
          Serial.println(parameter);
          byte p = parameter.toInt();
          EEPROM.writeByte(eepromFuelWarnAddress, p);
        }
        break;


      // debug values
      case 910:
        if (parameter == "")
        {
          Serial.print(F("($910) debug speedo value = "));
          Serial.println(EEPROM.readByte(eepromDebugSpeedoAddress));
        }
        else
        {
          if (p < 12)
           {
            Serial.print(F("Setting ($910) debug speedo value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDebugSpeedoAddress, p);
            debugSpeedo = p;
           }
          else
          {
            Serial.println(F("Invalid value for debug speedo parameter"));
            debugSpeedo = 0;
          }
                }
        break;

      case 930:
        if (parameter == "")
        {
          Serial.print(F("($930) debug tacho value = "));
          Serial.println(EEPROM.readByte(eepromDebugTachoAddress));
        }
        else
        {
          if (p < 4)
          {
            Serial.print(F("Setting ($930) debug tacho value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDebugTachoAddress, p);
            debugTacho = p;
          }
          else
          {
            Serial.println(F("Invalid value for debug tacho parameter"));
            debugTacho = 0;
          }
        }
        break;

      case 950:
        if (parameter == "")
        {
          Serial.print(F("($950) debug gauges value = "));
          Serial.println(EEPROM.readByte(eepromDebugGaugesAddress));
        }
        else
        {
          if (p < 7)
          {
            Serial.print(F("Setting ($950) debug gauges value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDebugGaugesAddress, p);
            debugGauges = p;
          }
          else
          {
            Serial.println(F("Invalid value for debug gauges parameter"));
            debugGauges = 0;
          }
        }
        break;

      case 970:
        if (parameter == "")
        {
          Serial.print(F("($970) debug all value = "));
          Serial.println(EEPROM.readByte(eepromDebugAllAddress));
        }
        else
        {
          if (p < 4)
          {
            Serial.print(F("Setting ($970) debug all value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDebugAllAddress, p);
            debugAll = p;
          }
          else
          {
            Serial.println(F("Invalid value for debug all parameter"));
            debugAll = 0;
          }
        }
        break;

      // demo values

      case 920:
        if (parameter == "")
        {
          Serial.print(F("($920) demo speedo value = "));
          Serial.println(EEPROM.readByte(eepromDemoSpeedoAddress));
        }
        else
        {
          if ((p < 11) || (p ==20))
          {
            Serial.print(F("Setting ($920) demo speedo value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDemoSpeedoAddress, p);
            demoSpeedo = p;
          }
          else
          {
            Serial.println(F("Invalid value for demo speedo parameter"));
            EEPROM.writeByte(eepromDemoSpeedoAddress, 0);
            demoSpeedo = 0;
          }
        }
        break;

      case 940:
        if (parameter == "")
        {
          Serial.print(F("($940) demo tacho value = "));
          Serial.println(EEPROM.readByte(eepromDemoTachoAddress));
        }
        else
        {
          if (p < 6)
          {
            Serial.print(F("Setting ($940) demo tacho value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDemoTachoAddress, p);
            demoTacho = p;
          }
          else
          {
            Serial.println(F("Invalid value for demo tacho parameter"));
            EEPROM.writeByte(eepromDemoTachoAddress, 0);
            demoTacho = 0;
          }
        }
        break;

      case 960:
        if (parameter == "")
        {
          Serial.print(F("($960) demo gauges value = "));
          Serial.println(EEPROM.readByte(eepromDemoGaugesAddress));
        }
        else
        {
          if (p < 5)
          {
            Serial.print(F("Setting ($960) demo gauges value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDemoGaugesAddress, p);
            demoGauges = p;
          }
          else
          {
            Serial.println(F("Invalid value for demo gauges parameter"));
            EEPROM.writeByte(eepromDemoGaugesAddress, 0);
            demoGauges = 0;
          }
        }
        break;

      case 980:
        if (parameter == "")
        {
          Serial.print(F("($980) demo all value = "));
          Serial.println(EEPROM.readByte(eepromDemoAllAddress));
        }
        else
        {
          if (p < 3)
          {
            Serial.print(F("Setting ($980) demo all value = "));
            Serial.println(parameter);
            EEPROM.writeByte(eepromDemoAllAddress, p);
            demoAll = p;
          }
          else
          {
            Serial.println(F("Invalid value for demo all parameter"));
            EEPROM.writeByte(eepromDemoAllAddress, 0);
            demoAll = 0;
          }
        }
        break;



      case 999:
        if ((parameter == "") || (parameter.length() < 5))
        {
          Serial.println(F("You must supply a value and passcode"));
        }
        else
        {
          String odo = parameter.substring(0, parameter.length() - 5);
          String pc = parameter.substring(parameter.length() - 4);
          if (pc.toInt() == passCode)
          {
            Serial.println(F("Resetting odometer"));
            Serial.print(F("Odometer = "));
            Serial.println(odo.toInt());
            EEPROM.writeLong(eepromOdoAddress, odo.toInt());
            if (extEepromAvailable)
             {
              extEepromOdometer.totalOdometer=odo.toInt();
              speedoEeprom.write(EXT_EEPROM_ADDRESS_ODOMETER, (byte *)&extEepromOdometer.extEepromTotalOdometer, 4);
             }
          }
          else
          {
            Serial.println(F("ERROR: Incorrect passcode"));
          }
        }

        break;

      default:
        Serial.println(F("ERROR: Unknown setting"));
        break;
    }

 }
}


// show all variables

void showVariables()
 {
  Serial.println(F("EEPROM Contains"));
  EEPROM.readBlock(eepromTitleAddress, title);
  Serial.print(F("Title = "));
  Serial.println(title);
  Serial.print(F("Version high = "));
  Serial.println(EEPROM.readByte(eepromVersionHigh));
  Serial.print(F("Version low = "));
  Serial.println(EEPROM.readByte(eepromVersionLow));

        // get speedo settings


  Serial.print(F("($100)Speedo calibration = "));
  Serial.println(EEPROM.readLong(eepromSpeedoCalibrateAddress));

  Serial.print(F("($100)Speedo calibration as float = "));
  float c = (float)EEPROM.readLong(eepromSpeedoCalibrateAddress) / (float)SPEEDO_CALIBRATE_DIVIDER;
  dtostrf(c, 6, 4, buffer);
  Serial.println(buffer);

  Serial.print(F("Odometer count (read only) = "));
  Serial.println(EEPROM.readLong(eepromOdoAddress));

  Serial.print(F("($102)Tripmeter 1 count = "));
  Serial.println(EEPROM.readLong(eepromTrip1Address));
  Serial.print(F("($103)Tripmeter 2 count = "));
  Serial.println(EEPROM.readLong(eepromTrip2Address));
  Serial.print(F("($104)Speedo Mode Function = "));
  Serial.println(EEPROM.readByte(eepromSpeedoModeFuncAddress));


        // get tacho settings

  Serial.print(F("($200)Tacho PPR = "));
  Serial.println(EEPROM.readByte(eepromTachoPPRAddress));
  Serial.print(F("($201)Tacho Type = "));
  Serial.println(EEPROM.readByte(eepromTachoTypeAddress));

  Serial.print(F("($202)Tacho Redline = "));
  Serial.println(EEPROM.readInt(eepromTachoRedlineAddress));
  Serial.print(F("($203)Tacho Shift = "));
  Serial.println(EEPROM.readInt(eepromTachoShiftAddress));
  Serial.print(F("($204)Tacho Maximum = "));
  Serial.println(EEPROM.readInt(eepromTachoMaximumAddress));
  Serial.print(F("($205)Tacho Calibrate  = "));
  Serial.println(EEPROM.readInt(eepromTachoCalibrateAddress));



        // get gauge settings

        // Voltmeter

  Serial.print(F("($300)Voltmeter lower calibration = "));
  Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
  Serial.print(F("($301)Voltmeter upper calibration = "));
  Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
  Serial.print(F("($302)Voltmeter minimum reading = "));
  Serial.println(EEPROM.readInt(eepromVoltMinAddress));
  Serial.print(F("($303)Voltmeter maximum reading = "));
  Serial.println(EEPROM.readInt(eepromVoltMaxAddress));
  Serial.print(F("($304)Voltmeter warning reading = "));
  Serial.println(EEPROM.readInt(eepromVoltWarnAddress));
  Serial.print(F("($305)Voltmeter warning low = "));
  Serial.println(EEPROM.readByte(eepromVoltWarnLowAddress));

        // Oil pressure meter

  Serial.print(F("($400)Oil pressure meter lower calibration = "));
  Serial.println(EEPROM.readInt(eepromOilLowerAddress));
  Serial.print(F("($401)Oil pressure meter upper calibration = "));
  Serial.println(EEPROM.readInt(eepromOilUpperAddress));
  Serial.print(F("($402)Oil pressure meter minimum reading = "));
  Serial.println(EEPROM.readInt(eepromOilMinAddress));
  Serial.print(F("($403)Oil pressure meter maximum reading = "));
  Serial.println(EEPROM.readInt(eepromOilMaxAddress));
  Serial.print(F("($404)Oil pressure meter warning reading = "));
  Serial.println(EEPROM.readInt(eepromOilWarnAddress));
  Serial.print(F("($405)Oil pressure meter warning low = "));
  Serial.println(EEPROM.readByte(eepromOilWarnLowAddress));
  Serial.print(F("($406)Oil pressure meter inverted = "));
  Serial.println(EEPROM.readByte(eepromOilInvertedAddress));

        // Water temperature meter

  Serial.print(F("($500)Water temperature meter lower calibration = "));
  Serial.println(EEPROM.readInt(eepromTempLowerAddress));
  Serial.print(F("($501)Water temperature meter upper calibration = "));
  Serial.println(EEPROM.readInt(eepromTempUpperAddress));
  Serial.print(F("($502)Water temperature meter minimum reading = "));
  Serial.println(EEPROM.readInt(eepromTempMinAddress));
  Serial.print(F("($503)Water temperature meter maximum reading = "));
  Serial.println(EEPROM.readInt(eepromTempMaxAddress));
  Serial.print(F("($504)Water temperature meter warning reading = "));
  Serial.println(EEPROM.readInt(eepromTempWarnAddress));
  Serial.print(F("($505)Water temperature meter warning low = "));
  Serial.println(EEPROM.readByte(eepromTempWarnLowAddress));
  Serial.print(F("($506)Water temperature meter inverted = "));
  Serial.println(EEPROM.readByte(eepromTempInvertedAddress));
  Serial.print(F("($507)Water temperature celcius = "));
  Serial.println(EEPROM.readByte(eepromTempCelciusAddress));


  Serial.print(F("($510)Water temperature meter fan one on reading = "));
  Serial.println(EEPROM.readInt(eepromTempFanOneOnAddress));
  Serial.print(F("($511)Water temperature meter fan one off reading = "));
  Serial.println(EEPROM.readInt(eepromTempFanOneOffAddress));
  Serial.print(F("($512)Water temperature meter fan two on reading = "));
  Serial.println(EEPROM.readInt(eepromTempFanTwoOnAddress));
  Serial.print(F("($513)Water temperature meter fan two off reading = "));
  Serial.println(EEPROM.readInt(eepromTempFanTwoOffAddress));

        // Fuel level meter

  Serial.print(F("($600)Fuel level meter lower calibration = "));
  Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
  Serial.print(F("($601)Fuel level meter upper calibration = "));
  Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
  Serial.print(F("($602)Fuel level meter minimum reading = "));
  Serial.println(EEPROM.readInt(eepromFuelMinAddress));
  Serial.print(F("($603)Fuel level meter maximum reading = "));
  Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
  Serial.print(F("($604)Fuel level meter warning reading = "));
  Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
  Serial.print(F("($605)Fuel level meter warning low = "));
  Serial.println(EEPROM.readByte(eepromFuelWarnLowAddress));
  Serial.print(F("($606)Fuel level meter inverted = "));
  Serial.println(EEPROM.readByte(eepromFuelInvertedAddress));

        /*
          // a meter meter
            Serial.print(F("($?00) meter lower calibration = "));
            Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
            Serial.print(F("($?01) meter upper calibration = "));
            Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
            Serial.print(F("($?02) meter minimum reading = "));
            Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
            Serial.print(F("($?03) meter maximum reading = "));
            Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
            Serial.print(F("($?04) meter warning reading = "));
            Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
            Serial.print(F("($?04) meter warning low = "));
            Serial.println(EEPROM.readInt(eepromFuelWarnLowAddress));
        */

  Serial.print(F("($910)speedo debug value = "));
  Serial.println(EEPROM.readByte(eepromDebugSpeedoAddress));

  Serial.print(F("($920)speedo demo value = "));
  Serial.println(EEPROM.readByte(eepromDemoSpeedoAddress));

  Serial.print(F("($930)tacho debug value = "));
  Serial.println(EEPROM.readByte(eepromDebugTachoAddress));

  Serial.print(F("($940)tacho demo value = "));
  Serial.println(EEPROM.readByte(eepromDemoTachoAddress));

  Serial.print(F("($950)gauges debug value = "));
  Serial.println(EEPROM.readByte(eepromDebugGaugesAddress));

  Serial.print(F("($960)gauges demo value = "));
  Serial.println(EEPROM.readByte(eepromDemoGaugesAddress));

  Serial.print(F("($970)all debug value = "));
  Serial.println(EEPROM.readByte(eepromDebugAllAddress));

  Serial.print(F("($980)all demo value = "));
  Serial.println(EEPROM.readByte(eepromDemoAllAddress));


  Serial.println();
  Serial.print(F("brightness = "));
  sprintf(buffer, "%4d", brightnessBoost);
  Serial.println(buffer);

  Serial.println();
  Serial.print(F("speed = "));
  sprintf(buffer, "%4d", speed);
  Serial.println(buffer);
  Serial.println();
  Serial.print(F("rpm = "));
  sprintf(buffer, "%4d", rpm);
  Serial.println(buffer);

  Serial.print(F("Volt = "));
        dtostrf(float(voltVal) / 10, 4, 1, buffer);
        //      sprintf(buffer, "%4d", voltVal);
  Serial.println(buffer);
  Serial.print(F("Oil = "));
        dtostrf(float(oilVal) / 10, 4, 1, buffer);
        //      sprintf(buffer, "%4d", oilVal);
  Serial.println(buffer);
  Serial.print(F("Temp = "));
        dtostrf(float(tempVal) / 10, 4, 1, buffer);
        //      sprintf(buffer, "%4d", tempVal);
  Serial.println(buffer);
  Serial.print(F("Fuel = "));
        dtostrf(float(voltVal) / 10, 4, 1, buffer);
        //      sprintf(buffer, "%4d", fuelVal);
  Serial.println(buffer);


  Serial.println();
  if (!digitalRead(pinLightsOn))
   {
    Serial.println(F("Lights on"));
   }
  else
   {
    Serial.println(F("Lights off"));
   }
 }

// do serial received commands

void doSerialCommand(String readString)
{
//  byte p = 0;


  Serial.println(readString);  //so you can see the captured string

  if (readString == "$")
   {
    Serial.println(F("$        - this display"));
    Serial.println(F("$$       - show all eeprom variables plus current values for gauges"));
    Serial.println(F("$xxx=    - show value for eeprom variable xxx"));
    Serial.println(F("$xxx=ddd - set value for eeprom variable xxx"));
    Serial.println(F("$1000    - scan i2c bus"));
   }
  else
   {
    if (readString.startsWith("$"))
     {
      if (readString.startsWith("$$"))
       {

        showVariables();
       }
      else
       {
        if (readString.startsWith("$0"))
         {
          Serial.println(F("Resetting EEPROM except for odometer"));

          //TODO

         }
        else
         {
          if (readString.startsWith("$1000"))
           {
            scanI2cBus(false);
           }
          else
           {
            doVariables(readString);
            getEepromValues();
           }
         }
       }
     }
    else
     {
      Serial.println(F("ERROR: Unknown command"));
     }
  }
}


