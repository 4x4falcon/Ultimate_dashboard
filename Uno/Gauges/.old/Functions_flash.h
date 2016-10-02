//Functions.h

// do serial received commands

void doSerialCommand(String readString)
 {
    Serial.println(readString);  //so you can see the captured string 

    if (readString == "$")
     {
      Serial.println("EEPROM Contains");
      EEPROM.readBlock(eepromTitle, title);

      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[2])));
      Serial.print(buffer);
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[0])));
      Serial.print(buffer);
      Serial.println(title);
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[3])));
      Serial.print(buffer);
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[0])));
      Serial.print(buffer);
      Serial.println(EEPROM.readByte(eepromVersionHigh));
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[4])));
      Serial.print(buffer);
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[0])));
      Serial.print(buffer);
      Serial.println(EEPROM.readByte(eepromVersionLow));

/*
 // get gauge settings

  // Volt

      Serial.print(message300);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
      Serial.print(message301);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
      Serial.print(message302);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromVoltMinAddress));
      Serial.print(message303);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromVoltMaxAddress));
      Serial.print(message304);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromVoltWarnAddress));
      Serial.print(message305);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromVoltWarnLowAddress));


  // Oil pressure 

      Serial.print(message400);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromOilLowerAddress));
      Serial.print(message401);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromOilUpperAddress));
      Serial.print(message402);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromOilMinAddress));
      Serial.print(message403);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromOilMaxAddress));
      Serial.print(message404);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromOilWarnAddress));
      Serial.print(message405);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromOilWarnLowAddress));

  // Water temperature 

      Serial.print(message500);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromTempLowerAddress));
      Serial.print(message501);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromTempUpperAddress));
      Serial.print(message502);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromTempMinAddress));
      Serial.print(message503);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromTempMaxAddress));
      Serial.print(message504);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromTempWarnAddress));
      Serial.print(message505);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromTempWarnLowAddress));

  // Fuel level 

      Serial.print(message600);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
      Serial.print(message601);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
      Serial.print(message602);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromFuelMinAddress));
      Serial.print(message603);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromFuelMaxAddress));
      Serial.print(message604);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromFuelWarnAddress));
      Serial.print(message605);
      Serial.print(messageEqual);
      Serial.println(EEPROM.readByte(eepromFuelWarnLowAddress));
*/

