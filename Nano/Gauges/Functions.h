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
      Serial.print(F("Ver high = "));
      Serial.println(EEPROM.readByte(eepromVersionHigh));
      Serial.print(F("Ver low = "));
      Serial.println(EEPROM.readByte(eepromVersionLow));


 // get gauge settings

  // Volt

      Serial.print(F("($300)Volt lower calibration = "));
      Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
      Serial.print(F("($301)Volt upper calibration = "));
      Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
      Serial.print(F("($302)Volt minimum reading = "));
      Serial.println(EEPROM.readByte(eepromVoltMinAddress));
      Serial.print(F("($303)Volt maximum reading = "));
      Serial.println(EEPROM.readByte(eepromVoltMaxAddress));
      Serial.print(F("($304)Volt warning reading = "));
      Serial.println(EEPROM.readByte(eepromVoltWarnAddress));
      Serial.print(F("($305)Volt warning low = "));
      Serial.println(EEPROM.readByte(eepromVoltWarnLowAddress));


  // Oil pressure 

      Serial.print(F("($400)Oil pressure  lower calibration = "));
      Serial.println(EEPROM.readInt(eepromOilLowerAddress));
      Serial.print(F("($401)Oil pressure  upper calibration = "));
      Serial.println(EEPROM.readInt(eepromOilUpperAddress));
      Serial.print(F("($402)Oil pressure  minimum reading = "));
      Serial.println(EEPROM.readByte(eepromOilMinAddress));
      Serial.print(F("($403)Oil pressure  maximum reading = "));
      Serial.println(EEPROM.readByte(eepromOilMaxAddress));
      Serial.print(F("($404)Oil pressure  warning reading = "));
      Serial.println(EEPROM.readByte(eepromOilWarnAddress));
      Serial.print(F("($405)Oil pressure  warning low = "));
      Serial.println(EEPROM.readByte(eepromOilWarnLowAddress));

  // Water temperature 

      Serial.print(F("($500)Water temperature  lower calibration = "));
      Serial.println(EEPROM.readInt(eepromTempLowerAddress));
      Serial.print(F("($501)Water temperature  upper calibration = "));
      Serial.println(EEPROM.readInt(eepromTempUpperAddress));
      Serial.print(F("($502)Water temperature  minimum reading = "));
      Serial.println(EEPROM.readByte(eepromTempMinAddress));
      Serial.print(F("($503)Water temperature  maximum reading = "));
      Serial.println(EEPROM.readByte(eepromTempMaxAddress));
      Serial.print(F("($504)Water temperature  warning reading = "));
      Serial.println(EEPROM.readByte(eepromTempWarnAddress));
      Serial.print(F("($505)Water temperature  warning low = "));
      Serial.println(EEPROM.readByte(eepromTempWarnLowAddress));

  // Fuel level 

      Serial.print(F("($600)Fuel level  lower calibration = "));
      Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
      Serial.print(F("($601)Fuel level  upper calibration = "));
      Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
      Serial.print(F("($602)Fuel level  minimum reading = "));
      Serial.println(EEPROM.readByte(eepromFuelMinAddress));
      Serial.print(F("($603)Fuel level  maximum reading = "));
      Serial.println(EEPROM.readByte(eepromFuelMaxAddress));
      Serial.print(F("($604)Fuel level  warning reading = "));
      Serial.println(EEPROM.readByte(eepromFuelWarnAddress));
      Serial.print(F("($605)Fuel level  warning low = "));
      Serial.println(EEPROM.readByte(eepromFuelWarnLowAddress));

