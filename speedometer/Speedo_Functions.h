// Speedo Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the wheel has stopped spinning.
*/
void checkForTimeout() {
  if (loopTime - lastTrigger > timeoutValue) {
    rps = 0.0;
  }
}

/*
* Writes total miles to EEPROM
* only if it's been longer than write frequency and moving and totalMiles is greater than what is currently stored and
*/
void writeOdometer() {

  if (loopTime - lastOdometerWrite > odometerWriteFrequency)
   {
    if (rps != 0.0)
     {
      if (totalMiles > EEPROM.readFloat(eepromOdoAddress))
       {
        EEPROM.writeFloat(eepromOdoAddress, totalMiles);
        lastOdometerWrite = loopTime;
       }
     }
   }
}


/*
* write miles to specified tripmeter
*
* tripmeters are stored in ram so are volatile to power removal
*
* as the board will be constantly powered and only go into a sleep mode when the ignition is turned to off this should not be a problem
*
*/

void writeTripmeter(int trip) {

}


/*
* Updates the screen depending on the current mode
*
* RKS this needs to be changed for two different displays as speedometer and odometer will always be displayed
* the button changes between MODE_TRIPMETER_1 and MODE_TRIPMETER_2
*
*/
void updateDisplay() {

//update speedo
float fps = wheelCircumference * rps;

int speed = (int)((fps / speedDivisor) * 3600.0);	// RKS this is feet in a mile for km needs to be 1000 metres in a km
						// TODO rewrite this to calculate speed based on calibration number of pulses per km/mile


						// TODO need function to show speed

//update odometer
						// TODO need function to show odometer

//update tripmeter 1
						// TODO need function to show tripmeter 1

//update tripmeter 2
						// TODO need function to show tripmeter 2

						// TODO add functions to update rpm, volt, oil, fuel, temp

}

/*
* RKS toggle between tripmeter_1 and tripmeter_2 
*/
void buttonTripPressed() {
  modeTrip = !modeTrip;
}

/*
* RKS reset (current) trip meter only when trip button is long pressed
* odometer needs to be unchangeable
*/
void buttonTripLongPressed() {

  if (mode == MODE_TRIPMETER_1) {
//    EEPROM.writeFloat(0, totalMiles = 0.0);
  }
  if (mode == MODE_TRIPMETER_2) {
//    EEPROM.writeFloat(10, totalMiles = 0.0);
  }
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

/* RKS
* enter calibration mode when mode button is long pressed
* TODO write calibration function
*/

void buttonModeLongPressed() {

}


/*
* Writes each digit of a number to the LED screen with decimal point
* and minimum number of digits.
*/
void displayNumber(int value, int decimalPos, int minDigits) {
  int divisor = pow(10, numDigits-1);
  for(int i = 0; i < numDigits; i++) {
    int digit = (value / divisor) % 10;
    if (value < divisor && i < numDigits-minDigits) {
      alpha.writeDigitRaw(i, segmentValues[BLANK]);
    }
    else {
      uint16_t segments = segmentValues[digit];
      if (decimalPos > 0 && i == decimalPos) {
        segments |= segmentValues[DECIMAL];
      }
      alpha.writeDigitRaw(i, segments);
    }
    divisor /= 10;
  }
  alpha.writeDisplay();
}

/*
* Converts a floating point number to an integer for display on the LED screen
*/
int floatToInt(float value, int decimalPlaces) {
  int shift = pow(10, decimalPlaces);
  int whole = (int)value;
  int fraction = (value - (float)whole) * shift;
  return (whole * shift) + fraction;
}

/*
* ISR attached to the hall effect sensor; triggered each time the magnet
* passes by the sensor
*/
void sensorTriggered() {
  unsigned long duration = millis() - lastTrigger;
  if (duration > 0) {
    rps = 1000.0 / duration;				// Update pulses per second


    totalMiles += pulseDistance;			// Increment odometer
    totalTrip_1 += pulseDistance;
    totalTrip_2 += pulseDistance;
  }
  lastTrigger = millis();
}


/*
* This is the sleep function
* It will be activated when the ignition is turned off.
* It needs to write odo and trip values to the eeprom
* Will wake up on ignition turned on
*
*/

void goToSleep() {

}


