//Functions.h

// do serial received commands

void doSerialCommand(String readString)
 {
    Serial.println(readString);  //so you can see the captured string 

    if (readString == "$")
     {
      Serial.println("EEPROM Contains");
      EEPROM.readBlock(eepromTitle, title);
      Serial.print("Title = ");
      Serial.println(title);
      Serial.print("Version high = ");
      Serial.println(EEPROM.readByte(eepromVersionHigh));
      Serial.print("Version low = ");
      Serial.println(EEPROM.readByte(eepromVersionLow));

  // get speedo settings

      Serial.print("($100)Speedo calibration = ");
      float c = EEPROM.readFloat(eepromSpeedoCalibrate);
      dtostrf(c, 6, 4, buffer);
      Serial.println(buffer);

      Serial.print("Odometer count (read only) = ");
      Serial.println(EEPROM.readLong(eepromOdo));

      Serial.print("($102)Tripmeter 1 count = ");
      Serial.println(EEPROM.readLong(eepromTrip1));
      Serial.print("($103)Tripmeter 2 count = ");
      Serial.println(EEPROM.readLong(eepromTrip2));
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
                  float c = EEPROM.readFloat(eepromSpeedoCalibrate);
                  dtostrf(c, 10, 8, buffer);
                  Serial.println(buffer);
                 }
                else
                 {
                  Serial.print("Setting ($100) Speedo calibration = ");
                  Serial.println(parameter);
                  // EEPROM.writeFloat(eepromSpeedoCalibrate, parameter);
                 }
                break;
              case 102:
                if (parameter == "")
                 {
                  Serial.print("($102)Tripmeter 1 value = ");
                  Serial.println(EEPROM.readLong(eepromTrip1));
                 }
                else
                 {
                  Serial.print("Setting ($102) Tripmeter 1 value = ");
                  Serial.println(parameter);
                  // EEPROM.writeLong(eepromTrip1, parameter);
                 }
                break;
              case 103:
                if (parameter == "")
                 {
                  Serial.print("($103)Tripmeter 2 value = ");
                  Serial.println(EEPROM.readLong(eepromTrip2));
                 }
                else
                 {
                  Serial.print("Setting ($103) Tripmeter 2 value = ");
                  Serial.println(parameter);
                  // EEPROM.writeLong(eepromTrip2, parameter);
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


