//Display_Functions.h


/*
 * Sets the display brightness depending on if the headlights are on
 *
 */

void setBrightness() {


   byte b = brightnessBoost;

   if (digitalRead(pinLightsOn))
    {
     b = 2 * brightnessBoost;
     pixelBrightness = brightnessBoost;
     if (debug == 1)
      {
       Serial.print(F("Lights on  "));
       Serial.println(b);
      }
    }
   else
    {
     b= 15 * brightnessBoost;
     pixelBrightness = 3 * brightnessBoost;
     if (debug == 1)
      {
       Serial.print(F("Lights off  "));
       Serial.println(b);
      }
    }

    tachoSerial.write(0x7A);
    tachoSerial.write(b);

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

  if (debug == 1)
   {
    Serial.print(F("RPM      "));
    Serial.println(buffer);
    Serial.print(F("redLine  "));
    Serial.println(redLine);
    Serial.print(F("pixels     "));
    Serial.println(pixels);
    Serial.print(F("tachoStep   "));
    Serial.println(tachoStep);
   }

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


