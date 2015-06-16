//Display_Functions.h


/*
 * Sets the display brightness depending on if the headlights are on
 *
 */

void setBrightness() {

   byte b = 12 * brightnessBoost;
   pixelBrightness = brightnessBoost;
   if (digitalRead(pinLightsOn))
    {
#ifdef ECHO_SERIAL
      Serial.println("Lights off");
#endif
     b = 51 * brightnessBoost;
     pixelBrightness = 3 * brightnessBoost;
    }

    tachoSerial.write(0x7A);
    tachoSerial.write(b);


/*
  if (!digitalRead(pinLightsOn))
   {
    pixelBrightness = 4;        // this sets up the brightness used in displayRpm routine
                                 // for the 7 segment display set it here as it will remain that way until changed
    tachoSerial.write(0x7A);
    tachoSerial.write(byte(80));
   }
  else
   {
    pixelBrightness = 12;
    tachoSerial.write(0x7A);
    tachoSerial.write(byte(255));
#ifdef ECHO_SERIAL
    Serial.println("Lights on");
#endif
   }
*/
}

/*
 * Displays current rpm on 4 DIGIT LED
 * TODO display on 15 led 1/4 neo ring
 */

void displayRpm (int rpm) {

  char buffer[6];
  byte pixels = rpm / tachoStep;                 // needs to be a function of max tacho reading
  byte redLine = tachoRedline / tachoStep;

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
  Serial.print("pixels     ");
  Serial.println(pixels);
  Serial.print("tachoStep   ");
  Serial.println(tachoStep);
#endif

  for(byte i=0;i<pixels;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    tachoPixels.setPixelColor(i, tachoPixels.Color(0,0,pixelBrightness)); // blue color.
    if (i >= redLine)
     {
      tachoPixels.setPixelColor(i, tachoPixels.Color(pixelBrightness*20,0,0)); // red color with blue due to blue perspex.
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


void buttonBrightnessPressed() {

  brightnessBoost++;
  if (brightnessBoost > 5)
   {
    brightnessBoost = 1;
   }
  
  Serial.println("Brightnes button pressed");
  
}

void buttonBrightnessLongPressed() {

  brightnessBoost = 5;

  Serial.println("Brightness button long pressed");

}


