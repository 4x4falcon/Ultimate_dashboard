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

 // get tacho settings

      Serial.print("($200)Tacho Calibration = ");
      Serial.println(EEPROM.readByte(eepromTachoCalibrate));
      Serial.print("($201)Tacho Type = ");
      Serial.println(EEPROM.readByte(eepromTachoType));
      Serial.print("($202)Tacho Redline = ");
      Serial.println(EEPROM.readInt(eepromTachoRedline));
      Serial.print("($203)Tacho Shift = ");
      Serial.println(EEPROM.readInt(eepromTachoShift));
      Serial.print("($204)Tacho Maximum = ");
      Serial.println(EEPROM.readInt(eepromTachoMaximum));


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


// tacho
              case 200:
                if (parameter == "")
                 {
                  Serial.print("($200)Tachometer calibrate value = ");
                  Serial.println(EEPROM.readByte(eepromTachoCalibrate));
                 }
                else
                 {
                  Serial.print("Setting ($200) Tachometer calibrate value = ");
                  Serial.println(parameter);
                  // EEPROM.writeByte(eepromTachoCalibrate, parameter);
                 }
                break;
              case 201:
                if (parameter == "")
                 {
                  Serial.print("($201)Tachometer type value = ");
                  Serial.println(EEPROM.readByte(eepromTachoType));
                 }
                else
                 {
                  Serial.print("Setting ($201) Tacho type value = ");
                  Serial.println(parameter);
                  // EEPROM.writeByte(eepromTachoType, parameter);
                 }
                break;
              case 202:
                if (parameter == "")
                 {
                  Serial.print("($202)Tachometer Redline value = ");
                  Serial.println(EEPROM.readInt(eepromTachoRedline));
                 }
                else
                 {
                  Serial.print("Setting ($202) Tacho Redline value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromTachoRedline, parameter);
                 }
                break;
              case 203:
                if (parameter == "")
                 {
                  Serial.print("($203)Tachometer shift value = ");
                  Serial.println(EEPROM.readInt(eepromTachoShift));
                 }
                else
                 {
                  Serial.print("Setting ($203) Tacho shift value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromTachoShift, parameter);
                 }
                break;
              case 204:
                if (parameter == "")
                 {
                  Serial.print("($204)Tachometer maximum value = ");
                  Serial.println(EEPROM.readInt(eepromTachoMaximum));
                 }
                else
                 {
                  Serial.print("Setting ($204) Tacho maximum value = ");
                  Serial.println(parameter);
                  // EEPROM.writeInt(eepromTachoMaximum, parameter);
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


