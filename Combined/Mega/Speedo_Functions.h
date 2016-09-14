// Speedo_Functions.h
// Speedo Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the vehicle has stopped moving.
*
* save tripmeters and odometer to EEPROM here as well
*/
void checkForSpeedoTimeout() {

  unsigned long lT = lastTrigger;
  
  if ( (loopTime > lT) && (lT > timeoutValue) && ((loopTime - lT) > timeoutValue) )
   {
    speed = 0;
    displaySpeed (speed);

    if (debugSpeedo > 0)
     {
      Serial.print(F("pulseCount    "));
      Serial.println(pulseCount);
     }

    if (debugSpeedo > 1)
     {
      Serial.print(F("timeout looptime    "));
      Serial.println(loopTime);
      Serial.print(F("timeout lastVssTrigger    "));
      Serial.println(lastVssTrigger);
      Serial.print(F("timeout lastTrigger    "));
      Serial.println(lastTrigger);
      Serial.print(F("timeout timeoutValue    "));
      Serial.println(timeoutValue);   
     }
   }
}

void checkForEepromWrite() {

  if (debugAll > 0)
   {
    Serial.print(F("odoTimeout     "));
    Serial.println(odoTimeout);
   }

  if ((millis() - lastOdometerWrite) > odoTimeout)
   {
    lastOdometerWrite = millis();
    if (odoNotSaved)
     {
      if (debugAll > 0)
       {
        Serial.print(F("Timeout Saving odometer to EEPROM    "));
        Serial.println(totalOdometer);
       }
      else
       {
        EEPROM.writeLong(eepromOdoAddress, totalOdometer);
       }
      odoNotSaved = !odoNotSaved;
     }
    if (tripNotSaved)
     {
      if (debugAll > 0)
       {
        Serial.print(F("Timeout Saving Trip_1 to EEPROM    "));
        Serial.println(totalTrip_1);
        Serial.print(F("Timeout Saving Trip_2 to EEPROM    "));
        Serial.println(totalTrip_2);
       }
      else
       {
        EEPROM.writeLong(eepromTrip1Address,totalTrip_1);
        EEPROM.writeLong(eepromTrip2Address,totalTrip_2);
       }
      tripNotSaved = !tripNotSaved;
    }
  }
}

/*
* Writes odometer total to EEPROM
* only if it's been longer than write frequency and totalOdometer is greater than what is currently stored
* maybe if vehicle is only moving to0
* this helps protect EEPROM from excessive writes
*/
void writeOdometer() {

  if ((loopTime - lastOdometerWrite) > odometerWriteFrequency)
   {
    if (totalOdometer > EEPROM.readFloat(eepromOdoAddress))
     {
      if (debugAll > 0)
       {
        Serial.print(F("Saving odometer to EEPROM    "));
        Serial.println(totalOdometer);
       }
      else
       {
        EEPROM.writeFloat(eepromOdoAddress, totalOdometer);
       }
      lastOdometerWrite = loopTime;
     }
   }
}

/*
* write tripmeters to EEPROM
*
* tripmeters are stored in ram so are volatile to power removal
*
* as the board will be constantly powered and only go into a sleep mode when the ignition is turned to off this should not be a problem
* this function is only called when going to sleep
*
*/

void writeTripmeter() {

  if ((speed == 0) && (tripNotSaved))
   {
    if (debugAll > 0)
     {
      Serial.print(F("Saving Trip_1 to EEPROM    "));
      Serial.println(totalTrip_1);
      Serial.print(F("Saving Trip_2 to EEPROM    "));
      Serial.println(totalTrip_2);
     }
    else
     {
      EEPROM.writeFloat(eepromTrip1Address,totalTrip_1);
      EEPROM.writeFloat(eepromTrip2Address,totalTrip_2);
     }
    tripNotSaved = !tripNotSaved;
   }
  else
   {
    tripNotSaved = 1;
   }
}

/*
 *
 * ISR triggered by Vss counts the duration for 100 pulses
 *
 */

