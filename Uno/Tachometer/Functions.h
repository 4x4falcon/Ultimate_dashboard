//Functions.h

// do serial received commands

void doSerialCommand(String readString)
 {
  byte p = 0;
  Serial.println(readString);  //so you can see the captured string 

  if (readString == "$")
   {
    Serial.println(F("EEPROM Contains"));
    EEPROM.readBlock(eepromTitle, title);
    Serial.print(F("Title = "));
    Serial.println(title);
    Serial.print(F("Version high = "));
    Serial.println(EEPROM.readByte(eepromVersionHigh));
    Serial.print(F("Version low = "));
    Serial.println(EEPROM.readByte(eepromVersionLow));

 // get tacho settings

    Serial.print(F("($200)Tacho PPR = "));
    Serial.println(EEPROM.readByte(eepromTachoPPR));
    Serial.print(F("($201)Tacho Type = "));
    Serial.println(EEPROM.readByte(eepromTachoType));
    Serial.print(F("($202)Tacho Redline = "));
    Serial.println(EEPROM.readInt(eepromTachoRedline));
    Serial.print(F("($203)Tacho Shift = "));
    Serial.println(EEPROM.readInt(eepromTachoShift));
    Serial.print(F("($204)Tacho Maximum = "));
    Serial.println(EEPROM.readInt(eepromTachoMaximum));
    Serial.print(F("($205)Tacho Calibrate = "));
    Serial.println(EEPROM.readInt(eepromTachoCalibrate));
    Serial.print(F("($910)Tacho Debug = "));
    Serial.println(EEPROM.readByte(eepromTachoDebug));
    Serial.print(F("($930)Tacho Demo = "));
    Serial.println(EEPROM.readByte(eepromTachoDemo));

    Serial.println();
    Serial.print(F("brightness = "));
    sprintf(buffer, "%4d", brightnessBoost);
    Serial.println(buffer);

    Serial.println();
    Serial.print(F("rpm = "));
    sprintf(buffer, "%4d", rpm);
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
// tacho
            case 200:
              if (parameter == "")
               {
                Serial.print(F("($200)Tachometer PPR value = "));
                Serial.println(EEPROM.readByte(eepromTachoCalibrate));
               }
              else
               {
                Serial.print(F("Setting ($200) Tachometer PPR value = "));
                Serial.println(parameter);
                  // EEPROM.writeByte(eepromTachoCalibrate, parameter);
               }
              break;
            case 201:
              if (parameter == "")
               {
                Serial.print(F("($201)Tachometer type value = "));
                Serial.println(EEPROM.readByte(eepromTachoType));
               }
              else
               {
                Serial.print(F("Setting ($201) Tacho type value = "));
                Serial.println(parameter);
                // EEPROM.writeByte(eepromTachoType, parameter);
               }
              break;
            case 202:
              if (parameter == "")
               {
                Serial.print(F("($202)Tachometer Redline value = "));
                Serial.println(EEPROM.readInt(eepromTachoRedline));
               }
              else
               {
                Serial.print(F("Setting ($202) Tacho Redline value = "));
                Serial.println(parameter);
                // EEPROM.writeInt(eepromTachoRedline, parameter);
               }
              break;
            case 203:
              if (parameter == "")
               {
                Serial.print(F("($203)Tachometer shift value = "));
                Serial.println(EEPROM.readInt(eepromTachoShift));
               }
              else
               {
                Serial.print(F("Setting ($203) Tacho shift value = "));
                Serial.println(parameter);
                // EEPROM.writeInt(eepromTachoShift, parameter);
               }
              break;
            case 204:
              if (parameter == "")
               {
                Serial.print(F("($204)Tachometer maximum value = "));
                Serial.println(EEPROM.readInt(eepromTachoMaximum));
               }
              else
               {
                Serial.print(F("Setting ($204) Tacho maximum value = "));
                Serial.println(parameter);
                // EEPROM.writeInt(eepromTachoMaximum, parameter);
               }
              break;
            case 205:
              if (parameter == "")
               {
                Serial.print(F("($205)Tachometer calibrate value = "));
                Serial.println(EEPROM.readInt(eepromTachoCalibrate));
               }
              else
               {
                Serial.print(F("Setting ($205) Tacho calibrate value = "));
                Serial.println(parameter);
                // EEPROM.writeInt(eepromTachoCalibrate, parameter);
               }
              break;

            case 910:
              if (parameter == "")
               {
                Serial.print(F("($910) debug value = "));
                Serial.println(EEPROM.readByte(eepromTachoDebug));
               }
              else
               {
                p = parameter.toInt();
                if (p < 4)
                 {
                  Serial.print(F("Setting ($910) debug value = "));
                  Serial.println(parameter);
                  EEPROM.writeByte(eepromTachoDebug, p);
                  debug = p;
                 }
                else
                 {
                  Serial.println(F("Invalid value for debug parameter"));
//                  EEPROM.writeByte(eepromTachoDebug, 0);
                  debug = 0;
                 }
               }
              break;

            case 930:
              if (parameter == "")
               {
                Serial.print(F("($930) demo value = "));
                Serial.println(EEPROM.readByte(eepromTachoDemo));
               }
              else
               {
                p = parameter.toInt();
                if (p < 6)
                 {
                  Serial.print(F("Setting ($930) demo value = "));
                  Serial.println(parameter);
                  EEPROM.writeByte(eepromTachoDemo, p);
                  demo = p;
                 }
                else
                 {
                  Serial.println(F("Invalid value for demo parameter"));
                  EEPROM.writeByte(eepromTachoDemo, 0);
                  demo = 0;
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


void tachoDemo()
 {

  int rpm =  0;

  while (rpm < (tachoRedline + 1500))
   {
    rpm += 100;

    displayRpm(rpm);
    delay(1000/demo);
   }

  delay(1000);

  if (demo >= 4)
   {
    while (rpm > 0)
     {
      rpm -= 100;

      displayRpm(rpm);
      delay(1000/demo);
     }

   }
  demo = 0;
 }

