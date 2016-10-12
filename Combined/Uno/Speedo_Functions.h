// Speedo_Functions.h
// Speedo Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the vehicle has stopped moving.
*
* save tripmeters and odometer to EEPROM here as well
*/


/*
 * no longer required now in Display.h updateSpeedoDisplay
 * here for reference only
*/
/*
void checkForSpeedoTimeout()
 {
  if ( (loopTime - lastVssTrigger) > timeoutValue )
   {
    speed = 0;
    displaySpeed (speed);

    if (debugSpeedo == 1)
     {
      Serial.print(F("pulseCount    "));
      Serial.println(pulseCount);
     }
   }

  if (debugSpeedo == 2)
   {
    Serial.print(F("timeout looptime    "));
    Serial.println(loopTime);
    Serial.print(F("timeout lastVssTrigger    "));
    Serial.println(lastVssTrigger);
    Serial.print(F("timeout timeoutValue    "));
    Serial.println(timeoutValue);
    Serial.print(F("timeout speed = "));
    Serial.println(speed);
   }
 }
*/

void checkForEepromWrite() {

#ifdef INCLUDE_DEBUG
  if (debugAll > 0)
   {
    Serial.print(F("odoTimeout     "));
    Serial.println(odoTimeout);
   }
#endif

  if ((millis() - lastOdometerWrite) > odoTimeout)
   {
    lastOdometerWrite = millis();
    if (odoNotSaved)
     {
#ifdef INCLUDE_DEBUG
      if (debugAll > 0)
       {
        Serial.print(F("Timeout Saving odometer to EEPROM    "));
        Serial.println(extEepromOdometer.totalOdometer);
       }
      else
#endif
       {
        EEPROM.writeLong(eepromOdoAddress, extEepromOdometer.totalOdometer);
       }
      odoNotSaved = !odoNotSaved;
     }
    if (tripNotSaved)
     {
#ifdef INCLUDE_DEBUG
      if (debugAll > 0)
       {
        Serial.print(F("Timeout Saving Trip_1 to EEPROM    "));
        Serial.println(totalTrip_1);
        Serial.print(F("Timeout Saving Trip_2 to EEPROM    "));
        Serial.println(totalTrip_2);
       }
      else
#endif
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
    if (extEepromOdometer.totalOdometer > EEPROM.readLong(eepromOdoAddress))
     {
#ifdef INCLUDE_DEBUG
      if (debugAll > 0)
       {
        Serial.print(F("Saving odometer to EEPROM    "));
        Serial.println(extEepromOdometer.totalOdometer);
       }
      else
#endif
       {
        EEPROM.writeLong(eepromOdoAddress, extEepromOdometer.totalOdometer);
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
#ifdef INCLUDE_DEBUG
    if (debugAll > 0)
     {
      Serial.print(F("Saving Trip_1 to EEPROM    "));
      Serial.println(totalTrip_1);
      Serial.print(F("Saving Trip_2 to EEPROM    "));
      Serial.println(totalTrip_2);
     }
    else
#endif
     {
      EEPROM.writeLong(eepromTrip1Address,totalTrip_1);
      EEPROM.writeLong(eepromTrip2Address,totalTrip_2);
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
 * ISR triggered by Vss counts the duration for 100 pulses (stored in pulseMaxCount)
 *
 */

void sensorTriggered_2() {

  unsigned long lastTrigger = micros();
  if (lastTrigger > lastVssTrigger)
   {
    pulseCount++;
    if (pulseCount == pulseMaxCount)
     {
      pulseCount = 0UL;
      durationSpeedo = micros() - lastVssTrigger;
      doSpeed = !doSpeed;
      lastVssTrigger = micros();

#ifdef INCLUDE_DEBUG
      if (debugSpeedo == 5)
       {
        Serial.print(F("durationSpeedo     "));
        Serial.println(durationSpeedo);
        Serial.print(F("lastVssTrigger    "));
        Serial.println(lastVssTrigger);
       }
#endif
     }

    extEepromOdometer.totalOdometer++;   // += pulseDistance;			// Increment odometer
    totalTrip_1++;       // += pulseDistance;                     // Increment tripmeter 1
    totalTrip_2++;       // += pulseDistance;                     // Increment tripmeter 2
    tripNotSaved = 1;                                 // tripmeters can be saved to EEPROM
    odoNotSaved = 1;                                  // odometer can be saved to EEPROM
   }
}

/*
* toggle between tripmeter_1 and tripmeter_2 when not in calibrate mode
*/
void buttonTripPressed(Button& buttonTrip) {
#ifdef DEBUGGING
  Serial.println();
  Serial.print("Trip mode button pressed");
  Serial.println();
#endif

  buttonTripLongPress = false;
//  modeTrip = !modeTrip;
}


void buttonTripReleased(Button& buttonTrip) {

  if (!buttonTripLongPress)
   {
    modeTrip = !modeTrip;

#ifdef DEBUGGING
    Serial.println();
    Serial.print("Trip mode button released");
    Serial.println();
#endif

   }
  buttonTripLongPress = false;
}


/*
* reset (current) trip meter only when trip button is long pressed
* odometer needs to be unchangeable
*/
void buttonTripLongPressed(Button& buttonTrip) {

  if (modeTrip == MODE_TRIPMETER_1)
   {
    totalTrip_1 = 0;
   }
  if (modeTrip == MODE_TRIPMETER_2)
   {
    totalTrip_2 = 0;
   }

#ifdef DEBUGGING
  Serial.println();
  Serial.print("Trip mode button long pressed");
  Serial.println();
  buttonTripLongPress = true;
#endif
  
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
#ifdef ODOMETER_1602
// clear the odo display
  odo1602.clear();

// show message on display to start and distance to drive
  odo1602.print(F("press mode      "));
//  i2c_SendString_16(odoAddress, (char *)F("press mode      "));

  odo1602.setCursor(0, 1);
  if (tempMode == FUNC_KPH)
   {
    odo1602.print(F("drive 2 km      "));
   }
  else
   {
    odo1602.print(F("drive 2 miles      "));
   }
#endif
#ifdef ODOMETER_OLED_128X64
#endif  

// wait for button press
  do
   {
    delay(100);
   }
  while (digitalRead(pinSpeedoModeButton));

  attachInterrupt(speedoInterrupt, countCalibrate, FALLING);

#ifdef ODOMETER_1602
// show message start driving and press button at end
//  i2c_SendString_16(odoAddress, (char *)F("start driving   "));
//  i2c_SendString_16(odoAddress, (char *)F("press mode @ end"));
  odo1602.clear();
  odo1602.print(F("start driving   "));
  odo1602.print(F("press mode @ end"));
#endif
#ifdef ODOMETER_OLED_128X64
#endif  

  delay(1000);
  do
   {
// update the calibrate counter display;

    sprintf(buffer, "%16d", calibrateCounter);

//    i2c_serlcd_ClearDisplay(odoAddress);
#ifdef ODOMETER_1602
    odo1602.clear();
    odo1602.print(buffer);
#endif
#ifdef ODOMETER_OLED_128X64
#endif  
    delay(100);
   }
  while (digitalRead(pinSpeedoModeButton));

// save calibrate data to eeprom{
  EEPROM.writeLong(eepromSpeedoCalibrateAddress, float(calibrateCounter/2));

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
void buttonSpeedoModePressed(Button& buttonSpeedoMode)
 {
/*  

  modeSpeedoFunc++;
  if (modeSpeedoFunc > FUNC_CAL)
   {
    modeSpeedoFunc = FUNC_KPH;
   }
*/
  buttonSpeedoModeLongPress = false;
 }

void buttonSpeedoModeReleased(Button& buttonSpeedoMode)
 {
  if (!buttonSpeedoModeLongPress)
   {
    modeSpeedoFunc++;
    if (modeSpeedoFunc > FUNC_CAL)
     {
      modeSpeedoFunc = FUNC_KPH;
     }
   }
  buttonSpeedoModeLongPress = false;
 }

/*
* enter calibration mode when mode button is long pressed
*/

void buttonSpeedoModeLongPressed(Button& buttonSpeedoMode) {
  if ((speed ==  0) && (modeSpeedoFunc == FUNC_CAL))                              // only enter calibration if stationary and already selected calibrate
   {
    doCalibrate();
   }
  buttonTripLongPress = true;
}


