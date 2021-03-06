/* Tacho_Functions.h
 *
 * Tacho Functions
 */

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the engine has stopped.
*/

/*
 * no longer required now in Display.h updateTachoDisplay
 * here for reference only
*/
/*
void checkForTachoTimeout()
 {
  if ((loopTime - lastTachoTrigger) > timeoutValue)
   {
    rpm = 0;
   }

#ifdef SERIAL_DEBUG
  if (debugTacho == 1 )
   {
    Serial.print(F("loopTime    "));
    Serial.print(loopTime);

    Serial.print(F("    lastTachoTrigger    "));
    Serial.println(lastTachoTrigger);

    Serial.print(F("    timeoutValue    "));
    Serial.println(timeoutValue);


    Serial.print(F("checkForTachoTimeout rpm    "));
    Serial.println(rpm);
   }
#endif

 }
*/

/*
* ISR attached to the vehicle tachometer for petrol engines
* this is attached to the w or s terminal of the altenator on diesel engines
* triggered on every pulse
*/

void tachoTriggered()
 {
  unsigned long lastTrigger = micros();
  if (lastTrigger > lastTachoTrigger)
   {
    pulseCount++;
    if (pulseCount == pulseMaxCount)
     {
      pulseCount = 0UL;
      durationTacho = micros() - lastTachoTrigger;
      doTacho = !doTacho;
      lastTachoTrigger = micros();

#ifdef SERIAL_DEBUG
      if (debugAll > 0)
       {
        Serial.print(F("durationTacho     "));
        Serial.println(durationTacho);
        Serial.print(F("lastTachoTrigger    "));
        Serial.println(lastTachoTrigger);
       }
#endif

     }
   }
 }

/*
* mode button pressed
*/
void buttonTachoModePressed(Button& buttonTachoMode)
 {
#ifdef DEBUGGING
  Serial.println();
  Serial.print("Tacho mode button pressed");
  Serial.println();
#endif

  buttonTachoModeLongPress = false;
 }

/*
* mode button pressed
*/
void buttonTachoModeReleased(Button& buttonTachoMode)
 {
#ifdef DEBUGGING
  Serial.println();
  Serial.print("Tacho mode button released");
  Serial.println();
#endif

  buttonTachoModeLongPress = false;
 }

/*
* mode button long pressed
*/
void buttonTachoModeLongPressed(Button& buttonTachoMode)
 {
#ifdef DEBUGGING
  Serial.println();
  Serial.print("Tacho mode button long pressed");
  Serial.println();
#endif


  buttonTachoModeLongPress = true;
 }


