//Display_Functions.h

/*
 * Displays current rpm on 4 DIGIT LED
 * TODO display on 15 led 1/4 neo ring
 */

void displayRpm (int rpm) {

  char buffer[6];
  byte pixels = rpm / 1000;                             // needs to be a function of max tacho reading
  byte redLine = tachoRedline / 1000;

  if (rpm > 9999)
   {
    rpm /= 100;
    sprintf(buffer, "%3d-", rpm);		// always display last digit as 0 stops jitter
   }
  else
   {
    sprintf(buffer, "%4d", int(rpm/10)*10);		// always display last digit as 0 stops jitter
   }
  tachoSerial.print(buffer);

#ifdef ECHO_SERIAL
  Serial.print("RPM      ");
  Serial.println(buffer);
  Serial.print("redLine  ");
  Serial.println(redLine);
#endif


  for(byte i=0;i<pixels;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    tachoPixels.setPixelColor(i, tachoPixels.Color(0,0,20)); // blue color.
    if (i >= redLine)
     {
      tachoPixels.setPixelColor(i, tachoPixels.Color(20,0,0)); // red color.
     }
   }
  for(byte i=pixels;i<=numTachoLeds;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    tachoPixels.setPixelColor(i, tachoPixels.Color(0,0,0)); // blank the pixel
   }

  tachoPixels.show(); // This sends the updated pixel color to the hardware.




}

/*
 *  Setup the tacho display
 *  
 */

void setupTachoDisplay() {
  
}
