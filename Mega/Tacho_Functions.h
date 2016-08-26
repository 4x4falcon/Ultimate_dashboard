// Tacho_Functions.h
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
* mode button pressed
*/
void buttonTachoModePressed() {
}

/*
* mode button long pressed
*/
void buttonTachoModeLongPressed() {

}