/*
  // a  
      Serial.print("($?00)  lower calibration = ");
      Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
      Serial.print("($?01)  upper calibration = ");
      Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
      Serial.print("($?02)  minimum reading = ");
      Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
      Serial.print("($?03)  maximum reading = ");
      Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
      Serial.print("($?04)  warning reading = ");
      Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
      Serial.print("($?04)  warning low = ");
      Serial.println(EEPROM.readInt(eepromFuelWarnLowAddress));
*/

     }
    else
     {
      if (readString.startsWith("$"))
       {
        if (readString.startsWith("$0"))
         {
          Serial.println("Resetting EEPROM");
         }
        else
         {
          int pos = readString.indexOf("=");
          if (pos > 0)
           {

            String c = readString.substring(1, pos);
            int command = c.toInt();
            String para = readString.substring(pos + 1);

            switch (command)
             {
// Volt
              case 300:
                if (para == "")
                 {
                  Serial.print(message300);
                  Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message300);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromVoltLowerAddress, p);
                 }
                break;
              case 301:
                if (para == "")
                 {
                  Serial.print(message301);
                  Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message301);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromVoltUpperAddress, p);
                 }
                break;
              case 302:
                if (para == "")
                 {
                  Serial.print(message302);
                  Serial.println(EEPROM.readByte(eepromVoltMinAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message302);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromVoltMinAddress, p);
                 }
                break;
              case 303:
                if (para == "")
                 {
                  Serial.print(message303);
                  Serial.println(EEPROM.readByte(eepromVoltMaxAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message303);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromVoltMaxAddress, p);
                 }
                break;
              case 304:
                if (para == "")
                 {
                  Serial.print(message304);
                  Serial.println(EEPROM.readByte(eepromVoltWarnAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message304);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromVoltWarnAddress, p);
                 }
                break;
              case 305:
                if (para == "")
                 {
                  Serial.print(message305);
                  Serial.println(EEPROM.readByte(eepromVoltWarnLowAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message305);
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromVoltWarnLowAddress, p);
                 }
                break;


// Oil pressure 
              case 400:
                if (para == "")
                 {
                  Serial.print(message400);
                  Serial.println(EEPROM.readInt(eepromOilLowerAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message400);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromOilLowerAddress, p);
                 }
                break;
              case 401:
                if (para == "")
                 {
                  Serial.print(message401);
                  Serial.println(EEPROM.readInt(eepromOilUpperAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message401);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromOilUpperAddress, p);
                 }
                break;
              case 402:
                if (para == "")
                 {
                  Serial.print(message402);
                  Serial.println(EEPROM.readByte(eepromOilMinAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message402);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromOilMinAddress, p);
                 }
                break;
              case 403:
                if (para == "")
                 {
                  Serial.print(message403);
                  Serial.println(EEPROM.readByte(eepromOilMaxAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message403);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromOilMaxAddress, p);
                 }
                break;
              case 404:
                if (para == "")
                 {
                  Serial.print(message404);
                  Serial.println(EEPROM.readByte(eepromOilWarnAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message404);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromOilWarnAddress, p);
                 }
                break;
              case 405:
                if (para == "")
                 {
                  Serial.print(message405);
                  Serial.println(EEPROM.readByte(eepromOilWarnLowAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message404);
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromOilWarnLowAddress, p);
                 }
                break;

// Water Temperature 
              case 500:
                if (para == "")
                 {
                  Serial.print(message500);
                  Serial.println(EEPROM.readInt(eepromTempLowerAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message500);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromTempLowerAddress, p);
                 }
                break;
              case 501:
                if (para == "")
                 {
                  Serial.print(message501);
                  Serial.println(EEPROM.readInt(eepromTempUpperAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message501);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromTempUpperAddress, p);
                 }
                break;
              case 502:
                if (para == "")
                 {
                  Serial.print(message502);
                  Serial.println(EEPROM.readByte(eepromTempMinAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message502);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromTempMinAddress, p);
                 }
                break;
              case 503:
                if (para == "")
                 {
                  Serial.print(message503);
                  Serial.println(EEPROM.readByte(eepromTempMaxAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message503);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromTempMaxAddress, p);
                 }
                break;
              case 504:
                if (para == "")
                 {
                  Serial.print(message504);
                  Serial.println(EEPROM.readByte(eepromTempWarnAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message504);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromTempWarnAddress, p);
                 }
                break;
              case 505:
                if (para == "")
                 {
                  Serial.print(message505);
                  Serial.println(EEPROM.readByte(eepromTempWarnAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message505);
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromTempWarnAddress, p);
                 }
                break;

// Fuel Level 
              case 600:
                if (para == "")
                 {
                  Serial.print(message600);
                  Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message500);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromFuelLowerAddress, p);
                 }
                break;
              case 601:
                if (para == "")
                 {
                  Serial.print(message601);
                  Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message601);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromFuelUpperAddress, p);
                 }
                break;
              case 602:
                if (para == "")
                 {
                  Serial.print(message602);
                  Serial.println(EEPROM.readByte(eepromFuelMinAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message602);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromFuelMinAddress, p);
                 }
                break;
              case 603:
                if (para == "")
                 {
                  Serial.print(message603);
                  Serial.println(EEPROM.readByte(eepromFuelMaxAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message603);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromFuelMaxAddress, p);
                 }
                break;
              case 604:
                if (para == "")
                 {
                  Serial.print(message604);
                  Serial.println(EEPROM.readByte(eepromFuelWarnAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message604);
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromFuelWarnAddress, p);
                 }
                break;
              case 605:
                if (para == "")
                 {
                  Serial.print(message605);
                  Serial.println(EEPROM.readByte(eepromFuelWarnLowAddress));
                 }
                else
                 {
                  Serial.print(message001);
                  Serial.print(message605);
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromFuelWarnAddress, p);
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


