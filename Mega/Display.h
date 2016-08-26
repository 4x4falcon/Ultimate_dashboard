// Display.h

// Set the display brightness

void setBrightness() {

if (!digitalRead(pinLightsOn))      // confirm that this is low when completing circuit
   {
// set brightness to mid range when headlights are on
    pixelBrightness = 4;        // this sets up the brightness used in displayRpm routine
                                 // for the 7 segment display set it here as it will remain that way until changed
    tachoSerial.write(0x7A);
    tachoSerial.write(byte(80));

    odoSerial.write(0x7C);
    odoSerial.write(byte(80));

    speedoSerial.write(0x7A);
    speedoSerial.write(byte(1));
    
    voltSerial.write(0x7A);
    voltSerial.write(byte(80));
    oilSerial.write(0x7A);
    oilSerial.write(byte(80));
    tempSerial.write(0x7A);
    tempSerial.write(byte(80));
    fuelSerial.write(0x7A);
    fuelSerial.write(byte(80));

#ifdef ECHO_SERIAL
    Serial.println("Lights on");
#endif
   }
  else
   {
// set brightness to full on when headlights are off
    pixelBrightness = 12;        // this sets up the brightness used in displayRpm routine
                                 // for the 7 segment display set it here as it will remain that way until changed
    tachoSerial.write(0x7A);
    tachoSerial.write(byte(255));

    odoSerial.write(0x7C);
    odoSerial.write(byte(255));

    speedoSerial.write(0x7A);
    speedoSerial.write(byte(8));

    voltSerial.write(0x7A);
    voltSerial.write(byte(255));
    oilSerial.write(0x7A);
    oilSerial.write(byte(255));
    tempSerial.write(0x7A);
    tempSerial.write(byte(255));
    fuelSerial.write(0x7A);
    fuelSerial.write(byte(255));

   }

}


/*
 * Displays current speed on 4 DIGIT LED
 * TODO display on 15 led 1/4 neo ring
 */

void displaySpeed (int speed) {

//  char buffer[10];

  sprintf(buffer, "%4d", speed);
  speedoSerial.print(buffer);

#ifdef ECHO_SERIAL

  Serial.print ("Speed    ");
  Serial.println (speed);
  Serial.print ("Speed buffer    ");
  Serial.println(buffer);
#endif

  byte pixels = speed / 10;

  for(byte i=0;i<pixels;i++)
   {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    speedoPixels.setPixelColor(i, speedoPixels.Color(0,0,20)); // blue color.
    if (i >= 11)
     {
      speedoPixels.setPixelColor(i, speedoPixels.Color(20,0,0)); // red color.
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
  if (doSpeed)
   {
    doSpeed = !doSpeed;

#ifdef ECHO_SERIAL
  Serial.print("durationSpeedo   ");
  Serial.println(durationSpeedo);
  Serial.print("pulseMaxCount   ");
  Serial.println(pulseMaxCount);
  Serial.print("pulseDistance   ");
  Serial.println(pulseDistance);
#endif

    speed = int(((((1000.0 * float(pulseMaxCount)) / float(durationSpeedo)) * pulseDistance) * 3600.0) / 1000.0);
    displaySpeed(speed);

// toggle pin 13 led for  debugging
    arduinoLed = !arduinoLed;
    digitalWrite(13, arduinoLed);
   }
}

// TACHO display
void updateTachoDisplay() {

  if (doTacho)
   {
    doTacho = !doTacho;
    rpm = 1101;

//    rpm = (pps * 60) / tachoPPR;

    float v1 = (float(durationTacho) / float(pulseMaxCount));

    rpm = int( ((1000.0 / v1) * 60) / tachoPPR );

#ifdef ECHO_SERIAL

    Serial.print("v1      ");
    Serial.println(v1);

    Serial.print("rpm     ");
    Serial.println(rpm);

#endif

//    displayRpm(rpm);

//  char buffer[6];
    byte pixels = rpm / tachoStep;                 // needs to be a function of max tacho reading
    byte redLine = tachoRedline / tachoStep;

    if (rpm > 9999)
     {
      rpm /= 100;
      sprintf(buffer, "%3d-", rpm);		   // always display last digit as 0 stops jitter
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
}



/*
 * Sets KPH,MPH and CAL display
 * Displays current odometer distance at eighth character of top row of 16x2 white on black LCD
 *
 */

void displayOdometer () {

  char buffer[17] = "";
  
  odoSerial.write(254);    // cursor to the first character of top row
  odoSerial.write(128);

  if (modeSpeedoFunc == FUNC_KPH)
   {
    odoSerial.print("KPH");
   }
  else if (modeSpeedoFunc == FUNC_MPH)
   {
    odoSerial.print("MPH");
   }
  else if (modeSpeedoFunc == FUNC_CAL)
   {
    odoSerial.print("CAL");
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

  char buffer[6] = "";

// cursor to the first character of bottom line

//  odoSerial.write(254);
//  odoSerial.write(192);

//  odoSerial.print("1        2      ");

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

#ifdef ECHO_SERIAL

  Serial.print ("Trip_1    ");
  Serial.println (buffer);

#endif

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

#ifdef ECHO_SERIAL

  Serial.print ("Trip_2    ");
  Serial.println (buffer);

#endif

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



void updateMetersDisplay() {
  // GAUGES display

#ifdef ECHO_SERIAL
  Serial.println("Updating display voltmeter, oil pressure gauge, water temperature gauge, fuel level gauge");
#endif

#define SAMPLES 3

// voltmeter
// does not need maximum/minimum values as is based on voltage divider
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(voltAnalogPin);
  val /= SAMPLES;

  float v = (val * 5.0) / 1024;
  float v2 = v / (r2 / (r1 + r2));
#ifdef ECHO_SERIAL
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);
#endif

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  voltSerial.print(buffer);             // write the value to the display

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

//  float v = (val * 5.0) / 1024;
//  float v2 = v / (r2 / (r1 + r2));
#ifdef ECHO_SERIAL
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);
#endif

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  oilSerial.print(buffer);             // write the value to the display

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

//  float v = (val * 5.0) / 1024;
//  float v2 = v / (r2 / (r1 + r2));
#ifdef ECHO_SERIAL
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);
#endif

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  tempSerial.print(buffer);             // write the value to the display
  
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

//  float v = (val * 5.0) / 1024;
//  float v2 = v / (r2 / (r1 + r2));
#ifdef ECHO_SERIAL
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);
#endif

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  fuelSerial.print(buffer);             // write the value to the display

// check for voltage warning
  if (fuelWarnLow)
   {
    
   }
  else
   {
    
   }
  
}




void updateDisplay() {

  updateTachoDisplay();

  //update odometer
  displayOdometer();

//update tripmeters
  displayTripmeter();

  updateMetersDisplay();
  setBrightness();
}

