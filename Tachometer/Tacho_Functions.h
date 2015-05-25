// Tacho Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the engine has stopped.
*/
void checkForTimeout() {
  if (loopTime - lastTachoTrigger > timeoutValue) {
    rpm = 0.0;
  }
}


/*
* ISR attached to the vehicle speed sensor, triggered on every pulse from vss
*/
void sensorTriggered() {
  if (millis() > lastTachoTrigger)				// check to see if millis() has rolled over occurs approximately every 50 days.
   {
    unsigned long duration = millis() - lastTachoTrigger;
    if (duration > 0)
     {
     }
   }
  lastTachoTrigger = millis();
}


/*
* Updates the speedo, odometer and tachometer screen depending on the current mode
*
*/
void updateDisplay() {

  int rpm = 1101;

  displayRpm(rpm);

}


/*
* mode button pressed
*/
void buttonModePressed() {
}

/*
* mode button long pressed
*/
void buttonModeLongPressed() {

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
  

}

