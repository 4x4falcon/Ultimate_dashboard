/*
 *  Speedo_Functions.h
 */


void checkForEepromWrite() {

  if (debugSpeedo == 3)
   {
    Serial.print(F("odoTimeout     "));
    Serial.println(odoTimeout);
   }

  if ((millis() - lastOdometerWrite) > odoTimeout)
   {
    lastOdometerWrite = millis();
    if (odoNotSaved)
     {
      if (debugSpeedo == 3)
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
      if (debugSpeedo == 3)
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
* Writes total miles to EEPROM
* only if it's been longer than write frequency and totalMiles is greater than what is currently stored
* maybe if vehicle is only moving to
* this helps protect EEPROM from excessive writes
*/
void writeOdometer() {

  if ((loopTime - lastOdometerWrite) > odometerWriteFrequency)
   {
     {
      if (totalOdometer > EEPROM.readInt(eepromOdoAddress))
       {
        if (debugSpeedo == 3)
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
    if (debugSpeedo == 3)
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
 * ISR it counts the time for 100 pulses
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
       duration = millis() - lastVssTrigger;
       doSpeed = !doSpeed;
       lastVssTrigger = millis();
       
       Serial.print(F("duration     "));
       Serial.println(duration);
       Serial.print(F("lastVssTrigger    "));
       Serial.println(lastVssTrigger);
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

  Serial.println();
  Serial.print("Trip mode button long pressed");
  Serial.println();
  buttonTripLongPress = true;
  
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
#endif

  if (tempMode == FUNC_KPH)
   {
#ifdef ODOMETER_1602
    odo1602.print(F("drive 2 km      "));
#endif
#ifdef ODOMETER_OLED_128X64
#endif
   }
  else
   {
#ifdef ODOMETER_1602
    odo1602.print(F("drive 2 miles       "));
#endif
#ifdef ODOMETER_OLED_128X64
#endif
   }
   
// wait for button press
  do
   {
    delay(100);
   }
  while (digitalRead(pinModeButton));

  attachInterrupt(speedoInterrupt, countCalibrate, FALLING);

// show message start driving and press button at end
#ifdef ODOMETER_1602
    odo1602.print(F("start driving   "));
    odo1602.print(F("press mode @ end"));
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  delay(1000);
  do
   {
    sprintf(buffer, "%12d", calibrateCounter);
#ifdef ODOMETER_1602
// update the calibrate counter display;
    odo1602.setCursor(0, 0);
    odo1602.print("                ");
    odo1602.print(buffer);
#endif
#ifdef ODOMETER_OLED_128X64
#endif
   }
  while (digitalRead(pinModeButton));

// save calibrate data to eeprom
// TODO modify for MPH input

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
void buttonSpeedoModePressed(Button& b) {

/*
  modeSpeedoFunc++;
  if (modeSpeedoFunc > FUNC_CAL)
   {
    modeSpeedoFunc = FUNC_KPH;
   }
*/
  buttonSpeedoModeLongPress = false;
}

void buttonSpeedoModeReleased(Button& b)
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
* TODO write calibration function for speedo and tacho
*/

void buttonSpeedoModeLongPressed(Button& b)
 {
  buttonSpeedoModeLongPress = true;

  if ((speed ==  0) && (modeSpeedoFunc == FUNC_CAL))                              // only enter calibration if stationary and already selected calibrate
   {
    doCalibrate();
   }
 }




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

  if (totalOdometer > EEPROM.readInt(eepromOdoAddress))
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
  EEPROM.writeByte(eepromSpeedoModeFuncAddress, modeSpeedoFunc);
}