void sensorTriggered_2() {

  lastTrigger = millis();
  if (lastTrigger > lastVssTrigger)
   {
    pulseCount++;
    if (pulseCount == pulseMaxCount)
     {
      pulseCount = 0UL;
      durationSpeedo = millis() - lastVssTrigger;
      doSpeed = !doSpeed;
      lastVssTrigger = millis();

      if (debugSpeedo > 0)
       {
        Serial.print(F("durationSpeedo     "));
        Serial.println(durationSpeedo);
        Serial.print(F("lastVssTrigger    "));
        Serial.println(lastVssTrigger);
       }
     }

    totalOdometer++;   // += pulseDistance;			// Increment odometer
    totalTrip_1++;       // += pulseDistance;                     // Increment tripmeter 1
    totalTrip_2++;       // += pulseDistance;                     // Increment tripmeter 2
    tripNotSaved = 1;                                 // tripmeters can be saved to EEPROM
    odoNotSaved = 1;                                  // odometer can be saved to EEPROM
   }
}

/*
* toggle between tripmeter_1 and tripmeter_2 when not in calibrate mode
*/
void buttonTripPressed() {
  modeTrip = !modeTrip;
}

/*
* reset (current) trip meter only when trip button is long pressed
* odometer needs to be unchangeable
*/
void buttonTripLongPressed() {

  if (modeTrip == MODE_TRIPMETER_1)
   {
    totalTrip_1 = 0;
   }
  if (modeTrip == MODE_TRIPMETER_2)
   {
    totalTrip_2 = 0;
   }
}

/*
*
* These are the calibration functions
*
*
*/

void countCalibrate () {
  calibrateCounter++;
}

void doCalibrate() {

  byte tempMode = EEPROM.readByte(eepromSpeedoModeFuncAddress);
  
  calibrateCounter = 0;

  detachInterrupt(speedoInterrupt);

// clear the odo display
// TODO via I2C

//  odoSerial.write(254);
//  odoSerial.write(128);

//  odoSerial.write("                "));
//  odoSerial.write("                "));

// show message on display to start and distance to drive
//  odoSerial.print(F("press mode      "));

  if (tempMode == FUNC_KPH)
   {
//    odoSerial.print(F("drive 2 km      "));
   }
  else
   {
//    odoSerial.print(F("drive 2 m       "));
   }

// wait for button press
  do
   {
    delay(100);
   }
  while (digitalRead(pinSpeedoModeButton));

  attachInterrupt(speedoInterrupt, countCalibrate, FALLING);

// show message start driving and press button at end
//  odoSerial.print(F("start driving   "));
//  odoSerial.print(F("press mode @ end"));

  delay(1000);
  do
   {
// update the calibrate counter display;
// TODO via I2C

//    odoSerial.print(F("                "));
    sprintf(buffer, "%12d", calibrateCounter);
//    odoSerial.print(buffer);
   }
  while (digitalRead(pinSpeedoModeButton));

// save calibrate data to eeprom{
  EEPROM.writeFloat(eepromSpeedoCalibrateAddress, float(calibrateCounter/2));

  detachInterrupt(speedoInterrupt);

  attachInterrupt(speedoInterrupt, sensorTriggered_2, FALLING);
  
  // return to default mode
  modeSpeedoFunc = tempMode;
  setupOdometerDisplay();
}

/* RKS
*
* toggle between functions when mode button is pressed
* this cycles between KPH, MPH and CAL if others are added then change FUNC_CAL to FUNC_
*
*/
void buttonSpeedoModePressed() {
  modeSpeedoFunc++;
  if (modeSpeedoFunc > FUNC_CAL)
   {
    modeSpeedoFunc = FUNC_KPH;
   }
}

/*
* enter calibration mode when mode button is long pressed
* TODO write calibration function for speedo and tacho
*/

void buttonSpeedoModeLongPressed() {
  if ((speed ==  0) && (modeSpeedoFunc == FUNC_CAL))                              // only enter calibration if stationary and already selected calibrate
   {
    doCalibrate();
   }
}


