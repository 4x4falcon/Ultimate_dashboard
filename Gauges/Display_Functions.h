//Display_Functions.h


// set the display brightness depending on headlight state

void setBrightness()
 {
   if (!digitalRead(pinLightsOn))
    {
// set brightness to mid range when headlights are on
     voltSerial.write(0x7A);
     voltSerial.write(byte(60));
     oilSerial.write(0x7A);
     oilSerial.write(byte(60));
     tempSerial.write(0x7A);
     tempSerial.write(byte(60));
     fuelSerial.write(0x7A);
     fuelSerial.write(byte(60));
    }
   else
    {
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
 *
 *
 */

void displayCalibrateCount (int count) {
						// TODO need function to show calibrate count


}



/*
 *
 * Update the gauge displays
 * reads the analog pins for each gauge, converts to display figure and then sends to the display
 *
 */
 

void updateDisplay () {
  
  setBrightness();

#ifdef ECHO_SERIAL
  Serial.println("Updating display voltmeter, oil pressure gauge, water temperature gauge, fuel level gauge");
#endif
  // flash the onboard led to show it's working correctly
  arduinoLed = !arduinoLed;
  digitalWrite(pinLed, arduinoLed);

//  char buffer[10];

#define SAMPLES 3

// voltmeter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(voltAnalogPin);
  val /= SAMPLES;

  float v = (val * 5.0) / 1024;
  float v2 = v / (r2 / (r1 + r2));
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  voltSerial.print(buffer);             // write the value to the display


// oil pressure meter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(oilAnalogPin);
  val /= SAMPLES;

//  float v = (val * 5.0) / 1024;
//  float v2 = v / (r2 / (r1 + r2));
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  oilSerial.print(buffer);             // write the value to the display

  
// water temperature meter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(tempAnalogPin);
  val /= SAMPLES;

//  float v = (val * 5.0) / 1024;
//  float v2 = v / (r2 / (r1 + r2));
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  tempSerial.print(buffer);             // write the value to the display
  
// fuel level meter display
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(fuelAnalogPin);
  val /= SAMPLES;

//  float v = (val * 5.0) / 1024;
//  float v2 = v / (r2 / (r1 + r2));
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  fuelSerial.print(buffer);             // write the value to the display

}


