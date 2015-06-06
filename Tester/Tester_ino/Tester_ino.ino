// Tester.ino

#include <Arduino.h>

#include "Button.h"


// the tone value
volatile int toneValue = 30;

// the output pin
static const byte pinVss = 5;

// the button pin
static const byte pinModeButton = 7;

// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);

void buttonModePressed() {

  noTone(pinVss);
  toneValue++;
  if (toneValue > 500)
   {
    toneValue = 30;
   }

  Serial.print("toneValue = ");
  Serial.println(toneValue);

}

void buttonModeLongPressed() {

  noTone(pinVss);
  toneValue += 10;
  if (toneValue > 500)
   {
    toneValue = 30;
   }

  Serial.print("toneValue = ");
  Serial.println(toneValue);
}

void setup () {
  Serial.begin(9600);
  
  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);

  buttonMode.setLongPressHandler(buttonModeLongPressed);

}


void loop () {

  buttonMode.check();
  tone(pinVss, toneValue);
  delay(100);

}

