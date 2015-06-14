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
* Writes odometer total to EEPROM
* only if it's been longer than write frequency and totalOdometer is greater than what is currently stored
* maybe if vehicle is only moving to0
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
       
       Serial.print("durationSpeedo     ");
       Serial.println(durationSpeedo);
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
* toggle between tripmeter_1 and tripmeter_2 when not in calibrate mode
*/
void buttonTripPressed() {
  if (modeSpeedoFunc != FUNC_CAL)
   {
    modeTrip = !modeTrip;
   }
  else
   {
    if (!startCalibrateSpeed)
     {
      startCalibrateSpeed = !startCalibrateSpeed;
     }
    else
     {
      storeCalibrateSpeedo();
      startCalibrateSpeed = !startCalibrateSpeed;
      modeSpeedoFunc = EEPROM.readByte(eepromModeSpeedoFuncAddress);
     }
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


/* RKS
*
* toggle between functions when mode button is pressed
* this cycles between KPH, MPH and CAL if others are added then change FUNC_CAL to FUNC_
*
*/
void buttonSpeedoModePressed() {
  if (modeSpeedoFunc != FUNC_CAL)
   {
    modeSpeedoFunc = !modeSpeedoFunc;
#ifdef ECHO_SERIAL
    Serial.print("Saving modeSpeedoFunc to EEPROM     ");
    Serial.println(modeSpeedoFunc);
#else
    EEPROM.writeByte(eepromModeSpeedoFuncAddress, modeSpeedoFunc);
#endif
   }
  else
   {
    modeSpeedoCalibrate = FUNC_CAL_SPD;
    updateCalibrateDisplay();
   }
}

/*
* enter calibration mode when mode button is long pressed
* TODO write calibration function for speedo and tacho
*/

void buttonSpeedoModeLongPressed() {
  if (rps < 0.0001)                              // only enter calibration if stationary
   {
    byte tempMode = modeSpeedoFunc;                    // so can restore to original function mode
    modeSpeedoCalibrate = FUNC_CAL_SPD;
    doCalibrate();

  // last must be to return to previous mode
    modeSpeedoFunc = tempMode;
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

/*
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
  
// write the modeSpeedoFunc to EEPROM
  EEPROM.writeByte(eepromModeSpeedoFuncAddress, modeSpeedoFunc);


}
*/

