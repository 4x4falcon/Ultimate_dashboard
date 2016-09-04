// Tacho Functions

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the engine has stopped.
*/
void checkForTimeout()
 {
  if ((loopTime - lastTrigger) > timeoutValue)
   {
    rpm = 0;
    displayRpm(rpm);
   }

  if (debug == 2)
   {

    Serial.print(F("loopTime    "));
    Serial.print(loopTime);
  
    Serial.print(F("    lastTachoTrigger    "));
    Serial.println(lastTachoTrigger);
   }
 }

/*
* ISR attached to the vehicle tachometer for petrol engines
* this is attached to the w or s terminal of the altenator on diesel engines
* triggered on every pulse
*/

void sensorTriggered() {

  lastTrigger = millis();
  if (lastTrigger > lastTachoTrigger)
   {
    pulseCount++;
    if (pulseCount == pulseMaxCount)
     {
       pulseCount = 0UL;
       duration = millis() - lastTachoTrigger;
       doTacho = !doTacho;
       lastTachoTrigger = millis();

     if (debug == 2)
      {
       Serial.print(F("duration     "));
       Serial.println(duration);
       Serial.print(F("lastTachoTrigger    "));
       Serial.println(lastTachoTrigger);
      }

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
void updateDisplay() {

//  if (doTacho)
   {
    doTacho = !doTacho;
    rpm = 1101;

//    rpm = (pps * 60) / tachoPPR;

    float v1 = (float(duration) / float(pulseMaxCount));

    rpm = int( ((1000.0 / v1) * 60) / tachoPPR );

     if (debug == 1)
      {
       Serial.print("v1      ");
       Serial.println(v1);

       Serial.print("rpm     ");
       Serial.println(rpm);
      }

    setBrightness();
    displayRpm(rpm);
   }
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

