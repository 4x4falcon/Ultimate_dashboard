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


