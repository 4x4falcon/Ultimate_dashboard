/*
 * demo functions
 */


void gaugesDemo(byte d)
 {
  int r =  1;

   i2c_s7s_ClearDisplay(I2C_ADDRESS_VOLT);
   i2c_s7s_ClearDisplay(I2C_ADDRESS_OIL);
   i2c_s7s_ClearDisplay(I2C_ADDRESS_TEMP);
   i2c_s7s_ClearDisplay(I2C_ADDRESS_FUEL);

  if (d == 1)     // display each decimal, apostrophe and colon
   {
    while (r < 64)
     {
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_VOLT, r);
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_OIL, r);
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_TEMP, r);
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_FUEL, r);

      r *= 2;
      delay(1000);
     }
   }

  if (d == 2)       // display each segment
   {
    while (r < 128)
     {
      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_1_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_2_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_3_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_4_CONTROL, r);
      
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL, DIGIT_1_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL, DIGIT_2_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL, DIGIT_3_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL, DIGIT_4_CONTROL, r);

      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_1_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_2_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_3_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_4_CONTROL, r);

      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_1_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_2_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_3_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_4_CONTROL, r);

      r *= 2;
      delay(500);
     }
   }
  if ((d == 3) || (d == 10))      // random bits
   {

//Seed random generator with analog input - nothing needs to be connected to A7
    randomSeed(analogRead(7));

    while (r < 32)
     {

      for(int x = 0 ; x < 4 ; x++)
       {
        byte randNumber = random(0, 127);    //Give me random number between 0 and 127
        i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_1_CONTROL + x, randNumber);        //Control individual segments on a digit, Turn on random segments
        i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL, DIGIT_1_CONTROL + x, randNumber);        //Control individual segments on a digit, Turn on random segments
        i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_1_CONTROL + x, randNumber);        //Control individual segments on a digit, Turn on random segments
        i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_1_CONTROL + x, randNumber);        //Control individual segments on a digit, Turn on random segments
       }

      r += 1;
      delay(1500/d);
     }
   }

  if (d == 4)      // countdown predator
   {

    r = 127;

    while (r >= 0)
     {
      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_1_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL,  DIGIT_1_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_1_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_1_CONTROL, r);

      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_2_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL,  DIGIT_2_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_2_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_2_CONTROL, r);

      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_3_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL,  DIGIT_3_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_3_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_3_CONTROL, r);

      i2c_s7s_SendDigitControl(I2C_ADDRESS_VOLT, DIGIT_4_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_OIL,  DIGIT_4_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_TEMP, DIGIT_4_CONTROL, r);
      i2c_s7s_SendDigitControl(I2C_ADDRESS_FUEL, DIGIT_4_CONTROL, r);

      r -= 1;
      delay(500);
     }
   }


  delay(1000);

  i2c_s7s_ClearDisplay(I2C_ADDRESS_VOLT);
  i2c_s7s_SendDecimalControl(I2C_ADDRESS_VOLT, S7S_DIGIT_3_POINT);

  i2c_s7s_ClearDisplay(I2C_ADDRESS_OIL);
//  i2c_s7s_SendDecimalControl(I2C_ADDRESS_OIL, S7S_DIGIT_3_POINT);

  i2c_s7s_ClearDisplay(I2C_ADDRESS_TEMP);
//  i2c_s7s_SendDecimalControl(I2C_ADDRESS_TEMP, S7S_DIGIT_3_POINT);

  i2c_s7s_ClearDisplay(I2C_ADDRESS_FUEL);
//  i2c_s7s_SendDecimalControl(I2C_ADDRESS_FUEL, S7S_DIGIT_3_POINT);

}


void tachoDemo(byte d)
 {

  int r =  0;
  char b[5];
  i2c_s7s_ClearDisplay(I2C_ADDRESS_TACHO);

  while (r < (tachoRedline + 1500))
   {
    r += 100;

    sprintf(b, "%4d", r);

    i2c_SendString_4(I2C_ADDRESS_TACHO, b);

    if (r >= tachoRedline)
     {
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, S7S_DIGIT_A_POINT);
     }
    else
     {
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, 0b00000000);
     }

    if (r >= tachoShift)
     {
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, S7S_DIGIT_APOST);
     }
    else
     {
      i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, 0b00000000);
     }

    displayTachoPixels(r);
    delay(1000/d);
   }

  delay(1000);

  if (d >= 4)
   {
    while (r > 0)
     {
      r -= 100;

      sprintf(b, "%4d", r);
      i2c_SendString_4(I2C_ADDRESS_TACHO, b);

      if (r >= tachoRedline)
       {
        i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, S7S_DIGIT_A_POINT);
       }
      else
       {
        i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, 0b00000000);
       }

      if (r >= tachoShift)
       {
        i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, S7S_DIGIT_APOST);
       }
      else
       {
        i2c_s7s_SendDecimalControl(I2C_ADDRESS_TACHO, 0b00000000);
       }

      displayTachoPixels(r);
      delay(1000/d);
     }

   }
  
  i2c_s7s_ClearDisplay(I2C_ADDRESS_TACHO);
  displayTachoPixels(0);
 }


void speedoDemo(byte d)
 {

  int r =  0;

  while (r < 160)
   {
    r += 1;

    displaySpeed(r);
    delay(1000/d);
   }

  delay(1000);

  if (d >= 4)
   {
    while (r > 0)
     {
      r -= 1;

      displaySpeed(r);
      delay(1000/d);
     }

   }
 }


void odometerDemo(byte d)
 {

  unsigned long r = 0;
  unsigned long t = 0;

  unsigned long tempOdoEeprom = extEepromOdometer.totalOdometer;
  unsigned long tempOdo = odometerCounter;
  unsigned long tempTrip_1 = totalTrip_1;
  unsigned long tempTrip_2 = totalTrip_2;

  while (r < 4000000000)
   {

#ifdef DEBUGGING
    Serial.print("odometerDemo  ");
    Serial.println(r);
#endif

    odometerCounter = r;

    displayOdometer();

    totalTrip_1 = 100;
    totalTrip_2 = 120;

    displayTripmeter();

    t++;
    r += 10000000;
   }

  extEepromOdometer.totalOdometer = tempOdoEeprom;
  odometerCounter = tempOdo;
  totalTrip_1 = tempTrip_1;
  totalTrip_2 = tempTrip_2;

 }


