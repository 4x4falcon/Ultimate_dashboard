//Display_Functions.h


// set the display brightness depending on headlight state

void setBrightness()
 {
   if (digitalRead(pinLightsOn) == LOW)
    {
// set brightness to mid range when headlights are on
     volt_serial.write(0x7A);
     volt_serial.write(byte(60));
    }
   else
    {
     volt_serial.write(0x7A);
     volt_serial.write(byte(255));
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

  char buffer[10];

#define SAMPLES 3

// voltmeter
  float val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(voltAnalogPin);
  val /= SAMPLES;

  float v = (val * 5.0) / 1024;
  float v2 = v / (r2 / (r1 + r2));
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  volt_serial.print(buffer);             // write the value to the display


// oil pressure meter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(voltAnalogPin);
  val /= SAMPLES;

//  float v = (val * 5.0) / 1024;
//  float v2 = v / (r2 / (r1 + r2));
  dtostrf(v2, 4, 1, buffer);
  Serial.println(buffer);

  sprintf(buffer, "%4d", int(v2 * 10));  // setup as integer
  oil_serial.print(buffer);             // write the value to the display

  
// water temperature meter
//  temp_meter.print(buffer);
  
// fuel level meter display
//  fuel_meter.print(buffer);
  
}


