// Display.h

// Set the display brightness

void setBrightness()
 {
  byte b = brightnessBoost;
  byte b1 = brightnessBoost;
  byte b2 = brightnessBoost;
  pixelBrightness = brightnessBoost;

  if (digitalRead(pinLightsOn))      // confirm that this is low when completing circuit
   {
// set brightness to mid range when headlights are on
    b = 2 * brightnessBoost;
    b1 = 2 * brightnessBoost;
    b2 = int(0.5 * brightnessBoost);
    pixelBrightness = int(0.5 * brightnessBoost);

    if (debugAll > 0)
     {
      Serial.println(F("Lights on"));
     }
   }
  else
   {
// set brightness to full on when headlights are off
    b= 15 * brightnessBoost;
    b1 = 15 * brightnessBoost;
    b2 = int(0.9 * brightnessBoost);
    pixelBrightness = int(1.5 * brightnessBoost);

    if (debugAll > 0)
     {
      Serial.println(F("Lights off"));
     }
   }
// set brightness on 7 segment displays via I2C

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_VOLT, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_OIL, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_TEMP, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_FUEL, b);

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_TACHO, b);

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_SPEEDO, b2);

// set brightness on 1602 lcd displays via I2C

//  i2c_serlcd_SetDisplayBrightness(I2C_ADDRESS_ODO, b1);

}


/*
 * Displays current speed on 4 DIGIT LED
 * TODO display on 15 led 1/4 neo ring
 */

void displaySpeed (int speed) {

//  char buffer[10];

  sprintf(buffer, "%4d", speed);

// TODO send current speed to 7 segment display via I2C

  i2c_SendString_4(I2C_ADDRESS_SPEEDO, buffer);

  if (debugSpeedo > 0)
   {
    Serial.print(F("Speed    "));
    Serial.println (speed);
    Serial.print(F("Speed buffer    "));
    Serial.println(buffer);
   }

  byte pixels = speed / 10;

  for(byte i=0;i<pixels;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    speedoPixels.setPixelColor(i, speedoPixels.Color(0,0,pixelBrightness)); // blue color.
    if (i >= 11)
     {
      speedoPixels.setPixelColor(i, speedoPixels.Color(pixelBrightness * 50,0,0)); // red color.
     }
   }
  for(byte i=pixels;i<=numSpeedoLeds;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    speedoPixels.setPixelColor(i, speedoPixels.Color(0,0,0)); // blank the pixel
   }

  speedoPixels.show(); // This sends the updated pixel color to the hardware.

}

// SPEEDO display
void updateSpeedoDisplay() {
  if ((doSpeed) || (speed == 0))
   {
    doSpeed = !doSpeed;

    if (debugSpeedo > 0)
     {
      Serial.print(F("durationSpeedo   "));
      Serial.println(durationSpeedo);
      Serial.print(F("pulseMaxCount   "));
      Serial.println(pulseMaxCount);
      Serial.print(F("pulseDistance   "));
      Serial.println(pulseDistance);
     }

    speed = int(((((1000.0 * float(pulseMaxCount)) / float(durationSpeedo)) * pulseDistance) * 3600.0) / 1000.0);
    displaySpeed(speed);

// toggle pin 13 led for  debugging
    arduinoLed = !arduinoLed;
    digitalWrite(13, arduinoLed);

   }
}


// TACHO display
void displayTachoPixels (int rpm)
 {
  byte pixels = byte (rpm / tachoStep)  + tachoPixelOffset;                 // needs to be a function of max tacho reading
  byte redLine = byte (tachoRedline / tachoStep) + tachoPixelOffset;

  for(byte i=tachoPixelOffset;i<pixels;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    tachoPixels.setPixelColor(i, tachoPixels.Color(0,0,pixelBrightness)); // blue color.
    if (i >= redLine)
     {
      tachoPixels.setPixelColor(i, tachoPixels.Color(pixelBrightness*2,0,0)); // red color with blue due to blue perspex.
     }
   }
  for(byte i=pixels;i<=(numTachoLeds + tachoPixelOffset);i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    tachoPixels.setPixelColor(i, tachoPixels.Color(0,0,0)); // blank the pixel
   }

/*
  byte pixels = byte (rpm / tachoStep);                 // needs to be a function of max tacho reading
  byte redLine = byte (tachoRedline / tachoStep);

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
*/

  tachoPixels.show(); // This sends the updated pixel color to the hardware.
  if (debugTacho == 5)
   {
    Serial.print(F("redLine  "));
    Serial.println(redLine);
    Serial.print(F("pixels     "));
    Serial.println(pixels);
   }
 }



