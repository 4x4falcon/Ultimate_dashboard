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

  if (debugTacho == 1 )
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

      if (debugAll > 0)
       {
        Serial.print(F("durationTacho     "));
        Serial.println(durationTacho);
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
* mode button pressed
*/
void buttonTachoModePressed() {
}

/*
* mode button long pressed
*/
void buttonTachoModeLongPressed() {

}


