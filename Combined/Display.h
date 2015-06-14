// Display.h

// Set the display brightness

// TODO move all display changes to here rather than different files

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

void updateMetersDisplay() {
  // GAUGES display
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
