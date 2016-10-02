//Functions.h

// do serial received commands

void doSerialCommand(String readString)
 {
    byte p = 0;

    Serial.println(readString);  //so you can see the captured string

    if (readString == "$")
     {

     }
    else
     {
      if (readString.startsWith("$$"))
       {
        Serial.println(F("EEPROM Contains"));
        EEPROM.readBlock(eepromTitleAddress, title);
        Serial.print(F("Title = "));
        Serial.println(title);
        Serial.print(F("Version high = "));
        Serial.println(EEPROM.readByte(eepromVersionHighAddress));
        Serial.print(F("Version low = "));
        Serial.println(EEPROM.readByte(eepromVersionLowAddress));

  // get speedo settings

        Serial.print(F("($100)Speedo calibration = "));
        Serial.println(EEPROM.readLong(eepromSpeedoCalibrateAddress));

        Serial.print(F("Odometer count (read only) = "));
        Serial.println(EEPROM.readLong(eepromOdoAddress));

        Serial.print(F("($102)Tripmeter 1 count = "));
        Serial.println(EEPROM.readLong(eepromTrip1Address));
        Serial.print(F("($103)Tripmeter 2 count = "));
        Serial.println(EEPROM.readLong(eepromTrip2Address));

        Serial.print(F("($910)debug value = "));
        Serial.println(EEPROM.readByte(eepromDebugSpeedoAddress));
        Serial.print(F("($920)demo value = "));
        Serial.println(EEPROM.readByte(eepromDemoSpeedoAddress));

        Serial.println();
        Serial.print(F("brightness = "));
        sprintf(buffer, "%4d", brightnessBoost);
        Serial.println(buffer);

        Serial.println();
        Serial.print(F("speed = "));
        sprintf(buffer, "%4d", speed);
        Serial.println(buffer);

        Serial.println();
        if (digitalRead(pinLightsOn))
         {
          Serial.println(F("Lights on"));
         }
        else
         {
          Serial.println(F("Lights off"));
         }
       }
      else
       {
        if (readString.startsWith("$"))
         {
          if (readString.startsWith("$0"))
           {
            Serial.println(F("Resetting EEPROM except for odometer"));
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
                    Serial.print(F("($100)Speedo calibration = "));
                    unsigned long c = EEPROM.readInt(eepromSpeedoCalibrateAddress);
                    dtostrf(c, 10, 8, buffer);
                    Serial.println(buffer);
                   }
                  else
                   {
                    Serial.print(F("Setting ($100) Speedo calibration = "));
                    Serial.println(parameter);
                    // EEPROM.writeFloat(eepromSpeedoCalibrateAddress, parameter);
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
                    // EEPROM.writeLong(eepromTrip1Address, parameter);
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
                    // EEPROM.writeLong(eepromTrip2Address, parameter);
                   }
                  break;
                case 910:
                  if (parameter == "")
                   {
                    Serial.print(F("($910) debug value = "));
                    Serial.println(EEPROM.readByte(eepromDebugSpeedoAddress));
                   }
                  else
                   {
    
                    p = parameter.toInt();
                    if (p < 4)
                     {
                      Serial.print(F("Setting ($910) debug value = "));
                      Serial.println(parameter);
                      EEPROM.writeByte(eepromDebugSpeedoAddress, p);
                      debugSpeedo = p;
                     }
                    else
                     {
                      Serial.println(F("Invalid value for debug parameter"));
                      debugSpeedo = 0;
                     }
                   }
                  break;

                case 920:
                  if (parameter == "")
                   {
                    Serial.print(F("($920) demo value = "));
                    Serial.println(EEPROM.readByte(eepromDemoSpeedoAddress));
                   }
                  else
                   {
                    p = parameter.toInt();
                    if (p < 6)
                     {
                      Serial.print(F("Setting ($920) demo value = "));
                      Serial.println(parameter);
                      EEPROM.writeByte(eepromDemoSpeedoAddress, p);
                      demoSpeedo = p;
                     }
                    else
                     {
                      Serial.println(F("Invalid value for demo parameter"));
                      EEPROM.writeByte(eepromDemoSpeedoAddress, 0);
                      demoSpeedo = 0;
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
                    String odo = parameter.substring(0, parameter.length()-4);
                    String pc = parameter.substring(parameter.length()-4);
                    if (pc.toInt() == passCode)
                     {
                      Serial.println(F("Resetting odometer"));
                      Serial.print(F("Odometer = "));
                      Serial.println(odo);
                    //
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
            else
             {
              Serial.println(F("ERROR: Invalid input"));
             }
           }
         }
        else
         {
          Serial.println(F("ERROR: Unknown command"));
         }
       }
     }
//    readString=""; //empty for next input
 }



byte speedoDemo(byte demo)
 {

  int rpm =  0;

  while (rpm < 160)
   {
    rpm += 1;

    displaySpeed(rpm);
    delay(1000/demo);
   }

  delay(1000);

  if (demo >= 4)
   {
    while (rpm > 0)
     {
      rpm -= 1;

      displaySpeed(rpm);
      delay(1000/demo);
     }

   }
  return 0;
 }

