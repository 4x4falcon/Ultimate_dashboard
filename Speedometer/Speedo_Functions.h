// Speedo Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the vehicle has stopped moving.
*
* save tripmeters and odometer to EEPROM here as well
*/
void checkForTimeout() {

  unsigned long lT = lastTrigger;
  
  if ( (loopTime > lT) && (lT > timeoutValue) && ((loopTime - lT) > timeoutValue) )
   {
    speed = 0;
    displaySpeed (speed);

#ifdef ECHO_SERIAL
      Serial.print("pulseCount    ");
      Serial.println(pulseCount);
#endif

#ifdef ECHO_SERIAL_2
      Serial.print("timeout looptime    ");
      Serial.println(loopTime);
      Serial.print("timeout lastVssTrigger    ");
      Serial.println(lastVssTrigger);
      Serial.print("timeout lastTrigger    ");
      Serial.println(lastTrigger);
      Serial.print("timeout timeoutValue    ");
      Serial.println(timeoutValue);   
#endif
   }
}

void checkForEepromWrite() {

#ifdef ECHO_SERIAL_3
        Serial.print("odoTimeout     ");
        Serial.println(odoTimeout);
#endif

  if ((millis() - lastOdometerWrite) > odoTimeout)
   {
    lastOdometerWrite = millis();
    if (odoNotSaved)
     {
#ifdef ECHO_SERIAL_3
        Serial.print("Timeout Saving odometer to EEPROM    ");
        Serial.println(totalOdometer);
#else
      EEPROM.writeLong(eepromOdoAddress, totalOdometer);
#endif
      odoNotSaved = !odoNotSaved;
     }
    if (tripNotSaved)
     {
  #ifdef ECHO_SERIAL_3
        Serial.print("Timeout Saving Trip_1 to EEPROM    ");
        Serial.println(totalTrip_1);
        Serial.print("Timeout Saving Trip_2 to EEPROM    ");
        Serial.println(totalTrip_2);
  #else
     EEPROM.writeLong(eepromTrip1Address,totalTrip_1);
     EEPROM.writeLong(eepromTrip2Address,totalTrip_2);
  #endif
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
//    if (rps > 0.01)
     {
      if (totalOdometer > EEPROM.readFloat(eepromOdoAddress))
       {
#ifdef ECHO_SERIAL
        Serial.print("Saving odometer to EEPROM    ");
        Serial.println(totalOdometer);
#else
        EEPROM.writeFloat(eepromOdoAddress, totalOdometer);
#endif
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

  if ((rps < 0.00001) && (tripNotSaved))
   {
#ifdef ECHO_SERIAL
        Serial.print("Saving Trip_1 to EEPROM    ");
        Serial.println(totalTrip_1);
        Serial.print("Saving Trip_2 to EEPROM    ");
        Serial.println(totalTrip_2);
#else
    EEPROM.writeFloat(eepromTrip1Address,totalTrip_1);
    EEPROM.writeFloat(eepromTrip2Address,totalTrip_2);
#endif

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
       
       Serial.print("duration     ");
       Serial.println(duration);
       Serial.print("lastVssTrigger    ");
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
* Updates the speedo and odometer screen depending on the current mode
*
*/
void updateDisplay() {

  if (doSpeed)
   {
    doSpeed = !doSpeed;

#ifdef ECHO_SERIAL
  Serial.print("duration   ");
  Serial.println(duration);
  Serial.print("pulseMaxCount   ");
  Serial.println(pulseMaxCount);
  Serial.print("pulseDistance   ");
  Serial.println(pulseDistance);
#endif

    speed = int(((((1000.0 * float(pulseMaxCount)) / float(duration)) * pulseDistance) * 3600.0) / 1000.0);
    displaySpeed(speed);

#ifdef ECHO_SERIAL_2
  Serial.print ("Speed    ");
  Serial.println (speed);
#endif

//update odometer
    displayOdometer();

//update tripmeters
    displayTripmeter();

// toggle pin 13 led for  debugging
    arduinoLed = !arduinoLed;
    digitalWrite(13, arduinoLed);


   }
  setBrightness();
}


/*
* toggle between tripmeter_1 and tripmeter_2 when not in calibrate mode
*/
void buttonTripPressed() {
  if (modeFunc != FUNC_CAL)
   {
    modeTrip = !modeTrip;
   }
}

/*
* reset (current) trip meter only when trip button is long pressed
* odometer needs to be unchangeable
*/
void buttonTripLongPressed() {

  if (modeTrip == MODE_TRIPMETER_1)
   {
    totalTrip_1 = 0.0;
   }
  if (modeTrip == MODE_TRIPMETER_2)
   {
    totalTrip_2 = 0.0;
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

  byte tempMode = EEPROM.readByte(eepromModeFuncAddress);
  
  calibrateCounter = 0;

  detachInterrupt(speedoInterrupt);

// clear the odo display
  odoSerial.write(254);
  odoSerial.write(128);

  odoSerial.write("                ");
  odoSerial.write("                ");

// show message on display to start and distance to drive
  odoSerial.print("press mode      ");

  if (tempMode == FUNC_KPH)
   {
    odoSerial.print("drive 2 km      ");
   }
  else
   {
    odoSerial.print("drive 2 m       ");
   }
   
// wait for button press
  do
   {
    delay(100);
   }
  while (digitalRead(pinModeButton));

  attachInterrupt(speedoInterrupt, countCalibrate, FALLING);

// show message start driving and press button at end
  odoSerial.print("start driving   ");
  odoSerial.print("press mode @ end");

  delay(1000);
  do
   {
// update the calibrate counter display;
    odoSerial.print("                ");
    sprintf(buffer, "%12d", calibrateCounter);
    odoSerial.print(buffer);
   }
  while (digitalRead(pinModeButton));

// save calibrate data to eeprom{
  EEPROM.writeFloat(eepromSpeedoCalibrateAddress, float(calibrateCounter/2));

  detachInterrupt(speedoInterrupt);

  attachInterrupt(speedoInterrupt, sensorTriggered_2, FALLING);
  
  // return to default mode
  modeFunc = tempMode;
  setupOdometerDisplay();
}



/* RKS
*
* toggle between functions when mode button is pressed
* this cycles between KPH, MPH and CAL if others are added then change FUNC_CAL to FUNC_
*
*/
void buttonModePressed() {

  modeFunc++;
  if (modeFunc > FUNC_CAL)
   {
    modeFunc = FUNC_KPH;
   }

}

/*
* enter calibration mode when mode button is long pressed
* TODO write calibration function for speedo and tacho
*/

void buttonModeLongPressed() {
  if ((rps < 0.0001) && (modeFunc == FUNC_CAL))                              // only enter calibration if stationary and already selected calibrate
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
  
// write the modeFunc to EEPROM
  EEPROM.writeByte(eepromModeFuncAddress, modeFunc);


}

