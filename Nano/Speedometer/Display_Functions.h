//Display_Functions.h

// set the display brightness depending on headlight state

void setBrightness()
 {
  byte b = brightnessBoost;
  byte b1 = brightnessBoost;
  pixelBrightness = brightnessBoost;

   if (digitalRead(pinLightsOn))
    {
     b = 2 * brightnessBoost;
     b1 = 2 * brightnessBoost;
     pixelBrightness = int(0.5 * brightnessBoost);
     if (debug == 1)
      {
       Serial.print(F("Lights on  "));
       Serial.println(b);
      }
    }
   else
    {
     b= 15 * brightnessBoost;
     b1 = 15 * brightnessBoost;
     pixelBrightness = int(1.5 * brightnessBoost);
     if (debug == 1)
      {
       Serial.print(F("Lights off  "));
       Serial.println(b);
      }
    }

  odoSerial.write(0x7C);
  odoSerial.write(byte(b));

  speedoSerial.write(0x7A);
  speedoSerial.write(byte(b1));
 }


void odoDisplay(byte on)
 {
  odoSerial.begin(9600);
  delay(500);

  if (!on)
   {
    odoSerial.write(0x7C);
    odoSerial.write(128);
   }
  else
   {
    setBrightness();
   }
 }




/*
 * Displays current speed on 4 DIGIT LED
 */

void displaySpeed (int speed) {

//  char buffer[10];

  sprintf(buffer, "%4d", speed);
  speedoSerial.print(buffer);

  if (debug == 1)
   {
    Serial.print (F("Speed    "));
    Serial.println (speed);
    Serial.print (F("Speed buffer    "));
    Serial.println(buffer);
   }

  byte pixels = int(speed / 10) + pixelOffset;

  for(byte i=pixelOffset;i<pixels;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    speedoPixels.setPixelColor(i, speedoPixels.Color(0,0,pixelBrightness)); // blue color.
    if (i >= (11 + pixelOffset))
     {
      speedoPixels.setPixelColor(i, speedoPixels.Color(pixelBrightness,0,0)); // red color.
     }
   }
  for(byte i=pixels;i<=(numSpeedoLeds + pixelOffset);i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    speedoPixels.setPixelColor(i, speedoPixels.Color(0,0,0)); // blank the pixel
   }

  speedoPixels.show(); // This sends the updated pixel color to the hardware.

}



/*
 * Sets KPH,MPH and CAL display
 * Displays current odometer distance at eighth character of top row of 16x2 white on black LCD
 *
 */

void displayOdometer () {

//  char buffer[17] = "";
  
  odoSerial.write(254);    // cursor to the first character of top row
  odoSerial.write(128);

  if (modeFunc == FUNC_KPH)
   {
    odoSerial.print(F("KPH"));
   }
  else if (modeFunc == FUNC_MPH)
   {
    odoSerial.print(F("MPH"));
   }
  else if (modeFunc == FUNC_CAL)
   {
    odoSerial.print(F("CAL"));
   }



// cursor to eighth character of top line
  odoSerial.write(254);
  odoSerial.write(135);

  float odo = (totalOdometer * pulseDistance) / 1000.0;

  if (odo > 999999.9)
   {
     odo = 0.0;
     totalOdometer = 0;
   }


  dtostrf(odo,9,1,buffer);

  odoSerial.print(buffer);

  if (debug == 1)
   {
    Serial.print (F("Odo    "));
    Serial.println (buffer);
   }
 }


/*
 * Displays tripmeter 1 at third digit of lower row of 16x2 white on black LCD
 * Displays tripmeter 2 at twelth digit of lower row of 16x2 white on black LCD
 *
 */

void displayTripmeter () {

//  char buffer[6] = "";

// cursor to third character of bottom line

  odoSerial.write(254);
  odoSerial.write(194);

  float odo = (totalTrip_1 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_1 = 0;
   }

  dtostrf(odo,5,1,buffer);
  odoSerial.print(buffer);

  if (debug == 1)
   {
    Serial.print (F("Trip_1    "));
    Serial.println (buffer);
   }

// cursor to twelth character of bottom line

  odoSerial.write(254);
  odoSerial.write(203);

  odo = (totalTrip_2 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_2 = 0;
   }


  dtostrf(odo,5,1,buffer);
  odoSerial.print(buffer);

  if (debug == 1)
   {
    Serial.print (F("Trip_2    "));
    Serial.println (buffer);
   }

  if (!modeTrip)
   {
    odoSerial.write(254);
    odoSerial.write(193);        // second character of bottom row
    odoSerial.print(tripActive);
    odoSerial.write(254);
    odoSerial.write(202);        // eleventh character of bottom row
    odoSerial.print(" ");
   }
  else
   {
    odoSerial.write(254);
    odoSerial.write(193);        // second character of bottom row
    odoSerial.print(" ");
    odoSerial.write(254);
    odoSerial.write(202);        // eleventh character of bottom row
    odoSerial.print(tripActive);
   }

}




/*
 * setup the odometer Display
 *
 */


void setupOdometerDisplay() {

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


void buttonBrightnessPressed() {

  brightnessBoost++;
  if (brightnessBoost > 5)
   {
    brightnessBoost = 1;
   }
  if (debug == 1)
   {
    Serial.println(F("Brightnes button pressed"));
   }
}

void buttonBrightnessLongPressed() {

  brightnessBoost = 5;

  if (debug == 1)
   {
    Serial.println(F("Brightness button long pressed"));
   }
}