/*
  // a  
      Serial.print(F("($?00)  lower calibration = "));
      Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
      Serial.print(F("($?01)  upper calibration = "));
      Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
      Serial.print(F("($?02)  minimum reading = "));
      Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
      Serial.print(F("($?03)  maximum reading = "));
      Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
      Serial.print(F("($?04)  warning reading = "));
      Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
      Serial.print(F("($?04)  warning low = "));
      Serial.println(EEPROM.readInt(eepromFuelWarnLowAddress));
*/

      Serial.print(F("($910)Gauges Debug = "));
      Serial.println(EEPROM.readByte(eepromGaugesDebugAddress));

      Serial.print(F("($940)Gauges Demo = "));
      Serial.println(EEPROM.readByte(eepromGaugesDemoAddress));
      Serial.println();
      Serial.print(F("brightness = "));
      sprintf(buffer, "%4d", brightnessBoost);
      Serial.println(buffer);

      Serial.println();
      Serial.print(F("Volt value = "));
      sprintf(buffer, "%4d", voltVal);
      Serial.println(buffer);
      Serial.println();
      Serial.print(F("Oil value = "));
      sprintf(buffer, "%4d", oilVal);
      Serial.println(buffer);
      Serial.println();
      Serial.print(F("Temp value = "));
      sprintf(buffer, "%4d", tempVal);
      Serial.println(buffer);
      Serial.println();
      Serial.print(F("Fuel value = "));
      sprintf(buffer, "%4d", fuelVal);
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
          Serial.println(F("Resetting EEPROM except for odo"));
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
                  Serial.print(F("($300)Volt lower value = "));
                  Serial.println(EEPROM.readInt(eepromVoltLowerAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($300) Volt Lower value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromVoltLowerAddress, p);
                 }
                break;
              case 301:
                if (para == "")
                 {
                  Serial.print(F("($301)Volt upper value = "));
                  Serial.println(EEPROM.readInt(eepromVoltUpperAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($301) Volt Upper value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromVoltUpperAddress, p);
                 }
                break;
              case 302:
                if (para == "")
                 {
                  Serial.print(F("($302)Volt min value = "));
                  Serial.println(EEPROM.readInt(eepromVoltMinAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($302) Volt min value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromVoltMinAddress, p);
                 }
                break;
              case 303:
                if (para == "")
                 {
                  Serial.print(F("($303)Volt max value = "));
                  Serial.println(EEPROM.readInt(eepromVoltMaxAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($303) Volt max value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromVoltMaxAddress, p);
                 }
                break;
              case 304:
                if (para == "")
                 {
                  Serial.print(F("($304)Volt warn value = "));
                  Serial.println(EEPROM.readInt(eepromVoltWarnAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($304) Volt warn value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromVoltWarnAddress, p);
                 }
                break;
              case 305:
                if (para == "")
                 {
                  Serial.print(F("($305)Volt warn low value = "));
                  Serial.println(EEPROM.readInt(eepromVoltWarnLowAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($305) Volt warn low value = "));
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromVoltWarnLowAddress, p);
                 }
                break;


// Oil pressure 
              case 400:
                if (para == "")
                 {
                  Serial.print(F("($400)Oil Pressure  lower value = "));
                  Serial.println(EEPROM.readInt(eepromOilLowerAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($400) Oil Pressure Lower value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromOilLowerAddress, p);
                 }
                break;
              case 401:
                if (para == "")
                 {
                  Serial.print(F("($401)Oil Pressure upper value = "));
                  Serial.println(EEPROM.readInt(eepromOilUpperAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($401) Oil Pressure Upper value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromOilUpperAddress, p);
                 }
                break;
              case 402:
                if (para == "")
                 {
                  Serial.print(F("($402) Oil Pressure min value = "));
                  Serial.println(EEPROM.readInt(eepromOilMinAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($402) Oil Pressure min value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromOilMinAddress, p);
                 }
                break;
              case 403:
                if (para == "")
                 {
                  Serial.print(F("($403) Oil Pressure max value = "));
                  Serial.println(EEPROM.readInt(eepromOilMaxAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($403) Oil Pressure max value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromOilMaxAddress, p);
                 }
                break;
              case 404:
                if (para == "")
                 {
                  Serial.print(F("($404) Oil Pressure warn value = "));
                  Serial.println(EEPROM.readInt(eepromOilWarnAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($404) Oil Pressure warn value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromOilWarnAddress, p);
                 }
                break;
              case 405:
                if (para == "")
                 {
                  Serial.print(F("($405) Oil Pressure warn low value = "));
                  Serial.println(EEPROM.readInt(eepromOilWarnLowAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($404) Oil Pressure warn low value = "));
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromOilWarnLowAddress, p);
                 }
                break;

// Water Temperature 
              case 500:
                if (para == "")
                 {
                  Serial.print(F("($500) Water Temperature  lower value = "));
                  Serial.println(EEPROM.readInt(eepromTempLowerAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($500) Water Temperature Lower value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromTempLowerAddress, p);
                 }
                break;
              case 501:
                if (para == "")
                 {
                  Serial.print(F("($501) Water Temperature upper value = "));
                  Serial.println(EEPROM.readInt(eepromTempUpperAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($501) Water Temperature Upper value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromTempUpperAddress, p);
                 }
                break;
              case 502:
                if (para == "")
                 {
                  Serial.print(F("($502) Water Temperature min value = "));
                  Serial.println(EEPROM.readInt(eepromTempMinAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($502) Water Temperature min value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeByte(eepromTempMinAddress, p);
                 }
                break;
              case 503:
                if (para == "")
                 {
                  Serial.print(F("($503) Water Temperature max value = "));
                  Serial.println(EEPROM.readInt(eepromTempMaxAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($503) Water Temperature max value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromTempMaxAddress, p);
                 }
                break;
              case 504:
                if (para == "")
                 {
                  Serial.print(F("($504) Water Temperature warn value = "));
                  Serial.println(EEPROM.readInt(eepromTempWarnAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($504) Water Temperature warn value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromTempWarnAddress, p);
                 }
                break;
              case 505:
                if (para == "")
                 {
                  Serial.print(F("($505) Water Temperature warn low value = "));
                  Serial.println(EEPROM.readInt(eepromTempWarnAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($505) Water Temperature warn low value = "));
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromTempWarnAddress, p);
                 }
                break;

// Fuel Level 
              case 600:
                if (para == "")
                 {
                  Serial.print(F("($600) Fuel Level  lower value = "));
                  Serial.println(EEPROM.readInt(eepromFuelLowerAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($500) Fuel Level Lower value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromFuelLowerAddress, p);
                 }
                break;
              case 601:
                if (para == "")
                 {
                  Serial.print(F("($601) Fuel Level upper value = "));
                  Serial.println(EEPROM.readInt(eepromFuelUpperAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($501) Fuel Level Upper value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromFuelUpperAddress, p);
                 }
                break;
              case 602:
                if (para == "")
                 {
                  Serial.print(F("($602) Fuel Level min value = "));
                  Serial.println(EEPROM.readInt(eepromFuelMinAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($502) Fuel Level min value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromFuelMinAddress, p);
                 }
                break;
              case 603:
                if (para == "")
                 {
                  Serial.print(F("($603) Fuel Level max value = "));
                  Serial.println(EEPROM.readInt(eepromFuelMaxAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($503) Fuel Level max value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromFuelMaxAddress, p);
                 }
                break;
              case 604:
                if (para == "")
                 {
                  Serial.print(F("($604) Fuel Level warn value = "));
                  Serial.println(EEPROM.readInt(eepromFuelWarnAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($604) Fuel Level warn value = "));
                  Serial.println(para);
                  int p = para.toInt();
                  // EEPROM.writeInt(eepromFuelWarnAddress, p);
                 }
                break;
              case 605:
                if (para == "")
                 {
                  Serial.print(F("($605) Fuel Level warn low value = "));
                  Serial.println(EEPROM.readInt(eepromFuelWarnLowAddress));
                 }
                else
                 {
                  Serial.print(F("Setting ($605) Fuel Level warn low value = "));
                  Serial.println(para);
                  byte p = para.toInt();
                  // EEPROM.writeByte(eepromFuelWarnAddress, p);
                 }
                break;



            case 910:
              if (para == "")
               {
                Serial.print(F("($910) debug value = "));
                Serial.println(EEPROM.readByte(eepromGaugesDebugAddress));
               }
              else
               {
                p = para.toInt();
                if (p < 4)
                 {
                  Serial.print(F("Setting ($910) debug value = "));
                  Serial.println(para);
                  EEPROM.writeByte(eepromGaugesDebugAddress, p);
                  debug = p;
                 }
                else
                 {
                  Serial.println(F("Invalid value for debug parameter"));
                  debug = 0;
                 }
               }
              break;

            case 940:
              if (para == "")
               {
                Serial.print(F("($940) demo value = "));
                Serial.println(EEPROM.readByte(eepromGaugesDemoAddress));
               }
              else
               {
                p = para.toInt();
                if (p < 6)
                 {
                  Serial.print(F("Setting ($940) demo value = "));
                  Serial.println(para);
                  EEPROM.writeByte(eepromGaugesDemoAddress, p);
                  demo = p;
                 }
                else
                 {
                  Serial.println(F("Invalid value for demo parameter"));
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
//    readString=""; //empty for next input

  
 }


float fastMap(long x, long in_min, long in_max, long out_min, long out_max)
  {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }




/*
#define DIGIT1  0x7B
#define DIGIT2  0x7C
#define DIGIT3  0x7D
#define DIGIT4  0x7E

#define SEGMENT1  0
#define SEGMENT2  1
#define SEGMENT3  2
#define SEGMENT4  3
#define SEGMENT5  4
#define SEGMENT6  5
#define SEGMENT7  6




void gaugesDemo()
 {

  int rpm =  0;

  if (demo == 1)     // display each decimal, apostrophe and colon
   {
    while (rpm < 64)
     {
      voltSerial.write(0x77);
//      voltSerial.write(0b00000100);  // sets digit 3 decimal on
      voltSerial.write(rpm);

      tempSerial.write(0x77);
      tempSerial.write(rpm);

      oilSerial.write(0x77);
      oilSerial.write(rpm);

      fuelSerial.write(0x77);
      fuelSerial.write(rpm);

      if (rpm == 0)
       {
        rpm +=1;
       }
      rpm *= 2;
      delay(1000);
     }
   }

  if (demo == 2)       // display each segment
   {
    while (rpm < 128)
     {
      voltSerial.write(DIGIT1);
      voltSerial.write(rpm);
      voltSerial.write(DIGIT2);
      voltSerial.write(rpm);
      voltSerial.write(DIGIT3);
      voltSerial.write(rpm);
      voltSerial.write(DIGIT4);
      voltSerial.write(rpm);

      tempSerial.write(DIGIT1);
      tempSerial.write(rpm);
      tempSerial.write(DIGIT2);
      tempSerial.write(rpm);
      tempSerial.write(DIGIT3);
      tempSerial.write(rpm);
      tempSerial.write(DIGIT4);
      tempSerial.write(rpm);

      oilSerial.write(DIGIT1);
      oilSerial.write(rpm);
      oilSerial.write(DIGIT2);
      oilSerial.write(rpm);
      oilSerial.write(DIGIT3);
      oilSerial.write(rpm);
      oilSerial.write(DIGIT4);
      oilSerial.write(rpm);

      fuelSerial.write(DIGIT1);
      fuelSerial.write(rpm);
      fuelSerial.write(DIGIT2);
      fuelSerial.write(rpm);
      fuelSerial.write(DIGIT3);
      fuelSerial.write(rpm);
      fuelSerial.write(DIGIT4);
      fuelSerial.write(rpm);

      if (rpm == 0)
       {
        rpm +=1;
       }
      rpm *= 2;
      delay(500);
     }
   }

  if (demo == 3)      // random bits
   {

//Seed random generator with analog input - nothing needs to be connected to A7
    randomSeed(analogRead(7));
    
    while (rpm < 64)
     {

      for(int x = 0 ; x < 4 ; x++)
       {
        byte randNumber = random(0, 127);    //Give me random number between 0 and 127
        voltSerial.write(DIGIT1 + x);        //Control individual segments on a digit
        voltSerial.write(randNumber);        //Turn on random segments

        tempSerial.write(DIGIT1 + x);        //Control individual segments on a digit
        tempSerial.write(randNumber);        //Turn on random segments

        oilSerial.write(DIGIT1 + x);        //Control individual segments on a digit
        oilSerial.write(randNumber);        //Turn on random segments

        fuelSerial.write(DIGIT1 + x);        //Control individual segments on a digit
        fuelSerial.write(randNumber);        //Turn on random segments
       }

      rpm += 1;
      delay(500);
     }
   }

  if (demo == 4)      // countdown predator
   {

    rpm = 127;

    while (rpm >= 0)
     {
      tempSerial.write(DIGIT1);
      tempSerial.write(rpm);
      tempSerial.write(DIGIT2);
      tempSerial.write(rpm);
      tempSerial.write(DIGIT3);
      tempSerial.write(rpm);
      tempSerial.write(DIGIT4);
      tempSerial.write(rpm);
      
      rpm -= 1;
      delay(500);
     }
   }



  delay(1000);

  demo = 0;
  voltSerial.write(0x76);
  voltSerial.write(0x77);
  voltSerial.write(0b00000100);  // sets digit 3 decimal on

  tempSerial.write(0x76);
  tempSerial.write(0x77);
  tempSerial.write(0b00000100);  // sets digit 3 decimal on

  oilSerial.write(0b00000100);   // sets digit 3 decimal on
  oilSerial.write(0x77);
  oilSerial.write(0x76);

  fuelSerial.write(0b00000100);  // sets digit 3 decimal on
  fuelSerial.write(0x77);
  fuelSerial.write(0x76);
 }
*/

