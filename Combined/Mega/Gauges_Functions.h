/*
* mode button pressed
*/
void buttonGaugesModePressed(Button& buttonGaugesMode)
 {
#ifdef DEBUGGING
  Serial.println();
  Serial.print("Gauges mode button pressed");
  Serial.println();
#endif

  buttonGaugesModeLongPress = false;
 }

/*
* mode button pressed
*/
void buttonGaugesModeReleased(Button& buttonGaugesMode)
 {
#ifdef DEBUGGING
  Serial.println();
  Serial.print("Gauges mode button released");
  Serial.println();
#endif

  buttonGaugesModeLongPress = false;
 }

/*
* mode button long pressed
*/
void buttonGaugesModeLongPressed(Button& buttonGaugesMode)
 {
#ifdef DEBUGGING
  Serial.println();
  Serial.print("Gauges mode button long pressed");
  Serial.println();
#endif


  buttonGaugesModeLongPress = true;
 }


