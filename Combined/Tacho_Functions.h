// Tacho Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the engine has stopped.
*/
void checkForTachoTimeout() {
  if ((loopTime - lastTrigger) > timeoutValue) {
    rpm = 0;
  }

#ifdef ECHO_SERIAL_1

  Serial.print("loopTime    ");
  Serial.print(loopTime);
  
  Serial.print("    lastTachoTrigger    ");
  Serial.println(lastTachoTrigger);

#endif

}

/*
* ISR attached to the vehicle tachometer for petrol engines
* this is attached to the w or s terminal of the altenator on diesel engines
* triggered on every pulse
*/

void tachoTriggered() {

  lastTrigger = millis();
  if (lastTrigger > lastTachoTrigger)
   {
    pulseCount++;
    if (pulseCount == pulseMaxCount)
     {
       pulseCount = 0UL;
       durationTacho = millis() - lastTachoTrigger;
       doTacho = !doTacho;
       lastTachoTrigger = millis();

#ifdef ECHO_SERIAL_1
       Serial.print("durationTacho     ");
       Serial.println(durationTacho);
       Serial.print("lastTachoTrigger    ");
       Serial.println(lastTachoTrigger);
#endif

     }
   }

  // blink the led on pin 13 for debugging purposes

  arduinoLed = !arduinoLed;
  digitalWrite(13, arduinoLed);

}





/*
* Updates the tachometer screen depending on the current mode
*
*/
/*
void updateTachoDisplay() {

  if (doTacho)
   {
    doTacho = !doTacho;
    rpm = 1101;

//    rpm = (pps * 60) / tachoPPR;

    float v1 = (float(durationTacho) / float(pulseMaxCount));

    rpm = int( ((1000.0 / v1) * 60) / tachoPPR );

#ifdef ECHO_SERIAL

    Serial.print("v1      ");
    Serial.println(v1);

    Serial.print("rpm     ");
    Serial.println(rpm);

#endif

//    setBrightness();
    displayRpm(rpm);
   }
}
*/

/*
* mode button pressed
*/
void buttonTachoModePressed() {
}

/*
* mode button long pressed
*/
void buttonTachoModeLongPressed() {

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
  

}
*/

