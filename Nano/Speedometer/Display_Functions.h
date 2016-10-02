/*
 * Display_Functions.h
 */

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
     if (debugSpeedo == 1)
      {
       Serial.print(F("Lights on  "));
       Serial.println(b);
      }
    }
   else
    {
     b = 15 * brightnessBoost;
     b1 = 15 * brightnessBoost;
     pixelBrightness = int(1.5 * brightnessBoost);
     if (debugSpeedo == 1)
      {
       Serial.print(F("Lights off  "));
       Serial.println(b);
      }
    }

// TODO this requires hardware to be able to change the backlight brightness

  odo1602.setBacklight(125);

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_SPEEDO, b1);

 }


/*
 * Displays current speed on 4 DIGIT LED
 */

void displaySpeed (int speed) {

//  char buffer[10];

  sprintf(buffer, "%4d", speed);

//  speedoSerial.print(buffer);

  i2c_SendString_4(I2C_ADDRESS_SPEEDO, buffer);

  if (debugSpeedo == 1)
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

void displayOdometer ()
 {

#ifdef ODOMETER_1602
  odo1602.setCursor(0, 0);
  odo1602.print("KPH    0000000.0");
  if (modeSpeedoFunc == FUNC_KPH)
   {
    odo1602.print(F("KPH"));
   }
  else if (modeSpeedoFunc == FUNC_MPH)
   {
    odo1602.print(F("MPH"));
   }
  else if (modeSpeedoFunc == FUNC_CAL)
   {
    odo1602.print(F("CAL"));
   }
#endif
#ifdef ODOMETER_OLED_128X64
#endif




// cursor to eighth character of top line
#ifdef ODOMETER_1602
  odo1602.setCursor(7, 0);
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  float odo = (totalOdometer * pulseDistance) / 1000.0;

  if (odo > 999999.9)
   {
     odo = 0.0;
     totalOdometer = 0;
   }


  dtostrf(odo,9,1,buffer);

#ifdef ODOMETER_1602
  odo1602.print(buffer);
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  if (debugSpeedo == 1)
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

// cursor to third character of bottom line

#ifdef ODOMETER_1602
  odo1602.setCursor(2, 1);
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  float odo = (totalTrip_1 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_1 = 0;
   }

  dtostrf(odo,5,1,buffer);
#ifdef ODOMETER_1602
  odo1602.print(buffer);
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  if (debugSpeedo == 1)
   {
    Serial.print (F("Trip_1    "));
    Serial.println (buffer);
   }

// cursor to twelth character of bottom line
#ifdef ODOMETER_1602
  odo1602.setCursor(11, 1);
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  odo = (totalTrip_2 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_2 = 0;
   }


  dtostrf(odo,5,1,buffer);
#ifdef ODOMETER_1602
  odo1602.print(buffer);
#endif
#ifdef ODOMETER_OLED_128X64
#endif

  if (debugSpeedo == 1)
   {
    Serial.print (F("Trip_2    "));
    Serial.println (buffer);
   }

  if (!modeTrip)
   {
#ifdef ODOMETER_1602
    // second character of bottom row
    odo1602.setCursor(1, 1);
    odo1602.print(tripActive);

    // eleventh character of bottom row
    odo1602.setCursor(10, 1);
    odo1602.print(" ");
#endif
#ifdef ODOMETER_OLED_128X64
#endif
   }
  else
   {
#ifdef ODOMETER_1602
    // second character of bottom row
    odo1602.setCursor(1, 1);
    odo1602.print(tripActive);

    // eleventh character of bottom row
    odo1602.setCursor(10, 1);
    odo1602.print(" ");
#endif
#ifdef ODOMETER_OLED_128X64
#endif
   }
}



// SPEEDO display
void updateSpeedoDisplay() {
  if ( (loopTime - lastVssTrigger) > timeoutValue )
   {
    speed = 0;
   }

  if ((doSpeed) || (speed == 0))
   {
    doSpeed = !doSpeed;

    if (debugSpeedo == 10)
     {
      Serial.print(F("durationSpeedo   "));
      Serial.println(durationSpeedo);
      Serial.print(F("pulseMaxCount   "));
      Serial.println(pulseMaxCount);
      Serial.print(F("pulseDistance   "));
      Serial.println(pulseDistance);
     }

//    speed = int(((((1000.0 * float(pulseMaxCount)) / float(durationSpeedo)) * pulseDistance) * 3600.0) / 1000.0);

// This is pulses per second * distance per pulse in metres = metres per second
// * 3600 = metres per hour
// / 1000 = km per hour
// calculation is done in kph then converted in display if mph function is set
    
    if ( (loopTime - lastVssTrigger) < timeoutValue )
     {
      speed = int((((1000000.0 / (float(durationSpeedo) / float(pulseMaxCount))) * pulseDistance) * 3600.0) / 1000.0);
     }

// TODO
// This is (pulses * durationSpeedo) / speedoCalibrate = km per microsecond
// * 1000 = km per second
// * 3600 = km per hour
// calculation is done in kph then converted in display if mph function is set


    if (debugSpeedo == 11)
     {
      Serial.print(F("speed   "));
      Serial.println(speed);
     }
    displaySpeed(speed);

   }
}


/*
 * setup the speedo display
 */

void setupSpeedoDisplay()
 {
  i2c_s7s_ClearDisplay(I2C_ADDRESS_SPEEDO);
  i2c_SendString_4(I2C_ADDRESS_SPEEDO, "SPED");
 }



/*
 * setup the odometer Display
 *
 */


void setupOdometerDisplay()
 {

// top line shows current function mode setting (KPH, MPH or CAL)
// cursor to the first character of the top line

#ifdef ODOMETER_1602
  odo1602.setCursor(0, 0);
  odo1602.print("KPH    0000000.0");
#endif
#ifdef ODOMETER_OLED_128X64
#endif

// display current Odometer reading  
  displayOdometer();

// bottom line shows tripmeters with current one highlighted
// cursor to first character of bottom line

#ifdef ODOMETER_1602
  odo1602.setCursor(0, 1);
  odo1602.print("1 000.0  2 000.0");
#endif
#ifdef ODOMETER_OLED_128X64

#endif

  displayTripmeter();

}


void buttonBrightnessPressed() {

  brightnessBoost++;
  if (brightnessBoost > 5)
   {
    brightnessBoost = 1;
   }
  if (debugSpeedo == 1)
   {
    Serial.println(F("Brightnes button pressed"));
   }
}

void buttonBrightnessLongPressed() {

  brightnessBoost = 5;

  if (debugSpeedo == 1)
   {
    Serial.println(F("Brightness button long pressed"));
   }
}