void updateTachoDisplay() {

  if ((doTacho) || (rpm == 0))
   {
    doTacho = !doTacho;
    rpm = 1101;

//    rpm = (pps * 60) / tachoPPR;

    float v1 = (float(durationTacho) / float(pulseMaxCount));

    rpm = int( ((1000.0 / v1) * 60) / tachoPPR );

    if (debugTacho == 1)
     {
      Serial.print(F("v1      "));
      Serial.println(v1);

      Serial.print(F("rpm     "));
      Serial.println(rpm);
     }


    if (rpm > 9999)
     {
      rpm /= 100;
      sprintf(buffer, "%3d-", rpm);		            // always display last digit as 0 stops jitter
     }
    else
     {
      sprintf(buffer, "%4d", int(rpm/10)*10);		  // always display last digit as 0 stops jitter
     }

    i2c_SendString_4(I2C_ADDRESS_TACHO, buffer);

    displayTachoPixels (rpm);

    if (debugTacho == 1)
     {
      Serial.print(F("RPM      "));
      Serial.println(buffer);
      Serial.print(F("tachoStep   "));
      Serial.println(tachoStep);
     }
   }
}


/*
 * Sets KPH,MPH and CAL display
 * Displays current odometer distance at eighth character of top row of 16x2 white on black LCD
 *
 */

void displayOdometer () {

  char buffer[17] = "";

// TODO via I2C

//  odoSerial.write(254);    // cursor to the first character of top row
//  odoSerial.write(128);

  if (modeSpeedoFunc == FUNC_KPH)
   {
// TODO via I2C

//    odoSerial.print(F("KPH"));
   }
  else if (modeSpeedoFunc == FUNC_MPH)
   {
// TODO via I2C

//    odoSerial.print(F("MPH"));
   }
  else if (modeSpeedoFunc == FUNC_CAL)
   {
// TODO via I2C

//    odoSerial.print(F("CAL"));
   }



// cursor to eighth character of top line
// TODO via I2C

//  odoSerial.write(254);
//  odoSerial.write(135);

  float odo = (totalOdometer * pulseDistance) / 1000.0;

  if (odo > 999999.9)
   {
     odo = 0.0;
     totalOdometer = 0;
   }


  dtostrf(odo,9,1,buffer);

// TODO via I2C

//  odoSerial.print(buffer);

  if (debugSpeedo > 0)
   {
    Serial.print(F("Odo    "));
    Serial.println (buffer);
   }
}

/*
 * Displays tripmeter 1 at third digit of lower row of 16x2 white on black LCD
 * Displays tripmeter 2 at twelth digit of lower row of 16x2 white on black LCD
 *
 */

