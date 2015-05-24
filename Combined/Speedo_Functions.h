// Speedo Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the wheel has stopped spinning.
*/
void checkForTimeout() {
  if (loopTime - lastVssTrigger > timeoutValue) {
    rps = 0.0;
  }
}

/*
* Writes total miles to EEPROM
* only if it's been longer than write frequency and moving and totalMiles is greater than what is currently stored
* this helps protect EEPROM from excessive writes
*/
void writeOdometer() {

  if (loopTime - lastOdometerWrite > odometerWriteFrequency)
   {
    if (rps != 0.0)
     {
      if (totalOdometer > EEPROM.readFloat(eepromOdoAddress))
       {
        EEPROM.writeFloat(eepromOdoAddress, totalOdometer);
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
  EEPROM.writeFloat(eepromTrip1Address,totalTrip_1);
  EEPROM.writeFloat(eepromTrip2Address,totalTrip_2);
}


/*
* ISR attached to the vehicle speed sensor, triggered on every pulse from vss
*/
void sensorTriggered() {
  if (modeFunc != FUNC_CAL)
   {
    if (millis() > lastVssTrigger)				// check to see if millis() has rolled over occurs approximately every 50 days.
     {
      unsigned long duration = millis() - lastVssTrigger;
      if (duration > 0)
       {
        rps = 1000.0 / duration;				// Update pulses per second

        totalOdometer += pulseDistance;			// Increment odometer
        totalTrip_1 += pulseDistance;                     // Increment tripmeter 1
        totalTrip_2 += pulseDistance;                     // Increment tripmeter 2
       }
     }
   }
  else
   {
    calibrateCounter++;
   }
  lastVssTrigger = millis();
}


/*
* ISR attached to the tachometer
*/
void tachoTriggered() {
  unsigned long duration = millis() - lastTachoTrigger;
  rpm = 60000/duration;
}


/*
* Updates the speedo, odometer and tachometer screen depending on the current mode
*
*/
void updateDisplay() {

// no tacho interrupts while updating. VSS interrupt must continue otherwise we miss odo reading
  detachInterrupt(1);

  int speed = (int)((rps * pulseDistance) * 3600.0);
  displaySpeed(speed);

//update odometer
  displayOdometer();

//update tripmeters
  displayTripmeter();

//update tachometer
  displayTachometer();

//restart the tacho interrupts
  attachInterrupt(1, tachoTriggered, RISING);
}

/*
 * update the volt, oil pressure, water temp and fuel level meters
 *
 */

void updateMeters() {
// no tacho interrupts while updating.  VSS interrupt must continue otherwise we miss odo reading
  detachInterrupt(1);
  int val;

// Voltmeter
// TODO setup calibration this should be fixed as no need to recalibrate depending on vehicle
  val = analogRead(pinVoltAnalog);
  val = voltMax * (val / (voltUpper - voltLower));
  displayMeter(voltSerial, val);

// Oil pressure
// TODO setup calibration
  val = analogRead(pinVoltAnalog);
  displayMeter(voltSerial, val);

// Water Temperature
// TODO setup calibration
  val = analogRead(pinVoltAnalog);
  displayMeter(voltSerial, val);

// Fuel Level
// TODO setup calibration
  val = analogRead(pinVoltAnalog);
  displayMeter(voltSerial, val);


//restart the tacho interrupts
  attachInterrupt(1, tachoTriggered, RISING);
 }



/*
* toggle between tripmeter_1 and tripmeter_2 when not in calibrate mode
*/
void buttonTripPressed() {
  if (modeFunc != FUNC_CAL)
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
      storeCalibrateSpeed();
      startCalibrateSpeed = !startCalibrateSpeed;
      modeFunc = EEPROM.readByte(eepromModeFuncAddress);
     }
   }
}

/*
* RKS reset (current) trip meter only when trip button is long pressed
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
void buttonModePressed() {
  if (modeFunc != FUNC_CAL)
   {
    modeFunc = !modeFunc;
    EEPROM.writeByte(eepromModeFuncAddress, modeFunc);
   }
  else
   {
    modeCalibrate++;
    if (modeCalibrate > FUNC_CAL_FUEL)
     {
      modeCalibrate = FUNC_CAL_SPD;
     }
    updateCalibrateDisplay();

   }
}

/*
* enter calibration mode when mode button is long pressed
* TODO write calibration function for speedo and tacho
*/

void buttonModeLongPressed() {
  if ((rps < 0.0001) && (rpm < 10))              // only enter calibration if stationary and engine off
   {
    byte tempMode = modeFunc;                    // so can restore to original function mode
    modeCalibrate = FUNC_CAL_SPD;
    if (modeFunc == FUNC_CAL)
     {
      doCalibrate();
     }

  // last must be to return to previous mode
    modeFunc = tempMode;
   }
}




/*
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
    EEPROM.writeFloat(eepromOdoAddress, totalOdometer);
   }

// write the tripmeters to EEPROM
  writeTripmeter();
  
// write the modeFunc to EEPROM
  EEPROM.writeByte(eepromModeFuncAddress, modeFunc);


}

