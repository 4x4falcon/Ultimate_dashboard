// Tester.ino

#include <Arduino.h>

#include "Button.h"
#include "Timer.h"

// the speedo tone value
volatile int toneSpeedoValue = 40;
volatile int toneSpeedoStep = 10;
const int toneSpeedoMax = 600;
const int toneSpeedoMin = 40;

// the tacho tone value
volatile int toneTachoValue = 50;
volatile int toneTachoStep = 10;
const int toneTachoMax = 1000;
const int toneTachoMin = 40;


// the speedo output pin
static const byte pinVss = 5;

// the tacho output pin
static const byte pinTacho = 6;

// the button pin
static const byte pinModeButton = 7;

// the mode led pin
static const byte pinModeLed = 8;

// function modes
static const byte modeSpeedo = 0;
static const byte modeTacho = 0;

// the function modes
static byte MODE_SPEEDO = 0;
static byte MODE_TACHO = 1;

// function mode
volatile byte modeFunction = MODE_SPEEDO;


// update timer

Timer timer = Timer();
static long updateTime = 5000;

// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, LOW, 3000);

void buttonModePressed() {

  modeFunction = !modeFunction;
  digitalWrite(pinModeLed, modeFunction);
  toneSpeedoValue = toneSpeedoMin;
  toneTachoValue = toneTachoMin;
}

void buttonModeLongPressed() {

//  modeFunction = !modeFunction;
  digitalWrite(pinModeLed, modeFunction);
  toneSpeedoValue = toneSpeedoMax;
  toneTachoValue = toneTachoMax;
}


void doSpeedo() {
  Serial.print("Speedo output     ");
  Serial.println(toneSpeedoValue);
  noTone(pinVss);
  tone(pinVss, toneSpeedoValue);
}

void doTacho() {
  Serial.print("Tacho output    ");
  Serial.println(toneTachoValue);

  noTone(pinTacho);
  tone(pinTacho, toneTachoValue);
}

void updateOutput() {
 
  
  Serial.print("modeFunction = ");
  Serial.println(modeFunction);

  toneSpeedoValue += toneSpeedoStep;
  if ((toneSpeedoValue > toneSpeedoMax) || (toneSpeedoValue < toneSpeedoMin))
   {
    toneSpeedoStep = toneSpeedoStep * -1;
   }
  toneTachoValue += toneTachoStep;
  if ((toneTachoValue > toneTachoMax) || (toneTachoValue < toneTachoMin))
   {
    toneTachoStep = toneTachoStep * -1;
   }


  if (modeFunction == MODE_SPEEDO)
   {
    noTone(pinTacho);
    doSpeedo();
   }
  else
   {
    noTone(pinVss);
    doTacho();
   }
}


/*
 * setup
 */

void setup () {
  Serial.begin(9600);

  pinMode(pinVss, OUTPUT);
  pinMode(pinTacho, OUTPUT);
  pinMode(pinModeLed, OUTPUT);
  pinMode(pinModeButton, INPUT_PULLUP);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);

  buttonMode.setLongPressHandler(buttonModeLongPressed);

  timer.every(updateTime, updateOutput);
}

/*
 * main loop
 */

void loop () {

  buttonMode.check();
  timer.update();
}

