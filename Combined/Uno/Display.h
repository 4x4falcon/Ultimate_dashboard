// Display.h

// Set the display brightness

void setBrightness()
 {
  byte b = brightnessBoost;           // tacho and gauges for 7mm opensegment
  byte b1 = brightnessBoost;          // odometer for 16x02 lcd
  byte b2 = brightnessBoost;          // speedo for 20mm opensegment
  pixelBrightness = brightnessBoost;

  if (digitalRead(pinLightsOn))      // confirm that this is low when completing circuit
   {
// set brightness to mid range when headlights are on
    b = 2 * brightnessBoost;
    b1 = 15 * brightnessBoost;
    b2 = int(0.5 * brightnessBoost);
    pixelBrightness = int(0.5 * brightnessBoost);

#ifdef ODOMETER_OLED_128x64
    oledOdometer.setContrast(0);
#endif

#ifdef INCLUDE_DEBUG
    if (debugAll > 0)
     {
      Serial.println(F("Lights on"));
     }
#endif
   
   }
  else
   {
// set brightness to full on when headlights are off
    b= 15 * brightnessBoost;
    b1 = 50 * brightnessBoost;
    b2 = int(0.9 * brightnessBoost);
    pixelBrightness = int(1.5 * brightnessBoost);

#ifdef ODOMETER_OLED_128x64
    oledOdometer.setContrast(255);
#endif
#ifdef INCLUDE_DEBUG
    if (debugAll > 0)
     {
      Serial.println(F("Lights off"));
     }
#endif
   
   }
// set brightness on 7 segment displays via I2C

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_VOLT, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_OIL, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_TEMP, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_FUEL, b);

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_TACHO, b);

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_SPEEDO, b2);

#ifdef ODOMETER_1602
  analogWrite(pinBacklight, b1);
#endif
}


/*
 * Displays current speed on 4 DIGIT LED
 */

