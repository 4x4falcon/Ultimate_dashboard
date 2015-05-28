//Display_Functions.h

/*
 * Displays current speed on 4 DIGIT LED
 * TODO display on 15 led 1/4 neo ring
 */

void displaySpeed (int speed) {

  char buffer[6];

  sprintf(buffer, "%4d", speed);

  speedoSerial.write(buffer);

#ifdef ECHO_SERIAL

  Serial.print ("Speed    ");
  Serial.println (speed);
  Serial.print ("Speed buffer    ");
  Serial.println(buffer);
#endif

}


/*
 * Sets KPH,MPH and CAL display
 * Displays current odometer distance at eighth character of top row of 16x2 white on black LCD
 *
 */

void displayOdometer () {

  odoSerial.write(254);
  odoSerial.write(128);

  if (modeFunc == FUNC_KPH)
   {
    odoSerial.write("KPH");
   }
  else if (modeFunc == FUNC_MPH)
   {
    odoSerial.write("MPH");
   }
  else if (modeFunc == FUNC_CAL)
   {
    odoSerial.write("CAL");
   }

// cursor to eighth character of top line

  odoSerial.write(254);
  odoSerial.write(135);

  char buffer[9];

  dtostrf(totalOdometer,9,1,buffer);
  odoSerial.write(buffer);

#ifdef ECHO_SERIAL

  Serial.print ("Odo    ");
  Serial.println (buffer);

#endif



}


/*
 * Displays tripmeter 1 at third digit of lower row of 16x2 white on black LCD
 * Displays tripmeter 2 at twelth digit of lower row of 16x2 white on black LCD
 *
 */

void displayTripmeter () {

  char buffer[6];

// cursor to third character of bottom line

  odoSerial.write(254);
  odoSerial.write(194);

  dtostrf(totalTrip_1,5,1,buffer);
  odoSerial.write(buffer);

#ifdef ECHO_SERIAL

  Serial.print ("Trip_1    ");
  Serial.println (buffer);

#endif

// cursor to twelth character of bottom line

  odoSerial.write(254);
  odoSerial.write(203);

  dtostrf(totalTrip_2,5,1,buffer);
  odoSerial.write(buffer);

#ifdef ECHO_SERIAL

  Serial.print ("Trip_2    ");
  Serial.println (buffer);

#endif


}


/*
 * Displays count on first row of 16x2 LCD
 *
 */

void displayCalibrateCount (int count) {
						// TODO need function to show calibrate count



}


/*
 * setup the odometer Display
 *
 */


void setupOdometerDisplay() {

  odoSerial.begin(9600);
  delay(500);

// top line shows current function mode setting (KPH, MPH or CAL)
// cursor to the first character of the top line

  odoSerial.write(254);
  odoSerial.write(128);

  odoSerial.write("KPH    0000000.0");

// display current Odometer reading  
  displayOdometer();

// bottom line shows tripmeters with current one highlighted
// cursor to first character of bottom line

  odoSerial.write(254);
  odoSerial.write(192);
  
  odoSerial.write("1 000.0  2 000.0");

  displayTripmeter();

}



