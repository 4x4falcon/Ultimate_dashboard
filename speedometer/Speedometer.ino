#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>
#include "Button.h"
#include "Timer.h"
#include "Constants.h"
#include "Variables.h"

/*
* Initialization
*/
void setup() {
  Serial.begin(9600);
  
  // Attach interrupt for the hall effect sensor
  attachInterrupt(0, sensorTriggered, FALLING);
  
  // Read odometer value from flash memory
  totalMiles = EEPROM.readFloat(0x0);
  
  // Intialize LED display
  alpha.begin(0x70);
  alpha.writeDisplay();
  
  // Update the display every 100ms
  timer.every(100, updateDisplay);
  
  // Set up button handlers
  button.setPressHandler(buttonPressed);
  button.setLongPressHandler(buttonLongPressed);
}

/*
* Main loop
*/
void loop() {
  loopTime = millis();
  
  timer.update();
  
  button.check();
  
  writeOdometer();
  
  checkForTimeout();
}

/*
* Checks the last time the sensor was trigerred. If it's over a given
* duration, we assume the wheel has stopped spinning.
*/
void checkForTimeout() {
  if (loopTime - lastTrigger > timeoutValue) {
    rps = 0.0;
  }
}

/*
* Writes total miles to EEPROM
*/
void writeOdometer() {
  if (loopTime - lastOdometerWrite > odometerWriteFrequency) {
    EEPROM.writeFloat(0x0, totalMiles);
    lastOdometerWrite = loopTime;
  }
}

/*
* Updates the screen depending on the current mode
*/
void updateDisplay() {
  if (mode == MODE_SPEEDOMETER) {
    float fps = wheelCircumference * rps;
    int mph = (int)((fps / 5280.0) * 3600.0);
    displayNumber(mph, 0, 1);
  }
  else if (mode == MODE_ODOMETER) {
    int value = floatToInt(totalMiles, 2);
    displayNumber(value, 1, 3);
  }
}

/*
* Toggle between speedometer and odometer when button is pressed
*/
void buttonPressed() {
  mode = !mode;
}

/*
* Reset odometer when button is long-pressed
*/
void buttonLongPressed() {
  if (mode == MODE_ODOMETER) {
    EEPROM.writeFloat(0, totalMiles = 0.0);
  }
}

/*
* Writes each digit of a number to the LED screen with decimal point
* and minimum number of digits.
*/
void displayNumber(int value, int decimalPos, int minDigits) {
  int divisor = pow(10, numDigits-1);
  for(int i = 0; i < numDigits; i++) {
    int digit = (value / divisor) % 10;
    if (value < divisor && i < numDigits-minDigits) {
      alpha.writeDigitRaw(i, segmentValues[BLANK]);
    }
    else {
      uint16_t segments = segmentValues[digit];
      if (decimalPos > 0 && i == decimalPos) {
        segments |= segmentValues[DECIMAL];
      }
      alpha.writeDigitRaw(i, segments);
    }
    divisor /= 10;
  }
  alpha.writeDisplay();
}

/*
* Converts a floating point number to an integer for display on the LED screen
*/
int floatToInt(float value, int decimalPlaces) {
  int shift = pow(10, decimalPlaces);
  int whole = (int)value;
  int fraction = (value - (float)whole) * shift;
  return (whole * shift) + fraction;
}

/*
* ISR attached to the hall effect sensor; triggered each time the magnet
* passes by the sensor
*/
void sensorTriggered() {
  unsigned long duration = millis() - lastTrigger;
  if (duration > 0) {
    rps = 1000.0 / duration; // Update rotations per second
    totalMiles += (wheelCircumference / 5280.0); // Increment odometer
  }
  lastTrigger = millis();
}