void displayTripmeter () {

  char buffer[6] = "";

// cursor to the first character of bottom line

//  odoSerial.write(254);
//  odoSerial.write(192);

//  odoSerial.print(F("1        2      "));

// cursor to third character of bottom line

// TODO via I2C

//  odoSerial.write(254);
//  odoSerial.write(194);

  float odo = (totalTrip_1 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_1 = 0;
   }

  dtostrf(odo,5,1,buffer);
// TODO via I2C

//  odoSerial.print(buffer);

  if (debugSpeedo > 0)
   {
    Serial.print(F("Trip_1    "));
    Serial.println (buffer);
   }

// cursor to twelth character of bottom line

// TODO via I2C

//  odoSerial.write(254);
// TODO via I2C

//  odoSerial.write(203);

  odo = (totalTrip_2 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_2 = 0;
   }


  dtostrf(odo,5,1,buffer);
// TODO via I2C

//  odoSerial.print(buffer);

  if (debugSpeedo > 0)
   {
    Serial.print(F("Trip_2    "));
    Serial.println (buffer);
   }

  if (!modeTrip)
   {
// TODO via I2C

//    odoSerial.write(254);
//    odoSerial.write(193);        // second character of bottom row
//    odoSerial.print(tripActive);
//    odoSerial.write(254);
//    odoSerial.write(202);        // eleventh character of bottom row
//    odoSerial.print(F(" "));
   }
  else
   {
// TODO via I2C

//    odoSerial.write(254);
//    odoSerial.write(193);        // second character of bottom row
//    odoSerial.print(F(" "));
//    odoSerial.write(254);
//    odoSerial.write(202);        // eleventh character of bottom row
//    odoSerial.print(tripActive);
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
 * setup the tacho display
 */

void setupTachoDisplay()
 {
  i2c_s7s_ClearDisplay(I2C_ADDRESS_TACHO);
  i2c_SendString_4(I2C_ADDRESS_TACHO, "TACH");
 }


/*
 * setup the odometer Display
 *
 */


void setupOdometerDisplay() {

// top line shows current function mode setting (KPH, MPH or CAL)
// cursor to the first character of the top line

// TODO via I2C

//  odoSerial.write(254);
//  odoSerial.write(128);

//  odoSerial.write("KPH    0000000.0"));

// display current Odometer reading  
  displayOdometer();

// bottom line shows tripmeters with current one highlighted
// cursor to first character of bottom line

// TODO via I2C

//  odoSerial.write(254);
//  odoSerial.write(192);
  
//  odoSerial.write("1 000.0  2 000.0"));

  displayTripmeter();

}



void setupMetersDisplay() {

  i2c_s7s_ClearDisplay(I2C_ADDRESS_VOLT);
  i2c_SendString_4(I2C_ADDRESS_VOLT, "UOLT");
  i2c_s7s_SendDecimalControl(I2C_ADDRESS_VOLT, S7S_DIGIT_3_POINT);

  i2c_s7s_ClearDisplay(I2C_ADDRESS_OIL);
  i2c_SendString_4(I2C_ADDRESS_OIL, "OIL ");
  i2c_s7s_SendDecimalControl(I2C_ADDRESS_OIL, S7S_DIGIT_3_POINT);

  i2c_s7s_ClearDisplay(I2C_ADDRESS_TEMP);
  i2c_SendString_4(I2C_ADDRESS_TEMP, "TENP");
  i2c_s7s_SendDecimalControl(I2C_ADDRESS_TEMP, S7S_DIGIT_3_POINT);

  i2c_s7s_ClearDisplay(I2C_ADDRESS_FUEL);
  i2c_SendString_4(I2C_ADDRESS_FUEL, "FUEL");
  i2c_s7s_SendDecimalControl(I2C_ADDRESS_FUEL, S7S_DIGIT_3_POINT);

}



void updateMetersDisplay() {
  // GAUGES display

  float v = 0.0;
  float v2 = 0.0;

  if (debugGauges > 0)
   {
    Serial.println(F("Updating display voltmeter, oil pressure gauge, water temperature gauge, fuel level gauge"));
   }

#define SAMPLES 3

// voltmeter
// does not need maximum/minimum values as is based on voltage divider
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(voltAnalogPin);
  val /= SAMPLES;

  v = (val * 5.0) / (voltUpper - voltLower);
//  v2 = v / (r2 / (r1 + r2));        // TODO uncomment this and change below to v2 when hardware complete

  voltVal = int(v * 10);
//  voltVal = int(v);

  sprintf(buffer, "%4d", voltVal);  // setup as integer

  if (debugGauges > 0)
   {
    Serial.println(buffer);
   }


// write the value to the display
  i2c_SendString_4(I2C_ADDRESS_VOLT, buffer);

// check for voltage warning
  if (voltWarnLow)
   {
    
   }
  else
   {
    
   }

// oil pressure meter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(oilAnalogPin);
  val /= SAMPLES;

  v = (val * 5.0) / 1024;
//  v2 = v / (r2 / (r1 + r2));
  if (debugGauges > 0)
   {
    dtostrf(v2, 4, 1, buffer);
    Serial.println(buffer);
   }
  oilVal = int(v * 10);        // setup as integer
  sprintf(buffer, "%4d", oilVal);

// write the value to the display
  i2c_SendString_4(I2C_ADDRESS_OIL, buffer);

// check for voltage warning
  if (oilWarnLow)
   {
    
   }
  else
   {
    
   }
  
// water temperature meter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(tempAnalogPin);
  val /= SAMPLES;

  v = (val * 5.0) / 1024;
//  v2 = v / (r2 / (r1 + r2));
  if (debugGauges > 0)
   {
    dtostrf(v2, 4, 1, buffer);
    Serial.println(buffer);
   }

  tempVal = int(v * 10);            // setup as integer

  sprintf(buffer, "%4d", tempVal);

// write the value to the display
  i2c_SendString_4(I2C_ADDRESS_TEMP, buffer);
  
// check for voltage warning
  if (tempWarnLow)
   {
    
   }
  else
   {
    
   }

// fuel level meter display
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(fuelAnalogPin);
  val /= SAMPLES;

  v = (val * 5.0) / 1024;
//  v2 = v / (r2 / (r1 + r2));

  if (debugGauges > 0)
   {
    dtostrf(v2, 4, 1, buffer);
    Serial.println(buffer);
   }

  fuelVal = int(v * 10);             // setup as integer
  sprintf(buffer, "%4d", fuelVal);

// write the value to the display
  i2c_SendString_4(I2C_ADDRESS_FUEL, buffer);

// check for voltage warning
  if (fuelWarnLow)
   {
    
   }
  else
   {
    
   }
  
}




void updateDisplay() {
  setBrightness();

  updateTachoDisplay();

  //update odometer
  displayOdometer();

//update tripmeters
  displayTripmeter();

  updateMetersDisplay();
}