void displaySpeed (int speed)
 {
//  if ( (speed < (previousSpeed * 1.1)) && (speed > (previousSpeed * 0.9)) )
   {
// TODO convert to mph if mode is FUNC_MPH

    sprintf(buffer, "%4d", speed);

    i2c_SendString_4(I2C_ADDRESS_SPEEDO, buffer);

#ifdef INCLUDE_DEBUG
    if (debugSpeedo == 1)
     {
      Serial.print(F("Speed    "));
      Serial.println (speed);
      Serial.print(F("Speed buffer    "));
      Serial.println(buffer);
     }
#endif

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
   previousSpeed = speed;
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

#ifdef INCLUDE_DEBUG
    if (debugSpeedo == 10)
     {
      Serial.print(F("durationSpeedo   "));
      Serial.println(durationSpeedo);
      Serial.print(F("pulseMaxCount   "));
      Serial.println(pulseMaxCount);
      Serial.print(F("pulseDistance   "));
      Serial.println(pulseDistance);
     }
#endif

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

#ifdef INCLUDE_DEBUG
    if (debugSpeedo == 11)
     {
      Serial.print(F("speed   "));
      Serial.println(speed);
     }
#endif

    displaySpeed(speed);

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

#ifdef INCLUDE_DEBUG
  if (debugTacho == 5)
   {
    Serial.print(F("redLine  "));
    Serial.println(redLine);
    Serial.print(F("pixels     "));
    Serial.println(pixels);
   }
#endif
}


void updateTachoDisplay() {

  if ((loopTime - lastTachoTrigger) > timeoutValue)
   {
    rpm = 0;
   }

  if ((doTacho) || (rpm == 0))
   {
    doTacho = !doTacho;
//    rpm = 1101;
//    rpm = (pps * 60) / tachoPPR;

    float v1 = (float(durationTacho) / float(pulseMaxCount));

    if ((loopTime - lastTachoTrigger) < timeoutValue)
     {
      rpm = int( ((1000000.0 / v1) * 60) / tachoPPR );
     }

#ifdef INCLUDE_DEBUG
    if (debugTacho == 2)
     {
      Serial.print(F("v1      "));
      Serial.println(v1);

      Serial.print(F("updateTachoDisplay rpm     "));
      Serial.println(rpm);
     }
#endif

    if (rpm > 9999)
     {
//      rpm /= 100;
      sprintf(buffer, "%3d-", int(rpm/100));		            // always display last digit as 0 stops jitter
     }
    else
     {
      sprintf(buffer, "%4d", int(rpm/10)*10);		  // always display last digit as 0 stops jitter
     }

    i2c_SendString_4(I2C_ADDRESS_TACHO, buffer);

    displayTachoPixels (rpm);

#ifdef INCLUDE_DEBUG
    if (debugTacho == 3)
     {
      Serial.print(F("updateTachoDisplay RPM      "));
      Serial.println(buffer);
      Serial.print(F("tachoStep   "));
      Serial.println(tachoStep);
     }
#endif
   }
 }


/*
 * Sets KPH,MPH and CAL display
 * Displays current odometer distance at eighth character of top row of 16x2 white on black LCD
 *
 */

void displayOdometer () {

  char buffer[17] = "";


#ifdef ODOMETER_1602
  // cursor to the first character of top row
  odo1602.setCursor(0,0);

  if (modeSpeedoFunc == FUNC_KPH)
   {
    odo1602.print("KPH");
   }
  else if (modeSpeedoFunc == FUNC_MPH)
   {
    odo1602.print("MPH");
   }
  else if (modeSpeedoFunc == FUNC_CAL)
   {
    odo1602.print("CAL");
   }

// cursor to eighth character of top line
  odo1602.setCursor(7, 0);

  float odo = (extEepromOdometer.totalOdometer * pulseDistance) / 1000.0;
  if (odo > 999999.9)
   {
     odo = 0.0;
     extEepromOdometer.totalOdometer = 0;
   }

  dtostrf(odo,9,1,buffer);
  odo1602.print(buffer);

  #ifdef INCLUDE_DEBUG
  if (debugSpeedo == 3)
   {
    Serial.print(F("1602 Odo    "));
    Serial.println (buffer);
   }
  #endif
#endif


#ifdef ODOMETER_OLED_128x64

  oledOdometer.setFontSize(FONT_SIZE_SMALL);

  oledOdometer.setCursor(ODO_POSITION_01+1, 0);

  if (modeSpeedoFunc == FUNC_KPH)
   {
    oledOdometer.print("KPH ");
   }
  else if (modeSpeedoFunc == FUNC_MPH)
   {
    oledOdometer.print("MPH ");
   }
  else if (modeSpeedoFunc == FUNC_CAL)
   {
    oledOdometer.print("CAL ");
   }

  oledOdometer.setCursor(ODO_POSITION_02, 2);
  oledOdometer.setFontSize(FONT_SIZE_XLARGE);
  
  float odo = (float)extEepromOdometer.totalOdometer / speedoCalibrate;

//  odo = 999999.8;

  if (odo > 999999.9)
   {
     odo = 0.0;
     extEepromOdometer.totalOdometer = 0;
   }

  dtostrf(odo,9,1,buffer);
  oledOdometer.print(buffer);

  #ifdef INCLUDE_DEBUG
  if (debugSpeedo == 3)
   {
    Serial.print(F("oled Odo    "));
    Serial.println (buffer);

    sprintf(buffer, "%20d", extEepromOdometer.totalOdometer);
    Serial.print(F("oled extEepromOdometer.totalOdometer    "));
    Serial.println (buffer);

    dtostrf(pulseDistance,9,1,buffer);
    Serial.print(F("oled pulseDistance    "));
    Serial.println (buffer);
   }
  #endif

#endif

 }

/*
 * Displays tripmeter 1 at third digit of lower row of 16x2 white on black LCD
 * Displays tripmeter 2 at twelth digit of lower row of 16x2 white on black LCD
 *
 */

void displayTripmeter () {

  char buffer[6] = "";

#ifdef ODOMETER_1602

// cursor to third character of bottom line
  odo1602.setCursor(2, 1);

  float odo = (totalTrip_1 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_1 = 0;
   }

  dtostrf(odo,5,1,buffer);
  odo1602.print(buffer);

#ifdef INCLUDE_DEBUG
  if (debugSpeedo == 1)
   {
    Serial.print(F("Trip_1    "));
    Serial.println (buffer);
   }
#endif

// cursor to twelth character of bottom line

  odo1602.setCursor(11, 1);

  odo = (totalTrip_2 * pulseDistance) / 1000.0;
  
  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_2 = 0;
   }


  dtostrf(odo,5,1,buffer);
  odo1602.print(buffer);

#ifdef INCLUDE_DEBUG
  if (debugSpeedo == 1)
   {
    Serial.print(F("Trip_2    "));
    Serial.println (buffer);
   }
#endif

  if (!modeTrip)
   {
    // second character of bottom row
    odo1602.setCursor(1, 1);
    odo1602.print(tripActive);

    // eleventh character of bottom row
    odo1602.setCursor(10, 1);
    odo1602.print(" ");
   }
  else
   {
    // second character of bottom row
    odo1602.setCursor(1, 1);
    odo1602.print(" ");

    // eleventh character of bottom row
    odo1602.setCursor(10, 1);
    odo1602.print(tripActive);
   }
#endif

#ifdef ODOMETER_OLED_128x64

  oledOdometer.setFontSize(FONT_SIZE_SMALL);
  oledOdometer.setCursor(ODO_POSITION_01, 6);

  if (modeTrip)
   {
    oledOdometer.print(F("1"));
   }
  else
   {
    oledOdometer.print(F("1-"));
   }

  float odo = (float)totalTrip_1 / speedoCalibrate;

//  odo = 999.1;

  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_1 = 0;
   }

  dtostrf(odo,5,1,buffer);
  oledOdometer.setFontSize(FONT_SIZE_MEDIUM);
  oledOdometer.setCursor(ODO_POSITION_01 + 15, 6);
  oledOdometer.print(buffer);
  
