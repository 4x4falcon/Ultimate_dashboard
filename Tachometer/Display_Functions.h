//Display_Functions.h

/*
 * Displays current rpm on 4 DIGIT LED
 * TODO display on 15 led 1/4 neo ring
 */

void displayRpm (int rpm) {

  char tempstring[6];

  sprintf(tempstring, "%4d", int(rpm/10)*10);		// always display last digit as 0 stops jitter

  tachoSerial.write(tempstring);

}

/*
 *  Setup the tacho display
 *  
 */

void setupTachoDisplay() {
  
}
