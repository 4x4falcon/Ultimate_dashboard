//Display_Functions.h



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

#ifdef ECHO_SERIAL
  Serial.println("Updating display voltmeter, oil pressure gauge, water temperature gauge, fuel level gauge");
#endif
  // flash the onboard led to show it's working correctly
  arduinoLed = !arduinoLed;
  digitalWrite(pinLed, arduinoLed);

  char buffer[10];

// voltmeter
//  int val = volt_meter.read();

#define SAMPLES 3

  float val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += volt_meter.read();
  val /= SAMPLES;

  float v = (val * 5.0) / 1024;
  float v2 = v / (r2 / (r1 + r2));
  dtostrf(v2, 4, 1, buffer);
  volt_meter.display(buffer);

// oil pressure meter
  val = oil_meter.read();

  sprintf(buffer, "%4i", val);
  
  oil_meter.display(buffer);
  
  val = temp_meter.read();
  
  sprintf(buffer, "%4i", val);

  temp_meter.display(buffer);
  
  val = fuel_meter.read();
  
  sprintf(buffer, "%4i", val);

  fuel_meter.display(buffer);
  
}