#ifdef INCLUDE_DEBUG
  if (debugSpeedo == 3)
   {
    Serial.print(F("Trip_1    "));
    Serial.println (buffer);
   }
#endif

  oledOdometer.setFontSize(FONT_SIZE_SMALL);
  oledOdometer.setCursor(ODO_POSITION_03-22, 6);
  if (modeTrip)
   {
    oledOdometer.print(F("2-"));
   }
  else
   {
    oledOdometer.print(F("2"));
   }

  odo = (float)totalTrip_2 / speedoCalibrate;

//  odo = 999.1;

  if (odo > 999.9)
   {
     odo = 0.0;
     totalTrip_1 = 0;
   }

  dtostrf(odo,5,1,buffer);
  oledOdometer.setFontSize(FONT_SIZE_LARGE);
  oledOdometer.setCursor(ODO_POSITION_03-7, 6);
  oledOdometer.print(buffer);

  #ifdef INCLUDE_DEBUG
  if (debugSpeedo == 3)
   {
    Serial.print(F("Trip_2    "));
    Serial.println (buffer);
   }
  #endif
#endif


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

//#ifdef ODOMETER_1602

// top line shows current function mode setting (KPH, MPH or CAL)
// cursor to the first character of the top line

  // cursor to the first character of top row

  odo1602.setCursor(0, 0);
  odo1602.print(F("KPH    0000000.0"));

// bottom line shows tripmeters with current one highlighted
// cursor to first character of bottom line

  odo1602.setCursor(0, 1);
  odo1602.print(F("1 000.0  2 000.0"));

//#endif
//#ifdef ODOMETER_OLED_128x64

//#endif

// display current Odometer reading  
  displayOdometer();

// display current tripmeter readings
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

