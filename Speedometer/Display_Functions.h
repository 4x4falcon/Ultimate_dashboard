//Display_Functions.h

/*
 * Displays current speed on 3 DIGIT LED and 15 led neo ring
 *
 */

displaySpeed (int speed) {

						// TODO need function to show speed


}

/*
 * Displays current odometer distance on top row of 16x2 white on black LCD
 *
 */

displayOdometer (float distance) {

						// TODO need function to show odometer

}


/*
 * Displays tripmeter 1 on first (left most) four lower row digits of 16x2 white on black LCD
 * Displays tripmeter 2 on last (right most) four lower row digits of 16x2 white on black LCD
 *
 */

displayTripmeter (int num, float distance) {

						// TODO need function to show tripmeter 1


}


/*
 * Displays count on first row of 16x2 white on black LCD
 *
 */

displayCalibrateCount (int count) {
						// TODO need function to show calibrate count



}





// Below may not be needed


/*
* Writes each digit of a number to the LED screen with decimal point
* and minimum number of digits.
*/
void displayNumber(int value, int decimalPos, int minDigits) {
/*
int divisor = pow(10, numDigits-1);
  for(int i = 0; i < numDigits; i++) {
    int digit = (value / divisor) % 10;
    if (value < divisor && i < numDigits-minDigits) {
      alpha.writeDigitRaw(i, segmentValues[BLANK]);
    }
    else {
      uint16_t segments = segmentValues[digit];
      if (decimalPos > 0 && i == decimalPos) {
        segments |= segmentValues[DECIMAL];
      }
      alpha.writeDigitRaw(i, segments);
    }
    divisor /= 10;
  }
  alpha.writeDisplay();
*/
}

/*
* Converts a floating point number to an integer for display on the LED screen
*/
int floatToInt(float value, int decimalPlaces) {
  int shift = pow(10, decimalPlaces);
  int whole = (int)value;
  int fraction = (value - (float)whole) * shift;
  return (whole * shift) + fraction;
}


