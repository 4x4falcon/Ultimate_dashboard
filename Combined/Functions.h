/*
* TODO
*
* This is the sleep function
* It will be activated when the ignition is turned off.
* It needs to write odo and trip values to the eeprom
* Will wake up on ignition turned on
*
*/


void goToSleep() {
  
// write the odometer to EEPROM

  if (totalOdometer > EEPROM.readFloat(eepromOdoAddress))
   {
#ifdef ECHO_SERIAL
    Serial.print ("Saving odometer to EEPROM    ");
    Serial.println (totalOdometer);
#else
    EEPROM.writeFloat(eepromOdoAddress, totalOdometer);
#endif
   }

// write the tripmeters to EEPROM
  writeTripmeter();
  
// write the modeSpeedoFunc to EEPROM
  EEPROM.writeByte(eepromModeSpeedoFuncAddress, modeSpeedoFunc);

}



void doSerialCommand(String readString)
 {
    Serial.println(readString);  //so you can see the captured string 

    if (readString == "$")
     {
      Serial.println("EEPROM Contains");
      EEPROM.readBlock(eepromTitleAddress, title);
      Serial.print("Title = ");
      Serial.println(title);
      Serial.print("Version high = ");
      Serial.println(EEPROM.readByte(eepromVersionHigh));
      Serial.print("Version low = ");
      Serial.println(EEPROM.readByte(eepromVersionLow));

  // get speedo settings

      Serial.print("($100)Speedo calibration = ");
      float c = EEPROM.readFloat(eepromSpeedoCalibrateAddress);
      dtostrf(c, 6, 4, buffer);
      Serial.println(buffer);

      Serial.print("Odometer count (read only) = ");
      Serial.println(EEPROM.readLong(eepromOdoAddress));

      Serial.print("($102)Tripmeter 1 count = ");
      Serial.println(EEPROM.readLong(eepromTrip1Address));
      Serial.print("($103)Tripmeter 2 count = ");
      Serial.println(EEPROM.readLong(eepromTrip2Address));


  // get tacho settings

      Serial.print("($200)Tacho Calibration = ");
      Serial.println(EEPROM.readByte(eepromTachoCalibrateAddress));
      Serial.print("($201)Tacho Type = ");
      Serial.println(EEPROM.readByte(eepromTachoTypeAddress));

  // get gauge settings

  // Voltmeter

      Serial.print("($300)Voltmeter lower calibration = ");
      Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
      Serial.print("($301)Voltmeter upper calibration = ");
      Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
      Serial.print("($302)Voltmeter maximum reading = ");
      Serial.println(EEPROM.readInt(eepromVoltMaxAddress));
      Serial.print("($303)Voltmeter warning reading = ");
      Serial.println(EEPROM.readInt(eepromVoltWarnAddress));

  // Oil pressure meter

      Serial.print("($400)Oil pressure meter lower calibration = ");
      Serial.println(EEPROM.readInt(eepromOilLowerAddress));
      Serial.print("($401)Oil pressure meter upper calibration = ");
      Serial.println(EEPROM.readInt(eepromOilUpperAddress));
      Serial.print("($402)Oil pressure meter maximum reading = ");
      Serial.println(EEPROM.readInt(eepromOilMaxAddress));
      Serial.print("($403)Oil pressure meter warning reading = ");
      Serial.println(EEPROM.readInt(eepromOilWarnAddress));

  // Water temperature meter

      Serial.print("($500)Water temperature meter lower calibration = ");
      Serial.println(EEPROM.readInt(eepromTempLowerAddress));
      Serial.print("($501)Water temperature meter upper calibration = ");
      Serial.println(EEPROM.readInt(eepromTempUpperAddress));
      Serial.print("($502)Water temperature meter maximum reading = ");
      Serial.println(EEPROM.readInt(eepromTempMaxAddress));
      Serial.print("($503)Water temperature meter warning reading = ");
      Serial.println(EEPROM.readInt(eepromTempWarnAddress));

  // Fuel level meter

      Serial.print("($600)Fuel level meter lower calibration = ");
      Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
      Serial.print("($601)Fuel level meter upper calibration = ");
      Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
      Serial.print("($602)Fuel level meter maximum reading = ");
      Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
      Serial.print("($603)Fuel level meter warning reading = ");
      Serial.println(EEPROM.readInt(eepromFuelWarnAddress));

/*
  // a meter meter
      Serial.print("($?00) meter lower calibration = ");
      Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
      Serial.print("($?01) meter upper calibration = ");
      Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
      Serial.print("($?02) meter maximum reading = ");
      Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
      Serial.print("($?03) meter warning reading = ");
      Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
*/

     }
    else
     {
      if (readString.startsWith("$"))
       {
        if (readString.startsWith("$0"))
         {
          Serial.println("Resetting EEPROM except for odometer");

         }
        else
         {
          int pos = readString.indexOf("=");
          if (pos > 0)
           {

            String c = readString.substring(1, pos);
            int command = c.toInt();
            String parameter = readString.substring(pos + 1);

            switch (command)
             {
              case 100:
                if (parameter == "")
                 {
                  Serial.print("($100)Speedo calibration = ");
                  float c = EEPROM.readFloat(eepromSpeedoCalibrateAddress);
                  dtostrf(c, 10, 8, buffer);
                  Serial.println(buffer);
                 }
                else
                 {
                  Serial.print("Setting ($100) Speedo calibration = ");
                  Serial.println(parameter);
                  // EEPROM.writeFloat(eepromSpeedoCalibrateAddress, parameter);
                 }
                break;
              case 102:
                if (parameter == "")
                 {
                  Serial.print("($102)Tripmeter 1 value = ");
                  Serial.println(EEPROM.readLong(eepromTrip1Address));
                 }
                else
                 {
                  Serial.print("Setting ($102) Tripmeter 1 value = ");
                  Serial.println(parameter);
                  // EEPROM.writeLong(eepromTrip1Address, parameter);
                 }
                break;
              case 103:
                if (parameter == "")
                 {
                  Serial.print("($103)Tripmeter 2 value = ");
                  Serial.println(EEPROM.readLong(eepromTrip2Address));
                 }
                else
                 {
                  Serial.print("Setting ($103) Tripmeter 2 value = ");
                  Serial.println(parameter);
                  // EEPROM.writeLong(eepromTrip2Address, parameter);
                 }
                break;

// tacho
              case 200:
                if (parameter == "")
                 {
                  Serial.print("($200)Tachometer calibrate value = ");
                  Serial.println(EEPROM.readByte(eepromTachoCalibrateAddress));
                 }
                else
                 {
                  Serial.print("Setting ($200) Tachometer calibrate value = ");
                  Serial.println(parameter);
                  // EEPROM.writeByte(eepromTachoCalibrateAddress, parameter);
                 }
                break;
              case 201:
                if (parameter == "")
                 {
                  Serial.print("($201)Tachometer type value = ");
                  Serial.println(EEPROM.readByte(eepromTachoTypeAddress));
                 }
                else
                 {
                  Serial.print("Setting ($201) Tacho type value = ");
                  Serial.println(parameter);
                  // EEPROM.writeByte(eepromTachoTypeAddress, parameter);
                 }
                break;

// Voltmeter
              case 300:
                if (parameter == "")
                 {
                  Serial.print("($300)Voltmeter lower value = ");
                  Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
                 }
                else
                 {
                  Serial.print("Setting ($300) Voltmeter Lower value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromVoltLowerAddress, parameter);
                 }
                break;
              case 301:
                if (parameter == "")
                 {
                  Serial.print("($301)Voltmeter upper value = ");
                  Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
                 }
                else
                 {
                  Serial.print("Setting ($301) Voltmeter Upper value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromVoltUpperAddress, parameter);
                 }
                break;
              case 302:
                if (parameter == "")
                 {
                  Serial.print("($302)Voltmeter max value = ");
                  Serial.println(EEPROM.readInt(eepromVoltMaxAddress));
                 }
                else
                 {
                  Serial.print("Setting ($302) Voltmeter max value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromVoltMaxAddress, parameter);
                 }
                break;
              case 303:
                if (parameter == "")
                 {
                  Serial.print("($303)Voltmeter warn value = ");
                  Serial.println(EEPROM.readInt(eepromVoltWarnAddress));
                 }
                else
                 {
                  Serial.print("Setting ($303) Voltmeter warn value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromVoltWarnAddress, parameter);
                 }
                break;

// Oil pressure meter
              case 400:
                if (parameter == "")
                 {
                  Serial.print("($400)Oil Pressure meter lower value = ");
                  Serial.println(EEPROM.readInt(eepromOilLowerAddress));
                 }
                else
                 {
                  Serial.print("Setting ($400) Oil Pressure Lower value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromOilLowerAddress, parameter);
                 }
                break;
              case 401:
                if (parameter == "")
                 {
                  Serial.print("($401)Oil Pressure upper value = ");
                  Serial.println(EEPROM.readInt(eepromOilUpperAddress));
                 }
                else
                 {
                  Serial.print("Setting ($401) Oil Pressure Upper value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromOilUpperAddress, parameter);
                 }
                break;
              case 402:
                if (parameter == "")
                 {
                  Serial.print("($402) Oil Pressure max value = ");
                  Serial.println(EEPROM.readInt(eepromOilMaxAddress));
                 }
                else
                 {
                  Serial.print("Setting ($402) Oil Pressure max value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromOilMaxAddress, parameter);
                 }
                break;
              case 403:
                if (parameter == "")
                 {
                  Serial.print("($403) Oil Pressure warn value = ");
                  Serial.println(EEPROM.readInt(eepromOilWarnAddress));
                 }
                else
                 {
                  Serial.print("Setting ($403) Oil Pressure warn value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromOilWarnAddress, parameter);
                 }
                break;

// Water Temperature meter
              case 500:
                if (parameter == "")
                 {
                  Serial.print("($500) Water Temperature meter lower value = ");
                  Serial.println(EEPROM.readInt(eepromTempLowerAddress));
                 }
                else
                 {
                  Serial.print("Setting ($500) Water Temperature Lower value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromTempLowerAddress, parameter);
                 }
                break;
              case 501:
                if (parameter == "")
                 {
                  Serial.print("($501) Water Temperature upper value = ");
                  Serial.println(EEPROM.readInt(eepromTempUpperAddress));
                 }
                else
                 {
                  Serial.print("Setting ($501) Water Temperature Upper value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromTempUpperAddress, parameter);
                 }
                break;
              case 502:
                if (parameter == "")
                 {
                  Serial.print("($502) Water Temperature max value = ");
                  Serial.println(EEPROM.readInt(eepromTempMaxAddress));
                 }
                else
                 {
                  Serial.print("Setting ($502) Water Temperature max value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromTempMaxAddress, parameter);
                 }
                break;
              case 503:
                if (parameter == "")
                 {
                  Serial.print("($503) Water Temperature warn value = ");
                  Serial.println(EEPROM.readInt(eepromTempWarnAddress));
                 }
                else
                 {
                  Serial.print("Setting ($503) Water Temperature warn value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromTempWarnAddress, parameter);
                 }
                break;

// Fuel Level meter
              case 600:
                if (parameter == "")
                 {
                  Serial.print("($600) Fuel Level meter lower value = ");
                  Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
                 }
                else
                 {
                  Serial.print("Setting ($500) Fuel Level Lower value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromFuelLowerAddress, parameter);
                 }
                break;
              case 601:
                if (parameter == "")
                 {
                  Serial.print("($601) Fuel Level upper value = ");
                  Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
                 }
                else
                 {
                  Serial.print("Setting ($501) Fuel Level Upper value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromFuelUpperAddress, parameter);
                 }
                break;
              case 602:
                if (parameter == "")
                 {
                  Serial.print("($602) Fuel Level max value = ");
                  Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
                 }
                else
                 {
                  Serial.print("Setting ($502) Fuel Level max value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromFuelMaxAddress, parameter);
                 }
                break;
              case 603:
                if (parameter == "")
                 {
                  Serial.print("($603) Fuel Level warn value = ");
                  Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
                 }
                else
                 {
                  Serial.print("Setting ($503) Fuel Level warn value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromFuelWarnAddress, parameter);
                 }
                break;




              case 999:
                if ((parameter == "") || (parameter.length() < 5))
                 {
                  Serial.println("You must supply a value and passcode");
                 }
                else
                 {
                  String odo = parameter.substring(0, parameter.length()-4);
                  String pc = parameter.substring(parameter.length()-4);
                  if (pc.toInt() == passCode)
                   {
                    Serial.println("Resetting odometer");
                    Serial.print("Odometer = ");
                    Serial.println(odo);
                    //
                   }
                  else
                   {
                    Serial.println("ERROR: Incorrect passcode");
                   }
                 }
                
                break;

              default:
                Serial.println("ERROR: Unknown setting");
                break;
             }
           }
          else
           {
            Serial.println("ERROR: Invalid input");
           }
         }
       }
      else
       {
        Serial.println("ERROR: Unknown command");
       }
     }
//    readString=""; //empty for next input
 }



