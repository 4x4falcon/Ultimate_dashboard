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

// set brightness on 7 segment displays via I2C

  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_VOLT, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_OIL, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_TEMP, b);
  i2c_s7s_SetDisplayBrightness(I2C_ADDRESS_FUEL, b);

/*
   voltSerial.write(0x7A);
   voltSerial.write(b);
   oilSerial.write(0x7A);
   oilSerial.write(b);
   tempSerial.write(0x7A);
   tempSerial.write(b);
   fuelSerial.write(0x7A);
   fuelSerial.write(b);
*/
 }


/*
 *
 *
 */

void displayCalibrateCount (int count) {
						// TODO need function to show calibrate count


}


/*
 * show names on gauges at startup
 */

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



/*
 *
 * Update the gauge displays
 * reads the analog pins for each gauge, converts to display figure and then sends to the display
 *
 */

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





/*
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
*/


void buttonModePressed(Button& buttonModeButton) {

  
  Serial.println("Mode button pressed");
  
}

void buttonModeLongPressed(Button& buttonModeButton) {


  Serial.println("Mode button long pressed");

}

void buttonBrightnessPressed(Button& buttonBrightnessSw) {

  brightnessBoost++;
  if (brightnessBoost > 5)
   {
    brightnessBoost = 1;
   }
  
  Serial.println("Brightnes button pressed");
  
}

void buttonBrightnessLongPressed(Button& buttonBrightnessSw) {

  brightnessBoost = 5;

  Serial.println("Brightness button long pressed");

}

/*
 * below here may not be needed
 */
void displayValue(SoftwareSerial d, char b, byte p) {

  d.write(0x76);
  d.print(b);
}

