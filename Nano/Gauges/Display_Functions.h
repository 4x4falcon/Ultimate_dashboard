//Display_Functions.h


// set the display brightness depending on headlight state

void setBrightness()
 {
   byte b = brightnessBoost;

   if (digitalRead(pinLightsOn))
    {
     b = 2 * brightnessBoost;
     if (debug == 1)
      {
       Serial.print("Lights on  ");
       Serial.println(b);
      }
    }
   else
    {
     b= 15 * brightnessBoost;
     if (debug == 1)
      {
       Serial.print("Lights off  ");
       Serial.println(b);
      }
    }

   voltSerial.write(0x7A);
   voltSerial.write(b);
   oilSerial.write(0x7A);
   oilSerial.write(b);
   tempSerial.write(0x7A);
   tempSerial.write(b);
   fuelSerial.write(0x7A);
   fuelSerial.write(b);
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

// a buffer for the values
  char b[5];


  setBrightness();

  if (debug == 3)
   {
    Serial.println("Updating display voltmeter, oil pressure gauge, water temperature gauge, fuel level gauge");
   }

// flash the onboard led to show it's working correctly
  arduinoLed = !arduinoLed;
  digitalWrite(pinLed, arduinoLed);

#define SAMPLES 3

// voltmeter
  val = 0.0;

  for (int i=0; i< SAMPLES ; i++) val += analogRead(voltAnalogPin);
  val /= SAMPLES;

  float v = (val * 5.0) / (voltUpper - voltLower);
  float v2 = v / (r2 / (r1 + r2));

  voltVal = int(v * 10);
//  sprintf(b, "%4d", int(v2 * 10));
  sprintf(b, "%4d", voltVal);

  if (debug == 3)
   {
    Serial.println(b);
   }

  voltSerial.print(b);             // write the value to the display
  voltSerial.write(0x77);
  voltSerial.write(0b00000100);  // sets digit 3 decimal on


// oil pressure meter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(oilAnalogPin);
  val /= SAMPLES;

  v = (val * 5.0) / (oilUpper - oilLower);
//  v2 = v / (r2 / (r1 + r2));
  oilVal = int(v * 10);

  sprintf(b, "%4d", oilVal);

  if (debug == 3)
   {
    Serial.println(b);
   }

  oilSerial.print(b);             // write the value to the display
  oilSerial.write(0x77);
  oilSerial.write(0b00000100);  // sets digit 3 decimal on

  
// water temperature meter
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(tempAnalogPin);
  val /= SAMPLES;

  v = (val * 5.0) / (tempUpper - tempLower);
//  v2 = v / (r2 / (r1 + r2));

  tempVal = int (v * 10);
  
  sprintf(b, "%4d", tempVal);

  if (debug == 3)
   {
    Serial.println(b);
   }

  tempSerial.print(b);             // write the value to the display
  tempSerial.write(0x77);
  tempSerial.write(0b00000100);  // sets digit 3 decimal on


// fuel level meter display
  val = 0.0;
  for (int i=0; i< SAMPLES ; i++) val += analogRead(fuelAnalogPin);
  val /= SAMPLES;

  v = (val * 5.0) / (tempUpper - tempLower);
//  v2 = v / (r2 / (r1 + r2));

  fuelVal = int(v * 10);
  sprintf(b, "%4d", fuelVal);

  if (debug == 3)
   {
    Serial.println(b);
   }

  fuelSerial.print(b);             // write the value to the display
  fuelSerial.write(0x77);
  fuelSerial.write(0b00000100);  // sets digit 3 decimal on

}


void buttonModePressed() {

  
  Serial.println("Mode button pressed");
  
}

void buttonModeLongPressed() {


  Serial.println("Mode button long pressed");

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


void displayValue(SoftwareSerial d, char b, byte p) {

  d.write(0x76);
  d.print(b);
}