#ifdef INCLUDE_DEBUG
  if (debugGauges > 0)
   {
    Serial.println(F("Updating display voltmeter, oil pressure gauge, water temperature gauge, fuel level gauge"));
   }
#endif

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

#ifdef INCLUDE_DEBUG
  if (debugGauges > 0)
   {
    Serial.println(buffer);
   }
#endif

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

#ifdef INCLUDE_DEBUG
  if (debugGauges > 0)
   {
    dtostrf(v2, 4, 1, buffer);
    Serial.println(buffer);
   }
#endif

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

#ifdef INCLUDE_DEBUG
  if (debugGauges > 0)
   {
    dtostrf(v2, 4, 1, buffer);
    Serial.println(buffer);
   }
#endif

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

#ifdef INCLUDE_DEBUG
  if (debugGauges > 0)
   {
    dtostrf(v2, 4, 1, buffer);
    Serial.println(buffer);
   }
#endif

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

#define POSITION_01 0
#define POSITION_02 100

#if !defined(ODOMETER_OLED_128x64) && defined(INCLUDE_DIAGNOSTIC_OLED)

void printDiagnostics()
 {
  oledDiagnostic.setCursor(POSITION_01, 0);
  sprintf(buffer, "%4d", speed);
  oledDiagnostic.print("Speed");
  oledDiagnostic.setCursor(POSITION_02, 0);
  oledDiagnostic.print(buffer);

  sprintf(buffer, "%6d", rpm);
  oledDiagnostic.setCursor(POSITION_01, 1);
  oledDiagnostic.print("RPM ");
  oledDiagnostic.setCursor(POSITION_02-12, 1);
  oledDiagnostic.print(buffer);

/*  

  Serial.print("diagnostics rpm = ");
  Serial.println(rpm);
*/

  dtostrf(float(voltVal)/10, 4, 1, buffer);
  oledDiagnostic.setCursor(POSITION_01, 4);
  oledDiagnostic.print("Battery Voltage ");
  oledDiagnostic.setCursor(POSITION_02, 4);
  oledDiagnostic.print(buffer);

  dtostrf(float(oilVal)/10, 4, 1, buffer);
  oledDiagnostic.setCursor(POSITION_01, 3);
  oledDiagnostic.print("Oil Pressure ");
  oledDiagnostic.setCursor(POSITION_02, 3);
  oledDiagnostic.print(buffer);

  dtostrf(float(tempVal)/10, 4, 1, buffer);
  oledDiagnostic.setCursor(POSITION_01, 2);
  oledDiagnostic.print("Temperature ");
  oledDiagnostic.setCursor(POSITION_02, 2);
  oledDiagnostic.print(buffer);

  dtostrf(float(fuelVal)/10, 4, 1, buffer);
  oledDiagnostic.setCursor(POSITION_01, 5);
  oledDiagnostic.print("Fuel Level");
  oledDiagnostic.setCursor(POSITION_02, 5);
  oledDiagnostic.print(buffer);


  if (magnetometerAvailable)
   {
    oledDiagnostic.setCursor(POSITION_01, 6);
    oledDiagnostic.print("Heading");
    sprintf(buffer, "%4d", getHeading());
    oledDiagnostic.setCursor(POSITION_02, 6);
    oledDiagnostic.print(buffer);
   }
 }

#endif




void updateDisplay() {
  setBrightness();

  updateTachoDisplay();

  //update odometer
  displayOdometer();

//update tripmeters
  displayTripmeter();

  updateMetersDisplay();

#if !defined(ODOMETER_OLED_128x64) && defined(INCLUDE_DIAGNOSTIC_OLED)
  if (oledAvailable)
   {
    printDiagnostics();
   }
#endif


#ifdef INCLUDE_BLUETOOTH
  if (bluetoothAvailable)
   {
    printBluetooth();
   }
#endif



// toggle pin 13 led for  debugging
    arduinoLed = !arduinoLed;
    digitalWrite(13, arduinoLed);



}


